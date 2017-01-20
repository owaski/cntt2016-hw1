/* Copyright 2016 AcrossTheSky */
#include <iostream>
#include <cstdio>
#include <utility>
#include <cassert>
#include <map>
#include <vector>
#include <deque>
#include <queue>
#include <stack>
#include <set>
#include <ctime>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <sstream>
#include <bitset>
#include <fstream>
#include <string>
#include <cmath>
#include <algorithm>
#define REP(i, a, b) for (int i = (a); i <= (b); ++i)
#define PER(i, a, b) for (int i = (a); i >= (b); --i)
#define RVC(i, c) fot (int i = 0; i < (c).size(); ++i)
#define RED(k, u) for (int k = head[(u)]; k; k = edge[k].next)
#define lowbit(x) ((x) & (-(x)))
#define CL(x, v) memset(x, v, sizeof x)
#define MP std::make_pair
#define PB push_back
#define FR first
#define SC second
#define rank rankk
#define next nextt
#define link linkk
#define index indexx
#define abs(x) ((x) > 0 ? (x) : (-(x)))
using namespace std;
typedef long long LL;
typedef pair<int, int> PII;

template<class T> inline
bool getmin(T *a, const T &b) {
	if (b < *a) {
		*a = b;
		return true;
	}
	return false;
}

template<class T> inline
bool getmax(T *a, const T &b) {
	if (b > *a) {
		*a = b;
		return true;
	}
	return false;
}

const int mo = 1000000009;
template<class T>
T pow(T a, T b, int c = mo) {
	T res = 1;
	for (T i = 1; i <= b; i <<= 1, a = 1LL * a * a % c) if (b & i) res = 1LL * res * a % c;
	return res;
}

/*======================= TEMPLATE =======================*/
typedef vector<int> vi;
map<pair<int, vi>, int> S;
int n, m;
int l[100], r[100], h[100];
int dp(int m, vi v) {//大力出奇迹 就这么暴力压状态 从后往前放 已经放到第m个 每一列上的高度是v[]
    if (m < 0) return 1;
    if (S.find(MP(m, v)) != S.end()) return S[MP(m, v)];
    int res = 0;
    REP(i, 0, n - 1) { //枚举m的peak在哪一列
        vi t(v);
        int ll = -1, rr = -1;
        REP(j, 0, n - 1) {
            int hh = h[m] - abs(j - i);
            if (hh > t[j]) t[j] = hh;
        }
        REP(j, 0, n - 1) if (t[j] > v[j]) {
            ll = j;
            break;
        }
        REP(j, 0, n - 1) if (t[j] > v[j]) rr = j; //计算m的左右边界
        if (ll != l[m] || rr != r[m]) continue; 
        res = (res + dp(m - 1, t)) % mo;
    }
    return S[MP(m, v)] = res;
}
class Mountains {
	public:
		int countPlacements(vector<int> H, vector<string> V) {
            m = H.size();
            n = V[0].size();
            REP(i, 0, m - 1) {
                h[i] = H[i];
                l[i] = -1, r[i] = -1;
                REP(j, 0, n - 1) if (V[i][j] == 'X') {
                    l[i] = j; break;
                }
                REP(j, 0, n - 1) if (V[i][j] == 'X') r[i] = j; 
            }
            vector<int> v;
            REP(i, 0, n - 1) v.PB(0);
            S.clear();
			return dp(m - 1, v);
		}
};

// CUT begin
ifstream data("Mountains.sample");

string next_line() {
    string s;
    getline(data, s);
    return s;
}

template <typename T> void from_stream(T &t) {
    stringstream ss(next_line());
    ss >> t;
}

void from_stream(string &s) {
    s = next_line();
}

template <typename T> void from_stream(vector<T> &ts) {
    int len;
    from_stream(len);
    ts.clear();
    for (int i = 0; i < len; ++i) {
        T t;
        from_stream(t);
        ts.push_back(t);
    }
}

template <typename T>
string to_string(T t) {
    stringstream s;
    s << t;
    return s.str();
}

string to_string(string t) {
    return "\"" + t + "\"";
}

bool do_test(vector<int> heights, vector<string> visibility, int __expected) {
    time_t startClock = clock();
    Mountains *instance = new Mountains();
    int __result = instance->countPlacements(heights, visibility);
    double elapsed = (double)(clock() - startClock) / CLOCKS_PER_SEC;
    delete instance;

    if (__result == __expected) {
        cout << "PASSED!" << " (" << elapsed << " seconds)" << endl;
        return true;
    }
    else {
        cout << "FAILED!" << " (" << elapsed << " seconds)" << endl;
        cout << "           Expected: " << to_string(__expected) << endl;
        cout << "           Received: " << to_string(__result) << endl;
        return false;
    }
}

int run_test(bool mainProcess, const set<int> &case_set, const string command) {
    int cases = 0, passed = 0;
    while (true) {
        if (next_line().find("--") != 0)
            break;
        vector<int> heights;
        from_stream(heights);
        vector<string> visibility;
        from_stream(visibility);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(heights, visibility, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1477995754;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 1000 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(2);
    set<int> cases;
    bool mainProcess = true;
    for (int i = 1; i < argc; ++i) {
        if ( string(argv[i]) == "-") {
            mainProcess = false;
        } else {
            cases.insert(atoi(argv[i]));
        }
    }
    if (mainProcess) {
        cout << "Mountains (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end