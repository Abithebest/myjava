#include <iostream>
#include <random>

#include "vehicle.hpp"
#include "package.hpp"
#include "utils.hpp"

std::vector<Vehicle> vehicles;
Vehicle::Vehicle(int vehicleType) {
    id = get_random_string(6);
    level = 1;
    type = static_cast<VehicleType>(vehicleType);
    
    VehicleStats vehicleStats = VehicleStatData[(size_t)type];
    maxWeight = vehicleStats.weight;
    maintenance = {vehicleStats.maxFuel, 0.0, 0.0, 0.0};
}

std::string Vehicle::getId() const {
    return id;
}
int Vehicle::getLevel() const {
    return level;
}
double Vehicle::getMaxWeight() const {
    return maxWeight;
}
double Vehicle::getCurrentWeight() const {
    double vehicleWeight = 0.0;
    for(const Package& package : currentPackages) {
        vehicleWeight += package.getWeight();
    }

    return vehicleWeight;
}
const std::vector<Package>& Vehicle::getCurrentPackages() const {
    return currentPackages;
}

void Vehicle::addPackage(Package& package) {
    currentPackages.push_back(package);
}
void Vehicle::emptyPackages() {
    currentPackages.clear();
}
void Vehicle::upgradeVehicle() {
    double cost = VehicleStatData[(size_t)type].cost * (level + 1);
}

std::string formatVehicles(bool includeMaintenance, bool includePackages) {
    std::string vehicleString = "";
    for(const Vehicle& vehicle : vehicles) {
        std::string vehiclePackages = "";
        if(includePackages == true) {
            for(const Package& package : vehicle.getCurrentPackages()) {
                vehiclePackages += "  #" + package.getTrackingNumber() + " - " + toFixed(package.getWeight(), 1) + " lbs.\n";
            }
            if(vehiclePackages.empty() == true) {
                vehiclePackages = "  No Packages.";
            }
        }
        
        VehicleStats vStats = VehicleStatData[(size_t)vehicle.type];
        std::string vehicleName{vStats.name};
        vehicleString += "- (" + vehicleName + ") " + vehicle.getId() + " | " + toFixed(vehicle.getCurrentWeight(), 1) + "/" + toFixed(vehicle.getMaxWeight(), 1) + " lbs.";

        if(vehicle.departed) {
            vehicleString += " - DEPARTED\n";
        } else { vehicleString += "\n"; }
        if(includeMaintenance == true) {
            vehicleString += "🔧 Maintenance:\n  Fuel: " + toFixed(vehicle.maintenance.fuel, 1) + "/" + toFixed(vStats.maxFuel, 1) + " gl.\n  Chasis: " + toFixed(vehicle.maintenance.chasis, 1) + "%\n  Engine: " + toFixed(vehicle.maintenance.engine, 1) + "%\n  Tires: " + toFixed(vehicle.maintenance.tires, 1) + "%\n";
        }
        if(includePackages == true) {
            vehicleString += "📦 Packages:\n" + vehiclePackages;
        }
    }

    return vehicleString;
}