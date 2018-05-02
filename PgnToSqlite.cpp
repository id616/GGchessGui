#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"
#include <sys/stat.h>
#include <io.h>
#include <fcntl.h>
#include <share.h>

//�鿴һ�£�PGN �岽�ڲ��ڵ�ǰ���ߵ��岽��
int getMoveFormPgnStr(dispboard_t* pDis, char* sspgnStr){


	position_t *pos = pDis->pos;

	char ss[32];
	TCHAR pgnStr[32];
	strCopybyNum(ss, 8, sspgnStr);
	ss[9] = 0;
	ss[10] = 0;
	swprintf_s(pgnStr, sizeof(pgnStr) / sizeof(TCHAR), _T("%S"), ss);	

	gen_legal_moves(pos);

	while(pos->pMend > pos->all_move){

		pos->pMend--;

		if(pos->His[pos->curStep].ischeck == FALSE){
			if(move_is_legal(pos,pos->pMend->move) == FALSE){
				continue;
			}			
		}		

		TCHAR  szStepName[16];
		GetMoveName(pos,szStepName, pos->pMend->move, appData.moveType);


		//��ǰ��8���ַ��ǲ���һ��
		BOOL find = TRUE;

		for(int i = 0; i < 4; i++){
			if(szStepName[i] != pgnStr[i]){
				find= FALSE;
				break;
			}
		}

		if(find == TRUE){
			return pos->pMend->move;
		}
	}

	return 0;
}

//��һ���ǲ��������PGN��ʽ
BOOL Is_TiJi_PGN(dispboard_t* pDis,char *pgnBuf){

	int len = (int)strlen(pgnBuf);


	//char *pstart;
	//char *pend;
	//size_t  size;

	//PGN* pgn = pDis->pgn;

 //   pstart = strstr(pgnBuf,"[Game ");
	//if(pstart != NULL){
	//	pend = strstr(pstart,"\"]");		

	//	if(pend != NULL){
	//		size = pend - pstart - 5;
	//		if(size < sizeof(pgn->note)){
	//			strCopybyNum(pgn->note,size,pstart + 5);
	//		}
	//	}
	//}

	//pstart = strstr(pgnBuf,"[Event ");
	//if(pstart != NULL){
	//	pend = strstr(pstart,"\"]");
	//	if(pend != NULL){
	//		size = pend - pstart - 6;
	//		if(size < sizeof(pgn->pevent)){
	//			strCopybyNum(pgn->pevent,size,pstart + 6);
	//		}
	//	}
	//}

	//pstart = strstr(pgnBuf,"[Red ");
	//if(pstart != NULL){
	//	pend = strstr(pstart,"\"]");
	//	if(pend != NULL){
	//		size = pend - pstart - 4;
	//		if(size < sizeof(pgn->Red)){
	//			strCopybyNum(pgn->Red,size,pstart + 4);
	//		}
	//	}
	//}

	//pstart = strstr(pgnBuf,"[RedElo ");
	//if(pstart != NULL){
	//	pend = strstr(pstart,"\"]");
	//	if(pend != NULL){
	//		//sprintf_s(pgn->Red,sizeof(pgn->Red),"%s",pstart + 4);
	//		pgn->Relo = atoi(pstart+9);
	//	}
	//}



	////pstart = strstr(pgnBuf,"[RedTitle ");
	////if(pstart != NULL){
	////	pend = strstr(pstart,"\"]");
	////	if(pend != NULL){
	////		size = pend - pstart;
	////		//sprintf_s(pgn->Red,sizeof(pgn->Red),"%s",pstart + 4);
	////		strcat_s(pgn->Red,sizeof(pgn->Red),
	////	}
	////}

	//pstart = strstr(pgnBuf,"[Black ");
	//if(pstart != NULL){
	//	pend = strstr(pstart,"\"]");
	//	if(pend != NULL){
	//		size = pend - pstart - 6;
	//		if(size < sizeof(pgn->Black)){
	//			strCopybyNum(pgn->Black,size,pstart + 6);
	//		}
	//	}
	//}

	//pstart = strstr(pgnBuf,"[BlackElo ");
	//if(pstart != NULL){
	//	pend = strstr(pstart,"\"]");
	//	if(pend != NULL){			
	//		pgn->Relo = atoi(pstart+11);
	//	}
	//}

	//pstart = strstr(pgnBuf,"[Result ");
	//if(pstart != NULL){
	//	pend = strstr(pstart,"\"]");
	//	if(pend != NULL){
	//		size = pend - pstart - 1;
	//		if(size < sizeof(pgn->result)){
	//			strCopybyNum(pgn->result,size,pstart + 1);
	//		}
	//	}
	//}

	//pstart = strstr(pgnBuf,"[TimeControl ");
	//if(pstart != NULL){
	//	pend = strstr(pstart,"\"]");
	//	if(pend != NULL){
	//		size = pend - pstart - 14;
	//		if(size < sizeof(pgn->RtimeControl)){
	//			strCopybyNum(pgn->RtimeControl,size,pstart + 14);
	//			strCopybyNum(pgn->BtimeControl,size,pstart + 14);
	//		}
	//	}
	//}

	//pstart = strstr(pgnBuf,"[Opening ");
	//if(pstart != NULL){
	//	pend = strstr(pstart,"\"]");
	//	if(pend != NULL){
	//		size = pend - pstart - 13;
	//		//strcat_s(pgn->note,sizeof(pgn->note), pstart);
	//		//sprintf_s(pgn->RtimeControl,size,"%s",pstart + 13);
	//		//sprintf_s(pgn->BtimeControl,size,"%s",pstart + 13);
	//	}
	//}



	char *p = strstr(pgnBuf,"[Variation");

	if(p == NULL){
		return FALSE;
	}

	p = strstr(p,"]");

	if(p == NULL){
		return FALSE;
	}

	if(strstr(p, "1.")){
		return FALSE;        //������������
	}

	p += 3;

	char *pend;

	
	pend = pgnBuf + len;

	while(p <= (pend- 5)){
		
		if(*(p+2) == 0x2d){
			int fx = *(p+0) - 'A';
			int fy = '9' -  *(p+1);

			int tx = *(p+3) - 'A';
			int ty = '9' -  *(p+4);

			if(IsMoveValid_FT(pDis->pos,fx,fy,tx,ty) == NormalMove){
				MakeMove(pDis,fx,fy,tx,ty,0);
			}
			else{
				return FALSE;
			}

		}

		p+= 6;
	}


	///IsMoveValid_FT
	//MakeMove(pDis,StoX(FROM(move)) - 3,
	//			StoY(FROM(move)) - 3,
	//			StoX(TO(move))   - 3,
	//			StoY(TO(move))   - 3, 0);


	return TRUE;
}

//PGN* pgn
BOOL		ReadPgnToPos    (dispboard_t* pDis, TCHAR* pgnFname){

	char pgnBuf[4096*8];
	char ss[256];
	int  pFile;

	PGN* pgn = pDis->pgn;

	errno_t err = _wsopen_s(&pFile, pgnFname, _O_RDONLY, _SH_DENYNO,
		_S_IREAD | _S_IWRITE);

	if(err != 0){
		LogOut(pgnFname);
		LogOut(_T("\nPGN �ļ������ڣ���򲻿�!!\n"));
		return FALSE;
	}

	//���ļ�ȫ������BUF
	int bytesRead = _read(pFile, pgnBuf, sizeof(pgnBuf));

	if(bytesRead <= 0){
		LogOut(pgnFname);
		LogOut(_T("\nPGN �ļ������ڣ���򲻿�!!\n"));
		_close(pFile);
		return FALSE;
	}

	_close(pFile);

	if(bytesRead < 20){
		LogOut(pgnFname);
		LogOut(_T("\nPGN �ļ�����̫�٣���\n"));
		return FALSE;
	}

	//�� 00 �Կո�������
	for(int e = 0; e < (bytesRead-10); e++){
		if(pgnBuf[e] == 0){
			pgnBuf[e] = 0x20;
		}
	}

	char* pend;

	int len = bytesRead;  //  (int)strlen(pgnBuf);


	char *pstart;
	char* ps;
	//char *pend;
	size_t  size;

	//PGN* pgn = pDis->pgn;

	//pstart = strstr(pgnBuf,"[Game ");
	//if(pstart != NULL){
	//	ps = pstart;
	//	pend = strstr(pstart,"\"]");		

	//	if(pend != NULL){
	//		size = pend - pstart - 5;
	//		if(size < sizeof(pgn->note)){
	//			strCopybyNum(ss, size, pstart + 5);
	//			swprintf_s(pgn->note,sizeof(pgn->note)/sizeof(TCHAR), _T("%S"), ss);
	//		}
	//	}
	//}

	pstart = strstr(pgnBuf,"[Event ");
	if(pstart != NULL){
		ps = pstart;
		pend = strstr(pstart,"\"]");
		if(pend != NULL){
			size = pend - pstart - 8;
			if(size < sizeof(pgn->pevent)){
				strCopybyNum(ss, size, pstart + 8);
				swprintf_s(pgn->pevent, sizeof(pgn->pevent) / sizeof(TCHAR), _T("%S"), ss);
			}
		}
	}

	pstart = strstr(pgnBuf,"[Red ");
	if(pstart != NULL){
		ps = pstart;
		pend = strstr(pstart,"\"]");
		if(pend != NULL){
			size = pend - pstart - 6;
			if(size < sizeof(pgn->Red)){
				strCopybyNum(ss, size, pstart + 6);
				swprintf_s(pgn->Red, sizeof(pgn->Red) / sizeof(TCHAR), _T("%S"), ss);	
			}
		}
	}


	swprintf_s(pgn->round, sizeof(pgn->round) / sizeof(TCHAR), _T("%S"), "");

	swprintf_s(pgn->opera, sizeof(pgn->opera) / sizeof(TCHAR), _T("%S"), "��������");

	//pgn->round = L"";

	//pstart = strstr(pgnBuf,"[RedElo ");
	//if(pstart != NULL){
	//	ps = pstart;
	//	pend = strstr(pstart,"\"]");
	//	if(pend != NULL){
	//		//sprintf_s(pgn->Red,sizeof(pgn->Red),"%s",pstart + 4);
	//		pgn->Relo = atoi(pstart+9);
	//	}
	//}

	pgn->Relo = 0;



	pstart = strstr(pgnBuf,"[Black ");
	if(pstart != NULL){
		ps = pstart;
		pend = strstr(pstart,"\"]");
		if(pend != NULL){
			size = pend - pstart - 8;
			if(size < sizeof(pgn->Black)){
				strCopybyNum(ss, size, pstart + 8);
				swprintf_s(pgn->Black, sizeof(pgn->Black) / sizeof(TCHAR), _T("%S"), ss);
			}
		}
	}

	//pstart = strstr(pgnBuf,"[BlackElo ");
	//if(pstart != NULL){
	//	ps = pstart;
	//	pend = strstr(pstart,"\"]");
	//	if(pend != NULL){			
	//		pgn->Belo = atoi(pstart+11);
	//	}
	//}
	pgn->Belo = 0;

	pstart = strstr(pgnBuf,"[Result ");
	if(pstart != NULL){
		ps = pstart;
		pend = strstr(pstart,"\"]");
		if(pend != NULL){
			size = pend - pstart - 1;
			if(size < sizeof(pgn->result)){
				strCopybyNum(ss, size, pstart + 1);
				swprintf_s(pgn->result, sizeof(pgn->result) / sizeof(TCHAR), _T("%S"), ss);				
			}
		}
	}

	pstart = strstr(pgnBuf,"[TimeControl ");
	if(pstart != NULL){
		ps = pstart;
		pend = strstr(pstart,"\"]");
		if(pend != NULL){
			size = pend - pstart - 14;
			if(size < sizeof(pgn->RtimeControl)){
				strCopybyNum(ss, size, pstart + 14);
				swprintf_s(pgn->RtimeControl, sizeof(pgn->RtimeControl) / sizeof(TCHAR), _T("%S"), ss);
				swprintf_s(pgn->BtimeControl, sizeof(pgn->BtimeControl) / sizeof(TCHAR), _T("%S"), ss);
			}
		}
	}

	//pstart = strstr(pgnBuf,"[Opening ");
	//if(pstart != NULL){
	//	ps = pstart;
	//	pend = strstr(pstart,"\"]");
	//	if(pend != NULL){
	//		size = pend - pstart - 13;
	//		//strcat_s(pgn->note,sizeof(pgn->note), pstart);
	//		//sprintf_s(pgn->RtimeControl,size,"%s",pstart + 13);
	//		//sprintf_s(pgn->BtimeControl,size,"%s",pstart + 13);
	//	}
	//}


	// [FEN "rnbakabnr/9/1c5c1/p1p1p1p1p/9/9/P1P1P1P1P/1C5C1/9/RNBAKABNR w - - 0 1"]
	pstart = strstr(pgnBuf, "[FEN ");
	if (pstart != NULL) {
		ps = pstart;
		pend = strstr(pstart, "rnbakabnr/9/1c5c1/p1p1p1p1p/9/9/P1P1P1P1P/1C5C1/9/RNBAKABNR w");
		if (pend != NULL) {
			//size = pend - pstart - 5;
			//strCopybyNum(ss, size, pstart + 5);	
			pgn->isFenGame = false;
		}
		else {
			LogOut(_T("\n PGN ����ǲо֣�����ѧϰ��\n"));
			LogOut(pgn->note);
			return false;
		}
	}
	else {
		pgn->isFenGame = false;
	}
	
	pstart = strstr(pgnBuf, "Result");
	ps = pstart;
	ps = strstr(ps, "\n");
	ps = ps + 1;
	
	
	pend = pgnBuf + len;

	//*pend      = 0;
	//*(pend-1)  = 0;

	//*(pend-1) = 0;       //����һ����β 
	
	//ps = strstr(pgnBuf,"Round");

	//if(ps == NULL){
	//	LogOut(pgnFname);
	//	LogOut("\nPGN ��PGN�ļ���û�з��� Round�� ����\n");
	//	return FALSE;
	//}

	//ps = pgnBuf;

	//if(pstart != NULL){
	//	ps = pstart;
	//}

	int ply = 0;         //PGN�ļ�1��ͷ

	//char str_num[32];

	while(ps < pend){

		//if (ply == 121*2) {
		//	ply = 121*2;
		//}

		if((pend - ps) < 7){
			goto PGN_RET;  //û���岽��
		}

		ps = strstr(ps, "{");

		if(ps != NULL){				

			ps -= 1;

			//if (*ps == 0x0A && *(ps-1) == 0x0D) {
			//	ps -= 2;
			//}

			if (*ps == '\n') {
				ps -= 1;
			}


			while (*ps == 0x20) {
				ps--;
			}

			ps -= 7;
			
			int move = getMoveFormPgnStr(pDis,ps);
			

			if(move == 0){
				//int move1 = getMoveFormPgnStr(pDis, ps);
				goto PGN_RET;   //û���岽��
			}		


			MakeMove(pDis,StoX(FROM(move)) - 3,
				StoY(FROM(move)) - 3,
				StoX(TO(move))   - 3,
				StoY(TO(move))   - 3, 0);

			pDis->pos->His[pDis->pos->gply-1].search_score = 0;
			// �õ���ǰ�ĵ÷�
			pstart = strstr(ps, "{score:");
			if (pstart != NULL) {
				ps = strstr(pstart, "time:");
				if (ps != NULL) {
					//pgn->Belo = atoi(pstart+11);

					if (pDis->pos->side == WHITE) {
						pDis->pos->His[pDis->pos->gply - 1].search_score = -(sint16)atoi(pstart + 7);
					}
					else {
						pDis->pos->His[pDis->pos->gply - 1].search_score =  (sint16)atoi(pstart + 7);
					}					
				}
			}

			ply++;	

			//if (ply == 254) {
			//	int a = ply;
			//}

			if (ps < pend - 10) {
				ps = strstr(ps, "\n") + 1;
			}
			else {
				goto PGN_RET;   //û���岽��
			}		

			
		}

		else{
			goto PGN_RET;   //û���岽��
		}
	}

PGN_RET:


	//if( (pend-ps) > 7){

	//	LogOut(pgnFname);
	//	LogOut(_T("\n�����岽û�н�����!!\n"));
	//	LogOut(pgnFname);
	//	LogOut(_T("\n*******************************************"));
	//	return TRUE;
	//}

	if(ply >= 1){

		//��Ϊ����ʹ��

		//CheckDlgItem(		

		//LogOuts(pgnBuf);
		LogOut(pgnFname);
		LogOut(_T("\n�ɹ�������һ�֣Уǣ��ļ����ڴ�!\n"));

		return TRUE;
	}
	else{


		return FALSE;
	}
	
}

//��Ŀ¼�µ�PGN�ļ���һ��һ�����뿪�ֿ�
BOOL PgnFileCatToSql(dispboard_t* pDis, TCHAR* pgnRoot){

	//char pgnPath[MAX_PATH];

	//sprintf_s(pgnPath,MAX_PATH,"%s%s",installDir,"pgn\\");

	BOOL havePgn = FALSE;

	TCHAR filename[MAX_PATH*2];

	BOOL isFind = FALSE;
	TCHAR dir[MAX_PATH];
	TCHAR pre_name[MAX_PATH * 2];
	TCHAR new_name[MAX_PATH * 2];

	TCHAR ok_dir[MAX_PATH];

	int ok_num = 0;	

	swprintf_s(ok_dir,sizeof(ok_dir)/sizeof(TCHAR),_T("%s%s"),pgnRoot,_T("_ok"));

	CreateDirectory(ok_dir,NULL);  //����ת���ɹ���Ŀ¼ 

	do{		//��һ��pgn�ļ�
		OpenAllCatFileOnebyOne(&isFind,pgnRoot,_T("*.pgn"),_T("_ok"),dir,filename);

		if(isFind){
			swprintf_s(pre_name,sizeof(pre_name) / sizeof(TCHAR),_T("%s%s"),dir,filename);

			swprintf_s(pDis->pgn->note,sizeof(pDis->pgn->note)/sizeof(TCHAR),filename);  //���ļ�����

			if(ReadPgnToPos(pDis,pre_name)){

				//����ɹ��ˣ����ƶ���_okĿ¼��
				swprintf_s(new_name, sizeof(new_name) / sizeof(TCHAR), _T("%s%s%s"), ok_dir, _T("\\"), filename);

				if(FALSE == MoveFileEx(pre_name,new_name,MOVEFILE_REPLACE_EXISTING)){
					LogOut(pre_name);
					LogOut(_T("\n�����ƶ��������_okĿ¼!!\n"));
					//LogOut(new_name);
					break;
				}

				LogOut(_T("\n�ɹ�����һ��PGN�ļ�!\n"));
				LogOut(pre_name);

				PgnFenFromCurPosition(pDis);  //�õ��岽��FEN
				
				havePgn = TRUE;
			}

			else{
				//������ȷ����PGN�ļ�
				LogOut(pre_name);
				LogOut(_T("����PGN�ļ���������PGN��ʽ!!\n"));

				swprintf_s(new_name, sizeof(new_name) / sizeof(TCHAR), _T("%s%s%s"), ok_dir, _T("\\"), filename);

				if (FALSE == MoveFileEx(pre_name, new_name, MOVEFILE_REPLACE_EXISTING)) {
					LogOut(pre_name);
					LogOut(_T("\n�����ƶ��������_okĿ¼!!\n"));
					//LogOut(new_name);
					break;
				}
				havePgn = TRUE;

				break;
			}

			isFind = FALSE;

		}
		else{
			LogOut(pgnRoot);
			LogOut(_T("\n�Բ���û��������Ŀ¼���ҵ���Ч��PGN�ļ�\n"));
		}

	}while(false);

	return havePgn;
	
}



