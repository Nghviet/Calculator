#include<bits/stdc++.h>
using namespace std;

int main()
{
	freopen("solve.in","r",stdin);
	freopen("dout.out","w",stdout);

	int n;
	cin>>n;
	int ans = 0;
	for(int i=1;i<=n;i++) ans += i*pow(2,i-1);
	cout<<ans;
}