#if !defined(XQDATA_H_INCLUDED)
#define XQDATA_H_INCLUDED

#pragma pack(push, 1)

const int CHESS_MAN_NUM = 32; // ˫����������Ŀ

enum XM_TYPE
{
	XM_JU, // ��
	XM_MA, // ��
	XM_XIANG, // ����
	XM_SHI, // ��ʿ
	XM_KING, // ˧��
	XM_PAO, // ��
	XM_BING // ����
};

const XM_TYPE g_xqMan[] = 
{
	XM_JU, XM_MA, XM_XIANG, XM_SHI, XM_KING, XM_SHI, XM_XIANG, XM_MA, XM_JU, XM_PAO, XM_PAO, XM_BING, XM_BING, XM_BING, XM_BING, XM_BING,
	XM_JU, XM_MA, XM_XIANG, XM_SHI, XM_KING, XM_SHI, XM_XIANG, XM_MA, XM_JU, XM_PAO, XM_PAO, XM_BING, XM_BING, XM_BING, XM_BING, XM_BING
};

// ����˳��
enum XQ_ORDER
{
	XO_RED, // ����
	XO_BLACK, // ����
	XO_NONE // δ֪
};

// ���
enum XQ_RESULT
{
	XR_UNKNOWN, // δ֪
	XR_REDWIN, // ��ʤ
	XR_BLACKWIN, // ��ʤ
	XR_PEACE // ��
};

// ��������
enum XQ_TYPE
{
	XT_ALL, // ȫ��
	XT_OPEN, // ����
	XT_MIDDLE, // �о�
	XT_END // �о�
};

struct XQExplainData
{
	XQ_ORDER eOrder;
	XQExplainData()
	{
		eOrder = XO_NONE;
	}
};


struct XQFFileHeader
{
	WORD wMagic;
	BYTE ucVer;
	BYTE ucChk1;
	BYTE uc[0xC];
	BYTE ucBoard[CHESS_MAN_NUM];
	BYTE ucUn2[3];
	BYTE ucRes; // offset 0x33
	BYTE ucUn3[0xC];
	BYTE ucType; // �������(���в�ȫ), offset: 0x40
	BYTE ucUn4[0xF];
	BYTE ucTitleLen; // �������� offset 0x50
	char szTitle[0x90 - 0x51];
	BYTE ucUn5[0xD0 - 0x90];
	BYTE ucMatchName; // �������� offset 0xD0
	char szMatchName[0x110 - 0xD1]; // ��������
	BYTE ucDateLen; // ��������, offset 0x110
	char szDate[0x120 - 0x111];
	BYTE ucAddrLen; // �����ص㣬offset 0x120
	char szAddr[0x130 - 0x121];
	BYTE ucRedPlayerNameLen; // �췽��������, offset 0x130
	char szRedPlayerName[0x140 - 0x131];
	BYTE ucBlackPlayerNameLen; // �ڷ����������� offset 0x140
	char szBlackPlayerName[0x150 - 0x141];
	BYTE ucTimeRuleLen; //����ʱ����, offset 0x151
	char szTimeRule[0x190 - 0x151];
	BYTE ucRedTimeLen; // �췽��ʱ����, offset 0x190
	char szRedTime[0x1A0 - 0x191];
	BYTE ucBlackTime; // �ڷ���ʱ����, offset 0x1a0
	char szBlackTime[0x1B0 - 0x1A1]; 
	BYTE ucUn6[0x1D0 - 0x1B0];
	BYTE ucCommenerNameLen; // ��������������, offset 0x1D0
	char szCommenerName[0x1E0 - 0x1D1];
	BYTE ucAuthorNameLen; // �ļ�������������, offset 0x1E0
	char szAuthorName[0x1F0 - 0x1E1];
	BYTE ucUn7[0x400 - 0x1F0];
};
#pragma pack(pop)

struct XQNode
{
	BYTE ucStart;
	BYTE ucEnd;
	XQ_ORDER eOrder;     // ��ǰ���Ǻ��ߵĻ��Ǻ��ߵ�
	char* szComment;
	XQNode* pParent;
	XQNode* pFirstChild; // ��һ��ѡ��
	XQNode* pCurChild;   // ��ǰѡ��
	XQNode* pLeft;       // ����
	XQNode* pRight;      // �ҽ��
	BYTE ucChessBoard[CHESS_MAN_NUM]; // �����֮����
	XQNode()
	{
		ucStart = ucEnd = 0;
		eOrder = XO_NONE;
		szComment = NULL;
		pParent = NULL;
		pFirstChild = NULL;
		pCurChild = NULL;
		pLeft = NULL;
		pRight = NULL;
	}

	~XQNode()
	{
		delete []szComment;
	}

};

//struct XQData
//{
////	XQExplainData dataExplain;
//	XQFFileHeader fileHeader;
//	XQNode* pRoot;
//
//	XQData()
//	{
//		pRoot = NULL;
//	}
//
//	~XQData()
//	{
//		DeleteXQNode(pRoot);
//	}
//};




#endif  // Sentry