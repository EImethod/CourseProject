#ifndef SORT_H
#define SORT_H

#include<iostream>
#include<vector>
#include<cstdlib>
#include<ctime>
using namespace std;

//ð������˼�룺�����Ƚϣ��������
template<class T>
void Bubble_sort(vector<T> &v)
{
	int num=v.size();
	for(int c=1;c<num;c++)
	{
		for(int i=0;i<num-c;i++)
		{
			if(v[i]>v[i+1])
			{
				swap(v[i],v[i+1]);
			}
		}
	}
}

//ѡ������˼�룺ѡ��С�ķ��ڡ���λ��
template<class T>
void Select_sort(vector<T> &v)
{
	int ind,mi,n=v.size(),inf=0x7fffffff;
	for(int i=0;i<n-1;i++)//Ҫ�����λ��
	{
		mi=inf;
		for(int j=i;j<n;j++)//ѡ����Сֵ��λ��
		{
			if(v[j]<mi)
			{
				ind=j;
				mi=v[j];
			}
		}
		swap(v[i],v[ind]);//����
	}
}

//��������˼�룺ǰ��k�������ź��˵ģ������k+1��
template<class T>
void Insert_sort(vector<T> &v)
{
	int n=v.size();
	T temp;
	for(int i=1;i<n;i++)//�ѵ�k�����뵽ǰ��k-1���źõĶ���
	{
		temp=v[i];
		int j;
		for(j=i-1;j>=0 && v[j]>temp;j--)//KԪ�ز���Ĺ���
		{
			v[j+1]=v[j];
		}
		v[j+1]=temp;
	}
}


//ϣ������ ˼�룺���Ȳ������򣬶Կ�ȶ��֣�ÿ�ν������ٶ�������
template<class T>
void Shell_sort(vector<T> &v)
{
	int n=v.size();
	T temp;
	for(int len=n>>1;len>0;len>>=1)//��ȵ����Ϊ1��ʱ�����һ��Ĳ�������
	{
		for(int i=len;i<n;i++)
		{
			temp=v[i];
			int j;
			for(j=i-len;j>=0 && v[j]>temp;j-=len)//����Ĺ���
			{
				v[j+len]=v[j];
			}
			v[j+len]=temp;
		}
	}
}


//�������� ˼�룺����ĳ����ֵ������
template<class T>
void Count_sort(vector<T> &v)
{

	int ma=0,i;
	for(i=0;i<v.size();i++)//��������ֵ
		ma=(ma>v[i]?ma:v[i]);

	vector<int> sum(ma+3,0);//��������������
	vector<T> temp(v);

	int len=v.size();
	for(i=0;i<len;i++)//���������Ӧ��λ��+1
	{
		//if(v[i]>=ma)
			//system("pause");
		sum[v[i]]++;
	}
	for(i=1;i<=ma;i++)//��������
		sum[i]=sum[i]+sum[i-1];

	for(i=len-1;i>=0;i--)//�Ӻ���ǰ������������
	{
		v[ sum[temp[i]]-1  ]=temp[i];
		sum[temp[i]]--;
	}
}


//�鲢���� ˼�룺����
template<class T>
void Merge_sort(vector<T> &v,int left=-1,int right=-1)
{
	if(left==-1)
		left=0,right=v.size()-1;
	if(left==right)
		return;
	int mid=(left+right)>>1;

	//����
	Merge_sort(v,left,mid);
	Merge_sort(v,mid+1,right);

	//һ���Ǻϲ�����
	vector<T> L(mid-left+1);
	vector<T> R(right-mid);
	int ind=0,i;
	for(i=left;i<=mid;i++)
		L[ind++]=v[i];
	ind=0;
	for(i=mid+1;i<=right;i++)
		R[ind++]=v[i];

	ind=left;
	int lp=0,rp=0;
	while(lp<L.size() || rp<R.size())
	{
		if(lp>=L.size())
			v[ind++]=R[rp++];
		else if(rp>=R.size())
			v[ind++]=L[lp++];
		else if(L[lp]<=R[rp])
			v[ind++]=L[lp++];
		else
			v[ind++]=R[rp++];
	}
}


//�������� ˼�룺ѡȡһ����׼�㣬ÿ�ΰѴ������ݼ�������
template<class T>
void Quick_sort(vector<T> &v,int low=-1,int high=-1)
{
	if(low==-1)//�ǲ��ǵ�һ�ε��ã�����ǵ�һ�ε���ʹ��Ĭ�ϲ������Ժ���÷Ǹ���������-1�Ǹ����Ĵ���
		low=0,high=v.size()-1;
	if(low>=high)
		return ;
	int midIndex=partion(v,low,high);
	Quick_sort(v,low,midIndex-1);//�����Լ� �ݹ�
	Quick_sort(v,midIndex+1,high);
}

template<class T>//���ҷ�   ��С�Ҵ�
int partion(vector<T> &v,int low,int high)
{
	int _ind=low+rand()%(high-low);
	swap(v[low],v[_ind]);
	int pivot=v[low];

	while(low<high)
	{
		while(low<high && v[high]>=pivot)
			high--;
		if(low<high)
		{
			v[low]=v[high];
			low++;
		}

		while(low<high && v[low]<=pivot)
			low++;
		if(low<high)
		{
			v[high]=v[low];
			high--;
		}
	}
	v[low]=pivot;
	return low;
}


//�������� ˼�룺ÿ�����������򷽷�����ĳһλ��������������ü�������
template<class T>
void Radix_sort(vector<T> &v)
{
	int d[10];
	d[0]=1;
	for(int i=1;i<10;i++)
		d[i]=10*d[i-1];

	int num,len=v.size(),sum[10],_time=1;
	while(1)
	{
		vector<T> temp(v);
		memset(sum,0,sizeof(sum));
		for(int i=0;i<len;i++)
		{
			num=temp[i]%d[_time]/d[_time-1];
			sum[num]++;
		}
		for(int i=1;i<10;i++)
			sum[i]+=sum[i-1];

		if(sum[0]==len)
			break;
		for(int i=len-1;i>=0;i--)
		{
			num=temp[i]%d[_time]/d[_time-1];
			v[ --sum[num] ]=temp[i];//����1��
		}
		_time++;
	}
}

//������ ˼�룺�������ѵ�����
template<class T>
void max_Heapify(vector<T> &v,int maxIndex,int i)//ʹ֮���ѻ�
{
	int largest=i;

	int left= (i<<1)+1;   //left�ǳ���2+1����Ϊ�����0��ע����
	int right= (i<<1) +2;

	if(left<=maxIndex && v[left]>v[largest])
		largest=left;
	if(right<=maxIndex && v[right]>v[largest])
		largest=right;

	if(largest!=i)
	{
		swap(v[i],v[largest]); //����ַ******************
		max_Heapify(v,maxIndex,largest);
	}
}

template<class T>
void Heap_sort(vector<T> &v)
{
	int len=v.size();
	for(int i=len/2+1;i>=0;i--)
		max_Heapify(v,len-1,i);

	for(int _time=1;_time<len;_time++)
	{
		swap(v[len-_time],v[0]);
		max_Heapify(v,len-_time-1,0);
	}
}

#endif
