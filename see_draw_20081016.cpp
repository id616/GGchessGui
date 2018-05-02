#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"

BOOL see_draw_20081016(position_t *pos,int mfrom,int mto, int from, int to, int which){

	pos->cap_num[0][which] = 0;
	pos->isTrueCap         = false;

	//��ǰ�Ǻڷ�������
	if(which == WHITE){   //************************************//
		//1,�ҷ��ı�,����Ҫ��׽.
		//2,��һ���ǲ����ҷ��ĳ���׽, �����ڳ��ĳ��Ӳ�
        //�ڳ�
        for(int cap = PieceListStart(pos,BCHE); cap > 0x32; cap = NextPiece(pos,cap)){

            //int tmp = MOVE_capFC(cap,RCHE);
            int x   = StoX(cap);
            int y   = StoY(cap);

            //������Ӳ�
            int nDisp;
            SlideMoveStruct* psmv;

            nDisp = cap & 0xf0;            

			int becap;

			//��������Ǻ�����
			if(StoY(mfrom) != StoY(mto) || mto != cap){
				psmv = RankMove(x,pos->wBitRanks[y]);
				becap = psmv->RookCap[DUpLeft] + nDisp;            
				if(becap != cap){                
					if(IsWhite(pos->b256[becap])){
						if(isFourTypeChess(pos,mfrom,mto,cap,becap,which)){
							test_Is_True_Cap(pos,cap,becap,from,to,which);
						}
					}
				}
				becap = psmv->RookCap[DLoRight] + nDisp;
				if(becap != cap){                
					if(IsWhite(pos->b256[becap])){
						if(isFourTypeChess(pos,mfrom,mto,cap,becap,which)){
							test_Is_True_Cap(pos,cap,becap,from,to,which);
						}
					}
				}
			}

            //������Ӳ�
			//���������������
			if(StoX(mfrom) != StoX(mto) || mto != cap){
				psmv   = FileMove(y,pos->wBitFiles[x]);
				becap = psmv->RookCap[DUpLeft] + x;
				if(becap != cap){                
					if(IsWhite(pos->b256[becap])){
						if(isFourTypeChess(pos,mfrom,mto,cap,becap,which)){
							test_Is_True_Cap(pos,cap,becap,from,to,which);
						}
					}
				}
				becap = psmv->RookCap[DLoRight] + x;
				if(becap != cap){                
					if(IsWhite(pos->b256[becap])){
						if(isFourTypeChess(pos,mfrom,mto,cap,becap,which)){
							test_Is_True_Cap(pos,cap,becap,from,to,which);
						}
					}
				}
			}
         }

		//����
        for(int cap = PieceListStart(pos,BPAO); cap > 0x32; cap = NextPiece(pos,cap)){

            //int tmp = MOVE_capFC(cap,RPAO);
            int x   = StoX(cap);
            int y   = StoY(cap);

            int nDisp;
            SlideMoveStruct* psmv;

            nDisp = cap & 0xf0;
			int becap;

			//fen 1rb1ka3/4a4/2C1b4/p3p3p/9/2p3P2/P3P3P/N3C1N2/1c2A4/1RBAKR1rc b - - 20 20 
			//�����Ҫ�� mto != cap

			//����ڲ��Ǻ�����,�ÿ�����Ҳ���ܺ�������
			if(StoY(mfrom) != StoY(mto)){
				psmv  = RankMove(x,pos->wBitRanks[y]);
				becap = psmv->CannonCap[DUpLeft] + nDisp;            
				if(becap != cap){                
					if(IsWhite(pos->b256[becap])){
						if(isFourTypeChess(pos,mfrom,mto,cap,becap,which)){
							test_Is_True_Cap(pos,cap,becap,from,to,which);
						}
					}
				}

				becap = psmv->CannonCap[DLoRight] + nDisp;
				if(becap != cap){                
					if(IsWhite(pos->b256[becap])){
						if(isFourTypeChess(pos,mfrom,mto,cap,becap,which)){
							test_Is_True_Cap(pos,cap,becap,from,to,which);
						}
					}
				}
			}

			//����ڲ���������,�ÿ�����Ҳ������������
			if(StoX(mfrom) != StoX(mto)){
				//������Ӳ�
				psmv = FileMove(y,pos->wBitFiles[x]);
				becap = psmv->CannonCap[DUpLeft] + x;
				if(becap != cap){                
					if(IsWhite(pos->b256[becap])){
						if(isFourTypeChess(pos,mfrom,mto,cap,becap,which)){
							test_Is_True_Cap(pos,cap,becap,from,to,which);
						}
					}
				}

				becap = psmv->CannonCap[DLoRight] + x;
				if(becap != cap){                
					if(IsWhite(pos->b256[becap])){
						if(isFourTypeChess(pos,mfrom,mto,cap,becap,which)){
							test_Is_True_Cap(pos,cap,becap,from,to,which);
						}
					}
				}
			}
        }


		//����
        for(int cap = PieceListStart(pos,BMA); cap > 0x32; cap = NextPiece(pos,cap)){

            //int tmp      = MOVE_capFC(cap,BMA);
            uint8* lpDst = PreMaAndLegMove[cap];
			while(int becap = *lpDst++){ 
				if(pos->b256[*lpDst] == 0){ //����û����
					if(IsWhite(pos->b256[becap])){
						if(isFourTypeChess(pos,mfrom,mto,cap,becap,which)){
							test_Is_True_Cap(pos,cap,becap,from,to,which);
						}
					}
				}
                lpDst++;
            }
		}
		//����������߲�
		for(int cap = PieceListStart(pos,BXIANG); cap > 0x32; cap = NextPiece(pos,cap)){
			//int      tmp = MOVE_capFC(cap,BXIANG);
			uint8* lpDst = PreShiXiangAndEyeMove[cap];
			while(int becap = *lpDst++){
				if(pos->b256[*lpDst] == 0){    //����û����
					if(IsWhite(pos->b256[becap])){
						if(isFourTypeChess(pos,mfrom,mto,cap,becap,which)){
							test_Is_True_Cap(pos,cap,becap,from,to,which);
						}
					}
				}
				lpDst++;
			}
		}

		//��ʿ�������߲�
		for(int cap = PieceListStart(pos,BSHI); cap > 0x32; cap = NextPiece(pos,cap)){
			//int      tmp = MOVE_capFC(cap,BSHI);
			uint8* lpDst = PreShiXiangAndEyeMove[cap];
			while(int becap = *lpDst++){
				if(IsWhite(pos->b256[becap])){
					if(isFourTypeChess(pos,mfrom,mto,cap,becap,which)){
						test_Is_True_Cap(pos,cap,becap,from,to,which);
					}
				}
			}
		}
	}
	//��ǰ�Ǻ췽������
	else{		
		 //�쳵
        for(int cap = PieceListStart(pos,RCHE); cap > 0x32; cap = NextPiece(pos,cap)){

            //int tmp = MOVE_capFC(cap,RCHE);
            int x   = StoX(cap);
            int y   = StoY(cap);

            //������Ӳ�
            int nDisp;
            SlideMoveStruct* psmv;
			int becap;
            nDisp = cap & 0xf0;

			//������Ǻ�����,�ÿ�����Ҳ���ܺ�������
			if(StoY(mfrom) != StoY(mto) || mto != cap){
				psmv = RankMove(x,pos->wBitRanks[y]);
				becap = psmv->RookCap[DUpLeft] + nDisp;            
				if(becap != cap){                
					if(IsBlack(pos->b256[becap])){
						if(isFourTypeChess(pos,mfrom,mto,cap,becap,which)){
							test_Is_True_Cap(pos,cap,becap,from,to,which);
						}
					}
				}
				becap = psmv->RookCap[DLoRight] + nDisp;
				if(becap != cap){                
					if(IsBlack(pos->b256[becap])){
						if(isFourTypeChess(pos,mfrom,mto,cap,becap,which)){
							test_Is_True_Cap(pos,cap,becap,from,to,which);
						}
					}
				}
			}

			//������Ǻ�����,�ÿ�����Ҳ���ܺ�������
			if(StoX(mfrom) != StoX(mto) || mto != cap){
				//������Ӳ�
				psmv   = FileMove(y,pos->wBitFiles[x]);
				becap = psmv->RookCap[DUpLeft] + x;
				if(becap != cap){                
					if(IsBlack(pos->b256[becap])){
						if(isFourTypeChess(pos,mfrom,mto,cap,becap,which)){
							test_Is_True_Cap(pos,cap,becap,from,to,which);
						}
					}
				}
				becap = psmv->RookCap[DLoRight] + x;
				if(becap != cap){                
					if(IsBlack(pos->b256[becap])){
						if(isFourTypeChess(pos,mfrom,mto,cap,becap,which)){
							test_Is_True_Cap(pos,cap,becap,from,to,which);
						}
					}
				}
			}
         }

		//����
        for(int cap = PieceListStart(pos,RPAO); cap > 0x32; cap = NextPiece(pos,cap)){

            //int tmp = MOVE_capFC(cap,RPAO);
            int x   = StoX(cap);
            int y   = StoY(cap);

            int nDisp;
            SlideMoveStruct* psmv;
            nDisp = cap & 0xf0;
            int becap;

			//������Ǻ�����,�ÿ�����Ҳ���ܺ�������
			if(StoY(mfrom) != StoY(mto)){
				psmv  = RankMove(x,pos->wBitRanks[y]);
				becap = psmv->CannonCap[DUpLeft] + nDisp;            
				if(becap != cap){                
					if(IsBlack(pos->b256[becap])){
						if(isFourTypeChess(pos,mfrom,mto,cap,becap,which)){
							test_Is_True_Cap(pos,cap,becap,from,to,which);
						}
					}
				}

				becap = psmv->CannonCap[DLoRight] + nDisp;
				if(becap != cap){                
					if(IsBlack(pos->b256[becap])){
						if(isFourTypeChess(pos,mfrom,mto,cap,becap,which)){
							test_Is_True_Cap(pos,cap,becap,from,to,which);
						}
					}
				}
			}

			//������Ǻ�����,�ÿ�����Ҳ���ܺ�������
			if(StoX(mfrom) != StoX(mto)){
				//������Ӳ�
				psmv = FileMove(y,pos->wBitFiles[x]);
				becap = psmv->CannonCap[DUpLeft] + x;
				if(becap != cap){                
					if(IsBlack(pos->b256[becap])){
						if(isFourTypeChess(pos,mfrom,mto,cap,becap,which)){
							test_Is_True_Cap(pos,cap,becap,from,to,which);
						}
					}
				}
				becap = psmv->CannonCap[DLoRight] + x;
				if(becap != cap){                
					if(IsBlack(pos->b256[becap])){
						if(isFourTypeChess(pos,mfrom,mto,cap,becap,which)){
							test_Is_True_Cap(pos,cap,becap,from,to,which);
						}
					}
				}
			}
        }


		//����
        for(int cap = PieceListStart(pos,RMA); cap > 0x32; cap = NextPiece(pos,cap)){

            //int tmp      = MOVE_capFC(cap,RMA);
            uint8* lpDst = PreMaAndLegMove[cap];
			while(int becap = *lpDst++){ 
				if(pos->b256[*lpDst] == 0){ //����û����
					if(IsBlack(pos->b256[becap])){
						if(isFourTypeChess(pos,mfrom,mto,cap,becap,which)){
							test_Is_True_Cap(pos,cap,becap,from,to,which);
						}
					}
				}
                lpDst++;
            }
		}
		 //����������߲�
		for(int cap = PieceListStart(pos,RXIANG); cap > 0x32; cap = NextPiece(pos,cap)){
			//int      tmp = MOVE_capFC(cap,RXIANG);
			uint8* lpDst = PreShiXiangAndEyeMove[cap];
			while(int becap = *lpDst++){
				if(pos->b256[*lpDst] == 0){    //����û����
					if(IsBlack(pos->b256[becap])){
						if(isFourTypeChess(pos,mfrom,mto,cap,becap,which)){
							test_Is_True_Cap(pos,cap,becap,from,to,which);
						}
					}
				}
				lpDst++;
			}
		}

		//��ʿ�������߲�
		for(int cap = PieceListStart(pos,RSHI); cap > 0x32; cap = NextPiece(pos,cap)){
			//int      tmp = MOVE_capFC(cap,RSHI);
			uint8* lpDst = PreShiXiangAndEyeMove[cap];
			while(int becap = *lpDst++){
				if(IsBlack(pos->b256[becap])){
					if(isFourTypeChess(pos,mfrom,mto,cap,becap,which)){
						test_Is_True_Cap(pos,cap,becap,from,to,which);
					}
				}
			}
		}	
	}

	//���е�׽���б���, ���ϴε����е�׽�ȶ�һ��, ����ж�ͬһ��ID��,����׽.
	//����ж�����׽��, Ҫ�����ж��Ǹ�׽, ����������.
	//fen 3a1kb2/2r6/4ba3/p6Np/9/P3p1RcP/9/4B4/4A4/2BK1A3 b - - 53 53 
	//fen r2akab2/1c7/2n1b1c2/p1R1p3p/5nr2/9/P3P2NP/1CN1C4/5R3/2BAKAB2 b - - 16 16 

    int this_num = pos->cap_num[0][which];

	while(this_num > 0){  //������׽
		this_num --;
		int n_to_id			= pos->LastCapChess		 [this_num][0][which];	
		int n_last_to		= pos->last_to           [this_num][0][which];
		int last_num   = pos->cap_num[1][which];

		if(last_num == 0){
			pos->isTrueCap = true;
		}
		else{
			while(last_num > 0){
				last_num --;
				//int last_id      = pos->LastCapChess		[last_num][1][which];
				if(pos->LastCapChess[last_num][1][which] == n_to_id){
					//fen 3a5/9/4k4/3N1n3/9/3C2B2/3c5/4B4/2C1A4/4K4 w - - 13 13 
					if(pos->last_to[last_num][1][which] == n_last_to){
						pos->isTrueCap = true;  //���һ�����ÿ��ڵ�׽
					}
					if(pos->last_ot_from[last_num][1][which] == n_last_to){
						pos->isTrueCap = true;						  
					}
				}
			}
		}
	}	

	for(int i = 0;  i < pos->cap_num[0][which]; i++){
		pos->LastCapChess[i][1][which]	= pos->LastCapChess[i][0][which];

		pos->last_ot_from[i][1][which]  = pos->last_ot_from[i][0][which];
		//pos->last_ot_to[i][1][which]    = pos->last_ot_to[i][0][which];

		pos->last_to     [i][1][which]  = pos->last_to     [i][0][which];
	}

	pos->cap_num[1][which] = pos->cap_num[0][which]; 

	return pos->isTrueCap;
}



//enum  {
//       EMPTY=0,
//       RKING=1,  RSHI=2,RXIANG=3, RMA=4, RCHE=5, RPAO=6, RPAWN=7,
//       BKING=8,  BSHI=9,BXIANG=10,BMA=11,BCHE=12,BPAO=13,BPAWN=14,
//       EMPTY16=16, OUTSIDE=32};