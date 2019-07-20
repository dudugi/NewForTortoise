#pragma once

//add by lida 2017/09/29
//��дĿ��	
//1.ʵ������϶��ı�3D��ͼ�ĽǶ�
//2.ʵ�ֵ��3Dͼ��ʱ������ͼ���ϵ�tooltip��Ϣ

struct QLBCGP_CHART_INFO
{
	CString m_str_Label;
	CString m_str_X;
	CString m_str_Y;

	BCGPChartHitInfo::HitInfoTest	m_click_area;		//�����λ��
	CPoint	m_pt;				//���������

	QLBCGP_CHART_INFO()
	{
		m_str_Label = _T("");
		m_str_X = _T("");
		m_str_Y = _T("");
		m_click_area = BCGPChartHitInfo::HIT_NONE;		//���˵����� BCGPChartHitInfo
	}
};


class CQLBCGChartCtrl : public CBCGPChartCtrl
{
public:
	CQLBCGChartCtrl(UINT nType);
	~CQLBCGChartCtrl(void);

	enum
	{
		Type_None = 0,
		BCG_LINE2D,			//2D��ͼ
		BCG_Column2D,			//2D��״ͼ
		BCGP_Pie3D,			//3D��ͼ
		BCGP_ClusteredColumn3D,	//3D��״ͼ
	};

protected:
	CPoint		m_LBN_Down_pt;		//�����ʱ������
	UINT		m_ChartType;		//ͼ������
	BOOL		m_bRotate;			//����϶��Ƿ���ת


protected:
	BOOL GetChartInfo(CPoint pt,QLBCGP_CHART_INFO& qci);

public:
	void EnableRotate(BOOL bRotate = TRUE);		//3dͼ�Ƿ������ת����Ծ

	// Mouse events:
	virtual BOOL OnMouseDown(int nButton, const CBCGPPoint& pt);
	virtual void OnMouseUp(int nButton, const CBCGPPoint& pt);
	virtual void OnMouseMove(const CBCGPPoint& pt);
	virtual BOOL OnMouseWheel(const CBCGPPoint& pt, short zDelta);

	DECLARE_MESSAGE_MAP()

	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
};

