// DlgXYData.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "KD_Project.h"
#include "DlgXYData.h"
#include "afxdialogex.h"
#include "MainFrm.h"

// CDlgXYData �Ի���

IMPLEMENT_DYNAMIC(CDlgXYData, CDialogEx)

CDlgXYData::CDlgXYData(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgXYData::IDD, pParent)
	, v_editdata(_T(""))
	, v_datalen(0)
{

}

CDlgXYData::~CDlgXYData()
{
}

void CDlgXYData::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_DATA, m_listData);
	DDX_Control(pDX, IDC_EDIT_AFNFN, m_editAFNFN);
	DDX_Control(pDX, IDC_EDIT_DATA, m_editData);
	DDX_Control(pDX, IDC_EDIT_DATALEN, m_editDatalen);
	DDX_Control(pDX, IDC_EDIT_DOWNBM, m_editDownBM);
	DDX_Control(pDX, IDC_EDIT_DOWNMSG, m_editDownMsg);
	DDX_Control(pDX, IDC_EDIT_UPBM, m_editUpBM);
	DDX_Control(pDX, IDC_EDIT_UPMSG, m_editUpMsg);
	DDX_Control(pDX, IDC_COMB_AFN, m_combANF);
	DDX_Control(pDX, IDC_EDIT_NAME, m_editName);
	DDX_Text(pDX, IDC_EDIT_DATA, v_editdata);
	DDX_Text(pDX, IDC_EDIT_DATALEN, v_datalen);
}


BEGIN_MESSAGE_MAP(CDlgXYData, CDialogEx)
	ON_NOTIFY(NM_CLICK, IDC_LIST_DATA, &CDlgXYData::OnNMClickListData)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CDlgXYData::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_INSET, &CDlgXYData::OnBnClickedButtonInset)
	ON_BN_CLICKED(IDC_BUTTON_DEL, &CDlgXYData::OnBnClickedButtonDel)
	ON_CBN_SELCHANGE(IDC_COMB_AFN, &CDlgXYData::OnCbnSelchangeCombAfn)
//	ON_EN_CHANGE(IDC_EDIT_DOWNMSG, &CDlgXYData::OnEnChangeEditDownmsg)
//	ON_EN_CHANGE(IDC_EDIT_DATA, &CDlgXYData::OnEnChangeEditData)
//ON_NOTIFY(NM_THEMECHANGED, IDC_EDIT_DATA, &CDlgXYData::OnNMThemeChangedEditData)
ON_EN_CHANGE(IDC_EDIT_DATA, &CDlgXYData::OnEnChangeEditData)
END_MESSAGE_MAP()


// CDlgXYData ��Ϣ�������


BOOL CDlgXYData::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CMainFrame* pMain= (CMainFrame*)AfxGetApp()->GetMainWnd();
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_listData.InsertColumn(0,_T("AFN_FN"),LVCFMT_LEFT,100);
	m_listData.InsertColumn(1,_T("����"),LVCFMT_LEFT,200);
	m_listData.InsertColumn(2,_T("����"),LVCFMT_LEFT,100);
	m_listData.InsertColumn(3,_T("���ݳ���"),LVCFMT_LEFT,100);
	m_listData.InsertColumn(4,_T("���б���"),LVCFMT_LEFT,150);
	m_listData.InsertColumn(5,_T("������Ϣ"),LVCFMT_LEFT,150);
	m_listData.InsertColumn(6,_T("���б���"),LVCFMT_LEFT,150);
	m_listData.InsertColumn(7,_T("������Ϣ"),LVCFMT_LEFT,150);
	m_listData.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_editAFNFN.SetLimitText(6);

	wchar_t   buf[1000]; 
	GetPrivateProfileSectionNames(buf,sizeof(buf),  pMain->m_PeiZhi);//_T(".\\�����ļ�\\13762���ؼ�.ini")); 
	CString str;	
	for(wchar_t*   Name=buf;   *Name!= '\0';   Name+=wcslen(Name)+1) 
	{
		str.Format(_T("%s"), Name);
		m_combANF.AddString(str);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
void CDlgXYData::OnCbnSelchangeCombAfn()
{
	CMainFrame* pMain= (CMainFrame*)AfxGetApp()->GetMainWnd();
	CString strAfn = _T("") , strName = _T("");
	m_combANF.GetWindowTextW(strAfn);
	m_listData.DeleteAllItems();
	CString strData[1000];
	CString strMessage[10];
	wchar_t   buf[100]; 
	CString strWhere = _T("AFN_FN like '") + strAfn.Mid(0 , 2) + _T("%'");
	int nHang = 0;
	//if(!m_access.SelectDataFromTable(_T(".\\�����ļ�\\13762Data.accdb"),_T("DataMessage"),_T("AFN_FN,Databuf,Datalen,DownBM,DownXS,UpBM,UpXS"),strWhere,strData,nHang))
	if(!m_access.SelectDataFromTable(pMain->m_PeiZhi_db,_T("DataMessage"),_T("AFN_FN,Databuf,Datalen,DownBM,DownXS,UpBM,UpXS"),strWhere,strData,nHang))
	{
		AfxMessageBox(_T("���ݿ����ʧ�ܣ�"));
	}
	for (int n = 0 ; n < nHang ;n++)
	{
		m_tool.strlistData(strData[n],_T("$"),strMessage);
		GetPrivateProfileString(strAfn , strMessage[0] , _T("") ,buf,sizeof(buf), pMain->m_PeiZhi); //_T(".\\�����ļ�\\13762���ؼ�.ini"));
		strName.Format(_T("%s") , buf);
		m_listData.InsertItem(n,strMessage[0].Mid(2));
		m_listData.SetItemText(n , 1 , strName.Mid(6));
		m_listData.SetItemText(n , 2 , strMessage[1]);
		m_listData.SetItemText(n , 3 , strMessage[2]);
		m_listData.SetItemText(n , 4 , strMessage[3]);
		m_listData.SetItemText(n , 5 , strMessage[4]);
		m_listData.SetItemText(n , 6 , strMessage[5]);
		m_listData.SetItemText(n , 7 , strMessage[6]);
	}

}


void CDlgXYData::OnNMClickListData(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	for(int m_n=0; m_n<m_listData.GetItemCount(); m_n++)
	{
		if( m_listData.GetItemState(m_n,LVIS_SELECTED) == LVIS_SELECTED )
		{
			m_editAFNFN.SetWindowText(m_listData.GetItemText(m_n,0));
			m_editName.SetWindowText(m_listData.GetItemText(m_n,1));
			m_editData.SetWindowText(m_listData.GetItemText(m_n,2));
			m_editDatalen.SetWindowText(m_listData.GetItemText(m_n,3));
			m_editDownBM.SetWindowText(m_listData.GetItemText(m_n,4));
			m_editDownMsg.SetWindowText(m_listData.GetItemText(m_n,5));
			m_editUpBM.SetWindowText(m_listData.GetItemText(m_n,6));
			m_editUpMsg.SetWindowText(m_listData.GetItemText(m_n,7));
			m_nSelNumb = m_n;
			break;
		}
	}
	
	*pResult = 0;
}



void CDlgXYData::OnBnClickedButtonAdd()
{
	CMainFrame* pMain= (CMainFrame*)AfxGetApp()->GetMainWnd();
	//CString strAFNFN , strDatalen ,strData,strDownBM,strDownXS, strUPBM,strUPXS , strDataMessage;
	CString strlistName[8] = {_T("AFN_FN") ,_T("Databuf") ,_T("Datalen") ,_T("DownBM") ,_T("DownXS") ,_T("UpBM") ,_T("UpXS") ,_T("DataMessage") };
	CString strlistData[8];
	CString strAFN = _T("") , strName;
	m_editAFNFN.GetWindowText(strlistData[0]);
	m_editData.GetWindowText(strlistData[1]);
	m_editDatalen.GetWindowText(strlistData[2]);
	m_editDownBM.GetWindowText(strlistData[3]);
	m_editDownMsg.GetWindowText(strlistData[4]);
	m_editUpBM.GetWindowText(strlistData[5]);
	m_editUpMsg.GetWindowText(strlistData[6]);
	strlistData[7] = "";
	m_editName.GetWindowTextW(strName);
	m_combANF.GetWindowTextW(strAFN);
	if (wcslen(strlistData[0]) != 4)
	{
		AfxMessageBox(_T("FN �������"));
		return;
	}
	//if (wcslen(strlistData[1]) != 2 * _ttoi(strlistData[2]))
	//{
	//	AfxMessageBox(_T("�������ݳ��������ݲ���"));
	//	return;
	//}
	strlistData[0] = strAFN.Mid(0 , 2) + strlistData[0];
	//if(m_access.AddDataToTable(_T(".\\�����ļ�\\13762Data.accdb"),_T("DataMessage"),strlistName , strlistData ,8))
	if(m_access.AddDataToTable(pMain->m_PeiZhi_db,_T("DataMessage"),strlistName , strlistData ,8))
	{
		m_listData.InsertItem(m_listData.GetItemCount(),strlistData[0].Mid(2));
		m_listData.SetItemText(m_listData.GetItemCount() - 1 , 1 , strName);
		m_listData.SetItemText(m_listData.GetItemCount() - 1 , 2 , strlistData[1]);
		m_listData.SetItemText(m_listData.GetItemCount() - 1 , 3 , strlistData[2]);
		m_listData.SetItemText(m_listData.GetItemCount() - 1 , 4 , strlistData[3]);
		m_listData.SetItemText(m_listData.GetItemCount() - 1 , 5 , strlistData[4]);
		m_listData.SetItemText(m_listData.GetItemCount() - 1 , 6 , strlistData[5]);
		m_listData.SetItemText(m_listData.GetItemCount() - 1 , 7 , strlistData[6]);
		WritePrivateProfileString(strAFN , strlistData[0] ,_T("(") + strlistData[0].Mid(2) +_T(")") + strName ,pMain->m_PeiZhi);//_T(".\\�����ļ�\\13762���ؼ�.ini"));
	}
	else
	{
		AfxMessageBox(_T("�Ѵ��ڣ�"));
	}
}


void CDlgXYData::OnBnClickedButtonInset()
{
	CMainFrame* pMain= (CMainFrame*)AfxGetApp()->GetMainWnd();
	CString strAFN = _T("") ,strName;
	CString strlistData[7];
	m_editAFNFN.GetWindowText(strlistData[0]);
	m_editData.GetWindowText(strlistData[1]);
	m_editDatalen.GetWindowText(strlistData[2]);
	m_editDownBM.GetWindowText(strlistData[3]);
	m_editDownMsg.GetWindowText(strlistData[4]);
	m_editUpBM.GetWindowText(strlistData[5]);
	m_editUpMsg.GetWindowText(strlistData[6]);
	m_combANF.GetWindowTextW(strAFN);

	m_editName.GetWindowText(strName);

	if (wcslen(strlistData[0]) != 4)
	{
		AfxMessageBox(_T("FN �������"));
		return;
	}
	//if (wcslen(strlistData[1]) != 2 * _ttoi(strlistData[2]))
	//{
	//	AfxMessageBox(_T("�������ݳ��������ݲ���"));
	//	return;
	//}
	if(strlistData[0] != m_listData.GetItemText(m_nSelNumb,0))
	{
		AfxMessageBox(_T("AFN��FN ���ݲ����޸�"));
		return;
	}
	CString strSet = _T("Databuf='") + strlistData[1] +
					 _T("',Datalen='") + strlistData[2] +
					 _T("',DownBM='") + strlistData[3] +
					 _T("',DownXS='") + strlistData[4] +
					 _T("',UpBM='") + strlistData[5] +
					 _T("',UpXS='") + strlistData[6] + _T("'");
	CString stWhere = _T("AFN_FN='") + strAFN.Mid(0 , 2) + strlistData[0] + _T("'");
	//if(m_access.UpdataFromTable(_T(".\\�����ļ�\\13762Data.accdb"),_T("DataMessage"),strSet , stWhere))
	if(m_access.UpdataFromTable(pMain->m_PeiZhi_db,_T("DataMessage"),strSet , stWhere))
	{
		m_listData.SetItemText(m_nSelNumb , 1 , strName);
		m_listData.SetItemText(m_nSelNumb , 2 , strlistData[1]);
		m_listData.SetItemText(m_nSelNumb , 3 , strlistData[2]);
		m_listData.SetItemText(m_nSelNumb , 4 , strlistData[3]);
		m_listData.SetItemText(m_nSelNumb , 5 , strlistData[4]);
		m_listData.SetItemText(m_nSelNumb , 6 , strlistData[5]);
		m_listData.SetItemText(m_nSelNumb , 7 , strlistData[6]);

		WritePrivateProfileString(strAFN , strAFN.Mid(0 , 2) + strlistData[0] ,_T("(") + strlistData[0] +_T(")") + strName,pMain->m_PeiZhi);//_T(".\\�����ļ�\\13762���ؼ�.ini"));
	}
}


void CDlgXYData::OnBnClickedButtonDel()
{
	CMainFrame* pMain= (CMainFrame*)AfxGetApp()->GetMainWnd();
	CString strWhere , strAFN ,strFN;
	m_combANF.GetWindowTextW(strAFN);
	m_editAFNFN.GetWindowText(strFN);
	strWhere = _T("AFN_FN='") + strAFN.Mid(0,2) + strFN + _T("'");
	//if(m_access.DelectDataFromTable(_T(".\\�����ļ�\\13762Data.accdb"),_T("DataMessage") , strWhere))
	if(m_access.DelectDataFromTable(pMain->m_PeiZhi_db,_T("DataMessage") , strWhere))
	{
		m_listData.DeleteItem(m_nSelNumb);
		WritePrivateProfileString(strAFN , strAFN.Mid(0,2) + strFN , NULL ,pMain->m_PeiZhi);//_T(".\\�����ļ�\\13762���ؼ�.ini"));
	}

}




//void CDlgXYData::OnEnChangeEditDownmsg()
//{
//	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
//	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
//	// ���������� CRichEditCtrl().SetEventMask()��
//	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
//	INT8U DataBuf[200];
//	INT16U DataBuflen;
//	m_tool._str16tobuf16(v_editdata ,&DataBuf[2], DataBuflen);//
//	v_datalen=DataBuflen;
//	//upDataData(true);
//	UpdateData(FALSE);
//	// TODO:  �ڴ���ӿؼ�֪ͨ����������
//}









void CDlgXYData::OnEnChangeEditData()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
   UpdateData(TRUE);
	INT8U DataBuf[200];
	INT16U DataBuflen;
	m_tool._str16tobuf16(v_editdata ,&DataBuf[2], DataBuflen);//
	v_datalen=DataBuflen;
	UpdateData(FALSE);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
