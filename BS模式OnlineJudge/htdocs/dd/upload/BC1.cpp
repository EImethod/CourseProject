#include<iostream>
#include<vector>
#include<queue>
#include<string>
#include<algorithm>
#include<stdio.h>
#include<stdarg.h>   // char *fmt,... ֧��
#include<set>
//#include"BC3.cpp"
//#include<pthread.h>
using namespace std;

//C����ѧϰ

/*
void add(char* fm,...){
	va_list args;
	va_start(args,fm);
	
	vaend(args);
}
*/
/*
�Ѿֲ������ı�Ϊ��̬�������Ǹı������Ĵ洢��ʽ���ı�������������
��ȫ�ֱ����ı�Ϊ��̬���� ���Ǹı�����������������������ʹ�÷�Χ
*/

void exit1(){
	puts("exit function 1 called");
}
void exit2(){
	puts("exit function 2 called");
}

void* f(void *intval){
	printf("�������%d\n",*(int*)intval);
	return NULL;
}

void myPrintf(int n,...){ //��Ҫ <stdarg.h>��֧��
	va_list ap; //va_list��ָ���ջ�е�ַ��ָ������
	va_start(ap,n); //��apָ���ջ��n(��һ�����ɱ����)�ĵ�ַ
	//vprintf(fmt,args);
	for(int i=0;i<n;i++){
		char *buf=va_arg(ap,char*); //ָ����һ����ַ,������ֵ
		printf("%d %s\n",i+1,buf);
	}
	va_end(ap);  //����
}


union myUnion{
	char ch;
	int val;
	short s;
	long long L;
};

void test_union(){
	myUnion u;
	u.L=0x12131415161718LL;
	printf("int: %x\n",u.val);
	printf("char: %x\n",(int)u.ch);
	printf("short: %x\n",(int)u.s);
	printf("long long: %llx\n",u.L);
	u.s=(short)0x2222;  printf("changed u.s scope!\n");
	printf("int: %x\n",u.val);
	printf("char: %x\n",(int)u.ch);
	printf("short: %x\n",(int)u.s);
	printf("long long: %llx\n",u.L);
	//union�ṹ��ĸ�����������һ���ڴ�,���Ǵ�ͬһ����λ��ʼռ��һ�����ֽ���
	//���test˵���ڴ�����һ��long long��ʱ���� (��λ���ڴ�ĸ�λ,��λ���ڴ�ĵ�λ) �����Ӵ�ŵ�.
}

#define SRC_LOCATION  __FILE__,__LINE__
void printLine(char *file,int line){
	printf("�ļ���λ����:  file:%s line:%d\n",file,line);
}

int main(){
	test_union();
	
	//printf("%s\n",getenv("path"));  ��ȡ����������ֵ
	cout<<sizeof(char*)<<endl;
	cout<<sizeof(char )<<endl;
	
	atexit(exit1);//��ջʽ��ӵ�
	atexit(exit2);
	
	int s=3;
	f(&s);
	
	printLine(SRC_LOCATION);
	
	myPrintf(4,"arg1","arg2","arg3","arg4");
	
	#if defined DDD
	printf("�Ѿ�������DDD\n");
	#else
	printf("û�ж���DDD\n");
	#endif
}

/*
	char buf[1000],*ptr=buf;
	gets(buf);
	int a,n;
	while( sscanf(ptr,"%d%n",&a,&n)!=EOF ){
		printf("%d\n",a); ptr+=n;
	}
*/













