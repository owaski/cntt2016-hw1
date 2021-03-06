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

const int mo = 1000000007;
template<class T>
T pow(T a, T b, int c = mo) {
	T res = 1;
	for (T i = 1; i <= b; i <<= 1, a = 1LL * a * a % c) if (b & i) res = 1LL * res * a % c;
	return res;
}

/*======================= TEMPLATE =======================*/
const int N = 60;
const int inf = mo;
int d[N][N];
int l[N], r[N], t[N];
int n, m;
int f[1 << 16][16];
void format(string s, int &a, int &b, int &c) {
    stringstream fin(s);
    fin >> a >> b >> c;
}
class TravellingPurchasingMan {
	public:
		int maxStores(int N, vector<string> Stores, vector<string> roads) {
            n = N, m = Stores.size();
            REP(i, 0, n - 1) REP(j, 0, n - 1) d[i][j] = inf;
            REP(i, 0, n - 1) d[i][i] = 0;
            REP(i, 0, m - 1) format(Stores[i], l[i], r[i], t[i]);
            for (int i = 0; i < roads.size(); ++i) {
                int x, y, z;
                format(roads[i], x, y, z);
                getmin(&d[x][y], z);
                getmin(&d[y][x], z);
            }
            REP(k, 0, n - 1)
                REP(i, 0, n - 1)
                    REP(j, 0, n - 1) getmin(&d[i][j], d[i][k] + d[k][j]);
            CL(f, 0xff);
            REP(i, 0, m - 1) if (d[n - 1][i] <= r[i]) f[1 << i][i] = max(l[i], d[n - 1][i]);
            int ans = 0;
            REP(i, 1, (1 << m) - 1) {
                REP(j, 0, m - 1) if (i & (1 << j)) if (f[i][j] != -1) {
                    getmax(&ans, __builtin_popcount(i));
                    REP(k, 0, m - 1) {
                        if (i & (1 << k)) continue;
                        if (f[i][j] + t[j] + d[j][k] > r[k]) continue;
                        int x = max(f[i][j] + t[j] + d[j][k], l[k]);
                        int &res = f[i | (1 << k)][k];
                        if (res == -1 || res > x) res = x;
                    }
                }
            }
			return ans;
		}
};

// CUT begin
ifstream data("TravellingPurchasingMan.sample");

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

bool do_test(int N, vector<string> interestingStores, vector<string> roads, int __expected) {
    time_t startClock = clock();
    TravellingPurchasingMan *instance = new TravellingPurchasingMan();
    int __result = instance->maxStores(N, interestingStores, roads);
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
        int N;
        from_stream(N);
        vector<string> interestingStores;
        from_stream(interestingStores);
        vector<string> roads;
        from_stream(roads);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(N, interestingStores, roads, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1484876455;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 450 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "TravellingPurchasingMan (450 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
