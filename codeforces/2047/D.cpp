#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using db = double;
using ld = long double;
using pii = pair<int, int>;

#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define ALL(x) (x).begin(), (x).end()
#define SZ(x) (int)(x).size()
#define dbg(x) cout << #x << " = " << x << ", "
#define dbg2(x) cout << #x << " = " << x << endl

template<typename T> void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    while (!isdigit(c)) { if (c == '-') f = -1; c = getchar(); }
    while (isdigit(c)) { x = x * 10 + c - '0'; c = getchar(); }
    x *= f;
}

template<typename T, typename... Args> void read(T &x, Args&... args) {
    read(x); read(args...);
}

template<typename T> void write(T x) {
    static int buf[42];
    int p = 0;
    if (x < 0) putchar('-'), x = -x;
    if (x == 0) return putchar('0'), void();
    while(x) {
        buf[p++] = x % 10;
        x /= 10;
    }
    for (int i = p - 1; i >= 0; i--) putchar(buf[i] + '0');
}

void solve() {
    int n; read(n);
    vector<int> a(n);
    for (int i = 0; i < n; i++) read(a[i]);
    vector<pii> b(n);
    vector<int> locked(n, 0);
    for (int i = 0; i < n; i++) b[i] = mp(a[i], i);
    sort(b.begin(), b.end(), [](pii x, pii y) {
        return x.fi < y.fi || (x.fi == y.fi && x.se > y.se);
    });
    int maxpos = -1;
    bool isfirst = true;
    for (int i = 0; i < n; i++) {
        if (b[i].se > maxpos) {
            // 这个值可以不用修改
            int j = i;
            while (j < n && b[j].fi == b[i].fi && b[j].se > maxpos) j++;
            maxpos = max(b[i].se, maxpos);
            i = j - 1;
        }
        else {
            // 这个值要修改 +1
            // 后面所有值都要修改 +1
            // 除了和第一次触发且满足大于之前 maxpos 的 v+1 不用修改
            if (isfirst) {
                isfirst = false;
                
                // 找到 v+1
                int firstj = -1;
                for (int j = i + 1; j < n; j++) {
                    if (b[j].fi == b[i].fi + 1) {
                        firstj = j; break;
                    }
                }

                // v+1 合法的话，找到不需要向后抛的 v + 1 们
                if (firstj != -1 && b[firstj].se > maxpos) {
                    int lastj = firstj;
                    while (lastj < n && b[lastj].fi == b[firstj].fi && b[lastj].se > maxpos) lastj++;
                    for (int j = firstj; j < lastj; j++) locked[j] = 1;
                }

                // 给这一串 v 做 +1 操作
                int r = i;
                while (r < n && b[r].fi == b[i].fi) r++;
                for (int k = i; k < r; k++) b[k].fi++;

                maxpos = n;
                i = r - 1;
                continue;
            }

            if (!locked[i]) b[i].fi++;
        }
    }
    for (int i = 0; i < n; i++) {
        write(b[i].fi); putchar(" \n"[i == n - 1]);
    }
}


int main() {
#ifdef LOCAL
    freopen("test.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T = 1;
    read(T);
    while (T--) solve();
    return 0;
}