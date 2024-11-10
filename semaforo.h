// semaforo.h
#ifndef SEMAFORO_H
#define SEMAFORO_H

#include <pthread.h>

// Estructura para el semáforo utilizando mutex y variable de condición
typedef struct {
    int value;                // Valor del semáforo (número de recursos disponibles)
    pthread_mutex_t mutex;    // Mutex para proteger el acceso
    pthread_cond_t cond;      // Variable de condición para esperar y liberar el semáforo
} Semaforo;

// Declaración de funciones
void initSem(Semaforo *sem, int valor);
void Wait(Semaforo *sem);
void Signal(Semaforo *sem);
void error(const char* errorInfo);

#endif // SEMAFORO_H
