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
  vector<int> origA(n), B(n);
  rep(i, n) cin >> origA[i];
  rep(i, n) cin >> B[i];

  stack<vector<int>> oldAs;
  stack<vector<int>> newAs;

  oldAs.push(origA);

  // solve
  bool errFlag = false;
  rep(i, n - 2) {
    // B[0]からB[n-3]までを一致させる
    while (!oldAs.empty()) {
      auto A = oldAs.top();

      // 複数パターンある時は全部試す
      vector<int> indexVec;

      auto startItr = A.begin();
      while (true) {
        auto itr = find(startItr, A.end(), B[i]);
        if (itr == A.end()) break;
        indexVec.push_back(itr - A.begin());
        startItr = ++itr;
      }
      // Bの値がAに存在しなければただちにNo
      if (indexVec.empty()) {
        errFlag = true;
        break;
      }

      // rep(j, indexVec.size()) cout << "index:" << indexVec[j] << endl;

      rep(j, indexVec.size()) {
        A = oldAs.top();
        int index = indexVec[j];
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
          // rep(i, n) cout << A[i] << " ";
          index -= 2;
        }
        // rep(i, n) cout << A[i] << " ";
        // cout << endl;
        newAs.push(A);
      }
      oldAs.pop();
    }
    oldAs = newAs;
    while (!newAs.empty()) newAs.pop();
  }

  // 判定
  bool isYes = false;
  while (!oldAs.empty()) {
    auto A = oldAs.top();
    // rep(i, n) cout << A[i] << endl;
    oldAs.pop();
    if (A[n - 2] == B[n - 2] && A[n - 1] == B[n - 1]) isYes = true;
  }

  if (errFlag) isYes = false;

  // output
  cout << (isYes ? "Yes" : "No") << endl;

  return 0;
}