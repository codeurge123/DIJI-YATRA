#include <iostream>
#include <vector>
#include <limits>
#include <string>
#include <random>
#include <queue>
#include <algorithm>
#include <bits/stdc++.h>

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define CYAN "\033[36m"


void rating(void);
void captcha(void);

using namespace std;

class Dijkstras
{
private:
    vector<vector<int>> graph;
    int number_of_vertices;

public:
    void accept(int n)
    {
        number_of_vertices = n;

        graph.resize(number_of_vertices, vector<int>(number_of_vertices, 0));

        for (int i = 0; i < number_of_vertices; i++)
        {
            for (int j = i + 1; j < number_of_vertices; j++)
            {
                cout << "\t\t\tEnter distance between city " << i + 1 << " and city " << j + 1 << ": ";

                cin >> graph[i][j];

                graph[j][i] = graph[i][j];
            }
        }
    }

    void display()
    {
        cout << "\t\t\tGraph:" << endl;

        for (int i = 0; i < number_of_vertices; i++)
        {
            for (int j = 0; j < number_of_vertices; j++)
            {
                cout << "\t\t\t" << graph[i][j] << " ";
            }
            cout << endl;
        }

        cout << endl;
    }

    void apply_traffic_conditions()
    {
        random_device rd;

        mt19937 gen(rd()); // initialize random number generator.
        uniform_int_distribution<> dis(-20, 20); // Random adjustment between -20% to +20%

        cout << YELLOW << "Applying traffic conditions to the graph...\n"
             << RESET;

        for (int i = 0; i < number_of_vertices; i++)
        {
            for (int j = 0; j < number_of_vertices; j++)
            {
                // Only adjust if there's a valid edge

                if (graph[i][j] > 0 && i != j)

                {
                    int adjustment = dis(gen); // Generate random
                    int new_weight = graph[i][j] + (graph[i][j] * adjustment / 100);
                    graph[i][j] = max(1, new_weight); // Ensure weight remains at least 1
                }
            }
        }

        cout << GREEN << "Traffic conditions successfully applied.\n"
             << RESET;
    }

    int calculate_distance(int source, int destination)
    {
        if (source < 1 || source > number_of_vertices || destination < 1 || destination > number_of_vertices)
        {
            cout << RED << "Invalid source or destination city number.\n"
                 << RESET;

            return -1;
        }

        source--;
        destination--;

        vector<int> distance(number_of_vertices, numeric_limits<int>::max());

        vector<bool> visited(number_of_vertices, false);

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

        distance[source] = 0;

        pq.push({0, source});

        while (!pq.empty())
        {
            int u = pq.top().second;
            pq.pop();

            if (visited[u])
                continue;
            visited[u] = true;

            for (int v = 0; v < number_of_vertices; v++)
            {

                if (graph[u][v] > 0 && !visited[v])
                {
                    int weight = graph[u][v];

                    if (distance[u] + weight < distance[v])
                    {
                        distance[v] = distance[u] + weight;

                        pq.push({distance[v], v});
                    }
                }
            }
        }

        return distance[destination];
    }

    void road_block(int city1, int city2)
    {
        if (city1 < 1 || city2 < 1 || city1 > number_of_vertices || city2 > number_of_vertices)
        {
            cout << RED << "Invalid city numbers.\n"
                 << RESET;
            return;
        }
        graph[city1 - 1][city2 - 1] = 0;
        graph[city2 - 1][city1 - 1] = 0; //  undirected graph
        cout << YELLOW << "Road between the cities have been blocked.\n"
             << RESET;
    }

    void display_connectivity_matrix()
    {
        cout << CYAN << "Connectivity Matrix:\n"
             << RESET;
        for (int i = 0; i < number_of_vertices; i++)
        {
            for (int j = 0; j < number_of_vertices; j++)
            {
                cout << (graph[i][j] > 0 ? 1 : 0) << " ";
            }
            cout << endl;
        }
    }

    void rank_cities_by_connectivity()
    {
        vector<pair<int, int>> city_rank;

        for (int i = 0; i < number_of_vertices; i++)

        {
            int connections = 0;

            for (int j = 0; j < number_of_vertices; j++)
            {
                if (graph[i][j] > 0)
                {
                    connections++;
                }
            }
            city_rank.push_back({connections, i + 1});
        }

        sort(city_rank.rbegin(), city_rank.rend());
        cout << CYAN << "City Rankings (Based on Connectivity):\n"
             << RESET;
        for (auto &rank : city_rank)
        {
            cout << "City " << rank.second << ": " << rank.first << " connections\n";
        }
    }

    void find_all_routes(int source, int destination, vector<int> &path, vector<bool> &visited)
    {
        source--;      // Convert to zero-based index
        destination--; // Convert to zero-based index

        visited[source] = true;
        path.push_back(source + 1);

        if (source == destination)
        {
            for (size_t i = 0; i < path.size(); i++)
            {
                cout << path[i];
                if (i != path.size() - 1)
                    cout << " -> ";
            }
            cout << endl;
        }
        else
        {
            for (int v = 0; v < number_of_vertices; v++)
            {
                if (graph[source][v] > 0 && !visited[v])
                {
                    find_all_routes(v + 1, destination + 1, path, visited);
                }
            }
        }

        path.pop_back();
        visited[source] = false;
    }

    void list_all_routes(int source, int destination)
    {
        if (source < 1 || source > number_of_vertices || destination < 1 || destination > number_of_vertices)
        {
            cout << RED << "Invalid source or destination city number.\n"
                 << RESET;
            return;
        }

        vector<int> path;
        vector<bool> visited(number_of_vertices, false);

        cout << CYAN << "All possible routes from City " << source << " to City " << destination << ":\n"
             << RESET;
        find_all_routes(source, destination, path, visited);
    }

    vector<int> calculate_path(int source, int destination)
    {
        source--;
        destination--;

        vector<int> distance(number_of_vertices, numeric_limits<int>::max());
        vector<int> previous(number_of_vertices, -1);
        vector<bool> visited(number_of_vertices, false);

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        distance[source] = 0;
        pq.push({0, source});

        while (!pq.empty())
        {
            int u = pq.top().second;
            pq.pop();

            if (visited[u])
                continue;
            visited[u] = true;

            for (int v = 0; v < number_of_vertices; v++)
            {
                if (graph[u][v] > 0 && !visited[v])
                {
                    int weight = graph[u][v];
                    if (distance[u] + weight < distance[v])
                    {
                        distance[v] = distance[u] + weight;
                        previous[v] = u;
                        pq.push({distance[v], v});
                    }
                }
            }
        }

        vector<int> path;
        for (int at = destination; at != -1; at = previous[at])
        {
            path.push_back(at + 1);
        }
        reverse(path.begin(), path.end());

        return (path.front() == source + 1) ? path : vector<int>{};
    }
};

int main()
{

    captcha();
    cout << CYAN << "\t\t\t\t\t\tWELCOME" << endl;
    cout << GREEN << "\t\t\t\tJAYPEE INSTITUTE OF INFORMATION TECHNOLOGY" << endl;
    cout << "\n";
    cout << YELLOW << "\t\t\t\t\t\tProject" << endl;
    cout << "\t\t\t\t\t      DIJI-YATRA\n"
         << RESET;

    string password;
    string role;

    double busFare = 1.5;
    double trainFare = 2.0;
    double metroFare = 2.5;

    int number_of_vertices = 0;
    cout << CYAN << "\n\t\t\tEnter number of cities: ";
    cin >> number_of_vertices;
    cout << endl;

    Dijkstras obj;

    while (true)
    {
        cout << "\t\t\tEnter your role (admin/customer/exit): ";
        cin >> role;
        cout << endl;

        if (role == "exit")
        {
            cout << "THANKS FOR USING THE SERVICES OF DIGI- Yatra" << endl;
            rating();
            break;
        }
        cout << "\t\t\tEnter your password: ";
        cin >> password;
        cout << endl;




        if (role == "admin" && password == "admin123")
        {
            cout << "\t\t\t\t\tAccess granted to admin." << endl;

            while (true)
            {
                int choice;
                cout << "\nSelect an option:\n"
                     << "1. Set fares\n"
                     << "2. Set distances for all modes of travel\n"
                     << "3. Apply traffic conditions\n"
                     << "4. Display graph\n"
                     << "5. See Connectivity Matrix of cities\n"
                     << "6. Do repair/ roadblocks\n"
                     << "7. See connectivity ranking of the cities\n "
                     << "8. Exit to main menu\n"
                     << "Enter your choice (1-8): ";

                cin >> choice;

                switch (choice)
                {
                case 1:
                    cout << "\t\t\tEnter new fare for bus travel: ";
                    cin >> busFare;
                    cout << "\t\t\tEnter new fare for train travel: ";
                    cin >> trainFare;
                    cout << "\t\t\tEnter new fare for metro travel: ";
                    cin >> metroFare;
                    break;

                case 2:
                    obj.accept(number_of_vertices);
                    break;

                case 3:
                    obj.apply_traffic_conditions();
                    obj.display();
                    break;

                case 4:
                    obj.display();
                    break;

                case 5:
                    obj.display_connectivity_matrix();
                    break;

                case 6:
                    int city1;
                    int city2;
                    cout << "give the cities between which repair work or road-block has to happen\n ";
                    cin >> city1;
                    cin >> city2;
                    obj.road_block(city1, city2);
                    break;

                case 7:
                    obj.rank_cities_by_connectivity();
                    break;

                case 8:
                    cout << "Returning to main menu..." << endl;
                    goto endAdminMenu;

                default:
                    cout << "Invalid choice. Please try again." << endl;
                }
            }
        endAdminMenu:;
        }
        else if (role == "customer" && password == "cust123")
        {
            cout << "\t\t\t\t\tAccess granted to customer." << endl;

            while (true)
            {

                int choice;

                cout << "\nSelect an option:\n"
                     << "1. Find shortest path and calculate fare of the journey\n"
                     << "2. Apply latest traffic conditions\n"
                     << "3. Find all paths between two cities\n"
                     << "4. Exit to main menu\n"
                     << "Enter your choice (1-4): ";

                cin >> choice;

                switch (choice)
                {
                case 1:
                {
                    int source, destination;
                    cout << "\t\t\tEnter source city number: ";
                    cin >> source;
                    cout << "\t\t\tEnter destination city number: ";
                    cin >> destination;

                    vector<int> shortestPath = obj.calculate_path(source, destination);

                    if (!shortestPath.empty())
                    {
                        cout << "The shortest path is: ";
                        for (size_t i = 0; i < shortestPath.size(); ++i)
                        {
                            cout << shortestPath[i];
                            if (i != shortestPath.size() - 1)
                                cout << " -> ";
                        }
                        cout << endl;

                        double dist = obj.calculate_distance(source, destination);
                        cout << "Total distance of the journey =" << dist << endl;

                        cout << "Tell us your mode of transportation\n";
                        cout << "Bus\n";
                        cout << "train\n";
                        cout << "metro\n";
                        string tran;
                        cin >> tran;

                        random_device rd;
                        mt19937 gen(rd());
                        uniform_int_distribution<> dis(100000, 999999);

                        int tfare;
                        int bfare;
                        int mfare;

                        if (tran == "bus")
                        {
                            bfare = busFare * dist;
                            cout << "Your total transportation cost =" << bfare;

                            cout << endl;
                            cout << "Your bus ticket number is: " << dis(gen) << endl;
                        }

                        if (tran == "train")
                        {
                            tfare = trainFare * dist;
                            cout << "Your total transportation cost =" << tfare;

                            cout << endl;
                            cout << "Your train ticket number is: " << dis(gen) << endl;
                        }

                        if (tran == "metro")
                        {
                            mfare = metroFare * dist;
                            cout << "Your total transportation cost = " << mfare;

                            cout << endl;
                            cout << "Your train  ticket number is: " << dis(gen) << endl;
                        }
                    }
                    else
                    {
                        cout << "No path exists between the given cities." << endl;
                    }

                    break;
                }

                case 2:
                    obj.apply_traffic_conditions();
                    obj.display();
                    break;

                case 3:
                    int src, dest;
                    cout << "Enter source city number: ";
                    cin >> src;

                    cout << "Enter destination city number: ";
                    cin >> dest;

                    obj.list_all_routes(src, dest);
                    break;

                case 4:
                    cout << "Returning to main menu..." << endl;
                    goto endCustomerMenu;

                default:

                    cout << "Invalid choice. Please try again." << endl;
                }
            }
        endCustomerMenu:;
        }
        else
        {
            cout << "Invalid role or password entered." << endl;
        }
    }

    return 0;
}

void captcha()
{

    char str2[100];
    char str1[10] = "yes";
    int l1;
    int l2;
    int i, j, k;

    cout << "TO ENTER WE WILL ASK SOME QUESTIONS TO VERIFY YOU ARE HUMAN OR NOT\n";
    cout << "WRITE 'yes' TO CONTINUE 'no' TO DISCONTINUE\n";

    gets(str2);
    l1 = strlen(str1);
    l2 = strlen(str2);

    if (l1 != l2)
    {
        cout << "YOU DISCOUNTINUED CAPTHA VERIFICATION FAILED!!!\n";
        exit;
    }
    for (i = 0; str1[i]; i++)
    {
        if (str1[i] != str2[i])
        {
            cout << "YOU DISCOUNTINUED CAPTHA VERIFICATION FAILED!!!";
            return;
        }
    }
    cout << "ENTER THE NAME OF THE BELOW SHAPE?\n";

    for (i = 1; i <= 5; i++)
    {
        k = 1;
        for (j = 1; j <= 9; j++)
        {

            if (j >= 6 - i && j <= 4 + i && k)
            {
                cout << "*";
                k = 0;
            }
            else
            {
                cout << " ";
                k = 1;
            }
        }
        cout << "\n";
    }

    char str4[] = "triangle";
    char str5[10];
    gets(str5);

    int l4, l5;

    l4 = strlen(str4);
    l5 = strlen(str5);
    if (l4 != l5)
    {
        cout << "CAPTHA VERIFICATION FAILED\n";
        cout << "YOU ENTERED THE WRONG SHAPE\n";
        exit;
    }

    for (i = 0; str4[i]; i++)
    {
        if (str4[i] != str5[i])
        {
            cout << "CAPTHA VERIFICATION FAILED\n";
            cout << "YOU ENTERED THE WRONG SHAPE\n";
            return;
        }
    }

    cout << "YOU ENTERED THE RIGHT SHAPE\n\n";

    cout << "NOW WHAT IS THE SHAPE BELOW?\n";

    for (i = 1; i <= 9; i++)
    {

        if (i <= 5)
        {
            k++;
        }
        else
        {
            k--;
        }
        for (j = 1; j <= 9; j++)
        {
            if ((j == 6 - k || j == 4 + k) || (j == 5 || i == 5))
                cout << "*";
            else
                cout << " ";
        }
        cout << "\n";
    }

    int l6, l7;
    char str6[] = "diamond";
    char str7[10];
    gets(str7);
    l6 = strlen(str6);
    l7 = strlen(str7);
    if (l6 != l7)
    {
        cout << "CAPTHA VERIFICATION FAILED\n";
        cout << "YOU ENTER THE WRONG SHAPE\n";
        return;
    }
    for (i = 0; str6[i]; i++)
    {
        if (str6[i] != str7[i])
        {
            cout << "CAPTHA VERIFICATION FAILED\n";
            cout << "YOU ENTERED THE WRONG SHAPE\n";
            return;
        }
    }

    cout << "YOU ENTERED THE RIGHT SHAPE\n\n";

    cout << "ENTER THE BELOW SHAPE\n";

    for (i = 1; i <= 5; i++)
    {
        for (j = 1; j <= 9; j++)
        {
            if (j >= 6 - i && j <= 4 + i)
                cout << "*";
            else
                cout << " ";
        }
        cout << "\n";
    }

    for (i = 1; i <= 3; i++)
    {
        for (j = 1; j <= 9; j++)
        {
            cout << "*";
        }
        cout << "\n";
    }

    for (i = 1; i <= 5; i++)
    {
        for (j = 1; j <= 9; j++)
        {
            if (j >= i && j <= 10 - i)
                cout << "*";
            else
                cout << " ";
        }
        cout << "\n";
    }

    int l8, l9;
    char str8[] = "hexagon";
    char str9[10];
    gets(str9);
    l8 = strlen(str8);
    l9 = strlen(str9);
    if (l8 != l9)
    {
        cout << "CAPTHA VERIFICATION FAILED\n";
        cout << "YOU ENTERED THE WRONG SHAPE\n";
        return;
    }

    for (i = 0; str8[i]; i++)
    {
        if (str8[i] != str9[i])
        {
            cout << "CAPTHA VERIFICATION FAILED\n";
            cout << "YOU ENTERED THE WRONG SHAPE\n";
            return;
        }
    }

    cout << "YOU ENTERED THE RIGHT SHAPE\n\n";
    cout << "YOU HAVE SUCCESFULLY PASSED OUR CAPTHA VERIFICATION\n ";
    cout << "NOW YOU HAVE ENTERED OUR TRAVEL SERIVES\n";
}

void rating()
{
    int r;
    int i;
    int j;

    cout << "PLEASE ENTER YOUR RATING THIS WILL BE VALUABLE TO US" << endl;
    cout << "5 MEANS ABSOLUTELY BEST 1 MEANS WORST" << endl;

    cin >> r;

    if (r == 1)
    {
        for (i = 1; i <= 7; i++)
        {
            for (j = 1; j <= 5; j++)
            {
                if ((i == 2 && j == 2) || (i == 3 && j == 1) || (j == 3) || (i == 7))
                {
                    cout << "*";
                }
                else
                {
                    cout << " ";
                }
            }
            cout << endl;
        }

        cout << "THANK YOU FOR RATING US,YOU GAVE US 1 STARS" << endl;
        cout << "WE WILL MAKE SURE TO CHANGE YOUR EXPIEREINCE NEXT TIME" << endl;
    }

    if (r == 2)
    {
        for (i = 1; i <= 7; i++)
        {
            for (j = 1; j <= 4; j++)
            {
                if ((i <= 4 && j == 4) || (i <= 7 && i >= 4 && j == 1) || (i == 1) ||
                    (i == 4) || (i == 7))
                {
                    cout << "*";
                }
                else
                {
                    cout << " ";
                }
            }
            cout << endl;
        }

        cout << "THANK YOU FOR RATING US,YOU GAVE US 2 STARS" << endl;
        cout << "WE WILL MAKE SURE TO GIVE YOU BETTER EXPIEREINCE NEXT TIME"
             << endl;
    }

    if (r == 3)
    {
        for (i = 1; i <= 7; i++)
        {
            for (j = 1; j <= 4; j++)
            {
                if ((j == 4) || (i == 1) || (i == 4) || (i == 7))
                {
                    cout << "*";
                }
                else
                {
                    cout << " ";
                }
            }
            cout << endl;
        }

        cout << "THANK YOU FOR RATING US,YOU GAVE US 3 STARS" << endl;
        cout << "WE WILL MAKE SURE TO IMPROVE YOUR EXPIEREINCE FURTHER NEXT TIME"
             << endl;
    }

    if (r == 4)
    {
        for (i = 1; i <= 7; i++)
        {
            for (j = 1; j <= 4; j++)
            {
                if ((j == 4) || (i == 4) || (j == 1) && (i <= 4))
                {
                    cout << "*";
                }
                else
                {
                    cout << " ";
                }
            }
            cout << endl;
        }

        cout << "THANK YOU SO MUCH FOR RATING US,YOU GAVE US 4 STARS" << endl;
        cout << "WE WILL MAKE SURE TO IMPROVE YOUR EXPIEREINCE FURTHER NEXT TIME"
             << endl;
    }

    if (r == 5)
    {
        for (i = 1; i <= 7; i++)
        {
            for (j = 1; j <= 5; j++)
            {
                if ((i == 1) || (i == 4) || (i == 7) || (i <= 4) && (j == 1) ||
                    (i >= 4) && (i <= 7) && (j == 5))
                {
                    cout << "*";
                }
                else
                {
                    cout << " ";
                }
            }
            cout << endl;
        }

        cout << "THANK YOU SO MUCH FOR RATING US,YOU GAVE US 5 STARS" << endl;
        cout << "WE WILL MAKE SURE TO IMPROVE YOUR EXPIEREINCE FURTHER NEXT TIME"
             << endl;
    }

    cout << "THANK YOU FOR BEING WITH US AND BELIEVING US" << endl;
    cout << "HAPPY TRAVELLING WITH DIGI-YATRA" << endl;
}
