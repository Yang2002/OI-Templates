// Z algorithm for string matching (has the same effect as the KMP algorithm)
// Complexity: O(n + m)

#include<bits/stdc++.h>
#define rep(i, n) for(int i = 1; i <= n; ++i)
using namespace std;
typedef long long ll;
string s1, s2;
const int maxn = 1002000;
int zz[maxn];
inline void get_z(string s, int* z){
    int len = s.length(), l = 0, r = 0;
    for(int i = 1; i < len; ++i){
        if(i > r){
            l = r = i;
            while(r < len && s[r] == s[r - l]) r++;
            z[i] = r - l, r--;
        } else{
            if(z[i - l] < r - i + 1) z[i] = z[i - l];
            else {
                l = i;
                while(r < len && s[r] == s[r-l]) r++;
                z[i] = r - l, r--;
            }
        }
    }}
int main(){
    cin >> s2 >> s1;
    string s = s1 + '#' + s2;
    int len1 = s1.length(), totlen = s.length();
    get_z(s, zz);
    for(register int i = len1 + 1; i < totlen; ++i)
        if(zz[i] == len1) printf("%d\n", i - len1);
    return 0;
}
