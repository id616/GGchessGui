#ifndef preMoveGen_H
#define preMoveGen_H


// ������λ�С��͡�λ�С����ɳ����ŷ���Ԥ�ýṹ
struct SlideMoveStruct {
  unsigned char NonCap[2];    // ���������ߵ������һ��/��Сһ��
  unsigned char RookCap[2];   // ���������ߵ������һ��/��Сһ��
  unsigned char CannonCap[2]; // �ڳ������ߵ������һ��/��Сһ��
  unsigned char SuperCap[2];  // ������(�����ӳ���)���ߵ������һ��/��Сһ��
}; // smv

// ������λ�С��͡�λ�С��жϳ����ŷ������Ե�Ԥ�ýṹ
struct SlideMaskStruct {
  unsigned short NonCap, RookCap, CannonCap, SuperCap;
}; // sms

extern SlideMoveStruct _smvRankMoveTab[9][512];
extern SlideMoveStruct _smvFileMoveTab[10][1024];

extern SlideMaskStruct _smsRankMaskTab[9][512];   // 36,864 �ֽ�
extern SlideMaskStruct _smsFileMaskTab[10][1024]; // 81,920 �ֽ�

extern uint16 _UpMask[256];            //��ǰ���������е�F1111111
extern uint16 _LoMask[256];
extern uint16 _RightMask[256];
extern uint16 _LeftMask[256];
extern uint8  PreKingMove[256][8];
extern uint8  PreShiXiangAndEyeMove[256][16];           //��������
extern uint8  PreMaAndLegMove[256][32];                 //��������

extern uint8 _nBoardIndex[256];
//extern uint8  _GetDir[512];

extern uint8  _GetDir[256][256];
extern uint8  PreRPawnMove[256][4];                  //0,����,1,���'
extern uint8  PreBPawnMove[256][4];                  //0,����,1,���

extern void initPreGen(void);

extern uint64 Zobrist[BPAWN+1][256], ZobColour;

#endif