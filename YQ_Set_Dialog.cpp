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

//ж���������߳�
//DWORD WINAPI 
//UnLoadCpsThread(LPVOID lpParam){
//    ChessProgramState *cps = (ChessProgramState *)lpParam;
//
// 
//   
//
//    if(cps->UCCI_initDone == 0){
//        //MessageBox(hwndMain,"��ǰ���滹û���أ�����ж�أ�",cps->UCCI_name,MB_OK);
//		cps->hwndHide = NULL;
//        LogOut("��ǰ���滹û���أ�����ж�أ�\n");
//        return false;
//    }
//
//    //if(cps->UCCI_which != 1 && cps->UCCI_which != 2){
//    //if(cps->playWhat == NEUTRAL){
//    //    //MessageBox(hwndMain,"���Ҫж�ص����治�ǹ������棡",cps->UCCI_name,MB_OK);
//    //    LogOut("���Ҫж�ص����治�ǹ������棡\n");
//    //    return false;
//    //}
//
//    if(cps->hwndHide != NULL){
//         ShowWindow(cps->hwndHide,SW_HIDE);
//    }
//    //dispboard_t* DIS = OBS[cps->table];
//    //
//    LogOut("����ж�����棺");
//    LogOut(cps->UCCI_name);
//    LogOut("\n����ҪһЩʱ�䣬���Ժ�....\n");
//
//    bool rc = false;
//    switch(cps->ucci){
//        case UCCI_UCCI162:
//            if(cps->maybeThinking){
//                SendToProgram("stop\n", cps);
//                Sleep(1000);
//            }
//            SendToProgram("quit\n",cps);
//            for(int i = 0; i < 50; i++){
//                Sleep(100);
//                if(cps->UCCI_initDone == 0){
//                    rc = true;
//                    break;
//                }
//            }
//            break;
//        case UCCI_CYC105:
//            if(cps->maybeThinking){
//                SendToProgram("stop\n", cps);
//                Sleep(1000);
//            }
//            SendToProgram("quit\n",cps);
//            for(int i = 0; i < 50; i++){
//                Sleep(100);
//                if(cps->UCCI_initDone == 0){
//                    rc = true;
//                    break;
//                }
//            }
//            break;
//        case UCCI_DIS:
//            break;
//        case UCCI_QH:
//            break;
//        case UCCI_OTHER:
//            break;
//        default:
//            break;
//    }
//
//    if(rc == true){
//        LogOut("ж������ɹ��ˣ�\n");
//    }
//    else{
//        LogOut("ж������ʧ�ܣ�\n");
//    }
//
//    if(cps->hwndHide != NULL){
//        ShowWindow(cps->hwndHide,SW_SHOW);
//        cps->hwndHide = NULL;
//    }
//    return rc;
//}
////ж��һ������
//void 
//UnLoadChessProgramState(ChessProgramState *cps, HWND win){
//
//    DWORD dwThreadId;    
//    cps->hwndHide = win;
//    //DWORD dwThrdParam = cps->UCCI_which;
//
//    HANDLE hLoadCPS = CreateThread(
//        NULL,
//        NULL,
//        UnLoadCpsThread,
//        cps,
//        0,
//        &dwThreadId);
//
//    //                //    if(cps->UCCI_initDone){
//    //                //    LogOut(ColorShout,"����ж�����棺",true);
//    //                //    LogOut(ColorShour,cps->UCCI_name,true);
//    //                //    LogOut(ColorSeek,"����ҪһЩʱ�䣬���Ժ�....��n",true);
//    //                //    if(UnLoadChessProgramState(cps)){
//    //                //        LogOut(
//    //                //    }
//    //                //    else{
//    //                //    }
//    //                //}
//
//    //if(cps->UCCI_initDone == 0){
//    //    //MessageBox(hwndMain,"��ǰ���滹û���أ�����ж�أ�",cps->UCCI_name,MB_OK);
//    //    LogOut(ColorShout,"��ǰ���滹û���أ�����ж�أ�\n",true);
//    //    return false;
//    //}
//
//    //if(cps->UCCI_which != 1 && cps->UCCI_which != 2){
//    //    //MessageBox(hwndMain,"���Ҫж�ص����治�ǹ������棡",cps->UCCI_name,MB_OK);
//    //    LogOut(ColorShout,"���Ҫж�ص����治�ǹ������棡\n",true);
//    //    return false;
//    //}
//
//    ////
//    //LogOut(ColorShout,"����ж�����棺",true);
//    //LogOut(ColorShout,cps->UCCI_name,true);
//    //LogOut(ColorSeek,"\n����ҪһЩʱ�䣬���Ժ�....\n",true);
//
//    //bool rc = false;
//    //switch(cps->ucci){
//    //    case UCCI_UCCI:
//    //        break;
//    //    case UCCI_DIS:
//    //        break;
//    //    case UCCI_QH:
//    //        break;
//    //    case UCCI_OHTER:
//    //        break;
//    //    default:
//    //        break;
//    //}
//
//    //if(rc == true){
//    //    LogOut(ColorShout,"ж������ɹ��ˣ�\n",true);
//    //}
//    //else{
//    //    LogOut(ColorShout,"ж������ʧ�ܣ�\n",true);
//    //}
//    //return rc;
//}
//
//

//
//DWORD WINAPI 
//LoadCpsThread(LPVOID lpParam){  
//
//   char buf[MSG_SIZ];
//
//    ChessProgramState *cps = (ChessProgramState *)lpParam;      //��
//
//    //if(cps->UCCI_which != 1 && cps->UCCI_which != 2){
//    //    //MessageBox(hwndMain,"���Ҫ���ص����治�ǹ������棡",cps->UCCI_name,MB_OK);
//    //    LogOut("���Ҫ���ص����治�ǹ������棡\n");
//    //    return false;
//    //}
//
//    if(cps->UCCI_initDone == 1){        //�����������Ѽ�����,����ж����
//        UnLoadChessProgramState(cps, cps->hwndHide);
//    }
//
//    for(int i = 0; i < 100; i++){
//        if(cps->UCCI_initDone == 0){        //��ж����
//          break;
//        }       
//        Sleep(100);
//    }
//    if(cps->UCCI_initDone == 1){
//        //MessageBox(cps->hwndParent,cps->UCCI_name,"�����ˣ�������治��ж�أ���",MB_OK);
//        MessageBox(OBS[cps->table]->hwndThis,cps->UCCI_name,"�����ˣ�������治��ж�أ���",MB_OK);
//        return false;
//    }
//
//    //if(cps->UCCI_initDone == 1){
//    //    //MessageBox(hwndMain,"��ǰ���滹�ѳɹ����أ�������ж�أ�",cps->UCCI_name,MB_OK);
//    //    LogOut(ColorShout,"��ǰ���滹�ѳɹ����أ������ټ��أ�\n",true);
//    //    return false;
//    //}
//
//
//    //
//
//    if(cps->hwndHide != NULL){
//        ShowWindow(cps->hwndHide,SW_HIDE);
//    }
//
//    bool rc = false;
//
//    //LogOut(ColorShout,"���ڼ������棺",true);
//    //LogOut(ColorShout,cps->UCCI_name,true);
//    //LogOut(ColorSeek,"\n����ҪһЩʱ�䣬���Ժ�....\n",true);
//
//    sprintf_s(buf,MSG_SIZ,"���ڼ�������: ����: %s\n�ļ���: %s%s\n������ҪһЩʱ��,���Ե�...\n",
//        cps->UCCI_name,cps->UCCI_path,cps->UCCI_file);
//
//    LogOut(buf);
//
//    switch(cps->ucci){
//        case UCCI_UCCI162:
//            StartChessProgram(cps);
//            for(int i = 0; i < 50; i++){
//                Sleep(100);
//                if(cps->UCCI_initDone == 1){
//                    rc = true;
//                    break;
//                }
//            }           
//            break;
//        case UCCI_CYC105:
//            StartChessProgram(cps);
//            for(int i = 0; i < 50; i++){
//                Sleep(100);
//                if(cps->UCCI_initDone == 1){
//                    rc = true;
//                    break;
//                }
//            } 
//            break;
//        case UCCI_DIS:		//����ǼѼ��������
//            break;
//        case UCCI_QH:
//            break;
//        case UCCI_OTHER:
//            break;
//        default:
//            break;
//    }
//
//    if(rc == true){
//        LogOut("��������ɹ��ˣ�\n");
//    }
//    else{
//        LogOut("��������ʧ�ܣ�\n");
//    }
//
//    if(cps->hwndHide != NULL){
//        ShowWindow(cps->hwndHide,SW_SHOW);
//        cps->hwndHide = NULL;
//    }
//
//    return 0;
//}
//


void 
LoadChessProgramState(ChessProgramState *precps, ChessProgramState *loadcps, HWND hWin){

	//ShowWindow(win,SW_HIDE);			//����������һ��

	loadcps->loadWin        = hWin;		   //��������Ĵ��ڣ����򴰿ڷ�����ɵģ����˳�����Ϣ

	//1, �ڼ���ǰ��Ҫж��Ҫ���ص�����
	if(precps->UCCI_initDone == TRUE){		//��Ҫ��ж����
		LogOut("\n����ж������: ");
		LogOut(precps->UCCI_name);
		LogOut("\n����ҪһЩʱ�䣬 ���Ժ�...\n");

		switch(precps->ucci){
			case UCCI_UCCI162:
				if(precps->maybeThinking){
					SendToProgram("stop\n",precps);
					Sleep(500);
				}
				SendToProgram("quit\n", precps);
				for(int i = 0; i < 50; i++){
					Sleep(100);
					if(precps->UCCI_initDone == FALSE){
						break;
					}
				}
				break;
			case UCCI_CYC105:
				if(precps->maybeThinking){
					SendToProgram("stop\n",precps);
					Sleep(500);
				}
				SendToProgram("quit\n", precps);
				for(int i = 0; i < 50; i++){
					Sleep(100);
					if(precps->UCCI_initDone == FALSE){
						break;
					}
				}
				break;
			case UCCI_DIS:
				if(precps->maybeThinking){
					SendToProgram("stop\n",precps);
					Sleep(500);
				}
				SendToProgram("quit\n", precps);
				for(int i = 0; i < 50; i++){
					Sleep(100);
					if(precps->UCCI_initDone == FALSE){
						break;
					}
				}		
				break;
			default:
				break;
		}
	}

	if(precps->UCCI_initDone == TRUE){
		LogOut("\n��ǰ���治��ж��\n");
		return;
	}

	//struct _CPS * loadWhich;        //�������浽��һ������first,����second
	//BOOL          isInLoading;      //�������ڼ���֮�У�

	loadcps->loadWhich		= precps;
	loadcps->isInLoading	= TRUE;        //���ڼ�������
	

	LogOut("\n���ڼ������棺");
	LogOut(loadcps->UCCI_name);
	LogOut("\n����ҪһЩʱ�䣬���Ժ�....\n");

	StartChessProgram(loadcps);

}

//����һ������
//bool 
//LoadChessProgramState(ChessProgramState *cps){
//    
//    if(cps->UCCI_initDone == 1){
//        //MessageBox(hwndMain,"��ǰ���滹�ѳɹ����أ�������ж�أ�",cps->UCCI_name,MB_OK);
//        LogOut(ColorShout,"��ǰ���滹�ѳɹ����أ�������ж�أ�\n",true);
//        return false;
//    }
//    if(cps->UCCI_which != 1 && cps->UCCI_which != 2){
//        //MessageBox(hwndMain,"���Ҫ���ص����治�ǹ������棡",cps->UCCI_name,MB_OK);
//        LogOut(ColorShout,"���Ҫ���ص����治�ǹ������棡\n",true);
//        return false;
//    }
//
//    bool rc = false;
//
//    LogOut(ColorShout,"���ڼ������棺",true);
//    LogOut(ColorShout,cps->UCCI_name,true);
//    LogOut(ColorSeek,"\n����ҪһЩʱ�䣬���Ժ�....\n",true);
//
//
//    switch(cps->ucci){
//        case UCCI_UCCI:
//            StartChessProgram(cps);
//            for(int i = 0; i < 120; i++){
//                Sleep(100);
//                //if(cps->UCCI_which == 1){
//                //    if(DIS.first.UCCI_initDone == 1){
//                //        rc = true;
//                //        break;
//                //    }
//                //}
//                //else{
//                //    if(DIS.second.UCCI_initDone == 1){
//                //        rc = true;
//                //        break;
//                //    }
//                //}
//                if(cps->UCCI_initDone == 1){
//                    rc = true;
//                    break;
//                }
//            }
//            //Sleep(3000);
//            //if(cps->UCCI_initDone == 1){
//            //    rc = true;
//            //}
//            //else{
//            //    rc = false;
//            //}            
//            break;
//        case UCCI_DIS:
//            break;
//        case UCCI_QH:
//            break;
//        case UCCI_OHTER:
//            break;
//        default:
//            break;
//    }
//
//    if(rc == true){
//        LogOut(ColorShout,"��������ɹ��ˣ�\n",true);
//    }
//    else{
//        LogOut(ColorSeek,"��������ʧ�ܣ�\n",false);
//    }
//
//    return rc;
//}

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
        LogOut("-------------���ܴ��趨���ݿ�-------------\n"); 
        return rc;      //���д�,���ܱ���
    }

    sprintf_s(sql,1024,"SELECT * FROM yq WHERE yqID = %d",id);

    rc = sqlite3_get_table(db_ini,sql,&azResult,&nrow,&ncolumn,&szErrMsg);

    if(rc != SQLITE_OK){
        return rc;
    }

    if(nrow != 0){      //�ҵ��˼�¼ 
        cps->yqID = id;
        sprintf_s(cps->UCCI_name,sizeof(cps->UCCI_name),"%s",azResult[ncolumn+1]);
        sprintf_s(cps->UCCI_file,sizeof(cps->UCCI_file),"%s",azResult[ncolumn+2]);
        sprintf_s(cps->UCCI_author,sizeof(cps->UCCI_author),"%s",azResult[ncolumn+3]);
        sprintf_s(cps->UCCI_verson,sizeof(cps->UCCI_verson),"%s",azResult[ncolumn+4]);
        /*sprintf_s(cps->UCCI_dualtime,"%d",*/
        cps->UCCI_dualtime = atoi(azResult[ncolumn+5]);
        sprintf_s(cps->UCCI_path,sizeof(cps->UCCI_path),"%s",azResult[ncolumn+6]);
        cps->ucci       = atoi(azResult[ncolumn+7]);
        cps->UCCI_elo   = atoi(azResult[ncolumn+8]);        
        sprintf_s(cps->UCCI_iniString,sizeof(cps->UCCI_iniString),"%s",azResult[ncolumn+9]);
        sprintf_s(cps->UCCI_otherString,sizeof(cps->UCCI_otherString),"%s",azResult[ncolumn+10]);
        
        cps->UCCI_smpNum    = atoi(azResult[ncolumn+11]);
        cps->UCCI_hashsize  = atoi(azResult[ncolumn+12]);
        cps->timePerStep    = atoi(azResult[ncolumn+13]);
        cps->searchDepth    = atoi(azResult[ncolumn+14]);
        cps->isBaoGan       = atoi(azResult[ncolumn+15]);
        cps->BaoGanTime     = atoi(azResult[ncolumn+16]);
        cps->addTimePerStep = atoi(azResult[ncolumn+17]);
        cps->islostTimeUp   = atoi(azResult[ncolumn+18]);
        cps->firstClassTimeStep = atoi(azResult[ncolumn+19]);
        cps->firstClassTime     = atoi(azResult[ncolumn+20]);
        cps->secondClassTimeStep= atoi(azResult[ncolumn+21]);
        cps->secondClassTime    = atoi(azResult[ncolumn+22]);
        cps->isBook             = atoi(azResult[ncolumn+23]);
        cps->isEGB              = atoi(azResult[ncolumn+24]);
        sprintf_s(cps->UCCI_addInfo,sizeof(cps->UCCI_addInfo),"%s",azResult[ncolumn+25]);
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
        LogOut("-------------���ܴ��趨���ݿ�-------------\n"); 
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
        char  info[128];
        sprintf_s(info,sizeof(info),"%d) %s <%s>",id,azResult[k*ncolumn+0],azResult[k*ncolumn+2]);
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
    char    buf[512];

    if(rc = SqliteOpenDataBase(&db_ini,L3_DB_INI)){
        LogOut("-------------���ܴ��趨���ݿ�-------------\n"); 
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
        sprintf_s(tmp->UCCI_name,32,"%s",azResult[(k)*ncolumn + 1]);
        //
        sprintf_s(buf,sizeof(buf),"%d) %s",tmp->yqID,tmp->UCCI_name);
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
	char buf[512];

	intGet = GetDlgItemInt(hDlg,IDC_Table,&isGet,false);

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
		sprintf_s(buf,sizeof(buf),"���� (1) ���öԻ���, ʹ�������: %d, ��ǰ�����: %d", 
			pDis->first.yqID,	cps->yqID);

		//��һ�±���ǲ�����ͬ��
		if(pDis->first.yqID != cps->yqID){
			isDef = TRUE;
		}

	}
	else{
		sprintf_s(buf,sizeof(buf),"���� (2) ���öԻ���, ʹ�������: %d, ��ǰ�����: %d", 
			pDis->second.yqID,	cps->yqID);
		//��һ�±���ǲ�����ͬ��
		if(pDis->second.yqID != cps->yqID){
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
	if(pDis->set_cps.yqID != pDis->first.yqID && pDis->set_cps.yqID != pDis->second.yqID){
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

    //4, ��������
    SetDlgItemText(hDlg,IDC_YQ_NAME,cps->UCCI_name);

    //5, �����������
    SetDlgItemInt(hDlg, IDC_YQ_ELO, cps->UCCI_elo,false); //FALSE, uValue is unsigned. 
    
    //6, ���߳�  IDC_SMP_NUM
    SetDlgItemInt(hDlg,IDC_SMP_NUM,cps->UCCI_smpNum,false);

    //���������
    SetDlgItemText(hDlg,IDC_YQ_PROGRAME,cps->UCCI_file);

    //�������·��
    SetDlgItemText(hDlg,IDC_YQ_PATH,cps->UCCI_path);

    //��ʼָ��
    SetDlgItemText(hDlg,IDC_initString,cps->UCCI_iniString);
    //����ָ��
    SetDlgItemText(hDlg,IDC_YqOtherString,cps->UCCI_otherString);
    //���ֿ�
    SendDlgItemMessage(hDlg,IDC_IsBook,BM_SETCHECK,cps->isBook,0);
    //�оֿ�
    SendDlgItemMessage(hDlg,IDC_IsEGB, BM_SETCHECK,cps->isEGB,0);
    //hash���С
    SetDlgItemInt(hDlg,IDC_HashSize,cps->UCCI_hashsize,false);
    //ÿ�����ʱ��
    SetDlgItemInt(hDlg,IDC_TimePerStep,cps->timePerStep,false);
    //depth
    SetDlgItemInt(hDlg,IDC_SearchDepth,cps->searchDepth,false);

    //���ɼ�ʱ
    SendDlgItemMessage(hDlg,IDC_IsBaoGan,BM_SETCHECK,cps->isBaoGan,0);
    //�Ƿ�ֶμ�ʱ IDC_IsFenDuanTime
    SendDlgItemMessage(hDlg,IDC_IsFenDuanTime,BM_SETCHECK,!cps->isBaoGan,0);

    //���ٷ���ÿ�� IDC_BanGanTime
    SetDlgItemInt(hDlg,IDC_BanGanTime,cps->BaoGanTime,false);
    //ÿ��һ����ʱ TimeAddPerStep
    SetDlgItemInt(hDlg,IDC_TimeAddPerStep,cps->addTimePerStep,false);
    //IDC_IsLostTimeUp ?
    SendDlgItemMessage(hDlg,IDC_IsLostTimeUp,BM_SETCHECK,cps->islostTimeUp,0);

    //��һʱ��β� IDC_firstClassStep
    SetDlgItemInt(hDlg,IDC_firstClassStep,cps->firstClassTimeStep,false);
    //��һʱ���ʱ�� IDC_firstClassTime
    SetDlgItemInt(hDlg,IDC_firstClassTime,cps->firstClassTime,false);
    //�ڶ�ʱ��β�
    SetDlgItemInt(hDlg,IDC_secondClassStep,cps->secondClassTimeStep,false);
    //�ڶ�ʱ���ʱ�� secondClassTime
    SetDlgItemInt(hDlg,IDC_secondClassTime,cps->secondClassTime,false);
}

//���Ի������Ϣת��CPS��
bool
SetDialogToCps(ChessProgramState *cps, HWND hDlg){

    BOOL isGet;
    int  intGet;

    //1,�õ���ǰѡ�������ı��
    int sel = (int)SendDlgItemMessage(hDlg,IDC_YQ_LIST,CB_GETCURSEL,0,0);
    char buf[MSG_SIZ];
    SendDlgItemMessage(hDlg,IDC_YQ_LIST,CB_GETLBTEXT,sel,(LPARAM)buf);

    cps->yqID  = atoi(buf);

    //�õ�ѡ��Э����
    sel = (int)SendDlgItemMessage(hDlg,IDC_YQUCCI,CB_GETCURSEL,0,0);
    SendDlgItemMessage(hDlg,IDC_YQUCCI,CB_GETLBTEXT,sel,(LPARAM)buf);

    cps->ucci = atoi(buf);

    //�õ����������
    GetDlgItemText(hDlg,IDC_YQ_NAME,cps->UCCI_name,sizeof(cps->UCCI_name));

    //�õ����浱ǰ�ģţ̣�
    intGet = GetDlgItemInt(hDlg,IDC_YQ_ELO,&isGet,false);
    if(!isGet){
       MessageBox(hDlg,"��������ȷ������÷�(ELO)!","�ţңңϣҡ�����",MB_OK);
       return false;
    }
    cps->UCCI_elo = intGet;

    //�߳���
    intGet = GetDlgItemInt(hDlg,IDC_SMP_NUM,&isGet,false);
    if(!isGet){
       MessageBox(hDlg,"��������ȷ���߳���!","�ţңңϣҡ�����",MB_OK);
       return false;
    }
    cps->UCCI_smpNum = intGet;
    if(cps->UCCI_smpNum < 0 || cps->UCCI_smpNum > 16){
        cps->UCCI_smpNum = 1;
    }
   

    //�Ƿ��п��ֿ�
    if(IsDlgButtonChecked(hDlg,IDC_IsBook) == BST_CHECKED){
        cps->isBook = 1;
    }
    else{
        cps->isBook = 0;
    }
    //�Ƿ��воֿ�
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
    intGet = GetDlgItemInt(hDlg,IDC_HashSize,&isGet,false);  //&cps->hashSize,    
    if(!isGet){
       MessageBox(hDlg,"��������ȷ��HASH���С!","�ţңңϣҡ�����",MB_OK);
       return false;
    }
    cps->UCCI_hashsize = intGet;
    if(cps->UCCI_hashsize < 16 || cps->UCCI_hashsize > 256){
        cps->UCCI_hashsize = 16;
    }
    //ÿ��ʱ��
    intGet = GetDlgItemInt(hDlg,IDC_TimePerStep,&isGet,false); //&cps->timePerStep,
    if(!isGet){
       MessageBox(hDlg,"��������ȷ��ÿ������ʱ��!","�ţңңϣҡ�����",MB_OK);
       return false;
    }
    cps->timePerStep = intGet;
    //��������
    intGet = GetDlgItemInt(hDlg,IDC_SearchDepth,&isGet,false);

    if(!isGet){
        MessageBox(hDlg,"��������ȷ��ÿ����������!","�ţңңϣҡ�����",MB_OK);
        return false;
    }
    cps->searchDepth = intGet;

    if(cps->searchDepth < 0 || cps->searchDepth > 60){
        cps->searchDepth = 0;
    }
    //��ʱ�趨
    if(IsDlgButtonChecked(hDlg,IDC_IsBaoGan) == BST_CHECKED){
        cps->isBaoGan = 1;
    }
    else{
        cps->isBaoGan = 0;
    }
    
    //���ٷ��ӣ���
    intGet = GetDlgItemInt(hDlg,IDC_BanGanTime,&isGet,false);
    if(!isGet){
        MessageBox(hDlg,"��������ȷ�İ���ʱ��!","�ţңңϣҡ�����",MB_OK);
        return false;
    }
    cps->BaoGanTime = intGet;    
    if(cps->BaoGanTime == 0){
        cps->BaoGanTime = 1;
    }

    //ÿ��һ���Ӷ�����
    intGet = GetDlgItemInt(hDlg,IDC_TimeAddPerStep,&isGet,false);
    if(!isGet){
        MessageBox(hDlg,"��������ȷ��ÿ����ʱ!","�ţңңϣҡ�����",MB_OK);
        return false;
    }
    cps->addTimePerStep = intGet;

    //���ǳ�ʱ�и�
    if(IsDlgButtonChecked(hDlg,IDC_IsLostTimeUp) == BST_CHECKED){
        cps->islostTimeUp = 1;
    }
    else{
        cps->islostTimeUp = 0;
    }
    //��һʱ��β���
    intGet = GetDlgItemInt(hDlg,IDC_firstClassStep,&isGet,false);
    if(!isGet){
        MessageBox(hDlg,"��������ȷ�ĵ�һʱ���Ҫ�ߵĲ���!","�ţңңϣҡ�����",MB_OK);
        return false;
    }
    cps->firstClassTimeStep = intGet;
    if(cps->firstClassTimeStep == 0){
        cps->firstClassTimeStep = 30;
    }
    //��һʱ���ʱ��
    intGet = GetDlgItemInt(hDlg,IDC_firstClassTime,&isGet,false);
    if(!isGet){
        MessageBox(hDlg,"��������ȷ�ĵ�һʱ���ʱ��!","�ţңңϣҡ�����",MB_OK);
        return false;
    }
    cps->firstClassTime = intGet;
    if(cps->firstClassTime == 0){
        cps->firstClassTime = 1;
    }
    //�ڶ�ʱ��β���
    intGet = GetDlgItemInt(hDlg,IDC_secondClassStep,&isGet,false);
    if(!isGet){
        MessageBox(hDlg,"��������ȷ�ĵڶ�ʱ���Ҫ�ߵĲ���!","�ţңңϣҡ�����",MB_OK);
        return false;
    }
    cps->secondClassTimeStep = intGet;
    if(cps->secondClassTimeStep == 0){
        cps->secondClassTimeStep = 10;
    }
    intGet = GetDlgItemInt(hDlg,IDC_secondClassTime,&isGet,false);
    if(!isGet){
        MessageBox(hDlg,"��������ȷ�ĵڶ�ʱ���ʱ��!","�ţңңϣҡ�����",MB_OK);
        return false;
    }
    cps->secondClassTime = intGet;
    if(cps->secondClassTime == 0){
        cps->secondClassTime = 1;
    }
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
            "UPDATE yq SET yqName='%s',yqFile='%s',yqAuthor='%s',yqVerson='%s',yqDualTime=%d, \
            path='%s',xieyiID=%d,elo=%d,initString='%s',OtherString='%s',smpNum=%d,hashSize=%d,moveTime=%d,\
            depth=%d,isBaoGan=%d,BaoGanTime=%d,stepInc=%d,TimeUpLose=%d,FT_Step=%d,FT_Time=%d,SC_Step=%d,\
            SC_Time=%d,haveBook=%d,haveEGB=%d,yqOther='%s' WHERE yqID = %d",
            cps->UCCI_name,
            cps->UCCI_file,
            cps->UCCI_author,
            cps->UCCI_verson,
            cps->UCCI_dualtime,
            cps->UCCI_path,
            cps->ucci,
            cps->UCCI_elo,
            cps->UCCI_iniString,
            cps->UCCI_otherString,
            cps->UCCI_smpNum,
            cps->UCCI_hashsize,
            cps->timePerStep,
            cps->searchDepth,
            cps->isBaoGan,
            cps->BaoGanTime,
            cps->addTimePerStep,
            cps->islostTimeUp,
            cps->firstClassTimeStep,
            cps->firstClassTime,
            cps->secondClassTimeStep,
            cps->secondClassTime,
            cps->isBook,
            cps->isEGB,
            cps->UCCI_addInfo,
            cps->yqID
            );

        

        rc = sqlite3_exec(db_ini,sql,0,0,&szErrMsg);
        if(rc != 0){
            LogOut(szErrMsg);
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
            LogOut(szErrMsg);
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
                            VALUES('%s','%s','%s','%s','%d','%s','%d','%d','%s','%s',\
                                   '%d','%d','%d','%d','%d','%d','%d','%d','%d','%d',\
                                   '%d','%d','%d','%d','%s')",
            cps->UCCI_name,
            cps->UCCI_file,
            cps->UCCI_author,
            cps->UCCI_verson,
            cps->UCCI_dualtime,
            cps->UCCI_path,
            cps->ucci,
            cps->UCCI_elo,
            cps->UCCI_iniString,
            cps->UCCI_otherString,
            cps->UCCI_smpNum,
            cps->UCCI_hashsize,
            cps->timePerStep,
            cps->searchDepth,
            cps->isBaoGan,
            cps->BaoGanTime,
            cps->addTimePerStep,
            cps->islostTimeUp,
            cps->firstClassTimeStep,
            cps->firstClassTime,
            cps->secondClassTimeStep,
            cps->secondClassTime,
            cps->isBook,
            cps->isEGB,
            cps->UCCI_addInfo
            );

        rc = sqlite3_exec(db_ini,sql,0,0,&szErrMsg);

        if(rc != 0){
            LogOut(szErrMsg);
            sqlite3_free(szErrMsg);
        }

		// sprintf_s(sql,1024,"SELECT * FROM ucci");
		// SELECT relname, relpages FROM pg_class ORDER BY relpages DESC

		sprintf_s(sql,sizeof(sql),
			"SELECT yqID FROM yq ORDER BY yqID DESC");                        

		rc = sqlite3_get_table(db_ini,sql,&azResult,&nrow,&ncolumn,&szErrMsg);

		if(rc != 0){
            LogOut(szErrMsg);
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

    EnableWindow(GetDlgItem(hDlg,IDC_BanGanTime),		 cps->isBaoGan);
    EnableWindow(GetDlgItem(hDlg,IDC_firstClassStep),	!cps->isBaoGan);
    EnableWindow(GetDlgItem(hDlg,IDC_firstClassTime),	!cps->isBaoGan);
    EnableWindow(GetDlgItem(hDlg,IDC_secondClassStep),	!cps->isBaoGan);
    EnableWindow(GetDlgItem(hDlg,IDC_secondClassTime),	!cps->isBaoGan);	
    EnableWindow(GetDlgItem(hDlg,IDC_TimeAddPerStep),	!cps->isBaoGan);
    EnableWindow(GetDlgItem(hDlg,IDC_IsLostTimeUp),		!cps->isBaoGan);

    SendDlgItemMessage(hDlg,IDC_IsBaoGan,BM_SETCHECK,		cps->isBaoGan,0);
    SendDlgItemMessage(hDlg,IDC_IsFenDuanTime,BM_SETCHECK, !cps->isBaoGan,0);

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
    char buf[MSG_SIZ];
    SendDlgItemMessage(hDlg,IDC_YQ_LIST,CB_GETLBTEXT,sel,(LPARAM)buf);                        
    int id  = atoi(buf);
    return id;
}

LRESULT CALLBACK
YqSetCallBack(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam){

    //char str[512];

    OPENFILENAME  ofn;
    char buf[MSG_SIZ];
    char initDir[MAX_PATH];
    char title[MSG_SIZ];

    switch(message){
        case WM_INITDIALOG:{
            CenterWindow(hDlg,GetWindow(hDlg,GW_OWNER));	

			SendDlgItemMessage(hDlg,IDC_RADIO_YQA,BM_SETCHECK,1,0);
			SendDlgItemMessage(hDlg,IDC_RADIO_YQB,BM_SETCHECK,0,0);

            int  table = (int)lParam;

			SetDlgItemInt(hDlg,IDC_Table,table,FALSE);			//�����ű��浽�Ի�����

            dispboard_t *pDis = OBS[table];

            pDis->set_cps = pDis->first;							//��ʾ��һ������

			//���������
            //GetYqinfoFromSqliteByID(pDis->cur_set_cps,pDis->cur_set_cps->yqID);	//�����ݿ���ȡ��������Ϣ

            YqInfoToSetDialog(&pDis->set_cps,hDlg);								//��������Ϣ��ʾ���Ի�����

            SetTimeControlItemlEnables(hDlg,pDis);								//��ʾ��Ӧ���趨ʱ��			

            return TRUE;
						   }
		case WM_USER_YqLoad_OK:	{		//������سɹ���

			int table;
			BOOL isGet;
			int  intGet;

			intGet = GetDlgItemInt(hDlg,IDC_Table,&isGet,false);

			if(isGet){
				table = intGet;
			}
			else{
				table = 0;
			}
            dispboard_t *pDis = OBS[table];		//cps = pDis->cur_set_cps;

			//��������
			pDis->set_cps.isInLoading  = FALSE;
			
			memcpy(pDis->set_cps.loadWhich, &pDis->set_cps, sizeof(ChessProgramState));

			YqInfoToSetDialog(&pDis->set_cps,hDlg);
			SetTimeControlItemlEnables(hDlg,pDis);

								}
			break;
        //--------------------------------------------------------------                 
        case WM_COMMAND:{	//�а�ť��Ϣ   

			

			int table;
			BOOL isGet;
			int  intGet;

			intGet = GetDlgItemInt(hDlg,IDC_Table,&isGet,false);

			if(isGet){
				table = intGet;
			}
			else{
				table = 0;
			}
            dispboard_t *pDis = OBS[table];		//cps = pDis->cur_set_cps;

			if(TRUE == pDis->set_cps.isInLoading){		//��ǰ���ڼ�������
				SendToPlayerByColor("\n��ǰ���ڼ�������֮��\n",ColorShout,FALSE);
				break;
			}

            
            switch(LOWORD(wParam)){
		//		                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
        case IDC_YQ_ADD:{                   //������水ť
                    ZeroMemory(&ofn,sizeof(ofn));
                    ofn.lStructSize         = sizeof(OPENFILENAME);
                    ofn.lpstrFilter         = "��������\0*.exe\0";
                    ofn.nMaxCustFilter      = MSG_SIZ;
                    ofn.nFilterIndex        = 1;
                    ofn.hInstance           = hInst;
                    ofn.nMaxFile            = MAX_PATH;
                    ofn.hwndOwner           = hDlg;
                    buf[0]                  = 0;
                    ofn.lpstrFile           = buf;
                    StringCbPrintf(title,sizeof(title),
                        "��ѡ��һ���������� (����Ӧ����������Ŀ¼�µ�pluginsĿ¼��!)");
                    ofn.lpstrTitle          = title;
                    StringCbPrintf(initDir,sizeof(initDir),
                        "%s%s",installDir,"plugins\\");
                    ofn.lpstrInitialDir		= initDir;			//��ʼ��Ŀ¼
                    ofn.Flags               = OFN_EXPLORER+OFN_FILEMUSTEXIST+OFN_PATHMUSTEXIST+OFN_HIDEREADONLY;
                    if(GetOpenFileName(&ofn)){
                       //���ж�һ�£��ǲ�����installDir����
                        _strlwr_s(initDir,sizeof(initDir));
                        _strlwr_s(buf,sizeof(buf));
                        if(strstr(buf,initDir) == NULL){
                            StringCbPrintf(buf,MSG_SIZ,"�뽫��������ŵ� %sĿ¼�£�",initDir);
                            MessageBox(hDlg,buf,"ERROR...",MB_OK);
                            return TRUE;
                        }

                        //�õ���һ�������ļ�
                        
                        //1,�õ����������
                        ChessProgramState tmp[1];

						memcpy(tmp,&pDis->set_cps,sizeof(ChessProgramState));
                        
                        StringCbPrintf(tmp->UCCI_file,sizeof(tmp->UCCI_file),buf+ofn.nFileOffset);
                        StringCbPrintf(tmp->UCCI_name,sizeof(tmp->UCCI_file),buf+ofn.nFileOffset);

                        //2,�õ������Ŀ¼
                        char *p1 = strstr(buf,"plugins\\");
                        char *p2 = strstr(buf,tmp->UCCI_file);

                        StringCbPrintf(tmp->UCCI_path,p2-p1+1,p1);
                        
                        LogOut("�������棺<<");
                        LogOut(tmp->UCCI_name);

						int id = pDis->set_cps.yqID;
                        
                        if(InsertCpsInfoToSqlite(tmp, &id) == 0){       //����Ϣ���浽���ݿ���                            
                            //LogOut(">>�ѳɹ�����! �������Ӧ������\n");
							SendToPlayerByColor(">>�ѳɹ�����! �������Ӧ������\n",ColorShout,FALSE);

							//�õ���ǰ��ID��Ϣ
							GetYqinfoFromSqliteByID(tmp, id);

                            FillYqListToSetDialog(tmp,hDlg);	 //���ǽ�ԭ��ʹ�õ���ʾһ��

							pDis->set_cps.yqID = id;			 //���µ�ǰ��ID
                        }
                        else{
                             //LogOut(">>����ʧ��!\n");
							SendToPlayerByColor(">>����ʧ��!\n",ColorShout,FALSE);
                        }
                    }  
                        }
                    break;
				//
                case IDC_IsBaoGan:{                  //���ɼ�ʱ��ť
                    pDis->set_cps.isBaoGan   = TRUE;
                    SetTimeControlItemlEnables(hDlg,pDis);
                                  }
                    break;    
				//
                case IDC_IsFenDuanTime:  {           //�ֶμ�ʱ��ť
                    pDis->set_cps.isBaoGan   = FALSE;
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
				case IDC_RADIO_YQB:  {               //����(2)��ť
					if(IsDlgButtonChecked(hDlg,IDC_RADIO_YQB) == BST_CHECKED){

						SendDlgItemMessage(hDlg,IDC_RADIO_YQA,BM_SETCHECK,0,0);

						pDis->set_cps = pDis->second;

						GetYqinfoFromSqliteByID(&pDis->set_cps,pDis->set_cps.yqID);

						YqInfoToSetDialog(&pDis->set_cps,hDlg);

						SetTimeControlItemlEnables(hDlg,pDis);
					}           
									 }
									 break;
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
						if(MessageBox(hDlg,"��ȷ��,��������ɾ����������!","ע����!",MB_OKCANCEL) == IDOK){
							int id  = GetSelectYqID(hDlg);

							if(DeleteCpsByYqID(id) == SQLITE_OK){
								SendToPlayerByColor("\n���ѳɹ�ɾ����һ������\n",ColorShout,FALSE);
								
								//����ǰ�������趨Ϊʹ�õ�����
								if(IsDlgButtonChecked(hDlg,IDC_RADIO_YQA) == BST_CHECKED){	//�������������
									pDis->set_cps = pDis->first;
								}
								else{
									pDis->set_cps = pDis->second;
								}
								YqInfoToSetDialog(&pDis->set_cps,hDlg);
								SetTimeControlItemlEnables(hDlg,pDis);
							}
							else{
								SendToPlayerByColor("\n���޷�ɾ���������\n",ColorShout,FALSE);
							}
						}
                    }
                    break;
				//
				case ID_LOAD_SET_YQ: {            //����һ������
					BOOL can = TRUE;
					ChessProgramState *precps = NULL;
					if(IsDlgButtonChecked(hDlg,IDC_RADIO_YQA) == BST_CHECKED){
						if(pDis->set_cps.yqID == pDis->first.yqID){		//
							can = FALSE;							
						}
						precps = &pDis->first;
					}
					else{
						if(pDis->set_cps.yqID == pDis->second.yqID){		//
							can = FALSE;							
						}
						precps = &pDis->second;
					}
					if(can == FALSE){
						MessageBox(hDlg,"���Ѽ����˵�ǰ�����棬��Ҫ�ټ�����","Error",MB_OK);
						EnableWindow(GetDlgItem(hDlg,ID_LOAD_SET_YQ),FALSE);
						break;
					}

					LogOut("\n���ڼ������棬���Ժ�һ��....\n");

					LoadChessProgramState(precps, &pDis->set_cps, hDlg);					

					//�ȵ�ж��ԭ�ȵ�����
					//UnLoadChessProgramState(precps, hDlg);

					//while(precps->hwndHide != NULL){
					//	Sleep(500);
					//}
					//Sleep(500);

					//LoadChessProgramState(&ppDis->set_cps,hDlg);		//�������̼߳��أ�

					//while(&ppDis->set_cps.hwndHide != NULL){
					//	Sleep(500);
					//}

					//Sleep(2000);

					//����Ĳ����ã���Ϊ���ܻ�û���سɹ�
		
					//if(TRUE == ppDis->set_cps.UCCI_initDone){			//�Ѽ��سɹ���
					//	if(IsDlgButtonChecked(hDlg,IDC_RADIO_YQA) == BST_CHECKED){
					//		ppDis->first = ppDis->set_cps;
					//	}
					//	else{
					//		ppDis->second = ppDis->second;
					//	}

					//	YqInfoToSetDialog(&ppDis->set_cps,hDlg);

					//	SetTimeControlItemlEnables(hDlg,pDis);
					//}
					//else{
					//	SendToPlayerByColor(">>���ܼ��ص�ǰ������!\n",ColorShout,FALSE);
					//}
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
								pDis->first = pDis->set_cps;
							}
							if(pDis->set_cps.yqID == pDis->second.yqID){
								pDis->second = pDis->set_cps;
							}

							//SendToPlayerByColor("\n���µ�ǰ�������óɹ���\n",ColorShout,FALSE);
							LogOut("\n���µ�ǰ�������óɹ���\n");
						}
						else{
							SendToPlayerByColor("\n���޷����µ�ǰ���������\n",ColorShout,FALSE);
						}                      
                    }
                    break;
                case IDOK:                          //ȷ�ϰ�ť
                    //1, ���ǲ��Ǹ���������,����Ǹ����ˣ���Ҫֹͣ��ǰ�ģ����Լ������ڵģ�
                    {
                        //int id = GetSelectYqID(hDlg);
                        // ChessProgramState tmp[1];
                        // SetDialogToCps(tmp,hDlg);
                        // if(!UpdateCpsInfoToSqlite(tmp)){
                        //     //MessageBox(hDlg,"���µ�ǰ�������óɹ���","�밴�ϣ˷���",MB_OK);
                        //     LogOut("���µ�ǰ�������óɹ���\n");
                        //     if(id == pDis->first.yqID){
                        //         SetDialogToCps(&pDis->first,hDlg);
                        //     }
                        //     else if(id == pDis->second.yqID){
                        //         SetDialogToCps(&pDis->second,hDlg);
                        //     }
                        // }
                        // else{
                        //     //MessageBox(hDlg,"���µ�ǰ��������ʧ�ܣ�","�밴�ϣ˷���",MB_OK);
                        //     LogOut("���µ�ǰ��������ʧ�ܣ�\n");
                        // } 

                        // if(pDis->first.yqID != pDis->pre_first_id){
                        //     GetYqinfoFromSqliteByID(&pDis->first,pDis->first.yqID);
                        //     LoadChessProgramState(&pDis->first, hDlg);
                        // }
                        // if(pDis->second.yqID != pDis->pre_second_id){
                        //     GetYqinfoFromSqliteByID(&pDis->second,pDis->second.yqID);
                        //     LoadChessProgramState(&pDis->second, hDlg);
                        // }
                    }
                    //
                    EndDialog(hDlg, TRUE);
                    return TRUE;
                    break;
                case IDCANCEL:
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
