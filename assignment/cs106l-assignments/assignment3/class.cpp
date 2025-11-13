#include "class.h"

Cser::Cser(): name("Boven Ding"), job("C plus plus"), age(20) {}

Cser::Cser(std::string name, std::string job, int age) {
    set_name(name);
    set_job(job);
    set_age(age);
}

std::string Cser::getname() const {
    return name;
}

std::string Cser::getjob() const {
    return job;
}

int Cser::getage() const {
    return age;
}

void Cser::set_name(std::string name) {
    this->name = name;
}

void Cser::set_job(std::string job) {
    this->job = job;
}

void Cser::set_age(int age) {
    this->age = age;
}

