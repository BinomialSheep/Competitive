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
  bool isPrimeSimple(long long N) {
    if (N == 1) return false;
    for (long long i = 2; i * i <= N; ++i) {
      if (N % i == 0) return false;
    }
    return true;
  }

  void solve() {
    /* input */
    int N;
    cin >> N;

    /* solve */
    vvi A(N, vi(N));

    int gousei = -1;
    for (int i = N * N; i >= 0; i--) {
      if (i % 2 == 1 && !isPrimeSimple((ll)i)) {
        gousei = i;
        break;
      }
    }
    assert(gousei != -1);

    if (N % 2 == 0) {
      int now = -1;
      rep(j, N) {
        now += 2;
        A[N / 2 - 1][j] = now;
        A[N / 2][j] = gousei - now;
      }
      int low = now;
      for (int i = 0; i < N / 2 - 1; i++) {
        rep(j, N) {
          low += 2;
          A[i][j] = low;
        }
      }
      int high = gousei - now;
      for (int i = N / 2 + 1; i < N; i++) {
        rep(j, N) {
          high -= 2;
          if (high == 0) high = N * N;
          A[i][j] = high;
        }
      }
    } else {
      set<int> used;
      // 真ん中は固定
      A[N / 2 - 1][N / 2 - 1] = 1;
      A[N / 2][N / 2 - 1] = 8;
      A[N / 2][N / 2] = 7;
      A[N / 2 + 1][N / 2] = 2;
      used.insert(1);
      used.insert(8);
      used.insert(7);
      used.insert(2);
      //
      // debug(A);
      int now = 1;
      for (int j = 0; j < N / 2 - 1; j++) {
        now += 2;
        if (used.count(now) || used.count(gousei - now)) now += 2;
        A[N / 2 - 1][j] = now;
        A[N / 2][j] = gousei - now;
        used.insert(now);
        used.insert(gousei - now);
      }
      for (int j = N / 2 + 1; j < N; j++) {
        now += 2;
        if (used.count(now) || used.count(gousei - now)) now += 2;
        A[N / 2][j] = now;
        A[N / 2 + 1][j] = gousei - now;
        used.insert(now);
        used.insert(gousei - now);
      }
      // debug(A);
      int low = now;
      for (int i = 0; i <= N / 2 - 1; i++) {
        rep(j, N) {
          if (A[i][j] != 0) continue;
          low += 2;
          if (used.count(low)) low += 2;
          A[i][j] = low;
          used.insert(A[i][j]);
        }
      }
      int high = gousei - now;
      for (int i = N / 2 + 1; i < N; i++) {
        rep(j, N) {
          if (A[i][j] != 0) continue;
          high -= 2;
          while (high == 0 || used.count(high)) {
            if (high == 0) high = N * N - 1;
            if (used.count(high)) high -= 2;
          }
          A[i][j] = high;
          used.insert(A[i][j]);
        }
      }
    }
    // debug(A);
    set<int> used2;
    rep(i, N) rep(j, N) {
      assert(used2.count(A[i][j]) == 0);
      assert(0 < A[i][j] && A[i][j] <= N * N);
      used2.insert(A[i][j]);
      if (i + 1 < N) assert(!isPrimeSimple(A[i][j] + A[i + 1][j]));
      // debug(i, j);
      if (j + 1 < N) assert(!isPrimeSimple(A[i][j] + A[i][j + 1]));
    }
    /* output */
    rep(i, N) rep(j, N) printf("%d%c", A[i][j], j == N - 1 ? '\n' : ' ');
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