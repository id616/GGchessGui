#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"

//void
//SendMoveToProgram(moveNum, cps)
//     int moveNum;
//     ChessProgramState *cps;
//{
//    char buf[MSG_SIZ];
//    if (cps->useUsermove) {
//      SendToProgram("usermove ", cps);
//    }
//    if (cps->useSAN) {
//      char *space;
//      if ((space = strchr(parseList[moveNum], ' ')) != NULL) {
//	int len = space - parseList[moveNum];
//	memcpy(buf, parseList[moveNum], len);
//	buf[len++] = '\n';
//	buf[len] = NULLCHAR;
//      } else {
//	sprintf(buf, "%s\n", parseList[moveNum]);
//      }
//      SendToProgram(buf, cps);
//    } else {
//      SendToProgram(moveList[moveNum], cps);
//    }
//}
//
//void		//�����߲�������,ע��ֻ�Ƿ����û�����һ��,����Ҫ��������Ҫ����!!!
//SendMoveToProgram(int moveNum, ChessProgramState *cps){


void		//�����߲�������,ע��ֻ�Ƿ����û�����һ��,����Ҫ��������Ҫ����!!!
SendMoveToProgram(dispboard_t* pDis, ChessProgramState *cps, TCHAR* ponderMove){
    TCHAR   buf[FEN_SIZE];
	TCHAR *   pb;
	TCHAR    fen[MSG_SIZ];
    int     start;
    int     startSide;

    int     gply   = pDis->pos->gply;
    int     nonCap = pDis->pos->His[gply].nonCap;

	if (pDis->gameMode != AnalyzeMode){
		if(gply != pDis->pos->curStep){
			LogOut(_T("������,�ڷ��ͳ�ʼ����ʱ,��������ȷ!\n"));
			return;
		}
	}
	else{                                  //���Ƿ���ģʽ
		gply   = pDis->pos->curStep;
		nonCap = pDis->pos->His[gply].nonCap;
	}

	//if(cps->maybeThinking || cps->maybePonering){                 //����������ں�̨˼��
	//	SendToProgram("stop\n",cps);
	//	Sleep(1);		
	//}

    //�����߲�������
    //if(moveNum>0){
    //    ParaseDisMoveToUCCImove(DIS.moveList[moveNum-1],DIS.parseList[moveNum-1],cps->ucci);
    //}
    //ParaseDisMoveToUCCImove(DIS.moveList[moveNum],DIS.parseList[moveNum],cps->ucci);



	//����ǰ�ľ��渴��һ��
	memcpy(cps->pos, pDis->pos, sizeof(position_t));

	if(ponderMove != NULL){

		int pmove = str2move(cps->pos, cps->PonderMove);

		//cps->PonderMoveInt = pmove;
		//cps->PonderName[9] = 0; 
		GetMoveNameSimple(cps->pos,cps->PonderName,pmove,appData.moveType);
		MakePosMoveOnly(cps->pos,pmove);
		cps->pos->gply++;
	}

	//if(cps->UCCI_havePonder){

	//	int m = cps->pos->His[cps->pos->curStep].move;

	//	UnMakePosMoveOnly(cps->pos);

	//	cps->pdmove = str2move(cps->pos,ponderMove+1);  //���Ҫ��һ

	//	MakePosMoveOnly(cps->pos,m);
	//}

 //   int finalStep = gply;
	//if(ponder == TRUE){
	//	finalStep ++;
	//}

    switch(cps->ucci){
        case UCCI_UCCI_ms:	  //��������÷���һ��ʱ����Ƹ�UCCI
		case UCCI_UCCI_OLD:
            //
            //������һ�������ӵľ���  
            startSide = pDis->pos->side ^ (nonCap%2);
            start     = gply - nonCap;


            position_to_fen_by_b256(pDis->B256dis[start],startSide,fen);

			swprintf_s(buf, FEN_SIZE, L"position fen %s moves", fen);


            pb = buf + wcslen(buf);

            for(int i = start; i < gply; i++){

				swprintf_s(pb,FEN_SIZE,L" %s", pDis->parseList[i]);
                pb += 5;
            }

			if(ponderMove != NULL){
				wcscat_s(buf, sizeof(buf) / sizeof(TCHAR), L" ");
				wcscat_s(buf, sizeof(buf) / sizeof(TCHAR), ponderMove);
				//cps->UCCI_havePonder = FALSE;
			}

			wcscat_s(buf, sizeof(buf) / sizeof(TCHAR), L"\n");

            SendToProgram(buf,cps);   //���ͳ�ʼ���� 

            break;
		case UCCI_GGchess:

            //������һ�������ӵľ���  
            startSide = pDis->pos->side ^ (nonCap%2);
            start     = gply - nonCap;


            position_to_fen_by_b256(pDis->B256dis[start],startSide,fen);

           swprintf_s(buf,FEN_SIZE,L"fen %s moves",fen);

            pb = buf + wcslen(buf);

            for(int i = start; i < gply; i++){
				swprintf_s(pb, FEN_SIZE/2, L" %s", pDis->parseList[i]);
                pb += 5;
            }

			if(ponderMove != NULL){
				wcscat_s(buf, sizeof(buf) / sizeof(TCHAR), L" ");
				wcscat_s(buf, sizeof(buf) / sizeof(TCHAR), ponderMove);
				//cps->UCCI_havePonder = FALSE;
			}

			wcscat_s(buf, sizeof(buf) / sizeof(TCHAR), L"\n");

            SendToProgram(buf,cps);   //���ͳ�ʼ���� 

#ifdef  USE_OUT_FEN_TO_LOG
			LogOut(buf);
#endif

            break;
		//
        case UCCI_CYC105:

            //������һ�������ӵľ���  
            startSide = pDis->pos->side ^ (nonCap%2);
            start     = gply - nonCap;


            position_to_fen_by_b256(pDis->B256dis[start],startSide,fen);

			swprintf_s(buf, FEN_SIZE, L"fen %s moves", fen);

            pb = buf + wcslen(buf);

            for(int i = start; i < gply; i++){
				swprintf_s(pb, FEN_SIZE, L" %s", pDis->parseList[i]);
                pb += 5;
            }

			if(ponderMove != NULL){
				wcscat_s(buf, sizeof(buf) / sizeof(TCHAR), L" ");
				wcscat_s(buf, sizeof(buf) / sizeof(TCHAR), ponderMove);
				//cps->UCCI_havePonder = FALSE;
			}

			wcscat_s(buf, sizeof(buf) / sizeof(TCHAR), L"\n");

            SendToProgram(buf,cps);   //���ͳ�ʼ���� 
            break;
		//
        case UCCI_QianHong:			
            //StringCbPrintf(buf,MSG_SIZ,"PLAY %s",DIS.parseList[moveNum]);
            //SendToProgram(buf, cps);
            //SendToProgram("AI\n", cps);
            //SendToProgram("AI",cps);
            //ǳ����͵��ж�AI ����ֻ���û��ر�Ӧ�ó�����˳���ǰ���ʱ. 
            //�����Ǻ�TIMEOUT����, ��, �����֧��, �����͵����� AI ֹͣ˼��
            //����Ӧʹ�õ�ĿǰΪֹ���������õ��岽.
            break;
        //
        default:			
            //StringCbPrintf(buf,MSG_SIZ,"force %s\n",DIS.parseList[moveNum]);
            //StringCbPrintf(buf,MSG_SIZ,"%s\n",DIS.parseList[moveNum]);
            //SendToProgram(buf, cps);
            //SendToProgram("go\n", cps);
            break;

    }


}