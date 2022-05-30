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

const int N=1010;
int n;

deque<int> bl[N], q;
int gl[N][N];
int bm[N], gm[N];

void init(){
	rep(i,1,n) bl[i].clear();
	q.clear();
	rep(i,1,n) bm[i]=gm[i]=0;
}

void find(){
	rep(i,1,n) q.pb(i);
	while(q.size()){
		auto u=q.front(); q.pop_front();
		auto v=bl[u].front(); bl[u].pop_front();
		
		// u 向 v 申请匹配
		if(!gm[v]) gm[v]=u, bm[u]=v;
		else if(gl[v][u]>gl[v][gm[v]]) q.pb(gm[v]), gm[v]=u, bm[u]=v;
		else q.pb(u);
	}
}

map<string, int> gmp, bmp;
map<int, string> rgmp, rbmp;
int gt, bt;
int gget(string s){
	if(gmp.count(s)) return gmp[s];
	gmp[s]=++gt;
	rgmp[gt]=s;
	return gt;
}

int bget(string s){
	if(bmp.count(s)) return bmp[s];
	bmp[s]=++bt;
	rbmp[bt]=s;
	return bt;
}

int main(){
	int T=1;
	while(T--){
		cin>>n;
		init();
		rep(i,1,n){
			string s; cin>>s;
			bget(s);
		}
		rep(i,1,n){
			string s; cin>>s;
			gget(s);
		}
		
		rep(i,1,n) rep(j,1,n){
			string s; cin>>s;
			int x=gget(s);
			bl[i].pb(x);	
		}
		rep(i,1,n) rep(j,1,n){
			string s; cin>>s;
			int x=bget(s);
			gl[i][x]=n-j+1; // rank
		}
		
		find();
		
		rep(i,1,n) cout<<rbmp[i]<<' '<<rgmp[bm[i]]<<endl;
	}
	return 0;
}