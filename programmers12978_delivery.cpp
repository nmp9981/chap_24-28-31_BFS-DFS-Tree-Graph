#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int maxi = 51;
const int inf = 500000000;
vector<pair<int,int>> graph[maxi];//그래프
int minTimes[maxi];//1~i번까지 최단 시간

//초기화
void init(int n){
    for(int i=1;i<=n;i++) minTimes[i] = inf;
}
//그래프 세팅
void SetGraph(vector<vector<int> > road){
    for(int i=0;i<road.size();i++){
        int st = road[i][0];
        int ed = road[i][1];
        int times = road[i][2];
        graph[st].push_back({ed,times});//노드, 시간
        graph[ed].push_back({st,times});
    }
}
//배달
int Delivery(int n,int k){
    priority_queue<pair<int,int>> pq;//시간, 노드
    pq.push({0,1});
    minTimes[1] = 0;
    
    while(!pq.empty()){
        int hour = -pq.top().first;
        int node = pq.top().second;
        pq.pop();
        
        if(minTimes[node] < hour) continue;//더 큰값
        
        //다음 지점
        for(int i=0;i<graph[node].size();i++){
            int nextHour = graph[node][i].second;
            int nextNode = graph[node][i].first;
            
            if(minTimes[nextNode] > hour+nextHour){//더 작은값
                minTimes[nextNode] = hour+nextHour;
                pq.push({-minTimes[nextNode],nextNode});
            }
        }
    }
    int cnt = 0;
    for(int i=1;i<=n;i++){
        if(minTimes[i]<=k) cnt++;
    }
    return cnt;
}
int solution(int N, vector<vector<int> > road, int K) {
    init(N);//초기화
    SetGraph(road);//그래프 세팅
    return Delivery(N,K);//배달
}
