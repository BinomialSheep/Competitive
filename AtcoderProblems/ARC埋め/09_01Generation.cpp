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
    deque<int> A(N);
    rep(i, N) cin >> A[i];

    int rev = 0;
    while (!A.empty()) {
      if ((rev && A.back()) || (!rev && !A.back())) {
        A.pop_back();
      } else if ((!rev && !A.front()) || (rev && A.front())) {
        rev = !rev;
        A.pop_front();
      } else {
        cout << "No" << endl;
        return;
      }
    }
    cout << "Yes" << endl;

    /* solve */
    // auto rec = [&](auto f, int rev) -> bool {
    //   // debug(A, rev);
    //   if (A.empty()) return true;

    //   if ((rev && A.back()) || (!rev && !A.back())) {
    //     int tmp = A.back();
    //     A.pop_back();
    //     if (f(f, rev)) return true;
    //     A.push_back(tmp);
    //   }
    //   if ((!rev && !A.front()) || (rev && A.front())) {
    //     int tmp = A.front();
    //     A.pop_front();
    //     if (f(f, !rev)) return true;
    //     A.push_front(tmp);
    //   }
    //   return false;
    // };

    // cout << (rec(rec, 0) ? "Yes" : "No") << endl;

    /* output */
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