#include <stdio.h>

int console_log(duk_context *ctx){
  //const char *filename = duk_to_string(ctx, 0);
  int arg_count = duk_get_top(ctx); //
  int type, n = 0;
  for(; n <= arg_count; n++){
    type = duk_get_type(ctx, n);
    switch(type){
    case DUK_TYPE_NUMBER :
      printf("number %d\n", duk_to_int(ctx,n));      
      break;
    case DUK_TYPE_STRING :
      printf("string %s\n", duk_to_string(ctx,n));      
      break;
    case DUK_TYPE_BOOLEAN : 
      break;
    case DUK_TYPE_OBJECT :
      //      printf("object %d\n", duk_to_object(ctx, n));
      break;
    }
  } 
  return 1;
}

void console_init(duk_context *ctx){
  DUK_REGISTER_OBJECT_START(ctx, "_console");
  DUK_REGISTER_METHOD(ctx,console_log, "log");
  DUK_REGISTER_OBJECT_END(ctx, "_console");
}
