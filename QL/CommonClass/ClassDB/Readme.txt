CDataMid 数据类继承
	1-构造初始化方法：ResetData() 函数设置函数变量默认值	(必须设置)
	2-设置数据类型：SetDataType()设置数据类型 类型声明在KdsFileMgnTypeDef.h中(必须设置 在ResetData() 中实现)
	3-数据拷贝：Copy() 调用CDataMid::Copy(pData);保证基类数据拷贝(使用时重写)
	4-序列化 Serialize() 调用CDataMid::Serialize(ar);保证基类数据序列化(使用时重写)