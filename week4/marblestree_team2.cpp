#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 100100
int n;
int siz[N];
vector<int> ed[N];
bool ro[N];
int ans=0;
int myabs(int x)
{
	if(x<0)return -x;
	return x;
}
int work(int i)
{
	for(auto j:ed[i])
	{
		siz[i]+=work(j);
	}
	ans+=myabs(siz[i]-1);
	return siz[i]-1;
}
int main()
{	
	ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
//    freopen("g.out","w",stdout);
    while(1)
    {
    	cin>>n;
    	if(n==0)break;
    	ans=0;
    	for(int i=1;i<=n;++i)
    	{
			ro[i]=1;
			ed[i].clear();
		}
		for(int i=1;i<=n;++i)
		{
			int x,m;
			cin>>x;
			cin>>siz[i];
			cin>>m;
			for(int j=1;j<=m;++j)
			{
				cin>>x;
				ed[i].push_back(x);
				ro[x]=0;
			}
		}
		for(int i=1;i<=n;++i)
		{
			if(ro[i])
			{
				work(i);
				break;
			}
		}
		cout<<ans<<endl;
	}
}