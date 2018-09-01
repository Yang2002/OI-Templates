// This file includes: Adjacent list , Dijkstra, SPFA and floyd algorithm.
#include<bits/stdc++.h>
#define rep(i, n) for(int i = 1; i <= n; ++i)
using namespace std;
typedef pair<int, int> pii;
template <typename T>
inline void read(T& x){
	int w = 1; T data = 0;
	char ch = getchar();
	while(!isdigit(ch) && ch != '-') ch = getchar();
	if(ch == '-') w = -1, ch = getchar();
	while(isdigit(ch))
		data = 10 * data + ch - '0', ch = getchar();
	x = data * w;
}
int n, m;
namespace adjlist{
    const int maxn = 103030, maxm = 503200;
    int head[maxn], nxt[maxm], ecnt = 0;
    struct Edge{
        int from, to, w;
        Edge(int a = 0, int b = 0, int c = 0): from(a), to(b), w(c){}
    } e[maxm];
    inline void addedge(int x, int y, int w){
        e[++ecnt] = Edge(x, y, w);
        nxt[ecnt] = head[x];
        head[x] = ecnt;
    }
    inline void init(){
        memset(head, 0, sizeof head);
        ecnt = 0;
    }
}
using namespace adjlist;
namespace dij{
    int d[maxn];
    inline void init(int sz){
        adjlist::init();
        for(int i = 1; i <= sz + 100; ++i) d[i] = 2147483647;
    }
    inline void Dijkstra(int s){ // pair<Distance, NodeNumber>
        priority_queue<pii, vector<pii>, greater<pii> > pq;
        pq.push({0, s});
        d[s] = 0;
        while(!pq.empty()){
            pii cur = pq.top(); pq.pop();
            int di = cur.first, no = cur.second;
            if(di != d[no]) continue;
            for(int i = head[no]; i; i = nxt[i]){
                if(d[e[i].to ] > di + e[i].w){
                    d[e[i].to ] = di + e[i].w;
                    pq.push({d[e[i].to ], e[i].to });
                }
            }
        }
        for(int i = 1; i <= n; ++i)
            printf("%d%c", d[i], i == n ? '\n' : ' ');
    }
    inline void solve(){
        int s;
        read(n), read(m), read(s); init(n);
        rep(i, m) {
            int x, y, z; read(x), read(y), read(z);
            adjlist::addedge(x, y, z);
        }
        Dijkstra(s);
    }
}
namespace SPFA{
    #define INF 2147483647
    int d[maxn], cnt[maxn];
    bool inq[maxn];
    inline void init(int sz){
        adjlist::init();
        for(int i = 1; i <= sz + 100; ++i) d[i] = INF;
        memset(inq, 0, sizeof inq);
        memset(cnt, 0, sizeof cnt);
    }
    inline bool spfa(int s){
        queue<int> q;
        inq[s] = 1, q.push(s), d[s] = 0;
        while(!q.empty()){
            int u = q.front(); q.pop();
            inq[u] = 0;
            for(int i = head[u]; i; i = nxt[i]){
                if(d[e[i].to ] > e[i].w + d[u] && d[u] < INF){
                    d[e[i].to] = e[i].w + d[u];
                    if(!inq[e[i].to]){
                        inq[e[i].to] = 1; q.push(e[i].to );
                        if(++cnt[e[i].to] > n) return 0;
                    }
                }
            }
        }
        for(int i = 1; i <= n; ++i)
            printf("%d%c", d[i], i == n ? '\n' : ' ');
        return 1;
    }
    inline void solve(){
        int s;
        read(n), read(m), read(s); init(n);
        rep(i, m) {
            int x, y, z; read(x), read(y), read(z);
            adjlist::addedge(x, y, z);
        }
        spfa(s);
    }
}
namespace floyd{
    static const int maxn = 400;
    int d[maxn][maxn], n;
    inline void init(int sz){
        adjlist::init();
        memset(d, 0x3f, sizeof d);
        for(register int i = 1; i <= sz + 10; ++i)
            d[i][i] = 0;
    }
    inline void floyd(int s){
        for(int k = 1; k <= n; ++k)
            for(int i = 1; i <= n; ++i)
                for(int j = 1; j <= n; ++j)
                    d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
        for(int i = 1; i <= n; ++i)
            printf("%d%c", d[s][i] >= 0x3f3f3f3f ? 2147483647 : d[s][i] , i == n ? '\n' : ' ');
    }
    inline void solve(){
        int s;
        read(n), read(m), read(s); init(n);
        if(n > 400) {puts("QAQ");return;}
        rep(i, m) {
            int x, y, z; read(x), read(y), read(z);
            d[x][y] = min(d[x][y], z);
        }
        floyd(s);
    }
}
int main(){
    freopen("in.txt", "r", stdin);
    dij::solve();
    SPFA::solve();
    floyd::solve();
}
