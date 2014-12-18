/*
  nodejs filesystem like module
 */
#include <stdio.h>
#include <dirent.h>
#include <malloc.h>
#include <string.h>

//arg path
int fs_existsSync(duk_context *ctx){
}

//arg path
//return array
int fs_readdirSync(duk_context *ctx){
  const char *path = duk_to_string(ctx, 0);
  DIR *dir = opendir(path);
  struct dirent *_dirent;
  duk_idx_t arr_idx = duk_push_array(ctx);
  int index = 0;
  if(dir){
    while((_dirent = readdir(dir)) != NULL){
      duk_push_string(ctx, _dirent->d_name);
      duk_put_prop_index(ctx, arr_idx, index++);
    }
    closedir(dir);
  }

  return 1;
}

//arg path
int fs_mkdir(duk_context *ctx){
}

int fs_readFileSync(duk_context *ctx){
  const char *filename = duk_to_string(ctx, 0);
  //  int n = duk_get_top(ctx);  надо бы как-то проветь корректность и наличие аргументов

  FILE *file = fopen(filename, "r");
  //  if(!file)
  // return 0; //error handling need

  fseek(file, 0, SEEK_END);
  int fsize = ftell(file);
  char *buffer = malloc(fsize);
  fseek(file, 0, SEEK_SET);
  fread(buffer, sizeof(char), fsize, file);
  printf("filesize is: %s\n", buffer);
  
  fclose(file);
  duk_push_string(ctx, buffer);
  free(buffer);

  return 1;
}

//filename, data
int fs_writeFileSync(duk_context *ctx){
  const char *filename = duk_to_string(ctx, 0);
  const char *data = duk_to_string(ctx, 1);

  FILE *file = fopen(filename, "w");
  fseek(file, 0, SEEK_SET);
  fwrite(data, sizeof(char), strlen(data), file);

  fclose(file);
  duk_push_number(ctx, 1);
	 
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
