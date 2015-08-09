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
    addImage("in/tile/dungeon/floor_edge_bottom_center.png", "tile/dungeon/floor_edge_bottom", TYPE_TILE);

    // 4
    addImage("in/tile/dungeon/stair_left.png", "tile/dungeon/stair_left", TYPE_TILE);
    // 5 
    addImage("in/tile/dungeon/stair_right.png", "tile/dungeon/stair_right", TYPE_TILE);

    // 6
    addImage("in/tile/dungeon/wall_bottom_left.png", "tile/dungeon/wall_bottom_left", TYPE_TILE | TYPE_SOLID);
    // 7
    addImage("in/tile/dungeon/wall_bottom_right.png", "tile/dungeon/wall_bottom_right", TYPE_TILE | TYPE_SOLID);

    // 8
    addImage("in/tile/dungeon/wall_top_left.png", "tile/dungeon/wall_top_left", TYPE_TILE | TYPE_SOLID);
    // 9
    addImage("in/tile/dungeon/wall_top_right.png", "tile/dungeon/wall_top_right", TYPE_TILE | TYPE_SOLID);

    // 10
    addImage("in/tile/dungeon/wall_horizontal.png", "tile/dungeon/wall_horizontal", TYPE_TILE | TYPE_SOLID);
    // 11
    addImage("in/tile/dungeon/wall_vertical.png", "tile/dungeon/wall_vertical", TYPE_TILE | TYPE_SOLID);

    // 12
    addImage("in/tile/dungeon/wall_side.png", "tile/dungeon/wall_side", TYPE_TILE | TYPE_SOLID);

    // Add entities
    addImage("in/player.png", "entity/player", TYPE_ENTITY);

    // Add background
    addImage("in/background/mountain/0.png", "background/mountain_0", TYPE_UNDEF);
    addImage("in/background/mountain/1.png", "background/mountain_1", TYPE_UNDEF);
    addImage("in/background/mountain/2.png", "background/mountain_2", TYPE_UNDEF);
    addImage("in/background/mountain/3.png", "background/mountain_3", TYPE_UNDEF);
    addImage("in/background/mountain/4.png", "background/mountain_4", TYPE_UNDEF);
    addImage("in/background/mountain/5.png", "background/mountain_5", TYPE_UNDEF);
    addImage("in/background/mountain/floor.png", "background/mountain_floor", TYPE_UNDEF);

    // Add font
    addImage("in/font.png", "font", TYPE_UNDEF);

    byte level[16*16] = {
	8, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 9,
	11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 11,
	11, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 11,
	11, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 11,
	11, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 11,
	11, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 11,
	11, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 11,
	11, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 11,
	11, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 11,
	11, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 11,
	11, 3, 3, 3, 3, 3, 3, 2, 2, 3, 3, 3, 3, 3, 3, 11,
	11, 12, 12, 12, 12, 12, 12, 4, 5, 12, 12, 12, 12, 12, 12, 11,
	11, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 11,
	11, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 11,
	6, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 7,
	12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12
    };
    makeFile("level", TYPE_UNDEF, imageSize(16, 16), 16*16, level);

    byte *tile_vertex = 0x00;
    addFile("in/shaders/tile.vsh", "shaders/tile_vertex", TYPE_UNDEF, tile_vertex);
    byte *tile_fragment = 0x00;
    addFile("in/shaders/tile.fsh", "shaders/tile_fragment", TYPE_UNDEF, tile_fragment);
    byte *font_vertex = 0x00;
    addFile("in/shaders/font.vsh", "shaders/font_vertex", TYPE_UNDEF, font_vertex);
    byte *font_fragment = 0x00;
    addFile("in/shaders/font.fsh", "shaders/font_fragment", TYPE_UNDEF, font_fragment);

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
