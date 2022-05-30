#include<bits/stdc++.h>
using namespace std;

#define debug(x) cerr << #x << ": " << (x) << endl
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define dwn(i,a,b) for(int i=(a);i>=(b);i--)
#define pb push_back
#define x first
#define y second
using pii = pair<int, int>;
#define all(x) (x).begin(), (x).end()

#define int long long

inline void read(int &x){
    int s=0; x=1;
    char ch=getchar();
    while(ch<'0' || ch>'9') {if(ch=='-')x=-1;ch=getchar();}
    while(ch>='0' && ch<='9') s=(s<<3)+(s<<1)+ch-'0',ch=getchar();
    x*=s;
}

const int N=2e5+5, M=1e6+5, mod=1e9+7, lim=2e9;

struct Edge{
	int to, next;
}e[M];

int h[N], tot;

void add(int u, int v){
	e[tot].to=v, e[tot].next=h[u], h[u]=tot++;
}

int dout[N], din[N];

int H[N], a[N], b[N], c[N];
int n, m, C;

bool big[N];
long double g[N][2];
int f[N][3];
pii pre[N][3];
bool ok[N];

long double cal(int x){
	return log(x)/log(1.000001);
}

void dp(){
	queue<int> q;
	q.push(1);
	f[1][0]=a[1]+C;
	f[1][1]=b[1]*C;
	f[1][2]=c[1];
	if(f[1][1]>lim) big[1]=true, g[1][1]=cal(f[1][1]);
	
	while(q.size()){
		int u=q.front(); q.pop();
		// debug(u);
		for(int i=h[u]; ~i; i=e[i].next){
			int go=e[i].to;
			// debug(big[go]);
			if(big[u]){
				// debug(u);
				big[go]=true;
				ok[go]=true;
				
				long double val=-1;
				int x;
				rep(i,0,1) if(val<g[u][i]){
					val=g[u][i];
					x=i;
				}
				// debug(x);
				// g[go]=g[u]+cal(b[go]);
				if(val+cal(b[go])>g[go][1]){
					g[go][1]=val+cal(b[go]);
					pre[go][1]={u, x};
				}
			}
			else{
				// debug(go);
				int val=-1, x;
				rep(i,0,2) if(val<f[u][i]){
					val=f[u][i];
					x=i;
				}
				// debug(val);
				// cerr<<u<<' '<<x<<endl;
				
				if(val>=H[go]){
					ok[go]=true;
					
					if(val+a[go]>f[go][0]){
						f[go][0]=val+a[go];
						pre[go][0]={u, x};
						if(f[go][0]>lim) big[go]=true, g[go][0]=cal(f[go][0]);
					}
					
					if(val*b[go]>f[go][1] && cal(val*b[go])>g[go][1]){
						f[go][1]=val*b[go];
						// cerr<<val<<' '<<b[go]<<endl;
						pre[go][1]={u, x};
						if(f[go][1]>lim) big[go]=true, g[go][1]=cal(f[go][1]);
					}
					
					if(c[go]>f[go][2]){
						f[go][2]=c[go];
						pre[go][2]={u, x};
					}
				}
			}
			
			if(--din[go]==0 && ok[go]) q.push(go);
		}
	}
}

int res;
vector<pii> ans;

void find(int x, int y){
	if(!x) return;
	auto [tx, ty]=pre[x][y];
	find(tx, ty);
	ans.pb({x, y});
}

signed main(){
	memset(h, -1, sizeof h);
	cin>>n>>m>>C;
	rep(i,1,n) read(H[i]), read(a[i]), read(b[i]), read(c[i]);
	
	rep(i,1,m){
		int u, v; read(u), read(v);
		add(u, v);
		dout[u]++, din[v]++; 
	}
	
	if(C<H[1]){
		puts("-1");
		return 0;
	}
	memset(f, 0xcf, sizeof f);
	dp();
	
	res=-1;
	int x, y;
	long double G=0;
	rep(i,1,n) if(!dout[i]){
		if(big[i]){
			if(G<g[i][0]){
				G=g[i][0];
				x=i, y=0;
			}
			if(G<g[i][1]){
				G=g[i][1];
				x=i, y=1;
			}
		}
		else if(G<1e-15){
			rep(j,0,2) if(res<f[i][j]){
				res=f[i][j];
				x=i, y=j;
			}
		}
	}
	
	if(G<1e-15 && res==-1) puts("-1");
	else{
		find(x, y);
		
		int t=ans[0].y;
		res=f[1][t]%mod;
		rep(i,1,ans.size()-1){
			int y=ans[i].y, u=ans[i].x;
			// debug(u);
			if(y==0) (res+=a[u])%=mod;
			else if(y==1) res=res*b[u]%mod;
			else res=c[u];
		}
		
		cout<<res<<endl;
	}
	// debug(500LL * 1000 * 700 * 200 % mod);
	return 0;
}