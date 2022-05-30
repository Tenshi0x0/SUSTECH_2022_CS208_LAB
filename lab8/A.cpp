#include<bits/stdc++.h>
using namespace std;

const int N=3e6+5;
const double pi=acos(-1);

int n, m;

struct Complex{
	double x, y;
	Complex operator + (const Complex &o)const { return {x+o.x, y+o.y}; }
	Complex operator - (const Complex &o)const { return {x-o.x, y-o.y}; }
	Complex operator * (const Complex &o)const { return {x*o.x-y*o.y, x*o.y+y*o.x}; }
	
	double norm(){
		return sqrt(x*x+y*y);
	}
};

Complex a[N], b[N];
int res[N];

int rev[N], bit, tot;

void fft(Complex a[], int inv){
	for(int i=0; i<tot; i++) if(i<rev[i]) swap(a[i], a[rev[i]]);
	
	for(int mid=1; mid<tot; mid<<=1){
		auto w1=Complex({cos(pi/mid), inv*sin(pi/mid)});
		for(int i=0; i<tot; i+=mid*2){
			auto wk=Complex({1, 0});
			for(int j=0; j<mid; j++, wk=wk*w1){
				auto x=a[i+j], y=wk*a[i+j+mid];
				a[i+j]=x+y, a[i+j+mid]=x-y;
			}
		}
	}
}

int main(){
	cin>>n;
	n=1<<n;
	for(int i=0; i<n; i++) cin>>a[i].x;
	
	while((1<<bit)<n) bit++;
	tot=1<<bit;
	for(int i=0; i<tot; i++) rev[i]=(rev[i>>1]>>1)|((i&1)<<(bit-1));
	
	fft(a, 1);
	for(int i=0; i<n; i++) printf("%.10lf\n", a[i].norm());

	return 0;
}