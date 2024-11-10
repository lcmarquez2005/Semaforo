#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "semaforo.h"

// Función de ejemplo que simula el trabajo de un hilo
DWORD WINAPI trabajo(LPVOID param) {
    Semaforo* sem = (Semaforo*)param;
    
    sem_wait(sem);  // Solicita acceso al semáforo (decrementa el contador)
    printf("Hilo %lu entra y trabaja\n", GetCurrentThreadId());
    Sleep(2000); // Simula trabajo
    printf("Hilo %lu termina su trabajo\n", GetCurrentThreadId());
    sem_signal(sem);  // Libera el semáforo (incrementa el contador)
    
    return 0;
}

int main() {
    Semaforo sem;
    sem_init(&sem, 2);  // Inicializa el semáforo con 2 recursos disponibles

    HANDLE hilos[3];

    // Crear 3 hilos para simular trabajo
    for (int i = 0; i < 3; i++) {
        hilos[i] = CreateThread(NULL, 0, trabajo, (LPVOID)&sem, 0, NULL);
        if (hilos[i] == NULL) {
            printf("Error al crear hilo: %d\n", GetLastError());
            exit(EXIT_FAILURE);
        }
    }

    // Esperar a que todos los hilos terminen
    WaitForMultipleObjects(3, hilos, TRUE, INFINITE);

    // Destruir el semáforo
    sem_destroy(&sem);

    // Cerrar los hilos
    for (int i = 0; i < 3; i++) {
        CloseHandle(hilos[i]);
    }

    return 0;
}
