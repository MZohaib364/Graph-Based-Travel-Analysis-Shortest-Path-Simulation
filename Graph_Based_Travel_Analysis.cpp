#include <iostream>

using namespace std;

const int MY_INT_MAX = 2147483647;

// Node structure for adjacency list representation
struct Node {
    int dest, weight;
    Node* next;

    Node(int d) {
        dest = d;
        weight = 0;
        next = nullptr;
    }
};

// Queue class for BFS traversal
class Queue {
    Node* front;

public:
    Queue() {
        front = nullptr;
    }

    void enqueue(int d) {
        Node* new_Node = new Node(d);

        if (front == nullptr) {
            front = new_Node;
            new_Node->next = nullptr;
        } else {
            Node* temp = front;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = new_Node;
        }
    }

    int dequeue() {
        if (front == nullptr) {
            cout << "Queue already empty!\n";
            return -1;
        }
        Node* temp = front;
        front = front->next;
        int data = temp->dest;
        delete temp;
        return data;
    }

    bool isempty() {
        return front == nullptr;
    }

    ~Queue() {
        while (front != nullptr) {
            Node* temp = front;
            front = front->next;
            delete temp;
        }
    }
};

// BFS traversal using a custom queue
void BFS(Node** graph, int cities, int start) {
    bool* visited = new bool[cities]{false};
    Queue q;
    
    // Enqueue the starting node and mark it as visited
    q.enqueue(start);
    visited[start] = true;
    int node;

    // Continue BFS until the queue is empty
    while (!q.isempty()) {
        // Dequeue a node and print it
        node = q.dequeue();
        cout << node << " ";

        // Traverse the adjacency list of the dequeued node
        Node* current = graph[node];
        while (current != nullptr) {
            // Enqueue unvisited neighbors and mark them as visited
            if (!visited[current->dest]) {
                q.enqueue(current->dest);
                visited[current->dest] = true;
            }
            current = current->next;
        }
    }

    delete[] visited;
}

// Function to find the minimum distance vertex not yet included in the shortest path tree
int get_min_dist(int* dist, bool* sptSet, int cities) {
    int min = MY_INT_MAX, min_index;

    // Iterate over all vertices to find the minimum distance vertex
    for (int v = 0; v < cities; v++) {
        // If the vertex is not in the shortest path tree and has a smaller distance
        if (!sptSet[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }

    return min_index;
}

// Function to find the minimum days to reach the destination
int get_min_days(int cities, Node** graph) {
    // Array to store the distance from the source to each vertex
    int* dist = new int[cities];
    // Array to keep track of whether the vertex is in the shortest path tree
    bool* isshortest = new bool[cities];

    // Initializing
    for (int i = 0; i < cities; ++i) {
        dist[i] = MY_INT_MAX;
        isshortest[i] = false;
    }

    dist[0] = 0;

    // Iterate over all vertices
    for (int count = 0; count < cities - 1; ++count) {
        // Find the vertex with the minimum distance not yet included in the shortest path tree
        int u = get_min_dist(dist, isshortest, cities);

        // Mark the selected vertex as included in the shortest path tree
        isshortest[u] = true;

        // Traverse the adjacency list of the selected vertex
        Node* current = graph[u];
        while (current != nullptr) {
            int v = current->dest;
            int weight = current->weight;

            // Update the distance if a shorter path is found
            if (!isshortest[v] && dist[u] != MY_INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }

            current = current->next;
        }
    }

    int result = (dist[cities - 1] + 5) / 6 + 1;

    delete[] dist;
    delete[] isshortest;

    return result;
}


// Function to add an edge to the adjacency list
void addEdge(Node** graph, int src, int dest, int weight) {
    Node* newNode = new Node(dest);
    newNode->weight = weight;
    newNode->next = graph[src];
    graph[src] = newNode;
}

int main() {
    cout << "Sample Input:\n";
    cout << "Enter Cases: ";
    int num_cases;
    cin >> num_cases;

    int result[num_cases];

    for (int i = 0; i < num_cases; i++) {
        cout << "\n -------------- CASE " << i+1 << " --------------\n";
        int cities, num_aerial_routes;
        cout << "Enter No of cities: ";
        cin >> cities ;
        cout << "Enter No of Aerial Routes: ";
        cin >> num_aerial_routes;

        Node** graph = new Node*[cities]{nullptr};

        cout << "Enter " << num_aerial_routes << " Aerial Routes(Source Destination):\n";
        for (int j = 0; j < num_aerial_routes; ++j) {
            int src, dest;
            cin >> src >> dest;
            addEdge(graph, src - 1, dest - 1, 0);
        }

        for (int j = 0; j < cities - 1; ++j) {
            addEdge(graph, j, j + 1, 1);
        }

        result[i] = get_min_days(cities, graph);

        // Deallocate memory for the graph
        for (int j = 0; j < cities; ++j) {
            Node* current = graph[j];
            while (current != nullptr) {
                Node* temp = current;
                current = current->next;
                delete temp;
            }
        }
        delete[] graph;
    }

    cout << "*************\n";
    cout << "OUTPUT:\n";

    for (int i = 0; i < num_cases; i++) {
        cout << "Case " << i+1 << " = " << result[i] << endl;
    }
    cout << "*************\n";

    return 0;
}
