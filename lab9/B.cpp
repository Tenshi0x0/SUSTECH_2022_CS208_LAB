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

const int mod=1e9+7;

struct Mat{
    int n, m;
    vector<vector<int>> w;

    Mat(){}
    Mat(int _n, int _m){
        n=_n, m=_m;
        w.resize(n+1, vector<int>(m+1, 0));
    }

    void I(){
    	assert(n==m);
        rep(i,1,n) rep(j,1,n) w[i][j]=(i==j);
    }

    Mat operator * (const Mat &o)const{
        assert(m==o.n);
        Mat res(n, o.m);

        rep(i,1,n) rep(j,1,o.m){
            int &t=res.w[i][j];
            rep(k,1,o.n) (t+=w[i][k]*o.w[k][j])%=mod;
        }

        return res;
    }

    Mat fpow(int p){
        Mat res(n, m);
        Mat x=*this;
        res.I();
        for(; p; p>>=1, x=x*x) if(p&1) res=res*x;
        return res;
    }
};

int n, m;

signed main(){
	cin>>n>>m;
	if(m==1){
		puts("1");
		return 0;
	}
	Mat A(m, 1);
	A.w[1][1]=1;
	
	Mat T(m, m);
	rep(i,1,m){
		if(i<m) T.w[i+1][i]=1;
	}
	rep(i,1,m) T.w[1][i]=1;
	
	A=T.fpow(n)*A;
	
	int res=0;
	rep(i,1,m) (res+=A.w[i][1])%=mod;
	cout<<res<<endl;
	
	return 0;
}