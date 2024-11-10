#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "semaforo.h"

// Inicializa el semáforo con un valor específico
void sem_init(Semaforo* sem, int valor) {
    sem->semHandle = CreateSemaphore(NULL, valor, LONG_MAX, NULL);
    if (sem->semHandle == NULL) {
        printf("Error al crear semáforo: %d\n", GetLastError());
        exit(EXIT_FAILURE);
    }
}

// Función Wait (P) - Decrementa el semáforo y bloquea si no hay recursos disponibles
void sem_wait(Semaforo* sem) {
    DWORD dwWaitResult = WaitForSingleObject(sem->semHandle, INFINITE);
    if (dwWaitResult == WAIT_FAILED) {
        printf("Error al esperar el semáforo: %d\n", GetLastError());
        exit(EXIT_FAILURE);
    }
}

// Función Signal (V) - Incrementa el semáforo y despierta a un hilo si estaba esperando
void sem_signal(Semaforo* sem) {
    if (!ReleaseSemaphore(sem->semHandle, 1, NULL)) {
        printf("Error al liberar el semáforo: %d\n", GetLastError());
        exit(EXIT_FAILURE);
    }
}

// Función para destruir el semáforo
void sem_destroy(Semaforo* sem) {
    if (sem->semHandle != NULL) {
        CloseHandle(sem->semHandle);
    }
}
