
#include <cstdio>
#include <glad/glad.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

static const unsigned long long window_width = 640;
static const unsigned long long window_height = 480;

int main() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("failed to init SDL: %s\n", SDL_GetError());
        return 1;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_Window* window = SDL_CreateWindow("GL Playground", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_width, window_height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        printf("failed to create SDL window: %s\n", SDL_GetError());
        return 1;
    }

    SDL_GLContext gl_context;
	gl_context = SDL_GL_CreateContext(window);
    if (gl_context == nullptr) {
        printf("failed to create gl context with SDL: %s\n", SDL_GetError());
        return 1;
    }

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        printf("failed to load gl with glad\n");
        return 1;
    }
    printf("opengl version: %d.%d\n", GLVersion.major, GLVersion.minor);

    if (SDL_GL_SetSwapInterval(1) < 0) {
        printf("Unable to set VSync with SDL: %s\n", SDL_GetError());
    }

    const GLuint program_id = glCreateProgram();

    const GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    {
        const GLchar* source[] =
        {
            "#version 140\n"
            "in vec2 pos;"
            "void main() {"
                "gl_Position = vec4(pos.xy, 0, 1);"
            "}"
        };
        glShaderSource(vertex_shader, 1, source, nullptr);
        glCompileShader(vertex_shader);
        GLint shader_compiled = GL_FALSE;
        glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &shader_compiled);
        if (shader_compiled != GL_TRUE) {
            printf("failed to compile vertex shader %d\n", vertex_shader);
            // TODO(TB): print shader log
            return 1;
        }
        glAttachShader(program_id, vertex_shader);
    }

    const GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    {
		const GLchar* source[] =
		{
			"#version 140\nout vec4 fragment; void main() { fragment = vec4(1.0, 1.0, 1.0, 1.0); }"
		};
		glShaderSource(fragment_shader, 1, source, nullptr);
		glCompileShader(fragment_shader);
		GLint shader_compiled = GL_FALSE;
		glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &shader_compiled);
        if (shader_compiled != GL_TRUE) {
            printf("failed to compile fragment shader %d\n", fragment_shader);
            // TODO(TB): print shader log
            return 1;
        }
		glAttachShader(program_id, fragment_shader);
    }

	glLinkProgram(program_id);
    {
        GLint success = GL_TRUE;
		glGetProgramiv(program_id, GL_LINK_STATUS, &success);
        if (success != GL_TRUE) {
            printf("error linking program %d\n", program_id);
            // TODO(TB): print program log
            return 1;
        }
    }
	glUseProgram(program_id);

    GLint pos_location = glGetAttribLocation(program_id, "pos");
    if (pos_location == -1) {
        printf("pos is not a valid glsl program variable\n");
        return 1;
    }

    glClearColor(0.7f, 0.9f, 0.1f, 1.0f);

    GLfloat vertex_data[] =
    {
        -0.5f, -0.5f,
        0.5f, -0.5f,
        0.5f,  0.5f,
        -0.5f,  0.5f
    };
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 2 * 4 * sizeof(GLfloat), vertex_data, GL_STATIC_DRAW);

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);

    bool running = true;
	SDL_Event event;
    while (running) {
		while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

        SDL_GL_SwapWindow(window);
        SDL_Delay(1);
    }

    SDL_GL_DeleteContext(gl_context);
	SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
