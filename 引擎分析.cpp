
#include "stdafx.h"
#include "GGchess.h"
#include "chess.h"
#include "data.h"

//�����������ǰ�ľ���
BOOL LetYqAnalizeCurPos(dispboard_t* pDis){

	ChessProgramState *cps = &pDis->first; 

	if(cps->cps_stat != Cps_Waiting){
		SendToProgram(L"stop\n", cps);		
		Sleep(150);	
		pDis->gameMode = AnalyzeMode;
	}

	cps = &pDis->first; 	

	if(cps == NULL){

		LogOut(_T("\n**********************\n�����ܽ������ģʽ,����û�м����κγɹ�����!\n**********************"));
		
		return FALSE;
	}

	//������˼����ǰ����

	if(cps->playWhat != pDis->pos->side){
		cps->playWhat = pDis->pos->side;
	}

	SendProgramGo(cps,Cps_Analyse,L"none");

	return TRUE;
}
//
//int
//AnalyzeModeEvent()
//{
//	char buf[MSG_SIZ];
//
//	if (!first.analysisSupport) {
//		snprintf(buf, sizeof(buf), _("%s does not support analysis"), first.tidy);
//		DisplayError(buf, 0);
//		return 0;
//	}
//	/* [DM] icsEngineAnalyze [HGM] This is horrible code; reverse the gameMode and isEngineAnalyze tests! */
//	if (appData.icsActive) {
//		if (gameMode != IcsObserving) {
//			snprintf(buf, MSG_SIZ, _("You are not observing a game"));
//			DisplayError(buf, 0);
//			/* secure check */
//			if (appData.icsEngineAnalyze) {
//				if (appData.debugMode)
//					fprintf(debugFP, "Found unexpected active ICS engine analyze \n");
//				ExitAnalyzeMode();
//				ModeHighlight();
//			}
//			return 0;
//		}
//		/* if enable, user wants to disable icsEngineAnalyze */
//		if (appData.icsEngineAnalyze) {
//			ExitAnalyzeMode();
//			ModeHighlight();
//			return 0;
//		}
//		appData.icsEngineAnalyze = TRUE;
//		if (appData.debugMode)
//			fprintf(debugFP, "ICS engine analyze starting... \n");
//	}
//
//	if (gameMode == AnalyzeMode) { ToggleSecond(); return 0; }
//	if (appData.noChessProgram || gameMode == AnalyzeMode)
//		return 0;
//
//	if (gameMode != AnalyzeFile) {
//		if (!appData.icsEngineAnalyze) {
//			EditGameEvent();
//			if (gameMode != EditGame) return 0;
//		}
//		if (!appData.showThinking) ToggleShowThinking();
//		ResurrectChessProgram();
//		SendToProgram("analyze\n", &first);
//		first.analyzing = TRUE;
//		/*first.maybeThinking = TRUE;*/
//		first.maybeThinking = FALSE; /* avoid killing GNU Chess */
//		EngineOutputPopUp();
//	}
//	if (!appData.icsEngineAnalyze) gameMode = AnalyzeMode;
//	pausing = FALSE;
//	ModeHighlight();
//	SetGameInfo();
//
//	StartAnalysisClock();
//	GetTimeMark(&lastNodeCountTime);
//	lastNodeCount = 0;
//	return 1;
//}

BOOL AnalizeEvent(dispboard_t* pDis){

	 //(appData.noche)

	if (pDis->gameMode != AnalyzeMode){   //��ǰ���Ƿ���ģʽ

		if(LetYqAnalizeCurPos(pDis)){

			if((SendMessage(hwndToolBar,TB_GETSTATE,IDT_ANALIZE_FUN,0) & TBSTATE_CHECKED) == FALSE){
				//�ٽ���ť����
				SendMessage(hwndToolBar,TB_CHECKBUTTON,IDT_ANALIZE_FUN, 1);
			}

			pDis->gameMode = AnalyzeMode;

			LogOut(_T("\n**********************\n����ǰ�ѳɹ��������ģʽ\n**********************"));

			//�������ɲ�����
			SendMessage(hwndToolBar,TB_ENABLEBUTTON,IDT_HUIQI,	0);
			

			////��ֹͣ��Ϊ������
			//SendMessage(hwndToolBar,TB_ENABLEBUTTON,IDT_Stop,	0);			

			//����̨����, ����ɲ�����
			pDis->mustPonder =  FALSE;
			SendMessage(hwndToolBar,TB_ENABLEBUTTON,IDT_PONDER,	0); 
	
			return TRUE;

		}
	}

	//-------------------------------------------------------------------------------------------------

	//else{
	pDis->gameMode = BeginningOfGame;

	//�ٽ���ť����
	SendMessage(hwndToolBar,TB_CHECKBUTTON,IDT_ANALIZE_FUN, 0);

	//�������ɿ���
	SendMessage(hwndToolBar,TB_ENABLEBUTTON,IDT_HUIQI,	1);


	////��ֹͣ��Ϊ����
	//SendMessage(hwndToolBar,TB_ENABLEBUTTON,IDT_Stop,	1);			

	//����̨��ɿ���
	pDis->mustPonder =  FALSE;
	SendMessage(hwndToolBar,TB_ENABLEBUTTON,IDT_PONDER,	1); 


	//���ԭ�Ⱥ�̨��ѹ�µ�,��Ҫ�ָ�һ��
	if((SendMessage(hwndToolBar,TB_GETSTATE,IDT_PONDER,0) & TBSTATE_CHECKED) == TRUE){
		pDis->mustPonder =  TRUE;
	}

	ChessProgramState *cps = &pDis->first; 

	if(cps->cps_stat != Cps_Waiting){
		SendToProgram(L"stop\n", cps);
		Sleep(100);
		SendToProgram(L"stop\n", cps);
		Sleep(100);
	}


	if((SendMessage(hwndToolBar,TB_GETSTATE,IDT_ANALIZE_FUN,0) & TBSTATE_CHECKED) == TRUE){
		//�ٽ���ť����
		SendMessage(hwndToolBar,TB_CHECKBUTTON,IDT_ANALIZE_FUN, 0);
	}

	pDis->gameMode = BeginningOfGame;

	LogOut(_T("\n**********************\n����ǰ���˳��˷���ģʽ\n**********************"));

	return TRUE;
}

