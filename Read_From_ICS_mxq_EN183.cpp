#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"

//




//char MXQ_4D6460[92];
//char MXQ_4D64BA[92];
//char MXQ_4D6514[92];
//char MXQ_4D656E[92];
//char MXQ_4D65C8[92];
//char MXQ_4D6622[92];
//char MXQ_4D667C[92];
//char MXQ_4D66D6[92];
//char MXQ_4D6730[92];
//char MXQ_4D678A[92];


//void CMX_183_SEND_NOT_DELAY(char *command){
//    //
//    char pass_buf[512];
//
//
//
//    CMX_183CN_Get_Pass_By_Client("yesihave",passbuf);
//    SendToICSDelayed(passbuf, MXQ_LOG_DELAY_MS);
//}
//                       

void ParseIcsBuf_EN183(char *buf){
//
//    //char *pstr;
//    char str[512];
//    int  tkind;    
//    //char passbuf[128];
//    int  len = (int)strlen(buf);
///*
//    sprintf_s(ICS.star_match[0],8,"gnE0");
//    CMX_183CN_Get_Client_Pass();
//*/
//
//
///*
//       memcpy(ICS.ICS_Client,"{OV#",5);
//       char ppp[128];
//       CMX_183CN_Get_Pass_By_Client("yesihave",ppp);
//*/
//    if(ICS.loggedOn == FALSE){
//        LogOut("\n���ڵ�¼,���Ժ�....\n");
//
//        if(looking_at(buf,"@ client?")){
//            CMX_183_Get_Client_Code();
//        }
//
//        //y!@[M%EW..
//        if(strstr(buf,"Is your client in english")){
//            SendToICSDelayed("nowis183\n", MXQ_LOG_DELAY_MS);            
//        }
//
//        
//
//        //H7]^B(..  //H7]^B(..
//        //..Do you have a account?(y or n):
//        else if(strstr(buf,"Do you have a account?(y or n)")){
//            //SendToICSDelayed("yesihave\n", MXQ_LOG_DELAY_MS);
//            //CMX_183CN_Get_Pass_By_Client("yesihave",passbuf);
//            //SendToICSDelayed(passbuf, MXQ_LOG_DELAY_MS);
//            CMX_183_SEND_CODDING_DelayMs("yesihave",MXQ_LOG_DELAY_MS);
//        }
//        //..Login_name:
//        else if(strstr(buf,"Login_name:")){
//            //sprintf_s(str,sizeof(str),"%s",DIS.third.ICS_user);
//            CMX_183_SEND_CODDING_DelayMs(DIS.third.ICS_user,MXQ_LOG_DELAY_MS);
//            
//            /*            CMX_183CN_Get_Pass_By_Client(str,passbuf);    
//
//            SendToICSDelayed(passbuf, MXQ_LOG_DELAY_MS); */          
//        }
//        //..Password:
//        else if(strstr(buf,"Password:")){
//
// /*           sprintf_s(str,sizeof(str),"%s\n",DIS.third.ICS_pass);
//
//            CMX_183CN_Get_Pass_By_Client(str,passbuf); 
//
//            SendToICSDelayed(passbuf, MXQ_LOG_DELAY_MS);  */
//
//            CMX_183_SEND_CODDING_DelayMs(DIS.third.ICS_pass,MXQ_LOG_DELAY_MS);
//        }
//        else if(buf[len-1] == '%' || buf[len-2] == '%'){
//            SetIcsLogOk(buf);
//            SendToICS("map\n");
//        }
//        else{
//            //SendToPlayerByColor(buf,ColorSeek,TRUE);            
//        }
//        //SendToPlayerByColor(buf,ColorSeek,TRUE);
//        SendToPlayerByColor(buf,ColorSeek,TRUE);    
//        return;
//    }
//
//
//    if(buf[len-1] == '%'){ 
//        buf[len-1] = 0;
//        SetIcsTitleName(buf);
//        return;
//    }
//    else if(buf[len-2] == '%'){ 
//        buf[len-2] = 0;
//        SetIcsTitleName(buf);
//        return;
//    }
//    //else if(buf[len-3] == '%'){ 
//    //    buf[len-3] = 0;
//    //    SetIcsTitleName(buf);
//    //    return;
//    //}
//
//
//    if(len < 4){
//        return;
//    }
//
//    //ICS.index = 0;
//
//    //{ # �� 113 �� ����С��(3��) vs ���Ʒɶ�(1��) �� �� �� ʼ }
//    //{ # �� 71 �� ���Ʒɶ�(1��) vs icelolly(4f) �� �� �� �� ɱ }  
//    //{ # �� 57 �� �����޼�(5f) vs ������Ȫ(9��) �� ��  Ͷ �� �� �� }
//    //{ # �� 64 �� aaggdd(1��) vs kldk(��ħ) �� �� �� ʼ }
// /*   if(looking_at(buf,&ICS.index,"{ # �� @ �� @(@) vs @(@) @}")){
//        SendToPlayerByColor(&buf[2],ColorSeek,TRUE);
//    }*/
//    //{ Table 2 yyhhff(4r) Leave Red To Obs }
//    //{ Table 120 xiaoshulan(5K) Leave Black To Obs }
//    //if(looking_at(buf,&ICS.index,"{ Table @ @(@) Leave @ To Obs }")){
//    //    SendToPlayerByColor(&buf[2],ColorKibitz,TRUE);
//    //}
//    //
//    //{ Table 120 �����(4��) Join Red From Obs }
//    //if(looking_at(buf,&ICS.index,"{ Table @ @(@) Join @ From Obs }")){
//    //    SendToPlayerByColor(&buf[2],ColorKibitz,TRUE);
//    //}
//    //{ Table 72 Side Reset }
//    //if(looking_at(buf,&ICS.index,"{ Table @ Side Reset }")){
//    //    SendToPlayerByColor(&buf[2],ColorTell,TRUE);
//    //}
//    
//
//    //{ + �����ֳ�(7��)  �� �� �� ��. }\015\012������%
//    //if(looking_at(buf,&ICS.index, "{ +@. }")){         //��������
//    //    SendToPlayerByColor(&buf[2],ColorShout,TRUE);
//    //}
//    //  { - ������С��(3��)  �� ���� ȥ�� . }
//    //if(looking_at(buf,&ICS.index, "{ -@. }")){          //��������
//    //    SendToPlayerByColor(&buf[2],ColorShout,TRUE);
//    //}
//    // { * �� 63 �� yetmee(1��) �� �� �� �� }                //������ֻ��뿪  
//    // { * �� 7 �� fleming(2��) �� �� �� �� }
//    //if(looking_at(buf,&ICS.index, "{@�� @ �� @ �� �� @}")){ 
//    //    SendToPlayerByColor(&buf[2],ColorShout,TRUE);      
//    //}
//    //if(looking_at(buf,&ICS.index, "{@�� * �� @ �� �� @}")){ 
//    //    SendToPlayerByColor(&buf[2],ColorShout,TRUE);      
//    //}
//
//    //���
//    // ! ! ��ɽʥ��:*�۽�����*, [��ؤ]ʥ�����(����) vs [��ؤ]ţƤ�Ŷ�(��˧) ������!!
///*    if(looking_at(buf,&ICS.index,"! ! @")){
//        SendToPlayerByColor(&buf[2],ColorKibitz,TRUE);    
//    }  */ 
//    // # 4 ������ʿ:���Ե����رհ��ɳ�Աʹ��ר��Ȩ����
//    //����취�������߻�Ա���Ա�б���ѡ�иó�Ա��
//    //Ȼ���¡���/��ר�ߡ���Ŧ���ɹر���ʹ��ר��Ȩ����
//    //���Ҫ�ָ���ר��Ȩ��ʹ��ͬ���������ɡ�[��ǰ����ʱ��21:36]
//
//    //if(looking_at(buf,&ICS.index," # @")){
//    //    SendToPlayerByColor(&buf[2],ColorNormal,TRUE);    
//    //}
//    // ^ *
//    //NorthTower!%~ Stage 10 Table List
//    //if(looking_at(buf,&ICS.index,"^ @")){
//    //    SendToPlayerByColor(&buf[2],ColorSShout,TRUE);
//    //} 
//    //    ~ Room Map
//    //[ Dir     Room        Status Players ]
//    //East <����>Ӣ��¥ open 0
//    //South NO      closed 0
//    //West <�յ�>�յ��� open 0
//    //North <�յ�>�յ��� open 0
//    //EastNorth <�յ�>�յ��� open 0
//    //EastSouth NO      closed 0
//    //WestSouth NO      closed 0
//    //WestNorth <�о�>������ open 0
//
//    //NorthTower!%~ Stage 10 Table List
//
//
//    //if(looking_at(buf,&ICS.index,"@ @ Table List@")){
//    //    SetDlgItemText(DLG.hwndICS_Board_List,IDC_ICS_STAGE,ICS.star_match[0]);
//    //}
//
//    if(buf[0] == '^'){      //����ϵͳ��Ϣ
//        SendToPlayerByColor(buf,ColorSShout,TRUE);
//        return;
//    }
//    else if(buf[0] == '*' && buf[1] == '*'){
//        SendToPlayerByColor(buf,ColorSeek,TRUE);
//        return;
//    }
//    else if(buf[0] == '!'){
//        SendToPlayerByColor(buf,ColorTell,TRUE);
//        return;
//    }
//    //* ע��:��Ļ�Ա���޻���144��
//    else if(buf[0] == '*' && buf[1] == ' '){
//        SendToPlayerByColor(buf,ColorSShout,TRUE);
//        return;
//    }
//    // * ��ʾ:�ڱ������ڵ�����Ҽ��ɲ鿴���๦�ܲ˵�!
//    else if(buf[0] == ' ' && buf[1] == '*'){
//        SendToPlayerByColor(buf,ColorNormal,TRUE); return;        
//    }
//    else if(buf[0] == '$' && buf[1] == ' '){
//        SendToPlayerByColor(buf,ColorKibitz,TRUE); return;       
//    }
//
//    else if(looking_at(buf,"~ Player List")){            //��ǰ���û��б�
//        int i = 0;
//        ICS_LINE_ADD();
//        buf = ICS.buf[ICS.sstart_line];        
//        if(looking_at(buf,"[ NAME(RANK) ]")){
//            //������� IDC_ICS_USER_LIST
//            SendDlgItemMessage(DLG.hwndICS_Board_List,
//                IDC_ICS_USER_LIST,CB_RESETCONTENT,0,0);  //CB_RESETCONTENT
//            for(i = 0; i < 256; i ++){
//                ICS_LINE_ADD();
//                buf = ICS.buf[ICS.sstart_line];
//                if(looking_at(buf,"@(@) @")){
//                    //��һ���û�
//                    SendDlgItemMessage(DLG.hwndICS_Board_List,
//                       IDC_ICS_USER_LIST,CB_INSERTSTRING,-1,(LPARAM)buf);                
//                }
//                else{
//                    break;
//                }
//            }
//        }
//        else{
//            return;
//        }
//        if(i != 0){
//            SendDlgItemMessage(DLG.hwndICS_Board_List,
//                       IDC_ICS_USER_LIST, CB_SETCURSEL, i-1,0);
//        }
//        return;
//    }
//    else if(looking_at(buf,"@~@Table List")){      //�õ���Ӧ��λ��
//        SetDlgItemText(DLG.hwndICS_Board_List,IDC_ICS_STAGE,ICS.star_match[1]);
//        return;
//    }
//    else if(looking_at(buf,"[ Dir     Room        Status Players ]")){
//        for(int i = 0; i < 8; i++){
//            ICS_LINE_ADD();
//            buf = ICS.buf[ICS.sstart_line];
//            if(looking_at(buf,"@ @ @ @")){
//                //int test = 0;
//                sprintf_s(str,sizeof(str),"%s\n%s\n%s", ICS.star_match[1],
//                    ICS.star_match[2], ICS.star_match[3]);
//
//                //SetDlgItemText(HWND_CONSOLE,IDC_ICS_CONNECT,"�˳�");
//                SetDlgItemText(DLG.hwndGoPlace,MXQ_ICS_PLACE[i],str);
//            }
//        }
//        sprintf_s(str,sizeof(str),"��ǰλ��\n");
//        GetWindowText(HWND_CONSOLE,&str[9],10);
//        SetDlgItemText(DLG.hwndGoPlace,MXQ_ICS_PLACE[8],str);
//        return;
//    }
//     //NorthTower!%~ Stage 10 Table List
//     //\015\012            ~ FreeRoom Fast Game Table List
//     //\015\012[ Num Red       RK Black     RK Clock   G Obs ]
//    //[ Num Red       RK Black     RK Type    G Obs ]
//    else if(looking_at(buf,"[ Num Red       RK Black     RK Clock   G Obs ]")
//        ||(looking_at(buf,"[ Num Red       RK Black     RK Type    G Obs ]"))){
//        //�������ԭ�е��б�
//        SendDlgItemMessage(DLG.hwndICS_Board_List,
//            IDC_LIST_BOARD,LVM_DELETEALLITEMS,0,0);
//        int add = 1;        //��ֵ�ַ        
//        for(int i = 0; i < 200; i++){        //��ࣲ������
//            ICS_LINE_ADD();
//            buf = ICS.buf[ICS.sstart_line];      
//            if(looking_at(buf," @ @ @ @ @ @ @ @")){
//
//                //1,�õ��������
//                int bh = atoi(ICS.star_match[0]);
//                if(bh == 0){            //�������ǣ���������д�
//                    break;
//                } 
//                int SubItem = 0;
//                LV_ITEM lvi;
//                lvi.mask        = LVIF_TEXT + LVIF_PARAM;   
//                lvi.pszText     = str;             
//                lvi.iItem       = add++;
//                lvi.lParam      = bh;                   //����������
//                lvi.iSubItem    = SubItem++;
//                sprintf_s(str,sizeof(str),"%d",bh);
//                SendDlgItemMessage(DLG.hwndICS_Board_List,
//                    IDC_LIST_BOARD,LVM_INSERTITEM,0,(LPARAM)&lvi); 
//
//                //2,�õ��췽����
//                lvi.iItem   --; //ע�⣬�����Ҫ��һ��
//
//                lvi.iSubItem    = SubItem++;
//                lvi.mask        = LVIF_TEXT;                
//                lvi.pszText     = ICS.star_match[1];
//                SendDlgItemMessage(DLG.hwndICS_Board_List,
//                    IDC_LIST_BOARD,LVM_SETITEM,0,(LPARAM)&lvi); 
//
//                //3,�췽����
//                lvi.iSubItem    = SubItem++;
//                lvi.mask        = LVIF_TEXT;                
//                lvi.pszText     = ICS.star_match[2];
//                SendDlgItemMessage(DLG.hwndICS_Board_List,
//                    IDC_LIST_BOARD,LVM_SETITEM,0,(LPARAM)&lvi);
//                //4,�ڷ�����
//                lvi.iSubItem    = SubItem++;
//                lvi.mask        = LVIF_TEXT;                
//                lvi.pszText     = ICS.star_match[3];
//                SendDlgItemMessage(DLG.hwndICS_Board_List,
//                    IDC_LIST_BOARD,LVM_SETITEM,0,(LPARAM)&lvi);
//                //5,�ڷ�����
//                lvi.iSubItem    = SubItem++;
//                lvi.mask        = LVIF_TEXT;                
//                lvi.pszText     = ICS.star_match[4];
//                SendDlgItemMessage(DLG.hwndICS_Board_List,
//                    IDC_LIST_BOARD,LVM_SETITEM,0,(LPARAM)&lvi);
//                //6,��ʱ��ʽ
//                lvi.iSubItem    = SubItem++;
//                lvi.mask        = LVIF_TEXT;                
//                lvi.pszText     = ICS.star_match[5];
//                SendDlgItemMessage(DLG.hwndICS_Board_List,
//                    IDC_LIST_BOARD,LVM_SETITEM,0,(LPARAM)&lvi);
//                //7,��û�п�ʼ
//                lvi.iSubItem    = SubItem++;
//                lvi.mask        = LVIF_TEXT;                
//                lvi.pszText     = ICS.star_match[6];
//                SendDlgItemMessage(DLG.hwndICS_Board_List,
//                    IDC_LIST_BOARD,LVM_SETITEM,0,(LPARAM)&lvi);
//                //8,�ж��������Թ�
//                bh = atoi(ICS.star_match[7]);
//                lvi.iSubItem    = SubItem++;
//                lvi.mask        = LVIF_TEXT; 
//                //lvi.lParam      = bh;
//                sprintf_s(str,sizeof(str),"%d",bh);
//                lvi.pszText     = str;
//                SendDlgItemMessage(DLG.hwndICS_Board_List,
//                    IDC_LIST_BOARD,LVM_SETITEM,0,(LPARAM)&lvi);                
//            }
//            else{
//                break;      //û��������
//            }
//        }
//        return;
//    }       //�����б� 
//    //{ - pinggu(9D) Go North . }                      //ȥ��ʲô�ط�
//    else if(looking_at(buf,"{ - @(@) Go @ . }")){
//        SendToPlayerByColor(&buf[2],ColorNormal,TRUE); return;  
//    }
//    //{ - lsqmc(1D) Quit. }   
//    //{ - titoudao(7D) Quit }
//
//    else if(looking_at(buf,"{ - @(@) Quit@ }")){
//        SendToPlayerByColor(&buf[2],ColorNormal,TRUE); return;           
//    }
//    //{ + pinggu(9D) Come From WestNorth . }           //ʲô��ʲô�ط�����
//    else if(looking_at(buf,"{ + @(@) Come From @ . }")){
//         SendToPlayerByColor(&buf[2],ColorShout,TRUE); return;
//    }
//    //{ + mjzmm(6D) Enter. }
//    else if(looking_at(buf,"{ + @(@) Enter. }")){
//         SendToPlayerByColor(&buf[2],ColorShout,TRUE); return;
//    }
//    //{ * Stage 9 Table 3 jacksonqs(1P) Leave From Obs }
//    //{ * Stage 1 Table 11 qqqqqqs(4r) Leave From Red }
//    //{ * Stage 1 Table 11 qqqqqqs(4r) Leave From Black }
//    //{ * Table 48 jigangxc(5f) Leave From Black }
//    //{ * Table 122 yshuai(2K) Leave From Obs }
//    else if(looking_at(buf,"{ * Stage @ Table @ @(@) Leave From @ }")
//        ||looking_at(buf,"{ * Table @ @(@) Leave From @ }")){
//            SendToPlayerByColor(&buf[2],ColorSShout,TRUE); return;
//    }
//    //{ * Stage 1 Table 8 qqqqqqs(4r) Join As Red }
//    //{ * Stage 1 Table 8 qqqqqqs(4r) Join As Black }
//    //{ * Stage 1 Table 8 qqqqqqs(4r) Join As Obs }
//    else if(
//        (tkind = 1, looking_at(buf,"{ * Stage @ Table @ @(@) Join As @ }"))     //�����ս���
//      ||(tkind = 2, looking_at(buf,"{ * Table @ @(@) Join As @ }"))
//      ){
//          //if(tkind == 1){
//          //    pstr = ICS.star_match[4];
//          //}
//          //else if(tkind == 2){
//          //    pstr = ICS.star_match[3];
//          //}
//          ////1,�Թۣ���2,����췽����������ڷ�
//          //if(strstr(pstr,"Obs")){
//          //   ICS_Obs_Game_EN(tkind);
//          //}
//          //else if(strstr(pstr,"Red")){
//          //}
//          //else if(strstr(pstr,"Black")){
//          //}
//          
//          
//
//          SendToPlayerByColor(&buf[2],ColorSShout,TRUE); return;
//    }
//    // { # Stage 10 Table 4 sjjnhh(2D) vs chenenqing(9) Black Resigned }
//    // { # Stage 2 Table 3 yltl(4R) vs tsunami(7R) Black Was Checkmated }
//    // { # Table 65 jankson(0f) vs abbbba(9F) Red Was Checkmated }    
//    // { # Table 41 shanghai(5F) vs asen(2F) Red Was Stalemated }
//    // { # Table 116 dyzdj(3f) vs cjjh(3S) Red Run Out of Gametime }
//    // { # Table 61 juwenwang(5F) vs ytqyzlhong(4F) Black Was Declared To Be Defeated }
//
//
//    else if(                               // 0       1 2 3     4 5  6 7
//        (tkind = 1, looking_at(buf,"{ # Stage @ Table @ @(@) vs @(@) @ @ }"))
//      ||(tkind = 2, looking_at(buf,"{ # Stage @ Table @ @(@) vs @(@) @ @ @ }"))
//      ||(tkind = 3, looking_at(buf,"{ # Stage @ Table @ @(@) vs @(@) @ @ @ @ }"))
//      ||(tkind = 4, looking_at(buf,"{ # Stage @ Table @ @(@) vs @(@) @ @ @ @ @ }"))  
//      ||(tkind = 5, looking_at(buf,"{ # Stage @ Table @ @(@) vs @(@) @ @ @ @ @ @ }")) 
//
//      ||(tkind = 6, looking_at(buf,"{ # Table @ @(@) vs @(@) @ @ }"))
//      ||(tkind = 7, looking_at(buf,"{ # Table @ @(@) vs @(@) @ @ @ }"))
//      ||(tkind = 8, looking_at(buf,"{ # Table @ @(@) vs @(@) @ @ @ @ }"))
//      ||(tkind = 9, looking_at(buf,"{ # Table @ @(@) vs @(@) @ @ @ @ @ }"))
//      ||(tkind =10, looking_at(buf,"{ # Table @ @(@) vs @(@) @ @ @ @ @ @ }"))
//        ){
//            
//            //ICS_Tell_Game_End(tkind);
//            ////��ֽ�����            
//            ////{ # Table 41 minhhung(6F) vs horatio(6f) Red Resigned }   //�췽�ϸ�
//            //int stage;
//            //int table;
//
//            ////��һ���ǲ��ǵ�ǰ��������
//            //if(
//            //      (tkind == 1)
//            //    ||(tkind == 2)
//            //    ||(tkind == 3)
//            //    ||(tkind == 4)
//            //    ||(tkind == 5)
//            //    ){
//            //        stage = atoi(ICS.star_match[0]);
//            //        table = atoi(ICS.star_match[1]);
//            //}
//            //else{
//            //    stage = 0;
//            //    table = atoi(ICS.star_match[0]);
//            //}
//
//            //if(stage == ICS.stage && table == ICS.table){   //���ǵ�ǰ��ֵ���Ϣ
//            //    //char result[32];
//            //    char *ps = DIS.pgn.resultDetails;
//            //    switch(tkind){
//            //        case 1:
//            //            sprintf_s(ps,64,"%s%s",ICS.star_match[6],ICS.star_match[7]);
//            //            break;
//            //        case 1:
//            //            sprintf_s(ps,64,"%s%s%s",ICS.star_match[6],ICS.star_match[7],ICS.star_match[8]);
//            //        default:
//            //            break;
//            //    }
//            //}
//
//            SendToPlayerByColor(&buf[2],ColorKibitz,TRUE); return;  
//    }
//    //{ # fjxpfjsc(4R) get access to Stage 4 }
//    else if(looking_at(buf,"{ # @(@) get access to @ @ }")){
//        SendToPlayerByColor(&buf[2],ColorKibitz,TRUE); return;  
//    }
//    //{ Table 1 fbwt(0r) Leave Red To Obs }
//    //{ Stage 6 Table 2 willyyang(3D) Leave Black To Obs }
//    else if(looking_at(buf,"{ Stage @ Table @ @(@) Leave @ To Obs }")
//        ||looking_at(buf,"{ Table @ @(@) Leave @ To Obs }")){
//            SendToPlayerByColor(&buf[2],ColorSeek,TRUE); return;
//    }
//    //{ Stage 2 Table 1 Side Reset }
//    //{ Table 122 Side Reset }
//
//    else if(
//        (tkind = 1, looking_at(buf,"{ Stage @ Table @ Side Reset }"))
//      ||(tkind = 2, looking_at(buf,"{ Table @ Side Reset }"))
//        ){
//        SendToPlayerByColor(&buf[2],ColorSeek,TRUE); return;
//    }
//    // { Table 1 lisite(2R) Join Red From Obs }
//    else if(looking_at(buf,"{ Table @ @(@) Join @ From @ }")){
//        SendToPlayerByColor(&buf[2],ColorSeek,TRUE); return;
//    }
//    // { Table 118 Clock 1-1-0 }
//    else if(
//        (tkind = 1, looking_at(buf,"{ Stage @ Table @ Clock @ }"))
//      ||(tkind = 2, looking_at(buf,"{ Table @ Clock @ }"))
//        ){
//        SendToPlayerByColor(&buf[2],ColorKibitz,TRUE); return;
//    }
//    //< 41  Move 42 7J-7H 805 662 >
//    else if(looking_at(buf,"< @  Move @ @-@ @ @ >")){       //����һ���߲�
//        //int desk = atoi(ICS.star_match[0]);
//
//        //int kk = 0;
//
//        if((atoi(ICS.star_match[0]) != ICS.table) 
//            || ICS.table == 0){
//            return;
//        }
//        if(DIS.gameMode == IcsObserving){
//            if(DIS.pos.curStep != DIS.pos.gply){
//                ToEndEvent();
//            }
//        } 
//        if(atoi(ICS.star_match[1]) != DIS.pos.gply + 1){
//            SendToPlayerByColor("ICS ������ظ��岽��\n",ColorNormal,TRUE); return;
//        }
//
//
//        int fromX  = ICS.star_match[2][0] - '0';
//        int fromY  = 'J' - ICS.star_match[2][1];
//        int toX    = ICS.star_match[3][0] - '0';
//        int toY    = 'J' - ICS.star_match[3][1];
//
//
//        if(IsMoveValid_FT(&DIS.pos,fromX,fromY,toX,toY)){  
//            MakeMove(fromX,fromY,toX,toY,false); 
//            ShowMove(fromX,fromY,toX,toY);
//        }
//        else{
//            SendToPlayerByColor("������ʼ�岽���岽���ݲ���ȷ!\n\n",ColorSShout,FALSE);return;
//        }
//        return;        
//    }
//
//
//    //û�н���������Ҳ����һ��
//    SendToPlayer(buf,(int)strlen(buf));            
//
//    //��ǰ��¼�ɹ���    
}





void
read_from_ics_mxq_en183(InputSourceRef isr, VOIDSTAR closure,	char *data, int count, int error)  {
//
//#ifdef DEBUG_MODE 
//    //if(appData.debugMode){
//        if(!error){
//            fprintf(DIS.debugFP, "<ICS: ");
//            show_bytes(DIS.debugFP,data,count);
//            fprintf(DIS.debugFP,"\n");
//        }
//    //}
//#endif
//
//    //#define BUF_SIZE (8192)
//
//    //#define ICS_BUF_SIZE 8192
//    //#define ICS_BUF_NUM  16
//
//    //if(count > ICS_BUF_SIZE){
//    //    MessageBox(hwndMain,"ICS ������̫��","Err",MB_OK);
//    //    return;
//    //}
//
//
//
//    if(count <= 0){
//        RemoveInputSource(isr);
//        LogOut("Connection closed by ICS");
//        //SetWindowText(HWND_CONSOLE,"��־��Ϣ(�Ѷ���)");
//        //sprintf_s(buf,sizeof(buf),"��־��Ϣ �ʺ�: %s (�Ѷ���)!",DIS.third.ICS_user);
//        SetIcsTitleName("�Ѷ���!");
//        AlreadDisConnectIcs();
//
//        //started = STARTED_NONE;
//        //parse_pos = 0;
//        //firstTime = TRUE, intfSet = FALSE;
//        //ColorClass curColor = ColorNormal;
//        //ColorClass prevColor = ColorNormal;
//        //savingComment = FALSE;
//
//        initIcs();
//    }
//
//    //��������������
//    /* If last read ended with a partial line that we couldn't parse,
//    prepend it to the new read and try again. */
//
//    //1, ��data�е�������\015\012�ֶ�
//
//    //if(count > ICS_BUF_SIZE){
//    //    MessageBox(hwndMain,"ICS������̫��","Err",MB_OK);
//    //    return;
//    //}
//
//    //char *p;
//    int  pi = 0;  
//    ICS.sstart_line = ICS.cur_line;
//    for(int i = 0; i < count; i++){
//        //if(data[i] == NULLCHAR || data[i] == 'r'){
//        //    ICS.buf[bufNum][pi++] = '\n';
//        //    ICS.buf[bufNum][pi++] = 0;
//        //    ICS.bufNum++;
//        //    pi = 0;
//        //}
//
//        if(pi > ICS_BUF_SIZE){
//            MessageBox(hwndMain,"ICS ������̫��","Err",MB_OK);
//            return;
//        }
//
//        if(data[i] == '\015' && data[i+1] == '\012'){
//            i += 1;
//            goto NextLine;
//        }
//        //if(data[i] == '0' || data[i] == '\r'){
//        //    i += 0;
//        //    goto NextLine;
//        //}
//
//        ICS.buf[ICS.cur_line][pi++] = data[i];
//        continue;
//NextLine:
//
//        ICS.buf[ICS.cur_line][pi++] = '\n';
//        ICS.buf[ICS.cur_line][pi++] = 0;
//
//        //#define ICS_BUF_SIZE    8192
//        //#define ICS_BUF_NUM  16
//
//        ICS.cur_line ++;
//
//        if(ICS.cur_line >= ICS_BUF_NUM){
//            ICS.cur_line = 0;
//        }        
//        pi = 0;     //�ӿ�ͷ��ʼ
//
//    }
//
//    //ICS.buf[ICS.cur_line][pi++] = '\n';
//    ICS.buf[ICS.cur_line][pi++] = 0;
//
//    //�������һ���ϼ��Ͻ�����־
//    ICS.cur_line ++;
//
//    if(ICS.cur_line >= ICS_BUF_NUM){
//        ICS.cur_line = 0;
//    } 
//    ICS.buf[ICS.cur_line][0] = 0;
//
//    while(ICS.buf[ICS.sstart_line][0] != 0){
//        ParseIcsBuf_EN183(ICS.buf[ICS.sstart_line]);
//
//        ICS_LINE_ADD();
//    }
//
//    ICS.cur_line = ICS.sstart_line;

}
