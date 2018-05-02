#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"





BOOL Is_BanMove_By_Pos_Now(dispboard_t* pDis){
    
	position_t* nowpos = pDis->pos;
	nowpos->gply++;
	int res = ban_repeat(nowpos);
	nowpos->gply --;

	switch(res){
		case REPEAT_TRUE:      //�ظ��߲�
			//LogOut("\n˫���߲��ظ���!\n");
			return false;
			break;
		case REPEAT_NO:			//�����ӳ�����120��
			//LogOut("\n˫��REPEAT_NO!");
			return false;
			break;
		case REPEAT_BAN_OTHER:
			//LogOut(ColorSeek,"����,�Է�����,�Է���������׽!",false);
			LogOut(_T("\n����,�Է�����,�Է���������׽! �˲��ӿ��ֿ���ȥ��\n"));
			LogOut(_T("REPEAT_BAN_OTHER!"));
			return true;
			break;
		//case BLACK_CHECK_BAN:
		case REPEAT_BAN_ME:
			LogOut(_T("\n��������������׽��! ! �˲��ӿ��ֿ��в�ȥ��"));
			LogOut(_T("REPEAT_BAN_OTHER!"));
			return false;
			break;
		default:
			break;
	}

	return false;
}

BOOL isWhiteGo_By_FaceInfo(uint8* f33){

	switch(f33[0]){
		case 'f':
		case 'g':
		case 'h':

		case 'o':
		case 'p':
		case 'q':

		case 'x':
		case 'y':
		case 'z':
			return 1;  //return true;
		case '#':
		case '$':
		case '%':

		case ',':
		case '-':
		case '.':

		case '5':
		case '6':
		case '7':
			return 0;
		default:
			LogOut(_T("\n�������������,����λ���д�"));
			return 2;
	}

	return 2;
}

int Book_Back_Up(DB* dst, DB* src){
	//��src �е��岽ȫ�����浽dst��

	//�ù��������
	int ret;

	DBC *cur;

	src->cursor(src,NULL, &cur,0);

	DBT key, data;
	
    int num = 0;

	do{
		memset(&key, 0, sizeof(DBT));
		memset(&data,0, sizeof(DBT));

		ret = cur->c_get(cur, &key, &data,DB_NEXT);                  //�õ�һ������

		if(ret != 0){
			break;
		}

		//key.data  = bft->f33;

		//struct book_face_t {
		//	uint8  f33[33];
		//	book_face_info_t info[1];
		//};

		uint8* f33 = (uint8*)key.data;


		
		book_face_info_t *binfo = (book_face_info_t*)data.data;

	
	    //��������ж�һ���ǲ��Ǻõ��岽,���������STEP���ж���
		
		int isw = isWhiteGo_By_FaceInfo(f33);

		if(isw  == 1){
			if(binfo->result < BOOK_BALANCE){
				continue;
			}
		}
		else if(isw == 0){
			if(binfo->result > BOOK_BALANCE){
				continue;
			}
		}
		else if (isw == 2){
			continue;
		}


		//д����Ӧ������
		ret = dst->put(dst, NULL, &key, &data, 0);

		if (ret){
			LogOut(_T("\n����д��������ݵ��������ݿ���!!\n"));
			break;
		}
		num++;

	}while(true);

	if(cur != NULL){
		ret = cur->c_close(cur);
	}

	TCHAR buf[512];
	swprintf_s(buf, sizeof(buf) / sizeof(TCHAR), _T("\n�ɹ������� %d ����!!\n"), num);

	LogOut(buf);

	return ret;
}



BOOL is_book_face_ok(book_face_t *bft){
	if(abs(bft->info->result) > 2){
		return FALSE;
	}
	//if(bft->info->step > 250){
	//	return FALSE;
	//}
	//if(bft->info->rate > 100){
	//	return FALSE;
	//}
	if(abs(bft->info->isuse) > 1){
		return FALSE;
	}
	return TRUE;
}

//////////////////////////////////////////////////
/// ֻ���浱ǰ�ľ���÷ֵ������ȥ��
void UpDataOneFaceEvent(dispboard_t* pDis, DB *db){

	book_face_t last_face[1];
	last_face->info->result = BOOK_NOT_RESULT;

	//last_face->info->rate = 50;
	last_face->info->isuse = 1;
	//last_face->info->stepp = 60;

	position_t pos[1];

	memcpy(pos, pDis->pos, sizeof(position_t));

	//�õ��÷�
	if (false){
	}
	else if (IsDlgButtonChecked(HWND_SAVE, IDC_VERY_GOOD) == BST_CHECKED){
		last_face->info->result = BOOK_VERY_GOOD;
	}
	else if (IsDlgButtonChecked(HWND_SAVE, IDC_LIT_GOOD) == BST_CHECKED){
		last_face->info->result = BOOK_LIT_GOOD;
	}
	else if (IsDlgButtonChecked(HWND_SAVE, IDC_BALANCE) == BST_CHECKED){
		last_face->info->result = BOOK_BALANCE;
	}
	else if (IsDlgButtonChecked(HWND_SAVE, IDC_LIT_BAD) == BST_CHECKED){
		last_face->info->result = BOOK_LIT_BAD;
	}
	else if (IsDlgButtonChecked(HWND_SAVE, IDC_VERY_BAD) == BST_CHECKED){
		last_face->info->result = BOOK_VERY_BAD;
	}

	if (last_face->info->result == BOOK_NOT_RESULT){
		LogOut(_T("�㻹û���趨��ǰ����ĵ÷�!!\n"));
		return;
	}

	GetMirrorOnlyB33(pos, last_face->f33);
	if (!bk_SaveBookInfo(last_face, db)){
		LogOut(L"\n���浥������ɹ��ˣ�");
	}//�Ƚ���ǰ�ı���һ��
	else{
		LogOut(L"\n���浥������ʧ���ˣ�");
	}

	

	return;

}


//�õ���ǰ�����岽��Ϣ
int bk_GetBookInfo(book_face_t* bft, DB *db){
	
	int ret;

	DBT key,data;
	memset(&key, 0, sizeof(DBT));
	memset(&data,0, sizeof(DBT));

	//memset(bft->info,0,sizeof(book_face_info_t));

	bft->info->result = BOOK_NOT_RESULT;
	//bft->info->rate   = 0;
	bft->info->isuse  = 0;

	key.data  = bft->f33;
	key.size  = 33;
	data.ulen = sizeof(book_face_info_t);

	ret = db->get(db,NULL,&key,&data,0);

	if(ret == 0){
		book_face_info_t *binfo = (book_face_info_t*)data.data;

		bft->info->isuse  = binfo->isuse;
		//bft->info->rate   = binfo->rate;
		bft->info->result = binfo->result;
		//bft->info->step   = binfo->step;
	}
	//else{
	//	bft->info->result = BOOK_NOT_RESULT;
	//}

	return ret;
}

//��ǰ�ǲ���������岽����
int HaveBookMoveInDB(dispboard_t* pDis){

	if(pDis->book_num > 0){  //���������߲�

#ifdef USE_RAND_BOOK_MOVE		
		int ra = 0;
		srand((int)time(0));
		ra = rand() % pDis->book_num;
		return pDis->book_move[ra];
#else
		return pDis->book_move[pDis->book_max_num];
#endif

	}
	else{
		return 0;
	}
}


//ͨ����ǰ����ĺ����ŷ��õ��÷�
int GetPosBookScoreByAllNextPos(position_t *pos, DB *db){	
	int preScore;

	int  preSide   = pos->side;

	if(preSide == WHITE){			//��ǰ�Ǻ��ߵĻ��������ķ�Խ��Խ��
		preScore = -BOOK_NOT_RESULT;
	}
	else{			                //��ǰ�Ǻ��ߵĻ���ȡ�������С��
		preScore = BOOK_NOT_RESULT;
	}

	//�������е��߲�
	gen_legal_moves(pos);

	while(pos->pMend > pos->all_move){

		pos->pMend--;

		
		if (move_is_legal(pos, pos->pMend->move) == FALSE){		//�߲����Ϸ�
			continue;
		}
		

		MakePosMoveOnly(pos,pos->pMend->move);			//��һ����������curStep

		GetMirrorOnlyB33(pos,pos->book_face->f33);

		//pos->book_face->info->step = pos->curStep;
		bk_GetBookInfo(pos->book_face,db);

		int res = pos->book_face->info->result;

		if((res != BOOK_NOT_RESULT)){
			//if(pos->book_face->info->step == pos->curStep){
				if(preSide == WHITE){
					if(res > preScore){
						preScore = res;
						if(res == BOOK_VERY_GOOD){
							UnMakePosMoveOnly(pos);
							break;
						}
					}
				}
				else{
					if(res < preScore){
						preScore = res;
						if(res == BOOK_VERY_BAD){
							UnMakePosMoveOnly(pos);
							break;
						}
					}
				}
			//}
		}

		UnMakePosMoveOnly(pos);
	}

	if(abs(preScore) == BOOK_NOT_RESULT){
		return BOOK_NOT_RESULT;
	}
	else{
		return preScore;
	}
}

int bk_SaveBookInfo(book_face_t* bft, DB *db){
	
	int ret;
	
	//1

	if(is_book_face_ok(bft) == FALSE){
		LogOut((TCHAR*)(bft->f33));
		LogOut(_T("\nDB_ERR: ��ǰҪ������岽����ȷ����\n"));
		return -1;
	}

	//2 	
	// ��鵱ǰ������岽��STEP�ǲ��Ǵ��ڵ�ǰ��������еģ�
	//���У�˵�����ظ��������ܴ���

	//book_face_info_t pre = bft->info[0];

	//int oldStep = 
	//
	//bk_GetBookInfo(bft,db);

	//if(bft->info->step != 0){
	//	if(bft->info->step < pre.step){
	//		LogOut("��ǰ��������д��岽���Ҳ����ȵ�ǰҪ�����С\n");
	//		LogOut((char*)bft->f33);
	//		return -1;
	//	}
	//}

	//bft->info[0] = pre;


	//3

	DBT key,data;
	memset(&key, 0, sizeof(DBT));
	memset(&data,0, sizeof(DBT));

    //
	key.data	= bft->f33;
	key.size	= 33;
	data.data   = &bft->info[0];
	data.size	= sizeof(book_face_info_t);

	ret = db->put(db,NULL,&key,&data,0);


	db->sync(db,0);

	return ret;
}


//�������ĵ÷֣��õ�����ַ���
TCHAR* BookScoreToChar(int score){

	switch (score){
	case BOOK_VERY_GOOD:
		return _T("�����");
		break;
	case BOOK_LIT_GOOD:
		return _T("������");
		break;
	case BOOK_BALANCE:
		return _T("  ����");
		break;
	case BOOK_LIT_BAD:
		return _T("������");
		break;
	case BOOK_VERY_BAD:
		return _T("�ڴ���");
		break;
	default:
		return _T(" ");
		break;
	}	
}


void UpdateBookResult(dispboard_t * pDis, DB *db){


	position_t pos[1];
	book_face_t last_face[1];
	book_face_t tmp_face[1];
	
	memcpy(pos,pDis->pos,sizeof(position_t));	

	last_face->info->result = BOOK_NOT_RESULT;

	//�õ��÷�
	if(false){
	}
	else if (IsDlgButtonChecked(HWND_SAVE, IDC_VERY_GOOD) == BST_CHECKED){
		last_face->info->result = BOOK_VERY_GOOD;
	}
	else if (IsDlgButtonChecked(HWND_SAVE, IDC_LIT_GOOD) == BST_CHECKED){
		last_face->info->result = BOOK_LIT_GOOD;
	}
	else if (IsDlgButtonChecked(HWND_SAVE, IDC_BALANCE) == BST_CHECKED){
		last_face->info->result = BOOK_BALANCE;
	}
	else if (IsDlgButtonChecked(HWND_SAVE, IDC_LIT_BAD) == BST_CHECKED){
		last_face->info->result = BOOK_LIT_BAD;
	}
	else if (IsDlgButtonChecked(HWND_SAVE, IDC_VERY_BAD) == BST_CHECKED){
		last_face->info->result = BOOK_VERY_BAD;
	}

	if(last_face->info->result == BOOK_NOT_RESULT){
		LogOut(_T("�㻹û���趨��ǰ����ĵ÷�!!\n"));
		return;
	}

	last_face->info->isuse = FALSE;

	
	//�õ���ǰ��B28

	GetMirrorOnlyB33(pos,last_face->f33);

	int nextScore = GetPosBookScoreByAllNextPos(pos,db);

	int  num = 0;

	//int oldStep   = pos->curStep; 

	//face->info->isuse = lastIsUse;

	

	if(nextScore == BOOK_NOT_RESULT){
		//����û�е÷��ˣ�Ҫȫ�����£��Ӻ�����ǰ

		//tmp_face = last_face;

		memcpy(tmp_face,last_face,sizeof(book_face_t));

		bk_SaveBookInfo(tmp_face,db);		//�Ƚ���ǰ�ı���һ��

		while((pos->curStep) > 0){


			UnMakePosMoveOnly(pos);

			GetMirrorOnlyB33(pos,tmp_face->f33);

			//tmp_face->info->step = pos->curStep;
          
			bk_GetBookInfo(tmp_face,db);

			nextScore = GetPosBookScoreByAllNextPos(pos,db);

			if(nextScore == BOOK_NOT_RESULT){
				LogOut(_T("�����ˣ�������岽�Ҳ�������"));
				break;
			}

			if(tmp_face->info->result == BOOK_NOT_RESULT){		//���Ҳ���¾���
				//tmp_face->info->step		= pos->curStep;
				tmp_face->info->isuse		= last_face->info->isuse;
				//tmp_face->info->rate		= last_face->info->rate;
			}

			if(pos->side == WHITE){		//����������̫���Ҫrate,��Ҫisuse
				if(nextScore == BOOK_VERY_GOOD){
					tmp_face->info->isuse		= 0;
					//tmp_face->info->rate		= 0;
				}
				else if(nextScore <= BOOK_BALANCE){
					tmp_face->info->isuse		= 1;
				}
			}
			else{
				if(nextScore == BOOK_VERY_BAD){
					tmp_face->info->isuse		= 0;
					//tmp_face->info->rate		= 0;
				}
				else if(nextScore >= BOOK_BALANCE){
					tmp_face->info->isuse		= 1;
				}
			}


			tmp_face->info->result       = nextScore;
			bk_SaveBookInfo(tmp_face,db);			

			num++;	
			
		}


		//1,�õ���ǰ�ľ������Ϣ

	}
	else{		
		last_face->info->result = nextScore;
		bk_SaveBookInfo(last_face,db);			//ֻҪ���µ�ǰ��һ������,��Ϊ�к���ķ�

		num++;
	}

    
	TCHAR buf[128];

	swprintf_s(buf, sizeof(buf) / sizeof(TCHAR), _T("\n������ %d ��������!!\n"), num);

	LogOut(buf);

	//SendToPlayerByColor(buf,ColorSeek,FALSE);

};

//�������÷֣�������Ӧ�İ�ť
void UpDateBookScoreButton(int score){
	//SendDlgItemMessage(HWND_BOOK,IDC_VERY_GOOD,1,0);

	//1,�Ƚ����еİ�ť������˵
	SendDlgItemMessage(HWND_SAVE, IDC_VERY_GOOD, BM_SETCHECK, 0, 0);
	SendDlgItemMessage(HWND_SAVE, IDC_LIT_GOOD, BM_SETCHECK, 0, 0);
	SendDlgItemMessage(HWND_SAVE, IDC_BALANCE, BM_SETCHECK, 0, 0);
	SendDlgItemMessage(HWND_SAVE, IDC_LIT_BAD, BM_SETCHECK, 0, 0);
	SendDlgItemMessage(HWND_SAVE, IDC_VERY_BAD, BM_SETCHECK, 0, 0);

	if(false){
	}
     
	else if(score == BOOK_VERY_GOOD){

		SendDlgItemMessage(HWND_SAVE, IDC_VERY_GOOD, BM_SETCHECK, 1, 0);
	}
	else if(score == BOOK_LIT_GOOD){

		SendDlgItemMessage(HWND_SAVE, IDC_LIT_GOOD, BM_SETCHECK, 1, 0);
	}

	else if(score == BOOK_BALANCE){

		SendDlgItemMessage(HWND_SAVE, IDC_BALANCE, BM_SETCHECK, 1, 0);
	}

	else if(score == BOOK_LIT_BAD){

		SendDlgItemMessage(HWND_SAVE, IDC_LIT_BAD, BM_SETCHECK, 1, 0);
	}

	else if(score == BOOK_VERY_BAD){

		SendDlgItemMessage(HWND_SAVE, IDC_VERY_BAD, BM_SETCHECK, 1, 0);
	}
}


int GetValByBookFaceInfo(book_face_info_t *pFinfo, int side){

	int val = 0;

	int pj  = pFinfo->result;
	

	if(side == BLACK){
		val =  (+ pj * 50 * 100 / 50)   ;
	}
	else{
		val =  (- pj * 50 * 100 / 50)   ;
	}

	return val;
}

BOOL FillBookbyPos(dispboard_t* pDis, DB *db){		//���ݾ������book_�б�

	//return FALSE;


	if(pDis->hwndThis == NULL){
		return FALSE;
	}
	position_t *pos = pDis->pos;


	pDis->book_num		= 0;					//�岽����
	//pDis->book_max_num	= 0;

	int max_book_val = -1;


	ThStat.isFillQk = TRUE;


	//f
	if(MST->Book_Init_Ok == FALSE){
		return FALSE;
	}


	//�������е��߲�
	gen_legal_moves(pos);


	LogOut(_T("\n\n����岽�б�\n---------------------"));

	int id = 0;

	bool have_next = FALSE;
	while(pos->pMend > pos->all_move){

		pos->pMend--;

		
		if (move_is_legal(pos, pos->pMend->move) == FALSE){
			continue;
		}
		
		
		//pos->pMend--;

		//�õ��߲�������
		//GetMoveName(pDis,pos,pos->pMend->move, appData.moveType);

		TCHAR szStepName[16];

		GetMoveNameSimple(pDis->pos,szStepName,pos->pMend->move, appData.moveType);

		//if (pos->pMend->move != 0x6a4a7) continue;

		MakePosMoveOnly(pos,pos->pMend->move);    

		GetMirrorOnlyB33(pos,pos->book_face->f33);

		//pos->book_face->info->step = pos->curStep;

		bk_GetBookInfo(pos->book_face,db);

		int res = pos->book_face->info->result;

		if(res != BOOK_NOT_RESULT){

			//if(pos->book_face->info->step >= pos->curStep){ //�߲��Ƚ�С
			if(Is_BanMove_By_Pos_Now(pDis) == false){  //��ǰ���߲���, �Ϳ���ֱ���ж��ǲ��ǽ�ֹ����
				have_next = TRUE;
				if(pos->book_face->info->isuse == TRUE ){		//����岽ʹ����						
						if((pos->side == WHITE && res != BOOK_VERY_GOOD && res != BOOK_LIT_GOOD )		//��̫�õ��岽Ҳ����
							||(pos->side == BLACK && res != BOOK_VERY_BAD && res != BOOK_LIT_BAD )){

								int tval = GetValByBookFaceInfo(pos->book_face->info, pos->side);

								pDis->book_move[pDis->book_num] = pos->pMend->move;	
								pDis->book_val[pDis->book_num]  = tval;

								if(tval > max_book_val){
									pDis->book_num = 0;               // ���¿�ʼ�������岽
									max_book_val = tval;									
								}

								if (tval == max_book_val){
									pDis->book_move[pDis->book_num] = pos->pMend->move;
									pDis->book_val[pDis->book_num] = tval;
									pDis->book_num++;
								}
						}
				}
			}

			/////////////////////////////////////////////////////////////////////////
			// ��ʾ����־��ȥ 
			TCHAR buf[256]; 
			swprintf_s(buf, sizeof(buf) / sizeof(TCHAR), _T("\n%s ->  %s"),
				szStepName, BookScoreToChar(res));
			LogOut(buf);
		}

		id++;


		//-----------------------------
		UnMakePosMoveOnly(pos);
	}



	//if(have_next){			//��ǰ�岽�к���������Ҫ���÷ְ�ť���ܰ���

	//	EnableWindow(GetDlgItem(HWND_SAVE, IDC_VERY_GOOD), FALSE);
	//	EnableWindow(GetDlgItem(HWND_SAVE, IDC_LIT_GOOD), FALSE);
	//	EnableWindow(GetDlgItem(HWND_SAVE, IDC_BALANCE), FALSE);
	//	EnableWindow(GetDlgItem(HWND_SAVE, IDC_LIT_BAD), FALSE);
	//	EnableWindow(GetDlgItem(HWND_SAVE, IDC_VERY_BAD), FALSE);
	//	
	//}
	//else{
	//	EnableWindow(GetDlgItem(HWND_SAVE, IDC_VERY_GOOD), TRUE);
	//	EnableWindow(GetDlgItem(HWND_SAVE, IDC_LIT_GOOD), TRUE);
	//	EnableWindow(GetDlgItem(HWND_SAVE, IDC_BALANCE), TRUE);
	//	EnableWindow(GetDlgItem(HWND_SAVE, IDC_LIT_BAD), TRUE);
	//	EnableWindow(GetDlgItem(HWND_SAVE, IDC_VERY_BAD), TRUE);
	//}

	//1,���ȵõ���ǰ�������Ϣ
	GetMirrorOnlyB33(pos,pos->book_face->f33);
	//pos->book_face->info->step = pos->curStep;

	bk_GetBookInfo(pos->book_face,db);

	//�ǲ�������ʹ��
	SendDlgItemMessage(HWND_SAVE, IDC_BOOK_CAN_USE, BM_SETCHECK, pos->book_face->info->isuse, 0);

	pDis->pos->His[pDis->pos->curStep].search_score = 0;
	if(have_next == TRUE){
		int ret = GetPosBookScoreByAllNextPos(pos, db);
		UpDateBookScoreButton(ret);		
		int maxsc = ret * 200;
		if(pos->side != WHITE){
			maxsc *= -1;
		}
		pDis->pos->His[pDis->pos->curStep].search_score = (sint16)maxsc;
		HDCDrawChart(TAB.dlgScore, pDis, NULL, true);
	}
	else{
		UpDateBookScoreButton(pos->book_face->info->result);
	}

	

	SetDlgItemInt(HWND_SAVE, IDC_GPLY, pos->curStep, 0);


	ThStat.isFillQk = FALSE;

	return TRUE;  
};

