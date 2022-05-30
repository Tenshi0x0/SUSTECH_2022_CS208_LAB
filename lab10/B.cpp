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

const int N=1010, M=1000;

int n;
int f[N][N];
vector<int> w;

int main(){
	cin>>n;
	w.resize(n+1);
	rep(i,1,n) read(w[i]);
	w.erase(unique(all(w)), end(w));
	
	n=w.size()-1;
	
	memset(f, 0x3f, sizeof f);
	rep(i,1,n) f[i][i]=0;
	
	rep(len,2,n){
		rep(l,1,n-len+1){
			int r=l+len-1;
			if(w[l]==w[r]) f[l][r]=f[l+1][r-1]+1;
			else f[l][r]=min(f[l][r-1], f[l+1][r])+1;
		}
	}
	
	cout<<f[1][n]<<endl;
	
	return 0;
}