#pragma once

#include "MyListCtrl.h"
#include "afxcmn.h"
#include "Tools.h"
#include "afxwin.h"
#include "AccessData.h"
#include "Tools.h"
#include "MSDU2017.h"
#include "AddMacTest.h"
#include "CKQ2017.h"
// CCKQViewUpdata ������ͼ

class CCKQViewUpdata : public CFormView
{
	DECLARE_DYNCREATE(CCKQViewUpdata)

protected:
	CCKQViewUpdata();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CCKQViewUpdata();

public:
	enum { IDD = IDD_DIALOG_CKQ_UPDATA };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	CFont m_fontStatic;
	void SetNewFont();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int m_nDataLong , m_nYU , m_nCHU;
    CKQ2017 gCKQ2017;
	MSDU2017 gMSDU2017;
	CAccessData m_accessData;
	HANDLE m_hThreadsend;
	CStringList m_listStrShengjiData;//���������б�
	void SetUpdataListData();
	void SetMsduUpdataListData(INT16U blksize,INT32U ftpID);
	CString GetDuanAndLen(int nduan,int nlen);
	CString strHEX(CString str,bool bDaoxu = TRUE);
	void SaveNetDataToAccess(CString strTPdata);
	///////// 171220 by lc
	//INT8U SendRec_MAC_13762_toCCO(sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame,sPartQGDW376_2DeCodeFrame &sRecv376_2HostFrame);
    INT8U zhengchangshengji(CString m_strLujing);//�γ�1024
	/////////////

#ifdef _STD_CSG  //������׼
	int m_FileSize, m_NrOfSectors;
#endif
public:
	CTools m_tools;
	CMyListCtrl m_listData;
	afx_msg void OnBnClickedBtnChoosefile();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedBtnRefresh();
	CButton m_radioUpType;
	CEdit m_editFile;
	afx_msg void OnBnClickedBtnBeginupdata();
	CButton m_btnSend;
	afx_msg void OnBtnBeginupdata2();
	afx_msg void OnModerrUpdata1();
	CComboBox m_upType;
	afx_msg void Onshuaxinlb();
	afx_msg void OnAddNode();
};


