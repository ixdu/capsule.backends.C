int proc_cwd(duk_context *ctx){
  char *buffer = malloc(2000);
  GetCurrentDirectory(2000, buffer);
  duk_push_string(ctx, buffer);

  return 1;
}

void proc_init(duk_context *ctx, LPSTR cmdline){
  printf(cmdline);
  DUK_REGISTER_OBJECT_START(ctx, "proc");
  DUK_REGISTER_PROP_STRING(ctx, "backends.C.win32", "platform");
  DUK_REGISTER_METHOD(ctx, proc_cwd, "cwd");
  DUK_REGISTER_OBJECT_END(ctx, "proc");
}
