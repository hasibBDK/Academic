#include <stdio.h>

int pc = 0; // Path count

struct Node
{
    int nodeid;
    int adjcount;
    int adjs[10];
    int costs[10];
};

// Function to add a new node to the graph
int addNode(struct Node *p, int nid, int count)
{
    int i = 0, ncount = count;
    for (i = 0; i < count; i++)
    {
        if (p[i].nodeid == nid)
        {
            break; // Node already exists, no need to add again
        }
    }
    if (i == count)
    {
        p[i].nodeid = nid;       // Set the node ID
        p[i].adjcount = 0;       // Initialize adjacent count to zero
        ncount++;                // Increment node count
    }
    return ncount;  // Return the updated count of nodes
}

// Function to add an adjacent node to an existing node
void addAdjacent(struct Node *p, int nid1, int nid2, int cost, int count)
{
    int i = 0, index;
    for (i = 0; i < count; i++)
    {
        if (p[i].nodeid == nid1)
        {
            int c = p[i].adjcount;           // Get the current adjacent count
            p[i].adjs[c] = nid2;             // Add the adjacent node ID
            p[i].costs[c] = cost;            // Add the cost associated with the adjacent node
            p[i].adjcount = c + 1;           // Increment the adjacent count
            break;
        }
    }
}

// Function to check if a node is already present in the list
int added(int *list, int lcount, int nid)
{
    int i = 0;
    for (i = 0; i < lcount; i++)
    {
        if (list[i] == nid)
        {
            return 1; // Node already present in the list
        }
    }
    return 0; // Node not present in the list
}

// Function to find paths between two nodes in the graph
void findpath(struct Node *p, int count, int start, int end, int *list, int *clist, int lcount, int forbiddenNode)
{
    int index = 0, i = 0;

    // Check if the end node is reached
    if (list[lcount - 1] == end)
    {
        pc++;
        int tcost = 0;
        printf("\nPath: ");
        for (i = 0; i < lcount; i++)
        {
            printf("%d ", list[i]);  // Print the nodes in the path
            tcost += clist[i];       // Calculate the total cost of the path
        }
        printf("Cost = %d", tcost);  // Print the total cost of the path
        return;
    }

    for (i = 0; i < count; i++)
    {
        if (p[i].nodeid == start)
        {
            index = i;
            break;
        }
    }

    for (i = 0; i < p[index].adjcount; i++)
    {
        int a = added(list, lcount, p[index].adjs[i]);
        if (p[index].adjs[i] == forbiddenNode)
            continue;
        if (a == 0)
        {
            list[lcount] = p[index].adjs[i];   // Add the adjacent node to the path
            clist[lcount] = p[index].costs[i]; // Add the cost associated with the adjacent node
            lcount++;                          // Increment the length of the path

            // Recursively find paths from the adjacent node
            findpath(p, count, p[index].adjs[i], end, list, clist, lcount, forbiddenNode);
            lcount--;                          // Backtrack: Remove the added node from the path
        }
    }
}

int main()
{
    struct Node nodes[50];
    int nodecount = 0;
    int n1 = 0, n2 = 0, c = 0;

    // Read node connections and costs until termination signal is received
    while (1)
    {
        printf("Enter n1, n2, and cost (-9 to terminate): ");
        scanf("%d %d %d", &n1, &n2, &c);
        if (n1 == -9 || n2 == -9 || c == -9)
        {
            break; // Terminate input loop
        }
        // Add nodes and their connections to the graph
        nodecount = addNode(&nodes[0], n1, nodecount);
        nodecount = addNode(&nodes[0], n2, nodecount);
        addAdjacent(&nodes[0], n1, n2, c, nodecount);
        addAdjacent(&nodes[0], n2, n1, c, nodecount); // Assuming undirected graph
    }

    int start, end, forbiddenNode;
    printf("Enter start and end nodes: ");
    scanf("%d %d", &start, &end);
    printf("Enter forbidden Node: ");
    scanf("%d", &forbiddenNode);

    int list[50], clist[50], lcount = 0;
    list[0] = start;
    clist[0] = 0; // Assuming cost from start node to itself is 0
    lcount = 1;

    // Find paths between start and end nodes
    findpath(nodes, nodecount, start, end, list, clist, lcount, forbiddenNode);

    printf("\nPath count: %d", pc);

    return 0;
}
