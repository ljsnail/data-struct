#pragma once
//********************************************************************//
//第一层结构，从排样结果的dxf中读取数据的数据结构，经过排样后，
//只有LINE,ARC,CIRCLE这三种数据结构了，多段线转为了LINE
//********************************************************************//
typedef struct
{
	double x0, y0, x1, y1;//直线的起止点
	int flag;//作为直线是否已经被系统收录进入封闭体的标志
}LINE;//读取排样dxf结果时候的直线数据存储结构
typedef struct
{
	double Arccent_x, Arccent_y;//ARC的圆心
	double r;//ARC的半径
	double angle_start, angle_end;//ARC的起止角度
	//double x0, y0, x1, y1;//作为ARC的起点和终点,要找到上面五个参数与下面四个参数之间的关系
	int flag;
}ARC;
typedef struct
{
	double Circent_x, Circent_y;//CIRCLE的圆心
	double R;//CIRCLE的半径
	int flag;
}CIRCLE;
//********************************************************************//
//第二层结构，要对上面的三种数据结构建立统一标准的ID,用来后续遍历所有图元用
//这应该是一个统一的数据结构类型，包含了LINE,ARC,CIRCLE上面的三种数据类型
//********************************************************************//
class GEOMELE
{
public:
	GEOMELE();
	~GEOMELE();
public://将LINE ARC CIRLCE等元素读取进来，将来切割时候要用到这些原始数据
	LINE line;
	ARC arc;
	CIRCLE circle;//好像这三个都不需要包含进来。
	double GeoEle_start_x0, GeoEle_start_y0, GeoEle_start_x1, GeoEle_start_y1;
	int ID;//每一个图元有一个专门的标志，将来遍历用的
	int IID;//预留空位，给将来封闭环的时候写入不同的标志，作为判断时候使用
	bool flag;//判断是不是已经被收录了
public://这个类要实现的功能
	//读取转换数据的功能,输入LINE，ARC，CIRCLE的原始数据，转换成GeoEle_start_x0, GeoEle_start_y0, GeoEle_start_x1, GeoEle_start_y1;
	LINE ReadLineData(double x0,double y0,double x1,double y1);//读取直线的数据，并把数据保存起来返回给图元的统一起点和终点，用来将来寻找封闭环用
	LINE ReadARCData(double Arccent_x, double Arccent_y, double r, double angle_start, double angle_end);//读取ARC的参数，共有五个参数，但是要转为图元的统一起点和终点，用来将来寻找封闭环用
	LINE ReadCIRCLE(double Circent_x, double Circent_y,double R );//对于圆而言，那么他就是独立的封闭环，给它附一个特别的值如99999，下个类判断到这个值的时候，直接让他是一个封闭环就好
	//将
};

