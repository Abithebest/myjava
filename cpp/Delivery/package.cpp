#include <iostream>
#include <random>
#include <map>
#include <sstream>
#include <iomanip>
#include <algorithm>

#include "package.hpp"
#include "utils.hpp"

Package::Package() {
    type = static_cast<PackageType>(get_random_int(0, 3));
    trackingNumber = get_random_string(6);
    destination = destinations[get_random_index(2)];

    PackageStat packageStats = (PackageStats[(size_t)type]);
    weight = get_random_double(packageStats.minWeight, packageStats.maxWeight);
}
const std::string& Package::getTrackingNumber() const {
    return trackingNumber;
}
const std::string& Package::getDestination() const {
    return destination;
}
const double& Package::getWeight() const {
    return weight;
}
const PackageType& Package::getPackageType() const {
    return type;
}

std::map<std::string, Package> packages;
std::string formatPackages() {
    std::string packageString = "";
    for(auto package : packages) {
        Package& packageData = package.second;
        
        std::ostringstream weightStream;
        weightStream << std::fixed << std::setprecision(1)
                    << packageData.getWeight();

        packageString += "#" + packageData.getTrackingNumber() + 
                        " -> " + packageData.getDestination() + 
                        " -> " + weightStream.str() + " lbs.\n";
    }

    return packageString;
}