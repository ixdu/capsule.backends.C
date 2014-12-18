#include "duktape.h"

#include "defs.h"
#include "utils.h"

int _main(duk_context *ctx){
  duk_eval_string(ctx, "_console.log(_fs.existsSync('platforms'), _fs.existsSync('lalal'), proc.argv[4])");
  //  duk_eval_string(ctx, "_fs.mkdir('jj');_fs.writeFileSync('hop.txt', 'ulolop');_console.log(_fs.readFileSync('hop.txt'), _fs.readdirSync('platforms'), proc.cwd(), proc.platform, { privet : 'haha'}, 18);");
}

#if defined(HOST_PLATFORM_LIBC)
 #include "platforms/libc/main.c"
#elif defined(HOST_PLATFORM_WIN32)
 #include "platforms/win32/main.c"
#elif defined(HOST_PLATFORM_E)
 #include "platforms/e/main.c"
#endif
