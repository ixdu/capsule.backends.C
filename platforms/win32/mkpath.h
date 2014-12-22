/*
 * mkpath builtin module with api like mkpath module from npm
 */

int make_dir(const char *path){
    DWORD Attrs = GetFileAttributes(path);
  if(Attrs == INVALID_FILE_ATTRIBUTES){
    char dirname[_MAX_DIR];
    _splitpath(path, NULL, dirname, NULL, NULL);
    if(strlen(dirname)){
      dirname[strlen(dirname) -1] = 0;
      make_dir(dirname);
    }
    return CreateDirectory(path, NULL);
  }else
    return TRUE;
}
/*
 * arg path with directoies to create
 * return false or true
 */
int mkpath_sync(duk_context *ctx){
  int arg_count = duk_get_top(ctx);
  if(arg_count < 1)
    printf("need specify path\n");
  const char *path = duk_to_string(ctx, 0);
  make_dir(path); //нужно выбросить исключение, если не вышло
  return 0;
}

void mkpath_init(duk_context *ctx){
    DUK_REGISTER_OBJECT_START(ctx, "_mkpath");
    DUK_REGISTER_METHOD(ctx, "sync", mkpath_sync);
    DUK_REGISTER_OBJECT_END(ctx, "_mkpath");
}
