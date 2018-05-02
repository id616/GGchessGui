#ifndef CHESS_STRUCT_H
#define CHESS_STRUCT_H

typedef VOIDSTAR ProcRef;
typedef VOIDSTAR InputSourceRef;



#define MAX_GAME_LENGTH 600

/* Type definition: Node of a double linked list.
*/
typedef struct _ListNode {
    struct _ListNode *succ;
    struct _ListNode *pred;
} ListNode;

typedef struct {
    struct _ListNode *head;     /*  The list structure consists of two  */
    struct _ListNode *tail;     /*  ListNode's: The pred entry of the   */
    struct _ListNode *tailPred; /*  head being the succ entry of the    */
} List;


typedef  unsigned __int8  sc_t;
typedef  unsigned __int16 num_t;
typedef struct {
    int				pid;          //��ֱ��
    TCHAR			pevent[64];   //���λ��
	TCHAR            date[32];     //�������ڣ���ʽͳһΪ��yyyy.mm.dd���� 
	TCHAR            round[16];    //�����ִΣ� 
	TCHAR            Red[64];      //�췽����
	TCHAR            Black[64];    //�ڷ�����
	TCHAR            result[32];   //�������
    int             Relo;
    int             Belo;
	TCHAR            RtimeControl[32];
	TCHAR            BtimeControl[32];
    TCHAR            start_fen[128];
    TCHAR            fen_store[2400];
	TCHAR            strStepScore[MAX_GAME_LENGTH * 6];  // ÿ�����岽�÷֣�����������ʾ
	TCHAR            note[128];      //��ע
    
    int             isFenGame;   //�ǿ��ֻ��ǲо�
    int             isChecked;     //�Ƿ������÷�
    int             isLearned;     //�Ƿ�ѧϰ��
    int             isFinish;      //�Ƿ�����˼ƻ�
    int             PlanID;        //�ƻ�ID
    int             score;         //���÷�
	int             rate;          //����
	TCHAR           opera[32];     //����Ա
	int             yqScore;       //����÷� 90000û�з�
	
	int             IcsStepTime;   //��ʱ�õģ�ICS��ʱ	

	int             IcsReadTime;   //ICS ����


} PGN;

typedef struct {
	BOOL isLearn;
	BOOL outLearn;
	BOOL isImPort;
	BOOL isFillQk;       //������䣬����ͣѧϰ

	BOOL isVerfyFace;    //����У�����
    BOOL outVerfyFace;   //

} ThStat_t;


//struct timezone {
//    int tz_minuteswest;
//    int tz_dsttime;
//};

/* A point in time */
//typedef struct {
//    long sec;  /* Assuming this is >= 32 bits */
//    int ms;    /* Assuming this is >= 16 bits */
//} TimeMark;

/* Search stats from chessprogram */
//typedef struct {
//    char movelist[2*MSG_SIZ]; /* Last PV we were sent */
//    int depth;                /* Current search depth */
//    int nr_moves;             /* Total nr of root moves */
//    int moves_left;           /* Moves remaining to be searched */
//    char move_name[MOVE_LEN]; /* Current move being searched, if provided */
//    unsigned long nodes;      /* # of nodes searched */
//    int time;                 /* Search time (centiseconds) */
//    int score;                /* Score (centipawns) */
//    int got_only_move;        /* If last msg was "(only move)" */
//    int got_fail;             /* 0 - nothing, 1 - got "--", 2 - got "++" */
//    int ok_to_send;           /* handshaking between send & recv */
//    int line_is_book;         /* 1 if movelist is book moves */
//    int seen_stat;            /* 1 if we've seen the stat01: line */
//} ChessProgramStats;

typedef int CPKind;

typedef struct {
    CPKind kind;
    HANDLE hProcess;
    DWORD pid;
    HANDLE hTo;
    HANDLE hFrom;
    SOCKET sock;
    SOCKET sock2;  /* stderr socket for OpenRcmd */
} ChildProc;

//����Ϊ����
//typedef void (*DelayedEventCallback) (disboard_t* pDis);
typedef void (*InputCallback) (InputSourceRef isr, VOIDSTAR closure, char *buf, int count, int error);

typedef struct {
    char *name;
    int squareSize;
    int lineGap;
    int clockFontPxlSize;
    int coordFontPxlSize;
    int fontPxlSize;
    int smallLayout;
    int tinyLayout;
    int minScreenSize;
} SizeDefaults;

/* Types */
typedef struct {
    TCHAR faceName[LF_FACESIZE];
    float pointSize;
    BYTE bold, italic, underline, strikeout;
} MyFontParams;

typedef struct {
    TCHAR *def;
    MyFontParams mfp;
    LOGFONT lf;
    HFONT hf;
} MyFont;

typedef struct {
    COLORREF color;
    int effects;
    TCHAR *name;
} MyColorizeAttribs;

typedef struct {
    char* name;
    void* data;
} MySound;

typedef struct {
    COLORREF color;
    int effects;
    MySound sound;
} MyTextAttribs;

typedef char GetFunc(void *getClosure);

typedef struct {
    int   piece;  
    POINT pos;      /* window coordinates of current pos */
    POINT lastpos;  /* window coordinates of last pos - used for clipping */
    POINT from;     /* board coordinates of the piece's orig pos */
    POINT to;       /* board coordinates of the piece's new pos */
} AnimInfo;

typedef struct {
    POINT start;    /* window coordinates of start pos */
    POINT pos;      /* window coordinates of current pos */
    POINT lastpos;  /* window coordinates of last pos - used for clipping */
    POINT from;     /* board coordinates of the piece's orig pos */
} DragInfo;

typedef struct {
    POINT sq[2];	  /* board coordinates of from, to squares */
} HighlightInfo;

//typedef struct {
//    char *label;
//    int id;
//    HWND hwnd;
//    WNDPROC wndproc;
//} MyButtonDesc;

typedef struct _InputSource {
    CPKind kind;
    HANDLE hFile;
    SOCKET sock;
    int lineByLine;
    HANDLE hThread;
    DWORD id;
    char buf[INPUT_SOURCE_BUF_SIZE];
    char *next;
    DWORD count;
    int error;
    InputCallback func;
    struct _InputSource *second;  /* for stderr thread on CPRcmd */
    VOIDSTAR closure;
} InputSource;

typedef struct {
    HWND hDlg, hText;
    int sizeX, sizeY, newSizeX, newSizeY;
    HDWP hdwp;
} ResizeEditPlusButtonsClosure;

typedef struct {
    char *item;
    char *command;
    BOOLEAN getname;
    BOOLEAN immediate;
} IcsTextMenuEntry;

typedef struct {
    TCHAR *argName;
    ArgType argType;
    /***
    union {
    String *pString;       // ArgString
    int *pInt;             // ArgInt
    float *pFloat;         // ArgFloat
    Boolean *pBoolean;     // ArgBoolean
    COLORREF *pColor;      // ArgColor
    ColorClass cc;         // ArgAttribs
    String *pFilename;     // ArgFilename
    BoardSize *pBoardSize; // ArgBoardSize
    int whichFont;         // ArgFont
    DCB *pDCB;             // ArgCommSettings
    String *pFilename;     // ArgSettingsFilename
    } argLoc;
    ***/
    LPVOID argLoc;
    BOOL save;
} ArgDescriptor;

typedef struct {
    char piece;
    int command;
    char* name;
} DropEnable;


typedef struct {
    char *label;
    unsigned value;
} ComboData;

typedef struct {
    char *label;
    char *name;
} SoundComboData;

typedef struct {
    int item;
    int flags;
} Enables;


//#define DLOG         0
//#define DSTEP        1
//#define DDATA        2
//#define DCON         3
//#define	DYQ          4
//#define TIE_NUM      5

struct list_t {
    uint8 p, n;
};



struct Record
{   
    uint8  nonCap;
    uint8  ischeck;
	//sint16 book_score;
	sint16 search_score;      // �������岽�÷�

    uint32 move;
    uint64 key;
	
};

struct move_stack_t {
    int move;
    int score;
};

struct book_face_info_t {
	sint8 result;         // 2,1,0,-1,-2;
	uint8 dummy1;         // �岽����󣲣���       
	uint8 dummy2;         // ���أ�������������
	uint8 isuse;         // �ǲ�������ʹ�ñ��岽
};

struct book_face_t {
	uint8  f33[33];
	book_face_info_t info[1];
};




typedef struct stock_dbs_t {
	
	DB_ENV *Env;

	DB *book;			//���ǵ�ǰʹ�õĵ�book;
	DB *back_db;           //�����ϵͳȱʡ��book;

	char *book_db_name;
	char *good_db_name;

	BOOL Book_Init_Ok;

} STOCK_DBS;




//#define MAX_EAT_REPEAT       17              //���׽�����

struct position_t {

    uint8     b256[256];
    list_t    piece_list[256];          //
    uint16    wBitRanks[16];
    uint16    wBitFiles[16];
    int       gply;
    int       curStep;                  //��ǰ����
    int       side;
    Record    His[MAX_GAME_LENGTH];	

	move_stack_t* pMend;
    move_stack_t  all_move[128];

#ifdef   USE_EAT_DIFF_CHESS            //��׽��ͬ���ӣ����㳣׽
	int      eatChess[256];            //�Է���׽�Ե�����
	int      eatNum;                   //��׽�Ĳ���
#endif
	
#define MAX_REAL_CAP_NUM 4
	int    LastCapChess[MAX_REAL_CAP_NUM][2][2];                   //���һ�γԵ�����
	int    last_to[MAX_REAL_CAP_NUM][2][2];                        //���һ�ζԷ�to
    int    last_ot_from[MAX_REAL_CAP_NUM][2][2];                   //��������32����׽	
	int    cap_num[2][2];
	bool   isTrueCap;
	book_face_t book_face[1];
};

typedef struct _CPS {
	CPS_STAT cps_stat;
	void* pDis;                    //ָ���Լ�������
	struct _CPS * loadWhich;        //������һ�����棬��first,����second
	struct _CPS * loadPre;          //
	HWND          loadWin;			//��������Ĵ���
	position_t          pos[1];			//������ʾ�岽��
	int  playWhat;					//cps�ߺ���
    int  rep_eat_or_check;			 //������������׽
    ProcRef pr;
    InputSourceRef isr;

    int sendDrawOffers;
    int useSigint;
    int useSigterm;
    int offeredDraw; /* countdown */
    int reuse;
    int useSetboard; /* 0=use "edit"; 1=use "setboard" */
    int useSAN;      /* 0=use coordinate notation; 1=use SAN */
    int usePing;     /* 0=not OK to use ping; 1=OK */
    int lastPing;
    int lastPong;
    int usePlayother;/* 0=not OK to use playother; 1=OK */
    int useColors;   /* 0=avoid obsolete white/black commands; 1=use them */
    int useUsermove; /* 0=just send move; 1=send "usermove move" */
    int sendICS;     /* 0=don't use "ics" command; 1=do */
    int sendName;    /* 0=don't use "name" command; 1=do */
    int sdKludge;    /* 0=use "sd DEPTH" command; 1=use "depth\nDEPTH" */
    int stKludge;    /* 0=use "st TIME" command; 1=use "level 1 TIME" */
    char tidy[MSG_SIZ];
    int  matchWins;
    char variants[MSG_SIZ];
    BOOL analysisSupport;

    int  ICS_id;
    //int  ICS_language;      //�������ģ����ǣ�����֮�ǣ�
    int  ICS_net_id;
	TCHAR ICS_user[64];
	TCHAR ICS_pass[64];
	TCHAR ICS_info[256];

	TCHAR ICS_net_name[128];
	TCHAR ICS_net_host[256];
    int  ICS_net_port;
	TCHAR ICS_net_type[128];
    TCHAR ICS_net_info[256];


	BOOL 	IsBaoGan;	        //�Ƿ���ɼ�ʱ
	int     BaoGanTime;			//���ɼ�ʱʱ��

    int		timePerStep;		//ÿ������ʱ��
    int		timeSearchDepth;	//����������    
    
	int     time_1_Step;		//��һ�׶�ʱ����Ҫ�߶��ٲ�
	int     time_1_Time;

	int     time_2_Step;
	int     time_2_Time;

	int     timePerStepAdd;
	int     timeIsLost;         //��ʱ�жϸ�    

    //int     isPonderThink;      //�Ƿ��̨˼��
    int     useBook;			//�Ƿ�ʹ�����
    int     isEGB;              //�воֿ�
    int     isAutoLearn;        //�Ƿ��Զ�ѧϰ

	char     szHost[256];

    int       yqID;             //������
    int		  ucci;				//�����UCCIЭ��

	int       PonderMoveInt;        //��̨�߲�
	TCHAR     PonderMove[16];	    //��̨˼���岽����
	BOOL      PonderStop;           //��̨��ֹͣ��������
	TCHAR     PonderName[16];       //��̨�����岽����

	TCHAR     UCCI_name[64];
	TCHAR     UCCI_file[64];		//�����ļ���
	TCHAR     UCCI_path[MAX_PATH];	//���������������������Ŀ¼

	TCHAR     UCCI_copyright[128];
	TCHAR     UCCI_author[128];
	TCHAR     UCCI_user[64];
	TCHAR     UCCI_verson[16];
    

    bool      UCCI_batch;
    bool      UCCI_debug;
    bool      UCCI_usemillisec;

	BOOL      UCCI_haveselfBook;		//���Լ��Ŀ��ֿ�

	TCHAR      UCCI_iniString[256];
	TCHAR      UCCI_otherString[256];
	TCHAR      UCCI_addInfo[256];
    int       UCCI_smpNum;
	int       UCCI_Book_Num;        //ʹ�õ�����岽

    int       UCCI_hashsize;
    int       UCCI_threads;
    int       UCCI_drawmoves;
    int       UCCI_repetition;
	//TCHAR      UCCI_pruning[32];    //�ü��̶�
	//TCHAR      UCCI_knowledge[32];  //֪ʶ��С
	//TCHAR      UCCI_selectivity[32];//ѡ����(�����)ϵ��
    int       UCCI_style;
    int       UCCI_loadbook;
    int       UCCI_clearhash;
    int       UCCI_dualtime;
    //-------------------------------�������ñ�������
} ChessProgramState;

struct TimeDisp_t {
    int RemainTime;			//��ǰ���õ�ʱ��
	int movetime;           //��ʱ   
	//int movestogo;          //Ҫ�߶��ٲ�


	BOOL isBaoGan;
    //int  BaoGanTime;         //���ǰ��ɾ��Ƿֶ�
    int inc;
    int c1time;
    int c1step;
    int c2time;
    int c2step;

    int SetStepTime;
    int SetDepth;

};

//#define STARTED_NONE            0
//#define STARTED_MOVES           1
//#define STARTED_BOARD           2
//#define STARTED_OBSERVE         3
//#define STARTED_HOLDINGS        4
//#define STARTED_CHATTER         5
//#define STARTED_COMMENT         6
//#define STARTED_MOVES_NOHIDE    7
//#define STARTED_PLAYER_LIST     8
//#define STARTED_TABLE_LIST      9
//#define STARTED_ROOM_DIR       10

//BUF_SIZE

#define ICS_BUF_SIZE   8192

struct ICS_t {

    //int  lastnotfinish;
	char   cbuf[ICS_BUF_SIZE];
	TCHAR  tbuf[ICS_BUF_SIZE];                 // ת����TCHAR��Ļ���
    int  buf_len;
    int  tkind;
    ICS_STARTED  started;
    int  count; 
    //int  started;
    //int  i;
    //int  oldi;
    //int  tkind;
    //int  next_out;
    //int  leftover_len;
    //int  leftover_start;  
    TCHAR star_match[STAR_MATCH_N][MSG_SIZ];
    int  saveingComment;
    int  stage;      //��ǰ�Ĺ�λ
    int  table;      //��ս�����,��ǰ������
    int  loggedOn;
	TCHAR ICS_183[8];  //183�Ŀ�ʼ���ܴ�����

	bool cont_dalei;
	bool only_this_table;   

	TCHAR log_name[32]; //���ǵ�¼�ߵ�ICS����

	int last_table;   //��һ��������


	//char ICS_TimeMode[32];   //��ʱ��ʽ
	//char ICS_Score[32];
	//int  ICS_StepTime;       //ICS �Ĳ�ʱ

	//int  nowTable;    //ICS ��ǰ��������Ϣ       

	char *p;
    ColorClass curColor;
    ColorClass prevColor;
};



typedef void (*DelayedEventCallback) (void* pDis);
typedef struct {

	int                table;         //����
    HWND hwndThis; 
	//HWND hwndSaveDlg; 
	//BOOL                IsFenGame;          //�ǲ�������Ĳо�
    int					whiteFlag;
    int					blackFlag;
    int					userOfferedDraw;
    HICON				iconCurrent;
    TimeDisp_t          TimeDisp[2];  //���������
    PGN  			    pgn[1];  
    position_t          pos[1];
    int					flipView;                       //�ı���������ʾ
    int					leftView;                       //�ı���������ʾ
    int					premoveToX ;
    int					premoveToY ;
    int					premoveFromX ;
    int					premoveFromY ;
    int					premovePromoChar ;
    int					gotPremove;	
    int					fromX;
    int					fromY;
    int					toX;
    int					toY;
    uint8     B256dis[MAX_GAME_LENGTH][256];        //ÿ����ʷ����
    TCHAR     parseList[MAX_GAME_LENGTH][16];       //ÿ����UCCI����,���Ҳ��������? 
    TCHAR     moveListName[MAX_GAME_LENGTH][16];
	//int       moveScore[MAX_GAME_LENGTH];           //ÿ���岽�ĵ÷�       
    AnimInfo			animInfo;
    DragInfo			dragInfo;
    HighlightInfo		highlightInfo;
    HighlightInfo		premoveHighlightInfo;
    GameMode			gameMode;					// = BeginningOfGame;	
    ChessProgramState	first;
    //ChessProgramState	second;                     // ȡ���ڶ�������
    //ChessProgramState	ics;

    ChessProgramState   set_cps;					//��ǰ�����趨��CPS

    int					matchMode;
    int					screenHeight;
    int					screenWidth;
    int					doingSizing;
    int					lastSizing;
    RECT				boardRect;
    int					boardX;
    int					boardY;
    int					startedFromSetupPosition;  
    int					winWidth;
    int					winHeight;
    TCHAR				messageText[MESSAGE_TEXT_MAX];
    int					pausing;

	BOOL                mustPonder;		//�����̨˼��

    //********************************************************
    uint8  lastReq[256];
    uint8  lastDrawn[256];

	

	HighlightInfo lastDrawnHighlight;
	HighlightInfo lastDrawnPremove;
	int lastDrawnFlipView;
	int lastReqValid;
	int lastDrawnValid;

    int					 clockTimerEvent;
    int					 loadGameTimerEvent;
    int					 analysisTimerEvent;
    DelayedEventCallback delayedTimerCallback;
    int					 delayedTimerEvent;

	int   			    programStartTime;     //����ʼ������ʱ��
	int                 tickStartTM;          //���濪ʼ��ticked
    long				intendedTickLength;
	BOOL                clockMode;				//�ǲ��Ǽ�ʱ��ʽ   
    int					firstMove;		// = TRUE;
    int					ics_user_moved;
    int					pauseExamForwardMostMove;

    Boolean				sameAgain;
    int					recursive;
	bool                useMS;          // �ǲ���ʹ��MS
	int					searchTime;     //
	int					tinyLayout;
    int					smallLayout;
    int					squareSize;
    int					lineGap;
	BoardSize    		bsize;
	char				DspinCmd[MSG_SIZ];    //ÿ�����������
    char				DspCmdbuf[4096];	  //�����������
	//char				*variant;

	int                 book_move[128];		  //����߲�
	int                 book_val[128];        //�岽�ļ�ֵ
	int                 book_num;
	//int                 book_max_num;         //��õ��岽


	HANDLE				pieceBitmap[16];    //���̵�14������,�����һ����14,���Ե�15
    HANDLE				chessQbBitmap;      //����λͼ
    HANDLE				chessMask;          //͸������λͼ
    HANDLE				chessInve;
    HANDLE				piecePutDownBitmap; //��������
    HANDLE				piecePickFromBitmap;

	HBRUSH				lightSquareBrush;
    HBRUSH				darkSquareBrush;
    HBRUSH				whitePieceBrush;
    HBRUSH				blackPieceBrush;
    HBRUSH				iconBkgndBrush;
    HBRUSH				outlineBrush;

    HPEN				gridPen;
    HPEN				highlightPen;
    HPEN				premovePen;
    NPLOGPALETTE		pLogPal;
    BOOL				paletteChanged;

	HPALETTE			hPal;

	
	
	int                 matchGames;
	//BOOL                noChessProgram;
	char               *initialMode;

	BOOL                IcsGameStartAlready;
	//BOOL                IsAnalyzeMode;             //�ǲ����ڷ���ģʽ��
	//BOOL                IsAnalyzeStart;             //���Ƿ����Լ���ʼ��

	//char                evalInfo[256*1024];
	//TCHAR                *EvalInfo;
	int                 imPortNum;                //������������
	bool                notLookBook;

}dispboard_t;




typedef struct {
    int whitePieceColor;
    int blackPieceColor;
    int lightSquareColor;
    int darkSquareColor;
    int jailSquareColor;
    int highlightSquareColor;
    int premoveHighlightColor;
    int movesPerSession;
    int timeIncrement;
    char *initString;
    char *secondInitString;

    //Boolean firstPlaysBlack;
    //Boolean noChessProgram;         //��û������������س���
    //char *firstHost;
    //char *secondHost;
    //char *bitmapDirectory;
    //char *remoteShell;
	TCHAR *remoteUser;
    float timeDelay;
    //char *timeControl;
    Boolean icsActive;
    //char *icsCommPort;  /* if set, use serial port instead of tcp host/port */
    //char *icsLogon;     /* Hack to permit variable logon scripts. */
    //char *icsHelper;
    Boolean icsInputBox;
    Boolean useTelnet;
    TCHAR *telnetProgram;
    //char *gateway;
    //char *loadGameFile;
    //int loadGameIndex;      /* game # within file */
    //char *saveGameFile;
    Boolean autoSaveGames;		//�Զ�������Ϸ
    //char *loadPositionFile;
    //int loadPositionIndex;  /* position # within file */
    //char *savePositionFile;
    //Boolean matchMode;
    //int matchGames;
    //Boolean monoMode;
    //Boolean debugMode;
    //Boolean clockMode;
    char *boardSize;
    //Boolean Iconic;
    ////char *searchTime;
    //int searchDepth;
    Boolean showCoords;
    char *clockFont;
    char *messageFont; /* WinBoard only */
    char *coordFont;
    char *font; /* xboard only: all other fonts */
    char *tagsFont; /* WinBoard only */
    char *commentFont; /* WinBoard only */
    char *icsFont; /* WinBoard only */
    Boolean ringBellAfterMoves;
    Boolean autoCallFlag;
    Boolean flipView;
    Boolean autoFlipView;
    char *cmailGameName; /* xboard only */
    //Boolean alwaysPromoteToQueen;
    //Boolean oldSaveStyle; //�ϵı�����ʽ
    Boolean quietPlay;
    Boolean showThinking;
    Boolean ponderNextMove;
    Boolean periodicUpdates;
    Boolean autoObserve;
    Boolean autoComment;
    Boolean getMoveList;
    Boolean testLegality;
    int borderXoffset; /* xboard only */
    int borderYoffset; /* xboard only */
    Boolean titleInWindow; /* xboard only */
    Boolean localLineEditing; /* WinBoard only */
    //Boolean zippyTalk;
    //Boolean zippyPlay;
    int flashCount; /* Number of times to flash (xboard only) */
    int flashRate; /* Flashes per second (xboard only)  */
    char *pixmapDirectory; /* Path to XPM/XIM files to use (xboard only) */
    int msLoginDelay;  /* Delay per character (in msec) while sending
                       ICS logon script (xboard only) */
    Boolean colorize;	/* If True, use the following colors to color text */
    /* Strings for colors, as "fg, bg, bold" (strings used in xboard only) */
    char *colorShout;
    char *colorSShout;
    char *colorChannel1;
    char *colorChannel;
    char *colorKibitz;
    char *colorTell;
    char *colorChallenge;
    char *colorRequest;
    char *colorSeek;
    char *colorNormal;
    char *soundProgram; /* sound-playing program */
    char *soundShout;
    char *soundSShout;
    char *soundChannel1;
    char *soundChannel;
    char *soundKibitz;
    char *soundTell;
    char *soundChallenge;
    char *soundRequest;
    char *soundSeek;
    char *soundMove;
    char *soundIcsWin;
    char *soundIcsLoss;
    char *soundIcsDraw;
    char *soundIcsUnfinished;
    char *soundIcsAlarm;
    //�����ļ���ȱʡĿ¼*************************************************
    int  winWidth;					//���洰�ڵ��ϴο�ȣ�
    int  pieceStyle;				//���ӷ��
    int  moveType;
    char *path_mxq;

	TCHAR *remoteShell;
	TCHAR *gateway;

    int  wxf_is_get;                    //�Ƿ��ȡWXF���
    char *wxf_url;                  //http://www.clubxiangqi.com/viewer/wxfmoves.html?ID
    int  wxf_alread_read;           //�Ѿ�ѧϰ��  http://www.clubxiangqi.com/viewer/wxfmoves.html?ID=15520488
    int  wxf_per_read;				//ÿ�ζ���������Ŀ
    Boolean reuseFirst;
    Boolean reuseSecond;
    Boolean animateDragging; /* If True, animate mouse dragging of pieces */
    Boolean animate;	/* If True, animate non-mouse moves */
    int animSpeed;	/* Delay in milliseconds between animation frames */
    Boolean popupMoveErrors;
    Boolean popupExitMessage;
    int showJail;
    Boolean highlightLastMove;
    Boolean highlightDragging;
    Boolean blindfold;          /* if true, no pieces are drawn */
    Boolean premove;		/* true if premove feature enabled */ 
    Boolean premoveWhite;	/* true if premoving White first move  */ 
    TCHAR *premoveWhiteText;	/* text of White premove 1 */ 
    Boolean premoveBlack;	/* true if premoving Black first move */ 
    TCHAR *premoveBlackText;	/* text of Black premove 1 */ 
    Boolean icsAlarm;		/* true if sounding alarm at a certain time */	
    int icsAlarmTime;		/* time to sound alarm, in milliseconds */
    Boolean autoRaiseBoard;
    int fontSizeTolerance; /* xboard only */
    /*char *initialMode;*/
    //char *variant;
    //int firstProtocolVersion;
    //int secondProtocolVersion;
    Boolean showButtonBar;
    //char		*icsNames;
    int boardX;
    int boardY;
    int first_yqID;
    int second_yqID;

	HICON				iconWhite;
    HICON				iconBlack;
	int					buttonCount;  //���İ�ť

	BoardSize           bsize;
	BOOL                alwaysOnTop;
	MyFont				*Afont[NUM_SIZES][NUM_FONTS];

	COLORREF			AlightSquareColor;
    COLORREF			AdarkSquareColor;
    COLORREF			AwhitePieceColor; 
    COLORREF			AblackPieceColor;
    COLORREF			AhighlightSquareColor;
    COLORREF			ApremoveHighlightColor;
   

	MyTextAttribs       AtextAttribs[(int)NColorClasses];
	//MySound				Asounds[(int)NSoundClasses];
	int					AsaveSettingsOnExit;
	int					AchessProgram;

	ProcRef				AicsPR;
	ChessProgramState   ACPSics;     //����������,һ����˵����վ����

#ifdef DEBUG_USE_DEBUG_FILE 
	FILE			    *debugFP;
#endif

	InputSourceRef		AtelnetISR;
	InputSourceRef		AfromUserISR;

	CHARFORMAT			AconsoleCF;
	int					prevStderrPort;
	NPLOGPALETTE		ApLogPal;


	int					Aexiting;  
	int					Afrozen;
	int					oldMenuItemState[MENU_BAR_ITEMS];
	Boolean				alarmSounded;

	TCHAR	Ahistory[HISTORY_SIZE][1024];
	int		AhistIn;
	int		AhistP;

	int     PlaySoundNum;
	int     keepInfo;   /* [HGM] to protect PGN tags in auto-step game analysis */

} AppData, *AppDataPtr;
typedef struct {
    TCHAR *title, *question, *replyPrefix;
    ProcRef pr;
} QuestionParams;

//#define TIE_NUM 5

#define DLOG         0
//#define DBOOK        1
#define DSAVE	     1
#define DCON	     2
#define	DYQ 	     3
#define TIE_NUM      4

typedef struct {

	HWND                tabMain;            //tab ��������
	HWND                tab;                //tab ����
	HWND				dlgTab[TIE_NUM];	//tab �ؼ��ĶԻ�
	int					tabChosen;	

    WNDPROC     consoleTextWindowProc;
    WNDPROC     consoleInputWindowProc;
	WNDPROC     consoleScoreChartWindowProc; 
    BOOLEAN     consoleEcho;
    
    InputSource *consoleInputSource;
    COLORREF	consoleBackgroundColor;

	HWND  hSaveDlg;         // ������ִ���
    HWND  hText;
	HWND  hTextMS;
	HWND  dlgStepList;      // ��ʷ�岽�б�
	HWND  dlgScore;         // ˫�����ƴ���
    HWND  hwndGoPlace;
    //
    HWND hwndICS_Board_List;    //����б���

} Tab_T;



#define TIME_MAIN        TAB.dlgTab[DLOG]                                     //��ʱ��������
#define STEP_MAIN        TAB.dlgTab[DLOG]                                     //�岽�б��������
#define NAME_MAIN        TAB.dlgTab[DLOG]                                     //���Ƶ�������
#define HWND_CONSOLE     TAB.dlgTab[DLOG]

#define HWND_SAVE        TAB.hSaveDlg                                         //����������




#define hwndTabID			33





#endif