#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"



void 
SendControlParameterToCps(ChessProgramState *cps) {

    //if(cps->Already_Send_Initinfo == TRUE){     //�ѷ����˳�ʼ��Ϣ
    //    return;
    //}

    //��������趨ʱ�䷽����趨
    TCHAR buf[MSG_SIZ];

    //������趨�����������ã�ʱ�䣬��������̨˼����
    switch(cps->ucci){
        	
		//
        case UCCI_UCCI_ms:		//��Э�� *******************************************************

			//
			SendToProgram(L"setoption usemillisec on\n",cps);

			//
			if(cps->UCCI_loadbook){
				SendToProgram(L"setoption usebook true\n",cps);
			}
			else{
				SendToProgram(L"setoption usebook off\n",cps);
			}

			//
			
			swprintf_s(buf,sizeof(buf)/sizeof(TCHAR),L"setoption hashsize %d\n",cps->UCCI_hashsize);
			SendToProgram(buf,cps);
			
            //............................................
            break;
		//
		case UCCI_UCCI_OLD:
			//
			SendToProgram(L"setoption usemillisec false\n",cps);

			//
			if(cps->UCCI_loadbook){
				SendToProgram(L"setoption usebook true\n",cps);
			}
			else{
				SendToProgram(L"setoption usebook off\n",cps);
			}

			
			swprintf_s(buf, sizeof(buf) / sizeof(TCHAR), L"setoption hashsize %d\n", cps->UCCI_hashsize);
			SendToProgram(buf,cps);
			
            //............................................
            break;
		//
		case UCCI_GGchess:		//�Ѽ�Э�� *******************************************************

			if(cps->UCCI_hashsize < 64){
				cps->UCCI_hashsize = 64;
			}
			
			swprintf_s(buf, sizeof(buf) / sizeof(TCHAR), L"setoption name Hash value %d\n", cps->UCCI_hashsize);
			SendToProgram(buf,cps);

			swprintf_s(buf, sizeof(buf) / sizeof(TCHAR), L"setoption name Threads value %d\n", cps->UCCI_smpNum);
			SendToProgram(buf,cps);

			//define_uci_option(FALSE, "Threads",	         SMP_NUM,           UCI_SPIN,  1, 8);

			//SMP NUM

			swprintf_s(buf, sizeof(buf) / sizeof(TCHAR),
				L"\n*******************************\n"
				L"���� -> %s"
				L"�߳���(SMP):  %6d\n"
				L"Hash��:       %6dm\n"
				L"���ֲ���:     %6d�غ�\n"
				L"********************************\n",
				cps->UCCI_name,
				cps->UCCI_smpNum,
				cps->UCCI_hashsize,
				cps->UCCI_Book_Num);

			LogOut(buf);

			//sprintf_s(buf,sizeof(buf), "

			//
            break;
		case UCCI_QianHong:		//ǳ��Э�� *******************************************************
			if (wcsstr(cps->UCCI_file, L"keplugin.exe") != NULL){	//killegg���е�
                SendToProgram(L"LEVEL 5\n",cps);
            }
            else{
                SendToProgram(L"LEVEL 3\n",cps);
            }			
            //cps->maybeThinking = FALSE;
            //cps->offeredDraw = 0;
            break;
        case UCCI_CYC105:
            break;
        
        default:					 //*******************************************************
           
            break;
    }

}
