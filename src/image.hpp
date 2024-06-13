#pragma once

#include <array>

namespace land {

struct Coordinate
{
    int row{};
    int col{};
};

template <typename T, int Height, int Width, int Padding = 0>
struct Image
{
    static constexpr int height()                { return Height; }
    static constexpr int width()                 { return Width; }
    static constexpr int size()                  { return Height * Width; }
    static constexpr int padding()               { return Padding; }
    static constexpr int padded_height()         { return Height+2*Padding; }
    static constexpr int padded_width()          { return Width+2*Padding; }
    static constexpr int padded_size()           { return padded_height() * padded_width(); }
    static constexpr int index(int row, int col) { return (row+Padding)*padded_width() + (col+Padding); } // row-major

    Image() = default;
    Image(std::array<T, size()> const& contents, T padding_value)
    {
        std::fill(_data.begin(), _data.end(), padding_value);
        for (int h = 0; h < Height; ++h)
        {
            for (int w = 0; w < Width; ++w)
            {
                (*this)(h, w) = contents[h*Width + w];
            }
        }
    }
    
    T& operator()(int row, int col)              { return _data[index(row, col)]; }
    T& operator()(Coordinate c)                  { return _data[index(c.row, c.col)]; }
    const T& operator()(int row, int col) const  { return _data[index(row, col)]; }
    const T& operator()(Coordinate c) const      { return _data[index(c.row, c.col)]; }

    std::array<char, padded_size()> _data{};
};

}
