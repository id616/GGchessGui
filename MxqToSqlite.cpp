#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"
#include <sys/stat.h>
#include <io.h>
#include <fcntl.h>
#include <share.h>

BOOL		ReadMxqToPos   (dispboard_t* pDis, TCHAR* mxqFname){

   char mxqBuf[4096];
   char buf[256];
   char intbuf[32];
   char ss[256];

   int pFile;
   int i;

   setlocale(LC_CTYPE, "chs");

   PGN* pgn = pDis->pgn;

   errno_t err =   _wsopen_s(&pFile,mxqFname,_O_RDONLY, _SH_DENYNO, 
	   _S_IREAD | _S_IWRITE );

   if(err != 0){
	   //printf("info file %s does not exist.\n", mxqFname);
	   LogOut(L"info file %s does not exist.\n");
	   return FALSE;
   }
   //eof = fgets(mxqBuf, 2048, pFile);      //���ļ�PGN�����ڴ�

   int bytesread;

   if( ( bytesread = _read( pFile, mxqBuf, 4096 ) ) <= 0 ){

	   LogOut(L"info ERR Problem reading file %s\n"); // , mxqFname );

	   return FALSE;
   }

    _close( pFile );


	if(strlen(mxqBuf) < 20){
		return FALSE;
	}

    char* pcAnsi = mxqBuf; 
    // 
	//sprintf_s(pgn->pevent,sizeof(pgn->pevent),"%s","�������");
    
    //�õ�evnet�ĵĳ���
    int len = *pcAnsi;      //
    pcAnsi++;
	strCopybyNum(ss,len,pcAnsi);
	swprintf_s(pgn->pevent, sizeof(pgn->pevent) / sizeof(TCHAR), _T("%S"), ss);
    pcAnsi += len;

    //�õ��Ծֱ������ڵĳ���
    len = *pcAnsi;
    pcAnsi++;
	strCopybyNum(ss,len,pcAnsi);
	swprintf_s(pgn->date, sizeof(pgn->date) / sizeof(TCHAR), _T("%S"), ss);
    //�õ��췽-���-�ڷ����Ƴ���
     pcAnsi += len;   

    //�췽
    len   = *pcAnsi;
    pcAnsi ++;    
    for(i = 0; *pcAnsi != 0x2d; i++, len--){
		ss[i] = *(pcAnsi++);
    }
    ss[i] = 0; //���Ͻ�β
	swprintf_s(pgn->Red, sizeof(pgn->Red) / sizeof(TCHAR), _T("%S"), ss);
    //���
    pcAnsi++;    
    for(i = 0; *pcAnsi != 0x2d; i++, len--){
		ss[i] = *(pcAnsi++);
    }
    ss[i] = 0; //�Ծֽ��
	swprintf_s(pgn->result, sizeof(pgn->result) / sizeof(TCHAR), _T("%S"), ss);
    //�ڷ�
    pcAnsi ++;    
    for(i = 0; len>2;  i++, len--){
		ss[i] = *(pcAnsi++);
    }
    ss[i] = 0; //���Ͻ�β
	swprintf_s(pgn->Black, sizeof(pgn->Black) / sizeof(TCHAR), _T("%S"), ss);
    //�췽�ȼ���
    len = *pcAnsi;
    pcAnsi++;

    //strCopybyNum(PGN->pgn_white_elo,len,pcAnsi);
    //*****************************************************
    strCopybyNum(intbuf,len,pcAnsi);
	pgn->Relo = atoi(intbuf);
    //*****************************************************
    pcAnsi += len;
    
     //�ڷ��ȼ���
    len = *pcAnsi;
    pcAnsi++;

    //strCopybyNum(PGN->pgn_black_elo,len,pcAnsi);
    //*****************************************************
    strCopybyNum(intbuf,len,pcAnsi);
    pgn->Belo = atoi(intbuf);
    //*****************************************************

    pcAnsi += len;

     //��ʱ1
    len = *pcAnsi;
    pcAnsi++;
	ss[0] = 0;
	strcat_s(ss,sizeof(ss)," �췽��ʱ:");
    //strCopybyNum(PGN->use_time1,len,pcAnsi);
    //*****************************************************
    strCopybyNum(intbuf,len,pcAnsi);
	strcat_s(ss, sizeof(ss), intbuf);
    //PGN->use_time1 = atoi(intbuf);.............................................
    //*****************************************************

    pcAnsi += len;

    //��ʱ2
    len = *pcAnsi;
    pcAnsi++;
    //strCopybyNum(PGN->use_time2,len,pcAnsi);
    //*****************************************************
    strCopybyNum(intbuf,len,pcAnsi);
	strcat_s(ss, sizeof(ss), intbuf);
    //PGN->use_time2 = atoi(intbuf);.............................................
    //*****************************************************
    pcAnsi += len;

    //��ʱ3
    len = *pcAnsi;
    pcAnsi++;
    //strCopybyNum(PGN->use_time3,len,pcAnsi);
    //*****************************************************
    strCopybyNum(intbuf,len,pcAnsi);
	strcat_s(ss, sizeof(ss), intbuf);
    //PGN->use_time3 = atoi(intbuf);.............................................
    //*****************************************************
    pcAnsi += len;

	strcat_s(ss, sizeof(ss), "���ڷ���ʱ:");

    //�췽��ʱ1
    len = *pcAnsi;
    pcAnsi++;
    //strCopybyNum(PGN->white_time,len,pcAnsi);
    //*****************************************************
    strCopybyNum(intbuf,len,pcAnsi);
	strcat_s(ss, sizeof(ss), intbuf);
    //PGN->white_time = atoi(intbuf);.............................................
    //*****************************************************
    pcAnsi += len;

    //�ڷ���ʱ1
    len = *pcAnsi;
    pcAnsi++;
    //strCopybyNum(PGN->black_time,len,pcAnsi);
     //*****************************************************
    strCopybyNum(intbuf,len,pcAnsi);
	strcat_s(ss, sizeof(ss), intbuf);
	swprintf_s(pgn->note, sizeof(pgn->note) / sizeof(TCHAR), _T("%S"), ss);
    //*****************************************************
    pcAnsi += len;

    //��վ�ж�
    len = *pcAnsi;
    pcAnsi++;
    //strCopybyNum(PGN->result_other,len,pcAnsi);

	strCopybyNum(intbuf,len,pcAnsi);

	wcscat_s(pgn->result, sizeof(pgn->result) / sizeof(TCHAR), _T(" "));
	wcscat_s(pgn->result, sizeof(pgn->result) / sizeof(TCHAR), CA2W(intbuf));

    pcAnsi += len;

    //---------------//MOVES or INITBOARD
    len = *pcAnsi;
    strCopybyNum(buf,len,++pcAnsi);

    if(string_start_with(buf,"initboard")){ //����һ������

        return FALSE;//////////////////////////////////////////////////////////////
    }
    else{  //��ȫ��
        //strcpy_s(PGN->Fen,128,StartFen);
        //set_position(pos, (char*)StartFen);
        pcAnsi += len;
		pDis->pgn->isFenGame = FALSE;	//��ȫ�¿���         
    }

    do{//������һ���岽
        len = *pcAnsi;
        if(len != 5){
            break;
        }
        strCopybyNum(buf,len,++pcAnsi);

        //int fx = buf[0]-0x30;
        //int fy = buf[1]
        int f90  = buf[0]-0x30 + (74-buf[1])*9;
        int to90 = buf[3]-0x30 + (74-buf[4])*9;

        int from        = A90toA256[f90]   ;
        int to          = A90toA256[to90]  ;
        //int piece       = pos->board[from];
        //int capture     = pos->board[to];

        //make_move(pos,MOVE_FROM(from,piece,to,capture));

        //MOVE(from,to);

        //make_move(pos,MOVE_FROM(from,piece,to,capture),0);

		MakeMove(pDis,  StoX(from) - 3,
						StoY(from) - 3,
						StoX(to)   - 3,
						StoY(to)   - 3, 0);		

        pcAnsi += len;

    }while(TRUE);

    //�ж����һ���ǲ��ǽ���

   
    if(len == 4){
        strCopybyNum(buf,len,++pcAnsi);
        if(string_start_with(buf,"Ends")){

            //pos->His[pos->gply].ischeck = (sint8)isTurnInCheck(pos,pos->side);

			if(pDis->pos->gply < 40){
				LogOut(_T("\n������岽С��40��,̫����,û�е������\n"));
				return FALSE;
			}

            return TRUE;
        }
    }
    return FALSE;

}


//��Ŀ¼�µ�MXQ�ļ���һ��һ�����뿪�ֿ�
BOOL MxqFileCatToSql(dispboard_t* pDis, TCHAR* pgnRoot){

	//char pgnPath[MAX_PATH];

	//sprintf_s(pgnPath,MAX_PATH,"%s%s",installDir,"pgn\\");

	BOOL havePgn = FALSE;

	TCHAR filename[MAX_PATH*2];

	BOOL isFind = FALSE;
	TCHAR dir[MAX_PATH];
	TCHAR pre_name[MAX_PATH * 2];
	TCHAR new_name[MAX_PATH * 2];

	TCHAR ok_dir[MAX_PATH];
	//char bad_dir[MAX_PATH];

	int ok_num = 0;	

	swprintf_s(ok_dir, sizeof(ok_dir) / sizeof(TCHAR), _T("%s%s"), pgnRoot, _T("_ok"));

	CreateDirectory(ok_dir,NULL);  //����ת���ɹ���Ŀ¼ 

	//sprintf_s(ok_dir,sizeof(ok_dir),"%s%s",pgnRoot,"_ok");


	do{		//��һ��pgn�ļ�
		OpenAllCatFileOnebyOne(&isFind,pgnRoot,_T("*.mxq"),_T("_ok"),dir,filename);

		if(isFind){
			swprintf_s(pre_name, sizeof(pre_name) / sizeof(TCHAR), _T("%s%s"), dir, filename);

			swprintf_s((TCHAR*)pDis->pgn->note, sizeof(pDis->pgn->note) / sizeof(TCHAR), filename);  //���ļ�����

			if(ReadMxqToPos(pDis,pre_name)){

				//����ɹ��ˣ����ƶ���_okĿ¼��
				swprintf_s(new_name, sizeof(new_name) / sizeof(TCHAR), _T("%s%s%s"), ok_dir, _T("\\"), filename);

				if(FALSE == MoveFileEx(pre_name,new_name,MOVEFILE_REPLACE_EXISTING)){
					LogOut(pre_name);
					LogOut(_T("\n�����ƶ��������_okĿ¼!!\n"));
					LogOut(new_name);
					break;
				}

				LogOut(_T("\n�ɹ�����һ�������ļ�!\n"));
				LogOut(pre_name);
				
				havePgn = TRUE;
			}

			else{
				//������ȷ����PGN�ļ�
				LogOut(pre_name);
				LogOut(_T("���������ļ��������������ʽ!!\n"));

				//******************************************************************				
				swprintf_s(new_name, sizeof(new_name) / sizeof(TCHAR), _T("%s%s%s"), ok_dir, _T("\\"), filename);

				if(FALSE == MoveFileEx(pre_name,new_name,MOVEFILE_REPLACE_EXISTING)){
					LogOut(pre_name);
					LogOut(_T("\n�����ƶ��������_okĿ¼!!\n"));
					LogOut(new_name);
					break;
				}
				//******************************************************************
				havePgn = TRUE;
				break;
			}

			isFind = FALSE;

		}
		else{
			LogOut(pgnRoot);
			LogOut(_T("\n�Բ���û��������Ŀ¼���ҵ���Ч�������ļ�\n"));
		}

	}while(false);

	return havePgn;
	
}