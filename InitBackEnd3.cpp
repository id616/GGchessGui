#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"

void		//��ʼ��������
InitBackEnd3 (dispboard_t *pDis){
    GameMode initialMode;
    TCHAR buf[MSG_SIZ];
    //int err;

    //InitChessProgram(&DIS.first);

    //if (appData.icsActive) {		//internet connect 
    //    //err = establish();
    //    //if (err != 0) {
    //    //    if (*appData.icsCommPort != NULLCHAR) {
    //    //        StringCbPrintf(buf,MSG_SIZ,	"Could not open comm port %s",  
    //    //            appData.icsCommPort);
    //    //    } 
    //    //    else {
    //    //        StringCbPrintf(buf,MSG_SIZ,	"Could not connect to host %s, port %s",  
    //    //            appData.icsHost, appData.icsPort);
    //    //    }
    //    //    DisplayFatalError(buf, err, 1);
    //    //    return;
    //    //}
    //    //SetICSMode();
    //    //DIS.telnetISR   = AddInputSource(DIS.icsPR, FALSE, read_from_ics, &DIS.telnetISR);
    //    //DIS.fromUserISR = AddInputSource(NoProc, FALSE, read_from_player, &DIS.fromUserISR);
    //} 
    //else if (pDis->noChessProgram) {
    //    SetNCPMode();    //û��computer chess mode
    //} 
    //else {
    //    SetGNUMode();
    //}

    //if (*appData.cmailGameName != NULLCHAR) {      //�����ʼ���ʽ�ĶԾ�
    //    SetCmailMode();
    //    OpenLoopback(&DIS.cmailPR);
    //    DIS.cmailISR =
    //        AddInputSource(DIS.cmailPR, FALSE, CmailSigHandlerCallBack, &DIS.cmailISR);
    //}

    ThawUI();
    //DisplayMessage(pDis,"", "");
    if (StrCaseCmp(pDis->initialMode, "") == 0) {
        initialMode = BeginningOfGame;
    } 
    //else if (StrCaseCmp(pDis->initialMode, "AnalyzeFile") == 0) {
    //    initialMode = AnalyzeFile;		  //�����ļ�
    //} 
    else if (StrCaseCmp(pDis->initialMode, "Analysis") == 0) {
        //initialMode = AnalyzeMode;		  //������ʽ
    } 
    else if (StrCaseCmp(pDis->initialMode, "MachineWhite") == 0) {
        initialMode = MachinePlaysWhite;  //����ִ��
    }
    else if (StrCaseCmp(pDis->initialMode, "MachineBlack") == 0) {
        initialMode = MachinePlaysBlack;  //����ִ��
    } 
    else if (StrCaseCmp(pDis->initialMode, "EditGame") == 0) {
        initialMode = EditGame;			  //�༭��Ϸ
    } 
    else if (StrCaseCmp(pDis->initialMode, "EditPosition") == 0) {
        initialMode = EditPosition;		  //�༭λ��
    } 
    else if (StrCaseCmp(pDis->initialMode, "Training") == 0) {
        initialMode = Training;			  //������ʽ
    } 
    else {		
        StringCbPrintf(buf,MSG_SIZ,	_T("Unknown initialMode %s"), pDis->initialMode);
		LogOut(buf);
        return;
    }

    if (pDis->matchMode) {    //�����Ի�����ʽ
        /* Set up machine vs. machine match */
        //if (pDis->noChessProgram) {
        //    DisplayFatalError("Can't have a match with no chess programs",0, 2);
        //    return;
        //}
        pDis->matchMode = TRUE;
        //pDis->DIS.matchGame = 1;
        //if (*appData.loadGameFile != NULLCHAR) { //���ϴα������Ϸ
        //    if (!LoadGameFromFile(appData.loadGameFile,appData.loadGameIndex,appData.loadGameFile, FALSE)) {
        //        DisplayFatalError("Bad game file", 0, 1);
        //        return;
        //    }
        //} 
        //else if (*appData.loadPositionFile != NULLCHAR) { //���ϴα���ľ���
        //    if (!LoadPositionFromFile(appData.loadPositionFile,appData.loadPositionIndex,
        //        appData.loadPositionFile)) {
        //            DisplayFatalError("Bad position file", 0, 1);
        //            return;
        //    }
        //}
        TwoMachinesEvent();
    } 
    //else if (*appData.cmailGameName != NULLCHAR) {
    //    /* Set up cmail mode */
    //    ReloadCmailMsgEvent(TRUE);
    //} 
    else {
        /* Set up other modes */
        //if (initialMode == AnalyzeFile) {
        //    //if (*appData.loadGameFile == NULLCHAR) {
        //    //    DisplayFatalError("AnalyzeFile mode requires a game file", 0, 1);
        //    //    return;
        //    //}
        //}
        //if (*appData.loadGameFile != NULLCHAR) {
        //    (void) LoadGameFromFile(appData.loadGameFile,
        //        appData.loadGameIndex,
        //        appData.loadGameFile, TRUE);
        //} 
        //else if (*appData.loadPositionFile != NULLCHAR) {
        //    (void) LoadPositionFromFile(appData.loadPositionFile,
        //        appData.loadPositionIndex,
        //        appData.loadPositionFile);
        //}
        //if (initialMode == AnalyzeMode) {
		if(false){
            //if (pDis->noChessProgram) {//����ģʽ��Ҫһ��һ������������
            //    DisplayFatalError("Analysis mode requires a chess engine", 0, 2);
            //    return;
            //}
            //if (appData.icsActive) {     //
            //    DisplayFatalError("Analysis mode does not work with ICS mode",0,2);
            //    return;
            //}
            //AnalyzeModeEvent(pDis);
        }
        //else if (initialMode == AnalyzeFile) {
        //    ShowThinkingEvent(pDis,TRUE);
        //    AnalyzeFileEvent(pDis);
        //    AnalysisPeriodicEvent(1);
        //} 
        else if (initialMode == MachinePlaysWhite) {
            //if (pDis->noChessProgram) {
            //    DisplayFatalError("MachineWhite mode requires a chess engine",    0, 2);
            //    return;
            //}
            //if (appData.icsActive) {
            //    DisplayFatalError("MachineWhite mode does not work with ICS mode",0, 2);
            //    return;
            //}
            //MachineWhiteEvent();
        } 
        else if (initialMode == MachinePlaysBlack) {
            //if (pDis->noChessProgram) {
            //    DisplayFatalError("MachineBlack mode requires a chess engine",0, 2);
            //    return;
            //}
            //if (appData.icsActive) {
            //    DisplayFatalError("MachineBlack mode does not work with ICS mode",0, 2);
            //    return;
            //}
            //MachineBlackEvent();
        } 
        else if (initialMode == EditGame) {
            EditGameEvent(pDis);
        } 
        else if (initialMode == EditPosition) {
            EditPositionEvent();
        } 
        else if (initialMode == Training) {
            //if (*appData.loadGameFile == NULLCHAR) {
            //    DisplayFatalError("Training mode requires a game file", 0, 2);
            //    return;
            //}
            TrainingEvent();
        }
    }
}
