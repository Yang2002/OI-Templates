// POJ 2417
#include<cstdio>
#include<cmath>
#include<vector>
#include<utility>
#include<cstring>
#include<iostream>
#include<ctime>
#define rep(i, n) for(int i = 1; i <= n; ++i)
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

inline int qpow(int x, int y, int mod) {
    int ret = 1;
    for(; y; y >>= 1, x = 1LL * x * x % mod)
        if(y & 1) ret = 1LL * ret * x % mod;
    return ret;
}
inline int inv(int x, int mod) { return qpow(x, mod - 2, mod); }
const int HASHSIZE = 76543, KEYSIZE = 100200;
struct HashMap {;
    pair<int, int> *End, kv[KEYSIZE];
    int head[HASHSIZE], nxt[HASHSIZE], tot;

    HashMap() { clear(); End = new pair<int,int>; }
    pii* end() { return End; }
    void clear() { 
        memset(head, -1, sizeof head); 
        memset(nxt, -1, sizeof nxt);
        tot = 0;
    }
    void insert(int x, int y) {
        kv[++tot] = make_pair(x, y);
        int xm = x % HASHSIZE, id = tot;
        nxt[id] = head[xm];
        head[xm] = id;
    }
    pii* find(int x) {
        int xm = x % HASHSIZE;
        for(int p = head[xm]; ~p; p = nxt[p]) {
            if(kv[p].first == x) return kv + p;
        }
        return End;
    }
    int& operator [] (const int& idx) {
        if(find(idx) == End) insert(idx, 0);
        return find(idx)->second;
    }
} mp;
int BSGS(int B, int N, int P) { // log_B N (mod P)
    mp.clear();
    int sq = ceil(sqrt(P)), c = 1, t;
    for(int i = 0; i < sq; ++i) {
        if(N == c) return i;
        if(mp.find(c) == mp.end()) mp[c] = i;
        c = 1LL * c * B % P;
    }
    int ic = inv(c, P);
    t = N;
    for(int x = sq; x < P; x += sq) {
        t = 1LL * t * ic % P;
        if(mp.find(t) != mp.end())
            return mp[t] + x;
    }
    return -1;
}

int main() {
    int _p, _b, _n;
    auto start = clock();
    while(~scanf("%d%d%d", &_p, &_b, &_n)) {
        int ans = BSGS(_b, _n, _p);
        if(ans == -1) puts("no solution");
        else printf("%d\n", ans);
    }
    cerr << "> " << clock() - start << " ms used (user, map)\n";
    
    return 0;
}
