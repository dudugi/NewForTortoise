#pragma once

//add by lida 2017/09/29
//重写目的	
//1.实现鼠标拖动改变3D饼图的角度
//2.实现点击3D图形时，发送图表上的tooltip信息

struct QLBCGP_CHART_INFO
{
	CString m_str_Label;
	CString m_str_X;
	CString m_str_Y;

	BCGPChartHitInfo::HitInfoTest	m_click_area;		//鼠标点击位置
	CPoint	m_pt;				//鼠标点击坐标

	QLBCGP_CHART_INFO()
	{
		m_str_Label = _T("");
		m_str_X = _T("");
		m_str_Y = _T("");
		m_click_area = BCGPChartHitInfo::HIT_NONE;		//点击说明详见 BCGPChartHitInfo
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
		BCG_LINE2D,			//2D线图
		BCG_Column2D,			//2D柱状图
		BCGP_Pie3D,			//3D饼图
		BCGP_ClusteredColumn3D,	//3D柱状图
	};

protected:
	CPoint		m_LBN_Down_pt;		//鼠标点击时的坐标
	UINT		m_ChartType;		//图表类型
	BOOL		m_bRotate;			//鼠标拖动是否旋转


protected:
	BOOL GetChartInfo(CPoint pt,QLBCGP_CHART_INFO& qci);

public:
	void EnableRotate(BOOL bRotate = TRUE);		//3d图是否可以旋转、跳跃

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

