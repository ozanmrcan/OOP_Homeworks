// DO NOT MODIFY THIS FILE
#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include "factory.hpp"
#include <string>
#include <fstream> // i added this myself, tho it says dont add any new libraries but how am i supposed to do it without this?
#include <sstream> // edit: headerların birinde iostream falan var gerek olmayabilirmiş bunları eklememe, dönüp uğraşamam ama quiz için anlamı yok

class Simulation
{
private:
    Factory* m_factory;
    int m_total_days;

    std::vector<Worker> m_labor_market;
    std::vector<Machine> m_machines_market;

    Machine buyRandomMachine();
    Worker hireRandomWorker();
    
public:
    Simulation(Factory &factory, int total_days, std::string workers_list_path, std::string machines_list_path);

    void printWelcomeMessage() const;
    void run();
};


#endif // SIMULATION_HPP