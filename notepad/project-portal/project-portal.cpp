#include <bits/stdc++.h>
#include "../structure/notepad.pb.h"
#include<google/protobuf/repeated_ptr_field.h>
using namespace std;
using namespace google::protobuf;

namespace fs = std::filesystem;

class ProjectPortal
{
    string username;
    string path;
    vector<string> projects;
    string currProjectName;

public:
    ProjectPortal(string username)
    {
        this->username = username;
        this->path = "./project-portal/projects/" + this->username;
        if (!fs::exists(path))
        {
            fs::create_directory(path);
        }
    }
    void addLineContent(Content *content, string &line)
    {
        content->set_line(line);
    }
    bool isExistingFile()
    {
        for (int i = 0; i < projects.size(); i++)
        {
            if (currProjectName == projects[i])
                return true;
        }
        return false;
    }
    void readProject(Project &project)
    {
        // read the details of the current project
        ifstream inStream;
        inStream.open(path + '/' + currProjectName + ".txt", ios::in);
        project.ParseFromIstream(&inStream);
        inStream.close();
    }
    void writeProject(Project &project)
    {
        // write the project details into a file;
        ofstream outStream;
        outStream.open(path + '/' + currProjectName + ".txt", ios::out);
        project.SerializeToOstream(&outStream);
        outStream.close();
    }
    void createNewFile()
    {
        Project project;
        string p_id;
        while (1)
        {
            cout << "Enter the file name : ";
            getline(cin >> ws, this->currProjectName);
            if (!isExistingFile())
            {
                break;
            }
            cout << "File already Exists!!! Enter another filename!!!\n";
        }
        project.set_projectname(this->currProjectName);
        project.set_userid(this->username);
        p_id = project.userid() + '_' + project.projectname();
        project.set_projectid(p_id);
        cout << "Enter the contents to be written (use 'eof' to denote end of file)\n";
        string line = "";
        while (1)
        {
            getline(cin >> ws, line);
            if (line == "eof")
                break;
            addLineContent(project.add_contents(), line);
        }
        writeProject(project);
    }
    void listAllProjects()
    {
        for (const auto &entry : fs::directory_iterator(path))
        {
            projects.push_back(entry.path().filename().string());
        }
        for (int i = 0; i < projects.size(); i++)
        {
            cout << projects[i] << "  ";
        }
        cout << endl;
    }
    void append(Project &project)
    {
        // append a line at the end of file
        string line;
        cout << "Enter the line to append to file\n";
        getline(cin >> ws, line);
        addLineContent(project.add_contents(), line);
    }
    void update(Project &project)
    {
        cout << "Enter the line numbers(range) to be updated, (i to i) for a single line : ";
        int start, end;
        cin >> start >> end;
        if (start <= 0 || end > project.contents_size() || start > end)
        {
            cout << "Invalid line numbers!!!\n";
            return;
        }
        for (int i = start - 1; i < end; i++)
        {
            cout << i + 1 << " ~ ";
            Content *content = project.mutable_contents(i);
            string line;
            getline(cin >> ws, line);
            content->set_line(line);
        }
    }
    void remove(Project &project)
    {
        cout << "Enter the line numbers(range) to be removed, (i to i) for a single line : ";
        int start, end,num;
        cin >> start >> end;
        if (start <= 0 || end > project.contents_size() || start > end)
        {
            cout << "Invalid line numbers!!!\n";
            return;
        }
        start--;
        end--;
        //num will have the number of elements to be removed from the start index
        if(start == end) num = 1;
        else num = end - start + 1;
        
        RepeatedPtrField<Content> *rep = project.mutable_contents();

        //delete elements from start to start + num - 1 index
        rep->DeleteSubrange(start,num);
    }

    void display(Project &project)
    {
        // cout << "Project Details \n";
        // cout << "Project Name : " << project.projectname() << endl;
        // cout << "User Name : " << project.userid() << endl;
        cout << "Project contents : \n";
        for (int i = 0; i < project.contents_size(); i++)
        {
            const Content &content = project.contents(i);
            cout << i + 1 << " ~ " << content.line() << endl;
        }
    }
    void openProject()
    {
        cout << "Enter the name of the project : ";
        getline(cin >> ws, this->currProjectName);
        Project currProject;
        int choice;
        while (1)
        {
            // read the current state of the object before performing any operation
            readProject(currProject);
            cout << "1)Add\n2)Update\n3)Remove\n4)Display\n5)Exit";
            cin >> choice;
            switch (choice)
            {
            case 1:
                this->append(currProject);
                break;
            case 2:
                this->update(currProject);
                break;
            case 3:
                this->remove(currProject);
                break;
            case 4:
                this->display(currProject);
                break;
            case 5:
                return;
            }

            // write the current state of the object into its file
            writeProject(currProject);
        }
    }
    void versioning()
    {
    }
};