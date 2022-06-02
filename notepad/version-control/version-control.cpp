#include <bits/stdc++.h>
#include "../structure/notepad.pb.h"
using namespace std;
// using namespace google::protobuf;

namespace fs = std::filesystem;

class VersionControl
{
    string username;
    string path;
    string projectID;
    // Versions versions;
public:
    VersionControl() {}
    VersionControl(string username,string projectID)
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
        // read versions into file
        ifstream inStream;
        inStream.open(path + this->projectID + "_versions.txt", ios::in);
        versions.ParseFromIstream(&inStream);
        inStream.close();
    }
    void writeVersions(Versions &versions)
    {
        // write versions into file
        ofstream outStream;
        outStream.open(path + this->projectID+ "_versions.txt", ios::out);
        versions.SerializeToOstream(&outStream);
        outStream.close();
    }

    void addOperation(Operation &operation){
        Versions versions;
        versions.set_projectid(this->projectID);
        readVersions(versions);
        int size = versions.versions_size();
        //if there is no version at start or there are 5 operations in current version, create new version
        if(size == 0 || versions.versions(size - 1).operation_size() == 5){
            Version *v = versions.add_versions();
            
            //set version properties
            v->set_versionid("v" + size);
            time_t t = time(0);
            string dt = string(ctime(&t));
            v->set_createdtime(dt);
            Operation *opr = v->add_operation();
            *opr =  operation;
        }else{
            Version *v = versions.mutable_versions(size - 1);
            Operation *opr = v->add_operation();
            *opr = operation;
        }
        writeVersions(versions);
    }
};