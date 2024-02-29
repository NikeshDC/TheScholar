/***** reading block *****/
namespace readingN
{
    Color userNameC(1, 1, 1);
    Color scrollBoxC(0.9, 0.9, 0.9);
    Color refreshButtonC(0.1, 0.3, 0.7);
    Color refreshButtonTextC(1, 1, 1);

    Coord_Rect BookListD(-8.5, -6.5, 12, 10);
    Coord_Rect refreshButtonD(-8.75, -7.75, 1.9, 1);

    Text bookNameDis(-8.4, 4, userNameC, "Reading Book List:", GLUT_BITMAP_HELVETICA_18);
    ScrollBox BookListReading(dataf, BookListD, 8, scrollBoxC);

    void addReadingComponents(GUIBlock *_readingPage)
    {
        BookListReading.setActive(true);
        _readingPage->addComponent(&BookListReading);
        _readingPage->addComponent(&bookNameDis);
    }

} // namespace readingN
/****** completed block ******/
namespace completedN
{
    Color userNameC(1, 1, 1);
    Color scrollBoxC(0.9, 0.9, 0.9);
    Color refreshButtonC(0.1, 0.3, 0.7);
    Color refreshButtonTextC(1, 1, 1);

    Coord_Rect BookListD(-8.5, -6.5, 12, 10);
    Coord_Rect refreshButtonD(-8.75, -7.75, 1.9, 1);

    ScrollBox BookListCompleted(dataf, BookListD, 8, scrollBoxC);
    Text bookNameDis(-8.4, 4, userNameC, "Completed Book List:", GLUT_BITMAP_HELVETICA_18);

    void addCompletedComponents(GUIBlock *_completedPage)
    {
        _completedPage->addComponent(&BookListCompleted);
        _completedPage->addComponent(&bookNameDis);
    }
} // namespace completedN
/**** favourite block *****/
namespace favouriteN
{
    Color userNameC(1, 1, 1);
    Color scrollBoxC(0.9, 0.9, 0.9);
    Color refreshButtonC(0.1, 0.3, 0.7);
    Color refreshButtonTextC(1, 1, 1);

    Coord_Rect BookListD(-8.5, -6.5, 12, 10);
    Coord_Rect refreshButtonD(-8.75, -7.75, 1.9, 1);

    ScrollBox BookListFavourite(dataf, BookListD, 8, scrollBoxC);
    Text bookNameDis(-8.4, 4, userNameC, "Favourite Book List:", GLUT_BITMAP_HELVETICA_18);

    void addFavouriteComponents(GUIBlock *_favouritePage)
    {
        _favouritePage->addComponent(&BookListFavourite);
        _favouritePage->addComponent(&bookNameDis);
    }
} // namespace favouriteN
/**** shared block ****/
namespace sharedN
{
    Color userNameC(1, 1, 1);
    Color scrollBoxC(0.9, 0.9, 0.9);
    Color refreshButtonC(0.1, 0.3, 0.7);
    Color refreshButtonTextC(1, 1, 1);

    Coord_Rect BookListD(-8.5, -6.5, 12, 10);
    Coord_Rect refreshButtonD(-8.75, -7.75, 1.9, 1);

    ScrollBox BookListShare(dataf, BookListD, 8, scrollBoxC);
    Text bookNameDis(-8.4, 4, userNameC, "Shared Book List:", GLUT_BITMAP_HELVETICA_18);

    void addSharedComponents(GUIBlock *_sharedPage)
    {
        _sharedPage->addComponent(&BookListShare);
        _sharedPage->addComponent(&bookNameDis);
    }
} // namespace sharedN
