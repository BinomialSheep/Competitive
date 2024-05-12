#include <bits/stdc++.h>

using namespace std;

typedef long long ll;


const int INFTY = (int)pow(10, 10);

ll merge(ll A[], int left, int mid, int right) {
  // cout << "merge開始" << left << " to " << right << endl;
  ll inversionNum = 0;
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
    if(L[i] <= R[j]){
      A[k] = L[i];
      i++;
    } else {
      A[k] = R[j];
      inversionNum += n1 - i;
      j++;
    }
  }
  // cout << "merge終了 "; for(int k = left; k < right; k++) {cout << A[k] << " ";} cout << endl;
  return inversionNum;
}


ll mergeSort(ll A[], int left, int right) {
  ll inversionNum = 0;

  if(left + 1 < right) {
    int mid = (left + right) / 2;
   inversionNum += mergeSort(A, left, mid);
   inversionNum += mergeSort(A, mid, right);
   inversionNum += merge(A, left, mid, right);
  }

  return inversionNum;
}





int main() {
  int n;
  ll S[200000];
  scanf("%d", &n);
  for(int i = 0; i < n; i++) scanf("%lld", &S[i]);
  
  ll inversionNum = mergeSort(S, 0, n);

  /*
  for(int i = 0; i < n - 1; i++) {
    printf("%lld ", S[i]);
  }
  printf("%lld\n", S[n - 1]);
  */
  printf("%lld\n", inversionNum);

  // 5
  // 3 5 2 1 4
  // out 6

  


  return 0;
}