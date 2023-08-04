#include <iostream>
#include <queue>
using namespace std;

int n,m;
int our, enemy;
const int maxi = 101;
string world[maxi];//지도
bool visit[maxi][maxi];//방문 여부
//4방 탐색
int dx[4] = { -1,1,0,0 };
int dy[4] = { 0,0,-1,1 };

//max
inline int max(int x, int y) {
    return x > y ? x : y;
}
//초기화
void init() {
    our = 0; enemy = 0;
    for (int i = 0; i < maxi; i++) {
        for (int j = 0; j < maxi; j++) visit[i][j] = false;
    }
}
//입력
void input() {
    cin>>n>>m;
    for (int i = 0; i < m; i++) cin >> world[i];
}
//전투력 계산
void Power(int stX,int stY, char team) {
    queue<pair<int, int>> q;
    q.push({ stX,stY });
    visit[stX][stY] = true;
    int cnt = 1;

    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        //다음 지점
        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k];
            int ny = y + dy[k];

            if (nx >= m || nx < 0 || ny >= n || ny < 0) continue;//범위 조건
            if (visit[nx][ny]) continue;//방문 조건
            if (world[nx][ny] != team) continue;//다른 팀

            visit[nx][ny] = true;
            q.push({ nx,ny });
            cnt++;
        }
    }
    //전투력 계산
    if (team == 'W') our += (cnt * cnt);
    else enemy += (cnt * cnt);
}
//전투
void War() {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (!visit[i][j]) Power(i, j, world[i][j]);
        }
    }
    cout << our << " " << enemy;//출력
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    init();//초기화
    input();//입력
    War();//전투
    return 0;
}
