//This program track and manages your task. The user may able to :
//Add, Update, and Delete tasks
//Mark a task as in progress or done
//list all tasks, tasks that are done, tasks that are not done, and tasks in progress


#include <iostream>
#include <ctime>
#include <string>
#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;

enum Status{
    todo,in_progress, done
};

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

        existing["task"].push_back(o);
        existing["next_id"] = next_id+1;

        std::ofstream outfile("storage.json");
        outfile<< std::setw(4)<<existing<<std::endl;

    }
    
    void listTask()
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

        int lister_size = lister["task"].size();
        for (int  i = 0; i < lister_size; i++)
        {
            std::cout <<lister["task"].at(i).at("Id")<<'.'<<lister["task"].at(i).at("Description") <<'\n';
        }
        
    }

};
int task::counter{0};
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

    if(std::string(argv[1]) == "list")
    {
        varTask.listTask();
        return 0;
    }

}
