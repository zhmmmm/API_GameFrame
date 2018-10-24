#include "CModel2D.h"


CModel2D::CModel2D(){}
CModel2D::~CModel2D(){}
bool CModel2D::LoadModelFromFile(const char* filename)
{
	FILE* pf=NULL;
	fopen_s(&pf,filename,"r");
	if(!pf){return false;}//������ļ�ʧ�ܷ��ؼ�
	
	//fscanf(
	//����1,//�ļ�ָ��
	//����2,//��Ҫ������ı���ʽ�ַ���
	//...)//�ı���ʽ�ַ����б�����Ҫ�洢�ĵط�

	//char buff[256];
	//sprintf_s(buff,"%d123fsadfasd\n",123);


	//�ɹ�������£�����ģ���ļ�
	//1)��������Ϣ
	fscanf(pf,"%d\r\n",&mVertexNum);//���������
	CVector2D tmp;
	for (int i=0;i<mVertexNum;i++)//ѭ����ȡ���������
	{
		fscanf(pf,"(%f,%f)\r\n",&tmp.m_x,&tmp.m_y);
		mVertexs.push_back(tmp);
	}
	//2)��������Ϣ
	fscanf(pf,"%d\r\n",&mSegmentNum);//�߶ε�����
	SEGMENT_INDEX sg;
	for (int i=0;i<mSegmentNum;i++)//ѭ����ȡ�߶���������
	{
		fscanf(pf,"(%d,%d)\r\n",&sg.s,&sg.e);
		mSegments.push_back(sg);
	}
	fclose(pf);
	return true;
}
//void CModel2D::DrawModel(CMatrix3* m,int color)
//{
//	int i1,i2;//�߶ε���������
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