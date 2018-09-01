// EK algorithm. Overall complexity: O(nm^2)
// Functions: EK::init(), EK::addedge(from, to, capacity), EK::maxflow(Source, Target)
// Use EK::solve() to test the algorithm

#include<bits/stdc++.h>
using namespace std;
#define INF 0x3f3f3f3f
const int maxn = 10030, maxm = 300300;
namespace adjlist{
    int head[maxn], nxt[maxm], ecnt = 1, n, m;
    struct Edge{
        int from , to , cap, flow;
        Edge(int u = 0, int v = 0, int c = 0, int f = 0):
            from(u), to(v), cap(c), flow(f){}
    }e[maxm];
    inline void init(){
        memset(head, 0, sizeof head);
        ecnt = 1;
    }
    inline void addedge(int x, int y, int c){
        e[++ecnt] = Edge(x, y, c, 0), nxt[ecnt] = head[x], head[x] = ecnt;
        e[++ecnt] = Edge(y, x, 0, 0), nxt[ecnt] = head[y], head[y] = ecnt;
    }
}
namespace EK{
    #define INF 0x3f3f3f3f
    using namespace adjlist;
    int a[maxn], p[maxn];
    inline int maxflow(int s, int t){
        int flow = 0;
        for(;;){
            memset(a, 0, sizeof a);
            queue<int> q;
            q.push(s), a[s] = INF;
            while(!q.empty()){
                int x = q.front(); q.pop();
                for(int i = head[x]; i ; i = nxt[i]){
                    if(!a[e[i].to] && e[i].cap > e[i].flow){
                        a[e[i].to ] = min(a[x], e[i].cap - e[i].flow);
                        p[e[i].to] = i;
                        q.push(e[i].to);
                    }
                }
                if(a[t]) break;
            }
            if(!a[t]) break;
            for(int u = t; u != s; u = e[p[u]].from ){
                e[p[u]].flow += a[t];
                e[p[u] ^ 1].flow -= a[t];
            }
            flow += a[t];
        }
        return flow;
    }
    inline void solve(){
        int s, t;
        scanf("%d%d%d%d", &n, &m, &s, &t);
        for(int i = 1;i <= m; ++i){
            int x, y, cap;
            scanf("%d%d%d", &x, &y, &cap);
            addedge(x, y, cap);
        }
        printf("%d\n", maxflow(s, t));
    }
}
int main(){
    EK::solve();
    return 0;
}
