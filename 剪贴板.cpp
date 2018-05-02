#include "stdafx.h"
#include "chess.h"
#include "data.h"
#include "resource.h"

//#include "config.h"

//#include <windows.h>   /* required for all Windows applications */
//#include <stdio.h>
//#include <stdlib.h>
//#include <malloc.h>
#include <sys/stat.h>

//#include "common.h"
//#include "winboard.h"
//#include "frontend.h"
//#include "backend.h"
//#include "wclipbrd.h"

/* Imports from winboard.c */
//extern HWND hwndMain;

/* File globals */
static char *copyTemp;
static char *pasteTemp;

VOID 
CopyFENToClipboard(dispboard_t* pDis){
  //char *fen = NULL;
  TCHAR fen[MSG_SIZ];


  PositionToFEN(pDis,fen,pDis->pos->curStep,UCCI_UCCI_ms);
  //if (!fen) {
  //  DisplayError("Unable to convert position to FEN.", 0);
  //  return;
  //}
  if (!CopyTextToClipboard(fen))
	  LogOut(L"Unable to copy FEN to clipboard.");
  //free(fen);
}



void SendAllEvalToClipBoardFlip(dispboard_t* pDis){


	//ChessProgramState *cps;

	//cps = &pDis->first;

	//if (cps->cps_stat == Cps_Thinking || cps->cps_stat == Cps_Pondering || cps->cps_stat == Cps_Analyse
	//	|| cps->cps_stat == Cps_NotLoad){
	//	LogOut(_T("\n�Բ��𣬵�ǰ��������˼����û�м��سɹ������������ص���Ϣ\n")); return;
	//}

	//dispboard_t *NewDis = new dispboard_t;
	//memcpy(NewDis, pDis, sizeof(dispboard_t));

	//CopyGameToClipboardUBB(NewDis, FALSE);

	//SendCurPosToProgram(pDis, cps);

	//SendToProgram(L"cmd eval\n", cps);

	////dispboard_t *NewDis = new dispboard_t;
	////memcpy(NewDis, pDis, sizeof(dispboard_t));

	////board_red2black(NewDis);
	////SendAllEvalToClipBoard(pDis);

	//delete NewDis;

}

//���������Ϣ��������
void SendAllEvalToClipBoard(dispboard_t* pDis){
	
    ChessProgramState *cps;

	cps = &pDis->first;

	if(cps->cps_stat == Cps_Thinking || cps->cps_stat == Cps_Pondering || cps->cps_stat == Cps_Analyse 
		|| cps->cps_stat == Cps_NotLoad){
		LogOut(_T("\n�Բ��𣬵�ǰ��������˼����û�м��سɹ������������ص���Ϣ\n")); return;
	}

	CopyGameToClipboardUBB(pDis, FALSE);

	//SendOnlyFenToProgram(pDis, cps);
	SendCurPosToProgram(pDis, cps);

	SendToProgram(L"cmd eval\n", cps);

}


TCHAR *MoveToUBBove(TCHAR *pm){
	static TCHAR Ubb[32];
	//Ubb[0] = 'Z';
	//Ubb[1] = 'Z';
	//Ubb[2] = 'Z';
	//Ubb[3] = 'Z';
	Ubb[4] = 0;

	for(int i= 0; i<4; i++){
		TCHAR *p = pm + i;

		//uint16 name = *((uint16*)p);

		//int name = *p + ((*(p+1))<<8);

		TCHAR name = *p;

		switch(name){
			case L'��':
				Ubb[i] = '1';    //��
				break;			
			case L'��':
				Ubb[i] = '2';    //��
				break;
			case L'��':
				Ubb[i] = '3';    //��
				break;
			case L'��':
				Ubb[i] = '4';    //��
				break;
			case L'��':
				Ubb[i] = '5';    //��
				break;
			case L'ʿ':
				Ubb[i] = '6';    //ʿ
				break;
			case L'˧':
				Ubb[i] = '7';    //˧
				break;
			case L'��':
				Ubb[i] = '8';    //��
				break;
			case L'��':           //��
				Ubb[i] = '9';
				break;
			case L'��':		     //��
				Ubb[i] = 'A';
			case L'��':
				Ubb[i] = 'B';    //��
				break;	
			case L'һ':
				Ubb[i] = 'C';    //һ
				break;
			case L'��':
				Ubb[i] = 'D';    //1
				break;
			case L'��':           //��
				Ubb[i] = 'E';
				break;
			case L'��':		     //2
				Ubb[i] = 'F';
				break;			
			case L'��':           //��
				Ubb[i] = 'G';
				break;
			case L'��':
				Ubb[i] = 'H';    //3
				break;
			case L'��':
				Ubb[i] = 'I';    //��
				break;
			case L'��':
				Ubb[i] = 'J';    //4
				break;
			case L'��':
				Ubb[i] = 'K';    //��
				break;
			case L'��':
				Ubb[i] = 'L';    //5
				break;
			case L'��':
				Ubb[i] = 'M';    //��
				break;
			case L'��':
				Ubb[i] = 'N';    //6
				break;
			case L'��':
				Ubb[i] = 'O';    //��
				break;
			case L'��':
				Ubb[i] = 'P';    //7
				break;
			case L'��':
				Ubb[i] = 'Q';    //��
				break;
			case L'��':
				Ubb[i] = 'R';    //8
				break;
			case '��':
				Ubb[i] = 'S';    //��
				break;
			case L'��':
				Ubb[i] = 'T';    //9
				break;
			case L'��':
				Ubb[i] = 'X';    //��
				break;
			case L'��':
				Ubb[i] = 'Y';    //��
				break;
			case L'ƽ':
				Ubb[i] = 'Z';    //ƽ
				break;
			case L'ǰ':
				Ubb[i] = 'U';	 //ǰ
				break;
			case L'��':
				Ubb[i] = 'W';	 //��
				break;
			default:
				Ubb[i] = 'Z';
		}

	}

	return Ubb;
}


//1��[DhtmlXQ ]                                  UBB ��ʼ��־����ѡ
//2��[DhtmlXQ_ver]�ļ��汾[/DhtmlXQ_ver]         ����֧�ֲ�ͬ�ļ��汾  ��ѡ
//3��[DhtmlXQ_init]500,350[/DhtmlXQ_init]        ��һ���趨iframe��С  ��ѡ
//4��[DhtmlXQ_title]��ֱ���[/DhtmlXQ_title]
//5��[DhtmlXQ_event]��������[/DhtmlXQ_event]
//6��[DhtmlXQ_date]��������[/DhtmlXQ_date]
//7��[DhtmlXQ_place]�����ص�[/DhtmlXQ_place]
//8��[DhtmlXQ_round]�����ִ�[/DhtmlXQ_round]
//9��[DhtmlXQ_red]�췽[/DhtmlXQ_red]             ����������� ���� (�ȼ�)
//9.1��[DhtmlXQ_redteam]�췽����[/DhtmlXQ_redteam]  
//9.2��[DhtmlXQ_redlevel]�췽�ȼ�[/DhtmlXQ_redlevel] 
//9.3��[DhtmlXQ_redrating]�췽�ȼ���[/DhtmlXQ_redrating]
//9.4��[DhtmlXQ_redeng]�췽Ӣ����[/DhtmlXQ_redeng]
//9.5��[DhtmlXQ_redtime]�췽��ʱ[/DhtmlXQ_redtime]
//10��[DhtmlXQ_black]�ڷ�[/DhtmlXQ_black]        ��ʽ���������� ���� (��ʦ)
//10.1��[DhtmlXQ_blackteam]�ڷ�����[/DhtmlXQ_blackteam]  
//10.2��[DhtmlXQ_blacklevel]�ڷ��ȼ�[/DhtmlXQ_blacklevel] 
//10.3��[DhtmlXQ_blackrating]�ڷ��ȼ���[/DhtmlXQ_blackrating]
//10.4��[DhtmlXQ_blackeng]�ڷ�Ӣ����[/DhtmlXQ_blackeng]
//10.5��[DhtmlXQ_blacktime]�ڷ���ʱ[/DhtmlXQ_blacktime]
//11��[DhtmlXQ_result]�Ծֽ��[/DhtmlXQ_result]  
//12��[DhtmlXQ_open]����[/DhtmlXQ_open]          ʹ�ò���
//12��[DhtmlXQ_remark]��ע��Ա[/DhtmlXQ_remark]
//13��[DhtmlXQ_author]��������[/DhtmlXQ_author]                ����¼����Ա
//14��[DhtmlXQ_binit]��ʼ����[/DhtmlXQ_binit]              14��15����ѡ��һ
//15��[DhtmlXQ_movelist]�ŷ�����[/DhtmlXQ_movelist]        14��15����ѡ��һ
//16��[DhtmlXQ_comment0]ע��0[/DhtmlXQ_comment0]
//������������
//������������  ע��ʹ��comment�����ֵ���ʽ��ע���еĻ���ȫ�á�||�����档
//������������
//17��[DhtmlXQ_commentn]ע��n[/DhtmlXQ_commentn]
//18��[DhtmlXQ_type]�������|n[/DhtmlXQ_type] ȫ�֡����֡��во֡��ž֡������о֡�ʵ�òо֡�ʵս�о�
//19��[DhtmlXQ_timerule]ʱ�����[/DhtmlXQ_timerule]  ʱ��������廹�ǿ���
//20��[DhtmlXQ_endtype]������ʽ[/DhtmlXQ_endtype] ����������ͣ��кͣ�������Ա����������
//21��[DhtmlXQ_owner]��������[/DhtmlXQ_owner] ������˭����
//22��[DhtmlXQ_other]������Ϣ[/DhtmlXQ_other]
//23��[DhtmlXQ_firstnum]��ʼ���[/DhtmlXQ_firstnum]
//24��[DhtmlXQ_length]�ŷ�����[/DhtmlXQ_length]
//25��[DhtmlXQ_gametype]�������[/DhtmlXQ_gametype] ���塢���塢�����塢δ֪
//26��[DhtmlXQ_class]��ַ���[/DhtmlXQ_class] ���磺�������¡���ʦ�Ծ֡���������
//27��[DhtmlXQ_refer]������Դ[/DhtmlXQ_refer]
//28��[/DhtmlXQ ]                                         UBB ������־����ѡ
//
//���⻹���� adddate[���ʱ��] hits[����] price[�۸�] hidden[�Ƿ�����˽��]  ����Ŀ����Щ���п���
//
//���µ� DhtmlXQ ֧���ļ��Ͱ�װָ�����ص�ַ��http://www.dpxq.com/hldcg/share/soft/
//
//DhtmlXQ��̬����Ŀǰ�ɵ���UBB���롢HTML���롢�ı����ס��ı���ͼ���ֹ��ܣ�
//
//���ೣ�����׶���ֱ��ת���ɱ���̬���̴��룬����Ҫ����ҳ����ʾ��ת�����ס���ť����


void CopyUBBToClipboard(dispboard_t* pDis){

   TCHAR* buf = EvalInfo;
   PGN* pgn = pDis->pgn;

   const TCHAR* pweb =
	   L"<center>"
	   L"[DhtmlXQ]"
	   L"[DhtmlXQ_ver]www_dpxq_com[/DhtmlXQ_ver]";

   const TCHAR* ptitle =
	   L"[DhtmlXQ_init]500,350[/DhtmlXQ_init]"
	   L"[DhtmlXQ_title]";
   const TCHAR* ptitle_end =
	   L"[/DhtmlXQ_title]";

   const TCHAR* pred =
	   L"[DhtmlXQ_redteam]";
   const TCHAR* pred_end =
	   L"[/DhtmlXQ_redteam]";
   const TCHAR* pblack =
	   L"[DhtmlXQ_blackteam]";
   const TCHAR* pblack_end =
	   L"[/DhtmlXQ_blackteam]";
   const TCHAR* presult_start =
	   L"[DhtmlXQ_result]";
   const TCHAR* presult_end =
	   L"[/DhtmlXQ_result]";
   const TCHAR* pmove =
	   L"[DhtmlXQ_movelist]";
   const TCHAR* pmove_end =
	   L"[/DhtmlXQ_movelist]";
   const TCHAR* ptype =
	   L"[DhtmlXQ_type]";
   const TCHAR* ptype_end =
	   L"[/DhtmlXQ_type]";

   const TCHAR* prtime =
	   L"[DhtmlXQ_redtime]";
   const TCHAR* prtime_end =
	   L"[/DhtmlXQ_redtime]";
   const TCHAR* pbtime =
	   L"[DhtmlXQ_blacktime]";
   const TCHAR* pbtime_end =
	   L"[/DhtmlXQ_blacktime]";

   const TCHAR* pother =
	   L"[DhtmlXQ_other]";

   const TCHAR* pother_end =
	   L"[/DhtmlXQ_other]";

   const TCHAR* pfnum =
		L"[DhtmlXQ_firstnum]";
   const TCHAR* pfnum_end =
		L"[/DhtmlXQ_firstnum]";

   const TCHAR* prefer =
		L"[DhtmlXQ_refer]http://www.ggchess.com/[/DhtmlXQ_refer]"
		L"[/DhtmlXQ]</center>";

	//const char *pend =
	//	"UBB ������ [url=http://www.xiangqi.com.cn/down/view_58.html][color=Blue]���尮����[/color][/url] 
	//	" ������ɡ� [url=http://www.xiangqi.com.cn/files/help/ubb.swf][color=Red]�����˴��ۿ���Ƶ�̳�[/color][/url]";

   swprintf_s(buf, EVAL_INFO_SIZE, L"%s", pweb);

	//ptitle

   wcscat_s(buf, EVAL_INFO_SIZE, ptitle);

	//strcat_s(buf,sizeof(buf), pgn->note);

   wcscat_s(buf, EVAL_INFO_SIZE, L"-= �Ѽ����� =-   ");

   wcscat_s(buf, EVAL_INFO_SIZE, (pgn->Red));

   wcscat_s(buf, EVAL_INFO_SIZE, L" vs ");

   wcscat_s(buf, EVAL_INFO_SIZE, (pgn->Black));

   wcscat_s(buf, EVAL_INFO_SIZE, L" ");

   wcscat_s(buf, EVAL_INFO_SIZE, (pgn->result));

   wcscat_s(buf, EVAL_INFO_SIZE, ptitle_end);

   wcscat_s(buf, EVAL_INFO_SIZE, pred);
   wcscat_s(buf, EVAL_INFO_SIZE, (pgn->Red));
   wcscat_s(buf, EVAL_INFO_SIZE, pred_end);

   wcscat_s(buf, EVAL_INFO_SIZE, pblack);
   wcscat_s(buf, EVAL_INFO_SIZE, (pgn->Black));
   wcscat_s(buf, EVAL_INFO_SIZE, pblack_end);

	wcscat_s(buf, EVAL_INFO_SIZE, presult_start);
	wcscat_s(buf, EVAL_INFO_SIZE, (pgn->result));
	wcscat_s(buf, EVAL_INFO_SIZE, presult_end);

	wcscat_s(buf, EVAL_INFO_SIZE, pmove);

	for(int i = 0; i < pDis->pos->gply; i++){
		TCHAR mbuf[64];
		//char *pm = pDis->parseList[i];
		//sprintf_s(mbuf,sizeof(mbuf),"%C%C-%C%C ",ToUpper(pm[0]),ToUpper(pm[1]),ToUpper(pm[2]),ToUpper(pm[3]));	

		int move = pDis->pos->His[i+1].move; 

		int from = FROM(move);
		int to   = TO(move);

		int fx   = StoX(from) - 3;
		int fy   = StoY(from) - 3;

		int tx   = StoX(to) - 3;
		int ty   = StoY(to) - 3;

		int num    = i;

		int n1000  = i / 1000;
		int n100   = (i - n1000 * 1000)/100;
		int n10    = (i - n1000 * 1000 - n100 * 100)/10;
		int n      = i % 10;

		//swprintf_s(mbuf, sizeof(mbuf) / sizeof(TCHAR), L"%d%d%d%d%s%d%d%d%d", fx, fy, tx, ty, MoveToUBBove(pDis->moveListName[i] + 4), n1000, n100, n10, n);

		swprintf_s(mbuf, sizeof(mbuf) / sizeof(TCHAR), L"%d%d%d%d", fx, fy, tx, ty);

		wcscat_s(buf, EVAL_INFO_SIZE, mbuf);
	}

	wcscat_s(buf, EVAL_INFO_SIZE, pmove_end);

	wcscat_s(buf, EVAL_INFO_SIZE, ptype);
	wcscat_s(buf, EVAL_INFO_SIZE, L"ȫ��");
	wcscat_s(buf, EVAL_INFO_SIZE, ptype_end);
	wcscat_s(buf, EVAL_INFO_SIZE, prtime);
	wcscat_s(buf, EVAL_INFO_SIZE, (pgn->RtimeControl));
	wcscat_s(buf, EVAL_INFO_SIZE, prtime_end);
	wcscat_s(buf, EVAL_INFO_SIZE, pbtime);
	wcscat_s(buf, EVAL_INFO_SIZE, (pgn->BtimeControl));
	wcscat_s(buf, EVAL_INFO_SIZE, pbtime_end);
	wcscat_s(buf, EVAL_INFO_SIZE, pother);
	wcscat_s(buf, EVAL_INFO_SIZE, (pgn->note));
	wcscat_s(buf, EVAL_INFO_SIZE, pother_end);
	wcscat_s(buf, EVAL_INFO_SIZE, pfnum);
	wcscat_s(buf, EVAL_INFO_SIZE, pfnum_end);
	wcscat_s(buf, EVAL_INFO_SIZE, prefer);
	wcscat_s(buf, EVAL_INFO_SIZE, L"<br><center>[url=http://www.ggchess.com/][color=Blue]�Ѽ����延ӭ��[/color][/url]</center>");


	if (!CopyTextToClipboard(buf)) {
		LogOut(L"Cannot copy text to clipboard");
	}
	else{
		LogOut(_T("\nUBB����Ѹ��Ƶ�������\n"));
	}


}

void
CopyGameToClipboardUBB(dispboard_t* pDis, BOOL isStart){
  
	TCHAR *buf = EvalInfo;

	const TCHAR* UbbF3Start =
		 L"[align=center]"
		 L"[DhtmlXQ]"
		 L"[DhtmlXQ_ver]www_dpxq_com[/DhtmlXQ_ver]"
		 L"[DhtmlXQ_init]500,350[/DhtmlXQ_init]"
		 L"[DhtmlXQ_title]�Ѽ����� ��־��� ��ϸ��Ϣ[/DhtmlXQ_title]"
		 L"[DhtmlXQ_binit]";

	const TCHAR* UbbListStart = L"[/DhtmlXQ_binit][DhtmlXQ_movelist]";

	const TCHAR* UbbListEnd =
		 L"[/DhtmlXQ_movelist]"
		 L"[DhtmlXQ_refer]http://www.ggchess.com/[/DhtmlXQ_refer]"
		 L"[DhtmlXQ_generator]www.ggchess.com �Ѽ�����[/DhtmlXQ_generator]"
		 L"[/DhtmlXQ][/align]";

	swprintf_s(buf,EVAL_INFO_SIZE,L"%s", UbbF3Start);

	if(isStart){
		ToStartEvent(pDis);
	}
	//��ʼ����
	//
    TCHAR pchess[65];
	//memset(pchess,'9',64);
	for (int i = 0; i < 65; i++){
		pchess[i] = '9';
	}
	pchess[64] = 0;
	
	int pc[5];
	int k;

	//�쳵
	pc[0] = 0;
	pc[1] = 8 * 2;
	k     = 0;
	for(int from = PieceListStart(pDis->pos,RCHE); from > 0x32; from = NextPiece(pDis->pos,from)){
	   TCHAR x = StoX(from) - 3 + '0';
	   TCHAR y = StoY(from) - 3 + '0';
	   pchess[pc[k]    ] = x;
	   pchess[pc[k] + 1] = y;
	   k++;	  
	}
	//����
	pc[0] = 1 * 2;
	pc[1] = 7 * 2;
	k     = 0;
	for(int from = PieceListStart(pDis->pos,RMA); from > 0x32; from = NextPiece(pDis->pos,from)){
		TCHAR x = StoX(from) - 3 + '0';
		TCHAR y = StoY(from) - 3 + '0';
	   pchess[pc[k]    ] = x;
	   pchess[pc[k] + 1] = y;
	   k++;	  
	}
	//����
	pc[0] = 2 * 2;
	pc[1] = 6 * 2;
	k     = 0;
	for(int from = PieceListStart(pDis->pos,RXIANG); from > 0x32; from = NextPiece(pDis->pos,from)){
		TCHAR x = StoX(from) - 3 + '0';
		TCHAR y = StoY(from) - 3 + '0';
	   pchess[pc[k]    ] = x;
	   pchess[pc[k] + 1] = y;
	   k++;	  
	}
	//����
	pc[0] = 3 * 2;
	pc[1] = 5 * 2;
	k     = 0;
	for(int from = PieceListStart(pDis->pos,RSHI); from > 0x32; from = NextPiece(pDis->pos,from)){
		TCHAR x = StoX(from) - 3 + '0';
		TCHAR y = StoY(from) - 3 + '0';
	   pchess[pc[k]    ] = x;
	   pchess[pc[k] + 1] = y;
	   k++;	  
	}
	//����
	pc[0] = 9  * 2;
	pc[1] = 10 * 2;
	k     = 0;
	for(int from = PieceListStart(pDis->pos,RPAO); from > 0x32; from = NextPiece(pDis->pos,from)){
		TCHAR x = StoX(from) - 3 + '0';
		TCHAR y = StoY(from) - 3 + '0';
	   pchess[pc[k]    ] = x;
	   pchess[pc[k] + 1] = y;
	   k++;	  
	}
	//��˧
	pc[0] = 4 * 2;
	pc[1] = 4 * 2;
	k     = 0;
	for(int from = PieceListStart(pDis->pos,RKING); from > 0x32; from = NextPiece(pDis->pos,from)){
		TCHAR x = StoX(from) - 3 + '0';
		TCHAR y = StoY(from) - 3 + '0';
	   pchess[pc[k]    ] = x;
	   pchess[pc[k] + 1] = y;
	   k++;	  
	}
	//��
	pc[0] = 11*2;
	pc[1] = 12*2;
	pc[2] = 13*2;
	pc[3] = 14*2;
	pc[4] = 15*2;
	k = 0; 
	for(int from = PieceListStart(pDis->pos,RPAWN); from > 0x32; from = NextPiece(pDis->pos,from)){
		TCHAR x = StoX(from) - 3 + '0';
		TCHAR y = StoY(from) - 3 + '0';
	   pchess[pc[k]    ] = x;
	   pchess[pc[k] + 1] = y;
	   k++;	
	}

	//
	//�ڳ�
	pc[0] = 16 * 2;
	pc[1] = 24 * 2;
	k     = 0;
	for(int from = PieceListStart(pDis->pos,BCHE); from > 0x32; from = NextPiece(pDis->pos,from)){
		TCHAR x = StoX(from) - 3 + '0';
		TCHAR y = StoY(from) - 3 + '0';
	   pchess[pc[k]    ] = x;
	   pchess[pc[k] + 1] = y;
	   k++;	  
	}
	//����
	pc[0] = 17 * 2;
	pc[1] = 23 * 2;
	k     = 0;
	for(int from = PieceListStart(pDis->pos,BMA); from > 0x32; from = NextPiece(pDis->pos,from)){
		TCHAR x = StoX(from) - 3 + '0';
		TCHAR y = StoY(from) - 3 + '0';
	   pchess[pc[k]    ] = x;
	   pchess[pc[k] + 1] = y;
	   k++;	  
	}
	//����
	pc[0] = 18 * 2;
	pc[1] = 22 * 2;
	k     = 0;
	for(int from = PieceListStart(pDis->pos,BXIANG); from > 0x32; from = NextPiece(pDis->pos,from)){
		TCHAR x = StoX(from) - 3 + '0';
		TCHAR y = StoY(from) - 3 + '0';
	   pchess[pc[k]    ] = x;
	   pchess[pc[k] + 1] = y;
	   k++;	  
	}
	//����
	pc[0] = 19 * 2;
	pc[1] = 21 * 2;
	k     = 0;
	for(int from = PieceListStart(pDis->pos,BSHI); from > 0x32; from = NextPiece(pDis->pos,from)){
		TCHAR x = StoX(from) - 3 + '0';
		TCHAR y = StoY(from) - 3 + '0';
	   pchess[pc[k]    ] = x;
	   pchess[pc[k] + 1] = y;
	   k++;	  
	}
	//����
	pc[0] = 25  * 2;
	pc[1] = 26  * 2;
	k     = 0;
	for(int from = PieceListStart(pDis->pos,BPAO); from > 0x32; from = NextPiece(pDis->pos,from)){
		TCHAR x = StoX(from) - 3 + '0';
		TCHAR y = StoY(from) - 3 + '0';
	   pchess[pc[k]    ] = x;
	   pchess[pc[k] + 1] = y;
	   k++;	  
	}
	//�ڽ�
	pc[0] = 20 * 2;
	pc[1] = 20 * 2;
	k     = 0;
	for(int from = PieceListStart(pDis->pos,BKING); from > 0x32; from = NextPiece(pDis->pos,from)){
		TCHAR x = StoX(from) - 3 + '0';
		TCHAR y = StoY(from) - 3 + '0';
	   pchess[pc[k]    ] = x;
	   pchess[pc[k] + 1] = y;
	   k++;	  
	}
	//��
	pc[0] = 27*2;
	pc[1] = 28*2;
	pc[2] = 29*2;
	pc[3] = 30*2;
	pc[4] = 31*2;
	k = 0; 
	for(int from = PieceListStart(pDis->pos,BPAWN); from > 0x32; from = NextPiece(pDis->pos,from)){
		TCHAR x = StoX(from) - 3 + '0';
		TCHAR y = StoY(from) - 3 + '0';
	   pchess[pc[k]    ] = x;
	   pchess[pc[k] + 1] = y;
	   k++;	
	}

	wcscat_s(buf, EVAL_INFO_SIZE , pchess);
	wcscat_s(buf, EVAL_INFO_SIZE , UbbListStart);

	if(isStart){
		for(int i = 0; i < pDis->pos->gply; i++){
			TCHAR mbuf[64];
			//char *pm = pDis->parseList[i];
			//sprintf_s(mbuf,sizeof(mbuf),"%C%C-%C%C ",ToUpper(pm[0]),ToUpper(pm[1]),ToUpper(pm[2]),ToUpper(pm[3]));	

			int move = pDis->pos->His[i+1].move; 

			int from = FROM(move);
			int to   = TO(move);

			int fx   = StoX(from) - 3;
			int fy   = StoY(from) - 3;

			int tx   = StoX(to) - 3;
			int ty   = StoY(to) - 3;

			int num    = i;

			int n1000  = i / 1000;
			int n100   = (i - n1000 * 1000)/100;
			int n10    = (i - n1000 * 1000 - n100 * 100)/10;
			int n      = i % 10;

			//sprintf_s(mbuf,sizeof(mbuf),"%d%d%d%d%s%d%d%d%d",fx,fy,tx,ty,MoveToUBBove(pDis->moveListName[i]+4),n1000,n100,n10,n);

			swprintf_s(mbuf, sizeof(mbuf) / sizeof(TCHAR), L"%d%d%d%d", fx, fy, tx, ty);

			wcscat_s(buf, EVAL_INFO_SIZE , mbuf);
		}
	}
	else{
		for(int i = pDis->pos->curStep; i < pDis->pos->gply; i++){
			TCHAR mbuf[64];
			//char *pm = pDis->parseList[i];
			//sprintf_s(mbuf,sizeof(mbuf),"%C%C-%C%C ",ToUpper(pm[0]),ToUpper(pm[1]),ToUpper(pm[2]),ToUpper(pm[3]));	

			int move = pDis->pos->His[i+1].move; 

			int from = FROM(move);
			int to   = TO(move);

			int fx   = StoX(from) - 3;
			int fy   = StoY(from) - 3;

			int tx   = StoX(to) - 3;
			int ty   = StoY(to) - 3;

			int num    = i;

			int n1000  = i / 1000;
			int n100   = (i - n1000 * 1000)/100;
			int n10    = (i - n1000 * 1000 - n100 * 100)/10;
			int n      = i % 10;

			//sprintf_s(mbuf,sizeof(mbuf),"%d%d%d%d%s%d%d%d%d",fx,fy,tx,ty,MoveToUBBove(pDis->moveListName[i]+4),n1000,n100,n10,n);

			swprintf_s(mbuf, sizeof(mbuf) / sizeof(TCHAR), L"%d%d%d%d", fx, fy, tx, ty);

			wcscat_s(buf, EVAL_INFO_SIZE, mbuf);
		}
	}

	wcscat_s(buf, EVAL_INFO_SIZE, UbbListEnd);



	if (!CopyTextToClipboard(buf)) {
		LogOut(_T("Cannot copy text to clipboard"));
	}
	else{
		if(isStart){
			ToEndEvent(pDis);
			LogOut(_T("\nJAVA����Ѹ��Ƶ�������\n"));			
		}
	}


	

//[DhtmlXQ]
//[DhtmlXQ_ver]www_dpxq_com[/DhtmlXQ_ver]
//[DhtmlXQ_init]500,350[/DhtmlXQ_init]
//[DhtmlXQ_binit]9999474859999999999999458699999999994241405299999999994384199999[/DhtmlXQ_binit]
//[DhtmlXQ_movelist64]47254262[/DhtmlXQ_movelist]
//[DhtmlXQ_refer]http%3A//ggchess.game.topzj.com/%0D%0Ahttp%3A//ggchess.game.topzj.com/viewthread.php%3Ftid%3D19292%26page%3D1%26extra%3Dpage%253D1[/DhtmlXQ_refer]
//[DhtmlXQ_generator]www.dpxq.com[/DhtmlXQ_generator]
//[/DhtmlXQ]

//�ͻ��˱��ָ�� ���׾���������ŷ������������¼���������Ͻ�Ϊ(0,0)�����½�Ϊ(8,9)��
//���硰�ڶ�ƽ�塱����¼Ϊ��7747��������򵥵ĳ����¼��ʽ��
//�����ʽΪ��������ʿ˧ʿ�������ڱ���������������ʿ��ʿ�����������������䡱��˳��
//��¼�Ķ�Ϊ�������꣬û�е�������99���档�����Ŀ����֧�ֲо���ʾ 
//ע�⣺[DhtmlXQ_comment+��ǰ�ŷ������+]+ע���ı�+[/DhtmlXQ_comment+��ǰ�ŷ������+]
//����DhtmlXQ_comment��ע��������ַ�����
//���磺[DhtmlXQ_comment0]�������׸մ�ʱ������ע��[/DhtmlXQ_comment0]



}


int 
CopyTextToClipboard(TCHAR *text)
{

	dispboard_t* pDis = OBS[0];
	//BOOL bResult;                   // generic Boolean value

	int len = int(wcslen(text));

	if (len <= 0){
		LogOut(L"���ִ��޷����Ƶ������壡\n");
		return FALSE;
	}

	len += 1;

	if (!OpenClipboard(pDis->hwndThis))
	{
		return FALSE;
	}
	EmptyClipboard();

	HANDLE hData = ::GlobalAlloc(GMEM_MOVEABLE, (len)*sizeof(TCHAR));

	LPWSTR pData = (LPWSTR)::GlobalLock(hData);

	wcscpy_s(pData, len, text);

	GlobalUnlock(hData);

	SetClipboardData(CF_UNICODETEXT, hData);

	CloseClipboard();



	//if (!OpenClipboard(pDis->hwndThis))
	//{
	//	LogOut(L"Cannot open the Clipboard");
	//	return FALSE;
	//}

	//// Remove the current Clipboard contents
	//if (!EmptyClipboard())
	//{
	//	LogOut(L"Cannot empty the Clipboard");
	//	return FALSE;
	//}

	//if (::SetClipboardData(CF_UNICODETEXT, text) == NULL){
	//	LogOut(L"Unable to set Clipboard data");
	//	CloseClipboard();
	//	return FALSE;
	//}

	//CloseClipboard();


	///////////////////////////////////////////////////////////////////////////  
	//// 2. Open and empty clipboard. (OpenClipboard, EmptyClipboard)  
	//// 

	//if (!OpenClipboard(pDis->hwndThis)){
	//	return FALSE;
	//}

	//EmptyClipboard();

	///////////////////////////////////////////////////////////////////////////  
	//// 3. Create global buffer. (GlobalAlloc)  
	////  
	//TCHAR* lptstrCopy = (TCHAR *)HeapAlloc(GetProcessHeap(), 0, len);
 // 
	//if (lptstrCopy == NULL)
 //   {
 //       CloseClipboard();
 //       return FALSE;
 //   }

	//// Enable the privilege.

	//if (!LoggedSetLockPagesPrivilege(GetCurrentProcess(), TRUE))
	//{
	//	return FALSE;
	//}


 //   /////////////////////////////////////////////////////////////////////////  
 //   // 5. Copy text to the buffer. (strcpy)  
 //   //   
 //
 //   wcscpy_s(lptstrCopy,len, text);

 //   /////////////////////////////////////////////////////////////////////////  
 //   // 6. Unlock the buffer. (GlobalUnlock)  
 //   //   

 //  // GlobalUnlock(hglbCopy);

 //  /////////////////////////////////////////////////////////////////////////  
 //  // 7. Set buffer data to clipboard. (SetClipboardData)  
 //  //   

	//SetClipboardData(CF_TEXT, lptstrCopy);

	//bResult = HeapFree(GetProcessHeap(), 0, lptstrCopy);

 //  if (bResult != TRUE)
 //  {
	//   _tprintf(_T("Call to HeapFree has failed (%u)\n"), GetLastError());
 //  }


 //    /////////////////////////////////////////////////////////////////////////  
 //    // 8. Close clipboard. (CloseClipboard)  
 //    //   
 //
 //    CloseClipboard();
 //


//  dispboard_t* pDis = OBS[0];
//  /* some (most?) of the error checking may be overkill, 
//   * but hey, this is Windows 
//   */
//  HGLOBAL hGlobalMem;
//  LPVOID lpGlobalMem;
//  BOOL locked;
//#ifdef DEBUG_USE_DEBUG_FILE
//  UINT lockCount;
//#endif
//  DWORD err;
//
//  int a = wcslen(text)+2;
//
//  hGlobalMem = GlobalAlloc(GHND, a);
//  if (hGlobalMem == NULL) {
//	  LogOut(L"Unable to allocate memory for clipboard.");
//    return FALSE;
//  }
//  lpGlobalMem = GlobalLock(hGlobalMem);
//  if (lpGlobalMem == NULL) {
//	  LogOut(L"Unable to lock clipboard memory.");
//    GlobalFree(hGlobalMem);
//    return FALSE;
//  }
//  //lstrcpy((LPSTR)lpGlobalMem, text);
//  StringCbCopy((LPWSTR)lpGlobalMem,wcslen(text)+1,text);
//
//#ifdef DEBUG_USE_DEBUG_FILE
//  //if (appData.debugMode) {
//    lockCount = GlobalFlags(hGlobalMem) & GMEM_LOCKCOUNT;
//    fprintf(appData.debugFP, "CopyTextToClipboard(): lock count %d\n", lockCount);
//  //}
//#endif
//
//
//  SetLastError(NO_ERROR);
//  locked = GlobalUnlock(hGlobalMem);
//  err = GetLastError();
//
//#ifdef DEBUG_USE_DEBUG_FILE
//  //if (appData.debugMode) {
//    lockCount = GlobalFlags(hGlobalMem) & GMEM_LOCKCOUNT;
//    fprintf(appData.debugFP, "CopyTextToClipboard(): lock count %d\n", lockCount);
//  //}
//#endif
//
//
//  if (!locked) {
//    locked = !((err == NO_ERROR) || (err == ERROR_NOT_LOCKED));
//
//#ifdef DEBUG_USE_DEBUG_FILE
//    //if (appData.debugMode) {
//      fprintf(appData.debugFP, 
//	      "CopyTextToClipboard(): err %d locked %d\n", err, locked);
//    //}
//#endif
//
//  }
//  if (locked) {
//	  LogOut(L"Cannot unlock clipboard memory.");
//    GlobalFree(hGlobalMem);
//    return FALSE;
//  }
//  if (!OpenClipboard(pDis->hwndThis)) {
//	  LogOut(L"Cannot open clipboard.");
//    GlobalFree(hGlobalMem);
//    return FALSE;
//  }
//  if (!EmptyClipboard()) {
//	  LogOut(L"Cannot empty clipboard.");
//    return FALSE;
//  }
//  if (hGlobalMem != SetClipboardData(CF_TEXT, hGlobalMem)) {
//	  LogOut(L"Cannot copy text to clipboard.");
//    CloseClipboard();
//    GlobalFree(hGlobalMem);
//    return FALSE;
//  }
//  if (!CloseClipboard())
//	  LogOut(L"Cannot close clipboard.");
//  
  return TRUE;
}


VOID
PasteFENFromClipboard(dispboard_t *pDis)
{
  TCHAR *fen = NULL;
 
  if (!PasteTextFromClipboard(&fen, pDis)) {
	  LogOut(L"Unable to paste FEN from clipboard.");
      return;
  }

#ifdef DEBUG_USE_DEBUG_FILE
  //if (appData.debugMode) {
    fprintf(appData.debugFP, "PasteFenFromClipboard(): fen '%s'\n", fen);
  //}
#endif

	//if(fen == 

	//if(strstr(fen,"fen ") == NULL){
	//	SendToPlayerByColor("�Բ���Ҫճ���ľ��治���� fen ��ͷ���ַ���\n", ColorSeek, FALSE);
	//	free(fen);
	//	return;
	//}

  EditPositionPasteFEN(fen, pDis); /* call into backend */

  // ********************************
  pDis->book_num = 0; 

  if(pDis->gameMode == BeginningOfGame){
	  pDis->gameMode = EditGame;
  }

  //pDis->IsFenGame = TRUE; 
 

  swprintf_s(pDis->pgn->start_fen,sizeof(pDis->pgn->start_fen)/sizeof(TCHAR),L"%s",fen);

  FillBookbyPos(pDis,MST->book);

  free(fen);
}


VOID
PasteGameFromClipboard(dispboard_t* pDis)
{
  /* Write the clipboard to a temp file, then let LoadGameFromFile()
   * do all the work.  */
  //char *buf;
  //FILE *f;
  //size_t len;
  //if (!PasteTextFromClipboard(&buf, pDis)) {
  //  return;
  //}
  //if (!pasteTemp) {
  //  pasteTemp = _tempnam(NULL, "wbpt");
  //}
  ////f = fopen(pasteTemp, "w");
  //fopen_s(&f,pasteTemp, "w");
  //if (!f) {
  //  DisplayError("Unable to create temporary file.", 0);
  //  return;
  //}
  //len = fwrite(buf, sizeof(char), strlen(buf), f);
  //fclose(f);
  //if (len != strlen(buf)) {
  //  DisplayError("Error writing to temporary file.", 0);
  //  return;
  //}
  //LoadGameFromFile(pasteTemp, 0, "Clipboard", TRUE);
}


int 
PasteTextFromClipboard(TCHAR **text, dispboard_t* pDis)
{
	//dispboard_t* pDis = OBS[0];
	/* some (most?) of the error checking may be overkill, 
	* but hey, this is Windows 
	*/
	HANDLE hClipMem;
	LPVOID lpClipMem;
	BOOL locked = FALSE;
	DWORD err;
	UINT lockCount;

	if (!OpenClipboard(pDis->hwndThis)) {
		LogOut(L"Unable to open clipboard.");
		return FALSE;
	}
	hClipMem = GetClipboardData(CF_UNICODETEXT);
	if (hClipMem == NULL) {
		CloseClipboard();
		LogOut(L"No text in clipboard.");
		return FALSE;
	}
	lpClipMem = GlobalLock(hClipMem);
	if (lpClipMem == NULL) {
		CloseClipboard();
		LogOut(L"Unable to lock clipboard memory.");
			return FALSE;
	}
	//*text = (TCHAR *) malloc(GlobalSize(hClipMem)+1);

	*text = (TCHAR *)malloc((GlobalSize(hClipMem) + 1)*sizeof(TCHAR));
	if (!*text) {
		LogOut(L"Unable to allocate memory for text string.");
		CloseClipboard();
		return FALSE;
	}
	//lstrcpy(*text, (LPCSTR)lpClipMem);
	StringCbCopy(*text, (lstrlen((LPCWSTR)lpClipMem) + 1)*sizeof(TCHAR), (LPCWSTR)lpClipMem);

	SetLastError(NO_ERROR);

	/*suggested by Wilkin Ng*/
	lockCount = GlobalFlags(hClipMem) & GMEM_LOCKCOUNT;
	if (lockCount) {
		locked = GlobalUnlock(hClipMem);
	}

	err = GetLastError();

	if (!locked) {
		locked = !((err == NO_ERROR) || (err == ERROR_NOT_LOCKED));
	}
	if (locked) 
		LogOut(L"Unable to unlock clipboard memory.");

	if (!CloseClipboard())
		LogOut(L"Unable to close clipboard.");

	return TRUE;
}

VOID
DeleteClipboardTempFiles()
{
  if (copyTemp) remove(copyTemp);
  if (pasteTemp) remove(pasteTemp);
}
