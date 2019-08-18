#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;


// Перечислимый тип для статуса задачи
enum class TaskStatus {
    NEW,          // новая
    IN_PROGRESS,  // в разработке
    TESTING,      // на тестировании
    DONE          // завершена
};

// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;

// Принимаем словарь по значению, чтобы иметь возможность
// обращаться к отсутствующим ключам с помощью [] и получать 0,
// не меняя при этом исходный словарь
void PrintTasksInfo(TasksInfo tasks_info) {
    cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
        ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
        ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
        ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}


class TeamTasks {
public:
    // Получить статистику по статусам задач конкретного разработчика
    const TasksInfo& GetPersonTasksInfo(const string& person) const {
        return people.at(person);
    }
  
    // Добавить новую задачу (в статусе NEW) для конкретного разработчитка
    void AddNewTask(const string& person) {
        people[person][TaskStatus::NEW]++;
    }
  
    // Обновить статусы по данному количеству задач конкретного разработчика,
    // подробности см. ниже
    tuple<TasksInfo, TasksInfo> PerformPersonTasks(
        const string& person, int task_count) {
        TasksInfo updated;
        TasksInfo same;

        for (int en_int = (int)TaskStatus::NEW; en_int <= (int)TaskStatus::DONE; en_int++) {
            TaskStatus status = static_cast<TaskStatus>(en_int);
            same[status] = people[person][status];
        }

        for (int en_int = (int)TaskStatus::NEW; en_int < (int)TaskStatus::DONE; en_int++) {
            TaskStatus status = static_cast<TaskStatus>(en_int);
            TaskStatus next_st = static_cast<TaskStatus>(en_int+1);
            int new_tasks_count = people[person][status];
            if (new_tasks_count > 0) {
                if (new_tasks_count >= task_count) {
                    people[person][status] -= task_count;
                    updated[next_st] += task_count;
                    same[status] -= task_count;
                    task_count = 0;
                } else {
                    people[person][status] = 0;
                    updated[next_st] += new_tasks_count;
                    same[status] = 0;
                    task_count -= new_tasks_count;
                }
            }
            if (task_count <= 0) {
                break;
            }
        }
        for (int en_int = (int)TaskStatus::NEW; en_int <= (int)TaskStatus::DONE; en_int++) {
            TaskStatus status = static_cast<TaskStatus>(en_int);
            people[person][status] = same[status] + updated[status];
        }
        // delete all keys with zero values
        vector<int> updated_zeros;
        vector<int> same_zeros;
        for (int en_int = (int)TaskStatus::NEW; en_int <= (int)TaskStatus::DONE; en_int++) {
            TaskStatus status = static_cast<TaskStatus>(en_int);
            if (updated[status] == 0) {
                updated_zeros.push_back(en_int);
            }
            if (same[status] == 0) {
                same_zeros.push_back(en_int);
            }
        }
        for (auto key : updated_zeros) {
            updated.erase(static_cast<TaskStatus>(key));
        }
        for (auto key : same_zeros) {
            same.erase(static_cast<TaskStatus>(key));
        }
        same.erase(TaskStatus::DONE);
        return tie(updated, same);
    }
private:
    map<string, TasksInfo> people;
};


int main() {
    TeamTasks tasks;
    tasks.AddNewTask("Ilia");
    for (int i = 0; i < 3; ++i) {
        tasks.AddNewTask("Ivan");
    }
    cout << "Ilia's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));
    cout << "Ivan's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));
  
    TasksInfo updated_tasks, untouched_tasks;
  
    tie(updated_tasks, untouched_tasks) =
        tasks.PerformPersonTasks("Ivan", 2);
    cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);
  
    tie(updated_tasks, untouched_tasks) =
          tasks.PerformPersonTasks("Ivan", 2);
    cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);

    return 0;
}
