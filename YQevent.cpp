#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"

void	//���������Ƿ�׼��������
TwoMachinesEventIfReady (dispboard_t* DIS){
    //if (pDis->first.lastPing != pDis->first.lastPong) {
    //    DisplayMessage(DIS,"", "Waiting for first chess program");
    //    ScheduleDelayedEvent(DIS,TwoMachinesEventIfReady, 1000);
    //    return;
    //}
    //if (pDis->second.lastPing != pDis->second.lastPong) {
    //    DisplayMessage(DIS,"", "Waiting for second chess program");
    //    ScheduleDelayedEvent(DIS,TwoMachinesEventIfReady, 1000);
    //    return;
    //}
    //ThawUI();
    //TwoMachinesEvent();
}


void
SetWhiteToPlayEvent(dispboard_t* DIS){
    //if (pDis->gameMode == EditPosition) {
    //    //DIS.blackPlaysFirst = FALSE;
    //    DisplayBothClocks(DIS);	/* works because currentMove is 0 */
    //} 
    //else if (DIS.gameMode == IcsExamining) {
    //    //SendToICS(DIS.ics_prefix);
    //    SendToICS("tomove white\n");
    //}
}

void
SetBlackToPlayEvent(){
    //if (DIS.gameMode == EditPosition) {
    //    //DIS.blackPlaysFirst = TRUE;
    //    //DIS.currentMove = 1;	/* kludge */
    //    DisplayBothClocks();
    //    //DIS.currentMove = 0;
    //} 
    //else if (DIS.gameMode == IcsExamining) {
    //    SendToICS(DIS.ics_prefix);
    //    SendToICS("tomove black\n");
    //}
}

//void SetGameModeByDisCps(void){
//        //if(now->playWhat != NEUTRAL && other->playWhat != NEUTRAL){
//    //    DIS.gameMode = TwoMachinesPlay;
//    //}
//    //else{
//    //    if(now->playWhat == BLACK){
//    //        DIS.gameMode = 
//    //    }
//    //}
//    if(DIS.first.playWhat != NEUTRAL && DIS.second.playWhat != NEUTRAL){
//        DIS.gameMode = TwoMachinesPlay;
//    }
//    else{
//        if(DIS.first.playWhat == WHITE || DIS.second.playWhat == WHITE){
//            DIS.gameMode = MachinePlaysWhite;
//        }
//        else if(DIS.first.playWhat == BLACK || DIS.second.playWhat == BLACK){
//            DIS.gameMode = MachinePlaysBlack;
//        }
//        else{
//            DIS.gameMode = EditGame;
//        }
//    }
//}

void        //�趨CPS���Ƿ�
SetCpsPlayWhat(ChessProgramState* now){

    dispboard_t* pDis = OBS[now->table];

    now->playWhat = NEUTRAL;
    //������CPS, ��,��,ICS,
    if(pDis->ics.playWhat == NEUTRAL){      //ICS��û�趨����
        //if(now->other->playWhat == WHITE){
        //}
        //else if(now->other->playWhat == BLACK){
        //}
        switch(now->other->playWhat){
            case WHITE:
                now->playWhat = BLACK;
                break;
            case BLACK:
                now->playWhat = WHITE;
                break;
            default:
                now->playWhat = pDis->pos->side;
                break;
        }
    }
    else{                                   //�Ѿ�ICS��¼��,����ȷ����CPS���߷�
        if(pDis->ics.playWhat == WHITE){
            if(now->other->playWhat != WHITE){
                now->playWhat = WHITE;
            }
        }
        else if(pDis->ics.playWhat == BLACK){
            if(now->other->playWhat == BLACK){
                now->playWhat = BLACK;
            }
        }
    }

    //
    //LogOut(
    LogOut(now->UCCI_path);
    LogOut(now->UCCI_file);
    LogOut(now->UCCI_name);
    switch(now->playWhat){
        case WHITE:
            LogOut("�ߺ췽\n");
            break;
        case BLACK:
            LogOut("�ߺڷ�\n");
            break;
        default:
            LogOut("����ȷ�����Ƿ�,��ȷ�ϲ���!\n");
            break;
    }

    pDis->gameMode = EditGame;

    //�趨��ǰ��GAMEMODE
    if(pDis->ics.playWhat != NEUTRAL){
    }
    else{
        if(pDis->first.playWhat == NEUTRAL){
            if(pDis->second.playWhat == BLACK){
                pDis->gameMode = MachinePlaysBlack;
            }
            else if(pDis->second.playWhat == WHITE){
                pDis->gameMode = MachinePlaysWhite;
            }
        }
        else if(pDis->second.playWhat == NEUTRAL){
            if(pDis->first.playWhat == BLACK){
                pDis->gameMode = MachinePlaysBlack;
            }
            else if(pDis->first.playWhat == WHITE){
                pDis->gameMode = MachinePlaysWhite;
            }
        }
        else{
            pDis->gameMode = TwoMachinesPlay;
        }
    }

    //if(now->playWhat == NEUTRAL){       //�ٿ�һ���ܲ�������
    //    return;
    //}
}

//void //������ܲ�����һ��
//IsComputerCanGo(ChessProgramState* now){
        
    //char buf[MSG_SIZ];

    

    //ChessProgramState* other;

    //if(now->UCCI_initDone == 0){
    //    LogOut("���ܼ�������,��������������\n");
    //    if(now->UCCI_which == 1){
    //        SendMessage(hwndToolBar,TB_CHECKBUTTON,IDT_COM_RED, 0);
    //    }
    //    else{
    //        SendMessage(hwndToolBar,TB_CHECKBUTTON,IDT_COM_BLUE, 0);
    //    }  
    //    return;
    //}

    //if(now == &DIS.first){
    //    other = &DIS.second;
    //}
    //else{
    //    other = &DIS.first;
    //}

    //if(now->playWhat == NEUTRAL){
    //    //SendMessage(hwndToolBar,TB_CHECKBUTTON,IDT_COM_BLUE, 1);
    //    if(WhiteOnMove(DIS.currentMove)){           //���ں췽����
    //        if(other->playWhat == WHITE){ //��һ������Ҳ���˺���
    //            LogOut("��һ���������˺췽\n");        //�����������
    //            //���ý�����ȥ�İ�ť������
    //            if(now->UCCI_which == 1){
    //                SendMessage(hwndToolBar,TB_CHECKBUTTON,IDT_COM_RED, 0);
    //            }
    //            else{
    //                SendMessage(hwndToolBar,TB_CHECKBUTTON,IDT_COM_BLUE, 0);
    //            }                
    //            return;
    //        }
    //        else{
    //            now->playWhat  = WHITE;  
    //            //DIS.gameMode   = MachinePlaysWhite;
    //        }
    //    }
    //    else{
    //        if(other->playWhat == BLACK){
    //            LogOut("��һ���������˺ڷ�\n");        //�����������
    //            //���ý�����ȥ�İ�ť������
    //            if(now->UCCI_which == 1){
    //                SendMessage(hwndToolBar,TB_CHECKBUTTON,IDT_COM_RED, 0);
    //            }
    //            else{
    //                SendMessage(hwndToolBar,TB_CHECKBUTTON,IDT_COM_BLUE, 0);
    //            }
    //            return;
    //        }
    //        else{
    //            now->playWhat  = BLACK;  
    //            //DIS.gameMode   = MachinePlaysBlack;
    //        }
    //    }
    //    //now->working = true;
    //    LogOut(now->UCCI_name);
    //    LogOut("�Ѽ�������!\n");
    //}
    //else{
    //    //SendMessage(hwndToolBar,TB_CHECKBUTTON,IDT_COM_BLUE, 0);
    //    if(now->maybeThinking){                 //������������˼��
    //        SendToProgram("stop\n",now);
    //    }
    //    //now->working = false;
    //    now->playWhat = NEUTRAL;
    //    LogOut(now->UCCI_name);
    //    LogOut("::��ֹͣ����!\n");

    //    return;
    //}

    //if(now->playWhat != NEUTRAL && other->playWhat != NEUTRAL){
    //    DIS.gameMode = TwoMachinesPlay;
    //}
    //else{
    //    if(now->playWhat == BLACK){
    //        DIS.gameMode = 
    //    }
    //}
    //SetGameModeByDisCps();

    //if(now->working && other->working){
    //    DIS.gameMode = TwoMachinesPlay;
    //}

    //if (appData.noChessProgram || (DIS.gameMode == MachinePlaysWhite)){
    //    return;
    //}
    //if (DIS.gameMode == PlayFromGameFile || DIS.gameMode == TwoMachinesPlay  
    //    || DIS.gameMode == Training      || DIS.gameMode == AnalyzeMode      
    //    || DIS.gameMode == EndOfGame)
    //{
    //    EditGameEvent();
    //}

    //if (DIS.gameMode == EditPosition) {
    //    EditPositionDone();
    //}

    //if (!WhiteOnMove(DIS.currentMove)) {			//���ڲ��Ǻ���
    //    DisplayError("It is not White's turn", 0);
    //    return;
    //}

    //if (DIS.gameMode == AnalyzeMode || DIS.gameMode == AnalyzeFile){
    //    ExitAnalyzeMode();
    //}

    //if (DIS.gameMode == EditGame || DIS.gameMode == AnalyzeMode || DIS.gameMode == AnalyzeFile){
          //TruncateGame();
    //}

    //ResurrectChessProgram();	/* in case it isn't running */
    //DIS.gameMode	= MachinePlaysWhite;
    //DIS.pausing		= FALSE;
    //ModeHighlight();
    //SetGameInfo(); 
    
    //��ʾ���ڱ���, ��˭��˭����

    //StringCbPrintf(DIS.GGQJ.Rname,sizeof(DIS.GGQJ.Rname),"�Ѽ��û�"); 
    //StringCbPrintf(DIS.GGQJ.Bname,sizeof(DIS.GGQJ.Bname),"�Ѽ��û�"); 

    //if(now->playWhat == WHITE){
    //    StringCbPrintf(DIS.GGQJ.Rname, sizeof(DIS.GGQJ.Rname), now->UCCI_name);
    //}
    //else if(now->playWhat == BLACK){
    //    StringCbPrintf(DIS.GGQJ.Bname, sizeof(DIS.GGQJ.Bname), now->UCCI_name);
    //}

    //if(other->playWhat == WHITE){
    //    StringCbPrintf(DIS.GGQJ.Rname, sizeof(DIS.GGQJ.Rname), other->UCCI_name);
    //}
    //else if(other->playWhat == BLACK){
    //    StringCbPrintf(DIS.GGQJ.Bname, sizeof(DIS.GGQJ.Bname), other->UCCI_name);
    //}

    //StringCbPrintf(buf,MSG_SIZ,"%s vs. %s", DIS.GGQJ.Rname, DIS.GGQJ.Bname);
    //DisplayTitle(buf);				//���ڱ�����ʾһ��

    //FeedMovesToProgram(now,DIS.currentMove);  //���ͳ�ʼ���������

    //switch(now->ucci){
    //    case UCCI_UCCI:
    //        SendMoveToProgram(DIS.currentMove-1,now);
    //        SendProgramGo(now);
    //        break;
    //    case UCCI_QH:
    //        break;
    //    default:
    //        break;
    //}

    //now->maybeThinking = TRUE;
    //StartClocks();


    //SetMachineThinkingEnables();		//���²˵���
    //DIS.first.maybeThinking = TRUE;
    //StartClocks();
    //if (appData.autoFlipView && !DIS.flipView) {
    //    DIS.flipView = !DIS.flipView;
    //    DrawPosition(false, NULL);
    //}
//}

void MachinePlayEvent(ChessProgramState* now){
    

    //DIS.first.playWhat    = NEUTRAL;
    //DIS.second.playWhat   = NEUTRAL;

    //LoadChessProgramState(&DIS.second,hwndMain);

   //if(SendMessage(hwndToolBar,TB_ISBUTTONCHECKED,
   //             IDT_IMPORT,0)){//�������尴ť������

    //int but = (now == &DIS.first?IDT_COM_RED:IDT_COM_BLUE);

    //if(SendMessage(hwndToolBar,TB_CHECKBUTTON,but,0)){   //��������水ť������

       //SetDlgButton(

//**************************************************************
        //if(now->UCCI_initDone == FALSE){        //�����ǰ�����滹û����,�ͼ�����
        //    //�Ƚ����水ť����������ɹ��ٰ���
        //    if(now == &DIS.first){
        //        SendMessage(hwndToolBar,TB_CHECKBUTTON,IDT_COM_RED,0);
        //    }
        //    else{
        //        SendMessage(hwndToolBar,TB_CHECKBUTTON,IDT_COM_BLUE,0);
        //    }
        //    LoadChessProgramState(now,hwndMain);
        //    return;
        //}
        //else if(now->yqOldId != now->yqID){ //�����Ǹ���������, �ý���ǰ��ж�أ��ټ��ص�ǰ��
        //    now->UCCI_initDone = FALSE;
        //    //�Ƚ����水ť����������ɹ��ٰ���
        //    if(now == &DIS.first){
        //        SendMessage(hwndToolBar,TB_CHECKBUTTON,IDT_COM_RED,0);
        //    }
        //    else{
        //        SendMessage(hwndToolBar,TB_CHECKBUTTON,IDT_COM_BLUE,0);
        //    }
        //    LoadChessProgramState(now,hwndMain);
        //    return;
        //}


        //if(now->Already_Send_Initinfo == FALSE){
        //    SendControlParameterToCps(now);
        //    now->Already_Send_Initinfo = TRUE;
        //}

        ////��ǰ�����Ѽ�����

        //SetCpsPlayWhat(now);

        ////�õ�����ʱ��
        //GetTimeSetInfoFromCps(now);

        //if(now->playWhat == DIS.pos.side){
        //    //
        //    SendProgramGo(now);  



        //}
    //**************************************************************
             

    //}
    //else{                                           //��������水ť������
    //    if(now->maybeThinking){
    //        SendToProgram("stop\n", now);
    //    }

    //    Sleep(100);
    //    now->maybeThinking  = FALSE;
    //    now->playWhat       = NEUTRAL;

    //}


}

    ////����ť������

    //SendMessage(hwndToolBar,TB_CHECKBUTTON,IDT_COM_RED, 0);
    //SendMessage(hwndToolBar,TB_CHECKBUTTON,IDT_COM_BLUE,0);

void	//�����ߺ췽�¼�, �����ǰ����˵�һ������
MachineWhiteEvent(void){

    //char buf[MSG_SIZ];
    //ChessProgramState* first  = &DIS.first;

    //char buf[MSG_SIZ];
    //ChessProgramState* cps = &DIS.first;


    //if (appData.noChessProgram || (DIS.gameMode == MachinePlaysWhite)){
    //    return;
    //}
    //if (DIS.gameMode == PlayFromGameFile || DIS.gameMode == TwoMachinesPlay  
    //    || DIS.gameMode == Training      || DIS.gameMode == AnalyzeMode      
    //    || DIS.gameMode == EndOfGame)
    //{
    //    EditGameEvent();
    //}

    //if (DIS.gameMode == EditPosition) {
    //    EditPositionDone();
    //}

    //if (!WhiteOnMove(DIS.currentMove)) {			//���ڲ��Ǻ���
    //    DisplayError("It is not White's turn", 0);
    //    return;
    //}

    //if (DIS.gameMode == AnalyzeMode || DIS.gameMode == AnalyzeFile){
    //    ExitAnalyzeMode();
    //}

    //if (DIS.gameMode == EditGame || DIS.gameMode == AnalyzeMode || DIS.gameMode == AnalyzeFile){
    //    TruncateGame();
    //}

    //ResurrectChessProgram();	/* in case it isn't running */
    //DIS.gameMode	= MachinePlaysWhite;
    //DIS.pausing		= FALSE;
    //ModeHighlight();
    //SetGameInfo();

    //StringCbPrintf(buf,MSG_SIZ,"%s vs. %s", DIS.GGQJ.Rname, DIS.GGQJ.Bname);
    //DisplayTitle(buf);				//���ڱ�����ʾһ��



    ////FeedMovesToProgram(cps,DIS.currentMove);  //���ͳ�ʼ���������

    //switch(DIS.first.ucci){
    //    case UCCI_UCCI:

    //        if(cps->isBaoGan){	//���ɼ�ʱ
    //            StringCbPrintf(buf,MSG_SIZ,"go time %d increment %d depth %d\n", 
    //                cps->timePerStep,cps->addTimePerStep,cps->searchDepth);
    //            SendToProgram(buf, cps);
    //        }
    //        else{
    //            Sleep(10);
    //            StringCbPrintf(buf,MSG_SIZ,"go depth %d\n",cps->searchDepth);
    //            SendToProgram(buf, cps);
    //        }
    //        break;
    //    case UCCI_QH:
    //        SendToProgram("AI\n", cps);	
    //        break;
    //    case UCCI_DIS:
    //        if (DIS.first.sendName) {
    //            //sprintf(buf, "name %s\n", DIS.gameInfo.black);
    //            StringCbPrintf(buf,MSG_SIZ,"name %s\n", DIS.GGQJ.Bname);
    //            SendToProgram(buf, &DIS.first);
    //        }
    //        if (DIS.first.sendTime) {
    //            if (DIS.first.useColors) {
    //                SendToProgram("black\n", &DIS.first); /*gnu kludge*/
    //            }
    //            SendTimeRemaining(&DIS.first, TRUE);
    //        }
    //        if (DIS.first.useColors) {
    //            SendToProgram("white\ngo\n", &DIS.first);
    //        } 
    //        else {
    //            SendToProgram("go\n", &DIS.first);	
    //        }
    //        break;
    //    default:
    //        break;
    //}


    //SetMachineThinkingEnables();		//���²˵���
    //DIS.first.maybeThinking = TRUE;
    //StartClocks();
    //if (appData.autoFlipView && !DIS.flipView) {
    //    DIS.flipView = !DIS.flipView;
    //    DrawPosition(false, NULL);
    //}
}

void
MachineBlackEvent(){
    //char buf[MSG_SIZ];
    //ChessProgramState* cps = &DIS.first;

    //if (appData.noChessProgram || (DIS.gameMode == MachinePlaysBlack)){
    //    return;
    //}


    //if (	DIS.gameMode == PlayFromGameFile || DIS.gameMode == TwoMachinesPlay  
    //    || 	DIS.gameMode == Training         || DIS.gameMode == AnalyzeMode     
    //    || 	DIS.gameMode == EndOfGame)
    //{
    //    EditGameEvent();
    //}

    //if (DIS.gameMode == EditPosition) { 
    //    EditPositionDone();
    //}

    //if (WhiteOnMove(DIS.currentMove)) {
    //    DisplayError("It is not Black's turn", 0);
    //    return;
    //}

    //if (DIS.gameMode == AnalyzeMode || DIS.gameMode == AnalyzeFile)
    //    ExitAnalyzeMode();

    //if (DIS.gameMode == EditGame || DIS.gameMode == AnalyzeMode || 
    //    DIS.gameMode == AnalyzeFile)
    //    TruncateGame();

    //ResurrectChessProgram();	/* in case it isn't running */
    //DIS.gameMode = MachinePlaysBlack;
    //DIS.pausing = FALSE;
    //ModeHighlight();
    //SetGameInfo();	
    //StringCbPrintf(buf,MSG_SIZ,"%s vs. %s", DIS.GGQJ.Rname, DIS.GGQJ.Bname);
    //DisplayTitle(buf);


    ////if (DIS.first.useColors) {
    ////	SendToProgram("black\ngo\n", &DIS.first);
    ////} 
    ////else {
    ////	SendToProgram("go\n", &DIS.first);
    ////}
    ////FeedMovesToProgram(cps,DIS.currentMove);  //���ͳ�ʼ���������

    //switch(cps->ucci){
    //    case UCCI_UCCI:
    //        if(cps->isBaoGan){	//���ɼ�ʱ
    //            StringCbPrintf(buf,MSG_SIZ,"go time %d increment %d depth %d\n", 
    //                cps->timePerStep,cps->addTimePerStep,cps->searchDepth);
    //            SendToProgram(buf, cps);
    //        }
    //        else{
    //            StringCbPrintf(buf,MSG_SIZ,"go depth %d\n",cps->searchDepth);
    //            SendToProgram(buf, cps);
    //        }
    //        break;			
    //    case UCCI_QH:
    //        SendToProgram("AI\n",cps);	
    //        break;
    //    case UCCI_DIS:
    //        if (cps->sendName) {		
    //            StringCbPrintf(buf,MSG_SIZ,"name %s\n", DIS.GGQJ.Rname);
    //            SendToProgram(buf, &DIS.first);
    //        }
    //        if (cps->sendTime) {
    //            if (cps->useColors) {
    //                SendToProgram("white\n", cps); /*gnu kludge*/
    //            }
    //            SendTimeRemaining(cps, FALSE);
    //        }
    //        break;
    //    default:
    //        break;
    //}

    //SetMachineThinkingEnables();
    //DIS.first.maybeThinking = TRUE;
    //StartClocks();

    //if (appData.autoFlipView && DIS.flipView) {
    //    DIS.flipView = !DIS.flipView;
    //    DrawPosition(false, NULL);
    //}
}



void      //˫�����ս�¼�
TwoMachinesEvent (void){
    //int i;
    //char buf[MSG_SIZ];
    //ChessProgramState *onmove;

    //if (appData.noChessProgram){
    //    return;
    //}

    //switch (DIS.gameMode) {
    //  case TwoMachinesPlay:
    //      return;
    //  case MachinePlaysWhite:
    //  case MachinePlaysBlack:
    //      if (WhiteOnMove(DIS.forwardMostMove) == (DIS.gameMode == MachinePlaysWhite)) {
    //          DisplayError("Wait until your turn,\nor select Move Now", 0);
    //          return;
    //      }
    //      /* fall through */
    //  case BeginningOfGame:
    //  case PlayFromGameFile:
    //  case EndOfGame:
    //      EditGameEvent();
    //      if (DIS.gameMode != EditGame){
    //          return;
    //      }
    //      break;
    //  case EditPosition:
    //      EditPositionDone();
    //      break;
    //  case AnalyzeMode:
    //  case AnalyzeFile:
    //      ExitAnalyzeMode();
    //      break;
    //  case EditGame:
    //  default:
    //      break;
    //}

    //DIS.forwardMostMove = DIS.currentMove;
    //ResurrectChessProgram();	/* �����һ������û�п�ʼ�Ļ� in case first program isn't running */

    //if (DIS.second.pr == NULL) {
    //    StartChessProgram(&DIS.second);
    //    //if (DIS.second.protocolVersion == 1) {
    //    //	TwoMachinesEventIfReady();
    //    //} 
    //    //else {
    //    /* kludge: allow timeout for initial "feature" command */
    //    FreezeUI();
    //    DisplayMessage("", "Starting second chess program");
    //    ScheduleDelayedEvent(TwoMachinesEventIfReady, FEATURE_TIMEOUT);
    //    //}
    //    return;
    //}
    //DisplayMessage("", "");
    //InitChessProgram(&DIS.second);

    //switch(DIS.second.ucci){
    //    case UCCI_UCCI:
    //        break;
    //    case UCCI_QH:
    //        //SendToProgram("AI\n", &DIS.second);
    //        break;
    //    case UCCI_DIS:
    //        break;
    //    default:
    //        SendToProgram("force\n", &DIS.second);
    //        break;
    //}


    //if (DIS.startedFromSetupPosition) {
    //    SendBoard(&DIS.second, DIS.backwardMostMove);
    //}
    //for (i = DIS.backwardMostMove; i < DIS.forwardMostMove; i++) {
    //    SendMoveToProgram(i, &DIS.second);
    //}

    //DIS.gameMode = TwoMachinesPlay;
    //DIS.pausing = FALSE;
    //ModeHighlight();
    //SetGameInfo();
    //DisplayTwoMachinesTitle();
    //DIS.firstMove = TRUE;
    //if ((DIS.first.twoMachinesColor[0] == 'w') == WhiteOnMove(DIS.forwardMostMove)) {
    //    onmove = &DIS.first;
    //} 
    //else {
    //    onmove = &DIS.second;
    //}

    ////SendToProgram(DIS.first.computerString, &DIS.first);

    //if (DIS.first.sendName) {
    //    //sprintf(buf, "name %s\n", DIS.second.tidy);
    //    StringCbPrintf(buf,MSG_SIZ,"name %s\n", DIS.second.tidy);
    //    SendToProgram(buf, &DIS.first);
    //}

    ////SendToProgram(DIS.second.computerString, &DIS.second);

    //if (DIS.second.sendName) {
    //    //sprintf(buf, "name %s\n", DIS.first.tidy);
    //    StringCbPrintf(buf,MSG_SIZ,"name %s\n", DIS.first.tidy);
    //    SendToProgram(buf, &DIS.second);
    //}

    //if (!DIS.first.sendTime || !DIS.second.sendTime) {
    //    ResetClocks();
    //    DIS.timeRemaining[0][DIS.forwardMostMove] = DIS.whiteTimeRemaining;
    //    DIS.timeRemaining[1][DIS.forwardMostMove] = DIS.blackTimeRemaining;
    //}

    //if (onmove->sendTime) {
    //    if (onmove->useColors) {
    //        SendToProgram(onmove->other->twoMachinesColor, onmove); /*gnu kludge*/
    //    }
    //    SendTimeRemaining(onmove, WhiteOnMove(DIS.forwardMostMove));
    //}

    //if (onmove->useColors) {
    //    SendToProgram(onmove->twoMachinesColor, onmove);
    //}

    ///*SendToProgram("go\n", onmove);*/

    //switch(onmove->ucci){
    //    case UCCI_UCCI:
    //        //SendMoveToProgram("");
    //        StringCbPrintf(buf,MSG_SIZ,"go depth %d\n",onmove->searchDepth);			
    //        SendToProgram(buf, onmove);
    //        break;
    //    case UCCI_QH:
    //        SendToProgram("AI\n", onmove);
    //        break;
    //    case UCCI_DIS:
    //        break;
    //    default:
    //        SendToProgram("go\n", onmove);
    //        break;
    //}

    //onmove->maybeThinking = TRUE;
    //SetMachineThinkingEnables();

    //StartClocks();
}
