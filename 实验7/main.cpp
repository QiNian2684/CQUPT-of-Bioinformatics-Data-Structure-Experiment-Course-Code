#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>

using namespace std;

#define MVNum 100
#define MaxInt 32767

typedef struct {
    int vex[MVNum + 1];        // 顶点表，编号从1到n
    int arcs[MVNum + 1][MVNum + 1]; // 邻接矩阵，1表示有边，0表示无边
    int Vexnum;                 // 顶点数
    int arcnum;                 // 边数
} AMGraph;

// 函数声明
void initializeGraph(AMGraph &G);
int bfs(const AMGraph &G, int start);

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while(true){
        int n, m;
        cin >> n >> m;
        if(n == 0 && m == 0){
            break; // 输入结束
        }

        AMGraph G;
        G.Vexnum = n;
        G.arcnum = m;

        // 初始化邻接矩阵
        initializeGraph(G);

        // 读取m条边
        for(int i = 0; i < m; ++i){
            int a, b;
            cin >> a >> b;
            if(a >=1 && a <=n && b >=1 && b <=n){
                G.arcs[a][b] = 1;
                G.arcs[b][a] = 1; // 无向图
            }
        }

        // 对每个节点执行BFS，计算距离不超过6的节点数量
        for(int node = 1; node <= n; ++node){
            int count = bfs(G, node);
            double percentage = ((double)count / n) * 100.0;
            // 设置输出格式为两位小数
            cout << node << ": " << fixed << setprecision(2) << percentage << "%" << "\n";
        }
    }

    return 0;
}

// 初始化图的邻接矩阵
void initializeGraph(AMGraph &G){
    for(int i = 1; i <= G.Vexnum; ++i){
        for(int j = 1; j <= G.Vexnum; ++j){
            if(i == j){
                G.arcs[i][j] = 0;
            }
            else{
                G.arcs[i][j] = 0;
            }
        }
    }
}

// BFS函数，返回与start节点距离不超过6的节点数量
int bfs(const AMGraph &G, int start){
    vector<bool> visited(G.Vexnum +1, false);
    vector<int> distance(G.Vexnum +1, MaxInt);
    queue<int> Q;

    // 初始化
    Q.push(start);
    visited[start] = true;
    distance[start] = 0;

    while(!Q.empty()){
        int u = Q.front();
        Q.pop();

        // 如果当前距离已经达到6，继续，不再扩展
        if(distance[u] >=6){
            continue;
        }

        // 遍历所有邻接点
        for(int v =1; v <= G.Vexnum; ++v){
            if(G.arcs[u][v] ==1 && !visited[v]){
                visited[v] = true;
                distance[v] = distance[u] +1;
                Q.push(v);
            }
        }
    }

    // 统计距离不超过6的节点数量，包括自身
    int count =0;
    for(int i =1; i <= G.Vexnum; ++i){
        if(distance[i] <=6){
            count++;
        }
    }
    return count;
}
