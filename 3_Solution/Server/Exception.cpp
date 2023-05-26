#include "Exception.h"

void Exception::what()
{
	Log::write(message);
}
