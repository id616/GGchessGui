#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"

void BoardDisplay(uint8 B256[256], TCHAR* reason){
    //��ʾ��ǰ��B256����

    //LogOut(ColorShout,reason,true);

    LogOut(reason);

    //ConsoleOutput(reason,(int)strlen(reason),true);

    static TCHAR *c_BoardStrSim[19] = {
        _T(" ��--��--��--��--��--��--��--��--�� \n"),
        _T(" ��  ��  ��  ���ܩ�����  ��  ��  �� \n"),
        _T(" ��--��--��--��--��--��--��--��--�� \n"),
        _T(" ��  ��  ��  �������ܩ�  ��  ��  �� \n"),
        _T(" ��--��--��--��--��--��--��--��--�� \n"),
        _T(" ��  ��  ��  ��  ��  ��  ��  ��  �� \n"),
        _T(" ��--��--��--��--��--��--��--��--�� \n"),
        _T(" ��  ��  ��  ��  ��  ��  ��  ��  �� \n"),
        _T(" ��--��--��--��--��--��--��--��--�� \n"),
        _T(" ��                              �� \n"),
        _T(" ��--��--��--��--��--��--��--��--�� \n"),
        _T(" ��  ��  ��  ��  ��  ��  ��  ��  �� \n"),
        _T(" ��--��--��--��--��--��--��--��--�� \n"),
        _T(" ��  ��  ��  ��  ��  ��  ��  ��  �� \n"),
        _T(" ��--��--��--��--��--��--��--��--�� \n"),
        _T(" ��  ��  ��  ���ܩ�����  ��  ��  �� \n"),
        _T(" ��--��--��--��--��--��--��--��--�� \n"),
        _T(" ��  ��  ��  �������ܩ�  ��  ��  �� \n"),
        _T(" ��--��--��--��--��--��--��--��--�� \n")
    };

    static TCHAR chessStr[16][4] = {
		_T("��"),
		_T("��"), _T("��"), _T("��"), _T("�R"), _T("܇"), _T("��"), _T("��"),
		_T("��"), _T("ʿ"), _T("��"), _T("��"), _T("��"), _T("��"), _T("��"),
		_T("��")
    };

    TCHAR buf[512];
    for(int r = 0; r < 19; r++){
		swprintf_s(buf, sizeof(buf) / sizeof(TCHAR), c_BoardStrSim[r]);
        if(r%2 == 0){
            TCHAR* p = c_BoardStrSim[r];
            for(int f = 0; f < 9; f++){
                int chess = B256[XYtoS(f+3, r/2+3)];
                //if(chess != 0){
                //    buf[f*4+1] = chessStr[chess][0];
                //    buf[f*4+2] = chessStr[chess][1];                    
                //}
                if(IsWhite(chess)){
                    Colorize(ColorShout,TRUE);
                    ConsoleOutput(buf+(f*4+0),1,TRUE);

                    Colorize(ColorSeek,TRUE);
                    ConsoleOutput(chessStr[chess],2,TRUE);

                    Colorize(ColorShout,TRUE);
                    ConsoleOutput(buf+(f*4+3),1,TRUE);
                }
                else if(IsBlack(chess)){
                    Colorize(ColorShout,TRUE);
                    ConsoleOutput(buf+(f*4+0),1,TRUE);

                    Colorize(ColorChannel1,TRUE);
                    ConsoleOutput(chessStr[chess],2,TRUE);

                    Colorize(ColorShout,TRUE);
                    ConsoleOutput(buf+(f*4+3),1,TRUE);
                }
                else{
                    Colorize(ColorShout,TRUE);
                    ConsoleOutput(buf+(f*4),4,TRUE);
                }
            } 
            //LogOut(ColorShout,"\n",true);
			LogOut(_T("\n"));
        }
        else{
            //LogOut(ColorShout,buf,true);
            LogOut(buf);
        }
    }
}

//void LogOut(ColorClass cc, char* data, bool NotShout){
//
//    int len = (int)strlen(data);
//    Colorize(cc,NotShout);
//
//    if(len > 0){       
//        LogOutput(data,len,TRUE);
//        //if(IsReturn){               //����һ���س�
//        //    LogOutput("\n",1,FALSE);
//        //}
//    }
//
//}