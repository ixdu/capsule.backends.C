#include <stdio.h>

#include "proc.h"
#include "console_log.h"
#include "require.h"
#include "fs.h"
#include "path.h"
int platform_init(duk_context *ctx){
  fs_init(ctx);
  printf("i am libc initializer\n");
}
