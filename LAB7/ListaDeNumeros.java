import java.sql.Array;
import java.util.ArrayList;
import java.util.Random;

public class ListaDeNumeros {
    private Integer tamanhoDoVetor;
    private int[] numeros;
    private Integer quantidadeDePares;
    
    // construtor que inicia a lista de números a serem checados
    public ListaDeNumeros(Integer tamanhoDoVetor){
        this.tamanhoDoVetor = tamanhoDoVetor;
        this.quantidadeDePares = 0;
        this.numeros = new int[tamanhoDoVetor];
        Random gerador = new Random();
        for (int i = 0; i < tamanhoDoVetor; i++) {
            numeros[i] = gerador.nextInt(101); // adiciona inteiros entre 0 e 100 no array
        }
    }

    public Integer getTamanhoDoVetor() {
        return tamanhoDoVetor;
    }

    public int[] getListaDeNumeros() {
        return numeros;
    }

    public Integer getQuantidadeDePares() {
        return quantidadeDePares;
    }

    // metodo que adiciona um par na contagem utilizando exclusao mutua
    public synchronized void addQuantidadeDePares() {
        this.quantidadeDePares++;
    }
}
