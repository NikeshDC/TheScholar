/**** Welcome Page *****/
namespace welcome
{
    float devInfoX = -9.1;
    float devInfoY = -4.5;
    Color titleC(1, 0.95, 0);
    Color devInfo(1, 0.95, 0);
    Color loginButtonC(0, 0, 0.46);
    Color loginButtonTextC(1, 1, 1);
    Color exitButtonC(0.85, 0.85, 0.85);
    Color exitButtonTextC(0, 0, 0);

    Coord_Rect exitButtonD(8.1, 8.7, 1.4, 0.9);
    Coord_Rect loginButtonD(2, -8, 2.5, 1.2);
    Coord_Rect signupButtonD(loginButtonD, 'x', 3.4);

    Text titleT(-2.5, 2.5, titleC, "THE SCHOLAR", GLUT_BITMAP_TIMES_ROMAN_24);
    //Text subTitleT(-2.2, 1.8, titleC, "E-lib of some sort", GLUT_BITMAP_HELVETICA_18);
    Text devInfoA(devInfoX, devInfoY, devInfo, "DEVELOPED BY:", GLUT_BITMAP_TIMES_ROMAN_24);
    Text devInfoB(devInfoX, devInfoY - 1, devInfo, "Ravi Pandey", GLUT_BITMAP_HELVETICA_18);
    Text devInfoC(devInfoX, devInfoY - 2, devInfo, "Rohan Chhetry", GLUT_BITMAP_HELVETICA_18);
    Text devInfoD(devInfoX, devInfoY - 3, devInfo, "Nikesh D.C.", GLUT_BITMAP_HELVETICA_18);
    Button loginButton("Log In", loginButtonC, loginButtonTextC, loginButtonD,CHAR_WIDTH*1.9, 0.45);
    Button signupButton("Sign Up", loginButtonC, loginButtonTextC, signupButtonD,CHAR_WIDTH*1.2, 0.45);
    Button exitButton("EXIT", exitButtonC, exitButtonTextC, exitButtonD, CHAR_WIDTH * 1.1, CHAR_WIDTH * 1.1);

    void addWelcomComponents(GUIPage *_welcomePage)
    {
        loginButton.setFont(GLUT_BITMAP_9_BY_15);
        signupButton.setFont(GLUT_BITMAP_9_BY_15);
        _welcomePage->addComponent(&titleT);
        //_welcomePage->addComponent(&subTitleT);
        _welcomePage->addComponent(&devInfoA);
        _welcomePage->addComponent(&devInfoB);
        _welcomePage->addComponent(&devInfoC);
        _welcomePage->addComponent(&devInfoD);
        _welcomePage->addComponent(&loginButton);
        _welcomePage->addComponent(&signupButton);
        _welcomePage->addComponent(&exitButton);
    }
}; // namespace welcome
/**** Login Page *****/
namespace LogIn
{
    Color userNameC(0.95, 0.95, 0.9);
    Color passwordC = userNameC;
    Color boxTextC(0, 0, 0);
    Color logInTextC(1, 1, 0);
    Color loginButtonC(1, 0.97, 0);
    Color loginButtonTextC(0, 0, 0);
    Color toSignupC(0.3, 0.9, 0.6);
    Color pageTextC(1, 0.95, 0);
    Color rectBoxC(1, 0.97, 0);
    Color TitleC(0.5, 0.95, 0.11);
    Color exitButtonC(0.9, 0.0, 0.0);
    Color exitButtonTextC(1, 1, 1);

    Coord_Rect exitButtonD(8.1, 8.7, 1.4, 0.9);
    Coord_Rect logInButtonD(-1.4, -6, 2.5, 1.2);
    Coord_Rect userNameD(-5, 0, 9, 1.9);
    Coord_Rect passwordD(userNameD, 'y', -3);
    Coord_Rect toSignupD(-2.8, -8, 5.5, 1.5);
    Coord_Rect rectBoxA(-6.5, -3.5, 12.5, 7);
    Coord_Rect rectBoxB(-6.3, -3.3, 12.1, 6.6);

    Text logInScreen(-3, 5, pageTextC, "THE SCHOLAR", GLUT_BITMAP_TIMES_ROMAN_24);
    Text userNameT(-4.8, 2.2, TitleC, "Enter User-name:", GLUT_BITMAP_HELVETICA_18);
    Text passwordT(-4.8, -0.8, TitleC, "Enter Password:", GLUT_BITMAP_HELVETICA_18);
    TextBox userNameB(userNameD, userNameC, boxTextC);
    PasswordBox passwordB(passwordD, passwordC, boxTextC);
    CheckBox showPassword(&passwordB, 4.5, -2.8, loginButtonC);
    Button logInButton("Log In", loginButtonC, loginButtonTextC, logInButtonD, CHAR_WIDTH*1.9, 0.45);
    Button toSignup("New to THE SCHOLAR?", toSignupC, loginButtonTextC, toSignupD);
    rectOutline rectBoxa(rectBoxA, rectBoxC);
    rectOutline rectBoxb(rectBoxB, rectBoxC);
    Button exitButton("EXIT", exitButtonC, exitButtonTextC, exitButtonD, CHAR_WIDTH * 1.1, CHAR_WIDTH * 1.1);

    void addlogInComponents(GUIPage *logInPage)
    {
        userNameB.setFont(GLUT_BITMAP_HELVETICA_18);
        logInButton.setFont(GLUT_BITMAP_9_BY_15);
        logInPage->addComponent(&logInScreen);
        logInPage->addComponent(&userNameB);
        logInPage->addComponent(&passwordB);
        logInPage->addComponent(&userNameT);
        logInPage->addComponent(&passwordT);
        logInPage->addComponent(&showPassword);
        logInPage->addComponent(&logInButton);
        logInPage->addComponent(&toSignup);
        logInPage->addComponent(&rectBoxa);
        logInPage->addComponent(&rectBoxb);
        logInPage->addComponent(&exitButton);
    }
}; // namespace LogIn
/***** Sign Up Page *******/
namespace SignUp
{
    Color userNameC(0.95, 0.95, 0.9);
    Color passwordC = userNameC;
    Color boxTextC(0,0,0);
    //Color signUpTextC(0, 0, 0);
    Color signUpButtonTextC(0, 0, 0);
    Color signUpButtonC(0.3, 0.9, 0.6);
    Color pageTextC(0.3, 0.9, 0.6);
    Color toLoginC(0.3, 1, 0.2);
    Color rectBoxC(0.3, 0.9, 0.6);
    Color TitleC(0.5, 0.95, 0.11);
    Color exitButtonC(0.9, 0.0, 0.0);
    Color exitButtonTextC(1, 1, 1);

    Coord_Rect exitButtonD(8.1, 8.7, 1.4, 0.9);
    Coord_Rect signUpButtonD(-2, -6, 3, 1.2);
    Coord_Rect userNameD(-5, 0, 9, 1.9);
    Coord_Rect passwordD(userNameD, 'y', -3);
    Coord_Rect toLoginD(-3, -8, 4.8, 1.3);
    Coord_Rect rectBoxA(-6.5, -3.5, 12.5, 7);
    Coord_Rect rectBoxB(-6.3, -3.3, 12.1, 6.6);

    Text signUpScreen(-3, 5, pageTextC, "THE SCHOLAR", GLUT_BITMAP_TIMES_ROMAN_24);
    Text userNameT(-4.8, 2.2, TitleC, "Enter User-name:", GLUT_BITMAP_HELVETICA_18);
    Text passwordT(-4.8, -0.8, TitleC, "Enter Password:", GLUT_BITMAP_HELVETICA_18);
    TextBox userNameB(userNameD, userNameC, boxTextC);
    PasswordBox passwordB(passwordD, passwordC, boxTextC);
    CheckBox showPassword(&passwordB, 4.5, -2.8, signUpButtonC);
    Button signUpButton("Sign Up", signUpButtonC, signUpButtonTextC, signUpButtonD);
    Button toLogin("Already a member?", toLoginC, signUpButtonTextC, toLoginD);
    rectOutline rectBoxa(rectBoxA, rectBoxC);
    rectOutline rectBoxb(rectBoxB, rectBoxC);
    Button exitButton("EXIT", exitButtonC, exitButtonTextC, exitButtonD, CHAR_WIDTH * 1.1, CHAR_WIDTH * 1.1);

    void addsignUpComponents(GUIPage *signUpPage)
    {
        userNameB.setFont(GLUT_BITMAP_HELVETICA_18);
        signUpButton.setFont(GLUT_BITMAP_9_BY_15);
        signUpPage->addComponent(&signUpScreen);
        signUpPage->addComponent(&userNameB);
        signUpPage->addComponent(&passwordB);
        signUpPage->addComponent(&userNameT);
        signUpPage->addComponent(&passwordT);
        signUpPage->addComponent(&showPassword);
        signUpPage->addComponent(&signUpButton);
        signUpPage->addComponent(&toLogin);
        signUpPage->addComponent(&rectBoxa);
        signUpPage->addComponent(&rectBoxb);
        signUpPage->addComponent(&exitButton);
    }
}; // namespace SignUp
/********* Home page **********/
namespace Home
{
    Color userNameC(0, 0, 0);
    Color logoutButtonC(0.02, 0.23, 0.61);
    Color logoutButtonTextC(1, 1, 1);
    Color miniButtonsC(0.02, 0.23, 0.61);
    Color searchBoxC(1, 1, 1);

    Coord_Rect logoutButtonD(7.3, 7.5, 2.2, 1.1);
    Coord_Rect backgroundD(-9, -8, 18, 13.65);
    Coord_Rect reading(-9, 5.6, 2.3, 0.9);
    Coord_Rect completed(-6.5, 5.6, 2.3, 0.9);
    Coord_Rect favourite(-4, 5.6, 2.3, 0.9);
    Coord_Rect shared(-1.5, 5.6, 1.75, 0.9);
    Coord_Rect SBoxD(-4, 7.5, 2.5, 1.1);

    Text User(3.5, 8, userNameC, userName, GLUT_BITMAP_HELVETICA_18);

    rectBox background(backgroundD, Color(0, 0.46, 0.4));
    Button logoutButton("Log Out", logoutButtonC, logoutButtonTextC, logoutButtonD, CHAR_WIDTH * 1, CHAR_WIDTH * 1.5);
    Button readingButton("Reading", miniButtonsC, logoutButtonTextC, reading, CHAR_WIDTH * 1.5, CHAR_WIDTH);
    Button completedButton("Completed", miniButtonsC, logoutButtonTextC, completed, CHAR_WIDTH * 1.5, CHAR_WIDTH);
    Button favouriteButton("Favourite", miniButtonsC, logoutButtonTextC, favourite, CHAR_WIDTH * 1.5, CHAR_WIDTH);
    Button sharedButton("Shared", miniButtonsC, logoutButtonTextC, shared, CHAR_WIDTH * 1.4, CHAR_WIDTH);
    Button searchButton("Search", Color(0, 0.46, 0.4),  logoutButtonTextC, SBoxD, CHAR_WIDTH * 1.5, CHAR_WIDTH * 1.5);

    void addHomeComponents(GUIPage *_homePage)
    {
        searchButton.setFont(GLUT_BITMAP_HELVETICA_18);
        logoutButton.setFont(GLUT_BITMAP_9_BY_15);

        _homePage->addComponent(&logoutButton);
        _homePage->addComponent(&User);
        _homePage->addComponent(&readingButton);
        _homePage->addComponent(&completedButton);
        _homePage->addComponent(&favouriteButton);
        _homePage->addComponent(&sharedButton);
        _homePage->addComponent(&background);
        _homePage->addComponent(&searchButton);    }
}; //namespace Home

/********* Book Detail Page *********/
namespace BookDetails
{
    BookDetail page('R');
    void addBookDetailComponents(GUIPage *_bdPage)
    {
        _bdPage->addComponent(&page);
    }
}; // namespace BookDetails
/********** Search Page *************/
namespace SearchN
{
    float searchX = -8.7;
    float searchY = 6.5;
    float searchW = 7;
    float searchH = 1.3;
    float gap = 1;
    int searchIndex=0;

    Color userNameC(1, 1, 1);
    Color searchBoxC(0.9, 0.9, 0.8);
    Color searchBoxTextC(0, 0, 0);
    Color searchButtonC(1, 1, 1);
    Color ButtonsC(0, 0.1, 0.6);
    Color backButtonC(0, 0.1, 0.6);
    Color scrollBoxC(0, 1, 0);
    Color relevantOptionsC(1,0,0);

    Coord_Rect BookListD(0.5, -8.1, 8, 14);
    Coord_Rect SNameD(searchX, searchY - gap - 1.5, searchW, searchH);
    Coord_Rect SAuthorD(SNameD, 'y', -gap - 1);
    Coord_Rect SGenreD(SAuthorD, 'y', -gap - 1);
    Coord_Rect SDateD(SGenreD, 'y', -gap - 1);
    Coord_Rect SBoxD(searchX + 2, searchY - 11, 2.5, 1.1);
    Coord_Rect backButtonD(7, 7.5, 1.60, 1.0);
    Coord_Rect nextButtonD(2,-9.5,1.8,1);
    Coord_Rect prevButtonD(nextButtonD,'x',6);

    Text PageTitle(-8, 6.3, userNameC, "Enter details to Search:                      Results:", GLUT_BITMAP_HELVETICA_18);
    Text SNameT(searchX, searchY - gap, userNameC, "Name:", GLUT_BITMAP_HELVETICA_12);
    Text SAuthorT(searchX, searchY - gap - 2, userNameC, "Author:", GLUT_BITMAP_HELVETICA_12);
    Text SGenreT(searchX, searchY - gap - 4, userNameC, "Genre:", GLUT_BITMAP_HELVETICA_12);
    Text SDateT(searchX, searchY - gap - 6, userNameC, "Date:", GLUT_BITMAP_HELVETICA_12);
    Text Book_Article(searchX, searchY - gap - 12.5, userNameC, "Book           Article", GLUT_BITMAP_HELVETICA_18);
    TextBox SNameB(SNameD, searchBoxC, searchBoxTextC, true);
    TextBox SAuthorB(SAuthorD, searchBoxC, searchBoxTextC);
    TextBox SGenreB(SGenreD, searchBoxC, searchBoxTextC);
    TextBox SDateB(SDateD, searchBoxC, searchBoxTextC);
    Button backButton("Back", backButtonC, searchBoxC, backButtonD, CHAR_WIDTH * 1.5, CHAR_WIDTH * 1.5);
    Button nextButton("Next", backButtonC, searchBoxC, nextButtonD, CHAR_WIDTH * 1.8, CHAR_WIDTH * 1.5);
    Button prevButton("Previous", backButtonC, searchBoxC, prevButtonD, CHAR_WIDTH * 1, CHAR_WIDTH * 1.5);
    CheckBox bookCB(-7.3,-7,userNameC,true);
    CheckBox articleCB(-4.3,-7,userNameC);

    Button searchButton("Search", ButtonsC, searchButtonC, SBoxD, CHAR_WIDTH * 1.5, CHAR_WIDTH * 1.5);
    ScrollBox searchResultList(dataf, BookListD, 15, scrollBoxC);
    ScrollBox relevantOptionsList(dataf,BookListD,15,searchBoxC);

    void addSearchComponents(GUIPage *_searchPage)
    {
        relevantOptionsList.setActive(false);
        searchResultList.setActive(false);
        prevButton.show(false);
        bookCB.setTwin(&articleCB);
        articleCB.setTwin(&bookCB);
        bookCB.setActive(true);
        nextButton.show(false);
        searchButton.setFont(GLUT_BITMAP_9_BY_15);
        _searchPage->addComponent(&PageTitle);
        _searchPage->addComponent(&SNameT);
        _searchPage->addComponent(&SAuthorT);
        _searchPage->addComponent(&SGenreT);
        _searchPage->addComponent(&SDateT);
        _searchPage->addComponent(&SNameB);
        _searchPage->addComponent(&SAuthorB);
        _searchPage->addComponent(&SGenreB);
        _searchPage->addComponent(&SDateB);
        _searchPage->addComponent(&backButton);
        _searchPage->addComponent(&searchButton);
        _searchPage->addComponent(&nextButton);
        _searchPage->addComponent(&prevButton);
        _searchPage->addComponent(&bookCB);
        _searchPage->addComponent(&articleCB);
        _searchPage->addComponent(&Book_Article);
        _searchPage->addComponent(&searchResultList);
        _searchPage->addComponent(&relevantOptionsList);
    }
} // namespace SearchN
