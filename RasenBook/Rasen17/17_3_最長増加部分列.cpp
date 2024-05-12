#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
// g++ --std=c++14 -I "/mnt/c/Program Files (x86)/Microsoft Visual
// Studio/2019/Community/VC/Tools/MSVC/14.29.30037/include" code.cpp
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define MAX 100000
#define INFTY (1 << 29)
// 浮動小数点の誤差を考慮した等式
#define EPS (1e-10)
#define equal(a, b) (fabs((a) - (b)) < EPS)

// O(n log n)

int lis(vector<int> &A) {
  // L[i]は、長さがi+1であるような増加部分列の最後の要素のうち、最小の値
  // 例えば1, 6, 2, 3ならL[0]=1, L[1]=2, L[2]=3。
  vector<int> L(A.size());
  L[0] = A[0];
  // lenは、i番目の要素までを使った時点の最長増加部分列の長さを表す整数
  int len = 1;

  for (int i = 1; i < A.size(); i++) {
    if (L[len - 1] < A[i]) {
      // 増加部分列の長さを更新できるならする
      L[len++] = A[i];
    } else {
      // よりリーズナブルな増加部分列に置き換えられるならする（二分探索を使ってA[i]以上となる最初の位置を計算）
      *lower_bound(L.begin(), L.begin() + len, A[i]) = A[i];
    }
  }

  return len;
}

int main() {
  int n;
  cin >> n;
  vector<int> A(n);
  rep(i, n) cin >> A[i];

  cout << lis(A) << endl;

  return 0;
}