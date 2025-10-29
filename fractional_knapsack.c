#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int index;
    int profit;
    int weight;
    double ratio;
} Item;

void swap(Item* x, Item* y) {
    Item temp = *x;
    *x = *y;
    *y = temp;
}

int partition(Item arr[], int low, int high) {
    double pivot = arr[high].ratio;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j].ratio > pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quick_sort(Item arr[], int low, int high) {
    if (low < high) {
        int pivot = partition(arr, low, high);
        quick_sort(arr, low, pivot - 1);
        quick_sort(arr, pivot + 1, high);
    }
}

double fractional_knapsack(int p[], int w[], int n, int capacity) {
    Item items[n];
    
    for (int i = 0; i < n; i++) {
        items[i].index = i + 1;
        items[i].profit = p[i];
        items[i].weight = w[i];
        items[i].ratio = (double)p[i] / w[i];
    }

    // Sort items based on profit/weight ratio in descending order
    quick_sort(items, 0, n - 1);

    double total = 0.0;
    int remain = capacity;

    for (int i = 0; i < n && remain > 0; i++) {
        if (items[i].weight <= remain) {
            total += items[i].profit;
            remain -= items[i].weight;
        } else {
            double fraction = (double)remain / items[i].weight;
            total += items[i].profit * fraction;
            remain = 0;
        }
    }

    return total;
}

int main() {
    int profit[] = {3, 4, 5, 6};
    int weight[] = {2, 3, 4, 5};
    int cap = 5;
    int n = sizeof(profit) / sizeof(profit[0]);

    double ans = fractional_knapsack(profit, weight, n, cap);
    printf("Maximum profit: %.2f\n", ans);

    return 0;
}
