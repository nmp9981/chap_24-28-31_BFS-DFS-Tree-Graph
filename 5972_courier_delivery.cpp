#include <iostream>
#include <queue>
using namespace std;

int n,m;
const int maxi = 50001;
const int inf = 500000001;
vector<pair<int, int>> graph[maxi];//그래프
int dist[maxi];//1번으로부터의 거리

//입력
void input() {
    cin >> n >> m ;
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        graph[a].push_back({ b,c });//정점, 거리
        graph[b].push_back({ a,c });
    }
}
//초기화
void init() {
    for (int i = 1; i <= n; i++) dist[i] = inf;
}
//이동
void Move(int start) {
    dist[start] = 0;
    priority_queue<pair<int, int>> pq;
    pq.push({ 0,start });//거리, 정점

    while (!pq.empty()) {
        int cow = -pq.top().first;
        int node = pq.top().second;
        pq.pop();

        if (dist[node] < cow) continue;//더 큰값이 나옴

        //다음 지점
        for (int i = 0; i < graph[node].size(); i++) {
            int nextCow = graph[node][i].second;
            int nextNode = graph[node][i].first;

            if (cow + nextCow < dist[nextNode]) {//거리 갱신
                dist[nextNode] = cow + nextCow;
                pq.push({ -dist[nextNode],nextNode });
            }
        }
    }
    cout << dist[n];//거리
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    input();//입력
    init();//초기화
    Move(1);//이동
    return 0;
}
