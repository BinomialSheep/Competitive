#include <bits/stdc++.h>
// デバッグ用マクロ：https://naskya.net/post/0002/
#ifdef LOCAL
#include <debug_print.hpp>
#define debug(...) debug_print::multi_print(#__VA_ARGS__, __VA_ARGS__)
#else
#define debug(...) (static_cast<void>(0))
#endif
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
// #include <atcoder/all>
// using namespace atcoder;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(x) (x).begin(), (x).end()
// #define MAX 10000
#define INFTY (1 << 30)
// 浮動小数点の誤差を考慮した等式
#define EPS (1e-10)
#define equal(a, b) (fabs((a) - (b)) < EPS)

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
    int N;
    cin >> N;
    string S;
    cin >> S;
    vi W(N);
    rep(i, N) cin >> W[i];

    /* solve */
    vi child;
    vi adult;
    rep(i, N) {
      if (S[i] == '0') {
        child.push_back(W[i]);
      } else {
        adult.push_back(W[i]);
      }
    }
    sort(child.begin(), child.end());
    sort(adult.begin(), adult.end());
    debug(child);
    debug(adult);

    int ans = 0;
    rep(i, (int)adult.size()) {
      int X = adult[i];
      // Xに設定した時、正しく判定できる大人の人数
      int aNum = (int)adult.size() - i;
      // Xに設定した時、間違えて判定する子どもの人数
      auto lt = lower_bound(child.begin(), child.end(), X);
      if (lt == child.end()) {
        chmax(ans, aNum + (int)child.size());
        continue;
      }
      int dis = (int)distance(child.begin(), lt);
      debug(dis);
      chmax(ans, aNum + dis);
    }

    rep(i, (int)child.size()) {
      int X = child[i] + 1;
      // Xに設定した時、正しく判定できる子どもの人数
      int aNum = i + 1;
      // Xに設定した時、間違えて判定する大人の人数
      auto lt = lower_bound(adult.begin(), adult.end(), X);
      if (lt == adult.end()) {
        chmax(ans, aNum);
        continue;
      }
      int dis = (int)distance(adult.begin(), lt);
      debug(aNum, (int)adult.size() - dis);
      chmax(ans, aNum + (int)adult.size() - dis);
    }

    /* output */
    cout << ans << endl;
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