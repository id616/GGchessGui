#include "stdafx.h"
#include "data.h"
#include "chess.h"
#include "Resource.h"
#include "pregen.h"




void ParseIcsBuf_CN(char *buf){


    //char str[512];
    //int  len = (int)strlen(buf);

    //if(ICS.loggedOn == FALSE){
    //    LogOut("���ڵ�¼,���Ժ�....\n");
    //    
    //    //nowisnot183..
    //    if(strstr(buf,"client? :")){
    //        //SendToICSDelayed("\n", MXQ_LOG_DELAY_MS);      
    //    }
 
    //    //nowisnot183..  nowisnot183..
    //    if(strstr(buf,"Is your client in english")){
    //        SendToICSDelayed("nowis183\n", MXQ_LOG_DELAY_MS);  

    //        //SendToICSDelayed("nowisnot183\n", MXQ_LOG_DELAY_MS); 
    //    }

    //    //H7]^B(..  //H7]^B(..  Jesi[ave..
    //    else if(strstr(buf,"�㲻�ǳ���է����")){

    //        //str[0] = 0x48;
    //        //str[1] = 0x37;
    //        //str[2] = 0x5D;
    //        //str[3] = 0x5E;
    //        //str[4] = 0x42;
    //        //str[5] = 0x28;
    //        //str[6] = 0x0D;
    //        //str[7] = 0x0A;
    //        //str[8] = 0x00;
    //        //str[9] = 0x00;

    //        //sprintf_s(str,sizeof(str),buf);
    //        //
    //        //sprintf_s(str,sizeof(str),"yesihave\n");
    //        //sprintf_s(str,sizeof(str),"kknd1974\n");
    //        //sprintf_s(str,sizeof(str),"msnlgl\n");


    //        //SendToICSDelayed(str, MXQ_LOG_DELAY_MS);
    //        SendToICSDelayed("yesihave\n", MXQ_LOG_DELAY_MS);  

    //    }
    //    else if(strstr(buf,"��½��(Ӣ��):")){
    //        sprintf_s(str,sizeof(str),"%s\n",DIS.third.ICS_user);
    //        SendToICSDelayed(str, MXQ_LOG_DELAY_MS);           
    //    }

    //    else if(strstr(buf,"Do you have a account?(y or n):")){
    //        SendToICSDelayed("yesihave\n", MXQ_LOG_DELAY_MS);  
    //    }
    //    

    //    else if(strstr(buf,"����:")){
    //        sprintf_s(str,sizeof(str),"%s\n",DIS.third.ICS_pass);
    //        SendToICSDelayed(str, MXQ_LOG_DELAY_MS);  
    //    }
    //    if(buf[len-1] == '%'){
    //        SetIcsLogOk(buf);
    //        SendToICS("map\n");
    //    }

    //    SendToPlayerByColor(buf,ColorSeek,TRUE);
    //    return;
    //}


    //if(buf[len-1] == '%' || buf[len-2]  == '%'){                  //���ǵط�
    //    //if(ICS.getPlace == FALSE){
    //    //    ICS.getPlace = TRUE;
    //        SetIcsTitleName(buf);
    //    //}

    //    //test 

    //    //SendToPlayerByColor(&buf[2],ColorSeek,TRUE);
    //    //

    //    return;
    //}

    //if(len < 4){
    //    return;
    //}

    //ICS.index = 0;
//    if(false){
//    }
//    //
//    //{ # �� 113 �� ����С��(3��) vs ���Ʒɶ�(1��) �� �� �� ʼ }
//    //{ # �� 71 �� ���Ʒɶ�(1��) vs icelolly(4f) �� �� �� �� ɱ }  
//    //{ # �� 57 �� �����޼�(5f) vs ������Ȫ(9��) �� ��  Ͷ �� �� �� }
//    //{ # �� 64 �� aaggdd(1��) vs kldk(��ħ) �� �� �� ʼ }
//    else if(looking_at(buf,&ICS.index,"{ # �� @ �� @(@) vs @(@) @}")){
//        SendToPlayerByColor(&buf[2],ColorSeek,TRUE);
//    }
//    //{ Table 2 yyhhff(4r) Leave Red To Obs }
//    //{ Table 120 xiaoshulan(5K) Leave Black To Obs }
//    else if(looking_at(buf,&ICS.index,"{ Table @ @(@) Leave @ To Obs }")){
//        SendToPlayerByColor(&buf[2],ColorKibitz,TRUE);
//    }
//    //
//    //{ Table 120 �����(4��) Join Red From Obs }
//    else if(looking_at(buf,&ICS.index,"{ Table @ @(@) Join @ From Obs }")){
//        SendToPlayerByColor(&buf[2],ColorKibitz,TRUE);
//    }
//    //{ Table 72 Side Reset }
//    else if(looking_at(buf,&ICS.index,"{ Table @ Side Reset }")){
//        SendToPlayerByColor(&buf[2],ColorTell,TRUE);
//    }
//    
//
//    //{ + �����ֳ�(7��)  �� �� �� ��. }\015\012������%
//    else if(looking_at(buf,&ICS.index, "{ +@. }")){         //��������
//        SendToPlayerByColor(&buf[2],ColorShout,TRUE);
//    }
//    //  { - ������С��(3��)  �� ���� ȥ�� . }
//    else if(looking_at(buf,&ICS.index, "{ -@. }")){          //��������
//        SendToPlayerByColor(&buf[2],ColorShout,TRUE);
//    }
//    // { * �� 63 �� yetmee(1��) �� �� �� �� }                //������ֻ��뿪  
//    // { * �� 7 �� fleming(2��) �� �� �� �� }
//    else if(looking_at(buf,&ICS.index, "{@�� @ �� @ �� �� @}")){ 
//        SendToPlayerByColor(&buf[2],ColorShout,TRUE);      
//    }
//    else if(looking_at(buf,&ICS.index, "{@�� @ �� @ �� �� @}")){ 
//        SendToPlayerByColor(&buf[2],ColorShout,TRUE);      
//    }
//
//    //���
//    // ! ! ��ɽʥ��:*�۽�����*, [��ؤ]ʥ�����(����) vs [��ؤ]ţƤ�Ŷ�(��˧) ������!!
//    else if(looking_at(buf,&ICS.index,"! ! @")){
//        SendToPlayerByColor(&buf[2],ColorKibitz,TRUE);    
//    }   
//    // # 4 ������ʿ:���Ե����رհ��ɳ�Աʹ��ר��Ȩ����
//    //����취�������߻�Ա���Ա�б���ѡ�иó�Ա��
//    //Ȼ���¡���/��ר�ߡ���Ŧ���ɹر���ʹ��ר��Ȩ����
//    //���Ҫ�ָ���ר��Ȩ��ʹ��ͬ���������ɡ�[��ǰ����ʱ��21:36]
//
//    else if(looking_at(buf,&ICS.index," # @")){
//        SendToPlayerByColor(&buf[2],ColorNormal,TRUE);    
//    }
//    // ^ *
//
//    else if(looking_at(buf,&ICS.index,"^ @")){
//        SendToPlayerByColor(&buf[2],ColorSShout,TRUE);
//    } 
//    else if(looking_at(buf,&ICS.index,"[ Dir     Room        Status Players ]")){
//        //if(DLG.hwndGoPlace != NULL){
//            //ICS.start_line ++;                      //����[ Dir     Room        Status Players ]
//            //if(ICS.start_line >= ICS_BUF_NUM){
//            //    ICS.start_line = 0;
//            //}
//
//
//
//        for(int i = 0; i < 8; i++){
//            ICS.start_line ++;                      //East <����>Ӣ��¥ open 0
//            if(ICS.start_line >= ICS_BUF_NUM){
//                ICS.start_line = 0;
//            }
//            buf = ICS.buf[ICS.start_line];
//            ICS.index = 0;
//            if(looking_at(buf,&ICS.index,"@ @ @ @")){
//                //int test = 0;
//                sprintf_s(str,sizeof(str),"%s\n%s\n%s", ICS.star_match[1],
//                     ICS.star_match[2], ICS.star_match[3]);
//
//                //SetDlgItemText(HWND_CONSOLE,IDC_ICS_CONNECT,"�˳�");
//                SetDlgItemText(DLG.hwndGoPlace,MXQ_ICS_PLACE[i],str);
//            }
//        }
//        sprintf_s(str,sizeof(str),"��ǰλ��\n");
//        GetWindowText(HWND_CONSOLE,&str[9],10);
//        SetDlgItemText(DLG.hwndGoPlace,MXQ_ICS_PLACE[8],str);
//            
//        //}
//        //ParseIcsBuf(ICS.buf[ICS.start_line]);
//
//        //ICS.start_line ++;
//        //if(ICS.start_line >= ICS_BUF_NUM){
//        //    ICS.start_line = 0;
//        //}
//        
//    }
//
////    ~ Room Map
////[ Dir     Room        Status Players ]
////East <����>Ӣ��¥ open 0
////South NO      closed 0
////West <�յ�>�յ��� open 0
////North <�յ�>�յ��� open 0
////EastNorth <�յ�>�յ��� open 0
////EastSouth NO      closed 0
////WestSouth NO      closed 0
////WestNorth <�о�>������ open 0
//
//    else{       //û���κο�ʶ��ѡ��ʱ
//        SendToPlayer(buf,(int)strlen(buf));
//    }          

    //��ǰ��¼�ɹ���    
}





void
read_from_ics_mxq_cn(InputSourceRef isr, VOIDSTAR closure,	char *data, int count, int error)  {

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
//        ParseIcsBuf_CN(ICS.buf[ICS.sstart_line]);
//
//        ICS_LINE_ADD();
//
//        //ICS.start_line ++;
//        //if(ICS.start_line >= ICS_BUF_NUM){
//        //    ICS.start_line = 0;
//        //}
//    }
//    ICS.cur_line = ICS.sstart_line;
//
//
//
//    //if(count < 3){
//    //   return;
//    //}
//
//    //int len;
//    ////ICS.curNum = 0;
//    //while(p < (data + count)){
//    //    if(strstr(p,"\015\012")){
//    //        p += 2;
//    //        char *pend = strstr(p,"\015\012");
//    //        if(pend == NULL){          //ֻ��һ��
//    //            //memcpy(ICS.buf,p,strlen(p)); 
//    //            //sprintf_s(ICS.buf,data + count - p - 1,p);
//    //            len = (int)(data + count - p);
//    //            memcpy(ICS.buf,p,len);
//    //            ICS.buf[len+1] = '\n';
//    //            ICS.buf[len+2] = 0;
//    //        }
//    //        else{   
//    //           len = (int)(pend - p);
//    //           memcpy(ICS.buf,p,len); 
//    //           p = pend;
//    //           ICS.buf[len+1] = '\n';
//    //           ICS.buf[len+2] = 0;
//    //        }
//    //        ParseIcsBuf(ICS.buf);
//    //    }
//    //    else{
//    //        break;
//    //       //SendToPlayer(data,count);
//    //    }
//    //}
}






//void 


//recognized 'normal' (-1) as variant normal
//GGchess 1.0.8
//Reset(1, 0) from gameMode 0
//recognized 'normal' (-1) as variant normal
//GameEnds(0, (null), 2)
//<ICS: \015\0123OT< client? :
//<ICS: \015\012Is your client in english?(y or n):
//>ICS: noitisnot140\012
//<ICS: \015\012�㲻�ǳ���է����?:
//>ICS: yesihave\012
//<ICS: \015\012��½��(Ӣ��):
//>ICS: msnlgl\012
//<ICS: \015\012����:
//>ICS: kknd1974\012
//<ICS: \015\012������%
//<ICS:  ^                   ���� ��ӭ�������콭��!\015\012*********************
//*******************************************\015\012!        ��  
//�����������޻��ѵ����彭����Ц�ɸ�·���ܣ� \015\012!        ����   ����
//�Կ�����Ӣ�ۣ�˭��һͳ������\015\012***************************************
//*************************\015\012# ���κν�������ʻ��ֳ���BUG�������������!
//\015\012^ �ۿ���ɽ�۽�,����ϻ�ɽ����һ��![30��������-9������]\015\012^ 
//��ս����,��ɴ�������¥ʩչ����![25��������-1100+��·��]\015\012^ ��ս����,
//��ɺ����һ���һ�ѷ���![10���ӿ���-1100+��·��]\015\012! ������о�������������Ϊ���ƻ���
//�ɵ���������о�\015\012^ �쵶��̨-281����1560+ ���ɵ���̨-282��  
//1560+\015\012****************************************************************\015\012! 
//�����㿨���������"����"->"��Ҫ�������㿨"������ҳ\015\012*****************************
//***********************************\015\012^ �����ĺͶ����칦�ܻ�������Ϥ���˿��Ե���Ҳ��ͼ���ġ�����
//��ͼ\015\012^ �꣬������ֱ�۵Ŀͻ��˵�ͼ�ΰ���ϵͳ\015\012****************************
//************************************.\015\012^ ������Ե����������רҵ��վ��www.chesssky.net����
//��ӭ���Ĺ��٣�\015\012****************************************************************\015\012
//������%\015\012~ Player List\015\012[ ����(�ȼ�) ]\015\012aaacccc(4r) aaacccc\015\012aaggdd(����)
//aaggdd\015\012���ֵ���(2r) aakuaile\015\012�׺��쵶(3r) adslabcd\015\012��������ζ(5r) 
//ahtlhyq\015\012̷ӽ��(9��) alanal\015\012anabc(4r) anabc\015\012��ˮ��(����) aotian\015\012�����(2��)
//appley\015\012����С��(3��) atttta\015\012����(5r) azhu\015\012�׿�������(4r) azzlxjj\015\012��������(����)
//bailinhao\015\012�ǻҴ�(����) bestplayer\015\012����С�Ʒ�(9��) billjack\015\012����(5r)
//biwen\015\012����(5r) cccpzj\015\012��ɽ�ۼ�(4��) cghabc\015\012�ϵ�һ��(3r) chaoren\015\012��������(2��)
//chengweyin\015\012��������(5r) chunxiao\015\012����ǿ��(6r) chysh\015\012czdxsb(3r) 
//czdxsb\015\012�����ѳ���(9��) daycm\015\012����������(4r) dong\015\012һ��(����) 
//dudulaile\015\012������ʦ(5r) elmo\015\012ħ������(9��) fefefefe\015\012�ɱ�����(2��) 
//feiben\015\012���Ʒɶ�(2��) feidu\015\012���Ի�(����) fffgggfg\015\012fleming(2��) 
//fleming\015\012˫��������(����) frankdu\015\012��˳��һ(7��) fsjo\015\012gjfaaaaaad(4r) 
//gjfaaaaaad\015\012һ�о���(4��) glpglp\015\012gongqk(4r) gongqk\015\012�º�����(3��) 
//guinfirst\015\012��ϲ������(3��) guokai\015\012guozhu(4r) guozhu\015\012gzfd(5r) gzfd\015\012��ѧ(����)
//haoping\015\012�������(5��) himwerttui\015\012��������ũ(5r) hjhdr\015\012��ߴ����(2��) 
//hjhmang\015\012hualeyi(3r) hualeyi\015\012��ƽʹ��(4r) huangxi\015\012����С�ſ�(����) 
//huuua\015\012����(6��) huyong\015\012��������(2r) hyklh\015\012icelolly(5r) 
//icelolly\015\012iikkmmiikk(4r) iikkmmiikk\015\012�ݲ�����(3��) jbjy\015\012�Ϸ���ʤ(����) 
//jerwwwww\015\012������(3��) jiaqiba\015\012jigangxc(4r) jigangxc\015\012����(2r) 
//jimmy\015\012��������(2��) jingfan\015\012����(5r) jinw\015\012��С��(5r) 
//jinxiaolin\015\012ɽ���(2r) jjhfzzh\015\012jjyyahg(5r) jjyyahg\015\012jovialkids(5r) 
//jovialkids\015\012���(5r) kikiki\015\012������(5r) kisslove\015\012������ʹ(1r) 
//kkooa\015\012kldk(3��) kldk\015\012����(5r) lanwu\015\012�㻹����(5r) ldyffff\015\012��ѩ��(3��) 
//lengxuejs\015\012�����Ͽ�(5��) lfgshk\015\012������̽(5��) linjinmt\015\012����������(4��) 
//liqingquan\015\012�ܿ�һ��(2��) lishanli\015\012��ͨ(2r) liutong\015\012lizhao(4r) 
//lizhao\015\012�޵�����(5r) lllfffhhh\015\012ɶ�з����(4��) lmafx\015\012��������(3r)
//lschew\015\012ltaoys(5r) ltaoys\015\012·��̯(4r) lululu\015\012�ѵú�Ϳ(8��) 
//luwq\015\012�����(3��) lxshh\015\012������(3r) lywzy\015\012majinan(4r) majinan\015\012maker(4r) 
//maker\015\012��(����) maoshun\015\012�����ҵİ�(5r) miping\015\012��ϩ�(3r) 
//mjigl\015\012����֮����(1��) mklh\015\012������(1��) mmmmzz\015\012��������(3��)
//mrchess\015\012��ò���(4��) msnlgl\015\012����(4r) nedshow\015\012newcat(5r)
//newcat\015\012ССǿǿ(3r) newcom\015\012��������(9��) nshshch\015\012ţħ��֮��(5r) 
//nxgnxg\015\012Сŷ(3��) ouxl\015\012�¾�ն˫��(1��) pdsx\015\012����С��(3r) 
//peterliao\015\012��Ȼ��(9��) pianke\015\012������(����) poiuj\015\012����֮�ؽ�(4��) 
//ppoollk\015\012ɵ�����(9��) pppppppp\015\012�������(8��) qazmlp\015\012qdzfhong(����) 
//qdzfhong\015\012�õ���Ӱ(����) qgom\015\012qiyujin(4r) qiyujin\015\012�����(5r) 
//qmjqmjqmj\015\012��������(5r) qqabcd\015\012ѰӦ(9��) qqqqqqaa\015\012��������(4r) 
//qqqqqqs\015\012������(3��) qwaszxerdf\015\012��������(5r) qymq\015\012����(5r) 
//ralaopei\015\012���L�輧(2��) raphael\015\012�絶(2r) ruihongqin\015\012���ܿ��(8��) 
//shmilyfy\015\012һ��һ����(2��) sjzsmt\015\012����(5��) tianming\015\012������˳(4r) 
//tjmjs\015\012�Ϲ�(4r) tlliu\015\012��������(����) toto\015\012�޺�(3��) ttttllll\015\012��������(2r)
//tytyaaaaaa\015\012������(4r) tyuhjk\015\012�켦�ȼ���(2r) violence\015\012����(3r) 
//vvvttt\015\012��̳��ʥ(1r) wangbotaoq\015\012����С(9��) wangcaiabc\015\012����(2��) 
//wdyhm\015\012wlhsjsn(5r) wlhsjsn\015\012���岻����(1��) wrfhaibei\015\012�帣��(3��)
//wufuwa\015\012����(1r) wune\015\012��Ȫ(1r) wuquan\015\012��˧(5r) wuysh\015\012����Ԫ˧(3��) 
//wwssxxxx\015\012wwwsoshj(0r) wwwsoshj\015\012����һ��(����) xiaodan\015\012С����(9��) 
//xiaoshulan\015\012С��(����) xiaowen\015\012����(6��) xingsheng\015\012�ܹ�����(1��) 
//xqchenl\015\012����������(4r) xsjqq\015\012������̫��(�½�) xsjty\015\012�����İ�(5r) 
//xtflewis\015\012xuzi(4r) xuzi\015\012һ��(3r) xxsxx\015\012xxxhutu(5r) xxxhutu\015\012��������(4r)
//xymasdf\015\012xyzfzs(5r) xyzfzs\015\012���ֿ���(�½�) yangguanga\015\012������(3r) 
//yanghongbo\015\012�˱���(����) yangwu\015\012���尳���(6��) yccz\015\012֣Ŭ��(4��) 
//ycfengwen\015\012���⳴ţ��(6��) ycxycx\015\012������(5��) ydhrhutft\015\012һ�˷���(5r) 
//<ICS: \015\012{ * �� 81 �� jjyyahg(2��) �� �� �� �� }\015\012������%
//<ICS: \015\012{ # �� 41 �� ������(2��) vs �޵�����(5f) �� �� �� ʼ }\015\012������%
//<ICS: \015\012{ * �� 116 �� jjyyahg(2��) �� �� �� �� }\015\012������%
//<ICS: \015\012{ - ����(5��)  �� ��. }\015\012������%
//<ICS: \015\012{ # �� 117 �� �㻹����(6f) vs ��������(5f) �� ��  Ͷ �� �� �� }\015\012������%
//<ICS: \015\012{ # �� 117 �� �㻹����(6f) vs ��������(5f) �� �� �� ʼ }\015\012������%
//<ICS: \015\012{ * �� 75 �� ��˧(5f) �� �� �� �� }\015\012������%
//<ICS: \015\012{ * �� 73 �� һ��(5��) �� �� �� �� }\015\012������%
//<ICS: \015\012{ # �� 73 �� һ��(5��) vs jigangxc(5f) �� �� �� ʼ }\015\012������%
//<ICS: \015\012{ - �����(3��)  �� ���� ȥ�� . }\015\012������%
//<ICS: \015\012{ * �� 55 �� kldk(��ħ) �� �� �� �� }\015\012������%
//<ICS: \015\012{ # �� 45 �� ƽƽ��(2��) vs ��������(6f) �� �� �� �� ɱ }\015\012������%
//<ICS: \015\012{ # �� 70 �� ��ƽʹ��(2f) vs ��������(6��) �� ��  Ͷ �� �� �� }\015\012������%
//<ICS: \015\012{ * �� 55 �� kldk(��ħ) �� �� �� �� }\015\012������%
//<ICS: \015\012{ * �� 45 �� ƽƽ��(2��) �� �� �� �� }\015\012������%
//<ICS: \015\012{ # �� 120 �� С����(�޼�) vs �ܹ�����(6��) �� �� �� �� ʱ }\015\012������%
//<ICS: \015\012{ * �� 45 �� ƽƽ��(2��) �� �� �� �� }\015\012������%
//<ICS: \015\012{ # �� 70 �� ��ƽʹ��(2f) vs ��������(6��) �� �� �� ʼ }\015\012������%
//<ICS: \015\012{ * �� 4 �� ������С��(3��) �� �� �� �� }\015\012������%
//<ICS: \015\012{ # �� 45 �� ƽƽ��(2��) vs ��������(6f) �� �� �� ʼ }\015\012������%
//<ICS: \015\012{ - ������С��(3��)  �� ���� ȥ�� . }\015\012������%
//<ICS: \015\012{ + Ц������(5r)  �� �� �� ��. }\015\012������%
//<ICS: \015\012{ - ������̽(5��) �u��������''o�u��������^'''�q�Шr�Шr.','�u�u��u �� ��. }\015\012������%
//<ICS: \015\012{ * �� 121 �� �ɱ�����(3��) �� �� �� �� }\015\012������%
//<ICS: \015\012{ - ɵ�����(9��)  �� �� ȥ�� . }\015\012������%
//<ICS: \015\012{ + ������С��(3��)  �� ���� �� ��. }\015\012������%
//<ICS: \015\012{ + һ��ɱ��(7��) �֡��̫ƽ����֡������̫ƽ�֡�֨��������������� �� ��. }\015\012������%
//<ICS: \015\012{ # �� 64 �� aaggdd(1��) vs anabc(5f) �� �� �� �� ɱ }\015\012������%
//<ICS: \015\012{ * �� 55 �� kldk(��ħ) �� �� �� �� }\015\012������%
//<ICS: \015\012{ * �� 41 �� Ц������(3f) �� �� �� ս }\015\012������%
//<ICS: \015\012{ # �� 120 �� С����(�޼�) vs �ܹ�����(6��) �� �� �� ʼ }\015\012������%
//<ICS: \015\012{ * �� 64 �� anabc(5f) �� �� �� �� }\015\012������%
//<ICS: \015\012{ * �� 122 �� һ��ɱ��(2��) �� �� �� �� }\015\012������%
//<ICS: \015\012{ * �� 55 �� ������С��(1��) �� �� �� �� }\015\012������%
//<ICS: \015\012{ * �� 64 �� kldk(��ħ) �� �� �� �� }\015\012������%
//<ICS: \015\012{ # �� 42 �� majinan(1f) vs �¾�ն˫��(9��) �� �� �� �� ɱ }\015\012������%
//<ICS: \015\012{ * �� 120 �� һ��ɱ��(2��) �� �� �� ս }\015\012������%
//<ICS: \015\012{ * �� 75 �� anabc(5f) �� �� �� �� }\015\012������%
//<ICS: \015\012{ # �� 64 �� aaggdd(1��) vs kldk(��ħ) �� �� �� ʼ }\015\012������%
//<ICS: \015\012{ * �� 120 �� һ��ɱ��(2��) �� �� �� ս }\015\012������%
//<ICS: \015\012{ * �� 116 �� ������(4f) �� �� �� �� }\015\012������%
//<ICS: \015\012{ * �� 119 �� ������(4f) �� �� �� �� }\015\012������%
//<ICS: \015\012{ Table 3 Side Reset }\015\012������%
//<ICS: \015\012{ Table 3 Side Reset }\015\012������%
//<ICS: \015\012{ * �� 3 �� �켦�ȼ���(2r) �� �� �� �� }\015\012������%
//<ICS: \015\012{ * �� 4 �� �켦�ȼ���(2r) �� �� �� �� }\015\012������%
//<ICS: \015\012{ * �� 118 �� ����С��(1��) �� �� �� �� }\015\012������%
//<ICS: \015\012{ Table 118 Side Reset }\015\012������%
//<ICS: \015\012{ # �� 18 �� ·��̯(4r) vs �õ���Ӱ(����) ˫ �� �� �� }\015\012������%
//<ICS: \015\012{ * �� 55 �� ������С��(1��) �� �� �� �� }\015\012������%
//<ICS: \015\012{ * �� 75 �� anabc(5f) �� �� �� �� }\015\012������%
//<ICS: \015\012{ * �� 55 �� ǿ���޵�(1��) �� �� �� �� }\015\012������%
//<ICS: \015\012{ * �� 72 �� ������ʹ(3f) �� �� �� �� }\015\012������%
//<ICS: \015\012{ - ������С��(3��)  �� �� ȥ�� . }\015\012������%
//<ICS: \015\012{ - ������(3��)  �� ��. }\015\012������%
//<ICS: \015\012{ * �� 4 �� �켦�ȼ���(2r) �� �� �� �� }\015\012������%
//<ICS: \015\012{ + ������(����)  �� ���� �� ��. }\015\012������%
//<ICS: \015\012{ * �� 55 �� ǿ���޵�(1��) �� �� �� �� }\015\012������%
//<ICS: \015\012{ * �� 118 �� ���޻�(8��) �� �� �� �� }\015\012������%
//<ICS: \015\012{ # �� 72 �� ������ʹ(3f) vs ��С��(1f) �� �� �� ʼ }\015\012������%
//<ICS: \015\012{ # �� 54 �� ����Ԫ˧(2��) vs �ϵ�һ��(1��) �� �� �� �� ɱ }\015\012������%
//<ICS: \015\012{ * �� 55 �� ��������(5f) �� �� �� ս }\015\012������%
//<ICS: \015\012{ # �� 67 �� ltaoys(2f) vs ����������(9��) �� �� �� �� ʱ }\015\012������%
//<ICS: \015\012{ * �� 55 �� �켦�ȼ���(4f) �� �� �� �� }\015\012������%
//<ICS: \015\012{ # �� 54 �� ����Ԫ˧(2��) vs �ϵ�һ��(1��) �� �� �� ʼ }\015\012������%
//<ICS: \015\012{ * �� 75 �� ��������(5f) �� �� �� �� }\015\012������%%
//<ICS: \015\012{ * �� 118 �� ����С��(1��) �� �� �� �� }\015\012������%
//<ICS: \015\012{ + �����ֳ�(7��)  �� �� �� ��. }\015\012������%
//<ICS: \015\012{ # �� 100 �� ̷ӽ��(2��) vs �Ϲ�(6f) �� ��  Ͷ �� �� �� }\015\012������%
//<ICS: \015\012{ - ��˾�R(����)  �� �� ȥ�� . }\015\012������%
//<ICS: \015\012{ # �� 66 �� hualeyi(4��) vs ��ˮ��(4f) �� ��  Ͷ �� �� �� }\015\012������%
//<ICS: \015\012{ * �� 100 �� �Ϲ�(6f) �� �� �� �� }\015\012������%
//<ICS: \015\012{ * �� 81 �� anabc(5f) �� �� �� �� }\015\012������%
//<ICS: \015\012{ + �����(8��)  �� ��. }\015\012������%
//<ICS: \015\012{ + �ٶλ��j(4��)  �� ��. }\015\012������%
//<ICS: \015\012{ Table 81 Side Reset }\015\012������%
//<ICS: \015\012{ * �� 67 �� ����������(9��) �� �� �� �� }\015\012������%
//<ICS: \015\012{ - �Ϲ�(4r)  �� ��. }\015\012������%
//<ICS: \015\012{ * �� 120 �� �����ֳ�(3��) �� �� �� ս }\015\012������%
//<ICS: \015\012{ + ���µ�һ(9��)  �� ��. }\015\012������%
//<ICS: \015\012{ - ������(����)  �� ���� ȥ�� . }\015\012������%
//<ICS: \015\012{ * �� 116 �� jjyyahg(2��) �� �� �� �� }\015\012������%
//<ICS: \015\012{ + wonaigaoqi(5r)  �� ��. }\015\012������%
//<ICS: \015\012{ - ��ѩ��(3��)  �� �� ȥ�� . }\015\012������%
//<ICS: \015\012{ * �� 81 �� ��˧(5f) �� �� �� �� }\015\012������%
//<ICS: \015\012{ * �� 100 �� jjyyahg(2��) �� �� �� �� }\015\012������%
//<ICS: \015\012{ # �� 59 �� ��̳��ʥ(1f) vs ���뿳�㰡(4��) �� �� �� �� ɱ }\015\012������%
//<ICS: \015\012{ * �� 59 �� ���뿳�㰡(4��) �� �� �� �� }\015\012������%
//<ICS: \015\012{ * �� 59 �� ���뿳�㰡(4��) �� �� �� �� }\015\012������%
//<ICS: \015\012{ # �� 100 �� ̷ӽ��(2��) vs jjyyahg(2��) �� �� �� ʼ }\015\012������%
//<ICS: \015\012{ # �� 68 �� ����С�Ʒ�(���) vs ��˳��һ(��ħ) �� �� �� �� ʱ }\015\012������%
//<ICS: \015\012{ * �� 81 �� ��˧(5f) �� �� �� �� }\015\012������%
//<ICS: \015\012{ # �� 59 �� ��̳��ʥ(1f) vs ���뿳�㰡(4��) �� �� �� ʼ }\015\012������%
//<ICS: \015\012{ * �� 67 �� ltaoys(2f) �� �� �� �� }\015\012������%
//<ICS: \015\012{ + �ؼ�����(6��)  �� ��. }\015\012������%
//<ICS: \015\012{ * �� 78 �� ltaoys(2f) �� �� �� �� }\015\012������%
//<ICS: \015\012{ + ����(2��)  �� ��. }\015\012������%
//<ICS: \015\012{ + 쭷�쳵(5r)  �� ��. }\015\012������%
//<ICS: \015\012{ * �� 75 �� ��������(5f) �� �� �� �� }\015\012������%
//<ICS: \015\012{ - �����(8��)  �� ���� ȥ�� . }\015\012������%
//<ICS: \015\012{ * �� 118 �� ��˧(5f) �� �� �� �� }\015\012������%
//<ICS: \015\012{ # �� 78 �� ltaoys(2f) vs ��ʫ��(2f) �� �� �� ʼ }\015\012������%
//<ICS: \015\012{ - ����(2r)  �� �� ȥ�� . }\015\012������%
//<ICS: \015\012{ * �� 55 �� �켦�ȼ���(4f) �� �� �� �� }\015\012������%
//<ICS: \015\012{ + ��ɽ��Ժ��(6��)  �� ���� �� ��. }\015\012������%
//<ICS: \015\012{ * �� 55 �� �켦�ȼ���(4f) �� �� �� �� }\015\012������%
//<ICS: \015\012{ * �� 55 �� �켦�ȼ���(4f) �� �� �� �� }\015\012������%
//<ICS: \015\012{ - ��ɽ��Ժ��(6��)  �� ���� ȥ�� . }\015\012������%
//<ICS: \015\012{ - xyzfzs(5r)  �� ���� ȥ�� . }\015\012������%
//<ICS: \015\012{ * �� 55 �� �켦�ȼ���(4f) �� �� �� �� }\015\012������%
//<ICS: \015\012{ + ����(3r)  �� ��. }\015\012������%
//<ICS: \015\012{ # �� 117 �� �㻹����(6f) vs ��������(5f) �� ��  Ͷ �� �� �� }\015\012������%
//<ICS: \015\012{ - ����������(4��)  �� ��. }\015\012������%
//<ICS: \015\012{ + ��������(5r)  �� ��. }\015\012������%
//<ICS: \015\012{ * �� 116 �� ��������(6f) �� �� �� �� }\015\012������%
//<ICS: \015\012{ + �°�(����)  �� ��. }\015\012������%
//<ICS: \015\012{ # �� 117 �� �㻹����(6f) vs ��������(5f) �� �� �� ʼ }\015\012������%
//<ICS: \015\012{ # �� 65 �� ������(3f) vs �׿�������(5f) �� ��  Ͷ �� �� �� }\015\012������%
//<ICS: \015\012{ * �� 55 �� wonaigaoqi(5f) �� �� �� �� }\015\012������%
//<ICS: \015\012{ Table 116 Clock 1-1-10 }\015\012������%
//<ICS: \015\012{ - ǿ���޵�(����)  �� ���� ȥ�� . }\015\012������%
//<ICS: \015\012{ - ��������(5r)  �� �� ȥ�� . }\015\012������%
//<ICS: \015\012{ + ������ò(2r)  �� ��. }\015\012������%\015\012{ Table 116 Side Reset }\015\012������%
//<ICS: \015\012{ # �� 118 �� ���޻�(8��) vs ��˧(5f) �� �� �� ʼ }\015\012������%
//<ICS: \015\012{ * �� 4 �� ��ߴ����(2��) �� �� �� ս }\015\012������%
//<ICS: \015\012{ * �� 75 �� ��������(5f) �� �� �� �� }\015\012������%
//<ICS: \015\012{ * �� 3 �� ����(3r) �� �� �� �� }\015\012������%
//<ICS: \015\012{ # �� 85 �� ����(5f) vs qiyujin(4f) �� �� �� �� ɱ }\015\012������%
//<ICS: \015\012{ * �� 65 �� �׿�������(5f) �� �� �� �� }\015\012������%
//<ICS: \015\012{ - �һ�����(5��) ����������ı���ģ��,���е�˼��  ������ͬ�ĵط�. �� ��. }\015\012������%
//<ICS: \015\012{ * �� 65 �� ��������(5f) �� �� �� �� }\015\012������%
//<ICS: \015\012{ - �켦�ȼ���(2r)  �� �� ȥ�� . }\015\012������%
//<ICS: \015\012{ * �� 66 �� hualeyi(4��) �� �� �� �� }\015\012������%
//<ICS: \015\012{ - �����(3��)  �� ���� ȥ�� . }\015\012������%
//<ICS: \015\012{ # �� 65 �� ������(3f) vs ��������(5f) �� �� �� ʼ }\015\012������%
//<ICS: \015\012{ - hualeyi(3r)  �� ��. }\015\012������%
//<ICS: \015\012{ + ��ս����(3��)  �� ��. }\015\012������%
//<ICS: \015\012{ # �� 84 �� ����(8��) vs ��ͨ(3f) �� �� �� �� ʱ }\015\012������%
//<ICS: \015\012{ + ��һ����(����)  �� ��. }\015\012������%
//<ICS: \015\012{ # �� 85 �� ����(4f) vs qiyujin(4f) �� �� �� ʼ }\015\012������%
//<ICS: \015\012{ # �� 84 �� ����(8��) vs ��ͨ(3f) �� �� �� ʼ }\015\012������%
//<ICS: \015\012{ + ʷ��(2��)  �� ��. }\015\012������%
//GameEnds(0, (null), 2)
