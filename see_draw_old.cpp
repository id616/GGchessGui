#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"

/*
//ͨ��SEE���ж���׽
BOOL see_draw_20080818(position_t *pos,int mfrom,int mto, int from, int to, int which){


	int sq2;
	SlideMoveStruct *psmv;

	//��ǰ�Ǻڷ�������
	if(which == WHITE){   
		//1, �ж϶Է����ڵı���,׽�Է�"����"����	
		for(int ot_pao = PieceListStart(pos,RPAO); ot_pao > 0x32; ot_pao = NextPiece(pos,ot_pao)){	
			//1,**************************************************
			if(StoX(mfrom) == StoX(ot_pao)){			//���ڵ�File���뿪
				if(StoX(mto) != StoX(ot_pao)){					
					//��һ���ڵ�������Ϣ
					psmv = FileMove(StoY(ot_pao),pos->wBitFiles[StoX(ot_pao)]);
					if(StoY(mfrom) > StoY(ot_pao)){		//���ڵ�����
						int sq1 = psmv->RookCap[DLoRight] + StoX(ot_pao);
						if(StoY(mfrom) < StoY(sq1) && IsWhite(pos->b256[sq1]) && testall_TrueCap_noPawnKing(pos,sq1,from,which)){
							return TRUE;
						}
					}
					else{
						int sq1 = psmv->RookCap[DUpLeft] + StoX(ot_pao);
						if(StoY(mfrom) > StoY(sq1) && IsWhite(pos->b256[sq1]) && testall_TrueCap_noPawnKing(pos,sq1,from,which)){
							return TRUE;
						}						
					}
				}										
			}
			//2,**************************************************
			if(StoX(mto) == StoX(ot_pao)){			//�ߵ��ڵ�File��
				if(StoX(mfrom) != StoX(ot_pao)){					
					//��һ���ڵ�������Ϣ
					psmv = FileMove(StoY(ot_pao),pos->wBitFiles[StoX(ot_pao)]);
					if(StoY(mto) > StoY(ot_pao)){		//���ڵ�����
						int sq3 = psmv->SuperCap[DLoRight] + StoX(ot_pao);
						if(StoY(mto) < StoY(sq3) && IsWhite(pos->b256[sq3]) && testall_TrueCap_noPawnKing(pos,sq3,from,which)){
							return TRUE;
						}
					}
					else{
						int sq3 = psmv->SuperCap[DUpLeft] + StoX(ot_pao);
						if(StoY(mto) > StoY(sq3)&& IsWhite(pos->b256[sq3]) && testall_TrueCap_noPawnKing(pos,sq3,from,which)){
							return TRUE;
						}
					}
				}

			}
			//3,**************************************************
			if(StoY(mfrom) == StoY(ot_pao)){			//���ڵ�Rank���뿪
				if(StoY(mto) != StoY(ot_pao)){
					//��һ���ڵ�������Ϣ
					psmv = RankMove(StoX(ot_pao),pos->wBitRanks[StoY(ot_pao)]);
					if(StoX(mfrom) > StoX(ot_pao)){
						int sq1 = psmv->RookCap[DLoRight] + (ot_pao & 0xf0);
						if(StoX(mfrom) < StoX(sq1)  && IsWhite(pos->b256[sq1]) && testall_TrueCap_noPawnKing(pos,sq1,from,which)){
							return TRUE;
						}						
					}
					else{
						int sq1 = psmv->RookCap[DUpLeft] + (ot_pao & 0xf0);
						if(StoX(mfrom) > StoX(sq1) && IsWhite(pos->b256[sq1]) && testall_TrueCap_noPawnKing(pos,sq1,from,which)){
							return TRUE;
						}						
					}
				}
			}
			//4,**************************************************
			if(StoY(mto) == StoY(ot_pao)){			//�ߵ��ڵ�Rank��
				if(StoY(mfrom) != StoY(ot_pao)){
					//��һ���ڵ�������Ϣ
					psmv = RankMove(StoX(ot_pao),pos->wBitRanks[StoY(ot_pao)]);
					if(StoX(mto) > StoX(ot_pao)){
						int sq3 = psmv->SuperCap[DLoRight] + (ot_pao & 0xf0);
						if(StoX(mto) < StoX(sq3) && IsWhite(pos->b256[sq3]) && testall_TrueCap_noPawnKing(pos,sq3,from,which)){
							return TRUE;
						}
					}
					else{
						int sq3 = psmv->SuperCap[DUpLeft] + (ot_pao & 0xf0);
						if(StoX(mto) > StoX(sq3) && IsWhite(pos->b256[sq3]) && testall_TrueCap_noPawnKing(pos,sq3,from,which)){
							return TRUE;
						}
					}
				}
			}
		}

		//2, �ж϶Է�����ı���,׽�Է�"����"����,��������һЩ��	
		//3, �ж϶Է�����ı���,׽�Է�"����"����,��������һЩ	
		
		//2, �ÿ�����,׽�Է�"����"����	
		//fen 3aknr2/4a4/4b4/p4PN1p/4R4/P1R5P/3r2c2/4C2C1/4A1c2/2B1KAB2 w - - 13 13 
		//�ÿ��ڳ�����
		//#####################################################################
		//�ǲ����ÿ�����,׽�Է�"����"����	
		for(int at = PieceListStart(pos,BPAO); at > 0x32; at = NextPiece(pos,at)){
			if(at != mto){		//�ߵĲ����Ǹ���							
				//1,**************************************************
				if(StoX(mfrom) == StoX(at)){			//���ڵ�File���뿪
					if(StoX(mto) != StoX(at)){					
						//��һ���ڵ�������Ϣ
						psmv = FileMove(StoY(at),pos->wBitFiles[StoX(at)]);
						if(StoY(mfrom) > StoY(at)){		//���ڵ�����
							sq2 = psmv->CannonCap[DLoRight] + StoX(at);
							//if(IsWhitePaoNoRiverPawn(sq2) && StoY(mfrom) < StoY(sq2) ){   //�ߵ�����sq2 �� at ���м�
							if(IsWhite(pos->b256[sq2]) && StoY(mfrom) < StoY(sq2) ){   //�ߵ�����sq2 �� at ���м�
								if(Is_True_Cap(pos,at,sq2,from,to,which)){
									return TRUE;
								}
							}
						}
						else{
							sq2 = psmv->CannonCap[DUpLeft] + StoX(at);
							//if(IsWhitePaoNoRiverPawn(sq2)  && StoY(mfrom) > StoY(sq2) ){
							if(IsWhite(pos->b256[sq2]) && StoY(mfrom) > StoY(sq2) ){
								if(Is_True_Cap(pos,at,sq2,from,to,which)){
									return TRUE;
								}
							}
						}
					}										
				}
				//2,**************************************************
				if(StoX(mto) == StoX(at)){			//�ߵ��ڵ�File��
					if(StoX(mfrom) != StoX(at)){					
						//��һ���ڵ�������Ϣ
						psmv = FileMove(StoY(at),pos->wBitFiles[StoX(at)]);

						if(StoY(mto) > StoY(at)){		//���ڵ�����
							sq2 = psmv->CannonCap[DLoRight] + StoX(at);
							//if(IsWhitePaoNoRiverPawn(sq2)  && StoY(mto) < StoY(sq2) ){///�΢ν�����
							if(IsWhite(pos->b256[sq2]) && StoY(mto) < StoY(sq2) ){
								if(Is_True_Cap(pos,at,sq2,from,to,which)){
									return TRUE;
								}
							}
						}
						else{
							sq2 = psmv->CannonCap[DUpLeft] + StoX(at);
							//if(IsWhitePaoNoRiverPawn(sq2)  && StoY(mto) > StoY(sq2) ){
							if(IsWhite(pos->b256[sq2]) && StoY(mto) > StoY(sq2) ){
								if(Is_True_Cap(pos,at,sq2,from,to,which)){
									return TRUE;
								}
							}
						}
					}

				}
				//3,**************************************************
				if(StoY(mfrom) == StoY(at)){			//���ڵ�Rank���뿪
					if(StoY(mto) != StoY(at)){
						//��һ���ڵ�������Ϣ
						psmv = RankMove(StoX(at),pos->wBitRanks[StoY(at)]);

						if(StoX(mfrom) > StoX(at)){
							sq2 = psmv->CannonCap[DLoRight] + (at & 0xf0);
							//if(IsWhitePaoNoRiverPawn(sq2)  && StoX(mfrom) < StoX(sq2) ){
							if(IsWhite(pos->b256[sq2]) && StoX(mfrom) < StoX(sq2) ){
								if(Is_True_Cap(pos,at,sq2,from,to,which)){
									return TRUE;
								}
							}
						}
						else{
							sq2 = psmv->CannonCap[DUpLeft] + (at & 0xf0);
							//if(IsWhitePaoNoRiverPawn(sq2)  && StoX(mfrom) > StoX(sq2) ){
							if(IsWhite(pos->b256[sq2]) && StoX(mfrom) > StoX(sq2) ){
								if(Is_True_Cap(pos,at,sq2,from,to,which)){
									return TRUE;
								}
							}
						}
					}
				}
				//4,**************************************************
				if(StoY(mto) == StoY(at)){			//�ߵ��ڵ�Rank��
					if(StoY(mfrom) != StoY(at)){
						//��һ���ڵ�������Ϣ
						psmv = RankMove(StoX(at),pos->wBitRanks[StoY(at)]);

						if(StoX(mto) > StoX(at)){
							sq2 = psmv->CannonCap[DLoRight] + (at & 0xf0);
							//if(IsWhitePaoNoRiverPawn(sq2)  && StoX(mto) < StoX(sq2) ){ 
							if(IsWhite(pos->b256[sq2]) && StoX(mto) < StoX(sq2) ){ 
								if(Is_True_Cap(pos,at,sq2,from,to,which)){  //BOOL Is_True_Cap(position_t *pos,int from, int to, int ot_from,int ot_to, int which){
									return TRUE;
								}
							}
						}
						else{
							sq2 = psmv->CannonCap[DUpLeft] + (at & 0xf0);
							//if(IsWhitePaoNoRiverPawn(sq2)  && StoX(mto) > StoX(sq2)){
							if(IsWhite(pos->b256[sq2]) && StoX(mto) > StoX(sq2)){
								if(Is_True_Cap(pos,at,sq2,from,to,which)){
									return TRUE;
								}
							}
						}
					}
				}

				//
			}
		}
		//#####################################################################
		//��һ���ǲ����ÿ��˳���׽,׽�Է�"����"����	
		for(int at = PieceListStart(pos,BCHE); at > 0x32; at = NextPiece(pos,at)){
			if(at != mto){		//�ߵĲ����Ǹ���							
				//1,**************************************************
				if(StoX(mfrom) == StoX(at)){			//���ڵ�File���뿪
					if(StoX(mto) != StoX(at)){					
						//��һ���ڵ�������Ϣ
						psmv = FileMove(StoY(at),pos->wBitFiles[StoX(at)]);

						if(StoY(mfrom) > StoY(at)){		//���ڵ�����
							sq2 = psmv->RookCap[DLoRight] + StoX(at);
							if(IsWhite(pos->b256[sq2]) && StoY(mfrom) < StoY(sq2) ){   //�ߵ�����sq2 �� at ���м�
								if(Is_True_Cap(pos,at,sq2,from,to,which)){
									return TRUE;
								}
							}
						}
						else{
							sq2 = psmv->RookCap[DUpLeft] + StoX(at);
							if(IsWhite(pos->b256[sq2]) && StoY(mfrom) > StoY(sq2) ){
								if(Is_True_Cap(pos,at,sq2,from,to,which)){
									return TRUE;
								}
							}
						}
					}										
				}
				//2,**************************************************
				if(StoX(mto) == StoX(at)){			//�ߵ�����File��
					if(StoX(mfrom) != StoX(at)){					
						//��һ�³���������Ϣ
						psmv = FileMove(StoY(at),pos->wBitFiles[StoX(at)]);

						if(StoY(mto) > StoY(at)){		//�ڳ�������
							sq2 = psmv->RookCap[DLoRight] + StoX(at);
							if(IsWhite(pos->b256[sq2]) && StoY(mto) < StoY(sq2) ){
								if(Is_True_Cap(pos,at,sq2,from,to,which)){
									return TRUE;
								}
							}
						}
						else{
							sq2 = psmv->RookCap[DUpLeft] + StoX(at);
							if(IsWhite(pos->b256[sq2]) && StoY(mto) > StoY(sq2) ){
								if(Is_True_Cap(pos,at,sq2,from,to,which)){
									return TRUE;
								}
							}
						}
					}

				}
				//3,**************************************************
				if(StoY(mfrom) == StoY(at)){			//�ӳ���Rank���뿪
					if(StoY(mto) != StoY(at)){
						//��һ�³���������Ϣ
						psmv = RankMove(StoX(at),pos->wBitRanks[StoY(at)]);

						if(StoX(mfrom) > StoX(at)){
							sq2 = psmv->RookCap[DLoRight] + (at & 0xf0);
							if(IsWhite(pos->b256[sq2]) && StoX(mfrom) < StoX(sq2) ){
								if(Is_True_Cap(pos,at,sq2,from,to,which)){
									return TRUE;
								}
							}
						}
						else{
							sq2 = psmv->RookCap[DUpLeft] + (at & 0xf0);
							if(IsWhite(pos->b256[sq2]) && StoX(mfrom) > StoX(sq2) ){
								if(Is_True_Cap(pos,at,sq2,from,to,which)){
									return TRUE;
								}
							}
						}
					}
				}
				//4,**************************************************
				if(StoY(mto) == StoY(at)){			//�ӳ���Rank���뿪
					if(StoY(mfrom) != StoY(at)){
						//��һ�³���������Ϣ
						psmv = RankMove(StoX(at),pos->wBitRanks[StoY(at)]);

						if(StoX(mto) > StoX(at)){
							sq2 = psmv->RookCap[DLoRight] + (at & 0xf0);
							if(IsWhite(pos->b256[sq2]) && StoX(mto) < StoX(sq2) ){
								if(Is_True_Cap(pos,at,sq2,from,to,which)){
									return TRUE;
								}
							}
						}
						else{
							sq2 = psmv->RookCap[DUpLeft] + (at & 0xf0);
							if(IsWhite(pos->b256[sq2]) && StoX(mto) > StoX(sq2)){
								if(Is_True_Cap(pos,at,sq2,from,to,which)){
									return TRUE;
								}
							}
						}
					}
				}
				//
			}
		}

		//fen 4kab2/4a4/2n1b4/p1p1c3p/4R4/2P1P4/P5r1P/C3BcN2/5C3/3AKAB2 w - - 0 0


        //   �������жϳ�׽�Է��������ӣ�����Ҫ�жϳ�׽�Է��߶����ӣ�
		//B, ��׽�߶�����. ���������ǰ��׽, ���ڵ�׽ȥ�ж�һ��.�ǲ��Ƕ�����Ŀ. 
		//1, �ж϶Է����ڵ���ϵ׽, ����ǳ�׽�Բ�������, 
		//2, �����ж���ǰ��׽, �ж��ߺ��׽, ����Ƕ������׽,����׽!!!! 
		//   ����и�to������, 

		//����Ƚϸ��ӣ�Ҫ�ж��ǲ��ǳ�׽��������,
		if(testall_TrueCap_noPawnKing(pos,to,from,which)){
			return TRUE;
		}
	}
	//=================================================================================�����жϺ췽��׽
	else{

		//3, �ÿ��˳���׽��������
		//4, �赲�˶Է��ı�����׽��������
		//a,�赲��������ı����������ʱû�г���
		//b,�赲��������ı����������ʱû�г���
		//c,�赲���ڵı��� 
		//fen 4kab2/4a4/2n1b4/p1p1c3p/4R4/2P1P4/P5r1P/C3BcN2/5C3/3AKAB2 w - - 0 0
		//����Ƚϸ��ӣ�Ҫ�ж��ǲ��ǳ�׽��������,
		for(int ot_pao = PieceListStart(pos,BPAO); ot_pao > 0x32; ot_pao = NextPiece(pos,ot_pao)){	
			//1,**************************************************
			if(StoX(mfrom) == StoX(ot_pao)){			//���ڵ�File���뿪
				if(StoX(mto) != StoX(ot_pao)){					
					//��һ���ڵ�������Ϣ
					psmv = FileMove(StoY(ot_pao),pos->wBitFiles[StoX(ot_pao)]);
					if(StoY(mfrom) > StoY(ot_pao)){		//���ڵ�����
						int sq1 = psmv->RookCap[DLoRight] + StoX(ot_pao);
						if(StoY(mfrom) < StoY(sq1) && IsBlack(pos->b256[sq1]) && testall_TrueCap_noPawnKing(pos,sq1,from,which)){
							return TRUE;
						}
					}
					else{
						int sq1 = psmv->RookCap[DUpLeft] + StoX(ot_pao);
						if(StoY(mfrom) > StoY(sq1) && IsBlack(pos->b256[sq1]) && testall_TrueCap_noPawnKing(pos,sq1,from,which)){
							return TRUE;
						}						
					}
				}										
			}
			//2,**************************************************
			if(StoX(mto) == StoX(ot_pao)){			//�ߵ��ڵ�File��
				if(StoX(mfrom) != StoX(ot_pao)){					
					//��һ���ڵ�������Ϣ
					psmv = FileMove(StoY(ot_pao),pos->wBitFiles[StoX(ot_pao)]);
					if(StoY(mto) > StoY(ot_pao)){		//���ڵ�����
						int sq3 = psmv->SuperCap[DLoRight] + StoX(ot_pao);
						if(StoY(mto) < StoY(sq3) && IsBlack(pos->b256[sq3]) && testall_TrueCap_noPawnKing(pos,sq3,from,which)){
							return TRUE;
						}
					}
					else{
						int sq3 = psmv->SuperCap[DUpLeft] + StoX(ot_pao);
						if(StoY(mto) > StoY(sq3)&& IsBlack(pos->b256[sq3]) && testall_TrueCap_noPawnKing(pos,sq3,from,which)){
							return TRUE;
						}
					}
				}

			}
			//3,**************************************************
			if(StoY(mfrom) == StoY(ot_pao)){			//���ڵ�Rank���뿪
				if(StoY(mto) != StoY(ot_pao)){
					//��һ���ڵ�������Ϣ
					psmv = RankMove(StoX(ot_pao),pos->wBitRanks[StoY(ot_pao)]);
					if(StoX(mfrom) > StoX(ot_pao)){
						int sq1 = psmv->RookCap[DLoRight] + (ot_pao & 0xf0);
						if(StoX(mfrom) < StoX(sq1)  && IsBlack(pos->b256[sq1]) && testall_TrueCap_noPawnKing(pos,sq1,from,which)){
							return TRUE;
						}						
					}
					else{
						int sq1 = psmv->RookCap[DUpLeft] + (ot_pao & 0xf0);
						if(StoX(mfrom) > StoX(sq1) && IsBlack(pos->b256[sq1]) && testall_TrueCap_noPawnKing(pos,sq1,from,which)){
							return TRUE;
						}						
					}
				}
			}
			//4,**************************************************
			if(StoY(mto) == StoY(ot_pao)){			//�ߵ��ڵ�Rank��
				if(StoY(mfrom) != StoY(ot_pao)){
					//��һ���ڵ�������Ϣ
					psmv = RankMove(StoX(ot_pao),pos->wBitRanks[StoY(ot_pao)]);
					if(StoX(mto) > StoX(ot_pao)){
						int sq3 = psmv->SuperCap[DLoRight] + (ot_pao & 0xf0);
						if(StoX(mto) < StoX(sq3) && IsBlack(pos->b256[sq3]) && testall_TrueCap_noPawnKing(pos,sq3,from,which)){
							return TRUE;
						}
					}
					else{
						int sq3 = psmv->SuperCap[DUpLeft] + (ot_pao & 0xf0);
						if(StoX(mto) > StoX(sq3) && IsBlack(pos->b256[sq3]) && testall_TrueCap_noPawnKing(pos,sq3,from,which)){
							return TRUE;
						}
					}
				}
			}
		}
		
		//2, �ÿ����ڣ�׽��������
		//fen 3aknr2/4a4/4b4/p4PN1p/4R4/P1R5P/3r2c2/4C2C1/4A1c2/2B1KAB2 w - - 13 13 
		//�ÿ��ڳ�����
		//#####################################################################

		//�ǲ����ÿ����ڳ�׽        
		for(int at = PieceListStart(pos,RPAO); at > 0x32; at = NextPiece(pos,at)){
			if(at != mto){		//�ߵĲ����Ǹ���							
				//1,**************************************************
				if(StoX(mfrom) == StoX(at)){			//���ڵ�File���뿪
					if(StoX(mto) != StoX(at)){					
						//��һ���ڵ�������Ϣ
						psmv = FileMove(StoY(at),pos->wBitFiles[StoX(at)]);

						//sq1 = psmv->RookCap[DLoRight] + StoX(at);
						//sq2 = psmv->CannonCap[DLoRight] + StoX(at);
						//sq3 = psmv->SuperCap[DLoRight] + StoX(at);

						if(StoY(mfrom) > StoY(at)){		//���ڵ�����
							sq2 = psmv->CannonCap[DLoRight] + StoX(at);
							//if(IsBlackPaoNoRiverPawn(sq2)  && StoY(mfrom) < StoY(sq2) ){	
							if(IsBlack(pos->b256[sq2]) && StoY(mfrom) < StoY(sq2) ){
								if(Is_True_Cap(pos,at,sq2,from,to,which)){
									return TRUE;
								}
							}
						}
						else{
							sq2 = psmv->CannonCap[DUpLeft] + StoX(at);
							//if(IsBlackPaoNoRiverPawn(sq2)   && StoY(mfrom) > StoY(sq2) ){	
							if(IsBlack(pos->b256[sq2]) && StoY(mfrom) > StoY(sq2) ){
								if(Is_True_Cap(pos,at,sq2,from,to,which)){
									return TRUE;
								}
							}
						}
					}										
				}
				//2,**************************************************
				if(StoX(mto) == StoX(at)){			//���ڵ�File���뿪 //�ߵ��ڵ�FILE��
					if(StoX(mfrom) != StoX(at)){					
						//��һ���ڵ�������Ϣ
						psmv = FileMove(StoY(at),pos->wBitFiles[StoX(at)]);

						if(StoY(mto) > StoY(at)){		//���ڵ�����
							sq2 = psmv->CannonCap[DLoRight] + StoX(at);
							//if(IsBlackPaoNoRiverPawn(sq2)   && StoY(mto) < StoY(sq2) ){		
							if(IsBlack(pos->b256[sq2]) &&  StoY(mto) < StoY(sq2) ){		
								if(Is_True_Cap(pos,at,sq2,from,to,which)){
									return TRUE;
								}
							}
						}
						else{
							sq2 = psmv->CannonCap[DUpLeft] + StoX(at);
							//if(IsBlackPaoNoRiverPawn(sq2)  && StoY(mto) > StoY(sq2) ){	
							if(IsBlack(pos->b256[sq2]) && StoY(mto) > StoY(sq2) ){	
								if(Is_True_Cap(pos,at,sq2,from,to,which)){
									return TRUE;
								}
							}
						}
					}										
				}
				//3, **************************************************
				if(StoY(mfrom) == StoY(at)){			//���ڵ�Rank���뿪
					if(StoY(mto) != StoY(at)){
						//��һ���ڵ�������Ϣ
						psmv = RankMove(StoX(at),pos->wBitRanks[StoY(at)]);

						if(StoX(mfrom) > StoX(at)){
							sq2 = psmv->CannonCap[DLoRight] + (at & 0xf0);
							//if(IsBlackPaoNoRiverPawn(sq2)   && StoX(mfrom) < StoX(sq2) ){	
							if(IsBlack(pos->b256[sq2]) && StoX(mfrom) < StoX(sq2) ){	
								if(Is_True_Cap(pos,at,sq2,from,to,which)){
									return TRUE;
								}
							}
						}
						else{
							sq2 = psmv->CannonCap[DUpLeft] + (at & 0xf0);
							//if(IsBlackPaoNoRiverPawn(sq2)   && StoX(mfrom) > StoX(sq2) ){	
							if(IsBlack(pos->b256[sq2]) && StoX(mfrom) > StoX(sq2) ){
								if(Is_True_Cap(pos,at,sq2,from,to,which)){
									return TRUE;
								}
							}
						}
					}
				}
				//4, **************************************************
				if(StoY(mto) == StoY(at)){			//���ڵ�Rank���뿪
					if(StoY(mfrom) != StoY(at)){
						//��һ���ڵ�������Ϣ
						psmv = RankMove(StoX(at),pos->wBitRanks[StoY(at)]);

						if(StoX(mto) > StoX(at)){
							sq2 = psmv->CannonCap[DLoRight] + (at & 0xf0);
							//if(IsBlackPaoNoRiverPawn(sq2)   && StoX(mto) < StoX(sq2)){		
							if(IsBlack(pos->b256[sq2]) && StoX(mto) < StoX(sq2)){
								if(Is_True_Cap(pos,at,sq2,from,to,which)){
									return TRUE;
								}
							}
						}
						else{
							sq2 = psmv->CannonCap[DUpLeft] + (at & 0xf0);
							//if(IsBlackPaoNoRiverPawn(sq2)  && StoX(mto) > StoX(sq2)){	
							if(IsBlack(pos->b256[sq2]) && StoX(mto) > StoX(sq2)){	
								if(Is_True_Cap(pos,at,sq2,from,to,which)){
									return TRUE;
								}
							}
						}
					}
				}

				//
			}
		}



		//#####################################################################
		//�ǲ����ÿ��˳�

		for(int at = PieceListStart(pos,RCHE); at > 0x32; at = NextPiece(pos,at)){
			if(at != mto){		//�ߵĲ����Ǹ���							
				//1,**************************************************
				if(StoX(mfrom) == StoX(at)){			//�ӳ���File���뿪
					if(StoX(mto) != StoX(at)){					
						//��һ���ڵ�������Ϣ
						psmv = FileMove(StoY(at),pos->wBitFiles[StoX(at)]);

						//sq1 = psmv->RookCap[DLoRight] + StoX(at);
						//sq2 = psmv->CannonCap[DLoRight] + StoX(at);
						//sq3 = psmv->SuperCap[DLoRight] + StoX(at);

						if(StoY(mfrom) > StoY(at)){		//�ڳ�������
							sq2 = psmv->RookCap[DLoRight] + StoX(at);
							if(IsBlack(pos->b256[sq2]) && StoY(mfrom) < StoY(sq2) ){								

								if(Is_True_Cap(pos,at,sq2,from,to,which)){
									return TRUE;
								}
							}
						}
						else{
							sq2 = psmv->RookCap[DUpLeft] + StoX(at);
							if(IsBlack(pos->b256[sq2])  && StoY(mfrom) > StoY(sq2) ){								

								if(Is_True_Cap(pos,at,sq2,from,to,which)){
									return TRUE;
								}
							}
						}
					}										
				}
				//2,**************************************************
				if(StoX(mto) == StoX(at)){			//�ӳ���File���뿪 //�ߵ�����File��
					if(StoX(mfrom) != StoX(at)){					
						//��һ���ڵ�������Ϣ
						psmv = FileMove(StoY(at),pos->wBitFiles[StoX(at)]);

						if(StoY(mto) > StoY(at)){		//�ڳ�������
							sq2 = psmv->RookCap[DLoRight] + StoX(at);
							if(IsBlack(pos->b256[sq2])  && StoY(mto) < StoY(sq2) ){							

								if(Is_True_Cap(pos,at,sq2,from,to,which)){
									return TRUE;
								}
							}
						}
						else{
							sq2 = psmv->RookCap[DUpLeft] + StoX(at);
							if(IsBlack(pos->b256[sq2]) && StoY(mto) > StoY(sq2) ){							

								if(Is_True_Cap(pos,at,sq2,from,to,which)){
									return TRUE;
								}
							}
						}
					}										
				}
				//3, **************************************************
				if(StoY(mfrom) == StoY(at)){			//�ӳ���Rank���뿪
					if(StoY(mto) != StoY(at)){
						//��һ���ڵ�������Ϣ
						psmv = RankMove(StoX(at),pos->wBitRanks[StoY(at)]);

						if(StoX(mfrom) > StoX(at)){
							sq2 = psmv->RookCap[DLoRight] + (at & 0xf0);
							if(IsBlack(pos->b256[sq2])  && StoX(mfrom) < StoX(sq2) ){							

								if(Is_True_Cap(pos,at,sq2,from,to,which)){
									return TRUE;
								}
							}
						}
						else{
							sq2 = psmv->RookCap[DUpLeft] + (at & 0xf0);
							if(IsBlack(pos->b256[sq2])  && StoX(mfrom) > StoX(sq2) ){								

								if(Is_True_Cap(pos,at,sq2,from,to,which)){
									return TRUE;
								}
							}
						}
					}
				}
				//4, **************************************************
				if(StoY(mto) == StoY(at)){			//�ӳ���Rank���뿪
					if(StoY(mfrom) != StoY(at)){
						//��һ�³���������Ϣ
						psmv = RankMove(StoX(at),pos->wBitRanks[StoY(at)]);

						if(StoX(mto) > StoX(at)){
							sq2 = psmv->RookCap[DLoRight] + (at & 0xf0);
							if(IsBlack(pos->b256[sq2])  && StoX(mto) < StoX(sq2)){							

								if(Is_True_Cap(pos,at,sq2,from,to,which)){
									return TRUE;
								}
							}
						}
						else{
							sq2 = psmv->RookCap[DUpLeft] + (at & 0xf0);
							if(IsBlack(pos->b256[sq2]) && StoX(mto) > StoX(sq2)){								

								if(Is_True_Cap(pos,at,sq2,from,to,which)){
									return TRUE;
								}
							}
						}
					}
				}

				//
			}
		}
		

		//1, ֱ��׽�����ߵ���
		//if(testall_TrueCap_noPawnKing(pos,to,from,which)){
		if(testall_TrueCap_noPawnKing(pos,to,from,which)){
			return TRUE;
		}
	}


	return FALSE;


} 
*/