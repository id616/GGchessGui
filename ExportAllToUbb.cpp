#include "stdafx.h"
#include "GGchess.h"
#include "chess.h"
#include "data.h"
#include "pregen.h"
#include <shellapi.h>
#include <sys/stat.h>
#include <io.h>
#include <fcntl.h>
#include <share.h>


void    ExportAllUbb         (void){

	//1, �½���һ���ļ�;

	FILE			    *UbbFile;

    TCHAR buf[MAX_PATH];
    swprintf_s(buf,MAX_PATH,_T("%s%s"),installDir,_T("ubb.txt"));
    errno_t err = _wfopen_s(&UbbFile,buf,_T("w"));  
    if(err != 0){
        //int ddd = 0;
        MessageBox(NULL,_T("���ܴ�UBB�ļ�"),_T("������"),MB_OK);
        return ;
    }

	int num = 0;       //�����ľ���

	//��pgn���ݿ�, ����һ�� PlanID //��Ϊ��־

	fclose(UbbFile);
   
}