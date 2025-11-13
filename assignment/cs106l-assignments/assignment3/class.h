#pragma once
#include <string>

class Cser {
public:
    Cser();
    Cser(std::string name, std::string job, int age);
    std::string getname() const;
    std::string getjob() const;
    int getage() const;

private:
    std::string name;
    std::string job;
    int age;
    void set_name(std::string name);
    void set_job(std::string job);
    void set_age(int age);
};

