#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 5

// A structure to represent an adjacency list node
struct adj_list_node
{
    int dest;
    int weight;
    struct adj_list_node *next;
};

// A structure to represent an adjacency list
struct adj_list
{
    struct adj_list_node *head;
};

// A structure to represent a graph
struct Graph
{
    int V;
    int *visited;
    struct adj_list *array;
};

//****************START OF METHODS RELATED TO GRAPH******************
//*******************************************************************
//*******************************************************************

// Function to create a new adjacency list node
struct adj_list_node *new_adj_list_node(int dest, int weight)
{
    struct adj_list_node *newNode = (struct adj_list_node *)malloc(sizeof(struct adj_list_node));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

// Function to creates a graph with V vertices
struct Graph *create_graph(int V)
{
    struct Graph *graph = (struct Graph *)malloc(sizeof(struct Graph));
    graph->V = V;

    graph->array = (struct adj_list *)malloc(V * sizeof(struct adj_list));

    int i;
    for (i = 0; i < V; ++i)
        graph->array[i].head = NULL;

    return graph;
}

// Fuction to add edges to graph
void add_edge(struct Graph *graph, struct Graph *gr, int src, int dest, int weight)
{

    struct adj_list_node *newNode = new_adj_list_node(dest, weight);

    newNode->next = graph->array[src].head;

    graph->array[src].head = newNode;

    get_transpose(gr, src, dest, weight);
}

// Function to print the graph
void print_graph(struct Graph *graph1)
{
    int v;
    for (v = 0; v < graph1->V; ++v)
    {
        struct adj_list_node *temp = graph1->array[v].head;
        while (temp)
        {
            printf("(%d -> %d(%d))\t", v, temp->dest, temp->weight);
            temp = temp->next;
        }
    }
}


// A recursive function to print DFS starting from v
void dfs_recursive(struct Graph *gr, int v, bool visited[])
{

    visited[v] = true;
    //printf("%d ", v);
    struct adj_list_node *temp = gr->array[v].head;

    while (temp)
    {
        if (!visited[temp->dest])
        {
            dfs_recursive(gr, temp->dest, visited);
        }
        temp = temp->next;
    }
}

// Fuction to add edges to transpose graph
void get_transpose(struct Graph *gr, int src, int dest, int weight)
{
    struct adj_list_node *newNode = new_adj_list_node(src, weight);
    newNode->next = gr->array[dest].head;
    gr->array[dest].head = newNode;
}

//*****************END OF METHODS RELATED TO GRAPH*******************
//*******************************************************************
//*******************************************************************

//**************START OF STRONGLY CONNECTED COMPONENTS CHECK***************
//*************************************************************************
//*************************************************************************

int strongly_connectivity(struct Graph *graph, struct Graph *gr, int v)
{

    bool visited[v];
    for (int i = 0; i < v; i++)
        visited[i] = false;

    // Dfs recursive traversal
    dfs_recursive(graph,0, visited);

    // If dfs_recursive didn't visit all vertices
    // then return
    for (int i = 0; i < v; i++)
    {
        if (visited[i] == false)
            return 0;
    }

    //  Create a reversed graph

    //  Again mark all the vertices as not visited
    for (int i = 0; i < v; i++)
        visited[i] = false;
    ;

    dfs_recursive(gr, 0, visited);

    // If all vertices are not visited in second transpose graph
    // then return false
    for (int i = 0; i < v; i++)
        if (visited[i] == false)
            return 0;

    return 1;
}

//****************END OF STRONGLY CONNECTED COMPONENTS CHECK***************
//*************************************************************************
//*************************************************************************

int main()
{

    struct Graph *graph1 = create_graph(MAX_SIZE);
    struct Graph *gr1 = create_graph(MAX_SIZE);

    add_edge(graph1, gr1, 1, 0, 2);
    add_edge(graph1, gr1, 0, 2, 2);
    add_edge(graph1, gr1, 2, 1, 2);
    add_edge(graph1, gr1, 0, 3, 2);
    add_edge(graph1, gr1, 3, 4, 2);

    int t1 = strongly_connectivity(graph1, gr1, MAX_SIZE);
    printf("Graph 1:\n");
    if(t1 == 0){
        printf("Graph is not Strongly connected\n");
    }else if(t1 == 1){
        printf("Graph is Strongly connected\n");
    }

    struct Graph *graph2 = create_graph(MAX_SIZE-2);
    struct Graph *gr2 = create_graph(MAX_SIZE);

    add_edge(graph2, gr2, 1, 0, 2);
    add_edge(graph2, gr2, 0, 2, 2);
    add_edge(graph2, gr2, 2, 1, 2);

    int t2 = strongly_connectivity(graph2, gr2, MAX_SIZE-2);
    printf("Graph 2:\n");
    if(t2 == 0){
        printf("Graph is not Strongly connected\n");
    }else if(t2 == 1){
        printf("Graph is Strongly connected\n");
    }


    return 0;
}
