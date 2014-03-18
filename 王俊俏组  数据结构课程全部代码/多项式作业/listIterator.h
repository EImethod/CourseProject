#ifndef LISTITERATOR_H
#define LISTITERATOR_H

#include"list.h"

template<class T>
class listIterator
{
    private:
        list<T> &obj;//���������ã����Ա����ó�ʼ���б�ķ�ʽ���г�ʼ��
        listNode<T> *cur,*pre;
    public:
        listIterator(list<T> &_obj);

        virtual bool init();
        virtual T& operator()();//�������ã�Ҫ�޸ĵ�
        virtual bool operator!();
        virtual bool operator++();
        virtual void operator=(T val);

        void removeCurrent();
        void addBefore(T val);
        void addAfter(T val);
};
//***********************
template<class T>
listIterator<T>::listIterator(list<T> &_obj):obj(_obj)//*****
{
    //obj=_obj;
    cur=obj.head;
    pre=NULL;
}
//*******************************

template<class T>
bool listIterator<T>::init()
{
    cur=obj.head;
    pre=NULL;
    return cur!=NULL;
}

template<class T>
T& listIterator<T>::operator()()
{
    assert(cur!=NULL);//����ͱ���������ո�ִ����removeCurrent�����Ͳ�������ִ�����ȡֵ����
    return cur->value;
}

template<class T>
void listIterator<T>::operator=(T val)
{
    assert(cur!=NULL);
    cur->value=val;
}

template<class T>
void listIterator<T>::removeCurrent()
{
    assert(cur!=NULL);
    if(pre==NULL)//���ɾ�������׽ڵ�
        obj.head=obj.head->next;
    else         //ɾ�������м�Ľڵ�
        pre->next=cur->next;

    delete cur;
    cur=NULL;
}

template<class T>
bool listIterator<T>::operator++()
{
    if(cur==NULL)
    {
        if(pre==NULL)
            cur=obj.head;
        else
            cur=pre->next;
    }
    else
    {
        pre=cur;
        cur=cur->next;
    }
    return cur!=NULL;
}

template<class T>
bool listIterator<T>::operator!()
{
    if(cur!=NULL)
        return true;
    else if(pre!=NULL)
        return pre->next!=NULL;
    else
        return obj.head!=NULL;
}

template<class T>
void listIterator<T>::addBefore(T val)
{
    if(pre!=NULL)
        pre=pre->insert(val);//insert����Ϊ�嵽���Ȼ�󷵻�����ڵ�ĵ�ַ
    else //preΪNULLʱ������������׽ڵ�֮ǰ
    {
        obj.list<T>::add(val);//obj.add(val);
        pre=obj.head;
    }
}

template<class T>
void listIterator<T>::addAfter(T val)
{
    if(cur!=NULL)//cur�ڵ�ʱ��
        cur->insert(val);
    else if(pre!=NULL)//pre�ڵ�ʱ��
        pre->insert(val);
    else
        obj.list<T>::add(val);
}

#endif