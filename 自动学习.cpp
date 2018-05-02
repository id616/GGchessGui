#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"

#include <sys/types.h>
#include <sys/timeb.h>



//�����ݿ��еõ�һ����У�Թ������
BOOL PgnGetOneCheckedGameFromSql(dispboard_t *pDis, sqlite3 *db){

	//1,��Sqlite
	//sqlite3 *db_pgn;
    char    *szErrMsg       = 0;
    int      nrow           = 0;
    int      ncolumn        = 0;
    int      rc             = -1;
    char    **azResult;
    char     sql[4096];

	int      id = -1;

	//rc = SqliteOpenDataBase(&db_pgn,L3_DB_PGN);

	//if(rc != SQLITE_OK) return rc;

	sprintf_s(sql,sizeof(sql),
		"SELECT pgnID FROM pgn WHERE isChecked = 1 AND isLearned <> 1 ORDER BY pgnID DESC");

	//"SELECT pgnID FROM pgn ORDER BY pgnID DESC");

	rc = sqlite3_get_table(db,sql,&azResult,&nrow,&ncolumn,&szErrMsg);

	if(rc != SQLITE_OK){
		LogOuts(szErrMsg);
		sqlite3_free(szErrMsg);
		//sqlite3_close(db_pgn);
		return rc;
	}

	for(int k = 1; k <= nrow; k++){
		id = atoi(azResult[ncolumn + 0]);
		break;
	}

	sqlite3_free_table(azResult);

	//sqlite3_close(db_pgn);

	if(id == -1){
		return id;
	}

	return PgnGetGameInfoFromSqliteById(pDis,id,db);

}

////////////////////////////////////////////////////////////////////////////
// �����ݿ��еõ��ܵĶԾ���
int PgnTotalGameNumFromSql(sqlite3 *db){

	//1,��Sqlite
	//sqlite3 *db_pgn;
	char    *szErrMsg = 0;
	int      nrow = 0;
	int      ncolumn = 0;
	int      rc = -1;
	char    **azResult;
	char     sql[4096];

	int      result;


	sprintf_s(sql, sizeof(sql),
		"SELECT COUNT(*) FROM pgn");

	rc = sqlite3_get_table(db, sql, &azResult, &nrow, &ncolumn, &szErrMsg);

	if (rc != SQLITE_OK){
		LogOuts(szErrMsg);
		sqlite3_free(szErrMsg);
		//sqlite3_close(db_pgn);
		return rc;
	}
	result = atoi(azResult[1]);

	sqlite3_free_table(azResult);

	return result;
}

////////////////////////////////////////////////////////////////////////////
// �����ݿ��еõ���û��У�ԵĶԾ���
int PgnTotalGameUncheckNumFromSql(sqlite3 *db){

	//1,��Sqlite
	//sqlite3 *db_pgn;
	char    *szErrMsg = 0;
	int      nrow = 0;
	int      ncolumn = 0;
	int      rc = -1;
	char    **azResult;
	char     sql[4096];

	int      result;


	sprintf_s(sql, sizeof(sql),
		"SELECT COUNT(*) FROM pgn WHERE isChecked = 0");

	rc = sqlite3_get_table(db, sql, &azResult, &nrow, &ncolumn, &szErrMsg);

	if (rc != SQLITE_OK){
		LogOuts(szErrMsg);
		sqlite3_free(szErrMsg);
		//sqlite3_close(db_pgn);
		return rc;
	}

	result = atoi(azResult[1]);

	sqlite3_free_table(azResult);

	return result;
}

/////////////////////////////////////////////////////////
// 
BOOL GetCheckedqipuAndLearn(dispboard_t * pDis, sqlite3 *db){

	TCHAR buf[512];
	int rc;
	//1, ���ȵõ�һ�ּ��������
	while(ThStat.isFillQk){
		Sleep(100);
	};
	rc = PgnGetOneCheckedGameFromSql(pDis,db);

	if(rc != SQLITE_OK){
		LogOut(_T("\n��ǰ�����û����У�Ե������\n"));
		return rc;
	}

	if(pDis->pgn->isChecked == 0 || pDis->pgn->isLearned == 1){
		LogOut(_T("\n����д�����һ��\n"));
		return -1;
	}

	//2, �ٽ�FENչ��һ��
	swprintf_s(buf, sizeof(buf) / sizeof(TCHAR), _T("\n����ѧϰ> ID:%d,N:%s,A:%s"),
		pDis->pgn->pid,pDis->pgn->note,pDis->pgn->pevent);

	LogOut(buf);

	if(PgnFenToPos(pDis,false) == FALSE){
		LogOut(_T("\n�о��ݲ���ѧϰ!!"));
		goto OutLearn;
	}

	//3, ��ʼѧϰ�岽
	PGN*        pgn    = pDis->pgn;
	position_t* pos    = pDis->pos;

	if(pgn->score == BOOK_NOT_RESULT){
		LogOut(_T("\nѧϰ����ֻ�û�е÷�"));
		return -1;
	}

	//4, 

    book_face_t last_face[1];
	book_face_t tmp_face[1];
	
	//last_face->info->rate  = pgn->rate;	
	//last_face->info->step  = pos->curStep;
	last_face->info->isuse = 1;

	

	//�õ���ǰ��B32
	GetMirrorOnlyB33(pos,last_face->f33);

	while(ThStat.isFillQk){
		Sleep(100);
	};
	int nextScore = GetPosBookScoreByAllNextPos(pos,MST->book);

	int num = 0;

	if(nextScore == BOOK_NOT_RESULT){
		last_face->info->result = pgn->score;
		nextScore = pgn->score;
	}
	else{
		last_face->info->result = nextScore;
	}


	memcpy(tmp_face,last_face,sizeof(book_face_t));

	//if(pos->curStep > BOOK_LEARN_NUM){			//ֻ��С��BOOK_LEARN_NUM�岽���ܴ������
	//	bk_SaveBookInfo(tmp_face,MST->book);		//�Ƚ���ǰ�ı���һ��
	//}


	//typedef enum {
	//	BOOK_VERY_BAD	= -2, 
	//	BOOK_LIT_BAD	= -1, 
	//	BOOK_BALANCE	=  0,
	//	BOOK_LIT_GOOD	=  1,
	//	BOOK_VERY_GOOD  =  2,
	//	BOOK_NOT_RESULT =  8
	//}Book_Sc;


	while(pos->curStep >= BOOK_MOVE_LEARN_PLY){
		UnMakePosMoveOnly(pos);
		tmp_face->info->result = tmp_face->info->result; //��������Ӧ�ı�
	}

	//tmp_face->info->step = pos->curStep;
	GetMirrorOnlyB33(pos,tmp_face->f33);

	while(ThStat.isFillQk){
		Sleep(100);
	};
	bk_SaveBookInfo(tmp_face,MST->book);		//�Ƚ���ǰ�ı���һ��

	while(pos->curStep > 0){

		UnMakePosMoveOnly(pos);
		GetMirrorOnlyB33(pos,tmp_face->f33);

		//tmp_face->info->step = pos->curStep;

		while(ThStat.isFillQk){
			Sleep(100);
		};
		bk_GetBookInfo(tmp_face,MST->book);				//�õ�ԭ�ȴ���ľ�����Ϣ

		//tmp_face->info->step = pos->curStep;			//���ӻ���ԭ����

		while(ThStat.isFillQk){
			Sleep(100);
		};
		nextScore = GetPosBookScoreByAllNextPos(pos,MST->book);

		if(nextScore == BOOK_NOT_RESULT){
			LogOut(_T("�����ˣ�������岽�Ҳ���!!"));
			return -1;
		}
		
		if(pos->side == WHITE){		//����������̫���Ҫrate,��Ҫisuse
			if(nextScore == BOOK_VERY_GOOD){
				tmp_face->info->isuse = 0;
				//tmp_face->info->rate  = 0;
			}
			else if(nextScore <= BOOK_BALANCE){
				tmp_face->info->isuse = 1;
				//if(tmp_face->info->rate == 0){
				//	tmp_face->info->rate = 1;
				//}
			}			
		}
		else{
			if(nextScore == BOOK_VERY_BAD){
				tmp_face->info->isuse		= 0;
				//tmp_face->info->rate		= 0;
			}
			else if(nextScore >= BOOK_BALANCE){
				tmp_face->info->isuse		= 1;
				//if(tmp_face->info->rate == 0){
				//	tmp_face->info->rate = 1;
				//}
			}
		}
		tmp_face->info->result = nextScore;

		while(ThStat.isFillQk){
			Sleep(100);
		};
		bk_SaveBookInfo(tmp_face,MST->book);		//�Ƚ���ǰ�ı���һ��

		num++;
	}


	//
	swprintf_s(buf, sizeof(buf) / sizeof(TCHAR), _T("\n �˾ֹ�ѧϰ��%d ������"), num);
	LogOut(buf);

OutLearn:

	//   ����ֱ��ѧϰ����
	pDis->pgn->isLearned = 1;

	while(ThStat.isFillQk){
		Sleep(100);
	};
    return PgnUpdateGameToSqlite(pDis,db);

}

/////////////////////////////////////////////////////////
//ѧϰ����������б�������,�Ѽ�����
DWORD WINAPI 
LearnAllFileGameThread(LPVOID lpParam){

    sqlite3 *db;
	TCHAR buf[256];

	int rc = SqliteOpenDataBase(&db,L3_DB_PGN);

	if(rc != SQLITE_OK){
		LogOut(_T("\n�����������ܴ�������ݿ�!\n"));
        goto OutLearn;
	}

	int num = 0;

	dispboard_t pDis[1];

	//pDis->gameMode   = PlayFromGameFile;

	ChangeGameMode(pDis,PlayFromGameFile);
	pDis->matchMode  = TRUE;						//�����߲��Ͳ��ᷢ����

    //Thread_Stat |= TH_Learning;						//��ǰ����ѧϰ
	ThStat.isLearn  = TRUE;
	ThStat.outLearn = FALSE;


	//if(Thread_Stat & TH_OutLearningOK){
	//	Thread_Stat ^= TH_OutLearningOK;           //
	//}

	while(GetCheckedqipuAndLearn(pDis,db) == SQLITE_OK && ThStat.isLearn == TRUE){
		num++;
	}

OutLearn:


	//if(Thread_Stat & TH_Learning){
	//	Thread_Stat ^= TH_Learning;
	//}

	if(ThStat.isLearn)	{
		ThStat.isLearn = FALSE;
	};


	//һ��Ҫ����������ݿ�
	sqlite3_close(db);

	swprintf_s(buf, sizeof(buf) / sizeof(TCHAR), _T("\nѧϰ��ɣ���ѧϰ�ˣ�%d ���!\n"), num);

	LogOut(buf);

	//TH_OutLearningOK
    
	//Thread_Stat |= TH_OutLearningOK;    //�ѳɹ��˳���ѧϰ״̬
	ThStat.outLearn = TRUE;

	return 0;
}

/////////////////////////////////////////////////////////
//���Զ�ѧϰ�߳�
void AutoLearnEvent(void){
	DWORD dwThreadId,dwThrdParam = 1;
	HANDLE hImport = CreateThread(
		NULL,
		NULL,
		LearnAllFileGameThread,
		&dwThrdParam,
		0,
		&dwThreadId);

	if(hImport == NULL){
		SendToPlayerByColor(_T("\n��ʼ��ѧϰ����߳�ʧ��!\n"), ColorShout, FALSE);
	}
	else{
		SendToPlayerByColor(_T("\n��ʼ��ѧϰ����̳߳ɹ�!\n"), ColorShout, TRUE);
	}
}


