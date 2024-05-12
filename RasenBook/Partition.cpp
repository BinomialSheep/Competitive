#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define MAX 100000
#define SENTINEL 200000000





int partition(int A[], int p, int r) {
  int x = A[r];
  int i = p - 1;

  for(int j = p; j < r; j++) {
    if(A[j] <= x){
      i++;
      swap(A[i], A[j]);
    }
  }
  swap(A[i + 1], A[r]);

  return i + 1;
}




int main() {
  // 入力
  int n;
  int S[MAX];
  scanf("%d", &n);
  for(int i = 0; i < n; i++) scanf("%d", &S[i]);

  // 戻り値はpartitionのインデックス
  int partIndex = partition(S, 0, n - 1);

  // 出力
  for(int i = 0; i < partIndex; i++) printf("%d ", S[i]);
  printf("[%d]", S[partIndex]);
  for(int i = partIndex + 1; i < n; i++) printf(" %d", S[i]);
  printf("\n");

  return 0;
}