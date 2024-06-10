#include "headworker.hpp"

HeadWorker::HeadWorker(Worker& worker) 
            :Worker{worker.getName(), worker.getCostPerDay(), worker.getReturnPerDay()}
{
    m_experience = worker.getExperience();
    increaseHeadWorkerCount();
}

float HeadWorker::getReturnPerDay() {
    return Unit::getReturnPerDay() + (5 * m_experience++);
}