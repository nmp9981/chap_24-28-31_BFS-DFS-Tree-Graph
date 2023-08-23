#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

int n,m,k;
const int maxi = 101;
int maxCnt = 0;
int world[maxi][maxi];
bool visit[maxi][maxi];//방문 여부
//4방 탐색
int dx[4] = { -1,1,0,0 };
int dy[4] = { 0,0,-1,1 };

//max
inline int max(int x, int y) {
    return x > y ? x : y;
}
//입력
void input() {
    cin>>n>>m>>k;
    for (int i = 0; i < k; i++) {
        int r, c;
        cin >> r >> c;
        world[r-1][c-1] = 1;
    }
}
//쓰레기 개수 세기
int CountTrash(int i,int j) {
    visit[i][j] = true;
    queue<pair<int, int>> q;
    q.push({ i,j });
    int cnt = 1;

    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        //다음 지점
        for (int dir = 0; dir < 4; dir++) {
            int nx = x + dx[dir];
            int ny = y + dy[dir];
            if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;//범위 조건
            if (visit[nx][ny]) continue;//방문 조건
            if (world[nx][ny] == 0) continue;//장애물이 아님

            visit[nx][ny] = true;
            q.push({ nx,ny });
            cnt++;
        }
    }
    return cnt;
}
//쓰레기 찾기
void Trash() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!visit[i][j] && world[i][j]==1) {
                maxCnt = max(maxCnt, CountTrash(i, j));
            }
        }
    }
    cout << maxCnt;//출력
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    input();//입력
    Trash();//쓰레기 찾기
    return 0;
}
