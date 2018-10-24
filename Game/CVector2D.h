#ifndef __CVERCTOR_2D_H__
#define __CVERCTOR_2D_H__

#define _USE_MATH_DEFINES	//������һ��궨����mathͷ�ļ���ǰ��
#include <math.h>

//1e-5//��ѧ������ 1*10^(-5) 0.00001
#define ISFLOATZERO(x)	abs(x)<1e-5

//��ά��������
class CVector2D
{
public:
	float m_x;
	float m_y;
	//Ĭ����һ��������
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
	//��������ģ
	float Length()
	{
		return sqrt(m_x*m_x+m_y*m_y);
	}
	//��λ����������λ����������
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
	//��ȡ��λ��������λ�������ǲ��ı���������
	CVector2D Nomalize()
	{
		float len=Length();
		if (ISFLOATZERO(len))
		{
			return CVector2D(0,0);
		}
		return CVector2D(m_x/len,m_y/len);
	}
	//�������ڻ������
	float Dot(CVector2D& v)
	{
		return m_x*v.m_x+m_y*v.m_y;
	}
	//�����Ĳ�ˣ����
	float Cross(CVector2D& v)
	{
		return m_x*v.m_y-m_y*v.m_x;
	}
	//������ͶӰ
	CVector2D Projection(CVector2D& n)
	{
		float d=Dot(n);//�����������ڻ�
		float m=n.m_x*n.m_x+n.m_y*n.m_y;//��ͶӰ������ģ��ƽ��
		if (ISFLOATZERO(m))
		{
			return CVector2D(0,0);
		}
		return CVector2D(n.m_x*d/m,n.m_y*d/m);
	}
	
	float Angle_r(CVector2D& v)//�������нǻ���
	{
		 float dot = this->Dot(v);
		 float cosa = dot/(this->Length()*v.Length());
		 //acos() double
		 //acosl() long double
		 float a = acosf(cosa);
		 return a;
	}
	
	float Angle_d(CVector2D& v)//�������нǽǶ�
	{
		float a = Angle_r(v);
		return a/M_PI*180;
	}
	//�����ӷ�
	CVector2D operator + (CVector2D& v)
	{
		return CVector2D(m_x+v.m_x,m_y+v.m_y);
	}
	//��������
	CVector2D operator - (CVector2D& v)
	{
		return CVector2D(m_x-v.m_x,m_y-v.m_y);
	}
	//�����ӷ�
	CVector2D& operator += (CVector2D& v)
	{
		m_x+=v.m_x,m_y+=v.m_y;
		return *this;
	}
	//��������
	CVector2D& operator -= (CVector2D& v)
	{
		m_x-=v.m_x,m_y-=v.m_y;
		return *this;
	}
	//����������
	CVector2D operator * (float k)
	{
		return CVector2D(m_x*k,m_y*k);
	}
	//����������
	CVector2D& operator *= (float k)
	{
		m_x*=k,m_y*=k;
		return *this;
	}
	//����������
	CVector2D operator / (float k)
	{
		if (ISFLOATZERO(k))
		{
			//���ܳ���0
			return CVector2D(0,0);
		}
		return CVector2D(m_x/k,m_y/k);
	}
	//����������
	CVector2D operator /= (float k)
	{
		if (ISFLOATZERO(k))
		{
			//���ܳ���0
			return CVector2D(0,0);
		}
		m_x/=k;
		m_y/=k;
		return *this;
	}
};
#endif