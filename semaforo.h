#ifndef SEMAFORO_H
#define SEMAFORO_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

// Funciones auxiliares para inicializar, hacer wait y Signal
void error(const char* errorInfo);
void Signal(int semid, int numSem);
void Wait(int semid, int numSem);
void initSem(int semid, int numSem, int valor);

#endif // SEMAFORO_H
