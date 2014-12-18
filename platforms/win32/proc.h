int proc_cwd(duk_context *ctx){
  char *buffer = malloc(2000);
  GetCurrentDirectory(2000, buffer);
  duk_push_string(ctx, buffer);

  return 1;
}

void proc_init(duk_context *ctx, LPSTR cmdline){
  DUK_REGISTER_OBJECT_START(ctx, "proc");
  DUK_REGISTER_PROP_STRING(ctx, "platform", "backends.C.win32");

  duk_idx_t arr_idx = duk_push_array(ctx);  
  int index = 0;
  LPSTR _cmdline = cmdline, _arg = cmdline;
  boolean quote = FALSE;
  while(*_cmdline){
    if(quote != FALSE && *_cmdline != '\"'){
      _cmdline++;
      continue;
    }
    if(*_cmdline == '\"'){
      if(quote == FALSE){
	_arg = ++_cmdline;
	quote = TRUE;
      }else{
	*_cmdline = '\0';
	duk_push_string(ctx, _arg);
	duk_put_prop_index(ctx, arr_idx, index++);
	_arg = ++_cmdline;
	quote = FALSE;
      }
    }else      
      if(isspace(*_cmdline)){
	if(_arg != _cmdline){
	  *_cmdline = '\0';
	  duk_push_string(ctx, _arg);
	  duk_put_prop_index(ctx, arr_idx, index++);
	}
	_arg = ++_cmdline;
      } else
	_cmdline++;
  }
  if(_arg != _cmdline){
    duk_push_string(ctx, _arg);
    duk_put_prop_index(ctx, arr_idx, index++);
  }
  duk_put_prop_string(ctx, obj_idx, "argv");

  DUK_REGISTER_METHOD(ctx, "cwd", proc_cwd);
  DUK_REGISTER_OBJECT_END(ctx, "proc");
}
