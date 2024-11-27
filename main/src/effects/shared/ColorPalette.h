#ifndef COLORPALETTE_H
#define COLORPALETTE_H

#include <FastLED.h>
#include <vector>

/**
 * @brief A class to handle color palettes
 * Acts differently based on the number of colors in the palette.
 * If there are only 2 colors, random will blend between them.
 */
class ColorPalette
{
private:
    std::vector<CHSV> colors;
    u8_t hueVariance;
    u8_t satVariance;
    u8_t valVariance;
    u8_t lastIndex = 0;
    bool isTwoColorSpread = true;

public:
    /**
     * @brief Constructs a ColorPalette with the given colors and variance parameters
     * @param colorList Vector of CHSV colors to use in the palette
     * @param hueVar Amount of random variance to apply to hue (default: 5)
     * @param satVar Amount of random variance to apply to saturation (default: 5)
     * @param valVar Amount of random variance to apply to value/brightness (default: 5)
     */
    ColorPalette(const std::vector<CHSV> &colorList, int hueVar = 5, int satVar = 5, int valVar = 5)
    {
        hueVariance = hueVar;
        satVariance = satVar;
        valVariance = valVar;

        colors = colorList;

        // Remove CHSV(0, 0, 0) using a lambda for accurate comparison
        auto it = std::remove_if(colors.begin(), colors.end(), [](const CHSV &c)
                                 { return (c.h == 0 && c.s == 0 && c.v == 0); });
        colors.erase(it, colors.end());

        // Determine if it's a two-color spread based on the remaining colors
        isTwoColorSpread = (colors.size() == 2);
    }

    /**
     * @brief Gets a color at the specified index without any random variance
     * @param index Index of the color to retrieve
     * @return The exact CHSV color at the index, or black if index is invalid
     */
    CHSV getExactColor(size_t index) const
    {
        if (index < colors.size())
        {
            return colors[index];
        }
        return CHSV(0, 0, 0);
    }

    /**
     * @brief Gets a random color from the palette without any variance
     * @return A random CHSV color from the palette, or black if palette is empty
     */
    CHSV getExactRandomColor() const
    {
        if (!colors.empty())
        {
            size_t randomIndex = random(colors.size());
            return colors[randomIndex];
        }
        return CHSV(0, 0, 0);
    }

    /**
     * @brief Gets a random color blended between the first two colors in the palette
     * @return A CHSV color randomly blended between colors[0] and colors[1]
     */
    CHSV getRandomSpreadTwoColor() const
    {
        return getBlendedColor(0, 1, random8());
    }

    /**
     * @brief Gets a color at the specified index with random variance applied
     * @param index Index of the color to retrieve
     * @return The CHSV color at the index with variance, or black if index is invalid
     */
    CHSV getColor(size_t index)
    {
        if (index < colors.size())
        {
            lastIndex = index;

            CHSV color = colors[index];

            int h = color.h + random(-hueVariance, hueVariance);
            int s = color.s + random(-satVariance, 0);
            int v = color.v + random(-valVariance, 0);

            color.h = h % 255;
            color.s = constrain(s, 0, 255);
            color.v = constrain(v, 0, 255);

            return color;
        }
        return CHSV(0, 0, 0);
    }

    /**
     * @brief Gets a random color from the palette with variance
     * For two-color palettes, returns a blend between the colors
     * @return A random CHSV color (with variance) from the palette, or black if empty
     */
    CHSV getRandomColor()
    {
        if (colors.size() == 2 && isTwoColorSpread)
        {
            return getRandomSpreadTwoColor();
        }
        if (!colors.empty())
        {
            size_t randomIndex = getNewRandomIndex();
            return getColor(randomIndex);
        }
        return CHSV(0, 0, 0);
    }

    /**
     * @brief Gets a new random index different from the last used index
     * @return A random index into the color palette
     */
    size_t getNewRandomIndex()
    {
        if (colors.size() == 1)
        {
            return 0;
        }
        size_t randomIndex = random(colors.size());
        while (randomIndex == lastIndex)
        {
            randomIndex = random(colors.size());
        }
        return randomIndex;
    }

    /**
     * @brief Blends two colors from the palette by the specified amount
     * @param index1 Index of the first color
     * @param index2 Index of the second color
     * @param blendAmt Amount to blend (0 = all color1, 255 = all color2)
     * @return The blended CHSV color, or black if either index is invalid
     */
    CHSV getBlendedColor(size_t index1, size_t index2, uint8_t blendAmt) const
    {
        if (index1 < colors.size() && index2 < colors.size())
        {
            CHSV color1 = colors[index1];
            CHSV color2 = colors[index2];

            uint8_t hue = blend8(color1.h, color2.h, blendAmt);
            uint8_t saturation = blend8(color1.s, color2.s, blendAmt);
            uint8_t value = blend8(color1.v, color2.v, blendAmt);
            return CHSV(hue, saturation, value);
        }
        return CHSV(0, 0, 0);
    }

    /**
     * @brief Gets the next color in sequence with variance applied
     * @return The next CHSV color in the palette rotation
     */
    CHSV getNextColor()
    {
        u8_t nextIndex = (lastIndex + 1) % colors.size();
        return getColor(nextIndex);
    }

    /**
     * @brief Returns the number of colors in the palette
     * @return Size of the color palette
     */
    size_t size() const
    {
        return colors.size();
    }

    /**
     * @brief Rotates the hue of a single-color palette
     * Only works if the palette contains exactly one color
     * @param index The new hue value (modulo 255)
     */
    void rotate(int index)
    {
        if (size() != 1)
        {
            return;
        }
        colors[0].h = (index % 255);
    }
};

#endif // COLORPALETTE_H
