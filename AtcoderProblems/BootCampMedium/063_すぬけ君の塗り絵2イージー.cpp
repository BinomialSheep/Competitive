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

int cnt(int W, int H, vvi &color) {
  int ret = 0;
  rep(i, W + 1) {
    if (i == 0) continue;
    rep(j, H + 1) {
      if (j == 0) continue;
      if (color[i][j] == 0) ret++;
    }
  }
  return ret;
}

int main() {
  /* input */
  int W, H, N;
  cin >> W >> H >> N;
  /* solve */
  // color[i][j] = 1のとき、(i-1, j-1)～(i-1, j-1)の1マスが黒く塗られている
  vvi color(W + 1, vi(H + 1));
  rep(i, N) {
    int x, y, a;
    cin >> x >> y >> a;
    if (a == 1) {
      rep(j, W + 1) {
        rep(k, H + 1) {
          if (x >= j) color[j][k] = 1;
        }
      }
    } else if (a == 2) {
      rep(j, W + 1) {
        rep(k, H + 1) {
          if (x < j) color[j][k] = 1;
        }
      }
    } else if (a == 3) {
      rep(j, W + 1) {
        rep(k, H + 1) {
          if (y >= k) color[j][k] = 1;
        }
      }
    } else {
      rep(j, W + 1) {
        rep(k, H + 1) {
          if (y < k) color[j][k] = 1;
        }
      }
    }
    // cout << cnt(W, H, color) << endl;
  }

  /* output */

  cout << cnt(W, H, color) << endl;

  return 0;
}