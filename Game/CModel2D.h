#ifndef __CMODEL_2D_H__
#define __CMODEL_2D_H__
#include<vector>
#include "CMatrix3.h"
//�߶������ṹ��
typedef struct __SegmentIndex
{
	int s;//�������
	int e;//�յ�����
}SEGMENT_INDEX,*PSEGMENT_INDEX;

class CModel2D
{
public:
	CModel2D();
	~CModel2D();
	//���ļ�����ģ��
	bool LoadModelFromFile(const char* filename);
	//void DrawModel(CMatrix3* m,int color=RGB(0,0,0));
	//��ȡ���������
	const int& GetVertexNum()  {return mVertexNum;}
	//��ȡ�߶ε�����
	const int& GetSegmentNum()  {return mSegmentNum;}

	//��ȡָ����������
	const CVector2D& Vertex(int idx)  {return mVertexs[idx];}
	//��ȡָ���������߶�
	const SEGMENT_INDEX& Segment(int idx)  {return mSegments[idx];}
protected:
private:
	int mVertexNum;//�������
	int mSegmentNum;//�߶θ���
	std::vector<CVector2D> mVertexs;//��������
	std::vector<SEGMENT_INDEX> mSegments;//�߶���������
};
#endif
