#include <string>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

const int maxi = 101;
const int inf = 1000000;
int visit[maxi][maxi];//방문 시간
int startX,startY,leverX,leverY;//시작, 레버 위치
int rSize,cSize;//지도 크기
//4방 탐색
int dx[4] = {-1,1,0,0};
int dy[4] = {0,0,-1,1};

//초기화
void init(vector<string> maps){
    rSize = maps.size();
    cSize = maps[0].size();
    for(int i=0;i<rSize;i++){
        for(int j=0;j<cSize;j++){
            if(maps[i][j]=='S'){
                startX = i;
                startY = j;
            }
            if(maps[i][j]=='L'){
                leverX = i;
                leverY = j;
            }
        }
    }
}
//레버까지
int Lever(int stX,int stY,vector<string>maps){
    memset(visit,-1,sizeof(visit));//초기화
    visit[stX][stY] = 0;
    queue<pair<int,int>> q;
    q.push({stX,stY});
    
    while(!q.empty()){
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        
        if(maps[x][y]=='L') return visit[x][y];//도착
        
        for(int i=0;i<4;i++){
            int nx = x+dx[i];
            int ny = y+dy[i];
            if(nx>=rSize || nx<0 || ny>=cSize || ny<0) continue;//범위 조건
            if(visit[nx][ny]!=-1) continue;//이미 방문
            if(maps[nx][ny]=='X') continue;//벽
            
            q.push({nx,ny});
            visit[nx][ny] = visit[x][y]+1;
        }
    }
    return inf;
}
//출구까지
int Exit(int stX,int stY,vector<string>maps){
    memset(visit,-1,sizeof(visit));//초기화
    visit[stX][stY] = 0;
    queue<pair<int,int>> q;
    q.push({stX,stY});
    
    while(!q.empty()){
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        
        if(maps[x][y]=='E') return visit[x][y];//도착
        
        for(int i=0;i<4;i++){
            int nx = x+dx[i];
            int ny = y+dy[i];
            if(nx>=rSize || nx<0 || ny>=cSize || ny<0) continue;//범위 조건
            if(visit[nx][ny]!=-1) continue;//이미 방문
            if(maps[nx][ny]=='X') continue;//벽
            
            q.push({nx,ny});
            visit[nx][ny] = visit[x][y]+1;
        }
    }
    return inf;
}

int solution(vector<string> maps) {
    init(maps);//초기화
    int answer = Lever(startX,startY,maps)+Exit(leverX,leverY,maps);//거리 구하기
    //출력
    if(answer>=inf) return -1;
    return answer;
}
