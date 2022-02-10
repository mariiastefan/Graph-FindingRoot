#include "graf.h"
#include <QTextStream>
#include <QFile>
#include <iostream>
#include <vector>
std::vector<Arc> Graf::GetArce()
{
	return arce;
}

std::vector<Node> Graf::GetNoduri()
{
	return noduri;
}


void Graf::AddNod(Node n)
{
	n.setNumber(noduri.size());
	noduri.push_back(n);
}

void Graf::AddArc(Arc n)
{
	for (auto index : arce)
	{
		if (index.getFirstPoint().getNumber() == n.getFirstPoint().getNumber() && index.getSecondPoint().getNumber() == n.getSecondPoint().getNumber())
		{
			return;
		}
	}
	arce.push_back(n);
}

Node Graf::GetLastNode()
{
	return noduri[noduri.size() - 1];
}
void Graf::DFS(int x, std::vector<int> &visited)
{
	visited[x] = 1;
	for (auto &y : GetArce())
	{
		if (y.getFirstPoint().getNumber() == x)
		{
			if (!visited[y.getSecondPoint().getNumber()])
				DFS(y.getSecondPoint().getNumber(), visited);
		}
	}
}

void Graf::gasireaRadacinii()
{
	std::vector<Node> noduri;
	noduri = GetNoduri();
	/*if (noduri.size() == 1)
		std::cout << noduri[0].getNumber();*/
	std::vector<int>visited;
	int v=-1;
	for (auto& nod : noduri)
	{
		visited.push_back(0);
	}
	for (auto& nod : noduri)
	{
		if (!visited[nod.getNumber()])
		{
			DFS(nod.getNumber(), visited);
			v = nod.getNumber();
		}
	}
	visited.clear();
	for (auto& nod : noduri)
	{
		visited.push_back(0);
	}
	
	DFS(v, visited);

	for (auto& nod : noduri)
	{
		if (!visited[nod.getNumber()])
		{
			v = -1;
		}
	}
		std::cout << v;
}


int Graf::getNumberofNodes()
{
	return noduri.size();
}

void Graf::GenerareListaAdiacenta()
{
	listaAdiacenta = GetArce();

}
