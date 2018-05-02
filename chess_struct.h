#ifndef CHESS_STRUCT_H
#define CHESS_STRUCT_H

typedef VOIDSTAR ProcRef;
typedef VOIDSTAR InputSourceRef;





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
    char			pevent[64];   //���λ��
    char            date[32];     //�������ڣ���ʽͳһΪ��yyyy.mm.dd���� 
    char            round[16];    //�����ִΣ� 
    char            Red[24];      //�췽����
    char            Black[24];    //�ڷ�����
    char            result[32];   //�������
    int             Relo;
    int             Belo;
    char            RtimeControl[32];
    char            BtimeControl[32];
    char            start_fen[128];
    char            fen_store[2400];
    char            note[128];      //��ע
    
    int             isFenGame;   //�ǿ��ֻ��ǲо�
    int             isChecked;     //�Ƿ������÷�
    int             isLearned;     //�Ƿ�ѧϰ��
    int             isFinish;      //�Ƿ�����˼ƻ�
    int             PlanID;        //�ƻ�ID
    int             score;         //���÷�
	int             rate;          //����
	char            opera[32];     //����Ա
	int             yqScore;       //����÷� 90000û�з�
} PGN;

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
    char faceName[LF_FACESIZE];
    float pointSize;
    BYTE bold, italic, underline, strikeout;
} MyFontParams;

typedef struct {
    char *def;
    MyFontParams mfp;
    LOGFONT lf;
    HFONT hf;
} MyFont;

typedef struct {
    COLORREF color;
    int effects;
    char *name;
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

typedef struct {
    char *label;
    int id;
    HWND hwnd;
    WNDPROC wndproc;
} MyButtonDesc;

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
    char *argName;
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


#define DSTEP        0
#define DLOG         1
#define DDATA	     2
#define DCON	     3
#define	DYQ 	     4
#define TIE_NUM      5

struct list_t {
    uint8 p, n;
};

#define MAX_GAME_LENGTH 1024

struct Record
{   
    uint8  nonCap;
    uint8  ischeck;
    //sint16 posVal;
    uint32 move;
    uint64 key;
};

struct move_stack_t {
    int move;
    int score;
};

struct book_face_info_t {
	sint8 result;       //2,1,0,-1,-2;
	uint8 step;         //�岽����󣲣���
	uint8 rate;         //���أ�������������
	uint8 isuse;        //�ǲ�������ʹ�ñ��岽
};

struct book_face_t {
	uint8  f33[33];
	book_face_info_t info[1];
};


#ifdef USE_BerKeley_DB

typedef struct stock_dbs_t {
	
	DB_ENV *Env;

	DB *book;			//���ǵ�ǰʹ�õĵ�book;
	DB *back_db;           //�����ϵͳȱʡ��book;

	char *book_db_name;
	char *good_db_name;

	BOOL Book_Init_Ok;

} STOCK_DBS;

#endif

struct position_t {


    //uint8     board_[256];
    //uint8     *board;                 //����p256
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

	book_face_t book_face[1];


};

typedef struct _CPS {
    //char *which;                //�ǵ�һ�����ǵڶ���

    //int msTotal;                  //��ʱ
    //int msStep;                   //��ʱ
    //int msFirst;                  //�ǲ��ǵ�һʱ���

    //HWND hwndHide;
    //HWND hwndParent;
    //dispboard_t* DIS;


	struct _CPS * loadWhich;        //������һ�����棬��first,����second
	struct _CPS * loadPre;          //


	BOOL          isInLoading;      //�������ڼ���֮�У�
	BOOL          isUpLoading;      //��������ж��֮��
	HWND          loadWin;			//��������Ĵ���

	position_t          pos[1];			//������ʾ�岽��
	int                 pdmove;				//��̨˼�����岽������
	

    int table;

    //char UCCI_which[128]; 
    //int  UCCI_which;             
    int  UCCI_initDone;        //�����ǲ���׼������
    //bool working;            //�������ڹ���
    int  playWhat;             //cps�ߺ���

    int  rep_eat_or_check;      //������������׽

    //char *yqName;             //
    BOOL maybeThinking;
	BOOL maybePonering;
    ProcRef pr;
    InputSourceRef isr;
    //char *twoMachinesColor; /* "white\n" or "black\n" */ 
    //struct _CPS *other;
    //int sendTime;   /* 0=don't, 1=do, 2=test */
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
    int  analysisSupport;
    int  analyzing;

    int  ICS_id;
    //int  ICS_language;      //�������ģ����ǣ�����֮�ǣ�
    int  ICS_net_id;
    char ICS_user[64];
    char ICS_pass[64];
    char ICS_info[256];

    char ICS_net_name[128];
    char ICS_net_host[256];
    int  ICS_net_port;
    char ICS_net_type[128];
    char ICS_net_info[256];


	//BOOL    clockMode;				//�ǲ��Ǽ�ʱ��ʽ

	BOOL 	IsBaoGan;	         //�Ƿ���ɼ�ʱ
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

    char      szHost[256];

    int       yqID;             //������
    int		  ucci;				//�����UCCIЭ��

    //int       Changed_ControlTime;
    //int       Already_Send_Initinfo;

	char      UCCI_ponderMove[32];	//��̨˼�����岽
	BOOL      UCCI_havePonder;      //�к�̨˼���岽

    char      UCCI_name[64];
    char      UCCI_file[64];		//�����ļ���
    char      UCCI_path[MAX_PATH];	//���������������������Ŀ¼

    char      UCCI_copyright[128];
    char      UCCI_author[128];
    char      UCCI_user[64];
    char      UCCI_verson[16];
    int       UCCI_elo;

    bool      UCCI_batch;
    bool      UCCI_debug;
    bool      UCCI_usemillisec;

    /*BOOL      UCCI_ponder;*/
    //bool      UCCI_usebook;
    //bool      UCCI_useegtb;

	BOOL      UCCI_haveselfBook;		//���Լ��Ŀ��ֿ�

    char      UCCI_iniString[256];
    char      UCCI_otherString[256];
    char      UCCI_addInfo[256];
    int       UCCI_smpNum;


    //char      UCCI_bookfiles[MAX_PATH];
    //char      UCCI_egtbpaths[MAX_PATH];

    int       UCCI_hashsize;
    int       UCCI_threads;
    int       UCCI_drawmoves;
    int       UCCI_repetition;
    char      UCCI_pruning[32];    //�ü��̶�
    char      UCCI_knowledge[32];  //֪ʶ��С
    char      UCCI_selectivity[32];//ѡ����(�����)ϵ��
    int       UCCI_style;
    int       UCCI_loadbook;
    int       UCCI_clearhash;
    int       UCCI_dualtime;
    //-------------------------------�������ñ�������
} ChessProgramState;

struct TimeDisp_t {
    int RemainTime;			//��ǰ���õ�ʱ��
	int movetime;           //��ʱ   
	int movestogo;          //Ҫ�߶��ٲ�


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

#define STARTED_NONE            0
#define STARTED_MOVES           1
#define STARTED_BOARD           2
//#define STARTED_OBSERVE         3
#define STARTED_HOLDINGS        4
#define STARTED_CHATTER         5
#define STARTED_COMMENT         6
#define STARTED_MOVES_NOHIDE    7
#define STARTED_PLAYER_LIST     8
#define STARTED_TABLE_LIST       9
#define STARTED_ROOM_DIR       10

//BUF_SIZE

#define ICS_BUF_SIZE   8192

struct ICS_t {

    //int  lastnotfinish;
    char buf[ICS_BUF_SIZE];
    int  buf_len;
    int  tkind;
    int  started;
    int  count; 
    //int  started;
    //int  i;
    //int  oldi;
    //int  tkind;
    //int  next_out;
    //int  leftover_len;
    //int  leftover_start;  
    char star_match[STAR_MATCH_N][MSG_SIZ];
    int  saveingComment;
    int  stage;      //��ǰ�Ĺ�λ
    int  table;      //��ս�����,��ǰ������
    int  loggedOn;
    char ICS_183[8];  //183�Ŀ�ʼ���ܴ�����
    char ICS_name[32]; 

    char *p;
    ColorClass curColor;
    ColorClass prevColor;
};



typedef void (*DelayedEventCallback) (void* pDis);
typedef struct {

    HWND hwndThis; 

	HWND hwndSaveDlg; 


	BOOL               IsFenGame;          //�ǲ�������Ĳо�


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
    char      parseList[MAX_GAME_LENGTH][16];       //ÿ����UCCI����,���Ҳ��������? 
    char      moveListName[MAX_GAME_LENGTH][16];
    AnimInfo			animInfo;
    DragInfo			dragInfo;
    HighlightInfo		highlightInfo;
    HighlightInfo		premoveHighlightInfo;
    GameMode			gameMode;					// = BeginningOfGame;	
    ChessProgramState	first;
    ChessProgramState	second;
    ChessProgramState	ics;

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
    char				messageText[MESSAGE_TEXT_MAX];
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
	char				*variant;

	int                 book_move[128];		  //����߲�
	int                 book_val[128];        //�岽�ļ�ֵ
	int                 book_num;
	int                 book_max_num;         //��õ��岽


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
	BOOL                noChessProgram;
	char               *initialMode;

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
    char *remoteUser;
    float timeDelay;
    //char *timeControl;
    Boolean icsActive;
    //char *icsCommPort;  /* if set, use serial port instead of tcp host/port */
    //char *icsLogon;     /* Hack to permit variable logon scripts. */
    //char *icsHelper;
    Boolean icsInputBox;
    Boolean useTelnet;
    char *telnetProgram;
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

	char *remoteShell;
	char *gateway;

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
    char *premoveWhiteText;	/* text of White premove 1 */ 
    Boolean premoveBlack;	/* true if premoving Black first move */ 
    char *premoveBlackText;	/* text of Black premove 1 */ 
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
	MySound				Asounds[(int)NSoundClasses];
	int					AsaveSettingsOnExit;
	int					AchessProgram;

	ProcRef				AicsPR;
	ChessProgramState   ACPSics;     //����������,һ����˵����վ����
	FILE			    *debugFP;
	InputSourceRef		AtelnetISR;
	InputSourceRef		AfromUserISR;

	CHARFORMAT			AconsoleCF;
	int					prevStderrPort;
	NPLOGPALETTE		ApLogPal;


	int					Aexiting;  
	int					Afrozen;
	int					oldMenuItemState[MENU_BAR_ITEMS];
	Boolean				alarmSounded;

	char	Ahistory[HISTORY_SIZE][1024];
	int		AhistIn;
	int		AhistP;

} AppData, *AppDataPtr;
typedef struct {
    char *title, *question, *replyPrefix;
    ProcRef pr;
} QuestionParams;
struct DLG_STRUCT {

	//HWND        hwndSaveGame;			//		������ִ��ھ��

    WNDPROC     consoleTextWindowProc;
    WNDPROC     consoleInputWindowProc;
    BOOLEAN     consoleEcho;
    
    InputSource *consoleInputSource;
    COLORREF	consoleBackgroundColor;

    HWND		hwndConsole;
    //bool        IsConsoleShow;
    HWND hText;
    HWND hInput;
    HWND dlgBook;          //��ⴰ��
    HWND  hwndGoPlace;
    //
    HWND hwndICS_Board_List;    //����б���
    //WN

};

//struct pgn_file_t {
//
//    int  isStart;
//    char Fen[128]; 
//    
//    //*****************data
//    int  pgn_score;            //����÷�
//    int  islearned;            //�ǲ���ѧϰ����
//    char pgn_event[64];
//    char pgn_date[32];
//    char pgn_round[32];
//    char pgn_site[32];
//    char pgn_white[32];
//    int  pgn_white_elo;
//    char pgn_black[32];
//    int  pgn_black_elo;
//    char pgn_result[16];
//    char pgn_format[8];
//    int  use_time1;
//    int  use_time2;
//    int  use_time3;
//    int  white_time;
//    int  black_time;
//    char result_other[16];      //�췽����ʲô��    
//    //*****************data
//};




#endif