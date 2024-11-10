#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "semaforo.h"  // Incluir el archivo de semáforos

int main() {
    printf("Sincronizacion con Semaforos\n");
    int semaforo;
    int numPlazas = 2; // Configurar el número de plazas disponibles

    // Crear semáforo con permisos 0700
    if ((semaforo = semget(IPC_PRIVATE, 1, IPC_CREAT | 0700)) < 0) {
        error("Error al crear semáforo con semget");
    }

    // Inicializar el semáforo con el número de plazas
    initSem(semaforo, 0, numPlazas);
    printf("Hay %d plazas libres\n", numPlazas);

    for (int i = 0; i < 2; i++) { // Crear dos procesos hijo para ilustrar la sincronización
        pid_t pid = fork();
        if (pid == -1) {
            error("Error en el fork");
        }

        if (pid == 0) { // Código del proceso hijo
            Wait(semaforo, 0);
            printf("Hijo %d entra, el padre o otro hijo espera\n", getpid());
            sleep(3); // Simular trabajo
            printf("Hijo %d sale\n", getpid());
            Signal(semaforo, 0);
            exit(EXIT_SUCCESS);
        }
    }

    // Esperar a que todos los procesos hijo terminen
    for (int i = 0; i < 2; i++) {
        wait(NULL);
    }

    // Liberar el semáforo
    if (semctl(semaforo, 0, IPC_RMID) == -1) {
        error("Error al liberar el semáforo");
    }

    printf("Semáforo liberado y finalizado\n");
    return 0;
}
