// CmdEdit.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "KD_Project.h"
#include "CmdEdit.h"


// CmdEdit

IMPLEMENT_DYNAMIC(CmdEdit, CEdit)

CmdEdit::CmdEdit()
{

	EnableAutomation();
}

CmdEdit::~CmdEdit()
{
}

void CmdEdit::OnFinalRelease()
{
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease�����ཫ�Զ�
	// ɾ���ö����ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

	CEdit::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CmdEdit, CEdit)
END_MESSAGE_MAP()


BEGIN_DISPATCH_MAP(CmdEdit, CEdit)
END_DISPATCH_MAP()

// ע��: ������� IID_ImdEdit ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡��� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {C5AC946D-DCC7-4BA7-A06B-6E8DAE19FBCE}
static const IID IID_ImdEdit =
{ 0xC5AC946D, 0xDCC7, 0x4BA7, { 0xA0, 0x6B, 0x6E, 0x8D, 0xAE, 0x19, 0xFB, 0xCE } };

BEGIN_INTERFACE_MAP(CmdEdit, CEdit)
	INTERFACE_PART(CmdEdit, IID_ImdEdit, Dispatch)
END_INTERFACE_MAP()


// CmdEdit ��Ϣ�������

//HBRUSH CmdEdit::CtlColor(CDC* pDC, UINT nCtlColor)
//{
// COLORREF clr = RGB(255,0,0);
// pDC->SetTextColor(clr);   //���ú�ɫ���ı�
// clr = RGB(255,0,0);
// pDC->SetBkColor(clr);     //���ú�ɫ�ı���
// HBRUSH m_bkBrush = ::CreateSolidBrush(clr);
// return m_bkBrush;  //��ΪԼ�������ر���ɫ��Ӧ��ˢ�Ӿ��
//}
//HBRUSH CmdEdit::CtlColor(CDC* pDC, UINT nCtlColor)  
//{     
//    pDC->SetBkMode(TRANSPARENT);                 // ͸��     
//    pDC->SetTextColor(RGB(23, 236, 26));           // ����ɫ��   
//    return (HBRUSH)GetStockObject(DKGRAY_BRUSH);    // ���屳��(OnEraseBkgndֻ�Ǳ�����˸)  
//}  

//void CmdEdit::OnNcpaint()  
//{  
//    CRect rect, rc;  
//    CDC* pDC;  
//    int  nSaveDC;  
//  
//  
//    pDC = GetWindowDC();  
//    GetWindowRect(&rect);  
//    rect -= rect.TopLeft();  
//  
//  
//    rc = rect;  
//    rc.InflateRect(-GetSystemMetrics(SM_CXEDGE), -GetSystemMetrics(SM_CYEDGE));  
//  
//  
//    nSaveDC = pDC->SaveDC();  
//    pDC->ExcludeClipRect(&rc);  
//    pDC->FillSolidRect(&rect, RGB(24,24,255));  
//    pDC->RestoreDC(nSaveDC);  
//  
//  
//    pDC->FrameRect(&rect, &CBrush(RGB(24,254,35)));  
//    ReleaseDC(pDC);  
//}  


void CmdEdit::OnNcPaint()
{
	CRect rc;
	GetWindowRect(&rc);
	CRect rcWindow(0,0,rc.Width(),rc.Height());

	CBrush brushFrame;
	brushFrame.CreateSolidBrush(RGB(255,24,11));

	CWindowDC dc(this);
	dc.FrameRect(&rcWindow,&brushFrame);
}
BOOL CmdEdit::OnEraseBkgnd(CDC* pDC)
{
     //TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
    CDC memDC;
    memDC.CreateCompatibleDC(pDC);
    memDC.SelectObject(&m_Bitmap);
    BITMAP m_Bmp;
    m_Bitmap.GetBitmap(&m_Bmp);
    CRect rect;
    GetClientRect(&rect);
//������ͼ
    pDC->StretchBlt(0,0,rect.Width() ,rect.Height(),&memDC,0,0,m_Bmp.bmWidth,m_Bmp.bmHeight,SRCCOPY);
    memDC.DeleteDC();
    return TRUE;
    //return CEdit::OnEraseBkgnd(pDC);
}
HBRUSH CmdEdit::CtlColor(CDC* pDC,  UINT nCtlColor)
{
    // TODO:  �ڴ˸��� DC ���κ�����
//͸��
    pDC->SetBkMode(TRANSPARENT);
	//pDC->SetTextColor
//����ɫ��
    pDC->SetTextColor(RGB(0,255,0));
//�յĻ���
        return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
    // TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
}
void CmdEdit::OnEnChange()
{
//ʹ��Ч
    Invalidate();
}