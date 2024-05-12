#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define MAX 500000

int H; // 木のサイズ

int parent(int x){
  return x / 2;
}
int left(int x) {
  return 2 * x;
}
int right(int x) {
  return 2 * x + 1;
}

void maxHeapify(int A[], int i) {
  int l = left(i);
  int r = right(i);
  int largest;
  // 左の子、自分、右の子で値が最大のノードを選ぶ
  if (l <= H && A[l] > A[i]) largest = l;
  else largest = i;
  if (r <= H && A[r] > A[largest]) largest = r;

  // cout << l << " " << i << " " << r << " " << largest << endl; 

  if (largest != i) {
    swap(A[i], A[largest]);
    maxHeapify(A, largest);
  }
}

void buildMaxHeap(int A[]) {
  
  for (int i = H/2; i >= 1; i--) maxHeapify(A, i);
}



int main() {
  int A[MAX+1]; // 1オリジンなので+1している
  cin >> H;
  for (int i = 1; i <= H; i++ ) cin >> A[i];

  buildMaxHeap(A);

  // 出力
  for(int i = 1; i <= H; i++ ) {
    cout << " " << A[i];
  }
  cout << endl;


  


  return 0;
}