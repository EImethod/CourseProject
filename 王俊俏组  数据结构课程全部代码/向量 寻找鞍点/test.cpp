#include"matrix.h"
#include<iostream>
using namespace std;




void find(const matrix<int> &mat)
{
	int rows=mat.get_rows(),cols=mat.get_cols();
	int c=1;
	for(int i=0;i<rows;i++)
	{
		for(int j=0;j<cols;j++)
		{
			bool flag=true;
			for(int k=0;k<cols;k++)
				if(mat[i][j]>mat[i][k])
				{
					flag=false;
					break;
				}
			for(k=0;k<rows;k++)
				if(mat[i][j]<mat[k][j])
				{
					flag=false;
					break;
				}
			if(flag)
				cout<<"��������"<<c++<<"      "<<i<<' '<<j<<endl;
		}
	}
}

int main()
{
	int cas,c=1;
	cout<<"����������ݵ�����\n";
	cin>>cas;
	while(cas--)
	{
		int rows,cols;
		cout<<"���������к���\n";
		cin>>rows>>cols;
		matrix<int> mat(rows,cols);
		cout<<"��������е�����"<<endl;
		for(int i=0;i<rows;i++)
			for(int j=0;j<cols;j++)
				cin>>mat[i][j];
		cout<<"test "<<c++<<endl;
		find(mat);
		cout<<endl;
	}
	return 0;
}