#include "duktape.h"

#include "config.h"
#include "utils.h"
#if defined(HOST_PLATFORM_LIBC)
 #include "platforms/libc/head.h"
#elif defined(HOST_PLATFORM_WIN32)
 #include "platforms/win32/head.h"
#endif

#include <stdio.h>

int main(int argc, char *argv[]) {
  duk_context *ctx = duk_create_heap_default();

  platform_init(ctx);

//	(void) argc; (void) argv;  /* suppress warning */

  duk_idx_t obj_idx;
  
  duk_eval_string(ctx, "print('2+3=' + _fs.readFileSync('build')); _fs.writeFileSync('lolo', 'uhaha'); print('uhaha' + (_fs.readdirSync('platforms'))[2]);");
  //duk_pop(ctx);  
  
  duk_destroy_heap(ctx);
    
  return 0;
}

