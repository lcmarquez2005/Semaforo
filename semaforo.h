#ifndef SEMAFORO_H
#define SEMAFORO_H

#include <windows.h>

// Estructura personalizada para un semáforo
typedef struct {
    HANDLE semHandle; // Manejador del semáforo en Windows
} Semaforo;

// Funciones para manejar el semáforo
void sem_init(Semaforo* sem, int valor);      // Inicializa el semáforo
void sem_wait(Semaforo* sem);                 // Decrementa el semáforo
void sem_signal(Semaforo* sem);               // Incrementa el semáforo
void sem_destroy(Semaforo* sem);              // Destruye el semáforo

#endif // SEMAFORO_H
