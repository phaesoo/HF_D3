
#include <vector>
#include <set>
#include <algorithm>
#include <stack>
#include <string>
#include <iterator>
#include <assert.h>
#include <iostream>

using namespace std;

enum Vertex // integer ���°� ���ɿ� ������
{
    A = 0,
    B,
    C,
    D,
    E,
    F,
    G,
};

class Graph
{
public:
    bool AddVertex(Vertex vt)
    {
        auto itr = find(_vertexes.begin(), _vertexes.end(), vt);
        if (itr != _vertexes.end())
        { 
            // �ߺ�
assert(0);
return false;
        }
        _vertexes.push_back(vt);
        return true;
    }

    bool AddEdge(const pair<Vertex, Vertex>&& edge)
    {
        if (edge.first > edge.second)
        {
            // �������� key��
            assert(0);
            return false;
        }

        auto itr = find(_edges.begin(), _edges.end(), edge);
        if (itr != _edges.end())
        {
            // �ߺ�
            assert(0);
            return false;
        }

        _edges.push_back(edge);
        return true;
    }

    // ���� �ڵ����������� set���
    void FindNeighbor(Vertex current, set<Vertex>& neighbor)
    {
        neighbor.clear();

        for (auto itr = _edges.begin(); itr != _edges.end(); ++itr)
        {
            if (itr->first == current)
            {
                neighbor.insert(itr->second);
            }
            else if (itr->second == current)
            {
                neighbor.insert(itr->first);
            }
        }
    }

    vector<Vertex> GetVertexes() { return _vertexes; }

private:
    vector<Vertex> _vertexes;
    vector<pair<Vertex, Vertex>> _edges;
};

char GetSymbol(Vertex vt)
{
    switch (vt)
    {
    case Vertex::A: return 'A';
    case Vertex::B: return 'B';
    case Vertex::C: return 'C';
    case Vertex::D: return 'D';
    case Vertex::E: return 'E';
    case Vertex::F: return 'F';
    case Vertex::G: return 'G';
    }

    assert(0);
    return '-';
}

bool IsCyclicGraph(const vector<Vertex>& visited)
{
    set<Vertex> duplicateChecker;

    for (auto itr = visited.begin(); itr != visited.end(); ++itr)
    {
        if (duplicateChecker.insert(*itr).second == false)
        {
            return true;
        }
    }
    return false;
}

int main()
{
    Graph graph;
    graph.AddVertex(Vertex::A);
    graph.AddVertex(Vertex::B);
    graph.AddVertex(Vertex::C);
    graph.AddVertex(Vertex::D);
    graph.AddVertex(Vertex::E);
    graph.AddVertex(Vertex::F);
    graph.AddVertex(Vertex::G);

    graph.AddEdge(make_pair(Vertex::A, Vertex::B));
    graph.AddEdge(make_pair(Vertex::A, Vertex::C));
    graph.AddEdge(make_pair(Vertex::A, Vertex::F));
    graph.AddEdge(make_pair(Vertex::B, Vertex::C));
    graph.AddEdge(make_pair(Vertex::B, Vertex::D));
    graph.AddEdge(make_pair(Vertex::C, Vertex::E));

    stack<Vertex> stk;
    stk.push(Vertex::A);

    vector<Vertex> visited; // �̹� ������ vertex

    while (!stk.empty())
    {
        Vertex current = stk.top(); // current�� �־���
        stk.pop(); // stack���� ��� ����

        set<Vertex> neighbor;
        graph.FindNeighbor(current, neighbor);

        for (auto itr = neighbor.begin(); itr != neighbor.end(); ++itr)
        {
            auto itrfind = find(visited.begin(), visited.end(), *itr);
            if (itrfind == visited.end())
            {
                // �湮�ߴ����� �ƴѰ�� stack�� �߰�
                stk.push(*itr);
            }
        }

        // ��� �߰�
        visited.push_back(current);
    }

    cout << "Visited Path : ";

    for (auto itr = visited.begin(); itr != visited.end(); ++itr)
    {
        if (itr != visited.begin())
        { 
            cout << " -> ";
        }
        cout << GetSymbol(*itr);
    }
    cout << endl;

    vector<Vertex> vertexed = graph.GetVertexes();
    sort(vertexed.begin(), vertexed.end());
    sort(visited.begin(), visited.end());

    vector<Vertex> dest;
    set_difference(vertexed.begin(), vertexed.end(), visited.begin(), visited.end(), inserter(dest, dest.begin()));

    cout << "Remain Vertexes: ";
    for (auto itr = dest.begin(); itr != dest.end(); ++itr)
    {
        if (itr != dest.begin())
        {
            cout << ", ";

        }
        cout << GetSymbol(*itr);
    }
    cout << endl;

    cout << "Check graph has cycle : ";
    if (IsCyclicGraph(visited))
    {
        cout << "yes";
    }
    else
    {
        cout << "no";
    }
    cout << endl;

    return 0;
}