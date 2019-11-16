#include"header.hpp"
LabBase::LabBase(int _argc, char* _argv[]) : argc(_argc), argv(_argv)
{
}

LabBase::~LabBase()
{
}

unordered_map<int, LabBase*> LabBase::instances;
