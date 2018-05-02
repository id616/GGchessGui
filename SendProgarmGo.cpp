#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"

void SendProgramGo(ChessProgramState *cps){

    dispboard_t* pDis = OBS[cps->table];

    if(cps->playWhat == NEUTRAL){
        MessageBox(pDis->hwndThis,"������!", "���治�����ӷ�!!",MB_OK);
        return;
    }
    if(cps->maybeThinking == TRUE){
        MessageBox(pDis->hwndThis,"������!", "���滹��˼��!!",MB_OK);
        return;
    }    

    TruncateGame(pDis);

    if(cps->playWhat != pDis->pos->side){
        LogOut("���治�����ӷ�!\n");
        return;
    }

    char buf[MSG_SIZ];

    TimeDisp_t *pt      = &pDis->TimeDisp[cps->playWhat];
    TimeDisp_t *pother  = &pDis->TimeDisp[cps->playWhat ^ 0x1];

    switch(cps->ucci){
        case UCCI_UCCI162:
            //UCCI �ø���ʱ���趨���Ϳ���ʱ���go
            //SendToProgram("go depth 10\n", cps);        //����������������

            //���ȷ��ͳ�ʼ����, 

            SendMoveToProgram(pDis,cps);
            
            if(pt->depth != 0){
                sprintf_s(buf,sizeof(buf), "go depth %d\n",pt->depth);                
            } 
            else if(pt->isBaoGan){
                sprintf_s(buf,sizeof(buf), "go wtime %d winc %d btime %d binc %d\n",
                    pt->msTotal,pt->stepAdd, pother->msTotal,pother->stepAdd);                

            }
            else{       //�ֶμ�ʱ
                if(pDis->pos->gply/2 >= pt->c1step){
                    //if(
                }  
                else {      //���ڵ�һʱ�����
                    sprintf_s(buf,sizeof(buf),"go movetime %d\n", pt->c1time/(pt->c1step - pDis->pos->gply*2));
                }                 
            }

            SendToProgram(buf,cps);

            StartClocks(pDis);      //��ʼ��ʱ

            cps->maybeThinking = TRUE;

            break;
        case UCCI_CYC105:

            SendMoveToProgram(pDis,cps);
            
            if(pt->depth != 0){
                sprintf_s(buf,sizeof(buf), "go depth %d\n",pt->depth);                
            } 
            else if(pt->isBaoGan){
                sprintf_s(buf,sizeof(buf), "go wtime %d winc %d btime %d binc %d\n",
                    pt->msTotal,pt->stepAdd, pother->msTotal,pother->stepAdd);                

            }
            else{       //�ֶμ�ʱ
                if(pDis->pos->gply/2 >= pt->c1step){
                    //if(
                }  
                else {      //���ڵ�һʱ�����
                    sprintf_s(buf,sizeof(buf),"go movetime %d\n", pt->c1time/(pt->c1step - pDis->pos->gply*2));
                }                 
            }

            SendToProgram(buf,cps);

            StartClocks(pDis);      //��ʼ��ʱ

            cps->maybeThinking = TRUE;

            break;
        case UCCI_QH:	
            break;
        case UCCI_DIS:	
            SendToProgram("go\n", cps);
            break;
        default:
            break;
    }
    
}
