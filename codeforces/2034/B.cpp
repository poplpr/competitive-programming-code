#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using db = double;
using ld = long double;

#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
#define dbg(x) cout << #x << " = " << x << ", "
#define dbg2(x) cout << #x << " = " << x << endl

template<typename T> void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    while (!isdigit(c)) { if (c == '-') f = -1; c = getchar(); }
    while (isdigit(c)) { x = x * 10 + c - '0'; c = getchar(); }
    x *= f;
}

int buf[42];
template<typename T> void write(T x) {
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
    int n, m, k; read(n); read(m); read(k);
    scanf("%s", s + 1);
    int ans = 0, now0 = 0;
    for (int i = 1; i <= n; i++) {
        if (s[i] == '0') now0++;
        else now0 = 0;
        if (now0 == m) {
            ans++;
            i = i + k - 1;
            now0 = 0;
        }
    }
    write(ans); putchar(10);
}

int main() {
#ifdef LOCAL
    freopen("test.in", "r", stdin);
#endif
    int T; read(T);
    while (T--) solve();
    return 0;
}