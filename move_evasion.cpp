#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"

#include "stdafx.h"
#include "chess.h"
#include "preGen.h"

////�����⽫��
//move_stack_t *generate_check_evasions(position_t *pos, move_stack_t *ms) {
//    //�����Ϸ��Ľ⽫����
//
//    //��������еĽ�����Ϣ�� //������������Ͻ�����,ǰ���������
//    //bool have           = false;
//
//#ifdef  DEBUG_EVASION_MOVE
//    //ASSERT(isTurnInCheck(pos,pos->side));    //��ǰ��������ӷ���������
//    //if(!isTurnInCheck(pos,pos->side)){
//    //    board_display(pos,"�⽫��\n",stdout);
//    //}
//
//    ASSERT(!isTurnInCheck(pos,pos->side^0x1));  
//        
//    if(isTurnInCheck(pos,pos->side^0x1)){
//         board_display(pos,"�⽫��\n",stdout);
//        int test = 0;
//    }
//
//
//    move_stack_t *prePS = ms;       //���濪ʼ���߲�
//#endif
//
//    int CheckType       =0;            //��,0001, �� 0010 �� 0100 �� 1000  ����������
//    int CheckPieceNum   =0;            //���������ӵ�����
//    int CheckPos256[8];                //���������ӵ�λ��, ���ֻ����ͬʱ��5�������ڽ���
//    int MaLeg256[4];                   //���������,���������� 256
//
//    int PaoJiaNum       =0;            //�ڼ��ӵ���Ŀ
//    int PaoJia256[4];                  //�ڼ�������,��Ϊ��˫�ڽ�����
//    int PaoJiaChess[4];                //�ڼ��ӵ���������    
//    int PaoHuo256[4];                  //�ڽ������ڵĺ��������
//    int PaoDir[4];                     //�ڽ����ķ���   
//    int PaoHuoChess[4];
//
//
//    int Not256Pos[16];
//    int NotNum          =0;         //�����ܽ⽫�����ӵ����� 
//    //1,��ס�˶Է����ܽ���������,
//    //2,�����ǳ� ����(��)���ǽ�,˧,
//    //3, ��������������,Ҳ���Ǳ�ǣ��ס��,���������⽫��  
//    //   ��������Ӵ�P48����ʱȥ��,����ٻ�ԭһ��,��ʣ�µ����Ӷ����߶���
//
//    int NotToFile       =0;         //�⽫�����Ӳ���ȥ�ĵط� File
//    int NotToRank       =0;         //���������Ӳ���ȥ�ĵط� Rank
//
//    int K256Up1         =0;         //�������һ������
//    int K256Up2         =0;
//    int K256Up3         =0;
//
//    int K256Left1       =0;
//    int K256Left2       =0;
//    int K256Left3       =0;
//
//    int K256Right1      =0;
//    int K256Right2      =0;
//    int K256Right3      =0;
//
//    int K256Lo1         =0;
//    int K256Lo2         =0;
//    int K256Lo3         =0;
//
//    int checkChess;            //���Ҿ�������
//    int checkSq256;            //���Ҿ������ӵ�λ��
//    int checkSqX;
//    int checkSqY;
//    int tCheckDir1;             //���������ӵĵ�һ������    
//
//    int paohou256       ;
//    int paojia256       ;
//    int paojiaX         ;
//    int paojiaY         ;
//    int paohouChess     ;       //�ڼܺ����������
//    int paojiaChess     ;
//
//    int leg256;
//    int to256;
//    int nDisp;
//
//    bool paojiaCan;
//
//    int OutCheckR = 0;  //ˮƽ����ɽ⽫����� Ranks
//    int OutCheckF = 0;  //���·���ɽ⽫����� Files  
//
//    SlideMoveStruct *psmv;
//
//    SlideMaskStruct *psF;
//    SlideMaskStruct *psR;   
//
//    if(pos->side == WHITE){   //�췽Ҫ�⽫
//
//        int MyKing256  = PieceListStart(pos,RKING);
//        int MyKingX    = StoX(MyKing256);
//        int MyKingY    = StoY(MyKing256);
//        int ky4        = MyKing256 & 0xf0;
//
//        int MyKingFile = pos->wBitFiles[MyKingX];
//        int MyKingRank = pos->wBitRanks[MyKingY];
//
//        //�õ�����������Ϣ
//        psmv = FileMove(MyKingY,MyKingFile);
//        //�õ�������ĵ�һ������
//        K256Up1 = psmv->RookCap[DUpLeft] + MyKingX;
//        if(K256Up1 != MyKing256){
//            int chess1    = pos->b256[K256Up1];
//            if(chess1 == BCHE){
//                CheckType                       |= CheCheck;
//                CheckPos256[CheckPieceNum++]     = K256Up1;
//            }
//            else if(chess1 == BPAWN){
//                if((K256Up1 + 16) == MyKing256){
//                    CheckType                   |= PawnCheck;
//                    CheckPos256[CheckPieceNum++]     = K256Up1;
//                }
//            }
//            else if(chess1 == BPAO){
//                NotToFile  = UpMask(MyKing256) & LoMask(K256Up1);       //���ܵ����Ǹ��ط�
//            }
//            //���˵�һ������,���еڶ���������
//            K256Up2 = psmv->CannonCap[DUpLeft] + MyKingX;
//            if(K256Up2 != MyKing256){
//                int chess2      = pos->b256[K256Up2];
//                if(chess2 == BPAO){                   //���ڽ���
//                    CheckType                       |= PaoCheck;
//                    CheckPos256[CheckPieceNum++]     = K256Up2;
//
//                    PaoJia256[PaoJiaNum]             = K256Up1;
//                    PaoJiaChess[PaoJiaNum]           = chess1;
//                    PaoDir[PaoJiaNum]                = DirUp;
//                    PaoHuo256[PaoJiaNum]             = 0;
//                    PaoJiaNum ++;
//
//                    if(chess1 == BPAO){             //�ڼ����ǶԷ��ĺ���,���ڽ�
//                        OutCheckF = UpMask(K256Up1) & LoMask(K256Up2) | yBitMask(K256Up2);
//                    }
//                    else{
//                        OutCheckF =(UpMask(MyKing256) & LoMask(K256Up2) 
//                            | yBitMask(K256Up2)) ^ yBitMask(K256Up1); // �������ȼ���, �ü���������
//                    }
//                }
//                else if(chess2 == BCHE || chess2 == BKING){  //���������Ǻڳ�,��ڽ�,��KingUp1�����Ӳ��ܶ��˽�
//                    if(IsWhite(chess1)){
//                        //Not48Pos[NotNum]            = chess481;
//                        Not256Pos[NotNum]           = K256Up1;
//                        //board->P48[chess481]        = 0;
//                        RemovePiece(pos, K256Up1);
//                        NotNum++;
//                    }
//                }
//                //���˵ڶ�������,���е�����������
//                K256Up3 = psmv ->SuperCap[DUpLeft] + MyKingX;                
//                if(K256Up3 != MyKingX){                   
//                    int chess3  = pos->b256[K256Up3];
//                    if(chess2 == BPAO){
//                        PaoHuo256[PaoJiaNum-1]      = K256Up3;
//                        PaoHuoChess[PaoJiaNum-1]    = chess3;
//                    }
//
//                    if(chess3 == BPAO){         //�����������Ǻ���,1,�ڶ������Ӳ����ܽ⽫��,                         
//                        if(IsWhite(chess2)){
//                            Not256Pos[NotNum]           = K256Up2;
//                            RemovePiece(pos, K256Up2);
//                            NotNum++;
//                        }
//                        if(IsWhite(chess1) && chess2 != BCHE && chess2 != BKING){
//                            Not256Pos[NotNum]           = K256Up1;
//                            RemovePiece(pos, K256Up1);
//                            NotNum++;                           
//                        }
//                    }
//                } 
//            }            
//        }
//        //�õ�������ĵ�һ������
//        K256Lo1 = psmv->RookCap[DLoRight] + MyKingX;
//        if(K256Lo1 != MyKing256){
//            int chess1 = pos->b256[K256Lo1];
//            if( chess1 == BCHE){
//                CheckType                       |= CheCheck;
//                CheckPos256[CheckPieceNum++]     = K256Lo1;
//            }
//            else if(chess1 == BPAO){
//                NotToFile |= UpMask(K256Lo1) & LoMask(MyKing256);
//            }
//            //���˵�һ������,���еڶ���������
//            K256Lo2 = psmv->CannonCap[DLoRight] + MyKingX;
//            if(K256Lo2 != MyKing256){
//                int chess2 = pos->b256[K256Lo2];
//                if(chess2 == BPAO){
//                    CheckType                      |= PaoCheck;
//                    CheckPos256[CheckPieceNum++]    = K256Lo2;
//
//                    PaoJia256[PaoJiaNum]            = K256Lo1;
//                    PaoJiaChess[PaoJiaNum]          = chess1;                   
//                    PaoDir[PaoJiaNum]               = DirLow;
//                    PaoHuo256[PaoJiaNum]            = 0;              //��ʱ��Ϊ0
//                    PaoJiaNum ++;
//                    OutCheckF    = yBitMask(K256Lo2);              //ֻ�ܳ���
//                }
//                else if(chess2 == BCHE){
//                    if(IsWhite(chess1)){
//                        Not256Pos[NotNum]            = K256Lo1;
//                        RemovePiece(pos, K256Lo1);
//                        NotNum++;
//                    }
//                }
//            }
//        } //��˧���治�����е��������� 
//        //�����ж�һ��
//        psmv = RankMove(MyKingX,MyKingRank);
//
//        K256Left1 = psmv->RookCap[DUpLeft] + ky4;
//        if(K256Left1 != MyKing256){
//            int chess1 = pos->b256[K256Left1];
//            if(chess1 == BCHE){
//                CheckType                          |= CheCheck;
//                CheckPos256[CheckPieceNum++]        = K256Left1;
//            }
//            else if((chess1 == BPAWN) &&(K256Left1 == MyKing256-1)){
//                CheckType                          |= PawnCheck;  
//                CheckPos256[CheckPieceNum++]        = K256Left1;
//            }
//            else if(chess1 == BPAO){
//                NotToRank |= LeftMask(MyKing256) & RightMask(K256Left1);
//            }
//            //���˵�һ������,���еڶ���������
//            K256Left2 = psmv->CannonCap[DUpLeft] + ky4;
//            if(K256Left2 != MyKing256){
//                int chess2 = pos->b256[K256Left2];
//                if(chess2 == BPAO){
//                    CheckType                      |= PaoCheck;
//                    CheckPos256[CheckPieceNum++]    = K256Left2;
//
//                    PaoJia256[PaoJiaNum]            = K256Left1;
//                    PaoJiaChess[PaoJiaNum]          = chess1;                   
//                    PaoDir[PaoJiaNum]               = DirLeft;
//                    PaoHuo256[PaoJiaNum]            = 0;              //��ʱ��Ϊ0
//                    PaoJiaNum ++;
//
//                    if(chess1 == BPAO){
//                        OutCheckR =  RightMask(K256Left2) & LeftMask(K256Left1) | xBitMask(K256Left2);
//                    }
//                    else {
//                        OutCheckR = (RightMask(K256Left2) & LeftMask(MyKing256)  | xBitMask(K256Left2)) ^ xBitMask(K256Left1);
//                    }
//                }
//                else if(chess2 == BCHE){
//                    if(IsWhite(chess1)){
//                        Not256Pos[NotNum]           = K256Left1;
//                        RemovePiece(pos, K256Left1);
//                        NotNum++;
//                    }
//                }
//                //���˶������е�����
//                K256Left3 = psmv->SuperCap[DUpLeft] + ky4;
//                if(K256Left3 != MyKing256){
//                    int chess3 = pos->b256[K256Left3];
//                    if(chess2 == BPAO){
//                        PaoHuo256[PaoJiaNum-1]      = K256Left3;
//                        PaoHuoChess[PaoJiaNum-1]    = chess3;
//                    }
//                    if(chess3 == BPAO){         //�����������Ǻ���,1,�ڶ������Ӳ����ܽ⽫��,  
//                        if(IsWhite(chess2)){
//                            Not256Pos[NotNum]            = K256Left2;
//                            RemovePiece(pos, K256Left2);
//                            NotNum++;
//                        }
//                        if(IsWhite(chess1) && chess2 != BCHE){                        
//                            Not256Pos[NotNum]            = K256Left1;
//                            RemovePiece(pos, K256Left1);
//                            NotNum++;                        
//                        }
//                    } 
//                }
//            }
//        }
//        //�����ж�һ��
//        K256Right1 = psmv->RookCap[DLoRight] + ky4;
//        if(K256Right1 != MyKing256){
//            int chess1 = pos->b256[K256Right1];
//            if(chess1 == BCHE){
//                CheckType                          |= CheCheck;
//                CheckPos256[CheckPieceNum++]        = K256Right1;
//            }
//            else if((chess1 == BPAWN) &&(K256Right1 == MyKing256+1)){
//                CheckType                          |= PawnCheck;  
//                CheckPos256[CheckPieceNum++]        = K256Right1;
//            }
//            else if(chess1 == BPAO){
//                NotToRank |= LeftMask(K256Right1) & RightMask(MyKing256);
//            }
//            //���˵�һ������,���еڶ���������
//            K256Right2 = psmv->CannonCap[DLoRight] + ky4;
//            if(K256Right2 != MyKing256){
//                int chess2 = pos->b256[K256Right2];
//                if(chess2 == BPAO){
//                    CheckType                      |= PaoCheck;
//                    CheckPos256[CheckPieceNum++]    = K256Right2;
//
//                    PaoJia256[PaoJiaNum]            = K256Right1;
//                    PaoJiaChess[PaoJiaNum]          = chess1;                   
//                    PaoDir[PaoJiaNum]               = DirRight;
//                    PaoHuo256[PaoJiaNum]            = 0;              //��ʱ��Ϊ0
//                    PaoJiaNum ++;
//
//                    if(chess1 == BPAO){
//                        OutCheckR =  RightMask(K256Right1) & LeftMask(K256Right2) | xBitMask(K256Right2);
//                    }
//                    else {
//                        OutCheckR = (RightMask(MyKing256)  & LeftMask(K256Right2)  | xBitMask(K256Right2)) ^ xBitMask(K256Right1);
//                    }
//                }
//                else if(chess2 == BCHE){
//                    if(IsWhite(chess1)){
//                        Not256Pos[NotNum]           = K256Right1;
//                        RemovePiece(pos, K256Right1);
//                        NotNum++;
//                    }
//                }
//                //���˵ڶ�������,���е�����������
//                K256Right3 = psmv->SuperCap[DLoRight] + ky4;
//                if(K256Right3 != MyKing256){
//                    int chess3 = pos->b256[K256Right3];
//                    if(chess2 == BPAO){
//                        PaoHuo256[PaoJiaNum-1]      = K256Right3;
//                        PaoHuoChess[PaoJiaNum-1]    = chess3;
//                    }
//
//                    if(chess3 == BPAO){ //�����������Ǻ���,1,�ڶ������Ӳ����ܽ⽫��,                        
//                        if(IsWhite(chess2)){
//                            Not256Pos[NotNum]           = K256Right2;
//                            RemovePiece(pos, K256Right2);
//                            NotNum++;
//                        }
//                        if(IsWhite(chess1) && chess2 != BCHE){                       
//                            Not256Pos[NotNum]           = K256Right1;
//                            RemovePiece(pos, K256Right1);
//                            NotNum++;                            
//                        }
//                    }
//                }
//            }
//        }
//        //�ж�һ����û�����ڽ�����
//
//        for(checkSq256 = PieceListStart(pos,BMA); checkSq256 > 0x32; checkSq256 = NextPiece(pos,checkSq256)){
//            int x       = horseLegTab(MyKing256 - checkSq256 + 256);
//            leg256  = checkSq256 + x;
//            int leg14;
//            if(x){                                  //���п��ܽ��� 
//                leg14 = pos->b256[leg256];
//                if(!leg14){                         //��������
//                    CheckType                       |= MaCheck;
//                    CheckPos256[CheckPieceNum]       = checkSq256;
//                    MaLeg256[CheckPieceNum]          = leg256;  //���������,����������,Ϊ�Ժ�⽫������
//                    CheckPieceNum++;
//                }
//                else{                               //��������������
//                    if(IsWhite(leg14)){
//                        //���ж�һ��,�ǲ����Ѿ�������
//                        bool isRemove = false;
//                        for(int i = 0; i < NotNum; i++){
//                            if(leg256 == Not256Pos[i]){
//                                isRemove = true;
//                                break;
//                            }
//                        }
//                        if(!isRemove){
//                            Not256Pos[NotNum]       = leg256;
//                            RemovePiece(pos, leg256);
//                            NotNum++;
//                        }
//                    }
//                }
//            }
//        }
//
//        ASSERT(CheckPieceNum!=0);      //���ӷ�һ��Ҫ�������� ////////////////////////////
//#if defined(DEBUG_EVASION_MOVE)
//        if(CheckPieceNum == 0){
//            board_display(pos,"ERROR ��ǰ�Ǻ췽�⽫,��û�������ڽ�!!!!\n",stdout);
//            //return ms;
//        }
//#endif
//        //----------------------------------------------------------���濪ʼ��⽫����
//        checkSq256    = CheckPos256[0];
//        checkSqX      = StoX(checkSq256);
//        checkSqY      = StoY(checkSq256);  
//        tCheckDir1    = GetDir(checkSq256, MyKing256); 
//        switch(CheckType){
//case PaoCheck:              //��ǰ�����ڽ���
//    paojia256       = PaoJia256[0];
//    paojiaX         = StoX(paojia256);
//    paojiaY         = StoY(paojia256);
//    paohouChess     = PaoHuoChess[0];       //�ڼܺ����������
//    paojiaChess     = PaoJiaChess[0]; 
//    if(PaoJiaNum > 1){  
//        int jian;
//        int tjiadir;
//        int paojia2;
//        int paocheck2;
//        if(paojiaChess >= BKING){   //�����Լ�������
//            if(PaoJiaChess[1] >= BKING){
//                  break; //board_display(pos,"����������ͬʱ�ڽ���!,û���⽫\n",stdout);               
//            }
//            else{
//                paojia256       = PaoJia256[1];
//                paojiaX         = StoX(paojia256);
//                paojiaY         = StoY(paojia256);
//                paohouChess     = PaoHuoChess[1];       //�ڼܺ����������
//                paojiaChess     = PaoJiaChess[1]; 
//                paojia2         = PaoJia256[0];
//                paocheck2       = CheckPos256[0];
//                tjiadir         = GetDir(paojia2,MyKing256);
//                jian = 1;
//            }
//        }
//        else{
//            paojia2     = PaoJia256[1];
//            paocheck2   = CheckPos256[1];
//            tjiadir     = GetDir(paojia2,MyKing256);
//            jian        = 0;
//        }
//        OutCheckF = 0;
//        OutCheckR = 0; 
//        if(tjiadir & DirUp){
//            OutCheckF =(UpMask(MyKing256) & LoMask(paocheck2) 
//                | yBitMask(paocheck2)) ^ yBitMask(paojia2); // �������ȼ���, �ü���������
//        }
//        else if(tjiadir & DirLow){
//            OutCheckF = (UpMask(paocheck2) & LoMask(MyKing256)
//                | yBitMask(paocheck2)) ^ yBitMask(paojia2);
//        }
//        else if(tjiadir & DirLeft){
//            OutCheckR = (RightMask(paocheck2) & LeftMask(MyKing256) 
//                | xBitMask(paocheck2)) ^ xBitMask(paojia2);
//        }
//        else if(tjiadir & DirRight){
//            OutCheckR = (LeftMask(paocheck2) & RightMask(MyKing256) 
//                | xBitMask(paocheck2)) ^ xBitMask(paojia2);
//        }
//
//        switch(paojiaChess){    //ֻ�к���,����,����ſ��ܽ�˫�ڽ�
//            uint8* lpDst;
//            int    tmp;
//case RMA:                            
//    lpDst = PreMaAndLegMove[paojia256];
//    tmp      = MOVE_FromFC(paojia256,RMA);
//    while(int to256 = *lpDst++){     //���Ե��ڻ����                                
//        int tx    = StoX(to256);
//        int ty    = StoY(to256);
//        if(   ((OutCheckR & xBitMask(to256)) && (ty == MyKingY)) 
//            || ((OutCheckF & yBitMask(to256)) && (tx == MyKingX)) ){
//                if(pos->b256[*lpDst] == 0){  //����û������
//                    (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,pos->b256[to256]);
//                } 
//        } 
//        lpDst++;
//    }                            
//    break;
//case RSHI:
//    lpDst = PreShiXiangAndEyeMove[paojia256];
//    tmp      = MOVE_FromFC(paojia256,RSHI);
//    while(int to256 = *lpDst++){                                
//        int tx    = StoX(to256);
//        int ty    = StoY(to256);
//        if(   ((OutCheckR & xBitMask(to256)) && (ty == MyKingY)) 
//            || ((OutCheckF & yBitMask(to256)) && (tx == MyKingX)) ){ 
//                (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,pos->b256[to256]);
//        }
//        lpDst++;
//    }
//    break;
//case RXIANG:
//    lpDst = PreShiXiangAndEyeMove[paojia256];
//    tmp      = MOVE_FromFC(paojia256,RXIANG);
//    while(int to256 = *lpDst++){                                
//        int tx    = StoX(to256);
//        int ty    = StoY(to256);
//        if(   ((OutCheckR & xBitMask(to256)) && (ty == MyKingY)) 
//            || ((OutCheckF & yBitMask(to256)) && (tx == MyKingX)) ){
//                if(pos->b256[*lpDst] == 0){  //������û������ if(!tree->board.B256[(nSrc+nDst)>>1])
//                    (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,pos->b256[to256]);
//                } 
//        }
//        lpDst++;
//    }
//    break;
//default:
//    break;
//        }
//    }
//    else{                   //ֻ��һ�����ڽ�                   
//        //int  paohou256       = 
//        //���ж�һ���ڼ��ϵ������ܲ�����
//        if(IsWhite(paojiaChess)){
//            if(paohouChess == BPAO){        //�ں�����
//                if(paojiaChess == RPAO){
//                    (ms++)->move = MOVE_FROM(paojia256,RPAO,PaoHuo256[0],BPAO);
//                }
//            }
//            else{  
//                int nSrcX = StoX(paojia256);
//                int nSrcY = StoY(paojia256);
//                int sr16  = pos->wBitRanks[nSrcY];
//                int sf16  = pos->wBitFiles[nSrcX];  
//                switch(paojiaChess){                                            //�����ڼ��ϵ�����
//                    int     tmp;
//                    uint8*  lpDst;
//case RPAWN:     //������ڼ�
//    tmp      = MOVE_FromFC(paojia256,RPAWN);
//    //1, ���ϳ��ڽ⽫
//    if((paojia256-16) == checkSq256){  
//        (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,BPAO);
//    }
//    //2,���Ҷ����⽫
//    if(paojia256<0x7b){      //���ӱ����ܽ⽫��
//        int to256 = paojia256-1;
//        int to14  = pos->b256[to256];
//        if(!IsWhite(to14)){       
//            (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,to14);
//        }
//        to256 = paojia256+1;
//        to14  = pos->b256[to256];
//        if(!IsWhite(to14)){
//            (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,to14);
//        }
//    }
//    break;
//case RPAO:      //�������ڼ�    //�����ҽ⽫, ���³��ӽ⽫  
//    tmp      = MOVE_FromFC(paojia256,RPAO);
//    psmv     = RankMove(nSrcX,sr16);
//
//    //���ҳ��Ӳ�
//    nDisp    = paojia256 & 0xf0;    
//    to256    = psmv->CannonCap[DUpLeft] + nDisp;
//    if(to256 != paojia256){
//        int to14 = pos->b256[to256];
//        if(IsBlack(to14)){
//            (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,to14);
//        }
//    }
//    to256    = psmv->CannonCap[DLoRight] + nDisp;
//    if(to256 != paojia256){
//        int to14 = pos->b256[to256];
//        if(IsBlack(to14)){
//            (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,to14);
//        }
//    }
//    if(tCheckDir1 & (DirUp+DirLow)){
//        //���Ҳ����Ӳ�
//        to256 = psmv->NonCap[DUpLeft] + nDisp;
//        while(to256 != paojia256){
//            (ms++)->move =  MOVE_FromFc_to(tmp,to256);
//            to256++;
//        }
//        to256 = psmv->NonCap[DLoRight] + nDisp;
//        while(to256 != paojia256){
//            (ms++)->move =  MOVE_FromFc_to(tmp,to256);
//            to256--;
//        }
//    }
//    // ���³��Ӳ�
//    psmv    = FileMove(nSrcY,sf16);
//    to256   = psmv->CannonCap[DUpLeft] + nSrcX;
//    if(to256 != paojia256){
//        int to14 = pos->b256[to256];
//        if(IsBlack(to14)){
//            (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,to14);
//        }
//    }
//    to256   = psmv->CannonCap[DLoRight] + nSrcX;
//    if(to256 != paojia256){
//        int to14 = pos->b256[to256];
//        if(IsBlack(to14)){
//            (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,to14);
//        }
//    }
//    if(tCheckDir1 & (DirLeft+DirRight)){    //�����Ӳ�
//        to256 = psmv->NonCap[DUpLeft] + nSrcX;
//        while(to256 != paojia256){
//            (ms++)->move =  MOVE_FromFc_to(tmp,to256);
//            to256 += 16;
//        }
//        to256 = psmv->NonCap[DLoRight] + nSrcX;
//        while(to256 != paojia256){
//            (ms++)->move =  MOVE_FromFc_to(tmp,to256);
//            to256 -= 16;
//        }
//    }
//    break;
//case RCHE:      //�쳵���ڼ�   
//    tmp      = MOVE_FromFC(paojia256,RCHE);
//    //���ҳ��Ӳ�
//    psmv     = RankMove(nSrcX,sr16);
//    //���ҳ��Ӳ�
//    nDisp    = paojia256 & 0xf0;
//    to256    = psmv->RookCap[DUpLeft] + nDisp;
//    if(to256 != paojia256){
//        int to14 = pos->b256[to256];
//        if(IsBlack(to14)){
//            (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,to14);
//        }
//    }
//    to256    = psmv->RookCap[DLoRight] + nDisp;
//    if(to256 != paojia256){
//        int to14 = pos->b256[to256];
//        if(IsBlack(to14)){
//            (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,to14);
//        }
//    }
//    if(tCheckDir1 & (DirUp+DirLow)){        //���½�,�����Ҳ����ӽ⽫
//        to256 = psmv->NonCap[DUpLeft] + nDisp;
//        while(to256 != paojia256){
//            (ms++)->move =  MOVE_FromFc_to(tmp,to256);
//            to256++;
//        }
//        to256 = psmv->NonCap[DLoRight] + nDisp;
//        while(to256 != paojia256){
//            (ms++)->move =  MOVE_FromFc_to(tmp,to256);
//            to256--;
//        }
//    }
//    //���·���⽫
//    psmv  = FileMove(nSrcY,sf16);
//    to256 = psmv->RookCap[DUpLeft] + nSrcX;
//    if(to256 != paojia256){
//        int to14 = pos->b256[to256];
//        if(IsBlack(to14)){
//            (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,to14);
//        }
//    }
//    to256 = psmv->RookCap[DLoRight] + nSrcX;
//    if(to256 != paojia256){
//        int to14 = pos->b256[to256];
//        if(IsBlack(to14)){
//            (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,to14);
//        }
//    }
//    //���ҽ�,�����²����ӽ⽫
//    if(tCheckDir1 & (DirLeft+DirRight)){    //�����Ӳ�
//        to256 = psmv->NonCap[DUpLeft] + nSrcX;
//        while(to256 != paojia256){
//            (ms++)->move =  MOVE_FromFc_to(tmp,to256);
//            to256 += 16;
//        }
//        to256 = psmv->NonCap[DLoRight] + nSrcX;
//        while(to256 != paojia256){
//            (ms++)->move =  MOVE_FromFc_to(tmp,to256);
//            to256 -= 16;
//        }
//    }                                 
//    break;
//case RMA:       //�������ڼ�        //����8������⽫ 
//    tmp      = MOVE_FromFC(paojia256,RMA);
//    lpDst = PreMaAndLegMove[paojia256];
//    while(int to256 = *lpDst++){               
//        if(pos->b256[*lpDst]){  //����������
//            lpDst++;
//            continue;
//        }
//        lpDst++;
//        int to14  =  pos->b256[to256];
//        if(IsWhite(to14)){    //���Լ��ĵ�����
//            continue;  
//        } 
//        int tx = StoX(to256);
//        int ty = StoY(to256);
//        if(tx == MyKingX){  //�ߵ���File��
//            if(NotToFile & yBitMask(to256)){
//                continue;
//            }
//        } 
//        else if(ty == MyKingY){
//            if(NotToRank & xBitMask(to256)){
//                continue;
//            }
//        }        
//        (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,to14);
//    }                                   
//    break;
//case RXIANG:    //�������ڼ�
//    tmp      = MOVE_FromFC(paojia256,RXIANG);
//    lpDst  = PreShiXiangAndEyeMove[paojia256];
//    while(int to256 = *lpDst++){                                         
//        if(pos->b256[*lpDst]){  //����������
//            lpDst++;
//            continue;
//        }
//        lpDst++;
//        int to14  =  pos->b256[to256];
//        if(IsWhite(to14)){
//            continue;
//        }  
//        int tx = StoX(to256);
//        int ty = StoY(to256);
//        if(tx == MyKingX){  //�ߵ���File��
//            if(NotToFile & yBitMask(to256)){
//                continue;
//            }
//        }
//        else if(ty == MyKingY){
//            if(NotToRank & xBitMask(to256)){
//                continue;
//            }
//        }        
//        (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,to14);
//    }
//    break;
//case RSHI:      //��ʿ���ڼ�
//    tmp      = MOVE_FromFC(paojia256,RSHI);
//    lpDst  = PreShiXiangAndEyeMove[paojia256];
//    while(int to256 = *lpDst++){                                         
//        int to14  =  pos->b256[to256];
//        if(IsWhite(to14)){
//            continue;
//        }
//        int tx = StoX(to256);
//        int ty = StoY(to256);
//        if(tx == MyKingX){  //�ߵ���File��
//            if(NotToFile & yBitMask(to256)){
//                continue;
//            }
//        }
//        else if(ty == MyKingY){
//            if(NotToRank & xBitMask(to256)){
//                continue;
//            }
//        }
//        (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,to14);
//    }
//    break;
//default:
//    break;
//                }
//            }
//        }
//        //������������Ӷ������ڼ���
//        //1.��������ڽ�*************************************************************
//        if(tCheckDir1 & DirUp){                             //���ֻ�ܽ�������ڽ� 
//            for(int nSrc256 = PieceListStart(pos,RPAWN); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){                
//
//                if(nSrc256 == paojia256){
//                    continue;
//                }
//
//                //�����ڼ��ϵı�ֻ�����ҽ⽫��
//                if(nSrc256 > 0x7b){
//                    continue;
//                }
//                int tmp      = MOVE_FromFC(nSrc256,RPAWN);
//                int to256 = nSrc256+1;
//                int tx    = StoX(to256);
//                if(tx == MyKingX){
//                    if(yBitMask(to256) & OutCheckF){                        
//                        (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,pos->b256[to256]);
//                    }
//                }
//                to256 = nSrc256-1;
//                tx    = StoX(to256);
//                if(tx == MyKingX){
//                    if(yBitMask(to256) & OutCheckF){                        
//                        (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,pos->b256[to256]);
//                    }
//                }
//            }
//        }// End ��������ڽ�
//        //���˽��ڽ�
//        for(int nSrc256 = PieceListStart(pos,RSHI); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//            if(nSrc256 == paojia256){
//                continue;
//            }
//            int tmp      = MOVE_FromFC(nSrc256,RSHI); 
//            uint8* lpDst = PreShiXiangAndEyeMove[nSrc256];
//            while(int to256 = *lpDst++){                                
//                int tx    = StoX(to256);
//                int ty    = StoY(to256);
//                if(   ((OutCheckR & xBitMask(to256)) && (ty == MyKingY)) 
//                    || ((OutCheckF & yBitMask(to256)) && (tx == MyKingX)) ){ 
//                        (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,pos->b256[to256]);
//                }
//            }
//        }//���˽��ڽ� End
//        //������ڽ�
//        for(int nSrc256 = PieceListStart(pos,RXIANG); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//
//            if(nSrc256 == paojia256){
//                continue;
//            }
//
//            int tmp         = MOVE_FromFC(nSrc256,RXIANG); 
//            uint8* lpDst    = PreShiXiangAndEyeMove[nSrc256];
//            while(int to256 = *lpDst++){                                
//                int tx    = StoX(to256);
//                int ty    = StoY(to256);
//                if(   ((OutCheckR & xBitMask(to256)) && (ty == MyKingY)) 
//                    || ((OutCheckF & yBitMask(to256)) && (tx == MyKingX)) ){
//                        if(pos->b256[*lpDst] == 0){  //������û������ if(!tree->board.B256[(nSrc+nDst)>>1])
//                            (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,pos->b256[to256]);
//                        } 
//                }
//                lpDst++;
//            }
//        }//������ڽ� End
//        //�������ڽ�
//        for(int nSrc256 = PieceListStart(pos,RMA); nSrc256 > 0x32  ; nSrc256 = NextPiece(pos,nSrc256)){
//
//            if(nSrc256 == paojia256){
//                continue;
//            }
//
//            int tmp      = MOVE_FromFC(nSrc256,RMA); 
//            uint8* lpDst = PreMaAndLegMove[nSrc256];
//            while(int to256 = *lpDst++){     //���Ե��ڻ����                                
//                int tx    = StoX(to256);
//                int ty    = StoY(to256);
//                if(   ((OutCheckR & xBitMask(to256)) && (ty == MyKingY)) 
//                    || ((OutCheckF & yBitMask(to256)) && (tx == MyKingX)) ){
//                        if(pos->b256[*lpDst] == 0){  //����û������
//                            (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,pos->b256[to256]);
//                        } 
//                } 
//                lpDst++;
//            }
//        }//�������ڽ� End
//        // 2. ���ڽ���ڽ�
//        for(int nSrc256 = PieceListStart(pos,RPAO); nSrc256 > 0x32 ; nSrc256 = NextPiece(pos,nSrc256)){
//
//            if(nSrc256 == paojia256){
//                continue;
//            }
//
//            int tmp   = MOVE_FromFC(nSrc256,RPAO); 
//            int nSrcX = StoX(nSrc256);
//            int nSrcY = StoY(nSrc256);       
//            psF  = FileMask(nSrcY,pos->wBitFiles[nSrcX]);
//            psR  = RankMask(nSrcX,pos->wBitRanks[nSrcY]);
//            if(OutCheckF){                  //���·�����Խ⽫               
//                if(nSrcX == checkSqX){      //��ͬһ��,ֻ�г԰��� 
//                    if(psF->CannonCap & yBitMask(checkSq256)){
//                        (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,BPAO);
//                    }
//                }
//                else{                       //����ͬһ��, �԰�,����
//                    if(OutCheckF & yBitMask(nSrc256)){  //�ڽ⽫������
//                        if(nSrcY == checkSqY){          //��ͬһ��
//                            if(psR->CannonCap & xBitMask(checkSq256)){
//                                (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,BPAO);
//                            }
//                        }
//                        else{
//                            if(psR->RookCap & xBitMask(checkSq256)){
//                                (ms++)->move =  MOVE_FromFc_to(tmp,XYtoS(checkSqX,nSrcY));
//                            }
//                        }                                      
//                    }
//                }
//            }
//            else if(OutCheckR){              //���ҷ�����Խ⽫                
//                if(nSrcY == checkSqY){       //��ͬһ��,ֻ�г���
//                    if(psR->CannonCap & xBitMask(checkSq256)){
//                        (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,BPAO);
//                    }
//                }
//                else{
//                    if(OutCheckR & xBitMask(nSrc256)){
//                        if(nSrcX == checkSqX){
//                            if(psF->CannonCap & yBitMask(checkSq256)){
//                                (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,BPAO);                            
//                            }
//                        }
//                        else{                    
//                            if(psF->RookCap & yBitMask(checkSq256)){
//                                (ms++)->move =  MOVE_FromFc_to(tmp,XYtoS(nSrcX,checkSqY));                           
//                            }
//                        }
//                    }
//                }
//            }
//        }// End ���ڽ���ڽ�
//        //3.�쳵�����ڽ�*************************************************************
//        for(int nSrc256 = PieceListStart(pos,RCHE); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){ 
//            if(nSrc256 == paojia256){
//                continue;
//            }
//            int tmp      = MOVE_FromFC(nSrc256,RCHE); 
//            int nSrcX = StoX(nSrc256);
//            int nSrcY = StoY(nSrc256);
//            psF  = FileMask(nSrcY,pos->wBitFiles[nSrcX]);
//            psR  = RankMask(nSrcX,pos->wBitRanks[nSrcY]);
//            if(OutCheckF){                  //���·�����Խ⽫
//                if(nSrcX == checkSqX){      //��ͬһ��,ֻ�г԰���                   
//                    if(psF->RookCap & yBitMask(checkSq256)){
//                        (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,BPAO);
//                    }
//                }
//                else{                       //����ͬһ��, �԰�,����
//                    if(OutCheckF & yBitMask(nSrc256)){  //�ڽ⽫������                        
//                        if(psR->RookCap & xBitMask(checkSq256)){
//                            int target256 = XYtoS(checkSqX,nSrcY);                             
//                            (ms++)->move =  MOVE_FromFc_to_tc(tmp,target256,pos->b256[target256]);
//                        }
//                    }
//                }
//            }
//            else if(OutCheckR){              //���ҷ�����Խ⽫
//                if(nSrcY == checkSqY){      //��ͬһ��,ֻ�г���
//                    if(psR->RookCap & xBitMask(checkSq256)){
//                        (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,BPAO);
//                    }
//                }
//                else{
//                    if(OutCheckR & xBitMask(nSrc256)){ //�ڽ⽫��������
//                        if(psF->RookCap & yBitMask(checkSq256)){
//                            int target256 = XYtoS(nSrcX,checkSqY);                             
//                            (ms++)->move =  MOVE_FromFc_to_tc(tmp,target256,pos->b256[target256]);
//                        }
//                    }
//                }
//            }
//        }// End �쳵����ڽ� 
//    }                
//    break;  //..........ֻ��һ�����ڽ� End
//case CheCheck:     //��ǰֻ��һ�����ڽ� 1, �Գ�, 2, ����
//    if(CheckPieceNum > 1){   
//        //board_display(board,"ERROR �������ڳ�ͬʱ�ڽ�����, ��ô����.....\n",log_file);  
//    }
//    else{
//        if(tCheckDir1 & DirUp){
//            OutCheckF = UpMask(MyKing256) & LoMask(checkSq256) | yBitMask(checkSq256); // �Գ�,������
//        }
//        else if(tCheckDir1 & DirLow){
//            OutCheckF = UpMask(checkSq256) & LoMask(MyKing256) | yBitMask(checkSq256);
//        }
//        else if(tCheckDir1 & DirLeft){
//            OutCheckR = (RightMask(checkSq256) & LeftMask(MyKing256)  | xBitMask(checkSq256));
//        }
//        else if(tCheckDir1 & DirRight){
//            OutCheckR = (RightMask(MyKing256) & LeftMask(checkSq256)  | xBitMask(checkSq256));
//        }
//        //1.�����ڳ���*************************************************************
//        if(tCheckDir1 & DirUp){                             //���ֻ�ܽ�����ĳ��� 
//            for(int nSrc256 = PieceListStart(pos,RPAWN); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//
//                if(nSrc256 > 0x7b){
//                    continue;   //û���ӵı����ܽ⽫��
//                }
//
//                int tmp      = MOVE_FromFC(nSrc256,RPAWN);
//                //��ֻ�����ҽ⳵����
//                int to256 = nSrc256+1;
//                int tx    = StoX(to256);
//                if(tx == MyKingX){
//                    if(yBitMask(to256) & OutCheckF){ 
//                        (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,pos->b256[to256]);
//                    }
//                }
//                to256 = nSrc256-1;
//                tx    = StoX(to256);
//                if(tx == MyKingX){
//                    if(yBitMask(to256) & OutCheckF){ 
//                        (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,pos->b256[to256]);
//                    }
//                }
//            }
//        }// End �����ڳ���
//        //���˽⳵��
//        for(int nSrc256 = PieceListStart(pos,RSHI); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//            int tmp      = MOVE_FromFC(nSrc256,RSHI);    
//            uint8* lpDst = PreShiXiangAndEyeMove[nSrc256];
//            while(int to256 = *lpDst++){                               
//                int tx    = StoX(to256);
//                int ty    = StoY(to256);
//                if(   ((OutCheckR & xBitMask(to256)) && (ty == MyKingY)) 
//                    || ((OutCheckF & yBitMask(to256)) && (tx == MyKingX)) ){   
//                        (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,pos->b256[to256]);
//                }
//            }
//        }//���˽⳵�� End
//        //����⳵��
//        for(int nSrc256 = PieceListStart(pos,RXIANG); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//            int tmp      = MOVE_FromFC(nSrc256,RXIANG);  
//            uint8* lpDst = PreShiXiangAndEyeMove[nSrc256];
//            while(int to256 = *lpDst++){                                 
//                int tx    = StoX(to256);
//                int ty    = StoY(to256);
//                if(   ((OutCheckR & xBitMask(to256)) && (ty == MyKingY)) 
//                    || ((OutCheckF & yBitMask(to256)) && (tx == MyKingX)) ){
//                        if(pos->b256[*lpDst] == 0){  //������û������ if(!tree->board.B256[(nSrc+nDst)>>1])
//                            (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,pos->b256[to256]);
//                        } 
//                }
//                lpDst++;
//            }
//        }//����⳵�� End
//        //�����ڳ��� 
//        for(int nSrc256 = PieceListStart(pos,RMA); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//            int tmp      = MOVE_FromFC(nSrc256,RMA); 
//            uint8* lpDst = PreMaAndLegMove[nSrc256];
//            while(int to256 = *lpDst++){     //���Ե�����Գ�                                
//                int tx    = StoX(to256);
//                int ty    = StoY(to256);
//                if(   ((OutCheckR & xBitMask(to256)) && (ty == MyKingY)) 
//                    || ((OutCheckF & yBitMask(to256)) && (tx == MyKingX)) ){
//                        if(pos->b256[*lpDst] == 0){  //����û������
//                            (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,pos->b256[to256]);
//                        } 
//                } 
//                lpDst++;
//            }
//        }//�����ڳ��� End
//        // 2. ���ڽ�ڳ���
//        for(int nSrc256 = PieceListStart(pos,RPAO); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//            int tmp      = MOVE_FromFC(nSrc256,RPAO); 
//            int nSrcX = StoX(nSrc256);
//            int nSrcY = StoY(nSrc256);
//            psF  = FileMask(nSrcY,pos->wBitFiles[nSrcX]);
//            psR  = RankMask(nSrcX,pos->wBitRanks[nSrcY]);
//            if(OutCheckF){                  //���·�����Խ⽫
//                if(nSrcX == checkSqX){      //��ͬһ��,ֻ�гԳ���
//                    if(psF->CannonCap & yBitMask(checkSq256)){
//                        (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,BCHE);
//                    }
//                }
//                else{                       //����ͬһ��, �Գ�,����
//                    if(OutCheckF & yBitMask(nSrc256)){  //�ڽ⽫������
//                        if(nSrcY == checkSqY){          //��ͬһ��
//                            if(psR->CannonCap & xBitMask(checkSq256)){                               
//                                (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,BCHE);
//                            }
//                        }
//                        else{
//                            if(psR->RookCap & xBitMask(checkSq256)){  
//                                (ms++)->move =  MOVE_FromFc_to(tmp,XYtoS(checkSqX,nSrcY));  
//                            }
//                        }                                      
//                    }
//                }
//            }
//            else if(OutCheckR){              //���ҷ�����Խ⽫
//                if(nSrcY == checkSqY){       //��ͬһ��,ֻ�гԳ�
//                    if(psR->CannonCap & xBitMask(checkSq256)){
//                        (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,BCHE);
//                    }
//                }
//                else{
//                    if(OutCheckR & xBitMask(nSrc256)){
//                        if(nSrcX == checkSqX){
//                            if(psF->CannonCap & yBitMask(checkSq256)){
//                                (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,BCHE);
//                            }
//                        }
//                        else{
//                            if(psF->RookCap & yBitMask(checkSq256)){  
//                                (ms++)->move =  MOVE_FromFc_to(tmp,XYtoS(nSrcX,checkSqY));  
//                            }
//                        }
//                    }
//                }
//            }
//        }// End ���ڽ�ڳ���
//        //3.�쳵��ڳ���*************************************************************
//        for(int nSrc256 = PieceListStart(pos,RCHE); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//            int tmp      = MOVE_FromFC(nSrc256,RCHE); 
//            int nSrcX = StoX(nSrc256);
//            int nSrcY = StoY(nSrc256);
//            psF  = FileMask(nSrcY,pos->wBitFiles[nSrcX]);
//            psR  = RankMask(nSrcX,pos->wBitRanks[nSrcY]);  
//            if(OutCheckF){                  //���·�����Խ⽫
//                if(nSrcX == checkSqX){      //��ͬһ��,ֻ�гԳ���
//                    if(psF->RookCap & yBitMask(checkSq256)){
//                        (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,BCHE);
//                    }
//                }
//                else{                       //����ͬһ��, �Գ�,����
//                    if(OutCheckF & yBitMask(nSrc256)){  //�ڽ⽫������
//                        if(psR->RookCap & xBitMask(checkSq256)){
//                            int target256 = XYtoS(checkSqX,nSrcY); 
//                            (ms++)->move =  MOVE_FromFc_to_tc(tmp,target256,pos->b256[target256]);
//                        }                                                                  
//                    }
//                }
//            }
//            else if(OutCheckR){              //���ҷ�����Խ⽫
//                if(nSrcY == checkSqY){      //��ͬһ��,ֻ�гԳ�
//                    if(psR->RookCap & xBitMask(checkSq256)){
//                        (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,BCHE);
//                    }
//                }
//                else{
//                    if(OutCheckR & xBitMask(nSrc256)){ //�ڽ⽫��������
//                        if(psF->RookCap & yBitMask(checkSq256)){
//                            int target256 = XYtoS(nSrcX,checkSqY);
//                            (ms++)->move =  MOVE_FromFc_to_tc(tmp,target256,pos->b256[target256]);
//                        }
//                    }
//                }
//            } 
//        }// End �쳵��ڳ��� 
//    }
//    break;      //End �ڳ�����
//case MaCheck:         //��ǰ�����ڽ�����, 1, ����, 2, ������
//    if(CheckPieceNum > 1){ 
//        if(MaLeg256[0] == MaLeg256[1]){  //ͬʱ���������ڽ�,��ֻ��Maleg��ͬ���ܽ⽫
//            leg256 = MaLeg256[0];
//            //1,  ��������ܽ���   //2,  ���˽��� 1, ����,����,
//            for(int nSrc256 = PieceListStart(pos,RSHI); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//                int tmp      = MOVE_FromFC(nSrc256,RSHI); 
//                if(inBoard(leg256) & IN_RSHI){
//                    if(GetDir(nSrc256,leg256) & DirShi){ 
//                        (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//                    } 
//                }
//            }//���˽��� End
//            //�������   if(!tree->board.B256[(nSrc256 + to256)>>1])
//            for(int nSrc256 = PieceListStart(pos,RXIANG); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//                int tmp      = MOVE_FromFC(nSrc256,RXIANG); 
//                if(inBoard(leg256) & IN_RXIANG){
//                    if(GetDir(nSrc256,leg256) & DirXiang){
//                        if(!pos->b256[(nSrc256 + leg256)>>1]){  //����û������
//                            (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//                        } 
//                    }
//                }
//            }//������� End
//            //��������
//            for(int nSrc256 = PieceListStart(pos,RMA); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//                int tmp      = MOVE_FromFC(nSrc256,RMA);
//                if(GetDir(nSrc256,leg256) & DirMa){
//                    if(!pos->b256[nSrc256 + horseLegTab(leg256 - nSrc256 + 256)]){  //����û������
//                        (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//                    } 
//                }              
//            }  //�������� End
//                    // 2. ���ڽ����
//            for(int nSrc256 = PieceListStart(pos,RPAO); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//                int tmp      = MOVE_FromFC(nSrc256,RPAO); 
//                int nSrcX = StoX(nSrc256);
//                int nSrcY = StoY(nSrc256);
//                psF  = FileMask(nSrcY,pos->wBitFiles[nSrcX]);
//                psR  = RankMask(nSrcX,pos->wBitRanks[nSrcY]);             
//
//                if(GetDir(nSrc256,leg256) & (DirUp+DirLow)){
//                    if(psF->RookCap & yBitMask(leg256)){ 
//                        (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//                    }
//                }
//                else if(GetDir(nSrc256,leg256) & (DirLeft+DirRight)){
//                    if(psR->RookCap & xBitMask(leg256)){
//                        (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//                    }
//                }
//            }// End ���ڽ����
//             // 2. �쳵�����
//            for(int nSrc256 = PieceListStart(pos,RCHE); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//                int tmp   = MOVE_FromFC(nSrc256,RCHE); 
//                int nSrcX = StoX(nSrc256);
//                int nSrcY = StoY(nSrc256);
//                psF  = FileMask(nSrcY,pos->wBitFiles[nSrcX]);
//                psR  = RankMask(nSrcX,pos->wBitRanks[nSrcY]); 
//
//                if(GetDir(nSrc256,leg256) & (DirUp+DirLow)){
//                    if(psF->RookCap & yBitMask(leg256)){ 
//                        (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//                    }
//                }
//                else if(GetDir(nSrc256,leg256) & (DirLeft+DirRight)){
//                    if(psR->RookCap & xBitMask(leg256)){
//                        (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//                    }
//                }
//            }// End �쳵�����
//        }
//    }
//    else{//����, �������ж��ܲ����ߵ��Ǹ�λ��, ��Ϊ���������γ������İ�����
//        leg256 = MaLeg256[0];
//        //1,  ��������ܽ���   //2,  ���˽��� 1, ����,����,
//        for(int nSrc256 = PieceListStart(pos,RSHI); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//            int tmp      = MOVE_FromFC(nSrc256,RSHI); 
//            if(inBoard(leg256) & IN_RSHI){
//                if(GetDir(nSrc256,leg256) & DirShi){ 
//                    (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//                } 
//            }
//            if(inBoard(checkSq256) & IN_RSHI){
//                if(GetDir(nSrc256,checkSq256) & DirShi){ 
//                    (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,BMA);
//                }
//            }
//        }//���˽��� End
//        //�������   if(!tree->board.B256[(nSrc256 + to256)>>1])
//        for(int nSrc256 = PieceListStart(pos,RXIANG); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//            int tmp      = MOVE_FromFC(nSrc256,RXIANG); 
//            if(inBoard(leg256) & IN_RXIANG){
//                if(GetDir(nSrc256,leg256) & DirXiang){
//                    if(!pos->b256[(nSrc256 + leg256)>>1]){  //����û������
//                        (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//                    } 
//                }
//            }
//            if(inBoard(checkSq256) & IN_RXIANG){
//                if(GetDir(nSrc256,checkSq256) & DirXiang){
//                    if(!pos->b256[(nSrc256 + checkSq256)>>1]){  //����û������
//                        (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,BMA);
//                    } 
//                }
//            }
//        }//������� End
//        //��������
//        for(int nSrc256 = PieceListStart(pos,RMA); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//            int tmp      = MOVE_FromFC(nSrc256,RMA);
//            if(GetDir(nSrc256,leg256) & DirMa){
//                if(!pos->b256[nSrc256 + horseLegTab(leg256 - nSrc256 + 256)]){  //����û������
//                    (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//                } 
//            }
//            else if(GetDir(nSrc256,checkSq256) & DirMa){
//                if(!pos->b256[nSrc256 + horseLegTab(checkSq256 - nSrc256 + 256)]){  //����û������
//                    (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,BMA);
//                } 
//            }                
//        }  //�������� End
//        // 2. ���ڽ����
//        for(int nSrc256 = PieceListStart(pos,RPAO); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//            int tmp      = MOVE_FromFC(nSrc256,RPAO); 
//            int nSrcX = StoX(nSrc256);
//            int nSrcY = StoY(nSrc256);
//            psF  = FileMask(nSrcY,pos->wBitFiles[nSrcX]);
//            psR  = RankMask(nSrcX,pos->wBitRanks[nSrcY]);             
//
//            if(GetDir(nSrc256,leg256) & (DirUp+DirLow)){
//                if(psF->RookCap & yBitMask(leg256)){ 
//                    (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//                }
//            }
//            else if(GetDir(nSrc256,leg256) & (DirLeft+DirRight)){
//                if(psR->RookCap & xBitMask(leg256)){
//                    (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//                }
//            }
//            if(GetDir(nSrc256,checkSq256) & (DirUp+DirLow)){
//                if(psF->CannonCap & yBitMask(checkSq256)){ 
//                    (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,BMA);
//                }
//            }
//            else if(GetDir(nSrc256,checkSq256) & (DirLeft+DirRight)){
//                if(psR->CannonCap & xBitMask(checkSq256)){
//                    (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,BMA);
//                }
//            }
//        }// End ���ڽ����
//        // 2. �쳵�����
//        for(int nSrc256 = PieceListStart(pos,RCHE); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//            int tmp   = MOVE_FromFC(nSrc256,RCHE); 
//            int nSrcX = StoX(nSrc256);
//            int nSrcY = StoY(nSrc256);
//            psF  = FileMask(nSrcY,pos->wBitFiles[nSrcX]);
//            psR  = RankMask(nSrcX,pos->wBitRanks[nSrcY]); 
//
//            if(GetDir(nSrc256,leg256) & (DirUp+DirLow)){
//                if(psF->RookCap & yBitMask(leg256)){ 
//                    (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//                }
//            }
//            else if(GetDir(nSrc256,leg256) & (DirLeft+DirRight)){
//                if(psR->RookCap & xBitMask(leg256)){
//                    (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//                }
//            }
//            if(GetDir(nSrc256,checkSq256) & (DirUp+DirLow)){
//                if(psF->RookCap & yBitMask(checkSq256)){ 
//                    (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,BMA);
//                }
//            }
//            else if(GetDir(nSrc256,checkSq256) & (DirLeft+DirRight)){
//                if(psR->RookCap & xBitMask(checkSq256)){ 
//                    (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,BMA);
//                }
//            }
//        }// End �쳵�����
//    }
//    break;            //End����
//case PawnCheck:       //��һ�����ڽ�, ������ͬʱ���������ڽ�, ֻ�г������⽫
//    //2, ������佫, 1, ��������ܽ��佫
//    for(int nSrc256 = PieceListStart(pos,RXIANG); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//        int tmp   = MOVE_FromFC(nSrc256,RXIANG);
//        if(GetDir(nSrc256,checkSq256) & DirXiang){
//            if(!pos->b256[(nSrc256 + checkSq256)>>1]){ 
//                (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,BPAWN);
//            }
//        }
//    } 
//    //3,���˽��佫
//    if(inBoard(checkSq256) & IN_RSHI){
//        for(int nSrc256 = PieceListStart(pos,RSHI); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//            int tmp   = MOVE_FromFC(nSrc256,RSHI);             
//            if(GetDir(nSrc256,checkSq256) & DirShi){
//                (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,BPAWN);
//            }        
//        }//���˽��佫 End                
//    }
//    //3,������佫                
//    for(int nSrc256 = PieceListStart(pos,RMA); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//        int tmp   = MOVE_FromFC(nSrc256,RMA);
//        if(GetDir(nSrc256,checkSq256) & DirMa){
//            if(!pos->b256[nSrc256 + horseLegTab(checkSq256 - nSrc256 + 256)]){  //����û������
//                (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,BPAWN);
//            } 
//        }                   
//    }  //�������佫 End
//    //���ڽ��佫                
//    for(int nSrc256 = PieceListStart(pos,RPAO); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//        int tmp   = MOVE_FromFC(nSrc256,RPAO);   
//        int nSrcX = StoX(nSrc256);
//        int nSrcY = StoY(nSrc256);
//        psF  = FileMask(nSrcY,pos->wBitFiles[nSrcX]);
//        psR  = RankMask(nSrcX,pos->wBitRanks[nSrcY]);   
//
//        if(GetDir(nSrc256,checkSq256) & (DirUp+DirLow)){
//            if(psF->CannonCap & yBitMask(checkSq256)){ 
//                (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,BPAWN);
//            }
//        }
//        else if(GetDir(nSrc256,checkSq256) & (DirLeft+DirRight)){
//            if(psR->CannonCap & xBitMask(checkSq256)){
//                (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,BPAWN);
//            }
//        }
//    } // End ���ڽ���佫
//    //�쳵���佫                
//    for(int nSrc256 = PieceListStart(pos,RCHE); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//        int tmp   = MOVE_FromFC(nSrc256,RCHE);  
//        int nSrcX = StoX(nSrc256);
//        int nSrcY = StoY(nSrc256);
//        psF  = FileMask(nSrcY,pos->wBitFiles[nSrcX]);
//        psR  = RankMask(nSrcX,pos->wBitRanks[nSrcY]); 
//        if(GetDir(nSrc256,checkSq256) & (DirUp+DirLow)){
//            if(psF->RookCap & yBitMask(checkSq256)){
//                (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,BPAWN);
//            }
//        }
//        else if(GetDir(nSrc256,checkSq256) & (DirLeft+DirRight)){
//            if(psR->RookCap & xBitMask(checkSq256)){  
//                (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,BPAWN);
//            }
//        }
//    } // End �쳵����佫
//    break;
//case MaCheck | PaoCheck:    //����˫��,�ɽ⽫
//    paojia256    = PaoJia256[0];
//    //if(NextPiece(pos,paojia256) < 0x33){ //if(board->P48[board->P256[paojia256]] == 0){   //�ڼ��ϵ����Ӳ���������
//    //    break;
//    //}
//
//    paojiaCan = true;
//    for(int i = 0; i<NotNum; i++){
//        if(paojia256 == Not256Pos[i]){
//            paojiaCan = false;
//            break;
//        }
//    }
//    if(false == paojiaCan){
//        break;
//    }
//    leg256       = MaLeg256[1];    
//    paojiaChess  = PaoJiaChess[0];
//    paohou256    = PaoHuo256[0];
//    int tmp;
//    int nSrcX;
//    int nSrcY;
//    switch(paojiaChess){
//        //case RPAWN:             //������
//        //    Print(4095,"����˫��,���û���⽫,�����⽫");
//        //    DisplayChessBoard(tree->board);
//        //    break;                        
//case RXIANG:            //������ 
//    tmp   = MOVE_FromFC(paojia256,RXIANG);  
//    if(inBoard(leg256) & IN_RXIANG){
//        if(GetDir(paojia256,leg256) & DirXiang){
//            if(!pos->b256[(paojia256 + leg256)>>1]){  //����û������ 
//                (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//            }
//        }
//    }
//    if(inBoard(CheckPos256[1]) & IN_RXIANG){
//        if(GetDir(paojia256,CheckPos256[1]) & DirXiang){
//            if(!pos->b256[(paojia256 + CheckPos256[1])>>1]){  //����û������ 
//                (ms++)->move =  MOVE_FromFc_to_tc(tmp,CheckPos256[1],BMA);
//            }
//        }
//    }
//    break;
//case RSHI:
//    tmp   = MOVE_FromFC(paojia256,RSHI);  
//    if(inBoard(leg256) & IN_RSHI){ 
//        if(inBoard(leg256) & IN_RSHI){
//            if(GetDir(paojia256,leg256) & DirShi){
//                (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//            }
//        }
//    }
//    if(inBoard(CheckPos256[1]) & IN_RSHI){  
//        if(inBoard(CheckPos256[1]) & IN_RSHI){
//            if(GetDir(paojia256,CheckPos256[1]) & DirShi){
//                (ms++)->move =  MOVE_FromFc_to_tc(tmp,CheckPos256[1],BMA);
//            }
//        }
//    }
//    break;
//case RMA:
//    tmp   = MOVE_FromFC(paojia256,RMA); 
//    if(GetDir(paojia256,leg256) & DirMa){
//        if(!pos->b256[paojia256 + horseLegTab(leg256 - paojia256 + 256)]){  //����û������
//            (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//        } 
//    }
//    else if(GetDir(paojia256,CheckPos256[1]) & DirMa){
//        if(!pos->b256[paojia256 + horseLegTab(CheckPos256[1] - paojia256 + 256)]){  //����û������
//            (ms++)->move =  MOVE_FromFc_to_tc(tmp,CheckPos256[1],BMA);
//        } 
//    } 
//    break;
//case RPAO:
//    tmp   = MOVE_FromFC(paojia256,RPAO); 
//    nSrcX = StoX(paojia256);
//    nSrcY = StoY(paojia256);
//    psF  = FileMask(nSrcY,pos->wBitFiles[nSrcX]);
//    psR  = RankMask(nSrcX,pos->wBitRanks[nSrcY]);  
//    if(GetDir(paojia256,leg256) & (DirUp+DirLow)){
//        if(psF->RookCap & yBitMask(leg256)){ 
//            (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//        }
//    }
//    else if(GetDir(paojia256,leg256) & (DirLeft+DirRight)){
//        if(psR->RookCap & xBitMask(leg256)){
//            (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//        }
//    }
//    if(GetDir(paojia256,CheckPos256[1]) & (DirUp+DirLow)){
//        if(psF->CannonCap & yBitMask(CheckPos256[1])){ 
//            (ms++)->move =  MOVE_FromFc_to_tc(tmp,CheckPos256[1],BMA);
//        }
//    }
//    else if(GetDir(paojia256,CheckPos256[1]) & (DirRight+DirLeft)){
//        if(psR->CannonCap & xBitMask(CheckPos256[1])){ 
//            (ms++)->move =  MOVE_FromFc_to_tc(tmp,CheckPos256[1],BMA);
//        }
//    }
//    break;
//case RCHE:
//    tmp   = MOVE_FromFC(paojia256,RCHE); 
//    nSrcX = StoX(paojia256);
//    nSrcY = StoY(paojia256);
//    psF  = FileMask(nSrcY,pos->wBitFiles[nSrcX]);
//    psR  = RankMask(nSrcX,pos->wBitRanks[nSrcY]); 
//
//    if(GetDir(paojia256,leg256) & (DirUp+DirLow)){
//        if(psF->RookCap & yBitMask(leg256)){ 
//            (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//        }
//    }
//    else if(GetDir(paojia256,leg256) & (DirLeft+DirRight)){
//        if(psR->RookCap & xBitMask(leg256)){
//            (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//        }
//    }
//    if(GetDir(paojia256,CheckPos256[1]) & (DirUp+DirLow)){
//        if(psF->RookCap & yBitMask(CheckPos256[1])){ 
//            (ms++)->move =  MOVE_FromFc_to_tc(tmp,CheckPos256[1],BMA);
//        }
//    }
//    else if(GetDir(paojia256,CheckPos256[1]) & (DirRight+DirLeft)){
//        if(psR->RookCap & xBitMask(CheckPos256[1])){
//            (ms++)->move =  MOVE_FromFc_to_tc(tmp,CheckPos256[1],BMA);
//        }
//    }
//    break;
//default:
//    break;
//    }
//    break;
//case CheCheck | PaoCheck:   //����˫��, ��Щ����ɽ⽫, �������һֱ��,���ɽ⽫
//    if(CheckPieceNum > 2){
//        //���������ڽ�,���ܽ⽫
//        break;
//    }
//    //CheckDir1 = IsCanTo(CheckPos256[1],CheckPos256[0]);
//    tCheckDir1 = GetDir(CheckPos256[1],CheckPos256[0]);
//    if(!(tCheckDir1 & DirChe)){               
//        /* Print(4095,"�ڷ�����˫��,�Ҳ���һֱ��, û���⽫,ֻ�ж����⽫");
//        DisplayChessBoard(tree->board); */
//        break;
//    }
//    if(tCheckDir1 & DirUp){
//        OutCheckF  = UpMask(MyKing256) & LoMask(K256Up1);
//    }
//    else if(tCheckDir1 & DirLow){
//        OutCheckF  = LoMask(MyKing256) & UpMask(K256Lo1); 
//    }
//    else if(tCheckDir1 & DirLeft){
//        OutCheckR  = LeftMask(MyKing256) &  RightMask(K256Left1);
//    }
//    else if(tCheckDir1 & DirRight){
//        OutCheckR =  RightMask(MyKing256) & LeftMask(K256Right1);
//    }
//    //1.����⳵�ڽ�*************************************************************
//    //if(CheckDir1 == DirUp){                             //���ֻ�ܽ�����ĳ��ڽ� 
//    if(tCheckDir1 & DirUp){
//        //for(int p48=27; p48<32; p48++){
//        //    if((nSrc256 = board->P48[p48])){      //���к������ʱ 
//        for(int nSrc256 = PieceListStart(pos,RPAWN); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//            int tmp   = MOVE_FromFC(nSrc256,RPAWN);  
//            if(nSrc256 > 0x7b){
//                continue;
//            }
//            //�����ڼ��ϵı�ֻ�����ҽ⽫��
//            int to256 = nSrc256+1;
//            int tx    = StoX(to256);
//            if(tx == MyKingX){
//                if(yBitMask(to256) & OutCheckF){  
//                    (ms++)->move =  MOVE_FromFc_to(tmp,to256);
//                }
//            }
//            to256 = nSrc256-1;
//            tx    = StoX(to256);
//            if(tx == MyKingX){
//                if(yBitMask(to256) & OutCheckF){
//                    (ms++)->move =  MOVE_FromFc_to(tmp,to256);
//                }
//            }
//        }
//    }// End ����⳵�ڽ�
//    //���˽⳵�ڽ�
//    for(int nSrc256 = PieceListStart(pos,RSHI); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//        int tmp      = MOVE_FromFC(nSrc256,RSHI);  
//        uint8* lpDst = PreShiXiangAndEyeMove[nSrc256];
//        while(int to256 = *lpDst++){                            
//            int tx    = StoX(to256);
//            int ty    = StoY(to256);
//            if(   ((OutCheckR & xBitMask(to256)) && (ty == MyKingY)) 
//                || ((OutCheckF & yBitMask(to256)) && (tx == MyKingX)) ){ 
//                    (ms++)->move =  MOVE_FromFc_to(tmp,to256);
//            }
//        }        
//    }//���˽⳵�ڽ� End
//    //����⳵�ڽ�
//    for(int nSrc256 = PieceListStart(pos,RXIANG); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//        int tmp      = MOVE_FromFC(nSrc256,RXIANG); 
//        uint8* lpDst = PreShiXiangAndEyeMove[nSrc256];
//        while(int to256 = *lpDst++){                            
//            int tx    = StoX(to256);
//            int ty    = StoY(to256);
//            if(   ((OutCheckR & xBitMask(to256)) && (ty == MyKingY)) 
//                || ((OutCheckF & yBitMask(to256)) && (tx == MyKingX)) ){
//                    if(!pos->b256[*lpDst]){  //������û������ if(!tree->board.B256[(nSrc+nDst)>>1]) 
//                        (ms++)->move =  MOVE_FromFc_to(tmp,to256);
//                    } 
//            }
//            lpDst++;
//        }        
//    }//����⳵�ڽ� End
//    //����⳵�ڽ�
//    for(int nSrc256 = PieceListStart(pos,RMA); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//        int tmp      = MOVE_FromFC(nSrc256,RMA); 
//        uint8* lpDst = PreMaAndLegMove[nSrc256];
//        while(int to256 = *lpDst++){     //���Ե��ڻ����                            
//            int tx    = StoX(to256);
//            int ty    = StoY(to256);
//            if(   ((OutCheckR & xBitMask(to256)) && (ty == MyKingY)) 
//                || ((OutCheckF & yBitMask(to256)) && (tx == MyKingX)) ){
//                    if(!pos->b256[*lpDst]){  //����û������                       
//                        (ms++)->move =  MOVE_FromFc_to(tmp,to256);
//                    } 
//            } 
//            lpDst++;
//        }                                
//    }   ////����⳵�ڽ� End
//    // 2. ���ڽ�ڳ��ڽ�
//    for(int nSrc256 = PieceListStart(pos,RPAO); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//        int tmp      = MOVE_FromFC(nSrc256,RPAO); 
//        int nSrcX = StoX(nSrc256);
//        int nSrcY = StoY(nSrc256);
//        psF  = FileMask(nSrcY,pos->wBitFiles[nSrcX]);
//        psR  = RankMask(nSrcX,pos->wBitRanks[nSrcY]); 
//
//        if(OutCheckF){                  //���·�����Խ⽫
//            if(nSrcX != checkSqX){      //����ͬһ��,                                                    
//                if(OutCheckF & yBitMask(nSrc256)){  //�ڽ⽫������
//                    if(nSrcY != checkSqY){          //����ͬһ��                                           
//                        if(psR->RookCap & xBitMask(checkSq256)){    //����
//                            (ms++)->move =  MOVE_FromFc_to(tmp,XYtoS(checkSqX,nSrcY)); 
//                        }
//                    }                                      
//                }
//            }
//        }
//        else if(OutCheckR){              //���ҷ�����Խ⽫
//            if(nSrcY != checkSqY){                                       
//                if(OutCheckR & xBitMask(nSrc256)){
//                    if(nSrcX != checkSqX){                                          
//                        if(psF->RookCap & yBitMask(checkSq256)){
//                            (ms++)->move =  MOVE_FromFc_to(tmp,XYtoS(nSrcX,checkSqY)); 
//                        }
//                    }
//                }
//            }
//        }    
//    } // End ���ڽ���ڽ�
//
//    // 2. �쳵��ڳ��ڽ�
//    for(int nSrc256 = PieceListStart(pos,RCHE); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//        int tmp      = MOVE_FromFC(nSrc256,RCHE); 
//        int nSrcX = StoX(nSrc256);
//        int nSrcY = StoY(nSrc256);
//        psF  = FileMask(nSrcY,pos->wBitFiles[nSrcX]);
//        psR  = RankMask(nSrcX,pos->wBitRanks[nSrcY]); 
//
//        if(OutCheckF){                  //���·�����Խ⽫
//            if(nSrcX != checkSqX){      //����ͬһ��,                                                    
//                if(OutCheckF & yBitMask(nSrc256)){  //�ڽ⽫������
//                    if(nSrcY != checkSqY){          //����ͬһ��                                           
//                        if(psR->RookCap & xBitMask(checkSq256)){    //����
//                            (ms++)->move =  MOVE_FromFc_to(tmp,XYtoS(checkSqX,nSrcY)); 
//                        }
//                    }                                      
//                }
//            }
//        }
//        else if(OutCheckR){              //���ҷ�����Խ⽫
//            if(nSrcY != checkSqY){       //��ͬһ��,ֻ�г���                                   
//                if(OutCheckR & xBitMask(nSrc256)){
//                    if(nSrcX != checkSqX){ 
//                        if(psF->RookCap & yBitMask(checkSq256)){   //����
//                            (ms++)->move =  MOVE_FromFc_to(tmp,XYtoS(nSrcX,checkSqY)); 
//                        }
//                    }
//                }
//            }
//        }    
//    } // End ���ڽ���ڽ� 
//
//    break;
//case CheCheck | PawnCheck:  //����˫��, �����������ܽ⽫��
//    /*Print(4095,"����˫��,û���⽫,ֻ�ж����⽫");
//    DisplayChessBoard(tree->board);*/
//    break;
//case PaoCheck | PawnCheck:
//    /*Print(4095,"�ڱ�˫��,û���⽫,ֻ�ж����⽫");
//    DisplayChessBoard(tree->board);*/
//    break;
//case MaCheck | PawnCheck:   //���˫��,���ɽ⽫
//    /*DisplayChessBoard(tree->board);
//    Print(4095,"���˫��,û���⽫");*/
//    break;            
//case CheCheck | MaCheck:    //����˫��,���ɽ⽫
//    //DisplayChessBoard(tree->board);
//    //Print(4095,"����˫��,û���⽫");
//    break;            
//default:        //�������,�����ܳ�����
//    /* Print(4095,"��������Ľ���,��һ����û�취�⽫�ۣ���, ��ô����.....");  
//    DisplayChessBoard(tree->board);*/
//    break;
//        }
//        // ��󶯽����⽫��             
//        uint8* lpDst = PreKingMove[MyKing256];
//        int ktmp        = MOVE_FromFC(MyKing256,RKING); 
//        while(int to256 = *lpDst++){  
//            int to14        = pos->b256[to256];
//            int tx          = StoX(to256);
//            int ty          = StoY(to256);
//            int ky4         = to256 & 0xf0;
//            int tKingDir  = GetDir(MyKing256,to256);
//            if(!IsWhite(to14)){       //�Ǻ����������
//                if(tKingDir == tCheckDir1 && (CheckType & (CheCheck + PaoCheck))){
//                    continue;
//                }//������ߵķ����뽫���ķ�����ͬ,�ҽ��������Ӳ��Ǳ�����ô�Ͳ����ܽ⽫
//                //���ж�һ���߽���᲻�ỹ�Ǳ���              
//
//                int kToF  = pos->wBitFiles[StoX(to256)] ^ yBitMask(MyKing256);     //���Ӧ���ǶԵ���
//                int kToR  = pos->wBitRanks[StoY(to256)] ^ xBitMask(MyKing256);               
//
//                //��to�ĵ����µ���Ϣ
//                psmv = FileMove(ty,kToF);            
//                //�õ����ڽ��ϵĵ�һ������ tmp = kf & UpMask(nMyKing);
//                int tmp = psmv->RookCap[DUpLeft] + tx;
//                if(tmp != to256){
//                    checkChess = pos->b256[tmp];
//                    if(    checkChess == BCHE 
//                        || checkChess == BKING 
//                        || (checkChess == BPAWN && (tmp+16) == to256)){            //???????????????
//                            continue;                        
//                    }
//                    //���˵�һ���ſ����еڶ���
//                    tmp = psmv->CannonCap[DUpLeft] + tx;
//                    if(tmp != to256){
//                        if(pos->b256[tmp] == BPAO){
//                            continue;
//                        }
//                    }
//                }
//                //�õ�������ĵ�һ������
//                tmp = psmv->RookCap[DLoRight] + tx;
//                if(tmp != to256){
//                    if(pos->b256[tmp] == BCHE){
//                        continue;
//                    }
//                    //���˵�һ���ſ����еڶ���
//                    tmp = psmv->CannonCap[DLoRight] + tx;
//                    if(tmp != to256){ 
//                        if(pos->b256[tmp] == BPAO){
//                            continue;
//                        }
//                    }
//                }
//
//                //�õ�����������ĵ�һ������
//                psmv = RankMove(tx,kToR);
//                tmp  = psmv->RookCap[DUpLeft] + ky4;
//                if(tmp != to256){
//                    checkChess = pos->b256[tmp];
//                    if((checkChess == BCHE)
//                        || (checkChess == BPAWN && tmp+1 == to256)){
//                            continue;
//                    }
//                    //���˵�һ���ſ����еڶ���
//                    tmp = psmv->CannonCap[DUpLeft] + ky4;
//                    if(tmp != to256){
//                        if(pos->b256[tmp] == BPAO){
//                            continue;
//                        }
//                    }
//                }
//                //�õ���������ĵ�һ������
//                tmp  = psmv->RookCap[DLoRight] + ky4;
//                if(tmp != to256){
//                    checkChess = pos->b256[tmp];
//                    if((checkChess == BCHE)
//                        || (checkChess == BPAWN && tmp-1 == to256)){
//                            continue;
//                    }
//                    //���˵�һ���ſ����еڶ���
//                    tmp = psmv->CannonCap[DLoRight] + ky4;
//                    if(tmp != to256){
//                        if(pos->b256[tmp] == BPAO){
//                            continue;
//                        }
//                    }
//                }
//                //���ÿ�һ����û��������
//                bool isMaCheck = false;
//                for(int nSrc256 = PieceListStart(pos,BMA); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//                    int m = horseLegTab(to256-nSrc256+256);
//                    if(m && !pos->b256[nSrc256 + m]){
//                        isMaCheck = true;
//                        break;
//                    }
//                } 
//                if(false == isMaCheck){
//                    (ms++)->move =  MOVE_FromFc_to_tc(ktmp,to256,to14);
//                }
//            }
//        }
//    }   //�췽Ҫ�⽫ End
//    else{ //�ڷ�Ҫ�⽫...............................................................................................
//        int MyKing256      = PieceListStart(pos,BKING);                              //�ڽ���λ��
//        int MyKingX        = StoX(MyKing256);                       //�ڽ���X
//        int MyKingY        = StoY(MyKing256);                       //�ڽ���Y
//        int ky4            = MyKing256 & 0xf0;
//
//        int MyKingFile     = pos->wBitFiles[MyKingX];
//        int MyKingRank     = pos->wBitRanks[MyKingY];
//
//        //�õ�����������Ϣ
//        psmv = FileMove(MyKingY,MyKingFile);
//        //�õ�������ĵ�һ������
//        K256Up1 = psmv->RookCap[DUpLeft] + MyKingX;
//        if(K256Up1 != MyKing256){
//            int chess1      = pos->b256[K256Up1]; 
//            if(chess1 == RCHE){                                 //�쳵�ڽ�
//                CheckType                         |= CheCheck;
//                CheckPos256[CheckPieceNum++]       = K256Up1;
//            }
//            else if(chess1 == RPAO){                            //˧�����Ǻ���,�������֮������Ӳ���������
//                NotToFile = UpMask(MyKing256) & LoMask(K256Up1);               
//            }
//            //���˵�һ������,���еڶ���������
//            K256Up2 = psmv->CannonCap[DUpLeft] + MyKingX;
//            if(K256Up2 != MyKing256){
//                int chess2    = pos->b256[K256Up2];               
//                if(chess2 == RPAO){         //���ڽ���
//                    CheckType                      |= PaoCheck;
//                    CheckPos256[CheckPieceNum++]    = K256Up2;
//
//                    PaoJia256[PaoJiaNum]            = K256Up1;
//                    PaoJiaChess[PaoJiaNum]          = chess1;                   
//                    PaoDir[PaoJiaNum]               = DirUp;
//                    PaoHuo256[PaoJiaNum]            = 0;              //��ʱ��Ϊ0
//                    PaoJiaNum ++;
//                    OutCheckF                       = yBitMask(K256Up2);              //ֻ�ܳ���
//                }
//                else if(chess2 == RCHE){  //���������Ǻڳ�,��ڽ�,��KingUp1�����Ӳ��ܶ��˽�
//                    if(IsBlack(chess1)){
//                        Not256Pos[NotNum]           = K256Up1;
//                        RemovePiece(pos, K256Up1);
//                        NotNum++;
//                    }
//                }  //�ڽ����治�����е���������
//            }
//        }
//        //�õ�������ĵ�һ������
//        K256Lo1 = psmv->RookCap[DLoRight] + MyKingX;
//        if(K256Lo1 != MyKing256){
//            int chess1    = pos->b256[K256Lo1];
//            if( chess1 == RCHE){
//                CheckType                       |= CheCheck;
//                CheckPos256[CheckPieceNum++]     = K256Lo1;
//            }
//            else if(chess1 == RPAWN){
//                if((K256Lo1-16) == MyKing256){
//                    CheckType                       |= PawnCheck;
//                    CheckPos256[CheckPieceNum++]    = K256Lo1;
//                }
//            }
//            else if(chess1 == RPAO){
//                NotToFile |= UpMask(K256Lo1) & LoMask(MyKing256);
//            }            
//            //���˵�һ������,���еڶ���������
//            K256Lo2 = psmv->CannonCap[DLoRight] + MyKingX;
//            if(K256Lo2 != MyKing256){
//                int chess2    = pos->b256[K256Lo2];               
//                if(chess2 == RPAO){
//                    CheckType                      |= PaoCheck;
//                    CheckPos256[CheckPieceNum++]    = K256Lo2;
//
//                    PaoJia256[PaoJiaNum]            = K256Lo1;
//                    PaoJiaChess[PaoJiaNum]          = chess1;                   
//                    PaoDir[PaoJiaNum]               = DirLow;
//                    PaoHuo256[PaoJiaNum]            = 0;              //��ʱ��Ϊ0
//                    PaoJiaNum ++;
//
//                    if(chess1 == RPAO){ //�ڼ����ǶԷ��ĺ���,���ڽ�
//                        OutCheckF = UpMask(K256Lo2) & LoMask(K256Lo1) | yBitMask(K256Lo2);
//                    }
//                    else{
//                        OutCheckF =(UpMask(K256Lo2) & LoMask(MyKing256) 
//                            | yBitMask(K256Lo2)) ^ yBitMask(K256Lo1); // �������ȼ���, �ü���������
//                    }
//                }
//                else if(chess2 == RCHE || chess2 == RKING) {
//                    if(IsBlack(chess1)){                        
//                        Not256Pos[NotNum]           = K256Lo1;
//                        RemovePiece(pos, K256Lo1);
//                        NotNum++;
//                    }
//                }
//                //���˵ڶ������е�������
//                K256Lo3 = psmv->SuperCap[DLoRight] + MyKingX;
//                if(K256Lo3 != MyKing256){
//                    int chess3  = pos->b256[K256Lo3];
//                    if(chess2 == RPAO){
//                        PaoHuo256[PaoJiaNum-1]      = K256Lo3;
//                        PaoHuoChess[PaoJiaNum-1]    = chess3;
//                    }
//
//                    if(chess3 == RPAO){
//                        if(IsBlack(chess2)){
//                            //Not48Pos[NotNum]            = chess2;
//                            Not256Pos[NotNum]           = K256Lo2;
//                            RemovePiece(pos, K256Lo2);
//                            NotNum++;
//                        }
//                        if(IsBlack(chess1) && chess2 != RCHE && chess2 != RKING){                            
//                            Not256Pos[NotNum]           = K256Lo1;
//                            RemovePiece(pos, K256Lo1);
//                            NotNum++;
//                        }
//                    }
//                }
//            }
//        }
//        //�����ж�һ��
//        psmv = RankMove(MyKingX,MyKingRank);
//        K256Left1 = psmv->RookCap[DUpLeft] + ky4;
//        if(K256Left1 != MyKing256){
//            int chess1 = pos->b256[K256Left1];            
//            if(chess1 == RCHE){
//                CheckType                          |= CheCheck;
//                CheckPos256[CheckPieceNum++]        = K256Left1;
//            }
//            else if((chess1 == RPAWN) &&(K256Left1 == MyKing256-1)){
//                CheckType                          |= PawnCheck;  
//                CheckPos256[CheckPieceNum++]        = K256Left1;
//            }
//            else if(chess1 == RPAO){
//                NotToRank |= LeftMask(MyKing256) & RightMask(K256Left1);
//            }
//            //���˵�һ������,���еڶ���������
//            K256Left2 = psmv->CannonCap[DUpLeft] + ky4;
//            if(K256Left2 != MyKing256){
//                int chess2    = pos->b256[K256Left2];                
//                if(chess2 == RPAO){
//                    CheckType                      |= PaoCheck;
//                    CheckPos256[CheckPieceNum++]    = K256Left2;
//
//                    PaoJia256[PaoJiaNum]            = K256Left1;
//                    PaoJiaChess[PaoJiaNum]          = chess1;                   
//                    PaoDir[PaoJiaNum]               = DirLeft;
//                    PaoHuo256[PaoJiaNum]            = 0;              //��ʱ��Ϊ0
//                    PaoJiaNum ++;
//
//                    if(chess1 == RPAO){
//                        OutCheckR =  RightMask(K256Left2) & LeftMask(K256Left1) | xBitMask(K256Left2);
//                    }
//                    else {
//                        OutCheckR = (RightMask(K256Left2) & LeftMask(MyKing256)  | xBitMask(K256Left2)) ^ xBitMask(K256Left1);
//                    }
//                }
//                else if(chess2 == RCHE){
//                    if(IsBlack(chess1)){
//                        //Not48Pos[NotNum]            = chess481;
//                        Not256Pos[NotNum]           = K256Left1;
//                        //board->P48[chess481]               = 0;
//                        RemovePiece(pos, K256Left1);
//                        NotNum++;
//                    }
//                }
//                //���˵ڶ�������,���е�����������
//                K256Left3 = psmv->SuperCap[DUpLeft] + ky4;
//                if(K256Left3 != MyKing256){
//                    int chess3   = pos->b256[K256Left3];
//                    if(chess2 == RPAO){
//                        PaoHuo256[PaoJiaNum-1]      = K256Left3;
//                        PaoHuoChess[PaoJiaNum-1]    = chess3;
//                    }
//
//                    if(chess3 == RPAO){         //�����������Ǻ���,1,�ڶ������Ӳ����ܽ⽫��, 
//                        //2, ��һ������������Ǻ���,Ҳ�����ǽ⽫��
//                        if(IsBlack(chess2)){                           
//                            Not256Pos[NotNum]            = K256Left2;
//                            RemovePiece(pos, K256Left2);
//                            NotNum++;
//                        }
//                        if(IsBlack(chess1) && chess2 != RCHE){           
//                            Not256Pos[NotNum]            = K256Left1;
//                            RemovePiece(pos, K256Left1);
//                            NotNum++;
//                        }
//                    } 
//                }
//            }
//        }
//        //�����ж�һ��
//        K256Right1 = psmv->RookCap[DLoRight] + ky4;
//        if(K256Right1 != MyKing256){
//            int chess1    = pos->b256[K256Right1];           
//            if(chess1 == RCHE){
//                CheckType                          |= CheCheck;
//                CheckPos256[CheckPieceNum++]        = K256Right1;
//            }
//            else if((chess1 == RPAWN) &&(K256Right1 == MyKing256+1)){
//                CheckType                          |= PawnCheck;  
//                CheckPos256[CheckPieceNum++]        = K256Right1;
//            }
//            else if(chess1 == RPAO){
//                NotToRank |= LeftMask(K256Right1) & RightMask(MyKing256);
//            }
//            //���˵�һ������,���еڶ���������
//            K256Right2 = psmv->CannonCap[DLoRight] + ky4;
//            if(K256Right2 != MyKing256){
//                int chess2    = pos->b256[K256Right2];                
//                if(chess2 == RPAO){
//                    CheckType                      |= PaoCheck;
//                    CheckPos256[CheckPieceNum++]    = K256Right2;
//
//                    PaoJia256[PaoJiaNum]            = K256Right1;
//                    PaoJiaChess[PaoJiaNum]          = chess1;                   
//                    PaoDir[PaoJiaNum]               = DirRight;
//                    PaoHuo256[PaoJiaNum]            = 0;              //��ʱ��Ϊ0
//                    PaoJiaNum ++;
//
//                    if(chess1 == RPAO){
//                        OutCheckR =  RightMask(K256Right1) & LeftMask(K256Right2) | xBitMask(K256Right2);
//                    }
//                    else {
//                        OutCheckR = (RightMask(MyKing256)  & LeftMask(K256Right2)  | xBitMask(K256Right2)) ^ xBitMask(K256Right1);
//                    }
//                }
//                else if(chess2 == RCHE){
//                    if(IsBlack(chess1)){
//                        Not256Pos[NotNum]           = K256Right1;
//                        RemovePiece(pos, K256Right1);
//                        NotNum++;
//                    }
//                }
//                //���˵ڶ�������,���е�����������
//                K256Right3 = psmv->SuperCap[DLoRight] + ky4;
//                if(K256Right3 != MyKing256){                                      
//                    int chess3     = pos->b256[K256Right3];
//                    if(chess2 == RPAO){
//                        PaoHuo256[PaoJiaNum-1]      = K256Right3;
//                        PaoHuoChess[PaoJiaNum-1]    = chess3;
//                    }
//                    if(chess3 == RPAO){ //�����������Ǻ���,1,�ڶ������Ӳ����ܽ⽫��, 
//                        //2, ��һ������������Ǻ���,Ҳ�����ǽ⽫��
//                        if(IsBlack(chess2)){
//                            Not256Pos[NotNum]           = K256Right2;
//                            RemovePiece(pos, K256Right2);
//                            NotNum++;
//                        }
//                        if(IsBlack(chess1) && chess2 != RCHE){
//                            Not256Pos[NotNum]           = K256Right1;
//                            RemovePiece(pos, K256Right1);
//                            NotNum++;
//                        }
//                    }
//                }                
//            }
//        }
//        //�ж�һ����û�����ڽ�����
//        for(checkSq256 = PieceListStart(pos,RMA); checkSq256 > 0x32; checkSq256 = NextPiece(pos,checkSq256)){
//            int x       = horseLegTab(MyKing256 - checkSq256 + 256);
//            leg256      = checkSq256 + x;
//            int leg14;
//            if(x){                                  //���п��ܽ��� 
//                leg14   = pos->b256[leg256];
//                if(!leg14){                         //��������
//                    CheckType                       |= MaCheck;
//                    CheckPos256[CheckPieceNum]       = checkSq256;
//                    MaLeg256[CheckPieceNum]          = leg256;  //���������,����������,Ϊ�Ժ�⽫������
//                    CheckPieceNum++;
//                }
//                else{                               //��������������
//                    if(IsBlack(leg14)){
//                        //���ж�һ��,�ǲ����Ѿ�������
//                        bool isRemove = false;
//                        for(int i = 0; i < NotNum; i++){
//                            if(leg256 == Not256Pos[i]){
//                                isRemove = true;
//                                break;
//                            }
//                        }
//                        //Not48Pos[NotNum]        = leg48;
//                        if(!isRemove){
//                            Not256Pos[NotNum]       = leg256;
//                            RemovePiece(pos, leg256);
//                            NotNum++;
//                        }
//                    }
//                }
//            }
//        }
//        ASSERT(CheckPieceNum!=0);      //���ӷ�һ��Ҫ�������� ////////////////////////////
//#if defined(DEBUG_EVASION_MOVE)   
//        if(CheckPieceNum == 0){ 
//            board_display(pos,"ERROR �ڷ��⽫,��û�������ڽ�!!!!\n",stdout);
//            //return ms;
//        }
//#endif
//
//        //----------------------------------------------------------���濪ʼ��⽫����
//
//        checkSq256    = CheckPos256[0];
//        checkSqX      = StoX(checkSq256);
//        checkSqY      = StoY(checkSq256);        //�õ������ĵ�һ�����ӵķ����� 
//        tCheckDir1    = GetDir(checkSq256,MyKing256);
//        //���ݽ��������ӵ��������⽫
//        switch(CheckType){
//case PaoCheck:              //��ǰ�����ڽ���               
//    paojia256       = PaoJia256[0];
//    paojiaX         = StoX(paojia256);
//    paojiaY         = StoY(paojia256);
//    paohouChess     = PaoHuoChess[0];       //�ڼܺ����������
//    paojiaChess     = PaoJiaChess[0]; 
//    if(PaoJiaNum > 1){                    
//        //DisplayChessBoard("ERROR ����������ͬʱ�ڽ�����\n"); 
//        //Ҳ�п��ܽ⽫, ֻ��һ���ڼ����Լ��ĵ�����ܽ⽫
//        //#define  BKING             7
//        int jian;
//        //int jiadir;
//        uint32 tjiadir;
//        int paojia2;
//        //int paojia2chess;
//        int paocheck2;
//        if(paojiaChess < BKING){   //�����Լ�������
//            if(PaoJiaChess[1] < BKING){                            
//                //board_display(pos,"����������ͬʱ�ڽ���!,û���⽫\n",stdout);
//                //break;
//                break;
//            }
//            else{
//                paojia256       = PaoJia256[1];
//                paojiaX         = StoX(paojia256);
//                paojiaY         = StoY(paojia256);
//                paohouChess     = PaoHuoChess[1];       //�ڼܺ����������
//                paojiaChess     = PaoJiaChess[1]; 
//                paojia2         = PaoJia256[0];
//                paocheck2       = CheckPos256[0];
//                tjiadir         = GetDir(paojia2,MyKing256);
//                jian = 1;
//            }
//        }
//        else{
//            paojia2   = PaoJia256[1];
//            paocheck2 = CheckPos256[1];
//            //jiadir  = IsCanTo(paojia2,MyKing256);
//            tjiadir  = GetDir(paojia2,MyKing256);
//            jian   = 0;
//        }
//        OutCheckF = 0;
//        OutCheckR = 0;
//
//        if(tjiadir & DirUp){
//            OutCheckF =(UpMask(MyKing256) & LoMask(paocheck2) 
//                | yBitMask(paocheck2)) ^ yBitMask(paojia2); // �������ȼ���, �ü���������
//        }
//        else if(tjiadir & DirLow){
//            OutCheckF = (UpMask(paocheck2) & LoMask(MyKing256)
//                | yBitMask(paocheck2)) ^ yBitMask(paojia2);
//        }
//        else if(tjiadir & DirLeft){
//            OutCheckR = (RightMask(paocheck2) & LeftMask(MyKing256) 
//                | xBitMask(paocheck2)) ^ xBitMask(paojia2);
//        }
//        else if(tjiadir & DirRight){
//            OutCheckR = (LeftMask(paocheck2) & RightMask(MyKing256) 
//                | xBitMask(paocheck2)) ^ xBitMask(paojia2);
//        }
//        switch(paojiaChess){    //ֻ�к���,����,����ſ��ܽ�˫�ڽ�
//            uint8* lpDst;
//            int    tmp;
//case BMA:                            
//    lpDst     = PreMaAndLegMove[paojia256];
//    tmp      = MOVE_FromFC(paojia256,BMA);
//    while(int to256 = *lpDst++){     //���Ե��ڻ����                                
//        int tx    = StoX(to256);
//        int ty    = StoY(to256);
//        if(   ((OutCheckR & xBitMask(to256)) && (ty == MyKingY)) 
//            || ((OutCheckF & yBitMask(to256)) && (tx == MyKingX)) ){
//                if(pos->b256[*lpDst] == 0){  //����û������
//                    (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,pos->b256[to256]);
//                } 
//        } 
//        lpDst++;
//    }                            
//    break;
//case BSHI:
//    lpDst = PreShiXiangAndEyeMove[paojia256];
//    tmp   = MOVE_FromFC(paojia256,BSHI);
//    while(int to256 = *lpDst++){                                
//        int tx    = StoX(to256);
//        int ty    = StoY(to256);
//        if(   ((OutCheckR & xBitMask(to256)) && (ty == MyKingY)) 
//            || ((OutCheckF & yBitMask(to256)) && (tx == MyKingX)) ){ 
//                (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,pos->b256[to256]);
//        }
//        lpDst++;
//    }
//    break;
//case BXIANG:
//    lpDst = PreShiXiangAndEyeMove[paojia256];
//    tmp   = MOVE_FromFC(paojia256,BXIANG);
//    while(int to256 = *lpDst++){                                
//        int tx    = StoX(to256);
//        int ty    = StoY(to256);
//        if(   ((OutCheckR & xBitMask(to256)) && (ty == MyKingY)) 
//            || ((OutCheckF & yBitMask(to256)) && (tx == MyKingX)) ){
//                if(pos->b256[*lpDst] == 0){  //������û������ if(!tree->board.B256[(nSrc+nDst)>>1])                    
//                    (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,pos->b256[to256]);
//                } 
//        }
//        lpDst++;
//    }
//    break;
//default:
//    break;
//        }
//    }
//    else{                   //ֻ��һ�����ڽ� 
//        //���ж�һ���ڼ��ϵ������ܲ�����
//        if(paojiaChess > RPAWN){
//            if(paohouChess == RPAO){
//                if(paojiaChess == BPAO){
//                    (ms++)->move = MOVE_FROM(paojia256,BPAO,PaoHuo256[0],RPAO);
//                }
//            }
//            else{ 
//                int nSrcX = StoX(paojia256);
//                int nSrcY = StoY(paojia256);
//                int sr16  = pos->wBitRanks[nSrcY];
//                int sf16  = pos->wBitFiles[nSrcX];  
//                switch(paojiaChess){                                            //�����ڼ��ϵ�����
//                    int     tmp;
//                    uint8*  lpDst;
//case BPAWN:     //�������ڼ�
//    //1, ���³��ڽ⽫
//    tmp      = MOVE_FromFC(paojia256,BPAWN);
//    if((paojia256+16) == checkSq256){ 
//        (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,RPAO);
//    }
//    //2,���Ҷ���⽫
//    if(paojia256>0x7b){      //���ӱ����ܽ⽫��
//        int to256 = paojia256-1;
//        int to14  = pos->b256[to256];
//        if(!IsBlack(to14)){    
//            (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,to14);
//        }
//        to256 = paojia256+1;
//        to14  = pos->b256[to256];
//        if(!IsBlack(to14)){   
//            (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,to14);
//        }
//    }
//    break;
//case BPAO:      //�������ڼ� 
//    tmp      = MOVE_FromFC(paojia256,BPAO);
//    psmv     = RankMove(nSrcX,sr16);
//
//    //���ҳ��˲�
//    nDisp = paojia256 & 0xf0;
//    to256 = psmv->CannonCap[DUpLeft] + nDisp;
//    if(to256 != paojia256){
//        int to14    = pos->b256[to256];
//        if(IsWhite(to14)){ 
//            (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,to14);
//        }
//    }
//    to256 = psmv->CannonCap[DLoRight] + nDisp;
//    if(to256 != paojia256){
//        int to14    = pos->b256[to256];
//        if(IsWhite(to14)){ 
//            (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,to14);
//        }
//    }
//    if(tCheckDir1 & (DirUp+DirLow)){ //���Ҳ����Ӳ�
//        //���Ҳ����Ӳ�
//        to256 = psmv->NonCap[DUpLeft] + nDisp;
//        while(to256 != paojia256){
//            (ms++)->move =  MOVE_FromFc_to(tmp,to256);
//            to256++;
//        }
//        to256 = psmv->NonCap[DLoRight] + nDisp;
//        while(to256 != paojia256){
//            (ms++)->move =  MOVE_FromFc_to(tmp,to256);
//            to256--;
//        }
//    }
//    // ���³��Ӳ�
//    psmv    = FileMove(nSrcY,sf16);
//    to256   = psmv->CannonCap[DUpLeft] + nSrcX;
//    if(to256 != paojia256){
//        int to14 = pos->b256[to256];
//        if(IsWhite(to14)){
//            (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,to14);
//        }
//    }
//    to256   = psmv->CannonCap[DLoRight] + nSrcX;
//    if(to256 != paojia256){
//        int to14 = pos->b256[to256];
//        if(IsWhite(to14)){
//            (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,to14);
//        }
//    }
//    if(tCheckDir1 & (DirLeft+DirRight)){    //�����Ӳ�
//        to256 = psmv->NonCap[DUpLeft] + nSrcX;
//        while(to256 != paojia256){
//            (ms++)->move =  MOVE_FromFc_to(tmp,to256);
//            to256 += 16;
//        }
//        to256 = psmv->NonCap[DLoRight] + nSrcX;
//        while(to256 != paojia256){
//            (ms++)->move =  MOVE_FromFc_to(tmp,to256);
//            to256 -= 16;
//        }
//    }
//    break;
//case BCHE:      //�ڳ����ڼ�   
//    tmp      = MOVE_FromFC(paojia256,BCHE);
//    psmv     = RankMove(nSrcX,sr16);
//    //���ҳ��Ӳ�
//    nDisp    = paojia256 & 0xf0;
//    to256    = psmv->RookCap[DUpLeft] + nDisp;
//    if(to256 != paojia256){
//        int to14 = pos->b256[to256];
//        if(IsWhite(to14)){
//            (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,to14);
//        }
//    }
//    to256    = psmv->RookCap[DLoRight] + nDisp;
//    if(to256 != paojia256){
//        int to14 = pos->b256[to256];
//        if(IsWhite(to14)){
//            (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,to14);
//        }
//    }
//    if(tCheckDir1 & (DirUp+DirLow)){        //���½�,�����Ҳ����ӽ⽫
//        to256 = psmv->NonCap[DUpLeft] + nDisp;
//        while(to256 != paojia256){
//            (ms++)->move =  MOVE_FromFc_to(tmp,to256);
//            to256++;
//        }
//        to256 = psmv->NonCap[DLoRight] + nDisp;
//        while(to256 != paojia256){
//            (ms++)->move =  MOVE_FromFc_to(tmp,to256);
//            to256--;
//        }
//    }
//    //���·���⽫
//    psmv  = FileMove(nSrcY,sf16);
//    to256 = psmv->RookCap[DUpLeft] + nSrcX;
//    if(to256 != paojia256){
//        int to14 = pos->b256[to256];
//        if(IsWhite(to14)){
//            (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,to14);
//        }
//    }
//    to256 = psmv->RookCap[DLoRight] + nSrcX;
//    if(to256 != paojia256){
//        int to14 = pos->b256[to256];
//        if(IsWhite(to14)){
//            (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,to14);
//        }
//    }
//    //���ҽ�,�����²����ӽ⽫
//    if(tCheckDir1 & (DirLeft+DirRight)){    //�����Ӳ�
//        to256 = psmv->NonCap[DUpLeft] + nSrcX;
//        while(to256 != paojia256){
//            (ms++)->move =  MOVE_FromFc_to(tmp,to256);
//            to256 += 16;
//        }
//        to256 = psmv->NonCap[DLoRight] + nSrcX;
//        while(to256 != paojia256){
//            (ms++)->move =  MOVE_FromFc_to(tmp,to256);
//            to256 -= 16;
//        }
//    }                                   
//    break;
//case BMA:       //�������ڼ�        //����8������⽫ 
//    tmp      = MOVE_FromFC(paojia256,BMA);
//    lpDst = PreMaAndLegMove[paojia256];
//    while(int to256 = *lpDst++){                                         
//        if(pos->b256[*lpDst]){  //����������
//            lpDst++;
//            continue;
//        }
//        lpDst++;
//        int to14  =  pos->b256[to256];
//        if(IsBlack(to14)){    //���Լ��ĵ�����
//            continue;  
//        }
//        int tx = StoX(to256);
//        int ty = StoY(to256);
//        if(tx == MyKingX){  //�ߵ���File��
//            if(NotToFile & yBitMask(to256)){
//                continue;
//            }
//        }
//        else if(ty == MyKingY){
//            if(NotToRank & xBitMask(to256)){
//                continue;
//            }
//        }  
//        (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,to14);
//    }                                   
//    break;
//case BXIANG:    //�������ڼ�
//    tmp      = MOVE_FromFC(paojia256,BXIANG);
//    lpDst  = PreShiXiangAndEyeMove[paojia256];
//    while(int to256 = *lpDst++){
//        if(pos->b256[*lpDst]){  //����������
//            lpDst++;
//            continue;
//        }
//        lpDst++;
//        int to14    = pos->b256[to256];
//        if(IsBlack(to14)){
//            continue;
//        }
//        int tx = StoX(to256);
//        int ty = StoY(to256);
//        if(tx == MyKingX){  //�ߵ���File��
//            if(NotToFile & yBitMask(to256)){
//                continue;
//            }
//        }
//        else if(ty == MyKingY){
//            if(NotToRank & xBitMask(to256)){
//                continue;
//            }
//        } 
//        (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,to14);
//    }
//    break;
//case BSHI:      //�������ڼ�
//    lpDst  = PreShiXiangAndEyeMove[paojia256];
//    tmp      = MOVE_FromFC(paojia256,BSHI);
//    while(int to256 = *lpDst++){                                         
//        int to14    = pos->b256[to256];
//        if(IsBlack(to14)){      //����Ǻ���
//            continue;
//        }
//        /* if(tree->board.B256[(to256 + paojia256)>>1]){
//        continue;
//        }*/
//        int tx = StoX(to256);
//        int ty = StoY(to256);
//        if(tx == MyKingX){  //�ߵ���File��
//            if(NotToFile & yBitMask(to256)){
//                continue;
//            }
//        }
//        else if(ty == MyKingY){
//            if(NotToRank & xBitMask(to256)){
//                continue;
//            }
//        } 
//        (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,to14);
//    }
//    break;
//default:
//    break;
//                }
//            }
//
//        }
//        //������������Ӷ������ڼ���
//        //1.�������ڽ�*************************************************************
//        //if(CheckDir1 == DirLow){                             //����ֻ�ܽ�������ڽ�  
//        if(tCheckDir1 & DirLow){
//            for(int nSrc256 = PieceListStart(pos,BPAWN); nSrc256 > 0x32 ; nSrc256 = NextPiece(pos,nSrc256)){ 
//                if(nSrc256 == paojia256){
//                    continue;
//                }
//
//                if(nSrc256 < 0x7b){
//                    continue;
//                }
//                int tmp      = MOVE_FromFC(nSrc256,BPAWN);
//                //�����ڼ��ϵı�ֻ�����ҽ⽫��
//                int to256 = nSrc256+1;
//                int tx    = StoX(to256);
//                if(tx == MyKingX){
//                    if(yBitMask(to256) & OutCheckF){ 
//                        (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,pos->b256[to256]);
//                    }
//                }
//                to256 = nSrc256-1;
//                tx    = StoX(to256);
//                if(tx == MyKingX){
//                    if(yBitMask(to256) & OutCheckF){  
//                        (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,pos->b256[to256]);
//                    }
//                }
//            }
//        }// End ���佫���ڽ�
//        //���˽���ڽ�
//        for(int nSrc256 = PieceListStart(pos,BSHI); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){                
//            if(nSrc256 == paojia256){
//                continue;
//            }
//
//            int tmp      = MOVE_FromFC(nSrc256,BSHI); 
//            uint8* lpDst = PreShiXiangAndEyeMove[nSrc256];
//            while(int to256 = *lpDst++){                                
//                int tx    = StoX(to256);
//                int ty    = StoY(to256);
//                if(   ((OutCheckR & xBitMask(to256)) && (ty == MyKingY)) 
//                    || ((OutCheckF & yBitMask(to256)) && (tx == MyKingX)) ){ 
//                        (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,pos->b256[to256]);
//                }
//            }           
//        }//���˽���ڽ� End
//        //������ڽ�
//        for(int nSrc256 = PieceListStart(pos,BXIANG); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){                
//            if(nSrc256 == paojia256){
//                continue;
//            }
//
//            int tmp         = MOVE_FromFC(nSrc256,BXIANG); 
//            uint8* lpDst = PreShiXiangAndEyeMove[nSrc256];
//            while(int to256 = *lpDst++){
//                int tx    = StoX(to256);
//                int ty    = StoY(to256);
//                if(   ((OutCheckR & xBitMask(to256)) && (ty == MyKingY)) 
//                    || ((OutCheckF & yBitMask(to256)) && (tx == MyKingX)) ){
//                        if(pos->b256[*lpDst] == 0){  //������û������ if(!tree->board.B256[(nSrc+nDst)>>1])  
//                            (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,pos->b256[to256]);
//                        } 
//                }
//                lpDst++;
//            }           
//        }//������ڽ� End
//        //�������ڽ�
//        for(int nSrc256 = PieceListStart(pos,BMA); nSrc256 > 0x32 ; nSrc256 = NextPiece(pos,nSrc256)){                
//            if(nSrc256 == paojia256){
//                continue;
//            }
//            int tmp      = MOVE_FromFC(nSrc256,BMA); 
//            uint8* lpDst = PreMaAndLegMove[nSrc256];
//            while(int to256 = *lpDst++){     //���Ե��ڻ����                                
//                int tx    = StoX(to256);
//                int ty    = StoY(to256);
//                if(   ((OutCheckR & xBitMask(to256)) && (ty == MyKingY)) 
//                    || ((OutCheckF & yBitMask(to256)) && (tx == MyKingX)) ){
//                        if(pos->b256[*lpDst] == 0){  //����û������  
//                            (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,pos->b256[to256]);
//                        } 
//                } 
//                lpDst++;
//            }                                    
//        }   ////�������ڽ� End
//        // 2. ���ڽ���ڽ�
//        for(int nSrc256 = PieceListStart(pos,BPAO); nSrc256 > 0x32 ; nSrc256 = NextPiece(pos,nSrc256)){                
//            if(nSrc256 == paojia256){
//                continue;
//            }
//            int tmp      = MOVE_FromFC(nSrc256,BPAO); 
//            int nSrcX = StoX(nSrc256);
//            int nSrcY = StoY(nSrc256);
//            psF  = FileMask(nSrcY,pos->wBitFiles[nSrcX]);
//            psR  = RankMask(nSrcX,pos->wBitRanks[nSrcY]);
//            if(OutCheckF){                  //���·�����Խ⽫               
//                if(nSrcX == checkSqX){      //��ͬһ��,ֻ�г԰��� 
//                    if(psF->CannonCap & yBitMask(checkSq256)){
//                        (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,RPAO);
//                    }
//                }
//                else{                       //����ͬһ��, �԰�,����
//                    if(OutCheckF & yBitMask(nSrc256)){  //�ڽ⽫������
//                        if(nSrcY == checkSqY){          //��ͬһ��
//                            if(psR->CannonCap & xBitMask(checkSq256)){
//                                (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,RPAO);
//                            }
//                        }
//                        else{
//                            if(psR->RookCap & xBitMask(checkSq256)){
//                                (ms++)->move =  MOVE_FromFc_to(tmp,XYtoS(checkSqX,nSrcY));
//                            }
//                        }                                      
//                    }
//                }
//            }
//            else if(OutCheckR){              //���ҷ�����Խ⽫                
//                if(nSrcY == checkSqY){       //��ͬһ��,ֻ�г���
//                    if(psR->CannonCap & xBitMask(checkSq256)){
//                        (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,RPAO);
//                    }
//                }
//                else{
//                    if(OutCheckR & xBitMask(nSrc256)){
//                        if(nSrcX == checkSqX){
//                            if(psF->CannonCap & yBitMask(checkSq256)){
//                                (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,RPAO);                            
//                            }
//                        }
//                        else{                    
//                            if(psF->RookCap & yBitMask(checkSq256)){
//                                (ms++)->move =  MOVE_FromFc_to(tmp,XYtoS(nSrcX,checkSqY));                          
//                            }
//                        }
//                    }
//                }
//            }          
//        } // End ���ڽ���ڽ�
//        //3.�ڳ�����ڽ�*************************************************************
//        for(int nSrc256 = PieceListStart(pos,BCHE); nSrc256 > 0x32 ; nSrc256 = NextPiece(pos,nSrc256)){ 
//            if(nSrc256 == paojia256){
//                continue;
//            }
//            int tmp      = MOVE_FromFC(nSrc256,BCHE); 
//            int nSrcX = StoX(nSrc256);
//            int nSrcY = StoY(nSrc256);
//            psF  = FileMask(nSrcY,pos->wBitFiles[nSrcX]);
//            psR  = RankMask(nSrcX,pos->wBitRanks[nSrcY]);
//            if(OutCheckF){                  //���·�����Խ⽫
//                if(nSrcX == checkSqX){      //��ͬһ��,ֻ�г԰���                   
//                    if(psF->RookCap & yBitMask(checkSq256)){
//                        (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,RPAO);
//                    }
//                }
//                else{                       //����ͬһ��, �԰�,����
//                    if(OutCheckF & yBitMask(nSrc256)){  //�ڽ⽫������                        
//                        if(psR->RookCap & xBitMask(checkSq256)){
//                            int target256 = XYtoS(checkSqX,nSrcY);                             
//                            (ms++)->move =  MOVE_FromFc_to_tc(tmp,target256,pos->b256[target256]);
//                        }
//                    }
//                }
//            }
//            else if(OutCheckR){              //���ҷ�����Խ⽫
//                if(nSrcY == checkSqY){      //��ͬһ��,ֻ�г���
//                    if(psR->RookCap & xBitMask(checkSq256)){
//                        (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,RPAO);
//                    }
//                }
//                else{
//                    if(OutCheckR & xBitMask(nSrc256)){ //�ڽ⽫��������
//                        if(psF->RookCap & yBitMask(checkSq256)){
//                            int target256 = XYtoS(nSrcX,checkSqY);                             
//                            (ms++)->move =  MOVE_FromFc_to_tc(tmp,target256,pos->b256[target256]);
//                        }
//                    }
//                }
//            }          
//        } // End �ڳ�����ڽ� 
//    }                
//    break;  //..........ֻ��һ�����ڽ� End
//case CheCheck:     //��ǰֻ��һ�����ڽ� 1, �Գ�, 2, ����
//    if(CheckPieceNum > 1){                    
//        //board_display(board,"ERROR �������쳵ͬʱ�ڽ�����, ��ô����.....\n",log_file); 
//    }
//    else{
//        if(tCheckDir1 & DirUp){
//            OutCheckF = UpMask(MyKing256) & LoMask(checkSq256) | yBitMask(checkSq256); // �Գ�,������
//        }
//        else if(tCheckDir1 & DirLow){
//            OutCheckF = UpMask(checkSq256) & LoMask(MyKing256) | yBitMask(checkSq256);
//        }
//        else if(tCheckDir1 & DirLeft){
//            OutCheckR = (RightMask(checkSq256) & LeftMask(MyKing256)  | xBitMask(checkSq256));
//        }
//        else if(tCheckDir1 & DirRight){
//            OutCheckR = (RightMask(MyKing256) & LeftMask(checkSq256)  | xBitMask(checkSq256));
//        }
//        //1.�����쳵��*************************************************************
//        //if(CheckDir1 == DirLow){                             //����ֻ�ܽ�����ĺ쳵��  
//        if(tCheckDir1 & DirLow){
//            for(int nSrc256 = PieceListStart(pos,BPAWN); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//                if(nSrc256 < 0x7b){
//                    continue;
//                }
//                int tmp      = MOVE_FromFC(nSrc256,BPAWN);
//                int to256 = nSrc256+1;
//                int tx    = StoX(to256);
//                if(tx == MyKingX){
//                    if(yBitMask(to256) & OutCheckF){  
//                        (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,pos->b256[to256]);
//                    }
//                }
//                to256 = nSrc256-1;
//                tx    = StoX(to256);
//                if(tx == MyKingX){
//                    if(yBitMask(to256) & OutCheckF){
//                        (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,pos->b256[to256]);
//                    }
//                }
//            }           
//        }// End ���佫�쳵��
//        //���˽�쳵��
//        for(int nSrc256 = PieceListStart(pos,BSHI); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//            int tmp      = MOVE_FromFC(nSrc256,BSHI);   
//            uint8* lpDst = PreShiXiangAndEyeMove[nSrc256];
//            while(int to256 = *lpDst++){                                   
//                int tx    = StoX(to256);
//                int ty    = StoY(to256);
//                if(   ((OutCheckR & xBitMask(to256)) && (ty == MyKingY)) 
//                    || ((OutCheckF & yBitMask(to256)) && (tx == MyKingX)) ){ 
//                        (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,pos->b256[to256]);
//                }
//            }            
//        }//���˽�쳵�� End
//        //�����쳵��
//        for(int nSrc256 = PieceListStart(pos,BXIANG); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//            int tmp      = MOVE_FromFC(nSrc256,BXIANG);  
//            uint8* lpDst = PreShiXiangAndEyeMove[nSrc256];
//            while(int to256 = *lpDst++){                                 
//                int tx    = StoX(to256);
//                int ty    = StoY(to256);
//                if(   ((OutCheckR & xBitMask(to256)) && (ty == MyKingY)) 
//                    || ((OutCheckF & yBitMask(to256)) && (tx == MyKingX)) ){
//                        if(pos->b256[*lpDst] == 0){  //������û������ if(!tree->board.B256[(nSrc+nDst)>>1])
//                            (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,pos->b256[to256]);
//                        } 
//                }
//                lpDst++;
//            }            
//        }//�����쳵�� End
//        //�����쳵��
//        for(int nSrc256 = PieceListStart(pos,BMA); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//            int tmp      = MOVE_FromFC(nSrc256,BMA); 
//            uint8* lpDst = PreMaAndLegMove[nSrc256];
//            while(int to256 = *lpDst++){     //���Ե�����Գ�                                
//                int tx    = StoX(to256);
//                int ty    = StoY(to256);
//                if(   ((OutCheckR & xBitMask(to256)) && (ty == MyKingY)) 
//                    || ((OutCheckF & yBitMask(to256)) && (tx == MyKingX)) ){
//                        if(pos->b256[*lpDst] == 0){  //����û������
//                            (ms++)->move =  MOVE_FromFc_to_tc(tmp,to256,pos->b256[to256]);
//                        } 
//                } 
//                lpDst++;
//            }                                    
//        }  //�����쳵�� End
//        // 2. ���ڽ�쳵��
//        for(int nSrc256 = PieceListStart(pos,BPAO); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//            int tmp      = MOVE_FromFC(nSrc256,BPAO);  
//            int nSrcX = StoX(nSrc256);
//            int nSrcY = StoY(nSrc256);
//            psF  = FileMask(nSrcY,pos->wBitFiles[nSrcX]);
//            psR  = RankMask(nSrcX,pos->wBitRanks[nSrcY]);
//            if(OutCheckF){                  //���·�����Խ⽫
//                if(nSrcX == checkSqX){      //��ͬһ��,ֻ�гԳ���
//                    if(psF->CannonCap & yBitMask(checkSq256)){
//                        (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,RCHE);
//                    }
//                }
//                else{                       //����ͬһ��, �Գ�,����
//                    if(OutCheckF & yBitMask(nSrc256)){  //�ڽ⽫������
//                        if(nSrcY == checkSqY){          //��ͬһ��
//                            if(psR->CannonCap & xBitMask(checkSq256)){                               
//                                (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,RCHE);
//                            }
//                        }
//                        else{
//                            if(psR->RookCap & xBitMask(checkSq256)){  
//                                (ms++)->move =  MOVE_FromFc_to(tmp,XYtoS(checkSqX,nSrcY));  
//                            }
//                        }                                      
//                    }
//                }
//            }
//            else if(OutCheckR){              //���ҷ�����Խ⽫
//                if(nSrcY == checkSqY){       //��ͬһ��,ֻ�гԳ�
//                    if(psR->CannonCap & xBitMask(checkSq256)){
//                        (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,RCHE);
//                    }
//                }
//                else{
//                    if(OutCheckR & xBitMask(nSrc256)){
//                        if(nSrcX == checkSqX){
//                            if(psF->CannonCap & yBitMask(checkSq256)){
//                                (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,RCHE);
//                            }
//                        }
//                        else{
//                            if(psF->RookCap & yBitMask(checkSq256)){  
//                                (ms++)->move =  MOVE_FromFc_to(tmp,XYtoS(nSrcX,checkSqY));  
//                            }
//                        }
//                    }
//                }
//            }           
//        } // End ���ڽ�쳵��
//        //3.�ڳ����쳵��*************************************************************
//        for(int nSrc256 = PieceListStart(pos,BCHE); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//            int tmp      = MOVE_FromFC(nSrc256,BCHE); 
//            int nSrcX = StoX(nSrc256);
//            int nSrcY = StoY(nSrc256);
//            psF  = FileMask(nSrcY,pos->wBitFiles[nSrcX]);
//            psR  = RankMask(nSrcX,pos->wBitRanks[nSrcY]);  
//            if(OutCheckF){                  //���·�����Խ⽫
//                if(nSrcX == checkSqX){      //��ͬһ��,ֻ�гԳ���
//                    if(psF->RookCap & yBitMask(checkSq256)){
//                        (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,RCHE);
//                    }
//                }
//                else{                       //����ͬһ��, �Գ�,����
//                    if(OutCheckF & yBitMask(nSrc256)){  //�ڽ⽫������
//                        if(psR->RookCap & xBitMask(checkSq256)){
//                            int target256 = XYtoS(checkSqX,nSrcY); 
//                            (ms++)->move =  MOVE_FromFc_to_tc(tmp,target256,pos->b256[target256]);
//                        }                                                                  
//                    }
//                }
//            }
//            else if(OutCheckR){              //���ҷ�����Խ⽫
//                if(nSrcY == checkSqY){      //��ͬһ��,ֻ�гԳ�
//                    if(psR->RookCap & xBitMask(checkSq256)){
//                        (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,RCHE);
//                    }
//                }
//                else{
//                    if(OutCheckR & xBitMask(nSrc256)){ //�ڽ⽫��������
//                        if(psF->RookCap & yBitMask(checkSq256)){
//                            int target256 = XYtoS(nSrcX,checkSqY);
//                            (ms++)->move =  MOVE_FromFc_to_tc(tmp,target256,pos->b256[target256]);
//                        }
//                    }
//                }
//            }           
//        } // End �ڳ����쳵��
//    }
//    break;      //End �쳵����
//case MaCheck:         //��ǰ�����ڽ�����, 1, ����, 2, ������
//    if(CheckPieceNum > 1){        
//        if(MaLeg256[0] == MaLeg256[1]){  //ͬʱ���������ڽ�,��ֻ��Maleg��ͬ���ܽ⽫
//            //�鿴�����ܲ��ܽ⽫
//             leg256 = MaLeg256[0];
//             for(int nSrc256 = PieceListStart(pos,BSHI); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//                 int tmp      = MOVE_FromFC(nSrc256,BSHI);
//                 if(inBoard(leg256) & IN_BSHI){
//                     if(GetDir(nSrc256,leg256) & DirShi){
//                         (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//                     }
//                 }                
//             }//���˽���� End
//             for(int nSrc256 = PieceListStart(pos,BXIANG); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//                 int tmp      = MOVE_FromFC(nSrc256,BXIANG); 
//                 if(inBoard(leg256) & IN_BXIANG){
//                     if(GetDir(nSrc256,leg256) & DirXiang){
//                         if(!pos->b256[(nSrc256 + leg256)>>1]){  //������û������ 
//                             (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//                         } 
//                     }
//                 }
//             }//�������� End
//              //��������
//             for(int nSrc256 = PieceListStart(pos,BMA); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//                 int tmp      = MOVE_FromFC(nSrc256,BMA); 
//                 if(GetDir(nSrc256,leg256) & DirMa){
//                     if(!pos->b256[nSrc256 + horseLegTab(leg256 - nSrc256 + 256)]){  //����û������ 
//                         (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//                     } 
//                 }               
//             } //�������� End
//             // 2. ���ڽ����
//             for(int nSrc256 = PieceListStart(pos,BPAO); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//                 int tmp      = MOVE_FromFC(nSrc256,BPAO);  
//                 int nSrcX = StoX(nSrc256);
//                 int nSrcY = StoY(nSrc256);
//                 psF  = FileMask(nSrcY,pos->wBitFiles[nSrcX]);
//                 psR  = RankMask(nSrcX,pos->wBitRanks[nSrcY]);             
//
//                 if(GetDir(nSrc256,leg256) & (DirUp+DirLow)){
//                     if(psF->RookCap & yBitMask(leg256)){ 
//                         (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//                     }
//                 }
//                 else if(GetDir(nSrc256,leg256) & (DirLeft+DirRight)){
//                     if(psR->RookCap & xBitMask(leg256)){
//                         (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//                     }
//                 }    
//             } // End ���ڽ����
//             for(int nSrc256 = PieceListStart(pos,BCHE); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//                 int tmp   = MOVE_FromFC(nSrc256,BCHE);  
//                 int nSrcX = StoX(nSrc256);
//                 int nSrcY = StoY(nSrc256);
//                 psF  = FileMask(nSrcY,pos->wBitFiles[nSrcX]);
//                 psR  = RankMask(nSrcX,pos->wBitRanks[nSrcY]); 
//
//                 if(GetDir(nSrc256,leg256) & (DirUp+DirLow)){
//                     if(psF->RookCap & yBitMask(leg256)){ 
//                         (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//                     }
//                 }
//                 else if(GetDir(nSrc256,leg256) & (DirLeft+DirRight)){
//                     if(psR->RookCap & xBitMask(leg256)){
//                         (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//                     }
//                 }
//             } // End �ڳ������
//        }
//    }
//    else{//����, �������ж��ܲ����ߵ��Ǹ�λ��, ��Ϊ���������γ������İ�����
//        //1,  ���䲻���ܽ���   //2,  ���˽���� 1, ����,����,
//        //Not256Pos[NotNum]       = leg256;
//        leg256 = MaLeg256[0];
//        for(int nSrc256 = PieceListStart(pos,BSHI); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//            int tmp      = MOVE_FromFC(nSrc256,BSHI);
//            if(inBoard(leg256) & IN_BSHI){
//                if(GetDir(nSrc256,leg256) & DirShi){
//                    (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//                }
//            }
//            if(inBoard(checkSq256) & IN_BSHI){
//                if(GetDir(nSrc256,checkSq256) & DirShi){
//                    (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,RMA);
//                }
//            }
//        }//���˽���� End
//        //��������   if(!tree->board.B256[(nSrc256 + to256)>>1])
//        for(int nSrc256 = PieceListStart(pos,BXIANG); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//            int tmp      = MOVE_FromFC(nSrc256,BXIANG); 
//            if(inBoard(leg256) & IN_BXIANG){
//                if(GetDir(nSrc256,leg256) & DirXiang){
//                    if(!pos->b256[(nSrc256 + leg256)>>1]){  //������û������ 
//                        (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//                    } 
//                }
//            }
//            if(inBoard(checkSq256) & IN_BXIANG){
//                if(GetDir(nSrc256,checkSq256) & DirXiang){
//                    if(!pos->b256[(nSrc256 + checkSq256)>>1]){  //������û������ 
//                        (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,RMA);
//                    } 
//                }  
//            }
//        }//�������� End
//        //��������
//        for(int nSrc256 = PieceListStart(pos,BMA); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//            int tmp      = MOVE_FromFC(nSrc256,BMA); 
//            if(GetDir(nSrc256,leg256) & DirMa){
//                if(!pos->b256[nSrc256 + horseLegTab(leg256 - nSrc256 + 256)]){  //����û������ 
//                    (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//                } 
//            }
//            else  if(GetDir(nSrc256,checkSq256) & DirMa){
//                if(!pos->b256[nSrc256 + horseLegTab(checkSq256 - nSrc256 + 256)]){  //����û������ 
//                    (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,RMA);
//                } 
//            }                
//        } //�������� End
//        // 2. ���ڽ����
//        for(int nSrc256 = PieceListStart(pos,BPAO); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//            int tmp      = MOVE_FromFC(nSrc256,BPAO);  
//            int nSrcX = StoX(nSrc256);
//            int nSrcY = StoY(nSrc256);
//            psF  = FileMask(nSrcY,pos->wBitFiles[nSrcX]);
//            psR  = RankMask(nSrcX,pos->wBitRanks[nSrcY]);             
//
//            if(GetDir(nSrc256,leg256) & (DirUp+DirLow)){
//                if(psF->RookCap & yBitMask(leg256)){ 
//                    (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//                }
//            }
//            else if(GetDir(nSrc256,leg256) & (DirLeft+DirRight)){
//                if(psR->RookCap & xBitMask(leg256)){
//                    (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//                }
//            }
//            if(GetDir(nSrc256,checkSq256) & (DirUp+DirLow)){
//                if(psF->CannonCap & yBitMask(checkSq256)){ 
//                    (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,RMA);
//                }
//            }
//            else if(GetDir(nSrc256,checkSq256) & (DirLeft+DirRight)){
//                if(psR->CannonCap & xBitMask(checkSq256)){
//                    (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,RMA);
//                }
//            }
//        } // End ���ڽ����
//        // 2. �ڳ������
//        for(int nSrc256 = PieceListStart(pos,BCHE); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//            int tmp   = MOVE_FromFC(nSrc256,BCHE);  
//            int nSrcX = StoX(nSrc256);
//            int nSrcY = StoY(nSrc256);
//            psF  = FileMask(nSrcY,pos->wBitFiles[nSrcX]);
//            psR  = RankMask(nSrcX,pos->wBitRanks[nSrcY]); 
//
//            if(GetDir(nSrc256,leg256) & (DirUp+DirLow)){
//                if(psF->RookCap & yBitMask(leg256)){ 
//                    (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//                }
//            }
//            else if(GetDir(nSrc256,leg256) & (DirLeft+DirRight)){
//                if(psR->RookCap & xBitMask(leg256)){
//                    (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//                }
//            }
//            if(GetDir(nSrc256,checkSq256) & (DirUp+DirLow)){
//                if(psF->RookCap & yBitMask(checkSq256)){ 
//                    (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,RMA);
//                }
//            }
//            else if(GetDir(nSrc256,checkSq256) & (DirLeft+DirRight)){
//                if(psR->RookCap & xBitMask(checkSq256)){ 
//                    (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,RMA);
//                }
//            }
//        } // End �ڳ������
//    }
//    break;            //End ������
//case PawnCheck:       //��һ������ڽ�, ������ͬʱ���������ڽ�, ֻ�гԱ����⽫
//    //2, ���������, 1, ���䲻���ܽ�����
//    for(int nSrc256 = PieceListStart(pos,BXIANG); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//        int tmp   = MOVE_FromFC(nSrc256,BXIANG);
//        //if(IsCanTo(nSrc256,checkSq256) == DirXiang){    //�����ܳԵ�
//        if(GetDir(nSrc256,checkSq256) & DirXiang){
//            if(!pos->b256[(nSrc256 + checkSq256)>>1]){                                 
//                (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,RPAWN);
//            }
//        }       
//    } // End ���������,
//    //3,��ʿ������
//    if(inBoard(checkSq256) & IN_BSHI){
//        for(int nSrc256 = PieceListStart(pos,BSHI); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//            int tmp   = MOVE_FromFC(nSrc256,BSHI); 
//            if(GetDir(nSrc256,checkSq256) & DirShi){
//                (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,RPAWN);
//            }  
//        }
//    }//��ʿ������ End                
//    //3,���������                
//    for(int nSrc256 = PieceListStart(pos,BMA); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//        int tmp   = MOVE_FromFC(nSrc256,BMA); 
//        if(GetDir(nSrc256,checkSq256) & DirMa){
//            if(!pos->b256[nSrc256 + horseLegTab(checkSq256 - nSrc256 + 256)]){  //����û������                                
//                (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,RPAWN);
//            } 
//        }                  
//    } //���������   End
//    //���ڽ�����                
//    for(int nSrc256 = PieceListStart(pos,BPAO); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//        int tmp   = MOVE_FromFC(nSrc256,BPAO);  
//        int nSrcX = StoX(nSrc256);
//        int nSrcY = StoY(nSrc256);
//        int sr16  = pos->wBitRanks[nSrcY];
//        int sf16  = pos->wBitFiles[nSrcX];
//        psF  = FileMask(nSrcY,pos->wBitFiles[nSrcX]);
//        psR  = RankMask(nSrcX,pos->wBitRanks[nSrcY]);   
//
//        if(GetDir(nSrc256,checkSq256) & (DirUp+DirLow)){
//            if(psF->CannonCap & yBitMask(checkSq256)){ 
//                (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,RPAWN);
//            }
//        }
//        else if(GetDir(nSrc256,checkSq256) & (DirLeft+DirRight)){
//            if(psR->CannonCap & xBitMask(checkSq256)){
//                (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,RPAWN);
//            }
//        }
//    } // End ���ڽ����� 
//    //�ڳ�������                
//    for(int nSrc256 = PieceListStart(pos,BCHE); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//        int tmp   = MOVE_FromFC(nSrc256,BCHE);   
//        int nSrcX = StoX(nSrc256);
//        int nSrcY = StoY(nSrc256);
//        psF  = FileMask(nSrcY,pos->wBitFiles[nSrcX]);
//        psR  = RankMask(nSrcX,pos->wBitRanks[nSrcY]); 
//        if(GetDir(nSrc256,checkSq256) & (DirUp+DirLow)){
//            if(psF->RookCap & yBitMask(checkSq256)){
//                (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,RPAWN);
//            }
//        }
//        else if(GetDir(nSrc256,checkSq256) & (DirLeft+DirRight)){
//            if(psR->RookCap & xBitMask(checkSq256)){  
//                (ms++)->move =  MOVE_FromFc_to_tc(tmp,checkSq256,RPAWN);
//            }
//        }
//    } // End �쳵����佫
//    break;
//case MaCheck | PaoCheck:    //�������˫��,�ɽ⽫
//    paojia256       = PaoJia256[0];
//    //if(NextPiece(pos,paojia256) < 0x33){ //if(board->P48[board->P256[paojia256]] == 0){   //�ڼ��ϵ����Ӳ���������
//    //    break;
//    //}
//    paojiaCan = true;
//    for(int i = 0; i<NotNum; i++){
//        if(paojia256 == Not256Pos[i]){
//            paojiaCan = false;
//            break;
//        }
//    }
//    if(false == paojiaCan){
//        break;
//    }
//    leg256          = MaLeg256[1]; 
//    paohouChess     = PaoHuoChess[0];       //�ڼܺ����������
//    paojiaChess     = PaoJiaChess[0]; 
//    int tmp;
//    int nSrcX;
//    int nSrcY;
//    switch(paojiaChess){
//
//        //�����ж�һ���ڼ��ϵ������ܲ�������
//
//        //case BPAWN:             //������
//        //    Print(4095,"����˫��,���û���⽫,�����⽫");
//        //    DisplayChessBoard(tree->board);
//        //    break;                        
//case BXIANG:            //������ 
//    tmp   = MOVE_FromFC(paojia256,BXIANG); 
//    if(inBoard(leg256) & IN_BXIANG){
//        if(GetDir(paojia256,leg256) & DirXiang){
//            if(!pos->b256[(paojia256 + leg256)>>1]){  //����û������ 
//                (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//            }
//        }
//    }
//    if(inBoard(CheckPos256[1]) & IN_BXIANG){
//        if(GetDir(paojia256,CheckPos256[1]) & DirXiang){
//            if(!pos->b256[(paojia256 + CheckPos256[1])>>1]){  //����û������ 
//                (ms++)->move =  MOVE_FromFc_to_tc(tmp,CheckPos256[1],RMA);
//            }
//        }
//    }
//    break;
//case BSHI:
//    tmp   = MOVE_FromFC(paojia256,BSHI); 
//    if(inBoard(leg256) & IN_BSHI){
//        if(GetDir(paojia256,leg256) & DirShi){
//            (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//        }
//    }
//    if(inBoard(CheckPos256[1]) & IN_BSHI){
//        if(GetDir(paojia256,CheckPos256[1]) & DirShi){
//            (ms++)->move =  MOVE_FromFc_to_tc(tmp,CheckPos256[1],RMA);
//        }
//    }
//    break;
//case BMA:
//    tmp   = MOVE_FromFC(paojia256,BMA); 
//    if(GetDir(paojia256,leg256) & DirMa){
//        if(!pos->b256[paojia256 + horseLegTab(leg256 - paojia256 + 256)]){  //����û������
//            (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//        } 
//    }
//    else if(GetDir(paojia256,CheckPos256[1]) & DirMa){
//        if(!pos->b256[paojia256 + horseLegTab(CheckPos256[1] - paojia256 + 256)]){  //����û������
//            (ms++)->move =  MOVE_FromFc_to_tc(tmp,CheckPos256[1],RMA);
//        } 
//    } 
//    break;
//case BPAO:
//    tmp   = MOVE_FromFC(paojia256,BPAO); 
//    nSrcX = StoX(paojia256);
//    nSrcY = StoY(paojia256);
//    psF  = FileMask(nSrcY,pos->wBitFiles[nSrcX]);
//    psR  = RankMask(nSrcX,pos->wBitRanks[nSrcY]);       //�ܲ����ߵ�����
//    if(GetDir(paojia256,leg256) & (DirUp+DirLow)){
//        if(psF->RookCap & yBitMask(leg256)){ 
//            (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//        }
//    }
//    else if(GetDir(paojia256,leg256) & (DirLeft+DirRight)){
//        if(psR->RookCap & xBitMask(leg256)){
//            (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//        }
//    }
//    if(GetDir(paojia256,CheckPos256[1]) & (DirUp+DirLow)){
//        if(psF->CannonCap & yBitMask(CheckPos256[1])){ 
//            (ms++)->move =  MOVE_FromFc_to_tc(tmp,CheckPos256[1],RMA);
//        }
//    }
//    else if(GetDir(paojia256,CheckPos256[1]) & (DirRight+DirLeft)){
//        if(psR->CannonCap & xBitMask(CheckPos256[1])){ 
//            (ms++)->move =  MOVE_FromFc_to_tc(tmp,CheckPos256[1],RMA);
//        }
//    }
//    break;
//case BCHE:
//    tmp      = MOVE_FromFC(paojia256,BCHE);
//    nSrcX = StoX(paojia256);
//    nSrcY = StoY(paojia256);
//    psF  = FileMask(nSrcY,pos->wBitFiles[nSrcX]);
//    psR  = RankMask(nSrcX,pos->wBitRanks[nSrcY]); 
//
//    if(GetDir(paojia256,leg256) & (DirUp+DirLow)){
//        if(psF->RookCap & yBitMask(leg256)){ 
//            (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//        }
//    }
//    else if(GetDir(paojia256,leg256) & (DirLeft+DirRight)){
//        if(psR->RookCap & xBitMask(leg256)){
//            (ms++)->move =  MOVE_FromFc_to(tmp,leg256);
//        }
//    }
//    if(GetDir(paojia256,CheckPos256[1]) & (DirUp+DirLow)){
//        if(psF->RookCap & yBitMask(CheckPos256[1])){ 
//            (ms++)->move =  MOVE_FromFc_to_tc(tmp,CheckPos256[1],RMA);
//        }
//    }
//    else if(GetDir(paojia256,CheckPos256[1]) & (DirRight+DirLeft)){
//        if(psR->RookCap & xBitMask(CheckPos256[1])){
//            (ms++)->move =  MOVE_FromFc_to_tc(tmp,CheckPos256[1],RMA);
//        }
//    }
//    break;
//default:
//    break;
//    }
//    break;
//case CheCheck | PaoCheck:   //����˫��, ��Щ����ɽ⽫, �������һֱ��,���ɽ⽫
//    if(CheckPieceNum > 2){  //���������ڽ�,���ܽ⽫
//        break;
//    }
//    tCheckDir1 = GetDir(CheckPos256[1],CheckPos256[0]);
//    if(!(tCheckDir1 & DirChe)){               
//        /* Print(4095,"�췽����˫��,�Ҳ���һֱ��, û���⽫,ֻ�ж����⽫");
//        DisplayChessBoard(tree->board); */
//        break;
//    } 
//    if(tCheckDir1 & DirUp){
//        OutCheckF  = UpMask(MyKing256) & LoMask(K256Up1);
//    }
//    else if(tCheckDir1 & DirLow){
//        OutCheckF  = LoMask(MyKing256) & UpMask(K256Lo1); 
//    }
//    else if(tCheckDir1 & DirLeft){
//        OutCheckR  = LeftMask(MyKing256) &  RightMask(K256Left1);
//    }
//    else if(tCheckDir1 & DirRight){
//        OutCheckR =  RightMask(MyKing256) & LeftMask(K256Right1);
//    }
//    //1.����⳵�ڽ�*************************************************************
//    //if(CheckDir1 == DirLow){                             //����ֻ�ܽ�����ĳ��ڽ�   
//    if(tCheckDir1 & DirLow){
//        for(int nSrc256 = PieceListStart(pos,BPAWN); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//            int tmp   = MOVE_FromFC(nSrc256,BPAWN); 
//            if(nSrc256 < 0x7b){
//                continue;
//            }
//            //�����ڼ��ϵ���ֻ�����ҽ⽫��
//            int to256 = nSrc256+1;
//            int tx    = StoX(to256);
//            if(tx == MyKingX){
//                if(yBitMask(to256) & OutCheckF){
//                    (ms++)->move =  MOVE_FromFc_to(tmp,to256);
//                }
//            }
//            to256 = nSrc256-1;
//            tx    = StoX(to256);
//            if(tx == MyKingX){
//                if(yBitMask(to256) & OutCheckF){
//                    (ms++)->move =  MOVE_FromFc_to(tmp,to256);
//                }
//            }
//        }       
//    }// End ����⳵�ڽ�
//    //���˽⳵�ڽ�
//    for(int nSrc256 = PieceListStart(pos,BSHI); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//        int tmp      = MOVE_FromFC(nSrc256,BSHI);  
//        uint8* lpDst = PreShiXiangAndEyeMove[nSrc256];
//        while(int to256 = *lpDst++){                             
//            int tx    = StoX(to256);
//            int ty    = StoY(to256);
//            if(   ((OutCheckR & xBitMask(to256)) && (ty == MyKingY)) 
//                || ((OutCheckF & yBitMask(to256)) && (tx == MyKingX)) ){  
//                    (ms++)->move =  MOVE_FromFc_to(tmp,to256);
//            }
//        }        
//    }//���˽⳵�ڽ� End
//    //����⳵�ڽ�
//    for(int nSrc256 = PieceListStart(pos,BXIANG); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//        int tmp      = MOVE_FromFC(nSrc256,BXIANG); 
//        uint8* lpDst = PreShiXiangAndEyeMove[nSrc256];
//        while(int to256 = *lpDst++){                            
//            int tx    = StoX(to256);
//            int ty    = StoY(to256);
//            if(   ((OutCheckR & xBitMask(to256)) && (ty == MyKingY)) 
//                || ((OutCheckF & yBitMask(to256)) && (tx == MyKingX)) ){
//                    if(!pos->b256[*lpDst]){  //������û������ if(!tree->board.B256[(nSrc+nDst)>>1])
//                        (ms++)->move =  MOVE_FromFc_to(tmp,to256);
//                    }
//            }
//            lpDst++;
//        }       
//    }//����⳵�ڽ� End
//    //����⳵�ڽ�
//    for(int nSrc256 = PieceListStart(pos,BMA); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//        int tmp      = MOVE_FromFC(nSrc256,BMA); 
//        uint8* lpDst = PreMaAndLegMove[nSrc256];
//        while(int to256 = *lpDst++){     //���Ե��ڻ����                            
//            int tx    = StoX(to256);
//            int ty    = StoY(to256);
//            if(   ((OutCheckR & xBitMask(to256)) && (ty == MyKingY)) 
//                || ((OutCheckF & yBitMask(to256)) && (tx == MyKingX)) ){
//                    if(!pos->b256[*lpDst]){  //����û������
//                        (ms++)->move =  MOVE_FromFc_to(tmp,to256);
//                    } 
//            }
//            lpDst++;
//        }                               
//    } ////����⳵�ڽ� End
//    // 2. ���ڽ�쳵�ڽ�
//    for(int nSrc256 = PieceListStart(pos,BPAO); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//        int tmp   = MOVE_FromFC(nSrc256,BPAO);  
//        int nSrcX = StoX(nSrc256);
//        int nSrcY = StoY(nSrc256);
//        psF  = FileMask(nSrcY,pos->wBitFiles[nSrcX]);
//        psR  = RankMask(nSrcX,pos->wBitRanks[nSrcY]); 
//
//        if(OutCheckF){                  //���·�����Խ⽫
//            if(nSrcX != checkSqX){      //����ͬһ��,                                                    
//                if(OutCheckF & yBitMask(nSrc256)){  //�ڽ⽫������
//                    if(nSrcY != checkSqY){          //����ͬһ��                                           
//                        if(psR->RookCap & xBitMask(checkSq256)){    //����
//                            (ms++)->move =  MOVE_FromFc_to(tmp,XYtoS(checkSqX,nSrcY)); 
//                        }
//                    }                                      
//                }
//            }
//        }
//        else if(OutCheckR){              //���ҷ�����Խ⽫
//            if(nSrcY != checkSqY){                                       
//                if(OutCheckR & xBitMask(nSrc256)){
//                    if(nSrcX != checkSqX){                                          
//                        if(psF->RookCap & yBitMask(checkSq256)){
//                            (ms++)->move =  MOVE_FromFc_to(tmp,XYtoS(nSrcX,checkSqY)); 
//                        }
//                    }
//                }
//            }
//        }        
//    } // End // 2. �ڳ���쳵�ڽ�
//
//    for(int nSrc256 = PieceListStart(pos,BCHE); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//        int tmp   = MOVE_FromFC(nSrc256,BCHE);  
//        int nSrcX = StoX(nSrc256);
//        int nSrcY = StoY(nSrc256);
//        psF  = FileMask(nSrcY,pos->wBitFiles[nSrcX]);
//        psR  = RankMask(nSrcX,pos->wBitRanks[nSrcY]); 
//
//        if(OutCheckF){                  //���·�����Խ⽫
//            if(nSrcX != checkSqX){      //����ͬһ��,                                                    
//                if(OutCheckF & yBitMask(nSrc256)){  //�ڽ⽫������
//                    if(nSrcY != checkSqY){          //����ͬһ��                                           
//                        if(psR->RookCap & xBitMask(checkSq256)){    //����
//                            (ms++)->move =  MOVE_FromFc_to(tmp,XYtoS(checkSqX,nSrcY)); 
//                        }
//                    }                                      
//                }
//            }
//        }
//        else if(OutCheckR){              //���ҷ�����Խ⽫
//            if(nSrcY != checkSqY){       //����ͬһ��,                                   
//                if(OutCheckR & xBitMask(nSrc256)){
//                    if(nSrcX != checkSqX){ 
//                        if(psF->RookCap & yBitMask(checkSq256)){   //����
//                            (ms++)->move =  MOVE_FromFc_to(tmp,XYtoS(nSrcX,checkSqY)); 
//                        }
//                    }
//                }
//            }
//        }       
//    } // End // 2. ���ڽ�쳵�ڽ� �ڳ��ɼ���һ����,
//
//    break;
//case CheCheck | PawnCheck:  //����˫��, �����������ܽ⽫��
//    /* Print(4095,"����˫��,û���⽫,ֻ�ж����⽫");
//    DisplayChessBoard(tree->board);*/
//    break;
//case PaoCheck | PawnCheck:
//    /*Print(4095,"�ڱ�˫��,û���⽫,ֻ�ж����⽫");
//    DisplayChessBoard(tree->board);*/
//    break;
//case MaCheck | PawnCheck:   //���˫��,���ɽ⽫
//    //*DisplayChessBoard(tree->board);
//    //Print(4095,"���˫��,û���⽫");
//    break;            
//case CheCheck | MaCheck:    //����˫��,���ɽ⽫
//    /*DisplayChessBoard(tree->board);
//    Print(4095,"����˫��,û���⽫");*/
//    break;            
//default:        //�������,�����ܳ�����
//    /*Print(4095,"��������Ľ���,��һ����û�취�⽫�ۣ���, ��ô����.....");  
//    DisplayChessBoard(tree->board);*/
//    break;
//        }
//        // ��󶯽����⽫��             
//        uint8* lpDst = PreKingMove[MyKing256];
//        int ktmp    = MOVE_FromFC(MyKing256,BKING); 
//        while(int to256 = *lpDst++){              
//            int to14        = pos->b256[to256];
//            int tx          = StoX(to256);
//            int ty          = StoY(to256);
//            int ky4         = to256 & 0xf0;
//            //int KingDir = IsCanTo(MyKing256,to256);
//            int tKingDir  = GetDir(MyKing256,to256);
//            if(!IsBlack(to14)){       //���Ǻ���
//                if(tKingDir == tCheckDir1 && (CheckType & (CheCheck + PaoCheck))){
//                    continue;
//                }//������ߵķ����뽫���ķ�����ͬ,�ҽ��������Ӳ��Ǳ�����ô�Ͳ����ܽ⽫
//                //���ж�һ���߽���᲻�ỹ�Ǳ���              
//
//                int kToF  = pos->wBitFiles[StoX(to256)] ^ yBitMask(MyKing256);     //���Ӧ���ǶԵ���
//                int kToR  = pos->wBitRanks[StoY(to256)] ^ xBitMask(MyKing256);
//
//                //��to�ĵ����µ���Ϣ
//                psmv = FileMove(ty,kToF); 
//                //�õ����ڽ��ϵĵ�һ������ tmp = kf & UpMask(nMyKing);
//                int tmp = psmv->RookCap[DUpLeft] + tx;
//                if(tmp != to256){
//                    checkChess = pos->b256[tmp];
//                    if(checkChess == RCHE ){
//                        continue;                        
//                    }
//                    //���˵�һ���ſ����еڶ���
//                    tmp = psmv->CannonCap[DUpLeft] + tx;
//                    if(tmp != to256){
//                        if(pos->b256[tmp] == RPAO){
//                            continue;
//                        }
//                    }
//                } 
//                //�õ�������ĵ�һ������
//                tmp = psmv->RookCap[DLoRight] + tx;
//                if(tmp != to256){
//                    checkChess = pos->b256[tmp];
//                    if( (checkChess == RCHE)
//                        || checkChess == RKING 
//                        || (checkChess == RPAWN && (tmp-16) == to256)){            //???????????????{
//                            continue;
//                    }
//                    //���˵�һ���ſ����еڶ���
//                    tmp = psmv->CannonCap[DLoRight] + tx;
//                    if(tmp != to256){
//                        if(pos->b256[tmp] == RPAO){
//                            continue;
//                        }
//                    }
//                } 
//                //�õ�����������ĵ�һ������
//                psmv = RankMove(tx,kToR);
//                tmp  = psmv->RookCap[DUpLeft] + ky4;
//                if(tmp != to256){
//                    checkChess = pos->b256[tmp];
//                    if((checkChess == RCHE)
//                        || (checkChess == RPAWN && tmp+1 == to256)){
//                            continue;
//                    }
//                    //���˵�һ���ſ����еڶ���
//                    tmp = psmv->CannonCap[DUpLeft] + ky4;
//                    if(tmp != to256){
//                        if(pos->b256[tmp] == RPAO){
//                            continue;
//                        }
//                    }
//                }
//                //�õ�����������ĵ�һ������
//                psmv = RankMove(tx,kToR);
//                tmp  = psmv->RookCap[DLoRight] + ky4;
//                if(tmp != to256){
//                    checkChess = pos->b256[tmp];
//                    if((checkChess == RCHE)
//                        || (checkChess == RPAWN && tmp-1 == to256)){
//                            continue;
//                    }
//                    //���˵�һ���ſ����еڶ���
//                    tmp = psmv->CannonCap[DLoRight] + ky4;
//                    if(tmp != to256){
//                        if(pos->b256[tmp] == RPAO){
//                            continue;
//                        }
//                    }
//                }
//                //���ÿ�һ����û��������
//                bool isMaCheck = false;
//                for(int nSrc256 = PieceListStart(pos,RMA); nSrc256 > 0x32; nSrc256 = NextPiece(pos,nSrc256)){
//                    int m = horseLegTab(to256-nSrc256+256);
//                    if(m && !pos->b256[nSrc256 + m]){
//                        //continue;       //����������,���ܼ����߲�
//                        isMaCheck = true;
//                        break;
//                    }
//                }
//                if(false == isMaCheck){
//                    (ms++)->move =  MOVE_FromFc_to_tc(ktmp,to256,to14);
//                }
//            }
//        }
//    }
//    //************************************************************************************************************************
//    //RES_EV:  
//    for(int i=0; i<NotNum; i++){
//        int sq = Not256Pos[i];
//        InsertPiece(pos,pos->b256[sq], sq);
//    }
//
//#ifdef  DEBUG_EVASION_MOVE
//    move_stack_t testMS[256];
//    //ASSERT(position_is_ok(pos));
//    //position fen 1rbakabnr/9/1c7/C1p1p1p1p/9/6P2/P1P1c3P/9/9/RNBAKABNR b - - 7 0
//    int check = false;
//    //int evnum  = 0;
//    int allnum = 0;
//    ////1, �⽫�Ĳ���������ȷ prePS
//    //for(move_stack_t *tms = prePS; tms < ms; tms++){
//    //    //make_move(pos,tms->move);
//    //    //check = isTurnInCheck(pos,pos->side^0x1);
//    //    //unmake_move(pos);
//
//    //    //if(check){
//    //    //    board_display(pos,"ERROR �⽫������??",stdout);
//    //    //    generate_check_evasions(pos,testMS);
//    //    //}
//    //    evnum++;
//    //}  
//
//    //�߲�����Ŀ�ǲ��Ƕ�
//    //ASSERT(position_is_ok(pos));
//
//    move_stack_t *allEnd = generate_moves(pos,testMS);
//
//    for(move_stack_t *st = testMS; st < allEnd; st++){
//        check = false;
//        make_move(pos,st->move);
//        check = isTurnInCheck(pos,pos->side^0x1);
//        unmake_move(pos);
//        if(false == check){         //����һ���⽫��
//            allnum++;
//
//            bool isInEva = false;
//            for(move_stack_t *tms = prePS; tms < ms; tms++){
//                if(tms->move == st->move){
//                    isInEva = true;
//                    break;
//                }
//            }
//
//            if(!isInEva){
//                board_display(pos,"isInEva err\n",stdout);
//                generate_check_evasions(pos,prePS);
//            }
//
//            ASSERT(isInEva);
//        }        
//    }
//
//    ASSERT((int)(ms-prePS) == allnum);
//
//#endif
//
//    ASSERT(position_is_ok(pos));
//
//    return ms;
//}
//
