#include "Standard.h"

using namespace std;

struct fileAll {
    FileInfo info;
    byte *data;
};

fileAll files[255];
int counter = 0;
byteInt offset;

void makeFile(string name, byte type, int extra, int size, byte data[]);
void addLevel(char *imageName, string name, byte type, byte *data, int widthHeight);
void addFile(char *imageName, string name, byte type, byte *data);
void addImage(char *fileName, string name, byte type);
int imageSize(int width, int height);

int main() {
    
    // Add tiles
    // 0
    addImage("in/tile/unknown.png", "tile/unknown", TYPE_TILE);
    // 1
    addImage("in/tile/grid.png", "tile/grid", TYPE_TILE);

    // 2
    addImage("in/tile/dungeon/floor_clean.png", "tile/dungeon/floor", TYPE_TILE);
    // 3
    addImage("in/tile/dungeon/filled.png", "tile/dungeon/filled", TYPE_TILE | TYPE_SOLID);

    // 4
    addImage("in/tile/dungeon/stair_left.png", "tile/dungeon/stair_left", TYPE_TILE);
    // 5 
    addImage("in/tile/dungeon/stair_right.png", "tile/dungeon/stair_right", TYPE_TILE);

    // 6
    addImage("in/tile/dungeon/wall_bottom_left.png", "tile/dungeon/wall_bottom_left", TYPE_TILE | TYPE_SOLID);
    // 7
    addImage("in/tile/dungeon/wall_bottom_right.png", "tile/dungeon/wall_bottom_right", TYPE_TILE | TYPE_SOLID);
    // 8
    addImage("in/tile/dungeon/wall_bottom_center.png", "tile/dungeon/wall_bottom_center", TYPE_TILE | TYPE_SOLID);

    // 9
    addImage("in/tile/dungeon/wall_top_left.png", "tile/dungeon/wall_top_left", TYPE_TILE | TYPE_SOLID);
    // 10
    addImage("in/tile/dungeon/wall_top_right.png", "tile/dungeon/wall_top_right", TYPE_TILE | TYPE_SOLID);
    // 11
    addImage("in/tile/dungeon/wall_top_center.png", "tile/dungeon/wall_top_center", TYPE_TILE | TYPE_SOLID);

    // 12
    addImage("in/tile/dungeon/wall_left_center.png", "tile/dungeon/wall_left_center", TYPE_TILE | TYPE_SOLID);
    // 13
    addImage("in/tile/dungeon/wall_right_center.png", "tile/dungeon/wall_right_center", TYPE_TILE | TYPE_SOLID);

    // 14
    addImage("in/tile/dungeon/wall_side.png", "tile/dungeon/wall_side", TYPE_TILE | TYPE_SOLID);

    // 15
    addImage("in/tile/dungeon/wall_bottom_left_inner.png", "tile/dungeon/wall_bottom_left_inner", TYPE_TILE | TYPE_SOLID);
    // 16
    addImage("in/tile/dungeon/wall_bottom_right_inner.png", "tile/dungeon/wall_bottom_right_inner", TYPE_TILE | TYPE_SOLID);
    // 17
    addImage("in/tile/dungeon/wall_top_left_inner.png", "tile/dungeon/wall_top_left_inner", TYPE_TILE | TYPE_SOLID);
    // 18
    addImage("in/tile/dungeon/wall_top_right_inner.png", "tile/dungeon/wall_top_right_inner", TYPE_TILE | TYPE_SOLID);

    // addImage("in/maze/NONE.png", "maze/none", TYPE_TILE);
    //
    // addImage("in/maze/N.png", "maze/n", TYPE_TILE);
    // addImage("in/maze/E.png", "maze/e", TYPE_TILE);
    // addImage("in/maze/S.png", "maze/s", TYPE_TILE);
    // addImage("in/maze/W.png", "maze/w", TYPE_TILE);
    //
    // addImage("in/maze/NE.png", "maze/ne", TYPE_TILE);
    // addImage("in/maze/NS.png", "maze/ns", TYPE_TILE);
    // addImage("in/maze/NW.png", "maze/nw", TYPE_TILE);
    //
    // addImage("in/maze/ES.png", "maze/es", TYPE_TILE);
    // addImage("in/maze/EW.png", "maze/ew", TYPE_TILE);
    //
    // addImage("in/maze/SW.png", "maze/sw", TYPE_TILE);
    //
    // addImage("in/maze/NES.png", "maze/nes", TYPE_TILE);
    // addImage("in/maze/NEW.png", "maze/new", TYPE_TILE);
    // addImage("in/maze/NSW.png", "maze/nsw", TYPE_TILE);
    // addImage("in/maze/ESW.png", "maze/ews", TYPE_TILE);
    //
    // addImage("in/maze/NESW.png", "maze/nesw", TYPE_TILE);

    // Add entities
    addImage("in/entity/player/class/mage.png", "entity/player/class/mage", TYPE_ENTITY);
    addImage("in/entity/enemy.png", "entity/enemy", TYPE_ENTITY);

    // Add font
    // addImage("in/font.png", "font", TYPE_UNDEF);

    // NOTE: Level is upside down
    // byte room_test[16*16] = {
	// // 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
	// tileWallSide, tileWallSide, tileWallSide, tileWallSide, tileWallSide, tileWallSide, tileWallSide, tileWallSide, tileWallSide, tileWallSide, tileWallSide, tileWallSide, tileWallSide, tileWallSide, tileWallSide, tileWallSide, 
	// // 6, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 7,
	// tileWallBottomLeft, tileWallHorizontal, tileWallHorizontal, tileWallHorizontal, tileWallHorizontal, tileWallHorizontal, tileWallHorizontal, tileWallHorizontal, tileWallHorizontal, tileWallHorizontal, tileWallHorizontal, tileWallHorizontal, tileWallHorizontal, tileWallHorizontal, tileWallHorizontal, tileWallBottomRight,
	// // 11, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 11,
	// tileWallVertical, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileWallVertical,
	// // 11, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 11,
	// tileWallVertical, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileWallVertical,
	// // 11, 12, 12, 12, 12, 12, 12, 4, 5, 12, 12, 12, 12, 12, 12, 11,
	// tileWallVertical, tileWallSide, tileWallSide, tileStairLeft, tileStairRight, tileWallSide, tileWallSide, tileWallSide, tileWallSide, tileWallSide, tileWallSide, tileWallSide, tileWallSide, tileWallSide, tileWallSide, tileWallVertical,
	// // 11, 3, 3, 3, 3, 3, 3, 2, 2, 3, 3, 3, 3, 3, 3, 11,
	// tileWallVertical, tileFloorEdgeBottom, tileFloorEdgeBottom, tileFloor, tileFloor, tileFloorEdgeBottom, tileFloorEdgeBottom, tileFloorEdgeBottom, tileFloorEdgeBottom, tileFloorEdgeBottom, tileFloorEdgeBottom, tileFloorEdgeBottom, tileFloorEdgeBottom, tileFloorEdgeBottom, tileFloorEdgeBottom, tileWallVertical,
	// // 11, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 11,
	// tileWallVertical, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileWallVertical,
	// // 11, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 11,
	// tileWallVertical, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileWallVertical,
	// // 11, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 11,
	// tileWallVertical, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileWallVertical,
	// // 11, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 11,
	// tileWallVertical, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileWallVertical,
	// // 11, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 11,
	// tileWallVertical, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileWallVertical,
	// // 11, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 11,
	// tileWallVertical, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileWallVertical,
	// // 11, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 11,
	// tileWallVertical, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileWallVertical,
	// // 11, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 11,
	// tileWallVertical, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileFloor, tileWallVertical,
	// // 11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 11,
	// tileWallVertical, tileWallSide, tileWallSide, tileWallSide, tileWallSide, tileWallSide, tileWallSide, tileWallSide, tileWallSide, tileWallSide, tileWallSide, tileWallSide, tileWallSide, tileWallSide, tileWallSide, tileWallVertical,
	// // 8, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 9
	// tileWallTopLeft, tileWallHorizontal, tileWallHorizontal, tileWallHorizontal, tileWallHorizontal, tileWallHorizontal, tileWallHorizontal, tileWallHorizontal, tileWallHorizontal, tileWallHorizontal, tileWallHorizontal, tileWallHorizontal, tileWallHorizontal, tileWallHorizontal, tileWallHorizontal, tileWallTopRight
    // };
    // makeFile("room_16x16_test", TYPE_UNDEF, imageSize(16, 16), 16*16, room_test);

    byte *tile_vertex = 0x00;
    addFile("in/shaders/tile.vsh", "shaders/tile_vert", TYPE_UNDEF, tile_vertex);
    byte *tile_fragment = 0x00;
    addFile("in/shaders/tile.fsh", "shaders/tile_frag", TYPE_UNDEF, tile_fragment);
    byte *font_vertex = 0x00;
    addFile("in/shaders/entity.vsh", "shaders/entity_vert", TYPE_UNDEF, font_vertex);
    byte *font_fragment = 0x00;
    addFile("in/shaders/entity.fsh", "shaders/entity_frag", TYPE_UNDEF, font_fragment);

    byteShort fileCount;
    fileCount.s = counter;

    ofstream file ("out.gaff", ios::out | ios::binary);
    if (file.is_open()) {
	file << MAGIC[0] << MAGIC[1] << MAGIC[2] << MAGIC[3];
	file << VERSION;
	for(int i = 0; i < 2; i++) {file << fileCount.b[i];}
    }

    for (int p = 0; p < counter; p++) {

	byte compressedData[files[p].info.size.i];
	long unsigned int length = files[p].info.size.i;
	long unsigned int lengthSource = files[p].info.size.i;
	int result  = compress(compressedData, &length, files[p].data, lengthSource);
	if(result != Z_OK) {
	    cout << "Compression of: " << files[p].info.name <<  " failed: " << result << endl;
	    return -1;
	}
	cout << files[p].info.name << " " << lengthSource << " " << length << endl;
	files[p].data = new byte[length];
	files[p].info.size.i = length;
	for (uint i = 0; i < length; i++) {
	    files[p].data[i] = compressedData[i];
	}
    }

    offset.i = 4 + 1 + 2;
    for(int p = 0; p < counter; p++) {
	offset.i += 1 + files[p].info.name.length() + 1 + 4 + 4 + 4;
    }

    for(int p = 0; p < counter; p++) {
	files[p].info.offset = offset;
	offset.i += files[p].info.size.i;
    }

    for(int p = 0; p < counter; p++) {
	file << files[p].info.nameSize << files[p].info.name << files[p].info.type;
	for(int i = 0; i < 4; i++) {file << files[p].info.extra.b[i];}
	for(int i = 0; i < 4; i++) {file << files[p].info.offset.b[i];}
	for(int i = 0; i < 4; i++) {file << files[p].info.size.b[i];}
    }
    for(int p = 0; p < counter; p++) {
	for(uint i = 0; i < files[p].info.size.i; i++) {file << files[p].data[i];}
    }

    file.close();
}

int imageSize(int width, int height) {

    byteShort w;
    w.s = (short)width;
    byteShort h;
    h.s = (short)height;

    byteInt extra;
    extra.b[0] = w.b[0];
    extra.b[1] = w.b[1];
    extra.b[2] = h.b[0];
    extra.b[3] = h.b[1];

    return extra.i;
}

void addImage(char *imageName, string name, byte type) {

    image image = loadPNG(imageName);
    makeFile(name, type, imageSize(image.width, image.height), image.size, image.data);
}

void addFile(char *fileName, string name, byte type, byte *data) {
    ifstream file(fileName, ios::in | ios::binary);
    file.seekg(0, ios::end);
    uint size = file.tellg();
    file.seekg(0, ios::beg);
    data = new byte[size];
    file.read(reinterpret_cast<char*>(data), size);

    makeFile(name, type, 0x00, size, data);
}

void makeFile(string name, byte type, int extra, int size, byte *data) {

    files[counter].info.nameSize = name.length();
    files[counter].info.name = name;
    files[counter].info.type = type;
    files[counter].info.extra.i = extra;
    files[counter].info.size.i = size;
    files[counter].data = data;

    counter++;
}
