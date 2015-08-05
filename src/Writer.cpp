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
void makeImage(char *imageName, string name, byte type);
int imageSize(int width, int height);

int main() {
    
    // Add tiles
    makeImage("in/tile/void.png", "tile/void", TYPE_TILE | TYPE_SOLID);
    makeImage("in/tile/grid.png", "tile/grid", TYPE_TILE);

    makeImage("in/tile/block.png", "tile/block", TYPE_TILE | TYPE_SOLID);
    makeImage("in/tile/pillar.png", "tile/pillar", TYPE_TILE | TYPE_SOLID);

    makeImage("in/tile/brickDark.png", "tile/brickDark", TYPE_TILE | TYPE_SOLID);
    makeImage("in/tile/brickLight.png", "tile/brickLight", TYPE_TILE | TYPE_SOLID);

    makeImage("in/tile/flag00.png", "tile/flag00", TYPE_TILE);
    makeImage("in/tile/flag01.png", "tile/flag01", TYPE_TILE);
    makeImage("in/tile/flag02.png", "tile/flag02", TYPE_TILE);
    makeImage("in/tile/flag03.png", "tile/flag03", TYPE_TILE);
    makeImage("in/tile/flag04.png", "tile/flag04", TYPE_TILE);
    makeImage("in/tile/flag05.png", "tile/flag05", TYPE_TILE);
    makeImage("in/tile/flag06.png", "tile/flag06", TYPE_TILE);
    makeImage("in/tile/flag07.png", "tile/flag07", TYPE_TILE);
    makeImage("in/tile/flag08.png", "tile/flag08", TYPE_TILE);
    makeImage("in/tile/flag09.png", "tile/flag09", TYPE_TILE);
    makeImage("in/tile/flag10.png", "tile/flag10", TYPE_TILE);
    makeImage("in/tile/flag11.png", "tile/flag11", TYPE_TILE);
    makeImage("in/tile/flag12.png", "tile/flag12", TYPE_TILE);

    makeImage("in/tile/window00.png", "tile/window00", TYPE_TILE);
    makeImage("in/tile/window01.png", "tile/window01", TYPE_TILE);
    makeImage("in/tile/window02.png", "tile/window02", TYPE_TILE);
    makeImage("in/tile/window03.png", "tile/window03", TYPE_TILE);
    makeImage("in/tile/window04.png", "tile/window04", TYPE_TILE);
    makeImage("in/tile/window05.png", "tile/window05", TYPE_TILE);
    makeImage("in/tile/window06.png", "tile/window06", TYPE_TILE);
    makeImage("in/tile/window07.png", "tile/window07", TYPE_TILE);
    makeImage("in/tile/window08.png", "tile/window08", TYPE_TILE);
    makeImage("in/tile/window09.png", "tile/window09", TYPE_TILE);
    makeImage("in/tile/window10.png", "tile/window10", TYPE_TILE);
    makeImage("in/tile/window11.png", "tile/window11", TYPE_TILE);

    // Add entities
    makeImage("in/player.png", "entity/player", TYPE_ENTITY);

    // Add font
    makeImage("in/font.png", "font", 0x00);

    // Level info
    // byte layout[4 * 8] = {
	// 0, 1, 2, 3, 4, 5, 6, 7,
	// 8, 9, 10, 11, 12, 13, 14, 15,
	// 16, 17, 18, 19, 20, 21, 22, 23,
	// 23, 25, 26, 27, 28, 29, 30, 31
    // };
    uint layoutSize = 3072;
    byte layout[layoutSize];
    ifstream layoutFile("in/level.dat", ios::in | ios::binary);
    layoutFile.read(reinterpret_cast<char*>(layout), layoutSize);

    makeFile("level", 0x00, imageSize(64, 48), 48*64, layout);

    byte layout0[layoutSize];
    ifstream layout0File("in/level0.dat", ios::in | ios::binary);
    layout0File.read(reinterpret_cast<char*>(layout0), layoutSize);

    makeFile("level0", 0x00, imageSize(64, 48), 48*64, layout0);

    byteShort fileCount;
    fileCount.s = counter;

    ofstream file ("out.gaff", ios::out | ios::binary);
    if (file.is_open()) {
	file << Gaff::MAGIC[0] << Gaff::MAGIC[1] << Gaff::MAGIC[2] << Gaff::MAGIC[3];
	file << Gaff::VERSION;
	for(int i = 0; i < 2; i++) {file << fileCount.b[i];}
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

void makeImage(char *imageName, string name, byte type) {

    image image = loadPNG(imageName);
    makeFile(name, type, imageSize(image.width, image.height), image.size, image.data);
    // free(image.data);
}

void makeFile(string name, byte type, int extra, int size, byte data[]) {

    files[counter].info.nameSize = name.length();
    files[counter].info.name = name;
    files[counter].info.type = type;
    files[counter].info.extra.i = extra;
    files[counter].info.size.i = size;
    files[counter].data = data;

    counter++;
}
