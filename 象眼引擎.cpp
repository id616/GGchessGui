#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"

void			//����UCCI���������������Ϣ
HandleMachineUCCI162(TCHAR *Tinfo, ChessProgramState *cps){


//    //char* yqName;
//    char buf[MSG_SIZ*8];
//
//
//	dispboard_t* pDis = (dispboard_t*)cps->pDis;
//
//	if(cps == &pDis->first){
//		LogOut("1:");
//	}
//	else{
//		LogOut("2:");
//	}
//
//    if(false){
//    }
//    //*******************************************************************************
//    else if(strncasecmp(message,"bestmove",8) == 0){
//
//        LogOut(cps->UCCI_name);        //�����������
//		LogOut(message);
//
//        //DispStatS(message);
//		SendMessage(hStatusBar,SB_SETTEXT,0,(LPARAM)"�����ϸ�!");
//
//        message +=9;
//        if(strlen(message) < 2){
//            LogOut("Err");
//            LogOut(message);
//            LogOut("\n");
//            //ConsoleOutput("\n",1,FALSE); //�س�����
//        }
//        else{
//            int machineWhite;
//            switch(pDis->gameMode){
//                case BeginningOfGame:
//                    /* Extra move from before last reset; ignore */
//#ifdef DEBUG_USE_DEBUG_FILE
//                    //if (appData.debugMode) {    //��������һ�ֵ�,��Ҫ��
//                        fprintf(appData.debugFP, "Ignoring extra move from %s\n", cps->UCCI_name);
//                    //}
//#endif
//                    return;                    
//                case EndOfGame:
//                case IcsIdle:
//                default:
//                    /* Extra move after we tried to stop.  The mode test is
//                    not a reliable way of detecting this problem, but it's
//                    the best we can do on engines that don't support ping.
//                    */
//#ifdef DEBUG_USE_DEBUG_FILE
//                    //if (appData.debugMode) {
//                        fprintf(appData.debugFP, "Undoing extra move from %s, gameMode %d\n",
//                            cps->UCCI_name, pDis->gameMode);
//                    //}
//#endif
//                    //SendToProgram("undo\n", cps);
//                    return;
//                case MachinePlaysWhite:
//                case IcsPlayingWhite:
//                    machineWhite = TRUE;
//                    break;
//                case MachinePlaysBlack:
//                case IcsPlayingBlack:
//                    machineWhite = FALSE;
//                    break;
//                case TwoMachinesPlay:   //�����սʶ��
//                    //machineWhite  = (cps->UCCI_which == 1);      //�ǵ�һ������ 
//                    machineWhite = cps->playWhat == WHITE;
//                    break;
//            }
//            //
//            //if(WhiteOnMove(DIS.forwardMostMove) != machineWhite){
//
//            if(pDis->pos->side != cps->playWhat){
//
//                //LogOut(ColorTell,"Ignoring move out of turn by %s, gameMode %d, forwardMost %d\n",
//                //        cps->which, DIS.gameMode, DIS.forwardMostMove, false);
//
//               
//                LogOut(message);
//                LogOut(" ���������߲�!!\n");
//
//#ifdef DEBUG_MODE               
//                //if(appData.debugMode){
//                    //fprintf(DIS.debugFP,
//                    //    "Ignoring move out of turn by %s, gameMode %d, forwardMost %d\n",
//                    //    cps->UCCI_name, DIS.gameMode, DIS.forwardMostMove);
//                //}
//#endif
//                return;
//            }
//            //�����߲�
//            int fromX,fromY,toX,toY;
//            ChessMove moveType;
//
//            char pmove[8];
//			sprintf_s(pmove, 5, message);
//
//            /*if(!ParseOneMove(pmove,DIS.forwardMostMove,&moveType,&fromX, &fromY, &toX, &toY, cps->ucci)) {*/
//            if(!ParseOneMove(pmove,pDis->pos->gply,&moveType,&fromX, &fromY, &toX, &toY, cps->ucci)) {
//                /* Machine move could not be parsed; ignore it. */
//				sprintf_s(buf, MSG_SIZ, "Illegal move \"%s\" from %s machine", message, cps->UCCI_name);
//                DisplayError(buf, 0);
//                if (pDis->gameMode == TwoMachinesPlay) {
//                    GameEnds(pDis,machineWhite ? BlackWins : WhiteWins,"Forfeit due to illegal move", GE_XBOARD);
//                }
//                return;
//            }
//            //else{   //��������ظ��жϻ������ж�  rep_eat_or_check ������������,�������3��,�Ͳ�����
//            //    
//            //}
//
//
//
//            //pDis->hintRequested = FALSE;
//            //pDis->lastHint[0]   = NULLCHAR;
//            //pDis->bookRequested = FALSE;
//            /* Program may be pondering now */
//            //cps->maybeThinking = TRUE;
//            //if (cps->sendTime == 2){
//            //    cps->sendTime = 1;
//            //}
//            if (cps->offeredDraw){
//                cps->offeredDraw--;
//            }
//            //StringCbCopy(machineMove,MSG_SIZ,DIS.currentMoveString);        
//            //StringCbCat(machineMove,MSG_SIZ,"\n");
//            MakeMove(pDis,fromX,fromY,toX,toY,false);    /*updates forwardMostMove*/
//            if(pDis->gameMode == TwoMachinesPlay){    //��˫�����ս
//                //if(cps->other->sendTime){
//                //    /*SendTimeRemaining(cps->other,cps->other->twoMachinesColor[0] == 'w');*/
//                //    //SendTimeRemaing(
//                //}
//                // UCCI ������ʱ��,
//                //SendMoveToProgram(DIS.forwardMostMove-1,cps->other);    //
//                //SendMoveToProgram(DIS.pos.gply - 1,cps->other);    //
//
//				
//				ChessProgramState* other;
//
//				if(cps == &pDis->first){
//					other = &pDis->second;
//				}
//				else{
//					other = &pDis->first;
//				}
//
//                //SendProgramGo(other);                              //ʹ�����濪ʼ����
//
//                if(pDis->firstMove){
//                    pDis->firstMove = FALSE;
//                }
//                //cps->other->maybeThinking = TRUE;
//            }            
//
//            ShowMove(pDis,fromX,fromY,toX,toY);
//
//            if(pDis->gameMode != TwoMachinesPlay){
//                
//				SetUserThinkingEnables();
//
//                //if(cps->UCCI_ponder_chelu == false){
//                //    cps->maybeThinking = false;
//                //}
//                //else{ //�����cps�����̨˼�� 
//                //    ////
//                //}
//            }
//            return;
//        }//��bestmove
//    }
//    //*******************************************************************************
//    else if(strncasecmp(message,"nobestmove",10) == 0){
//        
//        LogOut(cps->UCCI_name);        //�����������
//        LogOut(_T("nobestmove\n"));  
//        //DispStatS(message);
//		SendMessage(hStatusBar,SB_SETTEXT,0,(LPARAM)"�����ϸ�!");
//
//		cps->cps_stat = Cps_Waiting;
//
//		//cps->maybePonering = FALSE;
//		//cps->maybeThinking = FALSE;
//		//PostMessage(hwndToolBar,TB_ENABLEBUTTON,IDT_Stop,0); 
//
//        //EndGame(
//
//        //˼��״̬�ķ������˺����淵�ؿ���״̬����ʾ˼�������
//        // ������һ���ŷ�Ҳû���㣬��ʾ��ǰ�����������棬
//        // ���߽��յ����硰go depth 0����ֻ�����������̬�������۵�ָ� 
//    }
//    //*******************************************************************************
//    else if(strncasecmp(message,"id", 2) == 0){
//        LogOut(cps->UCCI_name);        //�����������
//        message +=3;
//
//        //LogOut(ColorShout,message,true);
//
//        if(false){
//        }
//        else if(strncasecmp(message,"name", 4) == 0){  
//
//            StringCbPrintf(cps->UCCI_name,128,"%s\n",message+5);
//            LogOut("��������: ");
//            LogOut(cps->UCCI_name);            
//        }
//        else if(strncasecmp(message,"copyright", 9) == 0){
//
//            StringCbPrintf(cps->UCCI_copyright,128,"%s\n",message+10);
//            LogOut("��Ȩ����: ");
//            LogOut(cps->UCCI_copyright);     
//        }
//        else if(strncasecmp(message,"author", 6) == 0){
//
//            StringCbPrintf(cps->UCCI_author,128,"%s\n",message+7);
//            LogOut("��������: ");
//            LogOut(cps->UCCI_author);  
//        }
//        else if(strncasecmp(message,"user", 4) == 0){
//
//            StringCbPrintf(cps->UCCI_user,128,"%s\n",message+5);
//            LogOut("��Ȩ�û�: ");
//            LogOut(cps->UCCI_user);  
//        }
//    }
//    //*******************************************************************************
//    else if(strncasecmp(message,"option", 6) == 0){
//        LogOut(cps->UCCI_name);        //�����������
//        message +=7; 
//        if(false){
//        }
//        else if(strncasecmp(message,"batch", 5) == 0){
//
//            message += 6;            
//            char* p = strstr(message,"default");
//            if(p != 0){
//                p += 8;
//                if(strncasecmp(p,"true",4) == 0){
//                    cps->UCCI_batch = true;
//                }
//                else{
//                    cps->UCCI_batch = false;
//                }
//                LogOut("����������ģʽ: ");
//
//                if(cps->UCCI_batch){
//                    LogOut("�ѿ���\n");
//                }
//                else{
//                    LogOut("�ѹر�\n");
//                }
//            }
//        }
//        else if(strncasecmp(message,"debug", 5) == 0){
//            message += 6;
//            char* p = strstr(message,"default");
//            if(p != 0){
//                p += 8;
//                if(strncasecmp(p,"true",4) == 0){
//                    cps->UCCI_debug = true;
//                }
//                else{
//                    cps->UCCI_debug = false;
//                }
//                LogOut("�������ģʽ: ");
//
//                if(cps->UCCI_debug){
//                    LogOut("�ѿ���\n");
//                }
//                else{
//                    LogOut("�ѹر�\n");
//                }
//            }
//        }
//        else if(strncasecmp(message,"usemillisec", 11) == 0){
//            message += 12;
//            char* p = strstr(message,"default");
//            if(p != 0){
//                p += 8;     
//                if(strncasecmp(p,"true",4) == 0){
//                    cps->UCCI_usemillisec = true;
//                }
//                else{
//                    cps->UCCI_usemillisec = false;
//                }
//                LogOut("�������ģʽ: ");
//
//                if(cps->UCCI_usemillisec){
//                    LogOut("�ѿ���\n");
//                }
//                else{
//                    LogOut("�ѹر�\n");
//                }
//            }
//        }
//        else if(strncasecmp(message,"ponder", 6) == 0){ //�Ƿ�ʹ�ú�̨˼����ʱ�����
//
//            //message += 7;
//            //char* p  = strstr(message,"default");
//            //if(p != 0){
//            //    p       += 8; 
//            //    if(strncasecmp(p,"true",4) == 0){
//            //        cps->UCCI_ponder_chelu = true;
//            //    }
//            //    else{
//            //        cps->UCCI_ponder_chelu = false;
//            //    }
//            //    LogOut("�����̨˼��ʱ�����: ");
//
//            //    if(cps->UCCI_ponder_chelu){
//            //        LogOut("�ѿ���\n");
//            //    }
//            //    else{
//            //        LogOut("�ѹر�\n");
//            //    }
//            //}
//        }
//        else if(strncasecmp(message,"usebook", 7) == 0){
//            message += 8;
//            char* p  = strstr(message,"default");
//            if(p != 0){
//                p += 8;
//                if(strncasecmp(p,"true",4) == 0){
//                    cps->UCCI_haveselfBook = true;
//                }
//                else{
//                    cps->UCCI_haveselfBook = false;
//                }
//                if(cps->UCCI_haveselfBook){
//                    LogOut("�����Դ����ֿ�\n");
//                }
//                else{
//                    LogOut( "����û�п��ֿ�\n");
//                }
//            }
//
//            /*LogOut(ColorChannel1,   "usebook, ����δ����\n",true); */  
//        }
//        else if(strncasecmp(message,"bookfiles", 9) == 0){
//            message += 10;
//            char* p  = strstr(message,"default");
//            if(p != 0){
//                p       += 8;              
//                //StringCbPrintf(cps->UCCI_bookfiles,MAX_PATH,"%s\n",p);
//                LogOut("���濪�ֿ�·��: ");
//                //LogOut(ColorChannel1,cps->UCCI_bookfiles,true); 
//            }
//        }
//        else if(strncasecmp(message,"egtbpaths", 9) == 0){
//            LogOut(   "egtbpaths, ����δ����\n"); 
//        }
//        else if(strncasecmp(message,"hashsize", 8) == 0){
//            message += 9;
//            char* p  = strstr(message,"default");
//            if(p != 0){
//                p       += 8;  
//                //cps->UCCI_hashsize = atoi(p);
//				int hash = atoi(p);
//                LogOut("����HASH��С: ");
//                StringCbPrintf(buf,512, "%dMB\n", hash);
//                LogOut(buf);  
//            }
//        }
//        else if(strncasecmp(message,"threads", 7) == 0){
//            LogOut(  "threads, ����δ����\n"); 
//        }
//        else if(strncasecmp(message,"drawmoves", 9) == 0){
//            LogOut(   "drawmoves, ����δ����\n"); 
//        }
//        else if(strncasecmp(message,"repetition", 10) == 0){
//            LogOut(   "repetition, ����δ����\n"); 
//        }
//        else if(strncasecmp(message,"pruning", 7) == 0){
//
//            message += 8;
//            char* p  = strstr(message,"default");           
//            if(p != 0){
//                p       += 8;  
//                StringCbPrintf(cps->UCCI_pruning,32, "%s\n", p);
//                LogOut("����ü��̶�: ");
//                LogOut(cps->UCCI_pruning);
//            }
//        }
//        else if(strncasecmp(message,"knowledge", 9) == 0){
//            message += 10;
//            char* p  = strstr(message,"default");
//            if(p != 0){
//                p       += 8;  
//                StringCbPrintf(cps->UCCI_knowledge,32, "%s\n", p);
//                LogOut("�����趨֪ʶ��С: ");
//                LogOut(cps->UCCI_knowledge);
//            }
//        }
//        else if(strncasecmp(message,"selectivity",11) == 0){
//            message += 12;
//            char* p  = strstr(message,"default");
//
//            if(p != 0){
//                p       += 8;  
//                StringCbPrintf(cps->UCCI_selectivity,32, "%s\n", p);
//                LogOut("����ѡ����(�����)ϵ��: ");
//                LogOut(cps->UCCI_selectivity);
//            }
//        }
//        else if(strncasecmp(message,"style",5) == 0){
//            LogOut(   "style, ����δ����\n"); 
//        }
//        else if(strncasecmp(message,"loadbook",8) == 0){
//            //LogOut(ColorChannel1,   "loadbook, ����δ����\n",false); 
//        }
//        else if(strncasecmp(message,"clearhash",9) == 0){
//            LogOut(   "clearhash, ����δ����\n"); 
//        }
//        else if(strncasecmp(message,"dualtime",8) == 0){
//
//            message += 9;
//            char* p  = strstr(message,"default");            
//            if(p != 0){
//                p       += 8;  
//                if(strncasecmp(p,"true",4) == 0){
//                    cps->UCCI_dualtime = true;
//                }
//                else{
//                    cps->UCCI_dualtime = false;
//                }              
//                LogOut("����˫ʱ�޹���: ");
//                if(cps->UCCI_dualtime){
//                    LogOut("�ѿ���\n");
//                }
//                else{
//                    LogOut("�ѹر�\n");
//                }
//            }
//            else{
//                cps->UCCI_dualtime = false;
//                LogOut("����˫ʱ�޹���: "); 
//                LogOut("�ѹر�\n");                
//            }
//        }
//        else if(strncasecmp(message,"newgame", 7) == 0){
//            //message +=8;
//            LogOut( message);
//            LogOut( "\n");
//        }
//        else{     //δʶ���ѡ��
//            LogOut("���治��ʶ�����淢�͵�ѡ��: ");
//            LogOut(message);
//        }
//    }
//    //*******************************************************************************
//    else if(strncasecmp(message,"ucciok", 6) == 0){
//        //if(cps->UCCI_initDone == FALSE){
//		if(cps->cps_stat == Cps_InLoading){
//			PostMessage(cps->loadWin,WM_USER_YqLoad_OK,0,(LPARAM)cps);  //���������ڴ��ڷ��ͳ�ʼ���ɹ�����Ϣ
//        }  
//    }
//    //*******************************************************************************
//    else if(strncasecmp(message,"readyok", 7) == 0){
//        //����״̬��˼��״̬�ķ������������洦�ھ���״̬(����������ָ��)��
//        LogOut(cps->UCCI_name);        //�����������
//        LogOut("�������ڽ���ָ��״̬!\n");
//    }
//    //*******************************************************************************
//    else if(strncasecmp(message,"info", 4) == 0){
//        //˼��״̬�ķ�������ʾ����˼����Ϣ��ͨ�������¼�����Ϣ�� 
//        //(1) nodes <�������Ľ����> time <�ѻ��ѵ�ʱ��>��˼����Ϣ�и�����ʱ��ͨ���Ժ���Ϊ��λ���������ʱ���������������ٶ�(NPSֵ)����λ��KNPS�� 
//        //(2) depth <��ǰ�������> [score <��ֵ> pv <��Ҫ����>]���������˼��������ȼ���˼��·�ߺͺû���
//        //ĿǰUCCI���桶������ʦ��ֻ��������Ϣ����������������ʼ�����£�
//        //��������ʦ���յ�����ķ�����info depth 6 score 4 pv b0c2 b9c7 c3c4 h9i7 c2d4 h7e7��
//        //��ô������Ӧ�����������ȣ�6����ֵ��4����Ҫ��������˽��� ������ ���߽�һ ������ ���߽��� �ڣ�ƽ������
//        //��ֵͨ����һ������(�����)Ϊ100�ּǣ�������Ϣ˵����ʱ��ǰҪ�ߵ�һ��ռ���൱��0.04�����ӵ����ơ� 
//        //(3) currmove <��ǰ�����ŷ�>�������������˼�����ŷ��� 
//        char *movestr;
//        message += 5;
//        if(false){
//        }
//        else if(strncasecmp(message,"log",3) == 0){
//            LogOut(cps->UCCI_name);        //�����������
//            LogOut(message+4);
//            LogOut("\n");
//        }
//        else if(movestr = strstr(message,"pv")){        //���淴���Ĺؼ�·��
//            LogOut(cps->UCCI_name);        //�����������
//            //DispStatS(message);               //����Ϣ��ʾ��״̬����
//			//SendMessage(hStatusBar,SB_SETTEXT,0,(LPARAM)"�����ϸ�!");
//            LogOut(message);
//            LogOut("\n");
//
//            //����MPV
//
//            //movestr += 3;          
//            //uint8 B256[256];
//            //memcpy(B256,DIS.pos.b256,256);
//            //int len = (int)strlen(movestr);
//            //int from;
//            //int to;     
//            //int chess;
//            //while(len >= 4){  
//            //    from = (movestr[0] - 'a' + 3) + (('9' - movestr[1] + 3) * 16);
//            //    to   = (movestr[2] - 'a' + 3) + (('9' - movestr[3] + 3) * 16);  
//            //    if(from < 0x32 || from > 0xcb || to < 0x32 || to > 0xcb){
//            //        LogOut(ColorSShout,"����˼��·���д�: ",false);
//            //        LogOut(ColorSShout,message,true);
//            //        break;
//            //    }
//            //    chess  = B256[from];
//            //    B256[from] = EMPTY;
//            //    B256[to]   = chess;                
//            //    movestr += 5;
//            //    len -= 5;
//            //} 
//            //char fen[256];
//            ////if(WhiteOnMove(DIS.currentMove+num)){
//            //if(IsBlack(chess)){
//            //    position_to_fen_by_b256(B256,WHITE,fen);
//            //}
//            //else{
//            //    position_to_fen_by_b256(B256,BLACK,fen);
//            //}
//            //StringCbPrintf(buf,512,"PV End fen %s\n",fen);            
//            //BoardDisplay(B256,buf); 
//        }
//        else {
//            //LogOut(ColorChannel1,message,true);
//            //LogOut(ColorNormal,"\n",true);
//            //DispStatS(message);               //����Ϣ��ʾ��״̬����
//        }
//        
//    }
//    //*******************************************************************************
//    else if(strncasecmp(message,"bye", 3) == 0){
//        //���յ�quitָ���ķ���������������˳���תǰ��׼��������
//        // ֪ͨ���棬���潫��˲�������˳���ת�������յ���ָ���
//        // ͨ��ֻ��Ҫ�ȴ�1���룬���ɹر��������ͨ����
//
//        //if(cps->twoMachinesColor[0] == 'w'){
//        //    LogOut(ColorSeek,    "�췽�����ѳɹ��˳�!\n",false);
//        //}
//        //else{
//        //    LogOut(ColorChannel1,"�ڷ������ѳɹ��˳�!\n",false);           
//        //}
//        //if(cps->UCCI_which == 1){           //���ǵ�һ������
//        //    SendMessage(hwndToolBar,TB_ENABLEBUTTON,IDT_COM_RED,0);    
//        //}
//        //else{
//        //    SendMessage(hwndToolBar,TB_ENABLEBUTTON,IDT_COM_BLUE,0);
//        //}
//        
//        //cps->UCCI_initDone  = FALSE;
//
//		//LogOut(cps->UCCI_name);        //�����������
//  //      LogOut("�����ѳɹ��˳�!\n\n");
//    }
//    //*******************************************************************************
//    else if(strncasecmp(message,"copyprotection", 14) == 0){
//        LogOut(cps->UCCI_name);        //�����������
//        message +=15;
//        LogOut("�����Ȩ��֤: ");
//
//        if(strncasecmp(message,"ok",2) == 0){
//            LogOut( "��ͨ��\n"); 
//        }
//        else{
//            LogOut( "δͨ��\n"); 
//        }
//    }   
//    //*******************************************************************************
//    else {  //����������������Ϣ
//        //if(cps->twoMachinesColor[0] == 'w'){
//        //    LogOut(ColorSeek,     "�췽����δʶ��ָ��\n", false);            
//        //}
//        //else{
//        //    LogOut(ColorChannel1, "�ڷ�����δʶ��ָ��\n", false);            
//        //}
//
//        LogOut(cps->UCCI_name);        //�����������
//        LogOut("����δʶ��ָ��\n"); 
//        LogOut( message);
//        LogOut( "\n");
//    }
	LogOut(_T("����δʶ��ָ��\n"));
	LogOut(Tinfo);
}

