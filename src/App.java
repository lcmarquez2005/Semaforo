
public class App {

    public static void main(String[] args) {
        Semaforo s = new Semaforo();
        // Creamos varios hilos
        Thread[] hilos = new Thread[5];
        for (int i = 0; i < 5; i++) {
            final int id = i + 1;
            hilos[i] = new Thread(() -> s.modificarArchivo(id));
            hilos[i].start();
        }

        // Esperamos que todos los hilos terminen
        for (Thread hilo : hilos) {
            try {
                hilo.join();//espera a que todos los hilos termine
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        }
    }

}
