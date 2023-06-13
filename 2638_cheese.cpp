#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int n,m;
int times = 0;
const int maxi = 101;
int world[maxi][maxi];//맵
bool visit[maxi][maxi];//방문 여부
//4방 탐색
int dx[4] = { -1,1,0,0 };
int dy[4] = { 0,0,-1,1 };

//입력
void input() {
    cin >> n>>m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) cin >> world[i][j];
    }
}
//초기화
void init() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            visit[i][j] = false;
            if (world[i][j] == 2) world[i][j] = 0;//원래대로
        }
    }
}
//모서리 연결 여부
void  EdgeConnect(int i,int j) {
    visit[i][j] = true;
    queue<pair<int, int>> q;
    q.push({ i,j });
    vector<pair<int, int>> connect;
    connect.push_back({ i,j });//외부와 연결된 지점
    bool isOut = false;//외부와 연결여부

    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        if (x == 0 || x == n - 1 || y == 0 || y == m - 1) isOut = true;//외부와 연결

        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k];
            int ny = y + dy[k];
            if (x < 0 || x >= n || y < 0 || y >= m) continue;//범위 조건
            if (visit[nx][ny]) continue;//방문 조건
            if (world[nx][ny] == 1) continue;//치즈

            visit[nx][ny] = true;
            q.push({ nx,ny });
            connect.push_back({ nx,ny });
        }
    }
    //외부영역은 2로 표시
    if (isOut) {
        for (int k = 0; k < connect.size(); k++) {
            int nx = connect[k].first;
            int ny = connect[k].second;
            world[nx][ny] = 2;
        }
    }
}

//홀 탐색
void Hole() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!visit[i][j] && world[i][j]==0) EdgeConnect(i,j);
        }
    }
}
//공기 접촉
void AirTouch() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (world[i][j] == 1) {//치즈
                int airCount = 0;//공기 개수
                for (int k = 0; k < 4; k++) {
                    int nx = i + dx[k];
                    int ny = j + dy[k];
                    if (world[nx][ny] == 2) airCount++;
                }
                if (airCount >= 2) world[i][j] = 0;//녹음
            }
        }
    }
}
//치즈 양
int CheeseAmount() {
    int cheese = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (world[i][j] == 1) cheese++;
        }
    }
    return cheese;
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    input();//입력
    while (true) {
        times++;
        init();//초기화
        Hole();//홀 탐색
        AirTouch();//공기 접촉
        if (CheeseAmount() == 0) break;//치즈 양
    }
    cout << times<<"\n";
    return 0;
}
