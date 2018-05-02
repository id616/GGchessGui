#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"
#include <sys/stat.h>
#include <io.h>
#include <fcntl.h>
#include <share.h>

//�鿴һ�£�PGN �岽�ڲ��ڵ�ǰ���ߵ��岽��
int getMoveFormPgnStr(dispboard_t* pDis, char* pgnStr){


	position_t *pos = pDis->pos;

	gen_legal_moves(pos);

	while(pos->pMend > pos->all_move){

		pos->pMend--;

		if(pos->His[pos->curStep].ischeck == FALSE){
			if(move_is_legal(pos,pos->pMend->move) == FALSE){
				continue;
			}			
		}

		//pos->pMend--;

		//�õ��߲�������
		GetMoveName(pDis,pos,pos->pMend->move, appData.moveType);

		char*   szStepName  = pDis->moveListName[pos->curStep] + 4;   //����ǰ��ı����

		//if(string_start_with(pgnStr,szStepName)){
		//	return pos->pMend->move;
		//}

		//��ǰ��8���ַ��ǲ���һ��
		BOOL find = TRUE;

		for(int i = 0; i < 8; i++){
			if(szStepName[i] != pgnStr[i]){
				find= FALSE;
				break;
			}
		}

		if(find == TRUE){
			return pos->pMend->move;
		}
	}

	return 0;
}

BOOL		ReadPgnToPos    (dispboard_t* pDis, char* pgnFname, pgn_file_t* PGN){

	char pgnBuf[4096];

	//memset(pgnBuf,0, sizeof(pgnBuf));
	//char buf[512];
	//char intbuf[32];
	int  pFile;
	//int  i;

	//��PGN���һ��
	memset(PGN,0,sizeof(pgn_file_t));

	sprintf_s(PGN->pgn_format,sizeof(PGN->pgn_format),"pgn");

	errno_t err = _sopen_s(&pFile, pgnFname, _O_RDONLY, _SH_DENYNO,
		_S_IREAD | _S_IWRITE);

	if(err != 0){
		LogOut(pgnFname);
		LogOut("\nPGN �ļ������ڣ���򲻿�!!\n");
		return FALSE;
	}

	//���ļ�ȫ������BUF
	int bytesRead = _read(pFile, pgnBuf, sizeof(pgnBuf));

	if(bytesRead <= 0){
		LogOut(pgnFname);
		LogOut("\nPGN �ļ������ڣ���򲻿�!!\n");
		_close(pFile);
		return FALSE;
	}

	_close(pFile);

	if(bytesRead < 20){
		LogOut(pgnFname);
		LogOut("\nPGN �ļ�����̫�٣���\n");
		return FALSE;
	}


	//Returns a pointer to the first occurrence of strSearch in str, 
	//or NULL if strSearch does not appear in str. 
	//If strSearch points to a string of zero length, the function returns str.


	char* ps;

	int len = (int)strlen(pgnBuf);

	char* pend = pgnBuf + len;

	*pend      = 0;
	*(pend-1)  = 0;

	//*(pend-1) = 0;       //����һ����β 
	
	//ps = strstr(pgnBuf,"Round");

	//if(ps == NULL){
	//	LogOut(pgnFname);
	//	LogOut("\nPGN ��PGN�ļ���û�з��� Round�� ����\n");
	//	return FALSE;
	//}

	ps = pgnBuf;

	int ply = 1;         //PGN�ļ�1��ͷ

	char str_num[32];

	while(ps < pend){

		if((pend - ps) < 7){
			goto PGN_RET;  //û���岽��
		}

		

		sprintf_s(str_num,sizeof(str_num),"%d. ",ply);

		ps = strstr(ps,str_num);

		if(ps != NULL){				//�������������
			
			ps = strstr(ps," ");    //�ҵ���һ���ո�

			if(ps == NULL){
				goto PGN_RET;  //û���岽��
			}

			while(ps < pend && *(++ps) == ' '){	//��������Ŀո�
			}

			if(ps > pend){
				goto PGN_RET;  //û���岽��
			}

			if((pend - ps) < 7){
				goto PGN_RET;  //û���岽��
			}

			int move = getMoveFormPgnStr(pDis,ps);

			if(move == 0){
				goto PGN_RET;   //û���岽��
			}

			//ֱ���߲���
			UserMoveEvent(pDis,
				StoX(FROM(move)) - 3,
				StoY(FROM(move)) - 3,
				StoX(TO(move))   - 3,
				StoY(TO(move))   - 3, 0);


			if((pend - ps) < 7){
				goto PGN_RET;  //û���岽��
			}

			ps = strstr(ps, " ");

			if(ps == NULL){
				goto PGN_RET;  //û���岽��
			}


			while(ps < pend && *(++ps) == ' '){	//��������Ŀո�
			}

			if(ps > pend){
				goto PGN_RET;  //û���岽��
			}

			if((pend - ps) < 7){
				goto PGN_RET;  //û���岽��
			}

			move = getMoveFormPgnStr(pDis,ps);

			if(move == 0){
				goto PGN_RET;   //û���岽��
			}

			//ֱ���߲���
			UserMoveEvent(pDis,
				StoX(FROM(move)) - 3,
				StoY(FROM(move)) - 3,
				StoX(TO(move))   - 3,
				StoY(TO(move))   - 3, 0);


			ply++;		
			
		}

		else{
			goto PGN_RET;   //û���岽��
		}
	}

PGN_RET:


	if( (pend-ps) > 7){

		LogOut(pgnFname);
		LogOut("\n�����岽û�н�����!!\n");
		LogOut(pgnBuf);
		LogOut("\n�岽��ţ�");
		LogOut(str_num);
	}

	if(ply > 1){

		//��Ϊ����ʹ��

		//CheckDlgItem(		

		LogOut(pgnBuf);

		LogOut("\n�ɹ�������һ�֣Уǣ��ļ����ڴ�!\n");

		return TRUE;
	}
	else{
		return FALSE;
	}
	
}

//��Ŀ¼�µ�PGN�ļ���һ��һ�����뿪�ֿ�
BOOL PgnFileCatToBook(char* pgnRoot){

	//char pgnPath[MAX_PATH];

	//sprintf_s(pgnPath,MAX_PATH,"%s%s",installDir,"pgn\\");

	BOOL havePgn = FALSE;

	char filename[MAX_PATH*2];

	BOOL isFind = FALSE;
	char dir[MAX_PATH];
	char pre_name[MAX_PATH*2];
	char new_name[MAX_PATH*2];

	char ok_dir[MAX_PATH];

	int ok_num = 0;

	dispboard_t *pDis = OBS[0];

	pgn_file_t PGN[1];

	ResetGameEvent(pDis);

	sprintf_s(ok_dir,sizeof(ok_dir),"%s%s",pgnRoot,"_ok");

	CreateDirectory(ok_dir,NULL);  //����ת���ɹ���Ŀ¼ 

	do{		//��һ��pgn�ļ�
		OpenAllCatFileOnebyOne(&isFind,pgnRoot,"*.pgn","_ok",dir,filename);

		if(isFind){
			sprintf_s(pre_name,sizeof(pre_name),"%s%s",dir,filename);

			if(ReadPgnToPos(pDis,pre_name,PGN)){

				//����ɹ��ˣ����ƶ���_okĿ¼��
				sprintf_s(new_name,sizeof(new_name),"%s%s%s",ok_dir,"\\",filename);

				if(FALSE == MoveFileEx(pre_name,new_name,MOVEFILE_REPLACE_EXISTING)){
					LogOut(pre_name);
					LogOut("\n�����ƶ��������_okĿ¼!!\n");
					LogOut(new_name);
					break;
				}

				LogOut("\n�ɹ�����һ��PGN�ļ�!\n");
				LogOut(pre_name);
				
				havePgn = TRUE;
			}

			else{
				//������ȷ����PGN�ļ�
				LogOut(pre_name);
				LogOut("����PGN�ļ���������PGN��ʽ!!\n");
				break;
			}

			isFind = FALSE;

		}
		else{
			LogOut(pgnRoot);
			LogOut("\n�Բ���û��������Ŀ¼���ҵ���Ч��PGN�ļ�\n");
		}

	}while(false);

	return havePgn;
	
}