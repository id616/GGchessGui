#pragma once


// dlgtest �Ի���

class dlgtest : public CDialogEx
{
	DECLARE_DYNAMIC(dlgtest)

public:
	dlgtest(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~dlgtest();

// �Ի�������
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
