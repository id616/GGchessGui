#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "pregen.h"

uint8  _nBoardIndex[256];        //���Ҫ�������
uint16 _UpMask[256];            //��ǰ���������е�F1111111
uint16 _LoMask[256];
uint16 _RightMask[256];
uint16 _LeftMask[256];
//uint8  _GetDir[512];

uint8  _GetDir[256][256];

uint8  PreKingMove[256][8];
uint8  PreShiXiangAndEyeMove[256][16]; //��������
uint8  PreMaAndLegMove[256][32];       //��������

uint8  PreRPawnMove[256][4];                  //0,����,1,���'
uint8  PreBPawnMove[256][4];                  //0,����,1,���

SlideMoveStruct _smvRankMoveTab[9][512];
SlideMoveStruct _smvFileMoveTab[10][1024];

SlideMaskStruct _smsRankMaskTab[9][512];   // 36,864 �ֽ�
SlideMaskStruct _smsFileMaskTab[10][1024]; // 81,920 �ֽ�


static const int nHorseMoveDir[] = { -33, -31, -18, -14, 14, 18, 31, 33 };

static void InitInBoardData(void){
    for(int i = 0; i < 256; i++){
        inBoard(i) = 0;
        int x = StoX(i);
        int y = StoY(i);
        if(x > 2 && x < 0xc && y > 2 && y < 0xd){ 
            if(y<8){
                inBoard(i) = IN_BSIDE;
            }
            else{
                inBoard(i) = IN_RSIDE;
            }

            //�ڷ�
            if(i == 0x36 || i == 0x38 || i==0x47 || i==0x56 || i==0x58){
                inBoard(i) |= IN_BSHI;
            }
            if(x > 5 && x < 9 && y < 6){
                inBoard(i) |= IN_BKING;
            }
            if(i == 0x35 || i == 0x39 || i==0x53 || i==0x57 || i==0x5b || i==0x75 || i==0x79){
                inBoard(i) |= IN_BXIANG;
            }

            //�췽
            if(i == 0xa6 || i == 0xa8 || i==0xb7 || i==0xc6 || i==0xc8){
                inBoard(i) |= IN_RSHI;
            }
            if(x > 5 && x < 9 && y > 9){
                inBoard(i) |= IN_RKING;
            }
            if(i == 0xc5 || i == 0xc9 || i==0xa3 || i==0xa7 || i==0xab || i==0x85 || i==0x89){
                inBoard(i) |= IN_RXIANG;
            }
        }
    }
}


static void InitMask(void){
    //extern uint16 _UpMask[256];            //��ǰ���������е�F1111111
    //extern uint16 _LoMask[256];
    //extern uint16 _RightMask[256];
    //extern uint16 _LeftMask[256];
    for(int from=0; from<255; from++){
        _UpMask[from]       = 0;
        _LoMask[from]       = 0;
        _RightMask[from]    = 0;
        _LeftMask[from]     = 0;

        if(inBoard(from)){
            int x = StoX(from)-3;
            int y = StoY(from)-3;
            //����
            for(int k=y-1; k>=0; k--){
                _UpMask[from] |= 1<<(k);
            }
            //����
            for(int k=y+1; k<=10; k++){
                _LoMask[from] |= 1<<(k);
            }
            //����
            for(int k=x-1; k>=0; k--){
                _LeftMask[from] |= 1<<(k);
            }
            //����
            for(int k=x+1; k<=9; k++){
                _RightMask[from] |= 1<<(k);
            }
        }
    }
}
static void InitPawnMoves(void){
    int i, m, n, Player;
    uint8* lpDst;
    
    int PawnMoveDir[2][3] = { {-16, -1, 1}, {16, -1, 1} };	// �ڣ������ң�  �죺������
    for(Player=0; Player<=1; Player++){
        for(m=0x33; m<0xcc; m++){
            if(!inBoard(m)){
                continue;
            }
            //lpDst = PrePawnMove[Player][m];

            if(Player == WHITE){
                lpDst = PreRPawnMove[m];
            }
            else{
                lpDst = PreBPawnMove[m];
            }

            for(i=0; i<3; i++){
                if( i>0 && ((!Player && m>128) || (Player && m<=128)) ){			//δ���ӵı��������һζ�
                    break;
                }
                n = m + PawnMoveDir[Player][i];
                if(inBoard(n)){
                    *(lpDst++) = n;
                }
            }
            *lpDst = 0;
        }
    }
}
static void InitSmvSms(void){
  SlideMoveStruct smv;
  SlideMaskStruct sms;

  int i, j, k;

    // Ȼ�����ɳ��ں����Ԥ������(�����Ӧ�ò���"pregen.h")
  for (i = 0; i < 9; i ++) {
    for (j = 0; j < 512; j ++) {
      // ��ʼ�������ڡ�λ�С��ĳ����ڵ��ŷ�Ԥ�������飬�������¼������裺
      // 1. ��ʼ����ʱ����"SlideMoveTab"������û���ŷ�������ʼ�����  //Ӧ����0���
      
      smv.NonCap[0] = smv.NonCap[1] = smv.RookCap[0] = smv.RookCap[1] =
      smv.CannonCap[0] = smv.CannonCap[1] = smv.SuperCap[0] = smv.SuperCap[1] = i + 3;

      sms.NonCap = sms.RookCap = sms.CannonCap = sms.SuperCap = 0;
      // ��ʾ������"pregen.h"��...[0]��ʾ���һ�������ƶ������ƶ�����[0]����֮��Ȼ
      // 2. ���������ƶ���Ŀ������...[0]��
      for (k = i + 1; k <= 8; k ++) {
        if ((j & (1 << k)) != 0) {
          smv.RookCap[0] = k + 3;
          sms.RookCap |= 1 << k;
          break;
        }
        smv.NonCap[0] = k + 3;
        sms.NonCap |= 1 << k;
      }
      for (k ++; k <= 8; k ++) {
        if ((j & (1 << k)) != 0) {
          smv.CannonCap[0] = k + 3;
          sms.CannonCap |= 1 << k;
          break;
        }
      }
      for (k ++; k <= 8; k ++) {
        if ((j & (1 << k)) != 0) {
          smv.SuperCap[0] = k + 3;
          sms.SuperCap |= 1 << k;
          break;
        }
      }
      // 3. ���������ƶ���Ŀ������...[1]
      for (k = i - 1; k >= 0; k --) {
        if ((j & (1 << k)) != 0) {
          smv.RookCap[1] = k + 3;
          sms.RookCap |= 1 << k;
          break;
        }
        smv.NonCap[1] = k + 3;
        sms.NonCap |= 1 << k;
      }
      for (k --; k >= 0; k --) {
        if ((j & (1 << k)) != 0) {
          smv.CannonCap[1] = k + 3;
          sms.CannonCap |= 1 << k;
          break;
        }
      }
      for (k --; k >= 0; k --) {
        if ((j & (1 << k)) != 0) {
          smv.SuperCap[1] = k + 3;
          sms.SuperCap |= 1 << k;
          break;
        }
      }

      //����úϲ�һ��SMS��RookCap��NonCap ***********************************
      sms.RookCap |= sms.NonCap;

      //�ٽ�

      // 4. ����ʱ����"SlideMoveTab"�������ŷ�Ԥ����������
      _smvRankMoveTab[i][j] = smv;
      _smsRankMaskTab[i][j] = sms;
    }
  }

  // Ȼ�����ɳ��������Ԥ������(�����Ӧ�ò���"pregen.h")
  for (i = 0; i < 10; i ++) {
    for (j = 0; j < 1024; j ++) {
      // ��ʼ�������ڡ�λ�С��ĳ����ڵ��ŷ�Ԥ�������飬�������¼������裺
      // 1. ��ʼ����ʱ����"smv"������û���ŷ�������ʼ�����
      smv.NonCap[0] = smv.NonCap[1] = smv.RookCap[0] = smv.RookCap[1] =
      smv.CannonCap[0] = smv.CannonCap[1] = smv.SuperCap[0] = smv.SuperCap[1] = (i + 3) * 16;
      sms.NonCap = sms.RookCap = sms.CannonCap = sms.SuperCap = 0;
      // 2. ���������ƶ���Ŀ������...[0]
      for (k = i + 1; k <= 9; k ++) {
        if ((j & (1 << k)) != 0) {
          smv.RookCap[0] = (k + 3) * 16;
          sms.RookCap |= 1 << k;
          break;
        }
        smv.NonCap[0] = (k + 3) * 16;
        sms.NonCap |= 1 << k;
      }
      for (k ++; k <= 9; k ++) {
        if ((j & (1 << k)) != 0) {
          smv.CannonCap[0] = (k + 3) * 16;
          sms.CannonCap |= 1 << k;
          break;
        }
      }
      for (k ++; k <= 9; k ++) {
        if ((j & (1 << k)) != 0) {
          smv.SuperCap[0] = (k + 3) * 16;
          sms.SuperCap |= 1 << k;
          break;
        }
      }
      // 3. ���������ƶ���Ŀ������...[1]
      for (k = i - 1; k >= 0; k --) {
        if ((j & (1 << k)) != 0) {
          smv.RookCap[1] = (k + 3) * 16;
          sms.RookCap |= 1 << k;
          break;
        }
        smv.NonCap[1] = (k + 3) * 16;
        sms.NonCap |= 1 << k;
      }
      for (k --; k >= 0; k --) {
        if ((j & (1 << k)) != 0) {
          smv.CannonCap[1] = (k + 3) * 16;
          sms.CannonCap |= 1 << k;
          break;
        }
      }
      for (k --; k >= 0; k --) {
        if ((j & (1 << k)) != 0) {
          smv.SuperCap[1] = (k + 3) * 16;
          sms.SuperCap |= 1 << k;
          break;
        }
      }

      //����úϲ�һ��SMS��RookCap��NonCap ***********************************
      sms.RookCap |= sms.NonCap;

      // 4. ����ʱ����"smv"�������ŷ�Ԥ����������
      _smvFileMoveTab[i][j] = smv;
      _smsFileMaskTab[i][j] = sms;
    }
  }
}


static void InitShiXiangMove(void){
    int m, n;
    uint8* lpDst;
    //int nBishopMoveDir[] = { -34, -30, 30, 34 };
    for(m=0x33; m<0xCC; m++){
        lpDst = PreShiXiangAndEyeMove[m];
        for(n=0x33; n<0xCC; n++){            
            //if(IsCanTo(m,n) == DirXiang){        //����ߵ�
            if((inBoard(m) & (IN_RXIANG+IN_BXIANG)) && (inBoard(n) & (IN_RXIANG+IN_BXIANG))){
                if(GetDir(m,n) & DirXiang){
                    *(lpDst++) = n;
                    *(lpDst++) = (m+n)/2;
                }
            }
            //else if(IsCanTo(m,n) == DirShi){     //ʿ���ߵ�
            if((inBoard(m) & (IN_RSHI+IN_BSHI)) && (inBoard(n) & (IN_RSHI+IN_BSHI))){
                if(GetDir(m,n) & DirShi){
                    *(lpDst++) = n;
                } 
            }
        }
        *lpDst = 0;
    }
}






static void InitMaMove(void){
    
//  //PreMaAndLegMoveControlCity
//  //PreMaGoodMove[256][32]; 
//
//    // ������"cbcEdgeSquares"�����˲��������λ�ã��������̱�Ե����������λ�õ����ǻ���
//static const bool cbcEdgeSquares[256] = {
//  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//  0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
//  0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0,
//  0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
//  0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
//  0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
//  0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
//  0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
//  0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
//  0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0,
//  0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
//  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
//};

    int i,m,n;
    uint8* lpDst; 
    //uint8* lpDstMaControl;
    //uint8* lpDstMaGood;

    for(m=0x33; m<0xcc; m++){
        if(inBoard(m)){
            lpDst           = PreMaAndLegMove[m];
            //lpDstMaControl  = PreMaAndLegMoveControlCity[m];
            //lpDstMaGood     = PreMaGoodMove[m];

            for(i=0; i<8; i++){
                n = m + nHorseMoveDir[i];
                if(inBoard(n)){ // ����������
                    *(lpDst++) = n;
                    //�ټ���������
                    *(lpDst++) = m + horseLegTab(n-m+256);  

                    //if(!cbcEdgeSquares[n]){
                         //*(lpDstMaGood++) = n;
                         //�ټ���������
                         //*(lpDstMaGood++) = m + horseLegTab(n-m+256);  
                    //}
                }
                //if(inCity(n)){
                //    //*(lpDstMaControl++) = n;
                //    //�ټ���������
                //    //*(lpDstMaControl++) = m + horseLegTab(n-m+256);   
                //}
            }
            *lpDst              = 0;
            //*lpDstMaControl     = 0;
            //*lpDstMaGood        = 0;
        }
    }
}
static void InitKingMoves(void){
    uint8* lpDst;
    int i,m,n;
    int nKingMoveDir[4] = { -16, -1, 1, 16 };
    for(m=0x36; m<0xc9; m++){   //��˧���ܵ�λ��
        if(inBoard(m) &(IN_RKING|IN_BKING)){
            lpDst = PreKingMove[m];
            for(i=0; i<4; i++){
                n = m + nKingMoveDir[i];
                if(inBoard(n) & (IN_RKING|IN_BKING)){
                    *(lpDst++) = n;
                }
            }
            *lpDst = 0;  // ��ʾ�������ƶ�
        }
    }
}


static void InitDirInfo(void){
    //for(int from = 0; from < 256; from++){
    //    _GetDir[i] = DirNone;
    //}

	int size = sizeof(_GetDir);

	memset(_GetDir,DirNone,size);


    for(int from = 0x33; from < 0xcc; from++){
        for(int to = 0x33; to < 0xcc; to++){
            
            //int dir = from-to+256;
            
            int fx  = StoX(from);
            int fy  = StoY(from);

            int tx  = StoX(to);
            int ty  = StoY(to);
            //ʿ
            if((inBoard(from) & (IN_RSHI+IN_BSHI)) && (inBoard(to) & (IN_RSHI+IN_BSHI))){
                if(ABS(fx-tx) == 1 && ABS(fy-ty) == 1){
                    _GetDir[from][to] |= DirShi;
                }
            }
            //��
            if((inBoard(from) & (IN_RXIANG+IN_BXIANG)) && (inBoard(to) & (IN_RXIANG+IN_BXIANG))){
                if(ABS(fx-tx) == 2 && ABS(fy-ty) == 2){
                    _GetDir[from][to] |= DirXiang;
                }
            }
            //��
            if((inBoard(from)) && (inBoard(to))){
                if(  (ABS(fx-tx) == 1 && ABS(fy-ty) == 2)
                   ||(ABS(fx-tx) == 2 && ABS(fy-ty) == 1)){
                    _GetDir[from][to] |= DirMa;
                }
            }
            //����
            if((inBoard(from)) && (inBoard(to))){
                if(  (ABS(fx-tx) == 1 && ABS(fy-ty) == 0)
                   ||(ABS(fx-tx) == 0 && ABS(fy-ty) == 1)){
                    _GetDir[from][to] |= DirKing;
                }
            }
            //����
            if((inBoard(from)) && (inBoard(to))){                
                if(fx == tx){   
                    if(fy<ty){      //�ǲ���������
                        _GetDir[from][to] |= DirUp;
                    }
                    else if(fy>ty){ //�ǲ���������
                        _GetDir[from][to] |= DirLow;
                    }
                }
                else if(fy == ty){
                    if(fx<tx){      //�ǲ���������
                        _GetDir[from][to] |= DirLeft;
                    }
                    else if(fx>tx){ //�ǲ���������
                        _GetDir[from][to] |= DirRight;
                    }
                }
            }
        }
    }
}

void //��ʼ����ʷ�߲�����
initHisMoveName(dispboard_t* pDis){
	//extern char     DispHisMoveName[7000];
	//extern int      DispHisMove[500];
	//char     DispHisMoveName[7000];
	//char*    DispHisMove[500];
	//BCHEYU[from] = &BCHEYU090[esi];    //ȡ�õ�ַ
	TCHAR* pc;
	
	for(int i=0; i<MAX_GAME_LENGTH; i++){
		//DispHisMove[i] = &DispHisMoveName[i*14];
		//pc			   = DispHisMove[i];
		//pc = &DIS.pos.moveListName[i*14];

        pc = pDis->moveListName[i];
		int ti = (i+2)/2;
		if(ti < 100){
			*pc = 0x30;
		}
		else{
			char k = ti /100;
			*pc = k+48;
			ti  -= 100 * k;
		}
		pc++;
		if(ti < 10){
			*pc = 0x30;
		}
		else{
			char k= ti /10;
			*pc = k+48;
			ti -= 10*k;
		}
		pc++;
		*pc = ti+48;
		 pc++;
		for( int e=0; e<10; e++){
			*(pc+e) = 0x20;
		}
		//=============================================
		if(i%2 == 1){
			pc = pDis->moveListName[i];
			*pc++ = 95;
			*pc++ = 95;
			*pc++ = 95;
		}
		//=============================================
	}   
	//======================================
	//for(int i=0; i<500; i++) ��
	//{
	//	pc = DispHisMove[i];
	//	DispLog(pc);
	//}
}




void initPreGen(void){
    p90ToAsc();
    InitInBoardData();
    InitMask();
    InitDirInfo();
    InitSmvSms();           //��������

    //�߲�
    InitMaMove();           //��
    InitKingMoves();        //��
    InitPawnMoves();        //��
    InitShiXiangMove();     //ʮ��

    init_mersenne();
    init_zobrist();     //��ʼ��hash key 
    initHisMoveName(OBS[0]);
}