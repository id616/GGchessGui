#include "stdafx.h"
#include <sys/timeb.h>
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"

//int
//StopClockTimer()
//{
//  if (clockTimerEvent == 0) return FALSE;
//  KillTimer(hwndMain, clockTimerEvent);
//  clockTimerEvent = 0;
//  return TRUE;
//}
int
StopClockTimer(dispboard_t* pDis){
	
	if (pDis->clockTimerEvent == 0){	
		return FALSE;
	}

    KillTimer(pDis->hwndThis, pDis->clockTimerEvent);

	pDis->clockTimerEvent = 0;

	return TRUE;
}

//DelayedEventCallback
//GetDelayedEvent()
//{
//  if (delayedTimerEvent) {
//    return delayedTimerCallback;
//  } else {
//    return NULL;
//  }
//}
DelayedEventCallback
GetDelayedEvent(dispboard_t* pDis){
  if (pDis->delayedTimerEvent) {
    return pDis->delayedTimerCallback;
  }
  else {
    return NULL;
  }
}
//void
//CancelDelayedEvent()
//{
//  if (delayedTimerEvent) {
//    KillTimer(hwndMain, delayedTimerEvent);
//    delayedTimerEvent = 0;
//  }
//}
void
CancelDelayedEvent(dispboard_t* pDis){
  if (pDis->delayedTimerEvent) {
    KillTimer(pDis->hwndThis, pDis->delayedTimerEvent);
    pDis->delayedTimerEvent = 0;
  }
}
//int
//StopLoadGameTimer()
//{
//  if (loadGameTimerEvent == 0) return FALSE;
//  KillTimer(hwndMain, loadGameTimerEvent);
//  loadGameTimerEvent = 0;
//  return TRUE;
//}
int
StopLoadGameTimer(dispboard_t* pDis){
	
	if (pDis->loadGameTimerEvent == 0){
		return FALSE;
	}

	KillTimer(pDis->hwndThis, pDis->loadGameTimerEvent);

	pDis->loadGameTimerEvent = 0;

	return TRUE;
}


//���������,������ʱ����һ������
void
ScheduleDelayedEvent(dispboard_t* pDis, DelayedEventCallback cb, long millisec){

	if (pDis->delayedTimerEvent != 0) {

#ifdef DEBUG_USE_DEBUG_FILE  
		fprintf(appData.debugFP, "ScheduleDelayedEvent: event already scheduled\n");
#endif

		KillTimer(pDis->hwndThis, pDis->delayedTimerEvent);
		pDis->delayedTimerEvent = 0;
		pDis->delayedTimerCallback(pDis);
	}
	pDis->delayedTimerCallback = cb;
	pDis->delayedTimerEvent = (int)SetTimer(pDis->hwndThis, (UINT) DELAYED_TIMER_ID,
		(UINT) millisec, NULL);
}
//VOID
//StartAnalysisClock()
//{
//  if (analysisTimerEvent) return;
//  analysisTimerEvent = SetTimer(hwndMain, (UINT) ANALYSIS_TIMER_ID,
//		                        (UINT) 2000, NULL);
//}
void
StartAnalysisClock(dispboard_t* pDis){
  if (pDis->analysisTimerEvent) return;
  pDis->analysisTimerEvent = (int)SetTimer(pDis->hwndThis, (UINT) ANALYSIS_TIMER_ID,
		                        (UINT) 2000, NULL);
}
//void
//StartLoadGameTimer(long millisec)
//{
//  loadGameTimerEvent = SetTimer(hwndMain, (UINT) LOAD_GAME_TIMER_ID,
//				(UINT) millisec, NULL);
//}
void
StartLoadGameTimer(dispboard_t* pDis, long millisec){
  pDis->loadGameTimerEvent = (int)SetTimer(pDis->hwndThis, (UINT) LOAD_GAME_TIMER_ID,
				(UINT) millisec, NULL);
}



void
DisplayAClock(dispboard_t* pDis, int fudge, int highlight, RECT *rect, char *color) {
	TCHAR buf[128];

	if(pDis->first.pDis == OBS[0]){			//�������ڵ�ʱ����ʾ
		if(color[0] == 'W'){			//Ҫ���º췽��ʱ����ʾ
			TimeString(pDis->TimeDisp[WHITE].RemainTime - fudge , buf);
			SetWindowText(GetDlgItem(TIME_MAIN,IDC_TIME_RED_TOTAL),buf);

			//GetDlgItem(TAB.dlgTab[DLOG],IDC_TIME_RED_TOTAL)

			TimeString(pDis->TimeDisp[WHITE].movetime, buf);
			//SetWindowText(TAB_R_TIME_STEP,buf);
			SetWindowText(GetDlgItem(TIME_MAIN,IDC_TIME_RED_STEP),buf);
		}
		else{							//Ҫ���ºڷ���ʱ����ʾ
			TimeString(pDis->TimeDisp[BLACK].RemainTime - fudge, buf);
			//SetWindowText(TAB_B_TIME_TOTAL,buf);
			SetWindowText(GetDlgItem(TIME_MAIN,IDC_TIME_BLUE_TOTAL),buf);

			TimeString(pDis->TimeDisp[BLACK].movetime, buf);
			//SetWindowText(TAB_B_TIME_STEP,buf);
			SetWindowText(GetDlgItem(TIME_MAIN,IDC_TIME_BLUE_STEP),buf);
		}
	}
	else{								//���Թ�����ʱ����ʾ
	}
}

 //��ʾ�췽��ʱ��

void
DisplayWhiteClock(dispboard_t *pDis, int fudge, int highlight){

	HDC hdc;
	hdc = GetDC(pDis->hwndThis);

	if(!IsIconic(pDis->hwndThis)){
		DisplayAClock(pDis, fudge, highlight, NULL, "White");
	}

	if(highlight && pDis->iconCurrent == appData.iconBlack){
		
		pDis->iconCurrent = appData.iconWhite;

		PostMessage(pDis->hwndThis, WM_SETICON, (WPARAM)TRUE, (LPARAM)pDis->iconCurrent);

		if(IsIconic(pDis->hwndThis)){
			DrawIcon(hdc,2,2,pDis->iconCurrent);
		}
	}

	ReleaseDC(pDis->hwndThis, hdc);


	if(pDis->first.pDis == OBS[0]){			//���ǵ�һ��
		PostMessage(TAB.tabMain,WM_SETICON, (WPARAM)TRUE, (LPARAM)pDis->iconCurrent);
	}
}

 
//��ʾ�ڷ���ʱ��
void             
DisplayBlackClock(dispboard_t *pDis, int fudge, int highlight){

	HDC hdc;
	hdc = GetDC(pDis->hwndThis);

	if(!IsIconic(pDis->hwndThis)){
		DisplayAClock(pDis, fudge, highlight, NULL, "Black");
	}

	if(highlight && pDis->iconCurrent == appData.iconWhite){

		pDis->iconCurrent = appData.iconBlack;

		PostMessage(pDis->hwndThis, WM_SETICON, (WPARAM)TRUE, (LPARAM)pDis->iconCurrent);

		if(IsIconic(pDis->hwndThis)){
			DrawIcon(hdc,2,2,pDis->iconCurrent);
		}
	}

	ReleaseDC(pDis->hwndThis, hdc);


	if(pDis->first.pDis == OBS[0]){			//���ǵ�һ��

		PostMessage(TAB.tabMain,WM_SETICON, (WPARAM)TRUE, (LPARAM)pDis->iconCurrent);
	}
}
//void
//StartClockTimer(long millisec)
//{
//  clockTimerEvent = SetTimer(hwndMain, (UINT) CLOCK_TIMER_ID,
//			     (UINT) millisec, NULL);
//}
void
StartClockTimer(dispboard_t* pDis, long millisec){  //��ʼ��ʱ
	pDis->clockTimerEvent 
        = (int)SetTimer(pDis->hwndThis, (UINT) CLOCK_TIMER_ID,(UINT) millisec, NULL);
}


void
TimeControlTagValue(char *buf){
    //char buf[MSG_SIZ];
    //if (!appData->clockMode) {
    //    StringCbCopy(buf,MSG_SIZ,"-");
    //} else if (DIS.movesPerSession > 0) {
    //    StringCbPrintf(buf,MSG_SIZ,"%d/%ld", DIS.movesPerSession, DIS.timeControl/1000);
    //} else if (DIS.timeIncrement == 0) {
    //    StringCbPrintf(buf,MSG_SIZ,"%ld", DIS.timeControl/1000);
    //} else {
    //    StringCbPrintf(buf,MSG_SIZ,"%ld+%ld", DIS.timeControl/1000, DIS.timeIncrement/1000);
    //}
    //return StrSave(buf);
}

/* Timekeeping seems to be a portability nightmare.  I think everyone
has ftime(), but I'm really not sure, so I'm including some ifdefs
to use other calls if you don't.  Clocks will be less accurate if
you have neither ftime nor gettimeofday.
*/

/* Get the current time as a TimeMark */
//void
//GetTimeMark(TimeMark *tm)
//
//{
////#define HAVE_FTIME
//
//#if HAVE_GETTIMEOFDAY
//
//    struct timeval timeVal;
//    struct timezone timeZone;
//
//    gettimeofday(&timeVal, &timeZone);
//    tm->sec = (long) timeVal.tv_sec; 
//    tm->ms = (int) (timeVal.tv_usec / 1000L);
//
//#else /*!HAVE_GETTIMEOFDAY*/
//#if HAVE_FTIME
//
////#include <sys/timeb.h>
//
//    struct _timeb timeB;
//
//    _ftime_s(&timeB);
//    tm->sec = (long) timeB.time;
//    tm->ms = (int) timeB.millitm;
//
//#else /*!HAVE_FTIME && !HAVE_GETTIMEOFDAY*/
//    tm->sec = (long) time(NULL);
//    tm->ms = 0;
//#endif
//#endif
//}
////////////////////////////////////////////////////////////////////////
/* Pause for `ms' milliseconds */
/* !! Ugh, this is a kludge. Fix it sometime. --tpm */
//void
//TimeDelay(ms)
//     long ms;
//{
//    TimeMark m1, m2;
//
//    GetTimeMark(&m1);
//    do {
//	GetTimeMark(&m2);
//    } while (SubtractTimeMarks(&m2, &m1) < ms);
//}
void
TimeDelay(long ms){
	int m1, m2;

	m1 = GetTickCount();

	do{
		m2 = GetTickCount();
	}while((m2-m1) < ms);
}
//void
//CheckTimeControl()
//{
//	if (!appData.clockMode || appData.icsActive ||
//		gameMode == PlayFromGameFile || forwardMostMove == 0) return;
//
//	if (timeIncrement >= 0) {
//		if (WhiteOnMove(forwardMostMove)) {
//			blackTimeRemaining += timeIncrement;
//		} else {
//			whiteTimeRemaining += timeIncrement;
//		}
//	}
//	/*
//	* add time to clocks when time control is achieved
//	*/
//	if (movesPerSession) {
//		switch ((forwardMostMove + 1) % (movesPerSession * 2)) {
//	  case 0:
//		  /* White made time control */
//		  whiteTimeRemaining += timeControl;
//		  break;
//	  case 1:
//		  /* Black made time control */
//		  blackTimeRemaining += timeControl;
//		  break;
//	  default:
//		  break;
//		}
//	}
//}

void
CheckTimeControl(dispboard_t* pDis){
	
	if(!pDis->clockMode || appData.icsActive 
		|| pDis->gameMode == PlayFromGameFile || pDis->pos->gply == 0){
		return;
	}

	TimeDisp_t *pt;

	if(LAST_DIS_SIDE(pDis) == WHITE){		//���һ���Ǻ���
		pt = &pDis->TimeDisp[BLACK];
	}
	else{
		pt = &pDis->TimeDisp[WHITE];
	}

	pt->RemainTime += pt->inc;

	if (pt->c2step == 0){
		pt->c2step = 1;
	}

	if(!pt->isBaoGan){
		int step = pDis->pos->gply / 2;

		if(step >= pt->c1step){			
		
			int n = (pDis->pos->gply + 1 - pt->c1step * 2) % (pt->c2step * 2);

			switch(n){
				case 0:
					pDis->TimeDisp[WHITE].RemainTime += pDis->TimeDisp[WHITE].c2time;					
					break;
				case 1:
					pDis->TimeDisp[BLACK].RemainTime += pDis->TimeDisp[BLACK].c2time;
					break;
				default:
					break;
			}

			//pt->StepTime = pt->RemainTime / pt->c2step ;

			//if(pt->StepTime > pt->SetStepTime){
			//	pt->StepTime = pt->SetStepTime;
			//}
		}
		else{
			//pt->StepTime = pt->c1time / pt->c1step;
			//if(pt->StepTime > pt->SetStepTime){
			//	pt->StepTime = pt->SetStepTime;
			//}
		}
	}
	else{	//��ǰ�ǰ��ɼ�ʱ
		//pt->StepTime = pt->RemainTime;
	}

	//��ʱ

	if(pt->SetStepTime == 0){
		pt->movetime = pt->RemainTime;
	}
	else{
		pt->movetime = pt->SetStepTime;
	}

}

//struct TimeDisp_t {
//    int Total;
//    int isBaoGan;           //���ǰ��ɾ��Ƿֶ�
//    int stepAdd;
//    int c1time;
//    int c1step;
//    int c2time;
//    int c2step;
//    int MaxStepTime;
//    int MaxDepth;
//	int remaining;      //ʣ�µ�ʱ��
//};

void GetTimeInfoFromCps(dispboard_t* pDis, TimeDisp_t* pTimeDisp, ChessProgramState * cps){
	
	//pTimeDisp->Total		= cps->timeBaoGan   * 60 * 1000;			    //���ɼ�ʱ
	//pTimeDisp->isBaoGan		= cps->timeIsBaoGan;

	pTimeDisp->inc          = cps->timePerStepAdd    * 1000;            //ÿ��һ����ʱ
	pTimeDisp->SetDepth     = cps->timeSearchDepth;						//ÿ������������

	//if(cps->timePerStep == 0){
	//	pTimeDisp->SetStepTime = 600 * 60 * 1000;					    //��ʱ,���600�룬 10����
	//}

	pTimeDisp->SetStepTime    = cps->timePerStep       * 1000;			 //ÿ�����ʱ��

	pTimeDisp->isBaoGan       = cps->IsBaoGan;
	//pTimeDisp->BaoGanTime     = cps->BaoGanTime   * 60 * 1000;

	//pTimeDisp->c1time       = cps->time_1_Time  * 60 * 1000;            //��һ�׶ε�ʱ��
	//pTimeDisp->c1step       = cps->time_1_Step;

	//pTimeDisp->c2time       = cps->time_2_Time  * 60 * 1000;
	//pTimeDisp->c2step       = cps->time_2_Step;

	//��һ���ǲ���Ҫ���µ�ǰ��ʱ��

	if(cps->IsBaoGan){

		int baotime = cps->BaoGanTime * 60 * 1000;

		pTimeDisp->RemainTime = baotime;

		//if(pDis->pos->gply == 0){		//��ǰ��������,�Ͳ��ܸ���ʱ����,total ֻ�ܴ󣬲���С
		//	pTimeDisp->RemainTime = baotime;
		//}
		//else{
		//	if(baotime < pTimeDisp->RemainTime){
		//		pTimeDisp->RemainTime = baotime;
		//	}
		//}
		
		////��ʱ

		//if(pTimeDisp->SetStepTime == 0){
		//	pTimeDisp->movetime = pTimeDisp->RemainTime;
		//}
		//else{
		//	pTimeDisp->movetime = pTimeDisp->SetStepTime;
		//}

		//pTimeDisp->movestogo = 40;
	}
	else{		//��ǰ�Ƿֶμ�ʱ		
		
		if(pDis->pos->gply == 0){
			pTimeDisp->c1time       = cps->time_1_Time  * 60 * 1000;            //��һ�׶ε�ʱ��
			pTimeDisp->c1step       = cps->time_1_Step;

			pTimeDisp->c2time       = cps->time_2_Time  * 60 * 1000;
			pTimeDisp->c2step       = cps->time_2_Step;

			//��ʱ��

			pTimeDisp->RemainTime   = pTimeDisp->c1time;						

			//��ʱ

			//if(pTimeDisp->SetStepTime == 0){
			//	pTimeDisp->movetime = pTimeDisp->RemainTime;
			//}
			//else{
			//	pTimeDisp->movetime = pTimeDisp->SetStepTime;
			//}

			//pTimeDisp->StepTime     = pTimeDisp->RemainTime / pTimeDisp->c1step;

			//if(pTimeDisp->StepTime > pTimeDisp->SetStepTime){
			//		pTimeDisp->StepTime = pTimeDisp->SetStepTime;
			//}
		}
		else{	//�ֶμ�ʱ���ҵ�ǰ���ǵ�һ����Ҳ�����Ѿ�������

			int go = pDis->pos->gply / 2;   //�Ѿ����˶��ٲ���

			if(go < pTimeDisp->c1step){	    //��û�����һʱ�䲽��
				
				//��ʱ
				if(pTimeDisp->c1time < pTimeDisp->RemainTime){
					pTimeDisp->RemainTime = pTimeDisp->c1time * (pTimeDisp->c1step - go) / pTimeDisp->c1step ;
				}

				////��ʱ
				//pTimeDisp->StepTime    = pTimeDisp->c1time / pTimeDisp->c1step;

				//if(pTimeDisp->StepTime > pTimeDisp->SetStepTime){
				//	pTimeDisp->StepTime = pTimeDisp->SetStepTime;
				//}
			}
			else{							//�������һʱ�䲽����
				
				//��ʱ
				pTimeDisp->RemainTime = pTimeDisp->c2time;

				////��ʱ
				//pTimeDisp->StepTime    = pTimeDisp->c2time / pTimeDisp->c2step;

				//if(pTimeDisp->StepTime > pTimeDisp->SetStepTime){
				//	pTimeDisp->StepTime = pTimeDisp->SetStepTime;
				//}
			}
		}
	}

	//��ʱ

	if(pTimeDisp->SetStepTime == 0){
		pTimeDisp->movetime = pTimeDisp->RemainTime;
	}
	else{
		pTimeDisp->movetime = pTimeDisp->SetStepTime;
	}
}

//int
//CheckFlags()
//{
//	if (whiteTimeRemaining <= 0) {
//		if (!whiteFlag) {
//			whiteFlag = TRUE;
//			if (appData.icsActive) {
//				if (appData.autoCallFlag &&
//					gameMode == IcsPlayingBlack && !blackFlag) {
//						SendToICS(ics_prefix);
//						SendToICS("flag\n");
//				}
//			} else {
//				if (blackFlag) {
//					DisplayTitle("Both flags fell");
//				} else {
//					DisplayTitle("White's flag fell");
//					if (appData.autoCallFlag) {
//						GameEnds(BlackWins, "Black wins on time", GE_XBOARD);
//						return TRUE;
//					}
//				}
//			}
//		}
//	}
//	if (blackTimeRemaining <= 0) {
//		if (!blackFlag) {
//			blackFlag = TRUE;
//			if (appData.icsActive) {
//				if (appData.autoCallFlag &&
//					gameMode == IcsPlayingWhite && !whiteFlag) {
//						SendToICS(ics_prefix);
//						SendToICS("flag\n");
//				}
//			} else {
//				if (whiteFlag) {
//					DisplayTitle("Both flags fell");
//				} else {
//					DisplayTitle("Black's flag fell");
//					if (appData.autoCallFlag) {
//						GameEnds(WhiteWins, "White wins on time", GE_XBOARD);
//						return TRUE;
//					}
//				}
//			}
//		}
//	}
//	return FALSE;
//}
//����ǲ��ǳ�ʱ��
int
CheckFlags(dispboard_t* pDis){
	//
	if(pDis->TimeDisp[WHITE].RemainTime <= 0 || pDis->TimeDisp[WHITE].movetime <= 0){	//�췽��ʱ��
		if(!pDis->whiteFlag){
			pDis->whiteFlag = TRUE;
			if(appData.icsActive){		//��ǰ������״̬
				if(appData.autoCallFlag && pDis->gameMode == IcsPlayingBlack && !pDis->blackFlag){
					//SendToICS(ics_prefix);
					SendToICS(L"flag\n");
				}
			}
			else{
				if(pDis->blackFlag){
					swprintf_s(pDis->pgn->result, sizeof(pDis->pgn->result) / sizeof(TCHAR), _T("%s"), _T("˫����ʱ��"));
					DisplayTitle(pDis);
				}
				else{
					//SendToPlayerByColor("\n�췽��ʱ��!!\n", ColorSeek, FALSE);
					//DisplayTitle(pDis,"�췽��ʱ��!!");

					swprintf_s(pDis->pgn->result, sizeof(pDis->pgn->result) / sizeof(TCHAR), _T("%s"), _T("�췽��ʱ��"));
					DisplayTitle(pDis);

					if(appData.autoCallFlag){
						//GameEnds(pDis,BlackWins,"�췽��ʱ�жϸ�",GE_XBOARD);
					}
				}
			}
		}
	}
	//
	if(pDis->TimeDisp[BLACK].RemainTime <= 0 || pDis->TimeDisp[BLACK].movetime <= 0){	//�ڷ���ʱ��
		if(!pDis->blackFlag){
			pDis->blackFlag = TRUE;
			if(appData.icsActive){		//��ǰ������״̬
				if(appData.autoCallFlag && pDis->gameMode == IcsPlayingWhite && !pDis->whiteFlag){
					//SendToICS(ics_prefix);
					SendToICS(L"flag\n");
				}
			}
			else{
				if(pDis->whiteFlag){
					//SendToPlayerByColor("\n˫����ʱ��!!\n", ColorSeek, FALSE);
					//DisplayTitle(pDis,"˫����ʱ��!!");

					swprintf_s(pDis->pgn->result, sizeof(pDis->pgn->result) / sizeof(TCHAR), _T("%s"), _T("�췽��ʱ��"));
					DisplayTitle(pDis);
				}
				else{
					//SendToPlayerByColor("\n�ڷ���ʱ��!!\n", ColorSeek, FALSE);
					//DisplayTitle(pDis,"�ڷ���ʱ��!!");

					swprintf_s(pDis->pgn->result, sizeof(pDis->pgn->result) / sizeof(TCHAR), _T("%s"), _T("�ڷ���ʱ��"));
					DisplayTitle(pDis);

					if(appData.autoCallFlag){
						//GameEnds(pDis,WhiteWins,"�ڷ���ʱ�жϸ�",GE_XBOARD);
					}
				}
			}
		}
	}

    return FALSE;
}

//void
//DisplayBothClocks()
//{
//    int wom = gameMode == EditPosition ?
//      !blackPlaysFirst : WhiteOnMove(currentMove);
//    DisplayWhiteClock(whiteTimeRemaining, wom);
//    DisplayBlackClock(blackTimeRemaining, !wom);
//}

void    //��ʾ˫����ʱ��
DisplayBothClocks(dispboard_t* pDis){
	
	int wom = pDis->pos->side == WHITE ? 1 : 0;

	DisplayWhiteClock(pDis, 0, wom);

	DisplayBlackClock(pDis, 0, !wom);
}

/* Return the difference in milliseconds between two
time marks.  We assume the difference will fit in a long!
*/
//long
//SubtractTimeMarks(TimeMark *tm2,TimeMark *tm1)
//{
//    return 1000L*(tm2->sec - tm1->sec) +
//        (long) (tm2->ms - tm1->ms);
//}

/*
* Code to manage the game clocks.
*
* In tournament play, black starts the clock and then white makes a move.
* We give the human user a slight advantage if he is playing white---the
* clocks don't run until he makes his first move, so it takes zero time.
* Also, we don't account for network lag, so we could get out of sync
* with GNU Chess's clock -- but then, referees are always right.  
*/

//static TimeMark tickStartTM;
//static long intendedTickLength;

long        //�õ���һ����ʱʱ��
NextTickLength(long timeRemaining)
{
    long nominalTickLength, nextTickLength;

	if (timeRemaining > 0L && timeRemaining <= 10000L) {     //С��1000MS��{
        nominalTickLength = 100L;			//0.1s
	}
	else{
        nominalTickLength = 1000L;			//1s
	}

    nextTickLength = timeRemaining % nominalTickLength;

    if (nextTickLength <= 0) {
        nextTickLength += nominalTickLength;
    }

    return nextTickLength;		//��һ����ʱ���ʱ��,
}



//void 
//ResetCpsTime(ChessProgramState *cps){
//	if(loadokcps->playWhat != NEUTRAL){
//		GetTimeInfoFromCps(pDis, &pDis->TimeDisp[loadokcps->playWhat], loadokcps);
//	}
//}

//* Stop clocks and reset to a fresh time control */
//void
//ResetClocks() 
//{
//	(void) StopClockTimer();
//	if (appData.icsActive) {
//		whiteTimeRemaining = blackTimeRemaining = 0;
//	} else {
//		whiteTimeRemaining = blackTimeRemaining = timeControl;
//	}
//	if (whiteFlag || blackFlag) {
//		DisplayTitle("");
//		whiteFlag = blackFlag = FALSE;
//	}
//	DisplayBothClocks();
//}
void  /* Stop clocks and reset to a fresh time control */ 
ResetClocks(dispboard_t* pDis) {
    
	StopClockTimer(pDis);

	//if(appData.icsActive){
	//	//pDis->TimeDisp[WHITE].RemainTime = 0;
	//	//pDis->TimeDisp[BLACK].RemainTime = 0;
	//}
	//else{

		GetTimeInfoFromCps(pDis, &pDis->TimeDisp[WHITE], &pDis->first);

		
		if(pDis->first.playWhat != NEUTRAL){
			GetTimeInfoFromCps(pDis, &pDis->TimeDisp[pDis->first.playWhat], &pDis->first);
		}	



	//}

	if(pDis->whiteFlag || pDis->blackFlag){
		
		//DisplayTitle(pDis, "ʱ�临λ��");

		LogOut(_T("\n˫��ʱ�临λ��"));

		pDis->whiteFlag = FALSE;
		pDis->blackFlag = FALSE;
	}

    DisplayBothClocks(pDis);
}


#define FUDGE 25 /* 25ms = 1/40 sec; should be plenty even for 50 Hz clocks */

/* Decrement running clock by amount of time that has passed */
//��������ʱ���ȥ
void
DecrementClocks(dispboard_t* pDis){
    long timeRemaining;
    long lastTickLength, fudge;
    //TimeMark now;

	int now;

    if (!pDis->clockMode){				//����ʱ�䷽ʽ
        return;
    }

	now = GetTickCount();  
	lastTickLength = now - pDis->tickStartTM; 

 

    //if (pDis->gameMode==AnalyzeMode || pDis->gameMode == AnalyzeFile){	//�����ļ������ģʽ
	if (pDis->gameMode == AnalyzeMode){	//�����ļ������ģʽ
        return;
    }

	now = GetTickCount();
	 
	lastTickLength = now - pDis->tickStartTM; 

    /* Fudge if we woke up a little too soon */ //�λ�, ����, ֽ������ӡ����
    fudge = pDis->intendedTickLength - lastTickLength;
    if (fudge < 0 || fudge > FUDGE){			//25ms ���, ��ʱ������
        fudge = 0;
    }

	if(LAST_DIS_SIDE(pDis) == WHITE){	

		pDis->TimeDisp[WHITE].RemainTime -= lastTickLength;
		pDis->TimeDisp[WHITE].movetime   -= lastTickLength;

		DisplayWhiteClock(pDis, fudge,  pDis->pos->side == WHITE); 
		
		timeRemaining = pDis->TimeDisp[WHITE].RemainTime;		
	}
	else{

		pDis->TimeDisp[BLACK].RemainTime  -= lastTickLength;
		pDis->TimeDisp[BLACK].movetime    -= lastTickLength;

		DisplayBlackClock(pDis, fudge, pDis->pos->side == WHITE);
		
		timeRemaining = pDis->TimeDisp[BLACK].RemainTime;		
	}



		//������������ϳ����Ĺ���
	if(pDis->gameMode == IcsPlayingWhite){
		
		if(pDis->TimeDisp[WHITE].RemainTime < const_MIN_TIME  || pDis->TimeDisp[WHITE].movetime < const_MIN_TIME ){
			
			ChessProgramState *cps = NULL;
			
			if(pDis->first.playWhat == WHITE){
				if(pDis->first.cps_stat == Cps_Thinking){
					cps = &pDis->first;
				}				
			}

			if(cps != NULL){
				SendToProgram(L"stop\n",cps);	
				Sleep(100);
				SendToProgram(L"stop\n", cps);
				Sleep(100);
			}
		}		
	}
	else if(pDis->gameMode == IcsPlayingBlack){

		if(pDis->TimeDisp[BLACK].RemainTime < const_MIN_TIME  || pDis->TimeDisp[BLACK].movetime < const_MIN_TIME ){
			
			ChessProgramState *cps = NULL;

			if(pDis->first.playWhat == BLACK){
				if(pDis->first.cps_stat == Cps_Thinking){
					cps = &pDis->first;
				}				
			}


			if(cps != NULL){	
				SendToProgram(L"stop\n", cps);
				Sleep(100);
				SendToProgram(L"stop\n", cps);
				Sleep(100);
			}	
		}

	}

    if (CheckFlags(pDis)) return;

    pDis->tickStartTM = now;
    
	pDis->intendedTickLength = NextTickLength(timeRemaining - fudge) + fudge;
    
	StartClockTimer(pDis,pDis->intendedTickLength);

    /* if the time remaining has fallen below the alarm threshold, sound the
    * alarm. if the alarm has sounded and (due to a takeback or time control
    * with increment) the time remaining has increased to a level above the
    * threshold, reset the alarm so it can sound again. 
    */

    if (appData.icsActive && appData.icsAlarm) {

        /* make sure we are dealing with the user's clock */
        if(!(((pDis->gameMode == IcsPlayingWhite) && (pDis->pos->side == WHITE)) ||
            ((pDis->gameMode == IcsPlayingBlack) && !(pDis->pos->side == WHITE))
            )){
                return;
        }

        if (appData.alarmSounded && (timeRemaining > appData.icsAlarmTime)) {
            appData.alarmSounded = FALSE;
        } 
        else if (!appData.alarmSounded && (timeRemaining <= appData.icsAlarmTime)) { 
            //PlayAlarmSound();
            appData.alarmSounded = TRUE;
        }
    }
}

//char *
//TimeString(long ms) {  //��ʱ��ת�����ַ���
void 
TimeString (long ms, TCHAR* buf){
    int second, minute;
    //int hour;
    int day;
    int rms;
    TCHAR *sign = L"";

    if(ms < 0){
        sign = L"-";
		ms = -ms;
    }
    day    = ms /  (60 * 60 * 24 * 1000);
    rms    = ms %  (60 * 60 * 24 * 1000);
    //hour   = rms / (60 * 60 * 1000);
    //rms    = rms % (60 * 60 * 1000);

    minute = rms / (60 * 1000);
    rms    = rms % (60 * 1000);
    
    second = rms / 1000;
    rms    = rms % 1000;

	//-000:00' 000"
	StringCbPrintf(buf,32,_T("%1s%.03d:%.02d' %.03d\n"),sign,minute,second,rms);
}

void
SwitchClocks(dispboard_t* pDis){

	if(pDis->hwndThis == NULL){
		return;
	}

    long lastTickLength;
	int now;
    int flagged = FALSE;

	now = GetTickCount();

    if (StopClockTimer(pDis) && pDis->clockMode) {

		lastTickLength = now - pDis->tickStartTM;

        if(LAST_DIS_SIDE(pDis) == WHITE){
			pDis->TimeDisp[BLACK].RemainTime -= lastTickLength;
			pDis->TimeDisp[BLACK].movetime -= lastTickLength;
        } 
        else {
			pDis->TimeDisp[WHITE].RemainTime -= lastTickLength;
			pDis->TimeDisp[WHITE].movetime   -= lastTickLength;
        }

        flagged = CheckFlags(pDis);
    }

    CheckTimeControl(pDis);

    if (flagged || !pDis->clockMode){
        return;
    }

    switch (pDis->gameMode) {
      case MachinePlaysBlack:
      case MachinePlaysWhite:
      case BeginningOfGame:
          if (pDis->pausing){
              return;
          }
          break;

      case EditGame:
      case PlayFromGameFile:
      case IcsExamining:
          return;

      default:
          break;
    }

    pDis->tickStartTM = now;

	pDis->intendedTickLength 
		= NextTickLength( (LAST_DIS_SIDE(pDis) == WHITE) ?  pDis->TimeDisp[WHITE].RemainTime : pDis->TimeDisp[BLACK].RemainTime);

    StartClockTimer(pDis,pDis->intendedTickLength);
}


///* Stop both clocks */
//void
//StopClocks()
//{	
//    long lastTickLength;
//    TimeMark now;
//
//    if (!StopClockTimer()) return;
//    if (!appData.clockMode) return;
//
//    GetTimeMark(&now);
//
//    lastTickLength = SubtractTimeMarks(&now, &tickStartTM);
//    if (WhiteOnMove(forwardMostMove)) {
//	whiteTimeRemaining -= lastTickLength;
//	DisplayWhiteClock(whiteTimeRemaining, WhiteOnMove(currentMove));
//    } else {
//	blackTimeRemaining -= lastTickLength;
//	DisplayBlackClock(blackTimeRemaining, !WhiteOnMove(currentMove));
//    }
//    CheckFlags();
//}
void  /* Stop both clocks */
StopClocks(dispboard_t* pDis){	

    long lastTickLength;
	int now;

    if (!StopClockTimer(pDis)){
        return;
    }
    if (!pDis->clockMode){
        return;
    }

	now = GetTickCount();

	lastTickLength = now - pDis->tickStartTM;


    if(LAST_DIS_SIDE(pDis) == WHITE){

		pDis->TimeDisp[WHITE].RemainTime -= lastTickLength;
		pDis->TimeDisp[WHITE].movetime   -= lastTickLength;

		DisplayWhiteClock(pDis, 0, pDis->pos->side == WHITE);
    } 
    else {

		pDis->TimeDisp[BLACK].RemainTime -= lastTickLength;
		pDis->TimeDisp[BLACK].movetime   -= lastTickLength;

		DisplayBlackClock(pDis,0, !pDis->pos->side == WHITE);
    }

    CheckFlags(pDis);
}

/* Start clock of player on move.  Time may have been reset, so
if clock is already running, stop and restart it. */
void
StartClocks(dispboard_t* pDis){
    
	StopClockTimer(pDis); /* in case it was running already */
   
	DisplayBothClocks(pDis);
    
	if (CheckFlags(pDis)){
        return;
    }
    if (!pDis->clockMode){
        return;
    }
    //if (pDis->gameMode == AnalyzeMode || pDis->gameMode == AnalyzeFile){
	if (pDis->gameMode == AnalyzeMode){
        return;
    }
    
	pDis->tickStartTM = GetTickCount();		//GetTimeMark(&pDis->tickStartTM);

	pDis->intendedTickLength = NextTickLength(LAST_DIS_SIDE(pDis) == WHITE ?
		pDis->TimeDisp[WHITE].RemainTime : pDis->TimeDisp[BLACK].RemainTime);

    StartClockTimer(pDis,pDis->intendedTickLength);
}

//int						//����ʱ�����
//ParseTimeControl(char *tc, int ti, int mps)  {
//    //int matched, min, sec, ms;
//    //matched = sscanf_s(tc, "%d:%d:%d", &min, &sec, &ms);
//    //if (matched == 1) {
//    //    DIS.timeControl = min * 60 * 1000;
//    //} 
//    //else if (matched == 2) {
//    //    DIS.timeControl = (min * 60 + sec) * 1000;
//    //}
//    //else if (matched == 3){
//    //    DIS.timeControl = (min * 60 + sec) * 1000 + ms;
//    //}
//    //else {
//    //    return FALSE;
//    //}
//
//    //if (ti >= 0) {
//    //    DIS.timeIncrement = ti * 1000;  /* convert to ms */
//    //    DIS.movesPerSession = 0;
//    //} 
//    //else {
//    //    DIS.timeIncrement = 0;
//    //    DIS.movesPerSession = mps;
//    //}
//    return TRUE;
//}
//
//
