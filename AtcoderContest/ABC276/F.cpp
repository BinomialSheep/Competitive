ｄ
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
#include <atcoder/all>
using namespace atcoder;
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
    vi A(N);
    rep(i, N) cin >> A[i];

    using mint = modint998244353;

    fenwick_tree<ll> fw1(3e5);
    fenwick_tree<ll> fw2(3e5);

    /* solve */
    vector<mint> ans(N);
    rep(i, N) {
      if (i == 0) {
        ans[i] = A[i];
        fw1.add(A[i], A[i]);
        fw2.add(A[i], 1);
        continue;
      }
      mint now = 0;
      // 2回前のやつを出す
      now += ans[i - 1];
      now *= i;
      now *= i;
      // 1回ずつ出す
      // A[i]未満
      ll num = fw1.sum(A[i] + 1, 3e5);
      ll cnt = fw2.sum(A[i] + 1, 3e5);
      debug(num, cnt);

      //(cnt / i+1) * num + ((i+1 - cnt) / i+1) * A[i];
      mint now2 = num;
      now2 += (i - cnt) * (ll)A[i];
      now2 /= i;

      // 頻度
      now2 *= i;
      now2 *= 2;
      now += now2;
      // 2回今のを出す
      now += A[i];
      //
      now /= (i + 1);
      now /= (i + 1);
      ans[i] = now;
      //
      fw1.add(A[i], A[i]);
      fw2.add(A[i], 1);
    }

    /* output */
    rep(i, N) cout << ans[i].val() << endl;
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