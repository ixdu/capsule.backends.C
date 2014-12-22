/*
 * javascript wrapper around capsule.backends.C for working with javascript capsule parts like module_loader
 * Also it is consist some javascript initialize code for capsule env
 */

proc.platform = 'C'; //resetting name platform for compatibility with capsule

//require implementation over module_loder
if(_fs.existsSync("../capsule/parts/module_loader.js"))
    eval(_fs.readFileSync("../capsule/parts/module_loader.js"));
else
    console.log('cannot load module_loader.js');
var loader = new module_loader();

function require(path) {
    return loader.load(path);
}

//wrapping native modules like a commonjs modules
loader.add('platforms/C/modules/fs.js', {exports : _fs });
loader.add('modules/fs.js', {exports : _fs} );
loader.add('platforms/C/modules/path.js', {exports : _path });
loader.add('modules/path.js', {exports : _path} );
loader.add('platforms/C/modules/mkpath.js', {exports : _mkpath });
loader.add('modules/mkpath.js', {exports : _mkpath} );

loader.unknown_module_getter = function(path){
    if(_fs.existsSync(path))
	return _fs.readFileSync(path);
    return null;
};

proc.argv.shift();
proc.argv.unshift("deployer.js");
proc.argv.unshift("cbc");

try{
    console.log('upppp');
    require('deployer/deployer.js');     
    console.log('upppp');
} catch (x) {
    console.log('exception', JSON.stringify(x));
}

console.log("hi from capsulator");