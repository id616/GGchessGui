#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"



BOOL HandleTableIcsMessage(dispboard_t *pDis, TCHAR* message){

	TCHAR str[512];
	PGN* pgn = pDis->pgn;

	//LogOut("\ntable message*********\n");
	//LogOut(message);

	//~x  //��������ֿ�ʼ����Ϣ
	if(message[0] == '~' && message[1] == 'x'){

		if(pDis->IcsGameStartAlready == FALSE){

			GameReset(pDis,TRUE,TRUE,FALSE);

			IcsGameStart(pDis);

			Sleep(200);
		}

		//LogOut(message);

		return TRUE;
	}

	//< 181 State Red ��ؤ10�� 0 Ӣ��ͬ�˻�Black ��ؤ10�� 6 ������
    //=====================================================================================
	if(looking_at(message,_T("< @ State "))){

		LogOut(message);

		return TRUE;
	}
    //=====================================================================================
	if (looking_at(message, _T("< @ You @"))){
		if (looking_at(message, _T("< @ You Join As @ >"))){

			// 30 You Join As Red >

			//if(OBS[ICS.table] == NULL){
			//	OBS[ICS.table] = OBS[0];
			//	OBS[ICS.table]->table = ICS.table;
			//}

			pDis->table = _wtoi(ICS.star_match[0]);


			if (wcsstr(ICS.star_match[1], _T("Obs"))){
				
				ChangeGameMode(pDis,IcsObserving);	
				
				GameReset(pDis,TRUE,TRUE, FALSE);
						
				swprintf_s(str, sizeof(str) / sizeof(TCHAR), _T("\n������%d���Թ�"), pDis->table);
				//DispStatS(str);
				LogOut(str);
			}
			else if (wcsstr(ICS.star_match[1], _T("Red"))){
				swprintf_s(pgn->Red, sizeof(pgn->Red) / sizeof(TCHAR), _T("%s"), ICS.log_name);
				ChangeGameMode(pDis,IcsPlayingWhite);
				
				swprintf_s(str, sizeof(str) / sizeof(TCHAR), _T("%s"), _T("\n����췽,�ȴ��Ծֿ�ʼ!"));
				//DispStatS(str);
				LogOut(str);

			}
			else if (wcsstr(ICS.star_match[1], _T("Black"))){
				swprintf_s(pgn->Black, sizeof(pgn->Black) / sizeof(TCHAR), _T("%s"), ICS.log_name);
				ChangeGameMode(pDis,IcsPlayingBlack);

				swprintf_s(str, sizeof(str) / sizeof(TCHAR), _T("%s"), _T("\n����ڷ�,�ȴ��Ծֿ�ʼ!"));
				//DispStatS(str);
				LogOut(str);
			}
			else{
				//DispStatS(message);
				LogOut(message);
			}
			return TRUE;
		}

		//< 40 You Leave Red To Obs >
		if (looking_at(message, _T("< @ You Leave @ To Obs >"))){
			if (wcsstr(ICS.star_match[1], _T("Red"))){
				swprintf_s(pgn->Red, sizeof(pgn->Red) / sizeof(TCHAR), _T("%s"), _T("No(No)"));
				ChangeGameMode(pDis,IcsObserving);	

				swprintf_s(str, sizeof(str) / sizeof(TCHAR), _T("%s"), _T("\n�����뿪�췽�������Թ�!"));
				//DispStatS(str);
				//SendMessage(hStatusBar,SB_SETTEXT,0,(LPARAM)str);
				LogOut(str);
			}
			else if (wcsstr(ICS.star_match[1], _T("Black"))){
				swprintf_s(pgn->Black, sizeof(pgn->Black) / sizeof(TCHAR), _T("%s"), _T("No(No)"));
				ChangeGameMode(pDis,IcsObserving);	

				swprintf_s(str, sizeof(str) / sizeof(TCHAR), _T("%s"), _T("\n�����뿪�ڷ��������Թ�!"));
				//DispStatS(str);
				//SendMessage(hStatusBar,SB_SETTEXT,0,(LPARAM)str);
				LogOut(str);
			}			
			DisplayTitle(pDis);	

			if(ICS.cont_dalei == TRUE){  
				ResetGameEvent(pDis);					//��λһ�����
				Sleep(668);
				CMX_183_SEND_CODDING(L"j");	
				//Sleep(200);
			}

			return TRUE;
		}

		//< 26 You Leave From Red >
		//< 26 You Leave From Obs >
		//
		if (looking_at(message, _T("< @ You Leave From @ >"))){

			if (wcsstr(ICS.star_match[1], _T("Red"))){
				swprintf_s(pgn->Red, sizeof(pgn->Red) / sizeof(TCHAR), _T("%s"), _T("No(No)"));

				swprintf_s(str, sizeof(str) / sizeof(TCHAR), _T("%s"), _T("\n�����뿪�췽!"));
				//DispStatS(str);
				LogOut(str);
			}
			else if (wcsstr(ICS.star_match[1], _T("Black"))){
				swprintf_s(pgn->Black, sizeof(pgn->Black) / sizeof(TCHAR), _T("%s"), _T("No(No)"));

				swprintf_s(str, sizeof(str) / sizeof(TCHAR), _T("%s"), _T("\n�����뿪�ڷ�!"));
				//DispStatS(str);
				LogOut(str);
			}
			else{
				swprintf_s(str, sizeof(str) / sizeof(TCHAR), _T("%s"), _T("\n���Ѳ����Թ�������!"));
				//DispStatS(str);
				LogOut(str);
			}

			pDis->table = 0;
			ChangeGameMode(pDis,IcsIdle);
			DisplayTitle(pDis);	

						//if(IsDlgButtonChecked(hDlg,IDC_LX_9) == BST_CHECKED){  //�������ް���������
			//if(ICS.cont_dalei == TRUE){  
			//	//1,�ټ������,
			//	//if(ICS.stage == 0){
			//	//	sprintf_s(str,sizeof(str),"j %d", curSel);
			//	//	table = curSel;
			//	//}
			//	//else{
			//	//	sprintf_s(str,sizeof(str),"j %d %d",ICS.stage,curSel);
			//	//	table = (ICS.stage-1)*20 + curSel;
			//	//}

			//	Sleep(1000);

			//	CMX_183_SEND_CODDING("j");					

			//	//2,��ͬ��Ծ�
			//	//sprintf_s(str,sizeof(str),"a %d",pDis->table);
			//	//CMX_183_SEND_CODDING(str);
			//}
			//else{
			//	sprintf_s(str,sizeof(str),"l %d", ICS.table);		//�����˾��뿪��
			//    CMX_183_SEND_CODDING(str);
			//}


            if(ICS.cont_dalei == TRUE){  
				ResetGameEvent(pDis);					//��λһ�����
				Sleep(668);
				CMX_183_SEND_CODDING(L"j");	
				//Sleep(200);
			}
			return TRUE;
		}
		
		// ����(40)��Ϣ����û�гɹ�
		//< 40 You ReJoin As Red >
		// 40 You ReJoin As Red >
		// 40 1 40 List 0 ��ò��� 4�� 2118 NO ����ʹ�� 4�� 2336 NO 20-3-50 *  
		// 40 State Red NO NO NOBlack Ӣ���޵а� ������ ����
		//
		// ����(40)��Ϣ����û�гɹ�
		//player 3 ~ Table 40 Move

		if (looking_at(message, _T("< @ You ReJoin As @ >"))){
			if (wcsstr(ICS.star_match[1], _T("Red"))){
				swprintf_s(str, sizeof(str) / sizeof(TCHAR), _T("%s"), _T("\n������ִ��,���������!"));
				//DispStatS(str);

				LogOut(str);

				ChangeGameMode(pDis,IcsPlayingWhite);

				GameReset(pDis,TRUE,TRUE, FALSE);

				Sleep(300);
				
			}
			else if (wcsstr(ICS.star_match[1], _T("Black"))){
				swprintf_s(str, sizeof(str) / sizeof(TCHAR), _T("%s"), _T("\n������ִ��,���������!"));
				//DispStatS(str);

				LogOut(str);

				ChangeGameMode(pDis,IcsPlayingBlack);

				GameReset(pDis,TRUE,TRUE, FALSE);

				Sleep(300);
				
			}
			else{
				//DispStatS(message);
				LogOut(message);
			}
			return TRUE;
		}
	}
	//=====================================================================================
	if (wcsstr(message, _T("\n�����Ѿ�����,���ڿ�ʼ�Ծ���?"))){		//�Է���׼�����˽�
		SendToPlayerByColor(message,ColorShout,FALSE);
		//DispStatS(message);
		return TRUE;
	}
	//=====================================================================================
	//< 26 totentanz(��ɷ) 2706 NO NO NO Leave Red To Obs >
	if (looking_at(message, _T("< @ @(@) @ @ @ @ Leave @ To Obs >"))){
		if (wcsstr(ICS.star_match[7], _T("Red"))){
			swprintf_s(pgn->Red, sizeof(pgn->Red) / sizeof(TCHAR), _T("No(No)"));
			DisplayTitle(pDis);
		}
		if (wcsstr(ICS.star_match[7], _T("Black"))){
			swprintf_s(pgn->Black, sizeof(pgn->Black) / sizeof(TCHAR), _T("No(No)"));
			DisplayTitle(pDis);
		}
		return TRUE;
	}	

	//=====================================================================================
	if (looking_at(message, _T("< @   * @"))){
		//< 40   * �� �� Ҫ�󻻱� >
		if (looking_at(message, _T("< @   * @ �� Ҫ�󻻱� >"))){
			SendToPlayerByColor(message,ColorShout,FALSE);
			//DispStatS(message);
			return TRUE;
		}
		//< 80   * �� �� ͬ �� �Ծ� >
		if (looking_at(message, _T("< @   * @ �� ͬ �� �Ծ� >"))){

			if (wcsstr(ICS.star_match[1], _T("��"))){
				//�������һ���ǲ����Լ�����
				if(wcsstr(pDis->pgn->Red,ICS.log_name)){
					ChangeGameMode(pDis,IcsPlayingWhite);
				}
			}
			else if (wcsstr(ICS.star_match[1], _T("��"))){
				//�������һ���ǲ����Լ�����
				if(wcsstr(pDis->pgn->Black,ICS.log_name)){
					ChangeGameMode(pDis,IcsPlayingBlack);
				}
			}

			SendToPlayerByColor(message,ColorShout,FALSE);
			//DispStatS(message);
			return TRUE;
		}
		//< 181   * ��ò���(4��) �� �� >
		if (looking_at(message, _T("< @   * @(@) �� �� >"))){
			LogOut(message);
			return TRUE;
		}		
		//< 26   * totentanz(��ɷ) �� �� �� ս >
	    //< 27   * totentanz(��ɷ) �� �� �� �� >
		if (looking_at(message, _T("< @   * @(@) �� �� @ @ >"))){
			if (wcsstr(ICS.star_match[3], _T("��"))){
				swprintf_s(pgn->Red, sizeof(pgn->Red) / sizeof(TCHAR), _T("No(No)"));
				DisplayTitle(pDis);
			}
			else if (wcsstr(ICS.star_match[3], _T("��"))){
				swprintf_s(pgn->Black, sizeof(pgn->Black) / sizeof(TCHAR), _T("No(No)"));
				DisplayTitle(pDis);
			}
			else if (wcsstr(ICS.star_match[3], _T("��"))){

			}
			return TRUE;
		}
	}
	//< 40   * 
	//=====================================================================================

	//< 39 Side Reset >  //��ڽ�����
	if(looking_at(message,_T("< @ Side Reset >"))){

		TCHAR ss[128];
		swprintf_s(ss, sizeof(ss) / sizeof(TCHAR), _T("%s"), pgn->Red);

		swprintf_s(pgn->Red, sizeof(pgn->Red) / sizeof(TCHAR), _T("%s"), pgn->Black);

		swprintf_s(pgn->Black, sizeof(pgn->Black) / sizeof(TCHAR), _T("%s"), ss);

		int elo   =  pgn->Relo;
		pgn->Relo =  pgn->Belo;
		pgn->Belo =  elo;

		if(pDis->gameMode == IcsPlayingWhite){
			ChangeGameMode(pDis,IcsPlayingBlack);
		}
		else if(pDis->gameMode == IcsPlayingBlack){
			ChangeGameMode(pDis,IcsPlayingWhite);
		}
		else {
			//ChangeGameMode(pDis,IcsPlayingBlack);
		}


		DisplayTitle(pDis);			

		return TRUE;
	}

	//=====================================================================================
	//��Ϸ������Է������־
	if (looking_at(message, _T("< @   $ @"))){

		//if(strstr(message,"͸��������") == NULL){

		//	if(strstr(message,"����") == NULL){
		//		//���
		//		sprintf_s(pgn->result,sizeof(pgn->result),ICS.star_match[1]);
		//		//�ط�
		//		sprintf_s(pgn->pevent,sizeof(pgn->pevent),"����ICS���");

		//		GameEnds(pDis,NAG,pgn->result,GE_ICS);	

		//		LogOut(message);
		//	}
		//}

		if(false){
		}
		else if (wcsstr(message, _T("����͸��������"))){
		}
		else if (wcsstr(message, _T("����͸��������"))){
		}
		else if (wcsstr(message, _T("�ر��˹�սͨ��"))){
		}
		else if (wcsstr(message, _T("�����˹�սͨ��"))){
		}
		else if (wcsstr(message, _T("����"))){
		}
		else if (wcsstr(message, _T("�����Ϸ��˸�������"))){
		}
		else if (wcsstr(message, _T("���������ϵ�������"))){
		}		
		else{
			//���
			swprintf_s(pgn->result, sizeof(pgn->result) / sizeof(TCHAR), (ICS.star_match[1]));
			//�ط�
			swprintf_s(pgn->pevent, sizeof(pgn->pevent) / sizeof(TCHAR), _T("����ICS���"));

			GameEnds(pDis,NAG,pgn->result,GE_ICS);	

			if(ICS.only_this_table == FALSE){
				Sleep(1000);
				swprintf_s(str, sizeof(str) / sizeof(TCHAR), L"l %d", ICS.table);		//�����˾��뿪��
				CMX_183_SEND_CODDING(str);                          //���뿪,�ټ���
			}
			else{
				//ICS.table = 
				Sleep(1000);
				swprintf_s(str, sizeof(str) / sizeof(TCHAR), L"a %d", pDis->table);
				CMX_183_SEND_CODDING(str);
			}
		}

		LogOut(message);
		return TRUE;
	}

	//=====================================================================================
	//< 27    2 Red Rating 2716 ��� �������� �����в��� ���u���L Black Rating 2703 ��ɷ NO NO NO >
	if (looking_at(message, _T("< @    @ Red Rating @ @ @ @ @ Black Rating @ @ @ @ @ >"))){
		return TRUE;
	}
	//=====================================================================================

	//< 42 Game Start >
	if (looking_at(message, _T("< @ Game Start >"))){
		
		GameReset(pDis,TRUE,TRUE, FALSE);

		//if(strstr(ICS.star_match[1],"Red")){
		//sprintf_s(pgn->Red,sizeof(pgn->Red),"%s",ICS.log_name);	

		if(wcsstr(pgn->Red,ICS.log_name) != NULL){

			swprintf_s(str, sizeof(str) / sizeof(TCHAR), _T("%s"), _T("\n������ִ��,���������!"));
			//DispStatS(str);

			LogOut(str);

			ChangeGameMode(pDis,IcsPlayingWhite);

			IcsGameStart(pDis);

			Sleep(300);

			//GameReset(pDis,TRUE,TRUE, FALSE);

		}

		//else if(strstr(ICS.star_match[1],"Black")){

		if(wcsstr(pgn->Black,ICS.log_name) != NULL){

			swprintf_s(str, sizeof(str) / sizeof(TCHAR), _T("%s"), _T("\n������ִ��,���������!"));
			//DispStatS(str);

			LogOut(str);

			ChangeGameMode(pDis,IcsPlayingBlack);

			IcsGameStart(pDis);

			Sleep(300);

			//GameReset(pDis,TRUE,TRUE, FALSE);

		}
		else{
			//DispStatS(message);
			LogOut(message);
		}

		DisplayTitle(pDis);

		return TRUE;
		
		//return TRUE;
	}
	//=====================================================================================

	// < 25 ��ɽС����(���) 2552 ��ˮս�� �����β� ������ �� �� �� �� >
	if (looking_at(message, _T("< @ @(@) @ @ @ @ �� �� @ @ >"))){
		if (wcsstr(ICS.star_match[7], _T("��"))){

			TrimIcsName(ICS.star_match[1]);

			swprintf_s(pgn->Red, sizeof(pgn->Red) / sizeof(TCHAR), _T("%s(%s)"), ICS.star_match[1], ICS.star_match[2]);
			pgn->Relo = _wtoi(ICS.star_match[3]);
			DisplayTitle(pDis);
			return TRUE;
		}
		else if (wcsstr(ICS.star_match[7], _T("��"))){

			TrimIcsName(ICS.star_match[1]);

			swprintf_s(pgn->Black, sizeof(pgn->Red) / sizeof(TCHAR), _T("%s(%s)"), ICS.star_match[1], ICS.star_match[2]);
			pgn->Relo = _wtoi(ICS.star_match[3]);
			DisplayTitle(pDis);
			return TRUE;
		}
		else if (wcsstr(ICS.star_match[7], _T("��"))){
			return TRUE;
		}		
	}

	//=====================================================================================

	//< 56 ����ʹ��(9��) 2388 Ӣ���޵а� ������ ���� Join Black From Obs >
	if(looking_at(message,_T("< @ @(@) @ @ @ @ Join @ From @ >"))){
		if(wcsstr(ICS.star_match[7],_T("Red"))){

			TrimIcsName(ICS.star_match[1]);

			swprintf_s(pgn->Red, sizeof(pgn->Red) / sizeof(TCHAR), _T("%s(%s)"), ICS.star_match[1], ICS.star_match[2]);
			pgn->Relo = _wtoi(ICS.star_match[3]);
			DisplayTitle(pDis);
			return TRUE;
		}
		else if(wcsstr(ICS.star_match[7],_T("Black"))){

			TrimIcsName(ICS.star_match[1]);

			swprintf_s(pgn->Black, sizeof(pgn->Black) / sizeof(TCHAR), _T("%s(%s)"), ICS.star_match[1], ICS.star_match[2]);
			pgn->Belo = _wtoi(ICS.star_match[3]);
			DisplayTitle(pDis);
			return TRUE;
		}
	}
	//=====================================================================================

	//��һ�¼�ʱ��ʽ
	TCHAR *ptime;
	if(ptime = wcsstr(message,_T("List "))){
		if (looking_at(ptime, _T("@ @ @ @ @ @ @ @ @ @ @ "))){

			//�õ�ʱ�����
			swprintf_s(pgn->RtimeControl, sizeof(pgn->RtimeControl) / sizeof(TCHAR), _T("%s"), (ICS.star_match[10]));
			swprintf_s(pgn->BtimeControl, sizeof(pgn->BtimeControl) / sizeof(TCHAR), _T("%s"), (ICS.star_match[10]));

			//�õ��췽����Ϣ  //+		[0x2]	0x00568a20 "ߴߴ����[-1&-1&-1]"	char [512]
			//Ҫ���������Ϣȥ����

			TrimIcsName(ICS.star_match[2]);

			swprintf_s(pgn->Red, sizeof(pgn->Red) / sizeof(TCHAR), _T("%s(%s)"), ICS.star_match[2], ICS.star_match[3]);

			//elo
			pgn->Relo = _wtoi(ICS.star_match[4]);

			//�õ��ڷ�����Ϣ
			TrimIcsName(ICS.star_match[7]);
			swprintf_s(pgn->Black, sizeof(pgn->Black) / sizeof(TCHAR), _T("%s(%s)"), ICS.star_match[6], ICS.star_match[7]);

			//elo
			pgn->Belo = _wtoi(ICS.star_match[8]);

			DisplayTitle(pDis);

			//��ʼ����ʱ��ʽ
			//��ʱ����ʱ������
			//if(looking_at(ICS.ICS_TimeMode,"@-@-@")){

			TCHAR* ps = pgn->RtimeControl;

			int t1 = _wtoi(ps);					//��ʱ
			int t2 = 1;
			ps = wcsstr(ps, _T("-"));
			if(ps != NULL){
				ps++;
				t2 = _wtoi(ps);					//��ʱ
			}

			int t3 = 1;
			ps = wcsstr(ps, _T("-"));
			if(ps != NULL){					    //����
				ps++;
				t3 = _wtoi(ps);
			}  

			//���ǰ��ɼ�ʱ
			TimeDisp_t* pt = &pDis->TimeDisp[WHITE];

			pt->isBaoGan        = TRUE;

			pt->SetDepth		= 0;
			pt->inc             = 0;

			pt->SetStepTime     = 0;
			pt->movetime		= 0;

			pt->RemainTime		= t1 * 1000 * 60;	

			pgn->IcsStepTime    = t2 * 1000 * 60;
 
			pgn->IcsReadTime    = t3 * 1000;             //t3 ������

			
			if(pgn->IcsReadTime == 0){
				pgn->IcsReadTime = 3000;
			}

			pt->movetime        = pgn->IcsStepTime;

			pt->inc             = pgn->IcsReadTime;			//ÿ����ʱ
			

			memcpy(&pDis->TimeDisp[BLACK],&pDis->TimeDisp[WHITE],sizeof(TimeDisp_t));

			return TRUE;
		}
	}

	//=====================================================================================

	//�õ��÷�
	if (looking_at(message, _T("< @  Score @ : @ >"))){
		swprintf_s(pgn->round, sizeof(pgn->round) / sizeof(TCHAR), _T("%s:%s"), ICS.star_match[1], ICS.star_match[2]);
		return TRUE;
	}

	//=====================================================================================

	//�õ��岽  //181  Move 51 1E-1J 661 1612 >		
	            // 40  Move 0 ---- 752 1200 >

	//if(looking_at(message,"< @ Move @")){
	if (looking_at(message, _T("< @  Move @ @ @ @ >"))){

		//LogOut(message);

		int num   = _wtoi(ICS.star_match[1]);

		if(pDis->pos->curStep != pDis->pos->gply){
			ToEndEvent(pDis);
		}

		//����һ��˫����ʱ��
		int wtime = _wtoi(ICS.star_match[3]) * 1000;
		int btime = _wtoi(ICS.star_match[4]) * 1000;

		TimeDisp_t* pt = &pDis->TimeDisp[WHITE];

		pt->RemainTime = wtime;
		pt->movetime   = pgn->IcsStepTime;

		if(pt->RemainTime <= pgn->IcsReadTime * 6){

			pt->RemainTime      = pgn->IcsReadTime;		//����ʱ��
			pt->SetStepTime     = pgn->IcsReadTime;
			pt->movetime        = pgn->IcsReadTime;
			pt->inc             = pgn->IcsReadTime * 4;

		}

		pt = &pDis->TimeDisp[BLACK];

		pt->RemainTime = btime;
		pt->movetime   = pgn->IcsStepTime;

		if(pt->RemainTime <= pgn->IcsReadTime * 6){

			pt->RemainTime      = pgn->IcsReadTime;		//����ʱ��
			pt->SetStepTime     = pgn->IcsReadTime;
			pt->movetime        = pgn->IcsReadTime;
			pt->inc             = pgn->IcsReadTime * 4;
		}


		if(num != pDis->pos->gply + 1){
			//LogOut("\nICS �����ظ��岽!");
			//LogOut(&ICS.buf[1]);

			//�����������Ϸ��ʽ��ʼ
			IcsGameStart(pDis);

			return TRUE;
		}

		int fromX  = ICS.star_match[2][0] - '0';
		int fromY  = 'J' - ICS.star_match[2][1];
		int toX    = ICS.star_match[2][3] - '0';
		int toY    = 'J' - ICS.star_match[2][4];

		if(IsMoveValid_FT(pDis->pos,fromX,fromY,toX,toY) == NormalMove){  
			//MakeMove(pDis,fromX,fromY,toX,toY,false); 
			//ShowMove(pDis,fromX,fromY,toX,toY);
			Sleep(1080);

			FinishMove(pDis,NormalMove,fromX,fromY,toX,toY); 			
			return TRUE;
		}
		else{
			SendToPlayerByColor(_T("\n������ʼ�岽���岽���ݲ���ȷ!\n\n"), ColorSShout, FALSE);
		}
	}
	//}



	//=====================================================================================
	//sprintf_s(str,sizeof(str),"move %s %s",ICS.star_match[0],ICS.star_match[1]);
	if (looking_at(message, _T("move @ @"))){
		
		
		//LogOut(message);
		
		int num = _wtoi(ICS.star_match[0]);

		if(pDis->pos->curStep != pDis->pos->gply){
			ToEndEvent(pDis);
		}

		if(num != pDis->pos->gply + 1){
			LogOut(_T("\nICS �����ظ��岽!"));
		}
		else{
			int fromX  = ICS.star_match[1][0] - '0';
			int fromY  = 'J' - ICS.star_match[1][1];
			int toX    = ICS.star_match[1][3] - '0';
			int toY    = 'J' - ICS.star_match[1][4];

			if(IsMoveValid_FT(pDis->pos,fromX,fromY,toX,toY) == NormalMove){  
				//Sleep(150);
				MakeMove(pDis,fromX,fromY,toX,toY,false); 
				ShowMove(pDis,fromX,fromY,toX,toY);
				return TRUE;
			}
			else{
				SendToPlayerByColor(_T("\n������ʼ�岽���岽���ݲ���ȷ!\n\n"), ColorSShout, FALSE);
			}
		}

		return TRUE;
	}
	//=====================================================================================
	//player 1 �������� 9�� 2047 ��ؤ10�� 0 Ӣ��ͬ�˻�
	//sprintf_s(str,sizeof(str),"player %d %s\n",ICS.count, &ICS.buf[1]);
	//�õ�player


	if (looking_at(message, _T("player @"))){
		if (looking_at(message, _T("player @  @ @ @ @ @ @"))){
			int count = _wtoi(ICS.star_match[0]);

			if(count == 1){				//�췽

				////��  "[" ȥ��
				//char *ptmp; 
				//ptmp = strstr(ICS.star_match[1],"[");
				//if(ptmp){
				//}

				TrimIcsName(ICS.star_match[1]);

				swprintf_s(pgn->Red, sizeof(pgn->Red) / sizeof(TCHAR), _T("%s(%s)"), ICS.star_match[1], ICS.star_match[2]);
				pgn->Relo = _wtoi(ICS.star_match[3]);
			}
			else if(count == 2){        //�ڷ�

				TrimIcsName(ICS.star_match[1]);

				swprintf_s(pgn->Black, sizeof(pgn->Black) / sizeof(TCHAR), _T("%s(%s)"), ICS.star_match[1], ICS.star_match[2]);
				pgn->Belo = _wtoi(ICS.star_match[3]);
			}		
			DisplayTitle(pDis);
			return TRUE;
		}

		else if (looking_at(message, _T("player @ @ @ @ @ @ @"))){
			int count = _wtoi(ICS.star_match[0]);
			return TRUE;
		}
		else {

		}
	}

	//=====================================================================================
    //< 40   # ��֮�� �� *�ɵ���̨* ��1�� �� �� �� ��! >

	if (looking_at(message, _T("< 40   # @ "))){
		LogOut(message+6);
		return TRUE;
	}

	//< 123 *          ȡ���Ծ�
	if (looking_at(message, _T("< @ *          ȡ���Ծ�"))){

		if(ICS.cont_dalei == TRUE){  //�������������
			//1,�ټ������,
			//if(ICS.stage == 0){
			//	sprintf_s(str,sizeof(str),"j %d", curSel);
			//	table = curSel;
			//}
			//else{
			//	sprintf_s(str,sizeof(str),"j %d %d",ICS.stage,curSel);
			//	table = (ICS.stage-1)*20 + curSel;
			//}

             /*			Sleep(1000);

			CMX_183_SEND_CODDING("j");		*/			

			//2,��ͬ��Ծ�

			//�½�һ��
			//GameReset(pDis,TRUE,TRUE,FALSE);

			if(pDis->IcsGameStartAlready == FALSE){            //�����û�п�ʼ,�Ͱ�ͬ��
				Sleep(1000);                                   //
				swprintf_s(str, sizeof(str)/sizeof(TCHAR), L"a %d", pDis->table);
				CMX_183_SEND_CODDING(str);
			}
		}
		return TRUE;
	}

	//< 123 # ע��:����㲻������ֶԾ�,������ڿ��ֽ׶�(���Ӳ�����10�����ҶԾ�ʱ�䲻����5����)ȡ���Ծ�[��Ӱ��˫������]
	if (looking_at(message, _T("< @ # @:"))){
		LogOut(message);
		return TRUE;
	}

	//* �Բ���:�˹��Ѿ�û�п�λ�ˣ����Ժ�����!

	if (looking_at(message, _T("< @ * �Բ���:@"))){
		Sleep(1000);                                 //
		swprintf_s(str, sizeof(str) / sizeof(TCHAR), L"%hs", "j");           // ��һ�μ���
		CMX_183_SEND_CODDING(str);
	}
	//< 123 # ����:�����Ҳ��ս����б�ѡ�ж������ֺ������Ҽ�ѡ����������������[�ƽ��Ա����][��Ҫ�۳�500����]
	//if(looking_at(message,"< @ # @:")){
	//	return TRUE;
	//}

	return FALSE;
}



void TrimIcsName(TCHAR* Name){

	TCHAR *pc = wcsstr(Name,_T("["));

	if(pc){
		*pc = 0;
	}
}