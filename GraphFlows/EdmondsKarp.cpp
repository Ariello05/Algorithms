#include "EdmondsKarp.h"
#include <queue>
#include <limits>

EdmondsKarp::EdmondsKarp(Graph * hcc)
{
	sr = 0;
	this->hc = hcc;
	wasRun = false;
}

EdmondsKarp::~EdmondsKarp()
{
}

int EdmondsKarp::run()
{
	sr = 0;
	int fmax = 0;
	int last = hc->getAmount();
	int t = last - 1;
	int s = 0;
	bool test = false;

	List** routes = hc->getNeighbourList();

	// We create flow network
	
	if (!wasRun) {
		wasRun = true;
		
		for (int u = 0; u < last; u++)
		{
			List* current = routes[u];
			while (current) {
				test = false;

				List* subcurrent = routes[current->val.v];
				while (subcurrent) {
					if (subcurrent->val.v == u) {
						test = true; break;
					}
					subcurrent = subcurrent->next;
				}
				if (test) {
					current = current->next;
					continue;
				}

				Route r(u, 0);
				List* el = new List(r);
				el->next = routes[current->val.v];
				routes[current->val.v] = el;

				current = current->next;
			}
		}
		
	}
	else {
		hc->reset();
		hc->shuffle();
	}
	
	std::queue<int> queue;
	int* prev = new int[last];//previous nodes
	int* CFP = new int[last];//capacity - flow
	int u,v,i;//helpers
	int cp;
	List* z;

	while (true) {
		for (i = 0; i < last; i++) {
			prev[i] = -1;
		}

		CFP[s] = INT_MAX;

		while (!queue.empty()) {
			queue.pop();
		}

		queue.push(s);                   

		// Search for route in flow network from source s to sink t [BFS]
		while (!queue.empty())
		{
			test = false;        
			u = queue.front();
			queue.pop();  

			for (z = routes[u]; z; z = z->next)
			{
				cp = z->val.capacity - z->val.flow;

				if (cp && (prev[z->val.v] == -1))
				{
					prev[z->val.v] = u;

					CFP[z->val.v] = cp < CFP[u] ? cp : CFP[u];

					if (z->val.v == t)// if this node reaches sink break
					{
						test = true;     
						sr++;
						break;            
					}
					else queue.push(z->val.v);// else push next node
				}
			}
			if (test) break;//found route
			//else try again with BFS

		}

		if (!test) break;//If we couldn't find route end

		fmax += CFP[t];

		//Update flow
		for (v = t; v != s; v = u)
		{
			u = prev[v];

			for (z = routes[u]; z; z = z->next) {
				if (z->val.v == v)
				{
					z->val.flow += CFP[t];
					break;
				}
			}

			for (z = routes[v]; z; z = z->next) {
				if (z->val.v == u)
				{
					z->val.flow -= CFP[t];
					break;
				}
			}
		}
	}

	delete[] prev;
	delete[] CFP;
	return fmax;
}

int EdmondsKarp::getLastRoutes()
{
	return sr;
}
