// TongJNodeDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "KD_Project.h"
#include "TongJNodeDialog.h"
#include "afxdialogex.h"
#include "MyListCtrl.h"

#include "MainFrm.h"
// TongJNodeDialog �Ի���

IMPLEMENT_DYNAMIC(TongJNodeDialog, CDialogEx)

TongJNodeDialog::TongJNodeDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(TongJNodeDialog::IDD, pParent)
{
	//LostNodeListDialog *ss=new LostNodeListDialog;
}

TongJNodeDialog::~TongJNodeDialog()
{
}

void TongJNodeDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(TongJNodeDialog, CDialogEx)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// TongJNodeDialog ��Ϣ�������


int TongJNodeDialog::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1; 
	// TODO:  �ڴ������ר�õĴ�������
	CRect cRect;
	GetWindowRect(&cRect);
	ScreenToClient(&cRect);  
	HICON hIcon[15];      // ͼ�������� 
	hIcon[0] = theApp.LoadIcon(IDI_CCO2); 
	hIcon[1] = theApp.LoadIcon(IDI_ZONGSE); 
	hIcon[2] = theApp.LoadIcon(IDI_LVSE); 
	hIcon[3] = theApp.LoadIcon(IDI_LANSE); 
	hIcon[4] = theApp.LoadIcon(IDI_YELLO); 
	hIcon[5] = theApp.LoadIcon(IDI_BAISE);
	    // ����ͼ������CImageList����   
    m_imageList.Create(16, 16, ILC_COLOR32, 6, 6);   
    // ������ͼ����ӵ�ͼ������   
    for (int i=0; i<6; i++)   
    {   
        m_imageList.Add(hIcon[i]);   
    }
	CString strMyClass = AfxRegisterWndClass(CS_VREDRAW | CS_HREDRAW,    
                   ::LoadCursor(NULL, IDC_ARROW),    (HBRUSH) ::GetStockObject(WHITE_BRUSH),     
                  ::LoadIcon(NULL, IDI_APPLICATION));  
  
    // Create the frame window with "this" as the parent  
    m_pMyFrame = new CFrameWnd;  
    m_pMyFrame->Create(strMyClass,_T(""), WS_CHILD,   CRect(10,10,600,600), this);  
  
    // and finally, create the splitter with the frame as the parent  
    m_cSplitter.CreateStatic(m_pMyFrame,1,3); //��Frame���з���ͼ����Ϊ1��3������һ������  
    m_cSplitter.CreateView(0,0, RUNTIME_CLASS(ShowNetTreeView),   CSize(cRect.Width()/3+100,cRect.Height()), NULL);//��һ��һ��  
    m_cSplitter.CreateView(0,1, RUNTIME_CLASS(ShowNetListView),   CSize(cRect.Width()/4+100,cRect.Height()), NULL);//��һ�ж���  
	m_cSplitter.CreateView(0,2, RUNTIME_CLASS(ShowNetListView),   CSize(cRect.Width()/4,cRect.Height()), NULL);//��һ�ж��� 
	pView=(ShowNetTreeView*)m_cSplitter.GetPane(0,0);//���ܷ��ڵ����ĺ�����
	pViewOnlineList=(ShowNetListView*)m_cSplitter.GetPane(0,1);
	pViewLostList=(ShowNetListView*)m_cSplitter.GetPane(0,2);
	pViewLostList->GetListCtrl().DeleteAllItems();
	pViewLostList->GetListCtrl().InsertColumn(0,_T("���"),LVCFMT_LEFT,50);
	pViewLostList->GetListCtrl().InsertColumn(1,_T("δ����MAC��ַ"),LVCFMT_LEFT,150);
	return 0;
}


void TongJNodeDialog::OnDestroy()
{
	CDialogEx::OnDestroy();
	if (m_pMyFrame) delete m_pMyFrame;  

	// TODO: �ڴ˴������Ϣ����������
}







void TongJNodeDialog::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	CRect cRect;  
    GetWindowRect(&cRect);
	cRect.left=cRect.left+10;
	cRect.top=cRect.top+38;
	cRect.right=cRect.right-10;
    ScreenToClient(&cRect);
	//m_cSplitter.SetColumnInfo(0,cRect.Width() * 0.4,10);//ÿһ���ָ�VIEW�ĵ��� ���һ������ ��Сָ��קʱ������С
	m_pMyFrame->MoveWindow(&cRect);
    m_pMyFrame->ShowWindow(SW_SHOW); 
}


void TongJNodeDialog::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	// TODO: �ڴ˴������Ϣ����������
	CMenu menu;//
	ShowNetTreeView *pTreeView=(ShowNetTreeView*)m_cSplitter.GetPane(0,0);
	ShowNetTreeView *pListView=(ShowNetTreeView*)m_cSplitter.GetPane(0,1);
	HWND hwndFocus=GetFocus()->GetSafeHwnd();
	HWND hwndTreeView = pTreeView->GetSafeHwnd();
	if(hwndTreeView==hwndFocus){
	    VERIFY(menu.LoadMenu(IDR_MENU_COPYFRAME));
	}
	else{
	    VERIFY(menu.LoadMenu(IDR_MENU_SAVESVC));
	}
	CMenu* pPopup = menu.GetSubMenu(0);
	ASSERT(pPopup != NULL);
	CWnd* pWndPopupOwner = this;

	while (pWndPopupOwner->GetStyle() & WS_CHILD)
		pWndPopupOwner = pWndPopupOwner->GetParent();
	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
		this);
}

void TongJNodeDialog::InsertItemToOnlineList(CString strMAC , CString strTEI , CString strAddress , CString strType)
{
	//ShowNetListView *pViewOnlineList=(ShowNetListView*)m_cSplitter.GetPane(0,1);//����OnCreate������
	pViewOnlineList->GetListCtrl().DeleteAllItems();
	pViewOnlineList->GetListCtrl().InsertColumn(0,_T("���"),LVCFMT_LEFT,50);
	pViewOnlineList->GetListCtrl().InsertColumn(1,_T("����MAC��ַ"),LVCFMT_LEFT,150);
	pViewOnlineList->GetListCtrl().InsertColumn(2,_T("TEI"),LVCFMT_CENTER,50);
	pViewOnlineList->GetListCtrl().InsertColumn(3,_T("ģ������"),LVCFMT_CENTER,200);
	CString strNumb;
	int n = 0;
	n = pViewOnlineList->GetListCtrl().GetItemCount();
	strNumb.Format(_T("%d") , n + 1);
	pViewOnlineList->GetListCtrl().InsertItem(n , strNumb);
	pViewOnlineList->GetListCtrl().SetItemText(n , 1 , strAddress);
	//pViewOnlineList->GetListCtrl().SetItemText(n , 1 , strMAC.Mid(0 , 2) + _T(":") + strMAC.Mid(2 , 2) + _T(":") + strMAC.Mid(4 , 2) + _T(":") + strMAC.Mid(6 , 2) + _T(":") + strMAC.Mid(8 , 2) + _T(":") + strMAC.Mid(10 , 2));
	pViewOnlineList->GetListCtrl().SetItemText(n , 2 , strTEI);
	//OnlineList.SetItemText(n , 3 , strAddress);
	//switch(_ttoi(strType))
	//{
	//case 1:
	//	break;
	//case 2:
	//	OnlineList.SetItemText(n , 4 , _T("�������ز�ģ��"));
	//	break;
	//case 3:
	//	break;
	//case 4:
	//	if (strMAC.Find(_T("BEBEBEBEBE")) != -1 )
	//	{
	//		OnlineList.SetItemText(n , 4 , _T("�������ز�ģ��"));
	//	} 
	//	else
	//	{
	//		OnlineList.SetItemText(n , 4 , _T("������ز�ģ��"));
	//	}
	//	break;
	//}
	pViewOnlineList->GetListCtrl().EnsureVisible(n,FALSE);
	pViewOnlineList->GetListCtrl().RedrawItems(n,n);
}

void TongJNodeDialog::InsertItemToLostList(CString strMAC)
{
	//ShowNetListView *pViewLostList=(ShowNetListView*)m_cSplitter.GetPane(0,2);//����OnCreate������
	pViewLostList->GetListCtrl().DeleteAllItems();
	pViewLostList->GetListCtrl().InsertColumn(0,_T("���"),LVCFMT_LEFT,50);
	pViewLostList->GetListCtrl().InsertColumn(1,_T("δ����MAC��ַ"),LVCFMT_LEFT,150);
	CString strNumb;
	int n = 0;
	n = pViewLostList->GetListCtrl().GetItemCount();
	strNumb.Format(_T("%d") , n + 1);
	pViewLostList->GetListCtrl().InsertItem(n , strNumb);
	pViewLostList->GetListCtrl().SetItemText(n , 1 ,strMAC);//n , 1 , strMAC.Mid(0 , 2) + _T(":") + strMAC.Mid(2 , 2) + _T(":") + strMAC.Mid(4 , 2) + _T(":") + strMAC.Mid(6 , 2) + _T(":") + strMAC.Mid(8 , 2) + _T(":") + strMAC.Mid(10 , 2));
	pViewLostList->GetListCtrl().EnsureVisible(n,FALSE);
	pViewLostList->GetListCtrl().RedrawItems(n,n);
}

void TongJNodeDialog::InsertItemToTreeList(CString strTableName)
{

	//pView=(ShowNetTreeView*)m_cSplitter.GetPane(0,0);//����OnCreate������
	pView->GetTreeCtrl().SetImageList(&m_imageList, TVSIL_NORMAL);
	pView->GetTreeCtrl().DeleteAllItems();
	CMainFrame* pMain= (CMainFrame*)AfxGetApp()->GetMainWnd();
	CString strTP_TIER = _T("");
	int nCeng = 15;//����15
	HTREEITEM m_hTree[500];
	CString strCeng = _T("");
	CString str_n = _T("");
	CString str_nodeNum = _T("");
	CString strAllDatalist[500][6];
	CString f_strDatalist[6][500];
	int nNumb = 0 , nAlldataNumb;
	int n = 0 , m = 0 , i = 0;
	m_access.SelectDataFromTable(pMain->m_PeiZhi_db/*_T(".\\�����ļ�\\HistTPShow.accdb")*/, strTableName , _T("TP_MAC,TP_TEI,TP_PTEI,TP_ROLE,TP_TIER,TP_READSUCCESS") ,_T("") ,m_strlist ,nAlldataNumb);
	if(nAlldataNumb>0){
		for(n = 0 ; n < nAlldataNumb ; n++)
		{
			m_tools.Split(m_strlist[n] , _T("$") ,strAllDatalist[n] , nNumb);
		}
		//��ȡ������Ϣ��
		for(n = 0 ; n < nAlldataNumb ; n++)
		{
			f_strDatalist[0][n]= strAllDatalist[n][0];//
			f_strDatalist[1][n]= strAllDatalist[n][1];
			f_strDatalist[2][n]= strAllDatalist[n][2];
			f_strDatalist[3][n]= strAllDatalist[n][3];
			f_strDatalist[4][n]= strAllDatalist[n][4];
			f_strDatalist[5][n]= strAllDatalist[n][5];
			strTP_TIER+=strAllDatalist[n][4] + _T("$");
		}
		//��ȡ�������㼶
		while(true)
		{
			strCeng.Format(_T("%d") , nCeng);
			if(strTP_TIER.Find(strCeng) != -1)
			{
				break;
			}
			nCeng-= 1;
		}
		str_nodeNum.Format(_T("%d") , nAlldataNumb-1);
		for(n = 0 ; n < nCeng ; n++)//ÿ�δ���һ��
		{
			for(m = 0 ; m < nAlldataNumb ; m++)
			{
		        str_n.Format(_T("%d") , n+1);
				if(f_strDatalist[4][m]==str_n){
					if(str_n==_T("1")){
						m_hTree[_ttoi(f_strDatalist[1][m])] = pView->GetTreeCtrl().InsertItem(_T("��TEI��")+f_strDatalist[1][m]+_T("��")+f_strDatalist[0][m]+_T("������STA������")+str_nodeNum+_T("��"), 0, 0);
					}
					else{
						m_hTree[_ttoi(f_strDatalist[1][m])]=pView->GetTreeCtrl().InsertItem(_T("��TEI��")+f_strDatalist[1][m]+_T("��")+f_strDatalist[0][m],n,n,m_hTree[_ttoi(f_strDatalist[2][m])],TVI_LAST);
					}
				}
			}
		}

		HTREEITEM hTreeItem=pView->GetTreeCtrl().GetRootItem();
		MyExpandTree(hTreeItem);

	}
}
void TongJNodeDialog::MyExpandTree(HTREEITEM hTreeItem)  
{  
	//hTreeItem=pView->GetTreeCtrl().GetRootItem();
    if(!pView->GetTreeCtrl().ItemHasChildren(hTreeItem))//������ؼ����ڵ�û���ӽڵ��򷵻�  
    {  
        return;  
    }  
    HTREEITEM hNextItem = pView->GetTreeCtrl().GetChildItem(hTreeItem);//�����ؼ��ĸ��ڵ����ӽڵ����ȡ���ڵ���ӽڵ�  
    while (hNextItem != NULL)//����  
    {  
        MyExpandTree(hNextItem);//�ݹ飬չ���ӽڵ��µ������ӽڵ�  
        hNextItem = pView->GetTreeCtrl().GetNextItem(hNextItem, TVGN_NEXT);//��ȡ���ڵ����һ���ӽڵ�  
    }  
    pView->GetTreeCtrl().Expand(hTreeItem,TVE_EXPAND);//չ���ڵ�  
} 