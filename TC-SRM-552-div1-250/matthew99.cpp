#include <bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for (int i = (a), i##_end_ = (b); i < i##_end_; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define mp make_pair
#define x first
#define y second
#define pb push_back
#define SZ(x) (int((x).size()))
#define ALL(x) (x).begin(), (x).end()

template<typename T> inline bool chkmin(T &a, const T &b) { return a > b ? a = b, 1 : 0; }
template<typename T> inline bool chkmax(T &a, const T &b) { return a < b ? a = b, 1 : 0; }

typedef long long LL;

const int oo = 0x3f3f3f3f;

class FoxPaintingBalls 
{
	public:
		long long theMax(long long R, long long G, long long B, int N) 
		{
			LL val = (LL)N * (N + 1) >> 1;
			LL tmp = val / 3;
			LL ret = (R + G + B) / val;
			if (tmp) chkmin(ret, min(R, min(G, B)) / tmp);
			return ret;
		}
};

// Powered by Greed 2.0-RC
