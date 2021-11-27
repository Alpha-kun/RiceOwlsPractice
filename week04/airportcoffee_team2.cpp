#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 500100
vector<LL> cof(N);
LL l,a,b,t,r;
int n;
double f[N];
int prevcof[N];
void outcof(int i,string s)
{
	cout<<i<<"::"<<cof[i]<<s<<endl;
}
void work(int i,int j,double newt)
{
//	outcof(j,"!@#");
//	cout<<newt<<"!!!\n";
	if(f[j]<0||f[j]>newt)
	{
		f[j]=newt;
		prevcof[j]=i;
	}
}
void outp(int i,int cnt)
{
	if(prevcof[i]<0)
	{
		cout<<cnt<<endl;
		cout<<i<<" ";
	}
	else
	{
		outp(prevcof[i],cnt+1);
		cout<<i<<" ";
	} 
}
int main()
{	
	ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>l>>a>>b>>t>>r;
    cin>>n;
    for(int i=0;i<n;++i)
	{
		cin>>cof[i];
		f[i]=-1;
	}
    if(cof[n-1]!=l)
    {
		++n;
		cof[n-1]=l;
		f[n-1]=-1;
	}
	cof[n]=1LL;
	cof[n]<<=60;
	for(int i=0;i<n;++i)
	{
		f[i]=1.0*cof[i]/a;
		prevcof[i]=-1;
	}
	for(int i=0;i<n;++i)
	{
		if(f[i]>=0)
		{
//			outcof(i,"====");
			LL dis1=t*a;
			LL dis2=dis1+r*b;
			LL tar=cof[i]+dis2;
			LL lo=cof[i]+dis1;
			auto found=lower_bound(cof.begin(),cof.begin()+n,tar);
			if(found!=cof.begin()+n)
			{
				int ind=found-cof.begin();
				double newt=(t+r)+1.0*(cof[ind]-tar)/a;
				work(i,ind,f[i]+newt);
			}
			auto foundless=prev(found);
			int ind=foundless-cof.begin();
			if(cof[ind]>lo)
			{
				double newt=t+1.0*(cof[ind]-lo)/b;
				work(i,ind,f[i]+newt);
			}
			else if(cof[ind]==l)
			{
				double newt=1.0*(cof[ind]-cof[i])/a;
				work(i,ind,f[i]+newt);
			}
		}
	}
//	for(int i=0;i<n;++i)
//		cout<<i<<" "<<f[i]<<" "<<prevcof[i]<<endl;
	if(prevcof[n-1]==-1)cout<<"0";
	else outp(prevcof[n-1],1);
}