#include "chess.h"


// ���Ϲ�������******************************************************************Start

extern int   ComRandSeed;
extern BOOL  IsSendRand;   

extern TCHAR		  installDir[MAX_PATH];  //�������Ŀ¼
extern HINSTANCE	  hInst;				// ��ǰʵ��
extern HMODULE hMod;
extern HMODULE msft_mod;
//extern HWND			hwndMain;
extern NOTIFYICONDATA Note;					//���̽ṹ
extern HMENU		  hPopupMenu;			//���̲˵�
extern TCHAR		  szTitle[MAX_LOADSTRING];					// �������ı�
extern TCHAR		  szWindowClass[MAX_LOADSTRING];			// ����������
//extern char			LogBuf[MSG_SIZ];

extern char			  P90ASC[92];
extern char           P256ASC[256];

extern HWND           hStatusBar;
extern HWND			  hwndToolBar;
extern ICS_t          ICS;
extern TCHAR          *EvalInfo;

extern dispboard_t   *OBS[MAX_OBS_BOARD];

extern ArgDescriptor	argDescriptorIndirection;

extern ULONG_PTR m_nGdiplusToken;  // To enable GDI+: 
// ������ʾ����******************************************************************Start
extern AppData				appData;
extern ErrorMap				errmap[];
extern Enables				cmailEnables[];
extern Enables				icsEnables[];
extern Enables				ncpEnables[];
extern Enables				gnuEnables[];
extern Enables				machineThinkingEnables[];
extern Enables				trainingOffEnables[];
extern Enables				userThinkingEnables[];
extern Enables				trainingOnEnables[];
//extern TCHAR				szAppName[];
extern TCHAR				szConsoleName[];
extern TCHAR				szConsoleTitle[];
extern SizeInfo				sizeInfo[];
extern ArgDescriptor		argDescriptors[];
extern TCHAR				*defaultTextAttribs[];
extern MyColorizeAttribs	colorizeAttribs[]; /* do I need the size? */
//extern char                 *variantNames[VARIANT_NAMES_NUM];

//extern TCHAR                pUserName[256];

extern ThStat_t             ThStat;


// ������ʾ����******************************************************************End
extern MyFont fontRec[NUM_SIZES][NUM_FONTS];
extern Tab_T TAB;

extern int		ZF90[91];
extern int		KF32[32];
extern int      TTFACE[32];
extern __int64  F64Count;

extern int LIST_ORDER_SJ;        //�ǲ�����������

extern STOCK_DBS    MST[1];

