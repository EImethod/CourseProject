#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include<iostream>
#include"term.h"
using namespace std;

class polynomial
{
private:
	list<term> exp;
public:
	polynomial();
	polynomial(const polynomial &p);

	list<term> get_exp()const {return exp;}
	void operator+=(const term &t);
	polynomial operator+(polynomial &p2);//���������õģ����ؾ������ˣ�ʵ�岻������

	friend ostream& operator<<(ostream &o,polynomial &p);
};

polynomial::polynomial()
{};

polynomial::polynomial(const polynomial &p):exp(p.exp)
{};

void polynomial::operator+=(const term &t)
{
	listIterator<term> it(exp);
	for(it.init();!it;it++)
	{
		if(it().p==t.p)
		{
			it().c+=t.c;
			return;
		}
		else if(it().p>t.p)
		{
			it.addBefore(t);
			return;
		}
	}
	it.addBefore(t);
	return;
}

polynomial polynomial::operator+(polynomial &p2)
{
	polynomial p3;
	listIterator<term> it1(exp),it2(p2.exp);
	term temp;
	for(it1.init();!it1;it1++)
	{
		temp=it1();//���ÿ����ٴ����������������𣿣���
		p3+=temp;
	}
	for(it2.init();!it2;it2++)
	{
		temp=it2();
		p3+=temp;
	}
	return p3;
}                    //p3������ͱ�������

ostream& operator<<(ostream &o,polynomial &p)
{
	//listIterator<term> it(p.get_exp());//����ǲ��еģ�p.get_exp()���ص���һ����ʱ�������ִ�����ͱ������ˣ�����it�ͳ����޸�֮����
	
	listIterator<term> it(p.exp);
	o<<it();
	it++;
	for(;!it;it++)
		o<<"+"<<it();
	return o;
}
#endif