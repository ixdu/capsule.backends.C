#include <string.h>
#include <stdlib.h>

//arg path
int fs_existsSync(duk_context *ctx){
  int arg_count = duk_get_top(ctx);
  if(arg_count < 1)
    printf("need specify path\n");
  const char *path = duk_to_string(ctx, 0);
  DWORD Attrs;
  Attrs = GetFileAttributes(path);
  if(Attrs == INVALID_FILE_ATTRIBUTES)
    duk_push_boolean(ctx, 0);
  else
    duk_push_boolean(ctx, 1);    

  return 1;
}

//arg path
int fs_mkdir(duk_context *ctx){
  int arg_count = duk_get_top(ctx);
  if(arg_count < 1)
    printf("need specify path\n");
  const char *path = duk_to_string(ctx, 0);
  CreateDirectory(path, NULL);

  return 0;
}

int fs_readdirSync(duk_context *ctx){
  int arg_count = duk_get_top(ctx);
  if(arg_count < 1)
    printf("need arguments\n");
  const char *path = duk_to_string(ctx, 0);
  
  WIN32_FIND_DATA data;
  char *new_path = malloc(strlen(path + 3));
  sprintf(new_path, "%s%s", path, "\\\\*");
  HANDLE find = FindFirstFile(new_path, &data);
  printf("path: %s\n", new_path);
  
  if(find == INVALID_HANDLE_VALUE)
    printf("cannot read dir\n");
  
  duk_idx_t arr_idx = duk_push_array(ctx);
  
  int index = 0;
  duk_push_string(ctx, data.cFileName);
  duk_put_prop_index(ctx, arr_idx, index++);
  do {
    duk_push_string(ctx, data.cFileName);
    duk_put_prop_index(ctx, arr_idx, index++);
  } while(FindNextFile(find, &data) != 0);

  FindClose(find);
  free(new_path);

  return 1;
}

//filename, data
int fs_writeFileSync(duk_context *ctx){
  int arg_count = duk_get_top(ctx);
  if(arg_count < 2)
    printf("need arguments\n");
  const char *filename = duk_to_string(ctx, 0);
  const char *data = duk_to_string(ctx, 1);

  if(arg_count > 2)
    duk_to_object(ctx, 0);//options    

  HANDLE hnd = CreateFile(filename, GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
  WriteFile(hnd, data, strlen(data), NULL, NULL);
  CloseHandle(hnd);

  return 1;
}
int fs_readFileSync(duk_context *ctx){
  int arg_count = duk_get_top(ctx);
  if(arg_count < 1)
    printf("need arguments\n");
  const char *filename = duk_to_string(ctx, 0);

  if(arg_count > 2)
    duk_to_object(ctx, 0);//options    

  HANDLE hnd = CreateFile(filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
  
  if(hnd == INVALID_HANDLE_VALUE)
     printf("cannot open file");     
  
  size_t size; 
  GetFileSizeEx(hnd, (PLARGE_INTEGER) &size);
  char *data = malloc(size);
  ReadFile(hnd, data, size, NULL, NULL);
  duk_push_string(ctx, data);
  free(data);

  return 1;
}

void fs_init(duk_context *ctx){
    DUK_REGISTER_OBJECT_START(ctx, "_fs");
    DUK_REGISTER_METHOD(ctx, "existsSync", fs_existsSync);
    DUK_REGISTER_METHOD(ctx, "mkdir", fs_mkdir);
    DUK_REGISTER_METHOD(ctx, "readdirSync", fs_readdirSync);
    DUK_REGISTER_METHOD(ctx, "readFileSync", fs_readFileSync);
    DUK_REGISTER_METHOD(ctx, "writeFileSync", fs_writeFileSync);
    DUK_REGISTER_OBJECT_END(ctx, "_fs");
}
