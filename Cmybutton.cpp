// Cmybutton.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "KD_Project.h"
#include "Cmybutton.h"


// Cmybutton

IMPLEMENT_DYNAMIC(Cmybutton, CButton)

Cmybutton::Cmybutton()
{

	EnableAutomation();
}

Cmybutton::~Cmybutton()
{
}

void Cmybutton::OnFinalRelease()
{
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease�����ཫ�Զ�
	// ɾ���ö����ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

	CButton::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(Cmybutton, CButton)
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()


BEGIN_DISPATCH_MAP(Cmybutton, CButton)
END_DISPATCH_MAP()

// ע��: ������� IID_Imybutton ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡��� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {FA12B997-F103-4706-9280-6B5480D9E8D9}
static const IID IID_Imybutton =
{ 0xFA12B997, 0xF103, 0x4706, { 0x92, 0x80, 0x6B, 0x54, 0x80, 0xD9, 0xE8, 0xD9 } };

BEGIN_INTERFACE_MAP(Cmybutton, CButton)
	INTERFACE_PART(Cmybutton, IID_Imybutton, Dispatch)	
	
END_INTERFACE_MAP()


// Cmybutton ��Ϣ�������
void Cmybutton::OnRButtonDown(UINT nFlags, CPoint point){
	AfxMessageBox(_T("�����ӳ�����"));
}

