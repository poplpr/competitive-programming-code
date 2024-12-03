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

const char dirc[] = "RLDU";
const int dr[] = {0, 0, 1, -1};
const int dc[] = {1, -1, 0, 0};

void solve() {
    int n, m; cin >> n >> m;
    vector<string> s(n);
    for (int i = 0; i < n; i++) cin >> s[i];

    if (n == m && n == 1) {
        return cout << "0" << "\n", void();
    }

    auto inside = [&](int r, int c) -> bool {
        return 0 <= r && r < n && 0 <= c && c < m;
    };

    vector<vector<int>> vis(n, vector<int>(m));
    vector<vector<int>> goout(n, vector<int>(m));
    queue<pii> q;

    int esc = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (s[i][j] == '?') continue;
            int dir;
            for (int k = 0; k < 4; k++) if (s[i][j] == dirc[k]) {
                dir = k; break;
            }
            if (!inside(i + dr[dir], j + dc[dir])) {
                q.push(mp(i, j));
                goout[i][j] = 1;
                vis[i][j] = 1;
            }
        }
    }
    while (!q.empty()) {
        auto [r, c] = q.front(); q.pop();
        for (int i = 0; i < 4; i++) {
            if (!inside(r + dr[i], c + dc[i]) || vis[r+dr[i]][c+dc[i]]) continue;
            if (dirc[(i ^ 1)] == s[r+dr[i]][c+dc[i]]) {
                q.push(mp(r + dr[i], c + dc[i]));
                goout[r+dr[i]][c+dc[i]] = 1;
                vis[r+dr[i]][c+dc[i]] = 1;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (s[i][j] != '?') continue;
            bool cango = true;
            for (int k = 0; k < 4; k++) {
                if (!inside(i + dr[k], j + dc[k])) continue;
                if (!goout[i + dr[k]][j + dc[k]]) {
                    cango = false;
                    break;
                }
            }
            if (cango) goout[i][j] = true;
        }
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            ans += goout[i][j];
        }
    }
    ans = n * m - ans;
    cout << ans << "\n";
}

int main() {
#ifdef LOCAL
    freopen("test.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T; cin >> T;
    while (T--) solve();
    return 0;
}