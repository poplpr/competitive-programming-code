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

void solve() {
    int n; cin >> n;
    string s; cin >> s;
    map<int, int> cnt;
    for (int i = 0; i < n; i++) cnt[s[i]-'a']++;
    vector<pii> a;
    for (auto p : cnt) a.emplace_back(p);
    sort(a.begin(), a.end(), [](pii x, pii y) {
        return x.se < y.se || (x.se == y.se && x.fi < y.fi);
    });
    int minx = a[0].fi, maxx = a.rbegin()->first;
    int minid = -1, maxid = -1;
    for (int i = 0; i < n; i++) {
        if (s[i] == minx + 'a') minid = i;
        if (s[i] == maxx + 'a') maxid = i;
    }
    s[minid] = maxx + 'a';
    cout << s << "\n";
}

int main() {
#ifdef LOCAL
    freopen("test.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T = 1;
    // read(T);
    cin >> T;
    while (T--) solve();
    return 0;
}