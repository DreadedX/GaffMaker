// Run this with nodejs to generate a json file which contains all files needed in the l
fs = require('fs');

// Types
var TYPE_UNDEF = 0x00;
var TYPE_TILE = 0x01;
var TYPE_SOLID = 0x02;
var TYPE_ENTITY = 0x04;
var TYPE_SHADER = 0x08;

// File types
var FILE_TYPE_FILE = 0x00;
var FILE_TYPE_IMAGE = 0x01;

var data = { "data": [

    // Tiles
    file("in/tile/unknown.png", TYPE_TILE),
    file("in/tile/grid.png", TYPE_TILE),

    file("in/tile/dungeon/floor_clean.png", TYPE_TILE),
    file("in/tile/dungeon/filled.png", TYPE_TILE),

    file("in/tile/dungeon/stair_left.png", TYPE_TILE),
    file("in/tile/dungeon/stair_right.png", TYPE_TILE),

    file("in/tile/dungeon/wall_bottom_left.png", TYPE_TILE | TYPE_SOLID),
    file("in/tile/dungeon/wall_bottom_right.png", TYPE_TILE | TYPE_SOLID),
    file("in/tile/dungeon/wall_bottom_center.png", TYPE_TILE | TYPE_SOLID),

    file("in/tile/dungeon/wall_top_left.png", TYPE_TILE | TYPE_SOLID),
    file("in/tile/dungeon/wall_top_right.png", TYPE_TILE | TYPE_SOLID),
    file("in/tile/dungeon/wall_top_center.png", TYPE_TILE | TYPE_SOLID),

    file("in/tile/dungeon/wall_left_center.png", TYPE_TILE | TYPE_SOLID),
    file("in/tile/dungeon/wall_right_center.png", TYPE_TILE | TYPE_SOLID),

    file("in/tile/dungeon/wall_side.png", TYPE_TILE | TYPE_SOLID),

    file("in/tile/dungeon/wall_bottom_left_inner.png", TYPE_TILE | TYPE_SOLID),
    file("in/tile/dungeon/wall_bottom_right_inner.png", TYPE_TILE | TYPE_SOLID),
    file("in/tile/dungeon/wall_top_left_inner.png", TYPE_TILE | TYPE_SOLID),
    file("in/tile/dungeon/wall_top_right_inner.png", TYPE_TILE | TYPE_SOLID),

    // Entities
    file("in/entity/player/class/mage.png", TYPE_ENTITY),
    file("in/entity/enemy.png", TYPE_ENTITY),

    // Shaders
    file("in/shader/tile.vsh", TYPE_SHADER),
    file("in/shader/tile.fsh", TYPE_SHADER),
    file("in/shader/entity.vsh", TYPE_SHADER),
    file("in/shader/entity.fsh", TYPE_SHADER),

    // JSON config files
    file("in/items.json"),

]};

function file(fileName, type) {
    if (type == null) {

	type = TYPE_UNDEF;
    }

    var fileType = FILE_TYPE_FILE;

    var outName = fileName.substring(3, fileName.lastIndexOf("."));

    if (fileName.substring(fileName.lastIndexOf(".")+1, fileName.length) == "png") {

	fileType = FILE_TYPE_IMAGE
    }

    if (fileName.substring(fileName.lastIndexOf(".")+1, fileName.length) == "vsh") {

	outName += "_vert";
    }

    if (fileName.substring(fileName.lastIndexOf(".")+1, fileName.length) == "fsh") {

	outName += "_frag";
    }

    return [ fileName, outName, type, fileType ];
}

fs.writeFile('files.json', JSON.stringify(data), function (err) {
    if (err) return console.log(err);
    console.log('files-pre.js > files.json');
});
