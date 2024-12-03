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
    int n, m; read(n, m);
    if (n == 1) {
        if (m == 1) {
            puts("YES\n1");
        }
        else puts("NO");
        return;
    }
    
    vector<int> J(15, 0);
    J[0] = 1;
    for (int i = 1; i <= 10; i++) J[i] = i * J[i-1];
    if (n <= 10 && m > J[n]) { return puts("NO"), void();}
    if (n <= 10 && m == J[n]) {
        // all permutation
        puts("YES");
        vector<int> p(n);
        iota(p.begin(), p.end(), 0);

        do {
            for (int i = 0; i < n; i++) {
                write(p[i] + 1); putchar(" \n"[i == n - 1]);
            }
        } while(next_permutation(p.begin(), p.end()));
        return;
    }
    if (n <= 10 && m == J[n] - 1) return puts("NO"), void();

    auto check = [&](vector<int>& x, vector<vector<int>>& y) {
        for (int i = 0; i < SZ(y); i++) {
            bool iseq = true;
            for (int j = 0; j < n; j++) {
                if (x[j] != y[i][j]) {
                    iseq = false;
                    break;
                }
            }
            if (iseq) return false;
        }
        return true;
    };

    auto printans = [&](vector<vector<int>>& bans, int state) {
        vector<int> p(n);
        iota(p.begin(), p.end(), 0);
        int cnt = 0;
        do {
            if (!check(p, bans)) continue;
            if (state == 1) {
                vector<int> p2(n);
                for (int i = 0; i < n; i++) p2[i] = n - 1 - p[i];
                if (!check(p2, bans)) continue;
                for (int i = 0; i < n; i++) {
                    write(p2[i] + 1); putchar(" \n"[i == n - 1]);
                }
                cnt++;
            }
            for (int i = 0; i < n; i++) {
                write(p[i] + 1); putchar(" \n"[i == n - 1]);
            }
            cnt++;
            if (cnt == m) return;
        } while (next_permutation(p.begin(), p.end()));
    };

    if (n <= 10 && m == J[n] - 2) {
        vector<vector<int>> ban(2, vector<int>(n));
        for (int i = 0; i < n; i++) ban[0][i] = i;
        for (int i = 0; i < n; i++) ban[1][i] = n - 1 - i;
        puts("YES");
        printans(ban, 0);
        return;
    }

    vector<vector<int>> ban;
    if (m % 2 == 0) {
        // m even
        puts("YES");
        printans(ban, 1);
    }
    else {
        // m odd
        if (m == 1) return puts("NO"), void();
        if (n % 2 == 0) return puts("NO"), void();
        ban = vector<vector<int>>(3, vector<int>(n));
        iota(ban[0].begin(), ban[0].end(), 0);
        for (int i = 0; i < n; i += 2) {
            ban[1][i] = n - 1 - i / 2;
            ban[2][i] = n / 2 - i / 2;
            if (i + 1 < n) {
                ban[1][i+1] = n / 2 - i / 2 - 1;
                ban[2][i+1] = n - 1 - i / 2;
            }
        }

        puts("YES");
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < n; j++) {
                write(ban[i][j] + 1); putchar(" \n"[j == n - 1]);
            }
        }
        m -= 3;
        if (m > 0) printans(ban, 1);
    }
}

int main() {
#ifdef LOCAL
    freopen("test.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T; read(T);
    while (T--) solve();
    return 0;
}