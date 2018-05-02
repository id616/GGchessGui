#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"

//�������е��߲�
move_stack_t *generate_moves(position_t *pos, move_stack_t *ms) {

    if(pos->side == WHITE){     //�������еĺ췽�߲�
        //�쳵
        for(int from = PieceListStart(pos,RCHE); from > 0x32; from = NextPiece(pos,from)){

            int tmp = MOVE_FromFC(from,RCHE);
            int x   = StoX(from);
            int y   = StoY(from);

            //������Ӳ�
            int nDisp;
            SlideMoveStruct* psmv;

            //nDisp = y * 16;
            nDisp = from & 0xf0;
            //psmv  = smvRankMoveTab[x-3] +  pos->wBitRanks[y]; 

            psmv = RankMove(x,pos->wBitRanks[y]);

            int to = psmv->RookCap[DUpLeft] + nDisp;            
            if(to != from){                
                if(IsBlack(pos->b256[to])){
                    (ms++)->move =  MOVE_FromFc_to_tc(tmp,to,pos->b256[to]);
                }
            }

            to = psmv->RookCap[DLoRight] + nDisp;
            if(to != from){                
                if(IsBlack(pos->b256[to])){
                    (ms++)->move =  MOVE_FromFc_to_tc(tmp,to,pos->b256[to]);
                }
            }

            //�����Ӳ�
            to = psmv->NonCap[DUpLeft] + nDisp;
            while(to != from){
                (ms++)->move =  MOVE_FromFc_to(tmp,to);                
                to++;
            }
            to = psmv->NonCap[DLoRight] + nDisp;
            while(to != from){
                (ms++)->move =  MOVE_FromFc_to(tmp,to);                
                to--;
            }


            //������Ӳ�
            //nDisp = x;
            //psmv  = smvFileMoveTab[y-3] + pos->wBitFiles[x];

            psmv   = FileMove(y,pos->wBitFiles[x]);

            to = psmv->RookCap[DUpLeft] + x;
            if(to != from){                
                if(IsBlack(pos->b256[to])){
                    (ms++)->move =  MOVE_FromFc_to_tc(tmp,to,pos->b256[to]);
                }
            }

            to = psmv->RookCap[DLoRight] + x;
            if(to != from){                
                if(IsBlack(pos->b256[to])){
                    (ms++)->move =  MOVE_FromFc_to_tc(tmp,to,pos->b256[to]);
                }
            }
            //���򲻳��Ӳ�
            to = psmv->NonCap[DUpLeft] + x;
            while(to != from){
                (ms++)->move =  MOVE_FromFc_to(tmp,to);    
                to += 16;
            }
            to = psmv->NonCap[DLoRight] + x;
            while(to != from){
                (ms++)->move =  MOVE_FromFc_to(tmp,to);    
                to -= 16;
            }
        }

        //����
        for(int from = PieceListStart(pos,RPAO); from > 0x32; from = NextPiece(pos,from)){

            int tmp = MOVE_FromFC(from,RPAO);
            int x   = StoX(from);
            int y   = StoY(from);

            int nDisp;
            SlideMoveStruct* psmv;

            //nDisp = y * 16;
            nDisp = from & 0xf0;
            //psmv  = smvRankMoveTab[x-3] +  pos->wBitRanks[y]; 

            psmv  = RankMove(x,pos->wBitRanks[y]);

            int to = psmv->CannonCap[DUpLeft] + nDisp;            
            if(to != from){                
                if(IsBlack(pos->b256[to])){
                    (ms++)->move =  MOVE_FromFc_to_tc(tmp,to,pos->b256[to]);
                }
            }

            to = psmv->CannonCap[DLoRight] + nDisp;
            if(to != from){                
                if(IsBlack(pos->b256[to])){
                    (ms++)->move =  MOVE_FromFc_to_tc(tmp,to,pos->b256[to]);
                }
            }

            //�����Ӳ�
            to = psmv->NonCap[DUpLeft] + nDisp;
            while(to != from){
                (ms++)->move =  MOVE_FromFc_to(tmp,to);                
                to++;
            }
            to = psmv->NonCap[DLoRight] + nDisp;
            while(to != from){
                (ms++)->move =  MOVE_FromFc_to(tmp,to);                
                to--;
            }

            //������Ӳ�
            //nDisp = x;
            //psmv  = smvFileMoveTab[y-3] + pos->wBitFiles[x];

            psmv = FileMove(y,pos->wBitFiles[x]);

            to = psmv->CannonCap[DUpLeft] + x;
            if(to != from){                
                if(IsBlack(pos->b256[to])){
                    (ms++)->move =  MOVE_FromFc_to_tc(tmp,to,pos->b256[to]);
                }
            }

            to = psmv->CannonCap[DLoRight] + x;
            if(to != from){                
                if(IsBlack(pos->b256[to])){
                    (ms++)->move =  MOVE_FromFc_to_tc(tmp,to,pos->b256[to]);
                }
            }

            //���򲻳��Ӳ�
            to = psmv->NonCap[DUpLeft] + x;
            while(to != from){
                (ms++)->move =  MOVE_FromFc_to(tmp,to);    
                to += 16;
            }
            to = psmv->NonCap[DLoRight] + x;
            while(to != from){
                (ms++)->move =  MOVE_FromFc_to(tmp,to);    
                to -= 16;
            }
        }

        //����������߲�
        for(int from = PieceListStart(pos,RMA); from > 0x32; from = NextPiece(pos,from)){

            int tmp      = MOVE_FromFC(from,RMA);
            uint8* lpDst = PreMaAndLegMove[from];

            while(int to = *lpDst++){ 
                if(pos->b256[*lpDst] == 0){ //����û����
                    //int tochess = pos->b256[to];
                    //if(tochess == EMPTY){
                    //    (ms++)->move =  MOVE_FromFc_to(tmp,to);  
                    //}
                    //else if(tochess >= BKING) {
                    //    (ms++)->move =  MOVE_FromFc_to_tc(tmp,to,tochess);
                    //} 

                    if(NotWhite(pos->b256[to])){
                        (ms++)->move =  MOVE_FromFc_to_tc(tmp,to,pos->b256[to]);
                    }
                }
                lpDst++;
            }
        }
        //����������߲�
        for(int from = PieceListStart(pos,RPAWN); from > 0x32; from = NextPiece(pos,from)){

            int      tmp = MOVE_FromFC(from,RPAWN);
            /*uint8* lpDst = PrePawnMove[pos->side][from];*/
            uint8* lpDst = PreRPawnMove[from];

            while(int to = *lpDst++){   
                if(NotWhite(pos->b256[to])){
                    (ms++)->move =  MOVE_FromFc_to_tc(tmp,to,pos->b256[to]);
                }
            }
        }
        //����������߲�
        for(int from = PieceListStart(pos,RXIANG); from > 0x32; from = NextPiece(pos,from)){

            int      tmp = MOVE_FromFC(from,RXIANG);
            uint8* lpDst = PreShiXiangAndEyeMove[from];

            while(int to = *lpDst++){
                if(pos->b256[*lpDst] == 0){    //����û����
                    if(NotWhite(pos->b256[to])){
                        (ms++)->move =  MOVE_FromFc_to_tc(tmp,to,pos->b256[to]);
                    }
                }
                lpDst++;
            }
        }

        //��ʿ�������߲�
        for(int from = PieceListStart(pos,RSHI); from > 0x32; from = NextPiece(pos,from)){
            int      tmp = MOVE_FromFC(from,RSHI);
            uint8* lpDst = PreShiXiangAndEyeMove[from];

            while(int to = *lpDst++){
                if(NotWhite(pos->b256[to])){
                    (ms++)->move =  MOVE_FromFc_to_tc(tmp,to,pos->b256[to]);
                }
            }
        }

        //��˧�������߲�
        int from = PieceListStart(pos,RKING);

        ASSERT(from != 0);

        int     tmp   = MOVE_FromFC(from,RKING);
        uint8*  lpDst = PreKingMove[from];

        while(int to = *lpDst++){
            if(NotWhite(pos->b256[to])){
                (ms++)->move =  MOVE_FromFc_to_tc(tmp,to,pos->b256[to]);
            }
        }
    }
    else{                       //�������еĺڷ��߲� ***************************************************
        //�ڳ�
        for(int from = PieceListStart(pos,BCHE); from > 0x32; from = NextPiece(pos,from)){

            int tmp = MOVE_FromFC(from,BCHE);
            int x   = StoX(from);
            int y   = StoY(from);

            //������Ӳ�
            int nDisp;
            SlideMoveStruct* psmv;

            //nDisp = y * 16;
            nDisp = from & 0xf0;
            //psmv  = smvRankMoveTab[x-3] +  pos->wBitRanks[y]; 

            psmv = RankMove(x,pos->wBitRanks[y]); 

            int to = psmv->RookCap[DUpLeft] + nDisp;            
            if(to != from){                
                if(IsWhite(pos->b256[to])){
                    (ms++)->move =  MOVE_FromFc_to_tc(tmp,to,pos->b256[to]);
                }
            }

            to = psmv->RookCap[DLoRight] + nDisp;
            if(to != from){                
                if(IsWhite(pos->b256[to])){
                    (ms++)->move =  MOVE_FromFc_to_tc(tmp,to,pos->b256[to]);
                }
            }

            //�����Ӳ�
            to = psmv->NonCap[DUpLeft] + nDisp;
            while(to != from){
                (ms++)->move =  MOVE_FromFc_to(tmp,to);                
                to++;
            }
            to = psmv->NonCap[DLoRight] + nDisp;
            while(to != from){
                (ms++)->move =  MOVE_FromFc_to(tmp,to);                
                to--;
            }

            //������Ӳ�
            //nDisp = x;
            //psmv  = smvFileMoveTab[y-3] + pos->wBitFiles[x];

            psmv = FileMove(y,pos->wBitFiles[x]);

            to = psmv->RookCap[DUpLeft] + x;
            if(to != from){
                if(IsWhite(pos->b256[to])){
                    (ms++)->move =  MOVE_FromFc_to_tc(tmp,to,pos->b256[to]);
                }
            }

            to = psmv->RookCap[DLoRight] + x;
            if(to != from){
                if(IsWhite(pos->b256[to])){
                    (ms++)->move =  MOVE_FromFc_to_tc(tmp,to,pos->b256[to]);
                }
            }

            //���򲻳��Ӳ�
            to = psmv->NonCap[DUpLeft] + x;
            while(to != from){
                (ms++)->move =  MOVE_FromFc_to(tmp,to);    
                to += 16;
            }
            to = psmv->NonCap[DLoRight] + x;
            while(to != from){
                (ms++)->move =  MOVE_FromFc_to(tmp,to);    
                to -= 16;
            }

        }

        //����
        for(int from = PieceListStart(pos,BPAO); from > 0x32; from = NextPiece(pos,from)){

            int tmp = MOVE_FromFC(from,BPAO);
            int x   = StoX(from);
            int y   = StoY(from);

            //������Ӳ�

            int nDisp;
            SlideMoveStruct* psmv;

            //nDisp = y * 16;
            nDisp = from & 0xf0;
            //psmv  = smvRankMoveTab[x-3] +  pos->wBitRanks[y];    

            psmv = RankMove(x,pos->wBitRanks[y]);    

            int to = psmv->CannonCap[DUpLeft] + nDisp;            
            if(to != from){
                if(IsWhite(pos->b256[to])){
                    (ms++)->move =  MOVE_FromFc_to_tc(tmp,to,pos->b256[to]);
                }
            }

            to = psmv->CannonCap[DLoRight] + nDisp;
            if(to != from){
                if(IsWhite(pos->b256[to])){
                    (ms++)->move =  MOVE_FromFc_to_tc(tmp,to,pos->b256[to]);
                }
            }

            //�����Ӳ�
            to = psmv->NonCap[DUpLeft] + nDisp;
            while(to != from){
                (ms++)->move =  MOVE_FromFc_to(tmp,to);                
                to++;
            }
            to = psmv->NonCap[DLoRight] + nDisp;
            while(to != from){
                (ms++)->move =  MOVE_FromFc_to(tmp,to);                
                to--;
            }

            //������Ӳ�
            //nDisp = x;
            //psmv  = smvFileMoveTab[y-3] + pos->wBitFiles[x];

            psmv = FileMove(y,pos->wBitFiles[x]);

            to = psmv->CannonCap[DUpLeft] + x;
            if(to != from){
                if(IsWhite(pos->b256[to])){
                    (ms++)->move =  MOVE_FromFc_to_tc(tmp,to,pos->b256[to]);
                }
            }

            to = psmv->CannonCap[DLoRight] + x;
            if(to != from){
                if(IsWhite(pos->b256[to])){
                    (ms++)->move =  MOVE_FromFc_to_tc(tmp,to,pos->b256[to]);
                }
            }

            //���򲻳��Ӳ�
            to = psmv->NonCap[DUpLeft] + x;
            while(to != from){
                (ms++)->move =  MOVE_FromFc_to(tmp,to);    
                to += 16;
            }
            to = psmv->NonCap[DLoRight] + x;
            while(to != from){
                (ms++)->move =  MOVE_FromFc_to(tmp,to);    
                to -= 16;
            }

            ////�ڵĳ��Ӳ�  ������Ӳ�
            //uint8* lpDst =  PreRankPaoEat[x-3][pos->wBitRanks[y]];
            //while (int to = *lpDst++){

            //    to = (from & 0xf0) | to;
            //    int tochess = pos->b256[to];
            //    if(tochess < BKING){
            //        (ms++)->move =  MOVE_FromFc_to_tc(tmp,to,tochess);
            //    }
            //}
            ////�ڵĳ��Ӳ�, ������Ӳ�
            //lpDst = PreFilePaoEat[y-3][pos->wBitFiles[x]];
            //while(int to = *lpDst++){

            //    to = to | x;
            //    int tochess = pos->b256[to];
            //    if(tochess < BKING){
            //        (ms++)->move =  MOVE_FromFc_to_tc(tmp,to,tochess);
            //    }
            //}

            ////�ڵĲ����Ӳ�  ���򲻳��Ӳ�
            //lpDst =  PreRankChePaoNotEat[x-3][pos->wBitRanks[y]];
            //while (int to = *lpDst++){
            //    to = (from & 0xf0) | to;
            //    (ms++)->move =  MOVE_FromFc_to(tmp,to);

            //}
            ////�ڵĲ����Ӳ�, ���򲻳��Ӳ�
            //lpDst = PreFileChePaoNotEat[y-3][pos->wBitFiles[x]];
            //while(int to = *lpDst++){  
            //    to = to | x;                    
            //    (ms++)->move =  MOVE_FromFc_to(tmp,to);                
            //}
        }

        //����������߲�
        for(int from = PieceListStart(pos,BMA); from > 0x32; from = NextPiece(pos,from)){

            int tmp      = MOVE_FromFC(from,BMA);
            uint8* lpDst = PreMaAndLegMove[from];

            while(int to = *lpDst++){ 
                if(pos->b256[*lpDst] == 0){ //����û����
                    //int tochess = pos->b256[to];
                    //if(tochess == EMPTY){
                    //    (ms++)->move =  MOVE_FromFc_to(tmp,to);  
                    //}
                    //else if(tochess < BKING) {
                    //    (ms++)->move =  MOVE_FromFc_to_tc(tmp,to,tochess);
                    //} 

                    if(NotBlack(pos->b256[to])){
                        (ms++)->move =  MOVE_FromFc_to_tc(tmp,to,pos->b256[to]);
                    }
                }
                lpDst++;
            }
        }
        //�ڱ��������߲�
        for(int from = PieceListStart(pos,BPAWN); from > 0x32; from = NextPiece(pos,from)){

            int      tmp = MOVE_FromFC(from,BPAWN);
            /*uint8* lpDst = PrePawnMove[pos->side][from];*/
            uint8* lpDst = PreBPawnMove[from];

            while(int to = *lpDst++){                
                //int tochess = pos->b256[to];
                //if(tochess == EMPTY){
                //    (ms++)->move =  MOVE_FromFc_to(tmp,to);  
                //}
                //else if(tochess < BKING){
                //    (ms++)->move =  MOVE_FromFc_to_tc(tmp,to,tochess);
                //}
                if(NotBlack(pos->b256[to])){
                    (ms++)->move =  MOVE_FromFc_to_tc(tmp,to,pos->b256[to]);
                }
            }
        }
        //����������߲�
        for(int from = PieceListStart(pos,BXIANG); from > 0x32; from = NextPiece(pos,from)){

            int      tmp = MOVE_FromFC(from,BXIANG);
            uint8* lpDst = PreShiXiangAndEyeMove[from];

            while(int to = *lpDst++){
                if(pos->b256[*lpDst] == 0){    //����û����
                    //int tochess = pos->b256[to];
                    //if(tochess == EMPTY){
                    //    (ms++)->move =  MOVE_FromFc_to(tmp,to);  
                    //}
                    //else if(tochess < BKING){
                    //    (ms++)->move =  MOVE_FromFc_to_tc(tmp,to,tochess);
                    //}
                    if(NotBlack(pos->b256[to])){
                        (ms++)->move =  MOVE_FromFc_to_tc(tmp,to,pos->b256[to]);
                    }
                }
                lpDst++;
            }
        }

        //��ʿ�������߲�
        for(int from = PieceListStart(pos,BSHI); from > 0x32; from = NextPiece(pos,from)){
            int      tmp = MOVE_FromFC(from,BSHI);
            uint8* lpDst = PreShiXiangAndEyeMove[from];

            while(int to = *lpDst++){
                //int tochess = pos->b256[to];
                //if(tochess == EMPTY){
                //    (ms++)->move =  MOVE_FromFc_to(tmp,to);  
                //}
                //else if(tochess < BKING){
                //    (ms++)->move =  MOVE_FromFc_to_tc(tmp,to,tochess);
                //}
                if(NotBlack(pos->b256[to])){
                    (ms++)->move =  MOVE_FromFc_to_tc(tmp,to,pos->b256[to]);
                }
            }
        }

        //�ڽ��������߲�
        int from = PieceListStart(pos,BKING);

        ASSERT(from != 0);

        int     tmp   = MOVE_FromFC(from,BKING);
        uint8*  lpDst = PreKingMove[from];

        while(int to = *lpDst++){
            //int tochess = pos->b256[to];
            //if(tochess == EMPTY){
            //    (ms++)->move =  MOVE_FromFc_to(tmp,to);  
            //}
            //else if(tochess < BKING){
            //    (ms++)->move =  MOVE_FromFc_to_tc(tmp,to,tochess);
            //}
            if(NotBlack(pos->b256[to])){
                (ms++)->move =  MOVE_FromFc_to_tc(tmp,to,pos->b256[to]);
            }
        }
    }

    return ms;
}



