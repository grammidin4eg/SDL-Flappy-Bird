#include "utils.h"

void exceptionIfNull(void* obj, const char* msg)
{
	if (obj == NULL) {
		throw std::logic_error(msg);
	}
}
