#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define MAX 10000
#define INFTY (1 << 29)
// 浮動小数点の誤差を考慮した等式
#define EPS (1e-10)
#define equal(a, b) (fabs((a) - (b)) < EPS)
ll llMax(ll x, ll y) { return (x >= y) ? x : y; }
ll llMin(ll x, ll y) { return (x <= y) ? x : y; }

vector<vector<int>> ice;
int nNum;
int mNum;

int dfs(int n, int m) {
  int num = 1;
  if (0 <= n - 1 && ice[n - 1][m] == 1) {
    ice[n - 1][m] = 2;
    num = max(num, 1 + dfs(n - 1, m));
    ice[n - 1][m] = 1;
  }
  if (n + 1 < nNum && ice[n + 1][m] == 1) {
    ice[n + 1][m] = 2;
    num = max(num, 1 + dfs(n + 1, m));
    ice[n + 1][m] = 1;
  }
  if (0 <= m - 1 && ice[n][m - 1] == 1) {
    ice[n][m - 1] = 2;
    num = max(num, 1 + dfs(n, m - 1));
    ice[n][m - 1] = 1;
  }
  if (m + 1 < mNum && ice[n][m + 1] == 1) {
    ice[n][m + 1] = 2;
    num = max(num, 1 + dfs(n, m + 1));
    ice[n][m + 1] = 1;
  }
  return num;
}

int main() {
  /* input */
  int m, n;
  cin >> m >> n;
  ice.resize(n);
  rep(i, n) ice[i].resize(m);
  rep(i, n) rep(j, m) cin >> ice[i][j];
  nNum = n;
  mNum = m;

  /* solve */
  int ans = 0;
  rep(i, n) rep(j, m) {
    if (ice[i][j] == 1) {
      ice[i][j] = 2;
      ans = max(ans, dfs(i, j));
      ice[i][j] = 1;
    }
  }
  /* output */
  cout << ans << endl;

  return 0;
}