#pragma once
// CEditDoubleNum
/*
by yangjr 2017-7-4
�����ã�ֻ��������С���㡢���֡������ŵ�Edit�ؼ�
*/
class CEditDoubleNum : public CBCGPEdit
{
	DECLARE_DYNAMIC(CEditDoubleNum)

public:
	CEditDoubleNum();
	CEditDoubleNum(int maxLength,int nDec);
	virtual ~CEditDoubleNum();

	void SetEditDoubleNum(int maxLength,int nDec);

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnChar( UINT nChar, UINT nRepCnt, UINT nFlags );
private:
	int m_nLength; //��󳤶�
	int m_nDec;  //С���㾫��
	virtual void PreSubclassWindow();
};


