#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define MAX 100000
#define SENTINEL 200000000


class Card {
  public:
    char suit;
    ll number;
    Card() {}
    Card(char s, ll n) {
      this->suit = s;
      this->number = n;
    }
};



int partition(Card A[], int p, int r) {
  int x = A[r].number;
  int i = p - 1;

  for(int j = p; j < r; j++) {
    if(A[j].number <= x){
      i++;
      swap(A[i], A[j]);
    }
  }
  swap(A[i + 1], A[r]);

  return i + 1;
}

void quickSort(Card A[], int p, int r) {
  if(p < r) {
    int q = partition(A, p, r);
    quickSort(A, p, q - 1);
    quickSort(A, q + 1, r);
  }
}


// 既知の安定ソートであるマージソートを利用
const int INFTY = (int)pow(10, 10);
int merge(Card A[], int left, int mid, int right) {
  // cout << "merge開始" << left << " to " << right << endl;
  int swapNum = 0;
  int n1 = mid - left;
  int n2 = right - mid;
  Card L[n1+1], R[n2+1];
  for(int i = 0; i < n1; i++) L[i] = A[left + i];
  for(int i = 0; i < n2; i++) R[i] = A[mid + i];
  L[n1].number = INFTY;
  R[n2].number = INFTY;
  int i = 0;
  int j = 0;
  // 整列済み左配列の先頭と整列済み右配列の先頭を比較し、小さい方をマージ後配列の後ろに追加
  for(int k = left; k < right; k++){
    // cout << "merge中" << i << "←左 index 右→ " << j << endl;
    swapNum++;
    if(L[i].number <= R[j].number){
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
int mergeSort(Card A[], int left, int right) {
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
  // 入力
  int n;
  Card S[MAX];
  scanf("%d", &n);
  for(int i = 0; i < n; i++){
    char suit;
    ll number;
    scanf(" %c %lld", &suit, &number);
    Card card(suit, number);
    S[i] = card;
  }

  // 比較用にディープコピーしておく
  Card copyS[n];
  for(int i = 0; i < n; i++) copyS[i] = S[i];

  // クイックソートの実行
  quickSort(S, 0, n - 1);

  /* クイックソートの結果が安定かチェック */
  // 安定ソートであるマージソートの実行
  mergeSort(copyS, 0, n);
  // クイックソートとマージソートの結果が等しいかチェック
  bool isStable = true;
  for(int i = 0; i < n; i++){
    if(S[i].suit != copyS[i].suit) {
      isStable = false;
      break;
    }
  }

  // 出力
  if(isStable){
    printf("Stable\n");
  } else {
    printf("Not stable\n");
  }

  for(int i = 0; i < n; i++) printf("%c %lld\n", S[i].suit, S[i].number);

  return 0;
}