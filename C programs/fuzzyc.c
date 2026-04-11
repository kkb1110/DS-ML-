#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double x, y;
} Point;

Point *points;
double **membership;
Point *centroids;

int n;
int c;
double m;
int maxIter;
double epsilon;

double distance(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

void initializeMembership() {
    for (int i = 0; i < n; i++) {
        double sum = 0.0;
        for (int j = 0; j < c; j++) {
            membership[i][j] = (double)rand() / RAND_MAX;
            sum += membership[i][j];
        }
        for (int j = 0; j < c; j++) {
            membership[i][j] /= sum;
        }
    }
}

void updateCentroids() {
    for (int j = 0; j < c; j++) {
        double numerator_x = 0.0, numerator_y = 0.0, denominator = 0.0;
        for (int i = 0; i < n; i++) {
            double u_ij_m = pow(membership[i][j], m);
            numerator_x += u_ij_m * points[i].x;
            numerator_y += u_ij_m * points[i].y;
            denominator += u_ij_m;
        }
        if (denominator != 0) {
            centroids[j].x = numerator_x / denominator;
            centroids[j].y = numerator_y / denominator;
        }
    }
}

void updateMembership() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < c; j++) {
            double dist_ij = distance(points[i], centroids[j]);
            if (dist_ij == 0.0) {
                membership[i][j] = 1.0;
                for (int k = 0; k < c; k++) {
                    if (k != j)
                        membership[i][k] = 0.0;
                }
                break;
            } else {
                double sum = 0.0;
                for (int k = 0; k < c; k++) {
                    double dist_ik = distance(points[i], centroids[k]);
                    if (dist_ik == 0.0)
                        dist_ik = 1e-6;
                    sum += pow(dist_ij / dist_ik, 2.0 / (m - 1));
                }
                membership[i][j] = 1.0 / sum;
            }
        }
    }
}

int isConverged(Point *oldCentroids) {
    for (int j = 0; j < c; j++) {
        if (distance(centroids[j], oldCentroids[j]) > epsilon)
            return 0;
    }
    return 1;
}

void printIterationResults(int iter) {
    printf("\n=== Iteration %d ===\n", iter + 1);
    printf("\nCluster Centers:\n");
    for (int j = 0; j < c; j++) {
        printf("C%d: (%.5f, %.5f)\n", j + 1, centroids[j].x, centroids[j].y);
    }
    printf("\nMembership Matrix:\n");
    for (int i = 0; i < n; i++) {
        printf("Point (%.2f, %.2f): ", points[i].x, points[i].y);
        for (int j = 0; j < c; j++) {
            printf("u%d=%.4f ", j + 1, membership[i][j]);
        }
        printf("\n");
    }
    printf("\nDominant Cluster Assignments:\n");
    for (int i = 0; i < n; i++) {
        int bestCluster = 0;
        double maxU = membership[i][0];
        for (int j = 1; j < c; j++) {
            if (membership[i][j] > maxU) {
                maxU = membership[i][j];
                bestCluster = j;
            }
        }
        printf("Point (%.2f, %.2f) -> Cluster %d (%.4f)\n",
               points[i].x, points[i].y, bestCluster + 1, maxU);
    }
}

void fuzzyCMeans() {
    initializeMembership();
    for (int iter = 0; iter < maxIter; iter++) {
        Point *oldCentroids = (Point *)malloc(c * sizeof(Point));
        for (int j = 0; j < c; j++)
            oldCentroids[j] = centroids[j];
        updateCentroids();
        updateMembership();
        printIterationResults(iter);
        if (isConverged(oldCentroids)) {
            printf("\nConverged after %d iterations.\n", iter + 1);
            free(oldCentroids);
            return;
        }
        free(oldCentroids);
    }
    printf("\nReached max iterations (%d) without full convergence.\n", maxIter);
}

void printFinalResults() {
    printf("\n========== FINAL RESULTS ==========\n");
    printf("\nFinal Cluster Centers:\n");
    for (int j = 0; j < c; j++) {
        printf("Cluster %d: (%.4f, %.4f)\n", j + 1, centroids[j].x, centroids[j].y);
    }
    printf("\nFinal Dominant Cluster Assignments:\n");
    for (int i = 0; i < n; i++) {
        int bestCluster = 0;
        double maxU = membership[i][0];
        for (int j = 1; j < c; j++) {
            if (membership[i][j] > maxU) {
                maxU = membership[i][j];
                bestCluster = j;
            }
        }
        printf("Point (%.2f, %.2f) -> Cluster %d (u=%.4f)\n",
               points[i].x, points[i].y, bestCluster + 1, maxU);
    }
}

int main() {
    printf("Enter number of points: ");
    scanf("%d", &n);
    points = (Point *)malloc(n * sizeof(Point));
    if (!points) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    printf("Enter %d points (x y):\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf", &points[i].x, &points[i].y);
    }
    printf("Enter number of clusters (c): ");
    scanf("%d", &c);
    centroids = (Point *)malloc(c * sizeof(Point));
    membership = (double **)malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++) {
        membership[i] = (double *)malloc(c * sizeof(double));
    }
    printf("Enter fuzziness parameter m (>1): ");
    scanf("%lf", &m);
    if (m <= 1.0) m = 2.0;
    printf("Enter convergence threshold (e.g., 0.00001): ");
    scanf("%lf", &epsilon);
    printf("Enter max iterations: ");
    scanf("%d", &maxIter);
    fuzzyCMeans();
    printFinalResults();
    for (int i = 0; i < n; i++)
        free(membership[i]);
    free(membership);
    free(points);
    free(centroids);
    return 0;
}