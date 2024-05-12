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

vector<vector<int>> G;
vector<int> d;
vector<int> f;
vector<int> color;
int myTimer;

void rec(int v) {
  color[v] = 0;
  d[v] = myTimer;
  myTimer++;
  for (auto u : G[v]) {
    if (color[u] != -1) continue;
    color[u] = 0;
    rec(u);
  }
  color[v] = 1;
  f[v] = myTimer;
  myTimer++;
}

int main() {
  /* input */
  int n;
  cin >> n;
  G.resize(n);
  rep(i, n) {
    int u, k;
    cin >> u >> k;
    --u;
    rep(j, k) {
      int v;
      cin >> v;
      --v;
      G[u].push_back(v);
    }
  }
  /* solve */
  // 初期化
  d.resize(n);
  f.resize(n);
  // -1を未訪問、0を訪問中、1を訪問済みとする
  color.resize(n);
  rep(i, n) color[i] = -1;
  //
  myTimer = 1;
  rep(i, n) {
    if (color[i] == -1) {
      rec(i);
    }
  }

  /* output */
  rep(i, n) { cout << i + 1 << " " << d[i] << " " << f[i] << endl; }

  return 0;
}