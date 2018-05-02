#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"

void			//�����ڻ�ͼ����
PaintProc(dispboard_t* pDis){
	HDC         hdc;
	PAINTSTRUCT ps;
	//HFONT       oldFont;

	//if(hdc = BeginPaint(hwnd, &ps)) {
    if(hdc = BeginPaint(pDis->hwndThis, &ps)) {
        if (IsIconic(pDis->hwndThis)) { //�����ͼ�껯,��ͼ���� 
			DrawIcon(hdc, 2, 2, pDis->iconCurrent);
		} 
		else {  //������������
             /*	if (!appData.monoMode) {
				SelectPalette(hdc, DIS.hPal, FALSE);
				RealizePalette(hdc);
			}*/			
			HDCDrawPosition(pDis,hdc,true,NULL);
			//DisplayBothClocks(DIS);                
			//��ʾ˫����ʱ��,�Ҿ��û�����״̬����Ҫ��һЩ
		}
        EndPaint(pDis->hwndThis,&ps);
	}
	return;
}

VOID
InsertInPalette(COLORREF color)
{
  LPPALETTEENTRY pe = &(appData.ApLogPal->palPalEntry[appData.ApLogPal->palNumEntries]);

  if (appData.ApLogPal->palNumEntries++ >= PALETTESIZE) {
	  DisplayFatalError(L"Too many colors", 0, 1);
    appData.ApLogPal->palNumEntries--;
    return;
  }

  pe->peFlags = (char) 0;
  pe->peRed = (char) (0xFF & color);
  pe->peGreen = (char) (0xFF & (color >> 8));
  pe->peBlue = (char) (0xFF & (color >> 16));
  return;
}


VOID
InitDrawingColors(dispboard_t *pDis)
{
  if (appData.ApLogPal == NULL) {
    /* Allocate enough memory for a logical palette with
     * PALETTESIZE entries and set the size and version fields
     * of the logical palette structure.
     */
    appData.ApLogPal = (NPLOGPALETTE)
      LocalAlloc(LMEM_FIXED, (sizeof(LOGPALETTE) +
			      (sizeof(PALETTEENTRY) * (PALETTESIZE))));
    appData.ApLogPal->palVersion    = 0x300;
  }
  appData.ApLogPal->palNumEntries = 0;

  InsertInPalette(appData.AlightSquareColor);
  InsertInPalette(appData.AdarkSquareColor);
  InsertInPalette(appData.AwhitePieceColor);
  InsertInPalette(appData.AblackPieceColor);
  InsertInPalette(appData.AhighlightSquareColor);
  InsertInPalette(appData.ApremoveHighlightColor);

  /*  create a logical color palette according the information
   *  in the LOGPALETTE structure.
   */
  pDis->hPal = CreatePalette((LPLOGPALETTE) appData.ApLogPal);

  pDis->lightSquareBrush	= CreateSolidBrush(appData.AlightSquareColor);
  pDis->darkSquareBrush		= CreateSolidBrush(appData.AdarkSquareColor);
  pDis->whitePieceBrush		= CreateSolidBrush(appData.AwhitePieceColor);
  pDis->blackPieceBrush		= CreateSolidBrush(appData.AblackPieceColor);
  pDis->iconBkgndBrush		= CreateSolidBrush(GetSysColor(COLOR_BACKGROUND));
}
