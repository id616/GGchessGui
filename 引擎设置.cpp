#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"

#include <windows.h>   /* required for all Windows applications */
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <fcntl.h>
#include <math.h>
#include <commdlg.h>
#include <dlgs.h>


void							//ԭ�ȵ����棬   //Ҫ���ص�����				 //��������Ĵ���
LoadChessProgramState(ChessProgramState *precps, ChessProgramState *loadcps, HWND hWin){

	//ShowWindow(win,SW_HIDE);			//����������һ��

	//if(precps->isUpLoading == TRUE){
	//	SendToPlayerByColor("�Բ��𣬵�ǰ����������ж��֮�У����ԵȺ��ټ���!!\n",ColorShout,FALSE);
	//	return;
	//}

	if(precps->cps_stat == Cps_UpLoading){
		SendToPlayerByColor(L"�Բ��𣬵�ǰ����������ж��֮�У����ԵȺ��ټ���!!\n",ColorShout,FALSE);
		return;
	}

	if(loadcps->cps_stat == Cps_InLoading){
		SendToPlayerByColor(L"�Բ��𣬵�ǰ���������ڼ���֮�У����ԵȺ��ټ���!!\n",ColorShout,FALSE);
		return;
	}

	if(loadcps->cps_stat == Cps_Waiting){
		SendToPlayerByColor(L"�Բ��𣬵�ǰ�������Ѽ��أ��벻Ҫ�ٴμ���!!\n",ColorShout,FALSE);
		return;
	}


	loadcps->loadWin        = hWin;		   //��������Ĵ��ڣ����򴰿ڷ�����ɵģ����˳�����Ϣ
	loadcps->loadPre        = precps;      //
	precps->loadWhich		= loadcps;

	loadcps->playWhat       = precps->playWhat;
	precps->playWhat        = NEUTRAL;

	if(precps->cps_stat != Cps_NotLoad){
		LogOut(_T("\n����ж������: "));
		LogOut(precps->UCCI_name);
		LogOut(_T("\n����ҪһЩʱ�䣬 ���Ժ�...\n"));

		switch(precps->ucci){
			case UCCI_UCCI_ms:
			case UCCI_UCCI_OLD:
				if(precps->cps_stat == Cps_Pondering 
					|| precps->cps_stat == Cps_Thinking 
					|| precps->cps_stat == Cps_Analyse){
						SendToProgram(L"stop\n",precps);
						Sleep(100);
				}
				SendToProgram(L"quit\n", precps);
				break;
			case UCCI_GGchess:
				if(precps->cps_stat == Cps_Pondering 
					|| precps->cps_stat == Cps_Thinking 
					|| precps->cps_stat == Cps_Analyse){
					SendToProgram(L"stop\n", precps);
						Sleep(100);
				}
				SendToProgram(L"quit\n", precps);
				break;
			case UCCI_CYC105:
				if(precps->cps_stat == Cps_Pondering 
					|| precps->cps_stat == Cps_Thinking 
					|| precps->cps_stat == Cps_Analyse){
					SendToProgram(L"stop\n", precps);
						Sleep(100);
				}
				SendToProgram(L"quit\n", precps);
				break;
			default:
				SendToProgram(L"quit\n", precps);
				SendToProgram(L"QUIT\n", precps);
				break;
		}
		precps->cps_stat = Cps_UpLoading;			//��������ж��
	}
	else{
		LogOut(_T("\n���ڼ�������:\n"));
		LogOut(loadcps->UCCI_name);
		LogOut(_T("\n����ҪһЩʱ�䣬���Ժ�....\n"));
		StartChessProgram(loadcps);
	}
}


int 
GetYqinfoFromSqliteByID(ChessProgramState *cps,int id){

	sqlite3 *db_ini;
	char    *szErrMsg       = 0;
	int      nrow           = 0;
	int      ncolumn        = 0;
	int      rc             = 0;
	char    **azResult;
	char     sql[1024];

	if(rc = SqliteOpenDataBase(&db_ini,L3_DB_INI)){
		LogOut(_T("-------------���ܴ��趨���ݿ�-------------\n"));
		return rc;      //���д�,���ܱ���
	}
	setlocale(LC_CTYPE, "chs");
	sprintf_s(sql,1024,"SELECT * FROM yq WHERE yqID = %d",id);

	rc = sqlite3_get_table(db_ini,sql,&azResult,&nrow,&ncolumn,&szErrMsg);

	if(rc != SQLITE_OK){

		MessageBox(NULL, _T("���ܴ�������Ϣ"), _T("Error"), MB_OK);

		return rc;
	}

	if(nrow != 0){      //�ҵ��˼�¼ 
		cps->yqID = id;
		swprintf_s(cps->UCCI_name, sizeof(cps->UCCI_name) / sizeof(TCHAR), _T("%S"), (azResult[ncolumn + 1]));
		swprintf_s(cps->UCCI_file, sizeof(cps->UCCI_file) / sizeof(TCHAR), _T("%S"), (azResult[ncolumn + 2]));
		swprintf_s(cps->UCCI_author, sizeof(cps->UCCI_author) / sizeof(TCHAR), _T("%S"), (azResult[ncolumn + 3]));
		swprintf_s(cps->UCCI_verson, sizeof(cps->UCCI_verson) / sizeof(TCHAR), _T("%S"), (azResult[ncolumn + 4]));
		/*sprintf_s(cps->UCCI_dualtime,"%d",*/
		cps->UCCI_dualtime = atoi(azResult[ncolumn+5]);
		//swprintf_s(cps->UCCI_path, sizeof(cps->UCCI_path) / sizeof(TCHAR), _T("%S"), (azResult[ncolumn + 6]));

		swprintf_s(cps->UCCI_path, sizeof(cps->UCCI_path) / sizeof(TCHAR), _T("%S"), "");
		cps->ucci            = atoi(azResult[ncolumn+7]);
		cps->UCCI_Book_Num   = atoi(azResult[ncolumn+8]);        
		swprintf_s(cps->UCCI_iniString, sizeof(cps->UCCI_iniString) / sizeof(TCHAR), _T("%S"), (azResult[ncolumn + 9]));
		swprintf_s(cps->UCCI_otherString, sizeof(cps->UCCI_otherString) / sizeof(TCHAR), _T("%S"), (azResult[ncolumn + 10]));

		cps->UCCI_smpNum		= atoi(azResult[ncolumn+11]);
		cps->UCCI_hashsize		= atoi(azResult[ncolumn+12]);
		cps->timePerStep		= atoi(azResult[ncolumn+13]);
		cps->timeSearchDepth    = atoi(azResult[ncolumn+14]);
		cps->IsBaoGan		    = atoi(azResult[ncolumn+15]);
		cps->BaoGanTime  		= atoi(azResult[ncolumn+16]);
		cps->timePerStepAdd		= atoi(azResult[ncolumn+17]);
		cps->timeIsLost			= atoi(azResult[ncolumn+18]);
		cps->time_1_Step		= atoi(azResult[ncolumn+19]);
		cps->time_1_Time		= atoi(azResult[ncolumn+20]);
		cps->time_2_Step		= atoi(azResult[ncolumn+21]);
		cps->time_2_Time		= atoi(azResult[ncolumn+22]);
		cps->useBook            = atoi(azResult[ncolumn+23]);
		cps->isEGB              = atoi(azResult[ncolumn+24]);
		swprintf_s(cps->UCCI_addInfo, sizeof(cps->UCCI_addInfo) / sizeof(TCHAR), _T("%S"), (azResult[ncolumn + 25]));
	}
	else{
		cps->UCCI_addInfo[0] = NULLCHAR;
	}

	sqlite3_free_table(azResult);

	rc = sqlite3_close(db_ini);

	return rc;
}


//�����������Ϣ�õ������UCCI��ϸ��Ϣ
int
FillYqUccciToSetDialog(ChessProgramState *cps, HWND hDlg){ //IDC_YQUCCI
	//1, ���趨���ݿ�
	sqlite3 *db_ini;
	char    *szErrMsg       = 0;
	int      nrow           = 0;
	int      ncolumn        = 0;
	int      rc             = 0;
	char    **azResult;
	char     sql[1024];
	//char    buf[512];

	if(rc = SqliteOpenDataBase(&db_ini,L3_DB_INI)){
		LogOut(_T("-------------���ܴ��趨���ݿ�-------------\n"));
		return rc;      //���д�,���ܱ���
	}

	sprintf_s(sql,1024,"SELECT * FROM ucci");

	rc = sqlite3_get_table(db_ini,sql,&azResult,&nrow,&ncolumn,&szErrMsg);

	if(rc != SQLITE_OK){
		return rc;
	}

	//���Э���б�
	SendDlgItemMessage(hDlg,IDC_YQUCCI,CB_RESETCONTENT,0,0);

	if(cps->ucci == 0){
		cps->ucci = 1;  //UCCI
	}
	int k;
	int nowID = -1;
	for(k = 1; k <= nrow; k++){      //����ÿһ������
		//
		int   id = atoi(azResult[k*ncolumn+1]);
		if(id == cps->ucci){
			nowID = k;
		}    
		TCHAR  info[128];
		swprintf_s(info,sizeof(info)/sizeof(TCHAR),L"%d) %S <%S>",id,azResult[k*ncolumn+0],azResult[k*ncolumn+2]);
		SendDlgItemMessage(hDlg,IDC_YQUCCI,CB_ADDSTRING,0,(LPARAM)info);
	}

	//�ͷ�Ϊ��¼��������ڴ棬��������˿ռ�¼�������ᷢ������
	sqlite3_free_table(azResult);

	rc = sqlite3_close(db_ini);

	//����ǰѡ�������Ϊ��ǰ CB_SETCURSEL
	SendDlgItemMessage(hDlg,IDC_YQUCCI,CB_SETCURSEL,nowID-1,0);

	return rc;
}

//�����е�����������䵽�Ի���
int
FillYqListToSetDialog(ChessProgramState *cps, HWND hDlg){  //IDC_YQ_LIST

	//1, ���趨���ݿ�
	sqlite3 *db_ini;
	char    *szErrMsg       = 0;
	int      nrow           = 0;
	int      ncolumn        = 0;
	int      rc             = 0;
	char    **azResult;
	char     sql[1024];
	TCHAR    buf[512];

	if(rc = SqliteOpenDataBase(&db_ini,L3_DB_INI)){
		LogOut(_T("-------------���ܴ��趨���ݿ�-------------\n"));
		return rc;      //���д�,���ܱ���
	}

	sprintf_s(sql,1024,"SELECT * FROM yq");

	rc = sqlite3_get_table(db_ini,sql,&azResult,&nrow,&ncolumn,&szErrMsg);

	if(rc != SQLITE_OK){
		return rc;
	}

	ChessProgramState tmp[1];
	//char  arg[512];

	//��������б�
	SendDlgItemMessage(hDlg,IDC_YQ_LIST,CB_RESETCONTENT,0,0);

	int nowID = -1;
	int k;

	for(k = 1; k <= nrow; k++){      //����ÿһ������
		//�õ�ID
		tmp->yqID = atoi(azResult[k*ncolumn + 0]);

		if(cps->yqID == tmp->yqID){
			nowID = k;
		}

		//�õ���������
		swprintf_s(tmp->UCCI_name, 64 , _T("%S"), (azResult[(k)*ncolumn + 1]));
		//
		swprintf_s(buf, sizeof(buf) / sizeof(TCHAR), _T("%d) %s"), tmp->yqID, tmp->UCCI_name);
		//�б�
		SendDlgItemMessage(hDlg,IDC_YQ_LIST,CB_ADDSTRING,0,(LPARAM)buf);
	}

	//�ͷ�Ϊ��¼��������ڴ棬��������˿ռ�¼�������ᷢ������
	sqlite3_free_table(azResult);

	rc = sqlite3_close(db_ini);

	if(nowID == -1){ //��ǰѡ������治���б���
		cps->yqID = tmp->yqID;
		GetYqinfoFromSqliteByID(cps,tmp->yqID);
		YqInfoToSetDialog(cps,hDlg);
		nowID = k;
	}

	//����ǰѡ�������Ϊ��ǰ CB_SETCURSEL
	SendDlgItemMessage(hDlg,IDC_YQ_LIST,CB_SETCURSEL,nowID-1,0);

	return rc;
}


//���������Ϣ��ʾ���Ի���,Ҫע�⵱ǰѡ��������һ��
void
YqInfoToSetDialog(ChessProgramState *cps, HWND hDlg){

	//�õ�������
	int table;
	BOOL isGet;
	int  intGet;
	TCHAR buf[512];

	intGet = GetDlgItemInt(hDlg,IDC_Table,&isGet,TRUE);

	if(isGet){
		table = intGet;
	}
	else{
		table = 0;
	}
	dispboard_t *pDis = OBS[table];		//cps = pDis->cur_set_cps;


	BOOL isDef = FALSE;

	//�õ���ǰ���Ǹ����水����
	if(IsDlgButtonChecked(hDlg,IDC_RADIO_YQA) == BST_CHECKED){	//�������������
		swprintf_s(buf, sizeof(buf) / sizeof(TCHAR), _T("���� (1) ���öԻ���, ʹ�������: %d, ��ǰ�����: %d"),
			pDis->first.yqID,	cps->yqID);

		//��һ�±���ǲ�����ͬ��
		if(pDis->first.yqID != cps->yqID){
			isDef = TRUE;
		}

	}

	if(isDef == TRUE){
		EnableWindow(GetDlgItem(hDlg,ID_LOAD_SET_YQ),TRUE);		//ʹ�������水ť����		
	}
	else{
		EnableWindow(GetDlgItem(hDlg,ID_LOAD_SET_YQ),FALSE);		
	}	

	// ��Ҫ��һ���ǲ���ɾ����Ҫ����һ������ɾ����
	if(pDis->set_cps.yqID != pDis->first.yqID ){
		EnableWindow(GetDlgItem(hDlg,IDC_DELETE_YQ), TRUE);		//ʹɾ�����水ť����
	}
	else{
		EnableWindow(GetDlgItem(hDlg,IDC_DELETE_YQ), FALSE);	//ʹɾ�����水ť����
	}

	SetWindowText(hDlg,buf);

	//

	//2, ���٣��б��
	FillYqListToSetDialog(cps,hDlg);

	//3, ���գãã��б��
	FillYqUccciToSetDialog(cps,hDlg);

	//3, ���SMP�߳��� �б��

	//4, ��������
	SetDlgItemText(hDlg, IDC_YQ_NAME, cps->UCCI_name);

	//5, �����ʹ������岽��

	SendDlgItemMessage(hDlg,IDC_YQ_LIST_BOOK_NUM,CB_SETCURSEL,cps->UCCI_Book_Num,0);

	//6, �߳���
	SendDlgItemMessage(hDlg,IDC_YQ_SMP_LIST,CB_SETCURSEL,cps->UCCI_smpNum - 1,0);  //��ʼһ���߳�

	//���������
	SetDlgItemText(hDlg,IDC_YQ_PROGRAME,cps->UCCI_file);
	//�������·��
	SetDlgItemText(hDlg, IDC_YQ_PATH, cps->UCCI_path);
	//��ʼָ��
	SetDlgItemText(hDlg, IDC_initString, cps->UCCI_iniString);
	//����ָ��
	SetDlgItemText(hDlg, IDC_YqOtherString, cps->UCCI_otherString);
	//���ֿ�
	SendDlgItemMessage(hDlg,IDC_IsBook,BM_SETCHECK,cps->useBook,0);
	//�оֿ�
	SendDlgItemMessage(hDlg,IDC_IsEGB, BM_SETCHECK,cps->isEGB,0);
	//hash���С
	SetDlgItemInt(hDlg,IDC_HashSize,cps->UCCI_hashsize,false);
	//ÿ�����ʱ��
	SetDlgItemInt(hDlg,IDC_TimePerStep,cps->timePerStep,false);
	//depth
	SetDlgItemInt(hDlg,IDC_SearchDepth,cps->timeSearchDepth,false);

	//���ɼ�ʱ
	SendDlgItemMessage(hDlg,IDC_IsBaoGan,		BM_SETCHECK, cps->IsBaoGan, 0);
	//�Ƿ�ֶμ�ʱ IDC_IsFenDuanTime
	SendDlgItemMessage(hDlg,IDC_IsFenDuanTime,	BM_SETCHECK,!cps->IsBaoGan, 0);

	//���ٷ���ÿ�� IDC_BanGanTime
	SetDlgItemInt(hDlg,IDC_BanGanTime,cps->BaoGanTime,false);
	//ÿ��һ����ʱ TimeAddPerStep
	SetDlgItemInt(hDlg,IDC_TimeAddPerStep,cps->timePerStepAdd,false);
	//IDC_IsLostTimeUp ?
	SendDlgItemMessage(hDlg,IDC_IsLostTimeUp,BM_SETCHECK,cps->timeIsLost,0);

	//��һʱ��β� IDC_firstClassStep
	SetDlgItemInt(hDlg,IDC_firstClassStep,cps->time_1_Step,false);
	//��һʱ���ʱ�� IDC_firstClassTime
	SetDlgItemInt(hDlg,IDC_firstClassTime,cps->time_1_Time,false);
	//�ڶ�ʱ��β�
	SetDlgItemInt(hDlg,IDC_secondClassStep,cps->time_2_Step,false);
	//�ڶ�ʱ���ʱ�� secondClassTime
	SetDlgItemInt(hDlg,IDC_secondClassTime,cps->time_2_Time,false);
}

//���Ի������Ϣת��CPS��
bool
SetDialogToCps(ChessProgramState *cps, HWND hDlg){

	BOOL isGet;
	int  intGet;

	//1,�õ���ǰѡ�������ı��
	int sel = (int)SendDlgItemMessage(hDlg,IDC_YQ_LIST,CB_GETCURSEL,0,0);
	TCHAR buf[MSG_SIZ];
	SendDlgItemMessage(hDlg,IDC_YQ_LIST,CB_GETLBTEXT,sel,(LPARAM)buf);

	cps->yqID  = _wtoi(buf);

	//�õ�ѡ��Э����
	sel = (int)SendDlgItemMessage(hDlg,IDC_YQUCCI,CB_GETCURSEL,0,0);
	SendDlgItemMessage(hDlg,IDC_YQUCCI,CB_GETLBTEXT,sel,(LPARAM)buf);

	cps->ucci = _wtoi(buf);

	//�õ����������
	GetDlgItemText(hDlg,IDC_YQ_NAME,cps->UCCI_name,sizeof(cps->UCCI_name));

	//�õ����浱ǰ�ģţ̣�
	//intGet = GetDlgItemInt(hDlg,IDC_YQ_ELO,&isGet,TRUE);
	//if(!isGet){
	//	MessageBox(hDlg,"��������ȷ������÷�(ELO)!","�ţңңϣҡ�����",MB_OK);
	//	return false;
	//}

	sel = (int)SendDlgItemMessage(hDlg,IDC_YQ_LIST_BOOK_NUM,CB_GETCURSEL,0,0);

	cps->UCCI_Book_Num = sel;

	//�߳���
	//intGet = GetDlgItemInt(hDlg,IDC_SMP_NUM,&isGet,TRUE);
	//if(!isGet){
	//	MessageBox(hDlg,"��������ȷ���߳���!","�ţңңϣҡ�����",MB_OK);
	//	return false;
	//}
	//cps->UCCI_smpNum = intGet;
	//if(cps->UCCI_smpNum < 0 || cps->UCCI_smpNum > 16){
	//	cps->UCCI_smpNum = 1;
	//}

	sel = (int)SendDlgItemMessage(hDlg,IDC_YQ_SMP_LIST,CB_GETCURSEL,0,0);

	cps->UCCI_smpNum = sel + 1;



	//�Ƿ�ʹ�ÿ��ֿ�
	if(IsDlgButtonChecked(hDlg,IDC_IsBook) == BST_CHECKED){
		cps->useBook = TRUE;
	}
	else{
		cps->useBook = FALSE;
	}
	//�Ƿ�ʹ�òоֿ�
	if(IsDlgButtonChecked(hDlg,IDC_IsEGB) == BST_CHECKED){
		cps->isEGB = 1;
	}
	else{
		cps->isEGB = 0;
	}
	//��ʼָ��
	GetDlgItemText(hDlg,IDC_initString,cps->UCCI_iniString,sizeof(cps->UCCI_iniString));
	//����ָ��
	GetDlgItemText(hDlg,IDC_YqOtherString,cps->UCCI_otherString,sizeof(cps->UCCI_otherString));
	//���·��
	GetDlgItemText(hDlg,IDC_YQ_PATH,cps->UCCI_path,sizeof(cps->UCCI_path));
	//�����ļ���
	GetDlgItemText(hDlg,IDC_YQ_PROGRAME,cps->UCCI_file,sizeof(cps->UCCI_file));
	//HASH���С
	intGet = GetDlgItemInt(hDlg,IDC_HashSize,&isGet,TRUE);  //&cps->hashSize,    
	if(!isGet){
		MessageBox(hDlg, _T("��������ȷ��HASH���С!"), _T("�ţңңϣҡ�����"), MB_OK);
		return false;
	}


	cps->UCCI_hashsize = intGet;
	if(cps->UCCI_hashsize < 16 || cps->UCCI_hashsize > 2048){
		MessageBox(hDlg, _T("��������ȷ��HASH���С!, ��64M ~ 1024M��"), _T("�ţңңϣҡ�����"), MB_OK);
		cps->UCCI_hashsize = 16;
	}
	/*
	int h = cps->UCCI_hashsize;
	if(h != 32 || h != 64 || h != 128 ||  */ 

	//ÿ��ʱ��
	intGet = GetDlgItemInt(hDlg,IDC_TimePerStep,&isGet,TRUE); //&cps->timePerStep,
	if(!isGet){
		MessageBox(hDlg, _T("��������ȷ��ÿ������ʱ��!"), _T("�ţңңϣҡ�����"), MB_OK);
		return false;
	}
	cps->timePerStep = intGet;
	//��������
	intGet = GetDlgItemInt(hDlg,IDC_SearchDepth,&isGet,TRUE);

	if(!isGet){
		MessageBox(hDlg, _T("��������ȷ��ÿ����������!"), _T("�ţңңϣҡ�����"), MB_OK);
		return false;
	}
	cps->timeSearchDepth = intGet;

	if(cps->timeSearchDepth < 0 || cps->timeSearchDepth > 60){
		cps->timeSearchDepth = 0;
	}
	//��ʱ�趨
	if(IsDlgButtonChecked(hDlg,IDC_IsBaoGan) == BST_CHECKED){
		cps->IsBaoGan = 1;
	}
	else{
		cps->IsBaoGan  = 0;
	}

	//���ٷ��ӣ���
	intGet = GetDlgItemInt(hDlg,IDC_BanGanTime,&isGet,TRUE);
	if(!isGet){
		MessageBox(hDlg, _T("��������ȷ�İ���ʱ��!"), _T("�ţңңϣҡ�����"), MB_OK);
		return false;
	}
	cps->BaoGanTime = intGet;    
	if(cps->BaoGanTime == 0){
		cps->BaoGanTime = 1;
	}

	//ÿ��һ���Ӷ�����
	intGet = GetDlgItemInt(hDlg,IDC_TimeAddPerStep,&isGet,TRUE);
	if(!isGet){
		MessageBox(hDlg, _T("��������ȷ��ÿ����ʱ!"), _T("�ţңңϣҡ�����"), MB_OK);
		return false;
	}
	cps->timePerStepAdd = intGet;

	//���ǳ�ʱ�и�
	if(IsDlgButtonChecked(hDlg,IDC_IsLostTimeUp) == BST_CHECKED){
		cps->timeIsLost = 1;
	}
	else{
		cps->timeIsLost = 0;
	}
	//��һʱ��β���
	intGet = GetDlgItemInt(hDlg,IDC_firstClassStep,&isGet,TRUE);
	if(!isGet){
		MessageBox(hDlg, _T("��������ȷ�ĵ�һʱ���Ҫ�ߵĲ���!"), _T("�ţңңϣҡ�����"), MB_OK);
		return false;
	}
	cps->time_1_Step = intGet;
	if(cps->time_1_Step == 0){
		cps->time_1_Step = 30;
	}
	//��һʱ���ʱ��
	intGet = GetDlgItemInt(hDlg,IDC_firstClassTime,&isGet,TRUE);
	if(!isGet){
		MessageBox(hDlg, _T("��������ȷ�ĵ�һʱ���ʱ��!"), _T("�ţңңϣҡ�����"), MB_OK);
		return false;
	}
	cps->time_1_Time = intGet;
	if(cps->time_1_Time == 0){
		cps->time_1_Time = 1;
	}
	//�ڶ�ʱ��β���
	intGet = GetDlgItemInt(hDlg,IDC_secondClassStep,&isGet,TRUE);
	if(!isGet){
		MessageBox(hDlg, _T("��������ȷ�ĵڶ�ʱ���Ҫ�ߵĲ���!"), _T("�ţңңϣҡ�����"), MB_OK);
		return false;
	}
	cps->time_2_Step = intGet;
	if(cps->time_2_Step == 0){
		cps->time_2_Step = 10;
	}
	intGet = GetDlgItemInt(hDlg,IDC_secondClassTime,&isGet,TRUE);
	if(!isGet){
		MessageBox(hDlg, _T("��������ȷ�ĵڶ�ʱ���ʱ��!"), _T("�ţңңϣҡ�����"), MB_OK);
		return false;
	}
	cps->time_2_Time = intGet;
	if(cps->time_2_Time == 0){
		cps->time_2_Time = 1;
	}

	cps->UCCI_addInfo[0] = NULLCHAR;
	return true;
}


//����������Ϣ���趨���ݿ���
int 
UpdateCpsInfoToSqlite(ChessProgramState *cps){
	int rc              = -1;
	sqlite3 *db_ini;
	char    *szErrMsg   = 0;
	char    sql[4096];

	if((rc = SqliteOpenDataBase(&db_ini,L3_DB_INI)) == 0){
		sprintf_s(sql,sizeof(sql),
			"UPDATE yq SET yqName='%S',yqFile='%S',yqAuthor='%S',yqVerson='%S',yqDualTime=%d, \
			path='%S',xieyiID=%d,elo=%d,initString='%S',OtherString='%S',smpNum=%d,hashSize=%d,moveTime=%d,\
			depth=%d,isBaoGan=%d,BaoGanTime=%d,stepInc=%d,TimeUpLose=%d,FT_Step=%d,FT_Time=%d,SC_Step=%d,\
			SC_Time=%d,haveBook=%d,haveEGB=%d,yqOther='%S' WHERE yqID = %d",
			cps->UCCI_name,
			cps->UCCI_file,
			cps->UCCI_author,
			cps->UCCI_verson,
			cps->UCCI_dualtime,
			cps->UCCI_path,
			cps->ucci,
			cps->UCCI_Book_Num,
			cps->UCCI_iniString,
			cps->UCCI_otherString,
			cps->UCCI_smpNum,
			cps->UCCI_hashsize,
			cps->timePerStep,
			cps->timeSearchDepth,
			cps->IsBaoGan,
			cps->BaoGanTime,
			cps->timePerStepAdd,
			cps->timeIsLost,
			cps->time_1_Step,
			cps->time_1_Time,
			cps->time_2_Step,
			cps->time_2_Time,
			cps->useBook,
			cps->isEGB,
			cps->UCCI_addInfo,
			cps->yqID
			);

		rc = sqlite3_exec(db_ini,sql,0,0,&szErrMsg);
		if(rc != 0){
			LogOuts(szErrMsg);
			sqlite3_free(szErrMsg);
		}
		sqlite3_close(db_ini);      //�ر����ݿ�        
	}

	return rc;
}


//ͨ�������IDɾ������
int 
DeleteCpsByYqID(int yqid){
	int rc = -1;
	sqlite3 *db_ini;
	char *szErrMsg = 0;
	char sql[4096];
	if((rc == SqliteOpenDataBase(&db_ini,L3_DB_INI)) == 0){//�򿪳ɹ���
		sprintf_s(sql,sizeof(sql),
			"DELETE FROM yq WHERE yqID = %d",yqid);
		rc = sqlite3_exec(db_ini,sql,0,0,&szErrMsg);
		if(rc != 0){
			LogOuts(szErrMsg);
			sqlite3_free(szErrMsg);
		}
		sqlite3_close(db_ini);
	}
	return rc;
}

//����һ��������,���õ��������ID
int
InsertCpsInfoToSqlite(ChessProgramState *cps, int *id){
	//1, ���趨���ݿ�
	sqlite3 *db_ini;
	char    *szErrMsg       = 0;
	int      nrow           = 0;
	int      ncolumn        = 0;
	int      rc             = -1;
	char    **azResult;
	char     sql[4096];

	if((rc = SqliteOpenDataBase(&db_ini,L3_DB_INI)) == 0){   //�򿪳ɹ���
		//����������Ϣ
		//INSERT INTO table (column_list) VALUES (value_list);
		sprintf_s(sql,sizeof(sql),
			"INSERT INTO yq (yqName,yqFile,yqAuthor,yqVerson,yqDualTime,path,xieyiID,elo,\
			initString,OtherString,smpNum,hashSize,moveTime,depth,isBaoGan,\
			BaoGanTime,stepInc,TimeUpLose,FT_Step,FT_Time,SC_Step,\
			SC_Time,haveBook,haveEGB,yqOther)  \
			VALUES('%S','%S','%S','%S','%d','%S','%d','%d','%S','%S',\
			'%d','%d','%d','%d','%d','%d','%d','%d','%d','%d',\
			'%d','%d','%d','%d','%S')",
			cps->UCCI_name,
			cps->UCCI_file,
			cps->UCCI_author,
			cps->UCCI_verson,
			cps->UCCI_dualtime,
			cps->UCCI_path,
			cps->ucci,
			cps->UCCI_Book_Num,
			cps->UCCI_iniString,
			cps->UCCI_otherString,
			cps->UCCI_smpNum,
			cps->UCCI_hashsize,
			cps->timePerStep,
			cps->timeSearchDepth,
			cps->IsBaoGan,
			cps->BaoGanTime,
			cps->timePerStepAdd,
			cps->timeIsLost,
			cps->time_1_Step,
			cps->time_1_Time,
			cps->time_2_Step,
			cps->time_2_Time,
			cps->useBook,
			cps->isEGB,
			cps->UCCI_addInfo
			);

		rc = sqlite3_exec(db_ini,sql,0,0,&szErrMsg);

		if(rc != 0){
			LogOuts(szErrMsg);
			sqlite3_free(szErrMsg);
		}

		// sprintf_s(sql,1024,"SELECT * FROM ucci");
		// SELECT relname, relpages FROM pg_class ORDER BY relpages DESC

		sprintf_s(sql,sizeof(sql),
			"SELECT yqID FROM yq ORDER BY yqID DESC");                        

		rc = sqlite3_get_table(db_ini,sql,&azResult,&nrow,&ncolumn,&szErrMsg);

		if(rc != 0){
			LogOuts(szErrMsg);
			sqlite3_free(szErrMsg);
			sqlite3_close(db_ini);
			return rc;
		}


		for(int k = 1; k <= nrow; k++){
			*id = atoi(azResult[k*ncolumn + 0]);
			break;
		}

		sqlite3_free_table(azResult);

		sqlite3_close(db_ini);
	}
	return rc;
}

//
void 
SetTimeControlItemlEnables(HWND hDlg,dispboard_t* pDis){

	ChessProgramState *cps = &pDis->set_cps;

	EnableWindow(GetDlgItem(hDlg,IDC_BanGanTime),		 cps->IsBaoGan);
	EnableWindow(GetDlgItem(hDlg,IDC_firstClassStep),	!cps->IsBaoGan);
	EnableWindow(GetDlgItem(hDlg,IDC_firstClassTime),	!cps->IsBaoGan);
	EnableWindow(GetDlgItem(hDlg,IDC_secondClassStep),	!cps->IsBaoGan);
	EnableWindow(GetDlgItem(hDlg,IDC_secondClassTime),	!cps->IsBaoGan);

	//EnableWindow(GetDlgItem(hDlg,IDC_TimeAddPerStep),	!cps->isBaoGan);

	//EnableWindow(GetDlgItem(hDlg,IDC_IsLostTimeUp),		!cps->isBaoGan);

	SendDlgItemMessage(hDlg,IDC_IsBaoGan,BM_SETCHECK,		cps->IsBaoGan,0);
	SendDlgItemMessage(hDlg,IDC_IsFenDuanTime,BM_SETCHECK, !cps->IsBaoGan,0);

	//SendDlgItemMessage(hDlg,IDC_RADIO_YQA,BM_SETCHECK,cps == &ppDis->first,0);
	//SendDlgItemMessage(hDlg,IDC_RADIO_YQB,BM_SETCHECK,cps != &ppDis->first,0);

	//if(cps->UCCI_which == 1){
	//if(cps->playWhat == WHITE){
	//   SetWindowText(hDlg,  "���� (1) ���öԻ���");	
	//}
	//else{
	//    SetWindowText(hDlg, "���� (2) ���öԻ���");	
	//}
}

//
int 
GetSelectYqID(HWND hDlg){       //�õ���ǰѡ�������ɣ�
	int sel = (int)SendDlgItemMessage(hDlg,IDC_YQ_LIST,CB_GETCURSEL,0,0);
	TCHAR buf[MSG_SIZ];
	SendDlgItemMessage(hDlg,IDC_YQ_LIST,CB_GETLBTEXT,sel,(LPARAM)buf);                        
	int id  = _wtoi(buf);
	return id;
}

LRESULT CALLBACK
YqSetCallBack(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam){


	OPENFILENAME  ofn;
	TCHAR buf[MSG_SIZ];
	TCHAR initDir[MAX_PATH];
	TCHAR title[MSG_SIZ];

	switch(message){
		case WM_INITDIALOG:{
			CenterWindow(hDlg,GetWindow(hDlg,GW_OWNER));	

			SendDlgItemMessage(hDlg,IDC_RADIO_YQA,BM_SETCHECK,1,0);
			SendDlgItemMessage(hDlg,IDC_RADIO_YQB,BM_SETCHECK,0,0);

			int  table = (int)lParam;

			SetDlgItemInt(hDlg,IDC_Table,table,FALSE);			//�����ű��浽�Ի�����

			dispboard_t *pDis = OBS[table];

			pDis->set_cps = pDis->first;							//��ʾ��һ������

			//��ʼ������ʹ���岽�б�
			//1, ����б�
			SendDlgItemMessage(hDlg,IDC_YQ_LIST_BOOK_NUM,CB_RESETCONTENT,0,0);
			
			for(int i = 0; i <= BOOK_MOVE_LEARN_PLY/2; i++){   //���25�غ�
               //char buf[
				swprintf_s(buf, sizeof(buf) / sizeof(TCHAR), _T("%d"), i);
				SendDlgItemMessage(hDlg,IDC_YQ_LIST_BOOK_NUM,CB_ADDSTRING,0,(LPARAM)buf);
			}
			//���ó�ȱʡ25�غ�
			SendDlgItemMessage(hDlg,IDC_YQ_LIST_BOOK_NUM,CB_SETCURSEL,BOOK_MOVE_LEARN_PLY/2,0);

			//��ʼ���߳��б� IDC_YQ_SMP_LIST
			SendDlgItemMessage(hDlg,IDC_YQ_SMP_LIST,CB_RESETCONTENT,0,0);
			for(int i = 0; i < 16; i++){
				swprintf_s(buf, sizeof(buf) / sizeof(TCHAR), _T("%d"), i + 1);
			   SendDlgItemMessage(hDlg,IDC_YQ_SMP_LIST,CB_ADDSTRING,0,(LPARAM)buf);
			}
			SendDlgItemMessage(hDlg,IDC_YQ_SMP_LIST,CB_SETCURSEL,0,0);  //��ʼһ���߳�

			YqInfoToSetDialog(&pDis->set_cps,hDlg);								//��������Ϣ��ʾ���Ի�����

			SetTimeControlItemlEnables(hDlg,pDis);								//��ʾ��Ӧ���趨ʱ��			

			return TRUE;
						   }
		case WM_USER_YqLoad_OK:	{		//������سɹ���

			//PostMessage(cps->loadWin,WM_USER_YqLoad_OK,0,(LPARAM)cps);  //���������ڴ��ڷ��ͳ�ʼ���ɹ�����Ϣ

			int table;
			BOOL isGet;
			int  intGet;

			intGet = GetDlgItemInt(hDlg,IDC_Table,&isGet,TRUE);

			if(isGet){
				table = intGet;
			}
			else{
				table = 0;
			}
			dispboard_t *pDis = OBS[table];		//cps = pDis->cur_set_cps;

			ChessProgramState *loadokcps = (ChessProgramState*)lParam;

			//loadokcps->isInLoading		= FALSE;
			//loadokcps->isUpLoading      = FALSE;
			//loadokcps->UCCI_initDone	= TRUE;

			//loadokcps->playWhat         = NEUTRAL;

			loadokcps->cps_stat = Cps_Waiting;

			//����������ݿ�����Ӧ����ʾ��ȥ
			if(loadokcps->playWhat != NEUTRAL){
				GetTimeInfoFromCps(pDis, &pDis->TimeDisp[loadokcps->playWhat], loadokcps);
			}


			//��������

			if(loadokcps->yqID == pDis->set_cps.yqID){
				SendToPlayerByColor(L"\n������سɹ���!!\n",ColorShout,TRUE);
				LogOut(loadokcps->UCCI_name);		
				LogOut(loadokcps->UCCI_path);

				//pDis->set_cps.isInLoading = FALSE;

				pDis->set_cps.cps_stat = Cps_Waiting;

				memcpy(pDis->set_cps.loadWhich, &pDis->set_cps, sizeof(ChessProgramState));
				YqInfoToSetDialog(&pDis->set_cps,hDlg);
				SetTimeControlItemlEnables(hDlg,pDis);

				//1, �õ�CPS�Ŀ��Ʋ���
				//GetTimeSetInfoFromCps(loadokcps);				
				//2, ���ͳ�ʼ������CPS
				SendControlParameterToCps(loadokcps);
			}
			else{
				//
				SendToPlayerByColor(L"�����ˣ����سɹ������治�ǵ�ǰ�趨������!!\n",ColorShout,FALSE);
			}

								}
								break;
		case WM_USER_YqUpload_OK:			//������ж�سɹ���
			{
				ChessProgramState *uploadokcps = (ChessProgramState*)lParam;

				LogOut(_T("\n��������\n<"));
				LogOut(uploadokcps->UCCI_name);
				LogOut(_T("\n��ж�سɹ�"));

				if(uploadokcps->loadWhich != NULL){
					LogOut(_T("\n���ڼ������棺"));
					LogOut(uploadokcps->loadWhich->UCCI_name);
					LogOut(_T("\n����ҪһЩʱ�䣬���Ժ�....\n"));

					StartChessProgram(uploadokcps->loadWhich);
				}
			}
			break;
			//--------------------------------------------------------------                 
		case WM_COMMAND:{	//�а�ť��Ϣ  			

			int table;
			BOOL isGet;
			int  intGet;

			intGet = GetDlgItemInt(hDlg,IDC_Table,&isGet,TRUE);

			if(isGet){
				table = intGet;
			}
			else{
				table = 0;
			}
			dispboard_t *pDis = OBS[table];		//cps = pDis->cur_set_cps;



			switch(LOWORD(wParam)){
				//		                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
		case IDC_YQ_ADD:{                   //������水ť
			ZeroMemory(&ofn,sizeof(ofn));
			ofn.lStructSize         = sizeof(OPENFILENAME);
			ofn.lpstrFilter         = _T("��������\0*.exe\0");
			ofn.nMaxCustFilter      = MSG_SIZ;
			ofn.nFilterIndex        = 1;
			ofn.hInstance           = hInst;
			ofn.nMaxFile            = MAX_PATH;
			ofn.hwndOwner           = hDlg;
			buf[0]                  = 0;
			ofn.lpstrFile           = buf;
			StringCbPrintf(title,sizeof(title),
				_T("��ѡ��һ���������� (����Ӧ����������Ŀ¼�µ�pluginsĿ¼��!)"));
			ofn.lpstrTitle          = title;
			StringCbPrintf(initDir,sizeof(initDir),
				_T("%s%s"), installDir, L"plugins\\");
			ofn.lpstrInitialDir		= initDir;			//��ʼ��Ŀ¼
			ofn.Flags               = OFN_EXPLORER+OFN_FILEMUSTEXIST+OFN_PATHMUSTEXIST+OFN_HIDEREADONLY;
			if(GetOpenFileName(&ofn)){
				//���ж�һ�£��ǲ�����installDir����
				_wcslwr_s(initDir, sizeof(initDir)/sizeof(TCHAR));
				_wcslwr_s(buf, sizeof(buf)/sizeof(TCHAR));
				if(wcsstr(buf,initDir) == NULL){
					StringCbPrintf(buf, MSG_SIZ, _T("�뽫��������ŵ� %sĿ¼�£�"), initDir);
					MessageBox(hDlg, buf, _T("ERROR..."), MB_OK);
					return TRUE;
				}

				//�õ���һ�������ļ�

				//1,�õ����������
				ChessProgramState tmp[1];

				memcpy(tmp,&pDis->set_cps,sizeof(ChessProgramState));

				StringCbPrintf(tmp->UCCI_file,sizeof(tmp->UCCI_file),buf+ofn.nFileOffset);
				StringCbPrintf(tmp->UCCI_name,sizeof(tmp->UCCI_file),buf+ofn.nFileOffset);

				//2,�õ������Ŀ¼
				TCHAR *p1 = wcsstr(buf,_T("plugins\\"));
				TCHAR *p2 = wcsstr(buf, tmp->UCCI_file);

				StringCbPrintf(tmp->UCCI_path,(p2-p1+1)*sizeof(TCHAR),p1);

				LogOut(_T("�������棺<<"));
				LogOut(tmp->UCCI_name);

				int id = pDis->set_cps.yqID;

				if(InsertCpsInfoToSqlite(tmp, &id) == 0){       //����Ϣ���浽���ݿ���                            
					//LogOut(">>�ѳɹ�����! �������Ӧ������\n");
					SendToPlayerByColor(L">>�ѳɹ�����! �������Ӧ������\n",ColorShout,FALSE);

					//�õ���ǰ��ID��Ϣ
					GetYqinfoFromSqliteByID(tmp, id);

					FillYqListToSetDialog(tmp,hDlg);	 //���ǽ�ԭ��ʹ�õ���ʾһ��

					pDis->set_cps.yqID = id;			 //���µ�ǰ��ID

					YqInfoToSetDialog(&pDis->set_cps,hDlg);
				}
				else{
					//LogOut(">>����ʧ��!\n");
					SendToPlayerByColor(L">>����ʧ��!\n",ColorShout,FALSE);
				}
			}  
						}
						break;
						//
		case IDC_IsBaoGan:{                  //���ɼ�ʱ��ť
			pDis->set_cps.IsBaoGan   = TRUE;
			SetTimeControlItemlEnables(hDlg,pDis);
						  }
						  break;    
						  //
		case IDC_IsFenDuanTime:  {           //�ֶμ�ʱ��ť
			pDis->set_cps.IsBaoGan    = FALSE;
			SetTimeControlItemlEnables(hDlg,pDis);
								 }
								 break;
								 //
		case IDC_RADIO_YQA: {                //����(1)��ť
			if(IsDlgButtonChecked(hDlg,IDC_RADIO_YQA) == BST_CHECKED){

				SendDlgItemMessage(hDlg,IDC_RADIO_YQB,BM_SETCHECK,0,0);

				pDis->set_cps = pDis->first;

				GetYqinfoFromSqliteByID(&pDis->set_cps,pDis->set_cps.yqID);

				YqInfoToSetDialog(&pDis->set_cps,hDlg);
			}
			SetTimeControlItemlEnables(hDlg,pDis);
							}
							break;
							//
		//case IDC_RADIO_YQB:  {               //����(2)��ť
		//	if(IsDlgButtonChecked(hDlg,IDC_RADIO_YQB) == BST_CHECKED){

		//		SendDlgItemMessage(hDlg,IDC_RADIO_YQA,BM_SETCHECK,0,0);

		//		pDis->set_cps = pDis->second;

		//		GetYqinfoFromSqliteByID(&pDis->set_cps,pDis->set_cps.yqID);

		//		YqInfoToSetDialog(&pDis->set_cps,hDlg);

		//		SetTimeControlItemlEnables(hDlg,pDis);
		//	}           
		//					 }
		//					 break;
							 //  
		case IDC_YQ_LIST: {    //�ı��˵�ǰ������
			if(HIWORD(wParam) == CBN_SELCHANGE){

				pDis->set_cps.yqID = GetSelectYqID(hDlg);

				GetYqinfoFromSqliteByID(&pDis->set_cps,pDis->set_cps.yqID);

				YqInfoToSetDialog(&pDis->set_cps,hDlg);

				SetTimeControlItemlEnables(hDlg,pDis);
			}
						  }
						  break;
						  //
		case IDC_DELETE_YQ:                 //ɾ�����水ť
			{
				if(MessageBox(hDlg,_T("��ȷ��,��������ɾ����������!"),_T("ע����!"),MB_OKCANCEL) == IDOK){
					int id  = GetSelectYqID(hDlg);

					if(DeleteCpsByYqID(id) == SQLITE_OK){
						SendToPlayerByColor(L"\n���ѳɹ�ɾ����һ������\n",ColorShout,FALSE);

						//����ǰ�������趨Ϊʹ�õ�����
						if(IsDlgButtonChecked(hDlg,IDC_RADIO_YQA) == BST_CHECKED){	//�������������
							pDis->set_cps = pDis->first;
						}
						//else{
						//	pDis->set_cps = pDis->second;
						//}
						YqInfoToSetDialog(&pDis->set_cps,hDlg);
						SetTimeControlItemlEnables(hDlg,pDis);
					}
					else{
						SendToPlayerByColor(L"\n���޷�ɾ���������\n",ColorShout,FALSE);
					}
				}
			}
			break;
			//
		case ID_LOAD_SET_YQ: {            //����һ������

			//if(TRUE == pDis->set_cps.isInLoading){		//��ǰ���ڼ�������

			if(pDis->set_cps.cps_stat == Cps_InLoading){
				SendToPlayerByColor(L"\n��ǰ���ڼ�������֮��\n",ColorShout,FALSE);
				break;
			}

			BOOL can = TRUE;
			ChessProgramState *precps = NULL;
			if(IsDlgButtonChecked(hDlg,IDC_RADIO_YQA) == BST_CHECKED){
				if(pDis->set_cps.yqID == pDis->first.yqID){		//
					can = FALSE;							
				}
				precps = &pDis->first;
			}
			//else{
			//	if(pDis->set_cps.yqID == pDis->second.yqID){		//
			//		can = FALSE;							
			//	}
			//	precps = &pDis->second;
			//}
			if(can == FALSE){
				MessageBox(hDlg, _T("���Ѽ����˵�ǰ�����棬��Ҫ�ټ�����"), _T("Error"), MB_OK);
				EnableWindow(GetDlgItem(hDlg,ID_LOAD_SET_YQ),FALSE);
				break;
			}

			LoadChessProgramState(precps, &pDis->set_cps, hDlg);					

							 }
							 break;
							 //
		case ID_UPDATE_SET_ONLY:      //�����ø���
			{                       
				//1����Ҫ��һ��Ҫ���µ��ǲ����뵱ǰʹ�õ�һ��

				ChessProgramState tmp[1];						

				SetDialogToCps(tmp,hDlg);

				if(UpdateCpsInfoToSqlite(tmp) == SQLITE_OK){

					//��Ҫ��һ���ǲ��ǵ�ǰʹ�õ���������
					if(pDis->set_cps.yqID == pDis->first.yqID){											

						SetDialogToCps(&pDis->first,hDlg);

						SendControlParameterToCps(&pDis->first);
					}
					//if(pDis->set_cps.yqID == pDis->second.yqID){								

					//	SetDialogToCps(&pDis->second,hDlg);
					//	SendControlParameterToCps(&pDis->second);
					//}

					ResetClocks(pDis);

					//GetTimeInfoFromCps(pDis, &pDis->TimeDisp[WHITE], &pDis->first);
					//GetTimeInfoFromCps(pDis, &pDis->TimeDisp[BLACK], &pDis->second);

					//if(pDis->first.playWhat != NEUTRAL){
					//	GetTimeInfoFromCps(pDis, &pDis->TimeDisp[pDis->first.playWhat], &pDis->first);
					//}

					//if(pDis->second.playWhat != NEUTRAL){
					//	GetTimeInfoFromCps(pDis, &pDis->TimeDisp[pDis->second.playWhat], &pDis->second);
					//}

					LogOut(_T("\n���µ�ǰ�������óɹ���\n"));
				}
				else{
					SendToPlayerByColor(_T("\n���޷����µ�ǰ���������\n"), ColorShout, FALSE);
				}						
			}
			break;
		case IDOK:                          //ȷ�ϰ�ť

			{
				//1, ���ǲ��Ǹ���������,����Ǹ����ˣ���Ҫֹͣ��ǰ�ģ����Լ������ڵģ�

				//if(pDis->set_cps.isInLoading == TRUE){		//���ڼ��ص�ǰ������
				if(pDis->set_cps.cps_stat == Cps_InLoading){
					SendToPlayerByColor(L"\n���ڼ��ص�ǰ���棬���Ժ򡣡���\n",ColorShout,FALSE);
					break;
				}						

				if(pDis->first.cps_stat == Cps_NotLoad){
					SendToPlayerByColor(L"\n��һ���滹û���سɹ��������¼��ػ����������һ��\n",ColorShout,FALSE);
					//break;
				}
				//if(pDis->second.cps_stat == Cps_NotLoad){
				//	SendToPlayerByColor(L"\n�ڶ����滹û���سɹ��������¼��ػ����������һ��\n",ColorShout,FALSE);
				//	//break;
				//}



				//����һ������
				ChessProgramState tmp[1];						
				SetDialogToCps(tmp,hDlg);

				if(UpdateCpsInfoToSqlite(tmp) != SQLITE_OK){
					SendToPlayerByColor(L"\n���޷����µ�ǰ���������\n",ColorShout,FALSE);
					break;
				}
				else{
					//��Ҫ��һ���ǲ��ǵ�ǰʹ�õ���������
					if(pDis->set_cps.yqID == pDis->first.yqID){											

						SetDialogToCps(&pDis->first,hDlg);
						SendControlParameterToCps(&pDis->first);
					}
					//if(pDis->set_cps.yqID == pDis->second.yqID){								

					//	SetDialogToCps(&pDis->second,hDlg);
					//	SendControlParameterToCps(&pDis->second);
					//}

					ResetClocks(pDis);

					//GetTimeInfoFromCps(pDis, &pDis->TimeDisp[WHITE], &pDis->first);
					//GetTimeInfoFromCps(pDis, &pDis->TimeDisp[BLACK], &pDis->second);

					//if(pDis->first.playWhat != NEUTRAL){
					//	GetTimeInfoFromCps(pDis, &pDis->TimeDisp[pDis->first.playWhat], &pDis->first);
					//}

					//if(pDis->second.playWhat != NEUTRAL){
					//	GetTimeInfoFromCps(pDis, &pDis->TimeDisp[pDis->second.playWhat], &pDis->second);
					//}

					//SendToPlayerByColor("\n���µ�ǰ�������óɹ���\n",ColorShout,FALSE);
					LogOut(_T("\n���µ�ǰ�������óɹ���\n"));
				}						

				DisplayBothClocks(pDis);

				EndDialog(hDlg, TRUE);
				return TRUE;
			} 
			break;
		case IDCANCEL:

			//if(pDis->first.UCCI_initDone == FALSE){
			//	SendToPlayerByColor("\n��һ���滹û���سɹ��������¼��ػ����������һ��\n",ColorShout,FALSE);
			//	break;
			//}
			//else if(pDis->second.UCCI_initDone == FALSE){
			//	SendToPlayerByColor("\n�ڶ����滹û���سɹ��������¼��ػ����������һ��\n",ColorShout,FALSE);
			//	break;
			//}

			DisplayBothClocks(pDis);
			EndDialog(hDlg,FALSE);
			return TRUE;                    
		default:
			break;
			}
						}
						break;        
		default:
			break;
	}

	return FALSE;
}

//�������öԻ��� ����һ�����Ų���

void		
YqSetOptionsPopup(int table){

	dispboard_t *pDis = OBS[table];
	FARPROC lpProc = MakeProcInstance((FARPROC)YqSetCallBack, hInst);
	DialogBoxParam(hInst,MAKEINTRESOURCE(IDD_YQ_SET),pDis->hwndThis,(DLGPROC) lpProc,(LPARAM)table);
	FreeProcInstance(lpProc);

}
