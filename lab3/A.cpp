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

const int N=1e6+5, M=N<<1;

struct Edge{
	int to, next;
}e[M];

int h[N], tot;

void add(int u, int v){
	e[tot].to=v, e[tot].next=h[u], h[u]=tot++;
}

pii w[N];

const int mod=1e9+7;

int n, m;
int f[N], g[N];
int d[N];

void bfs(int f[]){
	queue<int> q;
	rep(i,1,n) if(!d[i]) q.push(i), f[i]=1;
	while(q.size()){
		int u=q.front(); q.pop();
		for(int i=h[u]; ~i; i=e[i].next){
			int go=e[i].to;
			if(--d[go]==0) q.push(go);
			(f[go]+=f[u])%=mod;
		}
	}
}

signed main(){
	cin>>n>>m;
	rep(i,1,m){
		int u, v; read(u), read(v);
		w[i]={u, v};
	}	
	
	memset(h, -1, sizeof h);
	tot=0;
	rep(i,1,m){
		auto [u, v]=w[i];
		add(u, v), d[v]++;
	}
	bfs(f);
	
	memset(d, 0, sizeof d);
	memset(h, -1, sizeof h);
	tot=0;
	rep(i,1,m){
		auto [u, v]=w[i];
		add(v, u), d[u]++;
	}
	bfs(g);
	
	rep(i,1,n) cout<<(1LL*f[i]*g[i]%mod)<<' ';
	
	return 0;
}