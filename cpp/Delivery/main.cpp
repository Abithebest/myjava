#include <iostream>
#include <random>
#include <map>
#include <algorithm>

#include "vehicle.hpp"
#include "package.hpp"
#include "utils.hpp"

//truck maintenance - every departure weakens them by a random percentage
//  tires, engine, chasis
//truck fuel costs when comes back

//workers
//  hire either driver or loader
//  pay wage each day
//  upgrade workers (lvl. 5 max) - higher wages but can do more work
//      driver - uses less fuel & less maintenance
//          lvl.1 - default, lvl.2 - 25% less, lvl.3 - 50% less, lvl.4 - 75% less, lvl.5 - 100% less
//      loader - adds more packages at a time
//          lvl.1 - default, lvl.2 - 2 packages at a time, lvl.3 - 3 packages at a time, lvl. 4 - 4 packages at a time, lvl.5 - takes weight out of packages randomly

int main() {
    int menuChoice;
    bool continueCommands = true;

    Vehicle startingVehicle(0);
    vehicles.push_back(startingVehicle);

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
            case 1: { // Next Day
                std::string packageString = "";
                std::string vehicleString = "";

                // Package Delivery
                int packageCount = get_random_int(0, 5);
                int packagesAdded = 0;
                for(int i=0; i<packageCount; i++) {
                    Package package;
                    if((depotCurrentWeight + package.getWeight()) > depotMaxWeight) {
                        continue;
                    }
                    packages[package.getTrackingNumber()] = package;
                    packageString += "New package #" + package.getTrackingNumber() + "\n";

                    totalPackages++;
                    packagesAdded++;
                    totalWeight += package.getWeight();
                    depotCurrentWeight += package.getWeight();
                    depotMoney += package.getWeight() * depotMoneyPerLbs;
                }
                if(packageCount == 0 || packagesAdded == 0) {
                    packageString = "No Packages Today...\n";
                }

                // Depart & Return Vehicles
                for(Vehicle& vehicle : vehicles) {
                    if(vehicle.departed == true) {
                        vehicle.departed = false;
                        for(const Package& package : vehicle.getCurrentPackages()) {
                            depotCurrentWeight -= package.getWeight();
                            packages.erase(package.getTrackingNumber());
                        }

                        vehicle.emptyPackages();
                        vehicleString += vehicle.getId() + " returned.\n";
                    } else if(!vehicle.getCurrentPackages().empty()) {
                        vehicle.departed = true;
                        vehicleString += vehicle.getId() + " departed.\n";
                    }
                }
                if(vehicleString.length() == 0) {
                    vehicleString = "No Vehicle Departures.\n";
                }

                std::cout << packageString + "\n" + vehicleString + "\n";
                break;
            }

            case 2: { // Assign Packages
                if(packages.empty() == true) {
                    std::cout << "No packages to assign...\n\n";
                    break;
                }

                std::cout << formatVehicles(false) + "\nChoose a vehicle to assign to > ";

                std::string vehicleAssign;
                std::cin >> vehicleAssign;

                vehicleAssign = uppercase(vehicleAssign);

                auto vehicleData = std::find_if(
                    vehicles.begin(),
                    vehicles.end(),
                    [&vehicleAssign](const Vehicle& v) {
                        return v.getId() == vehicleAssign;
                    }
                );
                if (vehicleData == vehicles.end()) {
                    std::cout << "Vehicle does not exist...\n";
                    break;
                }

                Vehicle& vehicle = *vehicleData;
                std::cout << formatPackages() + "\nChoose a package to assign > ";

                std::string transferNumber;
                std::cin >> transferNumber;

                transferNumber = remove_char(transferNumber, '#');
                transferNumber = uppercase(transferNumber);
                Package& assignmentPackage = packages[transferNumber];
                if(packages.find(transferNumber) == packages.end()) {
                    std::cout << "Package does not exist...\n\n";
                    break;
                }

                if(assignmentPackage.getWeight() + vehicle.getCurrentWeight() > vehicle.getMaxWeight()) {
                    std::cout << "Package assignment exceeds max weight for vehicle...\n\n";
                    break;
                }

                depotCurrentWeight -= assignmentPackage.getWeight();
                vehicle.addPackage(assignmentPackage);
                packages.erase(transferNumber);

                std::cout << "Assigned package #" + transferNumber + " to vehicle " + vehicle.getId() + "\n\n";
                break;
            }

            case 3: { // Buy Vehicle
                std::string vehicleString = "";
                for(int i=0; i<5; i++) {
                    VehicleType vType = static_cast<VehicleType>(i);
                    VehicleStats vStats = VehicleStatData[i];
                    std::string vName{vStats.name};

                    vehicleString += std::to_string(i + 1) + ". " + vName + " - " + toFixed(vStats.weight, 1) + " max lbs. | $" + toFixed(vStats.cost, 0) + "\n";
                }

                std::cout << "Depot Money: $" + toFixed(depotMoney, 0) + "\n\n" + vehicleString + "\nChoose vehicle to buy > ";
                int vehicleNum;
                std::cin >> vehicleNum;
                if(vehicleNum > 5 || vehicleNum < 1) {
                    std::cout << "Vehicle does not exist for purchase...\n\n";
                    break;
                }

                VehicleStats vehicle = VehicleStatData[vehicleNum - 1];
                std::string vName{vehicle.name};
                if(depotMoney < vehicle.cost) {
                    std::cout << "Not enough money...\n\n";
                    break;
                }

                depotMoney -= vehicle.cost;
                Vehicle newVehicle(vehicleNum - 1);
                vehicles.push_back(newVehicle);

                std::cout << "Bought new " + vName + " for $" + toFixed(vehicle.cost, 0) + "!\n\n";
                break;
            }

            case 4: { // View Packages
                std::string packageString = "Max Weight: " + toFixed(depotCurrentWeight, 1) + "/" + toFixed(depotMaxWeight, 1) + " lbs.";
                if(packages.empty() == true) {
                    packageString += "\nNo packages.\n";
                }

                packageString += "\n" + formatPackages();
                std::cout << packageString + "\n";
                break;
            }

            case 5: // View Vehicles
                std::cout << formatVehicles(true) + "\n";
                break;

            case 6: { // View Depot Statistics
                double averageWeight = totalWeight / totalPackages;
                std::cout << "Packages Stored: " + toFixed(totalPackages, 0) + "\nTotal Weight: " + toFixed(totalWeight, 1) + " lbs.\nAverage Weight: " + toFixed(averageWeight, 1) + " lbs.\n\n";
                break;
            }

            case 7: { // Upgrade Depot
                double upgradeCost = depotLevel * 1500;
                if(depotMoney < upgradeCost) {
                    std::cout << "Not enough money to upgrade. $" + toFixed(upgradeCost, 0) + "\n\n";
                    break;
                }

                depotMoney -= upgradeCost;
                depotLevel++;
                depotMaxWeight += 150.0;
                depotMoneyPerLbs += 1.5;
                std::cout << "Upgraded depot!\n\n";
                break;
            }

            case 8: // Exit
                continueCommands = false;
                std::cout << "Exited instance...\n";
                break;

            default: // Not a command
                std::cout << "Not a command...\n";
                break;
        }
    }

    return 0;
}