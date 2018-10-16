
#include <GL/glew.h>
#include <string>
#include <fstream>

class Texture
{

public :
	Texture(std::string TextureLocation);
	GLuint getId();
private:
	const char* textureLoc;
	GLuint textureId;
};