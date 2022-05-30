#include<bits/stdc++.h>
using namespace std;

#define debug(x) cerr << #x << ": " << (x) << endl
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define dwn(i,a,b) for(int i=(a);i>=(b);i--)
#define pb push_back
#define all(x) (x).begin(), (x).end()

#define int long long

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

const int N=220, M=1e5+5, INF=1e18;

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

signed main(){
	memset(h, -1, sizeof h);
	cin>>n>>m>>S>>T;
	rep(i,1,m){
		int u, v, w; cin>>u>>v>>w;
		add(u, v, w);
	}
	cout<<dinic();
	return 0;
}