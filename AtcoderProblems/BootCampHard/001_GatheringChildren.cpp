#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
using vl = vector<long long>;
using vs = vector<string>;
using vc = vector<char>;
using vb = vector<bool>;
using vpii = vector<pair<int, int>>;
using vpll = vector<pair<long long, long long>>;
using vvi = vector<vector<int>>;
using vvl = vector<vector<long long>>;
using vvc = vector<vector<char>>;
using vvb = vector<vector<bool>>;
using vvvi = vector<vector<vector<int>>>;
using pii = pair<int, int>;
//#include <atcoder/all>
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define MAX 10000
#define INFTY (1 << 30)
// 浮動小数点の誤差を考慮した等式
#define EPS (1e-10)
#define equal(a, b) (fabs((a) - (b)) < EPS)
ll llMax(ll x, ll y) { return (x >= y) ? x : y; }
ll llMin(ll x, ll y) { return (x <= y) ? x : y; }

template <typename T>
inline bool chmax(T &a, T b) {
  return ((a < b) ? (a = b, true) : (false));
}
template <typename T>
inline bool chmin(T &a, T b) {
  return ((a > b) ? (a = b, true) : (false));
}

struct Solver {
  void solve() {
    /* input */
    string S;
    cin >> S;

    /* solve */
    vi rIdx;
    vi separateIdx;
    rep(i, (int)S.size() - 1) {
      if (S[i] == 'R' && S[i + 1] == 'L') rIdx.push_back(i);
      if (S[i] == 'L' && S[i + 1] == 'R') separateIdx.push_back(i);
    }

    // rep(i, rIdx.size()) cout << rIdx[i] << " ";
    // cout << endl;
    // rep(i, separateIdx.size()) cout << separateIdx[i] << " ";
    // cout << endl;

    //
    vi ans((int)S.size());

    rep(i, rIdx.size()) {
      // Rを足す
      int rNum = 0;
      if (i == 0) {
        rNum = (rIdx[i] + 1);
      } else {
        rNum = rIdx[i] - separateIdx[i - 1];
      }
      ans[rIdx[i]] += (int)ceil((double)rNum / 2);
      ans[rIdx[i] + 1] += rNum / 2;
      // Lを足す
      int lNum = 0;
      if (i == (int)rIdx.size() - 1) {
        lNum = (int)S.size() - rIdx[i] - 1;
      } else {
        lNum = separateIdx[i] - rIdx[i];
      }
      ans[rIdx[i]] += lNum / 2;
      ans[rIdx[i] + 1] += (int)ceil((double)lNum / 2);
    }
    /* output */
    rep(i, (int)ans.size()) { cout << ans[i] << " "; }
    cout << endl;
  }
};

int main() {
  int ts = 1;
  rep(ti, ts) {
    Solver solver;
    solver.solve();
  }
  return 0;
}