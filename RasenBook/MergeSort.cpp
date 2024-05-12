#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int INFTY = (int)pow(10, 10);


int merge(ll A[], int left, int mid, int right) {
  // cout << "merge開始" << left << " to " << right << endl;
  int swapNum = 0;
  int n1 = mid - left;
  int n2 = right - mid;
  ll L[n1+1], R[n2+1];
  for(int i = 0; i < n1; i++) L[i] = A[left + i];
  for(int i = 0; i < n2; i++) R[i] = A[mid + i];
  L[n1] = INFTY;
  R[n2] = INFTY;
  int i = 0;
  int j = 0;

  // 整列済み左配列の先頭と整列済み右配列の先頭を比較し、小さい方をマージ後配列の後ろに追加
  for(int k = left; k < right; k++){
    // cout << "merge中" << i << "←左 index 右→ " << j << endl;
    swapNum++;
    if(L[i] <= R[j]){
      A[k] = L[i];
      i++;
    } else {
      A[k] = R[j];
      j++;
    }
  }
  // cout << "merge終了 "; for(int k = left; k < right; k++) {cout << A[k] << " ";} cout << endl;
  return swapNum;
}




int mergeSort(ll A[], int left, int right) {
  int swapNum = 0;

  if(left + 1 < right) {
    int mid = (left + right) / 2;
    swapNum += mergeSort(A, left, mid);
    swapNum += mergeSort(A, mid, right);
    swapNum += merge(A, left, mid, right);
  }

  return swapNum;
}



int main() {
  int n;
  ll S[500000];
  scanf("%d", &n);
  for(int i = 0; i < n; i++) scanf("%lld", &S[i]);
  
  int swapNum = mergeSort(S, 0, n);

  for(int i = 0; i < n - 1; i++) {
    printf("%lld ", S[i]);
  }
  printf("%lld\n", S[n - 1]);
  printf("%d\n", swapNum);



  


  return 0;
}