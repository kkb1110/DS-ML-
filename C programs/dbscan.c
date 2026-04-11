#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_POINTS 1000

typedef struct {
    double x, y;
    int cluster_id;
    int visited;
    int type;
} Point;

Point points[MAX_POINTS];
int n;
double eps;
int minPts;

double distance(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int getNeighbors(int index, int neighbors[]) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (i != index && distance(points[index], points[i]) <= eps) {
            neighbors[count++] = i;
        }
    }
    return count;
}

void expandCluster(int index, int cluster_id) {
    int neighbors[MAX_POINTS];
    int neighbor_count = getNeighbors(index, neighbors);
    points[index].cluster_id = cluster_id;
    points[index].type = 1;
    for (int i = 0; i < neighbor_count; i++) {
        int neighbor_index = neighbors[i];
        if (!points[neighbor_index].visited) {
            points[neighbor_index].visited = 1;
            int new_neighbors[MAX_POINTS];
            int new_count = getNeighbors(neighbor_index, new_neighbors);
            if (new_count + 1 >= minPts) {
                for (int j = 0; j < new_count; j++) {
                    int new_idx = new_neighbors[j];
                    int already_present = 0;
                    for (int k = 0; k < neighbor_count; k++) {
                        if (neighbors[k] == new_idx) {
                            already_present = 1;
                            break;
                        }
                    }
                    if (!already_present) {
                        neighbors[neighbor_count++] = new_idx;
                    }
                }
            }
        }
        if (points[neighbor_index].cluster_id == 0) {
            points[neighbor_index].cluster_id = cluster_id;
        }
    }
}

void dbscan() {
    int cluster_id = 0;
    for (int i = 0; i < n; i++) {
        if (points[i].visited) continue;
        points[i].visited = 1;
        int neighbors[MAX_POINTS];
        int neighbor_count = getNeighbors(i, neighbors);
        if (neighbor_count + 1 < minPts) {
            points[i].cluster_id = -1;
            points[i].type = 3;
        } else {
            cluster_id++;
            expandCluster(i, cluster_id);
        }
    }
    for (int i = 0; i < n; i++) {
        if (points[i].cluster_id > 0 && points[i].type != 1) {
            int neighbors[MAX_POINTS];
            int count = getNeighbors(i, neighbors);
            int nearCore = 0;
            for (int j = 0; j < count; j++) {
                if (points[neighbors[j]].type == 1) {
                    nearCore = 1;
                    break;
                }
            }
            if (nearCore)
                points[i].type = 2;
        }
    }
}

void printResults() {
    printf("\n--- DBSCAN Clustering Results ---\n");
    for (int i = 0; i < n; i++) {
        printf("Point (%.2f, %.2f) -> ", points[i].x, points[i].y);
        if (points[i].cluster_id == -1)
            printf("Noise\n");
        else
            printf("Cluster %d\n", points[i].cluster_id);
    }
    printf("\nCore Points:\n");
    for (int i = 0; i < n; i++) {
        if (points[i].type == 1)
            printf("(%.2f, %.2f)\n", points[i].x, points[i].y);
    }
    printf("\nBorder Points:\n");
    for (int i = 0; i < n; i++) {
        if (points[i].type == 2)
            printf("(%.2f, %.2f)\n", points[i].x, points[i].y);
    }
    printf("\nNoise Points:\n");
    for (int i = 0; i < n; i++) {
        if (points[i].type == 3)
            printf("(%.2f, %.2f)\n", points[i].x, points[i].y);
    }
}

int main() {
    printf("Enter number of points: ");
    scanf("%d", &n);
    if (n > MAX_POINTS) {
        printf("Maximum allowed points is %d\n", MAX_POINTS);
        return 1;
    }
    printf("Enter %d points (x y):\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf", &points[i].x, &points[i].y);
        points[i].visited = 0;
        points[i].cluster_id = 0;
        points[i].type = 0;
    }
    printf("Enter eps (neighborhood radius): ");
    scanf("%lf", &eps);
    printf("Enter minPts (minimum points in cluster): ");
    scanf("%d", &minPts);
    dbscan();
    printResults();
    return 0;
}