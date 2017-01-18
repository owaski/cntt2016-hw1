#include <set>
#include <map>
#include <cmath>
#include <ctime>
#include <bitset>
#include <string>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <iomanip>
#include <iostream>
#include <algorithm>
#define PR pair
#define fi first
#define se second
#define mk make_pair
#define pb push_back
#define REP(i, x, y)   for(int i = (int)(x); i <= (int)(y); i++)
#define FOR(i, x, y)   for(int i = (int)(x); i <  (int)(y); i++)
#define PER(i ,x, y)  for(int i = (int)(x); i >= (int)(y); i--)
#define CH	         ch = getchar()
#define Exit(...)    printf(__VA_ARGS__), exit(0)
#define dln()        fprintf(stderr,"\n")
#define dprintf(...) fprintf(stderr,__VA_ARGS__)
using namespace std;
typedef double	  db;
typedef long long LL;
typedef vector<int> VI;
typedef vector<VI > VII;
typedef PR<int,int> PII;
typedef vector<PII> VPI;
const	int inf=2e9;
const	LL Inf=1e10;
const	int P=1e9+7;
const	int N=100005;

inline LL IN(){
	LL x = 0;
	int ch = 0, f = 0;
	for (CH; ch != -1 && (ch < 48 || ch > 57); CH) f = (ch == '-');
	for (; ch >= 48 && ch <= 57; CH) x = (x << 1) + (x << 3) + ch - '0';
	return f ? (-x) : x;
}
template<typename T> inline int chkmin(T &a, const T &b){if(b < a) return a = b, 1; return 0;}
template<typename T> inline int chkmax(T &a, const T &b){if(b > a) return a = b, 1; return 0;}

void renew(int &x, const int &y){
	x += y;
	if(x >= P) x -= P;
	if(x <  0) x += P;
}

int Pow(int x, int y, int p){
	int a = 1;
	for (; y; y >>= 1, x = (LL)x * x %p) if(y & 1) a=(LL)a * x%p;
	return a;
}

int f[55][55][2555];
struct LittleElephantAndPermutationDiv1{
	int getNumber(int n, int k){
		f[n][0][n * (n + 1) / 2] = 1;
		f[n][1][n * (n + 1) / 2 + n] = 1;
		PER(i, n, 2) REP(j, 0, n) REP(k, 0, n * (n + 1)){
			int val = f[i][j][k];
			if(!val) continue;
			renew(f[i - 1][j][k], val);
			renew(f[i - 1][j][k], 1LL * val * j % P);
			renew(f[i - 1][j + 1][k + (i - 1)], val);
			if(j) renew(f[i - 1][j - 1][k - (i - 1)], 1LL * val * j * j % P);
			renew(f[i - 1][j][k], 1LL * val * j % P);
		}
		int ans = 0;
		REP(i, k, n * (n + 1)) renew(ans, f[1][0][i]);
		REP(i, 1, n) ans = 1LL * ans * i % P;
		return ans;
	}
}s;