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
#define dbg(x) cout << #x << " = " << x << 

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

const int N = 200000 + 5;
char s[N];

void solve() {
    int n, m; read(n, m);
    scanf("%s", s);
    vector<int> suf(n + 1, 0);
    for (int i = n - 1; i >= 0; i--) {
        suf[i] = (s[i] == '0' ? -1 : +1) + suf[i+1];
    }
    sort(suf.begin() + 1, suf.end() - 1, greater<int>());
    long long int now = 0;
    for (int i = 1; i < n; i++) {
        now += suf[i];
        if (now >= m) {
            write(i + 1); putchar(10); return;
        }
    }
    puts("-1");
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