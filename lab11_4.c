#include <stdio.h>
#define MAX 100

int adj[MAX][MAX];
int visited[MAX];

void DFS(int v, int n) {
    visited[v] = 1;
    printf("%d ", v);

    for (int i = 0; i < n; i++) {
        if (adj[v][i] && !visited[i])
            DFS(i, n);
    }
}

int main() {
    int n, e, src, dest, start;
    printf("Enter number of vertices: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            adj[i][j] = 0;

    printf("Enter number of edges: ");
    scanf("%d", &e);

    printf("Enter edges (src dest):\n");
    for (int i = 0; i < e; i++) {
        scanf("%d%d", &src, &dest);
        adj[src][dest] = adj[dest][src] = 1;
    }

    printf("Enter starting vertex: ");
    scanf("%d", &start);

    printf("DFS Traversal: ");
    for (int i = 0; i < n; i++) visited[i] = 0;
    DFS(start, n);

    return 0;
}
