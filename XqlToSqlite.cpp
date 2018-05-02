#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"
#include <sys/stat.h>
#include <io.h>
#include <fcntl.h>
#include <share.h>
#include "xqf.h"
//#include <windows.h>
//#include <stdio.h>
//#include <iostream>
//#include <fstream>
//#include <numeric>
//#include <algorithm>
//#include <crtdbg.h>
//#include <fstream>
//#include <iostream>

HANDLE hFile;
//���°汾��
enum {RECENT_VER = 0x12};

//����������
BYTE m_ucKey[0x30];
// �ļ��汾
BYTE m_ucVer;
BYTE m_uc40E;
BYTE m_uc40F;
BYTE m_uc410;
WORD m_w412;

XQFFileHeader m_xqfHeader;

////////////////////////////////////
// ��ȡ���ݣ��Ƚ����ٷ���
////////////////////////////////////
HRESULT ReadByCrack(BYTE* buf, int nBufLen){

	//
	if(NULL == buf || nBufLen <= 0){
		return E_INVALIDARG;
	}

	//You can also use the SetFilePointer function to query the current 
	//	file pointer position. 
	//	To do this, specify a move method of FILE_CURRENT 
	//	and a distance of 0 (zero).

	//
	int nPos = SetFilePointer(hFile,0,NULL,FILE_CURRENT);

	DWORD nBytesRead;

	// ��ȡ����
	BOOL bResult = ReadFile(hFile,
		(char*)buf,
		nBufLen,
		&nBytesRead,
		NULL);

	//Check For End of File
	if(bResult && nBytesRead == 0){
		return E_INVALIDARG;
	}

	for(int i = 0; i < nBufLen; i++){
		buf[i] -= m_ucKey[((nPos + i) & 0x1F) +  0xC];
	}

	return S_OK;
}

////////////////////////////////////
// ��ȡע�ͳ���
////////////////////////////////////
HRESULT ReadCommentLen(int* pLen)
{
	if (NULL == pLen)
		return E_INVALIDARG;

	HRESULT hr = ReadByCrack((BYTE*)pLen, sizeof(int));
	if (FAILED(hr))
	{
		return hr;
	}

	*pLen -= m_w412;
	return S_OK;
}

////////////////////////////////////
// ���ļ��ж�ȡ����
////////////////////////////////////
//XQData* LeadHead(){
//	XQDate* pDate = new XQData;
//
//	if(NULL == pData){
//		return NULL;
//	}
//
//	//if(!SUCCEEDED(ReadXQFHeader((BYTE*)&m_xqfHeader, sizeof(m_xqfHeader)))){
//	//	return NULL;
//	//}
//
//	//memcpy(&pData->fileHeader, &m_xqfHeader, sizeof(m_xqfHeader));
//	
//	pData->pRoot = ReadStep(NULL);
//	return pData;
//}

////////////////////////////////////
// �����ļ���ʽ
////////////////////////////////////
bool CheckFormat(const BYTE* buf)
{

	// �����ļ�ͷ
	if (*(WORD*)buf != *(WORD*)"XQ")
		return false;
	
	// �ļ��ȳ���汾�ߣ��޷���ȡ
	if (buf[2] > RECENT_VER)
	{
		return false;
	}
	
	// ����
	//BYTE ucChk = std::accumulate(buf + 0xC, buf + 0x10, 0);
	//if (0 != ucChk)
	//{
	//	return false;
	//}

	return true;
}




//��ΪXQF�кܶ��,����Ҫ�ֱ��
BOOL		ReadXqfToPos   (dispboard_t* pDis, TCHAR* xqfFname){


	// �ײ��ļ�����
	//std::ifstream m_file; 


	//��ʼ����Ա����
	memset(m_ucKey, 0, sizeof(m_ucKey));
	m_ucVer = 0;
	m_uc40E = 0;
	m_uc40F = 0;
	m_uc410 = 0;
	m_uc40F = 0;

	//char* buf;
	//int pFile;

	//HANDLE hFile;

	hFile = CreateFile(xqfFname,
		           GENERIC_READ,          // open for reading
                   FILE_SHARE_READ,       // share for reading
                   NULL,                  // default security
                   OPEN_EXISTING,         // existing file only
                   FILE_ATTRIBUTE_NORMAL, // normal file
                   NULL);                 // no attr. template

	if (hFile == INVALID_HANDLE_VALUE) {
		LogOut(_T("\n���ܴ��ļ�\n"));
		LogOut(xqfFname);
		return FALSE;
	}


	//���ļ�ͷ
	//if (!SUCCEEDED(ReadXQFHeader((BYTE*)&m_xqfHeader, sizeof(m_xqfHeader))))
    DWORD nBytesRead;

	// ��ȡ����
	BOOL bResult = ReadFile(hFile,
		(char*)&m_xqfHeader,
		sizeof(m_xqfHeader),
		&nBytesRead,
		NULL);
    

	CloseHandle(hFile);   //�ر��ļ�


	return TRUE;
}

//��Ŀ¼�µ�PGN�ļ���һ��һ�����뿪�ֿ�
BOOL XqfFileCatToSql(dispboard_t* pDis, TCHAR* pgnRoot){

	BOOL havePgn = FALSE;

	TCHAR filename[MAX_PATH * 2];

	BOOL isFind = FALSE;
	TCHAR dir[MAX_PATH];
	TCHAR pre_name[MAX_PATH * 2];
	TCHAR new_name[MAX_PATH * 2];

	TCHAR ok_dir[MAX_PATH];
	//char bad_dir[MAX_PATH];w

	int ok_num = 0;	

	swprintf_s(ok_dir, sizeof(ok_dir) / sizeof(TCHAR), _T("%s%s"), pgnRoot, _T("_ok"));

	CreateDirectory(ok_dir,NULL);  //����ת���ɹ���Ŀ¼ 

	do{		//��һ��pgn�ļ�
		OpenAllCatFileOnebyOne(&isFind,pgnRoot,_T("*.xqf"),_T("_ok"),dir,filename);

		if(isFind){
			swprintf_s(pre_name, sizeof(pre_name) / sizeof(TCHAR), _T("%s%s"), dir, filename);

			swprintf_s(pDis->pgn->note, sizeof(pDis->pgn->note) / sizeof(TCHAR), filename);  //���ļ�����

			if(ReadXqfToPos(pDis,pre_name)){

				//����ɹ��ˣ����ƶ���_okĿ¼��
				swprintf_s(new_name, sizeof(new_name) / sizeof(TCHAR), _T("%s%s%s"), ok_dir, _T("\\"), filename);

				if(FALSE == MoveFileEx(pre_name,new_name,MOVEFILE_REPLACE_EXISTING)){
					LogOut(pre_name);
					LogOut(_T("\n�����ƶ��������_okĿ¼!!\n"));
					LogOut(new_name);
					break;
				}

				LogOut(_T("\n�ɹ�����һ��XQF�ļ�!\n"));
				LogOut(pre_name);
				
				havePgn = TRUE;
			}

			else{
				//������ȷ����PGN�ļ�
				LogOut(pre_name);
				LogOut(_T("����XQF�ļ���������XQF��ʽ!!\n"));

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
			LogOut(_T("\n�Բ���û��������Ŀ¼���ҵ���Ч��XQF�ļ�\n"));
		}

	}while(false);

	return havePgn;
	
}