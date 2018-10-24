#ifndef __RENDER_2D_PIP_H__
#define __RENDER_2D_PIP_H__
#include "CModel2D.h"

//��������ö��
enum MatrixType{
	MATRIX_WORLD,//����任����
	MATRIX_PROJECT,//ͶӰ�任����
	MATRIX_VIEW//�ӿڱ任����
};

void SetMatrix(MatrixType mt,CMatrix3* m);//���ñ任����
CMatrix3& CreateProjectMatrix(float minx,float maxx,float miny,float maxy,CMatrix3* m);//����ͶӰ�任����
CMatrix3& CreateViewportMatrix(float posx,float posy,float vw,float vh,CMatrix3* m);//�����ӿڱ任����
void DrawModel(CModel2D* md,int color=RGB(0,0,0));//����ģ��


#endif