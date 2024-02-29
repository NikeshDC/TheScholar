#ifndef VARS
#define VARS

const int WID_INI = 700;
const int HEI_INI = 650;
const int INI_X = 350;
const int INI_Y = 70;
float WC_R = 0.50;
float WC_G = 0;
float WC_B = 0.082;
float WC_A = 1;
const float COORD_X = 10;
const float COORD_Y = 10;
const int SPACE_KEY = 32;
const int DEL_KEY = 8;
const int ENTER_KEY = 13;
const int ESC_KEY = 27;
const int TAB_KEY = 9;
const int lx = -0.7;
const int ly = -8;
const float CHAR_WIDTH = 0.2667;
const float CHAR_HEIGHT = 0.3;
const float DIM_FACTOR = 0.2;
const float CHECK_BOX_DIMENSION = 0.5;
int mainWindowIndex;
int WID;
int HEI;
int PREV_PAGE;
int PREV_BLOCK;
int bindex;
int article_flag = 1;
char CHAR_MASK = '*';
char prevMode = 'R';
std::string userName = "";
std::string password = "";
std::string userNameN = "";
std::string passwordN = "";
std::vector<std::string> dataf={"","","","","","","","","","","","","","","","",""};
std::vector<std::string> books;
std::string bookNameSB;
std::string bookmarkT;
std::string reviewT;
std::string shareT;
int bookNameIndex;
#endif // VARS
