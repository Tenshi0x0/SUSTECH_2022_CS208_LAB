#include<bits/stdc++.h>
using namespace std;

#define debug(x) cerr << #x << ": " << (x) << endl
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define dwn(i,a,b) for(int i=(a);i>=(b);i--)
#define pb push_back
#define all(x) (x).begin(), (x).end()

#define x first
#define y second
using pii = pair<int, int>;
using ll = long long;

#define int long long

inline void read(int &x){
    int s=0; x=1;
    char ch=getchar();
    while(ch<'0' || ch>'9') {if(ch=='-')x=-1;ch=getchar();}
    while(ch>='0' && ch<='9') s=(s<<3)+(s<<1)+ch-'0',ch=getchar();
    x*=s;
}

const int N=5050, mod=1e9+7;

int n;
int L, R;
int f[3030][N];
int w[N];

signed main(){
	cin>>n>>L>>R;
	rep(i,1,n) read(w[i]);
	sort(w+1, w+1+n);
	
	int tot=0;
	f[0][0]=1;
	int sum=0;
	rep(i,1,n){
		int val=w[i], cnt=0;
		while(i<=n && w[i]==val) i++, cnt++, sum+=val;
		i--;
		
		++tot;
		rep(j,0,N-1) f[tot][j]=f[tot-1][j];
		rep(k,1,cnt){
			int t=k*val;
			dwn(j,N-1,t){
				(f[tot][j]+=f[tot-1][j-t])%=mod;
			}
		}
	}

	int res=0;
	rep(i,L,R) if(sum-i>=L && sum-i<=R) (res+=f[tot][i])%=mod;
	cout<<res<<endl;
	
	return 0;
}