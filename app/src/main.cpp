
#include "mtgdl.h"
#include <cstdint>
#include <iostream>
#include <map>
#include <stdlib.h>
#include <vector>
#include <windows.h>

using namespace std;

typedef Set*(__cdecl* DLMAIN)();

class SetLibrary {
private:
    string _library_name;
    HINSTANCE _library = nullptr;
    string _set_name;
    Set* _set = nullptr;

public:
    SetLibrary(string path)
    {
        _library_name = path;
        _library = LoadLibrary(path.c_str());
        DLMAIN entry_point = nullptr;

        if (_library == nullptr)
            throw 2;

        entry_point = (DLMAIN)GetProcAddress(_library, "dlmain");

        if (entry_point == nullptr)
            throw 3;

        _set = (entry_point)();
        _set_name = _set->name();
    }

    ~SetLibrary()
    {

        if (_set != nullptr) {
            delete _set;
            _set = nullptr;
        }

        if (_library != nullptr) {
            FreeLibrary(_library);
        }
    }

    Set* getSet()
    {
        return _set;
    }

    string getSetName()
    {
        return _set_name;
    }
};

class SetManager {
private:
    // returns a pointer to the file extension of the provided file name
    static char* getFileExtension(char* text)
    {
        intptr_t len = strlen(text);

        for (intptr_t index = len - 1; index >= 0; index--) {
            if (text[index] == L'.') {
                return &text[index];
            }
        }
        return text;
    }

    // return the list of all the dll's listed in the same directory as our executable.
    static vector<string> getDynamicLibs()
    {

        // Get the location of the current exe
        char path[MAX_PATH];
        GetModuleFileName(NULL, path, MAX_PATH);

        intptr_t length = strlen(path);

        // Prepare our find string by removing the file name of our exe and adding a * to the path
        // so we list all the files contained the directory and not just the directory
        for (intptr_t index = length; index >= 0; index--) {
            if (path[index] == '\\') {
                path[index + 1] = '*';
                path[index + 2] = '\0';
                break;
            }
        }

        WIN32_FIND_DATA fdFile;
        HANDLE hFind = NULL;

        // Start the find process
        if ((hFind = FindFirstFile(path, &fdFile)) == INVALID_HANDLE_VALUE) {
            printf("Path not found: [%s]\n", path);
            throw 1;
        }

        vector<string> dynamic_libs;
        do {
            // if its a dir we don't care
            if (strcmp(fdFile.cFileName, ".") == 0 || strcmp(fdFile.cFileName, "..") == 0 || fdFile.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                continue;

            // get the file extension
            char* extension = getFileExtension(fdFile.cFileName);

            // if its a dll we want it
            if (strcmp(extension, ".dll") == 0) {
                dynamic_libs.push_back(fdFile.cFileName);
            }

        } while (FindNextFile(hFind, &fdFile));

        return dynamic_libs;
    }

    vector<SetLibrary*> _sets;

public:
    SetManager()
    {
        vector<string> dynamic_libs = SetManager::getDynamicLibs();

        for (string lib : dynamic_libs) {
            _sets.push_back(new SetLibrary(lib));
        }
    }

    ~SetManager()
    {
        for (SetLibrary* set : _sets) {
            delete set;
        }
    }

    Set* getSetByName(string name)
    {
        for (intptr_t index = 0; index < _sets.size(); index++) {
            if (_sets[index]->getSetName() == name) {
                return _sets[index]->getSet();
            }
        }
    }

    Set* operator[](intptr_t index)
    {
        return _sets[index]->getSet();
    }

    intptr_t size()
    {
        return _sets.size();
    }
};

int main(int argc, char** argv)
{
    SetManager set_manger;

    for (intptr_t index = 0; index < set_manger.size(); index++) {
        vector<Card*> cards = set_manger[index]->getCards();

        for (Card* card : cards)
            std::cout << card->name() << std::endl;
    }
}
