/*
 * @Author: poplpr
 * @Date: 2024-12-09 10:29:46
 * @Description: competitive programming code
 */
#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
using i128 = __int128;
using f64 = double;
using f128 = long double;
using pii = pair<int, int>;

#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define ALL(x) (x).begin(), (x).end()
#define SZ(x) (int)(x).size()
#define dbg1(x) cout << #x << " = " << x << ", "
#define dbg2(x) cout << #x << " = " << x << endl

template <typename T>
void _debug(const char* format, T t) {
    cerr << format << '=' << t << endl;
}

template <class First, class... Rest>
void _debug(const char* format, First first, Rest... rest) {
    while (*format != ',') cerr << *format++;
    cerr << '=' << first << ',';
    _debug(format + 1, rest...);
}

template <typename T>
ostream& operator<<(ostream& os, const vector<T>& V) {
    os << "[ ";
    for (const auto& vv : V) os << vv << ", ";
    os << ']';
    return os;
}
#ifdef LOCAL
    #define dbg(...) _debug(#__VA_ARGS__, __VA_ARGS__)
#else
    #define dbg(...) 
#endif

template<typename T> void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    while (!isdigit(c)) { if (c == '-') f = -1; c = getchar(); }
    while (isdigit(c)) { x = x * 10 + c - '0'; c = getchar(); }
    x *= f;
}

template<typename T, typename... Args> void read(T &x, Args&... args) {
    read(x); read(args...);
}

template<typename T> void _write(T x) {
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

template<typename First, typename... Rest> void _write(const First& first, const Rest&... rest) {
    write(first); putchar(32); write(rest...);
}

template<typename T> void write(std::vector<T> x) {
    for(int i = 0; i < SZ(x); i++) {
        _write(x[i]); putchar(" \n"[i == SZ(x) - 1]);
    }
}

template<typename T> void write(T x, char end_char='\n') {
    _write(x);
    if (end_char != '\0') putchar(end_char);
}

template<typename First, typename... Rest> void write(const First& first, const Rest&... rest) {
    _write(first); putchar(32); _write(rest...); putchar(10);
}

void solve() {
    int n; read(n);
    vector<vector<int> > G(n);
    for (int i = 1; i < n; i++) {
        int u, v; read(u, v);
        u--; v--;
        G[u].emplace_back(v);
        G[v].emplace_back(u);
    }

    vector<int> a(n);
    int cur = 1;
    auto dfs = [&](this auto &&self, int x, int p = -1) -> void {
        a[x] = cur;
        bool first = true;
        for (auto y : G[x]) {
            if (y == p) {
                continue;
            }
            if (first) {
                first = false;
                cur++;
                self(y, x);
                cur++;
            } else {
                cur += 2;
                self(y, x);
            }
        }
    };

    dfs(0);
    write(a);
}

int main() {
#ifdef LOCAL
    freopen("test.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T = 1;
    read(T);
    // cin >> T;
    while (T--) solve();
    return 0;
}