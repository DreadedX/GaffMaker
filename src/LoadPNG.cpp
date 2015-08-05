#include "Standard.h"

image loadPNG(char *name) {
    image png;

    png_structp png_ptr;
    png_infop info_ptr;
    unsigned int sig_read = 0;
    int color_type;
    int interlace_type;
    FILE *fp;

    if ((fp = fopen(name, "rb")) == NULL) {
	return png;
    }

    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (png_ptr == NULL) {
	fclose(fp);
	return png;
    }

    info_ptr = png_create_info_struct(png_ptr);
    if (info_ptr == NULL) {
	fclose(fp);
	png_destroy_read_struct(&png_ptr, NULL, NULL);
	return png;
    }

    if (setjmp(png_jmpbuf(png_ptr))) {
	png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
	fclose(fp);
	return png;
    }

    png_init_io(png_ptr, fp);
    png_set_sig_bytes(png_ptr, sig_read);
    png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_EXPAND, NULL);

    png_uint_32 width;
    png_uint_32 height;
    int bit_depth;
    png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type, &interlace_type, NULL, NULL);

    unsigned int row_bytes = png_get_rowbytes(png_ptr, info_ptr);
    png.data = (byte*) malloc(row_bytes * height);
    png.size = row_bytes * height;

    png_bytepp row_pointers = png_get_rows(png_ptr, info_ptr);
    for (uint i = 0; i < height; i++) {
	// note that png is ordered top to
	// bottom, but OpenGL expect it bottom to top
	// so the order or swapped
	memcpy(png.data+(row_bytes * (height - 1 -i)), row_pointers[i], row_bytes);
    }

    png.width = width;
    png.height = height;

    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);

    fclose(fp);

    return png;
}




