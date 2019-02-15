#include<bits/stdc++.h>
#define pb push_back
#define INF 1e9+7
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
typedef std::pair<int,int> ii;
typedef std::vector<ii> vii;
typedef long long int lli;
typedef long long ll;
typedef std::pair<int,vi> ivi;

std::ifstream in;
std::ofstream out;

long cal()
{
	char c;
	long ans = 0 , cur = 0;
	bool add = true;
	bool min = false;
	bool mul = false;
	bool preadd = true;
	std::vector<long> container;
	int tmp;
	while(in>>c)
		switch(c)
		
{			case '(':
				cur = cal();
			break;

			case')':
				if(mul) for(int i=0;i<container.size();i++) cur *= container[i];
				if(add) ans += cur;
				if(min) ans -= cur;
				return ans;
			break;

			case '+':
				if(mul)
				{
					for(int i=0;i<container.size();i++) cur = cur * container[i];
					container.clear();
				}
				if(add)
				{
					ans += cur;
					min = false;
					cur = 0;
				}
				if(min)
				{
					ans-=cur;
					add = true;
					min = false;
					cur = 0;
				}
				break;
			case '-':
				if(mul)
				{
					for(int i=0;i<container.size();i++) cur = cur * container[i];
					container.clear();
				}
				if(add)
				{
					ans += cur;
					add = false;
					min = true;
					cur = 0;
				}
				if(min)
				{
					ans-=cur;
					add = false;
					min = true;
					cur = 0;
				}
				break;
			break;

			case '*':
				mul = true;
				container.push_back(cur);
				cur = 0;
			break;

			default:
				cur = cur * 10 + c - '0';
			break;
		}
	if(mul)
	{
		for(int i=0;i<container.size();i++) cur = cur * container[i];
		container.clear();
	}
	if(add)
	{
		ans += cur;
		add = false;
		min = true;
		cur = 0;
	}
	if(min)
	{
		ans-=cur;
		add = false;
		min = true;
		cur = 0;
	}

	return ans;
}


signed main()
{
	#ifdef _Nghviet
		freopen("solve.in","r",stdin);
		freopen("solve.out","w",stdout);
	#endif

	in.open("solve.in",std::fstream::in);
	out.open("solve.out",std::fstream::out);

	if(!in.good())
	{
		std::cout<<"Input err"<<std::endl;
		return 0;
	}	
	if(!out.good())
	{
		std::cout<<"Output err"<<std::endl;
		return 0;
	}

	out<<cal();

}