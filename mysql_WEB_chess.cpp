#include "stdafx.h"
#include "chess.h"
#include "data.h"

#define MAX_DOWN    12000
#define   WNUM      5          //web �����߳���


#ifdef USE_MYSQL_DATABASE
bool 
GetOneNodeFromWXF(char *string, char *node, char *ret, int retlen){
	//bool isok = false;
	char *pstart = strstr(string,node);
	if(pstart == NULL) return false;
	pstart += 8;
	for(int i=0; i<retlen; i++){
		if(*pstart == 0x0d){			
			*(ret-1) = 0;  //����һ����β
			return true;			
		}
		*ret++ = *pstart++;		
	}
	
	return false;
}
bool 
GetOneNodeFromWXFelo(char *string, char *node, char *ret, int retlen, bool iselo){
	bool isok = false;
	char *pstart = strstr(string,node);
	if(pstart == NULL) return false;
	pstart += 8;
	if(!iselo){
		for(int i=0; i<retlen; i++){
			if(*pstart == 0x3b){
				*(ret-1) = 0;  //����һ����β
				return true;
			}
			*ret++ = *pstart++;		
		}		
	}
	else{
		pstart = strstr(pstart,";");
		if(pstart == NULL) return false;
		memcpy(ret,pstart+2,4);
		*(ret+4) = 0;
		return true;
	}
	return false;
}
bool 
getOneNodeFromBuf(char *string, char *nodetype, char *ret, int retlen){
	//pdest = strstr( string, str );
    //result = (int)(pdest - string + 1);
	//#include <string.h>
	//#include <stdio.h>
	//
	//char str[] =    "lazy";
	//char string[] = "The quick brown dog jumps over the lazy fox";
	//char fmt1[] =   "         1         2         3         4         5";
	//char fmt2[] =   "12345678901234567890123456789012345678901234567890";
	//
	//int main( void )
	//{
	//char *pdest;
	//int  result;
	//printf( "String to be searched:\n   %s\n", string );
	//printf( "   %s\n   %s\n\n", fmt1, fmt2 );
	//pdest = strstr( string, str );
	//result = (int)(pdest - string + 1);
	//if ( pdest != NULL )
	//    printf( "%s found at position %d\n", str, result );
	//else
	//    printf( "%s not found\n", str );
	//}
	//Output
	char *pstart = strstr(string,nodetype);
	if(pstart == NULL){
		return false;
	}
	pstart += strlen(nodetype) + 1;
	char *pend   = strstr(pstart, nodetype);
	if(pend == NULL){
		return false;
	}
    
	int len = int(pend-pstart) - 1;
	if(len>retlen){
		return false;
	}

	//StringCbCopy(ret,len,pstart);  
	memcpy(ret,pstart,len);
	*(ret+len-1) = 0;

	return true;
}



bool 
DownloadFromUrl(char* url, char* string){
	DWORD bytes_read;     //���ص��ֽ���
	
	//��һ��internet����
    HINTERNET internet=InternetOpen("HTTP Downloader", INTERNET_OPEN_TYPE_PRECONFIG, 
        NULL, NULL, NULL);

	if(!internet){
		//throw "InternetOpen error!";
		//DispLog("InternetOpen error!");
        LogOut(ColorTell,"InternetOpen error!\n", false);
        //LogOutput("\n",1,FALSE) //�س�����
		return false;
	}

	//DispLog(url);
    LogOut(ColorTell,url,true);
    LogOutput("\n",1,FALSE); //�س�����

	//��һ��http url��ַ
    HINTERNET file_handle=InternetOpenUrl(internet, url, NULL, 0, INTERNET_FLAG_RELOAD, 0);
       // INTERNET_FLAG_RELOAD, 0);   INTERNET_FLAG_HYPERLINK

	if(!file_handle){ 		
		//throw "InternetOpenUrl error! - Maybe you should add Http:// or Ftp://";		
		//DispLog("InternetOpenUrl error! - Maybe you should add Http:// or Ftp://");
         LogOut(ColorTell,"InternetOpenUrl error! - Maybe you should add Http:// or Ftp://\n", false);
         //LogOutput("\n",1,FALSE) //�س�����
		return false;
	}

	  //��url��ַ�ж�ȡ�ļ����ݵ�������buffer
    BOOL b = InternetReadFile(file_handle, string, MAX_DOWN, &bytes_read);
	if(!b){
        //throw "InternetReadFile error!";
		//DispLog("InternetReadFile error!");
        LogOut(ColorTell,"InternetReadFile error!\n", false);
        //LogOutput("\n",1,FALSE) //�س�����
		return false;
	}
    
	*(string+bytes_read) = 0;

	//DispLog(string);

	// //�ر�����
 //   InternetCloseHandle(internet);
 //   
	////=========================================================
	//ggqj_t gg;

	//if(!getOneNodeFromBuf(string,"DhtmlXQ_red",gg.Rname,sizeof(gg.Rname))){
	//	DispLog("DhtmlXQ_red!");
	//	return false;
	//}

	//if(!getOneNodeFromBuf(string,"DhtmlXQ_black",gg.Bname,sizeof(gg.Bname))){
	//	DispLog("DhtmlXQ_black!");
	//	return false;
	//}

	//char rate[10];
	//if(!getOneNodeFromBuf(string,"DhtmlXQ_redrating",rate,sizeof(rate))){
	//	DispLog("DhtmlXQ_redrating!");
	//	return false;
	//}
	//gg.Relo = atoi(rate);

	//if(!getOneNodeFromBuf(string,"DhtmlXQ_blackrating",rate,sizeof(rate))){
	//	DispLog("DhtmlXQ_blackrating!");
	//	return false;
	//}
	//gg.Belo = atoi(rate);
 //   
	//char binit[80];
	//if(!getOneNodeFromBuf(string,"DhtmlXQ_binit",binit,sizeof(binit))){
	//	DispLog("DhtmlXQ_binit!");
	//	return false;
	//}

	//char movelist[512*4+64];
	//if(!getOneNodeFromBuf(string,"DhtmlXQ_movelist]'",movelist,sizeof(movelist))){
	//	DispLog("DhtmlXQ_movelist!");
	//	return false;
	//}

	//StringCbPrintf(gg.from,sizeof(gg.from),"dpxq");

	return true;
}

bool //�õ�from
GetIntFromWXFMove(sq_t b90[], sq_t* from, sq_t* ff,
	sq_t* tt, sq_t fromchess, bool who, int method, sq_t ch2, sq_t ch4){
//	//sq_t wxf_x;
//	//sq_t wxf_y;
//	//bool isok = false;
//	//if(ch >= '0' && ch <= '9'){
//	//	if(who == WHITE_GO){
//	//		wxf_x = 9 - (ch - '0');		
//	//	}
//	//	else{
//	//		wxf_x = ch - '0';
//	//	}
//	sq_t bb9[90];
//	memcpy(bb9,b90,90);
//
//	int qhnum;
//
//	if(ch2 < '0' || ch2 > '9'){	//����ǰ������		
//		//sq_t from;
//		//��һ�����ҳ���ͬ����
//		switch(ch2){
//			case '+':		//ǰ
//			case '-':
//				if((who == WHITE_GO && ch2 == '-')
//					|| (who == BLACK_GO && ch2 == '+')){	//�ҳ����������һ��							
//						for(int file=0; file<=8; file++){
//							qhnum = 0;
//							for(int rank=0; rank<=9; rank++){
//								if(b90[rank*9+file] == fromchess){
//									qhnum++;
//									if(qhnum==2){			//�ҵ�����
//										*from = rank*9 + file;
//										goto FIND_QH;
//									}
//								}
//							}
//						}
//				}
//				else{										//�ҳ����̵�����һ��
//					for(int file=0; file<=8; file++){
//						qhnum = 0;	
//						for(int rank=9; rank>=0; rank--){
//								if(b90[rank*9+file] == fromchess){
//									qhnum++;
//									if(qhnum==2){			//�ҵ�����
//										*from = rank*9 + file;
//										goto FIND_QH;
//									}
//								}
//							}
//					}					
//				}
//				return false;
//FIND_QH:			
//				*ff = S90toF(*from);
//				if(who == WHITE_GO){		//�����Ǻ�����					
//					*tt = 9 - (ch4 - '0');	
//				}
//				else{					
//					*tt = ch4 - '0' -1;			
//				}
//				return true;
//				break;			
//			default:
//				//MessageBox(hwndMain,"+-ERR","From WXF",MB_OK);
//				DispLog("+-ERR  From WXF");
//				return false;
//				break;
//		}	
//		
//	}
//	else{							//����ǰ������
//		if(who == WHITE_GO){		//�����Ǻ�����
//			*ff = 9 - (ch2 - '0');   
//			*tt = 9 - (ch4 - '0');	
//
//		}
//		else{
//			*ff = ch2 - '0' -1;
//			*tt = ch4 - '0' -1;			
//		}
//		for(int i=0; i<=9; i++){
//			if(b90[i*9 + *ff] == fromchess){				
//				//�����ж��ܲ�������
//				switch(fromchess){
//				case WhitePawn:
//					break;
//				case WhitePao:
//					break;
//				case WhiteChe:
//					break;
//				case WhiteMa:
//					break;
//				case WhiteXiang:
//					switch(method){
//				case '.':
//					return false;
//					break;
//				case '+':
//					if(i==5){
//						continue;
//					}
//					break;
//				case '-':
//					if(i==9){
//						continue;
//					}
//					break;
//				default:
//					return false;
//					break;
//					}
//					break;
//				case WhiteShi:
//					switch(method){
//				case '.':
//					return false;
//					break;
//				case '+':
//					if(i==7){
//						continue;
//					}
//					break;
//				case '-':
//					if(i==9){
//						continue;
//					}
//					break;
//				default:
//					return false;
//					break;
//					}
//					break;
//				case WhiteKing:
//					break;
//					//
//				case BlackPawn:
//					break;
//				case BlackPao:
//					break;
//				case BlackChe:
//					break;
//				case BlackMa:
//					break;
//				case BlackXiang:
//					switch(method){
//				case '.':
//					return false;
//					break;
//				case '+':
//					if(i==4){
//						continue;
//					}
//					break;
//				case '-':
//					if(i==0){
//						continue;
//					}
//					break;
//				default:
//					return false;
//					break;
//					}
//					break;
//				case BlackShi:
//					switch(method){
//				case '.':
//					return false;
//					break;
//				case '+':
//					if(i==2){
//						continue;
//					}
//					break;
//				case '-':
//					if(i==0){
//						continue;
//					}
//					break;
//				default:
//					return false;
//					break;
//					}
//					break;
//				case BlackKing:
//					break;
//				default:
//					break;
//
//				}
//				*from = (i*9 + *ff);
//				return true;
//			}
//		}
//	}

	
	//}
	return false;
}
bool //�õ�to
GetIntFromWXFMoveWithMethod(position_t* pos,sq_t from, sq_t* to, sq_t ff, sq_t tt, 
							sq_t fromchess, bool who, int method){

		//switch(method){
		//	case '.':			//ƽ											
		//		switch(fromchess){
		//			case WhitePawn:
		//				*to = char(from/9*9 + tt);
		//				break;
		//			case WhitePao:
		//				*to = char(from/9*9 + tt);
		//				break;
		//			case WhiteChe:
		//				*to = char(from/9*9 + tt);
		//				break;
		//			case WhiteMa:
		//				return false;
		//				break;
		//			case WhiteXiang:
		//				return false;
		//				break;
		//			case WhiteShi:
		//				return false;
		//				break;
		//			case WhiteKing:
		//				*to = char(from/9*9 + tt);
		//				break;
		//			//
		//			case BlackPawn:
		//				*to = char(from/9*9 + tt);
		//				break;
		//			case BlackPao:
		//				*to = char(from/9*9 + tt);
		//				break;
		//			case BlackChe:
		//				*to = char(from/9*9 + tt);
		//				break;
		//			case BlackMa:
		//				return false;
		//				break;
		//			case BlackXiang:
		//				return false;
		//				break;
		//			case BlackShi:
		//				return false;
		//				break;
		//			case BlackKing:
		//				*to = char(from/9*9 + tt);
		//				break;
		//			default:
		//				break;

		//		}
		//		break;
		//	case '+':			//��				
		//		switch(fromchess){
		//			case WhitePawn:
		//				tt = 9 - tt;      //��ԭһ��
		//				*to = from - tt*9;
		//				break;
		//			case WhitePao:
		//				tt = 9 - tt;      //��ԭһ��
		//				*to = from - tt*9;
		//				break;
		//			case WhiteChe:
		//				tt = 9 - tt;      //��ԭһ��
		//				*to = from - tt*9;
		//				break;
		//			case WhiteMa:
		//				switch(tt-ff){
		//					case 1:
		//						*to = from -17;
		//						break;
		//					case -1:
		//						*to = from -19;
		//						break;
		//					case 2:
		//						*to = from -7;
		//						break;
		//					case -2:
		//						*to = from -11;
		//						break;
		//					default:
		//						return false;
		//						break;
		//				}
		//				break;
		//			case WhiteXiang:		//����
		//				switch(tt-ff){
		//					case 2:
		//						*to = from -16;
		//						break;
		//					case -2:
		//						*to = from -20;
		//						break;
		//					default:
		//						return false;
		//						break;
		//				}
		//				break;
		//			case WhiteShi:
		//				switch(tt-ff){
		//					case 1:
		//						*to = from -8;
		//						break;
		//					case -1:
		//						*to = from -10;
		//						break;
		//					default:
		//						return false;
		//						break;
		//				}						
		//				break;
		//			case WhiteKing:
		//				tt = 9 - tt;       //��ԭһ��
		//				*to = from - tt*9;
		//				break;
		//			//*********************************************
		//			case BlackPawn:
		//				//tt = 9 - tt;       //��ԭһ��
		//				tt = 1 + tt;      //��ԭһ��
		//				*to = from + tt*9;
		//				break;
		//			case BlackPao:
		//				tt = 1 + tt;      //��ԭһ��
		//				*to = from + tt*9;
		//				break;
		//			case BlackChe:
		//				tt = 1 + tt;      //��ԭһ��
		//				*to = from + tt*9;
		//				break;
		//			case BlackMa:				//�������						
		//				switch(tt-ff){
		//					case 1:
		//						*to = from +19;
		//						break;
		//					case -1:
		//						*to = from +17;
		//						break;
		//					case 2:
		//						*to = from +11;
		//						break;
		//					case -2:
		//						*to = from +7;
		//						break;
		//					default:
		//						return false;
		//						break;
		//				}
		//				break;
		//			case BlackXiang:
		//				switch(tt-ff){
		//					case 2:
		//						*to = from +20;
		//						break;
		//					case -2:
		//						*to = from +16;
		//						break;
		//					default:
		//						return false;
		//						break;
		//				}
		//				break;						
		//			case BlackShi:
		//				switch(tt-ff){
		//					case 1:
		//						*to = from +10;
		//						break;
		//					case -1:
		//						*to = from +8;
		//						break;
		//					default:
		//						return false;
		//						break;
		//				}						
		//				break;
		//			case BlackKing:
		//				tt = 1 + tt;      //��ԭһ��
		//				*to = from + tt*9;
		//				break;
		//			default:
		//				return false;
		//				break;
		//		}
		//		break;
		//	case '-':			//��					
		//		switch(fromchess){
		//			case WhitePawn:
		//				tt = 9 - tt;      //��ԭһ��
		//				*to = from + tt*9;
		//				break;
		//			case WhitePao:
		//				tt = 9 - tt;      //��ԭһ��
		//				*to = from + tt*9;
		//				break;
		//			case WhiteChe:
		//				tt = 9 - tt;      //��ԭһ��
		//				*to = from + tt*9;
		//				break;
		//			case WhiteMa:
		//				switch(tt-ff){
		//					case 1:
		//						*to = from +19;
		//						break;
		//					case -1:
		//						*to = from +17;
		//						break;
		//					case 2:
		//						*to = from +11;
		//						break;
		//					case -2:
		//						*to = from +7;
		//						break;
		//					default:
		//						return false;
		//						break;
		//				}
		//				break;
		//			case WhiteXiang:			//����
		//				switch(tt-ff){
		//					case 2:
		//						*to = from +20;
		//						break;
		//					case -2:
		//						*to = from +16;
		//						break;
		//					default:
		//						return false;
		//						break;
		//				}
		//				break;
		//			case WhiteShi:
		//				switch(tt-ff){
		//					case 1:
		//						*to = from +10;
		//						break;
		//					case -1:
		//						*to = from +8;
		//						break;
		//					default:
		//						return false;
		//						break;
		//				}						
		//				break;
		//			case WhiteKing:
		//				tt = 9 - tt;      //��ԭһ��
		//				*to = from + tt*9;
		//				break;
		//			//*********************************************
		//			case BlackPawn:
		//				tt = 1 + tt;      //��ԭһ��
		//				*to = from - tt*9;
		//				break;
		//			case BlackPao:
		//				tt = 1 + tt;      //��ԭһ��
		//				*to = from - tt*9;
		//				break;
		//			case BlackChe:
		//				tt = 1 + tt;      //��ԭһ��
		//				*to = from - tt*9;
		//				break;
		//			case BlackMa:				//��������						
		//				switch(tt-ff){
		//					case 1:
		//						*to = from -17;
		//						break;
		//					case -1:
		//						*to = from -19;
		//						break;
		//					case 2:
		//						*to = from -7;
		//						break;
		//					case -2:
		//						*to = from -11;
		//						break;
		//					default:
		//						return false;
		//						break;
		//				}
		//				break;
		//			case BlackXiang:
		//				switch(tt-ff){
		//					case 2:
		//						*to = from -16;
		//						break;
		//					case -2:
		//						*to = from -20;
		//						break;
		//					default:
		//						return false;
		//						break;
		//				}
		//				break;						
		//			case BlackShi:
		//				switch(tt-ff){
		//					case 1:
		//						*to = from -8;
		//						break;
		//					case -1:
		//						*to = from -10;
		//						break;
		//					default:
		//						return false;
		//						break;
		//				}						
		//				break;
		//			case BlackKing:
		//				tt = 1 + tt;      //��ԭһ��
		//				*to = from - tt*9;
		//				break;
		//			default:
		//				return false;
		//				break;
		//		}
		//		break;				
		//	default:
		//		return false;
		//		break;
		//}
		return true;	
}
bool 
GetMoveFromWXF(char *qipu, char *pm, position_t* pos, bool who){
	
//	sq_t fromchess;
//
//	sq_t from;
//	sq_t to;
//	char ch1 = *pm;
//	char ch2 = *(pm+1);
//	char ch3 = *(pm+2);
//	char ch4 = *(pm+3);
//
//	sq_t ff;
//	sq_t tt;
//
///*	if(who == WHITE_GO){
//		ff = 9 - (ch2 - '0');   
//		tt = 9 - (ch4 - '0');	
//	}
//	else{
//		ff = ch2 - '0';
//		tt = ch4 - '0';
//	}*/	
//	
//	switch(ch1){
//				case 'C':		//��
//					fromchess = WhitePao;						
//					break;
//				case 'H':		//��					
//					fromchess = WhiteMa;
//					break;
//				case 'R':		//��					
//					fromchess = WhiteChe;
//					break;
//				case 'P':		//��					
//					fromchess = WhitePawn;
//					break;
//				case 'A':		//ʿ					
//					fromchess = WhiteShi;
//					break;
//				case 'E':		//��					
//					fromchess = WhiteXiang;
//					break;
//				case 'K':		//��					
//					fromchess = WhiteKing;
//					break;
//					//************************************
//				case 'c':		//��
//					// from
//					//if(!GetIntFromWXFMove(b90,&from,ch2,BlackPao,who)){					
//					//	MessageBox(hwndMain,"WEB �岽�� FROM��WXF","WXF ERR!",MB_OK);
//					//	return false;
//					//}else{
//					//	// to
//					//	if(!GetIntFromWXFMoveWithMethod(b90,from,&to,ch4,BlackPao,who,ch3)){					
//					//		MessageBox(hwndMain,"WEB �岽�� TO��WXF","WXF ERR!",MB_OK);
//					//		return false;
//					//	}else{//�õ�����ȷ��from to
//					//		
//					//	}
//					//}
//					//return true;
//					fromchess = BlackPao;
//					break;
//				case 'h':		//��					
//					fromchess = BlackMa;
//					break;
//				case 'r':		//��					
//					fromchess = BlackChe;
//					break;
//				case 'p':		//��					
//					fromchess = BlackPawn;
//					break;
//				case 'a':		//ʿ					
//					fromchess = BlackShi;
//					break;
//				case 'e':		//��					
//					fromchess = BlackXiang;
//					break;
//				case 'k':		//��					
//					fromchess = BlackKing;
//					break;
//				default:
//					//MessageBox(hwndMain,"WEB �岽��WXF","WXF ERR!",MB_OK);
//					DispLog("WEB �岽��WXF");
//					return false;				
//	}
//
//    
//	//if(ch2 >= '0' && ch2 <= '9'){
//	//	if(who == WHITE_GO){		//�����Ǻ�����
//	//		ff = 9 - (ch2 - '0');   
//	//		tt = 9 - (ch4 - '0');	
//	//		
//	//	}
//	//	else{
//	//		ff = ch2 - '0' -1;
//	//		tt = ch4 - '0' -1;			
//	//	}
//
//	if(!GetIntFromWXFMove(b90,&from,&ff,&tt,fromchess,who,ch3,ch2,ch4)){					
//		//MessageBox(hwndMain,"WEB �岽�� FROM��WXF","WXF ERR!",MB_OK);
//		DispLog("WEB �岽��WXF");
//		return false;
//	}else{
//		// to
//		if(!GetIntFromWXFMoveWithMethod(b90,from,&to,ff,tt,fromchess,who,ch3)){					
//			//MessageBox(hwndMain,"WEB �岽�� TO��WXF","WXF ERR!",MB_OK);
//			DispLog("WEB �岽��WXF");
//			return false;
//		}else{//�õ�����ȷ��from to
//			
//		}
//	}
//	/*}else{
//		
//		return false;
//	}*/
//    
//	*qipu ++ = from;
//	*qipu ++ = to;
//
//	//��һ��
//	if(b90[from] != fromchess){
//		return false;
//	}
//	b90[from] = NOCHESS;
//	b90[to]   = fromchess;

	return true;
}
bool //http://www.clubxiangqi.com/viewer/wxfmoves.html?ID=746990
DownLoadOneFromclubxiangqicom(char* url, char* string, GameQJ *pgg, MYSQL* my){
//	DWORD bytes_read;     //���ص��ֽ���	
//	//��һ��internet����
//	/*SendMessage(hStatusBar,SB_SETTEXT,StaBarCom,(LPARAM)url);*/
//	//DispLog(url);
//	//��һ��http url��ַ
//    int Errno = 0;
//#define err_wxf_max 20
//RE_WEB_READ:
//	
//	
//	HINTERNET internet=InternetOpen("HTTP Downloader", INTERNET_OPEN_TYPE_PRECONFIG, 
//        NULL, NULL, NULL);
//	if(!internet){
//		//throw "InternetOpen error!";
//		DispLog("InternetOpen error!");
//		return false;
//	}
//    HINTERNET file_handle=InternetOpenUrl(internet, url, NULL, 0, INTERNET_FLAG_RELOAD, 0);
//    // INTERNET_FLAG_RELOAD, 0);   INTERNET_FLAG_HYPERLINK
//	if(!file_handle){ 		
//		//throw "InternetOpenUrl error! - Maybe you should add Http:// or Ftp://";		
//		DispLog("InternetOpenUrl error! - Maybe you should add Http:// or Ftp://");
//		return false;
//	}
//	 //��url��ַ�ж�ȡ�ļ����ݵ�������buffer
//    BOOL b = InternetReadFile(file_handle, string, MAX_DOWN, &bytes_read);
//	if(!b){
//        //throw "InternetReadFile error!";
//		DispLog("InternetReadFile error!");
//		return false;
//	} 
//
//	InternetCloseHandle(internet);			//�ر�InterNet
//
//
//	*(string+bytes_read) = 0;
//
//	if(!GetOneNodeFromWXF(string,"FORMAT",pgg->from,sizeof(pgg->from))){
//		DispLog(url);
//		DispLog("NO FORMAT tag!!");
//		Errno ++;
//		if(Errno < err_wxf_max){
//			goto RE_WEB_READ;
//		}
//		else{
//			return false;
//		}
//	}
//	
//	
//	if(!GetOneNodeFromWXFelo(string,"RED",pgg->Rname, sizeof(pgg->Rname),false)){
//		DispLog(url);
//		DispLog("NO RED tag!!");
//		Errno ++;
//		if(Errno < err_wxf_max){
//			goto RE_WEB_READ;
//		}
//		else{
//			return false;
//		}
//	}
//	if(!GetOneNodeFromWXFelo(string,"BLACK",pgg->Bname, sizeof(pgg->Bname),false)){
//		DispLog(url);
//		DispLog("NO BLACK!! tag");
//		Errno ++;
//		if(Errno < err_wxf_max){
//			goto RE_WEB_READ;
//		}
//		else{
//			return false;
//		}
//	}
//
//	char elo[8];
//	if(!GetOneNodeFromWXFelo(string,"RED",elo, sizeof(elo),true)){
//		DispLog(url);
//		DispLog("NO RED Elo tag!!");
//		Errno ++;
//		if(Errno < err_wxf_max){
//			goto RE_WEB_READ;
//		}
//		else{
//			return false;
//		}
//	}
//    pgg->Relo = atoi(elo);
//   
//	//***************************************************************
//	if(pgg->Relo < 2000){
//		return true;
//	}
//  
//
//	if(!GetOneNodeFromWXFelo(string,"BLACK",elo, sizeof(elo),true)){
//		DispLog(url);
//		DispLog("NO BLACK Elo tag!!");
//		Errno ++;
//		if(Errno < err_wxf_max){
//			goto RE_WEB_READ;
//		}
//		else{
//			return false;
//		}
//	}
//    pgg->Belo = atoi(elo);
//
//	//***************************************************************
//	if(pgg->Belo < 2000){
//		return true;
//	}
//
//    pgg->qjid		= 0;
//	pgg->qipulen	= 0;
//	pgg->isChecked  = 0;
//	pgg->isLearned  = 0;
//	pgg->score      = SCORE_NO;
//
//	char result[64];
//	if(!GetOneNodeFromWXF(string,"DATE",result,sizeof(result))){
//		DispLog(url);
//		DispLog("NO DATE tag!!");
//		Errno ++;
//		if(Errno < err_wxf_max){
//			goto RE_WEB_READ;
//		}
//		else{
//			return false;
//		}
//	}
//	StringCbPrintf(pgg->note,sizeof(pgg->note),"DATE: %s, RESULT: ", result);
//	
//	
//	if(!GetOneNodeFromWXF(string,"RESULT",result,sizeof(result))){
//		DispLog(url);
//		DispLog("NO RESULT tag!!");
//		Errno ++;
//		if(Errno < err_wxf_max){
//			goto RE_WEB_READ;
//		}
//		else{
//			return false;
//		}
//	}
//	StringCbPrintf(pgg->resultDetails,4,result);
//	StringCbCat(pgg->note, sizeof(pgg->note), result);
//
//	if(!GetOneNodeFromWXF(string,"EVENT",result,sizeof(result))){
//		DispLog(url);
//		DispLog("NO EVENT tag!!");
//		Errno ++;
//		if(Errno < err_wxf_max){
//			goto RE_WEB_READ;
//		}
//		else{
//			return false;
//		}
//	}	
//	StringCbCat(pgg->note, sizeof(pgg->note), result);
//	
//
//
//	
//	//Ӧ�ö���ȫ����
//	pgg->qipulen = 32;          //���׵ĳ�ʼ����
//
//	Board90 b90;
//	memcpy(b90,initialPosition,sizeof(Board90));
//
//	B90ToD8((sq_t*)initialPosition,(int*)pgg->qipu,true);
//	char *ps = pgg->qipu + 32;  //�岽ָ��
//	
//	char *pchAnsi = strstr(string,"START{");
//	if(pchAnsi == NULL){
//		DispLog(url);
//		DispLog("NO START{ tag!!");
//		Errno ++;
//		if(Errno < err_wxf_max){
//			goto RE_WEB_READ;
//		}
//		else{
//			return false;
//		}
//	}
//	char *pchEnd = strstr(pchAnsi,"}END");
//	if(pchEnd == NULL){
//		DispLog(url);
//		DispLog("NO END tag!!");
//		Errno ++;
//		if(Errno < err_wxf_max){
//			Sleep(300);
//			goto RE_WEB_READ;
//		}
//		else{
//			return false;
//		}
//	}
//	pchAnsi += 7;  
//	//pchAnsi += 4;    //ָ����һ���岽�Ŀ�ͷ
//	//int qnum = 0;    // �岽����
//	pchEnd -= 7;
//	while(pchAnsi < pchEnd){
//		if(*pchAnsi == 0x0a){
//			pchAnsi += 1;
//		}
//		if(pgg->qipulen < 428){
//			pchAnsi += 4;    //ָ����һ���岽�Ŀ�ͷ
//		}else{
//			pchAnsi += 5;    //ָ����һ���岽�Ŀ�ͷ
//		}
//		
//		
//		if(GetMoveFromWXF(ps,pchAnsi,b90, WHITE_GO)){   //����
//			pgg->qipulen += 2;
//			ps           += 2;
//			pchAnsi      += 7;
//		}
//		else{
//			break;
//		}
//		if(*pchAnsi == '}'){
//			break;
//		}
//		if(GetMoveFromWXF(ps,pchAnsi,b90,BLACK_GO)){	//����
//			pgg->qipulen += 2;
//			ps           += 2;
//			pchAnsi      += 7;
//		}
//		else{
//			break;
//		}		
//	}
//	pgg->qipu[pgg->qipulen] = 0;
//
//	if(!MysqlSaveGGqj(pgg,my,true)){
//		//DispLog(url);
//		//DispLog("����д����ܱ����ۣ�");
//	}
//ELO_TOO_SMALL:      //elo̫С����������
	return true;
}
DWORD WINAPI 
WebToMysqlThread(LPVOID lpParam){
	char string[MAX_DOWN];    
	GameQJ  mygg;
	char   url[MSG_SIZ];
	char   buf[MSG_SIZ];
	MYSQL  mysql_web;                 //�������ݿ�����
	/*MYSQL* pcon_im;*/
	//pcon_im = mysql_init(&mycon_im);
	if(mysql_init(&mysql_web) == NULL){
		//DispLog("���ܳ�ʼ��MYSQL����,<WebToMysqlThread>");
		goto Out_Web;
	}	
	if(NULL == mysql_real_connect(&mysql_web,appData.sql_host,
		appData.sql_user,appData.sql_pass,appData.sql_db_chess,
		appData.sql_port,NULL,0))	{
			//DispLog("WebToMysqlThread,���ܽ���MYSQL����");
			goto Out_Web;
	}	
	mysql_set_character_set(&mysql_web, MYSQLCHAESET);		
	char clubxiangqi[] = "http://www.clubxiangqi.com/viewer/wxfmoves.html?ID=";
	//int  startid = wxf_start_id;    //15506010  //746990;
	//int  endid   = wxf_end_id;
	int  idadd   = *((int*)lpParam);
	int  dnum    = 0; 
	int  dnot    = 0;	
	int i;
	for(i=DIS.wxf_start_id; i<DIS.wxf_end_id; i += WNUM){
		StringCbPrintf(url,MSG_SIZ,"%s%d",clubxiangqi,i+idadd);
		if(DownLoadOneFromclubxiangqicom(url,string,&mygg, &mysql_web)){
			if(i>appData.wxf_alread_read){
				appData.wxf_alread_read = i;
			}
			dnum ++;	//�ɹ�����
		}
		else{
			dnot ++;    //ʧ�ܴ���	
			//DispLog(url);
			//DispLog("ʧ�ܣ�***********************************************��");
			if(dnot > 100){
				//DispLog("ʧ����������100���߳�ֹͣ����**************************");
				goto Out_Web;
			}
		}
		StringCbPrintf(buf,MSG_SIZ,"%d OK, %d Err, %s", dnum, dnot,url);
		SendMessage(hStatusBar,SB_SETTEXT,0,(LPARAM)buf);
		if(!SendMessage(hwndToolBar,TB_ISBUTTONCHECKED,IDT_IMPORT,0)){
				goto Out_Web;        //�ְ����˵��밴ť
		}
	}
Out_Web:
	StringCbPrintf(buf,MSG_SIZ,"��WEB�ϳɹ������� %d �����!", dnum);	
	//DispLog(buf);
	StringCbPrintf(buf,MSG_SIZ,"��WEB��ʧ���� %d �����!", dnot);	
	//DispLog(buf);
	mysql_close(&mysql_web);                //�ǵùر�mysql������	
    DIS.wxf_im_thread_num --;    
	if(DIS.wxf_im_thread_num == 0){
		SendMessage(hwndToolBar,TB_CHECKBUTTON,IDT_IMPORT,false);//�����밴ť������	
	}
	return 0;
}
void 
Web_To_Mysql_Event(void){
	char buf[MSG_SIZ];
	DWORD dwTid[WNUM];
	DWORD dwTpa[WNUM];	
	DIS.wxf_start_id = appData.wxf_alread_read;
	DIS.wxf_end_id   = DIS.wxf_start_id + appData.wxf_per_read;
	
	DIS.wxf_im_thread_num = WNUM;
	for(int i=0; i<WNUM; i++){
		dwTpa[i]		=i;
		//dwTid[WNUM]		=i;
		//���������߳�
		HANDLE hwebTH = CreateThread(
			NULL,
			NULL,
			WebToMysqlThread,
			&dwTpa[i],
			0,
			&dwTid[i]);
		if(hwebTH == NULL){
			StringCbPrintf(buf,MSG_SIZ,"��ʼWEB�����߳� %d ʧ�ܣ�",i);
		}
		else{
			StringCbPrintf(buf,MSG_SIZ,"��ʼWEB�����߳� %d �ɹ���",i);
			SetThreadPriority(hwebTH,THREAD_PRIORITY_BELOW_NORMAL);
		}		
		//DispLog(buf);
		Sleep(1000);
	}
	

	////���������߳�
	//DWORD dwThreadId, dwThrdParam = 1;
	//HANDLE hImportTH = CreateThread(//���������߳�
	//	NULL,
	//	NULL,
	//	WebToMysqlThread,
	//	&dwThrdParam,
	//	0,
	//	&dwThreadId);
	//if(hImportTH == NULL){
	//	DispLog("��ʼWebToMysql�߳�ʧ�ܣ�");
	//}else{
	//	DispLog("��ʼ��WebToMysql�̳߳ɹ���");
	//	SetThreadPriority(hImportTH,THREAD_PRIORITY_BELOW_NORMAL);
	//	//��������������ȼ�����һ��		
	//}
}
DWORD WINAPI 
LearnChecked_QJ_MysqlThread(LPVOID lpParam){
	char buf[MSG_SIZ];
	MYSQL  mysql_learn;                 //�������ݿ�����
	/*MYSQL* pcon_im;*/
	//pcon_im = mysql_init(&mycon_im);
	if(mysql_init(&mysql_learn) == NULL){
		//DispLog("���ܳ�ʼ��MYSQL����,<LearnChecked_QJ_MysqlThread>");
		goto Out_Learn;
	}	
	if(NULL == mysql_real_connect(&mysql_learn,appData.sql_host,
		appData.sql_user,appData.sql_pass,appData.sql_db_chess,
		appData.sql_port,NULL,0))	{
			//DispLog("WebToMysqlThread,���ܽ���MYSQL����");
			goto Out_Learn;
	}	
	mysql_set_character_set(&mysql_learn, MYSQLCHAESET);	
	
	int learned = 0;
	GameQJ gg;
	while(true){
		if(MysqlGetOneCheckedAndLearn(&gg,&mysql_learn)== false){
			break;
		}
		learned ++;
		StringCbPrintf(buf,MSG_SIZ,"����ѧϰ %d .....",gg.qjid);
		SendMessage(hStatusBar,SB_SETTEXT,0,(LPARAM)buf);
		if(!SendMessage(hwndToolBar,TB_ISBUTTONCHECKED,IDT_LEARN_QK,0)){
				goto Out_Learn;        //�ְ����˵��밴ť
		}
	}
	//MysqlGetOneCheckedAndLearn(GameQJ *pgg, MYSQL *my)
Out_Learn:
	StringCbPrintf(buf,MSG_SIZ,"��ǰ�ɹ�ѧϰ�� %d �����........",learned);
	SendMessage(hStatusBar,SB_SETTEXT,0,(LPARAM)buf);
	//DispLog(buf);
	mysql_close(&mysql_learn);	
	SendMessage(hwndToolBar,TB_CHECKBUTTON,IDT_LEARN_QK,false);//��ѧϰ��ť��������
	return 0;
}

void 
LearnChecked_QJ_To_Mysql_Event(void){

	

	DWORD dwThreadId, dwThrdParam = 1;
	//����ѧϰ�߳�
	HANDLE hlearnTH = CreateThread(
		NULL,
		NULL,
		LearnChecked_QJ_MysqlThread,
		&dwThrdParam,
		0,
		&dwThreadId);
	if(hlearnTH == NULL){
		//StringCbPrintf(buf,MSG_SIZ,"��ʼWEB�����߳� %d ʧ�ܣ�",i);
		//DispLog("��ʼ���ѧϰ�߳�ʧ�ܣ�");
	}
	else{
		//StringCbPrintf(buf,MSG_SIZ,"��ʼWEB�����߳� %d �ɹ���",i);
		//DispLog("��ʼ���ѧϰ�̳߳ɹ���...........��");
		SetThreadPriority(hlearnTH,THREAD_PRIORITY_BELOW_NORMAL);
	}	

}
#endif