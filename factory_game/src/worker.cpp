#include "worker.hpp"



Worker::Worker(std::string name, float cost_per_day, float base_return_per_day)
        :Unit{name, cost_per_day, base_return_per_day}, m_experience{0}
{ }

void Worker::increaseHeadWorkerCount()
{
        m_num_head_workers++;
}

int Worker::getExperience() const{
        return m_experience;
}

// modified return per day function
float Worker::getReturnPerDay() {
        return Unit::getReturnPerDay() + 2 * m_experience++ + 3 * m_num_head_workers; 
                                // increments experience after return
}