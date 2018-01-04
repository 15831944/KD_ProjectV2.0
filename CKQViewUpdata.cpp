// CKQViewUpdata.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "KD_Project.h"
#include "CKQViewUpdata.h"
#include "AccessData.h"
#include "MainFrm.h"
#include "SimJzq.h"
extern CSimJzq  gSimJzq;

IMPLEMENT_DYNCREATE(CCKQViewUpdata, CFormView)


CCKQViewUpdata::CCKQViewUpdata()
	: CFormView(CCKQViewUpdata::IDD)
{

}

CCKQViewUpdata::~CCKQViewUpdata()
{
}


void CCKQViewUpdata::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_LIST_DATA, m_listShowMsg);
	//  DDX_Control(pDX, IDC_LIST1, m_listData1);
	DDX_Control(pDX, IDC_RADIO_TYPE, m_radioUpType);
	DDX_Control(pDX, IDC_EDIT_FILE, m_editFile);
	DDX_Control(pDX, IDC_BTN_BEGINUPDATA, m_btnSend);
	DDX_Control(pDX, IDC_COMBO1, m_upType);
}

BEGIN_MESSAGE_MAP(CCKQViewUpdata, CFormView)
	ON_BN_CLICKED(IDC_BTN_CHOOSEFILE, &CCKQViewUpdata::OnBnClickedBtnChoosefile)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTN_REFRESH, &CCKQViewUpdata::OnBnClickedBtnRefresh)
	ON_BN_CLICKED(IDC_BTN_BEGINUPDATA, &CCKQViewUpdata::OnBnClickedBtnBeginupdata)
	ON_COMMAND(IDC_BTN_BEGINUPDATA2, &CCKQViewUpdata::OnBtnBeginupdata2)
	ON_COMMAND(ID_MODERR_UPDATA1, &CCKQViewUpdata::OnModerrUpdata1)
	ON_COMMAND(ID_shuaxinLB, &CCKQViewUpdata::Onshuaxinlb)
	ON_COMMAND(ID_32846, &CCKQViewUpdata::OnAddNode)
END_MESSAGE_MAP()


// CCKQViewUpdata ���

#ifdef _DEBUG
void CCKQViewUpdata::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CCKQViewUpdata::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CCKQViewUpdata ��Ϣ�������
HBRUSH CCKQViewUpdata::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	switch(pWnd->GetDlgCtrlID())
	{
	}
	return hbr;
}

void CCKQViewUpdata::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	SetNewFont();

	CRect rect;
	CRect rect1;
	GetClientRect(rect1);
	GetDlgItem(IDC_BTN_BEGINUPDATA)->GetWindowRect(rect);
	ScreenToClient(&rect);
	rect1.left += 10;
	rect1.top = rect.bottom + 10;
	rect1.right -= 10;
	rect1.bottom -= 10;
	m_listData.Create(WS_CHILD|WS_VISIBLE|LVS_REPORT|LVS_SHOWSELALWAYS| LVS_SINGLESEL|WS_BORDER ,rect1,this,IDC_LISTUPDATAMSG);//| LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_CHECKBOXES
	//m_listData.InsertColumn(0,_T(""),LVCFMT_LEFT,20);
	m_listData.InsertColumn(0,_T(""),LVCFMT_LEFT,30);
	m_listData.InsertColumn(1,_T("MAC��ַ"),LVCFMT_CENTER,200);
	m_listData.InsertColumn(2,_T("TEI"),LVCFMT_CENTER,200);
	m_listData.InsertColumn(4,_T("��������"),LVCFMT_CENTER,100);
	m_listData.InsertColumn(5,_T("����"),LVCFMT_CENTER,100);
	m_listData.InsertColumn(6,_T("��ʱ"),LVCFMT_CENTER,100);
	m_listData.InsertColumn(7,_T("�汾��"),LVCFMT_CENTER,200);
	m_listData.InsertColumn(8,_T("��ע"),LVCFMT_CENTER,200);
	m_listData.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_listData.m_nChooseList = 2;
	m_radioUpType.SetCheck(TRUE);
	m_upType.AddString(_T("������͸��MSDU"));
	m_upType.AddString(_T("������ת��376.2"));
	m_upType.SetCurSel(0);
	// TODO: �ڴ����ר�ô����/����û���
}

void CCKQViewUpdata::SetNewFont()
{
	LOGFONT lf;  //�߼�����ṹ
	::ZeroMemory(&lf,sizeof(lf));
	lf.lfHeight = 20;
	lf.lfWidth= 0;
	lf.lfEscapement = 0;
	lf.lfOrientation = 0;
	lf.lfWeight = FW_BOLD;
	lf.lfItalic = FALSE;
	lf.lfUnderline = FALSE;
	lf.lfStrikeOut= FALSE;
	lf.lfCharSet = DEFAULT_CHARSET;
	lf.lfOutPrecision = OUT_DEFAULT_PRECIS;
	lf.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	lf.lfQuality = DEFAULT_QUALITY;
	lf.lfPitchAndFamily = VARIABLE_PITCH | FF_ROMAN;
}

void CCKQViewUpdata::OnBnClickedBtnChoosefile()
{
	CString OpenFilePathName;
	CFileDialog dlg(TRUE,NULL,NULL,OFN_NOCHANGEDIR);
	int nOK=dlg.DoModal();
	if (nOK == IDOK)
	{
		OpenFilePathName = dlg.GetPathName();
		int len =WideCharToMultiByte(CP_ACP,0,OpenFilePathName,OpenFilePathName.GetLength(),NULL,0,NULL,NULL);
		char * pFileName = new char[len + 1];
		WideCharToMultiByte(CP_ACP,0,OpenFilePathName,OpenFilePathName.GetLength(),pFileName,len,NULL,NULL);
		pFileName[len+1] ='\0';
		m_editFile.SetWindowText(OpenFilePathName);
		m_btnSend.EnableWindow(TRUE);
	}
}
DWORD WINAPI ThreadSendRefresh (PVOID pParam)
{
	CMainFrame* pMain= (CMainFrame*)AfxGetApp()->GetMainWnd();
	CCKQViewUpdata * pView = (CCKQViewUpdata *)pParam;
	CAccessData access;
	CString strAllDatalist[6];
	CString strlist[1000];
	CString str;
	int nNumb = 0 , nAlldataNumb , nCount;

	////////////////��ȡ�ڵ��б�����������start
	INT8U ack = 0;
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
					//int num=ptDeCodeCKQ2017.s_RcvDataBuf[2]*256+ptDeCodeCKQ2017.s_RcvDataBuf[3];
					strAllTPdata += pView->m_tools._buf16tostr16(&ptDeCodeCKQ2017.s_RcvDataBuf[4] , ptDeCodeCKQ2017.s_RcvDataLen -4);
					if(ptDeCodeCKQ2017.s_RcvDataBuf[1]==1){
						pView->SaveNetDataToAccess(strAllTPdata);
						break;
					}
				}
				else{
                    break;
				}
			}
	}


	//////////////////end

	
	pView->m_listData.DeleteAllItems();
	access.SelectDataFromTable(pMain->m_PeiZhi_db, _T("TPShow") , _T("TP_MAC,TP_TEI") ,_T("") ,strlist ,nAlldataNumb);
	//access.SelectDataFromTable(_T(".\\�����ļ�\\13762Data.accdb") , _T("TPShow") , _T("TP_MAC,TP_ROLE") ,_T("") ,strlist ,nAlldataNumb);
	//m_listData.InsertItem(nAlldataNumb, _T(""));
	for (int n = 0 ; n < nAlldataNumb ; n++)
	{
		str.Format(_T("%d") , n + 1);
		pView->m_tools.Split(strlist[n] , _T("$") ,strAllDatalist , nNumb);
		if (strAllDatalist[0].Mid(0 , 10) != "0102030405")
		{
			//nCount = m_listData.GetItemCount();
			pView->m_listData.InsertItem(n, _T(""));
			pView->m_listData.SetItemText(n , 0 ,str);
			pView->m_listData.SetItemText(n ,1,strAllDatalist[0]);
			pView->m_listData.SetItemText(n ,2,strAllDatalist[1]);
			pView->m_listData.SetItemText(n ,3,_T("0"));
		}
	}
	return 0;
}



void CCKQViewUpdata::SaveNetDataToAccess(CString strTPdata)
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
	int nNumb = strTPdata.GetLength()/24;
	m_accessData.DelectDataFromTable(pMain->m_PeiZhi_db,_T("TPShow"),_T(""));
	for(int n = 0 ; n < nNumb ; n++)
	{
		
		strTEI = strTPdata.Mid(0 , 4);
		strlistData[1] = tools._str16tostr10(tools._strDaoxu(strTEI));

		strPTEI = strTPdata.Mid(4 , 4);
		strlistData[2] = tools._str16tostr10(tools._strDaoxu(strPTEI));

		strMAC = strTPdata.Mid(8 , 12);
		strlistData[0] = strMAC;//tools._strDaoxu(strMAC);

		strRole = strTPdata.Mid(20 , 2);//��ɫ��·�ɲ㼶  ��CKQ�ĳ���λ��·�ɲ㼶  ��ɫ ��λ��
		strRole.Format(_T("%d"),(_ttoi(strRole)+1)*2); 
		strlistData[3] = tools._str16tostr10(strRole);//

		strLayer = strTPdata.Mid(22 , 2);//��ɫ��·�ɲ㼶 ��CKQ�ĳ���λ��·�ɲ㼶  

		strLayer.Format(_T("%d"),_ttoi(strLayer)+1); 
        
		strlistData[4] = tools._str16tostr10(strLayer);//·�ɲ㼶

		strlistData[5] = "99";//m_tools._str16tostr10("11");


		if (strlistData[0].Mid(0,10) != "0102030405")//�жϱ��ַ
		{
			m_accessData.AddDataToTable(pMain->m_PeiZhi_db,_T("TPShow"),strlistName , strlistData ,6);
			//m_access.AddDataToTable(_T(".\\�����ļ�\\13762Data.accdb"),_T("TPShow"),strlistName , strlistData ,6);
		}
//--------------------------------------------------------------

		strTPdata = strTPdata.Mid(24);
	}

}
void CCKQViewUpdata::OnBnClickedBtnRefresh()
{
	CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CString strMessageAddress;
	pMain->m_bCommunictStop = false;
	if (pMain->m_bConnected == TRUE)
	{
		m_hThreadsend=CreateThread (NULL,0,ThreadSendRefresh,this,0,NULL);
		CloseHandle(m_hThreadsend);
	}
	else
	{
		AfxMessageBox(_T("��򿪴��ڣ�"));
	}

}



CString CCKQViewUpdata::strHEX(CString str,bool bDaoxu)
{
	INT8U * N_data;
	char d[5];
	CString strzong,strtwo;
	N_data=(INT8U*)str.GetBuffer(wcslen(str));
	for(int a=0;a<m_nDataLong;a++)
	{
		sprintf(d, "%X",N_data[a]);
		strtwo.Format(_T("%s"),d);
		if (wcslen(strtwo)==1)
		{
			strtwo = _T("0") + strtwo;
		}
		if (bDaoxu)
		{
			strzong=strtwo+strzong;
		} 
		else
		{
			strzong +=strtwo;
		}

	}
	return strzong;
}

CString CCKQViewUpdata::GetDuanAndLen(int nduan,int nlen)
{
	CString strData;
	CString str;
	CString str16duan,str16len;
	str.Format(_T("%d"),nduan);
	str16duan=m_tools._str10tostr16(str,4);
	str16duan=str16duan.Left(8).Right(2)+str16duan.Left(6).Right(2)+str16duan.Left(4).Right(2)+str16duan.Left(2);
	str.Format(_T("%d"),nlen);
	str16len=m_tools._str10tostr16(str,2);
	str16len=str16len.Left(4).Right(2)+str16len.Left(2);
	strData=str16duan+str16len;
	return strData;
}

void CCKQViewUpdata::SetUpdataListData()
{
	CMainFrame* pMain= (CMainFrame*)AfxGetApp()->GetMainWnd();
	int nHang= 0;
	CString strUpDataMessage;
	CString strFile;
	m_editFile.GetWindowText(strFile);
	m_listStrShengjiData.RemoveAll();
	char chBiaoshi[50];
	char chZhiling[50];
	CString strBiaoshi,strZhiling;
	POSITION pos=NULL;
	CString str;
	BYTE buf[2048];
	int tmp = 0, mod = 0;
	int iSectors = 0;
	int len =WideCharToMultiByte(CP_ACP,0,strFile,strFile.GetLength(),NULL,0,NULL,NULL);
	char * pFileName = new char[len + 1];
	WideCharToMultiByte(CP_ACP,0,strFile,strFile.GetLength(),pFileName,len,NULL,NULL);
	pFileName[len+1] ='\0';
	FILE * m_fp = NULL;
	m_fp = fopen(pFileName, "rb");
	fseek(m_fp,0,SEEK_END);
	long nLen = ftell(m_fp);
	CString strlong;
	strlong.Format(_T("%d"),nLen);
	strBiaoshi = _T("00");
	strZhiling = _T("00");
	int changdu=1024;
		m_nDataLong=changdu;
		if (nLen > 0)
		{
			tmp = nLen / changdu;
			mod = nLen % changdu;
			iSectors = (mod == 0)?tmp:(tmp + 1);
		}
		CString strZongduan;
		strZongduan.Format(_T("%d"),iSectors);

		m_nYU=_ttoi(strZongduan)%1024;
		m_nCHU=_ttoi(strZongduan)/1024;
		strZongduan=m_tools._str10tostr16(strZongduan,2);
		strZongduan=strZongduan.Left(4).Right(2)+strZongduan.Left(2);
		fseek(m_fp, 0, SEEK_SET);
		CString strDuanLen;
		int i=0;
		for (i=0; i < (iSectors-1); i++)
		{
			ZeroMemory(buf, changdu * sizeof(BYTE));
			strDuanLen=GetDuanAndLen(i,changdu);
			fread(buf,changdu,1,m_fp);
			if (strFile.Right(3)=="bin")
			{
				str = m_tools._buf16tostr16((INT8U*)buf,changdu,false,true);
			} 
			else
			{
				str=buf;
				str=strHEX(str,true);
			}
			pos=m_listStrShengjiData.InsertAfter(pos,_T("030000") + strZongduan + strDuanLen+str); 
		}
		if (mod!=0)
		{
			strDuanLen=GetDuanAndLen(i,mod);
			fread(buf,mod,1,m_fp);
			m_nDataLong=mod;
			if (strFile.Right(3)=="bin")
			{
				str = m_tools._buf16tostr16((INT8U*)buf,mod,false,true);
			} 
			else
			{
				str=buf;
				str=strHEX(str,true);
			}
			pos=m_listStrShengjiData.InsertAfter(pos,_T("030100")+strZongduan+strDuanLen+str);
		}

}

void CCKQViewUpdata::SetMsduUpdataListData(INT16U blksize,INT32U ftpID)
{
	CMainFrame* pMain= (CMainFrame*)AfxGetApp()->GetMainWnd();
	int nHang= 0;
	CString strUpDataMessage;
	CString strFile;
	m_editFile.GetWindowText(strFile);
	m_listStrShengjiData.RemoveAll();
	POSITION pos=NULL;
	CString str;
	BYTE buf[2048];
	INT16U tmp = 0, mod = 0;
	INT16U iSectors = 0;
	int len =WideCharToMultiByte(CP_ACP,0,strFile,strFile.GetLength(),NULL,0,NULL,NULL);
	char * pFileName = new char[len + 1];
	WideCharToMultiByte(CP_ACP,0,strFile,strFile.GetLength(),pFileName,len,NULL,NULL);
	pFileName[len+1] ='\0';
	FILE * m_fp = NULL;
	m_fp = fopen(pFileName, "rb");
	fseek(m_fp,0,SEEK_END);
	long nLen = ftell(m_fp);
	CString strlong;
	strlong.Format(_T("%d"),nLen);
	INT16U changdu=blksize;
	m_nDataLong=changdu;
	if (nLen > 0)
	{
		tmp = nLen / changdu;
		mod = nLen % changdu;
		iSectors = (mod == 0)?tmp:(tmp + 1);
	}
	CString strZongduan;
	strZongduan.Format(_T("%d"),iSectors);
	strZongduan=m_tools._str10tostr16(strZongduan,2);
	strZongduan=strZongduan.Left(4).Right(2)+strZongduan.Left(2);
	fseek(m_fp, 0, SEEK_SET);
	CString strDuanLen;
	INT32U i=0;
	for (i=0; i < tmp; i++)
	{
		ZeroMemory(buf, changdu * sizeof(BYTE));
		fread(buf,changdu,1,m_fp);
		//INT8U* databuf=(INT8U*)buf;
		//if (strFile.Right(3)=="bin")
		//{
		//	str = m_tools._buf16tostr16((INT8U*)buf,changdu,false,true);

		//} 
		//else
		//{
		//	str=buf;
		//	str=strHEX(str,true);
		//}
		sPLCPacket_App_Down_FTPTransfile Down_FTPTransfileCreatFrame;
		gMSDU2017.Fill_sPLCPacket_App_Down_FTPTransfile(Down_FTPTransfileCreatFrame,changdu,ftpID,i,(INT8U*)buf);
		gMSDU2017.Code_DownMsduFrame(Down_FTPTransfileCreatFrame);
		str = m_tools._buf16tostr16(Down_FTPTransfileCreatFrame.s_SendDataBuf,Down_FTPTransfileCreatFrame.s_SendDataLen,false,true);
		pos=m_listStrShengjiData.InsertAfter(pos,str); 
	}
	if (mod!=0)
	{
		fread(buf,mod,1,m_fp);
		m_nDataLong=mod;
		//if (strFile.Right(3)=="bin")
		//{
		//	str = m_tools._buf16tostr16((INT8U*)buf,mod,false,true);
		//} 
		//else
		//{
		//	str=buf;
		//	str=strHEX(str,true);
		//}
		sPLCPacket_App_Down_FTPTransfile Down_FTPTransfileCreatFrame;
		gMSDU2017.Fill_sPLCPacket_App_Down_FTPTransfile(Down_FTPTransfileCreatFrame,changdu,ftpID,i,(INT8U*)buf);
		gMSDU2017.Code_DownMsduFrame(Down_FTPTransfileCreatFrame);
		str = m_tools._buf16tostr16(Down_FTPTransfileCreatFrame.s_SendDataBuf,Down_FTPTransfileCreatFrame.s_SendDataLen,false,true);
		pos=m_listStrShengjiData.InsertAfter(pos,str);
	}
}

INT8U CCKQViewUpdata::zhengchangshengji(CString m_strLujing)//�γ�1024
{
	CString a;   
	INT8U ack;
	int DUAN_LEN=1024;
	CString xiazhuang=_T("00");
	sPartQGDW376_2CreatFrame sQGDW376_2HostFrame;
	sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
	CString strBiaoshi,strZhiling;
	CString str,str1,strZongduan,strDuanLen;
	CString str_banben,str_banben_qian;
	FILE* fp = NULL;
	POSITION pos=NULL;
	int tmp = 0, mod = 0;
	int iSectors = 0;
	int changdu=DUAN_LEN;//atoi(m_strFenduanlong);
	char chBiaoshi[50];
	char chZhiling[50];
	//plog.saveLog_strAll(TIME,"��ʼ��ȡ�汾��Ϣ",0);
	//ack =gSimJzq.HostSendRcv376_2NoBuf(AFN03,F1,sQGDW376_2HostFrame,DstDecodeDataFrame,1);
	//if(ack==DACK_SUCESS)
	//{
	//	if(DstDecodeDataFrame.s_RcvDataLen==9)
	//	{
	//		//if (DstDecodeDataFrame.s_RcvDataBuf[7]==buf_banben[0]&&DstDecodeDataFrame.s_RcvDataBuf[8]==buf_banben[1])
	//		//{
	//		INT16U cnt= Buf2ToHex16(&DstDecodeDataFrame.s_RcvDataBuf[7]);
	//		str_banben_qian.Format("%u", cnt);
	//		plog.saveLog_strAll(TIME,"��ǰ�汾�ţ�"+str_banben_qian,0);
	//		//}
	//	}
	//	else
	//	{
	//		ack = DACK_FAILURE;
	//	}
	//}
	//a = m_strLujing.Right(8);
	//str_banben=a.Left(4);
	////UINT8 buf_banben[2];
	////UINT16 len_banben;
	////m_tool._str16tobuf16(str_banben ,buf_banben, len_banben);
	////str.Format("%d",str_banben);
	//int mm;
	//sscanf(str_banben,"%d",&mm); 
	//str.Format("%d",mm);
	//plog.saveLog_strAll(TIME,"�����ļ��汾��Ϊ��"+str,0);
	
	//m_strLujing=".\\Զ������\\CCO�����ļ�\\123.bin";
	BYTE buf[4096];
	m_listStrShengjiData.RemoveAll();
	int len =WideCharToMultiByte(CP_ACP,0,m_strLujing,m_strLujing.GetLength(),NULL,0,NULL,NULL);
	char * pFileName = new char[len + 1];
	WideCharToMultiByte(CP_ACP,0,m_strLujing,m_strLujing.GetLength(),pFileName,len,NULL,NULL);
	pFileName[len+1] ='\0';
	fp = fopen(pFileName, "rb");
	fseek(fp,0,SEEK_END);
	//plog.saveLog_str(DATA_FILE,TIME,m_strLujing,0);
	//FILE* fp = NULL;
	//fp = fopen(m_strLujing, "rb");
	//BYTE buf[2048];
	//fseek(fp,100L,0);��fpָ���ƶ������ļ���ͷ100�ֽڴ���
    //fseek(fp,100L,1);��fpָ���ƶ������ļ���ǰλ��100�ֽڴ���
	//fseek(fp,100L,2);//��fpָ���˻ص����ļ���β100�ֽڴ���
	//fread(buf,2,3,fp);//ÿ�ζ�һ����Ԫ  ��Ԫ����changdu
	//str = m_tool._buf16tostr16((INT8U*)buf,changdu,false,0);
	//INT16U cnt= Buf2ToHex16(&DstDecodeDataFrame.s_RcvDataBuf[0]);
	//str.Format("������%u", cnt);
	//plog.saveLog_strAll(TIME,"������ɹ����ڵ���Ϊ"+str,0);
	long nLen;
	nLen = ftell(fp);
	strBiaoshi="03";
	strZhiling.Format(_T("%s"),chZhiling);
	//strNumb.Format(_T("%d") , n + 1);
	strZhiling=_T("00");
	m_nDataLong=changdu;
	if (nLen > 0)
	{
		tmp = nLen / changdu;
		mod = nLen % changdu;
		iSectors = (mod == 0)?tmp:(tmp + 1);
	}
	strZongduan.Format(_T("%d"),iSectors);
	strZongduan=m_tools._str10tostr16(strZongduan,2);
	strZongduan=strZongduan.Left(4).Right(2)+strZongduan.Left(2);
	fseek(fp, 0, SEEK_SET);
	int i,j;
	for (i=0; i < (iSectors-1); i++)
	{
		ZeroMemory(buf, changdu * sizeof(BYTE));
		strDuanLen=GetDuanAndLen(i,changdu);
		fread(buf,changdu,1,fp);//ÿ�ζ�һ����Ԫ  ��Ԫ����changdu
		if (m_strLujing.Right(3)==_T("bin"))
		{
			str = m_tools._buf16tostr16((INT8U*)buf,changdu,false,0);
		} 
		else
		{
			str=buf;
			str=strHEX(str,0);
		}
		if (xiazhuang==_T("00"))
		{
			pos=m_listStrShengjiData.InsertAfter(pos,_T("0000")+strZhiling+_T("0000000000000000"));
			xiazhuang=_T("03");
		}
		pos=m_listStrShengjiData.InsertAfter(pos,strBiaoshi+_T("00")+strZhiling+strZongduan+strDuanLen+str); 
		//AfxMessageBox(strBiaoshi+"00"+strZhiling+strZongduan+strDuanLen+str);
	}
	if (mod!=0)
	{
		ZeroMemory(buf, changdu * sizeof(BYTE));
		strDuanLen=GetDuanAndLen(i,mod);
		fread(buf,mod,1,fp);
		m_nDataLong=mod;
		if (m_strLujing.Right(3)=="bin")
		{
			str = m_tools._buf16tostr16((INT8U*)buf,mod,false,0);
		} 
		else
		{
			str=buf;
			str=strHEX(str,0);
		}
		pos=m_listStrShengjiData.InsertAfter(pos,strBiaoshi+"01"+strZhiling+strZongduan+strDuanLen+str);
		//AfxMessageBox(strBiaoshi+"00"+strZhiling+strZongduan+strDuanLen+str);
	}
	i=1;
	j=0;
	for(pos = m_listStrShengjiData.GetHeadPosition(); pos != NULL;)
	{
		CString strShuxingBiaoshiLen;
		strShuxingBiaoshiLen=(CString)m_listStrShengjiData.GetNext(pos);
		//m_tools._str16tobuf16(strShuxingBiaoshiLen, Sendbufdata , Sendbuflen);
		//m_tool._str16tobuf16(m_listStrShengjiData.GetNext(pos),buf,a);
		INT16U a;
		m_tools._str16tobuf16(strShuxingBiaoshiLen,buf,a);
		//memcpy(buf,str,m_listStrShengjiData.GetNext(pos).GetLength());
		ack =gSimJzq.HostSendRcv376_2Buf(0x15,F1,buf,a,sQGDW376_2HostFrame,DstDecodeDataFrame,1);
		if (DstDecodeDataFrame.s_head.s_AFN==0x00&&DstDecodeDataFrame.s_head.s_FN==F1)
		{
		}
		else if (ack==DACK_SUCESS)
		{
			str.Format(_T("%d"),i);
			str1.Format(_T("%d"),iSectors);
			if (DstDecodeDataFrame.s_RcvDataBuf[3]==0xff)
			{
				//plog.saveLog_str(DATA_FILE,TIME,"����FF�ļ�����ʧ�ܣ��ڶ��η���",0);
				ack =gSimJzq.HostSendRcv376_2Buf(0x15,F1,buf,a,sQGDW376_2HostFrame,DstDecodeDataFrame,1);
				if (ack==DACK_SUCESS)
				{
					str.Format(_T("%d"),i);
					str1.Format(_T("%d"),iSectors);
					if (DstDecodeDataFrame.s_RcvDataBuf[3]==0xff)
					{
						//plog.saveLog_str(DATA_FILE,TIME,"����FF�ļ�����ʧ�ܣ�����ԭ��",0);
						ack =gSimJzq.HostSendRcv376_2Buf(0x15,F1,buf,a,sQGDW376_2HostFrame,DstDecodeDataFrame,1);
						if (ack==DACK_SUCESS)
						{
							str.Format(_T("%d"),i);
							str1.Format(_T("%d"),iSectors);
							if (DstDecodeDataFrame.s_RcvDataBuf[3]==0xff)
							{
								//plog.saveLog_str(DATA_FILE,TIME,"����FF�ļ�����ʧ�ܣ�����ԭ��",0);
								ack = DACK_FAILURE;
								return ack;
							}
						}
					}
				}
			}
			//plog.saveLog_str(DATA_FILE,TIME,"��"+str+"�������ɹ����ܶ�����"+str1,0);
			i++;
		}
		else
		{
			str.Format(_T("%d"),i);
			j++;
			//plog.saveLog_str(DATA_FILE,TIME,"��"+str+"������ʧ�ܣ��ڶ��η��� ",0);
			ack =gSimJzq.HostSendRcv376_2Buf(0x15,F1,buf,a,sQGDW376_2HostFrame,DstDecodeDataFrame,1);
			if (ack==DACK_SUCESS)
			{
				str.Format(_T("%d"),i);
				str1.Format(_T("%d"),iSectors);
				//plog.saveLog_str(DATA_FILE,TIME,"��"+str+"�������ɹ����ܶ�����"+str1,0);
				i++;
			}
			else
			{
				str.Format(_T("%d"),i);
				j++;
				//plog.saveLog_str(DATA_FILE,TIME,"��"+str+"������ʧ�ܣ������η��� ",0);
				ack =gSimJzq.HostSendRcv376_2Buf(0x15,F1,buf,a,sQGDW376_2HostFrame,DstDecodeDataFrame,1);
				if (ack==DACK_SUCESS)
				{
					str.Format(_T("%d"),i);
					str1.Format(_T("%d"),iSectors);
					//plog.saveLog_str(DATA_FILE,TIME,"��"+str+"�������ɹ����ܶ�����"+str1,0);
					i++;
				}
				else
				{
					str.Format(_T("%d"),i);
					j++;
					//plog.saveLog_str(DATA_FILE,TIME,"��"+str+"������ʧ�ܣ�ֹͣ���Լ��ԭ�� ",0);
					ack = DACK_FAILURE;
					return ack;
				}

			}

		}
	}
	//plog.saveLog_str(DATA_FILE,TIME,"�����ļ��������",0);
	return ack;
}//��������

DWORD WINAPI ThreadSendbufUpData (PVOID pParam)
{
	//AfxMessageBox(_T("����"));
	CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CCKQViewUpdata * pView = (CCKQViewUpdata *)pParam;
	sPartQGDW376_2CreatFrame ptSendQGDW376_2;
	sPartQGDW376_2DeCodeFrame ptRecvQGDWF0376_2;
	sPartQGDW376_2DeCodeFrame ptRecvQGDW376_2;

	sPartCKQ2017CreatFrame ptSendCKQ2017;
	sPartCKQ2017DeCodeFrame ptDeCodeCKQ2017;

	CString NodeMAC,NodeTEI,NodeTYPE;
	INT8U Sendbufdata[2000] ,AddrBuf[6],TEIBuf[2];
	INT16U Sendbuflen = 0,temp16 = 0,teilen;
	INT8U ack = -1;
	if(pView->m_upType.GetCurSel()==0)
	{

		if(pView->m_radioUpType.GetCheck()){//ȫ������

		}
		else{//��������

			NodeMAC=pView->m_listData.GetItemText(pView->m_listData.GetSelectionMark(),1);
			NodeTEI=pView->m_listData.GetItemText(pView->m_listData.GetSelectionMark(),2);
			NodeTYPE=pView->m_listData.GetItemText(pView->m_listData.GetSelectionMark(),3);
			if(NodeMAC==""||NodeTEI==""){
				AfxMessageBox(_T("δѡ�нڵ�"));
				return 0;
			}
			pView->m_tools._str16tobuf16(NodeMAC , AddrBuf , temp16 , true);//С��ģʽ
			pView->m_tools._str16tobuf16(NodeTEI , TEIBuf , teilen , true);
			//pView->SetUpdataListData();//����MSDU֡��  �����ļ���֡
//-----------------------���Գ���-------------------------------------
		INT8U tmpbuf[1000];
		INT16U len16=0;
		INT8U amtbuf[6];
		INT8U amtbuf2[6]={0xaa,0xaa,0xaa,0xaa,0xaa,0xaa};
		INT8U ack;
		INT8U vSrc645Cnt=1;//��645�ĸ���
		sBinFa376_2_HostMsg  BinDownmsg;
		pView->m_tools._str16tobuf16(NodeMAC , amtbuf , temp16 , true);
		//INT8U amtbuf[6]={0x01,0x00,0x00,0x00,0x00,0x00};	//���ַ(��Ҫ���)
		gSimJzq.QueMore645Fame(DPCT_2007FG,1000,amtbuf2,vSrc645Cnt,tmpbuf,len16,BinDownmsg);//��ȡ��ʶ��645֡�������и�di������ȣ�

		
		////��MSDU����֡
		sPLCPacket_App_Down_TranData Down_TranDataCreatFrame;
		pView->gMSDU2017.Fill_Down_TranDataFrame(Down_TranDataCreatFrame,tmpbuf,len16,DPCT_2007FG);//���ṹ
		pView->gMSDU2017.Code_DownMsduFrame(Down_TranDataCreatFrame);//��MSDU����֡
				
		// �ȼӼ�������У��
		//pView->gMSDU2017.Add4BataIntegrityCheck(Down_TranDataCreatFrame);//�����ֽ�������У��

		////��mac֡ͷ
		INT8U MAC_y_buf[6]={0x01,0x02,0x03,0x04,0x05,0x00};
		INT8U MAC_sta_buf[6];//={0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};//�㲥ʱ�� ����Ҫ��
		pView->m_tools._str16tobuf16(NodeMAC , MAC_sta_buf , temp16 , false);//���ģʽ
		MacHead Down_MacHeadForMsdu;
		INT8U sendtype=_ttoi(NodeTYPE);
		INT16U mac_to_tei=_ttoi(NodeTEI);//Ŀ��tei  Ҫ��  �㲥ʱ��4095
		pView->gMSDU2017.Fill_MacHeadStuct(Down_MacHeadForMsdu,Down_TranDataCreatFrame.s_SendDataLen,0x30,Down_TranDataCreatFrame.s_seq,MAC_y_buf,MAC_sta_buf,1016,mac_to_tei,sendtype,1);
		pView->gMSDU2017.Code_MacHeadForMsdu(Down_MacHeadForMsdu);

		//���������У��
		//pView->gMSDU2017.Add4BataIntegrityCheck(Down_TranDataCreatFrame);//�����ֽ�������У��

		//��CKQ֡��������������������
		ptSendCKQ2017.TYPE=0x16;//���趨���ת��MSDUΪ0X16(��Ҫ���)
		INT8U buf[1000];
		INT8U i = 0;
		INT16U TEI_16=_ttoi(NodeTEI);
		buf[i++]=TEI_16>>8;//0x0f;//TEI_16>>8;//��TEI�����ֽ�(��Ҫ���)
		buf[i++]=(INT8U)TEI_16;//0xff;//(INT8U)TEI_16;//��TEI(��Ҫ���)
		buf[i++]=0x01;//��MAC
		buf[i++]=0xFF;//ҵ��LIDs��ʲô
		buf[i++]=(Down_MacHeadForMsdu.s_MacHeadDataLen+Down_TranDataCreatFrame.s_SendDataLen)>>8;
		buf[i++]=(INT8U)(Down_MacHeadForMsdu.s_MacHeadDataLen+Down_TranDataCreatFrame.s_SendDataLen);
		for(INT8U m=0; m<Down_MacHeadForMsdu.s_MacHeadDataLen; m++)//����MSDU֡MACͷ��������֡��
		{
			buf[i++] = Down_MacHeadForMsdu.s_MacHeadDataBuf[m];
		}
		for(INT8U m=0; m<Down_TranDataCreatFrame.s_SendDataLen; m++)//����MSDU֡������������У����ĸ��ֽڵ�������֡��
		{
			buf[i++] = Down_TranDataCreatFrame.s_SendDataBuf[m];
		}
		ptSendCKQ2017.s_SendDataBuf=buf;//���������MSDU֡�ĳ�����������
		ptSendCKQ2017.s_SendDataLen=Down_MacHeadForMsdu.s_MacHeadDataLen+Down_TranDataCreatFrame.s_SendDataLen+6;//



		//ptSendCKQ2017.TYPE=0x12;//���趨���ת��MSDUΪ0X11(��Ҫ���)
		//INT8U buf[1000];
		//INT8U i = 0;
		//INT16U TEI_16=_ttoi(NodeTEI);
		//buf[i++]=TEI_16>>8;//0x0f;//TEI_16>>8;//��TEI�����ֽ�(��Ҫ���)
		//buf[i++]=(INT8U)TEI_16;//0xff;//(INT8U)TEI_16;//��TEI(��Ҫ���)
		//buf[i++]=0x00;
		//buf[i++]=0x00;
		//buf[i++]=0x00;
		////buf[i++]=Down_TranDataCreatFrame.s_SendDataLen>>8;
		//buf[i++]=(INT8U)(Down_TranDataCreatFrame.s_SendDataLen);
		//for(INT8U m=0; m<Down_TranDataCreatFrame.s_SendDataLen; m++)//����MSDU֡��������֡��
		//{
		//	buf[i++] = Down_TranDataCreatFrame.s_SendDataBuf[m];
		//}
		//ptSendCKQ2017.s_SendDataBuf=buf;//���������MSDU֡�ĳ�����������
		//ptSendCKQ2017.s_SendDataLen=Down_TranDataCreatFrame.s_SendDataLen+6;//




		ack=pView->gCKQ2017.SendRcvCKQ2017Frame(ptSendCKQ2017,ptDeCodeCKQ2017);//���ͽ��ճ�����֡

		ack = pView->gCKQ2017.WaitCKQ2017Ack(5000,10,ptDeCodeCKQ2017);
		if(ack == DACK_SUCESS)
		{
		}


			//��ʼ����֡

			//ֹͣ����֡

			//��ʼ����֡

			//�����ļ��������в�ѯվ������״̬����Ӧ����ȷʵ�Ƿ���в������ͣ�

			//��ѯվ������״̬(����ǽ������̬,��CRCȷ���Ƿ�����ȷ)

			//ִ������֡���������ɣ�

			//AfxMessageBox(_T("MAC:")+NodeMAC+_T(" TEI:")+NodeTEI);
		}
	}
	else if(pView->m_upType.GetCurSel()==1){
	}
	//pView->SetUpdataListData();
	//pView->m_tools._str16tobuf16( pMain->m_strMAddress , AddrBuf , temp16 , true);
	//CString strDatalen = _T("") , str = _T("");


	//pView->m_tools._str16tobuf16(_T("0000000000000000000000")  , Sendbufdata , Sendbuflen);
	//ack = gSimJzq.HostSendRcv376_2F0F8(AddrBuf , 0x15 , F1 , Sendbufdata , Sendbuflen , ptSendQGDW376_2 ,ptRecvQGDWF0376_2 , ptRecvQGDW376_2);
	//if (ack == 0 && ptRecvQGDW376_2.s_head.s_AFN == 0x15)
	//{
	//	for(POSITION pos = pView->m_listStrShengjiData.GetHeadPosition(); pos != NULL;)
	//	{
	//		if (pMain->m_bCommunictStop)
	//		{
	//			return false;
	//		}
	//		strShuxingBiaoshiLen=(CString)pView->m_listStrShengjiData.GetNext(pos);
	//		pView->m_tools._str16tobuf16(strShuxingBiaoshiLen  , Sendbufdata , Sendbuflen);
	//		ack = gSimJzq.HostSendRcv376_2F0F8(AddrBuf , 0x15 , F1 , Sendbufdata , Sendbuflen , ptSendQGDW376_2 ,ptRecvQGDWF0376_2 , ptRecvQGDW376_2);
	//		switch(ack)
	//		{
	//		case 0:
	//			if (ptRecvQGDW376_2.s_head.s_AFN == 0x00 && ptRecvQGDW376_2.s_head.s_FN == F2)
	//			{
	//				switch(ptRecvQGDW376_2.s_RcvDataBuf[0])
	//				{
	//				case 0:
	//					str = _T(">>>>ʧ��:ͨ�ų�ʱ");
	//					break;
	//				case 1:
	//					str = _T(">>>>ʧ��:��Ч���ݵ�Ԫ");
	//					break;
	//				case 2:
	//					str = _T(">>>>ʧ��:���ȴ�");
	//					break;
	//				case 3:
	//					str = _T(">>>>ʧ��:У�����");
	//					break;
	//				case 4:
	//					str = _T(">>>>ʧ��:��Ϣ�಻����");
	//					break;
	//				case 5:
	//					str = _T(">>>>ʧ��:��ʽ����");
	//					break;
	//				case 6:
	//					str = _T(">>>>ʧ��:����ظ�");
	//					break;
	//				case 7:
	//					str = _T(">>>>ʧ��:��Ų�����");
	//					break;
	//				case 8:
	//					str = _T(">>>>ʧ��:���Ӧ�ò���Ӧ��");
	//					break;
	//				case 9:
	//					str = _T(">>>>ʧ��:���ڵ�æ");
	//					break;
	//				case 10:
	//					str = _T(">>>>ʧ��:���ڵ㲻֧�ִ�����");
	//					break;
	//				case 11:
	//					str = _T(">>>>ʧ��:�ӽڵ㲻Ӧ��");
	//					break;
	//				case 12:
	//					str = _T(">>>>ʧ��:�ӽڵ㲻������");
	//					break;
	//				}
	//				str += _T("\r\n");
	//			}
	//			else
	//			{

	//			}
	//			break;
	//		case 0x13://ʧ��
	//			break;
	//		case 0x30://SEQ��һ��
	//			break;
	//		case 0x0A://���ڵ㲻֧�ִ�����
	//			break;
	//		default:
	//			break;
	//		}
	//	}
	//}
	//
	return 0;
}
void CCKQViewUpdata::OnBnClickedBtnBeginupdata()
{
	CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CString strMessageAddress;
	pMain->m_bCommunictStop = false;
	if (pMain->m_bConnected == TRUE)
	{
		m_hThreadsend=CreateThread (NULL,0,ThreadSendbufUpData,this,0,NULL);
		CloseHandle(m_hThreadsend);
	}
	else
	{
		AfxMessageBox(_T("��򿪴��ڣ�"));
	}
}


void CCKQViewUpdata::OnBtnBeginupdata2()
{
	CString strCopy = m_listData.GetItemText (m_listData.m_itemYes , 0);
	AfxMessageBox(_T("1"));
}


void CCKQViewUpdata::OnModerrUpdata1()
{
	//CString strCopy = m_listData.GetItemText (m_listData.m_itemYes , 0);
	CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CString strMessageAddress;
	pMain->m_bCommunictStop = false;
	if (pMain->m_bConnected == TRUE)
	{
		m_hThreadsend=CreateThread (NULL,0,ThreadSendbufUpData,this,0,NULL);
		CloseHandle(m_hThreadsend);
	}
	else
	{
		AfxMessageBox(_T("��򿪴��ڣ�"));
	}
}


void CCKQViewUpdata::Onshuaxinlb()
{

		CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CString strMessageAddress;
	pMain->m_bCommunictStop = false;
	if (pMain->m_bConnected == TRUE)
	{
		m_hThreadsend=CreateThread (NULL,0,ThreadSendRefresh,this,0,NULL);
		CloseHandle(m_hThreadsend);
	}
	else
	{
		AfxMessageBox(_T("��򿪴��ڣ�"));
	}
	// TODO: �ڴ���������������
	//CMainFrame* pMain= (CMainFrame*)AfxGetApp()->GetMainWnd();
	//CAccessData access;
	//CString strAllDatalist[6];
	//CString strlist[1000];
	//CString str;
	//int nNumb = 0 , nAlldataNumb , nCount;
	//m_listData.DeleteAllItems();
	//access.SelectDataFromTable(pMain->m_PeiZhi_db, _T("TPShow") , _T("TP_MAC,TP_TEI") ,_T("") ,strlist ,nAlldataNumb);
	////access.SelectDataFromTable(_T(".\\�����ļ�\\13762Data.accdb") , _T("TPShow") , _T("TP_MAC,TP_ROLE") ,_T("") ,strlist ,nAlldataNumb);
	////m_listData.InsertItem(nAlldataNumb, _T(""));
	//for (int n = 0 ; n < nAlldataNumb ; n++)
	//{
	//	str.Format(_T("%d") , n + 1);
	//	m_tools.Split(strlist[n] , _T("$") ,strAllDatalist , nNumb);
	//	if (strAllDatalist[0].Mid(0 , 10) != "0102030405")
	//	{
	//		//nCount = m_listData.GetItemCount();
	//		m_listData.InsertItem(n, _T(""));
	//		m_listData.SetItemText(n , 0 ,str);
	//		m_listData.SetItemText(n ,1,strAllDatalist[0]);
	//		m_listData.SetItemText(n ,2,strAllDatalist[1]);
	//		m_listData.SetItemText(n ,3,_T("0"));
	//	}
	//}
}


void CCKQViewUpdata::OnAddNode()
{
	// TODO: �ڴ���������������
	INT_PTR nRes;             // ���ڱ���DoModal�����ķ���ֵ   
    CString str;
    AddMacTest tipDlg;           // ����Ի�����CTipDlg��ʵ��   
    nRes = tipDlg.DoModal();  // �����Ի���   
    if (IDCANCEL == nRes)     // �ж϶Ի����˳��󷵻�ֵ�Ƿ�ΪIDCANCEL���������return�������������ִ��   
        return;   
  
    // �����ؼ��е����ݱ��浽��Ӧ�ı���   
    UpdateData(TRUE);   
  
    // ���������ͼ����ļӺ͸�ֵ��m_editSum   
	int m=m_listData.GetItemCount();
    m_listData.InsertItem(m, _T(""));
	str.Format(_T("%d") , m + 1);
	m_listData.SetItemText(m , 0 ,str);
	m_listData.SetItemText(m ,1,tipDlg.m_MAC);
	m_listData.SetItemText(m ,2,tipDlg.m_TEI);  
	m_listData.SetItemText(m ,3,tipDlg.m_TYPE); 
  
    // ���ݸ�������ֵ������Ӧ�Ŀؼ����͵ı༭�����ʾm_editSum��ֵ   
    UpdateData(FALSE);  
}



//INT8U CCKQViewUpdata::SendRec_MAC_13762_toCCO(sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame,sPartQGDW376_2DeCodeFrame &sRecv376_2HostFrame)//���ͽ���CKQ��֡��MAC֡��376.2  ����ȡ376.2����
//{
//	INT16U temp16 = 0;
//	INT8U ack = -1;
//	CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
//	sPartCKQ2017CreatFrame ptSendCKQ2017;
//	sPartCKQ2017DeCodeFrame ptDeCodeCKQ2017,ptDeCodeCKQ2017_2;
//
//	//��MSDU��376.2֡
//	sPLCPacket_App_Down_13762 Down_Msdu13762DataCreatFrame;
//	gMSDU2017.Fill_DownMSDU_13762Frame(Down_Msdu13762DataCreatFrame,sQGDW376_2HostFrame.s_SendDataBuf,sQGDW376_2HostFrame.s_SendDataLen);//���ṹ
//	gMSDU2017.Code_DownMSDU_13762Frame(Down_Msdu13762DataCreatFrame);//��MSDU��376.2��֡
//
//	//��mac֡ͷ
//	MacHead Down_MacHeadForMsdu;
//	INT8U MAC_y_buf[6]={0x01,0x02,0x03,0x04,0x05,0x00};//������MAC ***********************Ҫ��
//	//INT8U MAC_y_buf[6];
//	//m_tools._str16tobuf16(pMain->m_strMAddress , MAC_y_buf , temp16 , false);
//	INT8U MAC_sta_buf[6];//�㲥ʱ�� ����Ҫ�� ***  ���
//	m_tools._str16tobuf16( pMain->m_strMAddress , MAC_sta_buf , temp16 , false);//��ˡ���CCO�ĵ�ַ
//	INT8U sendtype=0;//2;����0�����ع㲥2 *** ������CCO
//	INT16U mac_to_tei=1;//_ttoi(NodeTEI);//Ŀ��tei  Ҫ��  �㲥ʱ��0xfff ***CCO ��1
//	gMSDU2017.Fill_MacHeadStuct(Down_MacHeadForMsdu,Down_Msdu13762DataCreatFrame.s_SendDataLen,0x30,Down_Msdu13762DataCreatFrame.s_seq,MAC_y_buf,MAC_sta_buf,1016,mac_to_tei,sendtype,1);//������TEI 1016
//	gMSDU2017.Code_MacHeadForMsdu(Down_MacHeadForMsdu);
//
//		//��������У��
//	gMSDU2017.Add4BataIntegrityCheck(Down_Msdu13762DataCreatFrame);//�����ֽ�������У��
//
//
//	ptSendCKQ2017.TYPE=0x16;//��������TYPE(��Ҫ���)
//	INT8U buf[1000];
//	INT8U i = 0;
//	INT16U TEI_16=1;//0xfff;//ȫ�ֻ򵥵�TEI  ***CCO ��tei Ϊ1
//	buf[i++]=TEI_16>>8;//0x0f;//TEI_16>>8;//��TEI�����ֽ�(��Ҫ���)
//	buf[i++]=(INT8U)TEI_16;//0xff;//(INT8U)TEI_16;//��TEI(��Ҫ���)
//	buf[i++]=0x01;  
//	buf[i++]=0xFF;//ҵ��LIDs��ʲô
//	buf[i++]=(Down_MacHeadForMsdu.s_MacHeadDataLen+Down_Msdu13762DataCreatFrame.s_SendDataLen)>>8;
//	buf[i++]=(INT8U)(Down_MacHeadForMsdu.s_MacHeadDataLen+Down_Msdu13762DataCreatFrame.s_SendDataLen);
//	for(INT8U m=0; m<Down_MacHeadForMsdu.s_MacHeadDataLen; m++)//����MSDU֡MACͷ��������֡��
//	{
//		buf[i++] = Down_MacHeadForMsdu.s_MacHeadDataBuf[m];
//	}
//	for(INT8U m=0; m<Down_Msdu13762DataCreatFrame.s_SendDataLen; m++)//����MSDU֡��������֡��
//	{
//		buf[i++] = Down_Msdu13762DataCreatFrame.s_SendDataBuf[m];
//	}
//	ptSendCKQ2017.s_SendDataBuf=buf;//���������MSDU֡�ĳ�����������
//	ptSendCKQ2017.s_SendDataLen=Down_MacHeadForMsdu.s_MacHeadDataLen+Down_Msdu13762DataCreatFrame.s_SendDataLen+6;//
//	ack=gCKQ2017.SendRcvCKQ2017Frame(ptSendCKQ2017,ptDeCodeCKQ2017);//���ͽ��ճ�����֡
//	if(ack==DACK_SUCESS){
//		if(ptDeCodeCKQ2017.TYPE==0x96){
//			if(ptDeCodeCKQ2017.s_RcvDataBuf[0]=0x00){
//				ack = gCKQ2017.WaitCKQ2017Ack(5000,10,ptDeCodeCKQ2017_2);
//				if(ack==DACK_SUCESS){
//					if(ptDeCodeCKQ2017_2.TYPE==0x97){
//
//						//ptDeCodeCKQ2017.s_RcvDataBuf[17];//����2�ֽ�
//						//ptDeCodeCKQ2017.s_RcvDataBuf[18];
//						if(ptDeCodeCKQ2017.s_RcvDataLen>22){
//							INT16U len=ptDeCodeCKQ2017.s_RcvDataBuf[17]*16+ptDeCodeCKQ2017.s_RcvDataBuf[18];//MSDU����
//							//ptDeCodeCKQ2017.s_RcvDataBuf[19]->ptDeCodeCKQ2017.s_RcvDataBuf[18+len]//MADU����
//							sRecv376_2HostFrame.s_RcvDataLen=ptDeCodeCKQ2017.s_RcvDataBuf[21]*16+ptDeCodeCKQ2017.s_RcvDataBuf[22];
//							if(ptDeCodeCKQ2017.s_RcvDataLen>23+sRecv376_2HostFrame.s_RcvDataLen){
//								for(int m=0;m<sRecv376_2HostFrame.s_RcvDataLen;m++)
//								{
//									sRecv376_2HostFrame.s_RcvDataBuf[m]=ptDeCodeCKQ2017.s_RcvDataBuf[25+m];
//								}
//							}
//						}
//					}
//				}
//			}
//			else{
//				//1-���ĳ��ȴ���
//				//2-�������������
//				//3-Ŀ��TEI����
//				//4-MAC�����ֶδ���
//				//5-������Ӳ������
//				ack=ptDeCodeCKQ2017.s_RcvDataBuf[0];
//			}
//		}
//		else{
//		    ack=-1;
//		}
//	}
//	return ack;
//	
//}
