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

vector<vector<int>> T;
vector<int> C;
vector<ll> sum;

vector<int> color;

// vは頂点、cntは現在のカウンタの値
void dfs(int v, ll cnt) {
  color[v] = 1;
  cnt += C[v];
  sum[v] = cnt;
  for (auto u : T[v]) {
    if (color[u] == 0) {
      dfs(u, cnt);
    }
  }
}

int main() {
  /* input */
  int N, Q;
  cin >> N >> Q;
  T.resize(N);
  rep(i, N - 1) {
    int a, b;
    cin >> a >> b;
    --a;
    --b;
    T[a].push_back(b);
    T[b].push_back(a);
  }
  C.resize(N);
  rep(i, Q) {
    int p, x;
    cin >> p >> x;
    --p;
    C[p] += x;
  }

  /* solve */
  color.resize(N);
  // 頂点0からdfsをする
  sum.resize(N);
  dfs(0, 0);

  /* output */
  rep(i, N) cout << sum[i] << " ";
  cout << endl;

  return 0;
}