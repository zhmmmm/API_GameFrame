#ifndef __CMODEL_2D_H__
#define __CMODEL_2D_H__
#include<vector>
#include "CMatrix3.h"
//线段索引结构体
typedef struct __SegmentIndex
{
	int s;//起点索引
	int e;//终点索引
}SEGMENT_INDEX,*PSEGMENT_INDEX;

class CModel2D
{
public:
	CModel2D();
	~CModel2D();
	//从文件加载模型
	bool LoadModelFromFile(const char* filename);
	//void DrawModel(CMatrix3* m,int color=RGB(0,0,0));
	//获取顶点的数量
	const int& GetVertexNum()  {return mVertexNum;}
	//获取线段的数量
	const int& GetSegmentNum()  {return mSegmentNum;}

	//获取指定索引顶点
	const CVector2D& Vertex(int idx)  {return mVertexs[idx];}
	//获取指定索引的线段
	const SEGMENT_INDEX& Segment(int idx)  {return mSegments[idx];}
protected:
private:
	int mVertexNum;//顶点个数
	int mSegmentNum;//线段个数
	std::vector<CVector2D> mVertexs;//顶点数组
	std::vector<SEGMENT_INDEX> mSegments;//线段索引数组
};
#endif
