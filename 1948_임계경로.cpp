#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int n,m;
int st, ed;
const int maxi = 10001;
vector<pair<int,int>> graph[maxi];//그래프
vector<pair<int, int>> backGraph[maxi];//역추적 그래프
int getNode[maxi] = { 0, };//진입 차수
int arrive[maxi] = { 0, };//각 도시 도착 시간
bool visit[maxi] = { false, };//방문 여부

//max
inline int max(int x, int y) {
    return x > y ? x : y;
}
//입력
void input() {
    cin >> n>>m;
    for (int i = 0; i < m; i++) {
        int a, b,d;
        cin >> a >> b>>d;
        graph[a].push_back({ b,d });//노드, 거리
        backGraph[b].push_back({ a,d });
    }
    cin >> st >> ed;
}
//도시 탐색
void CityTime() {
    queue<int> q;
    q.push(st);//시작 지점
    arrive[st] = 0;

    while (!q.empty()) {
        int node = q.front();//현재 노드
        q.pop();

        //다음 지점
        for (int i = 0; i < graph[node].size(); i++) {
            int next = graph[node][i].first;//다음 노드
            int dist = graph[node][i].second;//거리

            //더 큰 값이 왔을 경우
            if (arrive[next] < arrive[node] + dist) {
                arrive[next] = arrive[node] + dist;
                q.push(next);
            }
        }
    }
    cout << arrive[ed]<<"\n";//도착 시간
}
//도시 역추적
void BackCity() {
    queue<pair<int,int>> q;
    q.push({ ed,arrive[ed] });
    visit[ed] = true;
    int roadCnt = 0;

    while (!q.empty()) {
        int node = q.front().first;
        int times = q.front().second;
        q.pop();

        //다음 지점
        for (int i = 0; i < backGraph[node].size(); i++) {
            int next = backGraph[node][i].first;
            int nextTimes = backGraph[node][i].second;

            if (arrive[next] == arrive[node] - nextTimes) {//시간 조건
                roadCnt++;
                if (visit[next]) continue;//방문 여부
                visit[next] = true;
                q.push({ next,arrive[next] });
            }
        }
    }
    cout << roadCnt;//도로 개수
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    input();//입력
    CityTime();//도시 탐색
    BackCity();//도시 역추적
    return 0;
}
