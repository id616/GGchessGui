#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"
//�ǲ��ǹ������׽
void test_Is_True_Cap(position_t *pos,int from, int to, int ot_from, int ot_to,int which){

  int to_id = PIECE_ID(pos->b256[to]);

   //---------------------------------------------------------------------------
   //1, �Ǳ����ڳ�, �ͷ��� FALSE ,���������, ��Ϊǰ�����ȥ����
   //---------------------------------------------------------------------------


   //---------------------------------------------------------------------------
   //2, �ж�������ܲ�����, ���������,Ҳ�Ͳ�����ȥ�ԶԷ���
   //---------------------------------------------------------------------------
	if(Is_Can_Move_To_Eat(pos,from,to) == FALSE){  //׽�����Ӳ��ܶ�.
		return;
	}

	//---------------------------------------------------------------------------
	//2, �������óԵ��Ǹ��ӵ�ORDER?
	//---------------------------------------------------------------------------
	//int order = 0;
	//for(int chess = PieceListStart(pos,pos->b256[to]); chess > 0x32; chess = NextPiece(pos,chess)){
	//	if(chess == to){          
	//		break;
	//	}	
	//	order++;		
	//}

   //---------------------------------------------------------------------------
   //3, ���ж�һ�����׽����ļ�ֵ�ǲ��Ǳȱ�׽����ļ�ֵС
   //---------------------------------------------------------------------------
	if(PieceValues[pos->b256[from]] >= PieceValues[pos->b256[to]]){
		//---------------------------------------------------------------------------
		//4, ���˫����������ͬ,��Ҫ�ж� 1, ��������ܲ�����, 2, ������ܲ��ܷ��ԶԷ�(��)
		//---------------------------------------------------------------------------
		if(PIECE_ID(pos->b256[from]) == to_id){

			//===================================================================================================
			//
			if(Is_Can_Move_To_Eat(pos,to,from) == TRUE ){ 
				if(to_id != MA) return;
				//fen 3ak4/4a4/2ncb4/4N4/2p1P1b2/6B2/2P6/1N7/9/3AKAB2 b - - 157 157 �������
				//fen 3ak4/4a4/2ncb4/4N4/2p3b2/6B2/2P6/1N7/9/3AKAB2 b ����ǳ�׽
				int m = horseLegTab(from - to + 256);
				if(pos->b256[to+m] == EMPTY) return;   //������ܲ��ܷ��ԶԷ�
				////����������,��Ҫ��һ��������ܲ��ܳԵ��Է�
			}
		}
		//---------------------------------------------------------------------------
		//5, �ٿ�һ���������û�����������ӱ�����
		//---------------------------------------------------------------------------
		//a, ����һ��from,to��File,Rank��Ϣ,			
		//-------------------------------------------------------
		int cap   = pos->b256[to];
		int piece = pos->b256[from];
		ASSERT(cap != EMPTY);
		RemovePiece(pos,to);  //��ʱ��ȥ,����Ϊȥ���Ժ����Ĵ��򲻶���. 

		pos->wBitRanks[StoY(from)]  ^= xBitMask(from);
		pos->wBitFiles[StoX(from)]  ^= yBitMask(from);

		MovePiece(pos,from,to);
		//board
		pos->b256[to]      = piece;
		pos->b256[from]    = EMPTY;
		//-------------------------------------------------------
		//���û�г���,ҲҪ����TO

		//b, �ٿ�һ����û�����������ӱ�����
		BOOL isP = isPretectedd(pos,which,to,EMPTY);
		//BOOL isP = isPretectedd(pos,which,to,to);

		//c, ��ԭһ��from,to��File,Rank��Ϣ,
		pos->wBitRanks[StoY(from)] ^= xBitMask(from);
		pos->wBitFiles[StoX(from)] ^= yBitMask(from);

		//P256
		pos->b256[from] = piece;
		pos->b256[to]   = cap;

		MovePiece(pos,to,from);
		InsertPiece(pos,cap,to);
		//-------------------------------------------------------

		if(isP == TRUE) return;
		//}		
	}
	//���ϴε�׽���бȶ�
	//��������ж�һ���ǲ���׽��ͬһ������-------------========================================================

	//����ж�����׽��, Ҫ�����ж��Ǹ�׽, ����������.
	//fen 3a1kb2/2r6/4ba3/p6Np/9/P3p1RcP/9/4B4/4A4/2BK1A3 b - - 53 53 
	//fen r2akab2/1c7/2n1b1c2/p1R1p3p/5nr2/9/P3P2NP/1CN1C4/5R3/2BAKAB2 b - - 16 16 

	//���汾�ε�׽
	int num  = pos->cap_num[0][which];

	pos->LastCapChess[num][0][which]      = to_id;  //���ֻ��׽������,
	pos->last_to[num][0][which]           = to;     //
	pos->last_ot_from[num][0][which]      = ot_from;
	//pos->last_ot_to[num][0][which]        = ot_to;  

	if(num < MAX_REAL_CAP_NUM - 1){   //���ͬʱ�ж�������׽
	   pos->cap_num[0][which]++;
	}

}

//for(int from = PieceListStart(pos,RCHE); from > 0x32; from = NextPiece(pos,from)){


//enum  {
//       EMPTY=0,
//       RKING=1,  RSHI=2,RXIANG=3, RMA=4, RCHE=5, RPAO=6, RPAWN=7,
//       BKING=8,  BSHI=9,BXIANG=10,BMA=11,BCHE=12,BPAO=13,BPAWN=14,
//       EMPTY16=16, OUTSIDE=32};


	//if(last_id == EMPTY){
	//	//******ֻ��׽�˲��ܸ����� start
	//	board->LastCapChess[which] = to_id;
	//	board->last_to[which]      = to;              //�������׽�Է������
	//	board->ot_from[which]      = ot_from;
	//	//******ֻ��׽�˲��ܸ����� end
	//	return TRUE;                           //ֻ�з���׽�Ӳ�,�Ÿ���һ���ϴ�׽������
	//}
	//else if(last_id == to_id){  //������ܻ�Ҫ�ж�һ���ǲ��ǳԵ�ͬһ������,�����ƶ����Ǹ�

	//	if(last_ot_from == to || last_to == to){                 //�Է�����,����׽��
	//		//******ֻ��׽�˲��ܸ����� start
	//		board->LastCapChess[which] = to_id;
	//		board->last_to[which]      = to;              //�������׽�Է������
	//		board->ot_from[which]      = ot_from;
	//		//******ֻ��׽�˲��ܸ����� end
	//		return TRUE;
	//	}
	//	//if(last_to == to){                     //������ڴ�
	//	//	//******ֻ��׽�˲��ܸ����� start
	//	//	board->LastCapChess[which] = to_id;
	//	//	board->last_to[which]      = to;              //�������׽�Է������
	//	//	board->ot_from[which]      = ot_from;
	//	//	//******ֻ��׽�˲��ܸ����� end
	//	//	return TRUE;
	//	//}
	//}