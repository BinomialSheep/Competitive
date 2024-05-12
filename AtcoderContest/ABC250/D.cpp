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
#define INFTY (1 << 29)
// 浮動小数点の誤差を考慮した等式
#define EPS (1e-10)
#define equal(a, b) (fabs((a) - (b)) < EPS)
ll llMax(ll x, ll y) { return (x >= y) ? x : y; }
ll llMin(ll x, ll y) { return (x <= y) ? x : y; }

// O(√n)の定数倍改善アルゴリズム
bool isPrime(ll x) {
  if (x == 2) return true;
  if (x < 2 || x % 2 == 0) return false;
  ll end = (ll)sqrt(x) + 1;
  for (ll i = 3; i <= end; i += 2)
    if (x % i == 0) return false;
  return true;
}

vector<ll> getPrimeList(ll n) {
  vector<ll> ret;
  for (int i = 2; i <= n; i++) {
    if (isPrime(i)) ret.push_back(i);
  }
  return ret;
}

int main() {
  /* input */
  ll N;
  cin >> N;

  /* solve */
  if (N <= 53) {
    cout << 0 << endl;
    return 0;
  }
  ll ans = 0;
  // qの範囲
  ll end = (ll)pow((ll)sqrt(N), 0.67);
  vl primeList = getPrimeList(end);

  ll sz = primeList.size();

  for (ll i = 1; i < sz; i++) {
    ll q = primeList[i];
    // pの範囲
    // とりあえず愚直
    for (ll j = 0; j < i; j++) {
      ll p = primeList[j];
      if (p * q * q * q > N) break;
      ans++;
    }
  }

  /* output */
  cout << ans << endl;

  return 0;
}