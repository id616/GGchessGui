#pragma once


// DLG_LOG_DISPLAY �Ի���

class DLG_LOG_DISPLAY : public CDialogEx
{
	DECLARE_DYNAMIC(DLG_LOG_DISPLAY)

public:
	DLG_LOG_DISPLAY(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DLG_LOG_DISPLAY();

// �Ի�������
	enum { IDD = DLG_RICH_LOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
