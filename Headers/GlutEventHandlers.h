#ifndef GLUT_EVENT_HANDLER
#define GLUT_EVENT_HANDLER

#include "./vars.h"
#include "./GUICompClass.h"
#include "./FileHandler.h"
#include "./GUIPages.h"
#include "./ErrorWindow.h"
#include "./GUIBlocks.h"
#include "DatabaseSearch.h"
#include "RelavantOptions.h"
//#include "./Events.h"

void mousePressed(int button, int state, int x, int y);
void keyPressed(unsigned char key, int x, int y);
void mouseMotion(int x, int y);
void callBackFun();
void initColor();
void ReshapeCallBack(int wid, int heig);
void createErrorWindow(const char *);
void showClock();
void getSearchResults();
void reloadReadingScrollBox();
void reloadFavouriteScrollBox();
void reloadSharedScrollBox();
void reloadCompletedScrollBox();
int windowWidth();
int windowHeight();

//For pages
GUIPage loginPage;
GUIPage signupPage;
GUIPage welcomePage;
GUIPage homePage;
GUIPage bookDetailPage;
GUIPage searchingPage;

/*** Navigate Pages ****/
int PAGE = 0;
enum
{
    WELCOME_P = 0,
    LOGIN_P = 1,
    SIGNUP_P = 2,
    HOME_P = 3,
    BOOK_DETAIL_P = 4,
    SEARCH_P = 5
};

std::vector<GUIPage *> activePage = {&welcomePage, &loginPage, &signupPage, &homePage, &bookDetailPage, &searchingPage};
//end of page navigator

//for blocks
GUIBlock readingB;
GUIBlock completedB;
GUIBlock favouriteB;
GUIBlock shareB;

/**** Navigate Blocks in HOME_PAGE *****/
int BLOCK = 0;
enum
{
    READING_MP = 0,
    COMPLETED_MP = 1,
    FAVOURITE_MP = 2,
    SHARED_MP = 3
};
std::vector<GUIBlock *> activeBlock = {&readingB, &completedB, &favouriteB, &shareB};

namespace REVIEW
{
    void updateRatingToFile(std::string bookDesPath, float _rating, std::string reviewedFilePath);
    bool hasRated(std::string bookDesPath, std::string reviewedFilePath);
} // namespace REVIEW
namespace USERS_BOOKS
{
    std::vector<DATABASE_SEARCH::BookDescriptor> reading;
    std::vector<std::string> reading_name;
    std::vector<std::string> reading_bookmark;
    std::vector<DATABASE_SEARCH::BookDescriptor> completed;
    std::vector<std::string> completed_name;
    std::vector<std::string> completed_bookmark;
    std::vector<DATABASE_SEARCH::BookDescriptor> favourite;
    std::vector<std::string> favourite_name;
    std::vector<DATABASE_SEARCH::BookDescriptor> shared;
    std::vector<std::string> share_name;
    std::vector<std::string> shared_bookmark;
    std::vector<std::string> rBookPath;
    std::vector<std::string> cBookPath;
    std::vector<std::string> fBookPath;
    std::vector<std::string> sBookPath;
    void clearAll()
    {
        rBookPath.clear();
        cBookPath.clear();
        fBookPath.clear();
        sBookPath.clear();
        reading_name.clear();
        completed_name.clear();
        reading_bookmark.clear();
        reading.clear();
        completed_bookmark.clear();
        completed_name.clear();
        completed.clear();
        shared.clear();
        shared_bookmark.clear();
        share_name.clear();
        favourite_name.clear();
        favourite.clear();
    }
} // namespace USERS_BOOKS

void changeBackgroundColor()
{
    if (PAGE == LOGIN_P)
    {
        WC_R = 0.1;
        WC_G = 0.1;
        WC_B = 0.1;
    }
    else if (PAGE == SIGNUP_P)
    {
        WC_R = 0.1;
        WC_G = 0.1;
        WC_B = 0.1;
    }
    else if (PAGE == BOOK_DETAIL_P)
    {
        WC_R = 0.55;
        WC_G = 0.55;
        WC_B = 0.5;
    }
    else if (PAGE == HOME_P)
    {
        WC_R = 0.87;
        WC_G = 0.67;
        WC_B = 0.29;
    }
    else if (PAGE == SEARCH_P)
    {
        WC_R = 0;
        WC_G = 0.46;
        WC_B = 0.4;
    }
}

//end blocks
void callBackFun()
{
    initColor();
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    WID = windowWidth();
    HEI = windowHeight();
    changeBackgroundColor();

    activePage[PAGE]->render();
    if (PAGE == HOME_P)
    {
        activeBlock[BLOCK]->render();
    }

    glutPostRedisplay();
    glutSwapBuffers();
}
void ReshapeCallBack(int wid, int heig)
{
    glViewport(0, 0, wid, heig);                      //full screen has been taken as view port //all drawings are displayed in the view port
    glMatrixMode(GL_PROJECTION);                      //Switches to projection mode to draw stuff on the window //from GL model view matrix(default)
    glLoadIdentity();                                 //resets the parameters of projection matrix
    gluOrtho2D(-COORD_X, COORD_X, -COORD_Y, COORD_Y); //takes 4 arguments left,right,bottom,top (2D graph)
    glMatrixMode(GL_MODELVIEW);                       //switches back to model-view mode,the default mode
                                                      //always should be in model view matrix , only go to projection matrix to set coordinates
}
void initColor()
{
    glClearColor(WC_R, WC_G, WC_B, WC_A);
}

void mousePressed(int button, int state, int x, int y)
{
    activePage[PAGE]->mouseHandler(button, state, x, y);
    if (PAGE == WELCOME_P)
    {
        if (activePage[PAGE]->buttonPressed(&welcome::signupButton))
        {
            PAGE = SIGNUP_P;
            activePage[LOGIN_P]->setActiveBox(&SignUp::userNameB);
        }
        else if (activePage[PAGE]->buttonPressed(&welcome::loginButton))
        {
            PAGE = LOGIN_P;
            activePage[LOGIN_P]->setActiveBox(&LogIn::userNameB);
        }
        else if (activePage[PAGE]->buttonPressed(&welcome::exitButton))
            exit(EXIT_SUCCESS);
    }

    else if (PAGE == LOGIN_P)
    {
        if (activePage[PAGE]->buttonPressed(&LogIn::logInButton))
        {
            userName = activePage[PAGE]->getText(&LogIn::userNameB);
            password = activePage[PAGE]->getText(&LogIn::passwordB);
            //std::cout << "\nUser = " << userName << "\nPass = " << password << "\n";
            logIn LogInObject(userName, password);

            if (LogInObject.IsLogedIn())
            {
                PAGE = HOME_P;
                activePage[HOME_P]->setText(&Home::User, &userName);
                USERS_BOOKS::clearAll();
                //reading scroll box
                reloadReadingScrollBox();
                //completed scroll box
                reloadCompletedScrollBox();
                //favourite scroll box
                reloadFavouriteScrollBox();
                //share scroll box
                reloadSharedScrollBox();
            }
            else
            {
                createErrorWindow("User name or password incorrect!");
            }
        }
        else if (activePage[PAGE]->buttonPressed(&LogIn::toSignup))
        {
            PAGE = SIGNUP_P;
            activePage[LOGIN_P]->setActiveBox(&SignUp::userNameB);
        }
        else if (activePage[PAGE]->buttonPressed(&LogIn::exitButton))
            exit(EXIT_SUCCESS);
    }
    else if (PAGE == SIGNUP_P)
    {
        if (activePage[PAGE]->buttonPressed(&SignUp::signUpButton))
        {
            userNameN = activePage[PAGE]->getText(&SignUp::userNameB);
            passwordN = activePage[PAGE]->getText(&SignUp::passwordB);
            //std::cout << "\nUser = " << userNameN << "\nPass = " << passwordN << "\n";
            if (userNameN == "" || passwordN == "")
            {
                createErrorWindow("UserName and Password required!");
            }
            else
            {
                signUp SignUpObject(userNameN, passwordN);
                if (!SignUpObject.valid())
                {
                    createErrorWindow("Password must contain at least a digit, an alphabet and a special character.");
                }
                else if (SignUpObject.userExists())
                {
                    createErrorWindow("User already exists. Try Logging In.");
                }
                else
                {
                    SignUpObject.signup();
                    userName = userNameN;
                    password = passwordN;
                    activePage[HOME_P]->setText(&Home::User, &userNameN);
                    PAGE = HOME_P;
                    USERS_BOOKS::clearAll();
                    USERS_BOOKS::clearAll();
                    //reading scroll box
                    reloadReadingScrollBox();
                    //completed scroll box
                    reloadCompletedScrollBox();
                    //favourite scroll box
                    reloadFavouriteScrollBox();
                    //share scroll box
                    reloadSharedScrollBox();
                }
            }
        }
        else if (activePage[PAGE]->buttonPressed(&SignUp::toLogin))
        {
            PAGE = LOGIN_P;
            activePage[LOGIN_P]->setActiveBox(&LogIn::userNameB);
        }
        else if (activePage[PAGE]->buttonPressed(&SignUp::exitButton))
            exit(EXIT_SUCCESS);
    }
    else if (PAGE == HOME_P)
    {
        activeBlock[BLOCK]->mouseHandler(button, state, x, y);
        activeBlock[BLOCK]->mouseMotionHandler(x, y);
        if (activePage[PAGE]->buttonPressed(&Home::logoutButton))
        {
            PAGE = LOGIN_P;
            BLOCK = READING_MP;
            userName = "";
            password = "";
            activePage[PAGE]->setText(&SearchN::SNameB, "");
            activePage[PAGE]->setText(&SearchN::SAuthorB, "");
            activePage[PAGE]->setText(&SearchN::SGenreB, "");
            activePage[PAGE]->setText(&SearchN::SDateB, "");
            SearchN::relevantOptionsList.setData(std::vector<std::string>());
            SearchN::searchResultList.setData(std::vector<std::string>());
            activePage[LOGIN_P]->setText(&LogIn::userNameB, &userName);
            activePage[LOGIN_P]->setText(&LogIn::passwordB, &userName);
            activePage[LOGIN_P]->setActiveBox(&LogIn::userNameB);
            activePage[LOGIN_P]->setActiveBox(&LogIn::passwordB, false);
            activePage[SIGNUP_P]->setText(&SignUp::userNameB, &userName);
            activePage[SIGNUP_P]->setText(&SignUp::passwordB, &userName);
            activePage[SIGNUP_P]->setActiveBox(&SignUp::userNameB);
            activePage[SIGNUP_P]->setActiveBox(&SignUp::passwordB, false);
            activeBlock[BLOCK]->setActiveScrollBox(&readingN::BookListReading, true);
            activeBlock[BLOCK]->setActiveScrollBox(&completedN::BookListCompleted, false);
            activeBlock[BLOCK]->setActiveScrollBox(&favouriteN::BookListFavourite, false);
            activeBlock[BLOCK]->setActiveScrollBox(&sharedN::BookListShare, false);
            BookDetails::page.changeMode('R');
            SearchN::prevButton.show(false);
        }
        else if (activePage[PAGE]->buttonPressed(&Home::readingButton))
        {
            BLOCK = READING_MP;
            activeBlock[BLOCK]->setActiveScrollBox(&readingN::BookListReading, true);
            activeBlock[BLOCK]->setActiveScrollBox(&completedN::BookListCompleted, false);
            activeBlock[BLOCK]->setActiveScrollBox(&favouriteN::BookListFavourite, false);
            activeBlock[BLOCK]->setActiveScrollBox(&sharedN::BookListShare, false);
            BookDetails::page.changeMode('R');
        }
        else if (activePage[PAGE]->buttonPressed(&Home::completedButton))
        {
            BLOCK = COMPLETED_MP;
            activeBlock[BLOCK]->setActiveScrollBox(&readingN::BookListReading, false);
            activeBlock[BLOCK]->setActiveScrollBox(&completedN::BookListCompleted, true);
            activeBlock[BLOCK]->setActiveScrollBox(&favouriteN::BookListFavourite, false);
            activeBlock[BLOCK]->setActiveScrollBox(&sharedN::BookListShare, false);
            BookDetails::page.changeMode('C');
        }
        else if (activePage[PAGE]->buttonPressed(&Home::favouriteButton))
        {
            BLOCK = FAVOURITE_MP;
            activeBlock[BLOCK]->setActiveScrollBox(&readingN::BookListReading, false);
            activeBlock[BLOCK]->setActiveScrollBox(&completedN::BookListCompleted, false);
            activeBlock[BLOCK]->setActiveScrollBox(&favouriteN::BookListFavourite, true);
            activeBlock[BLOCK]->setActiveScrollBox(&sharedN::BookListShare, false);
            BookDetails::page.changeMode('F');
        }
        else if (activePage[PAGE]->buttonPressed(&Home::sharedButton))
        {
            BLOCK = SHARED_MP;
            activeBlock[BLOCK]->setActiveScrollBox(&readingN::BookListReading, false);
            activeBlock[BLOCK]->setActiveScrollBox(&completedN::BookListCompleted, false);
            activeBlock[BLOCK]->setActiveScrollBox(&favouriteN::BookListFavourite, false);
            activeBlock[BLOCK]->setActiveScrollBox(&sharedN::BookListShare, true);
            BookDetails::page.changeMode('S');
        }
        else if (activePage[PAGE]->buttonPressed(&Home::searchButton))
        {
            PREV_PAGE = SEARCH_P;
            PAGE = SEARCH_P;
            prevMode = BookDetails::page.getMode();
        }
        if (activeBlock[BLOCK]->buttonPressed(button, state, x, y, &readingN::BookListReading))
        {
            bookNameSB = activeBlock[BLOCK]->getButtonText(button, state, x, y, &readingN::BookListReading);
            bookNameIndex = activeBlock[BLOCK]->getButtonIndex(button, state, x, y, &readingN::BookListReading);
            BookDetails::page.setDescription(USERS_BOOKS::reading[bookNameIndex], USERS_BOOKS::reading_bookmark[bookNameIndex]);
            PAGE = BOOK_DETAIL_P;
            PREV_PAGE = HOME_P;
        }
        else if (activeBlock[COMPLETED_MP]->buttonPressed(button, state, x, y, &completedN::BookListCompleted))
        {
            bookNameIndex = activeBlock[BLOCK]->getButtonIndex(button, state, x, y, &completedN::BookListCompleted);
            bookNameSB = activeBlock[BLOCK]->getButtonText(button, state, x, y, &completedN::BookListCompleted);
            BookDetails::page.setDescription(USERS_BOOKS::completed[bookNameIndex], USERS_BOOKS::completed_bookmark[bookNameIndex]);
            PAGE = BOOK_DETAIL_P;
            PREV_PAGE = HOME_P;
            //PREV_BLOCK = BLOCK;
        }
        else if (activeBlock[BLOCK]->buttonPressed(button, state, x, y, &favouriteN::BookListFavourite))
        {
            bookNameIndex = activeBlock[BLOCK]->getButtonIndex(button, state, x, y, &favouriteN::BookListFavourite);
            bookNameSB = activeBlock[BLOCK]->getButtonText(button, state, x, y, &favouriteN::BookListFavourite);
            BookDetails::page.setDescription(USERS_BOOKS::favourite[bookNameIndex], "No Bookmark");
            PAGE = BOOK_DETAIL_P;
            PREV_PAGE = HOME_P;
        }
        else if (activeBlock[BLOCK]->buttonPressed(button, state, x, y, &sharedN::BookListShare))
        {
            bookNameIndex = activeBlock[BLOCK]->getButtonIndex(button, state, x, y, &sharedN::BookListShare);
            bookNameSB = activeBlock[BLOCK]->getButtonText(button, state, x, y, &sharedN::BookListShare);
            BookDetails::page.setDescription(USERS_BOOKS::shared[bookNameIndex], USERS_BOOKS::shared_bookmark[bookNameIndex]);
            PAGE = BOOK_DETAIL_P;
            PREV_PAGE = HOME_P;
        }
    }
    else if (PAGE == BOOK_DETAIL_P)
    {
        if (activePage[PAGE]->buttonPressedBD(&BookDetails::page, &BookDetails::page.backButton))
        {
            PAGE = PREV_PAGE;
            USERS_BOOKS::clearAll();
            //reading scroll box
            reloadReadingScrollBox();
            //completed scroll box
            reloadCompletedScrollBox();
            //favourite scroll box
            reloadFavouriteScrollBox();
            //share scroll box
            reloadSharedScrollBox();
            // BLOCK = PREV_BLOCK;
        }
        else if (activePage[PAGE]->buttonPressedBD(&BookDetails::page, &BookDetails::page.reviewButton))
        {
            reviewT = activePage[PAGE]->getTextBD(&BookDetails::page, &BookDetails::page.reviewNum);
            activePage[PAGE]->setTextBD(&BookDetails::page, &BookDetails::page.reviewNum, "");
            int rating = reviewT[0] - 48;
            if (rating <= 5 && rating >= 0)
            {
                //must change reviewed.txt to actual path based on user
                std::string reviewedFilePath = "./users/" + Home::User.getText() + "/reviewed.txt";
                REVIEW::updateRatingToFile(BookDetails::page.getDesPath(), rating, reviewedFilePath);
            }
            //std::cout<<rating;
        }
        else if (activePage[PAGE]->buttonPressedBD(&BookDetails::page, &BookDetails::page.sharedButton))
        {
            shareT = activePage[PAGE]->getTextBD(&BookDetails::page, &BookDetails::page.shareUser);
            activePage[PAGE]->setTextBD(&BookDetails::page, &BookDetails::page.shareUser, "");
            bookmarkT = activePage[PAGE]->getTextBD(&BookDetails::page, &BookDetails::page.bookmarkText);
            if (bookmarkT.size() == 0)
                bookmarkT = Home::User.getText() + " with no Bookmark";
            else
                bookmarkT = Home::User.getText() + " with Bookmark: " + bookmarkT;
            activePage[PAGE]->setTextBD(&BookDetails::page, &BookDetails::page.bookmarkText, "");
            //write in share of another user
            FileWriter shareWriter(shareT);
            if (!shareWriter.UserExists())
            {
                createErrorWindow("User does not exist");
            }
            else
            {
                shareWriter.Writer(4, BookDetails::page.getDesPath(), bookmarkT);
            }
            //std::cout << bookmarkT << " " << reviewT << " " << shareT << "\n";
        }
        else if (activePage[PAGE]->buttonPressedBD(&BookDetails::page, &BookDetails::page.readingButton))
        {
            //std::cout << "Reading Button Pressed. in share";
            FileWriter fw(userName);
            fw.Writer(1, BookDetails::page.getDesPath());
            if (BookDetails::page.getMode() == 'S')
            {
                //fw.Writer(1, USERS_BOOKS::sBookPath[bookNameIndex]);
                fw.maskBookName(bookNameIndex, 'S');
            }
            else if (BookDetails::page.getMode() == 'F')
            {
                //fw.Writer(1, USERS_BOOKS::fBookPath[bookNameIndex]);
                fw.maskBookName(bookNameIndex, 'F');
            }
            else if (BookDetails::page.getMode() == 'O')
            {
                USERS_BOOKS::reading.push_back(DATABASE_SEARCH::bdlist[bindex]);
            }
        }
        else if (activePage[PAGE]->buttonPressedBD(&BookDetails::page, &BookDetails::page.favouriteButton) && (BookDetails::page.getMode() == 'C'))
        {
            //std::cout << "Fav Button Pressed in completed";
            FileWriter fw(userName);
            fw.Writer(3, BookDetails::page.getDesPath());
            fw.maskBookName(bookNameIndex, 'C');
        }
        else if (activePage[PAGE]->buttonPressedBD(&BookDetails::page, &BookDetails::page.bookmarkButton) && (BookDetails::page.getMode() == 'C'))
        {
            bookmarkT = activePage[PAGE]->getTextBD(&BookDetails::page, &BookDetails::page.bookmarkText);
            activePage[PAGE]->setTextBD(&BookDetails::page, &BookDetails::page.bookmarkText, "");
            //std::cout << "bookmark in completed";
            FileWriter fw(userName);
            fw.updateBookmark(bookNameIndex, 'C', USERS_BOOKS::cBookPath[bookNameIndex], bookmarkT);
            BookDetails::page.bookDes[6] = bookmarkT;
        }
        else if (activePage[PAGE]->buttonPressedBD(&BookDetails::page, &BookDetails::page.completedButton) && (BookDetails::page.getMode() == 'R'))
        {
            //std::cout << "Read Button Pressed in reading";
            FileWriter fw(userName);
            fw.Writer(2, BookDetails::page.getDesPath());
            fw.maskBookName(bookNameIndex, 'R');
        }
        else if (activePage[PAGE]->buttonPressedBD(&BookDetails::page, &BookDetails::page.favouriteButton) && (BookDetails::page.getMode() == 'R'))
        {
            //std::cout << "Fav Button Pressed in reading";
            FileWriter fw(userName);
            fw.Writer(3, BookDetails::page.getDesPath());
            fw.maskBookName(bookNameIndex, 'R');
        }
        else if (activePage[PAGE]->buttonPressedBD(&BookDetails::page, &BookDetails::page.bookmarkButton) && (BookDetails::page.getMode() == 'R'))
        {
            bookmarkT = activePage[PAGE]->getTextBD(&BookDetails::page, &BookDetails::page.bookmarkText);
            activePage[PAGE]->setTextBD(&BookDetails::page, &BookDetails::page.bookmarkText, "");
            //std::cout << "bookmark in reading";
            FileWriter fw(userName);
            fw.updateBookmark(bookNameIndex, 'R', BookDetails::page.getDesPath(), bookmarkT);
            BookDetails::page.bookDes[6] = bookmarkT;
        }
        else if (activePage[PAGE]->buttonPressedBD(&BookDetails::page, &BookDetails::page.openBookButton))
        {
            //Opens file externally
            Utility::FileHandler::openFileExternal(BookDetails::page.getBookPath());
        }
        else if (activePage[PAGE]->buttonPressedBD(&BookDetails::page, &BookDetails::page.removeButton))
        {
            FileWriter fw(userName);
            fw.maskBookName(bookNameIndex, BookDetails::page.getMode());
            PAGE = PREV_PAGE;
            USERS_BOOKS::clearAll();
            //reading scroll box
            reloadReadingScrollBox();
            //completed scroll box
            reloadCompletedScrollBox();
            //favourite scroll box
            reloadFavouriteScrollBox();
            //share scroll box
            reloadSharedScrollBox();
        }
    }
    else if (PAGE == SEARCH_P)
    {
        if (activePage[PAGE]->buttonPressed(&SearchN::backButton))
        {
            PAGE = HOME_P;
            BookDetails::page.changeMode(prevMode);
        }
        else if (activePage[PAGE]->buttonPressed(&SearchN::searchButton))
        {
            DATABASE_SEARCH::date_search_lines.clear();
            SearchN::searchIndex = 0;
            getSearchResults();
        }
        else if (activePage[SEARCH_P]->buttonPressed(button, state, x, y, &SearchN::searchResultList))
        {
            bindex = activePage[PAGE]->getButtonIndex(button, state, x, y, &SearchN::searchResultList);
            //std::cout << bindex;
            BookDetails::page.setDescription(DATABASE_SEARCH::bdlist[bindex], "page 1");
            PAGE = BOOK_DETAIL_P;
            BookDetails::page.changeMode('O');
        }
        else if (activePage[SEARCH_P]->buttonPressed(button, state, x, y, &SearchN::relevantOptionsList))
        {
            std::string bText = activePage[PAGE]->getButtonText(button, state, x, y, &SearchN::relevantOptionsList);
            //std::cout << bText;
            if (activePage[PAGE]->isActiveBox(&SearchN::SNameB))
            {
                SearchN::SNameB.setText(bText);
            }
            else if (activePage[PAGE]->isActiveBox(&SearchN::SAuthorB))
            {
                SearchN::SAuthorB.setText(bText);
            }
            else if (activePage[PAGE]->isActiveBox(&SearchN::SGenreB))
            {
                SearchN::SGenreB.setText(bText);
            }
        }
        else if (activePage[PAGE]->buttonPressed(&SearchN::nextButton))
        {
            SearchN::searchIndex++;
            SearchN::prevButton.show(true);
            getSearchResults();
        }
        else if (activePage[PAGE]->buttonPressed(&SearchN::prevButton))
        {
            SearchN::searchIndex--;
            getSearchResults();
            if (SearchN::searchIndex == 0)
            {
                SearchN::prevButton.show(false);
            }
        }
        else if (SearchN::bookCB.isActive())
        {
            if (article_flag == 1)
            {
                article_flag = 0;
                DATABASE_SEARCH::SEARCH_DIRS::setDirsForBook();
                RELEVANT_OPTIONS::SEARCH_DIRS::setDirsForBook();
            }
        }
        else if (SearchN::articleCB.isActive())
        {
            if (article_flag == 0)
            {
                article_flag = 1;
                DATABASE_SEARCH::SEARCH_DIRS::setDirsForArticle();
                RELEVANT_OPTIONS::SEARCH_DIRS::setDirsForArticle();
            }
        }
    }
}
void keyPressed(unsigned char key, int x, int y)
{
    activePage[PAGE]->keyboardHandler(key, x, y);
    if (PAGE == LOGIN_P)
    {
        if (activePage[PAGE]->isActiveBox(&LogIn::userNameB) && (key == ENTER_KEY || key == TAB_KEY))
        {
            activePage[PAGE]->setActiveBox(&LogIn::userNameB, false);
            activePage[PAGE]->setActiveBox(&LogIn::passwordB);
        }
        else if (activePage[PAGE]->isActiveBox(&LogIn::passwordB) && (key == ENTER_KEY || key == TAB_KEY))
        {
            if (key == TAB_KEY)
            {
                activePage[PAGE]->setActiveBox(&LogIn::passwordB, false);
                activePage[PAGE]->setActiveBox(&LogIn::userNameB);
            }
            else if (key == ENTER_KEY)
            {
                userName = activePage[PAGE]->getText(&LogIn::userNameB);
                password = activePage[PAGE]->getText(&LogIn::passwordB);
                //std::cout << "\nUser = " << userName << "\nPass = " << password << "\n";
                logIn LogInObject(userName, password);

                if (LogInObject.IsLogedIn())
                {
                    PAGE = HOME_P;
                    activePage[HOME_P]->setText(&Home::User, &userName);
                    USERS_BOOKS::clearAll();
                    //reading scroll box
                    reloadReadingScrollBox();
                    //completed scroll box
                    reloadCompletedScrollBox();
                    //favourite scroll box
                    reloadFavouriteScrollBox();
                    //share scroll box
                    reloadSharedScrollBox();
                }
                else
                {
                    createErrorWindow("User name or password incorrect!");
                }
            }
        }
    }
    else if (PAGE == SIGNUP_P)
    {
        if (activePage[PAGE]->isActiveBox(&SignUp::userNameB) && (key == ENTER_KEY || key == TAB_KEY))
        {
            activePage[PAGE]->setActiveBox(&SignUp::userNameB, false);
            activePage[PAGE]->setActiveBox(&SignUp::passwordB);
        }
        else if (activePage[PAGE]->isActiveBox(&SignUp::passwordB) && (key == ENTER_KEY || key == TAB_KEY))
        {
            if (key == TAB_KEY)
            {
                activePage[PAGE]->setActiveBox(&SignUp::passwordB, false);
                activePage[PAGE]->setActiveBox(&SignUp::userNameB);
            }
            else if (key == ENTER_KEY)
            {
                userNameN = activePage[PAGE]->getText(&SignUp::userNameB);
                passwordN = activePage[PAGE]->getText(&SignUp::passwordB);
                //std::cout << "\nUser = " << userNameN << "\nPass = " << passwordN << "\n";
                if (userNameN == "" || passwordN == "")
                {
                    createErrorWindow("UserName and Password required!");
                }
                else
                {
                    signUp SignUpObject(userNameN, passwordN);
                    if (!SignUpObject.valid())
                    {
                        createErrorWindow("Password must contain at least a digit, an alphabet and a special character.");
                    }
                    else if (SignUpObject.userExists())
                    {
                        createErrorWindow("User already exists. Try Logging In.");
                    }
                    else
                    {
                        SignUpObject.signup();
                        userName = userNameN;
                        password = passwordN;
                        activePage[HOME_P]->setText(&Home::User, &userNameN);
                        PAGE = HOME_P;
                        USERS_BOOKS::clearAll();
                        //reading scroll box
                        reloadReadingScrollBox();
                        //completed scroll box
                        reloadCompletedScrollBox();
                        //favourite scroll box
                        reloadFavouriteScrollBox();
                        //share scroll box
                        reloadSharedScrollBox();
                    }
                }
            }
        }
    }
    else if (PAGE == BOOK_DETAIL_P)
    {
        if (activePage[PAGE]->isActiveBox(&BookDetails::page, &BookDetails::page.bookmarkText) && key == ENTER_KEY)
        {
            bookmarkT = activePage[PAGE]->getTextBD(&BookDetails::page, &BookDetails::page.bookmarkText);
            activePage[PAGE]->setTextBD(&BookDetails::page, &BookDetails::page.bookmarkText, "");
        }
        else if (activePage[PAGE]->isActiveBox(&BookDetails::page, &BookDetails::page.reviewNum) && key == ENTER_KEY)
        {
            reviewT = activePage[PAGE]->getTextBD(&BookDetails::page, &BookDetails::page.reviewNum);
            activePage[PAGE]->setTextBD(&BookDetails::page, &BookDetails::page.reviewNum, "");
        }
        else if (activePage[PAGE]->isActiveBox(&BookDetails::page, &BookDetails::page.shareUser) && key == ENTER_KEY)
        {
            shareT = activePage[PAGE]->getTextBD(&BookDetails::page, &BookDetails::page.shareUser);
            activePage[PAGE]->setTextBD(&BookDetails::page, &BookDetails::page.shareUser, "");
            //std::cout << bookmarkT << " " << reviewT << " " << shareT << "\n";
        }
    }
    else if (PAGE == SEARCH_P)
    {
        if (key == ENTER_KEY || key == TAB_KEY)
        {
            if (activePage[PAGE]->isActiveBox(&SearchN::SNameB))
            {
                activePage[PAGE]->setActiveBox(&SearchN::SAuthorB, true);
                activePage[PAGE]->setActiveBox(&SearchN::SNameB, false);
            }
            else if (activePage[PAGE]->isActiveBox(&SearchN::SAuthorB))
            {
                activePage[PAGE]->setActiveBox(&SearchN::SGenreB, true);
                activePage[PAGE]->setActiveBox(&SearchN::SAuthorB, false);
            }
            else if (activePage[PAGE]->isActiveBox(&SearchN::SGenreB))
            {
                activePage[PAGE]->setActiveBox(&SearchN::SDateB, true);
                activePage[PAGE]->setActiveBox(&SearchN::SGenreB, false);
            }
            else if (activePage[PAGE]->isActiveBox(&SearchN::SDateB) && key == ENTER_KEY)
            {
                getSearchResults();
            }
        }
        else
        {
            if (activePage[PAGE]->isActiveBox(&SearchN::SNameB) && SearchN::SNameB.getText().size() > 0)
            {
                RELEVANT_OPTIONS::results.clear();
                RELEVANT_OPTIONS::result_size = 0;
                RELEVANT_OPTIONS::getRelevantBookNames(Utility::String::getLowerCase(SearchN::SNameB.getText()), RELEVANT_OPTIONS::results, RELEVANT_OPTIONS::result_size);
                /*for(int i=0; i< RELEVANT_OPTIONS::results.size(); i++)
                    Utility::String::manageCase(RELEVANT_OPTIONS::results[i]);*/
                SearchN::relevantOptionsList.setData(RELEVANT_OPTIONS::results);
                SearchN::relevantOptionsList.setActive(true);
                SearchN::searchResultList.setActive(false);
            }
            else if (activePage[PAGE]->isActiveBox(&SearchN::SAuthorB) && SearchN::SAuthorB.getText().size() > 0)
            {
                RELEVANT_OPTIONS::results.clear();
                RELEVANT_OPTIONS::result_size = 0;
                RELEVANT_OPTIONS::getRelevantBookAuthors(Utility::String::getLowerCase(SearchN::SAuthorB.getText()), RELEVANT_OPTIONS::results, RELEVANT_OPTIONS::result_size);
                /*for(int i=0; i< RELEVANT_OPTIONS::results.size(); i++)
                    Utility::String::manageCase(RELEVANT_OPTIONS::results[i]);*/
                SearchN::relevantOptionsList.setData(RELEVANT_OPTIONS::results);
                SearchN::relevantOptionsList.setActive(true);
                SearchN::searchResultList.setActive(false);
            }
            else if (activePage[PAGE]->isActiveBox(&SearchN::SGenreB) && SearchN::SGenreB.getText().size() > 0)
            {
                RELEVANT_OPTIONS::results.clear();
                RELEVANT_OPTIONS::result_size = 0;
                RELEVANT_OPTIONS::getRelevantBookGenres(Utility::String::getLowerCase(SearchN::SGenreB.getText()), RELEVANT_OPTIONS::results, RELEVANT_OPTIONS::result_size);
                /*for(int i=0; i< RELEVANT_OPTIONS::results.size(); i++)
                    Utility::String::manageCase(RELEVANT_OPTIONS::results[i]);*/
                SearchN::relevantOptionsList.setData(RELEVANT_OPTIONS::results);
                SearchN::relevantOptionsList.setActive(true);
                SearchN::searchResultList.setActive(false);
            }
        }
    }
}
void mouseMotion(int x, int y)
{
    activeBlock[BLOCK]->mouseMotionHandler(x, y);
    //std::cout << "x= " << x << " y= " << y << '\n';
}
void createErrorWindow(const char *err)
{
    if (ErrorWindow::canMake)
        ErrorWindow::create(err, glutGet(GLUT_WINDOW_X) + 150, glutGet(GLUT_WINDOW_Y) + 200);
}
int windowWidth()
{
    return glutGet(GLUT_WINDOW_WIDTH);
}
int windowHeight()
{
    return glutGet(GLUT_WINDOW_HEIGHT);
}
void showClock()
{
    glClear(GL_COLOR_BUFFER_BIT); //Clears the frame buffer of window,good habit
    glLoadIdentity();             //resets the matrix transformation done is previous options(i.e.,make default coordinate points)
    glClearColor(WC_R, WC_G, WC_B, WC_A);
    Showtime s1(-9, 1.5, 1, 1, 1);
    s1.displayClock(GLUT_BITMAP_TIMES_ROMAN_24);
    s1.displayCalendar(-5, -2.5, GLUT_BITMAP_HELVETICA_18);
    glutPostRedisplay();
    glutSwapBuffers();
}
void getSearchResults()
{
    //DATABASE_SEARCH::SEARCH_DIRS::setDirsForBook();
    DATABASE_SEARCH::keywords[DATABASE_SEARCH::NAME] = Utility::String::getLowerCase(activePage[PAGE]->getText(&SearchN::SNameB));
    DATABASE_SEARCH::keywords[DATABASE_SEARCH::AUTHOR] = Utility::String::getLowerCase(activePage[PAGE]->getText(&SearchN::SAuthorB));
    DATABASE_SEARCH::keywords[DATABASE_SEARCH::DATE] = Utility::String::getLowerCase(activePage[PAGE]->getText(&SearchN::SDateB));
    DATABASE_SEARCH::keywords[DATABASE_SEARCH::GENRE] = Utility::String::getLowerCase(activePage[PAGE]->getText(&SearchN::SGenreB));
    DATABASE_SEARCH::bdlist.clear();
    SearchN::nextButton.show(DATABASE_SEARCH::FullSearch(DATABASE_SEARCH::keywords, DATABASE_SEARCH::bdlist, SearchN::searchIndex * DATABASE_SEARCH::MAX_SEARCH_RESULT));
    std::vector<std::string> searchBookNameList;
    for (int i = 0; i < DATABASE_SEARCH::bdlist.size(); i++)
    {
        Utility::String::manageCase(DATABASE_SEARCH::bdlist[i].name);
        searchBookNameList.push_back(DATABASE_SEARCH::bdlist[i].name);
    }
    SearchN::searchResultList.setData(searchBookNameList);
    activePage[PAGE]->setActiveBox(&SearchN::SNameB, false);
    activePage[PAGE]->setActiveBox(&SearchN::SAuthorB, false);
    activePage[PAGE]->setActiveBox(&SearchN::SGenreB, false);
    activePage[PAGE]->setActiveBox(&SearchN::SDateB, false);
    activePage[SEARCH_P]->setActiveBox(&SearchN::relevantOptionsList, false);
    activePage[SEARCH_P]->setActiveBox(&SearchN::searchResultList, true);
}
void reloadReadingScrollBox()
{
    dataf.clear();
    FileReader fr(userName);
    dataf = fr.Reader(READING_MP + 1);
    DATABASE_SEARCH::BookDescriptor bdReading;
    int i = 0;
    for (auto it = dataf.begin(); it != dataf.end(); ++it)
    {
        if (i % 2 == 0)
        {
            bdReading.path = *it;
            bdReading.readFromFile();
            USERS_BOOKS::reading.push_back(bdReading);
            Utility::String::manageCase(bdReading.name);
            USERS_BOOKS::reading_name.push_back(bdReading.name);
            USERS_BOOKS::rBookPath.push_back(bdReading.bookPath);
        }
        else
        {
            USERS_BOOKS::reading_bookmark.push_back(*it);
        }
        i++;
    }
    activeBlock[BLOCK]->setData(&readingN::BookListReading, USERS_BOOKS::reading_name);
    dataf.clear();
}
void reloadCompletedScrollBox()
{
    FileReader fr(userName);
    dataf = fr.Reader(COMPLETED_MP + 1);
    DATABASE_SEARCH::BookDescriptor bdCompleted;
    int i = 0;
    for (auto it = dataf.begin(); it != dataf.end(); ++it)
    {
        if (i % 2 == 0)
        {
            bdCompleted.path = *it;
            bdCompleted.readFromFile();
            USERS_BOOKS::completed.push_back(bdCompleted);
            Utility::String::manageCase(bdCompleted.name);
            USERS_BOOKS::completed_name.push_back(bdCompleted.name);
            USERS_BOOKS::cBookPath.push_back(bdCompleted.bookPath);
        }
        else
        {
            USERS_BOOKS::completed_bookmark.push_back(*it);
        }
        i++;
    }
    activeBlock[BLOCK]->setData(&completedN::BookListCompleted, USERS_BOOKS::completed_name);
    dataf.clear();
}
void reloadFavouriteScrollBox()
{
    FileReader fr(userName);
    dataf = fr.Reader(FAVOURITE_MP + 1);
    DATABASE_SEARCH::BookDescriptor bdFavourite;
    for (auto it : dataf)
    {
        bdFavourite.path = it;
        bdFavourite.readFromFile();
        USERS_BOOKS::favourite.push_back(bdFavourite);
        Utility::String::manageCase(bdFavourite.name);
        USERS_BOOKS::favourite_name.push_back(bdFavourite.name);
        USERS_BOOKS::fBookPath.push_back(bdFavourite.bookPath);
    }
    activeBlock[BLOCK]->setData(&favouriteN::BookListFavourite, USERS_BOOKS::favourite_name);
    dataf.clear();
}
void reloadSharedScrollBox()
{
    FileReader fr(userName);
    dataf = fr.Reader(SHARED_MP + 1);
    DATABASE_SEARCH::BookDescriptor bdShare;
    int i = 0;
    for (auto it = dataf.begin(); it != dataf.end(); ++it)
    {
        if (i % 2 == 0)
        {
            bdShare.path = *it;
            bdShare.readFromFile();
            USERS_BOOKS::shared.push_back(bdShare);
            Utility::String::manageCase(bdShare.name);
            USERS_BOOKS::share_name.push_back(bdShare.name);
            USERS_BOOKS::sBookPath.push_back(bdShare.bookPath);
        }
        else
        {
            USERS_BOOKS::shared_bookmark.push_back(*it);
        }
        i++;
    }
    activeBlock[BLOCK]->setData(&sharedN::BookListShare, USERS_BOOKS::share_name);
    dataf.clear();
}

namespace REVIEW
{
    void updateRatingToFile(std::string bookDesPath, float _rating, std::string reviewedFilePath)
    {
        int updateChoice;
        const int NEW_REVIEW = 1, OVERWRITE_REVIEW = 0;
        if (hasRated(bookDesPath, reviewedFilePath))
        {
            updateChoice = OVERWRITE_REVIEW;
        }
        else
        {
            updateChoice = NEW_REVIEW;
            std::ofstream reviewedFile(reviewedFilePath.c_str(), std::ios::app);
            reviewedFile << bookDesPath << "\n";
            reviewedFile.close();
        }
        std::ifstream bookdesfile;
        std::ofstream tempFile("temp.txt");
        std::string temp;
        int noOfReviews;
        float rating;
        bookdesfile.open(bookDesPath.c_str());
        for (int i = 0; i < 6; i++)
        {
            std::getline(bookdesfile, temp);
            tempFile << temp << "\n";
        }
        bookdesfile >> noOfReviews;
        bookdesfile >> rating;
        if (updateChoice == NEW_REVIEW)
        {
            rating = (_rating + noOfReviews * rating) / (noOfReviews + 1);
            noOfReviews++;
        }
        else
        {
            rating = (_rating + (noOfReviews - 1) * rating) / noOfReviews;
        }
        tempFile << noOfReviews << "\n";
        tempFile << rating;
        BookDetails::page.bookDes[5] = std::to_string(rating);
        BookDetails::page.bookDes[7] = std::to_string(noOfReviews);
        bookdesfile.close();
        tempFile.close();
        remove(bookDesPath.c_str());
        rename("temp.txt", bookDesPath.c_str());
    }

    bool hasRated(std::string bookDesPath, std::string reviewedFilePath)
    {
        std::string path;
        std::ifstream reviewedFile(reviewedFilePath.c_str());
        if (!reviewedFile.good())
            return false;
        while (std::getline(reviewedFile, path))
        {
            if (path == bookDesPath)
            {
                reviewedFile.close();
                return true;
            }
        }
        reviewedFile.close();
        return false;
    }
} // namespace REVIEW
#endif // GLUT_EVENT_HANDLER
