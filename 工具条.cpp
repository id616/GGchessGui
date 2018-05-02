#include "stdafx.h"
#include "GGchess.h"
#include "chess.h"
#include "data.h"
#include "pregen.h"

HWND			//��������������
CreateAToolBar(HWND hwndParent){
	#define NUM_BUTTONS               14
	HWND hwndTB; 

	TBADDBITMAP tbab; 
	tbab.hInst = hInst;
	tbab.nID = IDR_TOOLBAR; // IDR_TOOLBAR;

	TBBUTTON tbb[NUM_BUTTONS]; 


	// Create a toolbar.  WS_EX_TOOLWINDOW "ToolWindowClass
	hwndTB = CreateWindowEx(
		WS_EX_TOOLWINDOW, 
		TOOLBARCLASSNAME,	
		(LPWSTR) NULL, 
		WS_CHILD + TBSTYLE_FLAT + WS_BORDER + TBSTYLE_TRANSPARENT + TBSTYLE_TOOLTIPS ,
		0,
		0, 
		0,
		0,
		hwndParent, 
		(HMENU)IDR_TOOLBAR, 
		hInst, NULL);

	//DWORD backgroundColor = GetSysColor(COLOR_BTNFACE);
	//COLORMAP colorMap;
	//colorMap.from = RGB(0, 0, 0);
	//colorMap.to = backgroundColor;
	//HBITMAP hbm = CreateMappedBitmap(g_hInst, IDB_BITMAP1, 0, &colorMap, 1);

	// Send the TB_BUTTONSTRUCTSIZE message, which is required for 
	// backward compatibility. 
	SendMessage(hwndTB, TB_BUTTONSTRUCTSIZE, (WPARAM) sizeof(TBBUTTON), 0); 
   
	//SendMessage(hwndTB, TB_SETBITMAPSIZE,0,(LPARAM)MAKELONG(16,15));

    //SendMessage(hwndTB,(UINT) TB_ADDBITMAP,NUM_BUTTONS,(LPARAM)(LPTBADDBITMAP)&tbab);
	int d = (int)SendMessage(hwndTB, (UINT)TB_ADDBITMAP, NUM_BUTTONS, (LPARAM)&tbab);
	
	tbb[0].iBitmap		= 0; 
	tbb[0].idCommand	= IDT_NEW;              //�����
	tbb[0].fsState		= TBSTATE_ENABLED; 
	tbb[0].fsStyle		= BTNS_BUTTON ; 
	tbb[0].dwData		= 0; 
	tbb[0].iString		= 0; 

	//tbb[1].iBitmap		= 1; 
	//tbb[1].idCommand	= IDT_FEN_GAME;         //�ڲо�
	//tbb[1].fsState		= TBSTATE_ENABLED; 
	//tbb[1].fsStyle		= BTNS_CHECK; 
	//tbb[1].dwData		= 0; 
	//tbb[1].iString		= 0; 

	tbb[1].iBitmap		= 1; 
	tbb[1].idCommand	= IDT_SAVE_GAME;         //���浱ǰ�����
	tbb[1].fsState		= TBSTATE_ENABLED; 
	tbb[1].fsStyle		= BTNS_CHECK; 
	tbb[1].dwData		= 0; 
	tbb[1].iString		= 0; 

	tbb[2].iBitmap		= 2; 
	tbb[2].idCommand	= IDT_ToStart;         //����ֿ�ͷ
	tbb[2].fsState		= TBSTATE_ENABLED; 
	tbb[2].fsStyle		= BTNS_BUTTON; 
	tbb[2].dwData		= 0; 
	tbb[2].iString		= 0; 

	tbb[3].iBitmap		= 3; 
	tbb[3].idCommand	= IDT_Backward;		  //����һ��
	tbb[3].fsState		= TBSTATE_ENABLED; 
	tbb[3].fsStyle		= BTNS_BUTTON; 
	tbb[3].dwData		= 0; 
	tbb[3].iString		= 0; 

	//tbb[12].iBitmap		= 12; 
	//tbb[12].idCommand	= IDT_pause;          //��ͣ���
	//tbb[12].fsState		= TBSTATE_ENABLED; 
	//tbb[12].fsStyle		= BTNS_BUTTON; 
	//tbb[12].dwData		= 0; 
	//tbb[12].iString		= 0; 

	tbb[4].iBitmap		= 4; 
	tbb[4].idCommand	= IDT_Forward;        //ǰ��һ��
	tbb[4].fsState		= TBSTATE_ENABLED; 
	tbb[4].fsStyle		= BTNS_BUTTON; 
	tbb[4].dwData		= 0; 
	tbb[4].iString		= 0; 

	tbb[5].iBitmap		= 5; 
	tbb[5].idCommand	= IDT_ToEnd;          //������ֵĽ�β
	tbb[5].fsState		= TBSTATE_ENABLED; 
	tbb[5].fsStyle		= BTNS_BUTTON; 
	tbb[5].dwData		= 0; 
	tbb[5].iString		= 0; 

	tbb[6].iBitmap		= 6; 
	tbb[6].idCommand	= IDT_COM_RED;        //����(2)��������
	tbb[6].fsState		= TBSTATE_ENABLED; 
	tbb[6].fsStyle		= BTNS_CHECK; 
	tbb[6].dwData		= 0; 
	tbb[6].iString		= 0; 

	tbb[7].iBitmap		= 7; 
	tbb[7].idCommand	= IDT_COM_BLUE;       //����(3)��������
	tbb[7].fsState		= TBSTATE_ENABLED; 
	tbb[7].fsStyle		= BTNS_CHECK; 
	tbb[7].dwData		= 0; 
	tbb[7].iString		= 0; 

	tbb[8].iBitmap		= 8; 
	tbb[8].idCommand	= IDT_Stop;          //����ֹͣ˼��
	tbb[8].fsState		= TBSTATE_ENABLED; 
	tbb[8].fsStyle		= BTNS_BUTTON; 
	tbb[8].dwData		= 0; 
	tbb[8].iString		= 0; 

	tbb[9].iBitmap		= 9; 
	tbb[9].idCommand	= IDT_HUIQI;          //�û�����
	tbb[9].fsState		= TBSTATE_ENABLED; 
	tbb[9].fsStyle		= BTNS_BUTTON; 
	tbb[9].dwData		= 0; 
	tbb[9].iString		= 0; 

	tbb[10].iBitmap		= 10; 
	tbb[10].idCommand	= IDT_YQ_SET;        //�������� 
	tbb[10].fsState		= TBSTATE_ENABLED; 
	tbb[10].fsStyle		= BTNS_BUTTON; 
	tbb[10].dwData		= 0; 
	tbb[10].iString		= 0; 

	tbb[11].iBitmap		= 11; 
	tbb[11].idCommand	= IDT_PONDER;		//��̨˼��
	tbb[11].fsState		= TBSTATE_ENABLED; 
	tbb[11].fsStyle		= BTNS_CHECK; 
	tbb[11].dwData		= 0; 
	tbb[11].iString		= 0; 

    tbb[12].iBitmap		= 12; 
	tbb[12].idCommand	= IDT_FLIP;           //���·�ת����
	tbb[12].fsState		= TBSTATE_ENABLED; 
	tbb[12].fsStyle		= BTNS_BUTTON; 
	tbb[12].dwData		= 0; 
	tbb[12].iString		= 0; 	
	
	
	tbb[13].iBitmap		= 13; 
	tbb[13].idCommand	= IDT_ANALIZE_FUN;      //��������ɷ���ģʽ  
	tbb[13].fsState		= TBSTATE_ENABLED; 
	tbb[13].fsStyle		= BTNS_CHECK; 
	tbb[13].dwData		= 0; 
	tbb[13].iString		= 0; 


	SendMessage(hwndTB, TB_ADDBUTTONS, (WPARAM) NUM_BUTTONS, (LPARAM) (LPTBBUTTON) &tbb); 

	SendMessage(hwndTB, TB_AUTOSIZE, 0, 0); 

	

	ShowWindow(hwndTB, SW_SHOW); 
	//MoveWindow(hwndTB,0,0,300,20,false);


	return hwndTB; 
}



