#include <iostream>
#include <climits>
#include <fstream>
#include <sstream>
#include <string>


using namespace std;


class EDGES
{
public:
    int source, destiny, weight;
};

class Graph
{
public:
    int VERT, E;
    EDGES* EDGES;
};

Graph* createGraph(int VERT, int E);
void bellF(struct Graph* Graph, int source);

int main(int argc, char **argv)
{
    string Line;
    string sub;
    stringstream strParaIntAux;
    int iter = 0, i = 0;
    int VERT, E, indiceGraph = 0;
    int source = 0, destiny = 0, weight = 0;
    Graph* G;

    fstream file; 
    file.open(argVERT[1], ios::in);
    if(file.is_open())
    {
        while(getLine(file, Line))
        {
            if (iter == 0)
            {
                for(int indiceLine = 0; indiceLine < Line.length(); indiceLine++)
                {
                    if (Line[indiceLine] != '')
                    {
                        sub += Line[indiceLine];
                    }
                    else
                    {
                        strParaIntAux << sub;
                        strParaIntAux >> VERT;
                        sub.clear();
                        strParaIntAux.clear();
                    }
                }
                strParaIntAux << sub;
                strParaIntAux >> E;
                sub.clear();
                G = criarGraph(VERT, E);
            }
            else
            {
                i = 0;
                sub.clear();
                for(int indiceLine = 0; indiceLine < Line.length(); indiceLine++)
                {
                    if (Line[indiceLine] != ' ')
                    {
                        sub += Line[indiceLine];
                    }
                    else
                    {
                        if(i == 0)
                        {
                            strParaIntAux << sub;
                            strParaIntAux >> source;
                            sub.clear();
                            strParaIntAux.clear();
                        }
                        else
                        {
                            strParaIntAux << sub;
                            strParaIntAux >> destiny;
                            sub.clear();
                            strParaIntAux.clear();
                        }
                        i++;
                    }
                }
                strParaIntAux << sub;
                strParaIntAux >> weight;
                sub.clear();
                strParaIntAux.clear();

                G->EDGES[indiceGraph].source = source;
                G->EDGES[indiceGraph].destiny = destiny;
                G->EDGES[indiceGraph].weight = weight;
                indiceGraph++;
            }
            iter++;
        }
        file.close();
    }

    bellF(G, 0);

    return 0;
}

Graph* createGraph(int VERT, int E)
{
    Graph* Graph = new Graph;
    Graph->VERT = VERT;
    Graph->E = E;
    Graph->EDGES = new EDGES[E];
    return Graph;
}

void bellF(struct Graph* Graph, int source)
{
    int VERT = Graph->VERT;
    int E = Graph->E;
    int dist[VERT];

    for (int i = 0; i < VERT; i++)
        dist[i] = INT_MAX;
    dist[source] = 0;

    for (int i = 1; i < VERT - 1; i++)
    {
        for (int j = 0; j < E; j++)
        {
            int u = Graph->EDGES[j].source;
            int VERT = Graph->EDGES[j].destiny;
            int weight = Graph->EDGES[j].weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[VERT])
                dist[VERT] = dist[u] + weight;
        }
    }

    for (int i = 0; i < E; i++)
    {
        int u = Graph->EDGES[i].source;
        int VERT = Graph->EDGES[i].destiny;
        int weight = Graph->EDGES[i].weight;
        if (dist[u] != INT_MAX && dist[u] + weight < dist[VERT])
        {
            cout << "negative" << endl;
            return;
        }
    }

    cout << "distancy - weight" << endl;
    for (int i = 0; i < VERT; i++)
        cout << i << " \t\t " << dist[i] << endl;

    return;
}