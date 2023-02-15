#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

const int alphaSize = 26;
//트라이 구조체
struct Trie {
    //현재 노드에서 해당 문자를 받으면 가는 노드
    Trie *alpha[alphaSize];//알파벳 소문자
    //현재 노드에서 해당문자의 go 목적지가 없을 때 가는 노드
    Trie *fail;
    //현재노드에 도달하면 찾는 문자열
    bool output;

    //생성자
    Trie() {
        for (int i = 0; i < alphaSize; i++) alpha[i] = NULL;
        output = false;
        fail = NULL;
    }
    //소멸자
    ~Trie() {
        for (int i = 0; i < alphaSize; i++) {
            if (alpha[i]) delete alpha[i];
        }
    }
    //삽입
    void insert(string s, int idx) {
        if (idx == s.length()) {//문자열 모두 삽입
            output = true;
            return;
        }

        int next = s[idx] - 'a';//다음 알파벳
        if (alpha[next] == NULL) alpha[next] = new Trie;//다음 노드가 없으면 트라이 생성
        alpha[next]->insert(s, idx + 1);//다음 문자 삽입
    }
};

int n,m;
string temp;
queue<Trie*> q;
Trie* root = new Trie;//트라이 구조

//입력
void input() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        string str;
        cin >> str;
        root->insert(str, 0);
    }
}
//bfs탐색
void bfs() {
    q.push(root);

    while (!q.empty()) {
        Trie* cur = q.front();//현재 노드
        q.pop();

        //다음 지점
        for (int i = 0; i < alphaSize; i++) {
            Trie* next = cur->alpha[i];//다음 트라이

            if (!next) continue;//다음 트라이가 없으면 다음으로
       
            if (cur == root) next->fail = root;//루트의 fail은 루트
            else {
                Trie* prev = cur->fail;
                //fail을 참조할 가장 가까운 조상
                while (prev != root && !prev->alpha[i]) {
                    prev = prev->fail;
                }
                //fail(px) = alpha(fail(p),x)
                if (prev->alpha[i]) prev = prev->alpha[i];
                next->fail = prev;
            }
            if (next->fail->output) next->output = true;
            q.push(next);
        }
    }
}
//검사
void examine() {
    cin >> m;
    for (int i = 0; i < m; i++) {
        string st;
        cin >> st;
        bool result = false;
        Trie* curr = root;//루트부터 시작

        for (int j = 0; j < st.length(); j++) {
            int nextNode = st[j] - 'a';

            //현재노드에서 갈 수 없다면 fail을 계속 따라감
            while (curr != root && !curr->alpha[nextNode]) curr = curr->fail;
            //alpha함수가 존재하면 이동, 루트면 이게 false일 수 있다.
            if (curr->alpha[nextNode]) curr = curr->alpha[nextNode];
            //현재노드에 output이 있으면 찾은것
            if (curr->output) {
                result = true;
                break;
            }
        }
        //결과
        if (result) cout << "YES\n";
        else cout << "NO\n";
    }
}
int main() {
    //빠른 입력
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    input();//입력
    bfs();//bfs탐색
    examine();//검사
    return 0;
}
