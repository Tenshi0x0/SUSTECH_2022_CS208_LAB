
#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;

#define endl '\n'
#define debug(x) cerr << #x << ": " << (x) << endl
#define pb push_back
#define eb emplace_back
#define set0(a) memset(a,0,sizeof(a))
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define dwn(i,a,b) for(int i=(a);i>=(b);i--)
#define ceil(a,b) (a+(b-1))/(b)

#define all(x) (x).begin(), (x).end()
#define SUM(a) accumulate(all(a), 0LL)
#define MIN(a) (*min_element(all(a)))
#define MAX(a) (*max_element(all(a)))
#define lb(a, x) distance(begin(a), lower_bound(all(a), (x)))
#define ub(a, x) distance(begin(a), upper_bound(all(a), (x)))

#define INF 0x3f3f3f3f
#define ll_INF 0x7f7f7f7f7f7f7f7f

#define x first
#define y second

using pii = pair<int, int>;
using pdd = pair<double, double>;
using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;
using vpii = vector<pii>;
using ll = long long;
using ull = unsigned long long;

inline void read(int &x){
    int s=0; x=1;
    char ch=getchar();
    while(ch<'0' || ch>'9') {if(ch=='-')x=-1;ch=getchar();}
    while(ch>='0' && ch<='9') s=(s<<3)+(s<<1)+ch-'0',ch=getchar();
    x*=s;
}

const int N=2e5+5, M=N<<1;

struct node{
    int to, next;
}e[M];

int h[N], tot;

void add(int u, int v){
    e[tot].to=v, e[tot].next=h[u], h[u]=tot++;
}

int fa[N][20], dep[N];

void get_lca(int u, int p){
	dep[u]=dep[p]+1, fa[u][0]=p;
	rep(i,1,17) fa[u][i]=fa[fa[u][i-1]][i-1];
	
	for(int i=h[u]; ~i; i=e[i].next){
		int go=e[i].to;
		if(go==p) continue;
		get_lca(go, u);
	}
}

int lca(int u, int v){
	if(dep[u]<dep[v]) swap(u, v);
	dwn(i,17,0) if(dep[fa[u][i]]>=dep[v]) u=fa[u][i];
	if(u==v) return u;
	dwn(i,17,0) if(fa[u][i]!=fa[v][i]) u=fa[u][i], v=fa[v][i];
	return fa[u][0];
}

int dis(int u, int v){
	int anc=lca(u, v);
	return dep[u]+dep[v]-dep[anc]*2;
}

int n, m;
int up[N];

int sz[N];

void get_sz(int u, int fa){
	sz[u]=1;
	for(int i=h[u]; ~i; i=e[i].next){
		int go=e[i].to;
		if(go==fa) continue;
		get_sz(go, u);
		sz[u]+=sz[go];
	}
}

int main(){
	memset(h, -1, sizeof h);
	cin>>n;
	rep(i,1,n-1){
		int u, v; read(u), read(v);
		add(u, v), add(v, u);
	}
	
	get_lca(1, 0);
	get_sz(1, -1);
	rep(i,1,n) up[i]=n-sz[i]+1;
	
	int m; cin>>m;
	while(m--){
		int x, y; read(x), read(y);
		if(dis(x, y)&1){
			puts("0");
			continue;
		}
		int anc=lca(x, y);
		if(x==y) cout<<n<<endl;
		else if(dis(anc, x)==dis(anc, y)){
			int res=n;
			int u, son;
			u=x;
			int del=dep[x]-dep[anc];
			dwn(i,17,0) if(del-(1<<i)>=1) u=fa[u][i], del-=1<<i;
			son=u, u=fa[u][0];
			res-=sz[son];
			
			u=y;
			del=dep[y]-dep[anc];
			dwn(i,17,0) if(del-(1<<i)>=1) u=fa[u][i], del-=1<<i;
			son=u, u=fa[u][0];
			res-=sz[son];
			
			cout<<res<<endl;
		}
		else{
			int del=dis(x, y)>>1;
			int u=dep[x]>dep[y]? x: y, son;
			dwn(i,17,0) if(del-(1<<i)>=1) u=fa[u][i], del-=1<<i;
			son=u, u=fa[u][0];
			// cerr<<u<<' '<<son<<endl;
			cout<<sz[u]-sz[son]<<endl;
		}
	}
	
	return 0;
}
