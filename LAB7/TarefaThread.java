import java.util.ArrayList;

public class TarefaThread extends Thread {
    private Integer id;
    ListaDeNumeros listaDeNumeros;
    Integer NThreads;

    public TarefaThread(Integer id, ListaDeNumeros listaDeNumeros, Integer NThreads) {
        this.id = id;
        this.listaDeNumeros = listaDeNumeros;
        this.NThreads = NThreads;
    }

    public void run(){
        System.out.println("Thread " + (this.id+1) + " iniciou!");
        int[] numeros = listaDeNumeros.getListaDeNumeros();
        for (int i = this.id; i < listaDeNumeros.getTamanhoDoVetor(); i+=NThreads) {
            if((numeros[i] % 2) == 0){
                listaDeNumeros.addQuantidadeDePares();
            }
        }
        System.out.println("Thread " + (this.id+1) + " terminou!");
    }

}
