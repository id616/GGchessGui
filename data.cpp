#include "stdafx.h"
#include "chess.h"
#include "data.h"


//int NextRandChar[18];
//int ComRandSeed;
int   ComRandSeed;
int   IsSendRand  = 0;   //1, �շ���, 2,�ѷ���

ULONG_PTR m_nGdiplusToken;
AppData			appData;
dispboard_t	   *OBS[MAX_OBS_BOARD];
//DLG_STRUCT		DLG;
Tab_T           TAB;

HINSTANCE		hInst;									// ��ǰʵ��
HMODULE hMod;
HMODULE msft_mod;
HWND			hwndToolBar;
HWND			hStatusBar;

NOTIFYICONDATA	Note;									//���̽ṹ
HMENU			hPopupMenu;								//���̲˵�
TCHAR			szTitle[MAX_LOADSTRING];				// �������ı�
TCHAR			szWindowClass[MAX_LOADSTRING];			// ����������

TCHAR          *EvalInfo;

//  ������ʾ����  End
ICS_t           ICS;
HANDLE			hDispThread;
HANDLE			hDispEvent;

TCHAR			installDir[MAX_PATH];			//�������Ŀ¼
//TCHAR			szAppName[] = _T("GGchess");
//TCHAR			*variantNames[] = VARIANT_NAMES;

ArgDescriptor	argDescriptorIndirection =
				{ _T(""), ArgSettingsFilename, (LPVOID) NULL, FALSE };

char			P90ASC[92];
char            P256ASC[256];
int				LIST_ORDER_SJ = 0;        //����岽�ǲ�����������
//TCHAR           pUserName[256];
//DisStat_t            pDST[1];             //��ǰ���߳�״̬

//uint32          Thread_Stat;          //��ǰ���߳�״̬

//BOOL            ThCanLearn;             //����ѧϰ��
//BOOL            ThOutLearn;             //���˳�ѧϰ״̬

ThStat_t       ThStat;

STOCK_DBS    MST[1];



