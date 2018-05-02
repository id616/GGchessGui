#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"




int 
CN183_Parse_Line(TCHAR* line){

    TCHAR str[512];
	TCHAR *p;
    
    if(ICS.buf_len < 4){
		LogOut(line);
        ICS.buf_len = 0;
        return TRUE;
    }

	//LogOut("\n<<<<<<<<<<>>>>>>>>>>\n");
	//LogOut(ICS.buf);

	//< 276 You ReJoin As Red > //���������ӷ�

    //ICS.buf_len ++; //����һ������

    //��û�е�¼�ɹ�
    if(ICS.loggedOn == FALSE){
        //
        //sprintf_s(ICS.star_match[0],16,"m`eW");
        //CMX_183_Get_Client_Code();

        //
        if(looking_at(&ICS.tbuf[1], _T("@ client?"))){
            CMX_183_Get_Client_Code();

#ifdef DEBUG_MODE 
        //LogOut(ICS.star_match[0]);
        //LogOut("\nDecode:\n");
        //LogOut(ICS.ICS_183);
#endif
            return TRUE;
        }

        if(looking_at(&ICS.tbuf[1],_T("Is your client in english?"))){
            //SendToICSDelayed("nowisnot187\n", MXQ_LOG_DELAY_MS);   
			SendToICSDelayed(L"nowitisnot191\n", MXQ_LOG_DELAY_MS); 
            return TRUE;
        }

        //
        if(looking_at(&ICS.tbuf[1],(TCHAR*)CN183_IsFirstCome)){ ////���ǲ��ǳ���է����
            CMX_183_SEND_CODDING_DelayMs(L"yesihave", MXQ_LOG_DELAY_MS);
            return TRUE;
        }

        //
		if (looking_at(&ICS.tbuf[1], (TCHAR*)CN183_UserName)){
            CMX_183_SEND_CODDING_DelayMs((appData.ACPSics.ICS_user),MXQ_LOG_DELAY_MS);
            return TRUE;
        }

        //
		if (looking_at(&ICS.tbuf[1], (TCHAR*)CN183_PassWord)){
            CMX_183_SEND_CODDING_DelayMs((appData.ACPSics.ICS_pass),MXQ_LOG_DELAY_MS);
            return TRUE;
        }
        
        //
        //if(ICS.tbuf[ICS.buf_len - 3] == '%'){    //
		if (TCHAR* p = wcsstr(ICS.tbuf,L"%")){
            //for(int i=0; i<256; i++){
            //    TCHAR c = ICS.tbuf[i+1];
            //    if(c =='!' || c=='%'){
            //        str[i] = 0;
            //        break;
            //    }
            //    str[i] = c;
            //}
			int i;
			for (i = 0; i< (p - ICS.tbuf-1); i++){
				str[i] = ICS.tbuf[i + 1];
			}
			str[i] = 0;

			SetIcsLogOk(str);
            CMX_183_SEND_CODDING_DelayMs(L"map",MXQ_LOG_DELAY_MS);
            return TRUE;
        }

        SendToPlayerByColor(ICS.tbuf,ColorSeek,TRUE);
        return TRUE;
    }
    //*********************************�����ǵ�¼�ɹ���*********************


    //***************************************************************************************
    //  ^
    if(ICS.tbuf[0] == ' ' && ICS.tbuf[1] == '^'){
        //��ʼ��¼��һ�仰
        SendToPlayerByColor(L"\n ����������¼ICS��վ!!\n",ColorShout,TRUE);
        SendToPlayerByColor(ICS.tbuf,ColorShout,TRUE);
        return TRUE;
    }
    //***************************************************************************************
    //**
    if(ICS.tbuf[1] == '*' && ICS.tbuf[2] == '*'){
        ICS.tbuf[0] = ' ';
        SendToPlayerByColor(ICS.tbuf,ColorNormal,TRUE);
        return TRUE;
    }
    //***************************************************************************************
    //* ע��
    if(ICS.tbuf[1] == '*' && ICS.tbuf[2] == ' '){
        ICS.tbuf[0] = ' ';
        SendToPlayerByColor(ICS.tbuf,ColorShout,TRUE);
        return TRUE;
    }
    //***************************************************************************************
    //^              �ϵ���̨-�����[����]
	//
    if(ICS.tbuf[1] == '^' && ICS.tbuf[2] == ' '){
        ICS.tbuf[0] = ' ';
        SendToPlayerByColor(ICS.tbuf,ColorSeek,TRUE);
        return TRUE;
    }
    //***************************************************************************************
    // * ��ʾ:�ڱ������ڵ�����Ҽ��ɲ鿴���๦�ܲ˵�!
    if(ICS.tbuf[1] == ' ' && ICS.tbuf[2] == '*'){
        ICS.tbuf[0] = ' ';
        SendToPlayerByColor(ICS.tbuf,ColorSeek,TRUE);
        return TRUE;
    }
    //***************************************************************************************
    if(ICS.tbuf[1] == '!' && ICS.tbuf[2] == ' '){
        ICS.tbuf[0] = ' ';
        SendToPlayerByColor(ICS.tbuf,ColorKibitz,TRUE);
        return TRUE;
    }
    //# 
    //***************************************************************************************
    if(ICS.tbuf[1] == ' ' && ICS.tbuf[2] == '#'){
        ICS.tbuf[0] = ' ';
        SendToPlayerByColor(ICS.tbuf,ColorNormal,TRUE);
        return TRUE;
    }
    //***************************************************************************************
    if(ICS.tbuf[1] == '#' && ICS.tbuf[2] == ' '){
        ICS.tbuf[0] = ' ';
        SendToPlayerByColor(ICS.tbuf,ColorNormal,TRUE);
        return TRUE;
    }

	//~x  //��������ֿ�ʼ����Ϣ
	if(ICS.tbuf[1] == '~' && ICS.tbuf[2] == 'x'){

		LogOut(_T("\nDeBug ��������ֿ�ʼ����Ϣ\n"));
		LogOut(ICS.tbuf);

		if(ICS.table != 0){
			SendMessage(OBS[ICS.table]->hwndThis,WM_USER_ICS_INFO,NULL,(LPARAM)&ICS.tbuf[1]);
		}
		else{
			LogOut(_T("\n��������\n"));
		}
		return TRUE;
	}

	//if(strstr(ICS.buf,"~x")){
	//	return TRUE;
	//}

    //***************************************************************************************
    //===========������ݲ��ܽ���==
    //$$ ������ ��ò��� 4�� 0 6 151 0 1 0 
    //
    //===========������ݲ��ܽ���==
    //$$$ maxads 1
    //if(ICS.buf[1] == '$' && ICS.buf[2] == '$'){
    //    ICS.buf[0] = ' ';
    //    SendToPlayerByColor(ICS.buf,ColorNormal,TRUE);
    //    return TRUE;
    //}
    if(looking_at(&ICS.tbuf[1],_T("$$ @ @ @ @ @ @ @ @ @"))){
        //SetIcsTitleName(ICS.star_match[0]);
		/*sprintf_s(ICS.ICS_log_name,sizeof(ICS.ICS_log_name),"%s(%s)",ICS.star_match[1],ICS.star_match[2]);*/

		swprintf_s(ICS.log_name, sizeof(ICS.log_name) / sizeof(TCHAR), L"%s", (ICS.star_match[1]));

        return TRUE;
    }
    if(looking_at(&ICS.tbuf[1],_T("$$$ maxads"))){
        return TRUE;
    }
    //***************************************************************************************
    //$ You Go East
    if(ICS.tbuf[1] == '$' && ICS.tbuf[2] == ' '){
        ICS.tbuf[0] = ' ';
        SendToPlayerByColor(ICS.tbuf,ColorKibitz,TRUE);
        return TRUE;
    }
    //***************************************************************************************
    //1,�ǲ���% ��!%��β
    if(ICS.cbuf[ICS.buf_len - 3] == '%'){    //
        for(int i=0; i<256; i++){
            TCHAR c = ICS.tbuf[i+1];
            if(c =='!' || c=='%'){
                str[i] = 0;
                break;
            }
            str[i] = c;
        }
        //SetIcsLogOk(str);
        //CMX_183_SEND_CODDING_DelayMs("map",MXQ_LOG_DELAY_MS);
        SetIcsTitleName(str);
        ICS.started = STARTED_NONE;
        return TRUE;
    }

	//+		&ICS.buf[1]	0x0053cfb9 "~ ������ �� �� �� �� �� //+		line	0x0053cfb8 "
	//~ ������ �� �� �� �� �� 
	//"	char *
    //***************************************************************************************
		//if(ICS.buf[0] == '~' && ICS.buf[1] == ' '){


	//}

    //***************************************************************************************

    if(looking_at(&ICS.tbuf[1],_T("[ ����(�ȼ�) ]"))){
        ICS.count   = 0;
        ICS.started = STARTED_PLAYER_LIST;
        return TRUE;
    }
    //����֮��(1��) adslhq
    if(ICS.started == STARTED_PLAYER_LIST){
        if(looking_at(&ICS.tbuf[1],_T("@(@) @"))){
			swprintf_s(str, sizeof(str) / sizeof(TCHAR), _T("%s %s"), ICS.star_match[0], ICS.star_match[1]);
            SendDlgItemMessage(TAB.hwndICS_Board_List,IDC_ICS_USER_LIST,
                CB_INSERTSTRING,-1,(LPARAM)str);  
            ICS.count ++;
            SendDlgItemMessage(TAB.hwndICS_Board_List,
                IDC_ICS_USER_LIST, CB_SETCURSEL, ICS.count-1,0); 
            return TRUE;
        }
        else{            
            ICS.started = STARTED_NONE;
        }        
    }
    //***************************************************************************************

    if(looking_at(&ICS.tbuf[1],_T("[ Dir     Room        Status Players Command ]"))){
        ICS.started = STARTED_ROOM_DIR;
        ICS.count   = 0;
        return TRUE;
    }
    //EastSouth NO      closed 0
    if(ICS.started == STARTED_ROOM_DIR){
        if(
			(ICS.tkind = 1, looking_at(&ICS.tbuf[1], _T("@ <@>@ @ @ @")))
			|| (ICS.tkind = 2, looking_at(&ICS.tbuf[1], _T("@ NO      closed 0")))
			|| (ICS.tkind = 3, looking_at(&ICS.tbuf[1], _T("CenterLeft ")))
			|| (ICS.tkind = 4, looking_at(&ICS.tbuf[1], _T("CenterRight ")))
        ){            
            if(ICS.tkind == 1){
                //sprintf_s(str,sizeof(str),"%s\n%s%s\n%s",
                //    ICS.star_match[1],ICS.star_match[2],ICS.star_match[3],ICS.star_match[4]);
				swprintf_s(str, sizeof(str) / sizeof(TCHAR), _T("%s\n%s\n%s"),
                    ICS.star_match[1],ICS.star_match[2],ICS.star_match[4]);
            }
            else if(ICS.tkind == 2){
				swprintf_s(str, sizeof(str) / sizeof(TCHAR), _T("%s\n�˴��ѹر�!\n"), ICS.star_match[0]);
            }
			if(ICS.count < 9){
				SetDlgItemText(TAB.hwndGoPlace,MXQ_ICS_PLACE[ICS.count],str);
			}
            ICS.count ++;
            return TRUE;
        }
        else{
            ICS.started = STARTED_NONE;
        }
    }
    //***************************************************************************************
  
	if (looking_at(&ICS.tbuf[1], _T("[ ����  �췽 "))){
        ICS.count       = 0;
        ICS.started     = STARTED_TABLE_LIST;
        return TRUE;
    }
    if(ICS.started == STARTED_TABLE_LIST){

		if (looking_at(&ICS.tbuf[1], _T(" @ @  @ @  @ @ @ @"))){
            //1, �õ��������
            int bh = _wtoi(ICS.star_match[0]);
            if(bh == 0){
                ICS.count ++;
                return TRUE;
            }
            //ICS.count ++;
            int SubItem  = 0;
            LV_ITEM lvi;
            lvi.mask     = LVIF_TEXT + LVIF_PARAM;
            lvi.pszText  = str;
            lvi.iItem    = ++ICS.count;
            lvi.lParam   = bh;
            lvi.iSubItem = SubItem++;
			swprintf_s(str, sizeof(str) / sizeof(TCHAR), _T("%d"), bh);
            SendDlgItemMessage(TAB.hwndICS_Board_List,
                IDC_LIST_BOARD,LVM_INSERTITEM,0,(LPARAM)&lvi);

           //�õ��췽����,

			TrimIcsName(ICS.star_match[1]);

            lvi.iItem --;       //ע��,������ü�һ��
            lvi.iSubItem    = SubItem++;
            lvi.mask        = LVIF_TEXT;
            lvi.pszText     = ICS.star_match[1];
            SendDlgItemMessage(TAB.hwndICS_Board_List,
                IDC_LIST_BOARD,LVM_SETITEM,0,(LPARAM)&lvi); 

            //3,�췽����
            lvi.iSubItem    = SubItem++;
            lvi.mask        = LVIF_TEXT;                
			lvi.pszText = ICS.star_match[2];
            SendDlgItemMessage(TAB.hwndICS_Board_List,
                IDC_LIST_BOARD,LVM_SETITEM,0,(LPARAM)&lvi);

			TrimIcsName(ICS.star_match[3]);

            //4,�ڷ�����
            lvi.iSubItem    = SubItem++;
            lvi.mask        = LVIF_TEXT;                
			lvi.pszText = ICS.star_match[3];
            SendDlgItemMessage(TAB.hwndICS_Board_List,
                IDC_LIST_BOARD,LVM_SETITEM,0,(LPARAM)&lvi);

			
            //5,�ڷ�����
            lvi.iSubItem    = SubItem++;
            lvi.mask        = LVIF_TEXT;                
			lvi.pszText = ICS.star_match[4];
            SendDlgItemMessage(TAB.hwndICS_Board_List,
                IDC_LIST_BOARD,LVM_SETITEM,0,(LPARAM)&lvi);
            //6,��ʱ��ʽ
            lvi.iSubItem    = SubItem++;
            lvi.mask        = LVIF_TEXT;                
            lvi.pszText     = ICS.star_match[5];
            SendDlgItemMessage(TAB.hwndICS_Board_List,
                IDC_LIST_BOARD,LVM_SETITEM,0,(LPARAM)&lvi);
            //7,��û�п�ʼ
            lvi.iSubItem    = SubItem++;
            lvi.mask        = LVIF_TEXT;                
            lvi.pszText     = ICS.star_match[6];
            SendDlgItemMessage(TAB.hwndICS_Board_List,
                IDC_LIST_BOARD,LVM_SETITEM,0,(LPARAM)&lvi);
            //8,�ж��������Թ�
            bh = _wtoi(ICS.star_match[7]);
            lvi.iSubItem    = SubItem++;
            lvi.mask        = LVIF_TEXT; 
            //lvi.lParam      = bh;
			swprintf_s(str, sizeof(str) / sizeof(TCHAR), _T("%d"), bh);
            lvi.pszText     = str;
            SendDlgItemMessage(TAB.hwndICS_Board_List,
                IDC_LIST_BOARD,LVM_SETITEM,0,(LPARAM)&lvi); 
            return TRUE;
        }

		else if (looking_at(&ICS.tbuf[1], _T(" @ @ @ @ @ @ @ @"))){
            //1, �õ��������
            int bh = _wtoi(ICS.star_match[0]);
            if(bh == 0){
                ICS.count ++;
                return TRUE;
            }
            //ICS.count ++;
            int SubItem  = 0;
            LV_ITEM lvi;
            lvi.mask     = LVIF_TEXT + LVIF_PARAM;
            lvi.pszText  = str;
            lvi.iItem    = ++ICS.count;
            lvi.lParam   = bh;
            lvi.iSubItem = SubItem++;
			swprintf_s(str, sizeof(str) / sizeof(TCHAR), _T("%d"), bh);
            SendDlgItemMessage(TAB.hwndICS_Board_List,
                IDC_LIST_BOARD,LVM_INSERTITEM,0,(LPARAM)&lvi);

           //�õ��췽����,

			TrimIcsName(ICS.star_match[1]);

            lvi.iItem --;       //ע��,������ü�һ��
            lvi.iSubItem    = SubItem++;
            lvi.mask        = LVIF_TEXT;
            lvi.pszText     = ICS.star_match[1];
            SendDlgItemMessage(TAB.hwndICS_Board_List,
                IDC_LIST_BOARD,LVM_SETITEM,0,(LPARAM)&lvi); 

            //3,�췽����
            lvi.iSubItem    = SubItem++;
            lvi.mask        = LVIF_TEXT;                
            lvi.pszText     = ICS.star_match[2];
            SendDlgItemMessage(TAB.hwndICS_Board_List,
                IDC_LIST_BOARD,LVM_SETITEM,0,(LPARAM)&lvi);

			TrimIcsName(ICS.star_match[3]);

            //4,�ڷ�����
            lvi.iSubItem    = SubItem++;
            lvi.mask        = LVIF_TEXT;                
            lvi.pszText     = ICS.star_match[3];
            SendDlgItemMessage(TAB.hwndICS_Board_List,
                IDC_LIST_BOARD,LVM_SETITEM,0,(LPARAM)&lvi);

			
            //5,�ڷ�����
            lvi.iSubItem    = SubItem++;
            lvi.mask        = LVIF_TEXT;                
            lvi.pszText     = ICS.star_match[4];
            SendDlgItemMessage(TAB.hwndICS_Board_List,
                IDC_LIST_BOARD,LVM_SETITEM,0,(LPARAM)&lvi);
            //6,��ʱ��ʽ
            lvi.iSubItem    = SubItem++;
            lvi.mask        = LVIF_TEXT;                
            lvi.pszText     = ICS.star_match[5];
            SendDlgItemMessage(TAB.hwndICS_Board_List,
                IDC_LIST_BOARD,LVM_SETITEM,0,(LPARAM)&lvi);
            //7,��û�п�ʼ
            lvi.iSubItem    = SubItem++;
            lvi.mask        = LVIF_TEXT;                
            lvi.pszText     = ICS.star_match[6];
            SendDlgItemMessage(TAB.hwndICS_Board_List,
                IDC_LIST_BOARD,LVM_SETITEM,0,(LPARAM)&lvi);
            //8,�ж��������Թ�
            bh = _wtoi(ICS.star_match[7]);
            lvi.iSubItem    = SubItem++;
            lvi.mask        = LVIF_TEXT; 
            //lvi.lParam      = bh;
			swprintf_s(str, sizeof(str) / sizeof(TCHAR), _T("%d"), bh);
            lvi.pszText     = str;
            SendDlgItemMessage(TAB.hwndICS_Board_List,
                IDC_LIST_BOARD,LVM_SETITEM,0,(LPARAM)&lvi); 
            return TRUE;
        }
        else{
            ICS.started = STARTED_NONE;
        }
    }
    //***************************************************************************************
    //{ * �� 62 �� ����(1f) �� �� �� �� }  ICS.buf[0] = ' '; ..if(ICS.buf[1] == '$' && ICS.buf[2] == '$'){
    if(ICS.tbuf[1] == '{' && ICS.tbuf[2] == ' ' && ICS.tbuf[3] == '*' ){

		/*
        //{ * �� 1 �� �� 7 ̨ ��ò���(0��) �� �� �� ս }
        if(
              (ICS.tkind = 1, looking_at(&ICS.buf[5],"�� @ �� �� @ ̨ @(@) @"))
            ||(ICS.tkind = 2, looking_at(&ICS.buf[5],"�� @ ̨ @(@) @"))
            ){
            char* pwhat;
            if(ICS.tkind == 1){
                pwhat = ICS.star_match[4];
                ICS.stage   = atoi(ICS.star_match[0]);
                ICS.table   = (ICS.stage - 1) * 20 + atoi(ICS.star_match[1]);
            }
            else if(ICS.tkind == 2){
                ICS.stage   = 0;
                ICS.table   = atoi(ICS.star_match[0]);
                pwhat = ICS.star_match[3];
            }

            if(strstr(pwhat,"�� �� �� ս")){
                //int test  = 0;
                //���ȵ��ж��ǲ������Լ��ڹ�ս
                if(ICS.tkind == 1){
                    pwhat = ICS.star_match[2];
                }
                else if(ICS.tkind == 2){
                    pwhat = ICS.star_match[1];
                }
                if(strcmp(ICS.ICS_log_name,pwhat) == 0){    //��������ս��
                    //    //    if(DIS.gameMode == IcsObserving){
                    //        //���Ѿ����Թ��˽�
                    //        LogOut("\n���Ѿ����Թ���!!\n");
                    //        return TRUE;
                    //    }
                    //    DIS.gameMode = IcsObserving;
                    //    ICS.table    = atoi(ICS.star_match[0]);
                    //if(DIS.gameMode == IcsObserving){
                    //    //���Ѿ����Թ��˽�
                    //    LogOut("\n���Ѿ����Թ���!!\n");                       
                    //}
                    //else{
                        //DIS.gameMode = IcsObserving;
                        //sprintf_s(str,sizeof(str),"�������Թ����: �� %d �� �� %d ��",ICS.stage,ICS.table); 
                        //DispStatS(str);
                    //}
                    
                }
                else{       //���˼����˹�ս
                }
            }
        }
        
        ICS.buf[0] = ' ';
        SendToPlayerByColor(&ICS.buf[2],ColorNormal,TRUE); */
        return TRUE;
    }
    //***************************************************************************************
    if(ICS.tbuf[1] == '{' && ICS.tbuf[2] == ' ' && ICS.tbuf[3] == '+'){
        
        /*ICS.buf[0] = ' ';
        SendToPlayerByColor(&ICS.buf[2],ColorNormal,TRUE);*/
        return TRUE;
    }
    //***************************************************************************************
    if(ICS.tbuf[1] == '{' && ICS.tbuf[2] == ' ' && ICS.tbuf[3] == '-'){
        
        /*ICS.buf[0] = ' ';
        SendToPlayerByColor(&ICS.buf[2],ColorNormal,TRUE);*/
        return TRUE;
    }
    //***************************************************************************************
    if(ICS.tbuf[1] == '{' && ICS.tbuf[2] == ' ' && ICS.tbuf[3] == '#'){
        
        /*ICS.buf[0] = ' ';
        SendToPlayerByColor(&ICS.buf[2],ColorNormal,TRUE);*/
        return TRUE;
    }
    //***************************************************************************************
    //{ Stage 3 Table 2 early(8F) Leave Red To Obs } //{ Table 42 Side Reset }
    if(
		(ICS.tkind = 1, looking_at(&ICS.tbuf[1], _T("{ Stage @ Table @ @")))
		|| (ICS.tkind = 2, looking_at(&ICS.tbuf[1], _T("{ Table @ @")))
       ){
        /*ICS.buf[0] = ' ';
        SendToPlayerByColor(&ICS.buf[2],ColorNormal,TRUE);*/
        return TRUE;
    }

    if(ICS.tbuf[1] == '<'){                          //������Ӧ��������Ϣ

		ICS.started = STARTED_NONE;

			//	if(looking_at(message,"< @ You Join As @ >")){	

			//// 30 You Join As Red >

			////if(OBS[ICS.table] == NULL){
			////	OBS[ICS.table] = OBS[0];
			////	OBS[ICS.table]->table = ICS.table;
			////}

			//pDis->table = atoi(ICS.star_match[0]);

        if(looking_at(&ICS.tbuf[1],_T("< @ @"))){
			ICS.table = _wtoi(ICS.star_match[0]);

			if(OBS[ICS.table] == NULL){
				OBS[ICS.table] = OBS[0];
				OBS[ICS.table]->table = ICS.table;
			}
			else{
				OBS[ICS.table] = OBS[0];
				OBS[ICS.table]->table = ICS.table;
			}

			//�������û�п�ʼ����Ҫ��ʼһ�¡�

			SendMessage(OBS[ICS.table]->hwndThis,WM_USER_ICS_INFO,NULL,(LPARAM)&ICS.tbuf[1]);
		}

        //ICS.buf[0] = ' ';
        //SendToPlayerByColor(&ICS.buf[2],ColorNormal,TRUE); //�������ʾ��ICS�岽��

        return TRUE;
    }




	//=================================================================================================
	//�� "~ "��ͷ�ĺ���һ�����
	if(ICS.tbuf[0] == '~' || ICS.tbuf[1] == '~'){
		
		// \015\012~ Room Map\015\012[ Dir     Room        Status Players ]\015\012East <�յ�>�յ��� open 0\015\012South <�յ�>�յ��� open 0\015\012
		if(looking_at(&ICS.tbuf[3],_T("Room Map"))){
			ICS.started = STARTED_ROOM_DIR;
			ICS.count   = 0;
			return TRUE;
		}

		//~ Player List     //�����û��б�
		if(looking_at(&ICS.tbuf[3],_T("Player List"))){
			ICS.count   = 0;
			ICS.started = STARTED_PLAYER_LIST;
			//���ȵ���ա��û��б�
			SendDlgItemMessage(TAB.hwndICS_Board_List,IDC_ICS_USER_LIST,CB_RESETCONTENT,0,0);  //CB_RESETCONTENT
			return TRUE;
		}
		
		//~ Table 183 Move
		if(looking_at(&ICS.tbuf[3],_T("Table @ Move"))){
			ICS.table   = _wtoi(ICS.star_match[0]);	
			ICS.started = STARTED_MOVES;                 //��ʼ�岽����
			ICS.count   = 0;
			LogOut(_T("\n��ʼ���ճ�ʼ�岽"));
			return TRUE;
		}

		if((p = wcsstr(&ICS.tbuf[1],_T(" �� �� ��"))) != NULL){
			//1, ��ǰ����
			//int len = (int)strlen(ICS.buf);
			TCHAR *oldp = p;
			while((p--) > &ICS.tbuf[1]){
				if(*p == '~' || *p == '\n'){
					break;
				}
			}

			ASSERT(p >= ICS.tbuf);

			p++;   //����һ���ո�
			p++;

			if(looking_at(p,_T("�� @ ��"))){
				ICS.stage = _wtoi(ICS.star_match[0]);
			}
			else{
				ICS.stage = 0;
			}

			memcpy(str,p,(oldp-p)*sizeof(TCHAR));
			str[(oldp - p)] = NULLCHAR;
			SetDlgItemText(TAB.hwndICS_Board_List,IDC_ICS_STAGE,str);

			//�������ԭ�е��б�
			SendDlgItemMessage(TAB.hwndICS_Board_List,
				IDC_LIST_BOARD,LVM_DELETEALLITEMS,0,0);

			ICS.count       = 0;
			ICS.started     = STARTED_TABLE_LIST;
			return TRUE;
		}

		//�õ���ǰѡ��
		//if(looking_at(&ICS.buf[0],"~ �� @ �� ѡ ��")){

		if(wcsstr(&ICS.tbuf[0],_T(" �� ѡ ��"))){

			//ICS.table = atoi(&ICS.buf[5]);

			ICS.started = STARTED_GAME_PLAYER;
			ICS.count   = 0;
			return TRUE;
		}


		//===========������ݲ��ܽ���==
		//~ �����Ѿ�����,���ڿ�ʼ�Ծ���?
		//
		if(wcsstr(&ICS.tbuf[3],_T("�����Ѿ�����,���ڿ�ʼ�Ծ���?"))){		//�Է���׼�����˽�
			//sprintf_s(str,sizeof(str),"< %d gamecanstart >\n", ICS.table);
			SendMessage(OBS[ICS.table]->hwndThis,WM_USER_ICS_INFO,NULL,(LPARAM)&ICS.tbuf[3]);
			ICS.started = STARTED_GAME_CAN_START;
			return TRUE;
		}
		
	}	//��������"~ "��ͷ������

	if(ICS.started == STARTED_GAME_CAN_START){
		//===========������ݲ��ܽ���==
		//[   ѡ��       ��Ӧ������������Ŧ               ]  
		//
		//===========������ݲ��ܽ���==
		//ͬ��Ծ�  ��ɫָ�ϼ�ͷ[��1�ŵ�1��] 
		//
		//===========������ݲ��ܽ���==
		//����ʱ��  С����ͼ��[��1�ŵ�2��] 
		//
		//===========������ݲ��ܽ���==
		//��������  ������¼�ͷ[��2�ŵ�1��] 
		//
		//===========������ݲ��ܽ���==
		//�뿪����  ��ɫ����ͼ��[��2�ŵ�2��] 
		//
		//===========������ݲ��ܽ���==
		//�Ŵ�����  �����������Ͻǡ��ڡ���Ŧ
		//
		//===========������ݲ��ܽ���==
		//| Related : a[ͬ�⿪ʼ] pushtable+26+xiyutian[��������] side[��������] l[��Ҫ�뿪]

		//SendMessage(OBS[ICS.table]->hwndThis,WM_USER_ICS_INFO,NULL,(LPARAM)&ICS.buf[0]);
		return TRUE;
	}

	//=================================================================================================

	if(ICS.started == STARTED_MOVES){		
		if(ICS.count == 0){
			ICS.count ++;
			return TRUE;  //015\012[ Num Move ]
		}
		if(looking_at(&ICS.tbuf[1],_T(" @ @"))){
			swprintf_s(str, sizeof(str) / sizeof(TCHAR), _T("move %s %s\n"), ICS.star_match[0], ICS.star_match[1]);
			SendMessage(OBS[ICS.table]->hwndThis,WM_USER_ICS_INFO,NULL,(LPARAM)str);
		}
		ICS.count++;
		return TRUE;
	}

	
	//[ ����        �ȼ� �ȼ��� ����     ����� ����      ]

	if(ICS.started == STARTED_GAME_PLAYER){
		if(wcsstr(&ICS.tbuf[0],_T("[ ���� "))){
			ICS.count = 0;
			return TRUE;
		}

		ICS.count ++;

		//if(looking_at(&ICS.buf[1]," @ @ @ @ @ @")){
		//	ICS.count++;
		//	//sprintf_s(str,sizeof(str),"%s %s %s",ICS.star_match[0],ICS.star_match[1],ICS.star_match[2]);
		//	//if(ICS.count == 1){  //�췽
		//	//	SetDlgItemText(HWND_CONSOLE,IDC_TIME_RED_NAME, &ICS.buf[1]);
		//	//}
		//	//else if(ICS.count == 2){
		//	//	SetDlgItemText(HWND_CONSOLE,IDC_TIME_BLACK_NAME, &ICS.buf[1]);
		//	//}
		//	return TRUE;
		//}

		//if(looking_at(&ICS.buf[1],"@ @ @ @ @ @")){		//�Թ���
		//	LogOut("\n�Թ��ߣ�");
		//	LogOut(&ICS.buf[1]);
		//	return TRUE;
		//}

		////��������
		//ICS.started = STARTED_NONE;

		swprintf_s(str, sizeof(str) / sizeof(TCHAR), _T("player %d %s\n"), ICS.count, &ICS.tbuf[1]);

		SendMessage(OBS[ICS.table]->hwndThis,WM_USER_ICS_INFO,NULL,(LPARAM)str);

		return TRUE;
	}



    //***************************************************************************************
    return FALSE;		//û�д�����Ϣ
}

//#define STARTED_NONE            0
//#define STARTED_MOVES           1
//#define STARTED_BOARD           2
//#define STARTED_OBSERVE         3
//#define STARTED_HOLDINGS        4
//#define STARTED_CHATTER         5
//#define STARTED_COMMENT         6
//#define STARTED_MOVES_NOHIDE    7
//#define STARTED_PLAYER_LIST     8
//#define STARTED_TABE_LIST       9

void 
read_from_ics_xqclub(InputSourceRef isr, VOIDSTAR closure, char *data, int count, int error){
	//if (count <= 0){
	//	RemoveInputSource(isr);
	//	LogOut(_T("Connection closed by ICS"));
	//	SetIcsTitleName(_T("�Ѷ���!"));
	//	AlreadDisConnectIcs();
	//	initIcs();
	//	return;
	//}

	for (int i = 0; i <= count; i++){
		int k = 0;
	}
}

//  
void
read_from_ics_mxq_cn183(InputSourceRef isr, VOIDSTAR closure,	char *data, int count, int error)  {
#ifdef DEBUG_MODE 
    //if(appData.debugMode){
    if(!error){
#ifdef DEBUG_USE_DEBUG_FILE
		fprintf(appData.debugFP, "<ICS: ");
        show_bytes(appData.debugFP,data,count);
        fprintf(appData.debugFP,"\n");
#endif
    }
    //}
#endif
    if(count <= 0){
        RemoveInputSource(isr);
        LogOut(_T("Connection closed by ICS"));
        SetIcsTitleName(_T("�Ѷ���!"));
        AlreadDisConnectIcs();
        initIcs();
        return;
    }

    //һ��һ�ж���ȥ
    //if(ICS.lastnotfinish == TRUE){      //�ϴ���û�н�������'

    for(int i = 0; i <= count; i++){
        //
        char d = data[i];
        switch(d){
            case '\r':       //��һ�н�����
                if(ICS.buf_len == 0){
                    continue;           //������һ��'r'
                }
                goto PARSE_LINE;
                break;
            case '%':
                ICS.cbuf[ICS.buf_len++] = d;
                goto PARSE_LINE;
                break;
            default:
                if(i == count){
                    if(ICS.loggedOn == FALSE){
                        goto PARSE_LINE;
                    }
                    else{
                        //ICS.buf_len--;      //����Ҫ��һ��
                    }
                }
                else{
                    ICS.cbuf[ICS.buf_len++] = d; 
                }
                break;
        }
        continue;
PARSE_LINE:
        ICS.cbuf[ICS.buf_len++] = '\n';      //����һ����β
        ICS.cbuf[ICS.buf_len++] = NULLCHAR;  //
		//ICS.tbuf = CA2W(ICS.cbuf);
		swprintf_s(ICS.tbuf, sizeof(ICS.tbuf) / sizeof(TCHAR) , _T("%S"), (ICS.cbuf));
        if(CN183_Parse_Line(ICS.tbuf) == TRUE){
            ICS.buf_len = 0;
        } 
        else{
            SendToPlayerByColor(L"\n===========������ݲ��ܽ���==\n",ColorChannel,FALSE);
            SendToPlayerByColor(ICS.tbuf,ColorChannel,TRUE);
            ICS.buf_len = 0;
        }
    }//for(int i = 0; i <= count; i++){
}

