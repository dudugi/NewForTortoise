using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;
using System.Drawing;
using DevExpress.XtraReports.UI;
using DevExpress.XtraPrinting;
using DevExpress.XtraGrid;
using DevExpress.XtraGrid.Views;
namespace DXMyCreateReport
{
    public class CreateReportByDataSet
    {
        string m_strTitle;
        DataSet m_dsFieldXml;
        DataSet m_dsDataXml;
        DataSet m_dsSumXml;
        bool m_bShowPageFoot;//是否显示页脚 yangjr 2017-6-28
        bool m_bShowReportHeader;//是否显示报表头 yangjr 2017-6-28

        public CreateReportByDataSet()
        {
            m_strTitle = "报表标题";
            m_dsFieldXml = null;
            m_dsDataXml = null;
            m_dsSumXml = null;
            m_bShowPageFoot = true;
            m_bShowReportHeader = true;
        }
        
        public XtraReport NewReportByDataSet(string strTitle, DataSet dsField,
            DataSet dsData, DataSet dsSum, bool bLandscape = false)
        {
            m_strTitle = strTitle;
            m_dsFieldXml = dsField;
            m_dsSumXml = dsSum;

            XtraReport rpt = new XtraReport();// 建立报表实例

            rpt.DataSource = dsData;
            if(null != dsData
               && dsData.Tables.Count > 0)
            {
                rpt.DataMember = dsData.Tables[0].TableName;
            }

            rpt.Landscape = bLandscape;

            InitBands(rpt);//添加带区（Bands）
            InitStyles(rpt);//添加Styles 
            InitDetailsBasedonXRTable(rpt);//用XRTable显示报表 

            return rpt;
        }

        //通过动态创建报表并加载数据导出xls文件 yangjr 2017-6-28
        public bool ExportXlsByDataSet(string strTitle, DataSet dsField,
            DataSet dsData, DataSet dsSum,string saveXlsName)
        {
            m_strTitle = strTitle;
            m_dsFieldXml = dsField;
            m_dsSumXml = dsSum;
            m_bShowPageFoot = false;
            m_bShowReportHeader = false;
            XtraReport rpt = new XtraReport();// 建立报表实例            
            rpt.DataSource = dsData;
            if (null != dsData
               && dsData.Tables.Count > 0)
            {
                rpt.DataMember = dsData.Tables[0].TableName;
            }
           
            InitBands(rpt);//添加带区（Bands）
            InitStyles(rpt);//添加Styles 
            InitDetailsBasedonXRTable(rpt);//用XRTable显示报表 

            XlsExportOptions xlsOptions = rpt.ExportOptions.Xls;
            // Set XLS-specific export options.
            xlsOptions.ShowGridLines = false;
            xlsOptions.TextExportMode = TextExportMode.Value;
            // Export the report to XLS.            
            try
            {
                rpt.ExportToXls(saveXlsName);
            }
            catch (Exception) 
            {
                //其他程序已打开文件关闭之前的
                return false;
            }
            return true;
        }

        public bool ExportXlsByDataSetNew(string strTitle, DataSet dsField,
            DataSet dsData, DataSet dsSum, string saveXlsName)
        {
            GridControl grid = new GridControl();
            DevExpress.XtraGrid.Views.Grid.GridView view = new DevExpress.XtraGrid.Views.Grid.GridView();
            grid.ViewCollection.Add(view);
            grid.MainView = view;
            view.GridControl = grid;

            foreach (DataColumn dc in dsData.Tables[0].Columns)
            {
                DevExpress.XtraGrid.Columns.GridColumn gridColumnNumber = view.Columns.AddVisible(dc.ColumnName);
                gridColumnNumber.FieldName = dc.ColumnName;
            }


            grid.DataSource = dsData;
            //this.Controls.Add(grid);//重要
            grid.ForceInitialize();//重要
            view.BestFitColumns();
            view.ExportToXls(saveXlsName);


            return true;
        }

        //通过动态创建报表并加载数据导出txt文件 yangjr 2017-7-3
        public bool ExportTxtFileByXmlText(string strTitle, DataSet dsField,
            DataSet dsData, DataSet dsSum, string saveFileName)
        {
            m_strTitle = strTitle;
            m_dsFieldXml = dsField;
            m_dsSumXml = dsSum;
            m_bShowPageFoot = false;
            m_bShowReportHeader = false;
            XtraReport rpt = new XtraReport();// 建立报表实例            
            rpt.DataSource = dsData;
            if (null != dsData
               && dsData.Tables.Count > 0)
            {
                rpt.DataMember = dsData.Tables[0].TableName;
            }

            InitBands(rpt);//添加带区（Bands）
            InitStyles(rpt);//添加Styles 
            InitDetailsBasedonXRTable(rpt);//用XRTable显示报表 

            TextExportOptions txtOptions = rpt.ExportOptions.Text;            
            //txtOptions.QuoteStringsWithSeparators = true;
            txtOptions.TextExportMode = TextExportMode.Value;                 
            try
            {
                rpt.ExportToText(saveFileName);
            }
            catch (Exception)
            {
                //其他程序已打开文件关闭之前的
                return false;
            }
            return true;
        }

        //通过动态创建报表并加载数据导出Jpg文件 yangjr 2017-7-3
        public bool ExportJpgFileByXmlText(string strTitle, DataSet dsField,
            DataSet dsData, DataSet dsSum, string saveFileName)
        {
            m_strTitle = strTitle;
            m_dsFieldXml = dsField;
            m_dsSumXml = dsSum;
            m_bShowPageFoot = false;
            m_bShowReportHeader = false;
            XtraReport rpt = new XtraReport();// 建立报表实例            
            rpt.DataSource = dsData;
            if (null != dsData
               && dsData.Tables.Count > 0)
            {
                rpt.DataMember = dsData.Tables[0].TableName;
            }

            InitBands(rpt);//添加带区（Bands）
            InitStyles(rpt);//添加Styles 
            InitDetailsBasedonXRTable(rpt);//用XRTable显示报表 

            ImageExportOptions options = rpt.ExportOptions.Image;
            //txtOptions.QuoteStringsWithSeparators = true;
                           
            try
            {
                rpt.ExportToImage(saveFileName);
            }
            catch (Exception)
            {
                //其他程序已打开文件关闭之前的
                return false;
            }
            return true;
        }

        public DataSet FillDataset()
        {
            DataSet myDataSet = new DataSet();
            myDataSet.DataSetName = "myDataSet";
            DataTable table = new DataTable("Detail");

            myDataSet.Tables.Add(table);

            table.Columns.Add("Name", typeof(String));
            table.Columns.Add("Address", typeof(String));
            table.Columns.Add("Sex", typeof(String));
            table.Columns.Add("Birthplace", typeof(String));
            table.Columns.Add("Birthday", typeof(String));

            table.Rows.Add(new object[] { "1Zhang", "辽宁锦州", "女", "辽宁", "1983-XX-XX" });
            table.Rows.Add(new object[] { "2Wang", "广东深圳", "男", "辽宁", "1984-10-XX" });
            table.Rows.Add(new object[] { "3Li", "北京", "男", "北京", "1985-XX-XX" });
            table.Rows.Add(new object[] { "4Zhao", "上海", "女", "湖南", "1984-XX-XX" });
            table.Rows.Add(new object[] { "5Liu", "广东深圳", "女", "辽宁", "1985-2-XX" });
            table.Rows.Add(new object[] { "6Zhang", "辽宁锦州", "女", "辽宁", "1983-XX-XX" });
            table.Rows.Add(new object[] { "7Wang", "广东深圳", "男", "辽宁", "1984-10-XX" });
            table.Rows.Add(new object[] { "8Li", "北京", "男", "北京", "1985-XX-XX" });
            table.Rows.Add(new object[] { "9Zhao", "上海", "女", "湖南", "1984-XX-XX" });
            table.Rows.Add(new object[] { "10Liu", "广东深圳", "女", "辽宁", "1985-2-XX" });
            table.Rows.Add(new object[] { "11Zhang", "辽宁锦州", "女", "辽宁", "1983-XX-XX" });
            table.Rows.Add(new object[] { "12Wang", "广东深圳", "男", "辽宁", "1984-10-XX" });
            table.Rows.Add(new object[] { "13Li", "北京", "男", "北京", "1985-XX-XX" });
            table.Rows.Add(new object[] { "14Zhao", "上海", "女", "湖南", "1984-XX-XX" });
            table.Rows.Add(new object[] { "15Liu", "广东深圳", "女", "辽宁", "1985-2-XX" });
            table.Rows.Add(new object[] { "16Zhang", "辽宁锦州", "女", "辽宁", "1983-XX-XX" });
            table.Rows.Add(new object[] { "17Wang", "广东深圳", "男", "辽宁", "1984-10-XX" });
            table.Rows.Add(new object[] { "18Li", "北京", "男", "北京", "1985-XX-XX" });
            table.Rows.Add(new object[] { "19Zhao", "上海", "女", "湖南", "1984-XX-XX" });
            table.Rows.Add(new object[] { "20Liu", "广东深圳", "女", "辽宁", "1985-2-XX" });
            table.Rows.Add(new object[] { "21Zhang", "辽宁锦州", "女", "辽宁", "1983-XX-XX" });
            table.Rows.Add(new object[] { "22Wang", "广东深圳", "男", "辽宁", "1984-10-XX" });
            table.Rows.Add(new object[] { "23Li", "北京", "男", "北京", "1985-XX-XX" });
            table.Rows.Add(new object[] { "24Zhao", "上海", "女", "湖南", "1984-XX-XX" });
            table.Rows.Add(new object[] { "25Liu", "广东深圳", "女", "辽宁", "1985-2-XX" });
            table.Rows.Add(new object[] { "26Zhang", "辽宁锦州", "女", "辽宁", "1983-XX-XX" });
            table.Rows.Add(new object[] { "27Wang", "广东深圳", "男", "辽宁", "1984-10-XX" });
            table.Rows.Add(new object[] { "28Li", "北京", "男", "北京", "1985-XX-XX" });
            table.Rows.Add(new object[] { "29Zhao", "上海", "女", "湖南", "1984-XX-XX" });
            table.Rows.Add(new object[] { "30Liu", "广东深圳", "女", "辽宁", "1985-2-XX" });
            table.Rows.Add(new object[] { "31Zhang", "辽宁锦州", "女", "辽宁", "1983-XX-XX" });
            table.Rows.Add(new object[] { "32Wang", "广东深圳", "男", "辽宁", "1984-10-XX" });
            table.Rows.Add(new object[] { "33Li", "北京", "男", "北京", "1985-XX-XX" });
            table.Rows.Add(new object[] { "34Zhao", "上海", "女", "湖南", "1984-XX-XX" });
            table.Rows.Add(new object[] { "35Liu", "广东深圳", "女", "辽宁", "1985-2-XX" });
            table.Rows.Add(new object[] { "36Liu", "广东深圳", "女", "辽宁", "1985-2-XX" });
            table.Rows.Add(new object[] { "37Zhang", "辽宁锦州", "女", "辽宁", "1983-XX-XX" });
            table.Rows.Add(new object[] { "38Wang", "广东深圳", "男", "辽宁", "1984-10-XX" });
            table.Rows.Add(new object[] { "39Li", "北京", "男", "北京", "1985-XX-XX" });
            table.Rows.Add(new object[] { "40Zhao", "上海", "女", "湖南", "1984-XX-XX" });
            table.Rows.Add(new object[] { "41Liu", "广东深圳", "女", "辽宁", "1985-2-XX" });
            table.Rows.Add(new object[] { "42Liu", "广东深圳", "女", "辽宁", "1985-2-XX" });
            table.Rows.Add(new object[] { "43Zhang", "辽宁锦州", "女", "辽宁", "1983-XX-XX" });
            table.Rows.Add(new object[] { "44Wang", "广东深圳", "男", "辽宁", "1984-10-XX" });
            table.Rows.Add(new object[] { "45Li", "北京", "男", "北京", "1985-XX-XX" });
            table.Rows.Add(new object[] { "46Zhao", "上海", "女", "湖南", "1984-XX-XX" });
            table.Rows.Add(new object[] { "47Liu", "广东深圳", "女", "辽宁", "1985-2-XX" });
                                           
            return myDataSet;              
        }

        public void InitBands(XtraReport rpt)
        {
            TopMarginBand topBand = new TopMarginBand();
            DetailBand detail = new DetailBand();
            PageHeaderBand pageHeader = new PageHeaderBand();
            ReportFooterBand reportFooter = new ReportFooterBand();
            BottomMarginBand bottomMargin = new BottomMarginBand();

            topBand.Height = 50;
            bottomMargin.Height = 50;
            rpt.Margins.Left = 50;
            rpt.Margins.Right = 50;

            detail.Height = 20;
            if (rpt.Landscape)
            {
                detail.Width = rpt.PageWidth - (rpt.Margins.Left + rpt.Margins.Right);
            }
            else 
            {
                detail.Width = rpt.PageHeight - (rpt.Margins.Top + rpt.Margins.Bottom);
            }
            
            reportFooter.Height = 40;
            reportFooter.Width = rpt.PageWidth - (rpt.Margins.Left + rpt.Margins.Right);
            
            pageHeader.Height = 20;
            pageHeader.Width = rpt.PageWidth - (rpt.Margins.Left + rpt.Margins.Right);

            rpt.Bands.AddRange(new DevExpress.XtraReports.UI.Band[] 
                { topBand,detail, pageHeader, reportFooter,bottomMargin});

        }

        public void InitStyles(XtraReport rep)
        {
            //奇偶行样式设置
            XRControlStyle oddStyle = new XRControlStyle();
            XRControlStyle evenStyle = new XRControlStyle();
           
            oddStyle.BackColor = Color.FromArgb(224,255,255);
            oddStyle.StyleUsing.UseBackColor = true;
            oddStyle.StyleUsing.UseBorders = false;
            oddStyle.Name = "OddStyle";

            evenStyle.BackColor = Color.White;
            evenStyle.StyleUsing.UseBackColor = true;
            evenStyle.StyleUsing.UseBorders = false;
            evenStyle.Name = "EvenStyle";

            rep.StyleSheet.AddRange(new DevExpress.XtraReports.UI.XRControlStyle[] 
                { oddStyle, evenStyle });

        }

        public void InitDetailsBasedonXRTable(XtraReport rpt)
        {
            DataSet ds = ((DataSet)rpt.DataSource);

            int colCount = m_dsFieldXml.Tables[0].Columns.Count;
            int colWidth = (rpt.PageWidth - (rpt.Margins.Left + rpt.Margins.Right)) / colCount;

            int nPageWidth = (rpt.PageHeight - (rpt.Margins.Left + rpt.Margins.Right));
            int nNeedTableWidth = 0;
            // Create a table to represent headers
            XRTable tableHeader = new XRTable();
            tableHeader.Height = 20;
            //if (rpt.Landscape)
            //{
            //    tableHeader.Width = (rpt.PageHeight - (rpt.Margins.Top + rpt.Margins.Bottom));
            //}
            //else 
            //{
                tableHeader.Width = (rpt.PageWidth - (rpt.Margins.Left + rpt.Margins.Right));
            //}
            
            XRTableRow headerRow = new XRTableRow();
            headerRow.Width = tableHeader.Width;


            //headerRow.BackColor = Color.FromArgb(223, 237, 255);
            headerRow.BackColor = Color.LightGray;
            headerRow.ForeColor = Color.Black;

            // Create a table to display data
            XRTable tableDetail = new XRTable();
            tableDetail.Height = 20;
            tableDetail.Width = (rpt.PageWidth - (rpt.Margins.Left + rpt.Margins.Right));
            tableDetail.Font = new System.Drawing.Font("宋体", 10.0F,
                    System.Drawing.FontStyle.Regular,
                    System.Drawing.GraphicsUnit.Point, ((byte)(0)));

            XRTableRow detailRow = new XRTableRow();
            detailRow.Width = tableDetail.Width;
           
            //奇偶行样式
            //tableDetail.EvenStyleName = "EvenStyle";
            //tableDetail.OddStyleName = "OddStyle";

            XRTable tableFoot = new XRTable();
            if (null != m_dsSumXml)
            {
                tableFoot.Height = 20;
                tableFoot.Width = tableDetail.Width;
                tableFoot.BackColor = Color.DarkGray;
                tableFoot.ForeColor = Color.Black;
            }

            XRTableRow footRow = new XRTableRow();
            if (null != m_dsSumXml)
            {
                footRow.Width = tableFoot.Width - 50;
                footRow.Height = 30;
            }
           
            TextAlignment textAlign = DevExpress.XtraPrinting.TextAlignment.MiddleCenter;

            // Create table cells, fill the header cells with text, bind the cells to data
            for (int i = 0; i < colCount; i++)
            {
                XRTableCell headerCell = new XRTableCell();
                
                headerCell.Text = m_dsFieldXml.Tables[0].Rows[0][i].ToString();
                
                string strWidth = m_dsFieldXml.Tables[0].Rows[1][i].ToString();
                int nWidth;
                Int32.TryParse(strWidth, out nWidth);
                if (nWidth <= 0)
                {
                    nWidth = colWidth;
                    //headerCell.Width = nWidth;
                }

                headerCell.Width = nWidth/*+i*10*/;
                nNeedTableWidth += nWidth;
                //DataRow drTmp = (DataRow)m_dsFieldXml.Tables[0].Rows[0];
                //drTmp[0][1];

                XRTableCell detailCell = new XRTableCell();
                detailCell.Width = nWidth;
                detailCell.DataBindings.Add("Text", null, m_dsFieldXml.Tables[0].Columns[i].Caption);
                if (i == 0)
                {
                    headerCell.Borders = DevExpress.XtraPrinting.BorderSide.Left 
                        |DevExpress.XtraPrinting.BorderSide.Top 
                        |DevExpress.XtraPrinting.BorderSide.Bottom;
                    detailCell.Borders = DevExpress.XtraPrinting.BorderSide.Left
                        |DevExpress.XtraPrinting.BorderSide.Bottom; 
                }
                else
                {
                    headerCell.Borders = DevExpress.XtraPrinting.BorderSide.All;
                    detailCell.Borders = DevExpress.XtraPrinting.BorderSide.Left
                        | DevExpress.XtraPrinting.BorderSide.Right
                        | DevExpress.XtraPrinting.BorderSide.Bottom;
                }
                headerCell.TextAlignment = textAlign;
                detailCell.TextAlignment = textAlign;

                headerCell.CanGrow = false;
                detailCell.CanGrow = false;
                // Place the cells into the corresponding tables
                headerRow.Cells.Add(headerCell);
                detailRow.Cells.Add(detailCell);

                if (null != m_dsSumXml)
                {
                    bool bSumCell = true;
                    string strId = m_dsFieldXml.Tables[0].Columns[i].Caption;
                    if (!m_dsSumXml.Tables[0].Columns.Contains(strId))
                    {
                        bSumCell = false;
                    }
                    XRTableCell footCell = new XRTableCell();
                    footCell.Width = nWidth;
                    if (0 == i)
                    {
                        footCell.Borders = DevExpress.XtraPrinting.BorderSide.Left
                            |DevExpress.XtraPrinting.BorderSide.Bottom;
                    }
                    else
                    {
                        if (bSumCell)
                        {
                            footCell.Borders = DevExpress.XtraPrinting.BorderSide.Left
                                |DevExpress.XtraPrinting.BorderSide.Bottom
                                |DevExpress.XtraPrinting.BorderSide.Right;
                        }
                        else
                        {
                            footCell.Borders = DevExpress.XtraPrinting.BorderSide.Bottom;
                            if (i == colCount - 1)
                            {
                                footCell.Borders |= DevExpress.XtraPrinting.BorderSide.Right;
                            }
                        }
                    }
                    footCell.CanGrow = false;
                    //footCell.Location = new System.Drawing.Point()
                    footCell.TextAlignment = textAlign;
                    footCell.DataBindings.Add("Text", m_dsSumXml, m_dsFieldXml.Tables[0].Columns[i].Caption);

                    //footCell.CanShrink = false; 
                    footRow.Cells.Add(footCell);
                }
                
            }

            //XRTableCell footCell1 = new XRTableCell();
            //footCell1.Width = 50;
            //footRow.Cells.Add(footCell1);
            
            tableHeader.Rows.Add(headerRow);
            tableDetail.Rows.Add(detailRow);


            // Place the labTitle onto a report's header band
            if(m_bShowReportHeader)
            {
                XRLabel labTitle = new XRLabel();
                labTitle.Text = m_strTitle;
                labTitle.TextAlignment = DevExpress.XtraPrinting.TextAlignment.MiddleCenter;
                labTitle.Font = new System.Drawing.Font("宋体", 13.5F,
                    System.Drawing.FontStyle.Bold,
                    System.Drawing.GraphicsUnit.Point, ((byte)(0)));
                labTitle.Height = 30;
                labTitle.Width = tableHeader.Width;
                labTitle.Location = new System.Drawing.Point(0, 20);
                rpt.Bands[BandKind.TopMargin].Controls.Add(labTitle);
            }
            //tableHeader.Width = nNeedTableWidth;
            //tableDetail.Width = nNeedTableWidth;
            tableHeader.Location = new System.Drawing.Point(0, 0);            
            rpt.Bands[BandKind.PageHeader].Controls.Add(tableHeader);
            rpt.Bands[BandKind.Detail].Controls.Add(tableDetail);

            if (null != m_dsSumXml)
            {
                //tableFoot.Width = nNeedTableWidth;
                tableFoot.Rows.Add(footRow);
                tableFoot.Location = new System.Drawing.Point(0, 0);
                rpt.Bands[BandKind.ReportFooter].Controls.Add(tableFoot);
            }
            
            if(m_bShowPageFoot)
            {
                //创建页脚 左边页码 右边时间 参考智佳
                XRPageInfo yeMaInfo = new XRPageInfo();
                yeMaInfo.PageInfo = PageInfo.NumberOfTotal;
                yeMaInfo.Width = 100;

                XRPageInfo dateInfo = new XRPageInfo();
                dateInfo.PageInfo = PageInfo.DateTime;
                dateInfo.Width = 100;
                dateInfo.LocationFloat = new DevExpress.Utils.PointFloat(rpt.PageWidth - rpt.Margins.Right - rpt.Margins.Left - dateInfo.Width - 0.10001F, 0.00001F);
                dateInfo.TextAlignment = DevExpress.XtraPrinting.TextAlignment.MiddleRight;

                rpt.Bands[BandKind.BottomMargin].Controls.Add(yeMaInfo);
                rpt.Bands[BandKind.BottomMargin].Controls.Add(dateInfo);
            } 
        }
    }
}
