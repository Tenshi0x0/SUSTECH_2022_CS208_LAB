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

inline void read(int &x){
    int s=0; x=1;
    char ch=getchar();
    while(ch<'0' || ch>'9') {if(ch=='-')x=-1;ch=getchar();}
    while(ch>='0' && ch<='9') s=(s<<3)+(s<<1)+ch-'0',ch=getchar();
    x*=s;
}

const int N=1e5+5, M=N<<1, INF=0x3f3f3f3f;

struct Edge{
	int to, next, w;
	int cnt;
}e[M];

int h[N], tot;

void add(int u, int v, int w){
	e[tot].to=v, e[tot].w=w, e[tot].next=h[u], h[u]=tot++;
}

int n, m;
int S, T;

int d[N], rd[N];
bool vis[N];
void dijk(int d[]){
	rep(i,1,n) d[i]=INF;
	memset(vis, 0, sizeof vis);
	priority_queue<pii, vector<pii>, greater<pii>> q;
	q.push({0, S});
	d[S]=0;
	
	while(q.size()){
		auto [dis, u]=q.top(); q.pop();
		if(vis[u]) continue;
		vis[u]=true;
		
		for(int i=h[u]; ~i; i=e[i].next){
			int go=e[i].to;
			if(d[go]>d[u]+e[i].w){
				d[go]=d[u]+e[i].w;
				q.push({d[go], go});
			}
		}
	}
}

int main(){
	memset(h, -1, sizeof h);
	cin>>n>>m;
	rep(i,1,m){
		int u, v, w; read(u), read(v), read(w);
		add(u, v, w), add(v, u, w);
	}
	
	int Q; cin>>Q;
	while(Q--){
		cin>>S>>T;
		dijk(d);
		swap(T, S);
		dijk(rd);
		swap(T, S);
		for(int i=0; i<tot; i+=2){
			int u=e[i^1].to, v=e[i].to;
			if(d[u]>d[v]) swap(u, v);
			if(d[u]+rd[v]+e[i].w==d[T]){
				e[i].cnt++, e[i^1].cnt++;
			}
		}
	}
	
	for(int i=0; i<tot; i+=2) cout<<e[i].cnt<<endl;
	
	return 0;
}