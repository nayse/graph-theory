#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define INFINITY 9999
#define MAX 10

FILE *file;
FILE *Saida;

void Dijkstra(int Graph[MAX][MAX], int n, int start, int destination, int k) {
  int cost[MAX][MAX], distance[MAX], pred[MAX];
  int visited[MAX], count, mindistance, nextnode, i, j;
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      if (Graph[i][j] == 0)
        cost[i][j] = INFINITY;
      else
        cost[i][j] = Graph[i][j];

  for (i = 0; i < n; i++) {
    distance[i] = cost[start][i];
    pred[i] = start;
    visited[i] = 0;
  }

  distance[start] = 0;
  visited[start] = 1;
  count = 1;

  while (count < n - 1) {
    mindistance = INFINITY;

    for (i = 0; i < n; i++)
    
      if (distance[i] < mindistance && !visited[i]) {
        mindistance = distance[i];
        nextnode = i;
      }

    visited[nextnode] = 1;
    for (i = 0; i < n; i++)
      if (!visited[i])
        if (mindistance + cost[nextnode][i] < distance[i]) {
          distance[i] = mindistance + cost[nextnode][i];
          pred[i] = nextnode;
        }
    count++;
  }
  if(destination != -1){
    if(k == 1)fprintf(Saida,"%d\n", distance[destination]);
    else printf("%d\n", distance[destination]);
    
  }
  else{
    for (i = 0; i < n; i++){
        if(k == 1)fprintf(Saida,"(%d: %d) ", i+1, distance[i]);
        else printf("(%d: %d) ", i+1, distance[i]);
    }
  }
  fclose(Saida);
}

int main(int argc, char **argv) {
  
  if(argc == 1) { // Sem parametros
    printf("Parametros faltando\n");
    exit(0);
  }
  int opt;
  int Graph[MAX][MAX],x , m, n, a, b, c = -1, u, l,k = 0;
    
	while((opt = getopt(argc, argv, ":o:f:hs:i:l")) != -1)
	{
		switch(opt)
		{
            case 'h':
                printf("A Escrita da linha do comando obedece o seguinte padrao:.\\Teste.exe -o Saida.txt -f Entrada.txt -s -i 1 -l 3\n");
                printf("onde a sequencia para os argumentos sao: -h(ajuda),-o 'arquivo_de_saida',-f 'arquivo_de_entrada, -s(para soluçao em ordem\n");
                printf("crescente,-i 'Vertice_inicial',-l 'Vertice_de_destino),Caso o algoritmo so tenha o -i(Vertice_inicial) e aconcelhado nao usar o -s.\n");
                return 0;
            case 'o':
                Saida = fopen(optarg, "w");
                k = 1;
                break;
            case 'f':
                for (int i=0; i<MAX; i++ ){
                    for (int j=0; j<MAX; j++ )
                    {
                        Graph[i][j] = 0;
                    }
                }
                file = fopen(optarg, "r");
                if(file == NULL){
                    printf("erro na leitura do txt");
                }
                fscanf(file, "%d %d" , &n, &m);
                for (int i=0; i<m; i++ ){
                    for (int j=0; j<m; j++ )
                    {
                      fscanf(file, "%d %d %d" , &a, &b, &c);
	                    Graph[a-1][b-1] = c;
	                    Graph[b-1][a-1] = c;
                    }
                break;
                }
            case 's':
                l = -1;
			case 'i':
				u = atoi(optarg)-1;
                l = -1;
				break;
            case 'l':
				l = atoi(optarg)-1;
				break;

		}
	}
  Dijkstra(Graph, n, u, l, k);
  fclose(Saida);
  return 0;
}
