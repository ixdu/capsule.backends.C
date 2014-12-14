//#include <signal.h>
//#include <time.h>

/*
  capsule timer module implementation based on posix timer api
 */

int _timer_create(duk_context *ctx){
}

void timer_init(duk_context *ctx){
  DUK_REGISTER_OBJECT_START(ctx, "_timer");  
  DUK_REGISTER_METHOD(ctx, _timer_create, "create");
  DUK_REGISTER_OBJECT_END(ctx, "_timer");
}
