#include "simulation.hpp"
using std::cout, std::cin, std::endl;

Simulation::Simulation(Factory &factory, int total_days, std::string workers_list_path, std::string machines_list_path) 
            :m_factory{&factory}, m_total_days{total_days} 
{

    // add workers to vector
    std::fstream worker_file(workers_list_path);
    std::string line = "";
    getline(worker_file, line); //skips first line

    std::string w_name, w_str_daily_cost, w_str_daily_return;
    float w_daily_cost, w_daily_return;
    while(getline(worker_file, line)) {
        std::stringstream w_row(line);

        // place name, cost and return to variables
        getline(w_row, w_name, ' ');

        getline(w_row, w_str_daily_cost, ' ');
        w_daily_cost = std::stof(w_str_daily_cost);

        getline(w_row, w_str_daily_return, ' ');
        w_daily_return = std::stof(w_str_daily_return);

        m_labor_market.push_back(Worker(w_name, w_daily_cost, w_daily_return)); //add the worker to vector
    }

    // add machines to vector
    std::fstream machine_file(machines_list_path);
    line = "";
    getline(machine_file, line); //skips first line

    std::string m_name, m_str_price, m_str_daily_cost, m_str_daily_return, m_str_fail_prob, m_str_repair_cost, m_str_repair_time;
    float m_price, m_daily_cost, m_daily_return, m_fail_prob, m_repair_cost, m_repair_time;
    while(getline(machine_file, line)) {
        std::stringstream m_row(line);

        getline(m_row, m_name, ' ');

        getline(m_row, m_str_price, ' ');
        m_price = std::stof(m_str_price);

        getline(m_row, m_str_daily_cost, ' ');
        m_daily_cost = std::stof(m_str_daily_cost);

        getline(m_row, m_str_daily_return, ' ');
        m_daily_return = std::stof(m_str_daily_return);

        getline(m_row, m_str_fail_prob, ' ');
        m_fail_prob = std::stof(m_str_fail_prob);

        getline(m_row, m_str_repair_cost, ' ');
        m_repair_cost = std::stof(m_str_repair_cost);

        getline(m_row, m_str_repair_time, ' ');
        m_repair_time = std::stof(m_str_repair_time);

        m_machines_market.push_back(Machine(m_name, m_price, m_daily_cost, m_daily_return, m_fail_prob, m_repair_cost, m_repair_time)); 
    }
}

void Simulation::printWelcomeMessage() const
{
    cout << "Welcome to the Car Factory!" << endl;
    cout << "You have " << m_total_days << " days to make as much money as possible" << endl;
    cout << "You can add workers, machines, and fast forward days" << endl;

    cout << "Available commands:" << endl;
    cout << "    wX: adds X workers" << endl;
    cout << "    mX: adds X machines" << endl;
    cout << "    pX: passes X days" << endl;
    cout << "    q: exit the game properly" << endl;
}

Machine Simulation::buyRandomMachine() {
    int random_index = rand() % m_machines_market.size();
    Machine new_machine = m_machines_market[random_index];
    cout << new_machine.getName() << " is bought\n";
    m_machines_market.erase(m_machines_market.begin()+random_index);    // remove bought machine from market
    return new_machine;  
}

Worker Simulation::hireRandomWorker() {
    int random_index = rand() % m_labor_market.size();
    Worker new_worker = m_labor_market[random_index];
    cout << new_worker.getName() << " is bought\n";
    m_labor_market.erase(m_labor_market.begin()+random_index);          // remove hired worker from linkedin xd
    return new_worker;
}

void Simulation::run() {

    int day_counter = 1;
    int starting_capital = m_factory->getCapital(); // to calculate net earning
    bool game_continues = true;

    while(game_continues) {
        std::string command;
        cout << "Enter command: ";
        cin >> command;
        // <name> hired / bought / promoted prompts are handled by corresponding methods

        std::string letter, number;
        letter = command[0];
        number = command.substr(1);
        
        if (letter == "w") {
            int workers_hired = std::stoi(number);
            for (int i = 0; i < workers_hired; i++) {
                Worker new_worker = hireRandomWorker();
                m_factory->addUnit(new_worker);
            }
        }

        else if (letter == "m") {
            int machines_bought = std::stoi(number);
            for (int i = 0; i < machines_bought; i++) {
                Machine new_machine = buyRandomMachine();
                m_factory->addUnit(new_machine);
            }
        }

        else if (letter == "p") {
            int days_passed = std::stoi(number);
            for (int i = 0; i < days_passed; i++) {
                cout << "--- Day: " << day_counter << "\n";
                m_factory->passOneDay();
                day_counter++;
                if (m_factory->getCapital() <= 0) {
                    cout << "You went bankrupt!\n";
                    game_continues = false;
                }
                if (day_counter > 30) {
                    cout << "Congrats! You have earned " << m_factory->getCapital() - starting_capital  << " in 30 days\n";
                    game_continues = false;     //this line makes while loop break after,
                    break;                      //breaking from the inner for loop with this line
                }
            }
        }

        else { // q or bad input // there is no test case for bad inputs so i default to q
            cout << "Congrats! You have earned " << m_factory->getCapital() - starting_capital  << " in 30 days"; //
            game_continues = false;
        }
    }
}