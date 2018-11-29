// Dinic algorithm for maxflow. Overall Complexity: O(n^2 m)
// Functions: Dinic::init() Dinic::addedge(from, to, capacity) Dinic::maxflow(source, target)
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
using namespace std;

typedef long long ll;

const int maxn = 3030, maxm = 303200;
int n, m, ss, tt;
long long tot = 0;

namespace adjlist{
    int head[maxn], nxt[maxm], ecnt = 1;
    struct Edge{
        int from, to, cap, flow;
        Edge(int a = 0, int b = 0, int c = 0, int d = 0): from(a), to(b), cap(c), flow(d){}
    } e[maxm];
    inline void addedge(int x, int y, int w){
        e[++ecnt] = Edge(x, y, w, 0);
        nxt[ecnt] = head[x];
        head[x] = ecnt;

        e[++ecnt] = Edge(y, x);
        nxt[ecnt] = head[y];
        head[y] = ecnt;
    }
    inline void init(){
        memset(head, 0, sizeof head);
        ecnt = 1;
    }
}
namespace Dinic{
    using namespace adjlist;
    int n, m, s, t, d[maxn], cur[maxn];
    bool vis[maxn];
    bool BFS(){
        memset(vis, 0, sizeof vis);
        queue<int> q;
        q.push(s), d[s] = 0, vis[s] = 1;
        while(!q.empty()){
            int x = q.front(); q.pop();
            for(int i = head[x]; i ; i = nxt[i]){
                if(!vis[e[i].to ] && e[i].cap > e[i].flow){
                    vis[e[i].to ] = 1;
                    d[e[i].to] = d[x] + 1;
                    q.push(e[i].to );
                }
            }
        }
        return vis[t];
    }
    int DFS(int x, int a){
        if(x == t || a == 0) return a;
        ll flow = 0, f;
        for(int i = cur[x]; i ; i = nxt[i], cur[x] = i){
            if(d[x] + 1 == d[e[i].to] && (f = DFS(e[i].to, min(a, e[i].cap-e[i].flow))) > 0){
                e[i].flow += f;
                e[i ^ 1].flow -= f;
                flow += f, a -= f;
                if(a == 0) break;
            }
        }
        return flow;
    }
    inline ll maxflow(int so, int ta){
        s = so, t = ta;
        ll flow = 0;
        while(BFS()){
            memcpy(cur, head, sizeof cur);
            flow += DFS(s, INF);
        }
        return flow;
    }
}

using Dinic::addedge;
using Dinic::maxflow;
