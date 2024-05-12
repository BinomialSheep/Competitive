#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define MAX 2000000



void countingSort(vector<int> &A, vector<int> &B, int k) {
  // Cの初期化 NOTE：C[k]には、Aにおける値k以下の個数が格納される
  int C[k + 1];
  for(int i = 0; i <= k; i++) C[i] = 0;

  // C[i]にiの出現数を記録
  for(int j = 0; j < A.size(); j++) C[A[j]]++;

  // C[i]にi以下の数の出現数を記録する
  for(int i = 1; i <= k; i++) C[i] += C[i - 1];

  /* print debug 
  for(int i = 0; i <= 10; i++) cout << C[i] << " ";
  cout << endl;
  */


  for(int j = A.size() - 1; j >= 0; j--) {
    B[C[A[j]] - 1] = A[j];
    C[A[j]]--;
  }

  /* print debug
  for(int i = 0; i < A.size(); i++) cout << B[i] << " ";
  cout << endl;
  */

}





int main() {
  // 入力
  int n;
  scanf("%d", &n);
  vector<int> A(n);
  vector<int> B(n);
  for(int i = 0; i < n; i++) scanf("%d", &A[i]);

  // ソートの実行
  int MAX_VALUE = 10000;
  countingSort(A, B, MAX_VALUE);

  // 出力
  for(int i = 0; i < n - 1; i++) {
    printf("%d ", B[i]);
  }
  printf("%d\n", B[n -1]);


  return 0;
}