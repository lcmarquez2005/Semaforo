public class Semaforo {
    private static int semaforo = 1;  // Semáforo inicializado a 1
    private static final Object lock = new Object();  // Objeto de bloqueo

    // Función que simula modificar un archivo
    public static void modificarArchivo(int id) {
        esperarSemaforo();  // Intentamos obtener el semáforo

        // Simulamos la modificación del archivo
        System.out.println("Hilo " + id + " está modificando el archivo.");
        try {
            Thread.sleep(1000);  // Simula el tiempo de modificación
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }

        liberarSemaforo();  // Liberamos el semáforo
    }
    // Función para esperar a que el semáforo esté disponible
    public static void esperarSemaforo() {
        synchronized (lock) {
            while (semaforo <= 0) {
                try {
                    lock.wait();  // Espera activa si el semáforo no está disponible
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                }
            }
            semaforo--;  // Adquirimos el semáforo
        }
    }

    // Función para liberar el semáforo
    public static void liberarSemaforo() {
        synchronized (lock) {
            semaforo++;  // Liberamos el semáforo
            lock.notify();  // Notificamos a otros hilos que el semáforo está disponible
        }
    }
}
