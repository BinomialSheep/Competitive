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

#define N 8
#define FREE -1
#define NOT_FREE 1

vector<int> row(N, FREE), col(N, FREE), dpos(2 * N - 1, FREE),
    dneg(2 * N - 1, FREE);
vector<vector<bool>> X(N, vector<bool>(N, false));

void printBoard() {
  rep(i, N) {
    rep(j, N) {
      if (X[i][j] && row[i] != j) return;
    }
  }
  rep(i, N) {
    rep(j, N) cout << (row[i] == j ? "Q" : ".");
    cout << endl;
  }
}

void recursive(int i) {
  // cout << "i " << i << endl;
  if (i == N) {
    // クイーンの配置に成功
    printBoard();
    return;
  }
  rep(j, N) {
    // (i, j)が他のクイーンに襲撃されている場合は無視
    if (NOT_FREE == col[j] || NOT_FREE == dpos[i + j] ||
        NOT_FREE == dneg[i - j + N - 1])
      continue;
    // (i, j)にクイーンを配置する
    row[i] = j;
    col[j] = dpos[i + j] = dneg[i - j + N - 1] = NOT_FREE;
    // 次の行を試す
    recursive(i + 1);
    // (i, j)に配置されているクイーンを取り除く
    row[i] = col[j] = dpos[i + j] = dneg[i - j + N - 1] = FREE;
  }
  // クイーンの配置に失敗
}

int main() {
  // initialize();
  // rep(i, N) rep(j, N) X[i][j] = false;

  int k;
  cin >> k;
  rep(i, k) {
    int r, c;
    cin >> r >> c;
    X[r][c] = true;
  }

  recursive(0);

  return 0;
}