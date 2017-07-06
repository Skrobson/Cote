#include "GLerror.h"


GLerror::GLerror(const std::string & error):std::runtime_error(error.c_str())
{
}

GLerror::GLerror(const char * error):std::runtime_error(error)
{
}

GLerror::~GLerror()
{
}
