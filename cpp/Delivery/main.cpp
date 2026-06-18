#include <iostream>
#include <random>
#include <map>

std::string menu = "=== Delivery Depot ===\n\n1. Recieve Package\n2. Ship Package\n3. View Packages\n4. Exit\n\n> ";
std::string menuChoice;
std::vector<std::string> destinations = {"Florida", "New York"};

std::string get_random_string(size_t length) {
    const std::string pool = "abcdefghijklmnopqrstuvwxyz"
                             "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                             "0123456789";

    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<size_t> distribution(0, pool.size() - 1);

    std::string result;
    result.reserve(length);
    
    for (size_t i = 0; i < length; ++i) {
        size_t random_index = distribution(generator);
        result += pool[random_index];
    }

    return result;
}
std::string get_random_item(std::vector<std::string> array) {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<size_t> distribution(0, array.size() - 1);

    size_t randomIndex = distribution(generator);
    std::string result = array[randomIndex];

    return result;
}
double get_random_weight() {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_real_distribution<double> distribution(5.0, 70.0);
    return distribution(generator);
}

class Package {
    private:
        std::string trackingNumber;
        std::string destination;
        double weight;

    public:
        Package() {
            trackingNumber = get_random_string(6);
            destination = get_random_item(destinations);
            weight = get_random_weight();
        }

        std::string getTrackingNumber() {
            return trackingNumber;
        }
        std::string getDestination() {
            return destination;
        }
        double getWeight() {
            return weight;
        }
};
std::map<std::string, Package> packages;

int main() {
    int menuChoice;
    bool continueCommands = true;

    while(continueCommands) {
        std::cout << menu;
        std::cin >> menuChoice;

        if (!menuChoice) {
            std::cout << "Invalid input...\n";

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            continue;
        }

        switch(menuChoice) {
            case 1: {
                Package package;
                packages[package.getTrackingNumber()] = package;
                break;
            }

            case 2:
                break;
            case 3:
                break;
            case 4:
                continueCommands = false;
                std::cout << "Exited instance...\n";
                break;
            default:
                std::cout << "Not a command...\n";
                break;
        }
    }

    return 0;
}