#pragma once

#include <cmath>
#include <glm/glm.hpp>

/**
 * @brief Abstract class for texture maps.
 * @tparam T type of data stored in the map.
 */
template<typename T>
class TextureMap {
    // TODO (project structure)
public:
    TextureMap(size_t width, size_t height);

    /**
     * @brief Get the width of texture map
     * @return size_t width (number of pixels)
     */
    size_t getWidth() const;
    /**
     * @brief Get the height of texture map
     * @return size_t height (number of pixels)
     */
    size_t getHeight() const;

    T operator()(float u, float v) const;
    
    virtual void set(int i, int j, T val);

    /**
     * @brief mapping between position in local coordinate and the value in texture map.
     * @param local position in object's local coordinate.
     * @return T color of texture.
     */
    virtual T map(const glm::vec3& local) const = 0;

    /**
     * @brief inverse mapping from the texture to three dimentional vector in local coordinate
     * @param u horizontal component on texture map
     * @param v vertical component on texture map
     * @return glm::vec3& vector of the pixel in object's local coordinate
     */
    virtual glm::vec3 invMap(float u, float v) const = 0;

    ~TextureMap();
protected:
    size_t width;
    size_t height;
    T* colorMap;
    T get(size_t i, size_t j) const;

    /**
     * @brief bilinear interpolation.
     * pixel index [x, y] covers the square region bounded by [x, y] and [x+1, y+1], and
     * the center of pixel [x, y] converted to floating point is actually [x+0.5, y+0.5].
     * @param i horizontal value
     * @param j vertical value
     * @return T color
     */
    T bilinInterp(float i, float j) const;
};

template<typename T>
TextureMap<T>::TextureMap(size_t width, size_t height)
    : width(width), height(height), colorMap(new T[width * height]) {}

template<typename T>
size_t TextureMap<T>::getWidth() const {
    return width;
}

template<typename T>
size_t TextureMap<T>::getHeight() const {
    return height;
}

template<typename T>
T TextureMap<T>::operator()(float u, float v) const {
    return bilinInterp(u, v);
}

template<typename T>
void TextureMap<T>::set(int i, int j, T val) {
    colorMap[i * height + j] = val;
}

template<typename T>
TextureMap<T>::~TextureMap() {
    delete[] colorMap;
}

// private methods //

template<typename T>
T TextureMap<T>::get(size_t i, size_t j) const {
    return colorMap[i * height + j];
}

template<typename T>
T TextureMap<T>::bilinInterp(float i, float j) const {
    i -= 0.5; j -= 0.5;
    int iLow = floor(i), iHigh = iLow + 1;
    int jLow = floor(j), jHigh = jLow + 1;
    float a = i - iLow, b = iHigh - i, c = j - jLow, d = jHigh - j;
    if(iLow < 0) iLow = width - 1;
    if(iHigh >= width) iHigh = 0;
    if(jLow < 0) jLow = height - 1;
    if(jHigh >= width) jHigh = 0;
    return b * d * get(iLow, jLow) + a * d * get(iHigh, jLow)
        + b * c * get(iLow, jHigh) + a * c * get(iLow, jLow);
}