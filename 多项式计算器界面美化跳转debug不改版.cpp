/*多项式计算器，有加法、减法、乘法、求导功能。
  输入为降幂多项式，输出也为降幂多项式*/


//界面跳转流畅，bug目前没发现，自己看着办吧

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
	cout<<"  请选择：";
	int t;
	string s;
	getline(cin, s);
	t = one_number(s, -1, s.size());
	if(t == -1){
		cout<<"  输入有误！请重新输入!"<<endl<<endl;
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
                cout<<"  输入有误！请重新输入!"<<endl<<endl;
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
	cout<<"  请用二元组序列按降幂的形式输入一个多项式"<<endl;
	cout<<"  比如3x^4+2x+5的输入为p=(3,4)(2,1)(5,0)，其中p为多项式的名称"<<endl<<endl;
in1:
try
{
	cout<<"  请按要求输入多项式："<<endl;
	cout<<"  ";
	string s;
	getline(cin,s);
	/*思路：先查找 = ，以它为分界线，判断等号前面是否合法（只有一个小写字母）
	  再查找（，判断= 与（之间是否均为空格。
	  之后以（为起点，对（与，之间 ，与）之间进行判断，是否有非法情况。
	  问题关键：如何寻找（）之间的非法输入。 */
	int begin = 0;
	char var;				//储存变量名
	bool flag = false;		//标记有没有等号
	int epos = s.find('='); //寻找等号的位置
	if(epos != s.npos)  	//存在等号
	{
		int namePos = one_small_letter(s,-1,epos); //判断等号前面是否为单个小写字母
		if(namePos == -1)
			throw runtime_error("ERROR");
		else
		{
			var = s[namePos];
			flag = true;
			begin = epos + 1;
		}
	}
	polynomial v; 			//存本组变量的pair对
    int x = 0,y = 0; 		//x存系数，y存指数
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
	//检查是否降幂输入，幂指数是否正确
	for(int i = 0;i < v.size(); ++i)
	{
		if((i != v.size() - 1) && v[i].second <= v[i+1].second)
		{
			cout<<"  请按降幂排序输入！"<<endl;
			throw runtime_error("ERROR");
		}
		if(v[i].second < 0)
		{
			cout<<"  幂指数不能为负！"<<endl;
			throw runtime_error("ERROR");
		}
	}
	if(v.empty())  throw runtime_error("ERROR");
	if(flag)	p[var] = v;
	cout<<endl<<"  操作成功！"<<endl<<endl;
	int c = choice();
	if(c == 1) goto in1;
	else if(c == 2) throw runtime_error("ERROR");
}
catch(runtime_error &ex)
{
in2:
	cout<<"  输入有误!"<<endl<<endl;;
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
	cout<<"  请输入：";
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
			cout<<"  "<<var<<"不存在！"<<endl;
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
		if(p.empty())	cout<<"  列表为空。"<<endl;
	}
	cout<<endl<<"  操作成功！"<<endl<<endl;
	int c = choice();
	if(c == 1) goto in1;
	else if(c == 2) throw runtime_error("ERROR");
}
catch(runtime_error &ex)
{
in2:
	cout<<"  输入有误!"<<endl<<endl;;
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
	cout<<"  请输入需判断的等式："<<endl;
	cout<<"  ";
	getline(cin,s);
	int flag = is_equal_legal(s,var1,var2);
	if(flag == 1)
		throw runtime_error("ERROR");
	else
	{
		if(!is_var_exist(var1))
		{
			cout<<"  "<<var1<<"不存在！"<<endl;
			throw runtime_error("ERROR");
		}
		else if(!is_var_exist(var2))
		{
			cout<<"  "<<var2<<"不存在！"<<endl;
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
	cout<<endl<<"  操作成功！"<<endl<<endl;
	int c = choice();
	if(c == 1) goto in1;
	else if(c == 2) throw runtime_error("ERROR");
}
catch(runtime_error &ex)
{
in2:
	cout<<"  输入有误!"<<endl<<endl;;
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
	cout<<"  请输入需赋值的等式："<<endl;
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
			cout<<"  "<<var1<<"不存在！"<<endl;
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
	cout<<endl<<"  操作成功！"<<endl<<endl;
	int c = choice();
	if(c == 1) goto in1;
	else if(c == 2) throw runtime_error("ERROR");
}
catch(runtime_error &ex)
{
in2:
	cout<<"  输入有误!"<<endl<<endl;;
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
	cout<<'\t'<<'\t'<<'\t'<<"*****"<<(char)1<<"欢迎使用多项式计算器"<<(char)1<<"*******"<<endl;
	cout<<'\t'<<'\t'<<'\t'<<"***  1.输入一个多项式          ***"<<endl;
	cout<<'\t'<<'\t'<<'\t'<<"***  2.显示一个或全部多项式    ***"<<endl;
	cout<<'\t'<<'\t'<<'\t'<<"***  3.两个多项式相加          ***"<<endl;
	cout<<'\t'<<'\t'<<'\t'<<"***  4.两个多项式相减          ***"<<endl;
	cout<<'\t'<<'\t'<<'\t'<<"***  5.两个多项式相乘          ***"<<endl;
	cout<<'\t'<<'\t'<<'\t'<<"***  6.判断两个多项式是否相等  ***"<<endl;
	cout<<'\t'<<'\t'<<'\t'<<"***  7.求多项式的导数          ***"<<endl;
	cout<<'\t'<<'\t'<<'\t'<<"***  8.求多项式代入某点的值    ***"<<endl;
	cout<<'\t'<<'\t'<<'\t'<<"***  9.退出系统                ***"<<endl;
	cout<<'\t'<<'\t'<<'\t'<<"***  0.显示菜单                ***"<<endl;
	cout<<'\t'<<'\t'<<'\t'<<"**********************************"<<endl;
	cout<<'\t'<<'\t'<<'\t'<<"**********************************"<<endl;
}

void exit_()
{
	system("cls");
	cout<<endl<<endl<<endl<<endl;
	cout<<'\t'<<'\t'<<'\t'<<(char)1<<(char)1<<(char)1<<(char)1<<(char)1<<"感谢您的使用！"<<(char)1<<(char)1<<(char)1<<(char)1<<(char)1<<endl;
	cout<<endl<<endl<<endl<<endl;
	exit(0);
}

/************************************/
/*  This is some function to detect */
/*  whether the input is legal      */
/************************************/

//判断（begin，end）间是否只存在一个小写字母,是则返回位置，否则返回-1
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

//判断（begin，end）间是否只存在一个数字
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

//如何判断（与，之间的非法输入
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

int is_show_legal(const string &s,char &var)	//判断显示函数的输入是否合法
{
	int judge = one_small_letter(s,-1,s.size());
	if(judge != -1)
	{
		var = s[judge];	//找到单个小写字母，返回2
		return 2;
	}
	else
	{
		int pos = s.find("all");
		if(pos == s.npos)			//不合法，返回1
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
			return 3;		//找到all，返回3
		}
	}
}

bool is_var_exist(char var)	//判断变量是否存在
{
	for(map<char,polynomial>::iterator it = p.begin();it != p.end(); ++it)
	{
		if(it->first == var)
			return true;
	}
	return false;
}

//相加,减，乘操作，找出参数。返回1：输入错误。返回2，两个参数。返回3，三个参数。
int is_operation_legal(const string &s,char ch,char &var1,char &var2,char &var3)
{
	int equal,op;
	equal = s.find('=');
	op = s.find(ch);
	if(op == s.npos)	//找不到相应操作符
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

int is_equal_legal(const string & s,char & var1,char & var2)//判断等于输入是否合法
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

int is_assignment_legal(const string & s,char & var1,char & var2)//判断赋值输入是否合法
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





//求导操作，查找参数。若输入不合法返回1，只有一个参数返回2，两个参数返回3
int is_derivation_legal(const string &s,char &var1,char &var2,int &num_of_quote)
{
	int equal,quote;
	equal = s.find('=');
	quote = s.find('\'');
	if(quote == s.npos) //没有找到求导符号
		return 1;
	else 				//找到求导符号
	{
		if(equal == s.npos)	//没有找到等号
		{
			int pos = one_small_letter(s,-1,quote);
			if(pos == -1)	return 1;	//没有找到字母
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
		else				//找到等号
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

//数对转换为多项式显示
void print(const polynomial &ans)
{
	bool flag = false;
	for(int i = 0;i < ans.size(); i++)
    {
    	if(flag && ans[i].first > 0)
		{
			cout<<'+';	//加减号
			flag = true;
		}
		if(ans[i].first != 0) 	//系数为0时，无需打印
		{
			if(ans[i].second != 0)	//次数不为0，显示x
			{
				if(ans[i].first != 1) cout<<ans[i].first;	//系数为1时不打印
				if(ans[i].second == 1) cout<<'x';	//次数为1
				else cout<<"x^"<<ans[i].second;	//次数不为1
			}
			else //次数为0，不显示x
				cout<<ans[i].first;
			flag = true;
		}
    }
    if(!flag) cout<<'0';
}

/*************************************/
/*  This is some opetation function  */
/*************************************/

//多项式加法
polynomial add(const polynomial &p1,const polynomial &p2) //类似归并排序的加法
{
        polynomial ans;
        int i1 = 0,i2 = 0;
        while(i1 != p1.size() && i2 != p2.size() )
        {
        	if(p1[i1].second == p2[i2].second)    //如果次数相同，相加
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

//多项式减法
polynomial subtract(const polynomial &p1,const polynomial &p2)
{
        polynomial ans;
        polynomial tmp;
        for(int i = 0;i < p2.size(); ++i)
			tmp.push_back(make_pair(-p2[i].first,p2[i].second));
        ans = add(p1,tmp);
        return ans;
}

//多项式乘法
polynomial multiply(const polynomial &p1,const polynomial &p2)
{
	polynomial ans;
	for(int i = 0;i < p1.size(); ++i)
	{
		polynomial x;
		for(int j = 0;j < p2.size(); ++j)	//第一个多项式每一项来乘第二个多项式然后相加
			x.push_back(make_pair(p1[i].first * p2[j].first , p1[i].second + p2[j].second));
		ans = add(ans,x);		//利用已经写好的加法来实现乘法
	}
	return ans;
}

void operation(char ch)
{
in1:
try
{
	cout<<"  现在执行运算的是：";
	if(ch == '+')		cout<<"加法";
	else if(ch == '-')	cout<<"减法";
	else if(ch == '*')  cout<<"乘法";
	else			 	cout<<"求导";
	cout<<endl<<"  请输入：";
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
		if(ch == 'd')		//求导
		{
			if(!is_var_exist(var3))
			{
				cout<<"  "<<var3<<"不存在！"<<endl;
				throw runtime_error("ERROR");
			}
			else
			{
				cout<<"  ans：";
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
				cout<<"  "<<var2<<"不存在！"<<endl;
				throw runtime_error("ERROR");
			}
			else if(!is_var_exist(var3))
			{
				cout<<"  "<<var3<<"不存在！"<<endl;
				throw runtime_error("ERROR");
			}
			else
			{
				cout<<"  ans：";
				if(ch =='+')		print(add(p[var2],p[var3]));
				else if(ch =='-')	print(subtract(p[var2],p[var3]));
				else 				print(multiply(p[var2],p[var3]));
				cout<<endl;
			}
		}

	}
	else if(flag == 3)
	{
		if(ch == 'd')		//求导
		{
			if(!is_var_exist(var3))
			{
				cout<<"  "<<var3<<"不存在！"<<endl;
				throw runtime_error("ERROR");
			}
			else
			{

				cout<<"  ans：";
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
				cout<<"  "<<var2<<"不存在！"<<endl;
				throw runtime_error("ERROR");
			}
			else if(!is_var_exist(var3))
			{
				cout<<"  "<<var3<<"不存在！"<<endl;
				throw runtime_error("ERROR");
			}
			else
			{
				cout<<"  ans：";
				if(ch =='+')		p[var1] = add(p[var2],p[var3]);
				else if(ch =='-')	p[var1] = subtract(p[var2],p[var3]);
				else 				p[var1] = multiply(p[var2],p[var3]);
				print(p[var1]);
				cout<<endl;
			}
		}
	}
	cout<<endl<<"  操作成功！"<<endl<<endl;
	int c = choice();
	if(c == 1) goto in1;
	else if(c == 2) throw runtime_error("ERROR");
}
catch(runtime_error &ex)
{
in2:
	cout<<"  输入有误!"<<endl<<endl;
	int c = choice();
	if(c == 1) goto in1;
	else if(c == 2) goto in2;
}

}

int choice()
{
	cout<<"  请选择：  0.返回主菜单"<<endl;
	cout<<"            1.重新输入式子  "<<endl;
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



//多项式求导
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
