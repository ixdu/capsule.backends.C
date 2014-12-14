#include <stdio.h>

#include "proc.h"
#include "console_log.h"
#include "require.h"
#include "fs.h"
#include "timer.h"
#include "path.h"

int main(int argc, char **argv){
  duk_context *ctx = duk_create_heap_default();

  printf("i am libc platform\n");
  fs_init(ctx);
  timer_init(ctx);

  duk_idx_t obj_idx;
  
  _main(ctx);
  //  duk_eval_string(ctx, "print('2+3=' + _fs.readFileSync('build')); _fs.writeFileSync('lolo', 'uhaha'); print('uhaha' + (_fs.readdirSync('platforms'))[2]);");
  //duk_pop(ctx);  
  
  duk_destroy_heap(ctx);
  return 0;
}
