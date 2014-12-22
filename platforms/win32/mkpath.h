/*
 * mkpath builtin module with api like mkpath module from npm
 */

/*
 * arg path with directoies to create
 * return false or true
 */
int mkpath_sync(duk_context *ctx){
  return 1;
}

void mkpath_init(duk_context *ctx){
    DUK_REGISTER_OBJECT_START(ctx, "_mkpath");
    DUK_REGISTER_METHOD(ctx, "sync", mkpath_sync);
    DUK_REGISTER_OBJECT_END(ctx, "_mkpath");
}
