#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"

void   //���³�ʼ����������, ��֮ǰ�����Ѵ���
InitChessProgram(ChessProgramState *cps) {

	//dispboard_t *pDis = OBS[cps->table];

	dispboard_t* pDis = (dispboard_t*)cps->pDis;

    //if (pDis->noChessProgram){
    //    return;
    //}
    //cps->table = pDis->table;
   /* pDis->hintRequested = FALSE;
    pDis->bookRequested = FALSE;	*/

    switch(cps->ucci){
        case UCCI_UCCI_ms:
		case UCCI_UCCI_OLD:
            //1, �Ƚ�ԭ�ȵ�ֹͣһ��
            //SendToProgram("stop\n", cps);
            //SendToProgram("stop\n",cps);
            SendToProgram(L"stop\n", cps);
			SendToProgram(L"uccinewgame\n", cps);        //���¿�ʼһ��
            break;
		//
		case UCCI_GGchess:
			SendToProgram(L"stop\n", cps);
			SendToProgram(L"ucinewgame\n", cps);        //���¿�ʼһ��
			break;
		//
        case UCCI_CYC105:
			SendToProgram(L"stop\n", cps);
			SendToProgram(L"uccinewgame\n", cps);        //���¿�ʼһ�� //ccinewgame
			SendToProgram(L"ucci\n", cps);

            //[GUI]stop
            //[GUI]ccinewgame
            //[GUI]cci

            break;
		//
        case UCCI_QianHong:
            break;
		//
        default:
			SendToProgram(L"stop\n", cps);
			SendToProgram(L"uccinewgame\n", cps);        //���¿�ʼһ��
            break;
    }

    SendControlParameterToCps(cps); 
    //cps->UCCI_initDone = TRUE;
}   

void		//��ʼ������״̬
ClearProgramStats(void){
    /* Init programStats */
    //DIS.programStats.movelist[0]	= 0;
    //DIS.programStats.depth			= 0;
    //DIS.programStats.nr_moves		= 0;
    //DIS.programStats.moves_left		= 0;
    //DIS.programStats.nodes			= 0;
    //DIS.programStats.time			= 100;
    //DIS.programStats.score			= 0;
    //DIS.programStats.got_only_move	= 0;
    //DIS.programStats.got_fail		= 0;
    //DIS.programStats.line_is_book	= 0;
}
