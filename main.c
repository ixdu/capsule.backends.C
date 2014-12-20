#include "duktape.h"

#include "defs.h"
#include "utils.h"

int _main(duk_context *ctx){
  if (duk_peval_string(ctx, "var capsulator = _fs.readFileSync('capsulator.js'); if(!capsulator)\
		  _console.log('capsulator file not exists'); eval(capsulator);") != 0) {
    /* Use duk_safe_to_string() to convert error into string.  This API
     * call is guaranteed not to throw an error during the coercion.
     */
    printf("Script error: %s\n", duk_safe_to_string(ctx, -1));
  }
  //  duk_eval_string(ctx, "function require(d){return 'ddd';};_console.log(require('t'),_fs.existsSync('platforms'), _fs.existsSync('lalal'), proc.argv[4])");
  //  duk_eval_string(ctx, "_fs.mkdir('jj');_fs.writeFileSync('hop.txt', 'ulolop');_console.log(_fs.readFileSync('hop.txt'), _fs.readdirSync('platforms'), proc.cwd(), proc.platform, { privet : 'haha'}, 18);");
}

#if defined(HOST_PLATFORM_LIBC)
 #include "platforms/libc/main.c"
#elif defined(HOST_PLATFORM_WIN32)
 #include "platforms/win32/main.c"
#elif defined(HOST_PLATFORM_E)
 #include "platforms/e/main.c"
#endif
