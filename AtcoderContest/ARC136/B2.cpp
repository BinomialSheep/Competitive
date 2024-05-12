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

int main() {
  // input
  int n;
  cin >> n;
  vector<int> A(n), B(n);
  rep(i, n) cin >> A[i];
  rep(i, n) cin >> B[i];

  // solve

  // 特殊ケース判定
  int specific = 0;
  vector<int> Acopy, Bcopy;
  copy(A.begin(), A.end(), back_inserter(Acopy));
  copy(B.begin(), B.end(), back_inserter(Bcopy));
  // Aに同じ数が2つ以上あればただちにtrue
  rep(i, n - 1) {
    if (Acopy[i] == Acopy[i + 1]) specific = 1;
  }
  // AとBで使用している数字が違う場合はただちにfalse
  sort(Acopy.begin(), Acopy.end());
  sort(Bcopy.begin(), Bcopy.end());
  rep(i, n) {
    if (Acopy[i] != Bcopy[i]) specific = 2;
  }

  rep(i, n - 2) {
    // B[0]からB[n-3]までを一致させる
    int index = find(A.begin(), A.end(), B[i]) - A.begin();

    while (true) {
      if (index <= i + 1) {
        if (index == i + 1) {
          // cout << " i+1パターン" << endl;
          //  ABCを2回triple-shiftしてBCAとする
          swap(A[index], A[index - 1]);
          swap(A[index], A[index + 1]);
        }
        break;
      }
      // 2以上離れていたら1回triple-shiftして続行
      // cout << " i+2パターン" << endl;
      // rep(i, n) cout << A[i] << " ";
      swap(A[index - 2], A[index - 1]);
      swap(A[index - 2], A[index]);

      index -= 2;
    }
  }

  // 判定
  bool isYes = false;

  if (A[n - 2] == B[n - 2] && A[n - 1] == B[n - 1]) isYes = true;

  if (specific == 1) isYes = true;
  if (specific == 2) isYes = false;

  // output
  cout << (isYes ? "Yes" : "No") << endl;

  return 0;
}