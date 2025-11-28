#include <stdio.h>
#include <stdlib.h>

#define MAX 100 //you can store upto 100 edges and use 99 indices in the arrays

struct Edge {
    int u, v, w;
}; //defines a structure edge to represent and edge in the graph, u-> starting vertex,v->ending vertex,w->weight of the edge

struct Edge edges[MAX], mst[MAX]; //in struct edfe, edge[MAX]  an array to store all edges of the input graph, mst[MAX] an array to store edges that will be in mst
int parent[MAX];//disjoint set
int V, E; //v-> number of vertices, e-> number of edges

/* Comparator for qsort */
int compare(const void *a, const void *b) {// comapring two edges using quicksort, 
    struct Edge *e1 = (struct Edge *)a;//typecasting
    struct Edge *e2 = (struct Edge *)b;//typecasting 
    return e1->w - e2->w; //if e1-w is smaller returns a -ve no, e1 comes first
}                         //if both weight are equal return 0, if e1-w is bigger return a +ve no, e2 comes first

/* Find with Path Compression */
int find(int i) {
    if (parent[i] != i)
        parent[i] = find(parent[i]);
    return parent[i];
}

/* Union Set */
void unionSet(int a, int b) {
    int rootA = find(a);
    int rootB = find(b);
    parent[rootB] = rootA;
}

int main() {
    int i, count = 0, totalCost = 0;

    printf("Enter number of vertices: ");
    scanf("%d", &V);

    printf("Enter number of edges: ");
    scanf("%d", &E);

    printf("\nEnter edges (u v weight):\n");
    for (i = 0; i < E; i++) {
        scanf("%d%d%d", &edges[i].u, &edges[i].v, &edges[i].w);
    }

    // Initialize parents
    for (i = 0; i < V; i++) {
        parent[i] = i;
    }

    // Sort edges using qsort
    qsort(edges, E, sizeof(struct Edge), compare);

    // Kruskal's Algorithm
    for (i = 0; i < E && count < V - 1; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].w;

        if (find(u) != find(v)) {
            mst[count++] = edges[i];
            totalCost += w;
            unionSet(u, v);
        }
    }

    printf("\nEdges in the Minimum Spanning Tree:\n");
    for (i = 0; i < count; i++) {
        printf("%d - %d   Weight: %d\n", mst[i].u, mst[i].v, mst[i].w);
    }

    printf("\nTotal Minimum Cost: %d\n", totalCost);

    return 0;
}

