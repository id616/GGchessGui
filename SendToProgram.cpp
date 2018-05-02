#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"

void
SendToProgram(TCHAR *message, ChessProgramState *cps){
	int count, outCount, error;
	TCHAR buf[MSG_SIZ];

	if (cps->pr == NULL){
		return;
	}
	Attention(cps);

	count = (int)wcslen(message);
	outCount = OutputToProcess(cps->pr, message, count, &error);

	//if(cps->ucci == UCCI_GGchess){			//ֻ�мѼ����淢����
	//	//char eme[FEN_SIZE];       
	//	//count = 0;
	//	//while((eme[count] = *(message+count)) != 0){
	//	//	count++;
	//	//}
	//	//if(count > FEN_SIZE || count == 0){
	//	//	MessageBox(NULL,_T("�����ˣ����͸��������Ϣ�����˻���"), _T("Error!"),MB_OK);
	//	//	return;
	//	//}

	//	//eme[count] = 0;   //����һ����β

	//	outCount = OutputToProcess(cps->pr, message, count, &error);
	//}
	//else{
	//	count = (int)wcslen(message);
	//	outCount = OutputToProcess(cps->pr, message, count, &error);
	//}

	if (outCount < count && !appData.Aexiting) {
		StringCbPrintf(buf,MSG_SIZ,_T("Error writing to %s chess program"), cps->UCCI_name);
		LogOut(buf);
	}
}