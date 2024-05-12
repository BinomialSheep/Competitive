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
  string S;
  cin >> S;

  /* solve */
  int N = (int)S.size();
  int lc = 0, rc = 0;

  if (N == 1) {
    cout << 0 << endl;
    return 0;
  }

  bool isWhite;
  isWhite = (S[0] == 'W' ? true : false);
  for (int i = 1; i < N; i++) {
    if (S[i] == 'B' && isWhite) {
      lc++;
      isWhite = !isWhite;
    } else if (S[i] == 'W' && !isWhite) {
      lc++;
      isWhite = !isWhite;
    }
  }

  isWhite = (S[N - 1] == 'W' ? true : false);
  for (int i = N - 2; i >= 0; i--) {
    if (S[i] == 'B' && isWhite) {
      rc++;
      isWhite = !isWhite;
    } else if (S[i] == 'W' && !isWhite) {
      rc++;
      isWhite = !isWhite;
    }
  }
  int ans = 0;
  chmax(ans, lc);
  chmax(ans, rc);

  /* output */
  cout << ans << endl;

  return 0;
}