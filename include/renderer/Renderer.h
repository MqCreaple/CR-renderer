#pragma once

#include "scene/Scene.h"
#include "utils/Spectrum.h"
#include "utils/Random.h"
#include <iostream>
#include <SDL2/SDL.h>

/**
 * @brief abstract renderer class
 * A renderer takes a scene and generates a graphic window
 */
class Renderer {
public:
    Renderer(Scene* scene, int width = WINDOW_DEFAULT_WIDTH, int height = WINDOW_DEFAULT_HEIGHT);
    virtual void render() = 0;
    void update();
    /**
     * @brief Convert fragment coordinate to image coordinate.
     * Fragment coordinate is the 2D vector inside square [-1, 1]x[-1, 1].
     * Image coordinate is the number of pixels to top and left side of the window.
     * @param pos fragment coordinate of a point
     * @return glm::ivec2 image coordinate of the point
     */
    glm::ivec2 toImageCoord(const glm::vec2& pos);
    
    /**
     * @brief convert image coordinate to fragment coordinate.
     * Fragment coordinate is the 2D vector inside square [-1, 1]x[-1, 1].
     * Image coordinate is the number of pixels to top and left side of the window.
     * @param x x component of image coordinate
     * @param y y component of image coordinate
     * @return std::pair<glm::vec2, glm::vec2> down-left and up-right corner of the pixel in fragment coordinate
     */
    std::pair<glm::vec2, glm::vec2> pixel(int x, int y);
    std::pair<glm::vec2, glm::vec2> pixel(const glm::ivec2& pos);

    /**
     * @brief main function.
     * Main function responces to keyboard and mouse events.
     */
    void main();

    /**
     * @brief Destroy the Renderer object
     */
    ~Renderer();

    static const int WINDOW_DEFAULT_WIDTH;
    static const int WINDOW_DEFAULT_HEIGHT;
protected:
    int windowWidth;
    int windowHeight;
    void initializeWindow(int width, int height);
    void setPixel(int x, int y, const Color& color);
    void terminateWindow();
    Scene* scene;
    SDL_Window* window;
    SDL_Surface* surface;
};