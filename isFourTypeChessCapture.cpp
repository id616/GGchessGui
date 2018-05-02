#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"


//cap ��׽����, becap, ��׽����.
BOOL isFourTypeChess(position_t *pos,int mfrom,int mto, int cap, int becap, int which){

	int rk = PieceListStart(pos,RKING);
	int bk = PieceListStart(pos,BKING);	

	//��ǰ�Ǻڷ�������
	if(which == WHITE){	

		if(pos->b256[becap]== RPAWN){   //��׽�����ӵı�����׽
			if(StoY(becap) >= 0x8) return false;
		}

		//*****************************************************************************
		//1, �ߵ���ֱ��ȥ׽�Է��ߵ��ӣ�(�Է��ض����߶����Ǹ���)
		if(cap == mto) return TRUE;
		//*****************************************************************************
		//2, �ÿ����ҷ����ڼ�,����,����,ȥ׽�Է�����.(�Է����ܲ���,���ܶ�)
		//   cap ԭ�����ڼ�,���ߵ����ڼ���
		if(pos->b256[cap] == BPAO){  //׽�Ե�������
			if(false){
			}
			else if(StoX(cap) == StoX(becap)){ //��ͬһ��
				if(false){
				}
				else if(StoX(mfrom) == StoX(cap)){  //�뿪������׽
					if(false){
					}
					else if(becap > cap){
						if(mfrom < becap && mfrom > cap) return TRUE;
					}
					else if(becap < cap){
						if(mfrom > becap && mfrom < cap) return TRUE;
					}
				}
				else if(StoX(mto)   == StoX(cap)){  //��ȥ������׽
					if(false){
					}
					else if(becap > cap){
						if(mto < becap && mto > cap) return TRUE;
					}
					else if(becap < cap){
						if(mto > becap && mto < cap) return TRUE;
					}
				}
			}
			else if(StoY(cap) == StoY(becap)){ //��ͬһ��
				if(false){
				}
				else if(StoY(mfrom) == StoY(cap)){  //�뿪������׽
					if(false){
					}
					else if(becap > cap){
						if(mfrom < becap && mfrom > cap) return TRUE;
					}
					else if(becap < cap){
						if(mfrom > becap && mfrom < cap) return TRUE;
					}
				}
				else if(StoY(mto)   == StoY(cap)){  //��ȥ������׽
					if(false){
					}
					else if(becap > cap){
						if(mto < becap && mto > cap) return TRUE;
					}
					else if(becap < cap){
						if(mto > becap && mto < cap) return TRUE;
					}
				}
			}
		}

		//3, �ÿ��˳�ȥ׽. 
		//fen 3akab2/3n3r1/6c2/pN2p3p/1rb3pn1/2N3P2/4PR2P/1C2B4/4A4/2BAK1R2 w - - 0 0
		if(pos->b256[cap] == BCHE){
			if(false){
			}
			else if(StoX(cap) == StoX(becap)){ //��ͬһ��
				if(false){
				}
				else if(StoX(mfrom) == StoX(cap)){  //�뿪������׽
					if(false){
					}
					else if(becap > cap){
						if(mfrom < becap && mfrom > cap) return TRUE;
					}
					else if(becap < cap){
						if(mfrom > becap && mfrom < cap) return TRUE;
					}
				}
			}
			else if(StoY(cap) == StoY(becap)){ //��ͬһ��
				if(false){
				}
				else if(StoY(mfrom) == StoY(cap)){  //�뿪������׽
					if(false){
					}
					else if(becap > cap){
						if(mfrom < becap && mfrom > cap) return TRUE;
					}
					else if(becap < cap){
						if(mfrom > becap && mfrom < cap) return TRUE;
					}
				}
			}
		}

		if(pos->b256[cap] == BMA){     //׽�Ե�������
			//fen 3ak4/4a2r1/2c1b4/p7p/4nn3/9/P2R4P/5C3/5K3/3A1AB2 r �ÿ�������׽
			//Ҫ��һ���ߵ���,�ǲ����ÿ�������, �ߵ��Ӿ�����
			int tmp = horseLegTab(becap-cap+256);
			if(cap+tmp == mfrom) return TRUE;
            
		}
		if(pos->b256[cap] == BXIANG){  //׽�Ե�������
			//fen Ccbak1br1/1n2a4/7n1/R7p/6p2/2P6/1r2P1P1P/4C1N2/9/2BAK1BR1 r �ÿ�������׽
			if((cap+becap)/2 == mfrom) return TRUE;
		}
		//*****************************************************************************
		//4, �ж϶Է�����ϵ,

		//����ֺü������, ����Ǵ�becap���������,
		//a  ��һ���� becap X1
		//1, �����һ������becap������, ��Ҫ�ж��ǲ��ǶԷ��ÿ���, ���γ� becap pao
		//2, �����һ������becap���ĳ�, ��Ҫ�ж��ǲ��ǶԷ��ó���������, ���γ�che���ܱ��� becap
        
		//b, �ڶ����� becap X1 X2
		//1, �ڶ�����becap����che,��Ҫ�ж��ǲ��ǵ�ס�˶Է���che,�����ڶԷ��ĳ����ܱ��� becap 
		//2, �ڶ�������becap������,��Ҫ�ж��ǲ����öԷ����ڲ�������, ���ܱ���becap��
		
		//c, �������� becap X1 X2 X3
		//1, ֻҪ�ж��ǲ���X1,X2������. �����,�����ߵ��Ƕ�,���öԷ����ڱ�����,Ҳ�ǿ����µ�׽

		//��ֹ�˶Է������߶�,����Է����������ڱ���becap, �������׽.

		//��Ҫ�������ǶԷ�������ԭ���б���. �����ڱ���,����,�ౣ��,
		//****** a,�ж϶Է��ĳ��ı���***********************************************************************************
		for(int protect = PieceListStart(pos,RCHE); protect > 0x32; protect = NextPiece(pos,protect)){
			if(protect != becap){
				if(false){
				}
				else if(StoX(protect) == StoX(becap)){  //�Է��ĳ��뱻�Ե���ͬһ��
					SlideMoveStruct *psmv;
					psmv = FileMove(StoY(protect),pos->wBitFiles[StoX(protect)]);
					if(StoX(mto) == StoX(protect) && StoX(mfrom) != StoX(protect)){
						if(false){
						}
						else if(psmv->CannonCap[DLoRight] + StoX(protect) == becap){
							if(mto > protect && mto < becap) return TRUE;
						}
						else if(psmv->CannonCap[DUpLeft]  + StoX(protect) == becap){
							if(mto < protect && mto > becap) return TRUE;
						}
					}
				}
				else if(StoY(protect) == StoY(becap)){  //�Է��ĳ��뱻�Ե���ͬһ��
					SlideMoveStruct *psmv;
					psmv = RankMove(StoX(protect),pos->wBitRanks[StoY(protect)]);
					//�ӽ�ȥ���2��
					if(StoY(mto)   == StoY(protect) && StoY(mfrom) != StoY(protect)){
						if(false){
						}
						else if(psmv->CannonCap[DLoRight] + (protect & 0xf0) == becap){
							if(mto > protect && mto < becap) return TRUE;
						}
						else if(psmv->CannonCap[DUpLeft]  + (protect & 0xf0) == becap){
							if(mto < protect && mto > becap) return TRUE;
						}
					}
				}
			}
		}
		//****** a,�ж϶Է����ڵı���
		//fen 4kab2/4a4/2n1b4/p1p1c3p/4R4/2P1P4/P5r1P/C3BcN2/5C3/3AKAB2 w - - 0 0
		for(int protect = PieceListStart(pos,RPAO); protect > 0x32 ; protect = NextPiece(pos,protect)){
			if(protect != becap){
				if(false){
				}
				else if(StoX(protect) == StoX(becap)){
					SlideMoveStruct *psmv;
					psmv = FileMove(StoY(protect),pos->wBitFiles[StoX(protect)]);
					//�ӽ�ȥ���2��
					if(StoX(mto)   == StoX(protect) && StoX(mfrom) != StoX(protect)){
						if(false){
						}
						else if(psmv->SuperCap[DLoRight] + StoX(protect) == becap){
							if(mto > protect && mto < becap) return TRUE;
						}
						else if(psmv->SuperCap[DUpLeft]  + StoX(protect) == becap){
							if(mto < protect && mto > becap) return TRUE;
						}
					}
					//�߿������0��
					if(StoX(mfrom) == StoX(protect) && StoX(mto) != StoX(protect)){
						if(false){
						}
						else if(psmv->RookCap[DLoRight] + StoX(protect) == becap){
							if(mfrom > protect && mfrom < becap) return TRUE;
						}
						else if(psmv->RookCap[DUpLeft]  + StoX(protect) == becap){
							if(mfrom < protect && mfrom > becap) return TRUE;
						}
					}
				}
				else if(StoY(protect) == StoY(becap)){
					SlideMoveStruct *psmv;
					psmv = RankMove(StoX(protect),pos->wBitRanks[StoY(protect)]);
					//�ӽ�ȥ���2��
					if(StoY(mto)   == StoY(protect) && StoY(mfrom) != StoY(protect)){
						if(false){
						}
						else if(psmv->SuperCap[DLoRight] + (protect & 0xf0) == becap){
							if(mto > protect && mto < becap) return TRUE;
						}
						else if(psmv->SuperCap[DUpLeft]  + (protect & 0xf0) == becap){
							if(mto < protect && mto > becap) return TRUE;
						}
					}
					//�߿������0��
					if(StoY(mfrom) == StoY(protect) && StoY(mto) != StoY(protect)){
						if(false){
						}
						else if(psmv->RookCap[DLoRight] + (protect & 0xf0) == becap){
							if(mfrom > protect && mfrom < becap) return TRUE;
						}
						else if(psmv->RookCap[DUpLeft]  + (protect & 0xf0) == becap){
							if(mfrom < protect && mfrom > becap) return TRUE;
						}
					}
				}
			}
		}
		//****** b,�ж϶Է�����ı��� fen 3akab2/3n3r1/6c2/pN2p3p/1rb3pn1/2N3P2/4PR2P/1C2B4/4A4/2BAK1R2 w - - 0 0
		for(int protect = PieceListStart(pos,RMA); protect > 0x32 ; protect = NextPiece(pos,protect)){
			if(protect != becap){
				int tmp = horseLegTab(becap-protect+256);
				if(tmp != 0 && protect+tmp == mto) return TRUE; 
			}
		}

		//****** b,�ж϶Է�����ı��� fen 3ak4/4a4/8b/R8/9/9/9/4BA3/N1r1A1n2/2B2K3 b - - 0 0
		for(int protect = PieceListStart(pos,RXIANG); protect > 0x32 ; protect = NextPiece(pos,protect)){
			if(protect != becap){
				if((protect+becap)/2 == mto) return TRUE;
			}
		}
		//*****************************************************************************
		//5,�ͷ����ҷ�����ȥ׽, ���絲�˶Է����ڼ�, �򳵼�.(�Է����ܲ���,���ܶ�), 
		//��Ҫ���������ҷ��������ҷ��Ľ���һ������.���п������ͷ��˵���ȥ׽��.
		//fen CR1akab1r/9/2n1b1n2/2p5p/6p2/2P6/r3P1P1P/4CcN2/9/2BAK1BR1 r
		if(StoX(bk) == StoX(cap) && StoX(bk) == StoX(mto)){ 
			//=======================================================
			//�ҷ��ߵ��ҷ��Ľ���, �����ҷ�ԭ�Ȳ��ܶ�������,�п��ܿ��Զ���.
			//1, ��ס�˶Է�����, �м���3����. 2, ��ס�˶Է��ĳ�, �м���2����. 
            SlideMoveStruct *psmv;
			psmv = FileMove(StoY(mto),pos->wBitFiles[StoX(mto)]);
			//ֻҪ���bk ������Ӿ�����
			int up;
			int low;
			up  = psmv->RookCap[DUpLeft] + StoX(mto);
			if(up != mto){  //��������
				if(up == bk){ //�� mto X X pao 
					low = psmv->SuperCap[DLoRight] + StoX(mto);
					if(pos->b256[low] == RPAO){                                   //�����ʱ�����㳵��Է��Ľ���
						if(cap > bk && cap < low) return TRUE;
					}
				}
				else{
					up = psmv->CannonCap[DUpLeft] + StoX(mto);
					if(up != mto){
						if(up == bk){  //����X��mto X pao 
							low = psmv->CannonCap[DLoRight] + StoX(mto);
							if(pos->b256[low] == RPAO){
								if(cap > bk && cap < low) return TRUE;
							}
						}
						else{
							up = psmv->SuperCap[DUpLeft] + StoX(mto);							
							if(up == bk){
								//��һ��������ǲ��ǶԷ�����
								low = psmv->RookCap[DLoRight] + StoX(mto);
								if(pos->b256[low] == RPAO){ //����X  X mto pao 
									if(cap > bk && cap < low) return TRUE;
								}
							}							
						}
					}					
				}
			}
			//=======================================================
		}
            
		if(StoY(bk) == StoY(cap) && StoY(bk) == StoY(mto)){
			//�������桡�� //�� mto X X pao 
			//=======================================================
			//�ҷ��ߵ��ҷ��Ľ���, �����ҷ�ԭ�Ȳ��ܶ�������,�п��ܿ��Զ���.
			//1, ��ס�˶Է�����, �м���3����. 2, ��ס�˶Է��ĳ�, �м���2����. 
            SlideMoveStruct *psmv;
			psmv = RankMove(StoX(mto),pos->wBitRanks[StoY(mto)]);
			//ֻҪ���bk ������Ӿ����� //�������桡�� //�� mto X X pao 
			int left;
			int right;
			left  = psmv->RookCap[DUpLeft] + (mto & 0xf0);
			if(left != mto){  //��������
				if(left == bk){ //�� mto X X pao 
					right = psmv->SuperCap[DLoRight] + (mto & 0xf0);
					if(pos->b256[right] == RPAO){                                   //�����ʱ�����㳵��Է��Ľ���
						if(cap > bk && cap < right) return TRUE;
					}
				}
				else{
					left = psmv->CannonCap[DUpLeft] + StoX(mto);
					if(left != mto){
						if(left == bk){  //����X��mto X pao 
							right = psmv->CannonCap[DLoRight] + (mto & 0xf0);
							if(pos->b256[right] == RPAO){
								if(cap > bk && cap < right) return TRUE;
							}
						}
						else{
							left = psmv->SuperCap[DUpLeft] + StoX(mto);							
							if(left == bk){
								//��һ��������ǲ��ǶԷ�����
								right = psmv->RookCap[DLoRight] + (mto & 0xf0);
								if(pos->b256[right] == RPAO){ //����X  X mto pao 
									if(cap > bk && cap < right) return TRUE;
								}
							}							
						}
					}					
				}
			}
			//��������
			//=======================================================
			right  = psmv->RookCap[DLoRight] + (mto & 0xf0);
			if(right != mto){  //��������
				if(right == bk){ //pao X X mto �� 
					left = psmv->SuperCap[DUpLeft] + (mto & 0xf0);
					if(pos->b256[left] == RPAO){                                   //�����ʱ�����㳵��Է��Ľ���
						if(cap < bk && cap > left) return TRUE;
					}
				}
				else{
					right = psmv->CannonCap[DLoRight] + StoX(mto);
					if(right != mto){
						if(right == bk){  //pao X mto X �� 
							left = psmv->CannonCap[DUpLeft] + (mto & 0xf0);
							if(pos->b256[left] == RPAO){
								if(cap < bk && cap > left) return TRUE;
							}
						}
						else{
							right = psmv->SuperCap[DLoRight] + StoX(mto);							
							if(right == bk){
								//��һ��������ǲ��ǶԷ�����
								left = psmv->RookCap[DUpLeft] + (mto & 0xf0);
								if(pos->b256[left] == RPAO){  //pao mto X X ��  
									if(cap < bk && cap > left) return TRUE;
								}
							}							
						}
					}					
				}
			}
			//=======================================================
		}
		//6,��ֹ�Է�������ȥ����������׽.
		//ͨ��ǣ�ƶԷ�����,������׽
		//1, ����ߵ�������,
		//if(pos->b256[mto] == BPAO){
		if(false){
		}
		else if(StoX(mto) == StoX(rk) && StoX(mfrom) != StoX(rk)){
			//�õ�mto �����µ�����
			SlideMoveStruct *psmv;
			psmv = FileMove(StoY(mto),pos->wBitFiles[StoX(mto)]);

			if(false){
			}
			else if(StoY(mto) < StoY(rk)){
				if(false){
				}
				else if(pos->b256[mto] == BCHE || pos->b256[mto] == BKING){ //������ü���һ���� :)
					int low2 = psmv->CannonCap[DLoRight] + StoX(mto);
					if(pos->b256[low2] == RKING){
						int low1 = psmv->RookCap[DLoRight] + StoX(mto);
						if(isCanProtect_Last_Move(pos,WHITE,low1,becap)){ //�ҷ����˳�,����ǣ���˶Է�һ����
							return TRUE;
						}
					}
				}
				else if(pos->b256[mto] == BPAO){ 
					int low3 = psmv->SuperCap[DLoRight] + StoX(mto);
					if(pos->b256[low3] == RKING){
						int low1 = psmv->RookCap[DLoRight] + StoX(mto);
						int low2 = psmv->CannonCap[DLoRight] + StoX(mto);
						if(isCanProtect_Last_Move(pos,WHITE,low1,becap)){ //�ҷ����˳�,����ǣ���˶Է�һ����
							return TRUE;
						}
						if(isCanProtect_Last_Move(pos,WHITE,low2,becap)){ //�ҷ����˳�,����ǣ���˶Է�һ����
							return TRUE;
						}
					}
				}
			}
			else if(StoY(mto) > StoY(rk)){
				if(false){
				}
				else if(pos->b256[mto] == BCHE){ 
					int up2 = psmv->CannonCap[DUpLeft] + StoX(mto);
					if(pos->b256[up2] == RKING){
						int up1 = psmv->RookCap[DUpLeft] + StoX(mto);
						if(isCanProtect_Last_Move(pos,WHITE,up1,becap)){ //�ҷ����˳�,����ǣ���˶Է�һ����
							return TRUE;
						}
					}
				}
				//else if(pos->b256[mto] == BPAO){ //���������,û������
				//}
			}
		}
		else if(StoY(mto) == StoY(rk) && StoY(mfrom) != StoY(rk)){
			//�õ�mto �����ҵ�����
			SlideMoveStruct *psmv;
			psmv = RankMove(StoX(mto),pos->wBitRanks[StoY(mto)]);
			if(false){
			}
			else if(StoX(mto) < StoX(rk)){
				if(false){
				}
				else if(pos->b256[mto] == BCHE){
                    int r2 = psmv->CannonCap[DLoRight] + (mto & 0xf0);
					if(pos->b256[r2] == RKING){
						int r1 = psmv->RookCap[DLoRight] + (mto & 0xf0);
						if(isCanProtect_Last_Move(pos,WHITE,r1,becap)){ //�ҷ����˳�,����ǣ���˶Է�һ����
							return TRUE;
						}
					}
				}
				else if(pos->b256[mto] == BPAO){
					int r3 = psmv->SuperCap[DLoRight] + (mto & 0xf0);
					if(pos->b256[r3] = RKING){
						int r1 = psmv->RookCap[DLoRight] + (mto & 0xf0);
						int r2 = psmv->CannonCap[DLoRight] + (mto & 0xf0);
						if(isCanProtect_Last_Move(pos,WHITE,r1,becap)){ //�ҷ����˳�,����ǣ���˶Է�һ����
							return TRUE;
						}
						if(isCanProtect_Last_Move(pos,WHITE,r2,becap)){ //�ҷ����˳�,����ǣ���˶Է�һ����
							return TRUE;
						}
					}
				}
			}
			else if(StoX(mto) > StoX(rk)){
				if(false){
				}
				else if(pos->b256[mto] == BCHE){
                    int l2 = psmv->CannonCap[DUpLeft] + (mto & 0xf0);
					if(pos->b256[l2] == RKING){
						int l1 = psmv->RookCap[DUpLeft] + (mto & 0xf0);
						if(isCanProtect_Last_Move(pos,WHITE,l1,becap)){ //�ҷ����˳�,����ǣ���˶Է�һ����
							return TRUE;
						}
					}
				}
				else if(pos->b256[mto] == BPAO){
					int l3 = psmv->SuperCap[DUpLeft] + (mto & 0xf0);
					if(pos->b256[l3] = RKING){
						int l1 = psmv->RookCap[DUpLeft] + (mto & 0xf0);
						int l2 = psmv->CannonCap[DUpLeft] + (mto & 0xf0);
						if(isCanProtect_Last_Move(pos,WHITE,l1,becap)){ //�ҷ����˳�,����ǣ���˶Է�һ����
							return TRUE;
						}
						if(isCanProtect_Last_Move(pos,WHITE,l2,becap)){ //�ҷ����˳�,����ǣ���˶Է�һ����
							return TRUE;
						}
					}
				}
			}
		}
	}
	//#######################################################################################################################
	//��ǰ�Ǻ췽������
	//#######################################################################################################################
	else{

		if(pos->b256[becap] == BPAWN){
			if(StoY(becap) <= 0x7) return false;
		}

		//*****************************************************************************
		//1, �ߵ���ֱ��ȥ׽�Է��ߵ��ӣ�(�Է��ض����߶����Ǹ���)
		if(cap == mto) return TRUE;
		//*****************************************************************************
		//2, �ÿ����ҷ����ڼ�,����,����,ȥ׽�Է�����.(�Է����ܲ���,���ܶ�)
		//   cap ԭ�����ڼ�,���ߵ����ڼ���
		//fen 2ba1k3/1N1Ca4/9/1n2c4/2b3p2/8p/6P1c/2C1B4/4A4/4KAB2 b ����׽����
		if(pos->b256[cap] == RPAO){  //׽�Ե�������  
			if(false){
			}
			else if(StoX(cap) == StoX(becap)){ //��ͬһ��
				if(false){
				}
				else if(StoX(mfrom) == StoX(cap)){  //�뿪������׽
					if(false){
					}
					else if(becap > cap){
						if(mfrom < becap && mfrom > cap) return TRUE;
					}
					else if(becap < cap){
						if(mfrom > becap && mfrom < cap) return TRUE;
					}
				}
				else if(StoX(mto)   == StoX(cap)){  //��ȥ������׽
					if(false){
					}
					else if(becap > cap){
						if(mto < becap && mto > cap) return TRUE;
					}
					else if(becap < cap){
						if(mto > becap && mto < cap) return TRUE;
					}
				}
			}
			else if(StoY(cap) == StoY(becap)){ //��ͬһ��
				if(false){
				}
				else if(StoY(mfrom) == StoY(cap)){  //�뿪������׽
					if(false){
					}
					else if(becap > cap){
						if(mfrom < becap && mfrom > cap) return TRUE;
					}
					else if(becap < cap){
						if(mfrom > becap && mfrom < cap) return TRUE;
					}
				}
				else if(StoY(mto)   == StoY(cap)){  //��ȥ������׽
					if(false){
					}
					else if(becap > cap){
						if(mto < becap && mto > cap) return TRUE;
					}
					else if(becap < cap){
						if(mto > becap && mto < cap) return TRUE;
					}
				}
			}
		}
		//3, �ÿ��˳�ȥ׽. 
		//fen 3akab2/3n3r1/6c2/pN2p3p/1rb3pn1/2N3P2/4PR2P/1C2B4/4A4/2BAK1R2 w - - 0 0
		if(pos->b256[cap] == RCHE){
			if(false){
			}
			else if(StoX(cap) == StoX(becap)){ //��ͬһ��
				if(false){
				}
				else if(StoX(mfrom) == StoX(cap)){  //�뿪������׽
					if(false){
					}
					else if(becap > cap){
						if(mfrom < becap && mfrom > cap) return TRUE;
					}
					else if(becap < cap){
						if(mfrom > becap && mfrom < cap) return TRUE;
					}
				}
			}
			else if(StoY(cap) == StoY(becap)){ //��ͬһ��
				if(false){
				}
				else if(StoY(mfrom) == StoY(cap)){  //�뿪������׽
					if(false){
					}
					else if(becap > cap){
						if(mfrom < becap && mfrom > cap) return TRUE;
					}
					else if(becap < cap){
						if(mfrom > becap && mfrom < cap) return TRUE;
					}
				}
			}
		}

		if(pos->b256[cap] == RMA){     //׽�Ե�������
			//Ҫ��һ���ߵ���,�ǲ����ÿ�������, �ߵ��Ӿ�����
			int tmp = horseLegTab(becap-cap+256);
			if(cap+tmp == mfrom) return TRUE;
            
		}
		if(pos->b256[cap] == RXIANG){  //׽�Ե�������
			if((cap+becap)/2 == mfrom) return TRUE;
		}
		//*****************************************************************************
		//****** a,�ж϶Է��ĳ��ı���
		for(int protect = PieceListStart(pos,BCHE); protect > 0x32; protect = NextPiece(pos,protect)){
			if(protect != becap){
				if(false){
				}
				else if(StoX(protect) == StoX(becap)){  //�Է��ĳ��뱻�Ե���ͬһ��
					SlideMoveStruct *psmv;
					psmv = FileMove(StoY(protect),pos->wBitFiles[StoX(protect)]);
					if(StoX(mto) == StoX(protect) && StoX(mfrom) != StoX(protect)){
						if(false){
						}
						else if(psmv->CannonCap[DLoRight] + StoX(protect) == becap){
							if(mto > protect && mto < becap) return TRUE;
						}
						else if(psmv->CannonCap[DUpLeft]  + StoX(protect) == becap){
							if(mto < protect && mto > becap) return TRUE;
						}
					}
				}
				else if(StoY(protect) == StoY(becap)){  //�Է��ĳ��뱻�Ե���ͬһ��
					//fen 3akab2/9/4bc2n/8C/4p4/6P2/P1c1P3P/4B1R2/1r2A1n1C/1N1AK1B2 r
					SlideMoveStruct *psmv;
					psmv = RankMove(StoX(protect),pos->wBitRanks[StoY(protect)]);
					//�ӽ�ȥ���2��
					if(StoY(mto)   == StoY(protect) && StoY(mfrom) != StoY(protect)){
						if(false){
						}
						else if(psmv->CannonCap[DLoRight] + (protect & 0xf0) == becap){
							if(mto > protect && mto < becap) return TRUE;
						}
						else if(psmv->CannonCap[DUpLeft]  + (protect & 0xf0) == becap){
							if(mto < protect && mto > becap) return TRUE;
						}
					}
				}
			}
		}
		//3, �ж϶Է�����ϵ,
		//��Ҫ�������ǶԷ�������ԭ���б���. �����ڱ���,����,�ౣ��,
		//****** a,�ж϶Է����ڵı���
		//fen 4kab2/4a4/2n1b4/p1p1c3p/4R4/2P1P4/P5r1P/C3BcN2/5C3/3AKAB2 w - - 0 0
		for(int protect = PieceListStart(pos,BPAO); protect > 0x32 ; protect = NextPiece(pos,protect)){
			if(protect != becap){
				if(false){
				}
				else if(StoX(protect) == StoX(becap)){
					SlideMoveStruct *psmv;
					psmv = FileMove(StoY(protect),pos->wBitFiles[StoX(protect)]);
					//�ӽ�ȥ���2��
					if(StoX(mto)   == StoX(protect) && StoX(mfrom) != StoX(protect)){
						if(false){
						}
						else if(psmv->SuperCap[DLoRight] + StoX(protect) == becap){
							if(mto > protect && mto < becap) return TRUE;
						}
						else if(psmv->SuperCap[DUpLeft]  + StoX(protect) == becap){
							if(mto < protect && mto > becap) return TRUE;
						}
					}
					//�߿������0��
					if(StoX(mfrom) == StoX(protect) && StoX(mto) != StoX(protect)){
						if(false){
						}
						else if(psmv->RookCap[DLoRight] + StoX(protect) == becap){
							if(mfrom > protect && mfrom < becap) return TRUE;
						}
						else if(psmv->RookCap[DUpLeft]  + StoX(protect) == becap){
							if(mfrom < protect && mfrom > becap) return TRUE;
						}
					}
				}
				else if(StoY(protect) == StoY(becap)){
					SlideMoveStruct *psmv;
					psmv = RankMove(StoX(protect),pos->wBitRanks[StoY(protect)]);
					//�ӽ�ȥ���2��
					if(StoY(mto)   == StoY(protect) && StoY(mfrom) != StoY(protect)){
						if(false){
						}
						else if(psmv->SuperCap[DLoRight] + (protect & 0xf0) == becap){
							if(mto > protect && mto < becap) return TRUE;
						}
						else if(psmv->SuperCap[DUpLeft]  + (protect & 0xf0) == becap){
							if(mto < protect && mto > becap) return TRUE;
						}
					}
					//�߿������0��
					if(StoY(mfrom) == StoY(protect) && StoY(mto) != StoY(protect)){
						if(false){
						}
						else if(psmv->RookCap[DLoRight] + (protect & 0xf0) == becap){
							if(mfrom > protect && mfrom < becap) return TRUE;
						}
						else if(psmv->RookCap[DUpLeft]  + (protect & 0xf0) == becap){
							if(mfrom < protect && mfrom > becap) return TRUE;
						}
					}
				}
			}
		}
		//****** b,�ж϶Է�����ı��� fen 3akab2/3n3r1/6c2/pN2p3p/1rb3pn1/2N3P2/4PR2P/1C2B4/4A4/2BAK1R2 w - - 0 0
		for(int protect = PieceListStart(pos,BMA); protect > 0x32 ; protect = NextPiece(pos,protect)){
			if(protect != becap){
				int tmp = horseLegTab(becap-protect+256);
				if(tmp != 0 && protect+tmp == mto) return TRUE; 
			}
		}
		//****** c,�ж϶Է�����ı��� 3ak4/4a4/8b/R8/9/9/9/4BA3/N1r1A1n2/2B2K3 b - - 0 0
		for(int protect = PieceListStart(pos,BXIANG); protect > 0x32 ; protect = NextPiece(pos,protect)){
			if(protect != becap){
				if((protect+becap)/2 == mto) return TRUE;
			}
		}

		//*****************************************************************************
		//4,�ͷ����ҷ�����ȥ׽, ���絲�˶Է����ڼ�, �򳵼�.(�Է����ܲ���,���ܶ�), 
		//��Ҫ���������ҷ��������ҷ��Ľ���һ������.���п������ͷ��˵���ȥ׽��.
		if(StoX(rk) == StoX(cap) && StoX(rk) == StoX(mto)){ 
			//=======================================================
			//�ҷ��ߵ��ҷ��Ľ���, �����ҷ�ԭ�Ȳ��ܶ�������,�п��ܿ��Զ���.
			//1, ��ס�˶Է�����, �м���3����. 2, ��ס�˶Է��ĳ�, �м���2����. 
            SlideMoveStruct *psmv;
			psmv = FileMove(StoY(mto),pos->wBitFiles[StoX(mto)]);
			//ֻҪ���rk ������Ӿ�����
			int up;
			int low;
			low  = psmv->RookCap[DLoRight] + StoX(mto);
			if(low != mto){  //��������
				if(low == rk){ //�� mto X X pao 
					up = psmv->SuperCap[DUpLeft] + StoX(mto);
					if(pos->b256[up] == BPAO){                                   //�����ʱ�����㳵��Է��Ľ���
						if(cap < rk && cap > up) return TRUE;
					}
				}
				else{
					low = psmv->CannonCap[DLoRight] + StoX(mto);
					if(low != mto){
						if(low == rk){  //����X��mto X pao 
							up = psmv->CannonCap[DUpLeft] + StoX(mto);
							if(pos->b256[up] == BPAO){
								if(cap < rk && cap > up) return TRUE;
							}
						}
						else{
							low = psmv->SuperCap[DLoRight] + StoX(mto);							
							if(low == rk){
								//��һ��������ǲ��ǶԷ�����
								up = psmv->RookCap[DUpLeft] + StoX(mto);
								if(pos->b256[up] == BPAO){ //����X  X mto pao 
									if(cap < rk && cap > up) return TRUE;
								}
							}							
						}
					}					
				}
			}
			//=======================================================
		}
		//
		if(StoY(rk) == StoY(cap) && StoY(rk) == StoY(mto)){
			//�������桡�� //�� mto X X pao 
			//=======================================================
			//�ҷ��ߵ��ҷ��Ľ���, �����ҷ�ԭ�Ȳ��ܶ�������,�п��ܿ��Զ���.
			//1, ��ס�˶Է�����, �м���3����. 2, ��ס�˶Է��ĳ�, �м���2����. 
            SlideMoveStruct *psmv;
			psmv = RankMove(StoX(mto),pos->wBitRanks[StoY(mto)]);
			//ֻҪ���bk ������Ӿ����� //�������桡�� //�� mto X X pao 
			int left;
			int right;
			left  = psmv->RookCap[DUpLeft] + (mto & 0xf0);
			if(left != mto){  //��������
				if(left == rk){ //�� mto X X pao 
					right = psmv->SuperCap[DLoRight] + (mto & 0xf0);
					if(pos->b256[right] == BPAO){                                   //�����ʱ�����㳵��Է��Ľ���
						if(cap > rk && cap < right) return TRUE;
					}
				}
				else{
					left = psmv->CannonCap[DUpLeft] + StoX(mto);
					if(left != mto){
						if(left == rk){  //����X��mto X pao 
							right = psmv->CannonCap[DLoRight] + (mto & 0xf0);
							if(pos->b256[right] == BPAO){
								if(cap > rk && cap < right) return TRUE;
							}
						}
						else{
							left = psmv->SuperCap[DUpLeft] + StoX(mto);							
							if(left == rk){
								//��һ��������ǲ��ǶԷ�����
								right = psmv->RookCap[DLoRight] + (mto & 0xf0);
								if(pos->b256[right] == BPAO){ //����X  X mto pao 
									if(cap > rk && cap < right) return TRUE;
								}
							}							
						}
					}					
				}
			}
			//��������
			//=======================================================
			right  = psmv->RookCap[DLoRight] + (mto & 0xf0);
			if(right != mto){  //��������
				if(right == rk){ //pao X X mto �� 
					left = psmv->SuperCap[DUpLeft] + (mto & 0xf0);
					if(pos->b256[left] == BPAO){                                   //�����ʱ�����㳵��Է��Ľ���
						if(cap < rk && cap > left) return TRUE;
					}
				}
				else{
					right = psmv->CannonCap[DLoRight] + StoX(mto);
					if(right != mto){
						if(right == rk){  //pao X mto X �� 
							left = psmv->CannonCap[DUpLeft] + (mto & 0xf0);
							if(pos->b256[left] == BPAO){
								if(cap < rk && cap > left) return TRUE;
							}
						}
						else{
							right = psmv->SuperCap[DLoRight] + StoX(mto);							
							if(right == rk){
								//��һ��������ǲ��ǶԷ�����
								left = psmv->RookCap[DUpLeft] + (mto & 0xf0);
								if(pos->b256[left] == BPAO){  //pao mto X X ��  
									if(cap < rk && cap > left) return TRUE;
								}
							}							
						}
					}					
				}
			}
			//=======================================================
		}

		//6,��ֹ�Է�������ȥ����������׽.
		//ͨ��ǣ�ƶԷ�����,������׽
		//1, ����ߵ�������,
		//if(pos->b256[mto] == BPAO){
		if(false){
		}
		else if(StoX(mto) == StoX(bk) && StoX(mfrom) != StoX(bk)){
			//�õ�mto �����µ�����
			SlideMoveStruct *psmv;
			psmv = FileMove(StoY(mto),pos->wBitFiles[StoX(mto)]);

			if(false){
			}
			else if(StoY(mto) < StoY(bk)){
				if(false){
				}
				else if(pos->b256[mto] == RCHE){ //������ü���һ���� :)
					int low2 = psmv->CannonCap[DLoRight] + StoX(mto);
					if(pos->b256[low2] == BKING){
						int low1 = psmv->RookCap[DLoRight] + StoX(mto);
						if(isCanProtect_Last_Move(pos,BLACK,low1,becap)){ //�ҷ����˳�,����ǣ���˶Է�һ����
							return TRUE;
						}
					}
				}
				//else if(pos->b256[mto] == BPAO){ 
				//	int low3 = psmv->SuperCap[DLoRight] + StoX(mto);
				//	if(pos->b256[low3] == RKING){
				//		int low1 = psmv->RookCap[DLoRight] + StoX(mto);
				//		int low2 = psmv->CannonCap[DLoRight] + StoX(mto);
				//		if(isCanProtect_Last_Move(pos,WHITE,low1,becap)){ //�ҷ����˳�,����ǣ���˶Է�һ����
				//			return TRUE;
				//		}
				//		if(isCanProtect_Last_Move(pos,WHITE,low2,becap)){ //�ҷ����˳�,����ǣ���˶Է�һ����
				//			return TRUE;
				//		}
				//	}
				//}
			}
			else if(StoY(mto) > StoY(bk)){
				if(false){
				}
				else if(pos->b256[mto] == RCHE || pos->b256[mto] == RKING){ 
					int up2 = psmv->CannonCap[DUpLeft] + StoX(mto);
					if(pos->b256[up2] == BKING){
						int up1 = psmv->RookCap[DUpLeft] + StoX(mto);
						if(isCanProtect_Last_Move(pos,BLACK,up1,becap)){ //�ҷ����˳�,����ǣ���˶Է�һ����
							return TRUE;
						}
					}
				}
				else if(pos->b256[mto] == RPAO){ 
					int up3 = psmv->SuperCap[DUpLeft] + StoX(mto);
					if(pos->b256[up3] == BKING){
						int up1 = psmv->RookCap[DUpLeft] + StoX(mto);
						int up2 = psmv->CannonCap[DUpLeft] + StoX(mto);
						if(isCanProtect_Last_Move(pos,BLACK,up1,becap)){ //�ҷ����˳�,����ǣ���˶Է�һ����
							return TRUE;
						}
						if(isCanProtect_Last_Move(pos,BLACK,up2,becap)){ //�ҷ����˳�,����ǣ���˶Է�һ����
							return TRUE;
						}
					}
				}
			}
		}
		else if(StoY(mto) == StoY(bk) && StoY(mfrom) != StoY(bk)){
			//�õ�mto �����ҵ�����
			SlideMoveStruct *psmv;
			psmv = RankMove(StoX(mto),pos->wBitRanks[StoY(mto)]);
			if(false){
			}
			else if(StoX(mto) < StoX(rk)){
				if(false){
				}
				else if(pos->b256[mto] == RCHE){
                    int r2 = psmv->CannonCap[DLoRight] + (mto & 0xf0);
					if(pos->b256[r2] == BKING){
						int r1 = psmv->RookCap[DLoRight] + (mto & 0xf0);
						if(isCanProtect_Last_Move(pos,BLACK,r1,becap)){ //�ҷ����˳�,����ǣ���˶Է�һ����
							return TRUE;
						}
					}
				}
				else if(pos->b256[mto] == RPAO){
					int r3 = psmv->SuperCap[DLoRight] + (mto & 0xf0);
					if(pos->b256[r3] == BKING){
						int r1 = psmv->RookCap[DLoRight] + (mto & 0xf0);
						int r2 = psmv->CannonCap[DLoRight] + (mto & 0xf0);
						if(isCanProtect_Last_Move(pos,BLACK,r1,becap)){ //�ҷ����˳�,����ǣ���˶Է�һ����
							return TRUE;
						}
						if(isCanProtect_Last_Move(pos,BLACK,r2,becap)){ //�ҷ����˳�,����ǣ���˶Է�һ����
							return TRUE;
						}
					}
				}
			}
			else if(StoX(mto) > StoX(rk)){
				if(false){
				}
				else if(pos->b256[mto] == RCHE){
                    int l2 = psmv->CannonCap[DUpLeft] + (mto & 0xf0);
					if(pos->b256[l2] == BKING){
						int l1 = psmv->RookCap[DUpLeft] + (mto & 0xf0);
						if(isCanProtect_Last_Move(pos,BLACK,l1,becap)){ //�ҷ����˳�,����ǣ���˶Է�һ����
							return TRUE;
						}
					}
				}
				else if(pos->b256[mto] == RPAO){
					int l3 = psmv->SuperCap[DUpLeft] + (mto & 0xf0);
					if(pos->b256[l3] == BKING){
						int l1 = psmv->RookCap[DUpLeft] + (mto & 0xf0);
						int l2 = psmv->CannonCap[DUpLeft] + (mto & 0xf0);
						if(isCanProtect_Last_Move(pos,BLACK,l1,becap)){ //�ҷ����˳�,����ǣ���˶Է�һ����
							return TRUE;
						}
						if(isCanProtect_Last_Move(pos,BLACK,l2,becap)){ //�ҷ����˳�,����ǣ���˶Է�һ����
							return TRUE;
						}
					}
				}
			}
		}
	}

	return FALSE;
}


//1, �ߵ���ֱ��ȥ׽�Է��ߵ��ӣ�(�Է��ض����߶����Ǹ���)
//2, �ÿ����ҷ����ڼ�,����,����,ȥ׽�Է�����.(�Է����ܲ���,���ܶ�)
//3, �ж϶Է��ı���,ȥ׽�Է�����, ��Է����ڵı���, ȥ׽�Է�ԭ���ڱ�������.(�Է����ܲ���,���ܶ�),
//4, �ͷ����ҷ�����ȥ׽, ���絲�˶Է����ڼ�, �򳵼�.(�Է����ܲ���,���ܶ�),
//
//�ȿ�����, �ҳ�Ŀǰ���е�׽, ��ÿһ��׽�����ж�. ����������һ��,����׽. 