#include "Render2DPip.h"
#include "../Frame/Frame.h"

//全局的矩阵变量，存储的是三个变换矩阵
CMatrix3 g_Mat[3];

void SetMatrix(MatrixType mt,CMatrix3* m)//设置变换矩阵
{
	if(mt<0||mt>MATRIX_VIEW)return;
	g_Mat[mt]=(*m);
}
CMatrix3& CreateProjectMatrix(float minx,float maxx,float miny,float maxy,CMatrix3* m)//创建投影变换矩阵
{

	float pcx=(maxx+minx)/2.0f;//投影中心坐标X
	float pcy=(maxy+miny)/2.0f;//投影中心坐标Y
	float pw=maxx-minx;//观察范围宽
	float ph=maxy-miny;//观察范围高
	m->Identity();
	m->Translate(-pcx,-pcy);//将物体移动到观察中心
	m->Scale(2.0f/pw,2.0f/ph);//将观察结果压缩到（-1,-1,+1,+1）范围内
	return *m;
}
CMatrix3& CreateViewportMatrix(float posx,float posy,float vw,float vh,CMatrix3* m)//创建视口变换矩阵
{
	m->Identity();
	m->Scale(1,-1);//因为屏幕坐标Y和世界坐标Y相反，所以先进行Y轴的反号
	float pvw=vw/2.0f,pvh=vh/2.0f;
	m->Scale(pvw,pvh);//将压缩后的画面缩放到要绘制的大小
	m->Translate(posx+pvw,posy+pvh);//将要绘制的画面移动到要绘制的位置
	return *m;
}
void DrawModel(CModel2D* md,int color)//绘制模型
{
	//用于存储矩阵变换计算后的点的数组
	static std::vector<CVector2D> tmp;


	tmp.resize(md->GetVertexNum());//重置顶点数量到模型顶点数量

	//先乘以世界变换矩阵
	for (int i=0;i<tmp.size();i++)
	{
		tmp[i]=md->Vertex(i)*g_Mat[MATRIX_WORLD];
	}
	//乘以投影变换矩阵（做裁剪）
	for (int i=0;i<tmp.size();i++)
	{
		tmp[i]=tmp[i]*g_Mat[MATRIX_PROJECT];
	}

	//投影完以后做投影裁剪（通过外接矩形实现的简单裁剪）
	float minx=tmp[0].m_x,maxx=tmp[0].m_x,miny=tmp[0].m_y,maxy=tmp[0].m_y;
	for (int i=0;i<tmp.size();i++)
	{
		if (tmp[i].m_x<minx){minx=tmp[i].m_x;}
		else if(tmp[i].m_x>maxx){maxx=tmp[i].m_x;}
		if(tmp[i].m_y<miny){miny=tmp[i].m_y;}
		else if(tmp[i].m_y>maxy){maxy=tmp[i].m_y;}
	}
	//如果没有相交，就不需要进行后面的绘制过程了
	if (minx>1||maxx<-1||miny>1||maxy<-1)
	{
		return;
	}

	//将能够绘制的物体，乘以视口变换矩阵
	for (int i=0;i<tmp.size();i++)
	{
		tmp[i]=tmp[i]*g_Mat[MATRIX_VIEW];
	}

	//绘制
	int i1,i2;//线段的两个索引
	for (int i=0;i<md->GetSegmentNum();i++)
	{
		i1=md->Segment(i).s;
		i2=md->Segment(i).e;
		g_GameOutput->DrawLine(tmp[i1].m_x,tmp[i1].m_y,tmp[i2].m_x,tmp[i2].m_y,color);
	}

}