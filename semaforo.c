#include <stdio.h>

#include <pthread.h>

#include <unistd.h>

// Estructura básica de un semáforo
typedef struct {
    int value;  // Valor del semáforo, 0 o 1 para exclusión mutua
    pthread_mutex_t mutex;  // Mutex para sincronización (exclusion mutua)
} Semaphore;

// Inicializar semáforo
void semaphore_init(Semaphore* semaforo, int value) {
    semaforo->value = value;
    pthread_mutex_init(&semaforo->mutex, NULL);
}

// Esperar (down) en el semáforo
void semaphore_wait(Semaphore* semaforo) {
    pthread_mutex_lock(&semaforo->mutex);  // Bloqueo de la sincronización
    while (semaforo->value <= 0) {  // Si el semforo está en 0, espera
        pthread_mutex_unlock(&semaforo->mutex);  // Liberar mutex mientras espera
        usleep(100);  // Dormir brevemente (simula la espera)
        pthread_mutex_lock(&semaforo->mutex);  // Intentar nuevamente
    }
    semaforo->value--;  // Descontar semáforo
    pthread_mutex_unlock(&semaforo->mutex);  // Liberar el mutex
}

// Señalizar (up) en el semáforo
void semaphore_signal(Semaphore* semaforo) {
    pthread_mutex_lock(&semaforo->mutex);  // Bloqueo de la sincronización
    semaforo->value++;  // Incrementar semáforo
    pthread_mutex_unlock(&semaforo->mutex);  // Liberar el mutex
}

// Función de los hilos que acceden a la sección crítica
void* acceso_recurso(void* arg) {
    Semaphore* semaforo = (Semaphore*)arg;

    printf("Hilo %ld esperando...\n", pthread_self());
    semaphore_wait(semaforo);  // Esperar a que el semáforo esté disponible
    
    // Sección crítica
    printf("Hilo %ld accede al recurso.\n", pthread_self());
    sleep(1);  // Simular trabajo con el recurso

    semaphore_signal(semaforo);  // Liberar el semáforo

    return NULL;
}

int main() {
    pthread_t hilos[5];
    Semaphore semaforo;

    // Inicializamos el semáforo con valor 1 (indica que el recurso está disponible)
    semaphore_init(&semaforo, 1);

    // Creamos 5 hilos que intentan acceder al recurso
    for (int i = 0; i < 5; i++) {
        pthread_create(&hilos[i], NULL, acceso_recurso, (void*)&semaforo);
    }

    // Esperamos que todos los hilos terminen
    for (int i = 0; i < 5; i++) {
        pthread_join(hilos[i], NULL);
    }

    // Destruimos el mutex al final
    pthread_mutex_destroy(&semaforo.mutex);

    return 0;
}
