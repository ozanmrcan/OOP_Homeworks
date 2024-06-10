#include "factory.hpp"

Factory::Factory(float capital) 
        :m_capital{capital}
{}

void Factory::addUnit(const Worker &rhs_worker) {
    m_workers.push_back(rhs_worker);
}

void Factory::addUnit(const Machine &rhs_machine) {
    m_machines.push_back(rhs_machine);
}

bool Factory::isBankrupt() const{
    return m_is_bankrupt;
}

float Factory::getCapital() const{
    return m_capital;
}

int Factory::getWorkerCount() const{
    return m_workers.size();
}

int Factory::getMachineCount() const{
    return m_machines.size();
}

int Factory::getHeadWorkerCount() const{
    return m_head_workers.size();
}

void Factory::passOneDay() {
    // daily costs and returns
    for (int i = 0; i < getWorkerCount(); i++) {
        m_capital += m_workers[i].getReturnPerDay();
        m_capital -= m_workers[i].getCostPerDay();        
    }
    for (HeadWorker hw : m_head_workers) {
        m_capital += hw.getReturnPerDay();
        m_capital -= hw.getCostPerDay();
    }
    for (Machine m : m_machines) {
        m_capital += m.getReturnPerDay();
        m_capital -= m.getCostPerDay();
    }
    
    // promotion of workers (promotion occurs the day after reaching 10 exp (ie 11th day), thus exp > 10)
    int exp;
    for (int i = 0; i < getWorkerCount(); i++) {
        exp = m_workers[i].getExperience(); 
        // promote to headworker
        if (exp > 10) {
            m_head_workers.push_back(HeadWorker(m_workers[i])); // add promoted headworker to container
            std::cout << m_head_workers.back().getName() << " is promoted\n";   
            m_workers.erase(m_workers.begin()+i); // remove worker object from container, essentially deleting them from system
        }    
    }
    // daily prompt
    std::cout << "[C: " << getCapital() << ", W: " << getWorkerCount() << " , M: " << getMachineCount() << ", HW: " << getHeadWorkerCount() << "]\n";
}