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

    /* solve */
    int X, Y;

    int left = 1;
    int right = N + 1;
    int cnt = 0;
    while (abs(right - left) >= 1) {
      cnt++;
      assert(cnt <= 20);
      int mid = (left + right) / 2;

      cout << "? " << left << " " << mid << " 1 " << N << endl;
      int T;
      cin >> T;

      if (T == mid + 1 - left) {
        // 右側にある
        left = mid + 1;
      } else {
        right = mid;
      }

      if (right - left == 1) {
        cnt++;
        assert(cnt <= 20);
        cout << "? " << left << " " << left << " 1 " << N << endl;
        int T2;
        cin >> T2;
        if (T2 == 0) {
          right = left;
        } else {
          right = left + 1;
        }
        break;
      }
    }
    X = right;
    
    

    left = 1;
    right = N + 1;
    while (abs(right - left) >= 1) {
      cnt++;
      assert(cnt <= 20);
      int mid = (left + right) / 2;

      cout << "? 1 " << N << " " << left << " " << mid << endl;
      int T;
      cin >> T;

      if (T == mid + 1 - left) {
        // 右側にある
        left = mid + 1;
      } else {
        right = mid;
      }
      if (right - left == 1) {
        cnt++;
        assert(cnt <= 20);
        cout << "? 1 " << N << " " << left << " " << left << endl;
        int T2;
        cin >> T2;
        if (T2 == 0) {
          right = left;
        } else {
          right = left + 1;
        }
        break;
      }
    }
    Y = right;

    /* output */
    cout << "! " << X << " " << Y << endl;
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