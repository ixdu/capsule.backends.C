#include <string.h>
#include <stdlib.h>

int fs_readdirSync(duk_context *ctx){
  int arg_count = duk_get_top(ctx);
  if(arg_count < 1)
    printf("need arguments\n");
  const char *path = duk_to_string(ctx, 0);
  
  WIN32_FIND_DATA data;
  HANDLE find = FindFirstFile(path, &data);
  
  if(find == INVALID_HANDLE_VALUE)
    printf("cannot read dir\n");
  
  duk_idx_t arr_idx = duk_push_array(ctx);
  
  int index = 0;
  duk_push_string(ctx, data.cFileName);
  duk_put_prop_index(ctx, arr_idx, index++);
  while(FindNextFile(find, &data)){
    printf(data.cFileName);
    duk_push_string(ctx, data.cFileName);
    duk_put_prop_index(ctx, arr_idx, index++);
  }

  FindClose(find);

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
    DUK_REGISTER_METHOD(ctx, fs_readdirSync, "readdirSync");
    DUK_REGISTER_METHOD(ctx,fs_readFileSync, "readFileSync");
    DUK_REGISTER_METHOD(ctx,fs_writeFileSync, "writeFileSync");
    DUK_REGISTER_OBJECT_END(ctx, "_fs");
}
