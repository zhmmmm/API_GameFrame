#ifndef __RENDER_2D_PIP_H__
#define __RENDER_2D_PIP_H__
#include "CModel2D.h"

//矩阵类型枚举
enum MatrixType{
	MATRIX_WORLD,//世界变换矩阵
	MATRIX_PROJECT,//投影变换矩阵
	MATRIX_VIEW//视口变换矩阵
};

void SetMatrix(MatrixType mt,CMatrix3* m);//设置变换矩阵
CMatrix3& CreateProjectMatrix(float minx,float maxx,float miny,float maxy,CMatrix3* m);//创建投影变换矩阵
CMatrix3& CreateViewportMatrix(float posx,float posy,float vw,float vh,CMatrix3* m);//创建视口变换矩阵
void DrawModel(CModel2D* md,int color=RGB(0,0,0));//绘制模型


#endif