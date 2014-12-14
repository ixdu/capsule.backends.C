#include "duktape.h"

#include "config.h"
#include "utils.h"

#if defined(HOST_PLATFORM_LIBC)
 #include "platforms/libc/main.c"
#elif defined(HOST_PLATFORM_WIN32)
 #include "platforms/win32/main.c"
#elif defined(HOST_PLATFORM_E)
 #include "platforms/e/main.c"
#endif
