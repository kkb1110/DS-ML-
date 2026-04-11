
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    float x, y;
    int cluster;
} Point;

typedef struct {
    float x, y;
} Centroid;

float calcDistance(Point p, Centroid c) {
    return sqrt(((p.x - c.x) * (p.x - c.x)) + ((p.y - c.y) * (p.y - c.y)));
}

void assignCluster(Point *points, Centroid *centroids, int n, int k) {
    for (int i = 0; i < n; i++) {
        float minDist = calcDistance(points[i], centroids[0]);
        int cluster = 0;
        for (int j = 1; j < k; j++) {
            float dist = calcDistance(points[i], centroids[j]);
            if (dist < minDist) {
                minDist = dist;
                cluster = j;
            }
        }
        points[i].cluster = cluster;
    }
}

void updateCentroids(Point *points, Centroid *centroids, int n, int k) {
    float sumX, sumY;
    int count;
    for (int j = 0; j < k; j++) {
        sumX = sumY = 0.0f;
        count = 0;
        for (int i = 0; i < n; i++) {
            if (points[i].cluster == j) {
                sumX += points[i].x;
                sumY += points[i].y;
                count++;
            }
        }
        if (!count) continue; //signify no points assigned to this cluster ,if not used may cause division by zero
        centroids[j].x = sumX / count;
        centroids[j].y = sumY / count;
    }
    assignCluster(points, centroids, n, k);
}

void printCluster(Point *points, int n) {
    for (int i = 0; i < n; i++) {
        printf("Point (%.4f %.4f) assigned to Cluster -> %d\n", points[i].x, points[i].y, points[i].cluster);
    }
    printf("\n");
}

void printCentroids(char *label, Centroid *centroids, int k) {
    printf("%s\n", label);
    for (int i = 0; i < k; i++) {
        printf("  Cluster %d centroid: (%.6f, %.6f)\n", i, centroids[i].x, centroids[i].y);
    }
    printf("\n");
}

int main() {
    int n, k = 2;
    printf("Enter the number of points : ");
    scanf("%d", &n);
    Point points[n];
    printf("Enter the 2D points \n");
    for (int i = 0; i < n; i++) {
        printf("Enter coordinates for point %d: ", i + 1);
        scanf("%f %f", &points[i].x, &points[i].y);
    }
    Centroid centroids[k];
    Centroid oldValue[k];
    centroids[0].x = points[0].x;
    centroids[0].y = points[0].y;
    centroids[1].x = points[1].x;
    centroids[1].y = points[1].y;
    assignCluster(points, centroids, n, k);
    printf("\nInitial Assignment\n");
    printCluster(points, n);
    printCentroids("Initial Centroids:", centroids, k);
    int count = 1;
    float threshold = 0.001;
    while (count < 10) {
        for (int i = 0; i < k; i++) {
            oldValue[i].x = centroids[i].x;
            oldValue[i].y = centroids[i].y;
        }
        updateCentroids(points, centroids, n, k);
        printf("Iteration %d\n", count);
        printCluster(points, n);
        printCentroids("Previous Centroids:", oldValue, k);
        printCentroids("Updated Centroids:", centroids, k);
        int flag = 0;
        for (int i = 0; i < k; i++) {
            if (fabsf(oldValue[i].x - centroids[i].x) < threshold && fabsf(oldValue[i].y - centroids[i].y) < threshold)
                flag++;
        }
        if (flag == k) break;
        count++;
    }
    return 0;
}
