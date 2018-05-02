#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"

extern void HandleMachineCYC105(TCHAR *Tinfo, ChessProgramState *cps);         //cyclone 105
extern void HandleMachineUCCI162(TCHAR *Tinfo, ChessProgramState *cps);         //UCCI1.62
extern void HandleMachineQH(TCHAR *Tinfo, ChessProgramState *cps);         //ǳ��
extern void HandleMachineQB(TCHAR *Tinfo, ChessProgramState *cps);		 //���
extern void HandleMachineGGyq(TCHAR *Tinfo, ChessProgramState *cps);         //cyclone 105


void			//�������������������Ϣ
HandleMachineMove(TCHAR *Tinfo, ChessProgramState *cps){

    //while (*message == '\007'){ //Kludge to ignore BEL characters
    //	message++; 
    //}

    switch(cps->ucci){
        case UCCI_UCCI_ms:
		case UCCI_UCCI_OLD:
			HandleMachineUCCI162(Tinfo, cps);
            break;
		case UCCI_GGchess:
			HandleMachineGGyq(Tinfo, cps);
            break;
        case UCCI_CYC105:
			HandleMachineCYC105(Tinfo, cps);
            break;
        case UCCI_QianHong:
			HandleMachineQH(Tinfo, cps);
            break;  
		case UCCI_QiBing:
			HandleMachineQB(Tinfo, cps);
			break;
        default:
			LogOut(_T("\nδ������Ϣ...\n"));
			LogOut(Tinfo);
            break;
    }  
}


