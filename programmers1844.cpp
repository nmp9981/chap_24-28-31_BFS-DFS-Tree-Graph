#include <vector>
#include <queue>
using namespace std;

//위치 점보
struct Pos{
    int x,y,cnt;    
};
int n,m;
const int maxi = 101;
bool visit[maxi][maxi];//방문 여부
//4방 탐색
int dx[4] = {-1,1,0,0};
int dy[4] = {0,0,-1,1};

//모험
int Adventure(vector<vector<int>> maps){
    //사이즈
    n = maps.size();
    m = maps[0].size();
    
    queue<Pos> q;
    q.push({0,0,1});
    visit[0][0] = true;
    
    while(!q.empty()){
        int x = q.front().x;
        int y = q.front().y;
        int dist = q.front().cnt;
        q.pop();
        
        //도착
        if(x==n-1 && y==m-1) return dist;
        
        //다음 지점
        for(int i=0;i<4;i++){
            int nx = x+dx[i];
            int ny = y+dy[i];
            if(nx<0 || nx>=n || ny<0 || ny>=m) continue;//범위 조건
            if(visit[nx][ny]) continue;//방문 조건
            if(maps[nx][ny]==0) continue;//벽
            visit[nx][ny] = true;
            q.push({nx,ny,dist+1});
        }
    }
    return -1;
}
int solution(vector<vector<int> > maps)
{
    return Adventure(maps);
}
