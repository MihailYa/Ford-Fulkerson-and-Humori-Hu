#include "output.hpp"

using namespace std;

namespace coursework
{

	void output(graph *gr, FILE **f)
	{
		fprintf(*f, " %13s | %9s | %s\n", "Edges", "Pass able", "Current stream");
		char tmp[20];
		for (int i = 0; i < gr->n_edges; i++)
		{
			fprintf(*f, "%5s", g_n(gr->v_n[gr->edges[i].out], tmp));
			fprintf(*f, " -> %-5s | % 9d | %d\n", g_n(gr->v_n[gr->edges[i].in], tmp), gr->edges[i].pass_abl, gr->edges[i].stream);
		}
	}

	void output_streams(graph *gr, FILE **f)
	{
		fprintf(*f, "   ");
		for (int i = 0; i <= gr->n_vertexes; i++)
		{
			if (i != 0)
				fprintf(*f, "%4d", gr->v_n[i - 1].v);
			for (int j = 0; j <= gr->n_vertexes; j++)
			{
				if (i == 0)
				{
					if (j == 0)
						fprintf(*f, " ");
					else
						fprintf(*f, "%4d", gr->v_n[j - 1].v);
				}
				else if (j != 0)
				{
					if(gr->streams[i - 1][j - 1]!=INF)
						fprintf(*f, "%4d", gr->streams[i - 1][j - 1]);
					else
						fprintf(*f, "%4s", "INF");
				}
			}
			fprintf(*f, "\n");
		}
	}

	string output_graphviz(graph *gr, bool type)
	{
		std::string res;
		char tmp[10];
		if (type)
		{
			// Create Gomory result graph
			res = "graph G {\n";
			for (int i = 0; i < gr->n_edges; i++)
			{
				res += "T";
				res += to_string(gr->v_n[gr->edges[i].in].v);
				res += " -- ";
				res += "T";
				res += to_string(gr->v_n[gr->edges[i].out].v);
				res += " [label=\" ";
				res += to_string(gr->edges[i].stream);
				res += "/";
				res += to_string(gr->edges[i].stream);
				res += " \"];\n";
			}
		}
		else if (gr->type)
		{
			res = "digraph G {\n";
			for (int i = 0; i < gr->n_edges; i++)
			{
				res += g_n(gr->v_n[gr->edges[i].in], tmp);
				res += " -> ";
				res+= g_n(gr->v_n[gr->edges[i].out], tmp);

				res += " [label=\" ";
				res += to_string(gr->edges[i].stream);
				res += "/";
				res += to_string(gr->edges[i].pass_abl);
				res += " \"];\n";
			}
		}
		else
		{
			res = "graph G {\n";
			for (int i = 0; i < gr->n_edges; i++)
			{
				res += g_n(gr->v_n[gr->edges[i].in], tmp);
				res += " -- ";
				res += g_n(gr->v_n[gr->edges[i].out], tmp);

				res += " [label=\" ";
				res += to_string(gr->edges[i].stream);
				res += "/";
				res += to_string(gr->edges[i].pass_abl);
				res += " \"];\n";
			}
		}

		res += "}";

		return res;
	}

	void graphviz(char *file_name, graph *gr, bool type)
	{
		std::string inp;

		// Create graph
		inp = output_graphviz(gr, type);

		GVC_t *gvc;
		gvc = gvContext();
		Agraph_t *g;
		g = agmemread(inp.c_str());
		
		gvLayout(gvc, g, "dot");
		gvRenderFilename(gvc, g, "png", file_name);
		gvFreeLayout(gvc, g);

		agclose(g);

		gvFreeContext(gvc);
	}

}
