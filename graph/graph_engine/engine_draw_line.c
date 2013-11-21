# include <data_structures.h>

# include "../graph_engine.h"

/*
    bresenham
*/
static si_t
__draw_line_with_bresenham__
(struct screen * s,
 struct rectangle * r,
 struct color * c,
 si_t x1,
 si_t y1,
 si_t x2,
 si_t y2)
{
    si_t a, b, delta, x, y, dx, dy, stepx, stepy, i;

    /* 竖直线 */
    if(x1 == x2)
    {
        return screen_set_v_line(s, r, c, x1, y1, x2, y2);
    }

    /* 水平线 */
    if(y1 == y2)
    {
        return screen_set_h_line(s, r, c, x1, y1, x2, y2);
    }

    /* 特殊的斜线 */
    if(ABSOLUTE_I(x1 - x2) == ABSOLUTE_I(y1 -y2))
    {
        return screen_set_x_line(s, r, c, x1, y1, x2, y2);
    }

    dx = ABSOLUTE_I(x1 - x2);
    dy = ABSOLUTE_I(y1 - y2);

    if(x2 > x1)
    {
        stepx = 1;
    }
    else
    {
        stepx = -1;
    }

    if(y2 > y1)
    {
        stepy = 1;
    }
    else
    {
        stepy = -1;
    }

    x = x1;
    y = y1;

    /* -1 < 斜率 < +1 */
    if(dx > dy)
    {
        a = dy << 1;
        b = (dy - dx) << 1;
        delta = (dy << 1) - dx;

        for(i = 0; i <= dx; ++ i)
        {
            screen_set_pixel(s, r, c, x, y);
            x += stepx;
            if(delta < 0)
            {
                delta += a;
            }
            else
            {
                delta += b;
                y += stepy;
            }
        }
    }
    /* 斜率 <= -1 或者 +1 <= 斜率 */
    else
    {
        a = dx << 1;
        b = (dx - dy) << 1;
        delta = (dx << 1) - dy;

        for(i = 0; i <= dy; ++ i)
        {
            screen_set_pixel(s, r, c, x, y);
            y += stepy;
            if(delta < 0)
            {
                delta += a;
            }
            else
            {
                delta += b;
                x += stepx;
            }
        }
    }

    return 0;
}

si_t
engine_draw_line
(si_t graphics_device_handle,
 si_t x1,
 si_t y1,
 si_t x2,
 si_t y2)
{
    struct graphics_device * gd;

    gd = (struct graphics_device *)graphics_device_handle;

    /*
    return __draw_line_with_dda__(&(gd->screen), &(gd->rectangle), &(gd->color), x1, y1, x2, y2);
    */

    /*
    return __draw_line_with_mp__(&(gd->screen), &(gd->rectangle), &(gd->color), x1, y1, x2, y2);
    */

    return __draw_line_with_bresenham__(&(gd->screen), &(gd->rectangle), &(gd->color), x1, y1, x2, y2);
}
