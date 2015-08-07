#include "Standard.h"

using namespace std;

struct fileAll {
    Gaff::fileInfo info;
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
    addImage("in/tile/void.png", "tile/void", TYPE_TILE | TYPE_SOLID);
    addImage("in/tile/grid.png", "tile/grid", TYPE_TILE);

    addImage("in/tile/block.png", "tile/block", TYPE_TILE | TYPE_SOLID);
    addImage("in/tile/pillar.png", "tile/pillar", TYPE_TILE | TYPE_SOLID);

    addImage("in/tile/brickDark.png", "tile/brickDark", TYPE_TILE | TYPE_SOLID);
    addImage("in/tile/brickLight.png", "tile/brickLight", TYPE_TILE | TYPE_SOLID);

    addImage("in/tile/flag00.png", "tile/flag00", TYPE_TILE);
    addImage("in/tile/flag01.png", "tile/flag01", TYPE_TILE);
    addImage("in/tile/flag02.png", "tile/flag02", TYPE_TILE);
    addImage("in/tile/flag03.png", "tile/flag03", TYPE_TILE);
    addImage("in/tile/flag04.png", "tile/flag04", TYPE_TILE);
    addImage("in/tile/flag05.png", "tile/flag05", TYPE_TILE);
    addImage("in/tile/flag06.png", "tile/flag06", TYPE_TILE);
    addImage("in/tile/flag07.png", "tile/flag07", TYPE_TILE);
    addImage("in/tile/flag08.png", "tile/flag08", TYPE_TILE);
    addImage("in/tile/flag09.png", "tile/flag09", TYPE_TILE);
    addImage("in/tile/flag10.png", "tile/flag10", TYPE_TILE);
    addImage("in/tile/flag11.png", "tile/flag11", TYPE_TILE);
    addImage("in/tile/flag12.png", "tile/flag12", TYPE_TILE);

    addImage("in/tile/window00.png", "tile/window00", TYPE_TILE);
    addImage("in/tile/window01.png", "tile/window01", TYPE_TILE);
    addImage("in/tile/window02.png", "tile/window02", TYPE_TILE);
    addImage("in/tile/window03.png", "tile/window03", TYPE_TILE);
    addImage("in/tile/window04.png", "tile/window04", TYPE_TILE);
    addImage("in/tile/window05.png", "tile/window05", TYPE_TILE);
    addImage("in/tile/window06.png", "tile/window06", TYPE_TILE);
    addImage("in/tile/window07.png", "tile/window07", TYPE_TILE);
    addImage("in/tile/window08.png", "tile/window08", TYPE_TILE);
    addImage("in/tile/window09.png", "tile/window09", TYPE_TILE);
    addImage("in/tile/window10.png", "tile/window10", TYPE_TILE);
    addImage("in/tile/window11.png", "tile/window11", TYPE_TILE);

    // Add entities
    addImage("in/player.png", "entity/player", TYPE_ENTITY);

    // Add font
    addImage("in/font.png", "font", 0x00);

    byte *level = 0x00;
    addLevel("in/level.dat", "level", 0x00, level, imageSize(64, 48));
    byte *level0 = 0x00;
    addLevel("in/level0.dat", "level0", 0x00, level0, imageSize(64, 48));

    byte *tile_vertex = 0x00;
    addFile("in/shaders/tile.vsh", "shaders/tile_vertex", 0x00, tile_vertex);
    byte *tile_fragment = 0x00;
    addFile("in/shaders/tile.fsh", "shaders/tile_fragment", 0x00, tile_fragment);
    byte *font_vertex = 0x00;
    addFile("in/shaders/font.vsh", "shaders/font_vertex", 0x00, font_vertex);
    byte *font_fragment = 0x00;
    addFile("in/shaders/font.fsh", "shaders/font_fragment", 0x00, font_fragment);

    byteShort fileCount;
    fileCount.s = counter;

    ofstream file ("out.gaff", ios::out | ios::binary);
    if (file.is_open()) {
	file << Gaff::MAGIC[0] << Gaff::MAGIC[1] << Gaff::MAGIC[2] << Gaff::MAGIC[3];
	file << Gaff::VERSION;
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

// TODO; This is temporary, as there will be an new level format
void addLevel(char *fileName, string name, byte type, byte *data, int widthHeight) {
    ifstream file(fileName, ios::in | ios::binary);
    file.seekg(0, ios::end);
    uint size = file.tellg();
    file.seekg(0, ios::beg);
    data = new byte[size];
    file.read(reinterpret_cast<char*>(data), size);

    makeFile(name, type, widthHeight, size, data);
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
