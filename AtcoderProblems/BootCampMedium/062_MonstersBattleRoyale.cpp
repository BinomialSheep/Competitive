#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
using vl = vector<long long>;
using vs = vector<string>;
using vc = vector<char>;
using vpii = vector<pair<int, int>>;
using vpll = vector<pair<long long, long long>>;
using vvi = vector<vector<int>>;
using vvl = vector<vector<long long>>;
using vvc = vector<vector<char>>;
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

// 計算量はO(N+log(a'))になるらしい。ただしa'はAで2番目に大きい数
template <class T>
T gcd_vec(vector<T> &A) {
  int size = (int)A.size();
  T ret = A[0];
  for (int i = 1; i < size; i++) {
    ret = gcd(ret, A[i]);
  }
  return ret;
}

int main() {
  /* input */
  int N;
  cin >> N;
  vi A(N);
  rep(i, N) cin >> A[i];

  /* solve */
  // 自明な下界を達成できないケース
  int ans = gcd_vec(A);

  // 互いに素な組を含む場合、自明な下界を達成できますかにはいと答える
  cout << ans << endl;

  /* output */

  return 0;
}