// ShowNetListView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "KD_Project.h"
#include "ShowNetListView.h"


// ShowNetListView

IMPLEMENT_DYNCREATE(ShowNetListView, CListView)

ShowNetListView::ShowNetListView()
{

}

ShowNetListView::~ShowNetListView()
{
}

BEGIN_MESSAGE_MAP(ShowNetListView, CListView)
END_MESSAGE_MAP()


// ShowNetListView ���

#ifdef _DEBUG
void ShowNetListView::AssertValid() const
{
	CListView::AssertValid();
}

#ifndef _WIN32_WCE
void ShowNetListView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif
#endif //_DEBUG


// ShowNetListView ��Ϣ�������


BOOL ShowNetListView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ����ר�ô����/����û���

	//return CListView::PreCreateWindow(cs);
		if (!CListView::PreCreateWindow (cs))  
	    return FALSE;  
	cs.style |= WS_CHILD|WS_VISIBLE|LVS_REPORT|LVS_OWNERDRAWFIXED;

	return TRUE;
}
