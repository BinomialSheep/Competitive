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

ll A, B;

ll getD(ll N) {
  for (int i = 1; i <= 20; i++) {
    if (N < (ll)pow((ll)10, i)) return i;
  }
  assert(false);
  return -1;
}

ll calcPrice(int N) {
  //
  return A * N + B * getD(N);
}

// indexが条件を満たすかどうか
bool isOK(int index, ll X) {
  if (calcPrice(index) > X)
    return true;
  else
    return false;
}

// 汎用的な二分探索のテンプレ
int binarySearch(ll key) {
  // index=0が条件を満たすこともあるので初期値は-1
  int ng = -1;
  // index = a.size()-1が条件を満たさないこともあるので初期値はa.size
  int ok = 1e9 + 1;

  // okとngのどちらが大きいか分からないことを考慮
  while (abs(ok - ng) > 1) {
    int mid = (ok + ng) / 2;

    if (isOK(mid, key))
      ok = mid;
    else
      ng = mid;
  }
  // okな最小のindexを返す
  return ok;
}

int main() {
  /* input */
  ll X;
  cin >> A >> B >> X;

  int cannotBuyMin = binarySearch(X);

  cout << max(0, cannotBuyMin - 1) << endl;

  /* solve */

  /* output */

  return 0;
}