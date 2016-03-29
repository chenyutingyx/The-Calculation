#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;
class A
{
public:
	A();
	~A();
	void B(int num);
	int C(int range);
	
	void Display( );

private:
	// 比较运算符的优先级
	bool ChoiceIsHigher();
	// 得到运算符的权值
	int Getyunsuanfuqz(const char oper);

private:
	int Result;
	// 表达式的结果
	char oper;
	// 表达式的运算符
	A *lhs;
	// 表达式的左节点
	A *rhs;
	// 表达式的右节点
	bool isEX;
	// 该表达式是否为最终的表达式
	A *Parent;
	// 表达式的父节点
	bool isLeft;
	// 是否为左节点(为了输出是加括号用)
};
A::A()
	: Result(0)
	, oper('\0')
	, lhs(NULL)
	, rhs(NULL)
	, Parent(NULL)
	, isLeft(false)
{

}

A::~A()//析构函数，用来清理扫尾
{
	if(lhs != NULL)
	{
		delete lhs;
	}

	if (rhs != NULL)
	{
		delete rhs;
	}
}
// 生成含有num个运算数字的随机表达式
void A::B(int num)
{
	if ( num==1 )
	{
		return ;
	}
	else
	{
		int fuhao = rand() % 4;//随机生成0-3的数来代表对应的四种运算符号的下标
		if (fuhao == 0)
		{
			oper = '+';
		}
		else if (  fuhao==1)
		{
			oper = '-';
		}
		else if ( fuhao==2 )
		{
			oper = '*';
		}
		else
		{
			oper = '/';
		}

		lhs = new A();
		rhs = new A();
		lhs->Parent = this;
		lhs->isLeft = true;
		rhs->Parent = this;
		rhs->isLeft = false;
		int numOfNodeLeft = num - rand() % num;
		if (numOfNodeLeft == num)
		{
			numOfNodeLeft = 1;
		}

		lhs->B(numOfNodeLeft);
		rhs->B(num - numOfNodeLeft);
	}
}
int A::C(int range)// 给生成的表达式框架填入符合条件的随机的数字
{
	if (lhs != NULL && rhs != NULL)
	{
		int lResult = 0;
		int rResult = 0;
		lResult = lhs->C( range);
		rResult = rhs->C( range);
		while (lResult >= range || lResult <= 0)
		{
			lResult = lhs->C( range);
		}
		while (rResult >= range|| rResult <= 0)
		{
			rResult = rhs->C( range);
		}
		if (oper == '+')
		{
			Result = lResult + rResult;
		}
		else if ( oper=='-' )
		{
			Result = lResult - rResult;
			if (Result < 0)//防止运算结果为负数
			{
				A *t = lhs;
				lhs = rhs;
				lhs->isLeft = true;
				rhs = t;
				rhs->isLeft = false;
				Result = rResult - lResult;
			}
		}
		else if ( oper=='*' )
		{
			int getNum = 0;
			Result = lResult * rResult;
			while(Result >= 100)
			{
				lResult = lhs->C(range);
				rResult = rhs->C(range);
				getNum++;
				if (getNum > 100)
				{
					int fuhao = rand() % 2;
					if (fuhao ==0 )
					{
						oper = '+';
						Result = lResult + rResult;
					}
					else if ( fuhao==1 )
					{
						oper = '-';
						Result = lResult - rResult;
						if (Result < 0)
						{
							A *temp = lhs;
							lhs = rhs;
							lhs->isLeft = true;
							rhs = temp;
							rhs->isLeft = false;
							Result = rResult - lResult;
						}
					}
					return Result;
				}

				Result = lResult * rResult;
			}
		}
		else if ( oper=='/' )
		{
			int getNum = 0;
			while ( lResult==0  ||  rResult== 0 || lResult % rResult != 0)
			{
				lResult = lhs->C(range);
				rResult = rhs->C(range);
				getNum++;
				if(getNum > 2000)
				{
					int fuhao = rand() % 2;
					if ( fuhao==0 )
					{
						oper = '+';
						Result = lResult + rResult;
					}
					else if ( fuhao== 1)
					{
						oper = '-';
						Result = lResult - rResult;
						if (Result < 0)
						{
							A *temp = lhs;
							lhs = rhs;
							lhs->isLeft = true;
							rhs = temp;
							rhs->isLeft = false;
							Result = rResult - lResult;
						}
					}
					return Result;
				}
			}

			Result = lResult / rResult;
		}
	}
	else//处理没输入运算数的范围，如果范围为0报错
	{
		Result = rand() % range;
		while (Result == 0)
		{
			Result = rand() % range;
		}
	}
	return Result;
}
void A::Display()// 输出所生成的表达式
{	
	if(lhs != NULL && rhs != NULL)
	{
		if (!ChoiceIsHigher())
		{	
			cout << '(';
		}
		lhs->Display();
		cout << " " << oper << " ";
		rhs->Display();
		if (!ChoiceIsHigher())
		{
			cout << ')';
		}
	}
	else
	{
		cout << Result;		
	}
}
bool A::ChoiceIsHigher()
{
	if (Parent ==NULL )
	{
		return true;
	}
	if (isLeft)
	{
		return Getyunsuanfuqz(this->oper) >= Getyunsuanfuqz(Parent->oper);
	}
	else
	{
		return Getyunsuanfuqz(this->oper) > Getyunsuanfuqz(Parent->oper);
	}
}
int A::Getyunsuanfuqz(const char oper)
{
	if (oper =='\0' )
	{
		return 3;
	}
	else if (oper =='/'  || oper == '*')
	{
		return 2;
	}
	else if ( oper=='+'  || oper== '-')
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
//void inputanswer(int Result,int numtimu,int i){
//	ofstream of;
//	of.open("answer.txt");
//	
//	of<<"答案"<<i<<":"<<" "<<Result;
//	
//	of.close();
//}
int main()
{
	int p;
	do{
		A *pEX = NULL;
		int numtimu = 0;
		int num = 0;
		cout <<"---------------------欢迎使用！！---------------------"<<endl;
		cout << "请输入题目的个数:" << " ";
		cin >> numtimu;
		int range,answer,youanswer;
		cout<<"请输入运算数的最大范围:"<< " ";
		cin>>range;
		cout<<endl;
		int Result = 0,score=0,score1=0;
		srand((int)time(0));
		for (int i = 0; i < numtimu; i++)
		{
			pEX = new A();
			num = rand() % 3+2;//随机生成不超过3的计算数
			pEX->B(num);
			Result = pEX->C( range);
			while (Result >= range || Result <= 0)
			{
				Result = pEX->C( range);
			}	
			cout <<"题目"<<i+1<<":  ";
			pEX->Display();
			cout << " = ";
			cin>>youanswer;
			if(youanswer==Result)
				score++;
			else
				score1++;
			//cout<<endl;
			cout<<"是否输出答案(1是0否):";
			cin>>answer;
			if(answer==1)
			{
				cout<<"答案"<<i+1<< ":"<<"  "<<Result<<endl;
				//inputanswer( Result, numtimu, i);
			}
			cout << endl;
			delete pEX;
			
		}
		cout<<"Correct："<<score<<"道题"<<endl;
		cout<<"Wrong："<<score1<<"道题"<<endl;
		cout<<endl;
		cout<<"是否继续生成运算题(输入1则生成否则不生成)"<<endl;
		cin>>p;
        cout<<endl;
		system("CLS");	
	}while(p==1);
	return 0;
}
