#include <string>
#include <vector>
#include <queue>
using namespace std;

const int maxi = 100001;
vector<int> graph[maxi];//그래프
int dist[maxi];//각 지점에서의 최단거리

//초기화
void Init(int n){
    for(int i=1;i<=n;i++) dist[i] = -1;
}
//길 세팅
void SettingRoad(vector<vector<int>> roads){
    int roadSize = roads.size();
    for(int i=0;i<roadSize;i++){//양방향
        graph[roads[i][0]].push_back(roads[i][1]);
        graph[roads[i][1]].push_back(roads[i][0]);
    }
}
//최단거리 구하기
void MinDist(int dest){
    dist[dest] = 0;
    queue<int> q;
    q.push(dest);
    
    while(!q.empty()){
        int cur = q.front();
        q.pop();
        
        //다음 지점
        for(int i=0;i<graph[cur].size();i++){
            int next = graph[cur][i];
            if(dist[next]==-1){//미방문
                dist[next] = dist[cur]+1;
                q.push(next);
            }
        }
    }
}
//결과
vector<int> Result(vector<int> sources){
    vector<int> answer;
    for(int i=0;i<sources.size();i++) answer.push_back(dist[sources[i]]);
    return answer;
}

vector<int> solution(int n, vector<vector<int>> roads, vector<int> sources, int destination) {
    Init(n);//초기화
    SettingRoad(roads);//길 세팅
    MinDist(destination);//최단 거리
    return Result(sources);//결과
}
