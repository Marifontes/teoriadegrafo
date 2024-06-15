#include <bits/stdc++.h>

using namespace std;

void leituraGrafo(vector<vector<double>> &, int);
void escritaGrafo(vector<vector<double>> &);
bool eureliano(vector<vector<double>> &);
bool isStronglyConnected(vector<vector<double>> &);
void dfs(const vector<vector<double>> &, int, vector<bool> &);
vector<vector<double>> getTranspose(const vector<vector<double>> &);
vector<int> encontrarCicloEuleriano(vector<vector<double>> &);

int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<double>> Grafo;
    Grafo.assign(n, vector<double>(n, 0));
    leituraGrafo(Grafo, m);
    escritaGrafo(Grafo);
    cout << "Total Vértices: " << n << endl;
    cout << "Total Arestas: " << m << endl;
   
    if (eureliano(Grafo))
    {
        vector<int> ciclo = encontrarCicloEuleriano(Grafo);
        cout << "Ciclo Euleriano (Algoritmo de Fleury): ";
        for (int v : ciclo)
            cout << v << " ";
        cout << endl;
    }
    else
        cout << "Não há um ciclo Euleriano neste grafo." << endl;

    return 0;
}

void leituraGrafo(vector<vector<double>> &G, int m)
{
    int a, b;
    double c;
    while (m--)
    {
        cin >> a >> b >> c;
        G[a][b] = c;
    }
}

void escritaGrafo(vector<vector<double>> &G)
{
    int n = G.size();
    cout << "Matriz de Adjacência:" << endl;
    cout << "   ";
    for (int u = 0; u < n; u++)
    {
        cout << u << " ";
    }
    cout << endl;
    for (int u = 0; u < n; u++)
    {
        cout << u << ": ";
        for (int v = 0; v < n; v++)
        {
            cout << G[u][v] << " ";
        }
        cout << endl;
    }
}

bool eureliano(vector<vector<double>> &G)
{
    if (!isStronglyConnected(G))
        return false;

    int n = G.size();
    vector<int> inDegree(n, 0), outDegree(n, 0);
    for (int u = 0; u < n; u++)
    {
        for (int v = 0; v < n; v++)
        {
            if (G[u][v] != 0)
            {
                outDegree[u]++;
                inDegree[v]++;
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        if (inDegree[i] != outDegree[i])
            return false;
    }

    return true;
}

bool isStronglyConnected(vector<vector<double>> &G)
{
    int n = G.size();
    vector<bool> visited(n, false);

    dfs(G, 0, visited);
    for (bool v : visited)
    {
        if (!v)
            return false;
    }

    vector<vector<double>> GT = getTranspose(G);
    fill(visited.begin(), visited.end(), false);
    dfs(GT, 0, visited);
    for (bool v : visited)
    {
        if (!v)
            return false;
    }

    return true;
}

void dfs(const vector<vector<double>> &G, int u, vector<bool> &visited)
{
    visited[u] = true;
    for (int v = 0; v < G.size(); v++)
    {
        if (G[u][v] != 0 && !visited[v])
            dfs(G, v, visited);
    }
}

vector<vector<double>> getTranspose(const vector<vector<double>> &G)
{
    int n = G.size();
    vector<vector<double>> GT(n, vector<double>(n, 0));
    for (int u = 0; u < n; u++)
    {
        for (int v = 0; v < n; v++)
        {
            if (G[u][v] != 0)
            {
                GT[v][u] = G[u][v];
            }
        }
    }
    return GT;
}

vector<int> encontrarCicloEuleriano(vector<vector<double>> &G)
{
    int u = 0;
    for (int i = 0; i < G.size(); i++)
    {
        for (int j = 0; j < G.size(); j++)
        {
            if (G[i][j] != 0)
            {
                u = i;
                break;
            }
        }
    }

    vector<int> ciclo;
    stack<int> currPath;
    currPath.push(u);

    while (!currPath.empty())
    {
        int currV = currPath.top();

        bool found = false;
        for (int nextV = 0; nextV < G.size(); nextV++)
        {
            if (G[currV][nextV] != 0)
            {
                currPath.push(nextV);
                G[currV][nextV] = 0; 
                found = true;
                break;
            }
        }

        if (!found)
        {
            ciclo.push_back(currV);
            currPath.pop();
        }
    }

    reverse(ciclo.begin(), ciclo.end());
    return ciclo;
}
