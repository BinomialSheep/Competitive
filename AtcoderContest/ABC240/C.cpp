#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
// g++ --std=c++14 -I "/mnt/c/Program Files (x86)/Microsoft Visual
// Studio/2019/Community/VC/Tools/MSVC/14.29.30037/include" code.cpp
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define MAX 10000
#define INTFY (1 << 29)

vector<int> c(100);
int n;

// 未計算は-1, 計算してダメなら0, 計算してOKなら1
vector<vector<int>> dp(101, vector<int>(10001, -1));

// i番目以降の要素を使ってmを作れる場合trueを返す
int solve(int i, int m) {
  if (dp[i][m] != -1) return dp[i][m];
  if (m == 0) {
    dp[i][m] = 1;
  } else if (i >= n - 1) {
    dp[i][m] = 0;
  } else if (solve(i + 1, m)) {
    dp[i][m] = 1;
  } else if (solve(i + 1, m - c[i])) {
    dp[i][m] = 1;
  } else {
    dp[i][m] = 0;
  }
  return dp[i][m];
}

int main() {
  int x;
  cin >> n >> x;
  vector<int> a(n), b(n);
  int aSum = 0, bSum = 0;
  rep(i, n) {
    cin >> a[i] >> b[i];
    aSum += a[i];
    bSum += b[i];
    c[i] = b[i] - a[i];
  }

  if (aSum > x || bSum < x) {
    cout << "No" << endl;
    return 0;
  }
  if (aSum == x || bSum == x) {
    cout << "Yes" << endl;
    return 0;
  }

  // Cを使ってx-aSumを作れるかという問題に還元された
  int ans = solve(0, x - aSum);

  cout << (ans == 1 ? "Yes" : "No") << endl;

  return 0;
}