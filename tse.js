if (!('WebAssembly' in window)) {
    alert('you need a browser with wasm support enabled :(');
}

var gameCanvas = document.getElementById("gameCanvas");
var ctx = gameCanvas.getContext("2d");

ctx.fillStyle = 'white';
ctx.strokestyle = 'black';
ctx.fillRect(0, 0, gameCanvas.width, gameCanvas.height);
ctx.strokeRect(0, 0, gameCanvas.width, gameCanvas.height);

// Loads a WebAssembly dynamic library, returns a promise.
// imports is an optional imports object
function loadWebAssembly(filename, imports) {
    // Fetch the file and compile it
    return fetch(filename)
        .then(response => response.arrayBuffer())
        .then(buffer => WebAssembly.compile(buffer))
        .then(module => {
            // Create the imports for the module, including the
            // standard dynamic library imports
            imports = imports || {};
            imports.env = imports.env || {};
            imports.env.__memory_base = imports.env.__memory_base || 0;
            imports.env.__table_base = imports.env.__table_base || 0;

            /* TODO how do I bring these cfunctions in? */
            imports.env.abort = function () {};
            imports.env._fprintf = function () {};
            imports.env.g$_stderr = function () {};
            imports.env._atoi = function () {};
            imports.env._exit = function () {};
            imports.env._fopen = function () {};
            imports.env._fread = function () {};
            imports.env._fseek = function () {};
            imports.env._ftell = function () {};
            imports.env._fwrite = function () {};
            imports.env._getopt = function () {};
            imports.env._malloc = function () {};
            imports.env._printf = function () {};
            imports.env._putchar = function () {};
            imports.env._puts = function () {};
            imports.env._rewind = function () {};
            imports.env._strtol = function () {};
            imports.env.g$_optarg = function () {};
            imports.env.g$_optind = function () {};
            imports.env._printPixel = function print_pixel(x,y) {
                ctx.fillStyle = 'red';
                ctx.fillRect(x, y, 1, 1);
            }

            if (!imports.env.memory) {
                imports.env.memory = new WebAssembly.Memory({ initial: 1024*10 });
            }
            if (!imports.env.table) {
                imports.env.table = new WebAssembly.Table({ initial: 50, element: 'anyfunc' });
            }


            // Create the instance.
            return new WebAssembly.Instance(module, imports);
        });
}

// Main part of this example, loads the module and uses it.
loadWebAssembly('tse.wasm')
    .then(instance => {
        var exports = instance.exports; // the exports of that instance
        var doubler = exports._doubler; // the "doubler" function (note "_" prefix)
        // now we are ready, set up the button so the user can run the code
        var button = document.getElementById('run');
        button.value = 'Call a method in the WebAssembly module';
        button.addEventListener('click', function() {
            var input = 21;
            alert(input + ' doubled is ' + exports._main_wasm());
        }, false);
    }
    );
