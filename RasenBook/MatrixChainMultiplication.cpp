#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

static const int N = 100;


int main() {
  int n, p[N + 1], m[N + 1][N + 1];
  cin >> n;
  // p[i]はi + 1個目の数字の行数であり、i個目の数字の列数
  for (int i = 1; i <= n; i++ ) cin >> p[i - 1] >> p[i];

  // m[i][j]はi個目からj個目の数字の掛け算の最小総回数
  // m[i][i]はなにも掛けないので0
  for (int i = 1; i <= n; i++) m[i][i] = 0;

  for (int l = 2; l <= n; l++) {
    for(int i = 1; i <= n - l + 1; i++ ) {
      int j = i + l - 1;
      m[i][j] = (1 << 21);
      for (int k = i; k <= j - 1; k++ ) {
        m[i][j] = min(m[i][j], m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j]);
      }
    }
  } 

  cout << m[1][n] << endl;


  return 0;
  
}