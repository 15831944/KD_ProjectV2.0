#pragma once


// AddMacTest �Ի���

class AddMacTest : public CDialogEx
{
	DECLARE_DYNAMIC(AddMacTest)

public:
	AddMacTest(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~AddMacTest();

// �Ի�������
	enum { IDD = IDD_DIALOG7 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_TYPE;
	CString m_MAC;
	CString m_TEI;
};
