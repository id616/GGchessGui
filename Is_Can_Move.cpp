#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"


BOOL Is_Can_Move_To_Eat(position_t *pos,int from, int to){

    int tmp;

	int fx      = StoX(from);
    int fy      = StoY(from);

	int tx      = StoX(to);
    int ty      = StoY(to);

	int kpos;

	if(IsWhite(pos->b256[from])){
		if(pos->b256[from] != RKING){
			kpos = PieceListStart(pos,RKING);
		}
		else{
			kpos = to;
		}
	}
	else{
		if(pos->b256[from] != BKING){
		    kpos = PieceListStart(pos,BKING);
		}
		else{
			kpos = to;
		}
	}

	int kx       = StoX(kpos);
    int ky       = StoY(kpos);

    int kr       = pos->wBitRanks[ky];
    int kf       = pos->wBitFiles[kx];

    int tr       = pos->wBitRanks[ty];
    int tf       = pos->wBitFiles[tx];        //



	if(IsWhite(pos->b256[from])){          //�жϺ���ܲ�������
		// a, �ڽ����������ϵ����Ӳ�����, ������ǳ��Ǹ���Ϳ���
		//for(tmp = PieceListStart(pos,BMA); tmp > 0x32; tmp = NextPiece(pos,tmp)){
		//	int m = horseLegTab(kpos-tmp+256);
		//	if(m){
		//		if((tmp+m)==from && to != tmp){
		//			return FALSE;
		//		}
		//	}
		//}
		// 2, ����һ��FR		
		if(tx == kx){
			kf |= yBitMask(to);
		}
		if(ty == ky){
			kr |= xBitMask(to);
		}
		if(fx == kx){
			kf ^= yBitMask(from);
		}
		if(fy == ky){
			kr ^= xBitMask(from);
		}

		SlideMaskStruct *psmsRank = RankMask(kx,kr);
        SlideMaskStruct *psmsFile = FileMask(ky,kf);

		//�ټ���һ��, ��,��,���ܲ��ܽ�, ����ü��Ͻ���
		for(tmp = PieceListStart(pos,BCHE); tmp > 0x32; tmp = NextPiece(pos,tmp)){
			if(tmp != to){
				int x = StoX(tmp);
				int y = StoY(tmp);
				if(x == kx){
					if(psmsFile->RookCap & yBitMask(tmp)){
						return (FALSE);
					}					
				}
				else if(y == ky){
					if(psmsRank->RookCap & xBitMask(tmp)){
						return (FALSE);
					}					
				}
			}
		}
		//�ټ���һ����
		for(tmp = PieceListStart(pos,BPAO); tmp > 0x32; tmp = NextPiece(pos,tmp)){
			if(tmp != to){
				int x = StoX(tmp);
				int y = StoY(tmp);
				if(x == kx){
					if(psmsFile->CannonCap & yBitMask(tmp)){
						return (FALSE);
					}					
				}
				else if(y == ky){
					if(psmsRank->CannonCap & xBitMask(tmp)){
						return (FALSE);
					}					
				}
			}
		}
		//�ټ���һ���ǲ��ǶԽ���
		tmp = PieceListStart(pos,BKING);
		if(StoX(tmp) == kx){
			if(psmsFile->RookCap & yBitMask(tmp)){
				return (FALSE);
			}
		}

		/*for(tmp = PieceListStart(pos,BMA); tmp > 0x32 && to != tmp; tmp = NextPiece(pos,tmp)){*/
		for(tmp = PieceListStart(pos,BMA); tmp > 0x32 ; tmp = NextPiece(pos,tmp)){

			if(to != tmp){
				int m = horseLegTab(kpos-tmp+256);
				if(m){
					//if((tmp+m)==from && to != tmp){
					//	return FALSE;
					//}

					//if(!pos->b256[tmp+m]){   //������û������
					//	return FALSE;
					//}

					if(from == tmp + m){
						return false;
					}
				}
			}
		}
	}
	else{                                  //�жϺڵ��ܲ�������
		//for(tmp = PieceListStart(pos,RMA); tmp > 0x32; tmp = NextPiece(pos,tmp)){
		//	int m = horseLegTab(kpos-tmp+256);
		//	if(m){   //��������ڽ���
		//		//if((tmp+m)==from && to != tmp){
		//		//	return FALSE;  //�ں���Ľ����Ľ��ϵ��岻����
		//		//}
		//		if(!pos->b256[tmp+m]){   //������û������
		//		}
		//		else if((tmp+m)==from && to != tmp){
		//			return FALSE;
		//		}
		//	}
		//}
		// 2, ����һ��FR
		if(tx == kx){
			kf |= yBitMask(to);
		}
		if(ty == ky){
			kr |= xBitMask(to);
		}
		if(fx == kx){
			kf ^= yBitMask(from);
		}
		if(fy == ky){
			kr ^= xBitMask(from);
		}

		SlideMaskStruct *psmsRank = RankMask(kx,kr);
		SlideMaskStruct *psmsFile = FileMask(ky,kf);

		for(tmp = PieceListStart(pos,RCHE); tmp > 0x32; tmp = NextPiece(pos,tmp)){
			if(tmp != to){
				int x = StoX(tmp);
				int y = StoY(tmp);
				if(x == kx){
					if(psmsFile->RookCap & yBitMask(tmp)){
						return (FALSE);
					}
				}
				else if(y == ky){
					if(psmsRank->RookCap & xBitMask(tmp)){
						return (FALSE);
					}
				}
			}
		}

		for(tmp = PieceListStart(pos,RPAO); tmp > 0x32; tmp = NextPiece(pos,tmp)){
			if(tmp != to){
				int x = StoX(tmp);
				int y = StoY(tmp);
				if(x == kx){
					if(psmsFile->CannonCap & yBitMask(tmp)){
						return (FALSE);
					}
				}
				else if(y == ky){
					if(psmsRank->CannonCap & xBitMask(tmp)){
						return (FALSE);
					}
				}
			}
		}

		tmp = PieceListStart(pos,RKING);
		if(StoX(tmp) == kx){
			if(psmsFile->RookCap & yBitMask(tmp)){
				return (FALSE);
			}
		}

		/*for(tmp = PieceListStart(pos,RMA); tmp > 0x32 && to != tmp; tmp = NextPiece(pos,tmp)){*/
		for(tmp = PieceListStart(pos,RMA); tmp > 0x32 ; tmp = NextPiece(pos,tmp)){
            
			if(to != tmp){

				int m = horseLegTab(kpos-tmp+256);
				if(m){   //��������ڽ���
					//if((tmp+m)==from && to != tmp){
					//	return FALSE;  //�ں���Ľ����Ľ��ϵ��岻����
					//}
					//if(!pos->b256[tmp+m]){   //������û������
					//	return FALSE;
					//}

					if(from == tmp + m){
						return false;
					}

					//if((tmp+m)==from && to != tmp){
					//	return FALSE;
					//}
				}
			}
		}
	}

	return TRUE;
}

