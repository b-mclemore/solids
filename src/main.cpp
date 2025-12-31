#include <iostream>
#include <GL/glew.h>
#include <SDL.h>
#include <mesh.h>
#include <loadShader.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int main(int argc, char* argv[]) {
	// Load window
	// =========================
    SDL_Window* window = nullptr;

    int screen_width = 1000;
    int screen_height = 800;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL failed initialization. " << SDL_GetError();
        return -1;
    } else {
        std::cout << "SDL successfully initialized.";
    }

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    window = SDL_CreateWindow("Euler's Formula", 
            0, 
            0, 
            screen_width, 
            screen_height, 
            SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    SDL_GLContext context;
    context = SDL_GL_CreateContext(window);

    // OpenGL setup
	glewExperimental = GL_TRUE;
	GLenum initGLEW(glewInit());
	if (initGLEW == GLEW_OK) {
		std::cout << "GLEW initialised";
	} else {
		std::cout << "GLEW failed to initialized. Proceeding anyways...";
	}

	// Create solid
	Mesh solid("../data/platonic/tetrahedron.txt");
    GLuint programID = LoadShaders("../shaders/vertex.glsl", "../shaders/fragment.glsl");

    // Create view
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    glm::mat4 projection;
    projection = glm::perspective(glm::radians(60.0f), float(screen_width)/(float)screen_height, 0.1f, 100.0f);

	bool done = false;
    uint32_t last = SDL_GetTicks();
    int solid_num = 0;

    while(!done) {
        uint32_t current = SDL_GetTicks();
        glViewport(0, 0, screen_width, screen_height);

        SDL_Event event;
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT) {
                done = true;
            }
            if(event.type == SDL_KEYDOWN) {
                solid_num = (solid_num + 1) % 9;
                switch(solid_num) {
                    case 0: solid.loadSolid("../data/platonic/tetrahedron.txt"); break;
                    case 1: solid.loadSolid("../data/platonic/cube.txt"); break;
                    case 2: solid.loadSolid("../data/platonic/octahedron.txt"); break;
                    case 3: solid.loadSolid("../data/platonic/dodecahedron.txt"); break;
                    case 4: solid.loadSolid("../data/platonic/icosahedron.txt"); break;
                    case 5: solid.loadSolid("../data/pathological/cubes_corner.txt"); break;
                    case 6: solid.loadSolid("../data/pathological/tetrahedron_edge.txt"); break;
                    case 7: solid.loadSolid("../data/pathological/hollow_cube.txt"); break;
                    case 8: solid.loadSolid("../data/pathological/stacked_cube.txt"); break;
                }
            }
        }
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        float dT = (current - last) / 1000.0f;
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(50.0f)*dT, glm::vec3(0.5f, 1.0f, 0.0f));

		int modelLoc = glGetUniformLocation(programID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		int viewLoc = glGetUniformLocation(programID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		int projectionLoc = glGetUniformLocation(programID, "projection");
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

		glUseProgram(programID);

		solid.drawWireframe();	    

        SDL_GL_SwapWindow(window);
    }
	
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}