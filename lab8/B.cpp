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

const int N=1e5+5, INF=1e9+10;

int n, m;

struct Node{
    int l, r;
    int cnt;
    #define ls tr[u].l
    #define rs tr[u].r
}tr[N*35];

int idx, root[N];

void pushup(int u){
    tr[u].cnt=tr[ls].cnt+tr[rs].cnt;
}

void insert(int &q, int p, int l, int r, int x){
    q=++idx;
    tr[q]=tr[p];
    if(l==r) return tr[q].cnt++, void();

    int mid=l+r>>1;
    if(x<=mid) insert(tr[q].l, tr[p].l, l, mid, x);
    else insert(tr[q].r, tr[p].r, mid+1, r, x);
    pushup(q);
}

int query(int p, int q, int l, int r, int k){
    if(l==r) return l;
    int mid=l+r>>1;
    int cnt=tr[tr[q].l].cnt-tr[tr[p].l].cnt;
    if(cnt>=k) return query(tr[p].l, tr[q].l, l, mid, k);
    else return query(tr[p].r, tr[q].r, mid+1, r, k-cnt);
}

int main(){
    cin>>n>>m;
    for(int i=1; i<=n; i++){
        int x; cin>>x;
        insert(root[i], root[i-1], 0, INF, x);
    }

    while(m--){
        int l, r; read(l), read(r);
        int rk=(r-l+2)>>1;
        cout<<query(root[l-1], root[r], 0, INF, rk)<<endl;
    }

    return 0;
}