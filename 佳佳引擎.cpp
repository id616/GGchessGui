#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"

#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"



void		//�����߲�������,ע��ֻ�Ƿ����û�����һ��,����Ҫ��������Ҫ����!!!
SendCurPosToProgram(dispboard_t* pDis, ChessProgramState *cps){
    TCHAR    buf[FEN_SIZE];
	//TCHAR*   pb;
	TCHAR    fen[MSG_SIZ];
    int     start;
    int     startSide;

	int     gply   = pDis->pos->curStep;
    int     nonCap = pDis->pos->His[gply].nonCap;

	//����ǰ�ľ��渴��һ��
	memcpy(cps->pos, pDis->pos, sizeof(position_t));

	//������һ�������ӵľ���  
	startSide = pDis->pos->side ^ (nonCap%2);
	start     = gply - nonCap;

	position_to_fen_by_b256(pDis->B256dis[start],startSide,fen);

	swprintf_s(buf, sizeof(buf) / sizeof(TCHAR), L"fen %s moves", fen);

	//pb = buf + wcslen(buf);

	for(int i = start; i < gply; i++){
		//swprintf_s(pb, sizeof(buf) / sizeof(TCHAR), L" %s", pDis->parseList[i]);
		//pb += 5;

		wcscat_s(buf, sizeof(buf) / sizeof(TCHAR), L" ");
		wcscat_s(buf, sizeof(buf) / sizeof(TCHAR), pDis->parseList[i]);
	}

	wcscat_s(buf, sizeof(buf) / sizeof(TCHAR), L"\n");
	SendToProgram(buf,cps);   //���ͳ�ʼ���� 
}

void SendOnlyFenToProgram(dispboard_t* pDis, ChessProgramState *cps){

	TCHAR    buf[MSG_SIZ];
	int start = pDis->pos->curStep;
	int startSide = pDis->pos->side;
	position_to_fen_by_b256(pDis->pos->b256, pDis->pos->side, buf);

	wcscat_s(buf, sizeof(buf) / sizeof(TCHAR), L"\n");
	SendToProgram(buf, cps);   //���ͳ�ʼ���� 
}


void			//����UCCI���������������Ϣ
HandleMachineGGyq(TCHAR* message, ChessProgramState *cps){

	TCHAR buf[MSG_SIZ * 8];

	dispboard_t* pDis = (dispboard_t*)cps->pDis;
	//setlocale(LC_CTYPE, "chs");
    if(false){
    }
	//*******************************************************************************
	else if (_wcsnicmp(message, L"cmd:", 4) == 0){
		LogOut(_T("\n"));
		LogOut(message);

		wcscat_s(EvalInfo, EVAL_INFO_SIZE, L"\n");
		wcscat_s(EvalInfo, EVAL_INFO_SIZE, message + 4);
	}
	else if (_wcsnicmp(message, L"cmdend:", 6) == 0){
		//���ڸ��Ƶ�������
		LogOut(_T("\n��ǰ����֣�����java����,ÿһ���������������ȫ�����Ƶ�������,�뷢������̳�ϣ��Ա㷢����������"));


		if (!CopyTextToClipboard(EvalInfo))
			LogOut(L"Unable to copy FEN to clipboard.");	
	}
    //*******************************************************************************
	else if (_wcsnicmp(message, L"bestmove", 8) == 0){


		if (pDis->gameMode != AnalyzeMode){		//��ǰ���Ƿ���ģʽ

			if(cps->cps_stat == Cps_Pondering){				//��ǰ���ں�̨˼��
				cps->cps_stat =  Cps_Waiting;			 

				if(cps->PonderStop == TRUE){				//�Ǻ�̨˼��������
					cps->PonderStop = FALSE;
					SendProgramGo(cps,Cps_Thinking,NULL);
				}
				return;
			}
		}

		cps->cps_stat =  Cps_Waiting;

		//if(cps->maybePonering == TRUE){
		//	cps->maybePonering = FALSE;
		//	return;
		//}
		

        message +=9;
        if(wcslen(message) < 2){
			LogOut(_T("Err"));
            LogOut(message);
			LogOut(_T("\n"));
            //ConsoleOutput("\n",1,FALSE); //�س�����
        }
        else{
            int machineWhite;
            switch(pDis->gameMode){
                case BeginningOfGame:
                    /* Extra move from before last reset; ignore */
#ifdef DEBUG_USE_DEBUG_FILE
                    //if (appData.debugMode) {    //��������һ�ֵ�,��Ҫ��
                        fprintf(appData.debugFP, "Ignoring extra move from %s\n", cps->UCCI_name);
                    //}
#endif
                    return;                    
                case EndOfGame:
                case IcsIdle:

                case MachinePlaysWhite:
                case IcsPlayingWhite:
                    machineWhite = TRUE;
                    break;
                case MachinePlaysBlack:
                case IcsPlayingBlack:
                    machineWhite = FALSE;
                    break;
				default:
					/* Extra move after we tried to stop.  The mode test is
					not a reliable way of detecting this problem, but it's
					the best we can do on engines that don't support ping.
					*/
#ifdef DEBUG_USE_DEBUG_FILE
					//if (appData.debugMode) {
					fprintf(appData.debugFP, "Undoing extra move from %s, gameMode %d\n",
						cps->UCCI_name, pDis->gameMode);
					//}
#endif
					//SendToProgram("undo\n", cps);
					return;
            }
            //
            //if(WhiteOnMove(DIS.forwardMostMove) != machineWhite){

            if(pDis->pos->side != cps->playWhat){

                //LogOut(ColorTell,"Ignoring move out of turn by %s, gameMode %d, forwardMost %d\n",
                //        cps->which, DIS.gameMode, DIS.forwardMostMove, false);

               
                LogOut(message);
				LogOut(_T(" ���������߲�!!,��ǰ������治�����ӷ�!!\n"));

#ifdef DEBUG_MODE               
                //if(appData.debugMode){
                    //fprintf(DIS.debugFP,
                    //    "Ignoring move out of turn by %s, gameMode %d, forwardMost %d\n",
                    //    cps->UCCI_name, DIS.gameMode, DIS.forwardMostMove);
                //}
#endif
                return;
            }
            //�����߲�
            int fromX,fromY,toX,toY;
            ChessMove moveType;

            TCHAR pmove[8];
            //StringCbPrintf(pmove,5,message);

			pmove[0] = message[0];
			pmove[1] = message[1];
			pmove[2] = message[2];
			pmove[3] = message[3];
			pmove[4] = 0;

            /*if(!ParseOneMove(pmove,DIS.forwardMostMove,&moveType,&fromX, &fromY, &toX, &toY, cps->ucci)) {*/
            /*if(!ParseOneMove(pmove,pDis->pos->gply,&moveType,&fromX, &fromY, &toX, &toY, cps->ucci)) {*/
			if(!ParseOneMove(pmove,pDis->pos->curStep,&moveType,&fromX, &fromY, &toX, &toY, cps->ucci)) {
                /* Machine move could not be parsed; ignore it. */
                swprintf_s(buf,MSG_SIZ,_T("Illegal move \"%s\" from %s machine"),message, cps->UCCI_name);
                //DisplayError(buf, 0);
				LogOut(buf);
                return;
            }
            //else{   //��������ظ��жϻ������ж�  rep_eat_or_check ������������,�������3��,�Ͳ�����
            //    
            //}

			TCHAR *ponder;

			if (pDis->gameMode != AnalyzeMode){		//��ǰ���Ƿ���ģʽ

				if(ponder = wcsstr(message,L"ponder ")){	

					ponder += 7;

					cps->PonderMove[0] = *(ponder+0);
					cps->PonderMove[1] = *(ponder+1);
					cps->PonderMove[2] = *(ponder+2);
					cps->PonderMove[3] = *(ponder+3);
					cps->PonderMove[4] = 0;

					cps->PonderMoveInt = str2move(cps->pos, cps->PonderMove);


					//char bb[256];

					//sprintf_s(bb,sizeof(bb),"\npd int %d\n",cps->PonderMoveInt );

					//LogOut(bb);

		            //cps->PonderMoveInt = pmove;
				}
				else {
					cps->PonderMove[0] = 0;
				}
			}
			else{
				cps->PonderMove[0] = 0;
			}

            if (cps->offeredDraw){
                cps->offeredDraw--;
            }

			if (pDis->gameMode != AnalyzeMode){		//��ǰ���Ƿ���ģʽ
				//�ŵ�UserMoveEvent��ͳһ����
				FinishMove(pDis,NormalMove,fromX,fromY,toX,toY);
			}
			else{									//��ǰ�Ƿ���ģʽ,���ܲ�������
							
			}
            return;
        }//��bestmove
    }
    //*******************************************************************************
	else if (_wcsnicmp(message, L"nobestmove", 10) == 0){
        
        LogOut(cps->UCCI_name);        //�����������
        LogOut(_T("��,��̫������,����û�а취������,ֻ���ϸ�\n"));  
        //DispStatS(message);

       SendMessage(hStatusBar,SB_SETTEXT,0,(LPARAM)L"�����ϸ�!");

		cps->cps_stat = Cps_Waiting;

		//cps->maybePonering = FALSE;
		//cps->maybeThinking = FALSE;
		//SendMessage(hwndToolBar,TB_ENABLEBUTTON,IDT_Stop,0); 

        //EndGame(

        //˼��״̬�ķ������˺����淵�ؿ���״̬����ʾ˼�������
        // ������һ���ŷ�Ҳû���㣬��ʾ��ǰ�����������棬
        // ���߽��յ����硰go depth 0����ֻ�����������̬�������۵�ָ� 
    }
    //*******************************************************************************
	else if (_wcsnicmp(message, L"id", 2) == 0){
        LogOut(cps->UCCI_name);        //�����������
        message +=3;

        //LogOut(ColorShout,message,true);

        if(false){
        }
		else if (_wcsnicmp(message, L"name", 4) == 0){

            swprintf_s(cps->UCCI_name,32,_T("%s\n"),(message+5));
            LogOut(_T("��������: "));
            LogOut(cps->UCCI_name);            
        }
		else if (_wcsnicmp(message, L"copyright", 9) == 0){

			swprintf_s(cps->UCCI_copyright, 64, _T("%s\n"), (message + 10));
			LogOut(_T("��Ȩ����: "));
			LogOut(cps->UCCI_copyright);
        }
		else if (_wcsnicmp(message, L"author", 6) == 0){

			swprintf_s(cps->UCCI_author, 64, _T("%s\n"), (message + 7));
			LogOut(_T("��������: "));
			LogOut(cps->UCCI_author);
        }
		else if (_wcsnicmp(message, L"user", 4) == 0){

			swprintf_s(cps->UCCI_user, 32, _T("%s\n"), (message + 5));
			LogOut(_T("��Ȩ�û�: "));
			LogOut(cps->UCCI_user);
        }
    }
    //*******************************************************************************
	else if (_wcsnicmp(message, L"option", 6) == 0){
		LogOut(cps->UCCI_name);        //�����������
        message +=7; 
        if(false){
        }
		else if (_wcsnicmp(message, L"batch", 5) == 0){

            message += 6;            
            TCHAR* p = wcsstr(message,L"default");
            if(p != 0){
                p += 8;
				if (_wcsnicmp(p, L"true", 4) == 0){
                    cps->UCCI_batch = true;
                }
                else{
                    cps->UCCI_batch = false;
                }
				LogOut(_T("����������ģʽ: "));

                if(cps->UCCI_batch){
					LogOut(_T("�ѿ���\n"));
                }
                else{
					LogOut(_T("�ѹر�\n"));
                }
            }
        }
		else if (_wcsnicmp(message, L"debug", 5) == 0){
            message += 6;
            TCHAR* p = wcsstr(message,L"default");
            if(p != 0){
                p += 8;
				if (_wcsnicmp(p, L"true", 4) == 0){
                    cps->UCCI_debug = true;
                }
                else{
                    cps->UCCI_debug = false;
                }
				LogOut(_T("�������ģʽ: "));

                if(cps->UCCI_debug){
					LogOut(_T("�ѿ���\n"));
                }
                else{
					LogOut(_T("�ѹر�\n"));
                }
            }
        }
		else if (_wcsnicmp(message, L"usemillisec", 11) == 0){
            message += 12;
           TCHAR* p = wcsstr(message,L"default");
            if(p != 0){
                p += 8;     
				if (_wcsnicmp(p, L"true", 4) == 0){
                    cps->UCCI_usemillisec = true;
                }
                else{
                    cps->UCCI_usemillisec = false;
                }
				LogOut(_T("�������ģʽ: "));

                if(cps->UCCI_usemillisec){
					LogOut(_T("�ѿ���\n"));
                }
                else{
					LogOut(_T("�ѹر�\n"));
                }
            }
        }
		else if (_wcsnicmp(message, L"ponder", 6) == 0){ //�Ƿ�ʹ�ú�̨˼����ʱ�����

            //message += 7;
            //char* p  = strstr(message,"default");
            //if(p != 0){
            //    p       += 8; 
            //    if(strncasecmp(p,"true",4) == 0){
            //        cps->UCCI_ponder_chelu = true;
            //    }
            //    else{
            //        cps->UCCI_ponder_chelu = false;
            //    }
            //    LogOut("�����̨˼��ʱ�����: ");

            //    if(cps->UCCI_ponder_chelu){
            //        LogOut("�ѿ���\n");
            //    }
            //    else{
            //        LogOut("�ѹر�\n");
            //    }
            //}
        }
		else if (_wcsnicmp(message, L"usebook", 7) == 0){
            message += 8;
            TCHAR* p  = wcsstr(message,L"default");
            if(p != 0){
                p += 8;
				if (_wcsnicmp(p, L"true", 4) == 0){
                    cps->UCCI_haveselfBook = true;
                }
                else{
                    cps->UCCI_haveselfBook = false;
                }
                if(cps->UCCI_haveselfBook){
					LogOut(_T("�����Դ����ֿ�\n"));
                }
                else{
					LogOut(_T("����û�п��ֿ�\n"));
                }
            }

            /*LogOut(ColorChannel1,   "usebook, ����δ����\n",true); */  
        }
		else if (_wcsnicmp(message, L"bookfiles", 9) == 0){
            message += 10;
            TCHAR* p  = wcsstr(message,L"default");
            if(p != 0){
                p       += 8;              
                //StringCbPrintf(cps->UCCI_bookfiles,MAX_PATH,"%s\n",p);
				LogOut(_T("���濪�ֿ�·��: "));
                //LogOut(ColorChannel1,cps->UCCI_bookfiles,true); 
            }
        }
		else if (_wcsnicmp(message, L"egtbpaths", 9) == 0){
			LogOut(_T("egtbpaths, ����δ����\n"));
        }
		else if (_wcsnicmp(message, L"hashsize", 8) == 0){
            message += 9;
            TCHAR* p  = wcsstr(message,L"default");
            if(p != 0){
                p       += 8;  
                cps->UCCI_hashsize = _wtoi(p);
				LogOut(_T("����HASH��С: "));
				swprintf_s(buf, 512, _T("%dMB\n"), cps->UCCI_hashsize);
                LogOut(buf);  
            }
        }
		else if (_wcsnicmp(message, L"threads", 7) == 0){
			LogOut(_T("threads, ����δ����\n"));
        }
		else if (_wcsnicmp(message, L"drawmoves", 9) == 0){
			LogOut(_T("drawmoves, ����δ����\n"));
        }
		else if (_wcsnicmp(message, L"repetition", 10) == 0){
			LogOut(_T("repetition, ����δ����\n"));
        }
		else if (_wcsnicmp(message, L"pruning", 7) == 0){

            message += 8;
            //char* p  = strstr(message,"default");           
            //if(p != 0){
            //    p       += 8;  
            //    StringCbPrintf(cps->UCCI_pruning,32, "%s\n", p);
            //    LogOut("����ü��̶�: ");
            //    LogOut(cps->UCCI_pruning);
            //}
        }
		else if (_wcsnicmp(message, L"knowledge", 9) == 0){
            message += 10;
            //char* p  = strstr(message,"default");
            //if(p != 0){
            //    p       += 8;  
            //    StringCbPrintf(cps->UCCI_knowledge,32, "%s\n", p);
            //    LogOut("�����趨֪ʶ��С: ");
            //    LogOut(cps->UCCI_knowledge);
            //}
        }
		else if (_wcsnicmp(message, L"selectivity", 11) == 0){
            message += 12;
            //char* p  = strstr(message,"default");

            //if(p != 0){
            //    p       += 8;  
            //    StringCbPrintf(cps->UCCI_selectivity,32, "%s\n", p);
            //    LogOut("����ѡ����(�����)ϵ��: ");
            //    LogOut(cps->UCCI_selectivity);
            //}
        }
		else if (_wcsnicmp(message, L"style", 5) == 0){
            //LogOut(   "style, ����δ����\n"); 
        }
		else if (_wcsnicmp(message, L"loadbook", 8) == 0){
            //LogOut(ColorChannel1,   "loadbook, ����δ����\n",false); 
        }
		else if (_wcsnicmp(message, L"clearhash", 9) == 0){
            LogOut(_T("clearhash, ����δ����\n")); 
        }
		else if (_wcsnicmp(message, L"dualtime", 8) == 0){

            message += 9;
            TCHAR* p  = wcsstr(message,L"default");            
            if(p != 0){
                p       += 8;  
				if (_wcsnicmp(p, L"true", 4) == 0){
                    cps->UCCI_dualtime = true;
                }
                else{
                    cps->UCCI_dualtime = false;
                }              
				LogOut(_T("����˫ʱ�޹���: "));
                if(cps->UCCI_dualtime){
					LogOut(_T("�ѿ���\n"));
                }
                else{
					LogOut(_T("�ѹر�\n"));
                }
            }
            else{
                cps->UCCI_dualtime = false;
				LogOut(_T("����˫ʱ�޹���: "));
				LogOut(_T("�ѹر�\n"));
            }
        }
		else if (_wcsnicmp(message, L"newgame", 7) == 0){
            //message +=8;
            LogOut(message);
			LogOut(_T("\n"));
        }
        else{     //δʶ���ѡ��
			LogOut(_T("���治��ʶ�����淢�͵�ѡ��: "));
			LogOut(message);
        }
    }
    //*******************************************************************************
	else if (_wcsnicmp(message, L"uciok", 5) == 0){
        //if(cps->UCCI_initDone == FALSE){

		//if(cps->cps_stat == Cps_Waiting){
		if(cps->cps_stat == Cps_InLoading){
			PostMessage(cps->loadWin,WM_USER_YqLoad_OK,0,(LPARAM)cps);  //���������ڴ��ڷ��ͳ�ʼ���ɹ�����Ϣ
        }  
    }
    //*******************************************************************************
	else if (_wcsnicmp(message, L"readyok", 7) == 0){
        //����״̬��˼��״̬�ķ������������洦�ھ���״̬(����������ָ��)��
		LogOut(cps->UCCI_name);        //�����������
        LogOut(_T("�������ڽ���ָ��״̬!\n"));
    }
    //*******************************************************************************
	else if (_wcsnicmp(message, L"info", 4) == 0){
        //˼��״̬�ķ�������ʾ����˼����Ϣ��ͨ�������¼�����Ϣ�� 
        //(1) nodes <�������Ľ����> time <�ѻ��ѵ�ʱ��>��˼����Ϣ�и�����ʱ��ͨ���Ժ���Ϊ��λ���������ʱ���������������ٶ�(NPSֵ)����λ��KNPS�� 
        //(2) depth <��ǰ�������> [score <��ֵ> pv <��Ҫ����>]���������˼��������ȼ���˼��·�ߺͺû���
        //ĿǰUCCI���桶������ʦ��ֻ��������Ϣ����������������ʼ�����£�
        //��������ʦ���յ�����ķ�����info depth 6 score 4 pv b0c2 b9c7 c3c4 h9i7 c2d4 h7e7��
        //��ô������Ӧ�����������ȣ�6����ֵ��4����Ҫ��������˽��� ������ ���߽�һ ������ ���߽��� �ڣ�ƽ������
        //��ֵͨ����һ������(�����)Ϊ100�ּǣ�������Ϣ˵����ʱ��ǰҪ�ߵ�һ��ռ���൱��0.04�����ӵ����ơ� 
        //(3) currmove <��ǰ�����ŷ�>�������������˼�����ŷ���
		if (_wcsnicmp(message, L"info time ", 10) == 0){
			LogOut(_T("\n\n"));
			LogOut(message);
		}

        TCHAR *movestr;
        message += 5;
        if(false){
        }
			// initok
		else if (_wcsnicmp(message, L"initok", 6) == 0){

			//IsSendRand = 1;
			//�Ѽ������ʼ���ɹ���
			Sleep(300);

			//LogOut("yq initok opppppppppppppppppppppp\n");
		}
		else if (_wcsnicmp(message, L"initend", 7) == 0){
		}

		else if (_wcsnicmp(message, L"log", 3) == 0){
        }
		else if(movestr = wcsstr(message,L"currmove ")){

			movestr += 9;
			movestr[5] = 0;

			int move = str2move(cps->pos, movestr);

			TCHAR szStepName[32];

			//char szStepName = str2move(cps->pos, movestr);
			GetMoveNameSimple(cps->pos,szStepName,move,appData.moveType);

			//if (movestr = wcsstr(message, L"currmovenumber ")){

			//	int num = _wtoi(movestr);
			//}

		//	int num = 

			SendMessage(hStatusBar,SB_SETTEXT,1,(LPARAM)szStepName);  //�岽����

			//----------------------------------------------------			
			// movestr += 21;
            // SendMessage(hStatusBar,SB_SETTEXT,2,(LPARAM)movestr);  //�岽���
			
		}
        else if(movestr = wcsstr(message,L"multipv ")){        //���淴���Ĺؼ�·��

			//char CurInfo[102]; //��ǰ��Ϣ

			TCHAR *depth = wcsstr(message, L" depth ");
			TCHAR *pv = wcsstr(message, L" pv ");
			TCHAR *psc = wcsstr(message, L" score");
			TCHAR *time = wcsstr(message, L" time ");
			TCHAR *nps = wcsstr(message, L" nps ");
			TCHAR *nodes = wcsstr(message, L" nodes ");
			//TCHAR *nodess = wcsstr(message, L" neodes ");
			int firstMove = -1;	

			buf[0] = '\n';

			//int slen = (int)wcslen(message);

			//if (psc == NULL) {
			//	LogOut(message);
			//	return;
			//}


			if(pv != NULL){
				pv[0] = '\n';
				pv[1]  = '.';
				pv[2]  = ' ';
				pv[3]  = 0; 
				//strcat_s(buf,sizeof(buf), depth);
			}			

			//******************************************************************
			//if(cps->maybePonering){	
			if (cps->cps_stat == Cps_Pondering){
				firstMove = cps->PonderMoveInt;
				TCHAR sta[256];
				swprintf_s(sta, sizeof(sta) / sizeof(TCHAR), L"��̨:%8s", cps->PonderName);
				SendMessage(hStatusBar, SB_SETTEXT, 0, (LPARAM)sta);
				swprintf_s(buf + 1, sizeof(buf) / sizeof(TCHAR)-2, _T("\n%s %s >>>:\n%s"), _T("��̨: "), cps->PonderName, depth);
			}
			else{
				if (pDis->gameMode == AnalyzeMode){
					SendMessage(hStatusBar, SB_SETTEXT, 0, (LPARAM)L"����...");
					swprintf_s(buf + 1, sizeof(buf) / sizeof(TCHAR)-2, _T("\n%s\n%s"), _T("����: >>>>>>> "), depth);
				}
				else{
					SendMessage(hStatusBar, SB_SETTEXT, 0, (LPARAM)L"˼��...");
					swprintf_s(buf + 1, sizeof(buf) / sizeof(TCHAR)-2, _T("\n%s\n%s"), _T("˼��: >>>>>>> "), depth);
				}
			}

			TCHAR szStepName[16];

			if(psc == NULL){
			  psc = wcsstr(message,L" mate ");
			}

			if(depth == NULL){
				LogOut(message);return;
			}
			if(psc == NULL){
				LogOut(message); return;
			}

			if(nodes == NULL){
				LogOut(message); return;
			}

			if(nps == NULL){
				LogOut(message); return;
			}


			int searchTime = 0;

			if(time == NULL){
				LogOut(message); return;
			}					
			
			psc[0]   = 0;
			time[0]  = 0;
			nodes[0] = 0;

            depth += 7;
			psc   += 7;
			time  += 6;	
			nps   += 5;	

			pDis->pos->His[cps->pos->gply].search_score = (sint16)_wtoi(psc);
			//pDis->pos->His[pDis->pos->gply].book_score = NO_BOOK_SCOER;

			HDCDrawChart(TAB.dlgScore, pDis, NULL, true);

			if(pv != NULL){

				movestr = pv;
				int num  = 0;
				movestr  += 4;

				int len   = (int)wcslen(movestr);

				BOOL First = TRUE;

				while(len >= 4){
					int move = str2move(cps->pos, movestr);
					GetMoveNameSimple(cps->pos,szStepName,move,appData.moveType);
					wcscat_s(buf,sizeof(buf)/sizeof(TCHAR),szStepName);

					if(cps->cps_stat != Cps_Pondering){
						if(First == TRUE){
							First = FALSE;
                          firstMove = move;
							//SendMessage(hStatusBar,SB_SETTEXT,1,(LPARAM)szStepName);
						}
					}

					MakePosMoveOnly(cps->pos,move);
					movestr += 5;
					len     -= 5;
					num++;
				}

				int old_num = num;

				while(num > 0){
					UnMakePosMoveOnly(cps->pos);
					num--;
				}
			}

		    LogOut(buf);		
        }
		//
  //      else if(movestr = strstr(message,"time ")){        //���淴���Ĺؼ�·��
		//	LogOut("\n\n");
		//	LogOut(message);
		//}
		//else if(movestr = strstr(message,"hashfull ")){        //���淴���Ĺؼ�·��
		//	LogOut("\n");
		//	LogOut(message);
		//}
        else {
            LogOut(message);               //����Ϣ��ʾ��״̬����
        }
        
    }
    //*******************************************************************************
	else if (_wcsnicmp(message, L"bye", 3) == 0){
        //���յ�quitָ���ķ���������������˳���תǰ��׼��������
        // ֪ͨ���棬���潫��˲�������˳���ת�������յ���ָ���
        // ͨ��ֻ��Ҫ�ȴ�1���룬���ɹر��������ͨ����

        //if(cps->twoMachinesColor[0] == 'w'){
        //    LogOut(ColorSeek,    "�췽�����ѳɹ��˳�!\n",false);
        //}
        //else{
        //    LogOut(ColorChannel1,"�ڷ������ѳɹ��˳�!\n",false);           
        //}
        //if(cps->UCCI_which == 1){           //���ǵ�һ������
        //    SendMessage(hwndToolBar,TB_ENABLEBUTTON,IDT_COM_RED,0);    
        //}
        //else{
        //    SendMessage(hwndToolBar,TB_ENABLEBUTTON,IDT_COM_BLUE,0);
        //}
        
        //cps->UCCI_initDone  = FALSE;

		//LogOut(cps->UCCI_name);        //�����������
		//LogOut("�����ѳɹ��˳�!\n\n");
    }
    //*******************************************************************************
	else if (_wcsnicmp(message, L"copyprotection", 14) == 0){
        LogOut(cps->UCCI_name);        //�����������
        message +=15;
		LogOut(_T("�����Ȩ��֤: "));

		if (_wcsnicmp(message, L"ok", 2) == 0){
			LogOut(_T("��ͨ��\n"));
        }
        else{
			LogOut(_T("δͨ��\n"));
        }
    }   
    //*******************************************************************************
    else {  //����������������Ϣ
        LogOut(cps->UCCI_name);        //�����������
		LogOut(_T("����δʶ��ָ��\n"));
		LogOut(message);
        LogOut(_T("\n"));
    }
}

