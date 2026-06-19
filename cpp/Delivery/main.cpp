#include <iostream>
#include <random>
#include <map>
#include <sstream>
#include <iomanip>
#include <algorithm>

#include "vehicle.h"

std::string menu = "=== Delivery Depot ===\n\n1. Recieve Package\n2. Ship Package\n3. View Packages\n4. View Depot Statistics\n5. Exit\n\n> ";
std::string menuChoice;
std::vector<std::string> destinations = {"Florida", "New York"};

int totalPackages = 0;
double totalWeight = 0.0;

std::string get_random_string(size_t length) {
    const std::string pool = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
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

            totalPackages++;
            totalWeight += weight;
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

std::string formatPackages() {
    std::string packageString = "";
    for(auto package : packages) {
        Package packageData = package.second;
        
        std::ostringstream weightStream;
        weightStream << std::fixed << std::setprecision(1)
                    << packageData.getWeight();

        packageString += "#" + packageData.getTrackingNumber() + 
                        " -> " + packageData.getDestination() + 
                        " -> " + weightStream.str() + " lbs.\n";
    }

    return packageString;
}

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
                //Recieve Package
                Package package;
                packages[package.getTrackingNumber()] = package;
                std::cout << "New package #" << package.getTrackingNumber() << " | Going to " << package.getDestination() << "\n\n";

                break;
            }

            case 2: {
                //Ship Package
                std::cout << formatPackages() + "\nChoose a package to ship > ";

                std::string transferNumber;
                std::cin >> transferNumber;

                transferNumber.erase(std::remove(transferNumber.begin(), transferNumber.end(), '#'), transferNumber.end());
                std::transform(transferNumber.begin(), transferNumber.end(), transferNumber.begin(), [](unsigned char c) {
                    return std::toupper(c);
                });

                packages.erase(transferNumber);
                break;
            }

            case 3:
                //View Packages
                std::cout << formatPackages() + "\n";
                break;

            case 4:
                //View Depot Statistics
                break;

            case 5:
                //Exit
                continueCommands = false;
                std::cout << "Exited instance...\n";
                break;

            default:
                //Not a command
                std::cout << "Not a command...\n";
                break;
        }
    }

    return 0;
}