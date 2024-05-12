#include <bits/stdc++.h>
using namespace std;
using ll = long long;
//#include <atcoder/all>
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define MAX 10000
#define INFTY (1 << 29)
// 浮動小数点の誤差を考慮した等式
#define EPS (1e-10)
#define equal(a, b) (fabs((a) - (b)) < EPS)
ll llMax(ll x, ll y) { return (x >= y) ? x : y; }
ll llMin(ll x, ll y) { return (x <= y) ? x : y; }

class DisjointSet {
 public:
  // rankは木の高さ（0-origen), pはrootの要素（rootのrootは自分自身）
  vector<int> rank, p;

  DisjointSet() {}
  DisjointSet(int size) {
    // 長さsizeで初期値0の動的配列を作る
    rank.resize(size, 0);
    p.resize(size, 0);
    // 0,..,n-1をそれぞれ唯一の要素とするn個の互いに素な集合を作る
    rep(i, size) makeSet(i);
  }

  void makeSet(int x) {
    p[x] = x;
    rank[x] = 0;
  }

  // 新しく要素数1の木を追加する
  int addSet() {
    int ret = p.size();
    p.push_back(ret);
    rank.push_back(0);
    return ret;
  }

  // 同じ木に所属しているか
  bool same(int x, int y) { return findSet(x) == findSet(y); }
  // xが所属する木とyが所属する木の合成
  void unite(int x, int y) { link(findSet(x), findSet(y)); }
  // 高い方に合成する（rankの更新を減らすため）
  void link(int x, int y) {
    if (x == y) return;
    if (rank[x] > rank[y]) {
      p[y] = x;
    } else {
      p[x] = y;
      if (rank[x] == rank[y]) {
        // 同じ高さ同士の木を合成した場合はインクリメント
        rank[y]++;
      }
    }
  }
  // 再帰的に親を辿ってrootを見つける。この実装では経路圧縮はしない。
  int findSet(int x) {
    if (x != p[x]) {
      p[x] = findSet(p[x]);
    }
    return p[x];
  }
};

int main() {
  /* input */
  int N;
  cin >> N;
  vector<int> P(N);
  rep(i, N) cin >> P[i];
  vector<int> Q(N);
  rep(i, N) cin >> Q[i];

  /* solve */
  // 表と裏のindex
  vector<int> PIndex(N);
  vector<int> QIndex(N);
  rep(i, N) {
    PIndex[P[i]] = i;
    QIndex[Q[i]] = i;
  }

  // 素集合データ木を作る
  DisjointSet unionFindTree(0);
  rep(i, N) {
    unionFindTree.addSet();
    // 既出なら合成
    if (PIndex[P[i]] < i) {
      unionFindTree.unite(i, P[i]);
    }
    if (QIndex[Q[i]] < i) {
      unionFindTree.unite(i, Q[i]);
    }
  }

  /* output */
  

  return 0;
}