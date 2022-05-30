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

#define int long long

const int N=2020, mod=1e9+7;

int n, m;
int f[N][N], a[N][N], b[N][N], c[N][N], s[N][N];

signed main(){
	cin>>n>>m;
	rep(i,1,n) rep(j,1,m){
		f[i][j]=1;
		if(i<=2 || j<=2){
			f[i][j]=1;
			s[i][j]=(f[i][j]+s[i-1][j]+s[i][j-1]-s[i-1][j-1]+mod)%mod;
			a[i][j]=(i*j%mod*f[i][j]+a[i-1][j]+a[i][j-1]-a[i-1][j-1])%mod;
			b[i][j]=(i*f[i][j]+b[i-1][j]+b[i][j-1]-b[i-1][j-1])%mod;
			c[i][j]=(j*f[i][j]+c[i-1][j]+c[i][j-1]-c[i-1][j-1])%mod;
			continue;
		}
		f[i][j]+=(i-1)*(j-1)%mod*s[i-2][j-2]%mod+a[i-2][j-2]+b[i-2][j-2]*(1-j)%mod+c[i-2][j-2]*(1-i)%mod;
		f[i][j]%=mod;
		s[i][j]=(f[i][j]+s[i-1][j]+s[i][j-1]-s[i-1][j-1]+mod)%mod;
		a[i][j]=(i*j%mod*f[i][j]+a[i-1][j]+a[i][j-1]-a[i-1][j-1])%mod;
		b[i][j]=(i*f[i][j]+b[i-1][j]+b[i][j-1]-b[i-1][j-1])%mod;
		c[i][j]=(j*f[i][j]+c[i-1][j]+c[i][j-1]-c[i-1][j-1])%mod;
	}

	cout<<(f[n][m]%mod+mod)%mod<<endl;
	
	return 0;
}