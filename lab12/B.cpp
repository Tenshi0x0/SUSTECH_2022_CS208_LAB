#pragma GCC optimize("O3")
#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
#include<map>
#include<set>
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

inline void read(int &x){
    int s=0; x=1;
    char ch=getchar();
    while(ch<'0' || ch>'9') {if(ch=='-')x=-1;ch=getchar();}
    while(ch>='0' && ch<='9') s=(s<<3)+(s<<1)+ch-'0',ch=getchar();
    x*=s;
}

const int N=5e4+50, M=1e6+5, INF=0x3f3f3f3f;

struct Edge{
    int to, c, next;
}e[M<<1];

int h[N], tot;

void add(int u, int v, int c){
    e[tot].to=v, e[tot].c=c, e[tot].next=h[u], h[u]=tot++;
    e[tot].to=u, e[tot].c=0, e[tot].next=h[v], h[v]=tot++;  
}

int n, m, S, T;

int d[N], q[N], cur[N];

bool bfs(){
    memset(d, -1, sizeof d);
    int tt=-1, hh=0;
    q[++tt]=S, d[S]=0, cur[S]=h[S];

    while(tt>=hh){
        int hd=q[hh++];
        for(int i=h[hd]; ~i; i=e[i].next){
            int go=e[i].to;
            if(d[go]==-1 && e[i].c){
                d[go]=d[hd]+1;
                cur[go]=h[go];
                if(go==T) return true;
                q[++tt]=go;
            }
        }
    }
    return false;
}

int find(int u, int limit){
    if(u==T) return limit;
    int flow=0;
    for(int i=cur[u]; ~i && flow<limit; i=e[i].next){
        cur[u]=i;
        int go=e[i].to;
        if(d[go]==d[u]+1 && e[i].c){
            int t=find(go, min(e[i].c, limit-flow));
            if(!t) d[go]=-1;
            e[i].c-=t, e[i^1].c+=t, flow+=t;
        }
    }
    return flow;
}

int dinic(){
    int res=0, flow;
    while(bfs()) while(flow=find(S, INF)) res+=flow;
    return res;
}

int a, b;
char g[110][110];
int id[110][110], idx;
int V;

int main(){
	int cs; cin>>cs;
	while(cs--){
		cin>>n>>m>>a>>b;
		
		// init
		V=n*m*2+2;
		rep(i,0,V) h[i]=-1;
		tot=0;
		idx=0;
		rep(i,1,n) rep(j,1,m) cin>>g[i][j], id[i][j]=++idx;
		
		S=n*m*2+1, T=S+1;
		int nm=n*m;
		rep(i,1,a){
			int u; read(u);
			if(g[1][u]=='1') continue;
			u=id[1][u];
			add(S, u, 1);
		}
		rep(i,1,b){
			int u; read(u);
			if(g[n][u]=='1') continue;
			u=id[n][u];
			add(u, T, 1);
		}
		
		rep(i,1,n) rep(j,1,m) if(g[i][j]=='0'){
			int fir=id[i][j], sec=id[i][j]+nm;
			add(fir, sec, 1), add(sec, fir, 1);
			if(i>1) add(fir, id[i-1][j], 1);
			if(i<n) add(fir, id[i+1][j], 1);
			if(j>1) add(sec, id[i][j-1]+nm, 1);
			if(j<m) add(sec, id[i][j+1]+nm, 1);
		}
		
		if(dinic()==a) puts("Yes");
		else puts("No");
	}
	return 0;
}