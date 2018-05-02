#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"

#include <sys/types.h>
#include <sys/timeb.h>

//�ӵ�ǰ����ֵõ�FEN
void PgnFenFromCurPosition(dispboard_t *pDis){

	PGN *pgn = pDis->pgn;
	position_t *pos = pDis->pos;

	if (pDis->pgn->isFenGame == TRUE){				//��������Ĳо�
		swprintf_s(pgn->fen_store, sizeof(pgn->fen_store) / sizeof(TCHAR), L"%s moves ", pgn->start_fen);
	}
	else{
		swprintf_s(pgn->fen_store, sizeof(pgn->fen_store) / sizeof(TCHAR), L"%s", L"moves ");
	}

	TCHAR *p = pgn->fen_store + wcslen(pgn->fen_store);

	//if (pos->gply >= 1){
	pgn->yqScore = pos->His[pos->gply].search_score;
	//}

	//������е��岽
	for (int i = 1; i <= pos->gply; i++){
		move2str(pos->His[i].move, p);
		p += 4;
	}
	*(p + 1) = 0;

	//������еĵ÷�
	p = pgn->strStepScore;
	for (int i = 0; i <= pos->gply; i++){
		int score = pos->His[i].search_score;
		swprintf_s(p, 32, L"%6d", score);
		p += 6;
	}

	p = 0;

}
//��PGN�е���Ϣд���Ի���
void PgnToSaveDlg(dispboard_t *pDis){

	HWND hDlg = HWND_SAVE;
	PGN* pgn = pDis->pgn;

	//��ֱ��
	SetDlgItemInt(hDlg, IDC_SAVE_PID, pgn->pid, TRUE);
	//���λ��
	SetDlgItemText(hDlg, IDC_SAVE_EVENT, (pgn->pevent));
	//��������
	SetDlgItemText(hDlg, IDC_SAVE_DATE, (pgn->date));

	//�����ִ�
	//char            round[16];    //�����ִΣ�

	//�췽����
	SetDlgItemText(hDlg, IDC_SAVE_RNAME, (pgn->Red));
	SetDlgItemText(hDlg, IDC_SAVE_BNAME, (pgn->Black));

	//result
	SetDlgItemText(hDlg, IDC_STEP_RESULT, (pgn->result));

	//Relo
	SetDlgItemInt(hDlg, IDC_SAVE_RELO, pgn->Relo, FALSE);
	SetDlgItemInt(hDlg, IDC_SAVE_BELO, pgn->Belo, FALSE);

	//��ʱ��ʽ
	//char            RtimeControl[32];
	SetDlgItemText(hDlg, IDC_STEP_RTIME, (pgn->RtimeControl));
	SetDlgItemText(hDlg, IDC_STEP_BTIME, (pgn->BtimeControl));
	//char            BtimeControl[32];

	//note
	SetDlgItemText(hDlg, IDC_SAVE_NOTE_OK, (pgn->note));

	//gameType
	if (pDis->pgn->isFenGame == FALSE){
		SetDlgItemText(hDlg, IDC_NOT_FEN_GAME, _T("��"));
	}
	else{
		SetDlgItemText(hDlg, IDC_NOT_FEN_GAME, _T("��"));
	}

	//planID
	SetDlgItemInt(hDlg, IDC_SAVE_PLANID, pgn->PlanID, TRUE);



	SendDlgItemMessage(hDlg, IDC_VERY_GOOD, BM_SETCHECK, 0, 0);
	SendDlgItemMessage(hDlg, IDC_LIT_GOOD, BM_SETCHECK, 0, 0);
	SendDlgItemMessage(hDlg, IDC_BALANCE, BM_SETCHECK, 0, 0);
	SendDlgItemMessage(hDlg, IDC_LIT_BAD, BM_SETCHECK, 0, 0);
	SendDlgItemMessage(hDlg, IDC_VERY_BAD, BM_SETCHECK, 0, 0);

	//score  ���۷�
	if (false){
	}

	else if (pgn->score == BOOK_VERY_GOOD){
		SendDlgItemMessage(hDlg, IDC_VERY_GOOD, BM_SETCHECK, 1, 0);
	}
	else if (pgn->score == BOOK_LIT_GOOD) {
		SendDlgItemMessage(hDlg, IDC_LIT_GOOD, BM_SETCHECK, 1, 0);
	}
	else if (pgn->score == BOOK_BALANCE)  {
		SendDlgItemMessage(hDlg, IDC_BALANCE, BM_SETCHECK, 1, 0);
	}
	else if (pgn->score == BOOK_LIT_BAD)  {
		SendDlgItemMessage(hDlg, IDC_LIT_BAD, BM_SETCHECK, 1, 0);
	}
	else if (pgn->score == BOOK_VERY_BAD) {
		SendDlgItemMessage(hDlg, IDC_VERY_BAD, BM_SETCHECK, 1, 0);
	}

	//����Ա
	SetDlgItemText(hDlg, IDC_SAVE_OPERATOR, pgn->opera);

	//SetWindowText(GetDlgItem(hDlg, IDC_SAVE_OPERATOR), pgn->opera);

	//����������
	SetDlgItemInt(hDlg, IDC_YQ_SCORE, pgn->yqScore, TRUE);

	//�Ƿ�У��
	SendDlgItemMessage(hDlg, IDC_IS_CHECKED, BM_SETCHECK, pgn->isChecked, 0);

	//�Ƿ�ѧϰ����
	SendDlgItemMessage(hDlg, IDC_IS_LEARNED, BM_SETCHECK, pgn->isLearned, 0);

	//�Ƿ������ IDC_IS_FINISHED
	SendDlgItemMessage(hDlg, IDC_IS_FINISHED, BM_SETCHECK, pgn->isFinish, 0);
}

//���Ի����е���Ϣд��PGN
BOOL PgnFromSaveDlg(dispboard_t *pDis){

	BOOL isGet;
	int  intGet;

	PGN* pgn = pDis->pgn;
	HWND hDlg = HWND_SAVE;

	if (hDlg == NULL) return FALSE;

	//�õ���ǰ����֣ɣ�
	intGet = GetDlgItemInt(hDlg, IDC_SAVE_PID, &isGet, TRUE);
	if (!isGet){
		return FALSE;
	}
	else{
		pgn->pid = intGet;
	}

	//�õ�event
	GetDlgItemText(hDlg, IDC_SAVE_EVENT, pgn->pevent, sizeof(pgn->pevent));

	//�õ�roud

	//�õ��췽����
	GetDlgItemText(hDlg, IDC_SAVE_RNAME, pgn->Red, sizeof(pgn->Red));
	GetDlgItemText(hDlg, IDC_SAVE_BNAME, pgn->Black, sizeof(pgn->Black));

	//�õ�result
	GetDlgItemText(hDlg, IDC_STEP_RESULT, pgn->result, sizeof(pgn->result));

	//�õ���ע
	GetDlgItemText(hDlg, IDC_SAVE_NOTE_OK, pgn->note, sizeof(pgn->note));

	//�õ�Relo
	intGet = GetDlgItemInt(hDlg, IDC_SAVE_RELO, &isGet, TRUE);
	if (!isGet){
		return FALSE;
	}
	else{
		pgn->Relo = intGet;
	}
	intGet = GetDlgItemInt(hDlg, IDC_SAVE_BELO, &isGet, TRUE);
	if (!isGet){
		return FALSE;
	}
	else{
		pgn->Belo = intGet;
	}

	//char            RtimeControl[32];
	//char            BtimeControl[32];

	//note
	GetDlgItemText(hDlg, IDC_STEP_NOTE, pgn->note, sizeof(pgn->note));

	//game_type
	//pgn->isFenGame = pDis->IsFenGame;

	//isChecked
	if (IsDlgButtonChecked(hDlg, IDC_IS_CHECKED) == BST_CHECKED){
		pgn->isChecked = TRUE;
	}
	else{
		pgn->isChecked = FALSE;
	}

	//isLearned
	if (IsDlgButtonChecked(hDlg, IDC_IS_LEARNED) == BST_CHECKED){
		pgn->isLearned = TRUE;
	}
	else{
		pgn->isLearned = FALSE;
	}

	//�Ƿ����
	if (IsDlgButtonChecked(hDlg, IDC_IS_FINISHED) == BST_CHECKED){
		pgn->isFinish = TRUE;
	}
	else{
		pgn->isFinish = FALSE;
	}

	//����÷�

	//intGet = GetDlgItemInt(hDlg,IDC_YQ_SCORE,&isGet,TRUE);
	//if(!isGet){
	//	return FALSE;
	//}
	//else{
	//	pgn->yqScore = intGet;
	//}

	//�õ��÷�
	if (false){
	}
	else if (IsDlgButtonChecked(hDlg, IDC_VERY_GOOD) == BST_CHECKED){
		pgn->score = BOOK_VERY_GOOD;
	}
	else if (IsDlgButtonChecked(hDlg, IDC_LIT_GOOD) == BST_CHECKED){
		pgn->score = BOOK_LIT_GOOD;
	}
	else if (IsDlgButtonChecked(hDlg, IDC_BALANCE) == BST_CHECKED){
		pgn->score = BOOK_BALANCE;
	}
	else if (IsDlgButtonChecked(hDlg, IDC_LIT_BAD) == BST_CHECKED){
		pgn->score = BOOK_LIT_BAD;
	}
	else if (IsDlgButtonChecked(hDlg, IDC_VERY_BAD) == BST_CHECKED){
		pgn->score = BOOK_VERY_BAD;
	}
	else{
		pgn->score = BOOK_NOT_RESULT;
	}

	return TRUE;
}

//ͨ���ɣĵõ��������Ϣ
BOOL PgnGetGameInfoFromSqliteById(dispboard_t* pDis, int id, sqlite3 *db){

	char    *szErrMsg = 0;
	int      nrow = 0;
	int      ncolumn = 0;
	int      rc = 0;
	char    **azResult;
	char     sql[1024];

	//rc = SqliteOpenDataBase(&db_pgn,L3_DB_PGN);

	//if(rc != SQLITE_OK) return rc;
	setlocale(LC_CTYPE, "chs");
	PGN* pgn = pDis->pgn;

	sprintf_s(sql, sizeof(sql), "SELECT * FROM pgn WHERE pgnID = %d", id);

	rc = sqlite3_get_table(db, sql, &azResult, &nrow, &ncolumn, &szErrMsg);

	if (nrow != 0){
		pgn->pid = id;
		swprintf_s(pgn->pevent, sizeof(pgn->pevent) / sizeof(TCHAR), _T("%S"), (azResult[ncolumn + 1]));
		swprintf_s(pgn->date, sizeof(pgn->date) / sizeof(TCHAR), _T("%S"), (azResult[ncolumn + 2]));
		swprintf_s(pgn->round, sizeof(pgn->round) / sizeof(TCHAR), _T("%S"), (azResult[ncolumn + 3]));
		swprintf_s(pgn->Red, sizeof(pgn->Red) / sizeof(TCHAR), _T("%S"), (azResult[ncolumn + 4]));
		swprintf_s(pgn->Black, sizeof(pgn->Black) / sizeof(TCHAR), _T("%S"), (azResult[ncolumn + 5]));
		swprintf_s(pgn->result, sizeof(pgn->result) / sizeof(TCHAR), _T("%S"), (azResult[ncolumn + 6]));

		pgn->Relo = atoi(azResult[ncolumn + 7]);
		pgn->Belo = atoi(azResult[ncolumn + 8]);

		swprintf_s(pgn->RtimeControl, sizeof(pgn->RtimeControl) / sizeof(TCHAR), _T("%S"), (azResult[ncolumn + 9]));
		swprintf_s(pgn->BtimeControl, sizeof(pgn->BtimeControl) / sizeof(TCHAR), _T("%S"), (azResult[ncolumn + 10]));

		swprintf_s(pgn->fen_store, sizeof(pgn->fen_store) / sizeof(TCHAR), L"%S", azResult[ncolumn + 11]);
		swprintf_s(pgn->note, sizeof(pgn->note) / sizeof(TCHAR), _T("%S"), azResult[ncolumn + 12]);

		pgn->isChecked = atoi(azResult[ncolumn + 13]);
		pgn->isLearned = atoi(azResult[ncolumn + 14]);
		pgn->isFinish = atoi(azResult[ncolumn + 15]);
		pgn->PlanID = atoi(azResult[ncolumn + 16]);
		pgn->score = atoi(azResult[ncolumn + 17]);
		pgn->rate = atoi(azResult[ncolumn + 18]);
		pgn->yqScore = atoi(azResult[ncolumn + 19]);
		//pgn->date      = 
		swprintf_s(pgn->opera, sizeof(pgn->opera) / sizeof(TCHAR), _T("%S"), (azResult[ncolumn + 20]));

		swprintf_s(pgn->strStepScore, sizeof(pgn->strStepScore) / sizeof(TCHAR), _T("%S"), (azResult[ncolumn + 21]));
	}

	sqlite3_free_table(azResult);
	//sqlite3_close(db_pgn);
	return rc;
}

//�����ݿ�õ�һ����ɵ���ֵı��
BOOL PgnGetOneFinishedGameFromSql(dispboard_t *pDis, sqlite3 *db){

	//1,��Sqlite
	//sqlite3 *db_pgn;
	char    *szErrMsg = 0;
	int      nrow = 0;
	int      ncolumn = 0;
	int      rc = -1;
	char    **azResult;
	char     sql[4096];

	int      id = -1;

	//rc = SqliteOpenDataBase(&db_pgn,L3_DB_PGN);

	//if(rc != SQLITE_OK) return rc;

	sprintf_s(sql, sizeof(sql),
		"SELECT pgnID FROM pgn WHERE isFinish <> 0 ORDER BY pgnID DESC");

	//"SELECT pgnID FROM pgn ORDER BY pgnID DESC");

	rc = sqlite3_get_table(db, sql, &azResult, &nrow, &ncolumn, &szErrMsg);

	if (rc != SQLITE_OK){
		LogOuts(szErrMsg);
		sqlite3_free(szErrMsg);
		//sqlite3_close(db_pgn);
		return rc;
	}

	for (int k = 1; k <= nrow; k++){
		id = atoi(azResult[ncolumn + 0]);
		break;
	}

	sqlite3_free_table(azResult);

	//sqlite3_close(db_pgn);

	if (id == -1){
		return id;
	}

	PgnGetGameInfoFromSqliteById(pDis, id, db);

	pDis->pgn->isFinish = FALSE;

	return PgnUpdateGameToSqlite(pDis, db);

}


//�����ݿ�õ�û�м�������ֵı��
BOOL PgnGetOneUnCheckedGameFromSql(dispboard_t *pDis, sqlite3 *db){

	//1,��Sqlite
	//sqlite3 *db_pgn;
	char    *szErrMsg = 0;
	int      nrow = 0;
	int      ncolumn = 0;
	int      rc = -1;
	char    **azResult;
	char     sql[4096];

	int      id = -1;

	//rc = SqliteOpenDataBase(&db_pgn,L3_DB_PGN);

	//if(rc != SQLITE_OK) return rc;

	sprintf_s(sql, sizeof(sql),
		"SELECT pgnID FROM pgn WHERE isChecked <> 1 ORDER BY pgnID DESC");

	//"SELECT pgnID FROM pgn ORDER BY pgnID DESC");

	rc = sqlite3_get_table(db, sql, &azResult, &nrow, &ncolumn, &szErrMsg);

	if (rc != SQLITE_OK){
		LogOuts(szErrMsg);
		sqlite3_free(szErrMsg);
		//sqlite3_close(db_pgn);
		return rc;
	}

	for (int k = 1; k <= nrow; k++){
		id = atoi(azResult[ncolumn + 0]);
		break;
	}

	sqlite3_free_table(azResult);

	//sqlite3_close(db_pgn);

	if (id == -1){
		return id;
	}

	return PgnGetGameInfoFromSqliteById(pDis, id, db);

}


BOOL PgnUpdateGameToSqlite(dispboard_t *pDis, sqlite3 *db){

	int rc = -1;
	//sqlite3 *db_pgn;
	char    *szErrMsg = 0;
	char    sql[4096 * 2];

	PGN* pgn = pDis->pgn;

	if (pgn->pid == -1) return rc;

	setlocale(LC_CTYPE, "chs");

	sprintf_s(sql, sizeof(sql),
		"UPDATE pgn SET pevent='%S',round='%S',red='%S',black='%S',Relo=%d,Belo=%d,\
				Rtime='%S',Btime='%S',note='%S',isChecked=%d,isLearned=%d,isFinish=%d,\
						PlanID=%d,score=%d,rate=%d,yqscore=%d,operator='%S',stepscore='%S' WHERE pgnID = %d",
						pgn->pevent,
						pgn->round,
						pgn->Red,
						pgn->Black,
						pgn->Relo,
						pgn->Belo,
						pgn->RtimeControl,
						pgn->BtimeControl,
						//pgn->fen_store,
						pgn->note,
						pgn->isChecked,
						pgn->isLearned,
						pgn->isFinish,
						pgn->PlanID,
						pgn->score,
						pgn->rate,
						pgn->yqScore,
						pgn->opera,
						pgn->strStepScore,
						pgn->pid);


	rc = sqlite3_exec(db, sql, 0, 0, &szErrMsg);
	if (rc != 0){
		LogOuts(szErrMsg);
		sqlite3_free(szErrMsg);
	}

	//sqlite3_close(db_pgn);		//��������ˣ��õ��õĹ�

	return rc;

}


//�õ�FEN��ͬ����ֱ��
BOOL PgnGetSameFenId(dispboard_t *pDis, int* sameId, sqlite3 *db){

	char    *szErrMsg = 0;
	int      nrow = 0;
	int      ncolumn = 0;
	int      rc = 0;
	char    **azResult;
	char     sql[4098];

	setlocale(LC_CTYPE, "chs");

	PGN* pgn = pDis->pgn;

	sprintf_s(sql, sizeof(sql), "SELECT pgnID FROM pgn WHERE fens = '%S'", pgn->fen_store);

	rc = sqlite3_get_table(db, sql, &azResult, &nrow, &ncolumn, &szErrMsg);

	if (rc != SQLITE_OK){
		LogOuts(szErrMsg);
		sqlite3_free(szErrMsg);
		//sqlite3_close(db_pgn);
		return rc;
	}

	for (int k = 1; k <= nrow; k++){
		*sameId = atoi(azResult[ncolumn + 0]);
		break;
	}



	sqlite3_free_table(azResult);
	//sqlite3_close(db_pgn);
	return rc;
}
//����һ�ֵ�SQLite��ȥ
BOOL PgnInsertGameToSqlite(dispboard_t *pDis, int* saveId, sqlite3 *db){

	//1,��Sqlite
	//sqlite3 *db_pgn;
	char    *szErrMsg = 0;
	int      nrow = 0;
	int      ncolumn = 0;
	int      rc = -1;
	char    **azResult;
	char     sql[4096 * 2];

	//if(pDis->)
	if (pDis->pos->gply <= 1) {
		return SQLITE_OK;
	}
	*saveId = -1;

	PGN* pgn = pDis->pgn;

	PgnGetSameFenId(pDis, saveId, db);

	if (*saveId != -1){
		pgn->pid = *saveId;
		return PgnUpdateGameToSqlite(pDis, db);
	}


	setlocale(LC_CTYPE, "chs");


	//���ڲ�����

	sprintf_s(sql, sizeof(sql),
		"INSERT INTO pgn (pevent,round,red,black,result,Relo,Belo,Rtime,Btime,fens,note,\
				isChecked,isLearned,isFinish,PlanID,score,rate,yqscore,operator,stepscore) \
						VALUES('%S','%S','%S','%S','%S','%d','%d','%S','%S','%S','%S',\
								'%d','%d','%d','%d','%d','%d','%d','%S','%S')",
								pgn->pevent,
								pgn->round,
								pgn->Red,
								pgn->Black,
								pgn->result,

								pgn->Relo,
								pgn->Belo,

								pgn->RtimeControl,
								pgn->BtimeControl,
								pgn->fen_store,
								pgn->note,

								pgn->isChecked,
								pgn->isLearned,
								pgn->isFinish,
								pgn->PlanID,
								pgn->score,
								pgn->rate,
								pgn->yqScore,
								pgn->opera,
								pgn->strStepScore);

	rc = sqlite3_exec(db, sql, 0, 0, &szErrMsg);

	if (rc != SQLITE_OK){
		LogOuts(szErrMsg);
		sqlite3_free(szErrMsg);
		return rc;
	}

	sprintf_s(sql, sizeof(sql),
		"SELECT pgnID FROM pgn ORDER BY pgnID DESC");

	rc = sqlite3_get_table(db, sql, &azResult, &nrow, &ncolumn, &szErrMsg);

	if (rc != SQLITE_OK){
		LogOuts(szErrMsg);
		sqlite3_free(szErrMsg);
		return rc;
	}

	for (int k = 1; k <= nrow; k++){
		*saveId = atoi(azResult[k*ncolumn + 0]);
		break;
	}

	sqlite3_free_table(azResult);

	return rc;
}


BOOL PgnFenToPos(dispboard_t* pDis, BOOL isStop){

	//�õ���ǰ�ģƣţ�

	PGN *pgn = pDis->pgn;

	if (pgn->pid == -1){
		return FALSE;
	}

	if ((pgn->fen_store[0] == 'm' && pgn->fen_store[1] == 'o')
		|| (pgn->fen_store[1] == 'm' && pgn->fen_store[2] == 'o')){

		EditPositionPasteFEN(StartFen, pDis);
		pDis->pgn->isFenGame = FALSE;					//�ǲ��ǲо�
	}
	else{
		EditPositionPasteFEN(pgn->fen_store, pDis); /* call into backend */
		// ********************************
		pDis->book_num = 0;
		pDis->pgn->isFenGame = TRUE;
	}

	TCHAR *c = wcsstr(pgn->fen_store, L"moves ");

	if (c == NULL) return FALSE;

	TCHAR *pend = pgn->fen_store + sizeof(pgn->fen_store);

	c += 6;

	while (*c != '\0' && c < pend && *c != ' '){
		int move = str2move(pDis->pos, c);

		if (move){
			//MakeMove(pDis,fromX, fromY, toX, toY,true); /*updates forwardMostMove*/
			int from = FROM(move);
			int to = TO(move);

			int fromX = StoX(from) - 3;
			int fromY = StoY(from) - 3;
			int toX = StoX(to) - 3;
			int toY = StoY(to) - 3;

			MakeMove(pDis, fromX, fromY, toX, toY, FALSE);
			ShowMove(pDis, fromX, fromY, toX, toY);
			c += 4;
		}
		else{
			break;
		}

		//if(isStop){   //У��ֻҪ�ߵ�һ���Ĳ��Ӿ�����.
		// if(pDis->pos->gply > (BOOK_MOVE_LEARN_PLY + 1)){
		//	 break;
		// }
		//}
	}

	TCHAR* pStr = pgn->strStepScore;
	for (int i = 0; i <= pDis->pos->gply; i++){
		TCHAR buf[32];
		swprintf_s(buf, 32, L"%.6s", pStr);
		pStr += 6;

		pDis->pos->His[i].search_score = (sint16)_wtoi(buf);
	}


	if (pDis->pos->gply > 0){
		if (isStop){
			//�ߵ�ҪУ�Ե���һ��
			if (pDis->pos->gply > (BOOK_MOVE_LEARN_PLY)){
				BackwardInner(pDis, BOOK_MOVE_LEARN_PLY);
			}
		}

		return TRUE;
	}
	else{
		return FALSE;
	}
}


DWORD WINAPI
ImportAllFileGameThread(LPVOID lpParam){

	//�������еģУǣθ�ʽ���ļ�w
	TCHAR gamePath[MAX_PATH];
	TCHAR buf[512];
	//int  num = 0;
	

	dispboard_t pDis[1];
	pDis->hwndThis = NULL;

	//Thread_Stat |= TH_Importing;
	ThStat.isImPort = TRUE;

	sqlite3 *db;

	int rc = SqliteOpenDataBase(&db, L3_DB_PGN);

	if (rc != SQLITE_OK){
		LogOut(_T("\n�����������ܴ�������ݿ�!\n"));
		return rc;
	}

	pDis->imPortNum = 0;
	LogOut(_T("\n���ڵ����������׸�ʽ���ļ�"));
	swprintf_s(gamePath, MAX_PATH, _T("%s%s"), installDir, _T("othergame\\"));
	while (ThStat.isImPort){
		ClearGameInfo(pDis->pgn);
		
		EditPositionPasteFEN(StartFen, pDis);
		if (MxqFileCatToSql(pDis, gamePath) == FALSE){
			break;
		}
		PgnFenFromCurPosition(pDis);  //�õ��岽��FEN
		int saveId = 0;
		if (PgnInsertGameToSqlite(pDis, &saveId, db) != SQLITE_OK){
			break;
		}
		swprintf_s(buf, MAX_PATH, _T("\n�ɹ�����������֣���ţ�%d"), saveId);
		pDis->imPortNum++;
	}
	swprintf_s(buf, MAX_PATH, _T("\n�ɹ������� %d ���������"), pDis->imPortNum);
	LogOut(buf);

	//**************************************************************************
	pDis->imPortNum = 0;
	LogOut(_T("\n���ڵ���������ĵ�PGN���׸�ʽ���ļ�"));
	while (ThStat.isImPort) {

		ClearGameInfo(pDis->pgn);

		EditPositionPasteFEN(StartFen, pDis);
		if (PgnFileCatToSql(pDis, _T("H:\\PGN_TEST2\\")) == FALSE) {
			break;
		}

		int saveId = 0;
		if (PgnInsertGameToSqlite(pDis, &saveId, db) != SQLITE_OK) {
			break;
		}
		swprintf_s(buf, MAX_PATH, _T("\n�ɹ�����PGN��֣���ţ�%d"), saveId);
		pDis->imPortNum++;
	}
	swprintf_s(buf, MAX_PATH, _T("\n�ɹ������� %d ��PGN���"), pDis->imPortNum);
	LogOut(buf);

	//goto KK;

	//**************************************************************************
	pDis->imPortNum = 0;
	LogOut(_T("\n���ڵ���PGN���׸�ʽ���ļ�"));
	while (ThStat.isImPort) {

		ClearGameInfo(pDis->pgn);

		EditPositionPasteFEN(StartFen, pDis);
		if (PgnFileCatToSql(pDis, gamePath) == FALSE) {
			break;
		}
		
		int saveId = 0;
		if (PgnInsertGameToSqlite(pDis, &saveId, db) != SQLITE_OK) {
			break;
		}
		swprintf_s(buf, MAX_PATH, _T("\n�ɹ�����PGN��֣���ţ�%d"), saveId);
		pDis->imPortNum++;
	}
	swprintf_s(buf, MAX_PATH, _T("\n�ɹ������� %d ��PGN���"), pDis->imPortNum);
	LogOut(buf);

	//**************************************************************************
	pDis->imPortNum = 0;
	LogOut(_T("\n���ڵ���������ĵ�PGN���׸�ʽ���ļ�"));
	while (ThStat.isImPort) {

		ClearGameInfo(pDis->pgn);

		EditPositionPasteFEN(StartFen, pDis);
		if (PgnFileCatToSql(pDis, _T("H:\\BHGui_3.6_20160501_SIM\\")) == FALSE) {
			break;
		}

		int saveId = 0;
		if (PgnInsertGameToSqlite(pDis, &saveId, db) != SQLITE_OK) {
			break;
		}
		swprintf_s(buf, MAX_PATH, _T("\n�ɹ�����PGN��֣���ţ�%d"), saveId);
		pDis->imPortNum++;
	}
	swprintf_s(buf, MAX_PATH, _T("\n�ɹ������� %d ��PGN���"), pDis->imPortNum);
	LogOut(buf);

	//**************************************************************************
	pDis->imPortNum = 0;
	LogOut(_T("\n���ڵ����ս��PGN���׸�ʽ���ļ�"));
	while (ThStat.isImPort) {

		ClearGameInfo(pDis->pgn);

		EditPositionPasteFEN(StartFen, pDis);
		if (PgnFileCatToSql(pDis, _T("Z:\\")) == FALSE) {
			break;
		}

		int saveId = 0;
		if (PgnInsertGameToSqlite(pDis, &saveId, db) != SQLITE_OK) {
			break;
		}
		swprintf_s(buf, MAX_PATH, _T("\n�ɹ�����PGN��֣���ţ�%d"), saveId);
		pDis->imPortNum++;
	}
	swprintf_s(buf, MAX_PATH, _T("\n�ɹ������� %d ��PGN���"), pDis->imPortNum);
	LogOut(buf);

//KK:


	sqlite3_close(db);

	ThStat.isImPort = false;  // ������������


	///ShowWindow(GetDlgItem(hDlg, IDC_IMPORT_GAME), SW_HIDE);

	return 0;
}

//Ҫ��һ���̵߳���
void ImportAllGameEvent(void){
	DWORD dwThreadId, dwThrdParam = 1;
	HANDLE hImport = CreateThread(
		NULL,
		NULL,
		ImportAllFileGameThread,
		&dwThrdParam,
		0,
		&dwThreadId);

	if (hImport == NULL){
		SendToPlayerByColor(_T("��ʼ����������߳�ʧ��!"), ColorShout, FALSE);
	}
	else{
		SendToPlayerByColor(_T("��ʼ����������̳߳ɹ���"), ColorShout, FALSE);
		SetThreadPriority(hImport, THREAD_PRIORITY_BELOW_NORMAL);
	}
}


//У�����
void CorrectQiJu(dispboard_t* pDis, sqlite3* db){

	HWND hDlg = HWND_SAVE;

	//pDis->gameMode   = PlayFromGameFile;
	//pDis->matchMode  = TRUE;						//�����߲��Ͳ��ᷢ����

	if (PgnGetOneUnCheckedGameFromSql(pDis, db) == SQLITE_OK){
		PgnToSaveDlg(pDis);
		pDis->notLookBook = true;
		PgnFenToPos(pDis, true);

		//LogOut(pDis->pgn->fen_store);

		pDis->notLookBook = false;
		//
		HDCDrawChart(TAB.dlgScore, pDis, NULL, true);

		SendToPlayerByColor(_T("\n����һ�֣���У��\n"), ColorSeek, FALSE);
	}
	else{
		SendToPlayerByColor(_T("\n��ǰ��û����ֿ�У����\n"), ColorSShout, FALSE);
		SendDlgItemMessage(hDlg, IDC_READ_UNCHECKED, BM_SETCHECK, FALSE, 0);
	}
}

// extern int PgnTotalGameUncheckNumFromSql(dispboard_t *pDis, sqlite3 *db);
void SetSaveWinTitle(HWND hwnd, sqlite3* db){

	int total = PgnTotalGameNumFromSql(db);
	int unCheck = PgnTotalGameUncheckNumFromSql(db); 

	TCHAR buf[512];
	swprintf_s(buf, sizeof(buf) / sizeof(TCHAR), L"��⹲�� %d �֣�ʣ %d ��δУ�ԣ�", total, unCheck);

	SetWindowText(hwnd, buf);

}

LRESULT CALLBACK
SaveGameDlgCallBack(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam){

	//�õ�������

	dispboard_t *pDis;
	int table;
	BOOL isGet;
	int  intGet;
	//char buf[512];

	switch (message){
	case WM_INITDIALOG:{
		//
		//ͼ��

		table = (int)lParam;

		pDis = OBS[table];

		HWND_SAVE = hDlg;



		SetDlgItemInt(hDlg, IDC_SAVE_TABLE, table, TRUE);		//����������

		//sprintf_s(buf,sizeof(buf),"���洰�ڣ������ţ�%d",table);
		//SetWindowText(hDlg,buf);

		//�ٵ���һ�´��ڵ�λ��
		RECT Rect;
		GetWindowRect(pDis->hwndThis, &Rect);

		int x = Rect.right;
		int y = Rect.top;
		int width = 320;
		int height = Rect.bottom - Rect.top;

		SetWindowPos(hDlg, NULL, x, y, width, height, SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOSIZE);


		ClearGameInfo(pDis->pgn);

		PgnToSaveDlg(pDis);

		sqlite3 * db;
		int rc = SqliteOpenDataBase(&db, L3_DB_PGN);
		if (rc != SQLITE_OK){
			LogOut(_T("\n�����������ܴ�������ݿ�!\n"));
			break;
		}
		// �õ���ǰ������е������Ϣ��
		SetSaveWinTitle(hDlg, db);
		sqlite3_close(db);

		// �Ƚ����еİ�ť��Ϊ��������˵

		EnableWindow(GetDlgItem(hDlg, IDC_SAVE_LAST_STEP), FALSE);
		EnableWindow(GetDlgItem(hDlg, IDC_SAVE_ANALIZE), FALSE);
		EnableWindow(GetDlgItem(hDlg, IDC_READ_UNCHECKED), FALSE);
		EnableWindow(GetDlgItem(hDlg, IDC_SAVE_UPDATE), FALSE);
		EnableWindow(GetDlgItem(hDlg, IDC_STEP_SAVE), FALSE);
		EnableWindow(GetDlgItem(hDlg, IDC_ONE_FACE_SAVE), FALSE);

		switch (pDis->gameMode){
		case IcsPlayingWhite:
		case IcsPlayingBlack:
			
			break;
		case EditGame:
		case BeginningOfGame:
		case GameNoneMode:
			if (pDis->pos->curStep != pDis->pos->gply){
				EnableWindow(GetDlgItem(hDlg, IDC_SAVE_LAST_STEP), FALSE);  // �ߵ����һ��
			}
			EnableWindow(GetDlgItem(hDlg, IDC_SAVE_ANALIZE), 1);    // ���� 
			EnableWindow(GetDlgItem(hDlg, IDC_READ_UNCHECKED), 1);  // ȡһ��δУ�Ե����
			//EnableWindow(GetDlgItem(hDlg, IDC_SAVE_UPDATE), FALSE);     // �������
			//EnableWindow(GetDlgItem(hDlg, IDC_STEP_SAVE), FALSE);       // �������
			//EnableWindow(GetDlgItem(hDlg, IDC_ONE_FACE_SAVE), FALSE);   // ������һ������
			break;
		default:
			break;
		}	

		//typedef enum {
		//	//û��
		//	GameNoneMode, BeginningOfGame, MachinePlaysWhite, MachinePlaysBlack,
		//	AnalyzeMode, TwoMachinesPlay,
		//	EditGame, PlayFromGameFile, EndOfGame, EditPosition, Training,
		//	IcsIdle, IcsPlayingWhite, IcsPlayingBlack, IcsObserving,
		//	IcsExamining, EditBook, //��ǰ���ڱ༭���
		//} GameMode;

	}

		return TRUE;
		break;
	case WM_COMMAND:	//�а�ť��Ϣ 

		intGet = GetDlgItemInt(hDlg, IDC_SAVE_TABLE, &isGet, TRUE);
		if (!isGet){
			//MessageBox(hDlg,"��������ȷ������÷�(ELO)!","�ţңңϣҡ�����",MB_OK);
			return FALSE;
		}
		table = intGet;

		pDis = OBS[table];

		//-----------------------------------------------------------------------------------

		switch (LOWORD(wParam)){
		case IDC_READ_UNCHECKED:	//��ȡһ��û��ѧϰ����
			if (IsDlgButtonChecked(hDlg, IDC_READ_UNCHECKED) == BST_CHECKED){
				sqlite3 * db;
				int rc = SqliteOpenDataBase(&db, L3_DB_PGN);
				if (rc != SQLITE_OK){
					LogOut(_T("\n�����������ܴ�������ݿ�!\n"));
					break;
				}
				SetSaveWinTitle(hDlg, db);
				CorrectQiJu(pDis, db);
				sqlite3_close(db);
			}
			break;
		case IDC_IMPORT_GAME: //
			// ShowWindow(GetDlgItem(hDlg, IDC_IMPORT_GAME), SW_HIDE); 
			LogOut(_T("\n����������������ʽ����ַ����������othergameĿ¼��,���ڿɵ���PGN, ���죬���Σ����ڣ�XQF, �����ŵȸ�ʽ�����ף�������ɺ�,�ļ������ƶ���_okĿ¼�£��붨��ɾ����\n"));
			if (ThStat.isImPort == FALSE){
				ImportAllGameEvent();
			}
			else{
				//
				LogOut(_T("\n��ǰ���ڵ������!!"));
			}
			break;
		case IDC_LEARN_ALL:
			//ShowWindow(GetDlgItem(hDlg,IDC_LEARN_ALL),SW_HIDE);

			if (ThStat.isLearn == FALSE){
				AutoLearnEvent();
			}
			else {
				LogOut(_T("\n��ǰ����ѧϰ��!!"));
			}
			//ShowWindow(GetDlgItem(hDlg,IDC_LEARN_ALL),SW_SHOW);
			break;
		case IDC_SAVE_ANALIZE:
			AnalizeEvent(pDis);
			break;
		case IDC_SAVE_LAST_STEP:
			ToEndEvent(pDis);
			break;
		case IDC_SAVE_UPDATE:	//������ְ�ť
		{

			if (IsDlgButtonChecked(hDlg, IDC_READ_UNCHECKED) == BST_CHECKED){
				if (pDis->gameMode == AnalyzeMode){   //��ǰ���Ƿ���ģʽ
					AnalizeEvent(pDis);
					LogOut(L"\n��ǰ���ڷ���ģʽ���޷�������֣�");
					break;
				}
			}
			//�õ���ǰ�����ID
			sqlite3* db;
			int rc = SqliteOpenDataBase(&db, L3_DB_PGN);


			if (rc != SQLITE_OK){
				LogOut(_T("\n�����������ܴ�������ݿ�!\n"));
				break;
			}

			PgnFromSaveDlg(pDis);

			if (pDis->pgn->score == BOOK_NOT_RESULT){
				SendToPlayerByColor(_T("\n�����ǰ�ľ���һ�����۲��ܸ���\n"), ColorSShout, FALSE);
				break;
			}

			PgnFenFromCurPosition(pDis);

			pDis->pgn->isChecked = TRUE;
			pDis->pgn->isLearned = FALSE;

			BOOL upok = FALSE;

			if (pDis->pgn->pid == -1){ //�����µ����
				LogOut(_T("\n��������֣��밴���水ť���浱ǰ���!"));
			}
			else{
				if (PgnUpdateGameToSqlite(pDis, db) == SQLITE_OK){
					upok = TRUE;
				}
			}

			if (upok){
				SendToPlayerByColor(_T("\n���µ�ǰ����ֳɹ�\n"), ColorSeek, FALSE);
				if (IsDlgButtonChecked(hDlg, IDC_READ_UNCHECKED) == BST_CHECKED){
					CorrectQiJu(pDis, db);
				}
			}
			else{
				SendToPlayerByColor(_T("\n���µ�ǰ�����ʧ����\n"), ColorShout, FALSE);
			}

			SetSaveWinTitle(hDlg, db);
			sqlite3_close(db);

			//��ѧϰһ��
			if (ThStat.isLearn == FALSE){
				AutoLearnEvent();
			}
			else {
				LogOut(_T("\n��ǰ����ѧϰ��!!"));
			}

			EnableWindow(GetDlgItem(hDlg, IDC_SAVE_UPDATE), 0);            // �������

		}
			break;

		case IDC_ONE_FACE_SAVE:   // ֻ���ݵ�ǰ�����Ƹ���һ�����档
			PgnFromSaveDlg(pDis);

			if (pDis->pgn->score == BOOK_NOT_RESULT){
				SendToPlayerByColor(_T("\n�����ǰ�ľ���һ�����۲��ܱ���\n"), ColorSShout, FALSE);
				break;
			}

			UpDataOneFaceEvent(pDis, MST->book);  // ֻ���µ�ǰ�ľ������
			EnableWindow(GetDlgItem(hDlg, IDC_ONE_FACE_SAVE), 0);
			break;
		case IDC_STEP_SAVE:		//������ְ�ť
		{

			if (IsDlgButtonChecked(hDlg, IDC_READ_UNCHECKED) == BST_CHECKED){
				if (pDis->gameMode == AnalyzeMode){   //��ǰ���Ƿ���ģʽ
					AnalizeEvent(pDis);
					LogOut(L"\n��ǰ���ڷ���ģʽ���޷�������֣�");
					break;
				}
			}
			//�õ���ǰ����֣ɣ�

			sqlite3 * db;

			int rc = SqliteOpenDataBase(&db, L3_DB_PGN);

			if (rc != SQLITE_OK){
				LogOut(_T("\n�����������ܴ�������ݿ�!\n"));
				break;
			}


			PgnFromSaveDlg(pDis);

			if (pDis->pgn->score == BOOK_NOT_RESULT){
				SendToPlayerByColor(_T("\n�����ǰ�ľ���һ�����۲��ܱ���\n"), ColorSShout, FALSE);
				break;
			}

			PgnFenFromCurPosition(pDis);

			pDis->pgn->isChecked = TRUE;
			pDis->pgn->isLearned = FALSE;

			BOOL saveorupok = FALSE;

			int saveId = -1;
			if (PgnInsertGameToSqlite(pDis, &saveId, db) == SQLITE_OK){
				SetDlgItemInt(hDlg, IDC_SAVE_PID, saveId, TRUE);
				saveorupok = TRUE;
			}

			if (saveorupok){
				SendToPlayerByColor(L"\n���浱ǰ����ֳɹ�\n", ColorSeek, FALSE);
				EnableWindow(GetDlgItem(hDlg, IDC_READ_UNCHECKED), TRUE);
				if (IsDlgButtonChecked(hDlg, IDC_READ_UNCHECKED) == BST_CHECKED){
					CorrectQiJu(pDis, db);
				}
			}
			else{
				SendToPlayerByColor(_T("\n���浱ǰ�����ʧ����\n"), ColorShout, FALSE);
			}

			SetSaveWinTitle(hDlg, db);

			sqlite3_close(db);

			//��ѧϰһ��
			if (ThStat.isLearn == FALSE){
				AutoLearnEvent();
			}
			else {
				LogOut(_T("\n��ǰ����ѧϰ��!!"));
			}

			EnableWindow(GetDlgItem(hDlg, IDC_STEP_SAVE), 0);                 // �������

		}
			break;
		case IDC_LIT_GOOD:
		case IDC_LIT_BAD:
		case IDC_BALANCE:
		case IDC_VERY_BAD:
		case IDC_VERY_GOOD:{

     		EnableWindow(GetDlgItem(hDlg, IDC_STEP_SAVE), 1);                  // �������
			EnableWindow(GetDlgItem(hDlg, IDC_ONE_FACE_SAVE), 1);
			if (pDis->pgn->pid != -1){ //�����µ����
				EnableWindow(GetDlgItem(hDlg, IDC_SAVE_UPDATE), 1);            // �������
			}			
			EnableWindow(GetDlgItem(hDlg, IDC_STEP_SAVE), 1);                  // �������
		}
			break;

		case IDOK:                          //ȷ�ϰ�ť
			EndDialog(hDlg, TRUE);
			SendMessage(hwndToolBar, TB_CHECKBUTTON, IDT_SAVE_GAME, 0);  //����ť������
			HWND_SAVE = NULL;
			return TRUE;
			break;
		case IDCANCEL:
			EndDialog(hDlg, FALSE);
			SendMessage(hwndToolBar, TB_CHECKBUTTON, IDT_SAVE_GAME, 0);
			HWND_SAVE = NULL;
			return FALSE;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}


	return FALSE;

}
//������ִ���

void DLG_SAVE_GAME_Event(int table){

	dispboard_t *pDis = OBS[0];

	if (HWND_SAVE == NULL){			//
		//�����Ի���
		FARPROC lpProc = MakeProcInstance((FARPROC)SaveGameDlgCallBack, hInst);
		HWND_SAVE = CreateDialogParam(hInst, MAKEINTRESOURCE(DLG_SAVE),
			pDis->hwndThis, (DLGPROC)lpProc, table);

		FreeProcInstance(lpProc);
		ShowWindow(HWND_SAVE, SW_SHOW);

		PostMessage(HWND_SAVE, WM_SETICON, (WPARAM)ICON_BIG, (LPARAM)pDis->iconCurrent);
	}
	else{
		//SendMessage(pDis->hwndSaveDlg,WM_CLOSE,0,0);		//�رմ���

		EndDialog(HWND_SAVE, 0);

		HWND_SAVE = NULL;
	}

}

