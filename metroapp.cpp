#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <limits>

class MetroGraph {
public:
    // Represents a station in the metro graph
    struct Station {
        std::string name;
        std::unordered_map<std::string, int> neighbors; // Neighboring stations and their distances
    };

    std::unordered_map<std::string, Station> stations; // Map of station name to Station structure

    // Add a station to the graph
    void addStation(const std::string& name) {
        stations[name] = Station{name, {}};
    }

    // Add a connection (edge) between two stations with a given distance
    void addConnection(const std::string& station1, const std::string& station2, int distance) {
        stations[station1].neighbors[station2] = distance;
        stations[station2].neighbors[station1] = distance;
    }

    // Dijkstra's algorithm to find the shortest distance from source to all other stations
    std::unordered_map<std::string, int> dijkstra(const std::string& source) {
        std::priority_queue<std::pair<int, std::string>, std::vector<std::pair<int, std::string>>, std::greater<>> pq;
        std::unordered_map<std::string, int> distance;

        for (const auto& entry : stations) {
            distance[entry.first] = std::numeric_limits<int>::max();
        }

        distance[source] = 0;
        pq.push({0, source});

        while (!pq.empty()) {
            std::string current = pq.top().second;
            int currentDistance = pq.top().first;
            pq.pop();

            for (const auto& neighbor : stations[current].neighbors) {
                int newDistance = currentDistance + neighbor.second;
                if (newDistance < distance[neighbor.first]) {
                    distance[neighbor.first] = newDistance;
                    pq.push({newDistance, neighbor.first});
                }
            }
        }

        return distance;
    }
};

// Function to print the menu options
void printMenu() {
    std::cout << "\nMetro Navigation System";
    std::cout << "\n------------------------";
    std::cout << "\n1. Display Stations";
    std::cout << "\n2. Add Connection";
    std::cout << "\n3. Find Minimum Distance";
    std::cout << "\n4. Exit";
    std::cout << "\nEnter your choice: ";
}

int main() {
    MetroGraph metro;

    // Adding sample stations
    metro.addStation("Station A");
    metro.addStation("Station B");
    metro.addStation("Station C");

    // Adding sample connections
    metro.addConnection("Station A", "Station B", 5);
    metro.addConnection("Station B", "Station C", 3);
    metro.addConnection("Station A", "Station C", 7);

    int choice;
    std::string source, destination;

    do {
        printMenu();
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "\nStations:\n";
                for (const auto& entry : metro.stations) {
                    std::cout << entry.first << "\n";
                }
                break;

            case 2:
                std::cout << "\nEnter source station: ";
                std::cin >> source;
                std::cout << "Enter destination station: ";
                std::cin >> destination;
                int distance;
                std::cout << "Enter distance between " << source << " and " << destination << ": ";
                std::cin >> distance;
                metro.addConnection(source, destination, distance);
                std::cout << "Connection added!\n";
                break;

            case 3:
                std::cout << "\nEnter source station: ";
                std::cin >> source;
                std::cout << "Enter destination station: ";
                std::cin >> destination;

                if (metro.stations.find(source) == metro.stations.end() || metro.stations.find(destination) == metro.stations.end()) {
                    std::cout << "Invalid station names.\n";
                } else {
                    auto distances = metro.dijkstra(source);
                    std::cout << "Minimum distance from " << source << " to " << destination << " is: " << distances[destination] << " units\n";
                }
                break;

            case 4:
                std::cout << "\nExiting...\n";
                break;

            default:
                std::cout << "\nInvalid choice. Please try again.\n";
        }

    } while (choice != 4);

    return 0;
}
