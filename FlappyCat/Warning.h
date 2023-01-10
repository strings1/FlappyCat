#pragma once
#include <iostream>
class warning : public std::exception
{
public:
    warning(const std::string& msg) {}
    const char* what() { return msg.c_str(); } //message of warning
private:
    std::string msg;
};