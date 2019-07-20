#pragma once
// CEditDoubleNum
/*
by yangjr 2017-7-4
类作用，只允许输入小数点、数字、正负号的Edit控件
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
	int m_nLength; //最大长度
	int m_nDec;  //小数点精度
	virtual void PreSubclassWindow();
};


