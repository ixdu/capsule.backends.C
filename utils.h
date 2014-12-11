#define DUK_REGISTER_OBJECT_START(ctx, name) duk_push_global_object(ctx); \
  duk_idx_t obj_idx;							\
  obj_idx = duk_push_object(ctx);					\

#define DUK_REGISTER_OBJECT_END(CTX, name) duk_put_prop_string(ctx, -2, name); \
  duk_pop(ctx);
  
#define DUK_REGISTER_METHOD(ctx, func, name) duk_push_c_function(ctx, func, DUK_VARARGS); \
  duk_put_prop_string(ctx, obj_idx, name);				\
  
#define DUK_REGISTER_FUNC(ctx, func, name) duk_push_global_object(ctx);	\
  duk_push_c_function(ctx, func, DUK_VARARGS);				\
  duk_put_prop_string(ctx, -2, name);					\
  duk_pop(ctx);
