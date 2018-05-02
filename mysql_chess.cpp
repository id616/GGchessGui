#include "stdafx.h"
#include "chess.h"
#include "data.h"

#ifdef USE_MYSQL_DATABASE
void  
initializeMySql(void){
	//
	
	if(appData.sql_installed){
		if(mysql_init(&DIS.mysql) == NULL){
            LogOut(ColorTell,"���ܳ�ʼ��MYSQL���ݿ�����!!, ��ȷ��MYSQL��û��װ....\n", true); 
		}
        else{
			/*pmycon = MysqlCreateConnect(&mysql,sql_host,
			sql_user,sql_pass,sql_db,sql_port);*/	

			if(mysql_real_connect(&DIS.mysql,appData.sql_host,
				appData.sql_user,appData.sql_pass,appData.sql_db_chess,
				appData.sql_port,NULL,0) != NULL){
					mysql_set_character_set(&DIS.mysql, MYSQLCHAESET);
					//DispLog("��ʼ��Mysql���ݿ�ɹ�!");
					//DispLog(DIS.mysql.server_version);
                    LogOut(ColorShout,"��ʼ��Mysql���ݿ�ɹ�!", true);
                    LogOut(ColorTell, DIS.mysql.server_version, true);
                    LogOutput("\n",1,FALSE); //�س�����
			}
			else{
				//DispLog("��ʼ��Mysql���ݿ�ʧ��!");
                LogOut(ColorShout,"��ʼ��Mysql���ݿ�ʧ��!\n", true);
                //LogOutput("\n",1,FALSE); //�س�����
			}
		}
	}
	else{
		//DispLog("MySql���ݿ�δ���أ���");
        LogOut(ColorTell,"MySql���ݿ�δ���أ���\n", true);
        //LogOutput("\n",1,FALSE); //�س�����
	}
}
#endif





#ifdef USE_MYSQL_DATABASE

bool					//isUpdate ������ͬ���Ƿ�Ҫ����
MysqlSaveGGqj(GameQJ *pgg, MYSQL* mycon, bool isUpdate){
	char qbuf[1536];
	int samenum;
	int qjid;
	MYSQL_RES *res;

	//�ȵ��ж�һ�²���������Ƿ�����
	if(false == IsGGqjNormal(pgg)){
		//DispLog("Ҫ��������ײ�������!!");
        LogOut(ColorTell,"Ҫ��������ײ�������!!\n", false);
        //LogOutput("\n",1,FALSE) //�س�����
		return false;
	}

	//�Ƚ����״���һ��
	
	for(int i=0; i<pgg->qipulen; i++){  
		//�������׷�����һ��,�����Ͳ�̫��������ͬ����
		qbuf[pgg->qipulen-i-1] = P90ASC[pgg->qipu[i]];
	}
	memcpy(pgg->qipu,qbuf,pgg->qipulen);
	//���ж�һ��,��û����ͬ������������,���������һ��,û��,�����
	StringCbPrintf(qbuf,sizeof(qbuf),
		"select qjid from ggqj where qipu = '%s' limit 1",pgg->qipu);
	if(mysql_query(mycon,qbuf)){
		//int kkk=0;
		return false;
	}
	res		= mysql_store_result(mycon);
    samenum	= (int)mysql_num_rows(res);

	//MYSQL_FIELD *field = mysql_
	//MYSQL_ROW mysql_fetch_row(MYSQL_RES *result) 
	if(samenum>0){
		MYSQL_ROW myrow = mysql_fetch_row(res);
		qjid = atoi(myrow[0]);
	}

	mysql_free_result(res);
	res = NULL;

	if(samenum >0){								//����ͬ�����
		qbuf[0] = 0;
		//StringCbPrintf(qbuf, sizeof(qbuf),
		//	"������ %d ����ͬ������������!",samenum);
		//DispLog(qbuf);
		//����һ�����
		//SendMessage(hStatusBar,SB_SETTEXT,StaBarCom,(LPARAM)buf);
		if(isUpdate){
			StringCbPrintf(qbuf,sizeof(qbuf),
				"update ggqj set rname='%s', relo=%d,bname='%s',belo=%d,score=%d,result='%s',ischecked='%d',islearned='%d',addr='%s',note='%s' where qjid=%d",
				pgg->Rname,pgg->Relo,pgg->Bname,pgg->Belo,pgg->score,pgg->resultDetails,pgg->isChecked,pgg->isLearned,pgg->from,pgg->note,qjid);
			if(mysql_query(mycon,qbuf)){
				//DispLog("UPDATE qiju ʧ��! <MysqlSaveGGqj>"); /*pgg->isChecked*/
				return false;
			}else{
				StringCbPrintf(qbuf,MSG_SIZ,"���������ֱ�ţ�%d �ɹ�����ͬ����%d",qjid,samenum);
				//DispLog(qbuf);
				//SendMessage(hStatusBar,SB_SETTEXT,StaBarCom,(LPARAM)qbuf);
				//DispLog("�ɹ�������һ����ֵ�MYSQL���ݿ�");
			}
		}
	}
	else{
		StringCbPrintf(qbuf,sizeof(qbuf),
			"insert into ggqj (qipu,rname,relo,bname,belo,score,result,ischecked,islearned,addr,note) values ('%s','%s',%d,'%s',%d,%d,'%s','%d','%d','%s','%s')",
			pgg->qipu,pgg->Rname,pgg->Relo,pgg->Bname,pgg->Belo,pgg->score,pgg->resultDetails,pgg->isChecked,pgg->isLearned,pgg->from,pgg->note);
		if(mysql_query(mycon,qbuf)){
			//DispLog("INSERT qiju ʧ��! <MysqlSaveGGqj>");
			return false;
		}else{
			//DispLog("�ɹ�������һ����ֵ�MYSQL���ݿ�");
		}
	}
	return true;
}
bool //�õ�һ��δУ�Ե����
MysqlGetOneUncheckGGqj(GameQJ *pgg, MYSQL* mycon){
	
	if (DIS.gameMode != BeginningOfGame) {			//���Ǹտ�ʼ��Ϸ
		GameReset(FALSE, TRUE);
	}
	
	
	//char qbuf[1000];
	MYSQL_RES	*res;
	bool		isok		= false;
	int			num			= 0;
    char		qbuf[1536];
	//StringCbPrintf(qbuf,sizeof(qbuf),
	//	"select * from ggqj where ischecked = 0 order by qjdi desc");
	//  "select * from ggqj where ischecked = 1 and islearned = 0 order by qjid desc LIMIT 0,1"

	if(mysql_query(mycon,"select * from ggqj where ischecked = 0 order by qjid desc LIMIT 1")){
	//if(mysql_query(mycon,"select * from ggqj where score = 80 and ischecked = 1 and islearned = 0 order by qjid desc LIMIT 0,1")){
		return false;
	}
	res = mysql_use_result(mycon);
    MYSQL_ROW myrow = mysql_fetch_row(res);
	if(myrow == NULL){
		//DispLog("��ǰ��û��δУ�Ե�������!");
		return false;
	}
	//�õ����׺�����
	pgg->qjid = atoi(myrow[0]);
	//StringCbPrintf(pgg->qipu,sizeof(pgg->qipu),  myrow[1]);
	int len = (int)strlen(myrow[1]);
	memcpy(pgg->qipu,myrow[1],len);
	pgg->qipu[len] = 0;

	StringCbPrintf(pgg->Rname,sizeof(pgg->Rname),myrow[2]);
	pgg->Relo = atoi(myrow[3]);
	StringCbPrintf(pgg->Bname,sizeof(pgg->Bname),myrow[4]);
	pgg->Belo		= atoi(myrow[5]);
	pgg->score		= atoi(myrow[6]);
	StringCbPrintf(pgg->resultDetails,sizeof(pgg->resultDetails), myrow[7]);
	pgg->isChecked  = atoi(myrow[8]);
	pgg->isLearned  = atoi(myrow[9]);
	StringCbPrintf(pgg->from,sizeof(pgg->from), myrow[10]);
	StringCbPrintf(pgg->note,sizeof(pgg->note), myrow[11]);

	pgg->qipulen  = (int)strlen(pgg->qipu);
    //��ԭһ������
	for(int i=0; i<pgg->qipulen; i++){
		//pgg->qipu[i] = P90ASC[pgg->qipu[i]];
		//qbuf[pgg->qipulen-i-1] = P90ASC[pgg->qipu[i]];
		qbuf[i] = ASCP90[pgg->qipu[pgg->qipulen-i-1]];
	}
	memcpy(pgg->qipu,qbuf,pgg->qipulen);   //���ü� ��0����

	mysql_free_result(res);
	res = NULL;

	

	LoadGameOneGameFromMysql(pgg,true);
   
	return isok;
}

bool         //�õ������һ������ľ��������
MysqlGetOneFaceScore(position_t* pos, bool isWhiteGo,qkface_t *pf, MYSQL *my){
	////struct qkface_t {
	////	int  qnum;
	////	int  qsc;
	////	char qf32[36];   //miroronly
	////};
	//pf->qsc = SCORE_NO;
	//char qbuf[512];
	//pf->qf32[32] = 0;//���Ͻ�����־��
	//FindMirrorOnly(b90,(int*)qbuf,isWhiteGo);	
	//for(int i=0; i<32; i++){
	//	pf->qf32[i] = P90ASC[qbuf[i]];   //�õ�ASCII
	//}
 //   
	//MYSQL_RES *res;
	//
	//StringCbPrintf(qbuf,512,"SELECT qnum,qsc FROM tface WHERE qf32='%s' LIMIT 1",pf->qf32);

	//if(mysql_query(my,qbuf)){
	//	return false;
	//} 
	//res = mysql_use_result(my);
	//MYSQL_ROW myrow = mysql_fetch_row(res);
	//if(myrow == NULL){			
	//	mysql_free_result(res);
	//	res = NULL;
	//	return false;
	//}
	////pgg->Belo		= atoi(myrow[5]);
	//pf->qnum = atoi(myrow[0]);
	//pf->qsc  = atoi(myrow[1]);

	//mysql_free_result(res);
	//res = NULL;
    
	return true;
}
bool		//����ǰ������������� 
MysqlSaveOneFace(position_t* pos,bool isWhiteGo,qkface_t *pf, MYSQL *my){	
	//char qbuf[MSG_SIZ];
	////MYSQL_RES *res;
	////int samenum;
	////#define   SCORE_NO		101
	////#define   SCORE_B_WIN		0
	////#define   SCORE_B_GOOD	35
	////#define   SCORE_B_LITTLE	20
	////#define	SCORE_BALANCE   50
	////#define   SCORE_R_LITTLE	68
	////#define   SCORE_R_GOOD	80
	////#define   SCORE_R_WIN		100

	//if((pf->qsc == 101) || (pf->qsc != 0 && pf->qsc != 20 && pf->qsc != 35 && pf->qsc != 50
	//	&& pf->qsc != 68 && pf->qsc != 80 && pf->qsc != 100)){
	//	MessageBox(hwndMain,"Ҫ����ĵ÷ֲ���ȷ��...","������...",MB_OK);
	//	return false;
	//}

	//FindMirrorOnly(b90,(int*)qbuf,isWhiteGo);  //	void   //�ҵ���ǰB90��ΨһD8
	//for(int i=0; i<32; i++){
	//	pf->qf32[i] = P90ASC[qbuf[i]];   //�õ�ASCII
	//}
	//pf->qf32[32] = 0;        // ����һ����β
	////pf->qnum     = 1;
	//if((!isWhiteGo && pf->qsc < SCORE_B_LITTLE) || (isWhiteGo && pf->qsc > SCORE_R_LITTLE))
	//{		//ɾ�����õľ���
	//	StringCbPrintf(qbuf,sizeof(qbuf),"delete from tface where qf32='%s'",pf->qf32);
	//	if(mysql_query(my,qbuf)){
	//		return false;
	//	}
	//	return true;
	//}
	////�Ȳ������,������ɹ�,�ͱ�ʾ���о���,�ͽ���������1
	//StringCbPrintf(qbuf,sizeof(qbuf),"insert into tface (qsc,qf32) value (%d,'%s')",pf->qsc,pf->qf32);
	//if(mysql_query(my,qbuf)){
	//	//�������о���,
	//	StringCbPrintf(qbuf,sizeof(qbuf),"update tface set qnum=qnum+1,qsc=%d where qf32='%s'",pf->qsc,pf->qf32);
	//	if(mysql_query(my,qbuf)){
	//		return false;
	//	}
	//}
	return true;	
}
bool 
MysqlGetScoreFromQkFaces(position_t* pos,bool isWhiteGo,qkface_t *pf, MYSQL *my){
    return false;
	//list_t list;	
	//int presc = pf->qsc;					   //����ԭ���ĵ÷�
	//int temp;
	//bool isScoreInQK = false;
	//gen_legal_moves(&list,b90,isWhiteGo);		//��Ʒ���е��߲�


	//if(isWhiteGo){								//��������Ǻ����
	//	temp = 0;
	//	for(int i=0; i<list.size; i++){
	//		//��һ��
	//		sq_t from		= MOVE_FROM(list.move[i]);
	//		sq_t to			= MOVE_TO(list.move[i]);
	//		sq_t tochess	= b90[to];
	//		b90[to]			= b90[from];
	//		b90[from]		= NOCHESS;
	//		if(MysqlGetOneFaceScore(b90,false,pf,my)){	//����е÷�
	//			isScoreInQK = true;
	//			if(pf->qsc > temp){
	//				temp = pf->qsc;
	//			}
	//		}			
	//		//��ԭ
	//		b90[from]		= b90[to];
	//		b90[to]         = tochess;
	//		if(temp == 100){		//��������Ǻ�������
	//			break;
	//		}
	//	}
	//	//�жϵ�ǰ�÷� pf->qsc = sc;
	//	if(isScoreInQK){
	//		pf->qsc = temp;
	//	}
	//	else{
	//		pf->qsc = presc;
	//	}
	//}
	//else{	//��������Ǻڵ���	
	//	temp = 100;
	//	for(int i=0; i<list.size; i++){
	//		//��һ��
	//		sq_t from		= MOVE_FROM(list.move[i]);
	//		sq_t to			= MOVE_TO(list.move[i]);
	//		sq_t tochess	= b90[to];
	//		b90[to]			= b90[from];
	//		b90[from]		= NOCHESS;
	//		if(MysqlGetOneFaceScore(b90,true,pf,my)){	//����е÷�
	//			isScoreInQK = true;
	//			if(pf->qsc < temp){
	//				temp = pf->qsc;
	//			}
	//		}			
	//		//��ԭ
	//		b90[from]		= b90[to];
	//		b90[to]         = tochess;
	//		if(temp == 0 ){		//��������Ǻ�������
	//			break;
	//		}
	//	}
	//	if(isScoreInQK){
	//		pf->qsc = temp;
	//	}
	//	else{
	//		pf->qsc = presc;
	//	}
	//	//�жϵ�ǰ�÷�
	//}

	//return MysqlSaveOneFace(b90,isWhiteGo,pf,my);
	//#define   SCORE_NO		101
	//#define   SCORE_B_WIN		0
	//#define   SCORE_B_GOOD	35
	//#define   SCORE_B_LITTLE	20
	//#define	SCORE_BALANCE   50
	//#define   SCORE_R_LITTLE	68
	//#define   SCORE_R_GOOD	80
	//#define   SCORE_R_WIN		100

   
	
}


bool //�õ�һ����У�Ե������ѧϰһ��
MysqlGetOneCheckedAndLearn(GameQJ *pgg, MYSQL *my){

    return false;

	//MYSQL_RES *res;
	//bool isok = false;
	//char qbuf[1536];
	////������ݿ���û��δѧϰ�������

	//if(mysql_query(my,"select * from ggqj where ischecked = 1 and islearned = 0 order by qjid desc LIMIT 0,1")){
	////if(mysql_query(my,"select * from ggqj where score = 80 and ischecked = 1 and islearned = 0 order by qjid desc LIMIT 0,1")){
	//	return false;
	//}	
	//res = mysql_use_result(my);
	//MYSQL_ROW myrow = mysql_fetch_row(res);
	//if(myrow == NULL){
	//	DispLog("��ǰ��û��У�Ժõĵ�������!");
	//	return false;
	//}
	////�õ����׺�����
	//pgg->qjid = atoi(myrow[0]);
 //   int len = (int)strlen(myrow[1]);
	//memcpy(pgg->qipu,myrow[1],len);
 //   
	//pgg->qipulen   = len;
	//pgg->qipu[len] = 0;				//���Ͻ�β��
	////StringCbPrintf(pgg->Rname,sizeof(pgg->Rname),myrow[2]);
	////pgg->Relo = atoi(myrow[3]);
	////StringCbPrintf(pgg->Bname,sizeof(pgg->Bname),myrow[4]);
	////pgg->Belo		= atoi(myrow[5]);
	//pgg->score		= atoi(myrow[6]);
	////StringCbPrintf(pgg->resultDetails,sizeof(pgg->resultDetails), myrow[7]);
	////pgg->isChecked  = atoi(myrow[8]);
	////pgg->isLearned  = atoi(myrow[9]);
	////StringCbPrintf(pgg->from,sizeof(pgg->from), myrow[10]);
	////StringCbPrintf(pgg->note,sizeof(pgg->note), myrow[11]);

	//////��ԭһ������
	//for(int i=0; i<pgg->qipulen; i++){
	//	//pgg->qipu[i] = P90ASC[pgg->qipu[i]];
	//	//qbuf[pgg->qipulen-i-1] = P90ASC[pgg->qipu[i]];
	//	qbuf[i] = ASCP90[pgg->qipu[pgg->qipulen-i-1]];
	//}
	//memcpy(pgg->qipu,qbuf,pgg->qipulen);   //���ü� ��0����

	//mysql_free_result(res);
	//res = NULL;
 //   
	////���ϵõ���һ��У�Ժ��˵�����
 //   Board90 b90;
	//bool    who = D8ToB90((int*)pgg->qipu,b90);	//˭����,����ÿ�ʼ����

	//char *pm		= pgg->qipu+32;		//�岽ָ��
	//char *pend		= pgg->qipu + pgg->qipulen;
	//sq_t from;
	//sq_t to;
	//sq_t Eat[1000];                     //����Ե�������
	//qkface_t qkface;
	//int num = (pgg->qipulen-32)/2;           //�岽��Ŀ
	//if(who){
	//	//�ߵ����
	//	for(int i=0; i<num; i++){
	//		from		= *(pm+i*2);
	//		to			= *(pm+i*2+1);
	//		Eat[i]		= b90[to];
	//		b90[to]		= b90[from];
	//		b90[from]	= NOCHESS;
	//		who        ^= 0x01;
	//	}
	//	//��ǰ����  
	//	//qkface.qsc = pgg->score;   //���һ��,���ϵ÷�
	//	for(int i=(num-1); i>=0; i--){	
	//		qkface.qsc = pgg->score;   
	//		MysqlGetScoreFromQkFaces(b90,who,&qkface,my);			
	//		who         ^= 0x01;
	//		from         = *(pm+i*2);
	//		to			 = *(pm+i*2+1);
	//		b90[from]    = b90[to];
	//		b90[to]      = Eat[i];
	//		//qkface.qsc   = SCORE_NO;
	//	}		
	//}
	//else{
	//	MessageBox(hwndMain,"������Ǻڵ������ۣ�","����һ��",MB_OK);
	//	return false;
	//}
	////�������ֱ�Ϊѧϰ����
	////"update ggqj set rname='%s', relo=%d,bname='%s',belo=%d,score=%d,result='%s',ischecked='%d',islearned='%d',addr='%s',note='%s' where qjid=%d",
	//StringCbPrintf(qbuf,sizeof(qbuf),"update ggqj set islearned = 1 where qjid=%d",pgg->qjid);
	//if(mysql_query(my,qbuf)){
	//	MessageBox(hwndMain,"�������ʧ����!!","MysqlGetOneCheckedAndLearn",MB_OK);
	//	return false;
	//}
    //return true;
}


//bool 
//TestMysqlGetOneQj(GameQJ *pgg, MYSQL *my){
//
//}

//void 
//FindZiShu(int ff[],int start,int num){
//	//for(int n=0;n<num;n++){
//		for(int i=start,n=0;n<num;i++){
//			if(i%2==0){
//				continue;
//			}
//			//�ж�3��5��7��9����i/2�Ƿ���i������
//			int j=3;
//			while(j<=i/2 && i%j!=0){
//				j+=2;
//			}
//			//��������������i�����ӣ���i������
//			if(j>i/2){
//				ff[n++] = i;
//			}
//		}
//	//}
//}
//
//void 
//FillZiShu(void){
//	//extern int ZF90[90];
//	//extern int KF32[32];
//	
//	FindZiShu(ZF90,91*91,91);
//	FindZiShu(KF32,90,32);
//
//	//���²���һ�¾�û���ظ��������
//	
//}
//
//void 
//TestIsSame(void){
//	FillZiShu();
//	F64Count = 0;
//	////�ж���û����ͬ�ľ��������
//	////int face[32];
//	////for(int i=0; i<32; i++){
//	////	//��������
//	////	for(int k=0; k<90; k++){
//	////		face[i] = ZF90[k];
//
//	////	}
//	////}
//	////TTFACE[32]
//	////ZeroMemory(TTFACE,sizeof(TTFACE));
//	////memset(TTFACE,90,sizeof(TTFACE));
//	//for(int i=0; i<32; i++){
//	//	TTFACE[i] = 90;
//	//}
//	//int weitotal = 1;
//	//F64Count = 0;
//	////GetOneFace(TTFACE,0,0,0);
//	//while(TTFACE[31] > 0){
//	//	TTFACE[0] --;
//	//	if(TTFACE[0] > 0){	
//	//		//�鿴��û����ͬ����
//	//		for(int i=1; i<weitotal; i++){
//	//			if(TTFACE[0] == TTFACE[i]){
//	//				break;
//	//			}
//	//			GetOneFaceAndStore(TTFACE);		
//	//		}				
//	//	}
//	//	else{
//	//		//����λ��
//	//		TTFACE[0] = 90;	
//	//		int i=1;
//	//		TTFACE[i] --;			
//	//		while(TTFACE[i] < 0){	//����λ		
//	//			TTFACE[i] = 90;
//	//			i++;
//	//			TTFACE[i] 
//	//		}
//	//		
//	//		
//	//		//for(int i=1; i<31; i++){
//	//		//	if(TTFACE[i] < 91){
//	//		//		break;		//��Ҫ�ٽ�λ��
//	//		//	}
//	//		//	else{			//��Ҫ�ٽ�λ��
//	//		//		TTFACE[i] = 0;					
//	//		//		i++;
//	//		//		TTFACE[i] ++;
//	//		//	}
//	//		//}
//	//	}		
//	//}
//}
//
//
//void
//TestMysqlSaveOneFace(Board90 b90,bool who,MYSQL *my){
//	char qbuf[MSG_SIZ];
//	char b32[36];
////	MYSQL_RES *res;
//	FindMirrorOnly(b90,(int*)qbuf,who);
//	for(int i=0; i<32; i++){
//		b32[i] = P90ASC[qbuf[i]];   //�õ�ASCII
//	}
//	b32[32] = 0;
//
//	//---------------------------------------------------
//	int fint = 0;
//	for( int i=0; i<32; i++){
//		fint += ZF90[b90[i]] * KF32[i];
//	}
//	StringCbPrintf(qbuf,sizeof(qbuf),
//		"insert into intface (Fint) value (%d)",fint);
//	if(mysql_query(my,qbuf)){
//		//DispLog("INSERT face ʧ��! <MysqlSaveGGqj>");		
//	}else{
//		//DispLog("�ɹ�������һ����ֵ�MYSQL���ݿ�");
//
//	}
//	//----------------------------------------------------
//
//	StringCbPrintf(qbuf,sizeof(qbuf),
//		"insert into tface (qf32) value ('%s')",b32);
//	if(mysql_query(my,qbuf)){
//		//DispLog("INSERT face ʧ��! <MysqlSaveGGqj>");		
//	}else{
//		//DispLog("�ɹ�������һ����ֵ�MYSQL���ݿ�");
//
//	}
//}
//bool 
//TestMysqlSaveFace(MYSQL *my,GameQJ *pgg){
//	MYSQL_RES *res;
//	bool isok   = false;
//	char qbuf[1536];
//	if(mysql_query(my,"select * from ggqj where ischecked = 0 order by qjid desc LIMIT 1")){
//		return false;
//	}
//    res = mysql_use_result(my);
//	MYSQL_ROW myrow = mysql_fetch_row(res);
//	if(myrow == NULL){
//		return false;
//	}
//	pgg->qjid = atoi(myrow[0]);
//	int len = (int)strlen(myrow[1]);
//	memcpy(pgg->qipu,myrow[1],len);
//	pgg->qipu[len] = 0;
//
//	pgg->qipulen  = (int)strlen(pgg->qipu);
//    //��ԭһ������
//	for(int i=0; i<pgg->qipulen; i++){
//		//pgg->qipu[i] = P90ASC[pgg->qipu[i]];
//		//qbuf[pgg->qipulen-i-1] = P90ASC[pgg->qipu[i]];
//		qbuf[i] = ASCP90[pgg->qipu[pgg->qipulen-i-1]];
//	}
//	memcpy(pgg->qipu,qbuf,pgg->qipulen);   //���ü� ��0����
//	mysql_free_result(res);
//	res = NULL;
//
//	char *pm		= pgg->qipu+32;		//�岽ָ��
//    Board90 b90;
//	sq_t from;
//	sq_t to;
//	bool    who = D8ToB90((int*)pgg->qipu,b90);	//˭����
//	int num = (pgg->qipulen-32)/2;              //�岽��Ŀ
//	if(who){
//		//�ߵ����
//		for(int i=0; i<num; i++){
//			from		= *(pm+i*2);
//			to			= *(pm+i*2+1);			
//			b90[to]		= b90[from];
//			b90[from]	= NOCHESS;
//			who        ^= 0x01;
//			TestMysqlSaveOneFace(b90,who,my);
//		}		
//	}
//	else{
//		MessageBox(hwndMain,"������Ǻڵ������ۣ�","����һ��",MB_OK);
//		return false;
//	}
//	//-------------------------------------------------------------------------
//	StringCbPrintf(qbuf,sizeof(qbuf),"update ggqj set ischecked = 1 where qjid=%d",pgg->qjid);
//	if(mysql_query(my,qbuf)){
//		MessageBox(hwndMain,"�������ʧ����!!","MysqlGetOneCheckedAndLearn",MB_OK);
//		return false;
//	}
//	//--------------------------------------------------------------------------
//
//	return true;
//}
//DWORD WINAPI 
//TestChecked_QJ_MysqlThread(LPVOID lpParam){
//	MYSQL mysql_test;
//	char buf[MSG_SIZ];
//
//	if(mysql_init(&mysql_test) == NULL){
//		DispLog("���ܳ�ʼ��MYSQL����,<TestChecked_QJ_MysqlThread>");
//		goto OutTest;
//	}
//	if(NULL == mysql_real_connect(&mysql_test,appData.sql_host,
//		appData.sql_user,appData.sql_pass,appData.sql_db_chess,
//		appData.sql_port,NULL,0))	{
//			DispLog("WebToMysqlThread,���ܽ���MYSQL����");
//			goto OutTest;
//	}	
//	mysql_set_character_set(&mysql_test, MYSQLCHAESET);
//
//	int testNum = 0;
//	GameQJ gg;
//	while(true){
//		if(TestMysqlSaveFace(&mysql_test,&gg) == false){
//			break;
//		}
//		testNum ++;
//		StringCbPrintf(buf,MSG_SIZ,"���ڲ��� %d",gg.qjid);
//		SendMessage(hStatusBar,SB_SETTEXT,StaBarCom,(LPARAM)buf);
//		if(!SendMessage(hwndToolBar,TB_ISBUTTONCHECKED,IDT_LEARN_QK,0)){
//			goto OutTest;        //�ְ����˵��밴ť
//		}
//	}
//
//OutTest:
//	StringCbPrintf(buf,MSG_SIZ,"��ǰ�ɹ�ѧϰ�� %d �����........",testNum);
//	SendMessage(hStatusBar,SB_SETTEXT,StaBarCom,(LPARAM)buf);
//	DispLog(buf);
//	mysql_close(&mysql_test);	
//	SendMessage(hwndToolBar,TB_CHECKBUTTON,IDT_LEARN_QK,false);//��ѧϰ��ť��������
//	return 0;
//}
//void 
//TestFaceEvent(void){
//	TestIsSame();
//   	DWORD dwThreadId, dwThrdParam = 1;
//	//����ѧϰ�߳�
//	HANDLE hlearnTH = CreateThread(
//		NULL,
//		NULL,
//		TestChecked_QJ_MysqlThread,
//		&dwThrdParam,
//		0,
//		&dwThreadId);
//	if(hlearnTH == NULL){
//		//StringCbPrintf(buf,MSG_SIZ,"��ʼWEB�����߳� %d ʧ�ܣ�",i);
//		DispLog("TEST���ѧϰ�߳�ʧ�ܣ�");
//	}
//	else{
//		//StringCbPrintf(buf,MSG_SIZ,"��ʼWEB�����߳� %d �ɹ���",i);
//		DispLog("TEST���ѧϰ�̳߳ɹ���...........��");
//		SetThreadPriority(hlearnTH,THREAD_PRIORITY_BELOW_NORMAL);
//	}	
//
//
//}

//**************************************************************************************
#endif