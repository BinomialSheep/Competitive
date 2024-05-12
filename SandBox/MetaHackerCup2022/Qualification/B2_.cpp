#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
using vs = vector<string>;
using vvi = vector<vector<int>>;
using pii = pair<int, int>;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

void solve(int testCase) {
  /* input */
  int R, C;
  cin >> R >> C;
  vs S(R);
  rep(i, R) cin >> S[i];

  /* solve */
  string ans = "Possible";
  vi dy = {-1, 0, 0, 1};
  vi dx = {0, -1, 1, 0};
  vvi visited(R, vi(C));

  // 隣接4マスに木もしくは空白が2つ以上あるならtrueを返す
  auto hasFriends = [&](int y, int x) {
    int cnt = 0;
    rep(k, 4) {
      int y2 = y + dy[k];
      int x2 = x + dx[k];
      if (y2 < 0 || x2 < 0 || y2 >= R || x2 >= C) continue;
      if (S[y2][x2] == '^' || S[y2][x2] == '.') cnt++;
    }
    return cnt >= 2;
  };
  // 石を始点に幅優先探索し、木を置けないマスに'x'印を付ける
  auto bfs = [&](int startY, int startX) {
    queue<pii> q;
    visited[startY][startX] = 1;
    q.emplace(startY, startX);

    while (!q.empty()) {
      auto p = q.front();
      q.pop();
      rep(k, 4) {
        int y = p.first + dy[k];
        int x = p.second + dx[k];
        if (y < 0 || x < 0 || y >= R || x >= C) continue;
        // 木を2つ隣接させられないマスは'x'印を付けておく
        if (!hasFriends(y, x)) {
          if (S[y][x] == '.') S[y][x] = 'x';
          if (visited[y][x]) continue;
          visited[y][x] = 1;
          q.emplace(y, x);
        }
      }
    }
  };

  if (R == 1 || C == 1) {
    rep(i, R) rep(j, C) {
      if (S[i][j] == '^') ans = "Impossible";
    }
  } else {
    // 木を置けない箇所をBFSで探索
    rep(i, R) rep(j, C) {
      if (S[i][j] == '#') {
        if (visited[i][j]) continue;
        bfs(i, j);
      }
    }
    // 置いていいところ全てに木を置く
    rep(i, R) rep(j, C) if (S[i][j] == '.') S[i][j] = '^';
    // '×'印を元に戻しておく
    rep(i, R) rep(j, C) if (S[i][j] == 'x') S[i][j] = '.';
    // 条件を満たしているかチェック
    rep(i, R) rep(j, C) {
      if (S[i][j] == '^') {
        int cnt = 0;
        rep(k, 4) {
          int y = i + dy[k];
          int x = j + dx[k];
          if (y < 0 || x < 0 || y >= R || x >= C) continue;
          if (S[y][x] == '^') cnt++;
        }
        if (cnt <= 1) ans = "Impossible";
      }
    }
  }

  /* output */
  printf("Case #%d: %s\n", testCase, ans.c_str());
  if (ans == "Possible") {
    rep(i, R) cout << S[i] << "\n";
  }
}

int main() {
  int T;
  cin >> T;
  rep(ti, T) solve(ti + 1);
  return 0;
}