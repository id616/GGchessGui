#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"



//��ָ�����Ƶ����ݿ�
int SqliteOpenDataBase(sqlite3 **db, char* dbname){
    char buf[MAX_PATH];
	setlocale(LC_CTYPE, "chs");
    sprintf_s(buf,MAX_PATH,"%S%s",installDir,dbname);

    int rc = sqlite3_open(buf,db);

    if(rc){
        LogOut((TCHAR*)sqlite3_errmsg(*db));
		LogOut(_T("-------------���ܴ��趨�ļ�-------------\n"));
    }

    return rc;
}

