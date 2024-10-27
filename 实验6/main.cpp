#include <iostream>
#include <vector>
#include <cstring>
#include <limits>
#include <stack>
#include <algorithm>

using namespace std;

#define MVNum 100
#define MaxInt 32767

typedef struct {
    char vex[MVNum];             // 顶点表
    int arcs[MVNum][MVNum];      // 邻接矩阵，权重为整数
    int Vexnum;                   // 顶点数
    int arcnum;                   // 边数
} AMGraph;

// Helper function to find the index of a vertex in the vertex list
int getIndex(char c, char vertex[], int n) {
    for (int i = 0; i < n; ++i) {
        if (vertex[i] == c)
            return i;
    }
    return -1; // Not found
}

// Dijkstra算法实现，返回最短路径长度，并通过path数组记录路径
int Dijkstra(AMGraph &G, int start, int end, int path[]) {
    int dist[MVNum];
    bool visited[MVNum];

    // 初始化
    for(int v = 0; v < G.Vexnum; v++) {
        dist[v] = G.arcs[start][v];
        visited[v] = false;
        if(G.arcs[start][v] < MaxInt && v != start)
            path[v] = start;
        else
            path[v] = -1;
    }
    dist[start] = 0;
    visited[start] = true;

    // 进行Vexnum-1次松弛
    for(int i = 1; i < G.Vexnum; i++) {
        // 选择当前未访问顶点中dist最小的顶点
        int min = MaxInt;
        int u = -1;
        for(int v = 0; v < G.Vexnum; v++) {
            if(!visited[v] && dist[v] < min) {
                min = dist[v];
                u = v;
            }
        }

        if(u == -1) break; // 无法到达剩余顶点

        visited[u] = true;

        // 松弛操作
        for(int v = 0; v < G.Vexnum; v++) {
            if(!visited[v] && G.arcs[u][v] < MaxInt && dist[u] + G.arcs[u][v] < dist[v]) {
                dist[v] = dist[u] + G.arcs[u][v];
                path[v] = u;
            }
        }
    }

    return dist[end];
}

int main(){
    while(1){
        int n, m;
        cin >> n >> m;
        if(n == 0 && m == 0){
            break; // 输入结束
        }

        AMGraph G;
        G.Vexnum = n;
        G.arcnum = m;

        // 读取顶点
        for(int i = 0; i < n; i++) {
            cin >> G.vex[i];
        }

        // 初始化邻接矩阵
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(i == j)
                    G.arcs[i][j] = 0;
                else
                    G.arcs[i][j] = MaxInt;
            }
        }

        // 读取边的信息
        for(int i = 0; i < m; i++) {
            char a, b;
            int d;
            cin >> a >> b >> d;
            int u = getIndex(a, G.vex, n);
            int v = getIndex(b, G.vex, n);
            if(u == -1 || v == -1){
                // 无效的顶点
                continue;
            }
            // 如果存在多条边，取最小的权重
            if(d < G.arcs[u][v]){
                G.arcs[u][v] = d;
            }
        }

        // 读取起点和终点
        char startC, endC;
        cin >> startC >> endC;
        int start = getIndex(startC, G.vex, n);
        int end = getIndex(endC, G.vex, n);

        if(start == -1 || end == -1){
            // 无效的起点或终点
            cout << "0" << endl;
            cout << endl;
            continue;
        }

        // 记录路径的前驱顶点
        int path[MVNum];
        int shortestDist = Dijkstra(G, start, end, path);

        // 输出最短距离
        cout << shortestDist << endl;

        // 重构路径
        stack<char> s;
        int current = end;
        while(current != -1){
            s.push(G.vex[current]);
            current = path[current];
            if(current == start){
                s.push(G.vex[current]);
                break;
            }
        }

        // 打印路径
        vector<char> route;
        while(!s.empty()){
            route.push_back(s.top());
            s.pop();
        }
        for(int i = 0; i < route.size(); i++){
            cout << route[i];
            if(i != route.size()-1)
                cout << " ";
        }
        cout << endl;
    }
    return 0;
}
