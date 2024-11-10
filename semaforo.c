// semaforo.c
#include "semaforo.h"
#include <stdio.h>
#include <stdlib.h>

// Función de manejo de errores
void error(const char* errorInfo) {
    perror(errorInfo);
    exit(EXIT_FAILURE);
}

// Inicializa el semáforo
void initSem(Semaforo *sem, int valor) {
    sem->value = valor;
    if (pthread_mutex_init(&(sem->mutex), NULL) != 0) {
        error("Error inicializando mutex");
    }
    if (pthread_cond_init(&(sem->cond), NULL) != 0) {
        error("Error inicializando variable de condición");
    }
}

// Realiza la operación Wait (decrecer el valor del semáforo)
void Wait(Semaforo *sem) {
    pthread_mutex_lock(&(sem->mutex));

    // Si no hay recursos disponibles, espera
    while (sem->value <= 0) {
        pthread_cond_wait(&(sem->cond), &(sem->mutex));
    }

    // Decrementa el valor del semáforo (alguien ha tomado un recurso)
    sem->value--;

    pthread_mutex_unlock(&(sem->mutex));
}

// Realiza la operación Signal (incrementar el valor del semáforo)
void Signal(Semaforo *sem) {
    pthread_mutex_lock(&(sem->mutex));

    // Incrementa el valor del semáforo (libera un recurso)
    sem->value++;

    // Despierta a un hilo esperando si es necesario
    pthread_cond_signal(&(sem->cond));

    pthread_mutex_unlock(&(sem->mutex));
}
