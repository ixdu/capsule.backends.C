/*
 * path builtin module with api like nodejs.path
 */

#include <stdlib.h>
#include <string.h>

/*
 * arg path
 * returns: dirname
 */
int path_dirname(duk_context *ctx){
  char dirname[_MAX_DIR];
  int arg_count = duk_get_top(ctx);
  if(arg_count < 1)
    printf("need specify path\n");
  const char *path = duk_to_string(ctx, 0);
  _splitpath(path, NULL, dirname, NULL, NULL);
  duk_push_string(ctx, dirname);

  return 1;
}

/*
 *arg path
 *returns: file or directory name
 */
int path_basename(duk_context *ctx){
  char filename[_MAX_FNAME + _MAX_EXT];
  int arg_count = duk_get_top(ctx);
  if(arg_count < 1)
    printf("need specify path\n");
  const char *path = duk_to_string(ctx, 0);
  _splitpath(path, NULL, NULL, filename, (filename + _MAX_FNAME));
  strcat(filename, (filename + _MAX_FNAME));
  duk_push_string(ctx, filename);

  return 1;
}

void path_init(duk_context *ctx){
    DUK_REGISTER_OBJECT_START(ctx, "_path");
    DUK_REGISTER_METHOD(ctx, "dirname", path_dirname);
    DUK_REGISTER_METHOD(ctx, "basename", path_basename);
    DUK_REGISTER_OBJECT_END(ctx, "_path");
}
