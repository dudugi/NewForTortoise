using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.SqlClient;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using DevExpress.XtraReports;
using DevExpress.XtraReports.UI;
using DevExpress.XtraReports.UserDesigner;
using System.Drawing.Design;
using System.ComponentModel.Design;
using DevExpress.XtraPrinting;
using DevExpress.XtraPrinting.Localization;
using System.Runtime.InteropServices;
using System.IO;
using System.Xml;

/*
using DevExpress.XtraPrinting.Control;
using DevExpress.XtraPrinting.Preview;
using DevExpress.XtraEditors;
*/

using DXMyCreateReport;

using System.Diagnostics; //打开线程包含 yangjr 2016-6-28
using System.Printing;


namespace KDS_CSharpReport
{
    //[ComVisible(true)]
    [Guid("0B5C6F1C-53ED-4615-B925-FE43D6857D61")]
    public interface IXtraReport
    {
        [DispId(1)]
        void LocalizerReport();
        [DispId(2)]
        void ShowPreviewDialog(string fileName);
        [DispId(3)]
        void Print(string fileName);
        [DispId(4)]
        void OpenDesigner();

        //新的可以用的接口  by WangZY 2017/06/25
        [DispId(5)]
        //通过模板与xml字串数据显示打印预览     by WangZY 2017/07/07
        void ShowPrintPreviewByXmlText(string strRepxFile, string strXmlText);

        [DispId(6)]
        //通过模板与xml文件显示打印预览     by WangZY 2017/07/07
        void ShowPrintPreviewByXml(string strRepxFile, string strXmlFile);

        [DispId(7)]
        //通过模板显示报表设计    by WangZY 2017/07/07
        void ShowPrintDesigner(string strRepxFile);

        [DispId(8)]
        //通过模板与sql语句显示打印预览     by WangZY 2017/07/07
        void ShowPrintPreviewBySQL(string strRepxFile,string strSqlConnection, string strSql);

        [DispId(9)]
        //动态创建模板显示打印预览的接口     by WangZY 2017/07/07
        void ShowNewPrintPreviewByXmlText(string strTitle, string strFieldXmlText,
                string strDataXmlText, string strSumXmlText);

        [DispId(10)]
        //动态创建模板导出xls的接口     by WangZY 2017/07/07
        bool ExportXlsByXmlText(string strTitle, string strFieldXmlText,
           string strDataXmlText, string strSumXmlText, string saveXlsName);

        [DispId(11)]
        void StartProcessOpenXls(string xlsFileName);

        [DispId(12)]
        //通过动态创建报表并加载数据导出文本文件 yangjr 2017-6-28
        bool ExportTxtFileByXmlText(string strTitle, string strFieldXmlText,
            string strDataXmlText, string strSumXmlText,string saveXlsName);

        [DispId(13)]
        //通过动态创建报表并加载数据导出jpg文件 yangjr 2017-7-3
        bool ExportJpgFileByXmlText(string strTitle, string strFieldXmlText,
            string strDataXmlText, string strSumXmlText, string saveFileName);

        [DispId(14)]
        //多份数的打印预览  by WangZY 2017/07/05
        void ShowPrintPreviewMultiCopiesByXmlText(string strRepxFile, 
            string strXmlText, int nCount);

        [DispId(15)]
        //通过模板与xml字串数据直接打印  by WangZY 2017/07/07
        void DoPrintByXmlText(string strRepxFile, string strXmlText);

        [DispId(16)]
        //动态创建模板直接打印的接口     by WangZY 2017/07/07
        void NewPrintByXmlText(string strTitle, string strFieldXmlText,
                string strDataXmlText, string strSumXmlText);
    
        [DispId(17)]
        //通过模板与xml字串数据显示模板报表设计  by WangZY 2017/07/11
        void ShowDesignerByRepxAndXmlText(string strRepxFile, 
            string strXmlText, string strXmlContentDic);
        
        [DispId(18)]
        //通过xml字串数据显示动态报表设计  by WangZY 2017/07/11
        void ShowDesignerByXmlText(string strTitle, string strFieldXmlText,
                string strDataXmlText, string strSumXmlText);

        [DispId(19)]
        void ShowMultPrintReportPreview(string strRepx,
            string StrXmlTexts, int nCount);

        //内部功能研究测试专用接口  by WangZY 2017/08/10
        [DispId(20)]
        void TestReportPreview(string strTitle, string strFieldXmlText,
                string strDataXmlText, string strSumXmlText);

        [DispId(21)]
        //通过模板与sql语句显示打印报表设计界面     by WangZY 2017/09/01
        void ShowPrintDesignerBySQL(string strRepxFile, string strSqlConnection,
            string strSql, string strXmlContentDic);

        [DispId(22)]
        //动态创建模板显示打印预览(纸张横向)的接口     by WangZY 2017/07/07
        void ShowNewLandscapePrintPreviewByXmlText(string strTitle, string strFieldXmlText,
                string strDataXmlText, string strSumXmlText);

        [DispId(23)]
        //动态创建模板直接打印(纸张横向)的接口     by WangZY 2017/07/07
        void NewLandscapePrintByXmlText(string strTitle, string strFieldXmlText,
                string strDataXmlText, string strSumXmlText);

        [DispId(24)]
        //通过模板与xml字串数据显示打印模板设计器  by WangZY 2017/11/30
        string ShowDesignerPreviewByRepxAndXmlText(string strRepxFile, string strXmlText,
            string strPrintName, bool bPreview, ref int nLandscape, ref bool bHasPrint);

        [DispId(25)]
        //通过模板与xml字串数据直接打印  by WangZY 2017/11/30
        string DoPrintByRepxAndXmlText(string strRepxFile, string strXmlText,
            string strPrintName, bool bPreview, ref int nLandscape, ref bool bHasPrint);
        
    }

    
    //[ComVisible(true)]
    [Guid("18F80909-A675-48B9-930A-A6C2A90E0AC7")]
    [ClassInterface(ClassInterfaceType.None)]
    public class MyXtraReport : IXtraReport
    {
        const string cs_replase_new = "";
        public void LocalizerReport()
        {
            //DevExpress.XtraPrinting.Localization.PreviewLocalizer.Active = new MyPreviewLocalizer();
            //DevExpress.XtraReports.Localization.ReportLocalizer.Active = new XtraReports_CN();
           
        }

        public string DoPrintByRepxAndXmlText(string strRepxFile, string strXmlText,
            string strPrintName, bool bPreview, ref int nLandscape, ref bool bHasPrint)
        {
            string strNewPrinterName = "";
            
            string strDebug;
            int nTime = System.Environment.TickCount;
            Debug.WriteLine("C#:DoPrintByRepxAndXmlText::begin = {0}\n", nTime);
            //时间消耗大头，暂时不用	by WangZY 2018/12/05
            //strXmlText = ReplaceNoteString(strXmlText);

            XtraReport rp = new XtraReport();
            try
            {
                rp.LoadLayout(strRepxFile);
            }
            catch
            {
                MessageBox.Show("打印模板文件加载异常!");

                return strNewPrinterName;
            }


            rp.DataSource = GetDataFromString(strXmlText);
            if (null == rp.DataSource)
            {
                MessageBox.Show("打印数据异常!");

                return strNewPrinterName;
            }

            rp.DataMember = "Parent";
            try
            {
                if (strPrintName != "")
                {
                    rp.PrinterName = strPrintName;
                }
                if (1 == nLandscape)
                {
                    rp.Landscape = true;
                }
                else if (2==nLandscape)
                {
                    rp.Landscape = false;
                }

                if (bPreview)
                {
                    m_bHasPrint = false;
                    rp.PrintProgress += new DevExpress.XtraPrinting.PrintProgressEventHandler(this.PrintingProgress);
                    rp.ShowPreviewDialog();

                    bHasPrint = m_bHasPrint;
                }
                else 
                {
                    rp.Print();
                    bHasPrint = true;
                }
                
                if (rp.Landscape)
                {
                    nLandscape = 1;
                }
                else
                {
                    nLandscape = 2;
                }
                //Thread.Sleep()
                //rp.pri
                //rp.Dispose();
                strNewPrinterName = rp.PrinterName;
            }
            catch
            {
            }
            int nTime2 = System.Environment.TickCount;
            int nTimeU = nTime2 - nTime;
            Debug.WriteLine("C#:DoPrintByRepxAndXmlText::End = {0}, Cost={1}\n", nTime2, nTimeU);

            return strNewPrinterName;
        }

        public string ShowDesignerPreviewByRepxAndXmlText(string strRepxFile,
            string strXmlText, string strPrintName, bool bPreview, ref int nLandscape, ref bool bHasPrint)
        {
            string strName = "";

            //时间消耗大头，暂时不用	by WangZY 2018/12/05
            //strXmlText = ReplaceNoteString(strXmlText);
            //strXmlContentDic = ReplaceNoteString(strXmlContentDic);

            XtraReport rp = new XtraReport();
            try
            {
                rp.LoadLayout(strRepxFile);
            }
            catch
            {
                MessageBox.Show("打印模板文件加载异常!");

                return strName;
            }


            DataSet dsSrc = GetDataFromString(strXmlText);
            if (null == dsSrc)
            {
                MessageBox.Show("打印数据异常!");

                return strName;
            }

#region 解析中文备注字典
            //解析中文备注字典  by WangZY 2017/09/04
            //DataSet dsDic = null;
            //if (strXmlContentDic != "")
            //{
            //    //支持多张表 yangjr 2017-9-20
            //    int srcRow = dsSrc.Tables.Count;
            //    dsDic = GetDataFromString(strXmlContentDic);
            //    if (null != dsDic)
            //    {
            //        int dicRow = dsDic.Tables.Count;
            //        for (int iRow = 0; iRow < dicRow && iRow < srcRow; ++iRow)
            //        {
            //            int nCount = dsSrc.Tables[iRow].Columns.Count;
            //            for (int i = 0; i < nCount; i++)
            //            {
            //                string strName = dsSrc.Tables[iRow].Columns[i].ColumnName;
            //                if (dsDic.Tables[iRow].Columns.Contains(strName))
            //                {
            //                    string strCaption = dsDic.Tables[iRow].Rows[0][strName].ToString();

            //                    dsSrc.Tables[iRow].Columns[i].Caption = strCaption;
            //                }
            //            }
            //        }
            //    }
            //}
#endregion
            


            rp.DataSource = dsSrc;
            rp.DataMember = "Parent";

            //rp.ShowDesignerDialog();


            XRDesignFormEx designForm = new XRDesignFormEx();
            //隐藏按钮
            designForm.DesignPanel.SetCommandVisibility(new ReportCommand[]{                
                ReportCommand.NewReport,                
                ReportCommand.NewReportWizard,
                ReportCommand.OpenFile,
                ReportCommand.SaveAll,
                ReportCommand.SaveFileAs,
                ReportCommand.SaveFile,
                ReportCommand.Close,
             
            }, DevExpress.XtraReports.UserDesigner.CommandVisibility.None);

            //更改状态
            designForm.ReportStateChanged += new ReportStateEventHandler(designForm_ReportStateChanged);
            //designForm.FormClosing += new FormClosingEventHandler(designForm_FormClosing);
            

#region 实现设计界面指定打印机的方式
            //直接设置打印机名称的样例代码	by WangZY 2018/11/29
            if (strPrintName != "")
            {
                rp.PrinterName = strPrintName;
            }  
#endregion
 
            
#region 横向打印
            //为0时，为按模板的方向打印，不做改变    by WangZY 2019/01/29
            if (1 == nLandscape)    //横向打印
            {
                rp.Landscape = true;
            }
            else if (2 == nLandscape)   //纵向打印
            {
                rp.Landscape = false;
            }
#endregion
            m_bHasPrint = false;
            //rp.AfterPrint += new EventHandler(this.BeginPrinting);
            rp.PrintProgress += new DevExpress.XtraPrinting.PrintProgressEventHandler(this.PrintingProgress);
            // 加载报表模板. 
            designForm.OpenReport(rp);

#region 实现设计界面默认预览的方式
            //方式一（代码样例1）：以绑定事件的方式处理，实现进到设计界面，默认显示预览页    by WangZY 2018/11/29
            //designForm.Shown += new EventHandler(designForm_Show);

            //方式二（代码样例2）：以直接设置标签值的方式处理，实现进到设计界面，默认显示预览页    by WangZY 2018/11/29
            if (bPreview)
            {
                designForm.DesignPanel.SelectedTabIndex = 1;
            }

            //方式三（代码样例3）：以直接执行命令的方式处理，实现进到设计界面，默认显示预览页    by WangZY 2018/11/29
            //designForm.DesignPanel.ExecCommand(ReportCommand.ShowPreviewTab);
#endregion


            designForm.ShowDialog();
            //designForm.
            designForm.Dispose();
            rp.SaveLayout(strRepxFile);
            strName = rp.PrinterName;
            bHasPrint = m_bHasPrint;
            
            if (rp.Landscape)
            {
                nLandscape = 1;
            }
            else
            {
                nLandscape = 2;
            }
            

            return strName;
        }

        private bool m_bHasPrint = false;
        private void PrintingProgress(object sender, EventArgs e)   
        {//针对开始打印事件进行相应的处理   
            m_bHasPrint = true;
        }


        public void ShowPreviewDialog(string fileName)
        {
            XtraReport rp = new XtraReport();
   
            try
            {
                rp.LoadLayout(fileName);
            }
            catch
            {
                MessageBox.Show("打印模板文件加载异常!");

                return;
            }
            ReportDesignTool design = new ReportDesignTool(rp);
            
            //rp.ShowDesignerDialog();
            //MessageBox.Show("test");
           // design.ShowDesignerDialog();
           // rp.DataSource. = 
            //rp.DataSource = Get
            ReportPrintTool printTool = new ReportPrintTool(rp);
            printTool.ShowPreviewDialog();
        }

        public void Print(string fileName)
        {
            XtraReport rp = new XtraReport();
            
            try
            {
                rp.LoadLayout(fileName);
            }
            catch
            {
                MessageBox.Show("打印模板文件加载异常!");

                return;
            }
           // rp.DataSource
            ReportPrintTool printTool = new ReportPrintTool(rp);

            // Invoke the Print dialog.
            if (true == printTool.PrintDialog())
            {
                // Send the report to the default printer.
               // printTool.
                printTool.Print();
            }
        }

        public void OpenDesigner()
        {
            XtraReport r = new XtraReport();
            //r.LoadLayout(@"C:\1.repx");
            XRDesignFormEx designForm = new XRDesignFormEx();

            //r.ShowDesigner();
            //隐藏按钮
            //designForm.DesignPanel.SetCommandVisibility(new ReportCommand[]{
            //    ReportCommand.NewReport,
            //    ReportCommand.SaveFileAs,
            //    ReportCommand.NewReportWizard,
            //    ReportCommand.OpenFile
            //}, CommandVisibility.None);


            ////更改状态
            //designForm.ReportStateChanged += new ReportStateEventHandler(designForm_ReportStateChanged);

            //designForm.FormClosing += new FormClosingEventHandler(designForm_FormClosing);

            //// 加载报表. 
            //designForm.OpenReport(r);

            // 打开设计器
            designForm.ShowDialog();
            designForm.Dispose();
        }

        public void ShowPrintPreviewByXmlText(string strRepxFile, string strXmlText)
        {
            XtraReport rp = new XtraReport();
           
            try
            {
                rp.LoadLayout(strRepxFile);
            }
            catch
            {
                MessageBox.Show("打印模板文件加载异常!");

                return;
            }
            //时间消耗大头，暂时不用	by WangZY 2018/12/05
            //strXmlText = ReplaceNoteString(strXmlText);            
            
            rp.DataSource = GetDataFromString(strXmlText);
            if (null == rp.DataSource)
            {
                MessageBox.Show("打印数据异常!");

                return;
            }
            rp.DataMember = "NewDataSet";
            //ReportPrintTool printTool = new ReportPrintTool(rp);
           // printTool.ShowPreviewDialog();
            //rp.PrintingSystem.ContinuousPageNumbering = true;
            //rp.ShowRibbonPreviewDialog();
            rp.ShowPreviewDialog();
        }

        public void ShowPrintPreviewMultiCopiesByXmlText(string strRepxFile, 
            string strXmlText, int nCount)
        {
            XtraReport rp = new XtraReport();

            try
            {
                rp.LoadLayout(strRepxFile);
            }
            catch
            {
                MessageBox.Show("打印模板文件加载异常!");

                return;
            }
            
            rp.DataSource = GetDataFromString(strXmlText);
            if (null == rp.DataSource)
            {
                MessageBox.Show("打印数据异常!");

                return;
            }
            rp.DataMember = "Parent";
            ReportPrintTool printTool = new ReportPrintTool(rp);
            if (nCount <= 0)
            {
                nCount = 1;
            }
            printTool.PrinterSettings.Copies = (short)nCount;  
            printTool.ShowPreviewDialog();
        }

        public void ShowPrintPreviewByXml(string strRepxFile, string strXmlFile)
        {
            XtraReport rp = new XtraReport();

            try
            {
                rp.LoadLayout(strRepxFile);
            }
            catch
            {
                MessageBox.Show("打印模板文件加载异常!");

                return;
            }


            DataSet dsXml = new DataSet();
            dsXml.ReadXml(strXmlFile);
            rp.DataSource = dsXml;

            rp.DataMember = "Parent";

            ReportPrintTool printTool = new ReportPrintTool(rp);
            printTool.ShowPreviewDialog();

            return;
        }

        /*
        public void ShowPrintDesigner(string strRepxFile)
        {
            XtraReport r = new XtraReport();

            r.LoadLayout(strRepxFile);
            r.ShowDesignerDialog();
            r.SaveLayout(strRepxFile);
            //r.ShowDesigner();  
        }
        */
        public void ShowPrintDesigner(string strRepxFile)
        {
            XtraReport r = new XtraReport();
            try
            {
                r.LoadLayout(strRepxFile);
            }
            catch
            {
                MessageBox.Show("打印模板文件加载异常!");

                return;
            } 
            XRDesignFormEx designForm = new XRDesignFormEx();
            //隐藏按钮
            designForm.DesignPanel.SetCommandVisibility(new ReportCommand[]{                
                ReportCommand.NewReport,                
                ReportCommand.NewReportWizard,
                ReportCommand.OpenFile,
                ReportCommand.SaveAll,
                ReportCommand.SaveFileAs,
                ReportCommand.SaveFile,
                ReportCommand.Close,
             
            }, DevExpress.XtraReports.UserDesigner.CommandVisibility.None);

            //更改状态
            designForm.ReportStateChanged += new ReportStateEventHandler(designForm_ReportStateChanged);
            designForm.Shown += new EventHandler(designForm_Show); 
            //designForm.FormClosing += new FormClosingEventHandler(designForm_FormClosing);
          

            //designForm.ShowMdiChildCaptionInParentTitle = true;

   
            

            designForm.OpenReport(r);
            //designForm.SetWindowVisibility(DevExpress.XtraReports.UserDesigner.DesignDockPanelType.ReportExplorer,true);
            //designForm.DesignPanel.ExecCommand(ReportCommand.ShowPreviewTab);
            
            
            designForm.ShowDialog();
            designForm.Dispose();
            r.SaveLayout(strRepxFile);
        }

        private void designForm_ReportStateChanged(object sender,
            ReportStateEventArgs e)
        {
            if (e.ReportState == ReportState.Changed)
            {
                ((XRDesignFormEx)sender).DesignPanel.ReportState 
                    = ReportState.Saved;
            }
        }

        private void designForm_Show(object sender, EventArgs e) 
        {
            //MessageBox.Show("测试测试");
            ((XRDesignFormEx)sender).DesignPanel.ExecCommand(ReportCommand.ShowPreviewTab);
                    //= ReportState.Saved;
        }

        public static DataSet GetDataFromString(string strXmlText)
        {
            string strXmlData = strXmlText;
            StringReader stream = null;
            XmlTextReader reader = null;

            try
            {
                DataSet xmlDS = new DataSet();
                stream = new StringReader(strXmlData);
                reader = new XmlTextReader(stream);
                xmlDS.ReadXml(reader);
                return xmlDS;
            }
            catch (Exception ex)
            {
                string strTest = ex.Message;
                return null;
            }
            finally
            {
                if (reader != null)
                {
                    reader.Close();
                }
            }      
        }
        public void ShowPrintDesignerBySQL(string strRepxFile, string strSqlConnection,
            string strSql, string strXmlContentDic)
        {
            XtraReport rp = new XtraReport();

            try
            {
                rp.LoadLayout(strRepxFile);
            }
            catch
            {
                MessageBox.Show("打印模板文件加载异常!");

                return;
            } 

            //从数据库读，并生成文件
            //string connection = @"Server=139.196.243.169,1433;Database=QLERP;UID=QLERP123QL;PWD=QLERP123456QL";
            SqlConnection con = new SqlConnection(strSqlConnection);
            con.Open();
            DataSet ds = new DataSet();
            //SqlDataAdapter sda = new SqlDataAdapter("select * from dbo.OtherRecords", con);
            SqlDataAdapter sda = new SqlDataAdapter(strSql, con);
            sda.Fill(ds, "dt0");
            con.Close();

            DataSet dsDic = null;
            if (strXmlContentDic != "")
            {
                dsDic = GetDataFromString(strXmlContentDic);
                if (null != dsDic)
                {
                    int nCount = ds.Tables[0].Columns.Count;
                    for (int i = 0; i < nCount; i++)
                    {
                        string strName = ds.Tables[0].Columns[i].ColumnName;
                        if (dsDic.Tables[0].Columns.Contains(strName))
                        {
                            string strCaption = dsDic.Tables[0].Rows[0][strName].ToString();

                            ds.Tables[0].Columns[i].Caption = strCaption;
                        }
                    }
                }
            }
            //ds.Tables[0].Columns["cCode"].Caption = "单号";

            rp.DataSource = ds;
            
            rp.DataMember = "Parent";
            rp.ShowDesignerDialog();
        }

        public void ShowPrintPreviewBySQL(string strRepxFile, string strSqlConnection,
            string strSql)
        {
            XtraReport rp = new XtraReport();

            try
            {
                rp.LoadLayout(strRepxFile);
            }
            catch
            {
                MessageBox.Show("打印模板文件加载异常!");

                return;
            } 
            

            //从数据库读，并生成文件
            //string connection = @"Server=139.196.243.169,1433;Database=QLERP;UID=QLERP123QL;PWD=QLERP123456QL";
            SqlConnection con = new SqlConnection(strSqlConnection);
            con.Open();
            DataSet ds = new DataSet();
            //SqlDataAdapter sda = new SqlDataAdapter("select * from dbo.OtherRecords", con);
            SqlDataAdapter sda = new SqlDataAdapter(strSql, con);
            sda.Fill(ds, "dt0");
            con.Close();

            rp.DataSource = ds;
            rp.DataMember = "Parent";
            rp.ShowPreviewDialog();
        }

        public void ShowNewPrintPreviewByXmlText(string strTitle, string strFieldXmlText,
            string strDataXmlText, string strSumXmlText)
        {
            CreateReportByDataSet crp = new CreateReportByDataSet();

            //时间消耗大头，暂时不用	by WangZY 2018/12/05
            //strFieldXmlText = ReplaceNoteString(strFieldXmlText);
            //strDataXmlText = ReplaceNoteString(strDataXmlText);
            //strSumXmlText = ReplaceNoteString(strSumXmlText);

            DataSet dsField = null;
            if (strFieldXmlText != "")
            {
                dsField = GetDataFromString(strFieldXmlText);//设置报表数据源 
            }
            else
            {
                return;
            }
            DataSet dsData = GetDataFromString(strDataXmlText);//设置报表数据源 

            DataSet dsSum = null;
            if (strSumXmlText != "")
            {
                dsSum = GetDataFromString(strSumXmlText);//设置报表数据源 
            }
            //crp.ShowReportPreviewByDataSet(strTitle,dsField, dsData, dsSum);
            XtraReport rpt = crp.NewReportByDataSet(strTitle, dsField, dsData, dsSum);

            rpt.ShowPreviewDialog();

            //rpt.ShowDesignerDialog();

        }

        //动态创建模板显示打印预览(纸张横向)的接口     by WangZY 2017/09/14
        public void ShowNewLandscapePrintPreviewByXmlText(string strTitle, string strFieldXmlText,
                string strDataXmlText, string strSumXmlText)
        {
            //时间消耗大头，暂时不用	by WangZY 2018/12/05
            //strFieldXmlText = ReplaceNoteString(strFieldXmlText);
            //strDataXmlText = ReplaceNoteString(strDataXmlText);
            //strSumXmlText = ReplaceNoteString(strSumXmlText);

            CreateReportByDataSet crp = new CreateReportByDataSet();

            DataSet dsField = null;
            if (strFieldXmlText != "")
            {
                dsField = GetDataFromString(strFieldXmlText);//设置报表数据源 
            }
            else
            {
                return;
            }
            DataSet dsData = GetDataFromString(strDataXmlText);//设置报表数据源 

            DataSet dsSum = null;
            if (strSumXmlText != "")
            {
                dsSum = GetDataFromString(strSumXmlText);//设置报表数据源 
            }

            //crp.ShowReportPreviewByDataSet(strTitle,dsField, dsData, dsSum);
            XtraReport rpt = crp.NewReportByDataSet(strTitle, dsField, dsData, dsSum, true);
            try
            {
                rpt.ShowPreviewDialog();
            }
            catch
            {

            }        
        }

   
        //动态创建模板直接打印(纸张横向)的接口     by WangZY 2017/09/14
        public void NewLandscapePrintByXmlText(string strTitle, string strFieldXmlText,
                string strDataXmlText, string strSumXmlText)
        {
            //时间消耗大头，暂时不用	by WangZY 2018/12/05
            //strFieldXmlText = ReplaceNoteString(strFieldXmlText);
            //strDataXmlText = ReplaceNoteString(strDataXmlText);
            //strSumXmlText = ReplaceNoteString(strSumXmlText);


            CreateReportByDataSet crp = new CreateReportByDataSet();

            DataSet dsField = null;
            if (strFieldXmlText != "")
            {
                dsField = GetDataFromString(strFieldXmlText);//设置报表数据源 
            }
            else
            {
                return;
            }
            DataSet dsData = GetDataFromString(strDataXmlText);//设置报表数据源 

            DataSet dsSum = null;
            if (strSumXmlText != "")
            {
                dsSum = GetDataFromString(strSumXmlText);//设置报表数据源 
            }
            XtraReport rpt = crp.NewReportByDataSet(strTitle, dsField, dsData, dsSum,true);
            try
            {
                rpt.Print();
            }
            catch
            {

            }
        }
        


        //通过动态创建报表并加载数据导出xls文件 yangjr 2017-6-28
        public bool ExportXlsByXmlText(string strTitle, string strFieldXmlText,
            string strDataXmlText, string strSumXmlText,string saveXlsName)
        {
            //时间消耗大头，暂时不用	by WangZY 2018/12/05
            //strFieldXmlText = ReplaceNoteString(strFieldXmlText);
            //strDataXmlText = ReplaceNoteString(strDataXmlText);
            //strSumXmlText = ReplaceNoteString(strSumXmlText);

            CreateReportByDataSet crp = new CreateReportByDataSet();
            //MessageBox.Show("测试");
            DataSet dsField = null;
            if (strFieldXmlText != "")
            {
                dsField = GetDataFromString(strFieldXmlText);//设置报表数据源 
            }
            DataSet dsData = GetDataFromString(strDataXmlText);//设置报表数据源 

            DataSet dsSum = null;
            if (strSumXmlText != "")
            {
                dsSum = GetDataFromString(strSumXmlText);//设置报表数据源 
            }
            return crp.ExportXlsByDataSet(strTitle, dsField, dsData, dsSum, saveXlsName);
        }

        public void StartProcessOpenXls(string xlsFileName)
        {
            Process process = new Process();
            try
            {
                process.StartInfo.FileName = xlsFileName;
                process.Start();
                process.WaitForInputIdle();
            }
            catch { }
        }

        //通过动态创建报表并加载数据导出文本文件 yangjr 2017-7-3
        public bool ExportTxtFileByXmlText(string strTitle, string strFieldXmlText,
            string strDataXmlText, string strSumXmlText, string saveFileName)
        {
            //时间消耗大头，暂时不用	by WangZY 2018/12/05
            //strFieldXmlText = ReplaceNoteString(strFieldXmlText);
            //strDataXmlText = ReplaceNoteString(strDataXmlText);
            //strSumXmlText = ReplaceNoteString(strSumXmlText);


            CreateReportByDataSet crp = new CreateReportByDataSet();
            DataSet dsField = null;
            if (strFieldXmlText != "")
            {
                dsField = GetDataFromString(strFieldXmlText);//设置报表数据源 
            }
            DataSet dsData = GetDataFromString(strDataXmlText);//设置报表数据源 

            DataSet dsSum = null;
            if (strSumXmlText != "")
            {
                dsSum = GetDataFromString(strSumXmlText);//设置报表数据源 
            }
            return crp.ExportTxtFileByXmlText(strTitle, dsField, dsData, dsSum, saveFileName);
        }

        //通过动态创建报表并加载数据导出jpg文件 yangjr 2017-7-3
        public bool ExportJpgFileByXmlText(string strTitle, string strFieldXmlText,
            string strDataXmlText, string strSumXmlText, string saveFileName)
        {
            //时间消耗大头，暂时不用	by WangZY 2018/12/05
            //strFieldXmlText = ReplaceNoteString(strFieldXmlText);
            //strDataXmlText = ReplaceNoteString(strDataXmlText);
            //strSumXmlText = ReplaceNoteString(strSumXmlText);

            
            CreateReportByDataSet crp = new CreateReportByDataSet();
            DataSet dsField = null;
            if (strFieldXmlText != "")
            {
                dsField = GetDataFromString(strFieldXmlText);//设置报表数据源 
            }
            DataSet dsData = GetDataFromString(strDataXmlText);//设置报表数据源 

            DataSet dsSum = null;
            if (strSumXmlText != "")
            {
                dsSum = GetDataFromString(strSumXmlText);//设置报表数据源 
            }
            return crp.ExportJpgFileByXmlText(strTitle, dsField, dsData, dsSum, saveFileName);
        }

        //通过模板与xml字串数据直接打印  by WangZY 2017/07/07
        public void DoPrintByXmlText(string strRepxFile, string strXmlText)
        {
            //时间消耗大头，暂时不用	by WangZY 2018/12/05
            //strXmlText = ReplaceNoteString(strXmlText);

            XtraReport rp = new XtraReport();
            try
            {
               rp.LoadLayout(strRepxFile);
            }
            catch
            {
                MessageBox.Show("打印模板文件加载异常!");

                return;
            }
            
           
            rp.DataSource = GetDataFromString(strXmlText);
            if (null == rp.DataSource)
            {
                MessageBox.Show("打印数据异常!");

                return;
            }

            rp.DataMember = "Parent";
            try 
            {
                rp.Print();
                rp.Dispose();
            }
            catch
            {
            }
        }

        //动态创建模板直接打印的接口     by WangZY 2017/07/07
        public void NewPrintByXmlText(string strTitle, string strFieldXmlText,
                string strDataXmlText, string strSumXmlText)
        {
            //时间消耗大头，暂时不用	by WangZY 2018/12/05
            //strFieldXmlText = ReplaceNoteString(strFieldXmlText);
            //strDataXmlText = ReplaceNoteString(strDataXmlText);
            //strSumXmlText = ReplaceNoteString(strSumXmlText);

            CreateReportByDataSet crp = new CreateReportByDataSet();

            DataSet dsField = null;
            if (strFieldXmlText != "")
            {
                dsField = GetDataFromString(strFieldXmlText);//设置报表数据源 
            }
            else
            {
                return;
            }
            DataSet dsData = GetDataFromString(strDataXmlText);//设置报表数据源 

            DataSet dsSum = null;
            if (strSumXmlText != "")
            {
                dsSum = GetDataFromString(strSumXmlText);//设置报表数据源 
            }
            XtraReport rpt = crp.NewReportByDataSet(strTitle, dsField, dsData, dsSum);
            try 
            {
                rpt.Print();
            }
            catch
            {

            }
        }

        
        //通过模板与xml字串数据显示模板报表设计  by WangZY 2017/07/11
        public void ShowDesignerByRepxAndXmlText(string strRepxFile, 
            string strXmlText, string strXmlContentDic)
        {
            //时间消耗大头，暂时不用	by WangZY 2018/12/05
            //strXmlText = ReplaceNoteString(strXmlText);
            //strXmlContentDic = ReplaceNoteString(strXmlContentDic);

            XtraReport rp = new XtraReport();
            try
            {
                rp.LoadLayout(strRepxFile);
            }
            catch
            {
                MessageBox.Show("打印模板文件加载异常!");

                return;
            }
            

            DataSet dsSrc = GetDataFromString(strXmlText);
            if (null == dsSrc)
            {
                MessageBox.Show("打印数据异常!");

                return;
            }
            
            //解析中文备注字典  by WangZY 2017/09/04
            DataSet dsDic = null;
            if (strXmlContentDic != "")
            {
                //支持多张表 yangjr 2017-9-20
                int srcRow = dsSrc.Tables.Count;
                dsDic = GetDataFromString(strXmlContentDic);
                if (null != dsDic)
                {
                    int dicRow = dsDic.Tables.Count;
                    for(int iRow=0;iRow<dicRow && iRow<srcRow;++iRow)
                    {
                        int nCount = dsSrc.Tables[iRow].Columns.Count;
                        for (int i = 0; i < nCount; i++)
                        {
                            string strName = dsSrc.Tables[iRow].Columns[i].ColumnName;
                            if (dsDic.Tables[iRow].Columns.Contains(strName))
                            {
                                string strCaption = dsDic.Tables[iRow].Rows[0][strName].ToString();

                                dsSrc.Tables[iRow].Columns[i].Caption = strCaption;
                            }
                        }
                    }                    
                }
            }
            
          
            rp.DataSource = dsSrc;
            rp.DataMember = "Parent";

            //rp.ShowDesignerDialog();

           
            XRDesignFormEx designForm = new XRDesignFormEx();
            //隐藏按钮
            designForm.DesignPanel.SetCommandVisibility(new ReportCommand[]{                
                ReportCommand.NewReport,                
                ReportCommand.NewReportWizard,
                ReportCommand.OpenFile,
                ReportCommand.SaveAll,
                ReportCommand.SaveFileAs,
                ReportCommand.SaveFile,
                ReportCommand.Close,
             
            }, DevExpress.XtraReports.UserDesigner.CommandVisibility.None);

            //更改状态
            designForm.ReportStateChanged += new ReportStateEventHandler(designForm_ReportStateChanged);
            //designForm.FormClosing += new FormClosingEventHandler(designForm_FormClosing);

#region 实现设计界面指定打印机的方式

            //直接设置打印机名称的样例代码	by WangZY 2018/11/29
            //rp.PrinterName = "我是打印机";


#endregion

            // 加载报表模板. 
            designForm.OpenReport(rp);

#region 实现设计界面默认预览的方式
            //方式一（代码样例1）：以绑定事件的方式处理，实现进到设计界面，默认显示预览页    by WangZY 2018/11/29
            //designForm.Shown += new EventHandler(designForm_Show);

            //方式二（代码样例2）：以直接设置标签值的方式处理，实现进到设计界面，默认显示预览页    by WangZY 2018/11/29
            designForm.DesignPanel.SelectedTabIndex = 1;

            //方式三（代码样例3）：以直接执行命令的方式处理，实现进到设计界面，默认显示预览页    by WangZY 2018/11/29
            //designForm.DesignPanel.ExecCommand(ReportCommand.ShowPreviewTab);
#endregion


            




            designForm.ShowDialog();
            designForm.Dispose();
            rp.SaveLayout(strRepxFile);


        }

        
        //通过xml字串数据显示动态报表设计  by WangZY 2017/07/11
        public void ShowDesignerByXmlText(string strTitle, string strFieldXmlText,
                string strDataXmlText, string strSumXmlText)
        {
            //时间消耗大头，暂时不用	by WangZY 2018/12/05
            //strFieldXmlText = ReplaceNoteString(strFieldXmlText);
            //strDataXmlText = ReplaceNoteString(strDataXmlText);
            //strSumXmlText = ReplaceNoteString(strSumXmlText);

            CreateReportByDataSet crp = new CreateReportByDataSet();
    
            DataSet dsField = null;
            if (strFieldXmlText != "")
            {
                dsField = GetDataFromString(strFieldXmlText);//设置报表数据源 
            }
            else
            {
                return;
            }
            DataSet dsData = GetDataFromString(strDataXmlText);//设置报表数据源 

            DataSet dsSum = null;
            if (strSumXmlText != "")
            {
                dsSum = GetDataFromString(strSumXmlText);//设置报表数据源 
            }
            XtraReport rpt = crp.NewReportByDataSet(strTitle, dsField, dsData, dsSum);

            rpt.ShowDesignerDialog();
        }

        //单模板多报表打印接口    by WangZY 2017/07/14
        public void ShowMultPrintReportPreview(string strRepx,
            string StrXmlTexts, int nCount)
        {
            //时间消耗大头，暂时不用	by WangZY 2018/12/05
            //StrXmlTexts = ReplaceNoteString(StrXmlTexts); 

            //string strArray[] = StrXmlTexts;
            XtraReport rp = new XtraReport();

            try
            {
                rp.LoadLayout(strRepx);
            }
            catch
            {
                MessageBox.Show("打印模板文件加载异常!");

                return;
            } 
            rp.DataSource = GetDataFromString(StrXmlTexts);
            if (null == rp.DataSource)
            {
                MessageBox.Show("打印数据异常!");

                return;
            }
            rp.DataMember = "Parent";
            //

            rp.ShowPreviewDialog();

        }
        private string ReplaceNoteString(string oldString)
        {
            int nTime = System.Environment.TickCount;
            Debug.WriteLine("C#:ReplaceNoteString::begin = {0}\n", nTime);
            string newString = "";
            bool bFindLeft = false;
            foreach (char c in oldString)
            {
                if (c == '_' || c == '*')
                {
                    if (bFindLeft)
                    {
                        continue;
                    }else
                    {
                        newString += c.ToString();
                    }
                }
                else
                {
                    newString += c.ToString();
                    if (c == '<')
                    {
                        bFindLeft = true;
                    }
                    else if (c == '>')
                    {
                        bFindLeft = false;
                    }
                }
            }

            int nTime2 = System.Environment.TickCount;
            int nTimeU = nTime2 - nTime;
            Debug.WriteLine("C#:ReplaceNoteString::End = {0}, Cost={1}\n", nTime2, nTimeU);
            return newString;
        }

        public void TestReportPreview(string strTitle, string strFieldXmlText,
                string strDataXmlText, string strSumXmlText)
        {
            //时间消耗大头，暂时不用	by WangZY 2018/12/05
            //strFieldXmlText = ReplaceNoteString(strFieldXmlText);
            //strDataXmlText = ReplaceNoteString(strDataXmlText);
            //strSumXmlText = ReplaceNoteString(strSumXmlText);

            CreateReportByDataSet crp = new CreateReportByDataSet();

            DataSet dsField = null;
            if (strFieldXmlText != "")
            {
                dsField = GetDataFromString(strFieldXmlText);//设置报表数据源 
            }
            else
            {
                return;
            }
            DataSet dsData = GetDataFromString(strDataXmlText);//设置报表数据源 

            DataSet dsSum = null;
            if (strSumXmlText != "")
            {
                dsSum = GetDataFromString(strSumXmlText);//设置报表数据源 
            }
            XtraReport rpt = crp.NewReportByDataSet(strTitle, dsField, dsData, dsSum);

            ReportPrintTool pt = new ReportPrintTool(rpt);
            

            // Generate the report's document. This step is required
            // to activate its PrintingSystem and access it later.
            pt.Report.CreateDocument(false);

            // Override the ExportGraphic command.
            pt.PrintingSystem.AddCommandHandler(new ExportToImageCommandHandler());

            // Show the report's print preview.
            pt.ShowPreview();
/*


            //////////////////////////////////////////////////////////////////////
            //XtraReport fXtraReport = new XtraReport();
            //fXtraReport.LoadLayout(@"C:\1.repx");

            PrintingSystem printingSystem1 = new PrintingSystem();

            PrintControl printControl1 = new PrintControl();
            printControl1.PrintingSystem = printingSystem1;


            PrintBarManager printBarManager = new PrintBarManager();
            printBarManager.Form = printControl1;
            printBarManager.Initialize(printControl1);
            printBarManager.MainMenu.Visible = false;
            printBarManager.AllowCustomization = false;

            
            printingSystem1.SetCommandVisibility(new PrintingSystemCommand[]{
                PrintingSystemCommand.Open,
                PrintingSystemCommand.Save,
                PrintingSystemCommand.ClosePreview,
                PrintingSystemCommand.Customize,
                PrintingSystemCommand.SendCsv,
                PrintingSystemCommand.SendFile,
                PrintingSystemCommand.SendGraphic,
                PrintingSystemCommand.SendMht,
                PrintingSystemCommand.SendPdf,
                PrintingSystemCommand.SendRtf,
                PrintingSystemCommand.SendTxt,
                PrintingSystemCommand.SendXls
            }, CommandVisibility.None);

            

            rpt.PrintingSystem = printingSystem1;
            */
/*
            rpt.CreateDocument();

            Controls.Add(printControl1);
            printControl1.Dock = DockStyle.Fill;
*/
        }
  
    }

    //以下为测试的代码  by WangZY 2017/08/10
    public class ExportToImageCommandHandler : DevExpress.XtraPrinting.ICommandHandler
    {
        public virtual void HandleCommand(PrintingSystemCommand command,
        object[] args, IPrintControl control, ref bool handled)
        {
            
            if (command == PrintingSystemCommand.PageOrientation)
            {
                if (control.PrintingSystem.PageSettings.Landscape)
                {
                    MessageBox.Show("横向");
                }
                else
                {
                    MessageBox.Show("纵向");
                }

                handled = true;

                return ;
            }

            if (!CanHandleCommand(command, control))
            {
                return;
            }
            // Export a document to png.
            control.PrintingSystem.ExportToImage("F:\\Report.png"/*, ImageFormat.Png*/);
            //control.PrintingSystem.
            // Set handled to true to avoid the standard exporting procedure to be called.
            handled = true;
        }

        public virtual bool CanHandleCommand(PrintingSystemCommand command, IPrintControl control)
        {
            // This handler is used for the ExportGraphic command.
            return command == PrintingSystemCommand.ExportGraphic;
            
            
        }
    }


    

}
