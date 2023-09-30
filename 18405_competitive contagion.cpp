#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

int n,k,s,X,Y;
const int maxi = 201;
int world[maxi][maxi];//지도
priority_queue<pair<int,pair<int, int>>> virus;//바이러스 정보
//4방 탐색
int dx[4] = { -1,1,0,0 };
int dy[4] = { 0,0,-1,1 };

//입력
void input() {
    cin>>n>>k;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) cin >> world[i][j];
    }
    cin >> s >> X >> Y;
}

//바이러스 확산
void SpreadVirus() {
    //초기 바이러스
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (world[i][j] != 0) virus.push({-world[i][j],{i,j} });
        }
    }
    
    //확산
    int times = 0;
    while (times<s) {
        int virusSize = virus.size();
        vector < pair<int, pair<int, int>>> newVirus;//새로운 바이러스
        for (int i = 0; i < virusSize; i++) {
            int type = virus.top().first;
            int x = virus.top().second.first;
            int y = virus.top().second.second;
            virus.pop();
            
            //다음 지점
            for (int k = 0; k < 4; k++) {
                int nx = x + dx[k];
                int ny = y + dy[k];
                if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;//범위조건
                if (world[nx][ny] != 0) continue;//이미 방문

                world[nx][ny] = -type;//전염
                newVirus.push_back({ type,{nx,ny} });
            }
        }
        //새로운 바이러스 넣기
        for (int i = 0; i < newVirus.size(); i++) {
            virus.push({ newVirus[i].first,{newVirus[i].second.first,newVirus[i].second.second } });
        }
        times++;//시간 증가
    }
    cout << world[X-1][Y-1];//출력
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    input();//입력
    SpreadVirus();//바이러스 확산
    return 0;
}
