// NetViewTPShow.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MyFunLib.h"
#include "KD_Project.h"
#include "NetViewTPShow.h"
#include "KD_ProjectDoc.h"
#include "SimJzq.h"
#include "MainFrm.h"
#include "DlgCCOTPchange.h"
#include "RightTabView.h"
#include "NetViewPToP.h"
#include "DlgCKQUpdataTime.h"
#include <list>
using namespace std;
extern CSimJzq  gSimJzq;
#include "GW13762.h"
extern CGW13762 Cgw13762;
// CNetViewTPShow
#include "SimJZQ.h"
IMPLEMENT_DYNCREATE(CNetViewTPShow, CFormView)

CNetViewTPShow::CNetViewTPShow()
	: CFormView(CNetViewTPShow::IDD)
{
	m_fFont = 15;
	m_Scale = 1.0f;
	m_cR = 20;
	m_cRW = 200;
	m_cTBWeith = 50;
	m_cLRWeith = 10;
	m_nAlldataNumb = 0;
	m_nLineType = 0;
	m_nMsgType = 1;
	m_nMsgTJType = 1;
	m_bSave = false;
	m_bAutoUpdata = false;
	m_bShow = false;
	m_nUpdataTime = 0;
	for(int m = 0 ; m < 10 ; m++)
	{
		m_nOnlineNumb[m] = 0;
	}
	m_bBreak = true;
}

CNetViewTPShow::~CNetViewTPShow()
{
	m_bBreak = false;
	Sleep(100);
}

void CNetViewTPShow::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CNetViewTPShow, CFormView)
	ON_WM_MOUSEWHEEL()
ON_WM_RBUTTONUP()
ON_WM_CONTEXTMENU()
ON_COMMAND(ID_RBTP_UPDATA, &CNetViewTPShow::OnRbtpUpdata)
//ON_WM_CREATE()
ON_COMMAND(ID_COO_CHANGE, &CNetViewTPShow::OnCooChange)
ON_COMMAND(ID_LINE_ZHI, &CNetViewTPShow::OnLineZhi)
ON_COMMAND(ID_LINE_ZHIJIAO, &CNetViewTPShow::OnLineZhijiao)
ON_WM_MOUSEMOVE()
ON_COMMAND(ID_RBTPJDMSG_FINDLIST, &CNetViewTPShow::OnRbtpjdmsgFindlist)
ON_COMMAND(IDR_MENU_RBTP_SHOW, &CNetViewTPShow::OnIdrMenuRbtpShow)
ON_COMMAND(IDR_MENU_RBTP_HEID, &CNetViewTPShow::OnIdrMenuRbtpHeid)
ON_COMMAND(IDR_MENU_RBTP_TJSHOW, &CNetViewTPShow::OnIdrMenuRbtpTJShow)
ON_COMMAND(IDR_MENU_RBTP_TJHIDE, &CNetViewTPShow::OnIdrMenuRbtpTJHeid)
ON_COMMAND(ID_RBTP_TEST, &CNetViewTPShow::OnRbtpTest)
ON_COMMAND(ID_RBTPJDMSG_PTP, &CNetViewTPShow::OnRbtpjdmsgPtp)
//ON_WM_CHAR()
//ON_WM_KEYDOWN()
ON_COMMAND(ID_RBTP_AUTOUPDATA, &CNetViewTPShow::OnRbtpAutoupdata)
ON_COMMAND(ID_RBTP_SAVE, &CNetViewTPShow::OnRbtpSave)
END_MESSAGE_MAP()


// CNetViewTPShow ���

#ifdef _DEBUG
void CNetViewTPShow::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CNetViewTPShow::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG

// CNetViewTPShow ��Ϣ�������
//��ʼ������
//ִ���߳�
DWORD WINAPI ThreadSendTP_10F21 (PVOID pParam) //��ȡ����ͼCKQ2017
{
	CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CNetViewTPShow * pView = (CNetViewTPShow *)pParam;
	INT16U u16BeginNumb = 0;
	INT8U SendDatabuf[10];
	INT8U ack = 0 , u8SendAFN = 0 ,AddrBuf[7] , u8ReadCount = 0;
	INT16U SendDatalen = 0 ,temp16 = 0;
	//CString strAllTPdata = _T("");

		//sPartCKQ2017CreatFrame ptSendCKQ2017;
	 //   sPartCKQ2017DeCodeFrame ptDeCodeCKQ2017;
		while(pView->m_bBreak)
		{

			if (pView->m_bAutoUpdata == true)
			{
				if (pView->m_nUpdataTime == 0)
				{
					pView->m_bAutoUpdata = false;
				}
				if (pMain->m_bConnected != TRUE)
				{
					AfxMessageBox(_T("���ȴ򿪴��ڣ�"));
					continue;
				}
					    sPartQGDW376_2CreatFrame ptSendQGDW376_2,sQGDW376_2HostFrame;
		sPartQGDW376_2DeCodeFrame ptRecvQGDW376_2,sRecv376_2HostFrame;
				//if (pMain->m_strMAddress == "")
				//{
				//	AfxMessageBox(_T("��������CCO��"));
				//	continue;
				//}

//////////////���ڵ�����MSDU��376.///////////////
				//Cgw13762.Code376_2_HostFrame(0x01,F1,ptSendQGDW376_2);//
				//ptSendQGDW376_2.s_SendDataBuf[3]=0x43;

				//ack = pView->gCKQ2017.SendRec_MAC_13762_toCCO(ptSendQGDW376_2,ptRecvQGDW376_2);//���ͽ���CKQ��֡��MAC֡��376.2  ����ȡ376.2����
				//if(ack == DACK_SUCESS)
				//{

				//}
///////////////////////////////////////////////////////////






//********************************************************************//
				//sPartCKQ2017CreatFrame ptSendCKQ2017;
	   //         
				//ptSendCKQ2017.TYPE=0x07;
		  //      ptSendCKQ2017.s_SendDataBuf=0;
		  //      ptSendCKQ2017.s_SendDataLen=0;
				//ack =pView->gCKQ2017.CodeCKQ2017Frame(ptSendCKQ2017);
				//if(ack == DACK_SUCESS)
				//{
				//		pView->gCKQ2017.SendCKQ2017ToCom(ptSendCKQ2017);
				//		CString strAllTPdata = _T("");
				//		while(true){
				//			sPartCKQ2017DeCodeFrame ptDeCodeCKQ2017;
				//			//ptDeCodeCKQ2017.s_RcvDataLen=0;
				//			ack = pView->gCKQ2017.WaitCKQ2017AckTYPE(10000 , 20 ,ptSendCKQ2017,ptDeCodeCKQ2017);
				//			if(ack == DACK_SUCESS)
				//			{
				//				int num=ptDeCodeCKQ2017.s_RcvDataBuf[2]*256+ptDeCodeCKQ2017.s_RcvDataBuf[3];
				//				strAllTPdata += pView->m_tools._buf16tostr16(&ptDeCodeCKQ2017.s_RcvDataBuf[4] , ptDeCodeCKQ2017.s_RcvDataLen -4);
				//				if(ptDeCodeCKQ2017.s_RcvDataBuf[1]==1){
				//				   pView->SetTPdataToAccess(strAllTPdata);
				//                   pView->GetPointCoordinate();
				//				   break;

				//				}
				//			}
				//			else{
    //                            break;
				//			}
				//		}
				//		pView->m_DlgTongJiNode.InsertItemToTreeList(_T("TPShow"));//170912120240_T("TPShow")


				//	//						//////////////////////////////
				//	//INT16U u16BeginNumb_Node = 1;
				//	//INT8U u8ReadCount_Node = 0 , n = 0 , temp8 = 0;
				//	//INT16U temp16_Node = 0 , u16Numb = 0;
				//	//CString strMAC = _T("") , strWhere = _T("");
				//	//CString strNumb , strSTAMsg[1024] , strlist[10];
				//	//int nlistNumb = 0 , nlistUN = 0 , nInNetNumb = 0 , nUnNetNumb = 0 , nLostNumb = 0 , nUnWhiteNumb = 0;
				//	//
				//	////pView->m_DlgTongJiNode.OnlineList.DeleteAllItems();
				//	////pView->m_DlgTongJiNode.LostList.DeleteAllItems();
				//	//
				//	//pView->m_access.DelectDataFromTable(pMain->m_PeiZhi_db , _T("TPMODERR") , _T(""));
	   // //            pView->m_access.SetCopyTable(pMain->m_PeiZhi_db, _T("TPShow") , _T("TPMODERR"));
	   // //            pView->m_tools._str16tobuf16( pMain->m_strMAddress , AddrBuf , temp16_Node , true);
				//	//ack = gSimJzq.HostSendRcv376_2F0F8(AddrBuf , 0x10 , F1 , SendDatabuf , SendDatalen , ptSendQGDW376_2 , ptRecvQGDW376_2 , ptRecvQGDW376_2);
				//	//if (ack != 0) return 0;
				//	//temp16_Node = ptRecvQGDW376_2.s_RcvDataBuf[1] << 8 | ptRecvQGDW376_2.s_RcvDataBuf[0];
				//	//while(temp16_Node)
				//	//{
				//	//	u16BeginNumb_Node += u8ReadCount_Node;
				//	//	if (temp16_Node >10)
				//	//	{
				//	//		u8ReadCount_Node = 10;
				//	//	}
				//	//	else
				//	//	{
				//	//		u8ReadCount_Node = temp16_Node;
				//	//	}
				//	//	temp16_Node -= u8ReadCount_Node;
				//	//	SendDatalen = 3;
				//	//	SendDatabuf[0] = (INT8U)u16BeginNumb_Node;
				//	//	SendDatabuf[1] = (INT8U)(u16BeginNumb_Node>>8);
				//	//	SendDatabuf[2] = u8ReadCount_Node;
				//	//	ack = gSimJzq.HostSendRcv376_2F0F8(AddrBuf , 0x10 , F2 , SendDatabuf , SendDatalen , ptSendQGDW376_2, ptRecvQGDW376_2 , ptRecvQGDW376_2);
				//	//	if (ack != 0) return 0;

				//	//	temp8 = ptRecvQGDW376_2.s_RcvDataBuf[2];
				//	//	for (n = 0; n < temp8; n++)
				//	//	{
				//	//		strMAC = pView->m_tools._buf16tostr16(&ptRecvQGDW376_2.s_RcvDataBuf[3 + 8 * n] , 6 , false , true);
				//	//		strWhere = _T("TP_MAC='") + strMAC + _T("'");
				//	//		pView->m_access.SelectDataFromTable(pMain->m_PeiZhi_db, _T("TPMODERR") , _T("TP_TEI,TP_ROLE") , strWhere , strSTAMsg , nlistNumb);
				//	//		//pView->m_access.SelectDataFromTable(_T(".\\�����ļ�\\13762Data.accdb") , _T("TPMODERR") , _T("TP_TEI,TP_ROLE") , strWhere , strSTAMsg , nlistNumb);
				//	//		if (nlistNumb == 0)
				//	//		{
				//	//			nUnNetNumb += 1;
				//	//			//pView->InsertItemToList(strMAC , _T("��") , _T("δ����") , _T("") , _T("δ֪") , _T(""));

				//	//			pView->m_DlgTongJiNode.InsertItemToLostList(strMAC);
				//	//		}
				//	//		else
				//	//		{
				//	//			nInNetNumb += 1;
				//	//			pView->m_tools.Split(strSTAMsg[0] , _T("$") , strlist , nlistNumb);
				//	//			//pView->InsertItemToList(strMAC , strlist[0] , _T("����") , _T("") , strMAC , strlist[1]);
				//	//			pView->m_DlgTongJiNode.InsertItemToOnlineList(strMAC,strlist[0],strMAC, strlist[1]);
				//	//			pView->m_access.DelectDataFromTable(pMain->m_PeiZhi_db , _T("TPMODERR") , strWhere);
				//	//			//pView->m_access.DelectDataFromTable(_T(".\\�����ļ�\\13762Data.accdb") , _T("TPMODERR") , strWhere);
				//	//		}
				//	//	}
				//	//}
				//	//pView->m_nOnlineNumb[5]=nUnNetNumb;
				//}
				
//***********************************************/////

////////////////////10F21��ʽ����������  ���ӳ����� ����//////////////////////////////
		INT16U temp16_Node = 0 , u16Numb = 0;
		INT16U u16BeginNumb_Node = 1;
		INT8U u8ReadCount_Node = 0 , n = 0 , temp8 = 0;
		CString strAllTPdata = _T("");
		ack = gSimJzq.HostSendRcv376_2NoBuf(0x10,F1,sQGDW376_2HostFrame,sRecv376_2HostFrame,1);
		if(ack == DACK_SUCESS)
		{
			ack = DACK_FAILURE; 
			if((sRecv376_2HostFrame.s_RcvDataLen ==4))
			{
				ack = DACK_SUCESS;
				temp16_Node= Buf2ToHex16(sRecv376_2HostFrame.s_RcvDataBuf);
			}
		}
		while(temp16_Node){

			u16BeginNumb_Node += u8ReadCount_Node;
			if (temp16_Node >10)
			{
				u8ReadCount_Node = 10;
			}
			else
			{
				u8ReadCount_Node = temp16_Node;
			}
			temp16_Node -= u8ReadCount_Node;
			SendDatalen = 3;
			SendDatabuf[0] = (INT8U)u16BeginNumb_Node;
			SendDatabuf[1] = (INT8U)(u16BeginNumb_Node>>8);
			SendDatabuf[2] = u8ReadCount_Node;
			ack =gSimJzq.HostSendRcv376_2Buf(0x10,F21,SendDatabuf,SendDatalen,ptSendQGDW376_2,ptRecvQGDW376_2);
			switch(ack)
			{
			case 0x00://�ɹ�
				strAllTPdata += pView->m_tools._buf16tostr16(&ptRecvQGDW376_2.s_RcvDataBuf[5] , ptRecvQGDW376_2.s_RcvDataLen -5);
				break;
			default:
				break;
			}
		}
		pView->SetTPdataToAccess_10F21(strAllTPdata);
		pView->GetPointCoordinate();
		pView->m_DlgTongJiNode.InsertItemToTreeList(_T("TPShow"));


////////////////////10F21��ʽ����������  ���ӳ����� ����//////////////////////////////

				Sleep(pView->m_nUpdataTime * 2000);
			}
			Sleep(200);
		}



		//sPartQGDW376_2CreatFrame ptSendQGDW376_2;
		//sPartQGDW376_2DeCodeFrame ptRecvQGDW376_2;
		//while(pView->m_bBreak)
		//{
		//	if (pView->m_bAutoUpdata == true)
		//	{
		//		if (pView->m_nUpdataTime == 0)
		//		{
		//			pView->m_bAutoUpdata = false;
		//		}
		//		if (pMain->m_bConnected != TRUE)
		//		{
		//			AfxMessageBox(_T("���ȴ򿪴��ڣ�"));
		//			continue;
		//		}
		//		//if (pMain->m_strMAddress == "")
		//		//{
		//		//	AfxMessageBox(_T("��������CCO��"));
		//		//	continue;
		//		//}
		//		u16BeginNumb = 0;
		//		SendDatalen = 0;
		//		u8ReadCount = 0;
		//		strAllTPdata = pMain->m_strMAddress + _T("0100000021000000");
		//		pView->m_tools._str16tobuf16( pMain->m_strMAddress , AddrBuf , temp16 , true);
		//		ack = gSimJzq.HostSendRcv376_2F0F8(AddrBuf , 0xF0 , F10 , SendDatabuf , SendDatalen , pView->m_ptSendQGDW376_2 , ptRecvQGDW376_2 , pView->m_ptRecvQGDW376_2);
		//		switch(ack)
		//		{
		//		case 0x00://�ɹ�
		//			temp16 = pView->m_ptRecvQGDW376_2.s_RcvDataBuf[1] << 8 | pView->m_ptRecvQGDW376_2.s_RcvDataBuf[0];
		//			while(temp16)
		//			{
		//				u16BeginNumb += u8ReadCount;
		//				if (temp16 >20)
		//				{
		//					u8ReadCount = 20;
		//				}
		//				else
		//				{
		//					u8ReadCount = temp16;
		//				}
		//				temp16 -= u8ReadCount;
		//				SendDatalen = 3;
		//				SendDatabuf[0] = (INT8U)u16BeginNumb;
		//				SendDatabuf[1] = (INT8U)(u16BeginNumb>>8);
		//				SendDatabuf[2] = u8ReadCount;
		//				ack = gSimJzq.HostSendRcv376_2F0F8(AddrBuf , 0xF0 , F9 , SendDatabuf , SendDatalen , pView->m_ptSendQGDW376_2, ptRecvQGDW376_2 , pView->m_ptRecvQGDW376_2);
		//				switch(ack)
		//				{
		//				case 0x00://�ɹ�
		//					strAllTPdata += pView->m_tools._buf16tostr16(&pView->m_ptRecvQGDW376_2.s_RcvDataBuf[5] , pView->m_ptRecvQGDW376_2.s_RcvDataLen -5);
		//					break;
		//				}
		//			}
		//			pView->SetTPdataToAccess(strAllTPdata);
		//			pView->GetPointCoordinate();

		//			//////////////////////////////
		//			INT16U u16BeginNumb_Node = 1;
		//			INT8U u8ReadCount_Node = 0 , n = 0 , temp8 = 0;
		//			INT16U temp16_Node = 0 , u16Numb = 0;
		//			CString strMAC = _T("") , strWhere = _T("");
		//			CString strNumb , strSTAMsg[1024] , strlist[10];
		//			int nlistNumb = 0 , nlistUN = 0 , nInNetNumb = 0 , nUnNetNumb = 0 , nLostNumb = 0 , nUnWhiteNumb = 0;
		//			
		//			pView->m_DlgTongJiNode.OnlineList.DeleteAllItems();
		//			pView->m_DlgTongJiNode.LostList.DeleteAllItems();
		//			pView->m_access.DelectDataFromTable(pMain->m_PeiZhi_db , _T("TPMODERR") , _T(""));
	 //               pView->m_access.SetCopyTable(pMain->m_PeiZhi_db, _T("TPShow") , _T("TPMODERR"));
	 //               pView->m_tools._str16tobuf16( pMain->m_strMAddress , AddrBuf , temp16_Node , true);
		//			ack = gSimJzq.HostSendRcv376_2F0F8(AddrBuf , 0x10 , F1 , SendDatabuf , SendDatalen , ptSendQGDW376_2 , ptRecvQGDW376_2 , ptRecvQGDW376_2);
		//			if (ack != 0) return 0;
		//			temp16_Node = ptRecvQGDW376_2.s_RcvDataBuf[1] << 8 | ptRecvQGDW376_2.s_RcvDataBuf[0];
		//			while(temp16_Node)
		//			{
		//				u16BeginNumb_Node += u8ReadCount_Node;
		//				if (temp16_Node >10)
		//				{
		//					u8ReadCount_Node = 10;
		//				}
		//				else
		//				{
		//					u8ReadCount_Node = temp16_Node;
		//				}
		//				temp16_Node -= u8ReadCount_Node;
		//				SendDatalen = 3;
		//				SendDatabuf[0] = (INT8U)u16BeginNumb_Node;
		//				SendDatabuf[1] = (INT8U)(u16BeginNumb_Node>>8);
		//				SendDatabuf[2] = u8ReadCount_Node;
		//				ack = gSimJzq.HostSendRcv376_2F0F8(AddrBuf , 0x10 , F2 , SendDatabuf , SendDatalen , ptSendQGDW376_2, ptRecvQGDW376_2 , ptRecvQGDW376_2);
		//				if (ack != 0) return 0;

		//				temp8 = ptRecvQGDW376_2.s_RcvDataBuf[2];
		//				for (n = 0; n < temp8; n++)
		//				{
		//					strMAC = pView->m_tools._buf16tostr16(&ptRecvQGDW376_2.s_RcvDataBuf[3 + 8 * n] , 6 , false , true);
		//					strWhere = _T("TP_MAC='") + strMAC + _T("'");
		//					pView->m_access.SelectDataFromTable(pMain->m_PeiZhi_db, _T("TPMODERR") , _T("TP_TEI,TP_ROLE") , strWhere , strSTAMsg , nlistNumb);
		//					//pView->m_access.SelectDataFromTable(_T(".\\�����ļ�\\13762Data.accdb") , _T("TPMODERR") , _T("TP_TEI,TP_ROLE") , strWhere , strSTAMsg , nlistNumb);
		//					if (nlistNumb == 0)
		//					{
		//						nUnNetNumb += 1;
		//						//pView->InsertItemToList(strMAC , _T("��") , _T("δ����") , _T("") , _T("δ֪") , _T(""));

		//						pView->m_DlgTongJiNode.InsertItemToLostList(strMAC);
		//					}
		//					else
		//					{
		//						nInNetNumb += 1;
		//						pView->m_tools.Split(strSTAMsg[0] , _T("$") , strlist , nlistNumb);
		//						//pView->InsertItemToList(strMAC , strlist[0] , _T("����") , _T("") , strMAC , strlist[1]);
		//						pView->m_DlgTongJiNode.InsertItemToOnlineList(strMAC,strlist[0],strMAC, strlist[1]);
		//						pView->m_access.DelectDataFromTable(pMain->m_PeiZhi_db , _T("TPMODERR") , strWhere);
		//						//pView->m_access.DelectDataFromTable(_T(".\\�����ļ�\\13762Data.accdb") , _T("TPMODERR") , strWhere);
		//					}
		//				}
		//			}
		//			pView->m_nOnlineNumb[5]=nUnNetNumb;






		//			//////////////////////////////


		//			break;
		//		}
		//		Sleep(pView->m_nUpdataTime * 2000);
		//	}
		//	Sleep(200);
		//}

	return 0;
}

DWORD WINAPI ThreadSendTP (PVOID pParam) //��ȡ����ͼCKQ2017
{
	CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CNetViewTPShow * pView = (CNetViewTPShow *)pParam;
	INT16U u16BeginNumb = 0;
	INT8U SendDatabuf[10];
	INT8U ack = 0 , u8SendAFN = 0 ,AddrBuf[7] , u8ReadCount = 0;
	INT16U SendDatalen = 0 ,temp16 = 0;
	//CString strAllTPdata = _T("");
	    sPartQGDW376_2CreatFrame ptSendQGDW376_2,sQGDW376_2HostFrame;
		sPartQGDW376_2DeCodeFrame ptRecvQGDW376_2,sRecv376_2HostFrame;

		//sPartCKQ2017CreatFrame ptSendCKQ2017;
	 //   sPartCKQ2017DeCodeFrame ptDeCodeCKQ2017;
		while(pView->m_bBreak)
		{
			if (pView->m_bAutoUpdata == true)
			{
				if (pView->m_nUpdataTime == 0)
				{
					pView->m_bAutoUpdata = false;
				}
				if (pMain->m_bConnected != TRUE)
				{
					AfxMessageBox(_T("���ȴ򿪴��ڣ�"));
					continue;
				}
				//if (pMain->m_strMAddress == "")
				//{
				//	AfxMessageBox(_T("��������CCO��"));
				//	continue;
				//}

//////////////���ڵ�����MSDU��376.///////////////
				//Cgw13762.Code376_2_HostFrame(0x01,F1,ptSendQGDW376_2);//
				//ptSendQGDW376_2.s_SendDataBuf[3]=0x43;

				//ack = pView->gCKQ2017.SendRec_MAC_13762_toCCO(ptSendQGDW376_2,ptRecvQGDW376_2);//���ͽ���CKQ��֡��MAC֡��376.2  ����ȡ376.2����
				//if(ack == DACK_SUCESS)
				//{

				//}
///////////////////////////////////////////////////////////






//********************************************************************//
				sPartCKQ2017CreatFrame ptSendCKQ2017;
	            
				ptSendCKQ2017.TYPE=0x07;
		        ptSendCKQ2017.s_SendDataBuf=0;
		        ptSendCKQ2017.s_SendDataLen=0;
				ack =pView->gCKQ2017.CodeCKQ2017Frame(ptSendCKQ2017);
				if(ack == DACK_SUCESS)
				{
						pView->gCKQ2017.SendCKQ2017ToCom(ptSendCKQ2017);
						CString strAllTPdata = _T("");
						while(true){
							sPartCKQ2017DeCodeFrame ptDeCodeCKQ2017;
							//ptDeCodeCKQ2017.s_RcvDataLen=0;
							ack = pView->gCKQ2017.WaitCKQ2017AckTYPE(10000 , 20 ,ptSendCKQ2017,ptDeCodeCKQ2017);
							if(ack == DACK_SUCESS)
							{
								int num=ptDeCodeCKQ2017.s_RcvDataBuf[2]*256+ptDeCodeCKQ2017.s_RcvDataBuf[3];
								strAllTPdata += pView->m_tools._buf16tostr16(&ptDeCodeCKQ2017.s_RcvDataBuf[4] , ptDeCodeCKQ2017.s_RcvDataLen -4);
								if(ptDeCodeCKQ2017.s_RcvDataBuf[1]==1){
								   pView->SetTPdataToAccess(strAllTPdata);
				                   pView->GetPointCoordinate();
								   break;

								}
							}
							else{
                                break;
							}
						}
						pView->m_DlgTongJiNode.InsertItemToTreeList(_T("TPShow"));//170912120240_T("TPShow")


					//						//////////////////////////////
					//INT16U u16BeginNumb_Node = 1;
					//INT8U u8ReadCount_Node = 0 , n = 0 , temp8 = 0;
					//INT16U temp16_Node = 0 , u16Numb = 0;
					//CString strMAC = _T("") , strWhere = _T("");
					//CString strNumb , strSTAMsg[1024] , strlist[10];
					//int nlistNumb = 0 , nlistUN = 0 , nInNetNumb = 0 , nUnNetNumb = 0 , nLostNumb = 0 , nUnWhiteNumb = 0;
					//
					////pView->m_DlgTongJiNode.OnlineList.DeleteAllItems();
					////pView->m_DlgTongJiNode.LostList.DeleteAllItems();
					//
					//pView->m_access.DelectDataFromTable(pMain->m_PeiZhi_db , _T("TPMODERR") , _T(""));
	    //            pView->m_access.SetCopyTable(pMain->m_PeiZhi_db, _T("TPShow") , _T("TPMODERR"));
	    //            pView->m_tools._str16tobuf16( pMain->m_strMAddress , AddrBuf , temp16_Node , true);
					//ack = gSimJzq.HostSendRcv376_2F0F8(AddrBuf , 0x10 , F1 , SendDatabuf , SendDatalen , ptSendQGDW376_2 , ptRecvQGDW376_2 , ptRecvQGDW376_2);
					//if (ack != 0) return 0;
					//temp16_Node = ptRecvQGDW376_2.s_RcvDataBuf[1] << 8 | ptRecvQGDW376_2.s_RcvDataBuf[0];
					//while(temp16_Node)
					//{
					//	u16BeginNumb_Node += u8ReadCount_Node;
					//	if (temp16_Node >10)
					//	{
					//		u8ReadCount_Node = 10;
					//	}
					//	else
					//	{
					//		u8ReadCount_Node = temp16_Node;
					//	}
					//	temp16_Node -= u8ReadCount_Node;
					//	SendDatalen = 3;
					//	SendDatabuf[0] = (INT8U)u16BeginNumb_Node;
					//	SendDatabuf[1] = (INT8U)(u16BeginNumb_Node>>8);
					//	SendDatabuf[2] = u8ReadCount_Node;
					//	ack = gSimJzq.HostSendRcv376_2F0F8(AddrBuf , 0x10 , F2 , SendDatabuf , SendDatalen , ptSendQGDW376_2, ptRecvQGDW376_2 , ptRecvQGDW376_2);
					//	if (ack != 0) return 0;

					//	temp8 = ptRecvQGDW376_2.s_RcvDataBuf[2];
					//	for (n = 0; n < temp8; n++)
					//	{
					//		strMAC = pView->m_tools._buf16tostr16(&ptRecvQGDW376_2.s_RcvDataBuf[3 + 8 * n] , 6 , false , true);
					//		strWhere = _T("TP_MAC='") + strMAC + _T("'");
					//		pView->m_access.SelectDataFromTable(pMain->m_PeiZhi_db, _T("TPMODERR") , _T("TP_TEI,TP_ROLE") , strWhere , strSTAMsg , nlistNumb);
					//		//pView->m_access.SelectDataFromTable(_T(".\\�����ļ�\\13762Data.accdb") , _T("TPMODERR") , _T("TP_TEI,TP_ROLE") , strWhere , strSTAMsg , nlistNumb);
					//		if (nlistNumb == 0)
					//		{
					//			nUnNetNumb += 1;
					//			//pView->InsertItemToList(strMAC , _T("��") , _T("δ����") , _T("") , _T("δ֪") , _T(""));

					//			pView->m_DlgTongJiNode.InsertItemToLostList(strMAC);
					//		}
					//		else
					//		{
					//			nInNetNumb += 1;
					//			pView->m_tools.Split(strSTAMsg[0] , _T("$") , strlist , nlistNumb);
					//			//pView->InsertItemToList(strMAC , strlist[0] , _T("����") , _T("") , strMAC , strlist[1]);
					//			pView->m_DlgTongJiNode.InsertItemToOnlineList(strMAC,strlist[0],strMAC, strlist[1]);
					//			pView->m_access.DelectDataFromTable(pMain->m_PeiZhi_db , _T("TPMODERR") , strWhere);
					//			//pView->m_access.DelectDataFromTable(_T(".\\�����ļ�\\13762Data.accdb") , _T("TPMODERR") , strWhere);
					//		}
					//	}
					//}
					//pView->m_nOnlineNumb[5]=nUnNetNumb;
				}
				
//***********************************************/////
				Sleep(pView->m_nUpdataTime * 2000);
			}
			Sleep(200);
		}



		//sPartQGDW376_2CreatFrame ptSendQGDW376_2;
		//sPartQGDW376_2DeCodeFrame ptRecvQGDW376_2;
		//while(pView->m_bBreak)
		//{
		//	if (pView->m_bAutoUpdata == true)
		//	{
		//		if (pView->m_nUpdataTime == 0)
		//		{
		//			pView->m_bAutoUpdata = false;
		//		}
		//		if (pMain->m_bConnected != TRUE)
		//		{
		//			AfxMessageBox(_T("���ȴ򿪴��ڣ�"));
		//			continue;
		//		}
		//		//if (pMain->m_strMAddress == "")
		//		//{
		//		//	AfxMessageBox(_T("��������CCO��"));
		//		//	continue;
		//		//}
		//		u16BeginNumb = 0;
		//		SendDatalen = 0;
		//		u8ReadCount = 0;
		//		strAllTPdata = pMain->m_strMAddress + _T("0100000021000000");
		//		pView->m_tools._str16tobuf16( pMain->m_strMAddress , AddrBuf , temp16 , true);
		//		ack = gSimJzq.HostSendRcv376_2F0F8(AddrBuf , 0xF0 , F10 , SendDatabuf , SendDatalen , pView->m_ptSendQGDW376_2 , ptRecvQGDW376_2 , pView->m_ptRecvQGDW376_2);
		//		switch(ack)
		//		{
		//		case 0x00://�ɹ�
		//			temp16 = pView->m_ptRecvQGDW376_2.s_RcvDataBuf[1] << 8 | pView->m_ptRecvQGDW376_2.s_RcvDataBuf[0];
		//			while(temp16)
		//			{
		//				u16BeginNumb += u8ReadCount;
		//				if (temp16 >20)
		//				{
		//					u8ReadCount = 20;
		//				}
		//				else
		//				{
		//					u8ReadCount = temp16;
		//				}
		//				temp16 -= u8ReadCount;
		//				SendDatalen = 3;
		//				SendDatabuf[0] = (INT8U)u16BeginNumb;
		//				SendDatabuf[1] = (INT8U)(u16BeginNumb>>8);
		//				SendDatabuf[2] = u8ReadCount;
		//				ack = gSimJzq.HostSendRcv376_2F0F8(AddrBuf , 0xF0 , F9 , SendDatabuf , SendDatalen , pView->m_ptSendQGDW376_2, ptRecvQGDW376_2 , pView->m_ptRecvQGDW376_2);
		//				switch(ack)
		//				{
		//				case 0x00://�ɹ�
		//					strAllTPdata += pView->m_tools._buf16tostr16(&pView->m_ptRecvQGDW376_2.s_RcvDataBuf[5] , pView->m_ptRecvQGDW376_2.s_RcvDataLen -5);
		//					break;
		//				}
		//			}
		//			pView->SetTPdataToAccess(strAllTPdata);
		//			pView->GetPointCoordinate();

		//			//////////////////////////////
		//			INT16U u16BeginNumb_Node = 1;
		//			INT8U u8ReadCount_Node = 0 , n = 0 , temp8 = 0;
		//			INT16U temp16_Node = 0 , u16Numb = 0;
		//			CString strMAC = _T("") , strWhere = _T("");
		//			CString strNumb , strSTAMsg[1024] , strlist[10];
		//			int nlistNumb = 0 , nlistUN = 0 , nInNetNumb = 0 , nUnNetNumb = 0 , nLostNumb = 0 , nUnWhiteNumb = 0;
		//			
		//			pView->m_DlgTongJiNode.OnlineList.DeleteAllItems();
		//			pView->m_DlgTongJiNode.LostList.DeleteAllItems();
		//			pView->m_access.DelectDataFromTable(pMain->m_PeiZhi_db , _T("TPMODERR") , _T(""));
	 //               pView->m_access.SetCopyTable(pMain->m_PeiZhi_db, _T("TPShow") , _T("TPMODERR"));
	 //               pView->m_tools._str16tobuf16( pMain->m_strMAddress , AddrBuf , temp16_Node , true);
		//			ack = gSimJzq.HostSendRcv376_2F0F8(AddrBuf , 0x10 , F1 , SendDatabuf , SendDatalen , ptSendQGDW376_2 , ptRecvQGDW376_2 , ptRecvQGDW376_2);
		//			if (ack != 0) return 0;
		//			temp16_Node = ptRecvQGDW376_2.s_RcvDataBuf[1] << 8 | ptRecvQGDW376_2.s_RcvDataBuf[0];
		//			while(temp16_Node)
		//			{
		//				u16BeginNumb_Node += u8ReadCount_Node;
		//				if (temp16_Node >10)
		//				{
		//					u8ReadCount_Node = 10;
		//				}
		//				else
		//				{
		//					u8ReadCount_Node = temp16_Node;
		//				}
		//				temp16_Node -= u8ReadCount_Node;
		//				SendDatalen = 3;
		//				SendDatabuf[0] = (INT8U)u16BeginNumb_Node;
		//				SendDatabuf[1] = (INT8U)(u16BeginNumb_Node>>8);
		//				SendDatabuf[2] = u8ReadCount_Node;
		//				ack = gSimJzq.HostSendRcv376_2F0F8(AddrBuf , 0x10 , F2 , SendDatabuf , SendDatalen , ptSendQGDW376_2, ptRecvQGDW376_2 , ptRecvQGDW376_2);
		//				if (ack != 0) return 0;

		//				temp8 = ptRecvQGDW376_2.s_RcvDataBuf[2];
		//				for (n = 0; n < temp8; n++)
		//				{
		//					strMAC = pView->m_tools._buf16tostr16(&ptRecvQGDW376_2.s_RcvDataBuf[3 + 8 * n] , 6 , false , true);
		//					strWhere = _T("TP_MAC='") + strMAC + _T("'");
		//					pView->m_access.SelectDataFromTable(pMain->m_PeiZhi_db, _T("TPMODERR") , _T("TP_TEI,TP_ROLE") , strWhere , strSTAMsg , nlistNumb);
		//					//pView->m_access.SelectDataFromTable(_T(".\\�����ļ�\\13762Data.accdb") , _T("TPMODERR") , _T("TP_TEI,TP_ROLE") , strWhere , strSTAMsg , nlistNumb);
		//					if (nlistNumb == 0)
		//					{
		//						nUnNetNumb += 1;
		//						//pView->InsertItemToList(strMAC , _T("��") , _T("δ����") , _T("") , _T("δ֪") , _T(""));

		//						pView->m_DlgTongJiNode.InsertItemToLostList(strMAC);
		//					}
		//					else
		//					{
		//						nInNetNumb += 1;
		//						pView->m_tools.Split(strSTAMsg[0] , _T("$") , strlist , nlistNumb);
		//						//pView->InsertItemToList(strMAC , strlist[0] , _T("����") , _T("") , strMAC , strlist[1]);
		//						pView->m_DlgTongJiNode.InsertItemToOnlineList(strMAC,strlist[0],strMAC, strlist[1]);
		//						pView->m_access.DelectDataFromTable(pMain->m_PeiZhi_db , _T("TPMODERR") , strWhere);
		//						//pView->m_access.DelectDataFromTable(_T(".\\�����ļ�\\13762Data.accdb") , _T("TPMODERR") , strWhere);
		//					}
		//				}
		//			}
		//			pView->m_nOnlineNumb[5]=nUnNetNumb;






		//			//////////////////////////////


		//			break;
		//		}
		//		Sleep(pView->m_nUpdataTime * 2000);
		//	}
		//	Sleep(200);
		//}

	return 0;
}



void CNetViewTPShow::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CRect rect;
	GetClientRect(rect); 
	m_cx=rect.right;
	m_cy=rect.bottom;
	SetScrollSizes(IDD_DIALOG_TUOPUSHOW , CSize(m_cx, m_cy));
	m_gw13762.SetMainAdd(pMain->m_HostNodeAddress);
	
#ifdef _STD_CSG  //������׼
	m_csg13762.SetMainAdd(pMain->m_HostNodeAddress);
#endif
	gSimJzq.SetMainAdd(pMain->m_HostNodeAddress);
	m_RrushFont.CreateSolidBrush(RGB(128,0,64));//�����ɫ
	m_BrushAll[2].CreateSolidBrush(RGB(255,0,0));//CC0
	m_BrushAll[3].CreateSolidBrush(RGB(255,128,128));//U_CCO
	m_BrushAll[4].CreateSolidBrush(RGB(0,255,0));//RGB(0,255,0));//STA
	m_BrushAll[5].CreateSolidBrush(RGB(128,255,128));//U_STA
	m_BrushAll[6].CreateSolidBrush(RGB(255,128,64));//PCO
	m_BrushAll[7].CreateSolidBrush(RGB(192,192,192));//����
	m_cpenXu.CreatePen(PS_SOLID,1,RGB(128,0,64));//�ߵ���ɫ
	int m = 0 ;
	for(m = 0 ; m < MODUMAXNUMB ; m++)
	{
		m_nPointColor[m] = 0;
		m_fPointWeith[m] = 0;
		m_fCoordinate[m][0] = 0;
		m_fCoordinate[m][1] = 0;
		m_strlist[m] = _T("");
		m_nPointLine[m][0] = 0;
		m_nPointLine[m][1] = 0;
		m_nPointNumb[m] = 0;
	}
	for(m = 0 ; m < 10 ; m++)
	{
		m_nOnlineNumb[m] = 0;
	}
	m_TPShowFindList.Create(IDD_DIALOG_FINDLIST,this);
	m_TPDlgJDMsg.Create(IDD_DIALOG_TPSHOW_JDMSG,this);
	m_TPDlgJDMsg.SetWindowPos(NULL,0,0,1,1,SWP_HIDEWINDOW);
	m_TPDlgShowExplian.Create(IDD_DIALOG_TPSHOW_EXPLIAN,this);
	m_DlgTongJiNode.Create(IDD_TONGJIDIALOG,this);
	m_TPDlgShowExplian.SetWindowPos(NULL,rect.right - 220,rect.top + 50, 200 ,410,SWP_HIDEWINDOW);
	//m_DlgTongJiNode.SetWindowPos(NULL,rect.right - 400,rect.top + 200, 800 ,600,SWP_HIDEWINDOW);
	m_hThreadsend=CreateThread (NULL,0,ThreadSendTP_10F21,this,0,NULL);
	CloseHandle(m_hThreadsend);
}
//��ͼ
void CNetViewTPShow::OnDraw(CDC* pDC)
{
	
	int n = 0;
	pDC->SelectObject(&m_cpenXu);//����
	if (m_nAlldataNumb != 0)
	{
		CRect rect;
		GetClientRect(rect); 
		m_TPDlgShowExplian.MoveWindow(rect.right - 220,rect.top + 50, 200 ,410);
	}
	for (n = 0; n<m_nAlldataNumb ;n++)
	{
		
		if(m_nLineType == 0)
		{
			if (m_nPointLine[n][1] != 0)
			{
				pDC->MoveTo(m_fCoordinate[m_nPointLine[n][0]][0],m_fCoordinate[m_nPointLine[n][0]][1]);
				pDC->LineTo(m_fCoordinate[m_nPointLine[n][1]][0],m_fCoordinate[m_nPointLine[n][1]][1]);
			}
		}
		else
		{
			if (m_nPointLine[n][1] != 0)
			{
				pDC->MoveTo(m_fCoordinate[m_nPointLine[n][0]][0],m_fCoordinate[m_nPointLine[n][0]][1]);
				pDC->LineTo(m_fCoordinate[m_nPointLine[n][0]][0],(m_fCoordinate[m_nPointLine[n][0]][1] - m_cTBWeith*4/5));
				pDC->LineTo(m_fCoordinate[m_nPointLine[n][1]][0],(m_fCoordinate[m_nPointLine[n][0]][1] - m_cTBWeith*4/5));
				pDC->LineTo(m_fCoordinate[m_nPointLine[n][1]][0],m_fCoordinate[m_nPointLine[n][1]][1]);
			}
		}
		
	}
	pDC->BeginPath();
	for (n = 1; n<m_nAlldataNumb + 1 ;n++)//��Բ�νڵ�
	{
		pDC->SelectObject(&m_BrushAll[m_nPointColor[m_nPointNumb[n-1]]]); 
		pDC->EndPath(); 
		pDC->Ellipse(m_fCoordinate[m_nPointNumb[n-1]][0] - m_cR,m_fCoordinate[m_nPointNumb[n-1]][1] - m_cR,m_fCoordinate[m_nPointNumb[n-1]][0] + m_cR,m_fCoordinate[m_nPointNumb[n-1]][1] + m_cR); 
	}

	pDC->SelectObject(&m_RrushFont);
	pDC->SetBkMode(TRANSPARENT); 
	LOGFONT lf;
	memset(&lf, 0, sizeof(lf));
	lf.lfHeight = -MulDiv(m_fFont, pDC->GetDeviceCaps(LOGPIXELSY), 72);
	lf.lfWeight = FW_NORMAL;
	lf.lfOutPrecision = OUT_TT_ONLY_PRECIS;
	CFont newFont;
	newFont.CreateFontIndirect(&lf);
	pDC->BeginPath();
	pDC->SelectObject(&newFont);
	CString str;
	float fFont = 0;
	for (n = 1; n<m_nAlldataNumb + 1 ;n++)//�ڵ��� 
	{
		str.Format(_T("%d") , m_nPointLine[n - 1][0]);
		switch(str.GetLength())
		{
		case 1:
			fFont = m_cR/4;
			break;
		case 2:
			fFont = m_cR/2;
			break;
		case 3:
			fFont = m_cR*6/7;
			break;
		}
		pDC->TextOut(m_fCoordinate[m_nPointNumb[n-1]][0]- fFont, m_fCoordinate[m_nPointNumb[n-1]][1]- m_cR/2,str);
	}
	pDC->EndPath();
	pDC->FillPath(); 
}
//��ڵ�����
void CNetViewTPShow::GetPointCoordinate(CString strTableName)
{
	CMainFrame* pMain= (CMainFrame*)AfxGetApp()->GetMainWnd();
	CString strAllDatalist[MODUMAXNUMB][6];
	int nNumb = 0 , nAlldataNumb;
	CString strWhere = _T("");
	CString strAll = _T("");//���нڵ�Ĳ㼶����"$"���
	int nCeng = 15;//������
	CString strCeng = _T("");
	int n = 0 , m = 0 , i = 0;
	int nChildNumb = 0;
	float fChildWeith = 0;
	float fWeith[MODUMAXNUMB];
	//ͬһ���ͽڵ��������
	for(m = 0 ; m < 10 ; m++)
	{
		m_nOnlineNumb[m] = 0;
	}
	//�����ݿ�����ȡ������Ϣ
	m_access.SelectDataFromTable(pMain->m_PeiZhi_db , strTableName , _T("TP_MAC,TP_TEI,TP_PTEI,TP_ROLE,TP_TIER,TP_READSUCCESS") ,_T("") ,m_strlist ,nAlldataNumb);
	//m_access.SelectDataFromTable(_T(".\\�����ļ�\\13762Data.accdb") , strTableName , _T("TP_MAC,TP_TEI,TP_PTEI,TP_ROLE,TP_TIER,TP_READSUCCESS") ,_T("") ,m_strlist ,nAlldataNumb);
	m_nAlldataNumb = nAlldataNumb;
	for(n = 0 ; n < nAlldataNumb ; n++)
	{
		m_tools.Split(m_strlist[n] , _T("$") ,strAllDatalist[n] , nNumb);
	}

	//ͳ��ͬһ���ͽڵ��������ȡTEI��PTEI��Ϣ
	for(n = 0 ; n < nAlldataNumb ; n++)
	{
		switch(_ttoi(strAllDatalist[n][3]))
		{
		case 2:
			m_nOnlineNumb[0] += 1;
			break;
		case 3:
			m_nOnlineNumb[1] += 1;
			break;
		case 4:
			m_nOnlineNumb[2] += 1;
			break;
		case 5:
			m_nOnlineNumb[3] += 1;
			break;
		case 6:
			m_nOnlineNumb[4] += 1;
			break;
		case 7:
			m_nOnlineNumb[5] += 1;
			break;
		}
		m_nPointNumb[n] = _ttoi(strAllDatalist[n][1]);
		m_nPointLine[n][0] = _ttoi(strAllDatalist[n][1]);
		m_nPointLine[n][1] = _ttoi(strAllDatalist[n][2]);
		strAll += strAllDatalist[n][4] + _T("$");
	}
	//��ȡ�������㼶
	while(true)
	{
		strCeng.Format(_T("%d") , nCeng);
		if(strAll.Find(strCeng) != -1)
		{
			break;
		}
		nCeng -= 1;
	}

	//��ȡ�����ڵ㼰�ڵ����ռ���
	for(i = 0 ; i < nCeng; i++)
	{
		strCeng.Format(_T("%d") , nCeng-i);
		for(n = 0 ; n < nAlldataNumb ; n++)
		{
			nChildNumb = 0;
			fChildWeith = 0;
			//����߲㿪ʼ��ȡ
			if (strAllDatalist[n][4] == strCeng)
			{
				//��ȡ�Ӽ��ܿ��
				for(m = 0 ; m < nAlldataNumb ; m++)
				{
					if (strAllDatalist[n][1] == strAllDatalist[m][2])
					{
						nChildNumb++; //��nChildNumb���Ӽ�
						fChildWeith += m_fPointWeith[_ttoi(strAllDatalist[m][1])];
					}
				}
				//��ȡ�Լ��Ŀ��
				if (nChildNumb == 0)
				{
					m_fPointWeith[_ttoi(strAllDatalist[n][1])] = m_cR * 2 + m_cLRWeith;
				}
				else
				{
					m_fPointWeith[_ttoi(strAllDatalist[n][1])] = fChildWeith;
				}
			}
		}
	}

	
	//��ȡÿ���ڵ����꣬�ӵ�һ�㿪ʼ��ȡ
	for (i = 1 ; i < nCeng + 1 ; i++)
	{
		for(m = 0 ; m < MODUMAXNUMB ; m++)
		{
			fWeith[m] = 0;
		}
	
		for(n = 0 ; n < nAlldataNumb ; n++)
		{
			if (_ttoi(strAllDatalist[n][4]) == i)
			{
				m_nPointColor[_ttoi(strAllDatalist[n][1])] =  _ttoi(strAllDatalist[n][3]);//���ݽ�ɫƥ����ɫ
				m_fCoordinate[_ttoi(strAllDatalist[n][1])][1] = (i)* (m_cTBWeith + 2*m_cR);//��ȡ�ڵ�Y����
				//��ȡ�ڵ�X����
				if (_ttoi(strAllDatalist[n][4]) == 1)//����Ϊ1ʱΪ���ڵ�
				{
					m_fCoordinate[_ttoi(strAllDatalist[n][1])][0] = m_fPointWeith[_ttoi(strAllDatalist[n][1])]/2 + m_cLRWeith ;
				}
				else
				{
					m_fCoordinate[_ttoi(strAllDatalist[n][1])][0] = m_fCoordinate[_ttoi(strAllDatalist[n][2])][0] - m_fPointWeith[_ttoi(strAllDatalist[n][2])]/2 + m_fPointWeith[_ttoi(strAllDatalist[n][1])]/2 + fWeith[_ttoi(strAllDatalist[n][2])];
					fWeith[_ttoi(strAllDatalist[n][2])] += m_fPointWeith[_ttoi(strAllDatalist[n][1])];
				}
			}
		}
	}
	//���ݲ������ܿ����ҳ���С
	if (nCeng* (m_cTBWeith + 2*m_cR) > m_cy)
	{
		m_cy = (nCeng + 1)* (m_cTBWeith + 2*m_cR);
	}
	if (m_fPointWeith[1] + m_cRW > m_cx)
	{
		m_cx = m_fPointWeith[1] + m_cRW;
	}

	//SetScrollSizes(IDD_DIALOG_TUOPUSHOW , CSize(m_cx, m_cy));
	m_TPDlgShowExplian.GetNumb(m_nOnlineNumb);//���¸���ģ�����
	Invalidate();//ˢ��
}
//���ֹ���������С����ͼ
BOOL CNetViewTPShow::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	static float upLimit = 10.0f;
	static float downLinit = 0.04f;
	static float fUp = 1.1;
	static float fDown = 0.9f;
	bool bChange = true ;
	int n = 0;
	if(zDelta > 0 && m_Scale <= upLimit)
	{
		m_cx *= fUp;
		m_cy *= fUp;
		m_cR *= fUp;
		m_cTBWeith *= fUp;
		m_cLRWeith *= fUp;
		m_cRW *= fUp;
		m_fFont *= fUp;
		for( n = 1 ; n < m_nAlldataNumb + 1 ; n++)
		{
			m_fCoordinate[m_nPointNumb[n-1]][0] *= fUp;
			m_fCoordinate[m_nPointNumb[n-1]][1] *= fUp;
		}
		bChange = true;
	}
	else if(zDelta < 0 && m_Scale >= downLinit)
	{
		m_cx /= fUp;
		m_cy /= fUp;
		m_cR /= fUp;
		m_cTBWeith /= fUp;
		m_cLRWeith /= fUp;
		m_cRW /= fUp;
		if (m_fFont != 1)
		{
			m_fFont /= fUp;
		}
		for( n = 1 ; n < m_nAlldataNumb + 1 ; n++)
		{
			m_fCoordinate[m_nPointNumb[n-1]][0] /= fUp;
			m_fCoordinate[m_nPointNumb[n-1]][1] /= fUp;
		}
		bChange = false;
	}
	this->Invalidate();
	SetScrollSizes(IDD_DIALOG_TUOPUSHOW , CSize(m_cx, m_cy));
	return CFormView::OnMouseWheel(nFlags, zDelta, pt);
}
//�Ҽ��˵�
void CNetViewTPShow::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CMenu menu;
	if (m_bShow)
	{
		VERIFY(menu.LoadMenu(IDR_MENU_RBTP_JDMSG));
	}
	else
	{
		VERIFY(menu.LoadMenu(IDR_MENU_RBTP));
	}
	CMenu* pPopup = menu.GetSubMenu(0);
	ASSERT(pPopup != NULL);
	CWnd* pWndPopupOwner = this;
	if (!m_bShow)
	{
		if (m_nLineType == 0)
		{
			pPopup->CheckMenuItem(ID_LINE_ZHI,MF_CHECKED);
			pPopup->CheckMenuItem(ID_LINE_ZHIJIAO,MF_UNCHECKED);
		}
		else
		{
			pPopup->CheckMenuItem(ID_LINE_ZHI,MF_UNCHECKED);
			pPopup->CheckMenuItem(ID_LINE_ZHIJIAO,MF_CHECKED);
		}

		if (m_nMsgType == 0)
		{
			pPopup->CheckMenuItem(IDR_MENU_RBTP_SHOW,MF_CHECKED);
			pPopup->CheckMenuItem(IDR_MENU_RBTP_HEID,MF_UNCHECKED);
		}
		else
		{
			pPopup->CheckMenuItem(IDR_MENU_RBTP_SHOW,MF_UNCHECKED);
			pPopup->CheckMenuItem(IDR_MENU_RBTP_HEID,MF_CHECKED);
		}
		if (m_nMsgTJType == 0)
		{
			pPopup->CheckMenuItem(IDR_MENU_RBTP_TJSHOW,MF_CHECKED);
			pPopup->CheckMenuItem(IDR_MENU_RBTP_TJHIDE,MF_UNCHECKED);
		}
		else
		{
			pPopup->CheckMenuItem(IDR_MENU_RBTP_TJSHOW,MF_UNCHECKED);
			pPopup->CheckMenuItem(IDR_MENU_RBTP_TJHIDE,MF_CHECKED);
		}

		if (m_bAutoUpdata)
		{
			pPopup->CheckMenuItem(ID_RBTP_AUTOUPDATA,MF_CHECKED);
		}
		else
		{
			pPopup->CheckMenuItem(ID_RBTP_AUTOUPDATA,MF_UNCHECKED);
		}
		if (m_bSave)
		{
			pPopup->CheckMenuItem(ID_RBTP_SAVE,MF_CHECKED);
		}
		else
		{
			pPopup->CheckMenuItem(ID_RBTP_SAVE,MF_UNCHECKED);
		}
	}
	while (pWndPopupOwner->GetStyle() & WS_CHILD)
		pWndPopupOwner = pWndPopupOwner->GetParent();
	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
		pWndPopupOwner);
	
}

void CNetViewTPShow::SetTPdataToAccess(CString strTPdata)
{
	CMainFrame* pMain= (CMainFrame*)AfxGetApp()->GetMainWnd();
	INT8U SucceBuf[3];
	INT16U temp16 = 0;
	CString  strMAC ,strTEI ,strPTEI, strRole , strLayer , strSuccess;
	CTools tools;
	CString strlistName[6] = {_T("TP_MAC") ,_T("TP_TEI") ,_T("TP_PTEI") ,_T("TP_ROLE") ,_T("TP_TIER")  ,_T("TP_READSUCCESS")};
	CString strlistData[6];
	CTime timeNow = CTime::GetCurrentTime();
	CString strTime = timeNow.Format("%Y%m%d%H%M%S") , strName , strData;
	
	char szANSIString[5000]; 
	FILE* file_tpmap;
	CString strCSVTime = timeNow.Format("%Y%m%d%H%M%S");  //CSV ����

	if (m_bSave)
	{
		CString strNewlistName[6] = {_T("TP_MAC TEXT") ,_T("TP_TEI TEXT") ,_T("TP_PTEI TEXT") ,_T("TP_ROLE TEXT") ,_T("TP_TIER TEXT")  ,_T("TP_READSUCCESS TEXT")};
		strName = _T("HISTTPNAME");
		strData = strTime.Mid(2);
		m_access.AddDataToTable(_T(".\\�����ļ�\\HistTPShow.accdb") , _T("HISTTPNAME") , &strName , &strData ,1);
		m_access.CreatTable(_T(".\\�����ļ�\\HistTPShow.accdb") ,strData ,strNewlistName ,6);//����ʱ���ַ���������

//--------------CSV ����----------------------------------------
		strCSVTime = _T(".\\��־\\TOPMap") + strCSVTime + _T(".csv");
		int len =WideCharToMultiByte(CP_ACP,0,strCSVTime,strCSVTime.GetLength(),NULL,0,NULL,NULL);
		char * pFileName = new char[len+1];
		
		WideCharToMultiByte(CP_ACP,0,strCSVTime,strCSVTime.GetLength(),pFileName,len,NULL,NULL);
		pFileName[len+1] ='\0';
		
		file_tpmap=fopen(pFileName,"r");
		if  ( file_tpmap == NULL )
		{
			file_tpmap=fopen(pFileName,"a+");
		}
		else
		{
			fclose(file_tpmap); 
			file_tpmap=fopen(pFileName,"a+");
		} 
		CString strTopLine = _T("        TP_MAC,TP_TEI,TP_PTEI,TP_ROLE,TP_TIER,TP_READSUCCESS\n");
		WideCharToMultiByte(CP_ACP,WC_COMPOSITECHECK,strTopLine,-1,szANSIString,sizeof(szANSIString),NULL,NULL);
		fwrite(szANSIString,wcslen(strTopLine),1,file_tpmap);
//--------------------------------------------------------------
	}
	int nNumb = strTPdata.GetLength()/24;//strTPdata.GetLength()/28;
	//m_access.DelectDataFromTable(_T(".\\�����ļ�\\13762Data.accdb"),_T("TPShow"),_T(""));
	m_access.DelectDataFromTable(pMain->m_PeiZhi_db,_T("TPShow"),_T(""));
	for(int n = 0 ; n < nNumb ; n++)
	{

		strTEI = strTPdata.Mid(0 , 4);
		strlistData[1] = tools._str16tostr10(tools._strDaoxu(strTEI));
		if(strTEI=="0100"){
			strRole.Format(_T("%d"),2); 
		}
		else{
		    strRole.Format(_T("%d"),4); 
		}
		strlistData[3] = tools._str16tostr10(strRole);//

		strPTEI = strTPdata.Mid(4 , 4);
		strlistData[2] = tools._str16tostr10(tools._strDaoxu(strPTEI));

		strMAC = strTPdata.Mid(8 , 12);
		strlistData[0] = strMAC;//tools._strDaoxu(strMAC);

		//strRole = strTPdata.Mid(20 , 2);//��ɫ��·�ɲ㼶  ��CKQ�ĳ���λ��·�ɲ㼶 ��λ��
		//strRole.Format(_T("%d"),(_ttoi(strRole)+1)*2); 
		//strlistData[3] = tools._str16tostr10(strRole);//

		strLayer = strTPdata.Mid(22 , 2);//��ɫ��·�ɲ㼶 ��CKQ�ĳ���λ��·�ɲ㼶  

		strLayer.Format(_T("%d"),_ttoi(strLayer)+1); 
        
		strlistData[4] = tools._str16tostr10(strLayer);//·�ɲ㼶

		strlistData[5] = "99";//m_tools._str16tostr10("11");


		if (strlistData[0].Mid(0,10) != "0102030405")//�жϱ��ַ
		{
			m_access.AddDataToTable(pMain->m_PeiZhi_db,_T("TPShow"),strlistName , strlistData ,6);
			//m_access.AddDataToTable(_T(".\\�����ļ�\\13762Data.accdb"),_T("TPShow"),strlistName , strlistData ,6);
		}

		if (m_bSave)
		{
			m_access.AddDataToTable(_T(".\\�����ļ�\\HistTPShow.accdb") ,strData ,strlistName ,strlistData ,6);
		}
//--------------CSV ����----------------------------------------
		if (m_bSave)
		{
			CString strTopLine = strlistData[0] + _T(",") + strlistData[1] + _T(",") + strlistData[2] + _T(",") + strlistData[3] + _T(",") + strlistData[4] + _T(",") + strlistData[5] + _T("\n");
			WideCharToMultiByte(CP_ACP,WC_COMPOSITECHECK,strTopLine,-1,szANSIString,sizeof(szANSIString),NULL,NULL);
			fwrite(szANSIString,wcslen(strTopLine),1,file_tpmap);
		}
//--------------------------------------------------------------

		strTPdata = strTPdata.Mid(24);
	}
//--------------CSV ����----------------------------------------
	if (m_bSave)
	{
		if  ( file_tpmap != NULL )
		{
			fclose(file_tpmap);
		}
	}
//--------------------------------------------------------------

}
void CNetViewTPShow::SetTPdataToAccess_10F21(CString strTPdata)
{
	CMainFrame* pMain= (CMainFrame*)AfxGetApp()->GetMainWnd();
	INT8U SucceBuf[3];
	INT16U temp16 = 0;
	CString  strMAC ,strTEI ,strPTEI, strRole , strLayer , strSuccess;
	CTools tools;
	CString strlistName[6] = {_T("TP_MAC") ,_T("TP_TEI") ,_T("TP_PTEI") ,_T("TP_ROLE") ,_T("TP_TIER")  ,_T("TP_READSUCCESS")};
	CString strlistData[6];
	CTime timeNow = CTime::GetCurrentTime();
	CString strTime = timeNow.Format("%Y%m%d%H%M%S") , strName , strData;
	
	char szANSIString[5000]; 
	FILE* file_tpmap;
	CString strCSVTime = timeNow.Format("%Y%m%d%H%M%S");  //CSV ����

	if (m_bSave)
	{
		CString strNewlistName[6] = {_T("TP_MAC TEXT") ,_T("TP_TEI TEXT") ,_T("TP_PTEI TEXT") ,_T("TP_ROLE TEXT") ,_T("TP_TIER TEXT")  ,_T("TP_READSUCCESS TEXT")};
		strName = _T("HISTTPNAME");
		strData = strTime.Mid(2);
		m_access.AddDataToTable(_T(".\\�����ļ�\\HistTPShow.accdb") , _T("HISTTPNAME") , &strName , &strData ,1);
		m_access.CreatTable(_T(".\\�����ļ�\\HistTPShow.accdb") ,strData ,strNewlistName ,6);

//--------------CSV ����----------------------------------------
		strCSVTime = _T(".\\��־\\TOPMap") + strCSVTime + _T(".csv");
		int len =WideCharToMultiByte(CP_ACP,0,strCSVTime,strCSVTime.GetLength(),NULL,0,NULL,NULL);
		char * pFileName = new char[len+1];
		
		WideCharToMultiByte(CP_ACP,0,strCSVTime,strCSVTime.GetLength(),pFileName,len,NULL,NULL);
		pFileName[len+1] ='\0';
		
		file_tpmap=fopen(pFileName,"r");
		if  ( file_tpmap == NULL )
		{
			file_tpmap=fopen(pFileName,"a+");
		}
		else
		{
			fclose(file_tpmap); 
			file_tpmap=fopen(pFileName,"a+");
		} 
		CString strTopLine = _T("        TP_MAC,TP_TEI,TP_PTEI,TP_ROLE,TP_TIER,TP_READSUCCESS\n");
		WideCharToMultiByte(CP_ACP,WC_COMPOSITECHECK,strTopLine,-1,szANSIString,sizeof(szANSIString),NULL,NULL);
		fwrite(szANSIString,wcslen(strTopLine),1,file_tpmap);
//--------------------------------------------------------------
	}
	int nNumb = strTPdata.GetLength()/22;
	//m_access.DelectDataFromTable(_T(".\\�����ļ�\\13762Data.accdb"),_T("TPShow"),_T(""));
	m_access.DelectDataFromTable(pMain->m_PeiZhi_db,_T("TPShow"),_T(""));
	for(int n = 0 ; n < nNumb ; n++)
	{
		
		strMAC = strTPdata.Mid(0 , 12);
		strlistData[0] = tools._strDaoxu(strMAC);

		strTEI = strTPdata.Mid(12 , 4);
		strlistData[1] = tools._str16tostr10(tools._strDaoxu(strTEI));

		strPTEI = strTPdata.Mid(16 , 4);
		strlistData[2] = tools._str16tostr10(tools._strDaoxu(strPTEI));

		strRole = strTPdata.Mid(20 , 2);
		CString str;
		if(tools._str16tostr10(strRole.Mid(0 ,1))=="4"){
			str.Format(_T("%d"),2); 
		}
		else if(tools._str16tostr10(strRole.Mid(0 ,1))=="2"){
		    str.Format(_T("%d"),4); 
		}
		strlistData[3] = tools._str16tostr10(str);

		strLayer= tools._str16tostr10(strRole.Mid(1 ,1));
		strLayer.Format(_T("%d"),_ttoi(strLayer)+1); 
		strlistData[4] = tools._str16tostr10(strLayer);//·�ɲ㼶
		strlistData[5] = "99";


		if (strlistData[0].Mid(0,10) != "0102030405")
		{
			m_access.AddDataToTable(pMain->m_PeiZhi_db,_T("TPShow"),strlistName , strlistData ,6);
			//m_access.AddDataToTable(_T(".\\�����ļ�\\13762Data.accdb"),_T("TPShow"),strlistName, strlistData ,6);
		}

		if (m_bSave)
		{
			m_access.AddDataToTable(_T(".\\�����ļ�\\HistTPShow.accdb") ,strData ,strlistName ,strlistData ,6);
		}
//--------------CSV ����----------------------------------------
		if (m_bSave)
		{
			CString strTopLine = strlistData[0] + _T(",") + strlistData[1] + _T(",") + strlistData[2] + _T(",") + strlistData[3] + _T(",") + strlistData[4] + _T(",") + strlistData[5] + _T("\n");
			WideCharToMultiByte(CP_ACP,WC_COMPOSITECHECK,strTopLine,-1,szANSIString,sizeof(szANSIString),NULL,NULL);
			fwrite(szANSIString,wcslen(strTopLine),1,file_tpmap);
		}
//--------------------------------------------------------------

		strTPdata = strTPdata.Mid(28);
	}
//--------------CSV ����----------------------------------------
	if (m_bSave)
	{
		if  ( file_tpmap != NULL )
		{
			fclose(file_tpmap);
		}
	}
//--------------------------------------------------------------

}
//ˢ������ͼ
void CNetViewTPShow::OnRbtpUpdata()
{
	if (m_nUpdataTime == 0)
	{
		m_bAutoUpdata = true;
	}
}
//��������ͼ���ݿ�
void CNetViewTPShow::OnCooChange()
{
	CDlgCCOTPchange dlgCCOchange;
	dlgCCOchange.DoModal();
}
//ֱ������
void CNetViewTPShow::OnLineZhi()
{
	m_nLineType = 0;
	this->Invalidate();
}
//ֱ��������
void CNetViewTPShow::OnLineZhijiao()
{
	m_nLineType = 1;
	this->Invalidate();
}
//�ƶ������ʾ�ڵ���Ϣ
void CNetViewTPShow::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	int nX  = point.x , nY = point.y , m = 0;
	CClientDC dc(this); //��ȡ�豸
	OnPrepareDC( &dc ); //׼���豸
	dc.DPtoLP( &point ); //���ת��
	nX = point.x - nX;
	nY = point.y - nY;
	CString str = _T("");
	for(int n = 0 ; n < m_nAlldataNumb ; n++)
	{
		if ((point.x > (m_fCoordinate[m_nPointNumb[n]][0] - m_cR/2))&&(point.x < (m_fCoordinate[m_nPointNumb[n]][0] + m_cR/2))&&
			(point.y > (m_fCoordinate[m_nPointNumb[n]][1] - m_cR/2))&&(point.y < (m_fCoordinate[m_nPointNumb[n]][1] + m_cR/2)))
		{
			if (!m_bShow)
			{
				int nNumb = 0;
				CString strAllDatalist[MODUMAXNUMB][10];
				str.Format(_T("%d"),m_nPointNumb[n]);
				for(m = 0 ; m < m_nAlldataNumb ; m++)
				{
					m_tools.Split(m_strlist[m] , _T("$") ,strAllDatalist[m] , nNumb);
					if (strAllDatalist[m][1] == str) break;
				}
				if (strAllDatalist[m][0].Mid(0,10) == "BEBEBEBEBE")
				{
					strAllDatalist[m][3] += _T("(������)");
				}
				m_strPMessage = _T("MAC��ַ:") + strAllDatalist[m][0] + _T("\r\n") + 
					  _T("TEI:") + strAllDatalist[m][1] + _T("\r\n") + 
					  _T("����TEI:") + strAllDatalist[m][2] + _T("\r\n") + 
					  _T("��ɫ:") + strAllDatalist[m][3] + _T("\r\n") + 
					  _T("�㼶:") + strAllDatalist[m][4] + _T("\r\n") + 
					  _T("����ɹ���:") + strAllDatalist[m][5] + _T("%");// + _T("\r\n") + 
					//  _T("STATUS:") + strAllDatalist[m][6];
				m_TPDlgJDMsg.SetWindowPos(NULL,m_fCoordinate[m_nPointNumb[n]][0] - nX,m_fCoordinate[m_nPointNumb[n]][1] - nY,180,160,SWP_SHOWWINDOW);
				m_TPDlgJDMsg.m_editMsg.SetWindowTextW(m_strPMessage);
				m_bShow = true;
				m_strChooseMAC = strAllDatalist[m][0];
			}
			CFormView::OnMouseMove(nFlags, point);
			return;
		}
	}
	m_bShow = false;
	m_TPDlgJDMsg.ShowWindow(SW_HIDE);
	CFormView::OnMouseMove(nFlags, point);
}

DWORD WINAPI ThreadSendTPFindlist (PVOID pParam) 
{
	//
	//�˴�Ϊ�Ҽ��������б�ִ�к�������δ�޸�
	CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CNetViewTPShow * pView = (CNetViewTPShow *)pParam;
	INT16U u16BeginNumb = 0;//u16temp = 0 , 
	INT8U SendDatabuf[10];
	INT8U ack = 0 , u8SendAFN = 0 ,AddrBuf[7] , u8ReadCount = 0;
	INT16U SendDatalen = 0 ,temp16 = 0;
	CString strAllTPdata =_T("");
    if (pMain->NW_OR_GW==1){ //������׼
		sPartQCSG376_2CreatFrame ptSendQCSG376_2;
		sPartQCSG376_2DeCodeFrame ptRecvQCSG376_2;
		bool bOK = true;
		pView->m_tools._str16tobuf16( pMain->m_strMAddress , AddrBuf , temp16 , true);//�ַ���תbuf
		SendDatabuf[0] = 0;
		SendDatabuf[1] = 0;
		SendDatabuf[2] = 0x14;
		SendDatalen = 3;
		while(bOK)
		{
			ack = gSimJzq.HostSendRcv376_2F0F8(AddrBuf , 0xF0 , F11 , SendDatabuf , SendDatalen , pView->m_ptSendQCSG376_2,ptRecvQCSG376_2 , pView->m_ptRecvQCSG376_2);
			switch(ack)
			{
			case 0x00://�ɹ�
				strAllTPdata += pView->m_tools._buf16tostr16(&pView->m_ptRecvQCSG376_2.s_RcvDataBuf[5] , pView->m_ptRecvQCSG376_2.s_RcvDataLen -5);//bufת�ַ���
				temp16 = pView->m_ptRecvQCSG376_2.s_RcvDataBuf[1] << 8 | pView->m_ptRecvQCSG376_2.s_RcvDataBuf[0];
				if (temp16 <= SendDatabuf[2])
				{
					bOK = false;
				}
				else
				{
					u16BeginNumb += 0x14;
					SendDatabuf[0] = u16BeginNumb;
					SendDatabuf[1] = u16BeginNumb >> 8;
				}
				break;
			}
		}
	}
	else{
		sPartQGDW376_2CreatFrame ptSendQGDW376_2;
		sPartQGDW376_2DeCodeFrame ptRecvQGDW376_2;
		bool bOK = true;
		pView->m_tools._str16tobuf16( pMain->m_strMAddress , AddrBuf , temp16 , true);//�ַ���תbuf
		SendDatabuf[0] = 0;
		SendDatabuf[1] = 0;
		SendDatabuf[2] = 0x14;
		SendDatalen = 3;
		while(bOK)
		{
			ack = gSimJzq.HostSendRcv376_2F0F8(AddrBuf , 0xF0 , F11 , SendDatabuf , SendDatalen , pView->m_ptSendQGDW376_2,ptRecvQGDW376_2 , pView->m_ptRecvQGDW376_2);
			switch(ack)
			{
			case 0x00://�ɹ�
				strAllTPdata += pView->m_tools._buf16tostr16(&pView->m_ptRecvQGDW376_2.s_RcvDataBuf[5] , pView->m_ptRecvQGDW376_2.s_RcvDataLen -5);//bufת�ַ���
				temp16 = pView->m_ptRecvQGDW376_2.s_RcvDataBuf[1] << 8 | pView->m_ptRecvQGDW376_2.s_RcvDataBuf[0];
				if (temp16 <= SendDatabuf[2])
				{
					bOK = false;
				}
				else
				{
					u16BeginNumb += 0x14;
					SendDatabuf[0] = u16BeginNumb;
					SendDatabuf[1] = u16BeginNumb >> 8;
				}
				break;
			}
		}
	}
	pView->m_TPShowFindList.SetTPdataToAccess(strAllTPdata);
	return 0;
}
//�ڵ��Ҽ������б�˵�����¼�
void CNetViewTPShow::OnRbtpjdmsgFindlist()
{
	CRect rect;
	GetClientRect(rect); 
	m_TPShowFindList.SetWindowPos(NULL,rect.left,rect.top,rect.right,rect.bottom,SWP_SHOWWINDOW);
	m_TPShowFindList.ShowWindow(SW_SHOWMAXIMIZED);
	m_TPShowFindList.m_staticPMessage.SetWindowTextW(m_strPMessage);
	m_TPDlgJDMsg.ShowWindow(SW_HIDE);
	CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
	if (pMain->m_bConnected == TRUE)
	{
		if (pMain->m_strMAddress != "")
		{
			m_hThreadsend=CreateThread (NULL,0,ThreadSendTPFindlist,this,0,NULL);
			CloseHandle(m_hThreadsend);
		}
		else
		{
			AfxMessageBox(_T("��������CCO��"));
		}
	}
	else
	{
		AfxMessageBox(_T("���ȴ򿪴��ڣ�"));
	}
}

void CNetViewTPShow::OnIdrMenuRbtpShow()
{
	m_nMsgType = 0;
	m_TPDlgShowExplian.GetNumb(m_nOnlineNumb);
	m_TPDlgShowExplian.ShowWindow(SW_SHOW);
}

void CNetViewTPShow::OnIdrMenuRbtpHeid()
{
	m_nMsgType = 1;
	m_TPDlgShowExplian.ShowWindow(SW_HIDE);
}

void CNetViewTPShow::OnIdrMenuRbtpTJShow()
{
	m_nMsgTJType = 0;
	//m_DlgTongJiNode.GetListMsg(CString nnnn);
	m_DlgTongJiNode.ShowWindow(SW_SHOW);
}

void CNetViewTPShow::OnIdrMenuRbtpTJHeid()
{
	m_nMsgTJType = 1;
	m_DlgTongJiNode.ShowWindow(SW_HIDE);
}

void CNetViewTPShow::OnRbtpTest()
{
	GetPointCoordinate(_T("CCOTPShow"));
}

void CNetViewTPShow::OnRbtpjdmsgPtp()
{
	CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CFrameSetNet * pChildFrm =  ( CFrameSetNet *) pMain->GetActiveFrame();
	CRightTabView *  pTabView =( CRightTabView *) pChildFrm->m_wndSplitter.GetPane(0 , 1);
	pTabView->SetActiveView(2);
	CNetViewPToP * pViewPTP = (CNetViewPToP *)pTabView->GetActiveView();
	pViewPTP->m_editMAC1.SetWindowText(m_strChooseMAC);
}

BOOL CNetViewTPShow::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	switch(pMsg->message)
	{
	case WM_KEYDOWN:
		switch(pMsg->wParam)
		{
		case VK_ESCAPE:
			break;
		case VK_RETURN:
			break;
		}
		break;
	case WM_CHAR:
		switch(pMsg->wParam)
		{
		case VK_ESCAPE:
			break;
		case VK_RETURN:
			break;
		}
		break;
	}
	return CFormView::PreTranslateMessage(pMsg);
}

void CNetViewTPShow::OnRbtpAutoupdata()
{
	if (m_bAutoUpdata)
	{
		m_bAutoUpdata = false;
		m_nUpdataTime = 0;
	}
	else
	{
		CDlgCKQUpdataTime dlgUpdataTime;
		if (dlgUpdataTime.DoModal() == IDOK)
		{
			m_nUpdataTime = _ttoi(dlgUpdataTime.m_strTime);
			m_bAutoUpdata = true;
		}
	}
	
}

void CNetViewTPShow::OnRbtpSave()
{
	if (m_bSave)
	{
		m_bSave = false;
	}
	else
	{
		m_bSave = true;
	}
}
