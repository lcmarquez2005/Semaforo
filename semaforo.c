#include "semaforo.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>

void error(const char* errorInfo) {
    perror(errorInfo);
    exit(EXIT_FAILURE);
}

void Signal(int semid, int numSem) {
    struct sembuf sops;
    sops.sem_num = numSem;
    sops.sem_op = 1;   // Operación de señalización
    sops.sem_flg = 0;

    if (semop(semid, &sops, 1) == -1) {
        error("Error al hacer Signal");
    }
}

void Wait(int semid, int numSem) {
    struct sembuf sops;
    sops.sem_num = numSem;
    sops.sem_op = -1;  // Operación de espera
    sops.sem_flg = 0;

    if (semop(semid, &sops, 1) == -1) {
        error("Error al hacer el Wait");
    }
}

void initSem(int semid, int numSem, int valor) {
    if (semctl(semid, numSem, SETVAL, valor) < 0) {
        error("Error iniciando semáforo");
    }
}
