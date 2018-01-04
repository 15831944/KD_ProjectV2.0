#pragma once
// TongJNodeDialog �Ի���
#include "Tools.h"
#include "AccessData.h"
#include "ShowNetTreeView.h"
#include "ShowNetListView.h"
class TongJNodeDialog : public CDialogEx
{
	DECLARE_DYNAMIC(TongJNodeDialog)
public:
	TongJNodeDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~TongJNodeDialog();
	void InsertItemToTreeList(CString strTableName);
	void InsertItemToOnlineList(CString strMAC , CString strTEI , CString strAddress , CString strType);
	void InsertItemToLostList(CString strMAC);

	 CFrameWnd *m_pMyFrame;
	 CSplitterWnd m_cSplitter; 
	 CImageList m_imageList;
	 CAccessData m_access;
	 CTools m_tools;
	 CString m_strlist[1000];
	 ShowNetTreeView *pView;
	 ShowNetListView *pViewOnlineList;
	  ShowNetListView *pViewLostList;
	 //LostNodeListDialog ss;
// �Ի�������
	enum { IDD = IDD_TONGJIDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
};

