#pragma once
//********************************************************************//
//��һ��ṹ�������������dxf�ж�ȡ���ݵ����ݽṹ������������
//ֻ��LINE,ARC,CIRCLE���������ݽṹ�ˣ������תΪ��LINE
//********************************************************************//
typedef struct
{
	double x0, y0, x1, y1;//ֱ�ߵ���ֹ��
	int flag;//��Ϊֱ���Ƿ��Ѿ���ϵͳ��¼��������ı�־
}LINE;//��ȡ����dxf���ʱ���ֱ�����ݴ洢�ṹ
typedef struct
{
	double Arccent_x, Arccent_y;//ARC��Բ��
	double r;//ARC�İ뾶
	double angle_start, angle_end;//ARC����ֹ�Ƕ�
	//double x0, y0, x1, y1;//��ΪARC�������յ�,Ҫ�ҵ�������������������ĸ�����֮��Ĺ�ϵ
	int flag;
}ARC;
typedef struct
{
	double Circent_x, Circent_y;//CIRCLE��Բ��
	double R;//CIRCLE�İ뾶
	int flag;
}CIRCLE;
//********************************************************************//
//�ڶ���ṹ��Ҫ��������������ݽṹ����ͳһ��׼��ID,����������������ͼԪ��
//��Ӧ����һ��ͳһ�����ݽṹ���ͣ�������LINE,ARC,CIRCLE�����������������
//********************************************************************//
class GEOMELE
{
public:
	GEOMELE();
	~GEOMELE();
public://��LINE ARC CIRLCE��Ԫ�ض�ȡ�����������и�ʱ��Ҫ�õ���Щԭʼ����
	LINE line;
	ARC arc;
	CIRCLE circle;//����������������Ҫ����������
	double GeoEle_start_x0, GeoEle_start_y0, GeoEle_start_x1, GeoEle_start_y1;
	int ID;//ÿһ��ͼԪ��һ��ר�ŵı�־�����������õ�
	int IID;//Ԥ����λ����������ջ���ʱ��д�벻ͬ�ı�־����Ϊ�ж�ʱ��ʹ��
	bool flag;//�ж��ǲ����Ѿ�����¼��
public://�����Ҫʵ�ֵĹ���
	//��ȡת�����ݵĹ���,����LINE��ARC��CIRCLE��ԭʼ���ݣ�ת����GeoEle_start_x0, GeoEle_start_y0, GeoEle_start_x1, GeoEle_start_y1;
	LINE ReadLineData(double x0,double y0,double x1,double y1);//��ȡֱ�ߵ����ݣ��������ݱ����������ظ�ͼԪ��ͳһ�����յ㣬��������Ѱ�ҷ�ջ���
	LINE ReadARCData(double Arccent_x, double Arccent_y, double r, double angle_start, double angle_end);//��ȡARC�Ĳ����������������������ҪתΪͼԪ��ͳһ�����յ㣬��������Ѱ�ҷ�ջ���
	LINE ReadCIRCLE(double Circent_x, double Circent_y,double R );//����Բ���ԣ���ô�����Ƕ����ķ�ջ���������һ���ر��ֵ��99999���¸����жϵ����ֵ��ʱ��ֱ��������һ����ջ��ͺ�
	//��
};

