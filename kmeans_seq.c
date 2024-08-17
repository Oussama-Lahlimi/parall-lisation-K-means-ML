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
    // Paramètres de l'algorithme K-means
    int numClusters = 3; // Nombre de clusters à trouver
    int numDataPoints = 1000; // Nombre de points de données
    int dataDimension = 2; // Dimension des données (2D dans cet exemple)
    int numIterations = 100; // Nombre d'itérations de l'algorithme K-means

    // Allouer de l'espace pour les données (données aléatoires pour la démonstration)
    double** data = (double**)malloc(numDataPoints * sizeof(double*)); // Allouer un tableau de pointeurs pour stocker les données
    for (int i = 0; i < numDataPoints; i++) {
        data[i] = (double*)malloc(dataDimension * sizeof(double)); // Allouer un tableau pour chaque point de données
        for (int j = 0; j < dataDimension; j++) {
            data[i][j] = (double)rand() / RAND_MAX; // Génération de données aléatoires pour chaque point
        }
    }

    // Allouer de l'espace pour les centroïdes (initialisation aléatoire pour la démonstration)
    double** centroids = (double**)malloc(numClusters * sizeof(double*)); // Allouer un tableau de pointeurs pour stocker les centroïdes
    for (int i = 0; i < numClusters; i++) {
        centroids[i] = (double*)malloc(dataDimension * sizeof(double)); // Allouer un tableau pour chaque centroïde
        for (int j = 0; j < dataDimension; j++) {
            centroids[i][j] = (double)rand() / RAND_MAX; // Initialisation aléatoire des positions initiales des centroïdes
        }
    }

    // Boucle d'itérations de l'algorithme K-means
    for (int iter = 0; iter < numIterations; iter++) {
        // Créer des tableaux pour stocker les nouvelles positions des centroïdes et le nombre de points dans chaque cluster
        double** newCentroids = (double**)malloc(numClusters * sizeof(double*)); // Allouer un tableau de pointeurs pour les nouvelles positions des centroïdes
        int* clusterSizes = (int*)malloc(numClusters * sizeof(int)); // Allouer un tableau pour stocker le nombre de points dans chaque cluster

        for (int i = 0; i < numClusters; i++) {
            newCentroids[i] = (double*)malloc(dataDimension * sizeof(double)); // Allouer un tableau pour chaque nouveau centroïde
            clusterSizes[i] = 0; // Initialiser le nombre de points dans chaque cluster à zéro
        }

        for (int i = 0; i < numDataPoints; i++) {
            int closestCentroid = 0;
            double minDistance = distance(data[i], centroids[0], dataDimension);

            // Trouver le centroïde le plus proche
            for (int j = 1; j < numClusters; j++) {
                double dist = distance(data[i], centroids[j], dataDimension);
                if (dist < minDistance) {
                    minDistance = dist;
                    closestCentroid = j;
                }
            }

            // Mettre à jour le centroïde du cluster
            for (int k = 0; k < dataDimension; k++) {
                newCentroids[closestCentroid][k] += data[i][k];
            }
            clusterSizes[closestCentroid]++;
        }

        // Mettre à jour les positions des centroïdes
        for (int i = 0; i < numClusters; i++) {
            for (int j = 0; j < dataDimension; j++) {
                if (clusterSizes[i] > 0) {
                    centroids[i][j] = newCentroids[i][j] / clusterSizes[i];
                }
            }
        }

        // Libérer la mémoire allouée pour les nouvelles positions des centroïdes et les tailles de cluster
        for (int i = 0; i < numClusters; i++) {
            free(newCentroids[i]);
        }
        free(newCentroids);
        free(clusterSizes);
    }

    // Afficher les résultats (les centroïdes finaux)
    printf("Centroïdes finaux :\n");
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

    // Libérer la mémoire allouée pour les données et les centroïdes
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
