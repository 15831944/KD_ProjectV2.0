#pragma once


// ShowNetTreeView ��ͼ

class ShowNetTreeView : public CTreeView
{
	DECLARE_DYNCREATE(ShowNetTreeView)

protected:
	ShowNetTreeView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~ShowNetTreeView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
};
