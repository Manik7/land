#include <gtest/gtest.h>
#include "../src/constants.hpp"
#include "../src/image.hpp"
#include "sample.hpp"

namespace {

TEST(image, index)
{
    const land::Image<char, 3, 2> image{};

    EXPECT_EQ(image.index(0, 0), 0);
    EXPECT_EQ(image.index(0, 1), 1);
    EXPECT_EQ(image.index(1, 0), 2);
    EXPECT_EQ(image.index(1, 1), 3);
    EXPECT_EQ(image.index(2, 0), 4);
    EXPECT_EQ(image.index(2, 1), 5);
}

TEST(image, index_padded)
{
    //  .  .  .  .
    //  .  5  6  .
    //  .  9 10  .
    //  . 13 14  .
    //  .  .  .  .

    const land::Image<char, 3, 2, 1> image{};

    EXPECT_EQ(image.index(0, 0), 5);
    EXPECT_EQ(image.index(0, 1), 6);
    EXPECT_EQ(image.index(1, 0), 9);
    EXPECT_EQ(image.index(1, 1), 10);
    EXPECT_EQ(image.index(2, 0), 13);
    EXPECT_EQ(image.index(2, 1), 14);
}

TEST(image, empty)
{
    const land::Image<char, 0, 0> image{};

    ASSERT_EQ(image.size(), 0);
    ASSERT_EQ(image._data.size(), 0);
    EXPECT_EQ(image.height(), 0);
    EXPECT_EQ(image.width(), 0);
}

TEST(image, symbols)
{
    const land::Image<char, 1, 5> image(land::symbols, SYMBOL::WATER);

    ASSERT_EQ(image.size(), 5);
    ASSERT_EQ(image._data.size(), 5);
    EXPECT_EQ(image.height(), 1);
    EXPECT_EQ(image.width(), 5);
    EXPECT_EQ(image(0, 0), '.');
    EXPECT_EQ(image(0, 1), '+');
    EXPECT_EQ(image(0, 2), '*');
    EXPECT_EQ(image(0, 3), '@');
    EXPECT_EQ(image(0, 4), '^');
}

TEST(image, six)
{
    const land::Image<char, 3, 2> image({'a', 'b', 'c', 'd', 'e', 'f'}, SYMBOL::WATER);

    ASSERT_EQ(image.size(), 6);
    ASSERT_EQ(image._data.size(), 6);
    EXPECT_EQ(image.height(), 3);
    EXPECT_EQ(image.width(), 2);
    EXPECT_EQ(image(0, 0), 'a');
    EXPECT_EQ(image(0, 1), 'b');
    EXPECT_EQ(image(1, 0), 'c');
    EXPECT_EQ(image(1, 1), 'd');
    EXPECT_EQ(image(2, 0), 'e');
    EXPECT_EQ(image(2, 1), 'f');
}

TEST(image, six_padded)
{
    const land::Image<char, 3, 2, 1> image({'a', 'b', 'c', 'd', 'e', 'f'}, SYMBOL::WATER);

    ASSERT_EQ(image.size(), 6);
    ASSERT_EQ(image.height(), 3);
    ASSERT_EQ(image.width(), 2);
    ASSERT_EQ(image.padded_size(), 20);
    ASSERT_EQ(image.padded_height(), 5);
    ASSERT_EQ(image.padded_width(), 4);
    EXPECT_EQ(image(0, 0), 'a');
    EXPECT_EQ(image(0, 1), 'b');
    EXPECT_EQ(image(1, 0), 'c');
    EXPECT_EQ(image(1, 1), 'd');
    EXPECT_EQ(image(2, 0), 'e');
    EXPECT_EQ(image(2, 1), 'f');
}

}
