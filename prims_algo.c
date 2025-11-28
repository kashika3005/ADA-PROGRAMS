#include <stdio.h>

#define MAX 100

// Structure for each element in priority queue
struct PriorityQueue {
    int vertex;
    int key;
};

struct PriorityQueue pq[MAX];
int size = 0;

/* INSERT with key */
void insert(int vertex, int key)
{
    if (size == MAX)
    {
        printf("Queue is full!\n");
        return;
    }

    pq[size].vertex = vertex;
    pq[size].key = key;
    size++;
}

/* EXTRACT MIN (based on key) */
int extractMin()
{
    if (size == 0)
    {
        printf("Queue is empty!\n");
        return -1;
    }

    int minIndex = 0;

    // Find index of minimum key
    for(int i = 1; i < size; i++)
    {
        if(pq[i].key < pq[minIndex].key)
        {
            minIndex = i;
        }
    }

    int minVertex = pq[minIndex].vertex;

    // Shift elements after removing min
    for(int i = minIndex; i < size - 1; i++)
    {
        pq[i] = pq[i + 1];
    }

    size--;

    return minVertex;
}

/* DECREASE KEY */
void decreaseKey(int vertex, int newKey)
{
    for(int i = 0; i < size; i++)
    {
        if(pq[i].vertex == vertex)
        {
            pq[i].key = newKey;
            return;
        }
    }

    printf("Vertex not found!\n");
}

/* DISPLAY QUEUE */
void display()
{
    printf("Priority Queue:\n");
    for(int i = 0; i < size; i++)
    {
        printf("Vertex: %d  Key: %d\n", pq[i].vertex, pq[i].key);
    }
}

/* MAIN FUNCTION */
int main()
{
    insert(0, 10);
    insert(1, 5);
    insert(2, 8);
    insert(3, 2);
    insert(4, 7);

    display();

    printf("\nExtracted Min Vertex: %d\n", extractMin());
    display();

    decreaseKey(2, 1);
    printf("\nAfter decrease key operation:\n");
    display();

    return 0;
}
