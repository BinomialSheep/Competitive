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
  bool rec(deque<char> q) {
    int len = (int)q.size();
    bool ret = false;
    if (len <= 1) return true;

    if (q.front() == 'A' && q.back() == 'A') {
      // 変えない場合
      q.pop_back();
      q.pop_front();
      ret = rec(q);
      // 変える場合
      // サイズが1以下なら変えない
      if (ret == false && (int)q.size() >= 2) {
        q[0] = 'B';
        rec(q);
      }
    } else if (q.front() == 'A' && q.back() == 'B') {
      // 無理
      return false;
    } else if (q.front() == 'B' && q.back() == 'A') {
      // 絶対変える
      if (len == 2) {
        return false;
      }
      q.pop_back();
      q.pop_back();
      q.push_back('A');
      q.pop_front();
      ret = rec(q);
    } else if (q.front() == 'B' && q.back() == 'B') {
      // 変えない
      q.pop_back();
      q.pop_front();
      ret = rec(q);
      // 後ろを変える
      
    }

    return ret;
  }

  void solve() {
    /* input */
    int N;
    string S;
    cin >> N >> S;

    /* solve */
    deque<char> q;
    rep(i, (int)S.size()) q.push_back(S[i]);

    bool isOK = rec(q);

    /* output */
    if (isOK) {
      cout << "Yes" << endl;
    } else {
      cout << "No" << endl;
    }
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