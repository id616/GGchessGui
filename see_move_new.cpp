#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"

////goto nextStep ʱ��Ҫ��һ���ǲ����Ǹ���������
////ͨ��SEE���ж���׽  
//
///*
//BOOL see_draw_new(position_t *pos,int mfrom,int mto, int from, int to, int which){
//
//    //return 0;
//
//    //int num_of_attackers[2];
//    //int swaplist[32];
//    //int attackers[2][16];
//    //int piece;
//    //int capture;
//    //int side;
//    //int piece_val;
//    //int val;
//    //int n;
//
//	int tochess = pos->b256[to];  //�õ�tochess;
//
//	//BOOL Ispao    = FALSE;          //���ܳԵ�
//	//int  paoToSq  = 0;
//
//	//if(tochess == EMPTY){
//	//	return FALSE;
//	//}
//
//	int side;
//
//	if(IsWhite(tochess)){
//		side = BLACK;			//�õ��Ǹ���SEE
//	}
//	else {
//		side = WHITE;
//	}
//
//	//��һ�����õ��ɳ�to�����ӣ���Ҫ�����ӷ���
//
//    register int tmp;
//
//    // Find attackers for both sides.  The capturing piece is not added 
//    // to the attack list.  Instead, we scan for X-ray attacks behind the
//    // capturing piece.
//
//    int tox = StoX(to);
//    int toy = StoY(to);
//
//    int tof = pos->wBitFiles[tox];
//    int tor = pos->wBitRanks[toy];     
//
//    int nDisp = to & 0xf0;
//
//    //num_of_attackers[WHITE] = num_of_attackers[BLACK] = 0;
//
//	//int whiteAttacker = 0;
//	//int blackAttacker = 0; 
//
//	int attacker = 0;
//    SlideMoveStruct *psmv;
//
//	int moveChessId = PIECE_ID(pos->b256[mto]);
//
//    //��to�ĵ����µ���Ϣ
//
//
//	int NotList[16];
//	int NotBoard[16];               //�����ϵ�����Ҳ��ȥ����
//    int NotNum          =0;         //�������ߵ����ӵ����� 
//
//	//**************************************************************************
//	// �õ������ߵ�����
//	//**************************************************************************
//
//	if(side == BLACK){
//
//		//////////////////////////////////////////////////////////////////////////////
//		// ���ڷ���������ȥ��
//		int king  = PieceListStart(pos,BKING);
//	    int kx    = StoX(king);
//		int ky    = StoY(king);
//		int ky4   = king & 0xf0;
//
//		int sq1;
//		int sq2;
//		int sq3;
//
//		psmv = FileMove(ky,pos->wBitFiles[kx]);
//
//		//�õ�����������Ϣ
//		sq2 = psmv->CannonCap[DUpLeft] + kx;
//	
//		if(sq2 != king){
//			if(pos->b256[sq2] == RCHE){
//				sq1 = psmv->RookCap[DUpLeft] + kx;
//
//				if(IsBlack(pos->b256[sq1])){
//					//Not256Pos[NotNum] = sq1;
//
//					//------------------------------------
//					NotList[NotNum]  = sq1;
//					NotBoard[NotNum] = pos->b256[sq1];  //����һ������
//					pos->b256[sq1]   = EMPTY;
//                    //-------------------------------------
//					RemovePiece(pos,sq1);
//					NotNum++;
//				}				
//			}
//		}
//        ///////////////////////////////////////////////////////////////////
//		//�õ��������һ������
//		sq1 = psmv->RookCap[DLoRight] + kx;
//		
//		if(sq1 != king){
//			
//			sq2 = psmv->CannonCap[DLoRight] + kx;
//
//			if(sq2 != king){
//
//				int chess1 = pos->b256[sq1];
//				int chess2 = pos->b256[sq2];
//
//				if(chess2 == RCHE || chess2 == RKING){
//					if(IsBlack(chess1)){
//						//Not256Pos[NotNum] = sq1;
//
//						//------------------------------------
//						NotList[NotNum]  = sq1;
//						NotBoard[NotNum] = pos->b256[sq1];  //����һ������
//						pos->b256[sq1]   = EMPTY;
//						//-------------------------------------
//
//						RemovePiece(pos,sq1);
//						NotNum++;
//					}
//				}
//
//				sq3 = psmv->SuperCap[DLoRight] + kx;
//				if(sq3 != king){
//					int chess3 = pos->b256[sq3];
//					if(chess3 == RPAO && sq3 != to){  //if(chess3 == RPAO){
//						if(IsBlack(chess2)){   //��������ж�һ��ToChess �ǲ�����
//							//if(tochess
//							//Not256Pos[NotNum] = sq2;
//
//							//------------------------------------
//							NotList[NotNum]  = sq2;
//							NotBoard[NotNum] = pos->b256[sq2];  //����һ������
//							pos->b256[sq2]   = EMPTY;
//							//-------------------------------------
//
//							RemovePiece(pos,sq2);
//							NotNum++;
//						}
//						if(IsBlack(chess1) && chess2 != RCHE && chess2 != RKING){
//							//Not256Pos[NotNum] = sq1;
//							
//							//------------------------------------
//							NotList[NotNum]  = sq1;
//							NotBoard[NotNum] = pos->b256[sq1];  //����һ������
//							pos->b256[sq1]   = EMPTY;
//							//-------------------------------------
//
//							RemovePiece(pos,sq1);
//							NotNum++;
//						}
//					}
//				}
//			}
//		}
//
//		//�����ж�һ��
//		psmv = RankMove(kx,pos->wBitRanks[ky]);
//
//		sq1 = psmv->RookCap[DUpLeft] + ky4;
//		if(sq1 != king){
//			
//			sq2 = psmv->CannonCap[DUpLeft] + ky4;
//
//			if(sq2 != king){
//				int chess1 = pos->b256[sq1];
//				int chess2 = pos->b256[sq2];
//				
//				if(chess2 == RCHE){
//					if(IsBlack(chess1)){
//						//Not256Pos[NotNum] = sq1;
//						//------------------------------------
//						NotList[NotNum]  = sq1;
//						NotBoard[NotNum] = pos->b256[sq1];  //����һ������
//						pos->b256[sq1]   = EMPTY;
//						//-------------------------------------
//						RemovePiece(pos,sq1);
//						NotNum++;
//					}
//				}
//
//				sq3 = psmv->SuperCap[DUpLeft] + ky4;
//				if(sq3 != king){
//					int chess3 = pos->b256[sq3];
//					//if(chess3 == RPAO){
//					if(chess3 == RPAO && sq3 != to){  //if(chess3 == RPAO){
//						if(IsBlack(chess2)){
//							//Not256Pos[NotNum] = sq2;
//							//------------------------------------
//							NotList[NotNum]  = sq2;
//							NotBoard[NotNum] = pos->b256[sq2];  //����һ������
//							pos->b256[sq2]   = EMPTY;
//							//-------------------------------------
//							RemovePiece(pos,sq2);
//							NotNum++;
//						}
//						if(IsBlack(chess1) && chess2 != RCHE ){
//							//Not256Pos[NotNum] = sq1;
//							//------------------------------------
//							NotList[NotNum]  = sq1;
//							NotBoard[NotNum] = pos->b256[sq1];  //����һ������
//							pos->b256[sq1]   = EMPTY;
//							//-------------------------------------
//							RemovePiece(pos,sq1);
//							NotNum++;
//						}
//					}
//				}
//			}		
//		}
//
//		//�����ж�һ��
//
//		psmv = RankMove(kx,pos->wBitRanks[ky]);
//
//		sq1 = psmv->RookCap[DLoRight] + ky4;
//		if(sq1 != king){
//			
//			sq2 = psmv->CannonCap[DLoRight] + ky4;
//
//			if(sq2 != king){
//				int chess1 = pos->b256[sq1];
//				int chess2 = pos->b256[sq2];
//				
//				if(chess2 == RCHE){
//					if(IsBlack(chess1)){
//						//Not256Pos[NotNum] = sq1;
//						//------------------------------------
//						NotList[NotNum]  = sq1;
//						NotBoard[NotNum] = pos->b256[sq1];  //����һ������
//						pos->b256[sq1]   = EMPTY;
//						//-------------------------------------
//						RemovePiece(pos,sq1);
//						NotNum++;
//					}
//				}
//
//				sq3 = psmv->SuperCap[DLoRight] + ky4;
//				if(sq3 != king){
//					int chess3 = pos->b256[sq3];
//					//if(chess3 == RPAO){
//					if(chess3 == RPAO && sq3 != to){  //if(chess3 == RPAO){
//						if(IsBlack(chess2)){
//							//Not256Pos[NotNum] = sq2;
//							//------------------------------------
//							NotList[NotNum]  = sq2;
//							NotBoard[NotNum] = pos->b256[sq2];  //����һ������
//							pos->b256[sq2]   = EMPTY;
//							//-------------------------------------
//							RemovePiece(pos,sq2);
//							NotNum++;
//						}
//						if(IsBlack(chess1) && chess2 != RCHE ){
//							//Not256Pos[NotNum] = sq1;
//							//------------------------------------
//							NotList[NotNum]  = sq1;
//							NotBoard[NotNum] = pos->b256[sq1];  //����һ������
//							pos->b256[sq1]   = EMPTY;
//							//-------------------------------------
//							RemovePiece(pos,sq1);
//							NotNum++;
//						}
//					}
//				}
//			}		
//		}
//
//		//*********************************************************
//		//�ٿ�һ����
//		 //�ж�һ����û�����ڽ�����
//        for(int checkSq256 = PieceListStart(pos,RMA); checkSq256 > 0x32; checkSq256 = NextPiece(pos,checkSq256)){
//
//			//���ÿ�һ���ߵ��ǲ����Ǹ���, �������,�Ͳ�Ҫ�ж�
//
//			if(checkSq256 != to){
//
//				int x   = horseLegTab(king - checkSq256 + 256);
//				int leg256 = checkSq256 + x;
//
//				if(x){
//					int leg14 = pos->b256[leg256];
//
//					if(IsBlack(leg14)){
//						//���ж�һ��,�ǲ����Ѿ�������
//						BOOL isRemove = FALSE;
//						for(int i = 0; i < NotNum; i++){
//							if(leg256 == NotList[i]){
//								isRemove = TRUE;
//								break;
//							}
//						}
//						//Not48Pos[NotNum]        = leg48;
//						if(isRemove == FALSE){
//							//Not256Pos[NotNum]       = leg256;
//
//							//------------------------------------
//							NotList[NotNum]  = leg256;
//							NotBoard[NotNum] = pos->b256[leg256];  //����һ������
//							pos->b256[leg256]   = EMPTY;
//							//-------------------------------------
//
//							RemovePiece(pos, leg256);
//							NotNum++;
//						}
//					}
//				}
//			}
//		}
//		//**********************************************************
//
//        // ���ڷ���������ȥ�� End
//		///////////////////////////////////////////////////////////////////////////////////////////////////////
//		//---------------------------------------------------------------------------------------------------------------------
//		//�õ��ߵ����� int moveChessId = PIECE_ID(pos->b256[mto]);
//		//�Է��ߵ���� int tochess = pos->b256[to];  //�õ�tochess;
//
//		switch(moveChessId){
//			case PAWN:        //��ʵ����
//				{
//					if(to == mto + 16 || (to > 0x80 && (to == mto -1 || to == mto + 1))){
//						attacker = mto;
//						goto NextStep;
//					}
//				}
//				break;
//			case KING:
//				{
//					if((GetDir(mto,to) & DirKing) != 0){
//						attacker = mto;
//						goto NextStep;
//					}
//				}
//				break;
//			case SHI:
//				{
//					if((GetDir(mto,to) & DirShi) != 0){
//						attacker = mto;
//						goto NextStep;
//					}
//				}
//				break;
//			case XIANG:
//				{
//					if((GetDir(mto,to) & DirXiang) != 0 && pos->b256[(mto+to)/2] == 0){
//						attacker = mto;
//						goto NextStep;
//					}
//				}
//				break;
//			case MA:{
//					int t = horseLegTab(to - mto + 256);
//					if(t != 0 && pos->b256[mto + t] == EMPTY){
//						attacker = mto;
//						goto NextStep;
//					}
//					 }
//				break;
//			case PAO: //��һ�����ܲ��ܳ�
//				{
//					//int tox = StoX(to);
//					//int toy = StoY(to);
//
//					//int tof = pos->wBitFiles[tox];
//					//int tor = pos->wBitRanks[toy];  
//					if(false){
//					}
//					else if(StoX(mto) == StoX(to)){
//						if((FileMask(StoY(mto),tof)->CannonCap & yBitMask(to)) != 0){
//							attacker = mto;
//							goto NextStep;
//						}
//					}
//					else if(StoY(mto) == StoY(to)){
//						if((RankMask(StoX(mto),tor)->CannonCap & xBitMask(to)) != 0){
//							attacker = mto;
//							goto NextStep;
//						}
//					}
//				}
//				break;
//			case CHE:{
//					if(false){
//					}
//					else if(StoX(mto) == StoX(to)){
//						if((FileMask(StoY(mto),tof)->RookCap & yBitMask(to)) != 0){
//							attacker = mto;
//							goto NextStep;
//						}
//					}
//					else if(StoY(mto) == StoY(to)){
//						if((RankMask(StoX(mto),tor)->RookCap & xBitMask(to)) != 0){
//							attacker = mto;
//							goto NextStep;
//						}
//					}
//					  }
//				break;
//			default:
//				break;
//		}
//
//		 //#####################################################################
//		// �ٿ�һ���ǲ����ÿ�������
//		for(int at = PieceListStart(pos,BXIANG); at > 0x32; at = NextPiece(pos,at)){
//			if(at != mto){		//�ߵĲ����Ǹ���	
//				//��һ��at�ܲ��ܳԵ�to
//				if((GetDir(at,to) & DirXiang) != 0){
//					if(mfrom == (at+to) /2 ){
//						attacker			= at;
//						//to                  = sq2;
//						//tox = StoX(to);
//						//toy = StoY(to);
//						//tof = pos->wBitFiles[tox];
//						//tor = pos->wBitRanks[toy];  
//						//nDisp = to & 0xf0;
//						goto NextStep;
//					}
//				}
//			}
//		}
//
//		//#####################################################################
//
//		// �ٿ�һ���ǲ����ÿ�������
//		for(int at = PieceListStart(pos,BMA); at > 0x32; at = NextPiece(pos,at)){
//			if(at != mto){		//�ߵĲ����Ǹ���
//
//				int t = horseLegTab(to - at + 256);
//				if(t != 0){
//
//					if(mfrom == at + t){
//						attacker			= at;
//						//to                  = sq2;
//						//tox = StoX(to);
//						//toy = StoY(to);
//						//tof = pos->wBitFiles[tox];
//						//tor = pos->wBitRanks[toy];  
//						//nDisp = to & 0xf0;
//						goto NextStep;
//					}
//				}
//			}
//		}
//
//		//#####################################################################
//
//		
//
//		//========================================
//
//		//#####################################################################
//
//		//��һ���ǲ����ÿ��˳���׽
//
//		for(int at = PieceListStart(pos,BCHE); at > 0x32; at = NextPiece(pos,at)){
//			if(at != mto){		//�ߵĲ����Ǹ���							
//				//1,**************************************************
//				if(StoX(mfrom) == StoX(at)){			//���ڵ�File���뿪
//					if(StoX(mto) != StoX(at)){					
//						//��һ���ڵ�������Ϣ
//						psmv = FileMove(StoY(at),pos->wBitFiles[StoX(at)]);
//
//						if(StoY(mfrom) > StoY(at)){		//���ڵ�����
//							sq2 = psmv->RookCap[DLoRight] + StoX(at);
//
//							//sq2 = psmv->RookCap
//							if(IsWhite(pos->b256[sq2]) && StoY(mfrom) < StoY(sq2) ){   //�ߵ�����sq2 �� at ���м�
//								//paoTo				= TRUE;
//								attacker			= at;
//
//								to                  = sq2;
//								tox = StoX(to);
//								toy = StoY(to);
//								tof = pos->wBitFiles[tox];
//								tor = pos->wBitRanks[toy]; 
//								nDisp = to & 0xf0;
//								goto NextStep;
//							}
//						}
//						else{
//							sq2 = psmv->RookCap[DUpLeft] + StoX(at);
//							if(IsWhite(pos->b256[sq2]) && StoY(mfrom) > StoY(sq2) ){
//								//paoTo				= TRUE;								
//								attacker			= at;
//
//								attacker			= at;
//								to                  = sq2;
//								tox = StoX(to);
//								toy = StoY(to);
//								tof = pos->wBitFiles[tox];
//								tor = pos->wBitRanks[toy];  
//								nDisp = to & 0xf0;
//								goto NextStep;
//							}
//						}
//					}										
//				}
//				//2,**************************************************
//				if(StoX(mto) == StoX(at)){			//�ߵ�����File��
//					if(StoX(mfrom) != StoX(at)){					
//						//��һ�³���������Ϣ
//						psmv = FileMove(StoY(at),pos->wBitFiles[StoX(at)]);
//
//						if(StoY(mto) > StoY(at)){		//�ڳ�������
//							sq2 = psmv->RookCap[DLoRight] + StoX(at);
//							if(IsWhite(pos->b256[sq2]) && StoY(mto) < StoY(sq2) ){
//								//paoTo				= TRUE;
//								attacker			= at;
//
//								to                  = sq2;
//								tox = StoX(to);
//								toy = StoY(to);
//								tof = pos->wBitFiles[tox];
//								tor = pos->wBitRanks[toy]; 
//								nDisp = to & 0xf0;
//								goto NextStep;
//							}
//						}
//						else{
//							sq2 = psmv->RookCap[DUpLeft] + StoX(at);
//							if(IsWhite(pos->b256[sq2]) && StoY(mto) > StoY(sq2) ){
//
//								attacker			= at;
//								to                  = sq2;
//								tox = StoX(to);
//								toy = StoY(to);
//								tof = pos->wBitFiles[tox];
//								tor = pos->wBitRanks[toy]; 
//								nDisp = to & 0xf0;
//								goto NextStep;
//							}
//						}
//					}
//										
//				}
//				//3,**************************************************
//				if(StoY(mfrom) == StoY(at)){			//�ӳ���Rank���뿪
//					if(StoY(mto) != StoY(at)){
//						//��һ�³���������Ϣ
//						psmv = RankMove(StoX(at),pos->wBitRanks[StoY(at)]);
//
//						if(StoX(mfrom) > StoX(at)){
//							sq2 = psmv->RookCap[DLoRight] + (at & 0xf0);
//							if(IsWhite(pos->b256[sq2]) && StoX(mfrom) < StoX(sq2) ){
//								//paoTo				= TRUE;								
//
//								attacker			= at;
//								to                  = sq2;
//								tox = StoX(to);
//								toy = StoY(to);
//								tof = pos->wBitFiles[tox];
//								tor = pos->wBitRanks[toy];  
//								nDisp = to & 0xf0;
//								goto NextStep;
//							}
//						}
//						else{
//							sq2 = psmv->RookCap[DUpLeft] + (at & 0xf0);
//							if(IsWhite(pos->b256[sq2]) && StoX(mfrom) > StoX(sq2) ){
//								//paoTo				= TRUE;						
//
//								attacker			= at;
//								to                  = sq2;
//								tox = StoX(to);
//								toy = StoY(to);
//								tof = pos->wBitFiles[tox];
//								tor = pos->wBitRanks[toy]; 
//								nDisp = to & 0xf0;
//								goto NextStep;
//							}
//						}
//					}
//				}
//				//4,**************************************************
//				if(StoY(mto) == StoY(at)){			//�ӳ���Rank���뿪
//					if(StoY(mfrom) != StoY(at)){
//						//��һ�³���������Ϣ
//						psmv = RankMove(StoX(at),pos->wBitRanks[StoY(at)]);
//
//						if(StoX(mto) > StoX(at)){
//							sq2 = psmv->RookCap[DLoRight] + (at & 0xf0);
//							if(IsWhite(pos->b256[sq2]) && StoX(mto) < StoX(sq2) ){
//								//paoTo				= TRUE;						
//
//								attacker			= at;
//								to                  = sq2;
//								tox = StoX(to);
//								toy = StoY(to);
//								tof = pos->wBitFiles[tox];
//								tor = pos->wBitRanks[toy];
//								nDisp = to & 0xf0;
//								goto NextStep;
//							}
//						}
//						else{
//							sq2 = psmv->RookCap[DUpLeft] + (at & 0xf0);
//							if(IsWhite(pos->b256[sq2]) && StoX(mto) > StoX(sq2)){
//								//paoTo				= TRUE;
//								
//								attacker			= at;
//								to                  = sq2;
//								tox = StoX(to);
//								toy = StoY(to);
//								tof = pos->wBitFiles[tox];
//								tor = pos->wBitRanks[toy];  
//								nDisp = to & 0xf0;
//								goto NextStep;
//							}
//						}
//					}
//				}
//
//				//
//			}
//		}
//
//
//		//#####################################################################
//
//		
//		for(int at = PieceListStart(pos,BPAO); at > 0x32; at = NextPiece(pos,at)){
//			if(at != mto){		//�ߵĲ����Ǹ���							
//				//1,**************************************************
//				if(StoX(mfrom) == StoX(at)){			//���ڵ�File���뿪
//					if(StoX(mto) != StoX(at)){					
//						//��һ���ڵ�������Ϣ
//						psmv = FileMove(StoY(at),pos->wBitFiles[StoX(at)]);
//
//						if(StoY(mfrom) > StoY(at)){		//���ڵ�����
//							sq2 = psmv->CannonCap[DLoRight] + StoX(at);
//							if(IsWhiteLargePiece(pos->b256[sq2]) && StoY(mfrom) < StoY(sq2) ){   //�ߵ�����sq2 �� at ���м�
//								//paoTo				= TRUE;
//								attacker			= at;
//								to                  = sq2;
//								tox = StoX(to);
//								toy = StoY(to);
//								tof = pos->wBitFiles[tox];
//								tor = pos->wBitRanks[toy]; 
//								nDisp = to & 0xf0;
//								goto NextStep;
//							}
//						}
//						else{
//							sq2 = psmv->CannonCap[DUpLeft] + StoX(at);
//							if(IsWhiteLargePiece(pos->b256[sq2]) && StoY(mfrom) > StoY(sq2) ){
//								//paoTo				= TRUE;								
//								attacker			= at;								
//								to                  = sq2;
//								tox = StoX(to);
//								toy = StoY(to);
//								tof = pos->wBitFiles[tox];
//								tor = pos->wBitRanks[toy];  
//								nDisp = to & 0xf0;
//								goto NextStep;
//							}
//						}
//					}										
//				}
//				//2,**************************************************
//				if(StoX(mto) == StoX(at)){			//�ߵ��ڵ�File��
//					if(StoX(mfrom) != StoX(at)){					
//						//��һ���ڵ�������Ϣ
//						psmv = FileMove(StoY(at),pos->wBitFiles[StoX(at)]);
//
//						if(StoY(mto) > StoY(at)){		//���ڵ�����
//							sq2 = psmv->CannonCap[DLoRight] + StoX(at);
//							if(IsWhiteLargePiece(pos->b256[sq2]) && StoY(mto) < StoY(sq2) ){
//								//paoTo				= TRUE;
//								attacker			= at;
//
//								to                  = sq2;
//								tox = StoX(to);
//								toy = StoY(to);
//								tof = pos->wBitFiles[tox];
//								tor = pos->wBitRanks[toy]; 
//								nDisp = to & 0xf0;
//								goto NextStep;
//							}
//						}
//						else{
//							sq2 = psmv->CannonCap[DUpLeft] + StoX(at);
//							if(IsWhiteLargePiece(pos->b256[sq2]) && StoY(mto) > StoY(sq2) ){
//
//								attacker			= at;
//								to                  = sq2;
//								tox = StoX(to);
//								toy = StoY(to);
//								tof = pos->wBitFiles[tox];
//								tor = pos->wBitRanks[toy]; 
//								nDisp = to & 0xf0;
//								goto NextStep;
//							}
//						}
//					}
//										
//				}
//				//3,**************************************************
//				if(StoY(mfrom) == StoY(at)){			//���ڵ�Rank���뿪
//					if(StoY(mto) != StoY(at)){
//						//��һ���ڵ�������Ϣ
//						psmv = RankMove(StoX(at),pos->wBitRanks[StoY(at)]);
//
//						if(StoX(mfrom) > StoX(at)){
//							sq2 = psmv->CannonCap[DLoRight] + (at & 0xf0);
//							if(IsWhiteLargePiece(pos->b256[sq2]) && StoX(mfrom) < StoX(sq2) ){
//								//paoTo				= TRUE;								
//
//								attacker			= at;
//								to                  = sq2;
//								tox = StoX(to);
//								toy = StoY(to);
//								tof = pos->wBitFiles[tox];
//								tor = pos->wBitRanks[toy];  
//								nDisp = to & 0xf0;
//								goto NextStep;
//							}
//						}
//						else{
//							sq2 = psmv->CannonCap[DUpLeft] + (at & 0xf0);
//							if(IsWhiteLargePiece(pos->b256[sq2]) && StoX(mfrom) > StoX(sq2) ){
//								//paoTo				= TRUE;						
//
//								attacker			= at;
//								to                  = sq2;
//								tox = StoX(to);
//								toy = StoY(to);
//								tof = pos->wBitFiles[tox];
//								tor = pos->wBitRanks[toy]; 
//								nDisp = to & 0xf0;
//								goto NextStep;
//							}
//						}
//					}
//				}
//				//4,**************************************************
//				if(StoY(mto) == StoY(at)){			//���ڵ�Rank���뿪
//					if(StoY(mfrom) != StoY(at)){
//						//��һ���ڵ�������Ϣ
//						psmv = RankMove(StoX(at),pos->wBitRanks[StoY(at)]);
//
//						if(StoX(mto) > StoX(at)){
//							sq2 = psmv->CannonCap[DLoRight] + (at & 0xf0);
//							if(IsWhiteLargePiece(pos->b256[sq2]) && StoX(mto) < StoX(sq2) ){
//								//paoTo				= TRUE;						
//
//								attacker			= at;
//								to                  = sq2;
//								tox = StoX(to);
//								toy = StoY(to);
//								tof = pos->wBitFiles[tox];
//								tor = pos->wBitRanks[toy];
//								nDisp = to & 0xf0;
//								goto NextStep;
//							}
//						}
//						else{
//							sq2 = psmv->CannonCap[DUpLeft] + (at & 0xf0);
//							if(IsWhiteLargePiece(pos->b256[sq2]) && StoX(mto) > StoX(sq2)){
//								//paoTo				= TRUE;
//								
//								attacker			= at;
//								to                  = sq2;
//								tox = StoX(to);
//								toy = StoY(to);
//								tof = pos->wBitFiles[tox];
//								tor = pos->wBitRanks[toy];  
//								nDisp = to & 0xf0;
//								goto NextStep;
//							}
//						}
//					}
//				}
//
//				//
//			}
//		}
//
//		//#####################################################################
//		//////////////////////////////////////////////////////////////////////////////////////////////////
//
//       
//
//		//case XIANG:
//		//	{
//		//		if((GetDir(mto,to) & DirXiang) != 0 && pos->b256[(mto+to)/2] == 0){
//		//			attacker = mto;
//		//			goto NextStep;
//		//		}
//		//	}
//		//	break;
//		//case MA:{
//		//	int t = horseLegTab(to - mto + 256);
//		//	if(t != 0 && pos->b256[mto + t] == EMPTY){
//		//		attacker = mto;
//		//		goto NextStep;
//		//	}
//		//		}
//		//		break;
//
//		//========================================
//
//	}
//	//************************************************************************** �������ܲ��ܳ�
//	else{
//		//////////////////////////////////////////////////////////////////////////////
//		// ���췽��������ȥ��
//		int king  = PieceListStart(pos,RKING);
//	    int kx    = StoX(king);
//		int ky    = StoY(king);
//		int ky4   = king & 0xf0;
//
//		int sq1;
//		int sq2;
//		int sq3;
//
//		psmv = FileMove(ky,pos->wBitFiles[kx]);
//
//		//�õ�������ڶ�������
//		sq2 = psmv->CannonCap[DLoRight] + kx;
//	
//		if(sq2 != king){
//			if(pos->b256[sq2] == BCHE){
//				sq1 = psmv->RookCap[DLoRight] + kx;
//
//				if(IsWhite(pos->b256[sq1])){
//					//Not256Pos[NotNum] = sq1;
//					//------------------------------------
//					NotList[NotNum]  = sq1;
//					NotBoard[NotNum] = pos->b256[sq1];  //����һ������
//					pos->b256[sq1]   = EMPTY;
//					//-------------------------------------
//					RemovePiece(pos,sq1);
//					NotNum++;
//				}				
//			}
//		}
//
//		//�õ��������һ������
//		sq1 = psmv->RookCap[DUpLeft] + kx;
//		
//		if(sq1 != king){
//			
//			sq2 = psmv->CannonCap[DUpLeft] + kx;
//
//			if(sq2 != king){
//
//				int chess1 = pos->b256[sq1];
//				int chess2 = pos->b256[sq2];
//
//				if(chess2 == BCHE || chess2 == BKING){
//					if(IsWhite(chess1)){
//						//Not256Pos[NotNum] = sq1;
//						//------------------------------------
//						NotList[NotNum]  = sq1;
//						NotBoard[NotNum] = pos->b256[sq1];  //����һ������
//						pos->b256[sq1]   = EMPTY;
//						//-------------------------------------
//						RemovePiece(pos,sq1);
//						NotNum++;
//					}
//				}
//
//				sq3 = psmv->SuperCap[DUpLeft] + kx;
//				if(sq3 != king){
//					int chess3 = pos->b256[sq3];
//					//if(chess3 == BPAO){
//					if(chess3 == BPAO && sq3 != to){  //if(chess3 == BPAO){
//						if(IsWhite(chess2)){
//							//Not256Pos[NotNum] = sq2;
//							//------------------------------------
//							NotList[NotNum]  = sq2;
//							NotBoard[NotNum] = pos->b256[sq2];  //����һ������
//							pos->b256[sq2]   = EMPTY;
//							//-------------------------------------
//							RemovePiece(pos,sq2);
//							NotNum++;
//						}
//						if(IsWhite(chess1) && chess2 != BCHE && chess2 != BKING){
//							//Not256Pos[NotNum] = sq1;
//							//------------------------------------
//							NotList[NotNum]  = sq1;
//							NotBoard[NotNum] = pos->b256[sq1];  //����һ������
//							pos->b256[sq1]   = EMPTY;
//							//-------------------------------------
//							RemovePiece(pos,sq1);
//							NotNum++;
//						}
//					}
//				}
//			}
//		}
//
//		//�����ж�һ��
//		psmv = RankMove(kx,pos->wBitRanks[ky]);
//
//		sq1 = psmv->RookCap[DUpLeft] + ky4;
//		if(sq1 != king){
//			
//			sq2 = psmv->CannonCap[DUpLeft] + ky4;
//
//			if(sq2 != king){
//				int chess1 = pos->b256[sq1];
//				int chess2 = pos->b256[sq2];
//				
//				if(chess2 == BCHE){
//					if(IsWhite(chess1)){
//						//Not256Pos[NotNum] = sq1;
//						//------------------------------------
//						NotList[NotNum]  = sq1;
//						NotBoard[NotNum] = pos->b256[sq1];  //����һ������
//						pos->b256[sq1]   = EMPTY;
//						//-------------------------------------
//						RemovePiece(pos,sq1);
//						NotNum++;
//					}
//				}
//
//				sq3 = psmv->SuperCap[DUpLeft] + ky4;
//				if(sq3 != king){
//					int chess3 = pos->b256[sq3];
//					//if(chess3 == BPAO){
//					if(chess3 == BPAO && sq3 != to){  //if(chess3 == BPAO){
//						if(IsWhite(chess2)){
//							//Not256Pos[NotNum] = sq2;
//							//------------------------------------
//							NotList[NotNum]  = sq2;
//							NotBoard[NotNum] = pos->b256[sq2];  //����һ������
//							pos->b256[sq2]   = EMPTY;
//							//-------------------------------------
//							RemovePiece(pos,sq2);
//							NotNum++;
//						}
//						if(IsWhite(chess1) && chess2 != BCHE ){
//							//Not256Pos[NotNum] = sq1;
//							//------------------------------------
//							NotList[NotNum]  = sq1;
//							NotBoard[NotNum] = pos->b256[sq1];  //����һ������
//							pos->b256[sq1]   = EMPTY;
//							//-------------------------------------
//							RemovePiece(pos,sq1);
//							NotNum++;
//						}
//					}
//				}
//			}		
//		}
//
//		//�����ж�һ��
//
//		psmv = RankMove(kx,pos->wBitRanks[ky]);
//
//		sq1 = psmv->RookCap[DLoRight] + ky4;
//		if(sq1 != king){
//			
//			sq2 = psmv->CannonCap[DLoRight] + ky4;
//
//			if(sq2 != king){
//				int chess1 = pos->b256[sq1];
//				int chess2 = pos->b256[sq2];
//				
//				if(chess2 == BCHE){
//					if(IsWhite(chess1)){
//						//Not256Pos[NotNum] = sq1;
//						//------------------------------------
//						NotList[NotNum]  = sq1;
//						NotBoard[NotNum] = pos->b256[sq1];  //����һ������
//						pos->b256[sq1]   = EMPTY;
//						//-------------------------------------
//						RemovePiece(pos,sq1);
//						NotNum++;
//					}
//				}
//
//				sq3 = psmv->SuperCap[DLoRight] + ky4;
//				if(sq3 != king){
//					int chess3 = pos->b256[sq3];
//					//if(chess3 == BPAO){
//					if(chess3 == BPAO && sq3 != to){  //if(chess3 == BPAO){
//						if(IsWhite(chess2)){
//							//Not256Pos[NotNum] = sq2;
//							//------------------------------------
//							NotList[NotNum]  = sq2;
//							NotBoard[NotNum] = pos->b256[sq2];  //����һ������
//							pos->b256[sq2]   = EMPTY;
//							//-------------------------------------
//							RemovePiece(pos,sq2);
//							NotNum++;
//						}
//						if(IsWhite(chess1) && chess2 != BCHE ){
//							//Not256Pos[NotNum] = sq1;
//							//------------------------------------
//							NotList[NotNum]  = sq1;
//							NotBoard[NotNum] = pos->b256[sq1];  //����һ������
//							pos->b256[sq1]   = EMPTY;
//							//-------------------------------------
//							RemovePiece(pos,sq1);
//							NotNum++;
//						}
//					}
//				}
//			}		
//		}
//
//		//�ٿ�һ����
//		 //�ж�һ����û�����ڽ�����
//        for(int checkSq256 = PieceListStart(pos,BMA); checkSq256 > 0x32; checkSq256 = NextPiece(pos,checkSq256)){
//
//			if(checkSq256 != to){
//
//				int x   = horseLegTab(king - checkSq256 + 256);
//				int leg256 = checkSq256 + x;
//
//				if(x){
//					int leg14 = pos->b256[leg256];
//
//					if(IsWhite(leg14)){
//						//���ж�һ��,�ǲ����Ѿ�������
//						BOOL isRemove = FALSE;
//						for(int i = 0; i < NotNum; i++){
//							if(leg256 == NotList[i]){
//								isRemove = TRUE;
//								break;
//							}
//						}
//						//Not48Pos[NotNum]        = leg48;
//						if(isRemove == FALSE){
//							//Not256Pos[NotNum]       = leg256;
//							//------------------------------------
//							NotList[NotNum]  = leg256;
//							NotBoard[NotNum] = pos->b256[leg256];  //����һ������
//							pos->b256[leg256]   = EMPTY;
//							//-------------------------------------
//							RemovePiece(pos, leg256);
//							NotNum++;
//						}
//					}
//				}
//			}
//		}
//
//		//�췽�����ߵ�����
//
//		switch(moveChessId){
//			case PAWN:        //��ʵ����
//				{
//					if(to == mto - 16 || (to < 0x80 && (to == mto -1 || to == mto + 1))){
//						attacker = mto;
//						goto NextStep;
//					}
//				}
//				break;
//			case KING:
//				{
//					if((GetDir(mto,to) & DirKing) != 0){
//						attacker = mto;
//						goto NextStep;
//					}
//				}
//				break;
//			case SHI:
//				{
//					if((GetDir(mto,to) & DirShi) != 0){
//						attacker = mto;
//						goto NextStep;
//					}
//				}
//				break;
//			case XIANG:
//				{
//					if((GetDir(mto,to) & DirXiang) != 0 && pos->b256[(mto+to)/2] == 0){
//						attacker = mto;
//						goto NextStep;
//					}
//				}
//				break;
//			case MA:{
//					int t = horseLegTab(to - mto + 256);
//					if(t != 0 && pos->b256[mto + t] == EMPTY){
//						attacker = mto;
//						goto NextStep;
//					}
//					 }
//				break;
//			case PAO: //��һ�����ܲ��ܳ�
//				{
//					//int tox = StoX(to);
//					//int toy = StoY(to);
//
//					//int tof = pos->wBitFiles[tox];
//					//int tor = pos->wBitRanks[toy];  
//					if(false){
//					}
//					else if(StoX(mto) == StoX(to)){
//						if((FileMask(StoY(mto),tof)->CannonCap & yBitMask(to)) != 0){
//							attacker = mto;
//							goto NextStep;
//						}
//					}
//					else if(StoY(mto) == StoY(to)){
//						if((RankMask(StoX(mto),tor)->CannonCap & xBitMask(to)) != 0){
//							attacker = mto;
//							goto NextStep;
//						}
//					}
//				}
//				break;
//			case CHE:{
//					if(false){
//					}
//					else if(StoX(mto) == StoX(to)){
//						if((FileMask(StoY(mto),tof)->RookCap & yBitMask(to)) != 0){
//							attacker = mto;
//							goto NextStep;
//						}
//					}
//					else if(StoY(mto) == StoY(to)){
//						if((RankMask(StoX(mto),tor)->RookCap & xBitMask(to)) != 0){
//							attacker = mto;
//							goto NextStep;
//						}
//					}
//					  }
//				break;
//			default:
//				break;
//		}
//
//		//#####################################################################
//		// �ٿ�һ���ǲ����ÿ�������
//		for(int at = PieceListStart(pos,RXIANG); at > 0x32; at = NextPiece(pos,at)){
//			if(at != mto){		//�ߵĲ����Ǹ���	
//				//��һ��at�ܲ��ܳԵ�to
//				if((GetDir(at,to) & DirXiang) != 0){
//					if(mfrom == (at+to) /2 ){
//						attacker			= at;
//						//to                  = sq2;
//						//tox = StoX(to);
//						//toy = StoY(to);
//						//tof = pos->wBitFiles[tox];
//						//tor = pos->wBitRanks[toy];  
//						//nDisp = to & 0xf0;
//						goto NextStep;
//					}
//				}
//			}
//		}
//
//		// �ٿ�һ���ǲ����ÿ�������
//		for(int at = PieceListStart(pos,RMA); at > 0x32; at = NextPiece(pos,at)){
//			if(at != mto){		//�ߵĲ����Ǹ���
//
//				int t = horseLegTab(to - at + 256);
//				if(t != 0){
//
//					if(mfrom == at + t){
//						attacker			= at;
//						//to                  = sq2;
//						//tox = StoX(to);
//						//toy = StoY(to);
//						//tof = pos->wBitFiles[tox];
//						//tor = pos->wBitRanks[toy];  
//						//nDisp = to & 0xf0;
//						goto NextStep;
//					}
//				}
//			}
//		}		
//		//////////////////////////////////////////////////////////////////////////////////////////////////
//
//		//#####################################################################
//		//�ǲ����ÿ��˳�
//
//		for(int at = PieceListStart(pos,RCHE); at > 0x32; at = NextPiece(pos,at)){
//			if(at != mto){		//�ߵĲ����Ǹ���							
//				//1,**************************************************
//				if(StoX(mfrom) == StoX(at)){			//�ӳ���File���뿪
//					if(StoX(mto) != StoX(at)){					
//						//��һ���ڵ�������Ϣ
//						psmv = FileMove(StoY(at),pos->wBitFiles[StoX(at)]);
//
//						//sq1 = psmv->RookCap[DLoRight] + StoX(at);
//						//sq2 = psmv->CannonCap[DLoRight] + StoX(at);
//						//sq3 = psmv->SuperCap[DLoRight] + StoX(at);
//
//						if(StoY(mfrom) > StoY(at)){		//�ڳ�������
//							sq2 = psmv->RookCap[DLoRight] + StoX(at);
//							if(IsBlack(pos->b256[sq2]) && StoY(mfrom) < StoY(sq2) ){								
//
//								attacker			= at;
//								to                  = sq2;
//								tox = StoX(to);
//								toy = StoY(to);
//								tof = pos->wBitFiles[tox];
//								tor = pos->wBitRanks[toy]; 
//								nDisp = to & 0xf0;
//								goto NextStep;
//							}
//						}
//						else{
//							sq2 = psmv->RookCap[DUpLeft] + StoX(at);
//							if(IsBlack(pos->b256[sq2])  && StoY(mfrom) > StoY(sq2) ){								
//
//								attacker			= at;
//								to                  = sq2;
//								tox = StoX(to);
//								toy = StoY(to);
//								tof = pos->wBitFiles[tox];
//								tor = pos->wBitRanks[toy]; 
//								nDisp = to & 0xf0;
//								goto NextStep;
//							}
//						}
//					}										
//				}
//				//2,**************************************************
//				if(StoX(mto) == StoX(at)){			//�ӳ���File���뿪 //�ߵ�����File��
//					if(StoX(mfrom) != StoX(at)){					
//						//��һ���ڵ�������Ϣ
//						psmv = FileMove(StoY(at),pos->wBitFiles[StoX(at)]);
//
//						if(StoY(mto) > StoY(at)){		//�ڳ�������
//							sq2 = psmv->RookCap[DLoRight] + StoX(at);
//							if(IsBlack(pos->b256[sq2])  && StoY(mto) < StoY(sq2) ){							
//
//								attacker			= at;
//								to                  = sq2;
//								tox = StoX(to);
//								toy = StoY(to);
//								tof = pos->wBitFiles[tox];
//								tor = pos->wBitRanks[toy];  
//								nDisp = to & 0xf0;
//								goto NextStep;
//							}
//						}
//						else{
//							sq2 = psmv->RookCap[DUpLeft] + StoX(at);
//							if(IsBlack(pos->b256[sq2]) && StoY(mto) > StoY(sq2) ){							
//
//								attacker			= at;
//								to                  = sq2;
//								tox = StoX(to);
//								toy = StoY(to);
//								tof = pos->wBitFiles[tox];
//								tor = pos->wBitRanks[toy];  
//								nDisp = to & 0xf0;
//								goto NextStep;
//							}
//						}
//					}										
//				}
//				//3, **************************************************
//				if(StoY(mfrom) == StoY(at)){			//�ӳ���Rank���뿪
//					if(StoY(mto) != StoY(at)){
//						//��һ���ڵ�������Ϣ
//						psmv = RankMove(StoX(at),pos->wBitRanks[StoY(at)]);
//
//						if(StoX(mfrom) > StoX(at)){
//							sq2 = psmv->RookCap[DLoRight] + (at & 0xf0);
//							if(IsBlack(pos->b256[sq2])  && StoX(mfrom) < StoX(sq2) ){							
//
//								attacker			= at;
//								to                  = sq2;
//								tox = StoX(to);
//								toy = StoY(to);
//								tof = pos->wBitFiles[tox];
//								tor = pos->wBitRanks[toy];  
//								nDisp = to & 0xf0;
//								goto NextStep;
//							}
//						}
//						else{
//							sq2 = psmv->RookCap[DUpLeft] + (at & 0xf0);
//							if(IsBlack(pos->b256[sq2])  && StoX(mfrom) > StoX(sq2) ){								
//
//								attacker			= at;
//								to                  = sq2;
//								tox = StoX(to);
//								toy = StoY(to);
//								tof = pos->wBitFiles[tox];
//								tor = pos->wBitRanks[toy]; 
//								nDisp = to & 0xf0;
//								goto NextStep;
//							}
//						}
//					}
//				}
//				//4, **************************************************
//				if(StoY(mto) == StoY(at)){			//�ӳ���Rank���뿪
//					if(StoY(mfrom) != StoY(at)){
//						//��һ�³���������Ϣ
//						psmv = RankMove(StoX(at),pos->wBitRanks[StoY(at)]);
//
//						if(StoX(mto) > StoX(at)){
//							sq2 = psmv->RookCap[DLoRight] + (at & 0xf0);
//							if(IsBlack(pos->b256[sq2])  && StoX(mto) < StoX(sq2)){							
//
//								attacker			= at;
//								to                  = sq2;
//								tox = StoX(to);
//								toy = StoY(to);
//								tof = pos->wBitFiles[tox];
//								tor = pos->wBitRanks[toy]; 
//								nDisp = to & 0xf0;
//								goto NextStep;
//							}
//						}
//						else{
//							sq2 = psmv->RookCap[DUpLeft] + (at & 0xf0);
//							if(IsBlack(pos->b256[sq2]) && StoX(mto) > StoX(sq2)){								
//
//								attacker			= at;
//								to                  = sq2;
//								tox = StoX(to);
//								toy = StoY(to);
//								tof = pos->wBitFiles[tox];
//								tor = pos->wBitRanks[toy]; 
//								nDisp = to & 0xf0;
//								goto NextStep;
//							}
//						}
//					}
//				}
//
//				//
//		     }
//		}
//
//
//		//#####################################################################
//
//
//        
//		for(int at = PieceListStart(pos,RPAO); at > 0x32; at = NextPiece(pos,at)){
//			if(at != mto){		//�ߵĲ����Ǹ���							
//				//1,**************************************************
//				if(StoX(mfrom) == StoX(at)){			//���ڵ�File���뿪
//					if(StoX(mto) != StoX(at)){					
//						//��һ���ڵ�������Ϣ
//						psmv = FileMove(StoY(at),pos->wBitFiles[StoX(at)]);
//
//						//sq1 = psmv->RookCap[DLoRight] + StoX(at);
//						//sq2 = psmv->CannonCap[DLoRight] + StoX(at);
//						//sq3 = psmv->SuperCap[DLoRight] + StoX(at);
//
//						if(StoY(mfrom) > StoY(at)){		//���ڵ�����
//							sq2 = psmv->CannonCap[DLoRight] + StoX(at);
//							if(IsBlackLargePiece(pos->b256[sq2]) && StoY(mfrom) < StoY(sq2) ){								
//
//								attacker			= at;
//								to                  = sq2;
//								tox = StoX(to);
//								toy = StoY(to);
//								tof = pos->wBitFiles[tox];
//								tor = pos->wBitRanks[toy]; 
//								nDisp = to & 0xf0;
//								goto NextStep;
//							}
//						}
//						else{
//							sq2 = psmv->CannonCap[DUpLeft] + StoX(at);
//							if(IsBlackLargePiece(pos->b256[sq2])  && StoY(mfrom) > StoY(sq2) ){								
//
//								attacker			= at;
//								to                  = sq2;
//								tox = StoX(to);
//								toy = StoY(to);
//								tof = pos->wBitFiles[tox];
//								tor = pos->wBitRanks[toy]; 
//								nDisp = to & 0xf0;
//								goto NextStep;
//							}
//						}
//					}										
//				}
//				//2,**************************************************
//				if(StoX(mto) == StoX(at)){			//���ڵ�File���뿪 //�ߵ��ڵ�FILE��
//					if(StoX(mfrom) != StoX(at)){					
//						//��һ���ڵ�������Ϣ
//						psmv = FileMove(StoY(at),pos->wBitFiles[StoX(at)]);
//
//						if(StoY(mto) > StoY(at)){		//���ڵ�����
//							sq2 = psmv->CannonCap[DLoRight] + StoX(at);
//							if(IsBlackLargePiece(pos->b256[sq2])  && StoY(mto) < StoY(sq2) ){							
//
//								attacker			= at;
//								to                  = sq2;
//								tox = StoX(to);
//								toy = StoY(to);
//								tof = pos->wBitFiles[tox];
//								tor = pos->wBitRanks[toy];  
//								nDisp = to & 0xf0;
//								goto NextStep;
//							}
//						}
//						else{
//							sq2 = psmv->CannonCap[DUpLeft] + StoX(at);
//							if(IsBlackLargePiece(pos->b256[sq2]) && StoY(mto) > StoY(sq2) ){							
//
//								attacker			= at;
//								to                  = sq2;
//								tox = StoX(to);
//								toy = StoY(to);
//								tof = pos->wBitFiles[tox];
//								tor = pos->wBitRanks[toy];  
//								nDisp = to & 0xf0;
//								goto NextStep;
//							}
//						}
//					}										
//				}
//				//3, **************************************************
//				if(StoY(mfrom) == StoY(at)){			//���ڵ�Rank���뿪
//					if(StoY(mto) != StoY(at)){
//						//��һ���ڵ�������Ϣ
//						psmv = RankMove(StoX(at),pos->wBitRanks[StoY(at)]);
//
//						if(StoX(mfrom) > StoX(at)){
//							sq2 = psmv->CannonCap[DLoRight] + (at & 0xf0);
//							if(IsBlackLargePiece(pos->b256[sq2])  && StoX(mfrom) < StoX(sq2) ){							
//
//								attacker			= at;
//								to                  = sq2;
//								tox = StoX(to);
//								toy = StoY(to);
//								tof = pos->wBitFiles[tox];
//								tor = pos->wBitRanks[toy];  
//								nDisp = to & 0xf0;
//								goto NextStep;
//							}
//						}
//						else{
//							sq2 = psmv->CannonCap[DUpLeft] + (at & 0xf0);
//							if(IsBlackLargePiece(pos->b256[sq2])  && StoX(mfrom) > StoX(sq2) ){								
//
//								attacker			= at;
//								to                  = sq2;
//								tox = StoX(to);
//								toy = StoY(to);
//								tof = pos->wBitFiles[tox];
//								tor = pos->wBitRanks[toy]; 
//								nDisp = to & 0xf0;
//								goto NextStep;
//							}
//						}
//					}
//				}
//				//4, **************************************************
//				if(StoY(mto) == StoY(at)){			//���ڵ�Rank���뿪
//					if(StoY(mfrom) != StoY(at)){
//						//��һ���ڵ�������Ϣ
//						psmv = RankMove(StoX(at),pos->wBitRanks[StoY(at)]);
//
//						if(StoX(mto) > StoX(at)){
//							sq2 = psmv->CannonCap[DLoRight] + (at & 0xf0);
//							if(IsBlackLargePiece(pos->b256[sq2])  && StoX(mto) < StoX(sq2)){							
//
//								attacker			= at;
//								to                  = sq2;
//								tox = StoX(to);
//								toy = StoY(to);
//								tof = pos->wBitFiles[tox];
//								tor = pos->wBitRanks[toy]; 
//								nDisp = to & 0xf0;
//								goto NextStep;
//							}
//						}
//						else{
//							sq2 = psmv->CannonCap[DUpLeft] + (at & 0xf0);
//							if(IsBlackLargePiece(pos->b256[sq2]) && StoX(mto) > StoX(sq2)){								
//
//								attacker			= at;
//								to                  = sq2;
//								tox = StoX(to);
//								toy = StoY(to);
//								tof = pos->wBitFiles[tox];
//								tor = pos->wBitRanks[toy]; 
//								nDisp = to & 0xf0;
//								goto NextStep;
//							}
//						}
//					}
//				}
//
//				//
//		     }
//		}
//
//		
//	}
//	//**************************************************************************
//
//
//	
//    
//NextStep:
//
//	/////////////////////////////////////////////////////////////////////////////////////
//	//����������ӻָ�һ��
//	for(int i=0; i<NotNum; i++){
//        int sq = NotList[i];
//		//
//		pos->b256[sq] = NotBoard[i];
//		//
//        InsertPiece(pos,pos->b256[sq], sq);
//
//        ASSERT(NextPiece(pos,PieceListStart(pos,pos->b256[sq])) != sq);
//    }
//	/////////////////////////////////////////////////////////////////////////////////////
//
//	if(attacker == 0){
//		return FALSE;
//	}
//
//	//////////////////////////////////////////////////////////////////////
//	////�ٿ�һ��,�����������ͬ,�Ͳ���
//	//if(PIECE_ID(pos->b256[to]) == PIECE_ID(pos->b256[attacker])){
//	//	return FALSE;
//	//}
//
//	//****************************************************************************
//    int at_id    = PIECE_ID(pos->b256[attacker]);
//	int to_id    = PIECE_ID(pos->b256[to]);
//
//#ifdef   USE_EAT_DIFF_CHESS            //��׽��ͬ���ӣ����㳣׽
//	//����������Ե����Ӵ�һ��
//	pos->eatChess[pos->eatNum] = to_id;
//#endif
//
//	if(at_id == PAWN || at_id == KING){
//		return FALSE;
//	}
//
//	//int me_id    = PIECE_ID(pos->b256[mto]);
//
//	//if(me_id == PAWN || me_id == KING){
//	//	return FALSE;
//	//}
//
//	//�ٿ�һ��fromchess�ļ�ֵ�ǲ��Ǳ�tochess�ļ�ֵС
//	if(PieceValues[pos->b256[attacker]] < PieceValues[pos->b256[to]]){
//		goto IsCanReturnTrue;
//	}
//
//	//if(at_id == to_id){
//	//	return FALSE;
//	//}
//	//*****************************************************************************
//
//	
//
////�ٿ�һ�³����Ӻ󣬶Է���û�����ӿɳԻ�
//
//	//����һ��FR*************
//
//	//if(paoTo == FALSE){
//		if(StoX(attacker) == tox){
//			tof ^= yBitMask(attacker);
//		}
//		if(StoY(attacker) == toy){
//			tor ^= xBitMask(attacker);
//		} 
//	//}
//	//else{
//	//	if(StoX(
//	//}
//
//	//�ٿ�һ�¶Է��ܲ��ܳԻ��� 
//
//	//////////////////////////////////////////////////////////////////////////////////////////////////
//	//  ���Ƚ��Է������ߵ�����ȥ�˲���
//	NotNum          =0;         //�������ߵ����ӵ����� 
//
//		//**************************************************************************
//	if(side == WHITE){
//
//		//////////////////////////////////////////////////////////////////////////////
//		// ���ڷ���������ȥ��
//		int king  = PieceListStart(pos,BKING);
//	    int kx    = StoX(king);
//		int ky    = StoY(king);
//		int ky4   = king & 0xf0;
//
//		int sq1;
//		int sq2;
//		int sq3;
//
//		psmv = FileMove(ky,pos->wBitFiles[kx]);
//
//		//�õ�����������Ϣ
//		sq2 = psmv->CannonCap[DUpLeft] + kx;
//	
//		if(sq2 != king){
//			if(pos->b256[sq2] == RCHE){
//				sq1 = psmv->RookCap[DUpLeft] + kx;
//
//				if(IsBlack(pos->b256[sq1])){
//					//Not256Pos[NotNum] = sq1;
//					//------------------------------------
//					NotList[NotNum]  = sq1;
//					NotBoard[NotNum] = pos->b256[sq1];  //����һ������
//					pos->b256[sq1]   = EMPTY;
//					//-------------------------------------
//					RemovePiece(pos,sq1);
//					NotNum++;
//				}				
//			}
//		}
//
//		//�õ��������һ������
//		sq1 = psmv->RookCap[DLoRight] + kx;
//		
//		if(sq1 != king){
//			
//			sq2 = psmv->CannonCap[DLoRight] + kx;
//
//			if(sq2 != king){
//
//				int chess1 = pos->b256[sq1];
//				int chess2 = pos->b256[sq2];
//
//				if(chess2 == RCHE || chess2 == RKING){
//					if(IsBlack(chess1)){
//						//Not256Pos[NotNum] = sq1;
//						//------------------------------------
//						NotList[NotNum]  = sq1;
//						NotBoard[NotNum] = pos->b256[sq1];  //����һ������
//						pos->b256[sq1]   = EMPTY;
//						//-------------------------------------
//						RemovePiece(pos,sq1);
//						NotNum++;
//					}
//				}
//
//				sq3 = psmv->SuperCap[DLoRight] + kx;
//				if(sq3 != king){
//					int chess3 = pos->b256[sq3];
//					if(chess3 == RPAO){
//						if(IsBlack(chess2)){
//							//Not256Pos[NotNum] = sq2;
//							//------------------------------------
//							NotList[NotNum]  = sq2;
//							NotBoard[NotNum] = pos->b256[sq2];  //����һ������
//							pos->b256[sq2]   = EMPTY;
//							//-------------------------------------
//							RemovePiece(pos,sq2);
//							NotNum++;
//						}
//						if(IsBlack(chess1) && chess2 != RCHE && chess2 != RKING){
//							//Not256Pos[NotNum] = sq1;
//							//------------------------------------
//							NotList[NotNum]  = sq1;
//							NotBoard[NotNum] = pos->b256[sq1];  //����һ������
//							pos->b256[sq1]   = EMPTY;
//							//-------------------------------------
//							RemovePiece(pos,sq1);
//							NotNum++;
//						}
//					}
//				}
//			}
//		}
//
//		//�����ж�һ��
//		psmv = RankMove(kx,pos->wBitRanks[ky]);
//
//		sq1 = psmv->RookCap[DUpLeft] + ky4;
//		if(sq1 != king){
//			
//			sq2 = psmv->CannonCap[DUpLeft] + ky4;
//
//			if(sq2 != king){
//				int chess1 = pos->b256[sq1];
//				int chess2 = pos->b256[sq2];
//				
//				if(chess2 == RCHE){
//					if(IsBlack(chess1)){
//						//Not256Pos[NotNum] = sq1;
//						//------------------------------------
//						NotList[NotNum]  = sq1;
//						NotBoard[NotNum] = pos->b256[sq1];  //����һ������
//						pos->b256[sq1]   = EMPTY;
//						//-------------------------------------
//						RemovePiece(pos,sq1);
//						NotNum++;
//					}
//				}
//
//				sq3 = psmv->SuperCap[DUpLeft] + ky4;
//				if(sq3 != king){
//					int chess3 = pos->b256[sq3];
//					if(chess3 == RPAO){
//						if(IsBlack(chess2)){
//							//Not256Pos[NotNum] = sq2;
//							//------------------------------------
//							NotList[NotNum]  = sq2;
//							NotBoard[NotNum] = pos->b256[sq2];  //����һ������
//							pos->b256[sq2]   = EMPTY;
//							//-------------------------------------
//							RemovePiece(pos,sq2);
//							NotNum++;
//						}
//						if(IsBlack(chess1) && chess2 != RCHE ){
//							//Not256Pos[NotNum] = sq1;
//							//------------------------------------
//							NotList[NotNum]  = sq1;
//							NotBoard[NotNum] = pos->b256[sq1];  //����һ������
//							pos->b256[sq1]   = EMPTY;
//							//-------------------------------------
//							RemovePiece(pos,sq1);
//							NotNum++;
//						}
//					}
//				}
//			}		
//		}
//
//		//�����ж�һ��
//
//		psmv = RankMove(kx,pos->wBitRanks[ky]);
//
//		sq1 = psmv->RookCap[DLoRight] + ky4;
//		if(sq1 != king){
//			
//			sq2 = psmv->CannonCap[DLoRight] + ky4;
//
//			if(sq2 != king){
//				int chess1 = pos->b256[sq1];
//				int chess2 = pos->b256[sq2];
//				
//				if(chess2 == RCHE){
//					if(IsBlack(chess1)){
//						//Not256Pos[NotNum] = sq1;
//						//------------------------------------
//						NotList[NotNum]  = sq1;
//						NotBoard[NotNum] = pos->b256[sq1];  //����һ������
//						pos->b256[sq1]   = EMPTY;
//						//-------------------------------------
//						RemovePiece(pos,sq1);
//						NotNum++;
//					}
//				}
//
//				sq3 = psmv->SuperCap[DLoRight] + ky4;
//				if(sq3 != king){
//					int chess3 = pos->b256[sq3];
//					if(chess3 == RPAO){
//						if(IsBlack(chess2)){
//							//Not256Pos[NotNum] = sq2;
//							//------------------------------------
//							NotList[NotNum]  = sq2;
//							NotBoard[NotNum] = pos->b256[sq2];  //����һ������
//							pos->b256[sq2]   = EMPTY;
//							//-------------------------------------
//							RemovePiece(pos,sq2);
//							NotNum++;
//						}
//						if(IsBlack(chess1) && chess2 != RCHE ){
//							//Not256Pos[NotNum] = sq1;
//							//------------------------------------
//							NotList[NotNum]  = sq1;
//							NotBoard[NotNum] = pos->b256[sq1];  //����һ������
//							pos->b256[sq1]   = EMPTY;
//							//-------------------------------------
//							RemovePiece(pos,sq1);
//							NotNum++;
//						}
//					}
//				}
//			}		
//		}
//
//		//�ٿ�һ����
//		 //�ж�һ����û�����ڽ�����
//        for(int checkSq256 = PieceListStart(pos,RMA); checkSq256 > 0x32; checkSq256 = NextPiece(pos,checkSq256)){
//
//			//if(checkSq256 != mto){
//
//				int x   = horseLegTab(king - checkSq256 + 256);
//				int leg256 = checkSq256 + x;
//
//				if(x){
//					int leg14 = pos->b256[leg256];
//
//					if(IsBlack(leg14)){
//						//���ж�һ��,�ǲ����Ѿ�������
//						BOOL isRemove = FALSE;
//						for(int i = 0; i < NotNum; i++){
//							if(leg256 == NotList[i]){
//								isRemove = TRUE;
//								break;
//							}
//						}
//						//Not48Pos[NotNum]        = leg48;
//						if(isRemove == FALSE){
//							//Not256Pos[NotNum]       = leg256;
//							//------------------------------------
//							NotList[NotNum]  = leg256;
//							NotBoard[NotNum] = pos->b256[leg256];  //����һ������
//							pos->b256[leg256]   = EMPTY;
//							//-------------------------------------
//							RemovePiece(pos, leg256);
//							NotNum++;
//						}
//					}
//				}
//			//}
//		}
//        // ���ڷ���������ȥ�� End
//		//////////////////////////////////////////////////////////////////////////////
//
//		psmv = FileMove(toy,tof);
//		//�õ������һ��
//		tmp = psmv->RookCap[DUpLeft] + tox;
//		if(tmp != to){ 
//
//			switch(pos->b256[tmp]){
//				case BCHE:  //�ڳ�
//					attacker = tmp;
//					goto CanEatBack;
//					break;			
//				case BKING: //�ڽ�
//					if(tmp+16 == to && toy < 0x6){
//						attacker = tmp;
//						goto CanEatBack;
//					}
//					break;
//				case BPAWN: //����
//					if(tmp+16 == to){
//						attacker = tmp;
//						goto CanEatBack;
//					}
//					break;
//				default:
//					break;
//			}
//
//			//���˵�һ�����еڶ�������
//			tmp = psmv->CannonCap[DUpLeft] + tox;
//			if(tmp != to){
//				int c14 = pos->b256[tmp];
//				if(c14 == BPAO){
//					attacker = tmp;
//					goto CanEatBack;
//				}
//			}
//		}
//		//�õ�to�������һ��������
//		tmp = psmv->RookCap[DLoRight] + tox;
//		if(tmp != to){   
//
//			switch(pos->b256[tmp]){			
//				case BCHE:
//					attacker = tmp;
//					goto CanEatBack;
//					break;
//				case BKING:
//					if(tmp-16 == to && toy < 0x6){
//						attacker = tmp;
//						goto CanEatBack;
//					}	
//					break;
//				default:
//					break;
//			} 
//
//			//���˵�һ�����еڶ�������
//			tmp = psmv->CannonCap[DLoRight] + tox;
//			if(tmp != to ){
//				int c14 = pos->b256[tmp];
//				if(c14 == BPAO){
//					attacker = tmp;
//					goto CanEatBack;
//				}
//			}
//		}
//		//�õ�to�����ҵ���Ϣ
//		//psmv = smvRankMoveTab[tox-3] + tor; 
//
//		psmv = RankMove(tox,tor);
//		//�õ�to����ĵ�һ������
//		tmp = psmv->RookCap[DUpLeft] + nDisp;
//		if(tmp != to){ 
//
//			switch(pos->b256[tmp]){
//				 case BCHE:
//					attacker = tmp;
//					goto CanEatBack;
//					 break;		
//					
//				 case BKING:
//					 if((inBoard(to) & IN_BKING) && tmp+1 == to){
//						 attacker = tmp;
//						 goto CanEatBack;
//					 }
//					 break;				
//				 case BPAWN:
//					 if(toy > 0x7 && tmp+1 == to){
//						 attacker = tmp;
//						 goto CanEatBack;
//					 }
//					 break;
//				 default:
//					 break;                
//			}  
//
//			//���˵�һ����,���еڶ�����
//			tmp = psmv->CannonCap[DUpLeft] + nDisp;
//			if(tmp != to){
//				int c14 = pos->b256[tmp];
//				if(c14 == BPAO){
//					attacker = tmp;
//				    goto CanEatBack;
//				}
//			}
//		}
//		//�õ�to����ĵ�һ������
//		tmp = psmv->RookCap[DLoRight] + nDisp;
//		if(tmp != to){
//
//			switch(pos->b256[tmp]){				
//				case BCHE:
//					attacker = tmp;
//				    goto CanEatBack;
//					break;				
//				case BKING:
//					if((inBoard(to) & IN_BKING) && tmp-1 == to){
//						attacker = tmp;
//						goto CanEatBack;
//					}
//					break;			
//				case BPAWN:
//					if(toy > 0x7 && tmp-1 == to){
//						attacker = tmp;
//				       goto CanEatBack;
//					}
//					break;
//				default:
//					break;
//			}
//
//			//���˵�һ����,���еڶ�����
//			tmp = psmv->CannonCap[DLoRight] + nDisp;
//			if(tmp != to ){
//				int c14 = pos->b256[tmp];
//				if(c14 == BPAO){
//					attacker = tmp;
//				    goto CanEatBack;
//				}            
//			}
//		}
//
//
//
//		//����
//		if(inBoard(to) & IN_BSHI){
//			for(int at = PieceListStart(pos,BSHI); at > 0x32; at = NextPiece(pos,at)){
//				//if(at != from && (GetDir(at,to) & DirShi)){
//				if((GetDir(at,to) & DirShi)){
//					attacker = at;
//				    goto CanEatBack;
//				}
//			}
//		}
//		//����
//		if(inBoard(to) & IN_BXIANG){
//			for(int at = PieceListStart(pos,BXIANG); at > 0x32; at = NextPiece(pos,at)){
//				/*if(at != from && (GetDir(at,to) & DirXiang) && pos->b256[(at+to)/2] == EMPTY){*/
//				if((GetDir(at,to) & DirXiang) && pos->b256[(at+to)/2] == EMPTY){
//					attacker = at;
//				    goto CanEatBack;
//				}
//			}
//		}
//
//		//����
//		for(int at = PieceListStart(pos,BMA); at > 0x32; at = NextPiece(pos,at)){
//			//if(at != from){
//			int m = horseLegTab(to-at+256);
//			if(m && !pos->b256[at+m]){
//				attacker = at;
//			    goto CanEatBack;
//			}
//			//}
//		}
//
//	}
//
//
//	//************************************************************************** �������ܲ��ܳ�
//	else{
//
//		//////////////////////////////////////////////////////////////////////////////
//		// ���췽��������ȥ��
//		int king  = PieceListStart(pos,RKING);
//	    int kx    = StoX(king);
//		int ky    = StoY(king);
//		int ky4   = king & 0xf0;
//
//		int sq1;
//		int sq2;
//		int sq3;
//
//		psmv = FileMove(ky,pos->wBitFiles[kx]);
//
//		//�õ��������һ������
//		sq2 = psmv->CannonCap[DLoRight] + kx;
//	
//		if(sq2 != king){
//			if(pos->b256[sq2] == BCHE){
//				sq1 = psmv->RookCap[DLoRight] + kx;
//
//				if(IsWhite(pos->b256[sq1])){
//					//Not256Pos[NotNum] = sq1;
//					//------------------------------------
//					NotList[NotNum]  = sq1;
//					NotBoard[NotNum] = pos->b256[sq1];  //����һ������
//					pos->b256[sq1]   = EMPTY;
//					//-------------------------------------
//					RemovePiece(pos,sq1);
//					NotNum++;
//				}				
//			}
//		}
//
//		//�õ��������һ������
//		sq1 = psmv->RookCap[DUpLeft] + kx;
//		
//		if(sq1 != king){
//			
//			sq2 = psmv->CannonCap[DUpLeft] + kx;
//
//			if(sq2 != king){
//
//				int chess1 = pos->b256[sq1];
//				int chess2 = pos->b256[sq2];
//
//				if(chess2 == BCHE || chess2 == BKING){
//					if(IsWhite(chess1)){
//						//Not256Pos[NotNum] = sq1;
//						//------------------------------------
//						NotList[NotNum]  = sq1;
//						NotBoard[NotNum] = pos->b256[sq1];  //����һ������
//						pos->b256[sq1]   = EMPTY;
//						//-------------------------------------
//						RemovePiece(pos,sq1);
//						NotNum++;
//					}
//				}
//
//				sq3 = psmv->SuperCap[DUpLeft] + kx;
//				if(sq3 != king){
//					int chess3 = pos->b256[sq3];
//					if(chess3 == BPAO){
//						if(IsWhite(chess2)){
//							//Not256Pos[NotNum] = sq2;
//							//------------------------------------
//							NotList[NotNum]  = sq2;
//							NotBoard[NotNum] = pos->b256[sq2];  //����һ������
//							pos->b256[sq2]   = EMPTY;
//							//-------------------------------------
//							RemovePiece(pos,sq2);
//							NotNum++;
//						}
//						if(IsWhite(chess1) && chess2 != BCHE && chess2 != BKING){
//							//Not256Pos[NotNum] = sq1;
//							//------------------------------------
//							NotList[NotNum]  = sq1;
//							NotBoard[NotNum] = pos->b256[sq1];  //����һ������
//							pos->b256[sq1]   = EMPTY;
//							//-------------------------------------
//							RemovePiece(pos,sq1);
//							NotNum++;
//						}
//					}
//				}
//			}
//		}
//
//		//�����ж�һ��
//		psmv = RankMove(kx,pos->wBitRanks[ky]);
//
//		sq1 = psmv->RookCap[DUpLeft] + ky4;
//		if(sq1 != king){
//			
//			sq2 = psmv->CannonCap[DUpLeft] + ky4;
//
//			if(sq2 != king){
//				int chess1 = pos->b256[sq1];
//				int chess2 = pos->b256[sq2];
//				
//				if(chess2 == BCHE){
//					if(IsWhite(chess1)){
//						//Not256Pos[NotNum] = sq1;
//						//------------------------------------
//						NotList[NotNum]  = sq1;
//						NotBoard[NotNum] = pos->b256[sq1];  //����һ������
//						pos->b256[sq1]   = EMPTY;
//						//-------------------------------------
//						RemovePiece(pos,sq1);
//						NotNum++;
//					}
//				}
//
//				sq3 = psmv->SuperCap[DUpLeft] + ky4;
//				if(sq3 != king){
//					int chess3 = pos->b256[sq3];
//					if(chess3 == BPAO){
//						if(IsWhite(chess2)){
//							//Not256Pos[NotNum] = sq2;
//							//------------------------------------
//							NotList[NotNum]  = sq2;
//							NotBoard[NotNum] = pos->b256[sq2];  //����һ������
//							pos->b256[sq2]   = EMPTY;
//							//-------------------------------------
//							RemovePiece(pos,sq2);
//							NotNum++;
//						}
//						if(IsWhite(chess1) && chess2 != BCHE ){
//							//Not256Pos[NotNum] = sq1;
//							//------------------------------------
//							NotList[NotNum]  = sq1;
//							NotBoard[NotNum] = pos->b256[sq1];  //����һ������
//							pos->b256[sq1]   = EMPTY;
//							//-------------------------------------
//							RemovePiece(pos,sq1);
//							NotNum++;
//						}
//					}
//				}
//			}		
//		}
//
//		//�����ж�һ��
//
//		psmv = RankMove(kx,pos->wBitRanks[ky]);
//
//		sq1 = psmv->RookCap[DLoRight] + ky4;
//		if(sq1 != king){
//			
//			sq2 = psmv->CannonCap[DLoRight] + ky4;
//
//			if(sq2 != king){
//				int chess1 = pos->b256[sq1];
//				int chess2 = pos->b256[sq2];
//				
//				if(chess2 == BCHE){
//					if(IsWhite(chess1)){
//						//Not256Pos[NotNum] = sq1;
//						//------------------------------------
//						NotList[NotNum]  = sq1;
//						NotBoard[NotNum] = pos->b256[sq1];  //����һ������
//						pos->b256[sq1]   = EMPTY;
//						//-------------------------------------
//						RemovePiece(pos,sq1);
//						NotNum++;
//					}
//				}
//
//				sq3 = psmv->SuperCap[DLoRight] + ky4;
//				if(sq3 != king){
//					int chess3 = pos->b256[sq3];
//					if(chess3 == BPAO){
//						if(IsWhite(chess2)){
//							//Not256Pos[NotNum] = sq2;
//							//------------------------------------
//							NotList[NotNum]  = sq2;
//							NotBoard[NotNum] = pos->b256[sq2];  //����һ������
//							pos->b256[sq2]   = EMPTY;
//							//-------------------------------------
//							RemovePiece(pos,sq2);
//							NotNum++;
//						}
//						if(IsWhite(chess1) && chess2 != BCHE ){
//							//Not256Pos[NotNum] = sq1;
//							//------------------------------------
//							NotList[NotNum]  = sq1;
//							NotBoard[NotNum] = pos->b256[sq1];  //����һ������
//							pos->b256[sq1]   = EMPTY;
//							//-------------------------------------
//							RemovePiece(pos,sq1);
//							NotNum++;
//						}
//					}
//				}
//			}		
//		}
//
//		//�ٿ�һ����
//		 //�ж�һ����û�����ڽ�����
//        for(int checkSq256 = PieceListStart(pos,BMA); checkSq256 > 0x32; checkSq256 = NextPiece(pos,checkSq256)){
//			int x   = horseLegTab(king - checkSq256 + 256);
//			int leg256 = checkSq256 + x;
//
//			if(x){
//				int leg14 = pos->b256[leg256];
//
//				if(IsWhite(leg14)){
//					//���ж�һ��,�ǲ����Ѿ�������
//					BOOL isRemove = FALSE;
//					for(int i = 0; i < NotNum; i++){
//						if(leg256 == NotList[i]){
//							isRemove = TRUE;
//							break;
//						}
//					}
//					//Not48Pos[NotNum]        = leg48;
//					if(isRemove == FALSE){
//						//Not256Pos[NotNum]       = leg256;
//						//------------------------------------
//						NotList[NotNum]  = leg256;
//						NotBoard[NotNum] = pos->b256[leg256];  //����һ������
//						pos->b256[leg256]   = EMPTY;
//						//-------------------------------------
//						RemovePiece(pos, leg256);
//						NotNum++;
//					}
//				}
//			}
//		}
//
//        // ���췽��������ȥ�� End
//		//////////////////////////////////////////////////////////////////////////////
//
//
//		psmv = FileMove(toy,tof);
//		//�õ������һ��
//		tmp = psmv->RookCap[DUpLeft] + tox;
//		if(tmp != to){ 
//
//			switch(pos->b256[tmp]){
//				case RCHE:  //�쳵
//					attacker = tmp;
//					goto CanEatBack;
//					break;
//				case RKING: //��˧
//					if(tmp+16 == to && toy > 0x9){
//						attacker = tmp;
//						goto CanEatBack;
//					}
//					break;				
//				default:
//					break;
//			}
//
//			//���˵�һ�����еڶ�������
//			tmp = psmv->CannonCap[DUpLeft] + tox;
//			if(tmp != to){
//				int c14 = pos->b256[tmp];
//				if(c14 == RPAO){
//					attacker = tmp;
//					goto CanEatBack;
//				}				
//			}
//		}
//		//�õ�to�������һ��������
//		tmp = psmv->RookCap[DLoRight] + tox;
//		if(tmp != to){   
//
//			switch(pos->b256[tmp]){
//				case RCHE:
//					attacker = tmp;
//					goto CanEatBack;
//					break;
//				
//				case RKING:
//					if(tmp-16 == to && toy > 0x9){
//						attacker = tmp;
//						goto CanEatBack;
//					}
//					break;
//				
//				case RPAWN:
//					if(tmp-16 == to){
//						attacker = tmp;
//					    goto CanEatBack;
//					}
//					break;
//
//				default:
//					break;
//			} 
//
//			//���˵�һ�����еڶ�������
//			tmp = psmv->CannonCap[DLoRight] + tox;
//			if(tmp != to ){
//				int c14 = pos->b256[tmp];
//				if(c14 == RPAO){
//					attacker = tmp;
//					goto CanEatBack;
//				}				
//			}
//		}
//		//�õ�to�����ҵ���Ϣ
//		//psmv = smvRankMoveTab[tox-3] + tor; 
//
//		psmv = RankMove(tox,tor);
//		//�õ�to����ĵ�һ������
//		tmp = psmv->RookCap[DUpLeft] + nDisp;
//		if(tmp != to){ 
//
//			switch(pos->b256[tmp]){
//				 case RCHE:
//					 attacker = tmp;
//					 goto CanEatBack;
//					 break;
//				
//				 case RKING:
//					 if((inBoard(to) & IN_RKING) && tmp+1 == to){
//						 attacker = tmp;
//						 goto CanEatBack;
//					 }
//					 break;
//				 
//				 case RPAWN:
//					 if(toy < 0x8 && tmp+1 == to){
//						 attacker = tmp;
//						 goto CanEatBack;
//					 }
//					 break;
//
//				 default:
//					 break;                
//			}  
//
//			//���˵�һ����,���еڶ�����
//			tmp = psmv->CannonCap[DUpLeft] + nDisp;
//			if(tmp != to){
//				int c14 = pos->b256[tmp];
//				if(c14 == RPAO){
//					attacker = tmp;
//					goto CanEatBack;
//				}			
//			}
//		}
//		//�õ�to����ĵ�һ������
//		tmp = psmv->RookCap[DLoRight] + nDisp;
//		if(tmp != to){
//
//			switch(pos->b256[tmp]){
//				case RCHE:
//					attacker = tmp;
//					goto CanEatBack;
//					break;
//				
//				case RKING:
//					if((inBoard(to) & IN_RKING) && tmp-1 == to){
//						attacker = tmp;
//					    goto CanEatBack;
//					}
//					break;
//				
//				case RPAWN:
//					if(toy < 0x8 && tmp-1 == to){
//						attacker = tmp;
//					    goto CanEatBack;
//					}
//					break;
//
//				default:
//					break;
//			}
//
//			//���˵�һ����,���еڶ�����
//			tmp = psmv->CannonCap[DLoRight] + nDisp;
//			if(tmp != to ){
//				int c14 = pos->b256[tmp];
//				if(c14 == RPAO){
//					attacker = tmp;
//					goto CanEatBack;
//				}				           
//			}
//		}
//
//		//����
//		if(inBoard(to) & IN_RSHI){
//			for(int at = PieceListStart(pos,RSHI); at > 0x32; at = NextPiece(pos,at)){
//				//if(at != from && shortDir(at-to+256) == 1){
//				/*if(at != from && (GetDir(at,to) & DirShi)){*/
//				if((GetDir(at,to) & DirShi)){
//					attacker = at;
//					goto CanEatBack;
//				}
//			}
//		}
//		//����
//		if(inBoard(to) & IN_RXIANG){
//			for(int at = PieceListStart(pos,RXIANG); at > 0x32; at = NextPiece(pos,at)){
//				/*if(at != from && (GetDir(at,to) & DirXiang) && pos->b256[(at+to)/2] == EMPTY){*/
//				if((GetDir(at,to) & DirXiang) && pos->b256[(at+to)/2] == EMPTY){
//					attacker = at;
//					goto CanEatBack;
//				}
//			}
//		}
//
//
//		//����
//		for(int at = PieceListStart(pos,RMA); at > 0x32; at = NextPiece(pos,at)){
//			//if(at != from){
//			int m = horseLegTab(to-at+256);
//			if(m && !pos->b256[at+m]){
//				attacker = at;
//				goto CanEatBack;
//			}
//			//}
//		}
//	}
//	//**************************************************************************
//
//	//�ȵûָ�һ��,
//	/////////////////////////////////////////////////////////////////////////////////////
//	//����������ӻָ�һ��
//	for(int i=0; i<NotNum; i++){
//        int sq = NotList[i];
//		//
//		pos->b256[sq] = NotBoard[i];
//		//
//        InsertPiece(pos,pos->b256[sq], sq);
//
//        ASSERT(NextPiece(pos,PieceListStart(pos,pos->b256[sq])) != sq);
//    }
//	/////////////////////////////////////////////////////////////////////////////////////
//
//	// PIECE_ID(pos->b256[attacker]);
//	
//	
//	//�ٿ�һ��
//
//	////********************************************************************
//	//if(moveChessId == to_id ){
//	//	//�ٿ�һ��, to_id �ǲ��ǲ��ܶ�,������ܶ�,����true;
//
//	//	BOOL canMove = TRUE;
//	//	for(int i = 0; i < NotNum; i++){
//	//		if(to == NotList[i]){
//	//			canMove = FALSE;
//	//			break;
//	//		}
//	//	}
//
//	//	//�����Ҫ��һ���ǲ����ߵ���ͬ����
//
//	//	if(canMove){
//	//		return FALSE;
//	//	}
//	//}
//	////**********************************************************************
//	//else 
//	if(at_id == to_id){
//
//		//��һ��to_id �ܲ�����
//
//
//		for(int i=0; i<NotNum; i++){
//			//int sq = NotList[i];
//			////
//			//pos->b256[sq] = NotBoard[i];
//			////
//			//InsertPiece(pos,pos->b256[sq], sq);
//
//			//ASSERT(NextPiece(pos,PieceListStart(pos,pos->b256[sq])) != sq);
//
//			if(NotList[i] == to){
//				goto IsCanReturnTrue;
//			}
//		}
//
//		return FALSE;
//	}
//
//	//if(alwaysCap == TRUE){
//
//	//}
//	//else{
//	//	if( 1 & n){
//	//		nOppChecks = 0;
//	//	}
//	//	else{
//	//		nOwnChecks = 0;
//	//	}										
//	//}
//
//	//
//	//if( 1 & n){
//	//	if(pos->OwnLastCapChess
//	//}
//	//else{
//	//}
//IsCanReturnTrue:	
//
//
//	//int    LastCapChess[2];              //���һ�γԵ�����
//	//int    last_att_sq[2];               //���һ�ι�����λ��256
//	//int    last_move_to[2];              //���һ�ζԷ��ߵĸ���
//
//	int last_id  = pos->LastCapChess[which];
//	//int last_to  = pos->last_att_sq[which];
//
//	int last_from = pos->last_from[which];
//	int last_to   = pos->last_to[which];
//
//
//	//int    LastCapChess[2];              //���һ�γԵ�����
//	//int    last_from[2];                 //���һ�ζԷ�from
//	//int    last_to[2];                   //���һ�ζԷ�to
//	//int    last_Att[2];                  //���һ�ι�����λ��256
//
//	pos->LastCapChess[which] = to_id;
//	//pos->last_att_sq[which]  = to;
//
//	pos->last_to[which]      = to;
//	pos->last_from[which]    = from;
//
//	if(last_id == EMPTY){
//		return TRUE;
//	}
//	else if(last_id == to_id){  //������ܻ�Ҫ�ж�һ���ǲ��ǳԵ�ͬһ������,�����ƶ����Ǹ�
//
//		if(last_from == to){       
//		   return TRUE;
//		}
//
//		if(last_to == to){
//			return TRUE;
//		}
//
//		//if(last_att == to){     //�ÿ��ڳ��򲻶�������
//		//	return TRUE;
//		//}
//
//		//if(last_to == to){      //��׽�Է��ߵ�����
//
//		//	return TRUE;
//		//}
//	}
//	
//	return FALSE;
//	
//
//	//return TRUE;
//
//
//	////////////////////////////////////////////////////////////////////////////////////////
//	// �ܳԻ���
//CanEatBack:
//
//	//�ȵûָ�һ��,
//	/////////////////////////////////////////////////////////////////////////////////////
//	//����������ӻָ�һ��
//	for(int i=0; i<NotNum; i++){
//        int sq = NotList[i];
//		//
//		pos->b256[sq] = NotBoard[i];
//		//
//        InsertPiece(pos,pos->b256[sq], sq);
//
//        ASSERT(NextPiece(pos,PieceListStart(pos,pos->b256[sq])) != sq);
//    }
//	/////////////////////////////////////////////////////////////////////////////////////
//	return FALSE;
//
//}
//
