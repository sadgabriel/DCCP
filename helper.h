#pragma once
#include <iostream>
using namespace std;

class Helper {
private:
	string mainHelp = " /mode_change ->how to change mode \n /Note -> how to insert/delete/replace notes \n /cursor -> about cursor \n /page -> about page \n /setting -> about octave, bpm ";
	string noteHelp = " /insert -> how to insert Note \n /remove -> how to remove Note  \n /replace -> how to replace Note";
	string modechangehelp = " ++ : change mode to INSERT MODE. \n --: change mode to REMOVE MODE. \n **: change mode to REPLACE MODE. \n /Note to know what to do in this modes.";
	string cursorhelp = " crN: move cursor right N steps. \n clN: move cursor left N steps. \n ctN : move cursor to N. \n ce: move cursor to the end. \n cs: move cursor to the start.";
	string pagehelp = " prN: move page right N steps. \n plN: move page left  steps. \n ptN: move to N page. \n ps: move to first page. \n pe: move to last page ";
	string settinghelp = " BPM N: set bpm N. ot N: set octave N.";
	struct noteHp {
		string remove = " remove: just type integer n, then n Notes are removed from the cursor position";
		string insert = " you can insert note WHEN MODE IS INSERT MODE. \n you should type length, pitch like this; cv  \n c is pitch, v is length. then pitch E, length 1/8 is inserted at Cursorpoint and Cursor moves one step to the right. \n If there exists a note  \n /pitch to know what words is about pitchs. \n And, z meand 1/1 and x is 1/2 and c is 1/4 and v is 1/8 and b is 1/16.";
		string replace = "replace: same with insert operation, but WHEN MODE IS REPLACE MODE, will replace note with typed length/pitch, instead of insert note.";
		string pitch = "-,+ means lower octave and upper octae; \n2=C#+ 3=D#+ 5=F#+ 6=G#+ 7=A#+ 9=C#++ 10=C#++ \n Q=C+ W=D+ E=E+ R=F+ T=G+ Y=A+ U=D+ I=C++ O= D++ P= E++ \N S=C# D=D# G=F# H=G# J=A# \N Z=C X=D C=E V=F B=G N=A M=A  , IS REST.";
	};
public:
	noteHp notehp;
	string whatCommand(string command) {
		if (command == "help") {
			return mainHelp;
		}
		else if (command == "Note") {
			return noteHelp;
		}
		else if (command == "remove") {
			return notehp.remove;
		}
		else if (command == "insert") {
			return notehp.insert;
		}
		else if (command == "mode_change") {
			return modechangehelp;
		}
		else if (command == "cursor") {
			return cursorhelp;
		}
		else if (command == "page") {
			return pagehelp;
		}
		else if (command == "setting") {
			return settinghelp;
		}
		else if (command == "pitch") {
			return notehp.pitch;
		}
		else {
			return "No help for that... how about /help ?";
		}
	}
};