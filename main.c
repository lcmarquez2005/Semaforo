// main.c
#include "semaforo.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Función para simular el trabajo de un proceso hijo
void* trabajo(void *arg) {
    Semaforo *sem = (Semaforo *)arg;

    Wait(sem);
    printf("Hijo %ld entra, el padre o otro hijo espera\n", pthread_self());
    sleep(3);  // Simulando trabajo
    printf("Hijo %ld sale\n", pthread_self());
    Signal(sem);

    return NULL;
}

int main() {
    printf("Sincronización con Semáforos en Unix\n");

    Semaforo sem;
    int numPlazas = 1;  // Número de recursos disponibles

    // Inicializamos el semáforo con el valor de plazas
    initSem(&sem, numPlazas);
    printf("Hay %d plazas libres\n", numPlazas);

    pthread_t threads[2];  // Array para guardar los hilos

    // Crear dos hilos para simular los procesos hijos
    for (int i = 0; i < 2; i++) {
        if (pthread_create(&threads[i], NULL, trabajo, (void*)&sem) != 0) {
            perror("Error creando el hilo");
            exit(EXIT_FAILURE);
        }
    }

    // Esperar a que todos los hilos terminen
    for (int i = 0; i < 4; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Semáforo liberado y finalizado\n");

    // Liberar los recursos
    pthread_mutex_destroy(&sem.mutex);
    pthread_cond_destroy(&sem.cond);

    return 0;
}
