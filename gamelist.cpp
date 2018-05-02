#include "stdafx.h"
#include "chess.h"
#include "data.h"


#include <stdio.h>
#include <errno.h>
#if STDC_HEADERS
# include <stdlib.h>
# include <string.h>
#else /* not STDC_HEADERS */
# if HAVE_STRING_H
#  include <string.h>
# else /* not HAVE_STRING_H */
#  include <strings.h>
# endif /* not HAVE_STRING_H */
#endif /* not STDC_HEADERS */


///* Clear an existing GameInfo structure.
// */
void ClearGameInfo(PGN *pgn){

	swprintf_s(pgn->opera, sizeof(pgn->opera) / sizeof(TCHAR), _T("%s"), _T("lgl"));

    //�õ���ǰ����
	_tzset();    
	_wstrdate_s(pgn->date, sizeof(pgn->date)/sizeof(TCHAR));

	//�õ��ص�
	swprintf_s(pgn->pevent, sizeof(pgn->pevent) / sizeof(TCHAR), _T("%s"), _T("�Ѽ����"));

	//PlanId
	pgn->PlanID = -1;
	//��ֱ��
	pgn->pid    = -1;

	//��ע
	swprintf_s(pgn->note, sizeof(pgn->note) / sizeof(TCHAR), _T("%s"), _T("��ע"));

	//round
	//sprintf_s(pgn->round,sizeof(pgn->round),"%s","0-0");

	//����
	pgn->rate =  1;

	//pgn->Relo =  2028;
	//pgn->Belo =  2018;

	//��ʱ��ʽ
	swprintf_s(pgn->RtimeControl, sizeof(pgn->RtimeControl) / sizeof(TCHAR), _T("%s"), _T("10-1-5"));
	swprintf_s(pgn->BtimeControl, sizeof(pgn->BtimeControl) / sizeof(TCHAR), _T("%s"), _T("10-1-5"));

	pgn->isFenGame = FALSE;

	swprintf_s(pgn->result, sizeof(pgn->result) / sizeof(TCHAR), _T("%s"), _T("δ֪"));

	//
	pgn->score     = BOOK_NOT_RESULT;

	//
	pgn->isChecked  = FALSE;
	pgn->isLearned  = FALSE;
	pgn->isFinish   = TRUE;

	//����������
	pgn->yqScore   = 90000;


}

