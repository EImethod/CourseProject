#include<iostream>
#include<queue>
#include<map>
#include<fstream>
#include<string>

using namespace std;

#define datafile "data1.txt"
#define encodefile "Encode1.txt"
#define decodefile "Decode1.txt"
#define huffman_treefile "Huffman_Tree1.txt"


//********************************************************
struct Node
{
	int ID,weight;
	bool isWord;
	char word;
	int left,right;//����Ӻ��Ҷ��ӵ��±�
	friend bool operator<(const Node &a,const Node &b)
	{
		return a.weight > b.weight;
	}
}node[600];
int root,ind;//huffman���ĸ��±꣬�ͼ����õ�index
//********************************************************


map<char,int> Count;
map<char,int>::iterator it;
map<char,string> Coding;
priority_queue<Node> pq;


//************************************************************


void Scan()//ɨ��ÿ��unsigned char���ֵĴ���
{
	ifstream fin(datafile,ios::binary);
	Count.clear();

	char ch;

	while(fin.get(ch))
	{
		Count[ch]++;
	}

	fin.close();
}

void Con_Huffman()
{
	memset(node,0,sizeof(node));

	ind=0;
	for(it=Count.begin();it!=Count.end();it++)
	{
		if(it->second)
		{
			node[ind].ID=ind;
			node[ind].weight=it->second;
			node[ind].isWord=true;
			node[ind].word=it->first;

			pq.push(node[ind++]);
		}
	}

	int id1,id2;
	while(1)
	{
		id1=pq.top().ID,pq.pop();
		id2=pq.top().ID,pq.pop();

		node[ind].ID=ind;
		node[ind].left=id1;
		node[ind].right=id2;
		node[ind].weight=node[id1].weight+node[id2].weight;

		if(pq.empty())
			break;

		pq.push(node[ind++]);
	}

	root=ind;
}

void Store_Huffman()
{
	ofstream fout(huffman_treefile);

	fout<<"huffman���Ľڵ���\n���   Ȩ��   �Ƿ��ַ�   �ַ�����ֵ   ����ӱ��   �Ҷ��ӱ��\n";
	fout<<ind+1<<endl;//huffman���Ľڵ���
	for(int i=0;i<=ind;i++)
	{
		fout<<node[i].ID<<' '<<node[i].weight<<' '
			<<node[i].isWord<<' '<<(int)node[i].word<<' '
			<<node[i].left<<' '<<node[i].right<<endl;
	}
	fout.close();//�رյ��ļ���
}

void Get_Code(int index,string path)
{
	if(node[index].isWord)
	{
		Coding[node[index].word]=path;
		return;
	}
	Get_Code(node[index].left,path+'0');
	Get_Code(node[index].right,path+'1');
}

void Huffman_Encoding()
{
	ifstream fin(datafile,ios::binary);
	ofstream fout(encodefile,ios::binary);

	char ch;
	string code;

	char temp=0;
	int ind=7;

	while(fin.get(ch))
	{
		code=Coding[ch];
		for(int j=0;j<code.length();j++)
		{
			if(code[j]=='1')
				temp|=1<<ind;
			if(ind==0)
			{
				fout<<temp;
				temp=0;
				ind=7;
			}
			else
				ind--;
		}

	}

	if(ind==7)
	{
		//fout.seekp(0,ios::beg);
		//fout<<0;
	}
	else
	{
		fout<<temp;//���һ�����ֱ�ʾÿ�е�ĩβ�м���01��û�õ�
		//fout.seekp(0,ios::beg);
		//fout<<ind+1;
	}

	fin.close();
	fout.close();
}

void Huffman_Decoding()
{
	ifstream fin(encodefile,ios::binary);
	ofstream fout(decodefile,ios::binary);

	int p=root;

	char ch;

	char wei;
	//fin>>wei;

	while(fin.get(ch))
	{
			for(int ind=7;ind>=0;ind--)
			{
				if( ch&( 1<<ind ))
					p=node[p].right;
				else
					p=node[p].left;

				if(node[p].isWord)
				{
					fout<<node[p].word;
					p=root;
				}
			}
	}
	fin.close();
	fout.close();
}


void test()
{
	ifstream fin(datafile,ios::binary);
	ofstream fout("copy.txt",ios::binary);
	char ch;
	while(fin.get(ch))
	{
		fout<<(ch);
	}
}
int main()
{
	//test();
	Scan();//���ļ�����ɨ�裬ͳ���ַ����ֵ�Ƶ��	

	Con_Huffman();//����huffman��

	Store_Huffman();//��huffman������Ϣ��ӡ���ĵ���Ա��´ν�ѹ��ʱ����

	Coding.clear();
	Get_Code(root,"");//ÿ���ַ���huffman��ֵ

	Huffman_Encoding();//ѹ��
	Huffman_Decoding();//��ѹ
}