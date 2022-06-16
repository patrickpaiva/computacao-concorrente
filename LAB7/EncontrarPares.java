import java.util.Arrays;

public class EncontrarPares {
    // static final int NTHREADS = 2;

    public static void main(String[] args) {
        if(args.length != 2){
            System.out.println("Coloque os parametros na forma EncontrarPares [Tamanho da Lista] [Numero de Threads]");
        }
        Integer tamanhoDoVetor = Integer.parseInt(args[0]); // pega o tamanho da lista solicitado
        Integer NThreads = Integer.parseInt(args[1]); // pega o numero de threads solicitado
        Thread[] threads = new Thread[NThreads]; // aloca um array de threads na memória

        ListaDeNumeros lista = new ListaDeNumeros(tamanhoDoVetor);

        System.out.println("Lista de Numeros");
        System.out.println(Arrays.toString(lista.getListaDeNumeros()));

        //cria as threads da aplicacao
        for (int i=0; i<threads.length; i++) {
            threads[i] = new TarefaThread(i, lista, NThreads);
        }

        //inicia as threads
        for (int i=0; i<threads.length; i++) {
            threads[i].start();
        }

        //espera pelo termino de todas as threads
        for (int i=0; i<threads.length; i++) {
            try { threads[i].join(); } catch (InterruptedException e) { return; }
        }

        System.out.println("Quantidade de Pares = " + lista.getQuantidadeDePares());
    }
}
