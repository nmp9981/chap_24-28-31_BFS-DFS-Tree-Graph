#include <iostream>
#include <queue>
using namespace std;

int n,m;
const int maxi = 501;
int maxArea = 0;//최대 넓이
int picture[maxi][maxi];//그림
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
    cin>>n>>m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) cin >> picture[i][j];
    }
}
//영역 넓이
int Area(int i, int j) {
    visit[i][j] = true;
    queue<pair<int, int>> q;
    q.push({ i,j });
    int square = 1;

    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k];
            int ny = y + dy[k];
            if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;//범위조건
            if (visit[nx][ny]) continue;//방문 조건
            if (picture[nx][ny] == 0) continue;//빈칸

            visit[nx][ny] = true;
            q.push({ nx,ny });
            square++;
        }
    }
    return square;
}
//그림 영역
void PictureArea() {
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!visit[i][j] && picture[i][j] == 1) {
                maxArea =max(maxArea, Area(i, j));
                cnt++;
            }
        }
    }
    //출력
    cout << cnt << "\n";
    cout << maxArea;
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    input();//입력
    PictureArea();//그림 영역
    return 0;
}
