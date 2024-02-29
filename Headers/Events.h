#include "./vars.h"
#include "./GUICompClass.h"
#include "./FileReader.h"
#include "./GUIPages.h"
#include "./ErrorWindow.h"
#include "./GUIBlocks.h"
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
    SEARCH_P =5
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
namespace WelcomeEvents
{
  void mouse()
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
};
