#include <bits/stdc++.h>

using namespace std;

void leituraGrafo(vector<vector<pair<int, int>>> &, int);
void escritaGrafo(vector<vector<pair<int, int>>> &);
bool eureliano(vector<vector<pair<int, int>>> &);
bool isStronglyConnected(vector<vector<pair<int, int>>> &);
void dfs(const vector<vector<pair<int, int>>> &, int, vector<bool> &);
vector<vector<pair<int, int>>> getTranspose(const vector<vector<pair<int, int>>> &);
vector<int> encontrarCicloEuleriano(vector<vector<pair<int, int>>> &);
bool isValidNextEdge(vector<vector<pair<int, int>>> &, int, int);

int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> Grafo;
    Grafo.assign(n, vector<pair<int, int>>());
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

void leituraGrafo(vector<vector<pair<int, int>>> &G, int m)
{
    int a, b;
    double c;
    while (m--)
    {
        cin >> a >> b >> c;
        G[a].push_back(make_pair(b, c));
    }
}

void escritaGrafo(vector<vector<pair<int, int>>> &G)
{
    int n = G.size();
    cout << "Lista de Adjacência:" << endl;
    for (int u = 0; u < n; u++)
    {
        cout << u << ": ";
        for (auto v : G[u])
        {
            cout << "[(" << u << "," << v.first << ") w: " << v.second << "] ";
        }
        cout << endl;
    }
}

bool eureliano(vector<vector<pair<int, int>>> &G)
{
    if (!isStronglyConnected(G))
        return false;

    int n = G.size();
    vector<int> inDegree(n, 0), outDegree(n, 0);
    for (int u = 0; u < n; u++)
    {
        for (auto v : G[u])
        {
            outDegree[u]++;
            inDegree[v.first]++;
        }
    }
    for (int i = 0; i < n; i++)
    {
        if (inDegree[i] != outDegree[i])
            return false;
    }

    return true;
}

bool isStronglyConnected(vector<vector<pair<int, int>>> &G)
{
    int n = G.size();
    vector<bool> visited(n, false);

    dfs(G, 0, visited);
    for (bool v : visited)
    {
        if (!v)
            return false;
    }

    vector<vector<pair<int, int>>> GT = getTranspose(G);
    fill(visited.begin(), visited.end(), false);
    dfs(GT, 0, visited);
    for (bool v : visited)
    {
        if (!v)
            return false;
    }

    return true;
}

void dfs(const vector<vector<pair<int, int>>> &G, int u, vector<bool> &visited)
{
    visited[u] = true;
    for (auto v : G[u])
    {
        if (!visited[v.first])
            dfs(G, v.first, visited);
    }
}

vector<vector<pair<int, int>>> getTranspose(const vector<vector<pair<int, int>>> &G)
{
    int n = G.size();
    vector<vector<pair<int, int>>> GT(n);
    for (int u = 0; u < n; u++)
    {
        for (auto v : G[u])
        {
            GT[v.first].push_back(make_pair(u, v.second));
        }
    }
    return GT;
}

vector<int> encontrarCicloEuleriano(vector<vector<pair<int, int>>> &G)
{
    int u = 0;
    for (int i = 0; i < G.size(); i++)
    {
        if (G[i].size() > 0)
        {
            u = i;
            break;
        }
    }

    vector<int> ciclo;
    stack<int> currPath;
    currPath.push(u);

    while (!currPath.empty())
    {
        int currV = currPath.top();

        if (!G[currV].empty())
        {
            int nextV = G[currV].back().first;
            currPath.push(nextV);
            G[currV].pop_back();
        }
        else
        {
            ciclo.push_back(currV);
            currPath.pop();
        }
    }

    reverse(ciclo.begin(), ciclo.end());
    return ciclo;
}
