//This program track and manages your task. The user may able to :
//Add, Update, and Delete tasks
//Mark a task as in progress or done
//list all tasks, tasks that are done, tasks that are not done, and tasks in progress


#include <iostream>
#include <ctime>
#include <string>
#include <json.hpp>
#include <fstream>
#include <sstream>  //for std::stringstream

using json = nlohmann::json;

namespace utils{
    void printError(const std::string &msg){
        std::cerr << "[ERROR]" << msg << std::endl;
    }
}

enum Status{
    todo,in_progress, done
};

int converStringToNumber(char* argv[]);
Status stringToStatus(const std::string& str);
std::string statusToString(const Status sta);

class task 
{
public:
    int m_id{};
    static int counter;
    std::string m_description{};    
    Status m_status{};
    time_t m_createdAt{};
    time_t m_updatedAt{}; 

    void enterTask(int argc,char* argv[])
        {
            m_id = ++counter;
            m_status = todo;
            m_createdAt = std::time(nullptr);
            m_updatedAt = std::time(nullptr);
            m_description.clear();

            for(int i = 2; i< argc; ++i)
                {
                    m_description += argv[i];
                    if(i < argc -1 )
                    m_description += " ";
                }
        }
        
    void addTask() const
    {
        json existing = json::object({{"task",json::array({})},{"next_id",1}});

        std::ifstream infile("storage.json");
        //To check whether the "storage.json" is empty if not store the objects to the json exisiting array
        if(infile.is_open() && infile.peek()!=std::ifstream::traits_type::eof())
        {
            infile >> existing;
        }
        infile.close();

        int next_id = existing["next_id"];

        json::object_t o;
        o["Id"] = next_id;
        o["Description"] = m_description;
        o["CreateAt"] = ctime(&m_createdAt);
        o["UpdatedAt"] = ctime(&m_updatedAt);
        o["Status"] = statusToString(m_status);

        //to output task added msg with it's index
        std::cout << "Task added successfully (ID: " << next_id << ")\n";

        existing["task"].push_back(o);
        existing["next_id"] = next_id+1;

        std::ofstream outfile("storage.json");
        outfile<< std::setw(4)<<existing<<std::endl;

    }

    void updateTask(int argc, char *argv[])
    {
        if(argc == 2){
            std::cerr << "Please use update feature properly\n";
            return;
        }

        int id_number = converStringToNumber(argv);
        json updater;
        std::ifstream infile("storage.json");
        if(infile.is_open() && infile.peek()!=std::ifstream::traits_type::eof())
        {
           infile >> updater;
        }else
        {
            std::cerr << "No existing list found.\nUse 'task-cli add <task>' to add task\n";
            return;
        }

        infile.close();

        //check wheather the give Id exit or not
        if(!doesIdExist(id_number))
        {
            utils::printError("The given Id doesn't exit.");
            return;
        }

        std::string description;
        time_t updatedtime;
        for(int i = 3; i< argc; ++i)
        {
            description += argv[i];
            if(i < argc -1 )
                description += " ";
        }

        updatedtime = std::time(nullptr);
        int updater_size = updater["task"].size();
        for(int i = 0; i< updater_size; i++)
        {
            if(updater["task"].at(i).at("Id") == id_number)
            {
                updater["task"].at(i).at("Description") = description;
                updater["task"].at(i).at("UpdatedAt") = ctime(&updatedtime);
                break;
            }
        }

        std::ofstream outfile {"storage.json"};
        outfile <<std::setw(4)<< updater;

    }

    void listTask(int argc, char* argv[])
    {
        json lister;
        std::ifstream infile("storage.json");
        
        if(infile.is_open() && infile.peek()!=std::ifstream::traits_type::eof())
        {
           infile >> lister;
        }else
        {
            std::cerr << "No existing list found.\nUse 'task-cli add <task>' to add task\n";
            return;
        }

        infile.close();

        if(lister["task"].empty())
        {
            utils::printError("No existing task found.\nUse 'task-cli add <task>' to add task");
            return;
        }

        int lister_size = lister["task"].size();
        for (int  i = 0; i < lister_size; i++)
        {
            auto strStatus = lister["task"].at(i).at("Status");

            if(argc == 2)
                std::cout <<lister["task"].at(i).at("Id")<<'.'<<lister["task"].at(i).at("Description") <<'\n';
            else if(std::string(argv[2]) == "done" && strStatus == statusToString(done))
                std::cout <<lister["task"].at(i).at("Id")<<'.'<<lister["task"].at(i).at("Description") <<'\n';
            else if(std::string(argv[2]) == "todo" && strStatus == statusToString(todo))
                std::cout <<lister["task"].at(i).at("Id")<<'.'<<lister["task"].at(i).at("Description") <<'\n';
            else if(std::string(argv[2]) == "in-progress" && strStatus == statusToString(in_progress))
                std::cout <<lister["task"].at(i).at("Id")<<'.'<<lister["task"].at(i).at("Description") <<'\n';
        }
        
    }

    void markTask(int argc, char* argv[])
    {
        (void)argc;
        std::ifstream infile{"storage.json"};
        json marker;

        if(infile.is_open() && infile.peek()!=std::ifstream::traits_type::eof())
        {
           infile >> marker;
        }else
        {
            std::cerr << "No existing list found.\nUse 'task-cli add <task>' to add task\n";
            return;
        }
        infile.close();

        int id_number = converStringToNumber(argv);

        if(!doesIdExist(id_number))
        {
            utils::printError("The given Id doesn't exist.");
            return;
        }
        
        int marker_size = marker["task"].size();
        time_t timestamp = std::time(nullptr);

        for(int i = 0; i< marker_size; i++)
        {
            if(marker["task"].at(i).at("Id") == id_number)
            {
                if(std::string(argv[1])=="mark-done")
                {
                    marker["task"].at(i).at("Status") = statusToString(done);
                }
                if(std::string(argv[1])== "mark-inprogress")
                {
                    marker["task"].at(i).at("Status") = statusToString(in_progress);
                }
                marker["task"].at(i).at("UpdatedAt") = ctime(&timestamp);
                break;
            }
        }

        std::ofstream outfile {"storage.json"};
        outfile <<std::setw(4)<< marker;
    }
    
    void deleteTask(int argc, char* argv[])
    {
        if(argc == 2){
            std::cerr << "Please use delete feature properly\n";
            return;
        }if(argc > 3){
            std::cerr << "Only one Key accepted at a time\n";
            return;
        }

        int id_number = converStringToNumber(argv);

        json deleter;
        std::ifstream infile("storage.json");
        if(infile.is_open() && infile.peek()!=std::ifstream::traits_type::eof())
        {
           infile >> deleter;
        }else
        {
            std::cerr << "No existing list found.\nUse 'task-cli add <task>' to add task\n";
            return;
        }
        infile.close();

        if(!doesIdExist(id_number))
        {
            utils::printError("The given Id doesn't exist.");
            return;
        }

        int deleter_size = deleter["task"].size();
        for(int i = 0; i< deleter_size; i++)
        {
            if(deleter["task"].at(i).at("Id") == id_number)
            {
                deleter["task"].erase(i);
                break;
            }
        }

        std::ofstream outfile {"storage.json"};
        outfile <<std::setw(4)<< deleter;




    }
    bool doesIdExist(int id)
    {
        json checker;
        std::ifstream infile("storage.json");
        if(infile.is_open() && infile.peek()!=std::ifstream::traits_type::eof())
        {
           infile >> checker;
        }else
        {
            return false;
        }
        infile.close();

        int checker_size = checker["task"].size();
        for (int i = 0; i < checker_size; i++)
        {
            if(id == checker["task"].at(i).at("Id"))
                return true;
        }

        return false;
    }

};
int task::counter{0};

Status stringToStatus(const std::string& str)
{
    if(str == "To Do") return todo;
    if(str == "In Progress") return in_progress;
    if(str == "Done") return done;

    return todo;
}
std::string statusToString(const Status sta)
{
    switch (sta)
    {
    case todo: return "To Do";
    case in_progress: return "In Progress";
    case done: return "Done";
    default: return "Unknown";
    }
}
int converStringToNumber(char * argv[])
{
    int myint{};
    std::stringstream convert{ argv[2] };
    if(!(convert >> myint))
        myint = 0;          //if conversion fails, set myint to a default value
    return myint;
}

int main(int argc, char *argv[])
{
    if(argc<2)
    {
        std::cerr<<"Usage: ./task add <description>\n";
        return 1;
    }

    task varTask;

    if(std::string(argv[1]) == "add")
    {
        varTask.enterTask(argc,argv);
        varTask.addTask();
    }

    if(std::string(argv[1]) == "update")
    {
        varTask.updateTask(argc,argv);
    }

    if(std::string(argv[1]) == "list")
    {
        varTask.listTask(argc,argv);
        return 0;
    }

    if(std::string(argv[1]) == "delete")
    {
        varTask.deleteTask(argc,argv);
    }
    
    if(std::string(argv[1]) == "mark-done" || std::string(argv[1]) == "mark-inprogress")
    {
        varTask.markTask(argc,argv);
    }

}
