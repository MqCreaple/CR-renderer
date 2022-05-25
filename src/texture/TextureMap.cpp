#include "texture/TextureMap.h"

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
        + b * c * get(iLow, jHigh) + a * c * get(iHigh, jHigh);
}