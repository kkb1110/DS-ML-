#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <time.h>

typedef struct {
    float x, y;
    int cluster;
} Point;

typedef struct {
    float x, y;
} Centroid;

float calcDistance(Point p, Centroid c) {
    return sqrtf((p.x - c.x) * (p.x - c.x) + (p.y - c.y) * (p.y - c.y));
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

void computeCentroids(Point *points, Centroid *centroids, int n, int k) {
    for (int j = 0; j < k; j++) {
        float sumX = 0, sumY = 0;
        int count = 0;
        for (int i = 0; i < n; i++) {
            if (points[i].cluster == j) {
                sumX += points[i].x;
                sumY += points[i].y;
                count++;
            }
        }
        if (count > 0) {
            centroids[j].x = sumX / count;
            centroids[j].y = sumY / count;
        }
    }
}

float calculateSSE(Point *points, Centroid *centroids, int n) {
    float sse = 0.0f;
    for (int i = 0; i < n; i++) {
        float dist = calcDistance(points[i], centroids[points[i].cluster]);
        sse += dist * dist;
    }
    return sse;
}

int kMeans(Point *originalPoints, int n, int k, Centroid *finalCentroids, float *sseOut) {
    Point points[n];
    for (int i = 0; i < n; i++) {
        points[i] = originalPoints[i];
    }

    Centroid centroids[k];
    for (int i = 0; i < k; i++) {
        int randIndex = rand() % n;
        centroids[i].x = points[randIndex].x;
        centroids[i].y = points[randIndex].y;
    }

    assignCluster(points, centroids, n, k);

    int maxIter = 100, iter;
    float threshold = 0.001;
    for (iter = 0; iter < maxIter; iter++) {
        Centroid oldCentroids[k];
        for (int i = 0; i < k; i++) {
            oldCentroids[i] = centroids[i];
        }

        computeCentroids(points, centroids, n, k);
        assignCluster(points, centroids, n, k);

        int stop = 1;
        for (int i = 0; i < k; i++) {
            if (fabsf(centroids[i].x - oldCentroids[i].x) > threshold ||
                fabsf(centroids[i].y - oldCentroids[i].y) > threshold) {
                stop = 0;
                break;
            }
        }

        if (stop) break;
    }

    for (int i = 0; i < k; i++) {
        finalCentroids[i] = centroids[i];
    }

    *sseOut = calculateSSE(points, centroids, n);
    return iter + 1;
}

void printCentroids(Centroid *centroids, int k) {
    for (int i = 0; i < k; i++) {
        printf("  Cluster %d centroid: (%.4f, %.4f)\n", i, centroids[i].x, centroids[i].y);
    }
}

int main() {
    int n, k;
    srand(time(NULL));// Seed for random number generation

    printf("Enter the number of points: ");
    scanf("%d", &n);
    Point points[n];
    printf("Enter the 2D points:\n");
    for (int i = 0; i < n; i++) {
        printf("Enter coordinates of point %d: ", i + 1);
        scanf("%f %f", &points[i].x, &points[i].y);
    }

    printf("Enter the number of clusters (k): ");
    scanf("%d", &k);

    float minSSE = FLT_MAX;
    int bestInstance = 0;
    Centroid bestCentroids[k];

    for (int i = 0; i < 3; i++) {
        Centroid currentCentroids[k];
        float currentSSE;
        int iterations = kMeans(points, n, k, currentCentroids, &currentSSE);

        printf("\nExecution Instance %d:\n", i + 1);
        printf("  Iterations: %d\n", iterations);
        printf("  SSE: %.6f\n", currentSSE);
        printf("  Centroids:\n");
        printCentroids(currentCentroids, k);

        if (currentSSE < minSSE) {
            minSSE = currentSSE;
            bestInstance = i + 1;
            for (int j = 0; j < k; j++) {
                bestCentroids[j] = currentCentroids[j];
            }
        }
    }

    printf("\nBest Instance: %d with Minimum SSE = %.6f\n", bestInstance, minSSE);
    printf("Centroids for Best Instance:\n");
    printCentroids(bestCentroids, k);

    return 0;
}