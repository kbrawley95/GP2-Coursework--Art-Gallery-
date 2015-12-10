#ifndef _FONT_H
#define _FONT_H

#include "Common.h"

class Font
{
public:
	float h;// Holds The Height Of The Font.
	GLuint * textures;// Holds The Texture Id's
	GLuint list_base;// Holds The First Display List Id

	// The Init Function Will Create A Font With
	// The Height h From The File fname.
	Font(const char * fname, unsigned int h)
	{
		// Allocate Some Memory To Store The Texture Ids.
		textures = new GLuint[128];

		this->h = h;

		// Create And Initilize A FreeType Font Library.
		FT_Library library;
		if (FT_Init_FreeType(&library))
			throw std::runtime_error("FT_Init_FreeType failed");

		// The Object In Which FreeType Holds Information On A Given
		// Font Is Called A "face".
		FT_Face face;

		// This Is Where We Load In The Font Information From The File.
		// Of All The Places Where The Code Might Die, This Is The Most Likely,
		// As FT_New_Face Will Fail If The Font File Does Not Exist Or Is Somehow Broken.
		if (FT_New_Face(library, fname, 0, &face))
			throw std::runtime_error("FT_New_Face failed (there is probably a problem with your font file)");

		// For Some Twisted Reason, FreeType Measures Font Size
		// In Terms Of 1/64ths Of Pixels.  Thus, To Make A Font
		// h Pixels High, We Need To Request A Size Of h*64.
		// (h << 6 Is Just A Prettier Way Of Writing h*64)
		FT_Set_Char_Size(face, h << 6, h << 6, 96, 96);

		// Here We Ask OpenGL To Allocate Resources For
		// All The Textures And Display Lists Which We
		// Are About To Create. 
		list_base = glGenLists(128);
		glGenTextures(128, textures);

		// This Is Where We Actually Create Each Of The Fonts Display Lists.
		for (unsigned char i = 0; i<128; i++)
			make_dlist(face, i, list_base, textures);

		// We Don't Need The Face Information Now That The Display
		// Lists Have Been Created, So We Free The Assosiated Resources.
		FT_Done_Face(face);

		// Ditto For The Font Library.
		FT_Done_FreeType(library);
	}

	// Free All The Resources Associated With The Font.
	~Font()
	{

	}

	void draw(float x, float y)
	{

	}
};

#endif