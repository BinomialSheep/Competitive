#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
// g++ --std=c++14 -I "/mnt/c/Program Files (x86)/Microsoft Visual
// Studio/2019/Community/VC/Tools/MSVC/14.29.30037/include" code.cpp
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define MAX 10000
#define INFTY (1 << 29)
// 浮動小数点の誤差を考慮した等式
#define EPS (1e-10)
#define equal(a, b) (fabs((a) - (b)) < EPS)

#define N 3
#define N2 9

struct Puzzle {
  int f[N2];
  int space;
  string path;

  bool operator<(const Puzzle &p) const {
    rep(i, N2) {
      if (f[i] == p.f[i]) continue;
      return f[i] > p.f[i];
    }
    return false;
  }
};

static const int dx[4] = {-1, 0, 1, 0};
static const int dy[4] = {0, -1, 0, 1};
static const char dir[4] = {'u', 'l', 'd', 'r'};

// 完成判定
bool isTarget(Puzzle p) {
  rep(i, N2) {
    if (p.f[i] != i + 1) return false;
  }
  return true;
}

string bfs(Puzzle s) {
  queue<Puzzle> Q;
  map<Puzzle, bool> V;
  Puzzle u, v;
  s.path = "";
  Q.push(s);
  V[s] = true;

  while (!Q.empty()) {
    u = Q.front();
    Q.pop();
    // 完成したら経路を返す
    if (isTarget(u)) return u.path;
    int sx = u.space / N;
    int sy = u.space % N;
    // 空白の隣接4つを動かす
    rep(r, 4) {
      int tx = sx + dx[r];
      int ty = sy + dy[r];
      // 動かせない時
      if (tx < 0 || ty < 0 || tx >= N || ty >= N) continue;
      v = u;
      // 空白と動かした側を入れかえ
      swap(v.f[u.space], v.f[tx * N + ty]);
      v.space = tx * N + ty;
      // 初見の局面ならキューに追加
      if (!V[v]) {
        V[v] = true;
        v.path += dir[r];
        Q.push(v);
      }
    }
  }
  return "unsolvable";
}

int main() {
  Puzzle in;

  rep(i, N2) {
    cin >> in.f[i];
    if (in.f[i] == 0) {
      // 空白
      in.f[i] = N2;
      in.space = i;
    }
  }
  string ans = bfs(in);
  // 経路の長さが解答
  cout << ans.size() << endl;

  return 0;
}