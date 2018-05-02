#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"

void
TruncateGame(dispboard_t* pDis){  //��ƽ
    /*if (DIS.forwardMostMove > DIS.currentMove) {*/
    if (pDis->pos->gply > pDis->pos->curStep) {
        //if (DIS.gameInfo.resultDetails != NULL) {
        //	free(DIS.gameInfo.resultDetails);
        //	DIS.gameInfo.resultDetails = NULL;
        //	DIS.gameInfo.result = GameUnfinished;
        //}
        //DIS.pgn.resultDetails[0] = NULLCHAR;
        //DIS.pgn.cmresult = GameUnfinished;
        pDis->pgn->isFinish = GameUnfinished;
        //DIS.forwardMostMove = DIS.currentMove;
        pDis->pos->gply = pDis->pos->curStep;
        //HistorySet(DIS.parseList, DIS.backwardMostMove, DIS.forwardMostMove,
        //	DIS.currentMove-1);
    }
}

void           //����ע��
ReplaceComment(int index,char *text){
    int len;

    while (*text == '\n'){
        text++;
    }
    len = (int)strlen(text);
    while (len > 0 && text[len - 1] == '\n'){
        len--;
    }

    //	if (DIS.commentList[index] != NULL){
    //		free(DIS.commentList[index]);
    //	}

    //	if (len == 0) {
    //		DIS.commentList[index] = NULL;
    //		return;
    //	}
    //	DIS.commentList[index] = (char *) malloc(len + 2);
    //strncpy(DIS.commentList[index], text, len);
    //DIS.commentList[index][len] = '\n';
    //DIS.commentList[index][len + 1] = NULLCHAR;
}

void
CrushCRs(char *text){
    char *p = text;
    char *q = text;
    char ch;

    do {
        ch = *p++;
        if (ch == '\r') continue;
        *q++ = ch;
    } while (ch != '\0');
}

void            //�����岽��ע��
AppendComment(int index,char *text){  
    //	int oldlen, len;
    //	char *old;

    //CrushCRs(text);					//ȥ���س���
    //while (*text == '\n'){			//ȥ��ǰ��Ļ���
    //	text++;
    //}
    //len = (int)strlen(text);
    //while (len > 0 && text[len - 1] == '\n'){
    //	len--;
    //}//ȥ������Ļ���

    //if (len == 0){
    //	return;		//û��������
    //}

    //if (DIS.commentList[index] != NULL) {
    //	old = DIS.commentList[index];
    //	oldlen = (int)strlen(old);
    //	DIS.commentList[index] = (char *) malloc(oldlen + len + 2);
    //	//strcpy(commentList[index], old);
    //	StringCbCopy(DIS.commentList[index],(oldlen + len ), old);
    //	free(old);
    //	strncpy(&DIS.commentList[index][oldlen], text, len);
    //	DIS.commentList[index][oldlen + len] = '\n';
    //	DIS.commentList[index][oldlen + len + 1] = NULLCHAR;
    //} 
    //else {
    //	DIS.commentList[index] = (char *) malloc(len + 2);
    //	strncpy(DIS.commentList[index], text, len);
    //	DIS.commentList[index][len] = '\n';
    //	DIS.commentList[index][len + 1] = NULLCHAR;
    //}
}