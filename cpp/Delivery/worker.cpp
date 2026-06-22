#include <iostream>
#include <map>

#include "worker.hpp"
#include "utils.hpp"

Worker::Worker(int workerType) {
    type = static_cast<WorkerType>(workerType);

    WorkerStats workerStats = WorkerStatData[(size_t)type];
    id = get_random_string(6);
    wage = workerStats.startingWage;
    level = 1;
    usedSpecialty = false;
}

std::string Worker::getId() const {
    return id;
}
double Worker::getWage() const {
    return wage;
}
int Worker::getLevel() const {
    return level;
}
WorkerType Worker::getType() const {
    return type;
}
WorkerStats Worker::getStats() const {
    return WorkerStatData[(size_t)type];
}
std::string Worker::train() {
    WorkerStats workerStats = getStats();
    if(depotMoney < (workerStats.startingWage * (level + 1))) {
        return "Not enough money to train.";
    }
    if(level >= 5) {
        return "Cant train workers above 5 levels.";
    }

    depotMoney -= (workerStats.startingWage * (level + 1));
    wage += 2.5;
    level++;

    return "Trained worker " + id + ".";
}

std::map<std::string, Worker> workers;
std::string formatWorkers(bool includeTraining) {
    std::string workerString = "";
    for(auto worker : workers) {
        Worker& workerData = worker.second;

        workerString += "(" + workerData.getStats().name + ") " + workerData.getId() + " - " + toFixed(workerData.getWage(), 2) + " $/day - Level " + std::to_string(workerData.getLevel()) + "\n";
    }

    return workerString;
}