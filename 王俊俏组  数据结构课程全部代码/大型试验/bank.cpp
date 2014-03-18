#include<iostream>
#include<queue>//���ö���  ����һ�����  һ�����ȶ���
#include<iomanip>//���������ʽ

using namespace std;

struct Case//�й��¼�
{
	int arrival,last,money,num;
	Case(int _a=0,int _l=0,int _m=0,int _i=0):arrival(_a),last(_l),money(_m),num(_i){};//���캯��
	friend bool operator<(const Case &a,const Case &b)//�������ȶ��еıȽ�
	{
		return a.money < b.money;//ȡǮΪ�ؼ�ֵ
	}
};


int main()
{
	queue<Case> list;//��Ž�Ҫ�������¼����˽����е��¼���   �������Ϊ����һ�����
	queue<Case> q1;  //������ĵ�һ�����У��ȴ�������
	priority_queue<Case> q2; //������ĵڶ������У��ȴ����д��

	int arrival,last,money,num=1; //num��¼���ǵڼ��ſͻ�
	cout<<"������������е��¼��б��ͻ��Ĵﵽʱ�䣬����ʱ���Ǯ����.\n";
	while(cin>>arrival>>last>>money)//����һ�����ҵ�񣨰���ʱ����Ⱥ�
		list.push( Case(arrival,last,money,num++) ); //�������е�˳��

	int currenTime=0;
	int totalMoney=10000;

	Case temp,temp2,temp3;//��ʱ����
	while(currenTime<600)
	{
		if(list.empty())//���û�пͻ����������������
			break;
		temp=list.front();//ȡδ��������еĵ�һ���� 
		list.pop();//�Ӷ���ɾ��
		cout<<"Time "<<setw(3)<<temp.arrival<<": "<<temp.num<<"�ſͻ���������."<<endl;

		q1.push(temp);//�ŵ���һ�����к���
		currenTime=temp.arrival;//�ѵ�ǰʱ���Ƶ�����ͻ��ĵ���ʱ�䣨��ɢ��

		while(!q1.empty() && currenTime<600)//ֻҪ��һ�����в�����ʱ�仹û�°࣬�Ϳ��Է���
		{
			temp=q1.front();//ȡ�����ڵ�һ��������ǰ���һ�����ȴ���������ˣ� 
			q1.pop();
			
			if(temp.money>=0)//����Ǵ�Ǯ��
			{
				cout<<"Time "<<setw(3)<<currenTime<<": ��̨��ʼΪ"<<temp.num<<"�ſͻ�����."<<endl;
				currenTime+=temp.last;  //��̨��Ϊ�����񣬰ѵ�ǰʱ���Ƶ�������ʱ

				while(!list.empty() && list.front().arrival <=currenTime)//�ڷ����ڼ�������˽�������
				{
					temp2=list.front();
					list.pop();
					cout<<"Time "<<setw(3)<<temp2.arrival<<": "<<temp2.num<<"�ſͻ���������."<<endl;
					q1.push(temp2);
				}//������Ϊǰһ���˷����ڼ��Ƿ������˽�������

				totalMoney+=temp.money;//������Ǯ������
				cout<<"Time "<<setw(3)<<currenTime<<": "<<temp.num<<"�ſͻ���������"<<temp.money<<"Ԫ���뿪����"<<endl;

				while(!q2.empty() && q2.top().money+totalMoney>=0 && currenTime<=600)//����Ǯ���˾Ϳ��ܲ��ܴ�����ͻ�
				{
					temp2=q2.top();
					q2.pop();
					cout<<"Time "<<setw(3)<<currenTime<<": ��̨��ʼΪ"<<temp2.num<<"�ſͻ�����"<<endl;

					currenTime+=temp2.last;//���е�ǰʱ������
					while(!list.empty() && list.front().arrival <=currenTime)//�����ڼ��Ƿ����˽�����
					{
						temp3=list.front();
						list.pop();
						cout<<"Time "<<setw(3)<<temp3.arrival<<": "<<temp3.num<<"�ſͻ���������."<<endl;
						q1.push(temp3);
					}
					totalMoney+=temp2.money;

					cout<<"Time "<<setw(3)<<currenTime<<": "<<temp2.num<<"�ſͻ�������ȡ��"<<-temp2.money<<"Ԫ���뿪����"<<endl;
				}
			}
			else//�����ҪȡǮ��
			{
				if(totalMoney+temp.money>=0)
				{
					cout<<"Time "<<setw(3)<<currenTime<<": ��̨��ʼΪ"<<temp.num<<"�ſͻ�����."<<endl;
					currenTime+=temp.last;

					while(!list.empty() && list.front().arrival <=currenTime)//�����ڼ����˽�������
					{
						temp2=list.front();
						list.pop();
						cout<<"Time "<<setw(3)<<temp2.arrival<<": "<<temp2.num<<"�ſͻ���������."<<endl;
						q1.push(temp2);
					}
					totalMoney+=temp.money;
					cout<<"Time "<<setw(3)<<currenTime<<": "<<temp.num<<"�ſͻ�������ȡ��"<<-temp.money<<"Ԫ���뿪����"<<endl;
				}
				else
				{
					cout<<"Time "<<setw(3)<<currenTime<<": ��������Ǯ������"<<temp.num<<"�ſͻ�����ڶ������еȺ�."<<endl;
					q2.push(temp);
				}
			}
		}
	}

	while(!q1.empty())
	{
		temp=q1.front();
		q1.pop();
		cout<<"Time "<<setw(3)<<currenTime<<": ��������Ҫ�ر�"<<temp.num<<"�ſͻ��뿪����."<<endl;
	}
	while(!q2.empty())
	{
		temp=q2.top();
		q2.pop();
		cout<<"Time "<<setw(3)<<currenTime<<": ��������Ҫ�ر�"<<temp.num<<"�ſͻ��뿪����."<<endl;
	}


	return 0;
}
