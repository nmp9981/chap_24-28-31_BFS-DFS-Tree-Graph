#include <iostream>
using namespace std;

int n, k;
int idx = 1;
const int maxi = 1000001;
int tree[maxi];//세그먼트 트리

//max
inline int max(int x, int y) {
    return x > y ? x : y;
}
//min
inline int min(int x, int y) {
    return x < y ? x : y;
}
//입력
void Input() {
    cin >> n >> k;
}
//초기화
int Init(int node, int start, int end) {
    if (start == end) return tree[node] = 1;
    int mid = (start + end) / 2;
    return tree[node] = Init(2 * node, start, mid) + Init(2 * node+1, mid + 1, end);
}
//삭제
int Delete(int node, int start, int end, int del) {
    tree[node]--;
    if (start == end) return 0;
    else {
        int mid = (start + end) / 2;
        if (del <= mid) return Delete(2 * node, start, mid, del);
        else return Delete(2 * node + 1, mid + 1, end, del);
    }
}
//쿼리
int Query(int node, int start,int end, int order){ //order은 순서
    if (start == end) return start;
    int mid = (start + end) / 2;

    if (order <= tree[2 * node]) return Query(2 * node, start, mid, order);
    else return Query(2 * node + 1, mid + 1, end, order - tree[2 * node]);
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    Input();//입력
    Init(1,1,n);//초기화

    //요세푸스 수열 출력
    cout << "<";
    for (int i = 0; i < n; i++) {
        //다음 순서
        int size = n - i;//인구 수
        idx += (k - 1);

        //인덱스 초과
        if (idx % size == 0) idx = size;
        else if (idx > size) idx = idx % size;

        //다음 순서
        int num = Query(1, 1, n, idx);

        //해당 번호 제거
        Delete(1, 1, n, num);

        //출력
        if (i == n - 1) cout << num;
        else cout << num << ", ";
    }
    cout << ">";
    return 0;
}
