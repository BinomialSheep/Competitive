#include <bits/stdc++.h>

using namespace std;


int *aArray;
long long *sumArray;
long long sumArrayIndex;

void rec(int i, int n, int S[]){
  if(i == n){
    // ここに来ると組み合わせのうちの1つになっている
    // for(int j = 0; j < n; j++) cout << " S[" << j << "]：" << S[j]; cout << endl;
    int sum = 0;
    for(int j = 0; j < n; j++){
      if(S[j] == 1) sum += aArray[j];
    }
    sumArray[sumArrayIndex] = sum;
    // cout << sumArrayIndex << " " << sumArray[sumArrayIndex] << endl;
    sumArrayIndex++;
    return;
  }
  rec(i + 1, n, S); // S[i] = 0のやつはS[i+1]以降全パターンはこっち
  S[i] = 1;
  rec(i + 1, n, S); // S[i] = 1のやつS[i+1]以降全パターンこっち
  S[i] = 0; // 0に戻しておく
}


void makeCombination(int n) {
  int S[n];
  for(int i = 0; i < n; i++){
    S[i] = 0;
  }
  rec(0, n, S);
}


int main() {
  int n, q;
  scanf("%d", &n); // n <= 20
  int A[n];
  for(int i = 0; i < n; i++) scanf("%d", &A[i]);
  scanf("%d", &q); // q <= 200
  int m[q];
  for(int i = 0; i < q; i++) scanf("%d", &m[i]);

  
  // A[n]から任意個取り出して足した配列を作る（2 ^ 20 = 10^6 なので全探索で間に合う）
  aArray = A; // グルーバル変数に入れてる（全部の引数に入れるのが面倒なので）
  long long sLength = (long long)pow(2, n);
  long long sArray[sLength];
  sumArray = sArray;
  sumArrayIndex = 0;
  makeCombination(n);

  for(int i = 0; i < q; i++){
    bool flag = false;
    for(int j = 0; j < sLength; j++){
      if(m[i] == sumArray[j]){
        flag = true;
        break;
      }
    }
    if(flag){
      printf("yes\n");
    } else {
      printf("no\n");
    }
  }


  return 0;
}