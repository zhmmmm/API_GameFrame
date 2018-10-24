#include "CModel2D.h"


CModel2D::CModel2D(){}
CModel2D::~CModel2D(){}
bool CModel2D::LoadModelFromFile(const char* filename)
{
	FILE* pf=NULL;
	fopen_s(&pf,filename,"r");
	if(!pf){return false;}//如果打开文件失败返回假
	
	//fscanf(
	//参数1,//文件指针
	//参数2,//需要读入的文本格式字符串
	//...)//文本格式字符串中变量需要存储的地方

	//char buff[256];
	//sprintf_s(buff,"%d123fsadfasd\n",123);


	//成功的情况下：解析模型文件
	//1)读顶点信息
	fscanf(pf,"%d\r\n",&mVertexNum);//顶点的数量
	CVector2D tmp;
	for (int i=0;i<mVertexNum;i++)//循环读取顶点的坐标
	{
		fscanf(pf,"(%f,%f)\r\n",&tmp.m_x,&tmp.m_y);
		mVertexs.push_back(tmp);
	}
	//2)读索引信息
	fscanf(pf,"%d\r\n",&mSegmentNum);//线段的数量
	SEGMENT_INDEX sg;
	for (int i=0;i<mSegmentNum;i++)//循环读取线段索引数组
	{
		fscanf(pf,"(%d,%d)\r\n",&sg.s,&sg.e);
		mSegments.push_back(sg);
	}
	fclose(pf);
	return true;
}
//void CModel2D::DrawModel(CMatrix3* m,int color)
//{
//	int i1,i2;//线段的两个索引
//	CVector2D p1,p2;
//	for (int i=0;i<mSegmentNum;i++)
//	{
//		i1=mSegments[i].s;
//		i2=mSegments[i].e;
//		p1=mVertexs[i1]*(*m);
//		p2=mVertexs[i2]*(*m);
//		g_GameOutput->DrawLine(p1.m_x,p1.m_y,p2.m_x,p2.m_y,color);
//	}
//}