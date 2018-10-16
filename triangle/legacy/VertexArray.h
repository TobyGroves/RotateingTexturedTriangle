#include <GL/glew.h>
#include <vector>

class VertexBuffer;

class VertexArray
{
private:
	GLuint id;
	std::vector<VertexBuffer*> buffers;
	bool dirty;

public:
	VertexArray();

	void setBuffer(std::string attribute, VertexBuffer* buffer);

	int GetVertexCount();
	GLuint GetId();

};