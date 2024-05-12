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
  ll N, L;
  cin >> N >> L;
  vl A(N);
  rep(i, N) cin >> A[i];

  /* solve */
  multiset<ll> st;
  rep(i, N) st.insert(A[i]);

  int loopNum = (int)N - 1;
  ll sum = 0;
  rep(i, N) sum += A[i];
  if (sum < L) {
    st.insert(L - sum);
    loopNum++;
  }

  ll ans = 0;
  ll now = 0;

  rep(i, loopNum) {
    auto fstAd = st.begin();
    auto scdAd = ++fstAd;
    --fstAd;
    ll fst = *fstAd;
    ll scd = *scdAd;
    // cout << fst << " " << scd << endl;
    st.erase(scdAd);
    st.erase(fstAd);
    now = fst + scd;
    st.insert(now);
    ans += now;
  }

  cout << ans << endl;

  /* output */

  return 0;
}