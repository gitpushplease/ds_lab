#include <stdio.h>

void displayMatrix(int n, int adj[n][n]) {
    printf("\nAdjacency Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%d ", adj[i][j]);
        printf("\n");
    }
}

int main() {
    int n, edges, i, src, dest, choice;
    printf("Enter number of vertices: ");
    scanf("%d", &n);

    int adj[n][n];
    for (i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            adj[i][j] = 0;

    printf("Enter number of edges: ");
    scanf("%d", &edges);

    printf("Enter 1 for Directed Graph or 2 for Undirected Graph: ");
    scanf("%d", &choice);

    printf("Enter edges (src dest):\n");
    for (i = 0; i < edges; i++) {
        scanf("%d%d", &src, &dest);
        adj[src][dest] = 1;
        if (choice == 2)
            adj[dest][src] = 1;
    }

    displayMatrix(n, adj);
    return 0;
}
