#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 100
int m;
int k=1;
char to2[N];
string to22;
string str2;
string ans="1";
LL ans10=0;
int main()
{	
	ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>m;
    if(m==1)
    {
		cout<<1;
		return 0;
	}
	if(m==2)
	{
		cout<<3;
		return 0;
	}
	m-=2;
    while(m>(1<<((k+1)/2)))
    {
		m-=(1<<((k+1)/2));
		++k;
	}
	--m;
//	cout<<m<<endl;
//	cout<<k<<endl;
	int cnt=(k+1)/2;
	if(m==0)to22="0";
	else
	while(m)
	{
		char cc=(m&1)+'0';
		string tmp(1,cc);
		to22=tmp+to22;
		m>>=1;
	}
//	cout<<to22<<endl;
//	itoa(m,to2,2);
	int len=to22.size();
	for(int i=1;i<=cnt-len;++i)ans+="0";
	ans+=to22;
	
//	
//	int len=strlen(ans);
	int siz=ans.size();
	if(k&1)
	{
		for(int i=siz-2;i>=0;--i)
			ans+=ans[i];
	}
	else
	{
		for(int i=siz-1;i>=0;--i)
			ans+=ans[i];
	}
//	cout<<ans<<endl;
	siz=ans.size();
	for(int i=0;i<siz;++i)
		ans10=(ans10<<1)+ans[i]-'0';
	cout<<ans10;
//	
//	printf("%s",ans);
}
