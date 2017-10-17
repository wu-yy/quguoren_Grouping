#include<iostream> 
#include<vector>
#include<map>
#include<fstream>
#include<stdio.h>
#include<string>
#include<set>


using namespace std;

#define N 12   //这里的N是外国人或者中国人的数量 
//其中 1-N 代表中国人  N+1-2N 代表外国人 
int form[N+1][N+1];
int Result[2*N+1];
vector< vector<int> > findFriends;
void insertVector(int A1,int A2)
{
	bool find=false;
	for(int i=0;i<findFriends.size();i++)
	{ 
		
		for(int j=0;j<findFriends[i].size();j++)
		{
			if(findFriends[i][j]==A1)
			{
				find=true;
				bool find2=false;
				for(int k=0;k<findFriends[i].size();k++)
				{
					if(A2+N ==findFriends[i][k])
					{
						find2=true;
						break;
					}
				}
				if(!find2)
				{
					findFriends[i].push_back(A2+N);
				}
				break;
			}

			else if(findFriends[i][j]==A2+N)
			{
				find=true;
				bool find2=false;
				for(int k=0;k<findFriends[i].size();k++)
				{
					if(A1==findFriends[i][k])
					{
						find2=true;
						break;
					}
				}
				if(!find2)
				{
					findFriends[i].push_back(A1);
				}
				break;
			}
		}

		if(find)
		{
			break;
		}

	}


	if(!find) //如果没有在这个vector里面发现
	{
		vector<int>AA;
		AA.push_back(A1);
		AA.push_back(A2+N);
		findFriends.push_back(AA);
	}
}

bool equalVector(vector<int> a,vector<int> b)
{
	for(int i=0;i<a.size();i++)
	{

		for(int j=0;j<b.size();j++)
		{
			if(a[i]==b[j])
			{
				return true;
			}
		}
	}
	return false;
}
//
vector<vector<int>> findVector;
void insertVector2(int A1,int A2)  //此处对于大规模的插入可能存在系统bug
{
	bool find=false;
	for(int i=0;i<findVector.size();i++)
	{ 
		
		for(int j=0;j<findVector[i].size();j++)
		{
			if(findVector[i][j]==A1)
			{
				find=true;
				bool find2=false;
				for(int k=0;k<findVector[i].size();k++)
				{
					if(A2 ==findVector[i][k])
					{
						find2=true;
						break;
					}
				}
				if(!find2)
				{
					findVector[i].push_back(A2);
				}
				break;
			}

			else if(findVector[i][j]==A2)
			{
				find=true;
				bool find2=false;
				for(int k=0;k<findVector[i].size();k++)
				{
					if(A1==findVector[i][k])
					{
						find2=true;
						break;
					}
				}
				if(!find2)
				{
					findVector[i].push_back(A1);
				}
				break;
			}
		}

		if(find)
		{
			break;
		}

	}


	if(!find) //如果没有在这个vector里面发现
	{
		vector<int>AA;
		AA.push_back(A1);
		AA.push_back(A2);
		findVector.push_back(AA);
	}
}

//第三次更新、修复bug
vector<set<int>>  Friends2;

struct pair_my
{
	int i;
	int j;

};
void check3()
{
	int finddata[10000];
	memset(finddata,1,sizeof(finddata));
	int len=findFriends.size();
	int dd[1000];
	pair_my pai[1000];
	int incre=0;
	memset(dd,0,sizeof(dd));
	for(int i=0;i<len-1;i++)
	{
		for(int j=i+1; j<len;j++)
		{
			if(i!=j && equalVector(findFriends[i],findFriends[j])) //发现相同的元素
			{
				cout<<"发现重复的元素组号："<<i<<" "<<j<<endl;
				//insertVector2(i,j); //这里是插入的index的数值
				pai[incre].i=i;
				pai[incre].j=j;
				incre++;
				dd[i]++;
				dd[j]++;
				finddata[i]=0;
				finddata[j]=0;
			}

		}

	}
	int max=-1;
	int max_index=-1;
	int dow=0;
	int dowe[1000];
	int dota[1000];
	memset(dota,0,sizeof(dota));
	memset(dowe,0,sizeof(dowe));
	while(dow<incre)  //采用的穿插的算法
	{
		max=-1;
		for(int i=0;i<len;i++)
		{
			if(dd[i]>=max&&dowe[i]==0)
			{
				max=dd[i];
				max_index=i;
				dowe[i]=1;
			}

		}
		for(int k=0;k<incre;k++)
		{
			if(dota[k]==0)
			{
				if(pai[k].i==max_index||pai[k].j==max_index)
				{
					insertVector2(pai[k].i,pai[k].j);
					dota[k]=1;
				}

			}
		}
		
		dow++;

	}



	for(int i=0;i<findVector.size();i++)
	{
		cout<<"队员有重复的组号：";
		set<int> temp;
		for(int j=0;j<findVector[i].size();j++)
		{
			cout<<findVector[i][j]<<" ";   //输出重复的组号
			for(int h=0;h<findFriends[findVector[i][j]].size();h++)
				temp.insert(findFriends[findVector[i][j]][h]);
			
		}
		Friends2.push_back(temp);
		cout<<endl;
	}
	for(int i=0;i<findFriends.size();i++)
	{
		if(finddata[i]==1)
		{
			set<int>temp;
			for(int h=0;h<findFriends[i].size();h++)
			{
				temp.insert(findFriends[i][h]);
			}

			Friends2.push_back(temp);
		}
	}

	memset(Result,0,sizeof(Result));
	for(int i=0;i<Friends2.size();i++)
	{
		cout<<"重新第二次分组："<<endl;
		for(set<int>::iterator it=Friends2[i].begin();it!=Friends2[i].end();it++)
		{
			Result[*it]=1;
			//cout<<*it<<" ";
			if(*it<=N)
			{	cout<<*it<<"  ";
				//outfile<<findFriends[i][j]<<"  ";
			}else
			{
				cout<<char(*it-N+64)<<"  ";
				//outfile<<char(findFriends[i][j]-N+64)<<"  ";
			}
		}
		cout<<"\n 分组结束\n";
	}
	cout<<"没有分组成功同学：\n";
	for(int i=1;i<=2*N;i++)
	{
		if(Result[i]==0)
		{
			if(i<=N)
			{	cout<<i<<"  ";
				//outfile<<findFriends[i][j]<<"  ";
			}else
			{
				cout<<char(i-N+64)<<"  ";
				//outfile<<char(findFriends[i][j]-N+64)<<"  ";
			}

		}

	}
	cout<<endl;


}

//暂时没用
void check2()
{
	vector<vector<int>> temp;
	for(vector<vector<int>>::iterator it=findFriends.begin(); it!=findFriends.end(); ){
		if((* it).size() == 2) {
			temp.push_back(*it);
			it = findFriends.erase(it);
			}
			else {
				++it;
			}
	}
	for(auto i=temp.begin();i!=temp.end();i++)
	{
		insertVector((*i)[0],(*i)[1]-N);

	}


}


void test()
{
	vector<int> test;
	vector<int> test2;
	test.push_back(1);
	test.push_back(2);
	test.push_back(3);
	test2.push_back(2);
	test2.push_back(4);
	set<int> my;
	my.insert(2);
	my.insert(2);

	for(set<int>::iterator it=my.begin();it!=my.end();it++)
	{
		cout<<"set数据："<<*it<<endl;
	}
	int num;
		for(vector<int>::iterator it=test2.begin();it!=test2.end();it++)
		{
			for(vector<int>::iterator itt=test.begin();itt!=test.end();itt++)
			{
				if(*it==*itt)
				{
					test.push_back(4);
					cout<<"find"<<endl;
					break;
				}
			}
		}



}
int main()
{
	
	
	cout<< "这里设置的中国人为"<<N<<"，外国人最大数目为"<<N<<"。 如果想要更换最大数目，请重新编译执行\n\n";
	memset(form,0,sizeof(form));
	

	ifstream infile;
	infile.open("test.txt");
	string s;
	while(getline(infile,s))
	{
		char sa[1000];
		for( int i=0;i<s.length();i++)
			sa[i] = s[i];
		sa[s.length()]='\0';
		const char *d = " :：,，";
		char *p;
		p = strtok(sa,d);
		int input1=0;
		int input2=0;
		while(p)
		{
			//printf("%s ",p);
			if(atoi(p)==0)
			{
				input2=((char)toupper(p[0])-64);
			}else
			{
				input1=atoi(p);
			}	
			form[input1][input2]++;
			p=strtok(NULL,d);
		}

	}

	infile.close();
	for(int i=1;i<=N;i++)
	{
		for(int jj=1;jj<=N;jj++)
		{
			if(form[i][jj]>1)
			insertVector(i,jj);
		}
	}

	check3();

	ofstream outfile("result.txt");
	
	for(int i=0;i<findFriends.size();i++)
	{
		cout<<"配对成功组号:" <<i+1<<" "<<endl; 
		outfile<<"配对成功组号:" <<i+1<<" "<<endl; 
		for(int j=0;j<findFriends[i].size();j++)
		{
			if(findFriends[i][j]<=N)
			{	cout<<findFriends[i][j]<<"  ";
				outfile<<findFriends[i][j]<<"  ";
			}else
			{
				cout<<char(findFriends[i][j]-N+64)<<"  ";
				outfile<<char(findFriends[i][j]-N+64)<<"  ";
			}
	
		}
		outfile<<endl;
		cout<<endl;
		outfile<<endl;
		cout<<endl;

	}
	outfile.close();

	system("pause");
	return 0;
}
