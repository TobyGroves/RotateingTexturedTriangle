#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <exception>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "stb_image.h"

#include "main.h"
#include "ShaderProgram.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Texture.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

int main(int argc, char *argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		throw std::exception();
	}

	SDL_Window *window = SDL_CreateWindow("Triangle",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

	if (!SDL_GL_CreateContext(window))
	{
		throw std::exception();
	}

	if (glewInit() != GLEW_OK)
	{
		throw std::exception();
	}

	bool quit = false;


	////////////////////////////////////////

	// create and bind texture
	Texture *texture = new Texture("YesNoodles.jpg");


	VertexBuffer *positions = new VertexBuffer();
	positions->add(glm::vec3(0.0f, 0.5f, 0.0f));
	positions->add(glm::vec3(-0.5f, -0.5f, 0.0f));
	positions->add(glm::vec3(0.5f, -0.5f, 0.0f));

	/*VertexBuffer *colors = new VertexBuffer();
	colors->add(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	colors->add(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
	colors->add(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));*/


	VertexBuffer *TexCoords = new VertexBuffer();
	TexCoords->add(glm::vec2(0.5f, 0.0f));
	TexCoords->add(glm::vec2(0.0f, 1.0f));
	TexCoords->add(glm::vec2(1.0f, 1.0f));

	VertexArray *shape = new VertexArray();
	shape->setBuffer("in_Position", positions);
	//shape->setBuffer("in_Color", colors);
	shape->setBuffer("in_TexCoord", TexCoords);

	float angle = 0;



	
	ShaderProgram *shaderProgram = new ShaderProgram("../shaders/matrix.vert", "../shaders/simple.frag");

	while (!quit)
	{
		SDL_Event event = { 0 };

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				quit = true;
			}
		}
		clearBG();

		
		glActiveTexture(GL_TEXTURE0 + 1);
		glBindTexture(GL_TEXTURE_2D, texture->getId());

		shaderProgram->SetUniform("in_Texture", 1);

		// Draw with perspective projection matrix
		shaderProgram->SetUniform("in_Projection", glm::perspective(glm::radians(45.0f), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.f));
		glm::mat4 model(1.0f);
		model = glm::translate(model, glm::vec3(0, 0, -2.5f));
		model = glm::rotate(model, glm::radians(angle), glm::vec3(0, 1, 0));
		shaderProgram->SetUniform("in_Model", model);
		shaderProgram->draw(shape);

		angle += 0.5f;
		

		//Draw with orthographic projection matrix 

		model = glm::mat4(1.0f);

		shaderProgram->SetUniform("in_Projection", glm::ortho(0.0f, (float)WINDOW_WIDTH, 0.0f, (float)WINDOW_HEIGHT, 0.0f, 1.0f));

		model = glm::translate(model, glm::vec3(100, WINDOW_HEIGHT - 100, 0));
		model = glm::scale(model, glm::vec3(100, 100, 1));

		shaderProgram->SetUniform("in_Model", model);
		shaderProgram->draw(shape);





		SDL_GL_SwapWindow(window);
	}

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}



void clearBG()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

}
