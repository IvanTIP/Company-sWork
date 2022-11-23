#include <iostream>

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
    Worker (int inI) {
        int num = std::rand() % 3;
        if (num == 0) {
            typeTask = 'A';
        } else if (num == 1) {
            typeTask = 'B';
        } else if (num == 2) {
            typeTask = 'C';
        }
        setName("Worker" + std::to_string(inI + 1));
    }

    void showTask () {
        std::cout << "      " << getName() << " took task #" << typeTask << std::endl;
    }
};

class Manager : public Human {
  private:
    int num;
    int task;
    int taskSum;
  public:
    Manager (int inTask, int inNum, int inMembersCount) : num(inNum + 1) {
        std::srand(inTask + num);
        taskSum = std::rand() % (inMembersCount + 1);
        task = inTask;
        setName("Manager" + std::to_string(inNum + 1));
    }

    int getTask () {
        return taskSum;
    }

    void showTask () {
        std::cout << getName() << " took task #" << task << std::endl;
    }
};

class Team {
  private:
    int memberCount;
    Manager* manager = nullptr;
    Worker** worker = nullptr;
  public:
    Team (int inMembersCount, int inTask, int inNum) : memberCount(inMembersCount) {
        std::cout << "TEAM #" << inNum + 1 << std::endl;
        manager = new Manager (inTask, inNum, inMembersCount);
        manager->showTask();
        std::cout << "  " << "Team #" << inNum + 1 << " performs " << manager->getTask() << " task(s)" << std::endl;
        worker = new Worker*[memberCount - 1];
        for (int i = 0;i < memberCount - 1;i++) {
            worker[i] = new Worker(i);
            worker[i]->showTask();
        }
    }

    void clear () {
        delete manager;
        for (int i = 0;i < memberCount - 1;i++) {
            delete worker[i];
        }
        delete[] worker;
    }
};

class Leader : public Human {
  private:
    Team** team = nullptr;
  public:
    Leader (int inTeamCount) {
        team = new Team*[inTeamCount];
    }

    void setTeam (int inI, int inMembersCount, int inTask) {
        team[inI] = new Team (inMembersCount, inTask, inI);
    }

    void clear (int inTeamCount) {
        for (int i = 0;i < inTeamCount;i++) {
            team[i]->clear();
            delete team[i];
        }
        delete[] team;
    }
};

int main() {
    int teamCount;
    std::cout << "Enter the count of teams: ";
    std::cin >> teamCount;
    Leader* leader = new Leader(teamCount);
    for (int i = 0;i < teamCount;i++) {
        int membersCount, task;
        std::cout << "Enter the count of members of team: ";
        std::cin >> membersCount;
        std::cout << "Enter the task: ";
        std::cin >> task;
        leader->setTeam(i, membersCount, task);
    }
    leader->clear(teamCount);
    delete leader;
    return 0;
}
