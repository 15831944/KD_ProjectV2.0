#pragma once


// ShowNetListView ��ͼ

class ShowNetListView : public CListView
{
	DECLARE_DYNCREATE(ShowNetListView)

protected:
	ShowNetListView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~ShowNetListView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
};

