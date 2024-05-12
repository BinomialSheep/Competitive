#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define MAX 2000000000

int H; // 木のサイズ
vector<int> priorityQ;

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

// vector用
void maxHeapify(int v) {
  int l = left(v);
  int r = right(v);
  int largest;
  int size = priorityQ.size() - 1;
  // 左の子、自分、右の子で値が最大のノードを選ぶ
  if (l <= size && priorityQ[l] > priorityQ[v]) largest = l;
  else largest = v;
  if (r <= size && priorityQ[r] > priorityQ[largest]) largest = r;

  // cout << size << " " << l << " " << v << " " << r << " " << largest << endl; 

  if (largest != v) {
    swap(priorityQ[v], priorityQ[largest]);
    maxHeapify(largest);
  }
}

void buildMaxHeap(int A[]) {
  
  for (int i = H/2; i >= 1; i--) maxHeapify(A, i);
}

void insert(int v) {
  priorityQ.push_back(v);
  // 親と比較し、自分の方が大きければswapを繰り返す
  int i = priorityQ.size() - 1;
  int pi, pv;
  while(i != 1) {
    pi = parent(i);
    if(priorityQ[pi] <= v) {
      swap(priorityQ[i], priorityQ[pi]);
      i = pi;
    } else {
      break;
    }
  }
}

int extract() {
  // 最大値はrootなので、rootの削除を行う
  // 末尾と交換した上で末尾(=rootの値)を削除
  int root = priorityQ[1];
  swap(priorityQ[1], priorityQ.back());
  priorityQ.pop_back();
  // 先頭の要素の位置を正すことでmax heapを維持
  maxHeapify(1);

  return root;
}


int main() {

  // 1オリジンにするためにindex 0を埋めておく
  priorityQ.push_back(-1);

  string command;
  int value;
  while(true) {
    cin >> command;
    if(command == "insert"){
      cin >> value;
      insert(value);
      // for(int v : priorityQ) cout << v << " "; cout << endl;
    } else if (command == "extract") {
      cout << extract() << endl;
    } else if (command == "end") {
      break;
    }
  }

  return 0;
}