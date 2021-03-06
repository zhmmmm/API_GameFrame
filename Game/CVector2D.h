#ifndef __CVERCTOR_2D_H__
#define __CVERCTOR_2D_H__

#define _USE_MATH_DEFINES	//定义这一句宏定义在math头文件的前面
#include <math.h>

//1e-5//科学计数法 1*10^(-5) 0.00001
#define ISFLOATZERO(x)	abs(x)<1e-5

//二维向量的类
class CVector2D
{
public:
	float m_x;
	float m_y;
	//默认是一个零向量
	CVector2D()
	{
		m_x=m_y=0;//sqrt(2.0)/2;
	}
	CVector2D(float x,float y)
	{
		m_x=x;m_y=y;
	}
	CVector2D(int x,int y)
	{
		m_x=x;m_y=y;
	}
	//求向量的模
	float Length()
	{
		return sqrt(m_x*m_x+m_y*m_y);
	}
	//单位化向量：单位化向量本身
	CVector2D& Nomalized()
	{
		float len=Length();
		if (ISFLOATZERO(len))
		{
			m_x=m_y=0;
			return *this;
		}
		m_x/=len;
		m_y/=len;
		return *this;
	}
	//获取单位向量：求单位向量但是不改变向量本身
	CVector2D Nomalize()
	{
		float len=Length();
		if (ISFLOATZERO(len))
		{
			return CVector2D(0,0);
		}
		return CVector2D(m_x/len,m_y/len);
	}
	//向量的内积，点乘
	float Dot(CVector2D& v)
	{
		return m_x*v.m_x+m_y*v.m_y;
	}
	//向量的叉乘，外积
	float Cross(CVector2D& v)
	{
		return m_x*v.m_y-m_y*v.m_x;
	}
	//向量的投影
	CVector2D Projection(CVector2D& n)
	{
		float d=Dot(n);//两个向量的内积
		float m=n.m_x*n.m_x+n.m_y*n.m_y;//被投影向量的模的平方
		if (ISFLOATZERO(m))
		{
			return CVector2D(0,0);
		}
		return CVector2D(n.m_x*d/m,n.m_y*d/m);
	}
	
	float Angle_r(CVector2D& v)//求向量夹角弧度
	{
		 float dot = this->Dot(v);
		 float cosa = dot/(this->Length()*v.Length());
		 //acos() double
		 //acosl() long double
		 float a = acosf(cosa);
		 return a;
	}
	
	float Angle_d(CVector2D& v)//求向量夹角角度
	{
		float a = Angle_r(v);
		return a/M_PI*180;
	}
	//向量加法
	CVector2D operator + (CVector2D& v)
	{
		return CVector2D(m_x+v.m_x,m_y+v.m_y);
	}
	//向量减法
	CVector2D operator - (CVector2D& v)
	{
		return CVector2D(m_x-v.m_x,m_y-v.m_y);
	}
	//向量加法
	CVector2D& operator += (CVector2D& v)
	{
		m_x+=v.m_x,m_y+=v.m_y;
		return *this;
	}
	//向量减法
	CVector2D& operator -= (CVector2D& v)
	{
		m_x-=v.m_x,m_y-=v.m_y;
		return *this;
	}
	//向量的数乘
	CVector2D operator * (float k)
	{
		return CVector2D(m_x*k,m_y*k);
	}
	//向量的数乘
	CVector2D& operator *= (float k)
	{
		m_x*=k,m_y*=k;
		return *this;
	}
	//向量的数除
	CVector2D operator / (float k)
	{
		if (ISFLOATZERO(k))
		{
			//不能除以0
			return CVector2D(0,0);
		}
		return CVector2D(m_x/k,m_y/k);
	}
	//向量的数除
	CVector2D operator /= (float k)
	{
		if (ISFLOATZERO(k))
		{
			//不能除以0
			return CVector2D(0,0);
		}
		m_x/=k;
		m_y/=k;
		return *this;
	}
};
#endif