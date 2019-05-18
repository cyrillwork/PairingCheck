#ifndef CONFIGFILEPARSER_H
#define CONFIGFILEPARSER_H

#include <string>
#include "paramsrs.h"
#include "paramsudp.h"

class ConfigFileParser
{
public:
    ConfigFileParser(std::string name);

    bool Init();
    TypeParams getParams() { return params; }

private:
    std::string fileName;
    TypeParams params = nullptr;
};

#endif // CONFIGFILEPARSER_H
