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

#define N 4
#define N2 16

static const int dx[4] = {0, -1, 0, 1};
static const int dy[4] = {1, 0, -1, 0};
static const char dir[4] = {'r', 'u', 'l', 'd'};
int MDT[N2][N2];

struct Puzzle {
  int f[N2], space, MD;
  int cost;

  bool operator<(const Puzzle &p) const {
    rep(i, N2) {
      if (f[i] == p.f[i]) continue;
      return f[i] < p.f[i];
    }
    return false;
  }
};

struct State {
  Puzzle puzzle;
  int estimated;
  bool operator<(const State &s) const { return estimated > s.estimated; }
};

int getAllMD(Puzzle pz) {
  int sum = 0;
  rep(i, N2) {
    if (pz.f[i] == N2) continue;
    sum += MDT[i][pz.f[i] - 1];
  }
  return sum;
}

int astar(Puzzle s) {
  priority_queue<State> PQ;
  s.MD = getAllMD(s);
  s.cost = 0;
  map<Puzzle, bool> V;
  Puzzle u, v;
  State initial;
  initial.puzzle = s;
  initial.estimated = getAllMD(s);
  PQ.push(initial);

  while (!PQ.empty()) {
    State st = PQ.top();
    PQ.pop();
    u = st.puzzle;

    if (u.MD == 0) return u.cost;
    V[u] = true;

    int sx = u.space / N;
    int sy = u.space % N;

    rep(r, 4) {
      int tx = sx + dx[r];
      int ty = sy + dy[r];
      if (tx < 0 || ty < 0 || tx >= N || ty >= N) continue;
      v = u;

      v.MD -= MDT[tx * N + ty][v.f[tx * N + ty] - 1];
      v.MD += MDT[sx * N + sy][v.f[tx * N + ty] - 1];

      swap(v.f[sx * N + sy], v.f[tx * N + ty]);
      v.space = tx * N + ty;
      if (!V[v]) {
        v.cost++;
        State news;
        news.puzzle = v;
        news.estimated = v.cost + v.MD;
        PQ.push(news);
      }
    }
  }
  return -1;
}

int main() {
  rep(i, N2) rep(j, N2) MDT[i][j] = abs(i / N - j / N) + abs(i % N - j % N);

  Puzzle in;

  rep(i, N2) {
    cin >> in.f[i];
    if (in.f[i] == 0) {
      in.f[i] = N2;
      in.space = i;
    }
  }
  cout << astar(in) << endl;

  return 0;
}