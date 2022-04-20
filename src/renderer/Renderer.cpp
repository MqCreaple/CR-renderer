#include "renderer/Renderer.h"

const int Renderer::WINDOW_DEFAULT_WIDTH = 600;
const int Renderer::WINDOW_DEFAULT_HEIGHT = 600;

// public methods

Renderer::Renderer(const Scene& scene, int width, int height)
    : scene(scene), windowWidth(width), windowHeight(height) {
    initializeWindow(width, height);
}

glm::ivec2 Renderer::toImageCoord(const glm::vec2& pos) {
    int x = (pos.x + 1) * windowWidth / 2;
    int y = (pos.y + 1) * windowHeight / 2;
    return glm::ivec2(x, y);
}

std::pair<glm::vec2, glm::vec2> Renderer::toFragmentCoord(const glm::ivec2& pos) {
    glm::vec2 v1 (
        pos.x * 2 / windowWidth - 1,
        pos.y * 2 / windowHeight - 1
    );
    glm::vec2 v2 (
        (pos.x + 1) * 2 / windowWidth - 1,
        (pos.y + 1) * 2 / windowHeight - 1
    );
    return std::make_pair(v1, v2);
}

Renderer::~Renderer() {
    terminateWindow();
}

// private methods

void Renderer::initializeWindow(int width, int height) {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("CR renderer", 0, 0, width, height, SDL_WINDOW_OPENGL);
    surface = SDL_GetWindowSurface(window);
}

void Renderer::setPixel(int x, int y, const Color& color) {
    Uint32* targetPixel = (Uint32*) (surface->pixels + y * surface->pitch + x * surface->format->BytesPerPixel);
    *targetPixel = SDL_MapRGB(surface->format, color.r * 256, color.g * 256, color.b * 256);
}

void Renderer::terminateWindow() {
    SDL_DestroyWindow(window);
    SDL_Quit();
}