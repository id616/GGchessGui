#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"
#ifdef USE_MYSQL_DATABASE
void	//��ʾ��ǰ��ֵ����������Ϣ
DispGGFaceQKinfo(position_t *pos,MYSQL *my){
	//char buf[32];
	////char moveName[32];
	////int  qknum = 0;
	//
	////LVS_EX_GRIDLINES 


	//gen_legal_moves(list,b90,isWhiteGo);		//���������߲�

	////���ԭ�ȵ���ʾ����
	//SendDlgItemMessage(TAB.dlgTab[DDATA],IDC_QK_LIST,LVM_DELETEALLITEMS,0,0);	
	////SendDlgItemMessage(TAB.dlgTab[DDATA],IDC_QK_LIST_OTHER,LVM_DELETEALLITEMS,0,0);
	//
	//LV_ITEM lvi;
	//lvi.pszText  = buf;
	//for(int i=0; i<list->size; i++){
	//	//=========================================���
	//	lvi.mask		= LVIF_TEXT+LVIF_PARAM;
	//	lvi.iItem		= i+1;
	//	lvi.lParam		= list->move[i];        //����MOVE��
	//	lvi.iSubItem	= 0;
	//	StringCbPrintf(buf,sizeof(buf),"%2d",i+1);
	//	//SendDlgItemMessage(TAB.dlgTab[DDATA],IDC_QK_LIST_OTHER,LVM_INSERTITEM,0,(LPARAM)&lvi);
	//	SendDlgItemMessage(TAB.dlgTab[DDATA],IDC_QK_LIST,LVM_INSERTITEM,0,(LPARAM)&lvi);
	//	
	//	//�õ��߲���������
	//	lvi.mask        = LVIF_TEXT;
	//	lvi.iItem    --;
	//	lvi.iSubItem    = 1;
	//	GetMoveName(b90,list->move[i],buf,StepNameTypeA);
	//	//lvi.pszText     = moveName;
	//	//SendDlgItemMessage(TAB.dlgTab[DDATA],IDC_QK_LIST_OTHER,LVM_SETITEM,0,(LPARAM)&lvi);	
	//	SendDlgItemMessage(TAB.dlgTab[DDATA],IDC_QK_LIST,LVM_SETITEM,0,(LPARAM)&lvi);

	//	//lvi.pszText     = buf;
	//	//�ٲ���һ���������û�е÷�
	//	mv_t	move	= list->move[i];
	//	sq_t	from	= MOVE_FROM(move);
	//	sq_t    to		= MOVE_TO(move);
	//	//��һ��
	//	sq_t	tochess = b90[to];
	//	b90[to]			= b90[from];
	//	b90[from]		= NOCHESS;
	//	//�鿴һ�����û�ж�Ӧ�ĵ÷���
	//	//MysqlGetOneFaceScore(Board90 b90, bool isWhiteGo,qkface_t *pf, MYSQL *my)
	//	qkface_t face;
	//	if(MysqlGetOneFaceScore(b90,isWhiteGo^0x01,&face,my)){				
	//		//=========================================���
	//		//lvi.mask		= LVIF_TEXT+LVIF_PARAM;
	//		//lvi.iItem		= qknum+1;
	//		//lvi.lParam		= list->move[i];        //����MOVE��
	//		//lvi.iSubItem	= 0;
	//		//StringCbPrintf(buf,sizeof(buf),"%2d",i+1);
	//		//SendDlgItemMessage(TAB.dlgTab[DDATA],IDC_QK_LIST,LVM_INSERTITEM,0,(LPARAM)&lvi);	
	//		////�õ��߲�����
	//		//lvi.mask        = LVIF_TEXT;
	//		//lvi.iItem    --;
	//		//lvi.iSubItem    = 1;
	//		////GetMoveName(b90,list->move[i],buf,StepNameTypeA);
	//		//lvi.pszText     = moveName;
	//		//SendDlgItemMessage(TAB.dlgTab[DDATA],IDC_QK_LIST,LVM_SETITEM,0,(LPARAM)&lvi);
	//		//lvi.pszText     = buf;			
	//		//�÷�---------------------------------
	//		lvi.iSubItem    = 2;
	//		//itoa(face.qsc,buf,10);
	//		_itoa_s(face.qsc,buf,sizeof(buf),10);
	//		SendDlgItemMessage(TAB.dlgTab[DDATA],IDC_QK_LIST,LVM_SETITEM,0,(LPARAM)&lvi);
	//		//StringCbPrintf(buf,face.qsc
	//		//������Ŀ---------------------------------
	//		lvi.iSubItem    = 3;
	//		//itoa(face.qsc,buf,10);
	//		_itoa_s(face.qnum,buf,sizeof(buf),10);
	//		SendDlgItemMessage(TAB.dlgTab[DDATA],IDC_QK_LIST,LVM_SETITEM,0,(LPARAM)&lvi);

	//		//qknum ++;
	//	}

	//	//��ԭһ��
	//	b90[from]		= b90[to];
	//	b90[to]			= tochess;
	//}
}




#endif

const int Book_Default_Width  = 450;
const int Book_Default_Height = 200;

void FitBookDlgPositionDefault(HWND hDlg){  //�����岽���ڵ�ȱʡλ��
 //   WINDOWPLACEMENT wp;
	//wp.length = sizeof(WINDOWPLACEMENT);
	//GetWindowPlacement(hwndMain,&wp);
 //   
 //   wp.rcNormalPosition.bottom = wp.rcNormalPosition.top + 200;
 //   wp.rcNormalPosition.top    = wp.rcNormalPosition.top;
 //   wp.rcNormalPosition.left   = wp.rcNormalPosition.right;
 //   wp.rcNormalPosition.right  = wp.rcNormalPosition.left  + 200;
 //   SetWindowPlacement(hDlg,&wp);
 //   FitBookDlgItem(hDlg);

	 dispboard_t* pDis = OBS[0];

    RECT Rect;
    GetWindowRect(pDis->hwndThis,&Rect);

    int x       = Rect.left;
    /*int y       = Rect.bottom;*/
    //int width   = Rect.right - Rect.left;
	int width   = Book_Default_Width;
    int height  = Book_Default_Height;

	int y       = Rect.top - Book_Default_Height;

    SetWindowPos(hDlg,NULL,x,y,width,height,SWP_NOZORDER|SWP_NOACTIVATE);

	ShowWindow(hDlg,SW_SHOW);
}

void FitBookItemPosition(HWND hDlg,int newX, int newY){

	       // HWND b = GetDlgItem(DLG.hwndConsole,MXQ_ICS_BUT[i]);
        //SetWindowPos(b,NULL,x,y,w,h,SWP_NOZORDER|SWP_NOACTIVATE);

	//ֻҪ��һ��
	//IDC_QK_LIST_USE
	//IDC_QK_K_USE

	int x1 = 2;
	int y1 = 90;
	int w1 = newX - 2;
	int h1 = (newY - 90);

	HWND hwnd = GetDlgItem(hDlg,IDC_QK_K_LIST);
	SetWindowPos(hwnd,NULL,x1,y1,w1,h1,SWP_NOZORDER|SWP_NOACTIVATE);

	hwnd = GetDlgItem(hDlg,IDC_QK_STEP_LIST);

	int x11 = x1 + 4;
	int y11 = y1 + 15;
	int w11 = w1 - 8;
	int h11 = h1 - 20;
	SetWindowPos(hwnd,NULL,x11,y11,w11,h11,SWP_NOZORDER|SWP_NOACTIVATE);

	////
	//hwnd = GetDlgItem(hDlg,IDC_QK_K_NOT_USE);

	//int x2    = x1;
	//int w2    = w1;
	//int y2    = y1 + h1 + 3;
	//int h2    = newY - (y1 + h1) - 4; 

	//SetWindowPos(hwnd,NULL,x2,y2,w2,h2,SWP_NOZORDER|SWP_NOACTIVATE);

 //   hwnd = GetDlgItem(hDlg,IDC_QK_LIST_NOT_USE);

	//int x21 = x2 + 4;
	//int y21 = y2 + 15;
	//int w21 = w2 - 8;
	//int h21 = h2 - 20;
	//SetWindowPos(hwnd,NULL,x21,y21,w21,h21,SWP_NOZORDER|SWP_NOACTIVATE);
}

void initBookList(HWND hDlg,int lid){

	//char *str[128];

	LV_COLUMN   lvc;
	lvc.mask    = LVCF_FMT+LVCF_TEXT+LVCF_WIDTH;
	lvc.fmt     = LVCFMT_CENTER;
	lvc.cx      = 28;
	lvc.pszText = "No:";
	SendDlgItemMessage(hDlg,lid,LVM_INSERTCOLUMN,0,(LPARAM)&lvc);

	lvc.cx      = 70;
	lvc.pszText = "�岽����";
	SendDlgItemMessage(hDlg,lid,LVM_INSERTCOLUMN,1,(LPARAM)&lvc);

	lvc.cx      = 70;
	lvc.pszText = "����";
	SendDlgItemMessage(hDlg,lid,LVM_INSERTCOLUMN,2,(LPARAM)&lvc);

	lvc.cx      = 40;
	lvc.pszText = "�岽";
	SendDlgItemMessage(hDlg,lid,LVM_INSERTCOLUMN,3,(LPARAM)&lvc);

	lvc.cx      = 40;
	lvc.pszText = "����";
	SendDlgItemMessage(hDlg,lid,LVM_INSERTCOLUMN,4,(LPARAM)&lvc);

	lvc.cx      = 40;
	lvc.pszText = "����";
	SendDlgItemMessage(hDlg,lid,LVM_INSERTCOLUMN,5,(LPARAM)&lvc);

	lvc.cx      = 40;
	lvc.pszText = "hash";
	SendDlgItemMessage(hDlg,lid,LVM_INSERTCOLUMN,6,(LPARAM)&lvc);

	lvc.cx      = 40;
	lvc.pszText = "val";
	SendDlgItemMessage(hDlg,lid,LVM_INSERTCOLUMN,7,(LPARAM)&lvc);

	SendDlgItemMessage(hDlg,lid,
				   LVM_SETEXTENDEDLISTVIEWSTYLE,0,
				   LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT  );
};




//int CALLBACK CompareFunc(LPARAM lParam1, LPARAM lParam2, 
//
//LPARAM lParamSort); 

BOOL CALLBACK StepCompareFucn(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort){

	LV_ITEM lvi;
	char buf1[128];
	char buf2[128];

	lvi.mask		= LVIF_TEXT;
	lvi.pszText		= buf1;
	lvi.cchTextMax	= sizeof(buf1);

	lvi.iSubItem    = (int)lParamSort;

	SendMessage(GetDlgItem(DLG.dlgBook,IDC_QK_STEP_LIST),
		LVM_GETITEMTEXT,
		lParam1,
		(LPARAM)&lvi);


	lvi.pszText = buf2;

	SendMessage(GetDlgItem(DLG.dlgBook,IDC_QK_STEP_LIST),
		LVM_GETITEMTEXT,
		lParam2,
		(LPARAM)&lvi);

	

	int ret;
	
	if(lParamSort == 1 || lParamSort == 2 || lParamSort == 6){
		ret = lstrcmpi(buf1,buf2);
	}
	else{
		int a = atoi(buf1);
		int b = atoi(buf2);

		ret   = a - b;
	}

	
	if(LIST_ORDER_SJ){
		ret *= -1;
	}

	if(ret < 0){
	  return TRUE;
    }
	else{
		return FALSE;
	}

	//return TRUE;
}

void UpdateSteplParam(void){		//���������ĳ�Ա
	HWND hlist = GetDlgItem(DLG.dlgBook,IDC_QK_STEP_LIST);

	LV_ITEM lvi;

	lvi.mask		= LVIF_PARAM;
	lvi.iSubItem	= 0;
	lvi.iItem		= 0;

	int total = (int)SendMessage(hlist,LVM_GETITEMCOUNT,0,0);

	while(total>0){
		lvi.lParam = lvi.iItem;
	
		SendMessage(hlist,LVM_SETITEM,0,(LPARAM)&lvi);

		lvi.iItem ++;
		total --;
	}
}

//�����ֻ��һ��������static

LRESULT CALLBACK
DLG_BOOK_PROC(HWND hDlg,UINT message,WPARAM wParam,LPARAM lParam){
    
	 dispboard_t* pDis = OBS[0];

	MINMAXINFO* mmi;
	static int  sizeX, sizeY;
	static int  curSel;
	static int  ListId;
	static int  move;
    int newSizeX, newSizeY;
    switch(message){
        case WM_INITDIALOG:
            PostMessage(hDlg, WM_SETICON, (WPARAM) TRUE, (LPARAM) appData.iconWhite);

			// SendDlgItemMessage(hDlg,IDC_IsBaoGan,		BM_SETCHECK, cps->timeIsBaoGan, 0);

			//��ʼ���岽�б�ͷ
			initBookList(hDlg,IDC_QK_STEP_LIST);
			//initBookList(hDlg,IDC_QK_LIST_NOT_USE);
		
			//IDC_SLIDER_RATE �趨slider �ķ�Χ
			SendDlgItemMessage(hDlg,IDC_SLIDER_RATE,
				TBM_SETRANGE,
				(WPARAM)TRUE,
				(LPARAM) MAKELONG(0,100));

			SendDlgItemMessage(hDlg,IDC_SLIDER_RATE,
				TBM_SETSEL,								//���õķ�Χ
				(WPARAM)TRUE,
				(LPARAM) MAKELONG(0,100));

			SendDlgItemMessage(hDlg,IDC_SLIDER_RATE,
				TBM_SETPAGESIZE,
				(WPARAM)TRUE,
				(LPARAM) 10);	//10%һ��

			SendDlgItemMessage(hDlg,IDC_SLIDER_RATE,
				TBM_SETPOS,
				(WPARAM)TRUE,
				(LPARAM) 10);
			
            return FALSE;            
        case WM_COMMAND:
			switch(LOWORD(wParam)){
				//case IDC_VERY_GOOD:
				//	EnableWindow(GetDlgItem(DLG.dlgBook,IDC_BUTTON_UPDATE_RESULT),TRUE);
				//	break;
				//case IDC_LIT_GOOD:
				//	EnableWindow(GetDlgItem(DLG.dlgBook,IDC_BUTTON_UPDATE_RESULT),TRUE);
				//	break;
				//case IDC_BALANCE:
				//	EnableWindow(GetDlgItem(DLG.dlgBook,IDC_BUTTON_UPDATE_RESULT),TRUE);
				//	break;
				//case IDC_LIT_BAD:
				//	EnableWindow(GetDlgItem(DLG.dlgBook,IDC_BUTTON_UPDATE_RESULT),TRUE);
				//	break;
				//case IDC_VERY_BAD:
				//	EnableWindow(GetDlgItem(DLG.dlgBook,IDC_BUTTON_UPDATE_RESULT),TRUE);
				//	break;
				case IDC_BUTTON_UPDATE_RESULT:		//���½��
					UpdateBookResult(pDis, MST->book);
					EnableWindow(GetDlgItem(hDlg,IDC_BUT_BOOK_PGN),TRUE);
					break;

				case IDC_ENABLE_EDIT_BOOK:{
					
					if(pDis->gameMode != EditBook){
						pDis->gameMode = EditBook;
						EnableWindow(GetDlgItem(DLG.dlgBook,IDC_BUTTON_UPDATE_RESULT),TRUE);
						//EnableWindow(GetDlgItem(DLG.dlgBook,IDC_BOOK_ZENLI),TRUE);
						SetDlgItemText(hDlg,IDC_ENABLE_EDIT_BOOK,"ȡ���༩");
					}
					else{
						pDis->gameMode = BeginningOfGame;
						EnableWindow(GetDlgItem(DLG.dlgBook,IDC_BUTTON_UPDATE_RESULT),FALSE);
						//EnableWindow(GetDlgItem(DLG.dlgBook,IDC_BOOK_ZENLI),FALSE);
						SetDlgItemText(hDlg,IDC_ENABLE_EDIT_BOOK,"�༩���");
					}
										  }
					break;
				case IDC_BUT_BOOK_PGN:			//��PGNĿ¼�еõ����еĿ�����Ϣ
					{

						char pgnPath[MAX_PATH];
						sprintf_s(pgnPath,MAX_PATH,"%s%s",installDir,"pgn\\");

						if(TRUE == PgnFileCatToBook(pgnPath)){
							
							//��ʼ��Ϊʹ��

							SendDlgItemMessage(hDlg,IDC_BOOK_CAN_USE,BM_SETCHECK,1,0);

							SendDlgItemMessage(hDlg,IDC_SLIDER_RATE,
								TBM_SETPOS,
								(WPARAM)TRUE,
								(LPARAM) 5);

							EnableWindow(GetDlgItem(hDlg,IDC_BUT_BOOK_PGN),FALSE);
						}

							//char pgnPath[MAX_PATH];

							//sprintf_s(pgnPath,MAX_PATH,"%s%s",installDir,"pgn\\");
					}
					break;
				case IDC_BOOK_BACK:		//��������ļ�

					//
					
					if(BD_openGoodDb(MST) == 0){

						Book_Back_Up(MST->back_db, MST->book);	

						if(MST->back_db != NULL){
							MST->back_db->close(MST->back_db,0);
						}
					}

					break;
					//�˵�
				case ID_BOOK_EDIT:	{				//�༭

					//ֱ���߲���
							UserMoveEvent(pDis,
								StoX(FROM(move)) - 3,
								StoY(FROM(move)) - 3,
								StoX(TO(move))   - 3,
								StoY(TO(move))   - 3, 0);

							//����ǰ���岽һֱ�ߵ����
							//ToEndEvent(pDis);

							//#define FROM(x)                         (((x)>>8)&0xff)
							//#define TO(x)                           ((x)&0xff)
							//#define PIECE(x)                        (((x)>>16)&0xff)
							//#define CAPTURE(x)                      (((x)>>24)&0xff)



							//int from = FROM(move);
							//int to   = TO(move);

							//int fromX = StoX(from) - 3;
							//int fromY = StoY(from) - 3;
							//int toX   = StoX(to)   - 3;
							//int toY   = StoY(to)   - 3;

							//               MakeMove(pDis,fromX,fromY,toX,toY,true);

							//ShowMove(pDis,fromX,fromY,toX,toY);


									}
					
					break;
				default:
					break;
			}

			            //switch(LOWORD(wParam)){  //wmId    = LOWORD(wParam); 
               //     //case ID_OBS:  {      //�Թ۰�ť
               //     ////�õ���ǰѡ����б��ı��
               //     ////LVM_INSERTITEM
               //     ////int sel = ListView_GetSelectedColumn(IDC_LIST_BOARD);
               //     //  int sel = (int)SendDlgItemMessage(hDlg,IDC_LIST_BOARD,
               //     //      LVM_GETSELECTEDCOLUMN,0,0);
               //     //  int test  = 0;
               //     //  }
               //     //break;
               // case IDC_LIST_BOARD:{
               //     int test = WM_RBUTTONDOWN;
               //             }
               //     break;
               // case IDM_ICS_OBS: 
            break;
		case  WM_NOTIFY:   
			{

				char str[512];
                //if(wParam == IDC_QK_LIST_USE || wParam == IDC_QK_LIST_NOT_USE){ //LVN_COLUMNCLICK
				if(wParam == IDC_QK_STEP_LIST){ //LVN_COLUMNCLICK
                    switch (((LPNMHDR) lParam)->code){
						case NM_DBLCLK:			{
							//��˫��item��
							if(pDis->gameMode != EditBook){
								break;
							}

							NMITEMACTIVATE  *lpnmitem = (LPNMITEMACTIVATE) lParam;
							int item = lpnmitem->iItem;
							LVITEM lvi;
							lvi.pszText     = str;
							lvi.iSubItem    = 0;
							lvi.iItem       = item;
							lvi.cchTextMax  = 510;
							SendDlgItemMessage(hDlg,(int)wParam,LVM_GETITEMTEXT,item,(LPARAM)(&lvi));

							curSel = atoi(lvi.pszText);
							if(curSel == 0){
								return FALSE;
							}

							lvi.iSubItem  = 7;
							SendDlgItemMessage(hDlg,(int)wParam,LVM_GETITEMTEXT,item,(LPARAM)(&lvi));

							move = atoi(lvi.pszText);

							//ֱ���߲���
							UserMoveEvent(pDis,
								StoX(FROM(move)) - 3,
								StoY(FROM(move)) - 3,
								StoX(TO(move))   - 3,
								StoY(TO(move))   - 3, 0);


												}
							break;
                        case NM_CLICK:					//����
							break;
        //                    {
        //                        NMITEMACTIVATE  *lpnmitem = (LPNMITEMACTIVATE) lParam;
        //                        int item = lpnmitem->iItem;
        //                        LVITEM lvi;
        //                        lvi.pszText     = str;
        //                        lvi.iSubItem    = 0;
        //                        lvi.iItem       = item;
        //                        lvi.cchTextMax  = 510;
        //                        SendDlgItemMessage(hDlg,(int)wParam,LVM_GETITEMTEXT,item,(LPARAM)(&lvi));
        //                         
        //                        curSel = atoi(lvi.pszText);
        //                        if(curSel == 0){
        //                            return FALSE;
        //                        }

								//ListId = (int)wParam;

								////ͬʱ�õ���ǰ���岽
								//lvi.iSubItem  = 7;
								//SendDlgItemMessage(hDlg,(int)wParam,LVM_GETITEMTEXT,item,(LPARAM)(&lvi));

								//move = atoi(lvi.pszText);

								//if(pDis->gameMode != EditBook){
								//	break;
								//}

        //                        POINT pt;
        //                        GetCursorPos(&pt);
        //                        //SetFore
        //                        HMENU hm = LoadMenu(hInst,MAKEINTRESOURCE(IDR_MENU_BOOK_USE));	
        //                        hm       = GetSubMenu(hm,0);
        //                        TrackPopupMenu(hm,TPM_LEFTALIGN|TPM_LEFTBUTTON |
        //                            TPM_RIGHTBUTTON,pt.x,pt.y,NULL,hDlg,NULL);
        //                    }
                            break;

						case LVN_COLUMNCLICK:			//�б�Ҫ������
							{
								NM_LISTVIEW *pnml = (NM_LISTVIEW*)lParam;
								
								//if(pnml->iSubItem == 

								SendMessage(GetDlgItem(hDlg,IDC_QK_STEP_LIST),
									LVM_SORTITEMS,
									pnml->iSubItem,
									(LPARAM)StepCompareFucn);

								UpdateSteplParam();

								LIST_ORDER_SJ ^= 0x1;
							}
							break;
                        default:
                            break;
                    }
                }//if(wParam == IDC_LIST_BOARD)
            }
            break;
        case WM_SIZE:
            //FitBookDlgItem(hDlg);
			if(IsIconic(hDlg)){
				break;
			}
			newSizeX = LOWORD(lParam);
			newSizeY = HIWORD(lParam);
			if(sizeX != newSizeX || sizeY != newSizeY){

				FitBookItemPosition(hDlg,newSizeX,newSizeY);
				//}                
			}
            break;
        case WM_GETMINMAXINFO:    //���ⴰ�����Ĺ�С /* Prevent resizing window too small */
            mmi = (MINMAXINFO*) lParam;
            mmi->ptMinTrackSize.x = Book_Default_Width;
			//mmi->ptMaxTrackSize.x = Book_Default_Width;
            mmi->ptMinTrackSize.y = Book_Default_Height;
            break;
        case WM_CLOSE:
            DLG_BOOK_Event();
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


void DLG_BOOK_Event(void){
    //(void) CheckMenuItem(GetMenu(hwndMain), IDM_SaveSettingsOnExit,

	 dispboard_t* pDis = OBS[0];
	//			MF_BYCOMMAND|(DIS.saveSettingsOnExit ?  MF_CHECKED : MF_UNCHECKED));
    if(DLG.dlgBook){
        if(IsWindowVisible(DLG.dlgBook)){
             ShowWindow(DLG.dlgBook,SW_HIDE);
             CheckMenuItem(GetMenu(pDis->hwndThis),IDM_BOOK_DLG,MF_UNCHECKED);
        }
        else{
            ShowWindow(DLG.dlgBook,SW_SHOW);
            CheckMenuItem(GetMenu(pDis->hwndThis), IDM_BOOK_DLG, MF_CHECKED);
        }
        //if(DLG.dlgBookUp){     //��ǰ�岽�Ի�������ʾ��           
        //    ShowWindow(DLG.dlgBook,SW_HIDE);
        //    DLG.dlgBookUp = false;
        //    CheckMenuItem(GetMenu(hwndMain),IDM_BOOK_DLG,MF_UNCHECKED);
        //}
        //else{               //��������
        //    ShowWindow(DLG.dlgBook,SW_SHOW);
        //    DLG.dlgBookUp = true;
        //    CheckMenuItem(GetMenu(hwndMain),IDM_BOOK_DLG,MF_CHECKED);
        //}
    }
    else{
         FARPROC lpProc = MakeProcInstance((FARPROC)DLG_BOOK_PROC,hInst);
         DLG.dlgBook = CreateDialog(hInst,MAKEINTRESOURCE(DLG_BOOK),pDis->hwndThis,(DLGPROC)lpProc);
         FreeProcInstance(lpProc);
         ShowWindow(DLG.dlgBook,SW_SHOW);
         //DLG.dlgBookUp = true;
         CheckMenuItem(GetMenu(pDis->hwndThis),IDM_BOOK_DLG,MF_CHECKED);

		 

         FitBookDlgPositionDefault(DLG.dlgBook);
    }

	//if(IsWindowVisible(DLG.dlgBook)){
		
		//��ʼ����ǰ�岽������岽
		FillBookbyPos(pDis,MST->book);
	//}

	//SWP_NOZORDER|SWP_NOACTIVATE

	SetActiveWindow(pDis->hwndThis);

	
}
