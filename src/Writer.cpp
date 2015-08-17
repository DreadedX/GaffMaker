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

    FILE* pFile = fopen("files.json", "rb");
    char buffer[65536];
    rapidjson::FileReadStream is(pFile, buffer, sizeof(buffer));
    rapidjson::Document d;
    d.ParseStream<0, rapidjson::UTF8<>, rapidjson::FileReadStream>(is);

    rapidjson::Value &fileInfo = d["data"];

    for (rapidjson::SizeType i = 0; i < fileInfo.Size(); i++) {

	std::string name = "";
	char *fileName;
	static byte *data = nullptr;

	cout << i << ": " << fileInfo[i][0].GetString() << " " << fileInfo[i][1].GetString() << endl;

	switch (fileInfo[i][3].GetInt()) {
	    case 0:
		name = fileInfo[i][1].GetString();
		fileName = strdup(fileInfo[i][0].GetString());

		addFile(fileName, name, fileInfo[i][2].GetInt(), data);
		break;

	    case 1:
		name = fileInfo[i][1].GetString();
		fileName = strdup(fileInfo[i][0].GetString());

		addImage(fileName, name, fileInfo[i][2].GetInt());
		break;
	}
    }

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
    data = new(nothrow) byte[size];
    if (!data) {

	cout << "Could not allocate memory" << endl;
	return;
    }
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
