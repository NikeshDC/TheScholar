#ifndef GUI_COMP_CLASS
#define GUI_COMP_CLASS

#include "./RenderingFunction.h"
#include "DatabaseSearch.h"
class GUIcomponent
{
protected:
    bool active;

public:
    GUIcomponent() { active = false; }
    bool isActive() { return active; }
    void setActive(bool _active = true) { active = _active; }

    virtual void render() = 0;
    virtual void mouseHandler(int button, int state, int x, int y) = 0;
    virtual void keyboardHandler(unsigned char key, int x, int y) = 0;
    virtual void mouseMotionHandler(int x, int y) = 0;
};

class TextBox : public GUIcomponent
{
protected:
    bool selected;
    std::string textField;
    Coord_Rect position;
    Color boxC;
    Color textC;
    void *f;
    float padding;
    long blinker;

public:
    TextBox(Coord_Rect pos, Color box = Color(0, 0, 0), Color txt = Color(1, 1, 1), bool _selected = false) : position(pos), boxC(box), textC(txt)
    {
        selected = _selected;
        f = GLUT_BITMAP_HELVETICA_12;
        padding = CHAR_WIDTH * 2;
    }
    std::string getText()
    {
        return textField;
    }
    void setText(std::string _text) //probably won't be used
    {
        textField = _text;
    }
    void setFont(void *_f)
    {
        f = _f;
    }
    void setPadding(float _gap)
    {
        padding = _gap;
    }
    void setActive(bool _active = true)
    {
        active = _active;
        selected = active;
    }
    void render()
    {
        setActive(selected);
        if (isActive())
        {
            boxC.applyColor();
        }
        else
        {
            boxC.dimColor();
        }
        glDrawP(position);
        textC.applyColor();
        glDrawRecOutlineTextBox(position);
        printTextInBox(textField, position, f, padding);
        if (isActive())
        {
            if (blinker % 200 >= 0 && blinker % 200 <= 100)
                glutBitmapCharacter(f, '|');
            blinker++;
        }
        else
            blinker = 0;
    }
    void keyboardHandler(unsigned char key, int x, int y)
    {
        if (selected)
        {
            if (key == ENTER_KEY || key == TAB_KEY)
            {
            }
            else if (key >= 36 && key <= 126 || key == SPACE_KEY)
            {
                textField.push_back(key);
            }
            else if (key = DEL_KEY && textField.size() > 0)
            {
                textField.pop_back();
            }
        }
    }
    void mouseHandler(int button, int state, int x, int y)
    {
        float X = toFloatX(x);
        float Y = toFloatY(y);
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && position.liesInside(X, Y))
        {
            selected = true;
        }
        else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            selected = false;
        }
    }
    void mouseMotionHandler(int x, int y)
    {
        return;
    }
};
class PasswordBox : public TextBox
{
    bool showpass;
    void *f;

public:
    PasswordBox(Coord_Rect pos, Color box = Color(0, 0, 0), Color txt = Color(1, 1, 1), bool _selected = false) : TextBox(pos, box, txt, _selected)
    {
        showpass = false;
        f = GLUT_BITMAP_HELVETICA_12;
    }
    void showPass(bool _showPass)
    {
        showpass = _showPass;
    }
    bool isShowing()
    {
        return showpass;
    }
    void setFont(void *_f)
    {
        f = _f;
    }
    void render()
    {
        setActive(selected);
        if (isActive())
        {
            boxC.applyColor();
        }
        else
        {
            boxC.dimColor();
        }
        glDrawP(position);
        textC.applyColor();
        glDrawRecOutlineTextBox(position);
        if (showpass)
            printTextInBox(textField, position, f);
        else
            printTextPass(TextBox::textField, TextBox::position, GLUT_BITMAP_TIMES_ROMAN_24);
        if (isActive())
        {
            if (blinker % 200 >= 0 && blinker % 200 <= 100)
                glutBitmapCharacter(f, '|');
            blinker++;
        }
        else
            blinker = 0;
    }
};
class Text : public GUIcomponent
{
    float x;
    float y;
    Color rgb;
    void *font;
    std::string text;
    bool background;
    Color backgroundC;
    Coord_Rect backgroundD;

public:
    Text(float _x, float _y, Color _rgb, const char *_text, void *_f, bool _bg = false, Color _bgC = Color(WC_R, WC_G, WC_B), float _w = 0, float _h = 0) : rgb(_rgb), text(std::string(_text)), backgroundC(_bgC), backgroundD(_x - 0.1, _y - 0.3, _w, _h)
    {
        x = _x;
        y = _y;
        font = _f;
        background = _bg;
    }
    Text(float _x, float _y, Color _rgb, std::string _text, void *_f, bool _bg = false, Color _bgC = Color(WC_R, WC_G, WC_B), float _w = 0, float _h = 0) : rgb(_rgb), text(_text), backgroundC(_bgC), backgroundD(_x - 0.1, _y - 0.3, _w, _h)
    {
        x = _x;
        y = _y;
        font = _f;
        background = _bg;
    }
    void setText(std::string *_text)
    {
        text = *_text;
    }
    std::string getText()
    {
        return text;
    }
    void render()
    {
        if (background)
        {
            backgroundC.applyColor();
            glDrawP(backgroundD);
        }
        printText(x, y, rgb, text.c_str(), font);
    }
    void keyboardHandler(unsigned char key, int x, int y)
    {
        return;
    }
    void mouseHandler(int button, int state, int x, int y)
    {
        return;
    }
    void mouseMotionHandler(int x, int y)
    {
        return;
    }
};
class CheckBox : public GUIcomponent
{
    bool selected;
    Coord_Rect dimensions;
    Color colr;
    PasswordBox *parent;
    char mode;
    CheckBox *twin;

public:
    CheckBox(PasswordBox *_parent, float x, float y, Color _colr = Color(1, 1, 1), bool _selected = false) : dimensions(x, y, CHECK_BOX_DIMENSION, CHECK_BOX_DIMENSION), colr(_colr)
    {
        parent = _parent;
        selected = _selected;
        mode = 'P';
        twin = nullptr;
    }
    CheckBox(float x, float y, Color _colr = Color(1, 1, 1), bool _selected = false) : dimensions(x, y, CHECK_BOX_DIMENSION, CHECK_BOX_DIMENSION), colr(_colr)
    {
        parent = nullptr;
        selected = _selected;
        mode = 'A';
        twin = nullptr;
    }
    void setTwin(CheckBox *_cb)
    {
        twin = _cb;
    }
    void setActive(bool _active)
    {
        active = _active;
        selected = active;
        if (mode == 'P')
            parent->setActive(_active);
    }
    void render()
    {
        colr.applyColor();
        glDrawRecOutlineCoordBox(dimensions);
        if (selected)
        {
            colr.briColor();
            glDrawP(dimensions.getx() + 0.09, dimensions.gety() + 0.09, dimensions.getwidth() - 0.18, dimensions.getheight() - 0.15);
        }
    }
    void mouseHandler(int button, int state, int x, int y)
    {
        if (mode == 'P')
        {
            if (dimensions.liesInside(toFloatX(x), toFloatY(y)) && state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
            {
                setActive(!selected);
                parent->showPass(selected);
            }
            // else if (dimensions.liesInside(toFloatX(x), toFloatY(y)) && state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
            // {
            //     setActive(false);
            //     parent->showPass(false);
            // }
        }
        else if (mode == 'A')
        {
            if (dimensions.liesInside(toFloatX(x), toFloatY(y)) && state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
            {
                // if (twin->isActive())
                // {
                //     twin->setActive(false);
                //     setActive(true);
                // }
                setActive(twin->isActive());
                twin->setActive(!twin->isActive());
            }
        }
    }
    void keyboardHandler(unsigned char key, int x, int y)
    {
        return;
    }
    void mouseMotionHandler(int x, int y)
    {
        return;
    }
};
class Button : public GUIcomponent
{
    bool showB;
    bool pressed;
    std::string buttonText;
    Coord_Rect buttonDimension;
    Color buttonColor;
    Color textColor;
    bool forScrollBox;
    float gapX;
    float gapY;
    void *f;

public:
    Button(const char *_text, Color _bColor, Color _tColor, Coord_Rect _dim, float _x = CHAR_WIDTH * 2, float _y = CHAR_WIDTH * 2) : buttonColor(_bColor), textColor(_tColor), buttonDimension(_dim)
    {
        showB = true;
        pressed = false;
        forScrollBox = false;
        buttonText = std::string(_text);
        f = GLUT_BITMAP_HELVETICA_12;
        gapX = _x;
        gapY = _y;
    }
    Button(std::string _text, Color _bColor, Color _tColor, Coord_Rect _dim, float _x = CHAR_WIDTH * 2, float _y = CHAR_WIDTH * 2) : buttonColor(_bColor), textColor(_tColor), buttonDimension(_dim)
    {
        showB = true;
        pressed = false;
        buttonText = _text;
        f = GLUT_BITMAP_HELVETICA_12;
        gapX = _x;
        gapY = _y;
    }
    void setText(std::string _text)
    {
        buttonText = _text;
    }
    void setForScrollBox(bool val = true)
    {
        forScrollBox = val;
    }
    std::string getText()
    {
        return buttonText;
    }
    void setFont(void *_f)
    {
        f = _f;
    }
    void show(bool _show)
    {
        showB = _show;
    }
    bool isActive()
    {
        if (showB)
            return active;
        return false;
    }
    void render()
    {
        if (showB)
        {
            setActive(pressed);
            if (isActive())
            {
                buttonColor.dimColor();
            }
            else
            {
                buttonColor.applyColor();
            }
            glDrawP(buttonDimension);
            textColor.applyColor();
            if(!forScrollBox)
                printTextInButton(buttonText, buttonDimension, f, gapX, gapY);
            else
                printMaxTextInButton(buttonText, buttonDimension, f, gapX, gapY);

        }
    }
    void mouseHandler(int button, int state, int x, int y)
    {
        if (showB)
        {
            if (buttonDimension.liesInside(toFloatX(x), toFloatY(y)) && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
            {
                pressed = true;
            }
            else
            {
                pressed = false;
            }
        }
    }
    void keyboardHandler(unsigned char key, int x, int y)
    {
        return;
    }
    void mouseMotionHandler(int x, int y)
    {
        return;
    }
};
class ScrollBox : public GUIcomponent
{
    std::vector<std::string> data;
    Color bgColor;
    Color textC;
    Coord_Rect dim;
    std::vector<Coord_Rect> bDim;
    std::vector<Button> dataB;
    int maxN;
    int top;
    bool scrolled;
    bool scrollable;
    float scrollerX;
    float scrollerY;
    float scrollerW;
    float scrollerH;
    float dec;
    float prevY;

public:
    ScrollBox(std::vector<std::string> _data, Coord_Rect _dim, int _maxN, Color _bgC = Color(WC_R, WC_G, WC_B), Color _textC = Color(0, 0, 0), bool _scrollable = true) : dim(_dim), bgColor(_bgC), textC(_textC)
    {
        data = _data;
        maxN = _maxN;
        top = 0;
        scrolled = false;
        scrollable = _scrollable;
        scrollerX = dim.getxw();
        scrollerY = dim.getyh() - dim.getheight() / 5;
        scrollerW = dim.getwidth() / 15;
        scrollerH = dim.getheight() / 5;
        dec = 0;
        prevY = scrollerY + scrollerH;
        for (int i = 1; i <= maxN; i++)
        {
            Coord_Rect d(dim.getx(), dim.getyh() - (i * (dim.getheight() / maxN)), dim.getwidth(), (dim.getheight() / maxN));
            bDim.push_back(d);
        }
        for (int i = 0; i < (maxN < data.size() ? maxN : data.size()); i++)
        {
            Button button(data[i], bgColor, textC, bDim[i], 0.1, 0.1);
            button.setForScrollBox();
            dataB.push_back(button);
        }

    }
    bool buttonPressed(int button, int state, int x, int y)
    {
        if (isActive())
            for (int i = 0; i < (maxN < data.size() ? maxN : data.size()); i++)
                if (bDim[i].liesInside(toFloatX(x), toFloatY(y)) && button == GLUT_LEFT && state == GLUT_DOWN)
                    return true;
        return false;
    }
    void refreshBox()
    {
        dec = ((scrollerY - dim.gety()) / (data.size() - maxN));
        int i;
        for (i = 0; i < (maxN < data.size() ? maxN : data.size()); i++)
        {
            dataB[i].setText(data[i + top]);
        }
    }
    void setData(std::vector<std::string> _data)
    {
        data = _data;
        refreshBox();
    }
    std::string getButtonText(int button, int state, int x, int y)
    {
        if (isActive())
            for (int i = 0; i < maxN; i++)
                if (bDim[i].liesInside(toFloatX(x), toFloatY(y)) && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
                {
                    return dataB[i].getText();
                }
        return "";
    }
    int getButtonIndex(int button, int state, int x, int y)
    {
        if (isActive())
            for (int i = 0; i < maxN; i++)
                if (bDim[i].liesInside(toFloatX(x), toFloatY(y)) && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
                {
                    return i + top;
                }
        return 0;
    }

    void render()
    {
        if (isActive())
        {
            if (scrollable)
            {
                if (scrolled)
                {
                    refreshBox();
                    scrolled = false;
                }
                if (data.size() > maxN)
                {
                    glDrawRecOutlineCoordBox(dim);
                    bgColor.briColor();
                    glDrawP(dim.getxw(), dim.gety(), scrollerW, dim.getheight());

                    bgColor.dimColor();
                    glDrawP(scrollerX, scrollerY - top * dec, scrollerW, scrollerH);
                }
            }
            for (int i = 0; i < (maxN < data.size() ? maxN : data.size()); i++)
            {
                dataB[i].render();
                if (i != 0)
                {
                    textC.applyColor();
                    glBegin(GL_LINES);
                    glVertex2f(bDim[i].getx(), bDim[i].getyh());
                    glVertex2f(bDim[i].getxw(), bDim[i].getyh());
                    glEnd();
                }
            }
        }
    }
    void keyboardHandler(unsigned char key, int x, int y)
    {
        return;
    }
    void mouseHandler(int button, int state, int x, int y)
    {
        if (isActive())
        {
            if (scrollable)
            {
                prevY = toFloatY(y);
                if (dim.liesInside(toFloatX(x), toFloatY(y)))
                {
                    if (button == 4 && state == GLUT_DOWN && (data.size() - top > maxN))
                    {
                        top++;
                        scrolled = true;
                    }
                    else if (button == 3 && state == GLUT_DOWN && (top > 0))
                    {
                        top--;
                        scrolled = true;
                    }
                    else
                    {
                        for (int i = 0; i < (maxN < data.size() ? maxN : data.size()); i++)
                            dataB[i].mouseHandler(button, state, x, y);
                    }
                }
            }
            else
            {
                for (int i = 0; i < (maxN < data.size() ? maxN : data.size()); i++)
                    dataB[i].mouseHandler(button, state, x, y);
            }
        }
    }
    void mouseMotionHandler(int x, int y)
    {
        if (data[0] != "")
        {
            if (scrollable)
            {
                Coord_Rect scroller(scrollerX, scrollerY - top * dec, scrollerW, scrollerH);
                if (scroller.liesInside(toFloatX(x), toFloatY(y)) && (data.size() - top > maxN) && toFloatY(y) <= prevY)
                {
                    top++;
                    refreshBox();
                    prevY = toFloatY(y);
                }
                else if (scroller.liesInside(toFloatX(x), toFloatY(y)) && top > 0 && toFloatY(y) > prevY)
                {
                    top--;
                    refreshBox();
                    prevY = toFloatY(y);
                }
            }
            return;
        }
    }
};
class BookDetail : public GUIcomponent
{
    std::string bookname;
    std::string bookpath;
    std::string desPath;
    char mode;
    float bookNamePosX;
    float bookNamePosY;
    float descriptionX;
    float descriptionY;
    float featureButtonX;
    float featureButtonY;

    Color navButtonC;
    Color featureButtonC;
    Color titleTextC;
    Color subTitleTextC;
    Color buttonTextC;
    Color textboxC;
    Color textboxTextC;

    Coord_Rect backButtonD;
    Coord_Rect openBookButtonD;
    void *f1;
    void *f2;

public:
    std::vector<std::string> bookDes;
    Button backButton;
    Button openBookButton;
    Button readingButton;
    Button completedButton;
    Button sharedButton;
    Button favouriteButton;
    Button reviewButton;
    Button bookmarkButton;
    Button removeButton;

    TextBox reviewNum;
    TextBox shareUser;
    TextBox bookmarkText;

    BookDetail(char _mode, std::string _bookname = "", Color _navButtonC = Color(0, 0.18, 0.6), Color _featureButtonC = Color(0.1, 0.28, 0.5), Color _titleTextC = Color(0, 1, 0), Color _subTitleTextC = Color(0, 0, 0), Color _textboxC = Color(0.7, 0.7, 0.72), Color _textboxTextC = Color(0, 0, 0), Coord_Rect _backButtonD = Coord_Rect(7, 8, 2, 1), Coord_Rect _openBookButtonD = Coord_Rect(2.5, -7.5, 3, 1.1), float _bookNamePosX = -9, float _bookNamePosY = 6, float _descriptionX = -8, float _descriptionY = 4, float _featureButtonX = 6.0, float _featureButtonY = 5, Button _tempButton = Button("", Color(0, 0, 0), Color(0, 0, 0), Coord_Rect(0, 0, 0, 0)), TextBox _tempTextBox = TextBox(Coord_Rect(0, 0, 0, 0), Color(0, 0, 0), Color(0, 0, 0))) : navButtonC(_navButtonC), featureButtonC(_featureButtonC), titleTextC(_titleTextC), subTitleTextC(_subTitleTextC), textboxC(_textboxC), textboxTextC(_textboxTextC), backButtonD(_backButtonD), openBookButtonD(_openBookButtonD), backButton(_tempButton), openBookButton(_tempButton), readingButton(_tempButton), completedButton(_tempButton), sharedButton(_tempButton), favouriteButton(_tempButton), reviewButton(_tempButton), bookmarkButton(_tempButton), removeButton(_tempButton), reviewNum(_tempTextBox), shareUser(_tempTextBox), bookmarkText(_tempTextBox), buttonTextC(Color(1, 1, 1))
    {
        mode = _mode;
        bookname = _bookname;
        bookNamePosX = _bookNamePosX;
        bookNamePosY = _bookNamePosY;
        descriptionX = _descriptionX;
        descriptionY = _descriptionY;
        featureButtonX = _featureButtonX;
        featureButtonY = _featureButtonY;
        backButton = Button("Back", navButtonC, buttonTextC, backButtonD, CHAR_WIDTH * 1.2, CHAR_WIDTH * 1.2);
        openBookButton = Button("OPEN BOOK", navButtonC, buttonTextC, openBookButtonD, CHAR_WIDTH, CHAR_WIDTH);
        openBookButton.setFont(GLUT_BITMAP_9_BY_15);
        removeButton = Button("Remove", navButtonC, buttonTextC, Coord_Rect(openBookButtonD, 'x', 4), CHAR_WIDTH * 3, CHAR_WIDTH);
        setButtonAndTextBox();
        f1 = GLUT_BITMAP_HELVETICA_18;
        f2 = GLUT_BITMAP_HELVETICA_12;
    }
    void setDescription(DATABASE_SEARCH::BookDescriptor &bd, std::string bookmark);
    void setButtonAndTextBox();
    void showBookDescription();
    void render();
    void mouseHandler(int button, int state, int x, int y);
    void keyboardHandler(unsigned char key, int x, int y);
    void mouseMotionHandler(int x, int y)
    {
        return;
    }
    void changeMode(char _mode)
    {
        mode = _mode;
        setButtonAndTextBox();
    }
    char getMode()
    {
        return mode;
    }
    std::string getBookPath()
    {
        return bookpath;
    }
    std::string getDesPath()
    {
        return desPath;
    }
    std::string getText(TextBox *_box)
    {
        return _box->getText();
    }
    void setText(TextBox *_box, std::string _text)
    {
        _box->setText(_text);
    }
    bool buttonPressed(Button *_button)
    {
        if (_button->isActive())
            return true;
        return false;
    }
    bool isActiveBox(TextBox *_box)
    {
        return _box->isActive();
    }
};
void BookDetail::setDescription(DATABASE_SEARCH::BookDescriptor &bd, std::string bookmark)
{
    bookDes.clear();
    Utility::String::manageCase(bd.name);
    bookDes.push_back(bd.name);
    std::string AName = "";
    for (int i = 0; i < bd.authors_display.size(); i++)
    {
        bd.authors_display[i][0] = std::toupper(bd.authors_display[i][0]);
        AName += bd.authors_display[i];
        if (i < bd.authors_display.size() - 1)
            AName += ", ";
    }
    Utility::String::manageCase(AName, " -.");
    bookDes.push_back(AName);
    std::string genre = "";
    for (int i = 0; i < bd.genres.size(); i++)
    {
        bd.genres[i][0] = std::toupper(bd.genres[i][0]);
        genre += bd.genres[i];
        if (i < bd.genres.size() - 1)
            genre += ", ";
    }
    Utility::String::manageCase(genre);
    bookDes.push_back(genre);
    bookDes.push_back(bd.date);
    std::string extdes = "";
    for (int i = 0; i < bd.extrades.size(); i++)
    {
        bd.extrades[i][0] = std::toupper(bd.extrades[i][0]);
        extdes += bd.extrades[i];
        if (i < bd.extrades.size() - 1)
            extdes += ". ";
    }
    bookDes.push_back(extdes);
    bookDes.push_back(std::to_string(bd.review));
    if (bookmark == "$")
    {
        bookDes.push_back("No Bookmark!");
    }
    else
    {
        bookDes.push_back(bookmark);
    }

    bookDes.push_back(std::to_string(bd.noOfReveiws));
    bookpath = bd.bookPath;
    desPath = bd.path;
}

void BookDetail::setButtonAndTextBox()
{
    if (mode == 'R')
    {
        completedButton = Button("Add to read", featureButtonC, buttonTextC, Coord_Rect(featureButtonX, featureButtonY - 1, 3, 1), CHAR_WIDTH * 2, CHAR_WIDTH);
        favouriteButton = Button("Add to favourite", featureButtonC, buttonTextC, Coord_Rect(featureButtonX, featureButtonY - 2.2, 3, 1.0), CHAR_WIDTH * 1.5, CHAR_WIDTH);
        bookmarkButton = Button("Add bookmark", featureButtonC, buttonTextC, Coord_Rect(featureButtonX, featureButtonY - 3.4, 3, 1.0), CHAR_WIDTH * 1.5, CHAR_WIDTH);
        sharedButton = Button("Share", featureButtonC, buttonTextC, Coord_Rect(featureButtonX, featureButtonY - 4.6, 3, 1.0), 1.1, CHAR_WIDTH);
        bookmarkText = TextBox(Coord_Rect(featureButtonX - 3, featureButtonY - 3.4, 2.9, 1.1), textboxC, textboxTextC);
        shareUser = TextBox(Coord_Rect(featureButtonX - 3, featureButtonY - 4.6, 2.9, 1.1), textboxC, textboxTextC);
        bookmarkText.setPadding(0.25);
        shareUser.setPadding(0.25);
        removeButton.show(true);
    }
    else if (mode == 'C')
    {
        favouriteButton = Button("Add to favourite", featureButtonC, buttonTextC, Coord_Rect(featureButtonX, featureButtonY - 1, 3, 1.0), CHAR_WIDTH * 1.5, CHAR_WIDTH);
        bookmarkButton = Button("Add bookmark", featureButtonC, buttonTextC, Coord_Rect(featureButtonX, featureButtonY - 2.2, 3, 1.0), CHAR_WIDTH * 1.5, CHAR_WIDTH);
        reviewButton = Button("Rate", featureButtonC, buttonTextC, Coord_Rect(featureButtonX, featureButtonY - 3.4, 3, 1), CHAR_WIDTH * 2, CHAR_WIDTH);
        sharedButton = Button("Share", featureButtonC, buttonTextC, Coord_Rect(featureButtonX, featureButtonY - 4.6, 3, 1.0), 1.1, CHAR_WIDTH);
        bookmarkText = TextBox(Coord_Rect(featureButtonX - 3, featureButtonY - 2.2, 2.9, 1.1), textboxC, textboxTextC);
        reviewNum = TextBox(Coord_Rect(featureButtonX - 3, featureButtonY - 3.4, 1.5, 1.1), textboxC, textboxTextC);
        shareUser = TextBox(Coord_Rect(featureButtonX - 3, featureButtonY - 4.6, 2.9, 1.1), textboxC, textboxTextC);
        bookmarkText.setPadding(0.25);
        shareUser.setPadding(0.25);
        reviewNum.setPadding(0.23);
        removeButton.show(true);
    }
    else if (mode == 'F')
    {
        readingButton = Button("Add to reading", featureButtonC, buttonTextC, Coord_Rect(featureButtonX, featureButtonY - 1, 3, 1), CHAR_WIDTH * 1, CHAR_WIDTH);
        reviewButton = Button("Rate", featureButtonC, buttonTextC, Coord_Rect(featureButtonX, featureButtonY - 2.2, 3, 1), CHAR_WIDTH * 2, CHAR_WIDTH);
        sharedButton = Button("Share", featureButtonC, buttonTextC, Coord_Rect(featureButtonX, featureButtonY - 3.4, 3, 1.0), 1.1, CHAR_WIDTH);
        reviewNum = TextBox(Coord_Rect(featureButtonX - 3, featureButtonY - 2.2, 1.5, 1.1), textboxC, textboxTextC);
        shareUser = TextBox(Coord_Rect(featureButtonX - 3, featureButtonY - 3.4, 2.9, 1.1), textboxC, textboxTextC);
        shareUser.setPadding(0.25);
        reviewNum.setPadding(0.23);
        removeButton.show(true);
    }
    else if (mode == 'S')
    {
        readingButton = Button("Add to reading", featureButtonC, buttonTextC, Coord_Rect(featureButtonX, featureButtonY - 1, 3, 1), CHAR_WIDTH * 1, CHAR_WIDTH);
        removeButton.show(true);
    }
    else if (mode == 'O')
    {
        readingButton = Button("Add to reading", featureButtonC, buttonTextC, Coord_Rect(featureButtonX, featureButtonY - 1, 3, 1), CHAR_WIDTH * 1, CHAR_WIDTH);
        removeButton.show(false);
    }
}
void BookDetail::showBookDescription()
{
    textboxC.applyColor();
    glDrawP(Coord_Rect(descriptionX, descriptionY - 9.7, 13, 5));
    glDrawP(Coord_Rect(-9.4, bookNamePosY - 0.5, 11.8, 1.4));
    glColor3f(0.1, 0.25, 0.88);
    printMaxTextInButton(bookDes[0],Coord_Rect(-9.4, bookNamePosY - 0.5, 11.8, 1.4),GLUT_BITMAP_TIMES_ROMAN_24);
    textboxC.applyColor();
    printText(bookNamePosX + 12, bookNamePosY + 1, titleTextC, "Rating: ", f1);
    printText(descriptionX, descriptionY, titleTextC, "Author Name:", f1);
    printText(descriptionX, descriptionY - 1.5, titleTextC, "Genre:", f1);
    printText(descriptionX, descriptionY - 3, titleTextC, "Published date:", f1);
    printText(descriptionX, descriptionY - 4.5, titleTextC, "Description:", f1);
    printText(bookNamePosX + 12, bookNamePosY, titleTextC, "Number Of Reviews: ", f1);
    printText(descriptionX + 3.5, descriptionY, subTitleTextC, bookDes[1], f2);
    printText(descriptionX + 2, descriptionY - 1.5, subTitleTextC, bookDes[2], f2);
    printText(descriptionX + 4, descriptionY - 3, subTitleTextC, bookDes[3], f2);
    subTitleTextC.applyColor();
    printTextForDes(bookDes[4], descriptionX + 0.5, descriptionY - 5.2, descriptionX + 12, f2);
    printText(bookNamePosX + 13.8, bookNamePosY + 1, subTitleTextC, bookDes[5], f1);
    printText(bookNamePosX + 17, bookNamePosY, subTitleTextC, bookDes[7], f1);
    glColor3f(WC_R, WC_G, WC_B);
    glDrawP(bookNamePosX + 14.5, bookNamePosY + 0.8, 2, 1);
    if (mode == 'S')
    {
        printText(descriptionX, descriptionY - 11, titleTextC, "Shared by:", f1);
        printText(descriptionX + 3, descriptionY - 11, subTitleTextC, bookDes[6], f2);
    }
    else if (mode != 'F' && mode != 'O')
    {
        printText(descriptionX, descriptionY - 11, titleTextC, "Bookmark:", f1);
        printText(descriptionX + 3, descriptionY - 11, subTitleTextC, bookDes[6], f2);
    }
}
void BookDetail::render()
{
    showBookDescription();
    backButton.render();
    openBookButton.render();
    removeButton.render();
    if (mode == 'R')
    {
        completedButton.render();
        favouriteButton.render();
        bookmarkButton.render();
        sharedButton.render();
        bookmarkText.render();
        shareUser.render();
    }
    else if (mode == 'C')
    {
        reviewButton.render();
        favouriteButton.render();
        bookmarkButton.render();
        sharedButton.render();
        bookmarkText.render();
        shareUser.render();
        reviewNum.render();
        printText(featureButtonX - 1.1, featureButtonY - 3, titleTextC, "[0-5]", f2);
    }
    else if (mode == 'F')
    {
        readingButton.render();
        reviewButton.render();
        sharedButton.render();
        shareUser.render();
        reviewNum.render();
        printText(featureButtonX - 1.1, featureButtonY - 1.8, titleTextC, "[0-5]", f2);
    }
    else if (mode == 'S' || mode == 'O')
    {
        readingButton.render();
    }
}
void BookDetail::mouseHandler(int button, int state, int x, int y)
{
    openBookButton.mouseHandler(button, state, x, y);
    backButton.mouseHandler(button, state, x, y);
    removeButton.mouseHandler(button, state, x, y);
    if (mode == 'R')
    {
        completedButton.mouseHandler(button, state, x, y);
        favouriteButton.mouseHandler(button, state, x, y);
        bookmarkButton.mouseHandler(button, state, x, y);
        sharedButton.mouseHandler(button, state, x, y);
        bookmarkText.mouseHandler(button, state, x, y);
        shareUser.mouseHandler(button, state, x, y);
    }
    else if (mode == 'C')
    {
        reviewButton.mouseHandler(button, state, x, y);
        favouriteButton.mouseHandler(button, state, x, y);
        bookmarkButton.mouseHandler(button, state, x, y);
        sharedButton.mouseHandler(button, state, x, y);
        bookmarkText.mouseHandler(button, state, x, y);
        shareUser.mouseHandler(button, state, x, y);
        reviewNum.mouseHandler(button, state, x, y);
    }
    else if (mode == 'F')
    {
        readingButton.mouseHandler(button, state, x, y);
        reviewButton.mouseHandler(button, state, x, y);
        sharedButton.mouseHandler(button, state, x, y);
        shareUser.mouseHandler(button, state, x, y);
        reviewNum.mouseHandler(button, state, x, y);
    }
    else if (mode == 'S' || mode == 'O')
    {
        readingButton.mouseHandler(button, state, x, y);
    }
}
void BookDetail::keyboardHandler(unsigned char key, int x, int y)
{
    backButton.keyboardHandler(key, x, y);
    openBookButton.keyboardHandler(key, x, y);
    if (mode == 'R')
    {
        bookmarkText.keyboardHandler(key, x, y);
        shareUser.keyboardHandler(key, x, y);
    }
    else if (mode == 'C')
    {
        bookmarkText.keyboardHandler(key, x, y);
        shareUser.keyboardHandler(key, x, y);
        reviewNum.keyboardHandler(key, x, y);
    }
    else if (mode == 'F')
    {
        shareUser.keyboardHandler(key, x, y);
        reviewNum.keyboardHandler(key, x, y);
    }
}
class rectOutline : public GUIcomponent
{
    Coord_Rect dimension;
    Color color;

public:
    rectOutline(Coord_Rect _dim, Color _color = Color(0, 0, 0)) : dimension(_dim), color(_color) {}
    void render()
    {
        color.applyColor();
        glDrawRecOutlineCoordBox(dimension);
    }
    void keyboardHandler(unsigned char key, int x, int y)
    {
        return;
    }
    void mouseHandler(int button, int state, int x, int y)
    {
        return;
    }
    void mouseMotionHandler(int x, int y)
    {
        return;
    }
};
class rectBox : public GUIcomponent
{
    Coord_Rect dimension;
    Color color;

public:
    rectBox(Coord_Rect _dim, Color _color = Color(0, 0, 0)) : dimension(_dim), color(_color) {}
    void render()
    {
        color.applyColor();
        glDrawP(dimension);
    }
    void keyboardHandler(unsigned char key, int x, int y)
    {
        return;
    }
    void mouseHandler(int button, int state, int x, int y)
    {
        return;
    }
    void mouseMotionHandler(int x, int y)
    {
        return;
    }
};
class GUIBlock
{
    std::vector<GUIcomponent *> components;

public:
    void addComponent(GUIcomponent *_component)
    {
        components.push_back(_component);
    }
    bool buttonPressed(Button *_button)
    {
        if (_button->isActive())
            return true;
        return false;
    }
    bool buttonPressed(int button, int state, int x, int y, ScrollBox *_sb)
    {
        return _sb->buttonPressed(button, state, x, y);
    }
    void setActiveScrollBox(ScrollBox *_sb, bool _value)
    {
        _sb->setActive(_value);
    }
    std::string getText(TextBox *_textbox)
    {
        return _textbox->getText();
    }
    bool isActiveBox(TextBox *_textbox)
    {
        return _textbox->isActive();
    }
    void setActiveBox(TextBox *_textbox, bool _value = true)
    {
        _textbox->setActive(_value);
    }
    void setText(Text *_textB, std::string *_text)
    {
        _textB->setText(_text);
    }
    void setText(TextBox *_textB, std::string *_text)
    {
        _textB->setText(*_text);
    }
    void setText(TextBox *_textB, const char *_text)
    {
        _textB->setText(_text);
    }
    void setData(ScrollBox *sb, std::vector<std::string> data)
    {
        sb->setData(data);
    }
    std::string getButtonText(int button, int state, int x, int y, ScrollBox *sb)
    {
        return sb->getButtonText(button, state, x, y);
    }
    int getButtonIndex(int button, int state, int x, int y, ScrollBox *sb)
    {
        return sb->getButtonIndex(button, state, x, y);
    }
    void render()
    {
        for (int i = 0; i < components.size(); i++)
            components[i]->render();
    }
    void keyboardHandler(unsigned char key, int x, int y)
    {
        for (int i = 0; i < components.size(); i++)
            components[i]->keyboardHandler(key, x, y);
    }
    void mouseHandler(int button, int state, int x, int y)
    {
        for (int i = 0; i < components.size(); i++)
            components[i]->mouseHandler(button, state, x, y);
    }
    void mouseMotionHandler(int x, int y)
    {
        for (int i = 0; i < components.size(); i++)
            components[i]->mouseMotionHandler(x, y);
    }
};
class GUIPage
{
    std::vector<GUIcomponent *> components;

public:
    void addComponent(GUIcomponent *_component)
    {
        components.push_back(_component);
    }
    bool buttonPressed(Button *_button)
    {
        if (_button->isActive())
            return true;
        return false;
    }
    bool buttonPressedBD(BookDetail *_bd, Button *_button)
    {
        return _bd->buttonPressed(_button);
    }
    bool buttonPressed(int button, int state, int x, int y, ScrollBox *_sb)
    {
        return _sb->buttonPressed(button, state, x, y);
    }
    std::string getText(TextBox *_textbox)
    {
        return _textbox->getText();
    }
    bool isActiveBox(TextBox *_textbox)
    {
        return _textbox->isActive();
    }
    bool isActiveBox(BookDetail *_bd, TextBox *_textbox)
    {
        return _bd->isActiveBox(_textbox);
    }
    void setActiveBox(TextBox *_textbox, bool _value = true)
    {
        _textbox->setActive(_value);
    }
    void setActiveBox(ScrollBox *_sbox, bool _value = true)
    {
        _sbox->setActive(_value);
    }
    void setText(Text *_textB, std::string *_text)
    {
        _textB->setText(_text);
    }
    void setText(TextBox *_textB, std::string *_text)
    {
        _textB->setText(*_text);
    }
    void setText(TextBox *_textB, const char *_text)
    {
        _textB->setText(_text);
    }
    void setData(ScrollBox *sb, std::vector<std::string> data)
    {
        sb->setData(data);
    }
    std::string getButtonText(int button, int state, int x, int y, ScrollBox *sb)
    {
        return sb->getButtonText(button, state, x, y);
    }
    int getButtonIndex(int button, int state, int x, int y, ScrollBox *sb)
    {
        return sb->getButtonIndex(button, state, x, y);
    }
    void setTextBD(BookDetail *_bd, TextBox *_box, std::string _text)
    {
        _bd->setText(_box, _text);
    }
    std::string getTextBD(BookDetail *_bd, TextBox *_box)
    {
        return _bd->getText(_box);
    }
    void render()
    {
        for (int i = 0; i < components.size(); i++)
            components[i]->render();
    }
    void keyboardHandler(unsigned char key, int x, int y)
    {
        for (int i = 0; i < components.size(); i++)
            components[i]->keyboardHandler(key, x, y);
    }
    void mouseHandler(int button, int state, int x, int y)
    {
        for (int i = 0; i < components.size(); i++)
            components[i]->mouseHandler(button, state, x, y);
    }
    void mouseMotionHandler(int x, int y)
    {
        for (int i = 0; i < components.size(); i++)
            components[i]->mouseMotionHandler(x, y);
    }
};
#endif // GUI_COMP_CLASS
