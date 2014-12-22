/*
 * path builtin module with api like nodejs.path
 */

/*
 * arg path
 * returns: dirname
 */
int path_dirname(duk_context *ctx){
  return 1;
}

void path_init(duk_context *ctx){
    DUK_REGISTER_OBJECT_START(ctx, "_path");
    DUK_REGISTER_METHOD(ctx, "dirname", path_dirname);
    DUK_REGISTER_OBJECT_END(ctx, "_path");
}
