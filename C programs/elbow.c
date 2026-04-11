#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

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

void kMeans(Point *originalPoints, int n, int k, float *sse) {
    Point points[n];
    for (int i = 0; i < n; i++) {
        points[i] = originalPoints[i];
    }

    Centroid centroids[k];
    for (int i = 0; i < k; i++) {
        centroids[i].x = points[i % n].x;
        centroids[i].y = points[i % n].y;
    }

    assignCluster(points, centroids, n, k);

    int maxIter = 100;
    float threshold = 0.001;
    for (int iter = 0; iter < maxIter; iter++) {
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

    *sse = calculateSSE(points, centroids, n);
}

int main() {
    int n;
    printf("Enter the number of points : ");
    scanf("%d", &n);
    Point points[n];
    printf("Enter the 2D points\n");
    for (int i = 0; i < n; i++) {
        printf("Enter %d coordinates: ", i + 1);
        scanf("%f %f", &points[i].x, &points[i].y);
    }

    float minSSE = FLT_MAX;
    int optimalK = 2;

    printf("\nElbow Method Analysis:\n");
    for (int k = 2; k <= 10; k++) {
        float sse;
        kMeans(points, n, k, &sse);
        printf("k = %d, SSE = %.6f\n", k, sse);
        if (sse < minSSE) {
            minSSE = sse;
            optimalK = k;
        }
    }

    printf("\nOptimal value of k = %d with Minimum SSE = %.6f\n", optimalK, minSSE);
    return 0;
}