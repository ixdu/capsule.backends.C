var console = _console;

//require implementation over module_loder
if(_fs.existsSync("../capsule/platforms/browser/module_loader.js"))
    eval(_fs.readFileSync("../capsule/platforms/browser/module_loader.js"));
else
    console.log('cannot load module_loader.js');
var loader = new module_loader();

function require(path) {
    return loader.load(path);
}

loader.add('modules/fs.js', _fs);
loader.unknown_module_getter = function(path){
    if(_fs.existsSync(path))
	return _fs.readFileSync(path);
    return null;
};

try{
    var fs = require('modules/fs.js');
    console.log(12);   
    var transport = require('../capsule/modules/transport.js');
    console.log(JSON.stringify(transport));    
    console.log(13);   
} catch (x) {
    console.log(x.code);
}
//require('hh/hh/ll.js');
//require('tt/hh/qqqqq');
_console.log("hi from capsulator");