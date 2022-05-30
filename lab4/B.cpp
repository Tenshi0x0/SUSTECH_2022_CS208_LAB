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

const int N=1e5+5;

int s[N];
int n, m;
int sum0;
int res;
int a[N], b[N];

struct Node{
	int l, r;
	int val, P;
	int add;
	
	#define ls (u<<1)
	#define rs (u<<1|1)
}tr[N<<2];

Node merge(Node L, Node R){
	return {
		L.l, R.r,
		min(L.val, R.val), (L.val<R.val? L.P: R.P),
		0
	};
}

void pushdown(int u){
	if(tr[u].add){
		int &del=tr[u].add;
		tr[ls].val+=del, tr[ls].add+=del;
		tr[rs].val+=del, tr[rs].add+=del;
		del=0;
	}
}

void build(int u, int l, int r){
	tr[u]={l, r};
	if(l==r) return tr[u].val=a[l], tr[u].P=l, void();
	int mid=l+r>>1;
	build(ls, l, mid), build(rs, mid+1, r);
	tr[u]=merge(tr[ls], tr[rs]);
}

void upd(int u, int l, int r, int k){
	if(l<=tr[u].l && tr[u].r<=r) return tr[u].val+=k, tr[u].add+=k, void();
	int mid=tr[u].l+tr[u].r>>1;
	pushdown(u);
	if(l<=mid) upd(ls, l, r, k);
	if(mid<r) upd(rs, l, r, k);
	tr[u]=merge(tr[ls], tr[rs]);
}

Node query(int u, int l, int r){
	if(l<=tr[u].l && tr[u].r<=r) return tr[u];
	int mid=tr[u].l+tr[u].r>>1;
	
	pushdown(u);
	Node L={-1}, R={-1};
	if(l<=mid) L=query(ls, l, r);
	if(mid<r) R=query(rs, l, r);
	if(R.l==-1) return L;
	if(L.l==-1) return R;
	return merge(L, R);
}

struct Msg{
	int l, r, sum;

	bool operator < (const Msg &o)const{
		return sum==o.sum? l<o.l: sum>o.sum;
	}
};

signed main(){
	cin>>n>>m;
	m++;
	rep(i,1,n) read(a[i]), a[i]++;
	rep(i,1,n) read(b[i]), sum0+=b[i], s[i]=b[i]+s[i-1];
	build(1, 1, n);
	
	set<Msg> st;
	st.insert({1, n, sum0});
	
	while(st.size() && m){
		auto t=*begin(st); st.erase(begin(st));
		
		int l=t.l, r=t.r, sum=t.sum;
		// cerr<<l<<' '<<r<<endl;
		auto qry=query(1, l, r);
		int val=qry.val, x=qry.P;
		
		int del=min(m, val);
		m-=del;
		res+=del*sum;

		
		upd(1, l, r, -del);
		if(x-1>=l) st.insert({l, x-1, s[x-1]-s[l-1]});
		if(x+1<=r) st.insert({x+1, r, s[r]-s[x]});

	}
	res-=sum0;
	cout<<res<<endl;
	// system("pause");
	
	return 0;
}