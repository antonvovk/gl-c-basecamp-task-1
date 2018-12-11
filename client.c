#ifdef __unix__     
    
#include "unix_network.h"

#elif defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64) 

#include "windows_network.h"

#endif

#include "system_api.h"

int main() {
    
    return 0;
}
