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

const int N=1e6+5, M=N<<1, mod=998244353;

int n, m;

struct Edge{
    int to, next;
}e[M];

int h[N], tot;

void add(int u, int v){
    e[tot].to=v, e[tot].next=h[u], h[u]=tot++;
}

int d[N];

int cnt[N];
void dfs(int u, int fa){
    for(int i=h[u]; ~i; i=e[i].next){
        int go=e[i].to;
        if(go==fa) continue;
        cnt[u]++;
        dfs(go, u);
    }   
}

int fac[N];

void init(){
	fac[0]=1;
	for(int i=1; i<N; i++) fac[i]=fac[i-1]*i%mod;
}

int f[N];
void get(int u, int fa){
	f[u]=fac[cnt[u]];
	for(int i=h[u]; ~i; i=e[i].next){
        int go=e[i].to;
        if(go==fa) continue;
        get(go, u);
        f[u]=(f[u]*f[go])%mod;
    }  
}

signed main(){
    init();
    memset(h, -1, sizeof h);
    cin>>n;
    rep(i,1,n-1){
        int u, v; read(u), read(v);
        add(u, v), add(v, u);
    }
	dfs(1, -1);
	get(1, -1);
	cout<<f[1]<<endl;
	
    return 0;
}