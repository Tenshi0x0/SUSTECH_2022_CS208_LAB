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

const int N=1e6+5;

// set<int> st;
deque<int> q;
int b[N], c[N], rc[N], ts;
bool vis[N];

int n, m;
int cnt;

int main(){
	// memset(b, -1, sizeof b);
	// memset(c, -1, sizeof c);
	
	cin>>n>>m;
	while(m--){
		string op; cin>>op;
		if(op=="put"){
			int x, y; read(x), read(y);
			if(!b[x]){
				cnt++;
				++ts;
				if(cnt>n){
					cnt--;
					while(q.size() && vis[q.front()]){
						q.pop_front();
					}
					auto t=q.front();
					b[rc[t]]=0;
					q.pop_front();
				}
				
				q.pb(ts);
				b[x]=y;
				rc[ts]=x;
				c[x]=ts;
			}
			else{
				b[x]=y;
				++ts;
				vis[c[x]]=true;
				c[x]=ts;
				rc[ts]=x;
				q.pb(ts);
			}
		}
		else{
			int x; read(x);
			if(b[x]){
				cout<<b[x]<<endl;
				++ts;
				vis[c[x]]=true;
				c[x]=ts;
				rc[ts]=x;
				q.pb(ts);
			}
			else puts("-1");
		}
	}
	return 0;
}