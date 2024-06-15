#include <bits/stdc++.h>
using namespace std;

class Grafo {
private:
    int V, A;
    vector<vector<int>> adj;

public:
    Grafo(int vertices, int arestas) {
        V = vertices;
        A = arestas;
        adj.assign(V, vector<int>(V, 0));
    }

    void adicionaAresta(int u, int v) {
        adj[u][v] = 1;
        adj[v][u] = 1;
    }

    void mostraGrafo() {
        cout << "Matriz de Adjacência:" << endl;
        cout << "   ";
        for (int u = 0; u < V; u++) {
            cout << u << " ";
        }
        cout << endl;
        for (int u = 0; u < V; u++) {
            cout << u << ": ";
            for (int v = 0; v < V; v++) {
                cout << adj[u][v] << " ";
            }
            cout << endl;
        }
        cout << "Total Vértices: " << V << endl;
        cout << "Total Arestas: " << A << endl;
    }

    bool grafoEureliano() {
        for (int u = 0; u < V; u++) {
            int grau = 0;
            for (int v = 0; v < V; v++) {
                if (adj[u][v] == 1) {
                    grau++;
                }
            }
            if (grau % 2 != 0) {
                return false;
            }
        }

        vector<bool> visitado(V, false);
        dfs(0, visitado);

        for (int u = 0; u < V; u++) {
            if (!visitado[u]) {
                int grau = 0;
                for (int v = 0; v < V; v++) {
                    if (adj[u][v] == 1) {
                        grau++;
                    }
                }
                if (grau > 0) {
                    return false;
                }
            }
        }

        return true;
    }

    void caminhoEulerianoFleury() {
        if (!grafoEureliano()) {
            cout << "Não há um ciclo Euleriano neste grafo.\n";
            return;
        }

        int inicio = 0;
        vector<int> path;
        getEulerPathFleury(inicio, path);

        cout << "Ciclo Euleriano (Algoritmo de Fleury): ";
        for (int v : path) {
            cout << v << " ";
        }
        cout << endl;
    }

    void getEulerPathFleury(int u, vector<int> &path) {
        for (int v = 0; v < V; v++) {
            if (adj[u][v] == 1) {
                if (isValidNextEdge(u, v)) {
                    removeAresta(u, v);
                    getEulerPathFleury(v, path);
                }
            }
        }
        path.push_back(u);
    }

    bool isValidNextEdge(int u, int v) {
        int grau = 0;
        for (int i = 0; i < V; i++) {
            if (adj[u][i] == 1) {
                grau++;
            }
        }

        if (grau == 1) {
            return true;
        }

        vector<bool> visitado(V, false);
        int count1 = dfsCount(u, visitado);

        removeAresta(u, v);
        visitado.assign(V, false);
        int count2 = dfsCount(u, visitado);

        adicionaAresta(u, v);

        return (count1 <= count2);
    }

    int dfsCount(int u, vector<bool> &visitado) {
        visitado[u] = true;
        int count = 1;
        for (int v = 0; v < V; v++) {
            if (adj[u][v] == 1 && !visitado[v]) {
                count += dfsCount(v, visitado);
            }
        }
        return count;
    }

    void removeAresta(int u, int v) {
        adj[u][v] = 0;
        adj[v][u] = 0;
    }

    void dfs(int u, vector<bool> &visitado) {
        visitado[u] = true;
        for (int v = 0; v < V; v++) {
            if (adj[u][v] == 1 && !visitado[v]) {
                dfs(v, visitado);
            }
        }
    }
};

int main() {
    int n, m;
    cin >> n >> m;

    Grafo grafo(n, m);

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        grafo.adicionaAresta(a, b);
    }

    grafo.mostraGrafo();

    grafo.caminhoEulerianoFleury();

    return 0;
}
