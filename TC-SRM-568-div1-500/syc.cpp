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
const	int N=155;

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

int vis[N];
int a[N][N], n, lab[N];
VPI e[N];

void add(int x, int y, int z){
	e[x].pb(mk(y, z));
	e[y].pb(mk(x, z));
}

int dfs(int x){
	vis[x] = 1;
	for(auto v : e[x]){
		int to = v.fi;
		int sm = v.se;
		int la = sm - lab[x];
		if(la < 0) return 0;
		if(lab[to] == -1){
			lab[to] = la;
			if(!dfs(to)) return 0;
		}else{
			if(lab[to] != la) return 0;
		}
	}
	return 1;
}

struct EqualSums{
	int count(vector<string> board){
		n = board.size();
		REP(i, 1, n) REP(j, 1, n) a[i][j] = board[i - 1][j - 1];
		REP(i, 1, n) REP(j, 1, n) if(a[i][j] != '-') add(i, n + j, a[i][j] - 48);
		int res = 1, zo = 1;
		REP(i, 1, n + n) if(!vis[i]){
			int ok = 0, nok = 0;
			REP(x, 0, 9){
				memset(lab, -1, sizeof lab);
				lab[i] = x;
				if(!dfs(i))continue;
				int zero = 0;
				REP(i, 1, n) if(lab[i] == 0) zero = 1;
				if(zero){
					ok ++;
				}else{
					nok ++;
				}
			}
			res = 1LL * res * (ok + nok) % P;
			zo = 1LL * zo * nok % P;
		}
		renew(res, -zo);
		return res;
	}
}stu;