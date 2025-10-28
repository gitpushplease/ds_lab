#include <stdio.h>
#include <stdlib.h>

struct Node {
    int vertex;
    struct Node* next;
};

struct Graph {
    int numVertices;
    struct Node** adjLists;
};

struct Node* createNode(int v) {
    struct Node* newNode = malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(int vertices) {
    struct Graph* graph = malloc(sizeof(struct Graph));
    graph->numVertices = vertices;
    graph->adjLists = malloc(vertices * sizeof(struct Node*));

    for (int i = 0; i < vertices; i++)
        graph->adjLists[i] = NULL;

    return graph;
}

void addEdge(struct Graph* graph, int src, int dest, int isDirected) {
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    if (!isDirected) {
        newNode = createNode(src);
        newNode->next = graph->adjLists[dest];
        graph->adjLists[dest] = newNode;
    }
}

void printGraph(struct Graph* graph) {
    for (int v = 0; v < graph->numVertices; v++) {
        struct Node* temp = graph->adjLists[v];
        printf("\nVertex %d:", v);
        while (temp) {
            printf(" -> %d", temp->vertex);
            temp = temp->next;
        }
    }
    printf("\n");
}

int main() {
    int V, E, src, dest, choice;
    printf("Enter number of vertices: ");
    scanf("%d", &V);
    printf("Enter number of edges: ");
    scanf("%d", &E);

    printf("Enter 1 for Directed Graph or 2 for Undirected Graph: ");
    scanf("%d", &choice);

    struct Graph* graph = createGraph(V);

    printf("Enter edges (src dest):\n");
    for (int i = 0; i < E; i++) {
        scanf("%d%d", &src, &dest);
        addEdge(graph, src, dest, choice == 1);
    }

    printGraph(graph);
    return 0;
}
