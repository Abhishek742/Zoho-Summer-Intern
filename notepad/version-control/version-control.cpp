#include <bits/stdc++.h>
#include "../structure/notepad.pb.h"
using namespace std;
using namespace google::protobuf;

namespace fs = std::filesystem;

class VersionControl
{
    string username;
    string path;
    string projectID;

public:
    VersionControl() {}
    VersionControl(string username, string projectID)
    {
        this->username = username;
        this->projectID = projectID;
        this->path = "./version-control/versions/" + this->username + "/";
        if (!fs::exists(path))
        {
            fs::create_directory(path);
        }
    }
    void readVersions(Versions &versions)
    {
        // read versions from file
        ifstream inStream;
        inStream.open(path + this->projectID + "_versions.txt", ios::in);
        versions.ParseFromIstream(&inStream);
        inStream.close();
    }
    void writeVersions(Versions &versions)
    {
        // write versions into file
        ofstream outStream;
        outStream.open(path + this->projectID + "_versions.txt", ios::out);
        versions.SerializeToOstream(&outStream);
        outStream.close();
    }

    void addOperation(Operation &operation)
    {
        Versions versions;
        versions.set_projectid(this->projectID);
        readVersions(versions);
        int size = versions.versions_size();
        // if there is no version at start or there are 5 operations in current version, create new version
        if (size == 0 || versions.versions(size - 1).operation_size() == 5)
        {
            Version *v = versions.add_versions();

            // set version properties
            v->set_versionid("V_" + to_string(size + 1));

            // set version created time
            time_t t = time(0);
            string dt = string(ctime(&t));
            v->set_createdtime(dt);

            Operation *opr = v->add_operation();
            *opr = operation;
        }
        else
        {
            Version *v = versions.mutable_versions(size - 1);
            Operation *opr = v->add_operation();
            *opr = operation;
        }
        writeVersions(versions);
    }
    void revertAdd(Project &currProject, Operation opr)
    {
        int range;
        if (opr.startline() == opr.endline())
            range = 1;
        else
            range = opr.endline() - opr.startline() + 1;

        RepeatedPtrField<Content> *rep = currProject.mutable_contents();

        // delete the lines that were added
        rep->DeleteSubrange(opr.startline(), range);
    }
    void revertUpdate(Project &currProject, Operation opr)
    {
        for (int i = opr.startline(), j = 0; i <= opr.endline(); i++, j++)
        {
            Content *prContent = currProject.mutable_contents(i);
            prContent->set_line(opr.contents(j).line());
        }
    }
    void revertRemove(Project &currProject, Operation opr)
    {
        Contents tempContents;
        // opr contents to tempContents
        for (int i = 0; i < opr.contents_size(); i++)
        {
            const Content copyContent = opr.contents(i);
            Content *cont = tempContents.add_contents();
            cont->set_line(copyContent.line());
        }

        // currProject contents to tempContents
        for (int i = opr.startline(); i < currProject.contents_size(); i++)
        {
            const Content copyContent = currProject.contents(i);
            Content *cont = tempContents.add_contents();
            cont->set_line(copyContent.line());
        }

        //delete copied elements
        RepeatedPtrField<Content> *rep = currProject.mutable_contents();
        rep->DeleteSubrange(opr.startline(),currProject.contents_size() - opr.startline());

        for(int i = 0;i<tempContents.contents_size();i++){
            Content *cont = currProject.add_contents();
            cont->set_line(tempContents.contents(i).line());
        }
    }
    void displayVersions()
    {
        system("clear");
        Versions versions;
        readVersions(versions);

        cout << "Versions : \n";
        for (int i = 0; i < versions.versions_size(); i++)
        {
            // get a single version from array of versions
            const Version &version = versions.versions(i);
            cout << "Version ID : " << version.versionid() << "\n";
            cout << "Created Time : " << version.createdtime() << "\n";

            for (int j = 0; j < version.operation_size(); j++)
            {
                // get a single operation from multiple operations
                const Operation &opr = version.operation(j);
                cout << "Operation Type - " << opr.operationtype() << "\n";
                cout << "Operation done from  - " << opr.startline() + 1 << " to " << opr.endline() + 1 << "\n";
                cout << "Content : \n";
                for (int k = 0; k < opr.contents_size(); k++)
                {
                    const Content &content = opr.contents(k);
                    cout << content.line() << "\n";
                }
            }
        }
    }
    void revertVersion(Project &currProject)
    {
        Versions versions;
        readVersions(versions);
        int versionNum;
        cout << "Revert to Version Number : ";
        cin >> versionNum;
        versionNum--;
        bool flag = false;
        // go through all operations in reverse and invert them with respective functions
        for (int i = versions.versions_size() - 1; i > versionNum; i--)
        {
            const Version &version = versions.versions(i);

            for (int j = version.operation_size() - 1; j >= 0; j--)
            {
                const Operation &opr = version.operation(j);
                if (opr.operationtype() == "add")
                {
                    revertAdd(currProject, opr);
                }
                else if (opr.operationtype() == "update")
                {
                    revertUpdate(currProject, opr);
                }
                else if (opr.operationtype() == "remove")
                {
                    revertRemove(currProject, opr);
                }
                else
                {
                    continue;
                }
            }
            RepeatedPtrField<Version> *rep = versions.mutable_versions();
            rep->DeleteSubrange(versions.versions_size() - 1, 1);
        }
        writeVersions(versions);
    }
    void versionMenu(Project &currProject)
    {
        int choice;
        while (1)
        {
            system("clear");
            cout << "Version Menu \n";
            cout << "1)Display Versions\n2)Revert Version\n3)Return\n";
            cin >> choice;
            switch (choice)
            {
            case 1:
                this->displayVersions();
                break;
            case 2:
                this->revertVersion(currProject);
                break;
            case 3:
                return;
            default:
                break;
            }
            cout<<"\nEnter any character to continue : ";
            string ch;
            getline(cin>>ws,ch);
        }
    }
};