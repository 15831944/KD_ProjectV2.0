// DlgTongJiNode.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "KD_Project.h"
#include "DlgTongJiNode.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "Tools.h"

// DlgTongJiNode �Ի���

IMPLEMENT_DYNAMIC(DlgTongJiNode, CDialogEx)

DlgTongJiNode::DlgTongJiNode(CWnd* pParent /*=NULL*/)
	: CDialogEx(DlgTongJiNode::IDD, pParent)
{


}

DlgTongJiNode::~DlgTongJiNode()
{
}

void DlgTongJiNode::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_ONLINE, OnlineList);
	DDX_Control(pDX, IDC_LIST_LOST, LostList);
	//DDX_Control(pDX, IDC_TREE_ONLINE, OnlineTree);
}


BEGIN_MESSAGE_MAP(DlgTongJiNode, CDialogEx)
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_LSAVE, &DlgTongJiNode::OnRSave)
END_MESSAGE_MAP()


// DlgTongJiNode ��Ϣ�������
BOOL DlgTongJiNode::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	    // ��ȡ�Ի����ʼ��С    
    GetClientRect(&m_rect);  //��ȡ�Ի���Ĵ�С
    old.x=m_rect.right-m_rect.left;  
    old.y=m_rect.bottom-m_rect.top;
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	
	OnlineList.InsertColumn(0,_T(""),LVCFMT_LEFT,50);
	OnlineList.InsertColumn(1,_T("����MAC��ַ"),LVCFMT_CENTER,150);
	OnlineList.InsertColumn(2,_T("TEI"),LVCFMT_CENTER,50);
	OnlineList.InsertColumn(3,_T("����ַ"),LVCFMT_CENTER,150);
	OnlineList.InsertColumn(4,_T("ģ������"),LVCFMT_CENTER,200);
	LostList.InsertColumn(0,_T(""),LVCFMT_LEFT,50);
	LostList.InsertColumn(1,_T("δ����MAC��ַ"),LVCFMT_CENTER,150);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
void DlgTongJiNode::ReSize(void)  
{  
    float fsp[2];  
    POINT Newp; //��ȡ���ڶԻ���Ĵ�С  
    CRect recta;      
    GetClientRect(&recta);     //ȡ�ͻ�����С    
    Newp.x=recta.right-recta.left;  
    Newp.y=recta.bottom-recta.top;  
    fsp[0]=(float)Newp.x/old.x;  
    fsp[1]=(float)Newp.y/old.y;  
    CRect Rect;  
    int woc;  
    CPoint OldTLPoint,TLPoint; //���Ͻ�  
    CPoint OldBRPoint,BRPoint; //���½�  
    HWND  hwndChild=::GetWindow(m_hWnd,GW_CHILD);  //�г����пؼ�    
    while(hwndChild){      
        woc=::GetDlgCtrlID(hwndChild);//ȡ��ID  
        GetDlgItem(woc)->GetWindowRect(Rect);    
        ScreenToClient(Rect);    
        OldTLPoint = Rect.TopLeft();    
        TLPoint.x = long(OldTLPoint.x*fsp[0]);    
        TLPoint.y = long(OldTLPoint.y*fsp[1]);    
        OldBRPoint = Rect.BottomRight();    
        BRPoint.x = long(OldBRPoint.x *fsp[0]);    
        BRPoint.y = long(OldBRPoint.y *fsp[1]);    
        Rect.SetRect(TLPoint,BRPoint);    
        GetDlgItem(woc)->MoveWindow(Rect,TRUE);  
        hwndChild=::GetWindow(hwndChild, GW_HWNDNEXT);      
    }
    old=Newp;  
}  
void DlgTongJiNode::OnSize(UINT nType, int cx, int cy)
{
    CDialogEx::OnSize(nType,cx,cy);
    if(nType!=SIZE_MINIMIZED )  //�жϴ����ǲ�����С���ˣ���Ϊ������С��֮�� �����ڵĳ��Ϳ����0����ǰһ�α仯��ʱ�ͻ���ֳ���0�Ĵ������
    {
        ReSize();
    }
}

void DlgTongJiNode::ChangeSize(UINT nID,int x,int y)
{
    CWnd *pWnd = GetDlgItem(nID);
    if(pWnd!=NULL)
    {
        CRect rec;
        pWnd->GetWindowRect(&rec);//��ȡ�ؼ��仯ǰ�Ĵ�С
        ScreenToClient(rec);   //���ؼ���Сװ��λ�ڶԻ����е���������
        // x / m_rect.Width(); ����rate
        rec.left = rec.left * x / m_rect.Width();
        rec.top = rec.top * y / m_rect.Height();
        rec.bottom = rec.bottom  * y / m_rect.Height();
        rec.right = rec.right * x / m_rect.Width();
        pWnd->MoveWindow(rec);//�����ؼ�
    }
}

void DlgTongJiNode::InsertItemToOnlineList(CString strMAC , CString strTEI , CString strAddress , CString strType)
{
	CString strNumb;
	int n = 0;
	n = OnlineList.GetItemCount();
	strNumb.Format(_T("%d") , n + 1);
	OnlineList.InsertItem(n , strNumb);
	OnlineList.SetItemText(n , 1 , strMAC.Mid(0 , 2) + _T(":") + strMAC.Mid(2 , 2) + _T(":") + strMAC.Mid(4 , 2) + _T(":") + strMAC.Mid(6 , 2) + _T(":") + strMAC.Mid(8 , 2) + _T(":") + strMAC.Mid(10 , 2));
	OnlineList.SetItemText(n , 2 , strTEI);
	OnlineList.SetItemText(n , 3 , strAddress);
	switch(_ttoi(strType))
	{
	case 1:
		break;
	case 2:
		OnlineList.SetItemText(n , 4 , _T("�������ز�ģ��"));
		break;
	case 3:
		break;
	case 4:
		if (strMAC.Find(_T("BEBEBEBEBE")) != -1 )
		{
			OnlineList.SetItemText(n , 4 , _T("�������ز�ģ��"));
		} 
		else
		{
			OnlineList.SetItemText(n , 4 , _T("������ز�ģ��"));
		}
		break;
	}
	OnlineList.EnsureVisible(n,FALSE);
	OnlineList.RedrawItems(n,n);
}

void DlgTongJiNode::InsertItemToLostList(CString strMAC)
{
	CString strNumb;
	int n = 0;
	n = LostList.GetItemCount();
	strNumb.Format(_T("%d") , n + 1);
	LostList.InsertItem(n , strNumb);
	LostList.SetItemText(n , 1 , strMAC.Mid(0 , 2) + _T(":") + strMAC.Mid(2 , 2) + _T(":") + strMAC.Mid(4 , 2) + _T(":") + strMAC.Mid(6 , 2) + _T(":") + strMAC.Mid(8 , 2) + _T(":") + strMAC.Mid(10 , 2));
	LostList.EnsureVisible(n,FALSE);
	LostList.RedrawItems(n,n);
}

void DlgTongJiNode::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	CMenu menu;
	VERIFY(menu.LoadMenu(IDR_MENU_SAVESVC));
	CMenu* pPopup = menu.GetSubMenu(0);
	ASSERT(pPopup != NULL);
	CWnd* pWndPopupOwner = this;

	//while (pWndPopupOwner->GetStyle() & WS_CHILD)
	//	pWndPopupOwner = pWndPopupOwner->GetParent();

	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
		pWndPopupOwner);
}

void DlgTongJiNode::OnRSave()
{
        // TODO: Add your control notification handler code here   
    // ���ù�����   
	CMainFrame* pMain= (CMainFrame*)AfxGetApp()->GetMainWnd();
    TCHAR szFilter[] = _T("�ļ�(*.csv)");   
    // ���챣���ļ��Ի���   
    CFileDialog fileDlg(FALSE, _T("csv"), _T("my"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);   
    CString strFilePath;   
  
    // ��ʾ�����ļ��Ի���   
    if (IDOK == fileDlg.DoModal())   
    {   	
		int nHang= 0;
		char szANSIString[5000];
		//CString strlist;
		CString strUpDataMessage;

	    CString strlist = fileDlg.GetPathName();  
//int len =WideCharToMultiByte(CP_ACP,0,strlist,-1,NULL,0,NULL,NULL);  
//char *ptxtTemp =new char[len +1];  
//WideCharToMultiByte(CP_ACP,0,strlist,-1,ptxtTemp,len,NULL,NULL ); 
		int len =WideCharToMultiByte(CP_ACP,0,strlist,strlist.GetLength(),NULL,0,NULL,NULL);
		char * pFileName = new char[len + 1];
		WideCharToMultiByte(CP_ACP,0,strlist,strlist.GetLength(),pFileName,len,NULL,NULL);
		pFileName[len] ='\0';

		m_tools.AutoMakedir(pFileName);
		m_fp=fopen(pFileName,"r");
		if  ( m_fp == NULL )
		{
			m_fp=fopen(pFileName,"a+");

			if(m_fp != NULL) 
			{
				CString strTopLine = _T("MAC,TEI,TYPE\n");
				WideCharToMultiByte(CP_ACP,WC_COMPOSITECHECK,strTopLine,-1,szANSIString,sizeof(szANSIString),NULL,NULL);
				fwrite(szANSIString,wcslen(strTopLine),1,m_fp);
			}
		}
		else
		{
			fclose(m_fp); 
			m_fp=fopen(pFileName,"a+");
		} 
		int OnCountNum=OnlineList.GetItemCount();
		int LostCountNum=LostList.GetItemCount();
		if(m_fp != NULL) 
		{
			for(int i=0;i<OnCountNum;i++){
				CString strlistData[3];
				//CString strSn;
				//strSn.Format(_T("%d"),2);
				strlistData[0] = OnlineList.GetItemText(i,3);
				strlistData[1]=OnlineList.GetItemText(i,2);;
				strlistData[2]=_T("1");

				CString strTopLine = strlistData[0] + _T(",") + strlistData[1] + _T(",") + strlistData[2]+ _T("\n");
				WideCharToMultiByte(CP_ACP,WC_COMPOSITECHECK,strTopLine,-1,szANSIString,sizeof(szANSIString),NULL,NULL);
				fwrite(szANSIString,wcslen(strTopLine),1,m_fp);
			}
			for(int i=0;i<LostCountNum;i++){
				CString strlistData[3];
				//CString strSn;
				//strSn.Format(_T("%d"),2);
				strlistData[0] = LostList.GetItemText(i,1);
				strlistData[1]=_T("");
				strlistData[2]=_T("0");

				CString strTopLine = strlistData[0] + _T(",") + strlistData[1] + _T(",") + strlistData[2]+ _T("\n");
				WideCharToMultiByte(CP_ACP,WC_COMPOSITECHECK,strTopLine,-1,szANSIString,sizeof(szANSIString),NULL,NULL);
				fwrite(szANSIString,wcslen(strTopLine),1,m_fp);
			}

			fclose(m_fp);
		}
        // ���������ļ��Ի����ϵġ����桱��ť����ѡ����ļ�·����ʾ���༭����   
        //strFilePath = fileDlg.GetPathName();   
        //AfxMessageBox(strFilePath);//SetDlgItemText(IDC_SAVE_EDIT, strFilePath);   
    }   
}
