#include "machine.hpp"

Machine::Machine(std::string name, float price, float cost_per_day, float base_return_per_day, 
                float failure_probability, int repair_time, float repair_cost)
        :Unit{name, cost_per_day, base_return_per_day}
{ 
    m_price = price;
    m_failure_probability = failure_probability;
    m_repair_time = repair_time;
    m_repair_cost = repair_cost;
}

float Machine::getPrice() const{
    return m_price;
}

// since getReturnPerDay() is called once every time passOneDay() is called, i decrement days_until_repair in this func
float Machine:: getReturnPerDay() {
    m_days_until_repair--; // !!!! might need to post increment this in the if block below !!!!
    // is this how i check if the machine is broken or not? there isn't any bool or sth
    if (m_days_until_repair > 0) {
        return 0;
    }
    else if ((std::rand() % RAND_MAX) > m_failure_probability) {
        m_days_until_repair = m_repair_time; // this will disable the machine for repair_time days (the if block above)
        return -m_repair_cost;
    }
    else {
        return Unit::getReturnPerDay();
    }
}