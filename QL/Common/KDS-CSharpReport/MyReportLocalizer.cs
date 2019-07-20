using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using DevExpress.XtraReports;
using DevExpress.XtraReports.Localization;
using System.Runtime.InteropServices;
namespace KDS_CSharpReport
{
    //[Guid("C6EC115C-CD43-4619-8D41-A9CBF10F9D5D")]
    //[ClassInterface(ClassInterfaceType.None)]
    [ComVisible(false)] //不对外开放 yangjr 2017-6-25
    public class XtraReports_CN : ReportLocalizer
    {
        public override string Language
        {
            get
            {
                return "简体中文";
            }
        }

        public override string GetLocalizedString(ReportStringId id)
        {
            switch (id)
            {
                case ReportStringId.BandDsg_QuantityPerPage: return "一个页面集合";
                case ReportStringId.BandDsg_QuantityPerReport: return "一个报表集合";
                case ReportStringId.BCForm_Lbl_Binding: return "结合";
                case ReportStringId.BCForm_Lbl_Property: return "属性";
                case ReportStringId.CatAppearance: return "版面";
                case ReportStringId.CatBehavior: return "状态";
                case ReportStringId.CatData: return "数据";
                case ReportStringId.CatLayout: return "布局";
                case ReportStringId.CatNavigation: return "导航";
                case ReportStringId.CatPageSettings: return "页面设置";
                case ReportStringId.Cmd_AlignToGrid: return "对齐网格线";
                case ReportStringId.Cmd_BottomMargin: return "底端边缘";
                case ReportStringId.Cmd_BringToFront: return "移到最上层";
                case ReportStringId.Cmd_Copy: return "复制";
                case ReportStringId.Cmd_Cut: return "剪贴";
                case ReportStringId.Cmd_Delete: return "删除";
                case ReportStringId.Cmd_Detail: return "详细";
                case ReportStringId.Cmd_DetailReport: return "详细报表";
                case ReportStringId.Cmd_GroupFooter: return "群组尾";
                case ReportStringId.Cmd_GroupHeader: return "群组首";
                case ReportStringId.Cmd_InsertBand: return "插入区段";
                case ReportStringId.Cmd_InsertDetailReport: return "插入详细报表";
                case ReportStringId.Cmd_InsertUnboundDetailReport: return "非绑定";
                case ReportStringId.Cmd_PageFooter: return "页尾";
                case ReportStringId.Cmd_PageHeader: return "页首";
                case ReportStringId.Cmd_Paste: return "粘贴";
                case ReportStringId.Cmd_Properties: return "属性";
                case ReportStringId.Cmd_ReportFooter: return "报表尾";
                case ReportStringId.Cmd_ReportHeader: return "报表首";
                case ReportStringId.Cmd_RtfClear: return "清除";
                case ReportStringId.Cmd_RtfLoad: return "加载文件";
                case ReportStringId.Cmd_SendToBack: return "移到最下层";
                case ReportStringId.Cmd_TableDelete: return "删除(&L)";
                case ReportStringId.Cmd_TableDeleteCell: return "单元格(&L)";
                case ReportStringId.Cmd_TableDeleteColumn: return "列(&C)";
                case ReportStringId.Cmd_TableDeleteRow: return "行(&R)";
                case ReportStringId.Cmd_TableInsert: return "插入(&I)";
                case ReportStringId.Cmd_TableInsertCell: return "单元格(&C)";
                case ReportStringId.Cmd_TableInsertColumnToLeft: return "左列(&L)";
                case ReportStringId.Cmd_TableInsertColumnToRight: return "右列(&R)";
                case ReportStringId.Cmd_TableInsertRowAbove: return "上行(&A)";
                case ReportStringId.Cmd_TableInsertRowBelow: return "下行(&B)";
                case ReportStringId.Cmd_TopMargin: return "顶端边缘";
                case ReportStringId.Cmd_ViewCode: return "检视代码";
                //case ReportStringId.FindForm_Msg_FinishedSearching: return "搜索文件完成";
                //case ReportStringId.FindForm_Msg_TotalFound: return "合计查找:";
                //case ReportStringId.FSForm_Btn_Delete: return "删除";
                //case ReportStringId.FSForm_GrBox_Sample: return "范例";
                //case ReportStringId.FSForm_Lbl_Category: return "类别";
                //case ReportStringId.FSForm_Lbl_CustomGeneral: return "一般格式不包含特殊数字格式";
                //case ReportStringId.FSForm_Lbl_Prefix: return "上标";
                //case ReportStringId.FSForm_Lbl_Suffix: return "下标";
                //case ReportStringId.FSForm_Msg_BadSymbol: return "损坏的符号";
                //case ReportStringId.FSForm_Tab_Custom: return "自定义";
                //case ReportStringId.FSForm_Tab_StandardTypes: return "标准类型";
                //case ReportStringId.Msg_CantFitBarcodeToControlBounds: return "条形码控件的边界太小";
                case ReportStringId.Msg_CreateReportInstance: return "您试图打开一个不同类型的报表来编辑。是否确定建立实例？";
                case ReportStringId.Msg_CreateSomeInstance: return "在窗体中不能建立两个实例类。";
                //case ReportStringId.Msg_CyclicBoormarks: return "报表循环书签";
                case ReportStringId.Msg_DontSupportMulticolumn: return "详细报表不支持多字段。";
                case ReportStringId.Msg_FileCorrupted: return "不能加载报表，文件可能被破坏或者报表组件丢失。";
                case ReportStringId.Msg_FileNotFound: return "文件没有找到";
                case ReportStringId.Msg_FillDataError: return "数据加载时发生错误。错误为：";
                case ReportStringId.Msg_IncorrectArgument: return "参数值输入不正确";
                case ReportStringId.Msg_IncorrectBandType: return "无效的带型";
                //case ReportStringId.Msg_InvalidBarcodeText: return "在文本中有无效的字符";
                //case ReportStringId.Msg_InvalidBarcodeTextFormat: return "无效的文本格式";
                case ReportStringId.Msg_InvalidMethodCall: return "对象的当前状态下不能调用此方法";
                case ReportStringId.Msg_InvalidReportSource: return "无法设置原报表";
                //case ReportStringId.Msg_InvPropName: return "无效的属性名";
                case ReportStringId.Msg_ScriptError: return "在脚本中发现错误： {0}";
                case ReportStringId.Msg_ScriptExecutionError: return "在脚本执行过程中发现错误 {0}:  {1} 过程 {0} 被运行，将不能再被调用。";
                case ReportStringId.Msg_WrongReportClassName: return "一个错误发生在并行化期间 - 可能是报表类名错误";
                case ReportStringId.MultiColumnDesignMsg1: return "重复列之间的空位";
                case ReportStringId.MultiColumnDesignMsg2: return "控件位置不正确，将会导致打印错误";
                case ReportStringId.PanelDesignMsg: return "在此可放置不同控件";
                case ReportStringId.RepTabCtl_Designer: return "设计";
                case ReportStringId.RepTabCtl_HtmlView: return "HTML视图";
                case ReportStringId.RepTabCtl_Preview: return "预览";
                //case ReportStringId.SSForm_Btn_Close: return "关闭";
                //case ReportStringId.SSForm_Caption: return "式样单编辑";
                case ReportStringId.SSForm_Msg_FileFilter: return "Report StyleSheet files (*.repss)|*.repss|All files (*.*)|*.*";
                case ReportStringId.SSForm_Msg_InvalidFileFormat: return "无效的文件格式";
                case ReportStringId.SSForm_Msg_MoreThanOneStyle: return "你选择了多过一个以上的式样";
                case ReportStringId.SSForm_Msg_NoStyleSelected: return "没有式样被选中";
                case ReportStringId.SSForm_Msg_SelectedStylesText: return "被选中的式样";
                case ReportStringId.SSForm_Msg_StyleNamePreviewPostfix: return "式样";
                //case ReportStringId.SSForm_Msg_StyleSheetError: return "StyleSheet错误";
                //case ReportStringId.SSForm_TTip_AddStyle: return "添加式样";
                //case ReportStringId.SSForm_TTip_ClearStyles: return "清除式样";
                //case ReportStringId.SSForm_TTip_LoadStyles: return "从文件中读入式样";
                //case ReportStringId.SSForm_TTip_PurgeStyles: return "清除式样";
                //case ReportStringId.SSForm_TTip_RemoveStyle: return "移除式样";
                //case ReportStringId.SSForm_TTip_SaveStyles: return "保存式样到文件";
                case ReportStringId.UD_FormCaption: return "XtraReport设计";
                case ReportStringId.UD_Msg_ReportChanged: return "报表内容已被修改，是否须要储存？";
                case ReportStringId.UD_ReportDesigner: return "XtraReport设计";
                case ReportStringId.UD_TTip_AlignBottom: return "对齐主控项的下缘";
                case ReportStringId.UD_TTip_AlignHorizontalCenters: return "对齐主控项的垂直中间";
                case ReportStringId.UD_TTip_AlignLeft: return "对齐主控项的左缘";
                case ReportStringId.UD_TTip_AlignRight: return "对齐主控项的右缘";
                case ReportStringId.UD_TTip_AlignToGrid: return "对齐网格线";
                case ReportStringId.UD_TTip_AlignTop: return "对齐主控项的上缘";
                case ReportStringId.UD_TTip_AlignVerticalCenters: return "对齐主控项的水平中央";
                case ReportStringId.UD_TTip_BringToFront: return "移到最上层";
                case ReportStringId.UD_TTip_CenterHorizontally: return "水平置中";
                case ReportStringId.UD_TTip_CenterVertically: return "垂直置中";
                case ReportStringId.UD_TTip_EditCopy: return "复制";
                case ReportStringId.UD_TTip_EditCut: return "剪贴";
                case ReportStringId.UD_TTip_EditPaste: return "粘贴";
                case ReportStringId.UD_TTip_FileOpen: return "打开文件";
                case ReportStringId.UD_TTip_FileSave: return "保存文件";
                case ReportStringId.UD_TTip_FormatAlignLeft: return "左对齐";
                case ReportStringId.UD_TTip_FormatAlignRight: return "右对齐";
                case ReportStringId.UD_TTip_FormatBackColor: return "背景颜色";
                case ReportStringId.UD_TTip_FormatBold: return "粗体";
                case ReportStringId.UD_TTip_FormatCenter: return "居中";
                case ReportStringId.UD_TTip_FormatFontName: return "字体";
                case ReportStringId.UD_TTip_FormatFontSize: return "大小";
                case ReportStringId.UD_TTip_FormatForeColor: return "前景颜色";
                case ReportStringId.UD_TTip_FormatItalic: return "斜体";
                case ReportStringId.UD_TTip_FormatJustify: return "两端对齐";
                case ReportStringId.UD_TTip_FormatUnderline: return "下划线";
                case ReportStringId.UD_TTip_HorizSpaceConcatenate: return "移除水平间距";
                case ReportStringId.UD_TTip_HorizSpaceDecrease: return "减少水平间距";
                case ReportStringId.UD_TTip_HorizSpaceIncrease: return "增加水平间距";
                case ReportStringId.UD_TTip_HorizSpaceMakeEqual: return "将垂直间距设为相等";
                case ReportStringId.UD_TTip_Redo: return "恢复";
                case ReportStringId.UD_TTip_SendToBack: return "移到最下层";
                case ReportStringId.UD_TTip_SizeToControl: return "设置成相同大小";
                case ReportStringId.UD_TTip_SizeToControlHeight: return "设置成相同高度";
                case ReportStringId.UD_TTip_SizeToControlWidth: return "设置成相同宽度";
                case ReportStringId.UD_TTip_SizeToGrid: return "依网格线调整大小";
                case ReportStringId.UD_TTip_Undo: return "撤消";
                case ReportStringId.UD_TTip_VertSpaceConcatenate: return "移除垂直间距";
                case ReportStringId.UD_TTip_VertSpaceDecrease: return "减少垂直间距";
                case ReportStringId.UD_TTip_VertSpaceIncrease: return "增加垂直间距";
                case ReportStringId.UD_TTip_VertSpaceMakeEqual: return "将垂直间距设为相等";
            }
            return base.GetLocalizedString(id);
        }        
    }
}
