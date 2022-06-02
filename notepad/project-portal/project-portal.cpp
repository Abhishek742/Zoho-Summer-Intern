#include <bits/stdc++.h>
#include "../structure/notepad.pb.h"
#include "../version-control/version-control.cpp"
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
        for (const auto &entry : fs::directory_iterator(path))
        {
            projects.push_back(entry.path().filename().string());
        }
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
    void addLineContent(Content *content, string &line)
    {
        content->set_line(line);
    }
    bool isExistingFile()
    {
        for (int i = 0; i < projects.size(); i++)
        {
            if (currProjectName + ".txt" == projects[i])
                return true;
        }
        return false;
    }
    void createNewFile()
    {
        Project project;
        Operation op;
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

        // set project attributes
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
            addLineContent(op.add_contents(), line);
        }
        writeProject(project);

        // set operation attributes
        op.set_operationtype("add");
        op.set_startline(0);
        op.set_endline(project.contents_size() - 1);

        VersionControl vc(username, project.projectname());
        Versions v;
        vc.writeVersions(v);
        vc.addOperation(op);
        projects.push_back(project.projectname() + ".txt");
    }
    void listAllProjects()
    {
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

        Operation op;
        // set operation attributes
        op.set_operationtype("add");
        op.set_startline(project.contents_size());
        op.set_endline(project.contents_size());
        addLineContent(op.add_contents(), line);

        // add operation to version control
        VersionControl vc(username, project.projectname());
        vc.addOperation(op);
    }
    void update(Project &project)
    {
        Operation op;
        cout << "Enter the line numbers(range) to be updated, (i to i) for a single line : ";
        int start, end;
        cin >> start >> end;
        if (start <= 0 || end > project.contents_size() || start > end)
        {
            cout << "Invalid line numbers!!!\n";
            return;
        }
        start--;
        end--;
        for (int i = start; i <= end; i++)
        {
            cout << i + 1 << " ~ ";
            Content *content = project.mutable_contents(i);
            Content *oprContent = op.add_contents();
            oprContent->set_line(content->line());
            string line;
            getline(cin >> ws, line);
            content->set_line(line);
        }

        // set operation attributes
        op.set_operationtype("update");
        op.set_startline(start - 1);
        op.set_endline(end - 1);

        // add operation to version control
        VersionControl vc(username, project.projectname());
        vc.addOperation(op);
    }
    void remove(Project &project)
    {
        Operation op;
        cout << "Enter the line numbers(range) to be removed, (i to i) for a single line : ";
        int start, end, num;
        cin >> start >> end;
        if (start <= 0 || end > project.contents_size() || start > end)
        {
            cout << "Invalid line numbers!!!\n";
            return;
        }
        start--;
        end--;
        // num will have the number of elements to be removed from the start index
        if (start == end)
            num = 1;
        else
            num = end - start + 1;

        RepeatedPtrField<Content> *rep = project.mutable_contents();

        //set content for operation
        for (int i = start; i <= end; i++)
        {
            const Content content = project.contents(i);
            Content *oprContent = op.add_contents();
            oprContent->set_line(content.line());
        }

        // set operation attributes
        op.set_operationtype("remove");
        op.set_startline(start - 1);
        op.set_endline(end - 1);

        // add operation to version control
        VersionControl vc(username, project.projectname());
        vc.addOperation(op);


        // delete elements from start to start + num - 1 index
        rep->DeleteSubrange(start, num);
    }

    void display(Project &project)
    {
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