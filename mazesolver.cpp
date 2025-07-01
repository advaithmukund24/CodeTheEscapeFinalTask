#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100;
int n, m;
char maze[MAXN][MAXN];
bool visited[MAXN][MAXN];
pair<int, int> parent[MAXN][MAXN];
int dx[] = {-1, 1, 0, 0};  // Up, Down
int dy[] = {0, 0, -1, 1};  // Left, Right
pair<int, int> start, end_pos;

bool isValid(int x, int y) {
    return x >= 0 && y >= 0 && x < n && y < m &&
           !visited[x][y] &&
           (maze[x][y] == '1' || maze[x][y] == 'E');
}

void bfs() {
    memset(visited, false, sizeof(visited));
    queue<pair<int, int>> q;
    visited[start.first][start.second] = true;
    q.push(start);

    while (!q.empty()) {
        pair<int, int> cur = q.front(); q.pop();
        if (cur == end_pos) break;

        for (int i = 0; i < 4; ++i) {
            int nx = cur.first + dx[i];
            int ny = cur.second + dy[i];

            if (isValid(nx, ny)) {
                visited[nx][ny] = true;
                parent[nx][ny] = cur;
                q.push({nx, ny});
            }
        }
    }
}

bool dfs(int x, int y) {
    if (!isValid(x, y)) return false;
    visited[x][y] = true;
    if (make_pair(x, y) == end_pos) return true;

    for (int i = 0; i < 4; ++i) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (isValid(nx, ny)) {
            parent[nx][ny] = {x, y};
            if (dfs(nx, ny)) return true;
        }
    }
    return false;
}

void reconstructPath(pair<int, int> end_point) {
    pair<int, int> cur = end_point;

    while (cur != start) {
        int x = cur.first, y = cur.second;
        if (maze[x][y] != 'E') maze[x][y] = '*';
        cur = parent[x][y];
    }
    // maze[start.first][start.second] = '*';
}

void printMaze() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << maze[i][j];
        }
        cout << '\n';
    }
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> maze[i][j];
            if (maze[i][j] == 'S') start = {i, j};
            if (maze[i][j] == 'E') end_pos = {i, j};
        }
    }

    cout << "\n--- BFS ---\n";
    bfs();
    reconstructPath(end_pos);
    printMaze();

    // Reset visited and maze path
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            if (maze[i][j] == '*') maze[i][j] = '1';
            visited[i][j] = false;
        }

    cout << "\n--- DFS ---\n";
    dfs(start.first, start.second);
    reconstructPath(end_pos);
    printMaze();

    return 0;
}
