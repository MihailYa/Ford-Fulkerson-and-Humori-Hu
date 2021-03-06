#include "Ford.hpp"

namespace coursework
{

	int Ford(const char *file_name, graph *&gr, int &iterations, int in, int out)
	{
		FILE *f = nullptr;

		// Open file
		if ((f = fopen(file_name, "wt")) == nullptr)
		{
			T_exception e;
			e.code = 1;
			e.text = "�� ������� ������� ���� ";
			e.text += file_name;
			throw(e);
		}

		// Give memory for visited vertexes
		bool *visited = new bool[gr->n_vertexes];
		int cg_value = INF;	// Value by which stream can be changed
		int c_stream;		// Current stream
		int iter = 0;		// Current iteration
		char name_of_file[40];
		char buf[10];

		fprintf(f, "--------------Ford_Fulkerson_Begin--------------\n");

		if (gr->adj_m == nullptr)
			gr->adj_m = adj(gr);

		// Define Source and Sink
		if (in == -1)
			in = def_ss(0, gr);
		if (out == -1)
			out = def_ss(1, gr);

		if (in == -1 || out == -1)
		{
			delete[] visited;
			if (fclose(f))
			{
				T_exception e;
				e.code = 1;
				e.text = "�� ������� ������� ���� ";
				e.text += file_name;
				throw(e);
			}
			T_exception e;
			e.code = 3;
			e.text = "�� ������� ������ ��� ��� ������� �����.";
			e.solution = "������ ����, ��� ������ ������� �� ���.";
			throw(e);
		}
		else if (in >= gr->n_vertexes || out >= gr->n_vertexes)
		{
			delete[] visited;
			if (fclose(f))
			{
				T_exception e;
				e.code = 1;
				e.text = "�� ������� ������� ���� ";
				e.text += file_name;
				throw(e);
			}
			T_exception e;
			e.code = 3;
			e.text = "�� ��������� ������� ������� ��� ��� �����.";
			throw(e);
		}

		// Define current stream
		c_stream = def_stream(gr, out);
		fprintf(f, "\n Current stream of web = %d.\nSource vertex: %s.\nSink vertex: ", c_stream, g_n(gr->v_n[in], buf));
		fprintf(f, "%s.\n\n", g_n(gr->v_n[out], buf));

		// Create stack
		T_stack *head = nullptr;
		T_stack_dat dat;

		// Init
		for (int i = 0; i < gr->n_vertexes; i++)
			visited[i] = false;
		visited[in] = true;

		dat.v = in;
		dat.orient = true;
		add_e(head, dat);

		// Algorithm
		while (DFS_Ford(gr, in, out, cg_value, visited, head))
		{
			// If too many iterations
			if (iter > MAX_ITER)
			{
				delete[] visited;
				get_e(head);

				if (fclose(f))
				{
					T_exception e;
					e.code = 1;
					e.text = "�� ������� ������� ���� ";
					e.text += file_name;
					throw(e);
				}

				T_exception e;
				e.code = 2;
				e.text = "�������� �����-���������� ��������� ����������� ������� ��������.";
				e.solution = "������ ����, ��� ������ ������� �� ���.";
				throw(e);
			}

			// Change streams
			cg_stream(gr, cg_value, head, &f);
			fprintf(f, "\nValued by which streams changed: %d\n", cg_value);
			fprintf(f, "\nCurrent streams:\n");
			output(gr, &f);

			// Define current stream of web
			c_stream = def_stream(gr, out);
			fprintf(f, "\n Current stream of web = %d\n\n", c_stream);

			// Init
			dat.v = in;
			dat.orient = true;
			add_e(head, dat);
			for (int i = 0; i < gr->n_vertexes; i++)
				visited[i] = false;
			visited[in] = true;

			cg_value = INF;

			iter++;

			// Draw current graph
			strcpy(name_of_file, "Ford_Iteration_");
			itoa(iter, buf, 10);
			strcat(name_of_file, buf);
			strcat(name_of_file, ".png");
			graphviz(name_of_file, gr);
		}

		// Free memory from stack
		get_e(head);

		fprintf(f, "\nNew way can't be found.\n Maximum stream = %d.", c_stream);
		delete[] visited;

		fprintf(f, "\n---------------Ford_Fulkerson_End---------------\n");
		if (fclose(f))
		{
			T_exception e;
			e.code = 1;
			e.text = "�� ������� ������� ���� ";
			e.text += file_name;
			throw(e);
		}

		iterations = iter;
		return c_stream;
	}

	int Ford(FILE **f, graph *&gr, int in, int out)
	{
		// Give memory for visited vertexes
		bool *visited = new bool[gr->n_vertexes];
		int cg_value = INF;	// Value by which stream can be changed
		int c_stream;		// Current stream
		int iter = 0;		// Current iteration
		char buf[10];

		fprintf(*f, "\n--------------Ford Fulkerson Begin--------------\n");

		if (gr->adj_m == nullptr)
			gr->adj_m = adj(gr);

		// Define Source and Sink
		if (in == -1)
			in = def_ss(0, gr);
		if (out == -1)
			out = def_ss(1, gr);

		if (in == -1 || out == -1)
		{
			delete[] visited;
			int e = 3;
			throw(e);
		}

		// Define current stream of web
		c_stream = def_stream(gr, out);
		fprintf(*f, "\n Current stream of web = %d.\nSource vertex: %s.\nSink vertex: ", c_stream, g_n(gr->v_n[in], buf));
		fprintf(*f, "%s.\n\n", g_n(gr->v_n[out], buf));

		// Create stack
		T_stack *head = nullptr;
		T_stack_dat dat;

		// Init
		for (int i = 0; i < gr->n_vertexes; i++)
			visited[i] = false;
		visited[in] = true;

		dat.v = in;
		dat.orient = true;
		add_e(head, dat);

		// Algorithm
		while (DFS_Ford(gr, in, out, cg_value, visited, head))
		{
			if (iter > MAX_ITER)
			{
				// Free memory
				get_e(head);
				delete[] visited;

				int e = 5;
				throw(e);
			}

			// Change streams
			cg_stream(gr, cg_value, head, f);
			fprintf(*f, "\nValued by which streams changed: %d\n", cg_value);
			fprintf(*f, "\nCurrent streams:\n");
			output(gr, f);

			// Define current stream
			c_stream = def_stream(gr, out);
			fprintf(*f, "\n Current stream of web = %d\n\n", c_stream);

			// Init
			dat.v = in;
			dat.orient = true;
			add_e(head, dat);
			for (int i = 0; i < gr->n_vertexes; i++)
				visited[i] = false;
			visited[in] = true;
			iter++;
			cg_value = INF;
		}

		// Free memory from stack
		get_e(head);

		fprintf(*f, "\nNew way can't be found.\n Maximum stream = %d.", c_stream);
		delete[] visited;

		fprintf(*f, "\n---------------Ford Fulkerson End---------------\n");

		return c_stream;
	}

	bool DFS_Ford(graph *gr, int c_v, int out, int &max, bool *visit, T_stack *&head)
	{
		if (c_v == out)
			return true;

		int temp = max;
		int edge_n; // Current edge
		T_stack_dat dat; // Vertex
		for (int i = 0; i < gr->n_vertexes; i++)
		{
			edge_n = g_e(c_v, i, gr);

			if (!visit[i] && gr->adj_m[c_v][i] && (gr->edges[edge_n].stream < gr->edges[edge_n].pass_abl))
			{
				// Fix orientation of undirected graph
				if (!gr->type && !gr->edges[edge_n].orient)
				{
					gr->edges[edge_n].orient = true;
					gr->adj_m[i][c_v] = 0;
				}

				// Add vertex to stack
				dat.v = i;
				dat.orient = true;
				add_e(head, dat);
				visit[i] = true;

				// Change max if needed
				if (gr->edges[edge_n].pass_abl - gr->edges[edge_n].stream < max)
					max = gr->edges[edge_n].pass_abl - gr->edges[edge_n].stream;

				// Recurs
				if (DFS_Ford(gr, i, out, max, visit, head))
					return true;
				else
				{
					if (!gr->type && gr->edges[edge_n].stream == 0)
					{
						gr->edges[edge_n].orient = false;
						gr->adj_m[i][c_v] = true;
					}
					max = temp;
					get_e(head);
					visit[i] = false;
				}
			}
			else if (!visit[i] && (gr->adj_m[i][c_v] && gr->edges[edge_n].stream != 0))
			{
				// Add vertex to stack
				dat.v = i;
				dat.orient = false;
				add_e(head, dat);
				visit[i] = true;

				// Change max if needed
				if (gr->edges[edge_n].stream < max)
					max = gr->edges[edge_n].stream;

				// Recurs
				if (DFS_Ford(gr, i, out, max, visit, head))
					return true;
				else
				{
					max = temp;
					get_e(head);
					visit[i] = false;
				}
			}
		}

		return false;
	}

	int def_ss(bool mode, graph *gr)
	{
		bool check;
		for (int i = 0; i < gr->n_vertexes; i++)
		{
			check = 1;
			for (int j = 0; j < gr->n_vertexes; j++)
			{
				if ((!mode && gr->adj_m[j][i]) || (mode && gr->adj_m[i][j]))
					check = 0;
			}

			// If we found sink/source
			if (check) return i;
		}

		return -1;
	}

	int def_stream(graph* gr, int s_v)
	{
		int sum = 0;
		for (int i = 0; i < gr->n_vertexes; i++)
		{
			if (gr->adj_m[i][s_v])
				sum += gr->edges[g_e(i, s_v, gr)].stream;
		}
		return sum;
	}

	void cg_stream(graph *&gr, int value, T_stack *&head, FILE **f)
	{
		T_stack_dat out;				// Out vertex of edge
		T_stack_dat in = get_e(head);	// In vertex of edge
		char buf[10];					// Char buffer

		fprintf(*f, "\nFound way:\n");
		while (head != nullptr)
		{
			out = in;

			// Get element from stack
			in = get_e(head);

			// If it is not oriented way
			if (!out.orient)
			{
				fprintf(*f, "%s -> ", g_n(gr->v_n[out.v], buf));
				gr->edges[g_e(out.v, in.v, gr)].stream -= value;
			}
			else
			{
				fprintf(*f, "%s <- ", g_n(gr->v_n[out.v], buf));
				gr->edges[g_e(out.v, in.v, gr)].stream += value;
			}
		}

		fprintf(*f, "%s\n", g_n(gr->v_n[in.v], buf));
	}

}
