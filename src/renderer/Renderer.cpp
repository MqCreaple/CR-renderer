#include "renderer/Renderer.h"

const int Renderer::WINDOW_DEFAULT_WIDTH = 700;
const int Renderer::WINDOW_DEFAULT_HEIGHT = 700;

// public methods

Renderer::Renderer(Scene* scene, int width, int height)
    : scene(scene), windowWidth(width), windowHeight(height) {
    initializeWindow(width, height);
}

glm::ivec2 Renderer::toImageCoord(const glm::vec2& pos) {
    int x = (pos.x + 1) * windowWidth / 2;
    int y = (pos.y + 1) * windowHeight / 2;
    return glm::ivec2(x, y);
}

std::pair<glm::vec2, glm::vec2> Renderer::pixel(int x, int y) {
    glm::vec2 v1 (
        x * 2.0f / windowWidth - 1,
        y * 2.0f / windowHeight - 1
    );
    glm::vec2 v2 (
        (x + 1) * 2.0f / windowWidth - 1,
        (y + 1) * 2.0f / windowHeight - 1
    );
    return std::make_pair(v1, v2);
}

std::pair<glm::vec2, glm::vec2> Renderer::pixel(const glm::ivec2& pos) {
    return pixel(pos.x, pos.y);
}

void Renderer::main() {
    SDL_Event e;
    bool quit = false;
    while(!quit) {
        if(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT) {
                quit = true;
            }
        }
    }
}

Renderer::~Renderer() {
    terminateWindow();
}

// private methods

void Renderer::initializeWindow(int width, int height) {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow (
        "CR renderer",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        width,
        height,
        SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL
    );
    surface = SDL_GetWindowSurface(window);
}

void Renderer::setPixel(int x, int y, const Color& color) {
    int yp = windowHeight - y + 1;
    Uint32* targetPixel = (Uint32*) (surface->pixels + yp * surface->pitch + x * surface->format->BytesPerPixel);
    Color c = Color (
        (color.r > 1)? 1: (color.r < 0)? 0: color.r,
        (color.g > 1)? 1: (color.g < 0)? 0: color.g,
        (color.b > 1)? 1: (color.b < 0)? 0: color.b
    );
    *targetPixel = SDL_MapRGB(surface->format, c.r * 255.9, c.g * 255.9, c.b * 255.9);
}

void Renderer::terminateWindow() {
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Renderer::update() {
    SDL_UpdateWindowSurface(window);
}