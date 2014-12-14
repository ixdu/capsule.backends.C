#include "duktape.h"

#include "config.h"
#include "utils.h"

int _main(duk_context *ctx){
  duk_eval_string(ctx, "_fs.writeFileSync('hop.txt', 'ulolop');_console.log(_fs.readFileSync('hop.txt'), _fs.readdirSync('platforms'), { privet : 'haha'}, 18);");
}

#if defined(HOST_PLATFORM_LIBC)
 #include "platforms/libc/main.c"
#elif defined(HOST_PLATFORM_WIN32)
 #include "platforms/win32/main.c"
#elif defined(HOST_PLATFORM_E)
 #include "platforms/e/main.c"
#endif
