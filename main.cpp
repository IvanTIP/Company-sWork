#include <iostream>
#include <vector>
#include <ctime>

class Human {
private:
    std::string name = "unknown";
public:
    std::string getName () {
        return name;
    }

    void setName (std::string name) {
        this->name = name;
    }
};

class Worker : public Human {
private:
    char typeTask = '0';
public:
    void setTask (char inTask) {
        typeTask = inTask;
        std::cout << "      " << getName() << " took task #" << typeTask << std::endl;
    }

    void getStatus () {
        if (typeTask == '0') {
            std::cout << "      " << getName() << " is free" << std::endl;
        } else {
            std::cout << "      " << getName() << " is already performing task #" << typeTask << std::endl;
        }

    }

    char getTypeTask () {
        return typeTask;
    }
};

class Manager : public Human {
private:
    int num;
    int task;
public:
    Manager (int inI) : num(inI + 1) {

    }

    int setTask (int inTask, unsigned long long workersCount) {
        task = inTask;
        std::cout << "TEAM #" << num << std::endl;
        std::cout << "  " << getName() << " took task #" << task << std::endl;
        int hash = task + num;
        std::srand(hash);
        int taskCount = std::rand() % workersCount + 1;
        return taskCount;
    }
};

class Team {
private:
    int membersCount;
    Manager* manager = nullptr;
    std::vector <Worker*> workers;
    int taskCount;
    bool fullEmployment = false;
public:
    Team (int inMembersCount, int inI) : membersCount(inMembersCount) {
        manager = new Manager(inI);
        for (int i = 0;i < membersCount - 1;i++) {
            workers.push_back(new Worker);
        }
    }

    void setName (int inI) {
        manager->setName("Manager" + std::to_string(inI + 1));
        for (int i = 0;i < membersCount - 1;i++) {
            workers[i]->setName("Worker" + std::to_string(i + 1));
        }
    }

    void setTask (int inTask, int inI) {
        taskCount = manager->setTask(inTask, workers.size());
        std::cout << "  " << manager->getName() << " has identified " << taskCount <<  " task(s)" << std::endl;
        settingTasksForWorkers(inI);
        setEmployment();
    }

    int setEmployment () {
        for (int i = 0;i < workers.size();i++) {
            if (workers[i]->getTypeTask() == '0') {
                fullEmployment = false;
                return 0;
            }
        }
        fullEmployment = true;
        return 1;
    }

    bool getEmployment () {
        return fullEmployment;
    }

    void settingTasksForWorkers (int inI) {
        std::srand(std::time(nullptr) + inI);
        for (int i = 0;i < workers.size();i++) {
            char task;
            if (taskCount != 0 && workers[i]->getTypeTask() == '0') {
                int num = std::rand() % 3;
                if (num == 0) {
                    task = 'A';
                } else if (num == 1) {
                    task = 'B';
                } else if (num == 2) {
                    task = 'C';
                }
                workers[i]->setTask(task);
                taskCount--;
            } else {
                workers[i]->getStatus();
            }
        }
        std::cout << std::endl;
    }

    void clear () {
        delete manager;
        for (int i = 0;i < membersCount - 1;i++) {
            delete workers[i];
        }
    }
};

class Leader : public Human {
private:
    int task = 0;
public:
    void setTasks (int inTask) {
        task = inTask;
    }

    int getTask () {
        return task;
    }
};

class Company {
private:
    Leader* leader = nullptr;
    std::vector <Team*> teams;
public:
    Company () {
        leader = new Leader;
        leader->setName("Header");
    }

    void setTeam (int inI) {
        int membersCount;
        std::cout << "Enter the count of members of the team #" << inI + 1;
        std::cin >> membersCount;
        teams.push_back(new Team (membersCount, inI));
        teams[inI]->setName(inI);
    }

    void taskSent (int inTeamCount) {
        std::cout << leader->getName() << " sent the task #" << leader->getTask() << " for managers" << std::endl;
        for (int i = 0;i < inTeamCount;i++) {
            if (!teams[i]->getEmployment()) {
                teams[i]->setTask(leader->getTask(), i);
            }
        }
    }

    void createTasks () {
        int task;
        std::cout << "Enter the company leader's task:" << std::endl;
        std::cin >> task;
        leader->setTasks(task);
    }

    bool getEmployment () {
        for (int i = 0;i < teams.size();i++) {
            if (!teams[i]->getEmployment()) {
                return false;
            }
        }
        return true;
    }

    void clear () {
        delete leader;
        for (int i = 0;i < teams.size();i++) {
            teams[i]->clear();
            delete teams[i];
        }
    }
};

int main() {
    int teamCount;
    std::cout << "Enter the count of teams: ";
    std::cin >> teamCount;
    Company* company = new Company;
    for (int i = 0;i < teamCount;i++) {
        company->setTeam(i);
    }
    while (!company->getEmployment()) {
        company->createTasks();
        company->taskSent(teamCount);
    }
    std::cout << "All employees are busy";
    company->clear();
    delete company;
    return 0;
}
