// Now our BIT supports negative numbers. Number range: [-1e7, 1e7]
// Operations:
// Insert x : Add(x, 1)
// Delete x : Add(x, -1)
// Find Kth : Find_kth(k)
// Find Rank: Find_rk(k)
// Previous : Prev(x)
// Next     : Next(x)
#include<bits/stdc++.h>
#define rep(i, n) for(int i = 1; i <= n; ++i)
using namespace std;
typedef long long ll;
const int maxn = 20000010, M = 10000001;
int n;
template<typename T> void read(T &x){
    x = 0; int f = 1; char ch = getchar();
    while(!isdigit(ch) ) { if(ch == '-') f *= -1; ch = getchar();}
    while( isdigit(ch) ) {x = x * 10 + ch - 48; ch = getchar();}
    x *= f;
}
template <typename T>
void write(T x){
     if (x < 0) putchar('-'),x = ~x + 1;
     if (x > 9) write(x / 10);
     putchar( x % 10 + '0');
}
template <typename T> inline void writeln(T x) { write(x), putchar('\n'); }


struct Fenwick {
    #define lowbit(x) (x & (-x))
    private:
    int c[maxn + 100];

    public:
    inline void Add(int x, int v) {
        for(; x <= maxn; x += lowbit(x))
            c[x] += v;
    }
    inline int Find_kth(int k) { // kth smallest
        int ans = 0, cnt = 0, i;
        for(i = 26; i >= 0; --i) {
            ans += 1 << i;
            if(ans >= maxn || c[ans] + cnt >= k) ans -= 1 << i;
            else cnt += c[ans];
        }
        return ans + 1;
    }
    inline int Find_rk(int x) {
        int ret = 0; x--;
        for(; x; x -= lowbit(x))
            ret += c[x];
        return ret + 1;
    }
} t;
int main(){
    int q; read(q);
    while(q--) {
        int opt, x; read(opt), read(x);
        switch (opt) {
            case 1: t.Add(x + M, 1); break;
            case 2: t.Add(x + M, -1); break;
            case 3: writeln(t.Find_rk(x + M)); break;
            case 4: writeln(t.Find_kth(x) - M); break;
            case 5: writeln(t.Find_kth(t.Find_rk(x + M) - 1) - M); break;
            case 6: writeln(t.Find_kth(t.Find_rk(x + 1 + M)) - M); break;
        }
    }
}
