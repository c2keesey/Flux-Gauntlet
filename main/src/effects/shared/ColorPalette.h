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
    ColorPalette(const std::vector<CHSV> &colorList, int hueVar = 5, int satVar = 5, int valVar = 5)
    {
        hueVariance = hueVar;
        satVariance = satVar;
        valVariance = valVar;

        colors = colorList;
        std::vector<CHSV>::const_iterator it = std::find(colorList.begin(), colorList.end(), CHSV(0, 0, 0));
        if (it != colorList.end())
        {
            isTwoColorSpread = false;
            colors.erase(it);
        }
    }

    CHSV getExactColor(size_t index) const
    {
        if (index < colors.size())
        {
            return colors[index];
        }
        return CHSV(0, 0, 0);
    }

    CHSV getExactRandomColor() const
    {
        if (!colors.empty())
        {
            size_t randomIndex = random(colors.size());
            return colors[randomIndex];
        }
        return CHSV(0, 0, 0);
    }

    CHSV getRandomSpreadTwoColor() const
    {
        return getBlendedColor(0, 1, random8());
    }

    CHSV getColor(size_t index)
    {
        if (index < colors.size())
        {
            lastIndex = index;

            CHSV color = colors[index];

            int h = color.h + random(-hueVariance, hueVariance);
            int s = color.s + random(-satVariance, satVariance);
            int v = color.v + random(-valVariance, valVariance);

            color.h = constrain(h, 0, 255);
            color.s = constrain(s, 0, 255);
            color.v = constrain(v, 0, 255);

            return color;
        }
        return CHSV(0, 0, 0);
    }

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

    CHSV getNextColor()
    {
        u8_t nextIndex = (lastIndex + 1) % colors.size();
        return getColor(nextIndex);
    }

    size_t size() const
    {
        return colors.size();
    }
};

#endif // COLORPALETTE_H