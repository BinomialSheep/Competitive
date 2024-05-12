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

int main() {
  /* input */
  int N, M;
  cin >> N >> M;
  vector<vector<int>> to(N);
  rep(i, M) {
    int a, b;
    cin >> a >> b;
    --a;
    --b;
    to[a].push_back(b);
  }

  /* solve */
  // 未探索は-1、それ以外は使う定期便の数
  vector<int> dist(N, INFTY);
  // 島1から幅優先探索して、島Nに到達できるならOK
  queue<int> q;
  q.push(0);
  dist[0] = 0;
  while (!q.empty()) {
    int a = q.front();
    q.pop();
    // 距離1の探索が終わったら終わり
    if (dist[a] >= 2) break;
    for (auto b : to[a]) {
      if (dist[b] > dist[a] + 1) {
        q.push(b);
        dist[b] = min(dist[b], dist[a] + 1);
      }
    }
  }

  /* output */
  cout << (dist[N - 1] == 2 ? "POSSIBLE" : "IMPOSSIBLE") << endl;

  return 0;
}