using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;
using DevExpress.XtraCharts;

namespace KDS_CSharpReport
{
    public partial class MyChartControl : DevExpress.XtraCharts.ChartControl
    {
        public MyChartControl()
        {

        }
    }

    public class MyChartControlData
    {
        public DataTable CreateChartData()
        {
            DataTable table = new DataTable("Table1");
            table.Columns.Add("Name", typeof(String));
            table.Columns.Add("Value", typeof(Int32));
            table.Rows.Add(new object[] { "A", 10 });
            table.Rows.Add(new object[] { "B", 20 });
            table.Rows.Add(new object[] { "C", 40 });
            table.Rows.Add(new object[] { "D", 20 });
            table.Rows.Add(new object[] { "E", 30 });
            return table;
        }
        public void BuilderDevChart(MyChartControl chartControl1)
        {
            Series _pieSeries = new Series("测试", ViewType.Pie3D);
            _pieSeries.ValueDataMembers[0] = "Value";
            _pieSeries.ArgumentDataMember = "Name";
            _pieSeries.DataSource = CreateChartData();
            chartControl1.Series.Add(_pieSeries);

            //----------------------------------------
            _pieSeries.LegendPointOptions.PointView = PointView.ArgumentAndValues;
            SetPiePercentage(_pieSeries);
        }

        /// 饼状Series设置成百分比显示
        public void SetPiePercentage(Series series)
        {
            if (series.View is PieSeriesView)
            {
                ((PiePointOptions)series.PointOptions).PercentOptions.ValueAsPercent = true;
                ((PiePointOptions)series.PointOptions).ValueNumericOptions.Format = NumericFormat.Percent;
                ((PiePointOptions)series.PointOptions).ValueNumericOptions.Precision = 0;
            }
        }
    }
}
