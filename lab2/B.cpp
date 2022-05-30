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

const int N=2e6+5, M=N<<1;

struct Edge{
	int to, next;
}e[M];

int h[N], tot;

void add(int u, int v){
	e[tot].to=v, e[tot].next=h[u], h[u]=tot++;
}

int n;

int d[N];
bool vis[N];
int q[N];
void bfs(){
	int tt=-1, hh=0;
	q[++tt]=1;
	vis[1]=true;
	while(tt>=hh){
		int u=q[hh++];
		for(int i=h[u]; ~i; i=e[i].next){
			int go=e[i].to;
			if(!vis[go]){
				vis[go]=true;
				d[go]=d[u]+1;
				q[++tt]=go;
			}
		}
		int go;
		if(u-1>0){
			go=u-1;
			if(!vis[go]){
				vis[go]=true;
				d[go]=d[u]+1;
				q[++tt]=go;
			}
		}
		if(u+1<=n){
			go=u+1;
			if(!vis[go]){
				vis[go]=true;
				d[go]=d[u]+1;
				q[++tt]=go;
			}
		}
	}
	rep(i,1,n) printf("%d ", d[i]);
}

int main(){
	memset(h, -1, sizeof h);
	cin>>n;
	rep(i,1,n){
		int x; read(x);
		add(i, x);
	}

	bfs();
	
	return 0;
}