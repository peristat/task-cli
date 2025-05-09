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
    void printTask() const
    {
        json o;
        o["Id"] = m_id;
        o["Description"] = m_description;
        o["CreateAt"] = ctime(&m_createdAt);
        o["UpdatedAt"] = ctime(&m_updatedAt);

        json existing = json::array();
        std::ifstream infile("storage.json");
        //To check whether the "storage.json" is empty if not store the objects to the json exisiting array
        if(infile.is_open() && infile.peek()!=std::ifstream::traits_type::eof())
        {
            infile >> existing;
            // if(!existing.is_array())
            // {
            //     json temp = existing;
            //     existing = json::array();
            //     existing.push_back(temp);
            // }
        }
        infile.close();

        existing.push_back(o);
        std::ofstream outfile("storage.json");
        outfile<< std::setw(4)<<existing<<std::endl;

        // std::cout << "Id: "<<m_id<<std::endl;
        // std::cout << "Description: "<<m_description<<std::endl;
        // std::cout << "Created At: "<<ctime(&m_createdAt)<<std::endl;
        // std::cout << "Updated At: "<<ctime(&m_updatedAt)<<std::endl;
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
    }
    varTask.printTask();
}
