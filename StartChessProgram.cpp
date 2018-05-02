#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"


void StartChessProgram(ChessProgramState *cps) {
    
    TCHAR buf[MSG_SIZ];
    int  err;



    //GetSetYQsetFromAppData();           //�õ�������趨����

    //if(cps->UCCI_initDone == TRUE){
    //    return;
    //}

	if(cps->cps_stat != Cps_NotLoad){
		return;
	}

	//cps->isInLoading	= TRUE;        //���ڼ�������
 //   cps->UCCI_initDone  = FALSE;

	cps->cps_stat = Cps_InLoading;

	if(strcmp(cps->szHost,"localhost") == 0){     //�Ǳ�����Ϸ
		switch(cps->ucci){
			case UCCI_UCCI_ms:	
			case UCCI_UCCI_OLD:
				StringCbPrintf(buf, MSG_SIZ, _T("%s"), cps->UCCI_file);
				break;
			//
			case UCCI_GGchess:
				IsSendRand = 0;
				StringCbPrintf(buf, MSG_SIZ, _T("%s"), cps->UCCI_file);
				break;
			//
			case UCCI_CYC105:
				StringCbPrintf(buf, MSG_SIZ, _T("%s%s%s"), installDir, cps->UCCI_path, cps->UCCI_file);
				break;
			//
			case UCCI_QianHong:			//ǳ��Э��
				StringCbPrintf(buf, MSG_SIZ, _T("%s -plugin"), cps->UCCI_file);  // ����һ��-plugin				
				break;
			//
			default:
				StringCbPrintf(buf, MSG_SIZ, _T("%s"), cps->UCCI_file);
				break;
		}
		err = StartChildProcess(buf, cps->UCCI_path, &cps->pr);	         //���������
	}
	else if(*appData.remoteShell == NULLCHAR){                           //������Ϸ
		err = OpenRcmd(cps->szHost, CW2A(appData.remoteUser),CW2A(cps->UCCI_file), &cps->pr);
	}
	else{                                                                //Զ���û�
		if (*appData.remoteUser == NULLCHAR) {
			StringCbPrintf(buf, MSG_SIZ, _T("%s %s %s"), appData.remoteShell, cps->szHost, cps->UCCI_file);
		} 
		else {		
			StringCbPrintf(buf, MSG_SIZ, _T("%s %s -l %s %s"), appData.remoteShell,
				cps->szHost, appData.remoteUser, cps->UCCI_file);
		}
		err = StartChildProcess(buf, _T(""), &cps->pr);
	}

	//********************************************************
	if (err != 0) {						//�����ʼ����
		StringCbPrintf(buf, MSG_SIZ, _T("Startup failure on '%s'"), cps->UCCI_file);
		LogOut(buf);
		//DisplayFatalError(buf, err, 1);
		cps->pr = NoProc;
		cps->isr = NULL;
		return;
	}
    cps->isr = AddInputSource(cps->pr, TRUE, ReceiveFromProgram, cps);      //����һ�������߳�

    // Э��汾����

    //if (cps->protocolVersion > 1) {
    //	//sprintf(buf, "xboard\nprotover %d\n", cps->protocolVersion);
    //	//StringCbPrintf(buf,MSG_SIZ,"xboard\nprotover %d\n", cps->protocolVersion);
    //	//SendToProgram(buf, cps);
    //	//SendToProgram("ucci",cps);
    //} 
    //else {
    //	//SendToProgram("ucci",cps);
    //	//SendToProgram("xboard\n", cps);
    //}


    //���������ʼ������
    switch(cps->ucci){
        case UCCI_UCCI_ms:			//��Э��
		case UCCI_UCCI_OLD:
            //�������������󣬽�����Ҫ�����淢�͵ĵ�һ��ָ�֪ͨ��������ʹ�õ���UCCIЭ�顣
			SendToProgram(L"ucci\n", cps);
            break;
		case UCCI_GGchess:		    //�������������
			//Sleep(1000);
			//sprintf_s(buf,sizeof(buf),"%s",UCCI_START);
			//SendToProgram(buf,cps);

            //SendToProgram("Authenticate 801C85DE5F7BDACFF1F8DC789FBE5B1B\n",cps);
            //StringCbPrintf(buf,MSG_SIZ,"Md5check %s%s%s\n",
            //	installDir,cps->dir,cps->program);
            //SendToProgram(buf,cps);
            //SendToProgram("notation 4 3\n",cps);		//�岽��ʽ
            ////SendToProgram("hard\n",cps);				//������̨˼��
            //SendToProgram("learn 0\n",cps);				//����ѧϰ����
            //SendToProgram("log off\n",cps);				//������־


            //SendToProgram("st 1\n",cps);				//������־
            //SendToProgram("time sd/10\n",cps);		//������־
            //SendToProgram("force H2E2\n",cps);
            //force H2E2
            //SendToProgram("Authenticate 801C85DE5F7BDACFF1F8DC789FBE5B1B\n",cps);

            //GetCurrentDirectory(MSG_SIZ, buf);
            //SetCurrentDirectory(installDir);
            //SetCurrentDirectory(dir);
            break;
        case UCCI_CYC105:
			SendToProgram(L"ucci\n", cps);
            break;
        case UCCI_QianHong:			//ǳ��Э��			
            break;
        
        default:			
            break;			
    }
}


