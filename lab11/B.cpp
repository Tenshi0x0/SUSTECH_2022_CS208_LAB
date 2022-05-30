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

const int N=25, mod=1e9+7;

int n, m;
int g[N];
int U;

int f[(1<<20)+13];

int dp(int x){
	if(f[x]) return f[x];
	
	int &res=f[x];
	rep(i,0,n-1) if(x>>i&1){
		int u=i+1;
		int y=(x^(1<<i))&g[u];
		int sz=__builtin_popcount(y);

		(res+=(1LL<<sz)*dp(x^(1<<i))%mod)%=mod;
	}
	return res;
}

signed main(){
	cin>>n>>m;
	rep(i,1,m){
		int u, v; cin>>u>>v;
		g[u]|=(1<<v-1);
	}
	
	U=(1<<n)-1;
	f[0]=1;
	cout<<dp(U)<<endl;
	
	return 0;
}