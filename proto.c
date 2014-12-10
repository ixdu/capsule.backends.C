#include "duktape.h"

#include "config.h"
#if defined(HOST_PLATFORM_LIBC)
 #include "platforms/libc/head.h"
#elif defined(HOST_PLATFORM_WIN32)
 #include "platforms/win32/head.h"
#endif

#include <stdio.h>

int adder(duk_context *ctx) {
    int i;
    int n = duk_get_top(ctx);  
    printf("%f", duk_to_number(ctx, 1));
    double res = 0.0;

    for (i = 0; i < n; i++) {
        res += duk_to_number(ctx, i);
    }

    duk_push_string(ctx, "UHAHA");
    return 1;  
}

int main(int argc, char *argv[]) {
  duk_context *ctx = duk_create_heap_default();

  platform_init(ctx);
  //  readFileSync("build");

//	(void) argc; (void) argv;  /* suppress warning */

  duk_push_global_object(ctx);
  duk_push_c_function(ctx, adder, DUK_VARARGS);
  duk_put_prop_string(ctx, -2, "adder");
  duk_pop(ctx);  
  
  duk_eval_string(ctx, "print('2+3=' + fs_readFileSync('build')); fs_writeFileSync('lolo', 'uhaha'); print('uhaha' + (fs_readdirSync('platforms'))[2]);");
  duk_pop(ctx);  
  
  duk_destroy_heap(ctx);
  
  return 0;
}

