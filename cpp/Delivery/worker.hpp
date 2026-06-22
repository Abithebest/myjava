#ifndef WORKER_HPP
#define WORKER_HPP

#include <iostream>
#include <map>

enum class WorkerType {
    Driver = 0,
    Loader,
    Mechanic,
    Count
};
struct WorkerStats {
    std::string name;
    double startingWage;
    double hireCost;
};
inline const std::array<WorkerStats, (size_t)WorkerType::Count> WorkerStatData = {{
    {"Driver", 22.0, 500.0},
    {"Loader", 16.0, 500.0},
    {"Mechanic", 23.0, 1000.0}
}};

class Worker {
    private:
        std::string id;
        double wage;
        int level;
        WorkerType type;
    public:
        bool usedSpecialty;

        Worker(int workerType);
        std::string getId() const;
        double getWage() const;
        int getLevel() const;
        WorkerType getType() const;
        WorkerStats getStats() const;
        std::string train();
};
extern std::map<std::string, Worker> workers;

std::string formatWorkers(bool includeTraining);

#endif