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

const int N=1e6+5;

int n, m, C, k;
int a[N], b[N];
int res;

int tr[N];

int lowbit(int x){
	return x&-x;
}

int query(int x){
	int res=0;
	for(; x; x-=lowbit(x)) res+=tr[x];
	return res;
}

int query(int l, int r){
	assert(l>0);
	return query(r)-query(l-1);
}

void add(int x, int k){
	for(; x<N; x+=lowbit(x)) tr[x]+=k;
}

signed main(){
	cin>>n>>m>>C>>k;
	rep(i,1,n) read(a[i]);
	rep(i,1,m) read(b[i]), add(i, C);
	sort(a+1, a+1+n), sort(b+1, b+1+m);
	
	rep(i,1,n){
		int l=a[i]-k, r=a[i]+k;
		if(r<b[1] || l>b[m]) continue;
		l=lower_bound(b+1, b+1+m, l)-b;
		r=upper_bound(b+1, b+1+m, r)-b-1;
		if(l>r) continue;
		
		int L=l, R=r;
		while(l<r){
			int mid=l+r>>1;
			if(query(L, mid)) r=mid;
			else l=mid+1;
		}
		if(!query(L, l)) continue;
		add(l, -1);
		res++;
	}
	cout<<res<<endl;
	
	return 0;
}