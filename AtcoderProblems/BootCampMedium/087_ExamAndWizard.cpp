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

int main() {
  /* input */
  int N;
  cin >> N;
  vi A(N), B(N);
  rep(i, N) cin >> A[i];
  rep(i, N) cin >> B[i];

  /* solve */
  vi D(N);
  ll lack = 0;
  ll ans = 0;
  ll surplus = 0;
  rep(i, N) {
    if (B[i] > A[i]) {
      lack += B[i] - A[i];
      ans++;
    } else {
      D[i] = A[i] - B[i];
      surplus += D[i];
    }
  }

  if (surplus < lack) {
    cout << -1 << endl;
    return 0;
  }
  if (lack == 0) {
    cout << 0 << endl;
    return 0;
  }
  sort(D.rbegin(), D.rend());
  rep(i, N) {
    ans++;
    lack -= D[i];
    if (lack <= 0) break;
  }

  /* output */
  cout << ans << endl;

  return 0;
}