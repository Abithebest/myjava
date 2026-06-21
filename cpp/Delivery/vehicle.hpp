#ifndef VEHICLE_HPP
#define VEHICLE_HPP

#include <iostream>
#include <vector>
#include <array>
#include <string_view>

#include "package.hpp"

enum class VehicleType {
    Van = 0,
    BoxTruck,
    SemiTruck,
    SmallPlane,
    BigPlane,
    Count
};
struct VehicleStats {
    std::string_view name;
    double cost;
    double weight;
};
inline const std::array<VehicleStats, (size_t)VehicleType::Count> VehicleStatData = {{
    {"Van", 1000.0, 100.0},
    {"Box Truck", 5000.0, 500.0},
    {"Semi Truck", 50000.0, 5000.0},
    {"Small Plane", 100000.0, 10000.0},
    {"Big Plane", 500000.0, 50000.0}
}};

struct VehicleMaintenance {
    double chasis;
    double engine;
    double tires;
};

class Vehicle {
    private:
        std::string id;
        int level;
        double maxWeight;
        std::vector<Package> currentPackages;

    public:
        VehicleType type;
        VehicleMaintenance maintenance;
        bool departed = false;

        Vehicle(int vehicleType);
        std::string getId() const;
        int getLevel() const;
        double getMaxWeight() const;
        double getCurrentWeight() const;
        const std::vector<Package>& getCurrentPackages() const;
        void addPackage(Package& package);
        void emptyPackages();
        void upgradeVehicle();
};
extern std::vector<Vehicle> vehicles;

std::string formatVehicles(bool includeMaintenance);

#endif