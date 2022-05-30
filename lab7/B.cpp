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

const int N=2e5+5;

int n, w[N];

struct Node{
	int l, r;
	int sum;
	int lv, rv;
	int val;
	
	#define ls u<<1
	#define rs u<<1|1
}tr[N<<2];

Node merge(Node L, Node R){
	Node res;
	res.l=L.l, res.r=R.r;
	res.sum=L.sum+R.sum;
	res.lv=max(L.lv, L.sum+R.lv);
	res.rv=max(R.rv, R.sum+L.rv);
	res.val=max({L.val, R.val, L.rv+R.lv});
	return res;
}

void build(int u, int l, int r){
	tr[u]={l, r};
	if(l==r){
		tr[u].sum=tr[u].lv=tr[u].rv=tr[u].val=w[l];
		return;
	}
	
	int mid=l+r>>1;
	build(ls, l, mid), build(rs, mid+1, r);
	tr[u]=merge(tr[ls], tr[rs]);
}

Node query(int u, int l, int r){
	if(l<=tr[u].l && tr[u].r<=r) return tr[u];
	int mid=tr[u].l+tr[u].r>>1;
	
	Node L={-1}, R={-1};
	if(l<=mid) L=query(ls, l, r);
	if(mid<r) R=query(rs, l, r);
	if(L.l==-1) return R;
	if(R.l==-1) return L;
	return merge(L, R);
}

signed main(){
	cin>>n;
	rep(i,1,n) read(w[i]);
	build(1, 1, n);
	
	int Q; cin>>Q;
	while(Q--){
		int l, r; read(l), read(r);
		cout<<query(1, l, r).val<<endl;
	}
	return 0;
}