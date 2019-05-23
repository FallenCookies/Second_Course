#include <iostream>
#include <map>
#include <vector>
#include <tuple>
using namespace std;



enum class TaskStatus {
    NEW,          // новая
    IN_PROGRESS,  // в разработке
    TESTING,      // на тестировании
    DONE          // завершена
};
using TasksInfo = map<TaskStatus, int>;
class TeamTasks {
public:
    // Получить статистику по статусам задач конкретного разработчика
    const TasksInfo& GetPersonTasksInfo(const string& person) const{
        return Dev_list.at(person);
    }

    // Добавить новую задачу (в статусе NEW) для конкретного разработчитка
    void ClearTask_list(TasksInfo& task_info){
        try {
            if (task_info.at(TaskStatus::NEW) == 0)
                task_info.erase(TaskStatus::NEW);
            if (task_info.at(TaskStatus::IN_PROGRESS) == 0)
                task_info.erase(TaskStatus::IN_PROGRESS);
            if (task_info.at(TaskStatus::TESTING) == 0)
                task_info.erase(TaskStatus::TESTING);
            if (task_info.at(TaskStatus::DONE) == 0)
                task_info.erase(TaskStatus::DONE);
        }catch(exception& e){

        }
    }
    void AddNewTask(const string& person){
        Dev_list[person][TaskStatus::NEW]+=1;
        ClearTask_list(Dev_list.at(person));
    }

    // Обновить статусы по данному количеству задач конкретного разработчика,
    // подробности см. ниже
    tuple<TasksInfo, TasksInfo> PerformPersonTasks(
            const string& person, int task_count){
        TasksInfo updating,Updated,untouched;
        if(Dev_list.count(person)>0)
            updating=Dev_list.at(person);
        if(Dev_list.count(person)>0)
            untouched=Dev_list.at(person);
        int TaskSum=0;
        TaskSum=updating[TaskStatus::NEW]+updating[TaskStatus::IN_PROGRESS]+updating[TaskStatus::TESTING];
        if(TaskSum<task_count)
            task_count=TaskSum;
        while (untouched[TaskStatus::NEW]>0 && task_count>0){
            updating[TaskStatus::NEW]-=1;
            updating[TaskStatus::IN_PROGRESS]+=1;
            Updated[TaskStatus::IN_PROGRESS]+=1;
            if(untouched[TaskStatus::NEW]>0)
                untouched[TaskStatus::NEW]-=1;
            task_count--;
        }
        while (untouched[TaskStatus::IN_PROGRESS]>0 && task_count>0){
            updating[TaskStatus::IN_PROGRESS]-=1;
            updating[TaskStatus::TESTING]+=1;
            Updated[TaskStatus::TESTING]+=1;
            if(untouched[TaskStatus::IN_PROGRESS]>0)
                untouched[TaskStatus::IN_PROGRESS]-=1;
            task_count--;
        }
        while (untouched[TaskStatus::TESTING]>0 && task_count>0){
            updating[TaskStatus::TESTING]-=1;
            updating[TaskStatus::DONE]+=1;
            Updated[TaskStatus::DONE]+=1;
            if(untouched[TaskStatus::TESTING]>0)
                untouched[TaskStatus::TESTING]-=1;
            task_count--;
        }

        ClearTask_list(Updated);
        ClearTask_list(updating);
        if(Dev_list.count(person)>0)
            Dev_list.at(person)=updating;
        untouched[TaskStatus::DONE]=0;
        ClearTask_list(untouched);
        return make_tuple(Updated,untouched);

    };

private:
    map<string,TasksInfo> Dev_list;
};
void PrintTasksInfo(TasksInfo tasks_info) {
    cout <<"NEW: " <<tasks_info[TaskStatus::NEW] << "," <<
         "IN_PROGRESS: " << tasks_info[TaskStatus::IN_PROGRESS] << ", " <<
         "TESTING: " << tasks_info[TaskStatus::TESTING] << ", " <<
         "DONE: " << tasks_info[TaskStatus::DONE] << endl;
}
int main() {
    TeamTasks tasks;
    for (int i = 0; i < 1; ++i) {
        tasks.AddNewTask("Ivan");
    }
    TasksInfo updated_tasks, untouched_tasks;
    tie(updated_tasks, untouched_tasks) =
            tasks.PerformPersonTasks("Ivan", 3);
    cout << "Ivan's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));
    for (int i = 0; i < 1; ++i) {
        tasks.AddNewTask("Ivan");
    }
    tie(updated_tasks, untouched_tasks) =
            tasks.PerformPersonTasks("Ivan", 2);
    cout << "Ivan's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));
    for (int i = 0; i < 1; ++i) {
        tasks.AddNewTask("Ivan");
    }
    cout << "Ivan's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));
    tie(updated_tasks, untouched_tasks) =
            tasks.PerformPersonTasks("Ivan", 3);
    cout << "Ivan's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));
    return 0;
}