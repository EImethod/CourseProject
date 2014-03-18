#include<iostream>
#include"BST.h"
#include<fstream>
#include<string>
#include<cstdlib>

using namespace std;

struct Item
{
	string name;
	string phoneNumber;
	
	Item(string a="",string b=""):name(a),phoneNumber(b){};
	
	bool operator<(const Item &b)
	{
		return name < b.name;
	}
	bool operator==(const Item &b)
	{
		return name == b.name;
	}
	friend ostream& operator<<(ostream &out,const Item &b)
	{
		return out<<"name: "<<b.name<<" phoneNumber: "<<b.phoneNumber;
	}
};

void work(BST<Item> &bst,int choice)
{
	string name,phoneNumber;
	if(choice==1)
	{
		cout<<"������Ҫ�½��������͵绰���룬��#�Ž���.\n";
		while(cin>>name)
		{
			if(name=="#")
				break;
			cin>>phoneNumber;
			bst.Insert(Item(name,phoneNumber));
		}
	}
	else if(choice==2)
	{
		cout<<"������Ҫɾ�����˵���������#�Ž���.\n";
		while(cin>>name)
		{
			if(name=="#")
				break;
			bst.Remove(Item(name));
		}
	}
	else if(choice==3)
	{
		cout<<"������Ҫ��ѯ���˵���������#�Ž���.\n";
		Node<Item> *p;
		while(cin>>name)
		{
			if(name=="#")
				break;
			p=bst.Find(Item(name));
			if(p==NULL)
				cout<<"�Բ������ݿ���û������˵���Ϣ.\n";
			else
				cout<<p->value<<endl;
		}
	}
}

int main()
{
	BST<Item> bst;
	cout<<"��ӭ����DDС��ͨѶ¼ϵͳ.\n\n";
	
	int choice;
	do
	{
		cout<<"�½���ϵ���밴1��ɾ����ϵ���밴2����ѯ��ϵ�˵绰�밴3���˳��밴0.\n";
		cin>>choice;
		if(choice==0)
			exit(0);
		else
			work(bst,choice);
	}while(1);
	
	ofstream fout("out.txt");
	
	bst.Print(fout);
}
