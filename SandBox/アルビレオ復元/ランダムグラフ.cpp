#include <bits/stdc++.h>
// デバッグ用マクロ：https://naskya.net/post/0002/
#ifdef LOCAL
#include <debug_print.hpp>
#define debug(...) debug_print::multi_print(#__VA_ARGS__, __VA_ARGS__)
#else
#define debug(...) (static_cast<void>(0))
#endif
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(x) (x).begin(), (x).end()

struct Solver {
  void solve() {
    /* input */
    int N = 60;
    int M = 65;
    const int MAX_DEGREE = 3;
    vector<vector<int>> G(N);
    random_device rng;

    // ランダムに制限列を作る
    vector<int> visitables(N);
    while (true) {
      rep(i, N) visitables[i] = rng() % MAX_DEGREE + 1;
      // rep(i, N) visitables[i] = MAX_DEGREE;
      int sumDegree = reduce(all(visitables));
      // visitable * 2が最大次数で、次数の和 * 2 = 辺なので係数が相殺
      if (sumDegree >= M) break;
    }

    // ランダムに次数制限付きのprufer列を作る
    auto randPrufer = [&]() {
      vector<int> countDegrees(N);
      vector<int> prufer;
      rep(i, N - 2) {
        while (true) {
          int v = rng() % N;
          if (countDegrees[v] == MAX_DEGREE) continue;
          countDegrees[v]++;
          prufer.push_back(v);
          break;
        }
      }
      return prufer;
    };

    auto prufer2tree = [&](vector<int>& prufer) {
      vector<int> degrees(N, 1);
      for (auto v : prufer) degrees[v]++;

      // 次数1で最小のiについて、辺(i, j)を追加する
      rep(i, N - 2) {
        int ai = prufer[i];
        rep(j, N) {
          if (degrees[j] == 1) {
            degrees[ai]--, degrees[j]--;
            G[ai].push_back(j);
            G[j].push_back(ai);
            break;
          }
        }
      }
      // 次数1の残った2頂点に辺を追加する
      vector<int> vec;
      rep(i, N) if (degrees[i] == 1) vec.push_back(i);
      assert(vec.size() == 2);
      G[vec[0]].push_back(vec[1]);
      G[vec[1]].push_back(vec[0]);
    };

    // 辺を適当に足す
    auto tree2graph = [&]() {
      vector<int> countDegrees(N);
      set<pair<int, int>> edges;
      rep(v, N) for (auto u : G[v]) {
        countDegrees[v]++;
        edges.emplace(min(v, u), max(v, u));
      }
      int loopCnt = 0;
      while (M > (int)edges.size() && loopCnt <= 100000) {
        loopCnt++;
        int i = rng() % N, j = rng() % N;
        if (i == j) continue;
        if (countDegrees[i] == visitables[i] * 2) continue;
        if (countDegrees[j] == visitables[j] * 2) continue;
        if (edges.count(make_pair(min(i, j), max(i, j)))) continue;
        edges.emplace(i, j);
        G[i].push_back(j);
        G[j].push_back(i);
        countDegrees[i]++, countDegrees[j]++;
        loopCnt = 0;
      }
      if (loopCnt >= 100000) assert(false);
    };

    auto printGraph = [&]() {
      printf("%d %d\n", N, M);
      set<pair<int, int>> edges;
      rep(v, N) for (auto u : G[v]) edges.emplace(min(v, u), max(v, u));
      for (auto [v, u] : edges) printf("%d %d\n", v + 1, u + 1);
      for (auto v : visitables) cout << v << " ";
      cout << endl;
    };

    vector<int> prufer = randPrufer();
    prufer2tree(prufer);
    tree2graph();
    printGraph();

    /* solve */

    /* output */
  }
};

int main() {
  int ts = 1;
  rep(ti, ts) {
    Solver solver;
    solver.solve();
  }
  return 0;
}