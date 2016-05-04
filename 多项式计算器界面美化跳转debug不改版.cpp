/*����ʽ���������мӷ����������˷����󵼹��ܡ�
  ����Ϊ���ݶ���ʽ�����ҲΪ���ݶ���ʽ*/


//������ת������bugĿǰû���֣��Լ����Ű��

#include<iostream>
#include<vector>
#include<utility>
#include<windows.h>
#include<map>
#include<stdexcept>
#include<string>
#include<cmath>

using namespace std;

typedef vector<pair<int, int> > polynomial;

map<char,polynomial> p;

void Menu();
void Input();
void Show();
void Add();
void Subtract();
void Multiply();
void Derivation();
void Equal();
void Assignment();

void showMenu();
void exit_();

int one_small_letter(const string &,int,int);
int one_number(const string &,int ,int );
int getPair(const string &,char ,int &,int );
int is_show_legal(const string &,char &);
bool is_var_exist(char);
void print(const polynomial &);
int is_operation_legal(const string &,char,char &,char &,char &);
int is_derivation_legal(const string &,char &,char &,int &);
int is_equal_legal(const string &,char &,char &);
int is_assignment_legal(const string &,char &,char &);
void operation(char);
int choice();


polynomial add(const polynomial &,const polynomial &);
polynomial subtract(const polynomial &,const polynomial &);
polynomial multiply(const polynomial &,const polynomial &);
polynomial derivation(const polynomial &);

class ReturnMenu{};

/***********************/
/*  This is a menu.   */
/***********************/

void Menu()
{
	showMenu();
in:
	cout<<"  ��ѡ��";
	int t;
	string s;
	getline(cin, s);
	t = one_number(s, -1, s.size());
	if(t == -1){
		cout<<"  ������������������!"<<endl<<endl;
		goto in;
	}
    else{
        switch(s[t]){
            case '0':
                throw ReturnMenu();
                break;
            case '1':
                system("cls");
                Input();
                break;
            case '2':
                system("cls");
                Show();
                break;
            case '3':
                system("cls");
                Add();
                break;
            case '4':
                system("cls");
                Subtract();
                break;
            case '5':
                system("cls");
                Multiply();
                break;
            case '6':
                system("cls");
                Equal();
                break;
            case '7':
                system("cls");
                Derivation();
                break;
            case '8':
                system("cls");
                Assignment();
                break;
            case '9':
                exit_();
                break;
            default:
                cout<<"  ������������������!"<<endl<<endl;
                goto in;
        }
    }
}


/************************************/
/*  This is a input function        */
/*  You can input a polynomial here */
/************************************/

void Input()
{
	cout<<"  ���ö�Ԫ�����а����ݵ���ʽ����һ������ʽ"<<endl;
	cout<<"  ����3x^4+2x+5������Ϊp=(3,4)(2,1)(5,0)������pΪ����ʽ������"<<endl<<endl;
in1:
try
{
	cout<<"  �밴Ҫ���������ʽ��"<<endl;
	cout<<"  ";
	string s;
	getline(cin,s);
	/*˼·���Ȳ��� = ������Ϊ�ֽ��ߣ��жϵȺ�ǰ���Ƿ�Ϸ���ֻ��һ��Сд��ĸ��
	  �ٲ��ң����ж�= �루֮���Ƿ��Ϊ�ո�
	  ֮���ԣ�Ϊ��㣬�ԣ��룬֮�� ���룩֮������жϣ��Ƿ��зǷ������
	  ����ؼ������Ѱ�ң���֮��ķǷ����롣 */
	int begin = 0;
	char var;				//���������
	bool flag = false;		//�����û�еȺ�
	int epos = s.find('='); //Ѱ�ҵȺŵ�λ��
	if(epos != s.npos)  	//���ڵȺ�
	{
		int namePos = one_small_letter(s,-1,epos); //�жϵȺ�ǰ���Ƿ�Ϊ����Сд��ĸ
		if(namePos == -1)
			throw runtime_error("ERROR");
		else
		{
			var = s[namePos];
			flag = true;
			begin = epos + 1;
		}
	}
	polynomial v; 			//�汾�������pair��
    int x = 0,y = 0; 		//x��ϵ����y��ָ��
    for(int i = begin;i < s.size(); ++i)
    {

    	if(s[i] == '(')
        	x = getPair(s,',',i,x);
        else if(s[i] == ',')
        {
            y = getPair(s,')',i,y);
			i++;
            v.push_back(make_pair(x,y));
            x = 0;
            y = 0;
        }
		else if(s[i] == ' ')
			continue;
		else
			throw runtime_error("ERROR");
	}
	//����Ƿ������룬��ָ���Ƿ���ȷ
	for(int i = 0;i < v.size(); ++i)
	{
		if((i != v.size() - 1) && v[i].second <= v[i+1].second)
		{
			cout<<"  �밴�����������룡"<<endl;
			throw runtime_error("ERROR");
		}
		if(v[i].second < 0)
		{
			cout<<"  ��ָ������Ϊ����"<<endl;
			throw runtime_error("ERROR");
		}
	}
	if(v.empty())  throw runtime_error("ERROR");
	if(flag)	p[var] = v;
	cout<<endl<<"  �����ɹ���"<<endl<<endl;
	int c = choice();
	if(c == 1) goto in1;
	else if(c == 2) throw runtime_error("ERROR");
}
catch(runtime_error &ex)
{
in2:
	cout<<"  ��������!"<<endl<<endl;;
	int c = choice();
	if(c == 1) goto in1;
	else if(c == 2) goto in2;
}
}

/**************************************************/
/*  This is a function to show a polynomial       */
/*  or all of the polynomial that had been stored */
/**************************************************/

void Show()
{
in1:
try
{
	cout<<"  �����룺";
	string s;
	getline(cin,s);
	char var;
	int flag = is_show_legal(s,var);
	if(flag == 1)
		throw runtime_error("ERROR");
	else if(flag == 2)
	{
		if(is_var_exist(var))
		{
			cout<<"  "<<var<<" = ";
			print(p[var]);
			cout<<endl;
		}
		else
		{
			cout<<"  "<<var<<"�����ڣ�"<<endl;
			throw runtime_error("ERROR");
		}
	}
	else
	{
		for(map<char,polynomial>::iterator it = p.begin();it != p.end(); ++it)
		{
			cout<<"  "<<it->first<<" = ";
			print(it->second);
			cout<<endl;
		}
		if(p.empty())	cout<<"  �б�Ϊ�ա�"<<endl;
	}
	cout<<endl<<"  �����ɹ���"<<endl<<endl;
	int c = choice();
	if(c == 1) goto in1;
	else if(c == 2) throw runtime_error("ERROR");
}
catch(runtime_error &ex)
{
in2:
	cout<<"  ��������!"<<endl<<endl;;
	int c = choice();
	if(c == 1) goto in1;
	else if(c == 2) goto in2;
}
}

/****************************/
/*  This is a function to   */
/*  add two polynomial      */
/****************************/

void Add()
{
	operation('+');
}

/****************************/
/*  This is a function to   */
/*  subtract two polynomial */
/****************************/

void Subtract()
{
	operation('-');
}

/****************************/
/*  This is a function to   */
/*  multiply two polynomial */
/****************************/

void Multiply()
{
	operation('*');
}

/************************************/
/*  This is a function to judge     */
/*  whether two polynomial is equal */
/************************************/

void Equal()
{
in1:
try
{
	string s;
	char var1,var2;
	cout<<"  ���������жϵĵ�ʽ��"<<endl;
	cout<<"  ";
	getline(cin,s);
	int flag = is_equal_legal(s,var1,var2);
	if(flag == 1)
		throw runtime_error("ERROR");
	else
	{
		if(!is_var_exist(var1))
		{
			cout<<"  "<<var1<<"�����ڣ�"<<endl;
			throw runtime_error("ERROR");
		}
		else if(!is_var_exist(var2))
		{
			cout<<"  "<<var2<<"�����ڣ�"<<endl;
			throw runtime_error("ERROR");
		}
		else
		{
			if(p[var1].size()!=p[var2].size())
			{
				cout<<endl;
				cout<<"  false"<<endl;
				cout<<"  "<<var1<<" = ";
				print(p[var1]);
				cout<<endl;
				cout<<"  "<<var2<<" = ";
				print(p[var2]);
				cout<<endl;
			}
			else
			{
				bool comp=true;
				for(int i=0;i<p[var1].size();i++)
				{
					if(p[var1][i].first!=p[var2][i].first||p[var1][i].second!=p[var2][i].second)
					{
						comp=false;
						break;
					}
				}
				if(comp)
				  cout<<endl<<"  true"<<endl;
				else
				{
					cout<<endl;
					cout<<"  false"<<endl;
					cout<<"  "<<var1<<" = ";
					print(p[var1]);
					cout<<endl;
					cout<<"  "<<var2<<" = ";
					print(p[var2]);
					cout<<endl;
				}
			}
			cout<<endl;
		}
	}
	cout<<endl<<"  �����ɹ���"<<endl<<endl;
	int c = choice();
	if(c == 1) goto in1;
	else if(c == 2) throw runtime_error("ERROR");
}
catch(runtime_error &ex)
{
in2:
	cout<<"  ��������!"<<endl<<endl;;
	int c = choice();
	if(c == 1) goto in1;
	else if(c == 2) goto in2;
}
}



/***********************************/
/*  This is a function to find     */
/*  the derivation of a polynomial */
/***********************************/

void Derivation()
{
	operation('d');
}


/***********************************/
/*  This is a function to find     */
/*  the answer of a polynomial     */
/***********************************/

void Assignment()
{
in1:
try
{
	string s;
	char var1,var2;
	cout<<"  �������踳ֵ�ĵ�ʽ��"<<endl;
	cout<<"  ";
	getline(cin,s);
	int flag = is_assignment_legal(s,var1,var2);
	if(flag == 1)
		throw runtime_error("ERROR");
	else
	{
		double base=var2-'0';
		if(!is_var_exist(var1))
		{
			cout<<"  "<<var1<<"�����ڣ�"<<endl;
			throw runtime_error("ERROR");
		}
		else
		{
			long long sum=0;
			for(int i = 0;i < p[var1].size();i++)
			   sum+=(p[var1][i].first*pow(base,p[var1][i].second));
			cout<<"  "<<var1<<"[x="<<base<<"] = "<<sum<<endl;
		}
	}
	cout<<endl<<"  �����ɹ���"<<endl<<endl;
	int c = choice();
	if(c == 1) goto in1;
	else if(c == 2) throw runtime_error("ERROR");
}
catch(runtime_error &ex)
{
in2:
	cout<<"  ��������!"<<endl<<endl;;
	int c = choice();
	if(c == 1) goto in1;
	else if(c == 2) goto in2;
}
}




/*********************************/
/*  This is some function needed */
/*  by the function Menu         */
/*********************************/

void showMenu()
{
	system("cls");
	cout<<endl<<endl<<endl<<endl;
	cout<<'\t'<<'\t'<<'\t'<<"**********************************"<<endl;
	cout<<'\t'<<'\t'<<'\t'<<"**********************************"<<endl;
	cout<<'\t'<<'\t'<<'\t'<<"*****"<<(char)1<<"��ӭʹ�ö���ʽ������"<<(char)1<<"*******"<<endl;
	cout<<'\t'<<'\t'<<'\t'<<"***  1.����һ������ʽ          ***"<<endl;
	cout<<'\t'<<'\t'<<'\t'<<"***  2.��ʾһ����ȫ������ʽ    ***"<<endl;
	cout<<'\t'<<'\t'<<'\t'<<"***  3.��������ʽ���          ***"<<endl;
	cout<<'\t'<<'\t'<<'\t'<<"***  4.��������ʽ���          ***"<<endl;
	cout<<'\t'<<'\t'<<'\t'<<"***  5.��������ʽ���          ***"<<endl;
	cout<<'\t'<<'\t'<<'\t'<<"***  6.�ж���������ʽ�Ƿ����  ***"<<endl;
	cout<<'\t'<<'\t'<<'\t'<<"***  7.�����ʽ�ĵ���          ***"<<endl;
	cout<<'\t'<<'\t'<<'\t'<<"***  8.�����ʽ����ĳ���ֵ    ***"<<endl;
	cout<<'\t'<<'\t'<<'\t'<<"***  9.�˳�ϵͳ                ***"<<endl;
	cout<<'\t'<<'\t'<<'\t'<<"***  0.��ʾ�˵�                ***"<<endl;
	cout<<'\t'<<'\t'<<'\t'<<"**********************************"<<endl;
	cout<<'\t'<<'\t'<<'\t'<<"**********************************"<<endl;
}

void exit_()
{
	system("cls");
	cout<<endl<<endl<<endl<<endl;
	cout<<'\t'<<'\t'<<'\t'<<(char)1<<(char)1<<(char)1<<(char)1<<(char)1<<"��л����ʹ�ã�"<<(char)1<<(char)1<<(char)1<<(char)1<<(char)1<<endl;
	cout<<endl<<endl<<endl<<endl;
	exit(0);
}

/************************************/
/*  This is some function to detect */
/*  whether the input is legal      */
/************************************/

//�жϣ�begin��end�����Ƿ�ֻ����һ��Сд��ĸ,���򷵻�λ�ã����򷵻�-1
int one_small_letter(const string & s,int begin,int end)
{
	for(int i = begin + 1;i < end; ++i)
	{
		if(s[i] != ' ' && (s[i] < 'a' || s[i] > 'z'))
		   return -1;
		else if(s[i] >= 'a' && s[i] <= 'z')
		{
			for(int k = i + 1;k < end; ++k)
				if(s[k] != ' ')
		   		   return -1;
			return i;
		}
	}
}

//�жϣ�begin��end�����Ƿ�ֻ����һ������
int one_number(const string & s,int begin,int end)
{
	for(int i = begin + 1;i < end; ++i)
	{
		if(s[i] != ' ' && (s[i] < '0' || s[i] > '9'))
		   return -1;
		else if(s[i] >= '0' && s[i] <= '9')
		{
			for(int k = i + 1;k < end; ++k)
				if(s[k] != ' ')
		   		   return -1;
			return i;
		}
	}
}

//����жϣ��룬֮��ķǷ�����
int getPair(const string &s,char ch,int &i,int xy)
{
	while(s[i + 1] == ' ') i++;
	if(s[i + 1] != '-' && s[i + 1] != '+' && (s[i + 1] < '0'||s[i + 1] > '9') )
		throw runtime_error("ERROR");
    if(s[i + 1] == '-')
    {
        i++;
        while(s[i + 1] != ch)
        {
            if(s[i + 1] == ' ')
            {
                i++;
				continue;
            }
            else if(s[i + 1] < '0'||s[i + 1] > '9')
				throw runtime_error("ERROR");
            xy = xy*10 + s[i + 1] - '0';
            i++;
        }
        xy = -xy;
    }
    else
    {
        while(s[i + 1] != ch )
        {
            if(s[i + 1] == ' ')
            {
                i++;
				continue;
            }
            else if(s[i + 1] < '0'||s[i + 1] > '9')
				throw runtime_error("ERROR");
            xy = xy*10 + s[i + 1] - '0';
            i++;
        }
    }
	return xy;
}

int is_show_legal(const string &s,char &var)	//�ж���ʾ�����������Ƿ�Ϸ�
{
	int judge = one_small_letter(s,-1,s.size());
	if(judge != -1)
	{
		var = s[judge];	//�ҵ�����Сд��ĸ������2
		return 2;
	}
	else
	{
		int pos = s.find("all");
		if(pos == s.npos)			//���Ϸ�������1
		  return 1;
		else
		{
			for(int i = 0;i < pos; ++i)
			{
				if(s[i] != ' ' && (s[i] < 'a' || s[i] > 'z'))
		     	  return 1;
			}
			for(int i=pos+3;i<s.size();i++)
			{
				if(s[i]!=' '&&(s[i]<'a'||s[i]>'z'))
		     	  return 1;
			}
			return 3;		//�ҵ�all������3
		}
	}
}

bool is_var_exist(char var)	//�жϱ����Ƿ����
{
	for(map<char,polynomial>::iterator it = p.begin();it != p.end(); ++it)
	{
		if(it->first == var)
			return true;
	}
	return false;
}

//���,�����˲������ҳ�����������1��������󡣷���2����������������3������������
int is_operation_legal(const string &s,char ch,char &var1,char &var2,char &var3)
{
	int equal,op;
	equal = s.find('=');
	op = s.find(ch);
	if(op == s.npos)	//�Ҳ�����Ӧ������
	  return 1;
	else if(equal == s.npos)
	{
		int judge1,judge2;
		judge1 = one_small_letter(s,-1,op);
		judge2 = one_small_letter(s,op,s.size());
		if(judge1 != -1)
		  var2 = s[judge1];
		else
		  return 1;
		if(judge2 != -1)
		  var3 = s[judge2];
		else
		  return 1;
		return 2;
	}
	else
	{
		int judge1,judge2,judge3;
		judge1 = one_small_letter(s,equal,op);
		judge2 = one_small_letter(s,op,s.size());
		judge3 = one_small_letter(s,-1,equal);
		if(judge1 != -1)
		  var2 = s[judge1];
		else
		  return 1;
		if(judge2 != -1)
		  var3 = s[judge2];
		else
		  return 1;
		if(judge3 != -1)
		  var1 = s[judge3];
		else
		  return 1;
		return 3;
	}
}

int is_equal_legal(const string & s,char & var1,char & var2)//�жϵ��������Ƿ�Ϸ�
{
	int equal = s.find("==");
	if(equal == s.npos)
	  return 1;
	else
	{
		int judge1,judge2;
		judge1 = one_small_letter(s,-1,equal);
		judge2 = one_small_letter(s,equal + 1,s.size());
		if(judge1 != -1)
		  var1 = s[judge1];
		else
		  return 1;
		if(judge2 != -1)
		  var2 = s[judge2];
		else
		  return 1;
		return 2;
	}
}

int is_assignment_legal(const string & s,char & var1,char & var2)//�жϸ�ֵ�����Ƿ�Ϸ�
{
	int left = s.find("[");
	int right = s.find("]");
	int equal = s.find("=");
	if(equal == s.npos||left == s.npos||right == s.npos)
	  return 1;
	else
	{
		int judge1,judge2,judge3;
		judge1 = one_small_letter(s,-1,left);
		judge2 = one_small_letter(s,left,equal);
		judge3 = one_number(s,equal,right);
		if(judge1 != -1)
		  var1 = s[judge1];
		else
		  return 1;
		if(judge2 == -1)
		  return 1;
		if(judge2 != -1)
		  var2 = s[judge3];
		else
		  return 1;
		for(int i = right + 1;i < s.size();i++)
		{
			if(s[i]!=' ')
			  return 1;
		}
		return 2;
	}
}





//�󵼲��������Ҳ����������벻�Ϸ�����1��ֻ��һ����������2��������������3
int is_derivation_legal(const string &s,char &var1,char &var2,int &num_of_quote)
{
	int equal,quote;
	equal = s.find('=');
	quote = s.find('\'');
	if(quote == s.npos) //û���ҵ��󵼷���
		return 1;
	else 				//�ҵ��󵼷���
	{
		if(equal == s.npos)	//û���ҵ��Ⱥ�
		{
			int pos = one_small_letter(s,-1,quote);
			if(pos == -1)	return 1;	//û���ҵ���ĸ
			else
			{
				var2 = s[pos];
				num_of_quote ++;
				for(int i = quote + 1;i < s.size(); ++i)
				{
					if(s[i] != '\'' && s[i] != ' ') return 1;
					else if(s[i] == '\'')
					{
						num_of_quote ++;
					}
				}
				return 2;
			}
		}
		else				//�ҵ��Ⱥ�
		{
			int pos1,pos2;
			pos1 = one_small_letter(s,-1,equal);
			pos2 = one_small_letter(s,equal,quote);
			if(pos1 != -1)
			  var1 = s[pos1];
			else
			  return 1;
			if(pos2 != -1)
			  var2 = s[pos2];
			else
			  return 1;
			num_of_quote ++;
			for(int i = quote + 1;i < s.size(); ++i)
			{
				if(s[i] != '\'' && s[i] != ' ') return 1;
				else if(s[i] == '\'')
				{
					num_of_quote ++;
				}
			}
			return 3;
		}
	}
}

/********************************/
/*  This is a function to print */
/*  a polynomial                */
/********************************/

//����ת��Ϊ����ʽ��ʾ
void print(const polynomial &ans)
{
	bool flag = false;
	for(int i = 0;i < ans.size(); i++)
    {
    	if(flag && ans[i].first > 0)
		{
			cout<<'+';	//�Ӽ���
			flag = true;
		}
		if(ans[i].first != 0) 	//ϵ��Ϊ0ʱ�������ӡ
		{
			if(ans[i].second != 0)	//������Ϊ0����ʾx
			{
				if(ans[i].first != 1) cout<<ans[i].first;	//ϵ��Ϊ1ʱ����ӡ
				if(ans[i].second == 1) cout<<'x';	//����Ϊ1
				else cout<<"x^"<<ans[i].second;	//������Ϊ1
			}
			else //����Ϊ0������ʾx
				cout<<ans[i].first;
			flag = true;
		}
    }
    if(!flag) cout<<'0';
}

/*************************************/
/*  This is some opetation function  */
/*************************************/

//����ʽ�ӷ�
polynomial add(const polynomial &p1,const polynomial &p2) //���ƹ鲢����ļӷ�
{
        polynomial ans;
        int i1 = 0,i2 = 0;
        while(i1 != p1.size() && i2 != p2.size() )
        {
        	if(p1[i1].second == p2[i2].second)    //���������ͬ�����
        	{
                ans.push_back(make_pair(p1[i1].first+p2[i2].first,p1[i1].second));
                i1++;
                i2++;
        	}
         	else if(p1[i1].second > p2[i2].second)   ans.push_back(p1[i1++]);
         	else	ans.push_back(p2[i2++]);
        }
        while(i1 != p1.size())	ans.push_back(p1[i1++]);
        while(i2 != p2.size())	ans.push_back(p2[i2++]);
        return ans;
}

//����ʽ����
polynomial subtract(const polynomial &p1,const polynomial &p2)
{
        polynomial ans;
        polynomial tmp;
        for(int i = 0;i < p2.size(); ++i)
			tmp.push_back(make_pair(-p2[i].first,p2[i].second));
        ans = add(p1,tmp);
        return ans;
}

//����ʽ�˷�
polynomial multiply(const polynomial &p1,const polynomial &p2)
{
	polynomial ans;
	for(int i = 0;i < p1.size(); ++i)
	{
		polynomial x;
		for(int j = 0;j < p2.size(); ++j)	//��һ������ʽÿһ�����˵ڶ�������ʽȻ�����
			x.push_back(make_pair(p1[i].first * p2[j].first , p1[i].second + p2[j].second));
		ans = add(ans,x);		//�����Ѿ�д�õļӷ���ʵ�ֳ˷�
	}
	return ans;
}

void operation(char ch)
{
in1:
try
{
	cout<<"  ����ִ��������ǣ�";
	if(ch == '+')		cout<<"�ӷ�";
	else if(ch == '-')	cout<<"����";
	else if(ch == '*')  cout<<"�˷�";
	else			 	cout<<"��";
	cout<<endl<<"  �����룺";
	string s;
	getline(cin,s);
	char var1,var2,var3;
	int num_of_quote = 0;
	int flag = 0;
	if(ch == 'd')	flag = is_derivation_legal(s,var2,var3,num_of_quote);
	else flag = is_operation_legal(s,ch,var1,var2,var3);
	if(flag == 1)
		throw runtime_error("ERROR");
	else if(flag == 2)
	{
		if(ch == 'd')		//��
		{
			if(!is_var_exist(var3))
			{
				cout<<"  "<<var3<<"�����ڣ�"<<endl;
				throw runtime_error("ERROR");
			}
			else
			{
				cout<<"  ans��";
				polynomial ans = p[var3];
				for(int i = 0;i < num_of_quote; ++i)
				{
					ans = derivation(ans);
				}
				print(ans);
				cout<<endl;
			}
		}
		else
		{
			if(!is_var_exist(var2))
			{
				cout<<"  "<<var2<<"�����ڣ�"<<endl;
				throw runtime_error("ERROR");
			}
			else if(!is_var_exist(var3))
			{
				cout<<"  "<<var3<<"�����ڣ�"<<endl;
				throw runtime_error("ERROR");
			}
			else
			{
				cout<<"  ans��";
				if(ch =='+')		print(add(p[var2],p[var3]));
				else if(ch =='-')	print(subtract(p[var2],p[var3]));
				else 				print(multiply(p[var2],p[var3]));
				cout<<endl;
			}
		}

	}
	else if(flag == 3)
	{
		if(ch == 'd')		//��
		{
			if(!is_var_exist(var3))
			{
				cout<<"  "<<var3<<"�����ڣ�"<<endl;
				throw runtime_error("ERROR");
			}
			else
			{

				cout<<"  ans��";
				p[var2] = p[var3];
				for(int i = 0;i < num_of_quote; ++i)
				{
					p[var2] = derivation(p[var2]);
				}
				print(p[var2]);
				cout<<endl;
			}
		}
		else
		{
			if(!is_var_exist(var2))
			{
				cout<<"  "<<var2<<"�����ڣ�"<<endl;
				throw runtime_error("ERROR");
			}
			else if(!is_var_exist(var3))
			{
				cout<<"  "<<var3<<"�����ڣ�"<<endl;
				throw runtime_error("ERROR");
			}
			else
			{
				cout<<"  ans��";
				if(ch =='+')		p[var1] = add(p[var2],p[var3]);
				else if(ch =='-')	p[var1] = subtract(p[var2],p[var3]);
				else 				p[var1] = multiply(p[var2],p[var3]);
				print(p[var1]);
				cout<<endl;
			}
		}
	}
	cout<<endl<<"  �����ɹ���"<<endl<<endl;
	int c = choice();
	if(c == 1) goto in1;
	else if(c == 2) throw runtime_error("ERROR");
}
catch(runtime_error &ex)
{
in2:
	cout<<"  ��������!"<<endl<<endl;
	int c = choice();
	if(c == 1) goto in1;
	else if(c == 2) goto in2;
}

}

int choice()
{
	cout<<"  ��ѡ��  0.�������˵�"<<endl;
	cout<<"            1.��������ʽ��  "<<endl;
	cout<<"  ";
	int t;
	string ss;
	getline(cin,ss);
	t = one_number(ss,-1,ss.size());
	if(t == -1)
		return 2;//goto in2;
	else
	{
		if(ss[t] == '0')
			throw ReturnMenu();
		else if(ss[t] == '1')
		    return 1;//goto in1;
		else
		    return 2;//goto in2;
	}
}



//����ʽ��
polynomial derivation(const polynomial & v)
{
	polynomial result;
	for(int i = 0;i < v.size();i++)
		if(v[i].second != 0)
			result.push_back(make_pair(v[i].first*v[i].second,v[i].second-1));
	return result;
}

int main()
{
retn:
	try
	{
		Menu();
	}
	catch(ReturnMenu &ex)
	{
		goto retn;
	}
    return 0;
}
