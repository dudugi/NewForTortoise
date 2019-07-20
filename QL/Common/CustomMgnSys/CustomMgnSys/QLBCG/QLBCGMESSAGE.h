#pragma once

//网格
#define BCGM_GRID_MSG_BASE		  WM_USER + 1000
#define BCGM_GRID_ITEM_RCLICK		BCGM_GRID_MSG_BASE + 1
#define BCGM_GRID_ITEM_LCLICK		BCGM_GRID_MSG_BASE + 2
#define BCGM_GRID_ITEM_LDBCLICK		BCGM_GRID_MSG_BASE + 3
#define BCGM_GRID_ITEM_BECHANGED	BCGM_GRID_MSG_BASE + 4	//修改
#define BCGM_GRID_ITEM_HEADRCLICK	BCGM_GRID_MSG_BASE + 5//表头右键

//图表		
#define BCGM_CHART_MOUSE_MOVE		BCGM_GRID_MSG_BASE + 6
#define BCGM_CHART_MOUSE_DOWN		BCGM_GRID_MSG_BASE + 7	
#define BCGM_CHART_MOUSE_UP		BCGM_GRID_MSG_BASE + 8	
#define BCGM_CHART_MOUSE_WHEEL		BCGM_GRID_MSG_BASE + 9	
#define BCGM_CHART_LBTN_UP			BCGM_GRID_MSG_BASE + 10
#define BCGM_CHART_LBTN_DBCLICK		BCGM_GRID_MSG_BASE + 11
#define BCGM_CHART_RBTN_UP			BCGM_GRID_MSG_BASE + 12


//表格界面编辑消息处理 wangzl 2017-11-21
#define BCGM_GRID_ITEM_BEGINEDIT		BCGM_GRID_MSG_BASE + 13
#define BCGM_GRID_ITEM_ENDEDIT			BCGM_GRID_MSG_BASE + 14	//修改
#define BCGM_GRID_TITLE_FILTER_CHANGED (BCGM_GRID_MSG_BASE + 15) //标题头过滤消息	by WangZY 2018/03/12

//分页网格切换页码时外部界面自己给自己转发消息 yangjr 2018/6/6
#define BCGM_GRID_PAGECHANGED_ME2ME (BCGM_GRID_MSG_BASE + 16) 

