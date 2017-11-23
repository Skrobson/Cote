#include "GlException.h"

using namespace cote::graphic;

GlException::GlException(const std::string & error) :std::exception(error.c_str())
{
}

GlException::GlException(const char * error) : std::exception(error)
{
}
