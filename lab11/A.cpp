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

const int N=5e5+5, M=N<<1;

struct Edge{
	int to, w, next;
}e[M];

int h[N], tot;

void add(int u, int v, int w){
	e[tot].to=v, e[tot].w=w, e[tot].next=h[u], h[u]=tot++;
}

int n;

int f[N][2];

void dfs(int u, int fa){
	int del=0;
	for(int i=h[u]; ~i; i=e[i].next){
		int go=e[i].to;
		if(go==fa) continue;
		
		f[go][1]+=e[i].w;
		dfs(go, u);
		f[u][0]+=f[go][0];
		del=max(del, f[go][1]-f[go][0]);
		f[u][1]+=f[go][0];
	}
	f[u][0]+=del;
}

signed main(){
	memset(h, -1, sizeof h);
	cin>>n;
	rep(i,1,n-1){
		int u, v, w; read(u), read(v), read(w);
		add(u, v, w), add(v, u, w);
	}

	dfs(1, 0);
	
	cout<<f[1][0]<<endl;
	
	return 0;
}