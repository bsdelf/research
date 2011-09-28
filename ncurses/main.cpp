#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <map>
using namespace std;

#include <ncurses.h>

WINDOW* create_newwin(int h, int w, int sx, int sy)
{
    WINDOW* wnd = newwin(h, w, sx, sy);
    //box(wnd, 0, 0);
    wrefresh(wnd);
    return wnd;
}

enum SpKey
{
    KeyEnter,
    KeySpace,
    KeyEsc,
    KeyBackspace,
    KeyTab,

    KeyCtrl,
    KeyAlt,
    
    KeyHome,
    KeyEnd,
    KeyInsert,
    KeyDelete,
    KeyPageUp,
    KeyPageDown,

    KeyUp,
    KeyDown,
    KeyRight,
    KeyLeft,

    KeyF1,
    KeyF2,
    KeyF3,
    KeyF4,

    KeyF5,
    KeyF6,
    KeyF7,
    KeyF8,

    KeyF9,
    KeyF10,
    KeyF11,
    KeyF12,

    KeyNil
};

struct KeyType
{
    SpKey key;
    int ch;
};

typedef vector<int> IntArray;


KeyType DetectKey(int ch, WINDOW* wnd)
{
    KeyType type;
    switch (ch)
    {
	case 13:
	    type.key = KeyEnter;
	    break;

	case 32:
	    type.key = KeySpace;
	    break;

	case 127:
	    type.key = KeyBackspace;
	    break;

	case 9:
	    type.key = KeyTab;
	    break;
	    
	case 27:
	{
	    wtimeout(wnd, 0);
	    ch = wgetch(wnd);
	    
	    switch (ch)
	    {
		case ERR:
		    type.key = KeyEsc;
		    break;

		case 91:
		{
		    ch = wgetch(wnd);

		    switch (ch)
		    {
			case 72:
			    type.key = KeyHome;
			    break;

			case 70:
			    type.key = KeyEnd;
			    break;

			case 65:
			    type.key = KeyUp;
			    break;

			case 66:
			    type.key = KeyDown;
			    break;

			case 67:
			    type.key = KeyRight;
			    break;

			case 68:
			    type.key = KeyLeft;
			    break;

			case 51:
			{
			    ch = wgetch(wnd);
			    type.key = (ch == 126) ? KeyDelete : KeyNil;
			}
			    break;

			case 53:
			{
			    ch = wgetch(wnd);
			    type.key = (ch == 126) ? KeyPageUp : KeyNil;
			}
			    break;

			case 54:
			{
			    ch = wgetch(wnd);
			    type.key = (ch == 126) ? KeyPageDown : KeyNil;
			}
			    break;

			case 49:
			{
			    ch = wgetch(wnd);
			    switch (ch)
			    {
				case 53:
				    ch = wgetch(wnd);
				    type.key = (ch == 126) ? KeyF5 : KeyNil;
				    break;
				case 55:
				    ch = wgetch(wnd);
				    type.key = (ch == 126) ? KeyF6 : KeyNil;
				    break;
				case 56:
				    ch = wgetch(wnd);
				    type.key = (ch == 126) ? KeyF7 : KeyNil;
				    break;
				case 57:
				    ch = wgetch(wnd);
				    type.key = (ch == 126) ? KeyF8 : KeyNil;
				    break;

				default:
				    type.key = KeyNil;
				    break;
			    }
			}
			    break;

			case 50:
			{
			    ch = wgetch(wnd);
			    switch (ch)
			    {
				case 126:
				    type.key = KeyInsert;
				    break;

				case 48:
				    ch = wgetch(wnd);
				    type.key = (ch == 126) ? KeyF9 : KeyNil;
				    break;
				case 49:
				    ch = wgetch(wnd);
				    type.key = (ch == 126) ? KeyF10 : KeyNil;
				    break;
				case 51:
				    ch = wgetch(wnd);
				    type.key = (ch == 126) ? KeyF11 : KeyNil;
				    break;
				case 52:
				    ch = wgetch(wnd);
				    type.key = (ch == 126) ? KeyF12 : KeyNil;
				    break;

				default:
				    type.key = KeyNil;
				    break;
			    }
			}
			    break;

			default:
			    type.key = KeyNil;
			    break;
		    }
			break;

		    case 79:
		    {
			ch = wgetch(wnd);
			switch (ch)
			{
			    case 80:
				type.key = KeyF1;
				break;

			    case 81:
				type.key = KeyF2;
				break;

			    case 82:
				type.key = KeyF3;
				break;

			    case 83:
				type.key = KeyF4;
				break;

			    default:
				type.key = KeyNil;
				break;
			}
		    }
			break;
		}
		    break;

		default:
		{
		    type.key = KeyAlt;
		    type.ch = ch;
		}
		    break;
	    }
	}
	    break;

	default:
	{
	   type.key = KeyCtrl;
	   type.ch = ch + 96;
	   break;
	}
    }

    return type;
}

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "");

    if (argc != 2)
	return -1;
    
    fstream stream;
    stream.open(argv[1], ios::out);
    stringstream ss;

    initscr();
    nonl();
    raw();
    noecho();
    keypad(stdscr, TRUE);


    int row, col;
    getmaxyx(stdscr, row, col);
    stream << "row size:" << row << endl;
    stream << "col size:" << col << endl;

    WINDOW* lnu = create_newwin(row, 1, 0, 0);
    wattron(lnu, A_REVERSE);
    wnoutrefresh(lnu);

    WINDOW* top = create_newwin(1, col, 0, 0);
    wattron(top, A_REVERSE);
    {
	int left = (col-6)/2;
	string blank(col, ' ');
	mvwaddnstr(top, 0, 0, blank.c_str(), blank.size());
	mvwaddnstr(top, 0, left, "foomac", 6);
    }
    wnoutrefresh(top);

    WINDOW* wnd = create_newwin(row-1, col, 1, 1);

    WINDOW* bot = create_newwin(1, col, row-2, 1);
    wattron(bot, A_REVERSE);

    {
	int left = (col-6)/2;
	string blank(col, ' ');
	mvwaddnstr(bot, 0, 0, blank.c_str(), blank.size());
	mvwaddnstr(bot, 0, left, "foomac", 6);
    }
    wrefresh(bot);

    WINDOW* cmd = create_newwin(1, col, row-1, 0);
    {
	string str("M-x ");
	mvwaddnstr(cmd, 0, 0, str.c_str(), str.size());
    }
    wrefresh(cmd);


    wmove(wnd, 0, 0);
    curs_set(1);
    
    int modify = -1;

    int modi = 0;
    int mod[] = {-1, -1, -1};

    while (true)
    {
	int ch = wgetch(wnd);
	
	if (ch == 3)
	    break;
	else 
	{
	    KeyType type = DetectKey(ch, wnd);
	    wtimeout(wnd, -1);
	    if (type.key == KeyAlt)
		stream << "alt" << (char)type.ch << flush;
	    else if (type.key == KeyCtrl)
		stream << "ctrl" << (char)type.ch << flush;
	    else
		stream << ch << flush;

	    stream << ", " << flush;

	}
	// left
	if (ch == 260)
	{
	    int y, x;
	    getyx(wnd, y, x);
	    wmove(wnd, y, --x);
	    wrefresh(wnd);
	}
	// right
	else if (ch == 261)
	{
	}
	else
	{
	    //printw("%c", a);
	    waddch(wnd, ch);
	}
	wrefresh(wnd);
	stream << ch << ", " << flush;
	
    }
    
    endwin();

    return 0;
}
