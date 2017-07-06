#include<stdio.h>

/*

    Algoritmo que busca um caminho que passa por todos os vértices do grafo pelo menos um vez.
    
    Esse algoritmo foi baseado no algoritmo de busca em profundidade do site http://www.thecrazyprogrammer.com/2014/03/depth-first-search-dfs-traversal-of-a-graph.html


*/

void DFS(int);
int G[10][10],visited[10],n;
int rota[10], count;    //n is no of vertices and graph is sorted in array G[10][10]

void main()
{
    int i,j;
    printf("Enter number of vertices:");

    scanf("%d",&n);
    //read the adjecency matrix
    printf("\nEnter adjecency matrix of the graph:");

    for(i=0;i<n;i++)
     for(j=0;j<n;j++)
        scanf("%d",&G[i][j]);

    //visited is initialized to zero
    for(i=0;i<n;i++)
        visited[i]=0;
    

    DFS(0);

}



//Retorna verdade se 2 vértices são vizinhos e falso caso contrário

int vizinho (int i, int j) {
    if (G[i][j] == 1) {
        return 1;
    }
    return 0;
}

//Verifica se o vértice pode ser inserido na rota   
int validacao(int i) {
    int j = 0;
    for (j = 0; j < count; j++) {
        if (rota[j] == i) {
            return 0;
        }
    }
    return 1;
}



//Retona o proximo vizinho de 'i' a ser testado depois de 'j', caso exista. Se não houver mais vizinhos retorna -1
int prox_vizinho(int i, int j) {
    int k = 0;
    for (k = j + 1; k < n; k++) {
        if (k != i && vizinho(i,k)) {
            return k;
        }
    }
    return -1;
}

//Imprime a rota
void print_route() {
    for (int i = 0; i < count; i++){
        printf (" %d -> ",rota[i]+1);
    }
    printf("\n");
}

//Checa se todos os vertices já foram vizitados
int check_route() {
    print_route();
    for (int j = 0; j < n; j++) {
        int found = 0;
        for (int i = 0; i < n; i++) {
            if (rota[i] == j) {
                found = 1;
            }
        }
        if (!found) { return 0; }
    }
    return 1; 
}

// Seta todos os valores do vetor como zero a partir da posição X
void inicializa(int x) {
    for (int i = x; i < n; i++) {
        rota[i] = 0;
    }
}


//      Algoritomo que busca a partir do vérticie 'i'
void DFS(int i)
{   

    int j;
    rota[count] = i;
    count++;
    if (!check_route()) {
        printf("teste1 \n");
        j = prox_vizinho(i,rota[count]);
        //Se houver mais vizinhos entra nesse IF
        if (j >= 0) {
            printf("vizinho :  %d \n" ,j);

            //Caso possa inserir J na rota, ele irá chamar a busca a partir de J
            if ( validacao(j) ) {
                DFS(j);

            //Caso contrário ele irá tentar o próximo vizinho depois de J
            } else {
                rota[count] = j;
                count--;
                DFS(i);
            }
        //Se não houver mais vizinhos a serem testados ele volta na rota pra testar todas as possibilidades
        //O 'count' armazena em qual posição do vetor eu estou       
        } else {
            printf("entrei no else %d \n" ,count);

            count = count-2;
            if (count >= 0) {
                inicializa(count+2);
                DFS(rota[count]);
            } else { 
                printf("acabou");
            }
        }
    } else {
        printf("ACHOU ROTA\n");
    }
}


/* 
    O QUE PODEMOS PARALELIZAR? 
        Podemos botar cada thread indo pra algum lado da arvore.
        Podemos verificar questão de menor custo (aí iriamos chegar no caixeiro viajante).
        Quando alguma thread acabar podemos parar o programa e ver quanto tempo de execução deu

*/



/*

Grafo pra teste

6

0 1 0 0 1 0
1 0 1 0 1 0
0 1 0 1 1 0
0 0 1 0 1 1
1 1 1 1 0 0
0 0 0 1 0 0
*/

