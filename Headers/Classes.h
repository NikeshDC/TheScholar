#ifndef CLASSES
#define CLASSES

#include <iostream>
#include <ctime>
class Coord_Rect
{
    float x; //bottom left x co-ordinate
    float y; //bottom left y co-ordinate
    float height;
    float width;
    float xw;
    float yh;

public:
    Coord_Rect(float _x, float _y, float _w, float _h)
    {
        x = _x;
        y = _y;
        width = _w;
        height = _h;
        xw = _x + _w;
        yh = _y + _h;
    }

    Coord_Rect(Coord_Rect a, char dim, float ext)
    {
        switch (dim)
        {
        case ('x'):
        {
            x = (a.x) + ext;
            y = a.y;
            width = a.width;
            height = a.height;
            xw = x + width;
            yh = y + height;
            break;
        }
        case ('y'):
        {
            x = a.x;
            y = (a.y) + ext;
            width = a.width;
            height = a.height;
            xw = x + width;
            yh = y + height;
            break;
        }
        }
    }
    Coord_Rect displace(float _x = 0, float _y = 0)
    {
        return Coord_Rect(x + _x, y + _y, width, height);
    }
    bool liesInside(float x1, float y1) //checks to see if x,y lies inside given rectangular box
    {
        if ((x1 >= x && x1 <= (x + width)) && (y1 >= y && y1 <= (y + height)))
            return true;
        else
            return false;
    }
    float getx()
    {
        return x;
    }
    float gety()
    {
        return y;
    }
    float getwidth()
    {
        return width;
    }
    float getheight()
    {
        return height;
    }
    float getxw()
    {
        return xw;
    }
    float getyh()
    {
        return yh;
    }
};

class Color
{
    float r;
    float g;
    float b;
    float a = DIM_FACTOR;

public:
    Color(float _r, float _g, float _b)
    {
        r = _r;
        g = _g;
        b = _b;
    }
    void setColor(float _r, float _g, float _b)
    {
        r = _r;
        g = _g;
        b = _b;
    }
    void applyColor()
    {
        glColor3f(r, g, b);
    }
    void dimColor()
    {
        float r1 = 0;
        float g1 = 0;
        float b1 = 0;
        if (r - a >= 0)
            r1 = r - a;
        if (g - a >= 0)
            g1 = g - a;
        if (b - a >= 0)
            b1 = b - a;
        glColor3f(r1, g1, b1);
    }
    void briColor()
    {
        float r1 = 1;
        float g1 = 1;
        float b1 = 1;
        if (r + a <= 1)
            r1 = r + a;
        if (g + a <= 1)
            g1 = g + a;
        if (b + a <= 1)
            b1 = b + a;
        glColor3f(r1, g1, b1);
    }
};

class Showtime
{
private:
    float x_pos;
    float y_pos;
    float redn;
    float greenn;
    float bluen;

public:
    Showtime()
    {
        x_pos = 100;
        y_pos = 100;
    }
    Showtime(float x, float y, float r = 1, float g = 0, float b = 0)
    {
        x_pos = x;
        y_pos = y;
        redn = r;
        greenn = g;
        bluen = b;
    }
    void displayClock(void *font)
    {
        time_t tim;
        tim = time(NULL);
        struct tm *local;
        local = localtime(&tim);
        int hr = local->tm_hour;
        if (hr > 12)
            hr -= 12;
        int hr1 = hr / 10;
        int hr2 = hr % 10;

        int mi = local->tm_min;

        int mi1 = mi / 10;
        int mi2 = mi % 10;

        int se = local->tm_sec;

        int se1 = se / 10;
        int se2 = se % 10;

        glColor3f(redn, greenn, bluen);

        glRasterPos2f(x_pos, y_pos);
        glutBitmapCharacter(font, static_cast<char>(hr1 + 48));

        glRasterPos2f(x_pos + 1.35, y_pos);
        glutBitmapCharacter(font, static_cast<char>(hr2 + 48));

        glRasterPos2f(x_pos + 2.72, y_pos);
        glutBitmapCharacter(font, static_cast<char>(58));

        glRasterPos2f(x_pos + 3.5, y_pos);
        glutBitmapCharacter(font, static_cast<char>(mi1 + 48));

        glRasterPos2f(x_pos + 4.75, y_pos);
        glutBitmapCharacter(font, static_cast<char>(mi2 + 48));

        glRasterPos2f(x_pos + 5.8, y_pos);
        glutBitmapCharacter(font, static_cast<char>(58));

        glRasterPos2f(x_pos + 6.5, y_pos);
        glutBitmapCharacter(font, static_cast<char>(se1 + 48));

        glRasterPos2f(x_pos + 8.15, y_pos);
        glutBitmapCharacter(font, static_cast<char>(se2 + 48));

        glColor3f(1.0, 1.0, 0.0);
    }

    void displayCalendar(float calX, float calY, void *font)
    {
        time_t cal;
        cal = time(NULL);
        struct tm *local;
        local = localtime(&cal);

        int year = (local->tm_year) + 1900;

        int y[2];
        y[2] = year % 10;
        year /= 10;
        y[1] = year % 10;
        year /= 10;
        y[0] = year % 10;
        year /= 10;

        int month = (local->tm_mon) + 1;

        int m1 = month / 10;
        int m2 = month % 10;

        int day = local->tm_mday;

        int d1 = day / 10;
        int d2 = day % 10;

        glColor3f(redn, greenn, bluen);
        //YEAR
        glRasterPos2f(calX, calY);
        glutBitmapCharacter(font, static_cast<char>(y[2] + 48));

        glRasterPos2f(calX - 1.35, calY);
        glutBitmapCharacter(font, static_cast<char>(y[1] + 48));

        glRasterPos2f(calX - 2.7, calY);
        glutBitmapCharacter(font, static_cast<char>(y[0] + 48));

        glRasterPos2f(calX - 4, calY);
        glutBitmapCharacter(font, static_cast<char>(year + 48));

        glRasterPos2f(calX + 1.5, calY);
        glutBitmapCharacter(font, static_cast<char>(47));

        //MONTH
        glRasterPos2f(calX + 2.5, calY);
        glutBitmapCharacter(font, static_cast<char>(m1 + 48));

        glRasterPos2f(calX + 3.65, calY);
        glutBitmapCharacter(font, static_cast<char>(m2 + 48));

        glRasterPos2f(calX + 5.05, calY);
        glutBitmapCharacter(font, static_cast<char>(47));

        //DAY
        glRasterPos2f(calX + 5.65, calY);
        glutBitmapCharacter(font, static_cast<char>(d1 + 48));

        glRasterPos2f(calX + 7.2, calY);
        glutBitmapCharacter(font, static_cast<char>(d2 + 48));
    }
};
#endif // CLASSES
