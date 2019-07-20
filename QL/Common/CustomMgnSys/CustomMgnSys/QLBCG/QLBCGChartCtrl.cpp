#include "StdAfx.h"
#include "QLBCGChartCtrl.h"
#include "QLBCGMESSAGE.h"

CQLBCGChartCtrl::CQLBCGChartCtrl(UINT nType)
{
	m_ChartType = nType;
	m_bRotate = FALSE;
}

CQLBCGChartCtrl::~CQLBCGChartCtrl(void)
{

}

void CQLBCGChartCtrl::EnableRotate(BOOL bRotate /*= TRUE*/)
{
	m_bRotate = bRotate;
}

BOOL CQLBCGChartCtrl::OnMouseDown(int nButton, const CBCGPPoint& pt)
{
	m_LBN_Down_pt = pt;

	return CBCGPChartCtrl::OnMouseDown(nButton,pt);
}

void CQLBCGChartCtrl::OnMouseUp(int nButton, const CBCGPPoint& pt)
{
	m_LBN_Down_pt = /*CPoint(0,0)*/pt;
	CBCGPChartCtrl::OnMouseUp(nButton,pt);
}

void CQLBCGChartCtrl::OnMouseMove(const CBCGPPoint& pt)
{
	CBCGPChartCtrl::OnMouseMove(pt);

	if (!m_bRotate)
		return;
	if ((GetKeyState(VK_LBUTTON) & 0x80 )== 0x80)
	{
		if (m_ChartType == Type_None)
			return;

		CBCGPChartVisualObject* pChart = GetChart();
		int xDelta = 10;
		double yDelta = 10.;
		if (m_ChartType == BCGP_Pie3D)
		{
			for (int i = 0; i < pChart->GetSeriesCount(); i++)
			{
				CBCGPChartPieSeries* pSeries = DYNAMIC_DOWNCAST(CBCGPChartPieSeries, pChart->GetSeries(i));
				ASSERT_VALID(pSeries);
				if (pSeries == NULL)
					continue;

				int nRotationAngle = pSeries->GetPieRotation();
				double dblPieAngle = pSeries->GetPieAngle();

				if (m_LBN_Down_pt.y > pt.y)		//鼠标向上
				{
					dblPieAngle -= (m_LBN_Down_pt.y - pt.y) / 20 * yDelta;
					if (dblPieAngle < 1.)
						dblPieAngle = 1.;
				}
				else if (m_LBN_Down_pt.y < pt.y)	//鼠标向下
				{
					dblPieAngle += (pt.y - m_LBN_Down_pt.y) / 20 * yDelta;	
				}

				if (m_LBN_Down_pt.x > pt.x)
				{
					nRotationAngle -= (m_LBN_Down_pt.x - pt.x) / 20 * xDelta;
				}
				else if (m_LBN_Down_pt.x < pt.x)
				{
					nRotationAngle += (pt.x - m_LBN_Down_pt.x) / 20 * xDelta;	
				}
				pSeries->SetPieRotation(nRotationAngle);
				pSeries->SetPieAngle(dblPieAngle);
			}
		}
		else if (m_ChartType == BCGP_ClusteredColumn3D)
		{
			CBCGPChartDiagram3D* pDiagram3D = pChart->GetDiagram3D();
			if (pDiagram3D != NULL)
			{
				double xRotation = pDiagram3D->GetXRotation();
				double yRotation = pDiagram3D->GetYRotation();
				double dblPerspectivePercent = pDiagram3D->GetPerspectivePercent();

				if (m_LBN_Down_pt.y > pt.y)		//鼠标向上
				{
					yRotation += (m_LBN_Down_pt.y - pt.y) / 20 * yDelta;
				}
				else if (m_LBN_Down_pt.y < pt.y)	//鼠标向下
				{
					yRotation -= (pt.y - m_LBN_Down_pt.y) / 20 * yDelta;	
				}
				if (m_LBN_Down_pt.x > pt.x)
				{
					xRotation -= (m_LBN_Down_pt.x - pt.x) / 20 * xDelta;
				}
				else if (m_LBN_Down_pt.x < pt.x)
				{
					xRotation += (pt.x - m_LBN_Down_pt.x) / 20 * xDelta;	
				}
				pDiagram3D->SetPosition(xRotation, yRotation, dblPerspectivePercent);
			}
		}
		else if (m_ChartType == BCG_LINE2D)
		{
		}

		pChart->SetDirty();
		pChart->Redraw();
		m_LBN_Down_pt = pt;
	}
}

BOOL CQLBCGChartCtrl::OnMouseWheel(const CBCGPPoint& pt, short zDelta)
{
	return CBCGPChartCtrl::OnMouseWheel(pt,zDelta);
}

BEGIN_MESSAGE_MAP(CQLBCGChartCtrl, CBCGPChartCtrl)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

void CQLBCGChartCtrl::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	//发送点击图表上的信息 add by lida 2017/11/14
	QLBCGP_CHART_INFO qci;
	GetChartInfo(point,qci);
	qci.m_pt = point;
	this->GetOwner()->SendMessage (BCGM_CHART_LBTN_DBCLICK, (WPARAM)this, LPARAM(&qci));
	//end

	CBCGPChartCtrl::OnLButtonDblClk(nFlags, point);
}

void CQLBCGChartCtrl::OnLButtonUp(UINT nFlags, CPoint point)
{
	QLBCGP_CHART_INFO qci;
	GetChartInfo(point,qci);
	qci.m_pt = point;
	this->GetOwner()->SendMessage (BCGM_CHART_LBTN_UP, (WPARAM)this, LPARAM(&qci));
	CBCGPChartCtrl::OnLButtonUp(nFlags, point);
}

void CQLBCGChartCtrl::OnRButtonUp(UINT nFlags, CPoint point)
{
	//发送点击图表上的信息 add by lida 2017/11/14
	QLBCGP_CHART_INFO qci;
	GetChartInfo(point,qci);
	qci.m_pt = point;
	this->GetOwner()->SendMessage (BCGM_CHART_RBTN_UP, (WPARAM)this, LPARAM(&qci));
	//end

	CBCGPChartCtrl::OnRButtonUp(nFlags, point);
}

BOOL CQLBCGChartCtrl::GetChartInfo(CPoint pt,QLBCGP_CHART_INFO& qci)
{
	CBCGPBaseVisualObject* pVisualObject = this->GetVisualObject();
	if (pVisualObject == NULL || !pVisualObject->GetRect().PtInRect(pt))
	{
		return FALSE;
	}
	CBCGPChartVisualObject* pVisualObject_chart = (CBCGPChartVisualObject* )pVisualObject;
	if (pVisualObject_chart == NULL)
	{
		return FALSE;
	}
	BCGPChartHitInfo hi;
	BOOL bHitResult = pVisualObject_chart->HitTest(pt,&hi, (DWORD)(BCGPChartHitInfo::HIT_AXIS 
		| BCGPChartHitInfo::HIT_DATA_POINT | BCGPChartHitInfo::HIT_DATA_LABEL|
		BCGPChartHitInfo::HIT_AXIS_SCALE_BREAK | BCGPChartHitInfo::HIT_DATA_TABLE));

	qci.m_click_area = hi.m_hitInfo;

	CBCGPChartSeries* pSeries = pVisualObject_chart->GetSeries(hi.m_nIndex1);
	if (pSeries == NULL)
	{
		return FALSE;
	}

	qci.m_str_X = pSeries->m_strSeriesName;

	CBCGPChartAxis* pAxisY = pSeries->GetRelatedAxis(CBCGPChartSeries::AI_Y);
	CBCGPChartAxis* pAxisX = pSeries->GetRelatedAxis(CBCGPChartSeries::AI_X);

	ASSERT_VALID(pAxisY);
	ASSERT_VALID(pAxisX);
	if (pAxisY == NULL || pAxisX == NULL)
	{
		return FALSE;
	}

	CBCGPChartValue valY = pSeries->GetDataPointValue(hi.m_nIndex2);

	if (valY.IsEmpty())
	{
		return FALSE;
	}

	CBCGPChartValue valX = pSeries->GetDataPointValue(hi.m_nIndex2, CBCGPChartData::CI_X);

	if (pAxisY->IsIndexedSeries())
	{
		valX.SetValue(hi.m_nIndex2);
	}
	else if (valX.IsEmpty())
	{
		valX.SetValue(hi.m_nIndex2 + 1);
	}

	pAxisY->GetDisplayedLabel(valY.GetValue(), qci.m_str_Y);
	pAxisX->GetDisplayedLabel(valX.GetValue(), qci.m_str_Label);


	return TRUE;
}
