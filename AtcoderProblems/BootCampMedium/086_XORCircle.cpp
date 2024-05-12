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
  vector<int> a(N);
  rep(i, N) cin >> a[i];

  /* solve */
  map<int, int> mp;
  rep(i, N) { mp[a[i]]++; }
  //
  if (mp.size() > 3) {
    cout << "No" << endl;
    return 0;
  }
  // 個数チェック
  vi cnt;
  // XORチェック
  vi vec;
  for (auto p : mp) {
    vec.push_back(p.first);
    cnt.push_back(p.second);
  }
  if (vec.size() == 1) {
    if ((vec[0] ^ vec[0]) != vec[0]) {
      cout << "No" << endl;
      return 0;
    }
  }

  if (vec.size() == 2) {
    // AABAAB..
    if (cnt[0] == 2 * cnt[1] && (vec[1] ^ vec[1]) == vec[0] &&
        (vec[0] ^ vec[1]) == vec[1]) {
      cout << "Yes" << endl;
      return 0;
    }
    if (cnt[1] == 2 * cnt[0] && (vec[0] ^ vec[0]) == vec[1] &&
        (vec[1] ^ vec[0]) == vec[0]) {
      cout << "Yes" << endl;
      return 0;
    }
    if (cnt[0] != 2 * cnt[1] && cnt[1] != 2 * cnt[0]) {
      cout << "No" << endl;
      return 0;
    }
    cout << "Yes" << endl;
    return 0;
  }

  if (vec.size() == 3) {
    if (cnt[0] != cnt[1] || cnt[1] != cnt[2] || (vec[0] ^ vec[1]) != vec[2]) {
      cout << "No" << endl;
      return 0;
    }
  }

  /* output */
  cout << "Yes" << endl;

  return 0;
}