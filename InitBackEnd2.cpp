#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"

void     //�ڶ�����ʼ��
InitBackEnd2(dispboard_t *pDis){

#ifdef DEBUG_MODE
    //if (appData.debugMode) {
        //fprintf(appData.debugFP, "%s\n", MAIN.programVersion);
    //}
#endif


    GameReset(pDis, TRUE, FALSE,TRUE);
   /* if (appData.noChessProgram || DIS.first.protocolVersion == 1) {*/
    //if (pDis->noChessProgram ) {
    //    InitBackEnd3(pDis);     //û���������
    //} 
    //else {
        /* kludge: allow timeout for initial "feature" commands */
        FreezeUI();
        //DisplayMessage(pDis,"", MAIN.programVersion);
        //DisplayMessage(pDis,"", "Starting chess program");
		LogOut(_T("���ڼ�����������..."));
        ScheduleDelayedEvent(pDis,(DelayedEventCallback)InitBackEnd3, FEATURE_TIMEOUT);		//��ʱ��ʼ��������
        //ScheduleDelayedEvent(InitBackEnd3, 5000);		//��ʱ��ʼ��������
    //}
}



