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
    int N, L, R;
    cin >> N >> L >> R;

    /* solve */
    //
    vi A(N, 1);

    int t = 1;
    if(R == 1 && N % 2 == 0) t = 2;
    if (t == 1) {
      cout << "First" << endl;
      
      int x, y;
      cout << x << y << endl;
    } else {
      cout << "Second" << endl;
    }

    //
    while (true) {
      int a, b;
      cin >> a >> b;
      if (a == 0 && b == 0) return;
      if (a == -1 && b == -1) return;
      rep(i, b) A[a + i] = 0;

      deque<pair<int, int>> B;
      rep(i, N) {
        if (B.empty()) {
          B.emplace_back(0, A[i]);
          continue;
        }
        if (A[i]) {
          if (B.back().second == 0) {
            B.pop_back();
            B.emplace_back(i, 1);
          } else {
            B[B.size() - 1].second++;
          }
        } else {
          if (B.back().second != 0) B.emplace_back(0, 0);
        }
      }
      if (B.back().second == 0) B.pop_back();

      int xorSum = 0;
      for (auto p : B) xorSum ^= p.second;

      int idx = 0;
      for (auto p : B) {
        if (p.second <= xorSum) {
          idx = p.first;
        }
      }
      cout << 2 1 
    }

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