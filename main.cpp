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
    char typeTask = 'a';
public:
    void setTask (char inTask) {
        typeTask = inTask;
        std::cout << "      " << getName() << " took task #" << typeTask << std::endl;
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
        std::cout << std::endl << "TEAM #" << num << std::endl;
        std::cout << "   " << getName() << " took task #" << task << std::endl;
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
    }

    void settingTasksForWorkers (int inI) {
        std::srand(std::time(nullptr) + inI);
        for (int i = 0;i < workers.size();i++) {
            char task;
            int num = std::rand() % 3;
            if (num == 0) {
                task = 'A';
            } else if (num == 1) {
                task = 'B';
            } else if (num == 2) {
                task = 'C';
            }
            workers[i]->setTask(task);
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
    std::vector<int> tasks;
public:
    void setTasks (int inTask) {
        tasks.push_back(inTask);
    }

    int taskSent () {
        int i = std::rand() % tasks.size();
        int task = tasks[i];
        tasks.erase(tasks.begin() + i);
        return task;
    }

    void clear (int inTeamCount) {

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

    void taskSend (int inTeamCount) {
        for (int i = 0;i < inTeamCount;i++) {
            std::srand(std::time(nullptr));
            int task = leader->taskSent();
            std::cout << leader->getName() << " sent the task #" << task << " for team #" << i + 1 << std::endl;
            teams[i]->setTask(task, i);
        }
    }

    void createTasks (int inTeamCount) {
        for (int i = 0;i < inTeamCount;i++) {
            int task;
            std::cout << "Enter the company leader's task" << i + 1 << ":" << std::endl;
            std::cin >> task;
            leader->setTasks(task);
        }
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
    company->createTasks(teamCount);
    company->taskSend(teamCount);
    company->clear();
    delete company;
    return 0;
}
