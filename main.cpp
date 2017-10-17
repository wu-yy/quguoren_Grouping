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
	//memset(finddata,1,sizeof(finddata));
	
	int len=findFriends.size();
	int dd[1000];
	pair_my pai[1000];
	int incre=0;
	//memset(dd,0,sizeof(dd));
	for(int i=0;i<1000;i++)
	{
		finddata[i]=1;
		dd[i]=0;
	}
	
	for(int i=0;i<len-1;i++)
	{
		for(int j=i+1; j<len;j++)
		{
			if(i!=j && equalVector(findFriends[i],findFriends[j])) //发现相同的元素
			{
				//cout<<"发现重复的元素组号："<<i<<" "<<j<<endl;
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
	while(dow<incre)  //采用的穿插的算法,出现最多的组号首先插入vector
	{
		max=-1;
		for(int i=0;i<len;i++)
		{
			if(dd[i]>=max&&dowe[i]==0)
			{
				max=dd[i];
				max_index=i;
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

	//

	for(int i=0;i<findVector.size();i++)
	{
		//cout<<"队员有重复的组号：";
		set<int> temp;
		for(int j=0;j<findVector[i].size();j++)
		{
			//cout<<findVector[i][j]<<" ";   //输出重复的组号
			for(int h=0;h<findFriends[findVector[i][j]].size();h++)
				temp.insert(findFriends[findVector[i][j]][h]);
			
		}
		Friends2.push_back(temp);
		temp.clear();
	}

	//没有重复元素的组号
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
	//memset(Result,0,sizeof(Result));
	for(int i=0;i<2*N+1;i++)
		Result[i]=0;
	int kk=1;
	ofstream outfile("result.txt");
	for(int i=0;i<Friends2.size();i++)
	{
		cout<<"分组"<<kk<<"："<<endl;
		outfile<<"分组"<<kk<<"："<<endl;

		kk++;
		for(set<int>::iterator it=Friends2[i].begin();it!=Friends2[i].end();it++)
		{
			Result[*it]=1;
			if(*it<=N)
			{	cout<<*it<<"  ";
			    outfile<<*it<<"  ";
			}else
			{
				cout<<char(*it-N+64)<<"  ";
				outfile<<char(*it-N+64)<<"  ";
			}
		}
		cout<<"\n";
		outfile<<"\n";
	}
	cout<<"没有分组成功同学：\n";
	outfile<<"没有分组成功的同学：\n";
	for(int i=1;i<=2*N;i++)
	{
		if(Result[i]==0)
		{
			if(i<=N)
			{	cout<<i<<"  ";
				outfile<<i<<"  ";
			}else
			{
				cout<<char(i-N+64)<<"  ";
				outfile<<char(i-N+64)<<"  ";
			}

		}

	}
	cout<<endl;
	outfile.close();

}

int main()
{
	
	
	cout<< "这里设置的中国人为"<<N<<"，外国人最大数目为"<<N<<"。 如果想要更换最大数目，请重新编译执行\n\n";
	memset(form,0,sizeof(form));
	

	ifstream infile;
	infile.open("input.txt");
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
	system("pause");
	return 0;
}
