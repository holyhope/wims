package atp;

import java.awt.Color;
import java.awt.image.RGBImageFilter;

class ColorMaskFilter extends RGBImageFilter
{

    ColorMaskFilter(Color color1)
    {
        maskORinvert = false;
        color = color1;
        maskORinvert = false;
        canFilterIndexColorModel = true;
    }

    ColorMaskFilter(Color color1, boolean flag)
    {
        maskORinvert = false;
        color = color1;
        maskORinvert = flag;
        canFilterIndexColorModel = true;
    }

    public int filterRGB(int i, int j, int k)
    {
        if(maskORinvert)
            return 0x1fff0000;
        int l = k & 0xffffff;
        if(l == 0xffffff)
            return l;
        else
            return 0xff000000 | color.getRGB();
    }

    Color color;
    boolean maskORinvert;
}
