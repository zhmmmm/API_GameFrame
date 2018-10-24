#include "Render2DPip.h"
#include "../Frame/Frame.h"

//ȫ�ֵľ���������洢���������任����
CMatrix3 g_Mat[3];

void SetMatrix(MatrixType mt,CMatrix3* m)//���ñ任����
{
	if(mt<0||mt>MATRIX_VIEW)return;
	g_Mat[mt]=(*m);
}
CMatrix3& CreateProjectMatrix(float minx,float maxx,float miny,float maxy,CMatrix3* m)//����ͶӰ�任����
{

	float pcx=(maxx+minx)/2.0f;//ͶӰ��������X
	float pcy=(maxy+miny)/2.0f;//ͶӰ��������Y
	float pw=maxx-minx;//�۲췶Χ��
	float ph=maxy-miny;//�۲췶Χ��
	m->Identity();
	m->Translate(-pcx,-pcy);//�������ƶ����۲�����
	m->Scale(2.0f/pw,2.0f/ph);//���۲���ѹ������-1,-1,+1,+1����Χ��
	return *m;
}
CMatrix3& CreateViewportMatrix(float posx,float posy,float vw,float vh,CMatrix3* m)//�����ӿڱ任����
{
	m->Identity();
	m->Scale(1,-1);//��Ϊ��Ļ����Y����������Y�෴�������Ƚ���Y��ķ���
	float pvw=vw/2.0f,pvh=vh/2.0f;
	m->Scale(pvw,pvh);//��ѹ����Ļ������ŵ�Ҫ���ƵĴ�С
	m->Translate(posx+pvw,posy+pvh);//��Ҫ���ƵĻ����ƶ���Ҫ���Ƶ�λ��
	return *m;
}
void DrawModel(CModel2D* md,int color)//����ģ��
{
	//���ڴ洢����任�����ĵ������
	static std::vector<CVector2D> tmp;


	tmp.resize(md->GetVertexNum());//���ö���������ģ�Ͷ�������

	//�ȳ�������任����
	for (int i=0;i<tmp.size();i++)
	{
		tmp[i]=md->Vertex(i)*g_Mat[MATRIX_WORLD];
	}
	//����ͶӰ�任�������ü���
	for (int i=0;i<tmp.size();i++)
	{
		tmp[i]=tmp[i]*g_Mat[MATRIX_PROJECT];
	}

	//ͶӰ���Ժ���ͶӰ�ü���ͨ����Ӿ���ʵ�ֵļ򵥲ü���
	float minx=tmp[0].m_x,maxx=tmp[0].m_x,miny=tmp[0].m_y,maxy=tmp[0].m_y;
	for (int i=0;i<tmp.size();i++)
	{
		if (tmp[i].m_x<minx){minx=tmp[i].m_x;}
		else if(tmp[i].m_x>maxx){maxx=tmp[i].m_x;}
		if(tmp[i].m_y<miny){miny=tmp[i].m_y;}
		else if(tmp[i].m_y>maxy){maxy=tmp[i].m_y;}
	}
	//���û���ཻ���Ͳ���Ҫ���к���Ļ��ƹ�����
	if (minx>1||maxx<-1||miny>1||maxy<-1)
	{
		return;
	}

	//���ܹ����Ƶ����壬�����ӿڱ任����
	for (int i=0;i<tmp.size();i++)
	{
		tmp[i]=tmp[i]*g_Mat[MATRIX_VIEW];
	}

	//����
	int i1,i2;//�߶ε���������
	for (int i=0;i<md->GetSegmentNum();i++)
	{
		i1=md->Segment(i).s;
		i2=md->Segment(i).e;
		g_GameOutput->DrawLine(tmp[i1].m_x,tmp[i1].m_y,tmp[i2].m_x,tmp[i2].m_y,color);
	}

}