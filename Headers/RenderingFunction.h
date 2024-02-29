#ifndef RENDERING_FUNCTIONS
#define RENDERING_FUNCTIONS

#include "./Classes.h"
#include <cmath>

void glDrawP(float x, float y, float w, float h)
{
    glBegin(GL_POLYGON);
    glVertex2f(x, y);
    glVertex2f(x + w, y);
    glVertex2f(x + w, y + h);
    glVertex2f(x, y + h);
    glEnd();
}
void glDrawP(Coord_Rect p)
{
    glBegin(GL_POLYGON);
    glVertex2f(p.getx(), p.gety());
    glVertex2f(p.getxw(), p.gety());
    glVertex2f(p.getxw(), p.getyh());
    glVertex2f(p.getx(), p.getyh());
    glEnd();
}
void DrawCircle(float cx, float cy, float r, int num_segments)
{
    glBegin(GL_LINE_LOOP);
    for (int ii = 0; ii < num_segments; ii++)
    {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments); //get the current angle

        float x = r * cosf(theta); //calculate the x component
        float y = r * sinf(theta); //calculate the y component

        glVertex2f(x + cx, y + cy); //output vertex
    }
    glEnd();
}
void printText(float x, float y, Color rgb = Color(1, 1, 1), const char *text = "", void *font = GLUT_BITMAP_HELVETICA_12)
{
    rgb.applyColor();
    char *c;
    glRasterPos2f(x, y);
    char buf[100] = {0};
    sprintf(buf, text);
    for (c = buf; *c != '\0'; c++)
    {
        glutBitmapCharacter(font, *c);
    }
    glColor3f(1.0, 1.0, 0.0);
    glutPostRedisplay();
}
void printText(float x, float y, Color rgb = Color(1, 1, 1), std::string text = "", void *font = GLUT_BITMAP_HELVETICA_12)
{
    rgb.applyColor();
    char *c;
    glRasterPos2f(x, y);
    char buf[100] = {0};
    sprintf(buf, text.c_str());
    for (c = buf; *c != '\0'; c++)
    {
        glutBitmapCharacter(font, *c);
    }
    glColor3f(1.0, 1.0, 0.0);
    glutPostRedisplay();
}
void printText(std::string tex, double x, double y, float max_x, void *font)
{
    glRasterPos2d(x, y);
    int i = 0, a;
    float tsize = tex.size() * CHAR_WIDTH;
    if (tsize < (max_x - x))
        a = 0;
    else
        a = (tex.size() - (int)((max_x - x) / CHAR_WIDTH));

    for (i = a; tex[i] != '\0'; i++)
    {
        glutBitmapCharacter(font, tex[i]);
    }
    glColor3f(0, 0, 0);
    glutPostRedisplay();
}
inline float pixToFloat(int wid);
void printTextForDes(std::string text, double x, double y, float max_x, void *font)
{
    glRasterPos2d(x, y);
    float cur_x =x;
    const float gap_y = CHAR_HEIGHT*2;
    for (int i = 0; i < text.size(); i++)
    {
        if(cur_x >= max_x)
        {
            //std::cout<<"\nX;"<<cur_x<<"Y:"<<y;
            y-=gap_y;
            cur_x = x;
            glRasterPos2d(x, y);
        }
        //std::cout<<"\nX;"<<cur_x<<"Y:"<<y;
        glutBitmapCharacter(font, text[i]);
        cur_x += pixToFloat(glutBitmapWidth(font, text[i]));
    }
    glutPostRedisplay();
}
void printTextInBox(std::string tex, Coord_Rect pos, void *font, float GAP = CHAR_WIDTH * 2)
{
    float x = pos.getx() + GAP;
    float y = pos.gety() + GAP;
    float max_x = pos.getxw() - GAP;
    glRasterPos2d(x, y);
    int i = 0, a;
    float tsize = (tex.size()) * CHAR_WIDTH;
    //float cur_x = x;
    /*for(a = tex.size()-1; a>=0; a--)
    {
        cur_x+= pixToFloat(glutBitmapWidth(font, tex[a]));
        if(cur_x >= max_x)
            break;
    }*/
    if (tsize < (max_x - x))
        a = 0;
    else
        a = (tex.size() - (int)((max_x - x) / CHAR_WIDTH));

    for (i = a; i<tex.size(); i++)
    {
        glutBitmapCharacter(font, tex[i]);
    }
    glutPostRedisplay();
}
void printTextPass(std::string tex, Coord_Rect pos, void *font)
{
    float GAP = CHAR_WIDTH * 1.5; //PADDING
    float x = pos.getx() + GAP;
    float y = pos.gety() + GAP;
    int max_Len = ((pos.getwidth()) / CHAR_WIDTH) - 6.5; //To Stop Overflow caused by error in CHAR_WIDTH
    glRasterPos2d(x, y);
    for (int j = 0; j < max_Len && j < tex.size(); j++)
    {
        glutBitmapCharacter(font, CHAR_MASK);
    }
    glutPostRedisplay();
}
void printMaxTextInButton(std::string text, Coord_Rect dim, void *font = GLUT_BITMAP_HELVETICA_12, float GAP_X = CHAR_WIDTH * 2, float GAP_Y = CHAR_WIDTH * 2)
{
    float cur_x =dim.getx();
    float max_x = dim.getxw() - pixToFloat(glutBitmapWidth(font, '.')) * 8;
    glRasterPos2f(dim.getx() + GAP_X, dim.gety() + GAP_Y);
    for (int i=0; i<text.size(); i++)
    {
        if(cur_x >= max_x)
        {
            glutBitmapCharacter(font, '.');
            glutBitmapCharacter(font, '.');
            glutBitmapCharacter(font, '.');
            break;
        }
        glutBitmapCharacter(font, text[i]);
        cur_x+= pixToFloat(glutBitmapWidth(font, text[i]));
    }
    glutPostRedisplay();
}
void printMaxTextInButton(std::string text, float x, float y,float _max_x, void *font = GLUT_BITMAP_HELVETICA_12, float GAP_X = CHAR_WIDTH * 2, float GAP_Y = CHAR_WIDTH * 2)
{
    float cur_x =x;
    float max_x = max_x - pixToFloat(glutBitmapWidth(font, '.')) * 8;
    glRasterPos2f(x + GAP_X, y + GAP_Y);
    for (int i=0; i<text.size(); i++)
    {
        if(cur_x >= max_x)
        {
            glutBitmapCharacter(font, '.');
            glutBitmapCharacter(font, '.');
            glutBitmapCharacter(font, '.');
            break;
        }
        glutBitmapCharacter(font, text[i]);
        cur_x+= pixToFloat(glutBitmapWidth(font, text[i]));
    }
    glutPostRedisplay();
}

void printTextInButton(std::string text, Coord_Rect dim, void *font = GLUT_BITMAP_HELVETICA_12, float GAP_X = CHAR_WIDTH * 2, float GAP_Y = CHAR_WIDTH * 2)
{
    char *c;
    glRasterPos2f(dim.getx() + GAP_X, dim.gety() + GAP_Y);
    char buf[100] = {0};
    sprintf(buf, text.c_str());
    for (c = buf; *c != '\0'; c++)
    {
        glutBitmapCharacter(font, *c);
    }
    glColor3f(1.0, 1.0, 0.0);
    glutPostRedisplay();
}



float toFloatX(int x)
{
    float tx;

    tx = static_cast<float>(x) / (WID / (2 * COORD_X));

    if (tx < COORD_X)
    {
        tx = (COORD_X - tx) * (-1);
    }
    if (tx > COORD_X)
    {
        tx = (tx - COORD_X);
    }
    return tx;
}
inline float pixToFloat(int wid)
{
    //(10+toFloatX(wid))%10;
    return (static_cast<float>(wid) / WID) * (2 * COORD_X);
}
float toFloatY(int y)
{
    float ty = static_cast<float>(y) / (HEI / (2 * COORD_Y));
    if (ty < COORD_Y)
    {
        ty = COORD_Y - ty;
    }
    if (ty > COORD_Y)
    {
        ty = (ty - COORD_Y) * (-1);
    }
    return ty;
}
void glDrawRecOutline(float a, float b, float c, float d)
{
    glBegin(GL_LINES);
    glVertex2f(a, b); //LefttLine
    glVertex2f(a, d);

    glVertex2f(c, b); //RightLine
    glVertex2f(c, d);

    glVertex2f(a, b); //RLowerLine
    glVertex2f(c, b);

    glVertex2f(a, d); //UpperLine
    glVertex2f(c, d);
    glEnd();
}
void glDrawRecOutlineTextBox(Coord_Rect pos)
{
    float PADDING = CHAR_WIDTH / 1.5;
    float x = pos.getx() + PADDING;
    float y = pos.gety() + PADDING;
    float xw = pos.getxw() - PADDING;
    float yh = pos.getyh() - PADDING;
    glBegin(GL_LINES);
    glVertex2f(x, y); //BottomLine
    glVertex2f(xw, y);

    glVertex2f(xw, y); //RightLine
    glVertex2f(xw, yh);

    glVertex2f(xw, yh); //TopLine
    glVertex2f(x, yh);

    glVertex2f(x, yh); //LeftLine
    glVertex2f(x, y);
    glEnd();
}
void glDrawRecOutlineCoordBox(Coord_Rect pos)
{
    glBegin(GL_LINES);
    glVertex2f(pos.getx(), pos.gety()); //BottomLine
    glVertex2f(pos.getxw(), pos.gety());

    glVertex2f(pos.getxw(), pos.gety()); //RightLine
    glVertex2f(pos.getxw(), pos.getyh());

    glVertex2f(pos.getxw(), pos.getyh()); //TopLine
    glVertex2f(pos.getx(), pos.getyh());

    glVertex2f(pos.getx(), pos.getyh()); //LeftLine
    glVertex2f(pos.getx(), pos.gety());
    glEnd();
}
#endif // RENDERING_FUNCTIONS
