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
  int H, W, R, C;
  cin >> H >> W >> R >> C;

  if (H == 1 && W == 1) {
    cout << 0 << endl;
    return 0;
  }
  if (H == 1) {
    if (C == 1 || C == W)
      cout << 1 << endl;
    else
      cout << 2 << endl;
    return 0;
  }
  if (W == 1) {
    if (R == 1 || R == H)
      cout << 1 << endl;
    else
      cout << 2 << endl;
    return 0;
  }

  int cnt = 0;
  if (R == 1 || R == H) cnt++;
  if (C == 1 || C == W) cnt++;

  if (cnt == 0) cout << 4 << endl;
  if (cnt == 1) cout << 3 << endl;
  if (cnt == 2) cout << 2 << endl;

  /* solve */

  /* output */

  return 0;
}