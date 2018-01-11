// MyFrameMsgTabCtrl.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "KD_Project.h"
#include "MyFrameMsgTabCtrl.h"
#include "MainFrm.h"
#include "SimJzq.h"
#include "GW13762.h"
#include "LogFile.h"
#include "CSG13762.h"
extern CLogFile plog;//������
extern CGW13762 Cgw13762;
extern CCSG13762 Ccsg13762;
extern CSimJzq  gSimJzq;
// CMyFrameMsgTabCtrl

IMPLEMENT_DYNAMIC(CMyFrameMsgTabCtrl, CTabCtrl)

CMyFrameMsgTabCtrl::CMyFrameMsgTabCtrl()
{
	//m_stat.Create(this);  
 //   m_stat.AddTool(GetDlgItem(IDC_BUTTON_MYBUTTON), _T("����Ҫ��ӵ���ʾ��Ϣ"));//.AddTool( GetDlgItem(IDC_BUTTON_MYBUTTON), "����Ҫ��ӵ���ʾ��Ϣ" ); 
	//m_stat.Activate(TRUE);
}

CMyFrameMsgTabCtrl::~CMyFrameMsgTabCtrl()
{
}


BEGIN_MESSAGE_MAP(CMyFrameMsgTabCtrl, CTabCtrl)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON_CMD, &CMyFrameMsgTabCtrl::OnBnClickedButtonCMD)
	ON_BN_CLICKED(IDC_BUTTON_DECODE, &CMyFrameMsgTabCtrl::OnBnClickedButtonDECODE)
	ON_BN_CLICKED(IDC_BUTTON_CLEARDECODE, &CMyFrameMsgTabCtrl::OnBnClickedButtonClearDECODE)
	ON_WM_RBUTTONDOWN(IDC_BUTTON_MYBUTTON, &CMyFrameMsgTabCtrl::OnBnClickedButtonDECODE)
END_MESSAGE_MAP()



// CMyFrameMsgTabCtrl ��Ϣ�������




int CMyFrameMsgTabCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CTabCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;
	//CTabCtrl *pTabCtrl = GetTabControl();     
	// TODO:  �ڴ������ר�õĴ�������
	//this->InsertItem
	//this-
	m_Font100K.CreatePointFont(90,_T(""));
	m_Font100H.CreatePointFont(95,_T(""));
	CRect rectDummy , rt;
	rectDummy.SetRectEmpty(); 

	m_ctrlMssage.Create(WS_CHILD|WS_VISIBLE|WS_BORDER|LVS_REPORT|LVS_OWNERDRAWFIXED,rectDummy,this,IDC_LISTXINXI);
	m_ctrlMssage.InsertColumn(0,_T("���"),LVCFMT_LEFT,60);
	m_ctrlMssage.InsertColumn(1,_T("����"),LVCFMT_LEFT,180);
	m_ctrlMssage.InsertColumn(2,_T("TEI��"),LVCFMT_CENTER,80);
	m_ctrlMssage.InsertColumn(3,_T("Э������"),LVCFMT_CENTER,130);
	m_ctrlMssage.InsertColumn(4,_T("�����й��ܵ���"),LVCFMT_CENTER,200);
	m_ctrlMssage.InsertColumn(5,_T("�������"),LVCFMT_CENTER,100);
	m_ctrlMssage.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	//m_ctrlMssage.m_nChooseList = 0;

	m_ctrlFrame.Create(WS_CHILD|WS_VISIBLE|WS_BORDER|LVS_REPORT|LVS_OWNERDRAWFIXED,rectDummy,this,IDC_LISTXINXI);
	m_ctrlFrame.GetWindowRect(rt);
	m_ctrlFrame.InsertColumn(0,_T("ʱ��"),LVCFMT_LEFT,160);
	m_ctrlFrame.InsertColumn(1,_T("�շ�"),LVCFMT_LEFT,50);
	m_ctrlFrame.InsertColumn(2,_T("����"),LVCFMT_LEFT,1200);
	m_ctrlFrame.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_ctrlFrame.ShowWindow(SW_HIDE);
	m_ctrlFrame.m_nChooseList = 1;
	m_button=new CButton();
	m_checkboxbutton=new CButton();
	m_DecodeButton=new CButton();
	m_ClearDecodeButton=new CButton();
	//m_editMLH =new CEdit();//(CEdit*)GetDlgItem(IDC_EDIT_MSG);
	//m_editRec =new CEdit();
	//DWORD dwStyle = ::GetWindowLong(m_editMLH->GetSafeHwnd(), GWL_STYLE);
 //   dwStyle |= ES_NUMBER;
 //   ::SetWindowLong(m_editMLH->GetSafeHwnd(), GWL_STYLE, dwStyle);
	//m_editMLH->Create(WS_CHILD|ES_MULTILINE|ES_WANTRETURN, rectDummy, this,IDC_EDIT_MSG);
	//m_editMLH->LineScroll(m_editMLH->GetLineCount()); 
	//m_editRec->Create(WS_CHILD, rectDummy, this,IDC_EDIT_REC2);
	//m_editMLH->SetWindowTextW(_T("12\n12"));
	//m_editMLH->SetSel(-1,-1);
 //   m_editMLH->ReplaceSel(_T("12\n12r\n"));
	//m_editRec->SetWindowTextW(_T("12\n12"));
	//m_button->Create();
	m_checkboxbutton->Create(_T("16����"), WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX , rectDummy, this, IDC_BUTTON_MYCHECKBOX );
	m_MYButton.Create(_T("����"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, rectDummy, this, IDC_BUTTON_MYBUTTON ); //������ť
	m_button->Create(_T("����"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, rectDummy, this, IDC_BUTTON_CMD ); //������ť
	m_cmdedit_send.Create(WS_CHILD|ES_MULTILINE|ES_WANTRETURN|WS_VISIBLE|WS_BORDER|ES_AUTOVSCROLL, rectDummy, this,IDC_EDIT_CMD);
	m_cmdedit_rec.Create(ES_MULTILINE|ES_AUTOVSCROLL|WS_BORDER|ES_WANTRETURN, rectDummy, this,IDC_EDIT_CMD_REC);
	m_button->SetFont(&m_Font100K);
	m_cmdedit_send.ShowWindow(SW_HIDE);
	m_cmdedit_rec.ShowWindow(SW_HIDE);
	m_cmdedit_send.SetFont(&m_Font100H);
	m_cmdedit_rec.SetFont(&m_Font100H);
	m_cmdedit_rec.ShowScrollBar(1);
	m_button->ShowWindow(SW_HIDE);
	m_MYButton.ShowWindow(SW_HIDE);
	//m_cmdedit_send.SetWindowTextW(_T(" ��'Shift'���ɷ���"));


	m_ClearDecodeButton->Create(_T("���"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, rectDummy, this, IDC_BUTTON_CLEARDECODE ); //������ť
	m_DecodeButton->Create(_T("����"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, rectDummy, this, IDC_BUTTON_DECODE ); //������ť
	m_cmdedit_Code.Create(WS_CHILD|ES_MULTILINE|ES_WANTRETURN|WS_VISIBLE|WS_BORDER|ES_AUTOVSCROLL, rectDummy, this,IDC_EDIT_CODE);
	m_cmdedit_Decode.Create(ES_MULTILINE|ES_AUTOVSCROLL|WS_BORDER|ES_WANTRETURN, rectDummy, this,IDC_EDIT_DECODE);
	m_cmdedit_Code.ShowWindow(SW_HIDE);
	m_cmdedit_Decode.ShowWindow(SW_HIDE);
	m_cmdedit_Code.ShowScrollBar(1);
	m_cmdedit_Code.SetFont(&m_Font100H);
	m_cmdedit_Decode.SetFont(&m_Font100H);
	m_cmdedit_Decode.ShowScrollBar(1);
	m_DecodeButton->ShowWindow(SW_HIDE);
	m_ClearDecodeButton->ShowWindow(SW_HIDE);
	m_DecodeButton->SetFont(&m_Font100K);
	m_ClearDecodeButton->SetFont(&m_Font100K);
	m_checkboxbutton->SetFont(&m_Font100K);
	m_checkboxbutton->ShowWindow(SW_HIDE);
	//m_MYButton.SubclassDlgItem(IDC_BUTTON_MYBUTTON,this);

	m_stat.Create(this);  
    //m_stat.AddTool(GetDlgItem(IDC_BUTTON_MYBUTTON), _T("����Ҫ��ӵ���ʾ��Ϣ/n ��һ��"));//.AddTool( GetDlgItem(IDC_BUTTON_MYBUTTON), "����Ҫ��ӵ���ʾ��Ϣ" ); 
	m_stat.SetDelayTime(0); //�����ӳ٣����Ϊ0�򲻵ȴ���������ʾ
    //m_stat.SetTipTextColor( RGB(0,0,255) ); //������ʾ�ı�����ɫ
    //m_stat.SetTipBkColor( RGB(255,255,255)); //������ʾ��ı�����ɫ
    
	//m_stat.SetTipTextColor( RGB(0,25,34) ); //������ʾ�ı�����ɫ  ������ɫû����
    //m_stat.SetTipBkColor( RGB(233,34,55)); //������ʾ��ı�����ɫ
	m_stat.AddTool(GetDlgItem(IDC_BUTTON_MYBUTTON), _T("����Ҫ��ӵ���ʾ��Ϣ\n��һ��\n��һ��\n��һ��\n��һ��\n��һ��"));
	m_stat.AddTool(GetDlgItem(IDC_BUTTON_CMD), _T("��෢�Ϳ�\n�Ҳ���տ�\n��shift���ɷ���"));
	m_stat.AddTool(GetDlgItem(IDC_EDIT_CMD), _T("���ʹ���\n��shift���ɷ���"));
	m_stat.AddTool(GetDlgItem(IDC_EDIT_CMD_REC), _T("���մ���"));
	m_stat.AddTool(GetDlgItem(IDC_EDIT_CODE), _T("�������֡�Ĵ���"));
	m_stat.AddTool(GetDlgItem(IDC_EDIT_DECODE), _T("�����������"));
	m_stat.SetMaxTipWidth(600);
	//m_stat.Activate(TRUE);
	return 0;
}


void CMyFrameMsgTabCtrl::OnSize(UINT nType, int cx, int cy)
{
	CTabCtrl::OnSize(nType, cx, cy);
	CRect rectClient;
	GetClientRect(rectClient); 
	//m_editMLH->SetWindowPos(NULL, rectClient.left + 1, rectClient.top  + 25, rectClient.Width()/2, rectClient.Height()-25, SWP_NOACTIVATE | SWP_NOZORDER);
	//m_editRec->SetWindowPos(NULL, rectClient.left+rectClient.Width()/2+10, rectClient.top  + 25, rectClient.Width()/2-20, rectClient.Height()  - 25, SWP_NOACTIVATE | SWP_NOZORDER);
	m_button->SetWindowPos(NULL, rectClient.left+1, rectClient.top  + 30, 50, 25, SWP_NOACTIVATE | SWP_NOZORDER);
	m_cmdedit_send.SetWindowPos(NULL, rectClient.left + 85, rectClient.top  + 30, rectClient.Width()/2-70, rectClient.Height()-25, SWP_NOACTIVATE | SWP_NOZORDER);
	m_cmdedit_rec.SetWindowPos(NULL, rectClient.left+rectClient.Width()/2+25, rectClient.top  + 30, rectClient.Width()/2-100, rectClient.Height()  - 25, SWP_NOACTIVATE | SWP_NOZORDER);
	m_ctrlMssage.SetWindowPos(NULL, rectClient.left + 5, rectClient.top  + 30, rectClient.Width() - 2, rectClient.Height()  - 25, SWP_NOACTIVATE | SWP_NOZORDER);
	m_ctrlFrame.SetWindowPos(NULL, rectClient.left + 5, rectClient.top  + 30, rectClient.Width() - 2, rectClient.Height()  - 25, SWP_NOACTIVATE | SWP_NOZORDER);


	m_checkboxbutton->SetWindowPos(NULL, rectClient.left+1, rectClient.top  +75, 75, 25, SWP_NOACTIVATE | SWP_NOZORDER);
	m_DecodeButton->SetWindowPos(NULL, rectClient.left+1, rectClient.top+30, 50, 25, SWP_NOACTIVATE | SWP_NOZORDER);
	m_cmdedit_Code.SetWindowPos(NULL, rectClient.left + 60, rectClient.top  + 30, rectClient.Width()/2-40, rectClient.Height()-25, SWP_NOACTIVATE | SWP_NOZORDER);
	m_cmdedit_Decode.SetWindowPos(NULL, rectClient.left+rectClient.Width()/2+25, rectClient.top  + 30, rectClient.Width()/2-100, rectClient.Height()  - 25, SWP_NOACTIVATE | SWP_NOZORDER);
	m_ClearDecodeButton->SetWindowPos(NULL, rectClient.right-60, rectClient.top  + 30, 50, 25, SWP_NOACTIVATE | SWP_NOZORDER);
	// TODO: �ڴ˴������Ϣ����������
	m_MYButton.SetWindowPos(NULL, rectClient.left+1, rectClient.top  + 105, 60, 25, SWP_NOACTIVATE | SWP_NOZORDER);
}
void CMyFrameMsgTabCtrl::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch(GetCurSel())
	{
	case 0:
		m_ctrlMssage.ShowWindow(SW_SHOW);
		m_ctrlFrame.ShowWindow(SW_HIDE);
		m_checkboxbutton->ShowWindow(SW_HIDE);
		//m_editMLH->ShowWindow(SW_HIDE);
		//m_editRec->ShowWindow(SW_HIDE);
		m_button->ShowWindow(SW_HIDE);
		m_cmdedit_send.ShowWindow(SW_HIDE);
		m_cmdedit_rec.ShowWindow(SW_HIDE);

		m_DecodeButton->ShowWindow(SW_HIDE);
		m_cmdedit_Code.ShowWindow(SW_HIDE);
		m_cmdedit_Decode.ShowWindow(SW_HIDE);

		m_ClearDecodeButton->ShowWindow(SW_HIDE);


		m_MYButton.ShowWindow(SW_HIDE);

		break;
	case 1:
		m_checkboxbutton->ShowWindow(SW_HIDE);
		m_ctrlMssage.ShowWindow(SW_HIDE);
		m_ctrlFrame.ShowWindow(SW_SHOW);
		//m_editMLH->ShowWindow(SW_HIDE);
		//m_editRec->ShowWindow(SW_HIDE);
		m_button->ShowWindow(SW_HIDE);
		m_cmdedit_send.ShowWindow(SW_HIDE);
		m_cmdedit_rec.ShowWindow(SW_HIDE);

		m_ClearDecodeButton->ShowWindow(SW_HIDE);
		m_DecodeButton->ShowWindow(SW_HIDE);
		m_cmdedit_Code.ShowWindow(SW_HIDE);
		m_cmdedit_Decode.ShowWindow(SW_HIDE);

		m_MYButton.ShowWindow(SW_HIDE);
		break;
	case 2:
		m_button->ShowWindow(SW_SHOW);
		m_checkboxbutton->ShowWindow(SW_SHOW);
		m_ctrlMssage.ShowWindow(SW_HIDE);
		m_ctrlFrame.ShowWindow(SW_HIDE);
		//m_editMLH->ShowWindow(SW_SHOW);
		//m_editRec->ShowWindow(SW_SHOW);
		m_cmdedit_send.ShowWindow(SW_SHOW);
		m_cmdedit_rec.ShowWindow(SW_SHOW);

		m_ClearDecodeButton->ShowWindow(SW_SHOW);
		m_DecodeButton->ShowWindow(SW_HIDE);
		m_cmdedit_Code.ShowWindow(SW_HIDE);
		m_cmdedit_Decode.ShowWindow(SW_HIDE);

		m_MYButton.ShowWindow(SW_HIDE);
		
		break;
	case 3:
				m_checkboxbutton->ShowWindow(SW_HIDE);
		m_button->ShowWindow(SW_HIDE);
		m_ctrlMssage.ShowWindow(SW_HIDE);
		m_ctrlFrame.ShowWindow(SW_HIDE);
		//m_editMLH->ShowWindow(SW_SHOW);
		//m_editRec->ShowWindow(SW_SHOW);
		m_cmdedit_send.ShowWindow(SW_HIDE);
		m_cmdedit_rec.ShowWindow(SW_HIDE);
		m_ClearDecodeButton->ShowWindow(SW_SHOW);
		m_DecodeButton->ShowWindow(SW_SHOW);
		m_cmdedit_Code.ShowWindow(SW_SHOW);
		
		m_cmdedit_Decode.ShowWindow(SW_SHOW);

		m_MYButton.ShowWindow(SW_HIDE);
		
      break;
	}
	CTabCtrl::OnLButtonUp(nFlags, point);
}



  DWORD WINAPI ThreadSendCMD (PVOID pParam) 
{
	CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CMyFrameMsgTabCtrl * pView = (CMyFrameMsgTabCtrl *)pParam;
	INT8U ack = DACK_FAILURE;
	INT8U recvbuf[D376_MAXRCVBUFLEN];
	INT16U recvbuflen=0;
	sPartQGDW376_2CreatFrame sQGDW376_2HostFrame;
	sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
	CString mStr;
	INT8U pa[200]; 
	INT16U  temp16=0;
    pMain->m_FrameShowWnd.m_myTabCtrl.m_cmdedit_send.GetWindowText(mStr);
	if(pMain->m_FrameShowWnd.m_myTabCtrl.m_checkboxbutton->GetCheck()==1){
	     pView->Tools._str16tobuf16( mStr, pa , temp16 , false);
	     gSimJzq.SendBufToCom(pa,temp16);
    }
    else{
	   unsigned char s[1024];
	   int n=mStr.GetLength();
	   memcpy(s, (unsigned char *)mStr.GetBuffer(0), mStr.GetLength()*2); 
	   for(int j=0,i=0;j<n;i++,j++){
		pa[j]=s[i];
		i++;
	   }

	   gSimJzq.SendBufToCom(pa,n);
    }
	gSimJzq.GetCOMM376_2ToBuf(D376_MAXRCVBUFLEN , 5*1000 , 50 , recvbuf , recvbuflen);
	if(recvbuflen>0)
	{
		int nItem = 0;
	    CString m_recStr=pMain->m_tools._buf16tostr16(recvbuf , recvbuflen , true);
	   	CString strEditXianshi;
		pMain->m_FrameShowWnd.m_myTabCtrl.m_cmdedit_rec.GetWindowText(strEditXianshi);
		pMain->m_FrameShowWnd.m_myTabCtrl.m_cmdedit_rec.SetSel(strEditXianshi.GetLength(),strEditXianshi.GetLength());
		pMain->m_FrameShowWnd.m_myTabCtrl.m_cmdedit_rec.ReplaceSel(m_recStr);


		ack = Cgw13762.Decode376_2Frame(recvbuf,recvbuflen,DstDecodeDataFrame);
		plog.saveLog_HexBuf(DATA_FILE,INPUT_DATA,recvbuf,recvbuflen);//��ӡ����֡����
		nItem = pMain->m_FrameShowWnd.m_myTabCtrl.m_ctrlFrame.GetItemCount();
		pMain->m_FrameShowWnd.m_myTabCtrl.m_ctrlFrame.InsertItem( nItem,pMain-> m_strSysDateTime);
		pMain->m_FrameShowWnd.m_myTabCtrl.m_ctrlFrame.SetItemText(nItem , 1, _T("����<<"));
		pMain->m_FrameShowWnd.m_myTabCtrl.m_ctrlFrame.SetItemText(nItem , 2 , pMain->m_tools._buf16tostr16(recvbuf , recvbuflen , true));
		pMain->m_FrameShowWnd.m_myTabCtrl.m_ctrlFrame.EnsureVisible(nItem,FALSE);
		pMain->m_FrameShowWnd.m_myTabCtrl.m_ctrlFrame.RedrawItems(nItem,nItem);
		if(ack == DACK_SUCESS)
		{
			plog.saveInformation_rev(DstDecodeDataFrame);
		}
		else
		{
		    plog.saveLog_err(DATA_FILE,NOTIME,_T(""),DACK_ERR_FORMAT);
		}
	}
	else{
		CString strEditXianshi;
		pMain->m_FrameShowWnd.m_myTabCtrl.m_cmdedit_rec.GetWindowText(strEditXianshi);
		pMain->m_FrameShowWnd.m_myTabCtrl.m_cmdedit_rec.SetSel(strEditXianshi.GetLength(),strEditXianshi.GetLength());
		pMain->m_FrameShowWnd.m_myTabCtrl.m_cmdedit_rec.ReplaceSel(_T("û���յ�����"));
	}

	//switch(ack)
	//{
	//case 0:
	//	pView->ShowZuzhenData();
	//	break;
	//case 0x13://ʧ��
	//	pView->SetWindowText(_T("ͨѶʧ�ܣ�����\r\n"));
	//	break;
	//case 0x30://SEQ��һ��
	//	pView->ShowZuzhenData(ack);
	//	break;
	//case 0x0A://���ڵ㲻֧�ִ�����
	//	pView->SetWindowText(_T("���ڵ㲻֧�ִ��������\r\n"));
	//	break;
	//default:
	//	pView->SetWindowText(_T("�������󣡣���\r\n"));
	//	break;
	//}
	pMain->m_FrameShowWnd.m_myTabCtrl.m_button->EnableWindow(TRUE);
	return 0;
}

BOOL CMyFrameMsgTabCtrl::PreTranslateMessage(MSG* pMsg) //�ı���Ӧenter��
{
  CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
	INT8U ack = DACK_FAILURE;
	INT8U recvbuf[D376_MAXRCVBUFLEN];
	INT16U recvbuflen=0;
	sPartQGDW376_2CreatFrame sQGDW376_2HostFrame;
	sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
	int nItem = 0;
   //TODO: Add your specialized code here and/or call the base class
  if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_SHIFT //shift��Ϣ
    && pMsg->hwnd == m_cmdedit_send.GetSafeHwnd())//����m_TestEdit�ؼ�
  {
		CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();

		CString strMessageAddress;
		pMain->m_bCommunictStop = false;
		if (pMain->m_bConnected == TRUE)
		{

				m_button->EnableWindow(FALSE);
				m_hCMDThread=CreateThread (NULL,0,ThreadSendCMD,this,0,NULL);
				CloseHandle(m_hCMDThread);
		}
		else
		{
			AfxMessageBox(_T("��򿪴��ڣ�"));
		}
  }
 

 if( pMsg->message == WM_MOUSEWHEEL )//�����¼�
 {
		  short zDelta = (short)HIWORD(pMsg->wParam);  
		  short xPos   = (short)LOWORD(pMsg->lParam);   
		  short yPos   = (short)HIWORD(pMsg->lParam);  
		  CPoint pt;
		  GetCursorPos(&pt);
		  ScreenToClient(&pt);
		  if( m_cmdedit_rec.GetSafeHwnd())
		  {
		   CRect rectControl;
		   m_cmdedit_rec.GetWindowRect(&rectControl);
		   ScreenToClient(&rectControl);
		   if( rectControl.PtInRect(pt) )
		   {
			int lineIndex = m_cmdedit_rec.LineFromChar();
			if( zDelta < 0 )
			{
			 lineIndex += 1;
			}
			else
			{
			 lineIndex -= 1;
			}
			int charindex = m_cmdedit_rec.LineIndex(lineIndex);
			m_cmdedit_rec.SetSel(charindex,charindex);
		   }
		   return TRUE;
		  }
 }
   m_stat.RelayEvent(pMsg); 
   return CWnd::PreTranslateMessage(pMsg);

}

// HBRUSH CMyFrameMsgTabCtrl::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
//{
//        HBRUSH hbr = CMyFrameMsgTabCtrl::OnCtlColor(pDC,pWnd,nCtlColor);
//        //CString strText = _T("");
//		const char * strtext="";
//        if(strcmp((const char *)strtext,"123")==0 || strcmp(strtext,"������")==0)
//			//��ɫ
//			pDC->SetBkColor(RGB(0,0,255));
//        else
//           pDC->SetTextColor(RGB(0,0,255));   //��ɫ
//         return hbr;
//}


 void CMyFrameMsgTabCtrl::OnBnClickedButtonCMD()//������
{
	CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();

	CString strMessageAddress;
	pMain->m_bCommunictStop = false;
	if (pMain->m_bConnected == TRUE)
	{

			m_button->EnableWindow(FALSE);
			m_hCMDThread=CreateThread (NULL,0,ThreadSendCMD,this,0,NULL);
            CloseHandle(m_hCMDThread);
	}
	else
	{
		AfxMessageBox(_T("��򿪴��ڣ�"));
	}
}
 void CMyFrameMsgTabCtrl::OnBnClickedButtonDECODE(){//376.2Э�����
	CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();

	INT8U ack = DACK_FAILURE;
	INT8U recvbuf[D376_MAXRCVBUFLEN];
	INT16U recvbuflen=0;

	sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
	sPartQCSG376_2DeCodeFrame DstDecodeDataFrameNW;
	CString mStr;
    pMain->m_FrameShowWnd.m_myTabCtrl.m_cmdedit_Code.GetWindowText(mStr);
	Tools._str16tobuf16(mStr , recvbuf , recvbuflen);

	ack = Cgw13762.Decode376_2Frame(recvbuf,recvbuflen,DstDecodeDataFrame);
	if(ack==DACK_SUCESS){
		appendText(&m_cmdedit_Decode,_T("---------------------------------------------------------------------------------------------"));
		appendText(&m_cmdedit_Decode,_T("<----������376.2֡��ʽ�������������£�---->"));
		appendText(&m_cmdedit_Decode,_T(""));
		appendText(&m_cmdedit_Decode,_T("������:�� ")+Tools._buf16tostr16(&DstDecodeDataFrame.s_head.u_con.s_conByte,1, true)+_T(" ��"));
		if(DstDecodeDataFrame.s_head.u_con.s_conBit.s_Con_DIR==0){
		    appendText(&m_cmdedit_Decode,_T("          ���䷽��λDIR:[ 0 ]  ���������������б���"));
		}
		else if(DstDecodeDataFrame.s_head.u_con.s_conBit.s_Con_DIR==1){
			appendText(&m_cmdedit_Decode,_T("          ���䷽��λDIR:[ 1 ]  ��ͨ��ģ�鷢�������б���"));
		}
		if(DstDecodeDataFrame.s_head.u_con.s_conBit.s_Con_DIR==0){
		    appendText(&m_cmdedit_Decode,_T("          ������־λPRM:[ 0 ]  �������ԴӶ�վ"));
		}
		else if(DstDecodeDataFrame.s_head.u_con.s_conBit.s_Con_DIR==1){
			appendText(&m_cmdedit_Decode,_T("          ������־λPRM:[ 1 ]  ������������վ"));
		}
	    if(DstDecodeDataFrame.s_head.u_con.s_conBit.s_Con_ComMode==3){
		    appendText(&m_cmdedit_Decode,_T("          ͨ�ŷ�ʽ:[ 3 ]  ����ز�ͨ��"));
		}
		else if(DstDecodeDataFrame.s_head.u_con.s_conBit.s_Con_ComMode==2){
		    appendText(&m_cmdedit_Decode,_T("          ͨ�ŷ�ʽ:[ 2 ]  �ֲ�ʽ·���ز�ͨ��"));
		}
		else if(DstDecodeDataFrame.s_head.u_con.s_conBit.s_Con_ComMode==1){
		    appendText(&m_cmdedit_Decode,_T("          ͨ�ŷ�ʽ:[ 1 ]  ����ʽ·���ز�ͨ��"));
		}
		else if(DstDecodeDataFrame.s_head.u_con.s_conBit.s_Con_ComMode==10){
		    appendText(&m_cmdedit_Decode,_T("          ͨ�ŷ�ʽ:[ 10 ]  ΢��������ͨ��"));
		}
		else if(DstDecodeDataFrame.s_head.u_con.s_conBit.s_Con_ComMode==1){
		    appendText(&m_cmdedit_Decode,_T("          ͨ�ŷ�ʽ:[ 20 ]  ��̫��ͨ��"));
		}
		else{
		    appendText(&m_cmdedit_Decode,_T("          ͨ�ŷ�ʽ:[ ] δ֪ͨ�ŷ�ʽ"));
		}

		appendText(&m_cmdedit_Decode,_T(""));
		appendText(&m_cmdedit_Decode,_T("��Ϣ��:�� ")+Tools._buf16tostr16(DstDecodeDataFrame.s_head.u_msg.s_msgbuf,5, true)+Tools._buf16tostr16(&DstDecodeDataFrame.s_head.s_Msg_Seq,1, true)+_T(" ��"));
		if(DstDecodeDataFrame.s_head.u_con.s_conBit.s_Con_DIR==0){
		    //appendText(&m_cmdedit_Decode,_T("          ���䷽��λDIR:[ 0 ]  ���������������б���"));
			if(DstDecodeDataFrame.s_head.u_msg.s_DownMsgBit.s_Msg_RouterFlag==0){
				appendText(&m_cmdedit_Decode,_T("          ·�ɱ�ʶ:[ 0 ]  ͨ��ģ���·�ɻ�����·��ģʽ"));
			}
			else if(DstDecodeDataFrame.s_head.u_msg.s_DownMsgBit.s_Msg_RouterFlag==1){
				appendText(&m_cmdedit_Decode,_T("          ·�ɱ�ʶ:[ 1 ]  ͨ��ģ�鲻��·�ɻ�������·ģʽ"));
			}
			if(DstDecodeDataFrame.s_head.u_msg.s_DownMsgBit.s_reserved_1==0){
				appendText(&m_cmdedit_Decode,_T("          �����ڵ��ʶ:[ 0 ]  �޸��ӽڵ�"));
			}
			else if(DstDecodeDataFrame.s_head.u_msg.s_DownMsgBit.s_reserved_1==1){
				appendText(&m_cmdedit_Decode,_T("          �����ڵ��ʶ:[ 1 ]  �и��ӽڵ�"));
			}
			if(DstDecodeDataFrame.s_head.u_msg.s_DownMsgBit.s_Msg_ComFlag==0){
				appendText(&m_cmdedit_Decode,_T("          ͨ��ģ���ʶ:[ 0 ]  �����ڵ�Ĳ���"));
			}
			else if(DstDecodeDataFrame.s_head.u_msg.s_DownMsgBit.s_Msg_ComFlag==1){
				appendText(&m_cmdedit_Decode,_T("          ͨ��ģ���ʶ:[ 1 ]  �Դӽڵ����"));
			}
			if(DstDecodeDataFrame.s_head.u_msg.s_DownMsgBit.s_reserved_2==0){
				appendText(&m_cmdedit_Decode,_T("          �м̼���:[ 0 ]  ���м�"));
			}
			else if(DstDecodeDataFrame.s_head.u_msg.s_DownMsgBit.s_reserved_2!=0){
						CString strNumb;
						int n = DstDecodeDataFrame.s_head.u_msg.s_DownMsgBit.s_reserved_2;
                        strNumb.Format(_T("%d") , n);
				appendText(&m_cmdedit_Decode,_T("          �м̼���:[ ")+ strNumb+_T("] ���м�"));
			}
			if(DstDecodeDataFrame.s_head.u_msg.s_DownMsgBit.s_chanle_num==0){
				appendText(&m_cmdedit_Decode,_T("          �ŵ���ʶ:[ 0 ]  �����ŵ�"));
			}
			else if(DstDecodeDataFrame.s_head.u_msg.s_DownMsgBit.s_chanle_num!=0){
						CString strNumb;
						int n = DstDecodeDataFrame.s_head.u_msg.s_DownMsgBit.s_chanle_num;
                        strNumb.Format(_T("%d") , n);
				appendText(&m_cmdedit_Decode,_T("          �ŵ���ʶ:[ ")+ strNumb+_T("] ���ŵ�"));
			}
			appendText(&m_cmdedit_Decode,_T("          ֡���к�:[ ")+Tools._buf16tostr16(&DstDecodeDataFrame.s_head.s_Msg_Seq,1, true)+_T("]"));
		}
		else if(DstDecodeDataFrame.s_head.u_con.s_conBit.s_Con_DIR==1){
			//appendText(&m_cmdedit_Decode,_T("          ���䷽��λDIR:[ 1 ]  ��ͨ��ģ�鷢�������б���"));
			if(DstDecodeDataFrame.s_head.u_msg.s_UpMsgBit.s_Msg_RouterFlag==0){
				appendText(&m_cmdedit_Decode,_T("          ·�ɱ�ʶ:[ 0 ]  ͨ��ģ���·�ɻ�����·��ģʽ"));
			}
			else if(DstDecodeDataFrame.s_head.u_msg.s_UpMsgBit.s_Msg_RouterFlag==1){
				appendText(&m_cmdedit_Decode,_T("          ·�ɱ�ʶ:[ 1 ]  ͨ��ģ�鲻��·�ɻ�������·ģʽ"));
			}
			if(DstDecodeDataFrame.s_head.u_msg.s_UpMsgBit.s_reserved_1==0){
				appendText(&m_cmdedit_Decode,_T("          �����ڵ��ʶ:[ 0 ]  �޸��ӽڵ�"));
			}
			else if(DstDecodeDataFrame.s_head.u_msg.s_UpMsgBit.s_reserved_1==1){
				appendText(&m_cmdedit_Decode,_T("          �����ڵ��ʶ:[ 1 ]  �и��ӽڵ�"));
			}
			if(DstDecodeDataFrame.s_head.u_msg.s_UpMsgBit.s_Msg_ComFlag==0){
				appendText(&m_cmdedit_Decode,_T("          ͨ��ģ���ʶ:[ 0 ]  �����ڵ�Ĳ���"));
			}
			else if(DstDecodeDataFrame.s_head.u_msg.s_UpMsgBit.s_Msg_ComFlag==1){
				appendText(&m_cmdedit_Decode,_T("          ͨ��ģ���ʶ:[ 1 ]  �Դӽڵ����"));
			}
			if(DstDecodeDataFrame.s_head.u_msg.s_UpMsgBit.s_reserved_2==0){
				appendText(&m_cmdedit_Decode,_T("          �м̼���:[ 0 ]  ���м�"));
			}
			else if(DstDecodeDataFrame.s_head.u_msg.s_UpMsgBit.s_reserved_2!=0){
						CString strNumb;
						int n = DstDecodeDataFrame.s_head.u_msg.s_DownMsgBit.s_reserved_2;
                        strNumb.Format(_T("%d") , n);
				appendText(&m_cmdedit_Decode,_T("          �м̼���:[ ")+ strNumb+_T("] ���м�"));
			}
			//s_Msg_phase:       
			if(DstDecodeDataFrame.s_head.u_msg.s_UpMsgBit.s_chanle_num==0){
				appendText(&m_cmdedit_Decode,_T("          �ŵ���ʶ:[ 0 ]  �����ŵ�"));
			}
			else if(DstDecodeDataFrame.s_head.u_msg.s_UpMsgBit.s_chanle_num!=0){
						CString strNumb;
						int n = DstDecodeDataFrame.s_head.u_msg.s_UpMsgBit.s_chanle_num;
                        strNumb.Format(_T("%d") , n);
				appendText(&m_cmdedit_Decode,_T("          �ŵ���ʶ:[ ")+ strNumb+_T("] ���ŵ�"));
			}
			if(DstDecodeDataFrame.s_head.u_msg.s_UpMsgBit.s_Msg_phase==0){
				appendText(&m_cmdedit_Decode,_T("          ʵ�����߱�ʶ:[ 0 ]  ��ȷ��"));
			}
			else if(DstDecodeDataFrame.s_head.u_msg.s_UpMsgBit.s_Msg_phase!=0){
						CString strNumb;
						int n = DstDecodeDataFrame.s_head.u_msg.s_UpMsgBit.s_Msg_phase;
                        strNumb.Format(_T("%d") , n);
				appendText(&m_cmdedit_Decode,_T("          ʵ�����߱�ʶ:[ ")+ strNumb+_T("] ������"));
			}

//s_Meter_flag:  
			if(DstDecodeDataFrame.s_head.u_msg.s_UpMsgBit.s_Meter_flag==0){
				appendText(&m_cmdedit_Decode,_T("          ���ͨ������:[ 0 ]  ����"));
			}
			else if(DstDecodeDataFrame.s_head.u_msg.s_UpMsgBit.s_Meter_flag==1){
				appendText(&m_cmdedit_Decode,_T("          ���ͨ������:[ 1 ]  �����ŵ�Ϊ���๩�磬�߼��ŵ�Ϊ���ŵ�"));
			}
			else if(DstDecodeDataFrame.s_head.u_msg.s_UpMsgBit.s_Meter_flag==2){
				appendText(&m_cmdedit_Decode,_T("          ���ͨ������:[ 2 ]  �����ŵ�Ϊ���๩�磬�߼��ŵ�Ϊ���ŵ�"));
			}
			else if(DstDecodeDataFrame.s_head.u_msg.s_UpMsgBit.s_Meter_flag==3){
				appendText(&m_cmdedit_Decode,_T("          ���ͨ������:[ 3 ]  �����ŵ�Ϊ���๩�磬�߼��ŵ�Ϊ���ŵ�"));
			}
			else if(DstDecodeDataFrame.s_head.u_msg.s_UpMsgBit.s_Meter_flag==4){
				appendText(&m_cmdedit_Decode,_T("          ���ͨ������:[ 4 ]  �����ŵ�Ϊ���๩�磬�߼��ŵ�Ϊ���ŵ�"));
			}
//s_CmdCsq
			if(DstDecodeDataFrame.s_head.u_msg.s_UpMsgBit.s_CmdCsq==0){
				appendText(&m_cmdedit_Decode,_T("          �ź�Ʒ��:[ 0 ]  ���ź�Ʒ��"));
			}
			else if(DstDecodeDataFrame.s_head.u_msg.s_UpMsgBit.s_CmdCsq!=0){
						CString strNumb;
						int n = DstDecodeDataFrame.s_head.u_msg.s_UpMsgBit.s_CmdCsq;
                        strNumb.Format(_T("%d") , n);
				appendText(&m_cmdedit_Decode,_T("          �ź�Ʒ��:[ ")+ strNumb+_T("] 1��ʾ���Ʒ�� 1-15"));
			}
			//s_Msg_Event
			if(DstDecodeDataFrame.s_head.u_msg.s_UpMsgBit.s_Msg_Event==0){
				appendText(&m_cmdedit_Decode,_T("          �¼���־:[ 0 ]  ���ϱ��¼�"));
			}
			else if(DstDecodeDataFrame.s_head.u_msg.s_UpMsgBit.s_Msg_Event==1){
				appendText(&m_cmdedit_Decode,_T("          �¼���־:[ 1 ]  ���ϱ��¼�"));
			}
			appendText(&m_cmdedit_Decode,_T("          ֡���к�:[ ")+Tools._buf16tostr16(&DstDecodeDataFrame.s_head.s_Msg_Seq,1, true)+_T("]"));

		}	

		//appendText(&m_cmdedit_Decode,_T(""));
		//appendText(&m_cmdedit_Decode,_T("��Ϣ��:�� ")+Tools._buf16tostr16(DstDecodeDataFrame.s_head.u_msg.s_msgbuf,5, true)+Tools._buf16tostr16(&DstDecodeDataFrame.s_head.s_Msg_Seq,1, true)+_T(" ��"));
		appendText(&m_cmdedit_Decode,_T(""));
		appendText(&m_cmdedit_Decode,_T("Ӧ�ù�����AFN:�� ")+Tools._buf16tostr16(&DstDecodeDataFrame.s_head.s_AFN,1, true)+_T(" ��"));
		//appendText(&m_cmdedit_Decode,_T("���ݵ�Ԫ��ʶFN:�� ")+Tools._buf16tostr16(DstDecodeDataFrame.s_head.s_FN,2, true)+_T(" ��"));
		//appendText(&m_cmdedit_Decode,_T("����������:"));
	//		CMainFrame* pMainDlg= (CMainFrame*)AfxGetApp()->GetMainWnd();
		UINT8 a_Fn;//=(UINT8)sQGDW376_2HostFrame.s_head.s_FN;
		//INT8U pRbuf[6]={0,0,0,0,0,0};
		INT8U S;
		ST_Fn pstFn;
		S=(UINT8)(DstDecodeDataFrame.s_head.s_FN);
		(&pstFn)->DT1=S;
		(&pstFn)->DT2=DstDecodeDataFrame.s_head.s_FN>>8;
		a_Fn=pMain->getFn(pstFn);
		CString i_fn;
		int n = a_Fn;
        i_fn.Format(_T("%d") , n);
		appendText(&m_cmdedit_Decode,_T(""));
		INT8U fn1=DstDecodeDataFrame.s_head.s_FN;
		INT8U fn2=DstDecodeDataFrame.s_head.s_FN >> 8;
		CString sfn=Tools._buf16tostr16(&fn1 ,1, true)+Tools._buf16tostr16(&fn2 ,1, true);
		appendText(&m_cmdedit_Decode,_T("���ݵ�Ԫ��ʶFN:�� ")+sfn+_T(" ��")+_T("F")+i_fn);

		appendText(&m_cmdedit_Decode,_T(""));
		appendText(&m_cmdedit_Decode,_T("Ӧ������:�� ")+Tools._buf16tostr16(DstDecodeDataFrame.s_RcvDataBuf , DstDecodeDataFrame.s_RcvDataLen, true)+_T(" ��"));
		//appendText(&m_cmdedit_Decode,_T("֡βУ��:�� ")+Tools._buf16tostr16(&DstDecodeDataFrame.s_RcvDataBuf[DstDecodeDataFrame.s_RcvDataLen-1],1, true)+_T(" ��"));
        appendText(&m_cmdedit_Decode,_T("---------------------------------------------------------------------------------------------"));
	}
	else{
		appendText(&m_cmdedit_Decode,_T("<----δ������376.2֡��ʽ������---->"));
	}
	appendText(&m_cmdedit_Decode,_T(""));
	appendText(&m_cmdedit_Decode,_T("============================================================================================="));
	//appendText(&m_cmdedit_Decode,_T(""));
	//ack = Ccsg13762.Decode376_2Frame(recvbuf,recvbuflen,DstDecodeDataFrameNW);
	//if(ack==DACK_SUCESS){
	//	       
	//			appendText(&m_cmdedit_Decode,_T("---------------------------------------------------------------------------------------------"));
	//			appendText(&m_cmdedit_Decode,_T("<----������376.2֡��ʽ�������������ж��Ƿ�����������£�---->"));
	//			appendText(&m_cmdedit_Decode,_T(""));
	//			appendText(&m_cmdedit_Decode,_T("������:�� ")+Tools._buf16tostr16(&DstDecodeDataFrameNW.s_head.u_con.s_conByte,1, true)+_T(" ��"));
	//			if(DstDecodeDataFrameNW.s_head.u_con.s_conBit.s_Con_DIR==0){
	//				appendText(&m_cmdedit_Decode,_T("          ���䷽��λDIR:[ 0 ]  ���������������б���"));
	//			}
	//			else if(DstDecodeDataFrameNW.s_head.u_con.s_conBit.s_Con_DIR==1){
	//				appendText(&m_cmdedit_Decode,_T("          ���䷽��λDIR:[ 1 ]  ��ͨ��ģ�鷢�������б���"));
	//			}
	//			if(DstDecodeDataFrameNW.s_head.u_con.s_conBit.s_Con_DIR==0){
	//				appendText(&m_cmdedit_Decode,_T("          ������־λPRM:[ 0 ]  �������ԴӶ�վ"));
	//			}
	//			else if(DstDecodeDataFrameNW.s_head.u_con.s_conBit.s_Con_DIR==1){
	//				appendText(&m_cmdedit_Decode,_T("          ������־λPRM:[ 1 ]  ������������վ"));
	//			}

	//			if(DstDecodeDataFrameNW.s_head.u_con.s_conBit.s_Con_ADD==1){
	//				appendText(&m_cmdedit_Decode,_T("          ��ַ���ʶ:[ 1 ]  ����ַ��"));
	//			}
	//			else if(DstDecodeDataFrameNW.s_head.u_con.s_conBit.s_Con_ADD==0){
	//				appendText(&m_cmdedit_Decode,_T("          ��ַ���ʶ:[ 0 ]  ������ַ��"));
	//			}
	//			CString strver;
	//			int n_ver = DstDecodeDataFrameNW.s_head.u_con.s_conBit.s_Con_VER;
	//			strver.Format(_T("%d") , n_ver);
	//			appendText(&m_cmdedit_Decode,_T("          �汾��:[ ")+ strver+_T(" ]"));

	//			appendText(&m_cmdedit_Decode,_T(""));
	//			if(DstDecodeDataFrameNW.s_head.u_con.s_conBit.s_Con_ADD==1){
	//				appendText(&m_cmdedit_Decode,_T("��ַ��:�� ")+Tools._buf16tostr16(DstDecodeDataFrameNW.s_head.s_MainAddBuf,6, true)+Tools._buf16tostr16(DstDecodeDataFrameNW.s_head.s_DestAddBuf,6, true)+_T(" ��"));
	//				appendText(&m_cmdedit_Decode,_T("          ���ڵ��ַ:[")+Tools._buf16tostr16(DstDecodeDataFrameNW.s_head.s_MainAddBuf,6, true)+_T(" ]"));
	//				appendText(&m_cmdedit_Decode,_T("          Ŀ�ĵ�ַ:[")+Tools._buf16tostr16(DstDecodeDataFrameNW.s_head.s_DestAddBuf,6, true)+_T(" ]"));
	//			}
	//			else if(DstDecodeDataFrameNW.s_head.u_con.s_conBit.s_Con_ADD==0){
	//				appendText(&m_cmdedit_Decode,_T("��ַ��:����"));
	//				appendText(&m_cmdedit_Decode,_T("          �޵�ַ��"));
	//			}

	//			appendText(&m_cmdedit_Decode,_T(""));
	//			appendText(&m_cmdedit_Decode,_T("Ӧ�ù�����AFN:�� ")+Tools._buf16tostr16(&DstDecodeDataFrameNW.s_head.s_AFN,1, true)+_T(" ��"));
	//			appendText(&m_cmdedit_Decode,_T(""));
	//			INT8U fn_1=DstDecodeDataFrameNW.s_head.s_FN;
	//	        INT8U fn_2=DstDecodeDataFrameNW.s_head.s_FN >> 8;
	//			INT8U fn_3=DstDecodeDataFrameNW.s_head.s_FN >> 16;
	//	        INT8U fn_4=DstDecodeDataFrameNW.s_head.s_FN >> 24;
	//	        CString sfn4=Tools._buf16tostr16(&fn_1 ,1, true)+Tools._buf16tostr16(&fn_2 ,1, true)+Tools._buf16tostr16(&fn_3 ,1, true)+Tools._buf16tostr16(&fn_4 ,1, true);
	//			CString sfn4d=Tools._buf16tostr16(&fn_4 ,1, true)+Tools._buf16tostr16(&fn_3 ,1, true)+Tools._buf16tostr16(&fn_2 ,1, true)+Tools._buf16tostr16(&fn_1 ,1, true);
	//	        appendText(&m_cmdedit_Decode,_T("���ݵ�Ԫ��ʶFN:�� ")+sfn4+_T(" ��")+sfn4d);
	//			appendText(&m_cmdedit_Decode,_T(""));
	//			appendText(&m_cmdedit_Decode,_T("֡���к�:�� ")+Tools._buf16tostr16(&DstDecodeDataFrameNW.s_head.s_Msg_Seq,1, true)+_T("��"));
	//			appendText(&m_cmdedit_Decode,_T(""));
	//	        appendText(&m_cmdedit_Decode,_T("Ӧ������:�� ")+Tools._buf16tostr16(DstDecodeDataFrameNW.s_RcvDataBuf , DstDecodeDataFrameNW.s_RcvDataLen, true)+_T(" ��"));

	//			appendText(&m_cmdedit_Decode,_T("---------------------------------------------------------------------------------------------"));

	//	}
	//else{
	//	 appendText(&m_cmdedit_Decode,_T("<----δ������376.2֡��ʽ������---->"));
	//	 appendText(&m_cmdedit_Decode,_T("---------------------------------------------------------------------------------------------"));
	//}
 }

 void CMyFrameMsgTabCtrl::appendText(CmdEdit *edit,CString mStr){//�༭��׷���ַ���
	 	CString strEditXianshi;
		edit->GetWindowText(strEditXianshi);
		edit->SetSel(strEditXianshi.GetLength(),strEditXianshi.GetLength());
		edit->ReplaceSel(mStr+_T("\r\n"));
 }

  void CMyFrameMsgTabCtrl::OnBnClickedButtonClearDECODE(){
	  switch(GetCurSel())
	{
	  case 2:
		  m_cmdedit_rec.SetWindowTextW(_T(""));
	  case 3:
	      m_cmdedit_Decode.SetWindowTextW(_T(""));
	 }
 }