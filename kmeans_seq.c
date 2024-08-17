#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Fonction pour calculer la distance euclidienne entre deux points
double distance(const double* p1, const double* p2, int dimension) {
    double dist = 0.0;
    for (int i = 0; i < dimension; i++) {
        double diff = p1[i] - p2[i];
        dist += diff * diff;
    }
    return sqrt(dist);
}

int main() {
    // Param�tres de l'algorithme K-means
    int numClusters = 3; // Nombre de clusters � trouver
    int numDataPoints = 1000; // Nombre de points de donn�es
    int dataDimension = 2; // Dimension des donn�es (2D dans cet exemple)
    int numIterations = 100; // Nombre d'it�rations de l'algorithme K-means

    // Allouer de l'espace pour les donn�es (donn�es al�atoires pour la d�monstration)
    double** data = (double**)malloc(numDataPoints * sizeof(double*)); // Allouer un tableau de pointeurs pour stocker les donn�es
    for (int i = 0; i < numDataPoints; i++) {
        data[i] = (double*)malloc(dataDimension * sizeof(double)); // Allouer un tableau pour chaque point de donn�es
        for (int j = 0; j < dataDimension; j++) {
            data[i][j] = (double)rand() / RAND_MAX; // G�n�ration de donn�es al�atoires pour chaque point
        }
    }

    // Allouer de l'espace pour les centro�des (initialisation al�atoire pour la d�monstration)
    double** centroids = (double**)malloc(numClusters * sizeof(double*)); // Allouer un tableau de pointeurs pour stocker les centro�des
    for (int i = 0; i < numClusters; i++) {
        centroids[i] = (double*)malloc(dataDimension * sizeof(double)); // Allouer un tableau pour chaque centro�de
        for (int j = 0; j < dataDimension; j++) {
            centroids[i][j] = (double)rand() / RAND_MAX; // Initialisation al�atoire des positions initiales des centro�des
        }
    }

    // Boucle d'it�rations de l'algorithme K-means
    for (int iter = 0; iter < numIterations; iter++) {
        // Cr�er des tableaux pour stocker les nouvelles positions des centro�des et le nombre de points dans chaque cluster
        double** newCentroids = (double**)malloc(numClusters * sizeof(double*)); // Allouer un tableau de pointeurs pour les nouvelles positions des centro�des
        int* clusterSizes = (int*)malloc(numClusters * sizeof(int)); // Allouer un tableau pour stocker le nombre de points dans chaque cluster

        for (int i = 0; i < numClusters; i++) {
            newCentroids[i] = (double*)malloc(dataDimension * sizeof(double)); // Allouer un tableau pour chaque nouveau centro�de
            clusterSizes[i] = 0; // Initialiser le nombre de points dans chaque cluster � z�ro
        }

        for (int i = 0; i < numDataPoints; i++) {
            int closestCentroid = 0;
            double minDistance = distance(data[i], centroids[0], dataDimension);

            // Trouver le centro�de le plus proche
            for (int j = 1; j < numClusters; j++) {
                double dist = distance(data[i], centroids[j], dataDimension);
                if (dist < minDistance) {
                    minDistance = dist;
                    closestCentroid = j;
                }
            }

            // Mettre � jour le centro�de du cluster
            for (int k = 0; k < dataDimension; k++) {
                newCentroids[closestCentroid][k] += data[i][k];
            }
            clusterSizes[closestCentroid]++;
        }

        // Mettre � jour les positions des centro�des
        for (int i = 0; i < numClusters; i++) {
            for (int j = 0; j < dataDimension; j++) {
                if (clusterSizes[i] > 0) {
                    centroids[i][j] = newCentroids[i][j] / clusterSizes[i];
                }
            }
        }

        // Lib�rer la m�moire allou�e pour les nouvelles positions des centro�des et les tailles de cluster
        for (int i = 0; i < numClusters; i++) {
            free(newCentroids[i]);
        }
        free(newCentroids);
        free(clusterSizes);
    }

    // Afficher les r�sultats (les centro�des finaux)
    printf("Centro�des finaux :\n");
    for (int i = 0; i < numClusters; i++) {
        printf("Cluster %d : [", i);
        for (int j = 0; j < dataDimension; j++) {
            printf("%lf", centroids[i][j]);
            if (j < dataDimension - 1) {
                printf(", ");
            }
        }
        printf("]\n");
    }

    // Lib�rer la m�moire allou�e pour les donn�es et les centro�des
    for (int i = 0; i < numDataPoints; i++) {
        free(data[i]);
    }
    free(data);

    for (int i = 0; i < numClusters; i++) {
        free(centroids[i]);
    }
    free(centroids);

    return 0;
}
