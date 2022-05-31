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

int main(){
	int n; cin>>n;
	puts("12");
	rep(i,0,5){
		vector<int> a, b;
		rep(j,0,n-1) if(j>>i&1) a.pb(j+1);
		rep(k,0,n-1) if(!(k>>i&1)) b.pb(k+1);
		
		cout<<a.size()<<' ';
		for(auto j: a) cout<<j<<' ';
		cout<<endl;
		
		cout<<b.size()<<' ';
		for(auto j: b) cout<<j<<' ';
		cout<<endl;
		
		a.clear(), b.clear();
		
		rep(j,0,n-1) if(!(j>>i&1)) a.pb(j+1);
		rep(k,0,n-1) if(k>>i&1) b.pb(k+1);
		
		cout<<a.size()<<' ';
		for(auto j: a) cout<<j<<' ';
		cout<<endl;
		
		cout<<b.size()<<' ';
		for(auto j: b) cout<<j<<' ';
		cout<<endl;
	}
	return 0;
}
