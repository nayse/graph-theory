#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define A 0
#define B 1
#define C 2
#define MAX 10
#define MAX_NODES 1000
#define O 1000000000
FILE *file;
FILE *Saida;

int n,m,l,u,s=0,t=0,i,a,b,c;
int e;
int capacity[MAX_NODES][MAX_NODES];
int flow[MAX_NODES][MAX_NODES];
int color[MAX_NODES];
int pred[MAX_NODES];

int min(int x, int y) {
  return x < y ? x : y;
}

int head, tail;
int q[MAX_NODES + 2];

void enqueue(int x) {
  q[tail] = x;
  tail++;
  color[x] = B;
}

int dequeue() {
  int x = q[head];
  head++;
  color[x] = C;
  return x;
}

int bfs(int start, int target) {
  int u, v;
  for (u = 0; u < n; u++) {
    color[u] = A;
  }
  head = tail = 0;
  enqueue(start);
  pred[start] = -1;
  while (head != tail) {
    u = dequeue();
    for (v = 0; v < n; v++) {
      if (color[v] == A && capacity[u][v] - flow[u][v] > 0) {
        enqueue(v);
        pred[v] = u;
      }
    }
  }
  return color[target] == C;
}

int fordFulkerson(int source, int sink) {
  int i, j, u;
  int max_flow = 0;
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      flow[i][j] = 0;
    }
  }

  while (bfs(source, sink)) {
    int increment = O;
    for (u = n - 1; pred[u] >= 0; u = pred[u]) {
      increment = min(increment, capacity[pred[u]][u] - flow[pred[u]][u]);
    }
    for (u = n - 1; pred[u] >= 0; u = pred[u]) {
      flow[pred[u]][u] += increment;
      flow[u][pred[u]] -= increment;
    }
   
    max_flow += increment;
  }
  return max_flow;
}

int main(int argc, char **argv) {
  if(argc == 1) { // Sem parametros
    printf("Parametros faltando\n");
    exit(0);
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      capacity[i][j] = 0;
    }
  }
  int opt,k =0;
	
  while((opt = getopt(argc, argv, ":o:f:hs:i:l:")) != -1)
	{
		switch(opt)
		{
          case 'h':
                printf("A Escrita da linha do comando obedece o seguinte padrao:.\\Teste.exe -o Saida.txt -f Entrada.txt -s -i 1 -l 3\n");
                printf("onde a sequencia para os argumentos sao: -h(ajuda),-o 'arquivo_de_saida',-f 'arquivo_de_entrada, -s(para soluçao em ordem\n");
                printf("crescente,-i 'Vertice_inicial',-l 'Vertice_de_destino),Esse algoritmo nao aceito o -s, e a entrada deve ter com -i o primeiro vertice\n");
                printf("e -l como o ULTIMO vertice da entrada desejada\n");
                return 0;
            case 'o':
                Saida = fopen(optarg, "w");
                k = 1;
                break;
            case 'f':
                for (int i=0; i<MAX; i++ ){
                    for (int j=0; j<MAX; j++ )
                    {
                        capacity[i][j] = 0;
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
	                    capacity[a-1][b-1] = c;
	                    capacity[b-1][a-1] = c;
                    }
                break;
                }
      case 's':
        //t = -1;
			case 'i':
				s = atoi(optarg)-1;
				break;
      case 'l':
				t = atoi(optarg)-1;
				break;
		}
	}
  if(k == 1)fprintf(Saida,"Max Flow: %d\n", fordFulkerson(s, t));
  else printf("Max Flow: %d\n", fordFulkerson(s, t));
  fclose(Saida);
  return 0;
}