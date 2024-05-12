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

int main() {
  /* input */
  int N, Q;
  cin >> N >> Q;
  vi x(Q);
  rep(i, Q) cin >> x[i];

  /* solve */
  vi v(N);
  rep(i, N) v[i] = i + 1;
  map<int, int> mp;
  rep(i, N) { mp[v[i]] = i; }
  rep(i, Q) {
    int pos = mp[x[i]];
    int temp;
    if (pos == N - 1) {
      temp = v[N - 2];
      v[N - 2] = v[N - 1];
      v[N - 1] = temp;
      mp[v[N - 1]] = N - 1;
      mp[v[N - 2]] = N - 2;
    } else {
      temp = v[pos + 1];
      v[pos + 1] = v[pos];
      v[pos] = temp;
      mp[v[pos]] = pos;
      mp[v[pos + 1]] = pos + 1;
    }
  }

  /* output */
  rep(i, N) cout << v[i] << " ";
  cout << endl;

  return 0;
}