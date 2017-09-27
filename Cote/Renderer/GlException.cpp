#include "GlException.h"

using namespace cote::graphic;

GlException::GlException(const std::string & error) :std::runtime_error(error.c_str())
{
}

GlException::GlException(const char * error) : std::runtime_error(error)
{
}
