#ifndef PACKAGE_HPP
#define PACKAGE_HPP
#include <iostream>
#include <string>
#include <string_view>
#include <map>

enum class PackageType {
    Envelope = 0,
    SmallBox,
    BigBox,
    Count
};
struct PackageStat {
    std::string_view name;
    double minWeight;
    double maxWeight;
};
inline const std::array<PackageStat, (size_t)PackageType::Count> PackageStats = {{
    {"Envelope", 1.5, 7.5},
    {"Small Box", 10.0, 35.0},
    {"Big Box", 50.0, 100.0}
}};
class Package {
    private:
        std::string trackingNumber;
        std::string destination;
        double weight;
        PackageType type;

    public:
        Package();
        const std::string& getTrackingNumber() const;
        const std::string& getDestination() const;
        const double& getWeight() const;
        const PackageType& getPackageType() const;
};
extern std::map<std::string, Package> packages;
std::string formatPackages();

#endif