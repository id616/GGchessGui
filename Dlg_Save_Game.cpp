#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"

//������ִ���

void DLG_SAVE_GAME_Event(dispboard_t *pDis){
	
	if(pDis->hwndSaveDlg == NULL){			//
		//�����Ի���

	}
	else{
		SendMessage(pDis->hwndSaveDlg,WM_CLOSE,0,0);		//�رմ���
	}

}