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

static const int DIAGONAL = 1;
static const int TOP = 0;

struct Item {
  int value, weight;
};

int N, W;
static const int NMAX = 105;
static const int WMAX = 10005;
vector<Item> items;
// C[i][w]は、i個目までの品物を考慮して大きさwのナップザックに入れる場合の価値合計の最大値
// G[i][w]は、大きさwのナップザックに入れる時の品物iの選択状態（選択ならDIAGONAL,
// 非選択ならTOP）
vector<vector<int>> C, G;

void compute(int &maxValue, vector<int> &selection) {
  // 初期化
  // 0個目までの品物をナップザックに入れたら価値0
  for (int w = 0; w <= W; w++) {
    C[0][w] = 0;
    G[0][w] = DIAGONAL;
  }
  // 大きさ0のナップザックに入れる場合の価値最大は0
  for (int i = 1; i <= N; i++) C[i][0] = 0;
  // 更新
  for (int i = 1; i <= N; i++) {
    for (int w = 1; w <= W; w++) {
      // items[i]を入れないパターン
      C[i][w] = C[i - 1][w];
      G[i][w] = TOP;
      if (items[i].weight > w) continue;
      if (items[i].value + C[i - 1][w - items[i].weight] > C[i - 1][w]) {
        // items[i]を入れた方が価値を高く出来るなら入れる
        C[i][w] = items[i].value + C[i - 1][w - items[i].weight];
        G[i][w] = DIAGONAL;
      } else {
        // items[i]を入れない方が価値高いなら入れない
      }
    }
  }
  // answer
  maxValue = C[N][W];
  // 選択の復元
  selection.clear();
  for (int i = N, w = W; i >= 1; i--) {
    if (G[i][w] == DIAGONAL) {
      selection.push_back(i);
      w -= items[i].weight;
    }
  }
  reverse(selection.begin(), selection.end());
}

int main() {
  // input
  cin >> N >> W;
  items.resize(N + 1);
  vector<vector<int>> tempC(N + 1, vector<int>(W + 1));
  vector<vector<int>> tempG(N + 1, vector<int>(W + 1));
  C = tempC;
  G = tempG;
  items[0].value = 0;
  items[0].weight = 0;
  rep(i, N) cin >> items[i + 1].value >> items[i + 1].weight;
  // solve
  int maxValue;
  vector<int> selection;
  compute(maxValue, selection);

  cout << maxValue << endl;

  return 0;
}