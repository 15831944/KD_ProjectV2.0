// ShowNetTreeView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "KD_Project.h"
#include "ShowNetTreeView.h"


// ShowNetTreeView

IMPLEMENT_DYNCREATE(ShowNetTreeView, CTreeView)

ShowNetTreeView::ShowNetTreeView()
{

}

ShowNetTreeView::~ShowNetTreeView()
{
}

BEGIN_MESSAGE_MAP(ShowNetTreeView, CTreeView)
END_MESSAGE_MAP()


// ShowNetTreeView ���

#ifdef _DEBUG
void ShowNetTreeView::AssertValid() const
{
	CTreeView::AssertValid();
}

#ifndef _WIN32_WCE
void ShowNetTreeView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif
#endif //_DEBUG


// ShowNetTreeView ��Ϣ�������



BOOL ShowNetTreeView::PreCreateWindow(CREATESTRUCT& cs)//����tree���
{
	// TODO: �ڴ����ר�ô����/����û���
	if (!CTreeView::PreCreateWindow (cs))  
	    return FALSE;  
	cs.style |= TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS |  
	TVS_SHOWSELALWAYS;

	 return TRUE;
}


