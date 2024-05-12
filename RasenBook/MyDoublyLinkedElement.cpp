#include <bits/stdc++.h>
using namespace std;


struct MyDoublyLinkedElement {
  MyDoublyLinkedElement *prev;
  int value;
  MyDoublyLinkedElement *next;
};


class MyDoublyLinkedList {
  public:
  MyDoublyLinkedElement  *headAddr;
  MyDoublyLinkedElement *tailAddr;
  MyDoublyLinkedList(){
    headAddr = new MyDoublyLinkedElement;
    tailAddr = new MyDoublyLinkedElement;
    headAddr->next = tailAddr;
    tailAddr->prev = headAddr;

  //  cout << headAddr << " " << headAddr->next << " " << tailAddr << endl;
  }
  // 連結リストの先頭にキーxを持つ要素を追加
  void insert(int x){
    MyDoublyLinkedElement *newHead = new MyDoublyLinkedElement;
    newHead->value = x;
    newHead->next = headAddr;
    headAddr->prev = newHead;
    headAddr = newHead;
   // cout << "insert：" << headAddr << " " << headAddr->next << " " << headAddr->next->next << endl;
  }
  // キーxを持つ最初の要素を連結リストから削除
  void myDelete(int x){
    MyDoublyLinkedElement *dle = headAddr;
    while(true){
      // 終端に達した場合、なにも削除せずにbreak
      if(dle == tailAddr->prev) break;
      // キーxを持つ最初の要素を連結リストから削除
      if(dle->value == x){
        // cout << "value == x" << endl;
        //cout << dle->prev->next << " " << dle->next->prev << endl;
        if(dle == headAddr){
          headAddr = dle->next;
        } else {
          dle->prev->next = dle->next;
        }
        dle->next->prev = dle->prev;
        delete dle;
        break;
      }
      // cout << "value != x" << endl;
      dle = dle->next;
    }
  }

  // 連結リストの先頭の要素を削除
  void deleteFirst(){
    MyDoublyLinkedElement *temp = headAddr;
    headAddr = headAddr->next;
    delete temp;
  }

  // 連結リストの末尾の要素を削除
  void deleteLast(){
    MyDoublyLinkedElement *temp = tailAddr;
    tailAddr = tailAddr->prev;
    delete temp;
  }

  // 連結リストのキーを空白区切りで出力
  void print(){
    MyDoublyLinkedElement *dle = headAddr;
    while(true){
      // cout << "print:" << dle << " " << dle->next << " " << tailAddr << endl;
      // 終端に達したら終わり
      if(dle == tailAddr->prev){ 
        printf("\n");
        break;
      }
      if(dle == headAddr){
        printf("%d", dle->value);
      } else {
        printf(" %d", dle->value);
      }
      dle = dle->next;
    }
  }

  void printForDebug(){
    cout << headAddr << " " << tailAddr << endl;
  }

};





int main() {

  MyDoublyLinkedList myDLL;

  int n;
  scanf("%d", &n);
  char cmd[20];
  int x;
  for(int i = 0; i < n; i++){
    scanf("%s %d", cmd, &x);
    if(cmd[0] == 'i'){
      myDLL.insert(x);
     //myDLL.print();
      continue;
    }
    if(strlen(cmd) == 6){
      myDLL.myDelete(x);
      continue;
    }
    if(cmd[6] == 'F'){
      myDLL.deleteFirst();
    } else {
      myDLL.deleteLast();
    }
  }

  myDLL.print();

  return 0;
}