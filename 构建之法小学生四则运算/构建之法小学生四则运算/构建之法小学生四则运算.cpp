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
	// �Ƚ�����������ȼ�
	bool ChoiceIsHigher();
	// �õ��������Ȩֵ
	int Getyunsuanfuqz(const char oper);

private:
	int Result;
	// ���ʽ�Ľ��
	char oper;
	// ���ʽ�������
	A *lhs;
	// ���ʽ����ڵ�
	A *rhs;
	// ���ʽ���ҽڵ�
	bool isEX;
	// �ñ��ʽ�Ƿ�Ϊ���յı��ʽ
	A *Parent;
	// ���ʽ�ĸ��ڵ�
	bool isLeft;
	// �Ƿ�Ϊ��ڵ�(Ϊ������Ǽ�������)
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

A::~A()//������������������ɨβ
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
// ���ɺ���num���������ֵ�������ʽ
void A::B(int num)
{
	if ( num==1 )
	{
		return ;
	}
	else
	{
		int fuhao = rand() % 4;//�������0-3�����������Ӧ������������ŵ��±�
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
int A::C(int range)// �����ɵı��ʽ�������������������������
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
			if (Result < 0)//��ֹ������Ϊ����
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
	else//����û�����������ķ�Χ�������ΧΪ0����
	{
		Result = rand() % range;
		while (Result == 0)
		{
			Result = rand() % range;
		}
	}
	return Result;
}
void A::Display()// ��������ɵı��ʽ
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
//	of<<"��"<<i<<":"<<" "<<Result;
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
		cout <<"---------------------��ӭʹ�ã���---------------------"<<endl;
		cout << "��������Ŀ�ĸ���:" << " ";
		cin >> numtimu;
		int range,answer,youanswer;
		cout<<"�����������������Χ:"<< " ";
		cin>>range;
		cout<<endl;
		int Result = 0,score=0,score1=0;
		srand((int)time(0));
		for (int i = 0; i < numtimu; i++)
		{
			pEX = new A();
			num = rand() % 3+2;//������ɲ�����3�ļ�����
			pEX->B(num);
			Result = pEX->C( range);
			while (Result >= range || Result <= 0)
			{
				Result = pEX->C( range);
			}	
			cout <<"��Ŀ"<<i+1<<":  ";
			pEX->Display();
			cout << " = ";
			cin>>youanswer;
			if(youanswer==Result)
				score++;
			else
				score1++;
			//cout<<endl;
			cout<<"�Ƿ������(1��0��):";
			cin>>answer;
			if(answer==1)
			{
				cout<<"��"<<i+1<< ":"<<"  "<<Result<<endl;
				//inputanswer( Result, numtimu, i);
			}
			cout << endl;
			delete pEX;
			
		}
		cout<<"Correct��"<<score<<"����"<<endl;
		cout<<"Wrong��"<<score1<<"����"<<endl;
		cout<<endl;
		cout<<"�Ƿ��������������(����1�����ɷ�������)"<<endl;
		cin>>p;
        cout<<endl;
		system("CLS");	
	}while(p==1);
	return 0;
}
