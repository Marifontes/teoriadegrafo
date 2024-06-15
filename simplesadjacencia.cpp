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
        adj.assign(V, vector<int>());
    }

    void adicionaAresta(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void mostraGrafo() {
        cout << "Lista de Adjacência:" << endl;
        for (int u = 0; u < V; u++) {
            cout << u << ": ";
            for (auto v : adj[u]) {
                cout << v << " ";
            }
            cout << endl;
        }
        cout << "Total Vértices: " << V << endl;
        cout << "Total Arestas: " << A << endl;
    }

    bool grafoEureliano() {
        for (int u = 0; u < V; u++) {
            if (adj[u].size() % 2 != 0) {
                return false;
            }
        }

        vector<bool> visitado(V, false);
        dfs(0, visitado);

        for (int u = 0; u < V; u++) {
            if (!visitado[u] && adj[u].size() > 0) {
                return false;
            }
        }

        return true;
    }

    void dfs(int u, vector<bool> &visitado) {
        visitado[u] = true;
        for (int v : adj[u]) {
            if (!visitado[v]) {
                dfs(v, visitado);
            }
        }
    }

    void getEulerCycleFleury(vector<int> &cycle) {
        int inicio = 0;
        for (int i = 0; i < V; i++) {
            if (adj[i].size() > 0) {
                inicio = i;
                break;
            }
        }

        getEulerCycleFleuryUtil(inicio, cycle);

        cout << "Ciclo Euleriano (Algoritmo de Fleury): ";
        for (int v : cycle) {
            cout << v << " ";
        }
        cout << endl;

        for (int u = 0; u < V; u++) {
            if (!adj[u].empty()) {
                if (adj[u].size() == 1) {
                    cout << "Excluiu vértice isolado: " << u << endl;
                    adj[u].clear();
                }
            }
        }
    }

    void getEulerCycleFleuryUtil(int u, vector<int> &cycle) {
        stack<int> pilha;
        pilha.push(u);

        while (!pilha.empty()) {
            int atual = pilha.top();
            bool encontrou = false;

            for (int v : adj[atual]) {
                if (isValidNextEdge(atual, v)) {
                    removeAresta(atual, v);
                    pilha.push(v);
                    encontrou = true;
                    break;
                }
            }

            if (!encontrou) {
                cycle.push_back(atual);
                pilha.pop();
            }
        }
    }

    bool isValidNextEdge(int u, int v) {
        if (adj[u].size() == 1) {
            return true;
        }

        vector<bool> visitado(V, false);
        int count1 = dfsCount(u, visitado);

        removeAresta(u, v);
        visitado.assign(V, false);
        int count2 = dfsCount(u, visitado);

        adicionaAresta(u, v);

        return (count1 > count2) ? false : true;
    }

    int dfsCount(int u, vector<bool> &visitado) {
        visitado[u] = true;
        int count = 1;
        for (int v : adj[u]) {
            if (!visitado[v]) {
                count += dfsCount(v, visitado);
            }
        }
        return count;
    }

    void removeAresta(int u, int v) {
        auto it = find(adj[u].begin(), adj[u].end(), v);
        adj[u].erase(it);
        it = find(adj[v].begin(), adj[v].end(), u);
        adj[v].erase(it);
    }
};

int main() {
    int n, m;
    cin >> n >> m;

    Grafo grafo(n, m);

    while (m--) {
        int a, b;
        cin >> a >> b;
        grafo.adicionaAresta(a, b);
    }

    grafo.mostraGrafo();

    if (grafo.grafoEureliano()) {
        vector<int> cicloEuleriano;
        grafo.getEulerCycleFleury(cicloEuleriano);
    } else {
        cout << "Não há ciclo Euleriano neste grafo." << endl;
    }

    return 0;
}
