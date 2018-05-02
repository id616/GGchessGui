#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"

//void        //��ÿһ���Թ۵���ַ���ͬ������Ϣ
//SendEveryObsBoard(UINT message,WPARAM wParam,LPARAM lParam){
//    //extern dispboard_t  *OBS[MAX_OBS_BOARD];
//    for(int i = 1; i < MAX_OBS_BOARD; i++){
//        dispboard_t *pDis = OBS[i];
//        if(pDis != NULL){
//            //SendDlgItemMessage(pDis->hwndThis,
//            SendMessage(pDis->hwndThis,message,wParam,lParam);
//        }
//    }
//}

void 
GetObsBoardPosition(int table){
    dispboard_t *pDis  = OBS[table];
    //dispboard_t *m    = pDis; 
    //pDis->boardRect     = m->boardRect;

    ClearPremoveHighlights(pDis);
    ClearHighlights(pDis);

    //�����������ϣ������λ��
    int Xoff  =  OUTER_MARGIN/2;
    int Yoff  = -27;
    pDis->boardRect.top      += Yoff;
    pDis->boardRect.bottom   += Yoff;
    pDis->boardRect.left     += Xoff;
    pDis->boardRect.right    += Xoff;
}

void copyDisFromMainBoard(int table){
    ASSERT(table != 0); 
    dispboard_t *pDis  = OBS[table];
    //dispboard_t *m    = pDis;
    HWND hDlg         = pDis->hwndThis;
    //pDis->iconCurrent  = m->iconCurrent;
    //pDis->lastReqValid  = true;
    ResetFrontEnd(pDis);
    InitPosition(pDis,TRUE);

    //DisplayBothClocks
}

//        case WM_SIZE:
//            //FitStepListDlgItem(hDlg);
//            if(IsIconic(hDlg)){
//                break;
//            }
//            newSizeX = LOWORD(lParam);
//            newSizeY = HIWORD(lParam);
//            if(sizeX != newSizeX || sizeY != newSizeY){                
//                int x = 0;
//                int y = -2;
//                int w = newSizeX - 0;
//                int h = newSizeY + 1;
//
//                SetWindowPos(pDis->steplistK,NULL,x,y,w,h,SWP_NOZORDER|SWP_NOACTIVATE);
//
//                x +=  1;
//                y +=  8;
//                w -=  4;
//                h -=  10;
//
//                SetWindowPos(pDis->steplist,NULL,x,y,w,h,SWP_NOZORDER|SWP_NOACTIVATE);
//            }
//            sizeX = newSizeX;
//            sizeY = newSizeY;
//            break;
void 
FitObsItem(int table){
/*
#define OBS_LEFT_WIDTH  262
#define OBS_BOT_HIGH    50
     
    int zx,zy,zw,zh;               //��Ͽ�Ĵ�Сλ��
    RECT rect;
    GetObsBoardPosition(table);    //�õ������ڵ����̴�С  
    dispboard_t *DIS = OBS[table];
    HWND hDlg        = pDis->hwndThis;
    //zx = pDis->boardRect.right + OUTER_MARGIN;
    zx = pDis->boardRect.left  - 2;
    zy = pDis->boardRect.top   - 8;
    //zw = OBS_LEFT_WIDTH;
    zw = (pDis->boardRect.right - pDis->boardRect.left) + OBS_LEFT_WIDTH;
    zh = pDis->boardRect.bottom - pDis->boardRect.top + 10 ;    

    HWND hwnd = GetDlgItem(hDlg,IDC_OBS_GROUP_LEFT);
    SetWindowPos(hwnd,NULL,zx,zy,zw,zh,SWP_NOZORDER|SWP_NOACTIVATE);

    //���ú췽ͼ��,�ڷ�ͼ��,�岽
    //IDC_redTimeIcon***************************************************************
    hwnd = GetDlgItem(hDlg,IDC_redTimeIcon);
    zx = pDis->boardRect.right + 2;
    zy = pDis->boardRect.top   + 10;
    SetWindowPos(hwnd,NULL,zx,zy,24,24,SWP_NOZORDER|SWP_NOACTIVATE);
    //IDC_OBS_RTOTAL        //���ʱ***************************************************************
    hwnd = GetDlgItem(hDlg,IDC_OBS_RTOTAL);
    zx = pDis->boardRect.right + 30;
    zy = pDis->boardRect.top   + 10;
    SetWindowPos(hwnd,NULL,zx,zy,48,14,SWP_NOZORDER|SWP_NOACTIVATE);
    //IDC_OBS_RSTEP         //�첽ʱ***************************************************************
    hwnd = GetDlgItem(hDlg,IDC_OBS_RSTEP);
    //zx = pDis->boardRect.right + 30;
    zy = pDis->boardRect.top   + 24;
    SetWindowPos(hwnd,NULL,zx,zy,48,14,SWP_NOZORDER|SWP_NOACTIVATE); 
    //IDC_blueTimeIcon***************************************************************
    hwnd = GetDlgItem(hDlg,IDC_blueTimeIcon);
    zx = pDis->boardRect.right + 84;
    zy = pDis->boardRect.top   + 10;
    SetWindowPos(hwnd,NULL,zx,zy,24,24,SWP_NOZORDER|SWP_NOACTIVATE);
    //IDC_OBS_BTOTAL        //�ھ�ʱ***************************************************************
    hwnd = GetDlgItem(hDlg,IDC_OBS_BTOTAL);
    zx = pDis->boardRect.right + 112;
    zy = pDis->boardRect.top   + 10;
    SetWindowPos(hwnd,NULL,zx,zy,48,14,SWP_NOZORDER|SWP_NOACTIVATE);
    //IDC_OBS_BSTEP         //�ڲ�ʱ***************************************************************
    hwnd = GetDlgItem(hDlg,IDC_OBS_BSTEP);
    //zx = pDis->boardRect.right + 112;
    zy = pDis->boardRect.top   + 24;
    SetWindowPos(hwnd,NULL,zx,zy,56,14,SWP_NOZORDER|SWP_NOACTIVATE); 
    //IDC_OBS_STEPLIST*************************************�岽�б�
    hwnd = GetDlgItem(hDlg,IDC_OBS_STEPLIST);
    zx = pDis->boardRect.right + 165;
    zy = pDis->boardRect.top   + 2;
    SetWindowPos(hwnd,NULL,zx,zy,90,40,SWP_NOZORDER|SWP_NOACTIVATE); 
    // IDC_OBS_RED_INFO �췽�������ȼ���
    hwnd = GetDlgItem(hDlg,IDC_OBS_RED_INFO);
    zx = pDis->boardRect.right + 4;
    zy = pDis->boardRect.top   + 46;
    SetWindowPos(hwnd,NULL,zx,zy,80,14,SWP_NOZORDER|SWP_NOACTIVATE); 
    // IDC_OBS_RED_INFO �췽�������ȼ���
    hwnd = GetDlgItem(hDlg,IDC_OBS_BLUE_INFO);
    zx = pDis->boardRect.right + 84;
    //zy = pDis->boardRect.top   + 46;
    SetWindowPos(hwnd,NULL,zx,zy,80,14,SWP_NOZORDER|SWP_NOACTIVATE);
    // IDC_OBS_SCORE
    hwnd = GetDlgItem(hDlg,IDC_OBS_SCORE);
    zx = pDis->boardRect.right + 175;
    //zy = pDis->boardRect.top   + 46;
    SetWindowPos(hwnd,NULL,zx,zy,80,14,SWP_NOZORDER|SWP_NOACTIVATE);
    //IDC_OBS_YQINFO  ������Ϣ
    hwnd = GetDlgItem(hDlg,IDC_OBS_YQINFO);
    zx   = pDis->boardRect.right +  4;
    zy   = pDis->boardRect.top   + 62;
    zw   = OBS_LEFT_WIDTH - 10;
    zh   = (pDis->boardRect.bottom - pDis->boardRect.top - 80 - 16)/3;
    SetWindowPos(hwnd,NULL,zx,zy,zw,zh,SWP_NOZORDER|SWP_NOACTIVATE);

    //IDC_OBS_ICS_INFO ��վ��Ϣ
    hwnd = GetDlgItem(hDlg,IDC_OBS_ICS_INFO);
    //zx   = pDis->boardRect.right +  4;
    zy  += zh + 2; 
    //zw   = OBS_LEFT_WIDTH - 10;
    zh  -= 8;
    SetWindowPos(hwnd,NULL,zx,zy,zw,zh,SWP_NOZORDER|SWP_NOACTIVATE);

    //IDC_OBS_USER_LIST
    hwnd = GetDlgItem(hDlg,IDC_OBS_USER_LIST);
    //zx   = pDis->boardRect.right +  4;
    zy  += zh + 2; 
    //zw   = OBS_LEFT_WIDTH - 10;
    //zh  -= 0; 
    zh   = (pDis->boardRect.bottom - zy - 24);
    SetWindowPos(hwnd,NULL,zx,zy,zw,zh,SWP_NOZORDER|SWP_NOACTIVATE);

    //IDC_OBS_USER_INPUT 
    hwnd = GetDlgItem(hDlg,IDC_OBS_USER_INPUT);
    //zx   = pDis->boardRect.right +  4;
    zy  += zh + 2; 
    //zw   = OBS_LEFT_WIDTH - 10;
    zw  -= 30;
    //zh  -= 0; 
    zh   = (20);
    SetWindowPos(hwnd,NULL,zx,zy,zw,zh,SWP_NOZORDER|SWP_NOACTIVATE);

    //IDC_OBS_BUT_SEND
    hwnd = GetDlgItem(hDlg,IDC_OBS_BUT_SEND);
    zx    = zx + zw + 2;
    zw  = 28;
    SetWindowPos(hwnd,NULL,zx,zy,zw,zh,SWP_NOZORDER|SWP_NOACTIVATE);

    //�������Ű�ťλ��
    int bw   = ((pDis->boardRect.right - pDis->boardRect.left) + OBS_LEFT_WIDTH) / 10 - 1;
    int bh   = OBS_BOT_HIGH / 2 - 4;
    int by   = pDis->boardRect.bottom + 4;
    //OBS_BUT[2][10];
    for(int i = 0; i < 2; i++){
        int bx  = pDis->boardRect.left  - 2;
        for(int j = 0; j < 10; j++){
            hwnd = GetDlgItem(hDlg,OBS_BUT[i][j]);
            SetWindowPos(hwnd,NULL,bx,by,bw,bh,SWP_NOZORDER|SWP_NOACTIVATE); 
            bx += bw + 1;
        }
        by += bh + 1;        
    }

    //���������ڵĴ�С
    GetWindowRect(hDlg,&rect);
    zx = rect.left;
    zy = rect.top;
    zw = (pDis->boardRect.right - pDis->boardRect.left) + OBS_LEFT_WIDTH + OUTER_MARGIN * 2 + 4;
    zh = pDis->boardRect.bottom - pDis->boardRect.top + OUTER_MARGIN * 2  + OBS_BOT_HIGH + 25;
    SetWindowPos(hDlg,NULL,zx,zy,zw,zh,SWP_NOZORDER|SWP_NOACTIVATE);
    

    DrawPosition(DIS,false,pDis->B256dis[pDis->pos->curStep]); */
    //
    //GetWindowRect(hDlg,&rect);
    //InvalidateRect(hDlg, &rect, TRUE);

    //PaintProc(DIS);

    //PostMessage(hDlg,WM_PAINT,0,0);

    //SendMessage(hDlg,WM_PAINT,1,0);

    //SendMessage(hDlg,WM_ERASEBKGND,0,0);
    return;
}

LRESULT CALLBACK
ObsBoardDialogCallBack(HWND hDlg,UINT message,WPARAM wParam,LPARAM lParam){
    //char passbuf[128];
    //char *pcommand;
    //bool is183;
    TCHAR str[512];
    int  table;

    MINMAXINFO* mmi;
    switch(message){
        case WM_INITDIALOG:
            {
            /*PostMessage(hDlg, WM_SETICON, (WPARAM) TRUE, (LPARAM) MAIN.iconWhite); */
            SendMessage(hDlg, WM_SETICON, (WPARAM) TRUE, (LPARAM) appData.iconWhite); 
            table = (int)lParam;
			swprintf_s(str, sizeof(str) / sizeof(TCHAR), _T("%d����"), table);
            SetWindowText(hDlg,str);
            OBS[table]->hwndThis = hDlg;
            
            copyDisFromMainBoard(table);    //

            FitObsItem(table);                   //���������ؼ��Ĵ�С

            //������վ��Ϣ��ˮƽ��
            SendDlgItemMessage(hDlg,IDC_OBS_YQINFO,  LB_SETHORIZONTALEXTENT,600,0);
            SendDlgItemMessage(hDlg,IDC_OBS_ICS_INFO,LB_SETHORIZONTALEXTENT,600,0);

            }
            return FALSE;  
        case WM_PAINT:
            GetWindowText(hDlg,str,512);
            table = _wtoi(str);
            PaintProc(OBS[table]);
            //return DefWindowProc(hDlg, message, wParam, lParam);
            //SendDlgItemMessage(hDlg,IDC_OBS_BTOTAL,WM_SETTEXT,0,(LPARAM)"ldll");
            break;
        case WM_COMMAND:  
            //switch(LOWORD(wParam)){
            //        case IDC_DIR_1:
            //            pcommand = "go 1";
            //            break;
            //        case IDC_DIR_2:
            //            pcommand = "go 2";
            //            break;
            //        case IDC_DIR_3:
            //            pcommand = "go 3";
            //            break;
            //        case IDC_DIR_4:
            //            pcommand = "go 4";
            //            break;
            //        case IDC_DIR_5:
            //            pcommand = "go 5";
            //            break;
            //        case IDC_DIR_6:
            //            pcommand = "go 6";
            //            break;
            //        case IDC_DIR_7:
            //            pcommand = "go 7";
            //            break;
            //        case IDC_DIR_8:
            //            pcommand = "go 8";
            //            break;
            //        default:
            //            return FALSE;
            //            break;
            //    }
            //    if(DIS.third.ICS_net_id == ICS_MXQ_EN183 ||
            //        DIS.third.ICS_net_id == ICS_MXQ_CN183){
            //            CMX_183_SEND_CODDING(pcommand);
            //            Sleep(100);
            //            CMX_183_SEND_CODDING("map");
            //    }
            //    else{
            //        char buf[256];
            //        sprintf_s(buf,sizeof(buf),"%s\n",pcommand);
            //        SendToICS(buf);
            //        SendToICS("map\n");
            //    }

            break;
        case WM_USER_ICS_INFO:      //����վ��������Ϣ
            {
            GetWindowText(hDlg,str,512);
            table = _wtoi(str);
            TCHAR *info = (TCHAR*)lParam; //LB_ADDSTRING,NULL,(LPARAM)&pDis->moveListName[i]);
            SendDlgItemMessage(hDlg,IDC_OBS_ICS_INFO,LB_ADDSTRING,NULL,lParam);
            }
            break;
        case WM_USER_MainBoard_Sized:
            GetWindowText(hDlg,str,512);
            table = _wtoi(str);
            FitObsItem(table);                   //���������ؼ��Ĵ�С
            break;
        //case WM_SIZE:
        //    //FitTimeDisplayDlgItem(hDlg);
        //    //FitObsItem(hDlg);
        //    GetWindowText(hDlg,str,512);
        //    table = atoi(str);
        //    FitObsItem(table);                   //���������ؼ��Ĵ�С
        //    break;
        case WM_CLOSE:
            //TimeDisplayListEvent();

            //����ӽ�//IDC_GO_PLACE

            //SendDlgItemMessage(HWND_CONSOLE,IDC_GO_PLACE,BM_SETCHECK,0,0);
            //ShowWindow(hDlg,SW_HIDE);
            // Obs_One_Board_t *pob     = OBS.pob[table];
            {
            //�õ���ǰ��������
            //GetWindowText(hDlg,str,512);
            //int table = atoi(str);
            //ASSERT(table != 0);
            GetWindowText(hDlg,str,512);
            table = _wtoi(str);
            
            delete OBS[table];

            OBS[table] = NULL;

            EndDialog(hDlg, LOWORD(wParam));

            //DLG.hwndGoPlace = NULL;

            return (INT_PTR)TRUE;
            }
            break;
        case WM_LBUTTONDOWN:
        case WM_MBUTTONDOWN:
        case WM_RBUTTONDOWN:
        case WM_LBUTTONUP:
        case WM_MBUTTONUP:
        case WM_RBUTTONUP:
        case WM_MOUSEMOVE:            
            GetWindowText(hDlg,str,512);
            table = _wtoi(str);
            MouseEvent(OBS[table],hDlg, message, wParam, lParam);
            break;
        case WM_GETMINMAXINFO:    //���ⴰ�����Ĺ�С /* Prevent resizing window too small */
            mmi = (MINMAXINFO*) lParam;
            mmi->ptMinTrackSize.x = 112;
            mmi->ptMinTrackSize.y = 130;
            break;
        default:
            break;
    }
    return FALSE;

    //���ڹ��̶�Ӧ�ڲ�ͬ����Ϣ�и��ֲ�ͬ����ķ���ֵ��
    //���Ի�����̷���BOOL���͵�ֵ������TRUE��ʾ�Ѿ�������ĳ����Ϣ��
    //����FALSE��ʾû�д������Ի������������������
    //����ֵ�����Ƿ��������ĳһ����Ϣ��Ωһ��������WM_INITDIALOG��Ϣ����
}

#define USE_MAIN_OBS  1

//��һ���Թ۴��ڣ��ǲ��Ƿ��͵�������
BOOL PopObsBoardDialog(int table){

	ASSERT(table != 0);

	//
	if(USE_MAIN_OBS){		//ʹ���������������е��Թ۴���		
		OBS[table] = OBS[0];

		dispboard_t* pDis    = OBS[table];

		if(pDis->table == 0){
			return TRUE;
		}
		else{
			return FALSE;
		}		
	}



    TCHAR str[512];

    if(table < 0 || table > MAX_OBS_BOARD){
		swprintf_s(str, sizeof(str) / sizeof(TCHAR), _T("����������ȷ!! %d \n"), table);
        LogOut(str);
        return FALSE;
    }

    dispboard_t* pDis    = OBS[table];
    if(pDis != NULL){
        //delete pob;
		swprintf_s(str, sizeof(str) / sizeof(TCHAR), _T("�������Թ�������,�벻Ҫ�ٴδ�!! %d \n"), table);
        LogOut(str);
        return FALSE;
    }
    FARPROC lpProc           = MakeProcInstance((FARPROC)ObsBoardDialogCallBack,hInst);
    //OBS.OB[table].hwndTable  = new 
    //OBS.pob[table] = new Obs_One_Board_t;
    pDis = new dispboard_t[1];
    memset(pDis,0,sizeof(dispboard_t));

	OBS[table] = pDis;
	pDis->table = table;

	pDis->first.pDis  = pDis;
	//pDis->second.pDis = pDis;


    //pob->hwndTable = CreateDialog(hInst,MAKEINTRESOURCE(DLG_OBS_BOARD),hwndMain,(DLGPROC)lpProc);
    pDis->hwndThis  = CreateDialogParam(hInst,MAKEINTRESOURCE(DLG_OBS_BOARD),
        /*pDis->hwndThis,(DLGPROC)lpProc,table);*/
        NULL,(DLGPROC)lpProc,table);
    FreeProcInstance(lpProc);
    ShowWindow(pDis->hwndThis,SW_SHOW);
    CenterWindow(pDis->hwndThis,pDis->hwndThis);

	return TRUE;

    //OBS.pob[table]
    //DLG.hwndGoPlace = CreateDialog(hInst,MAKEINTRESOURCE(IDD_GO_PLACE),hwndMain,(DLGPROC)lpProc);
    //FreeProcInstance(lpProc);
    //ShowWindow(DLG.hwndGoPlace,SW_HIDE);
    //CenterWindow(DLG.hwndGoPlace,hwndMain);
}