//
// Created by nryxenon on 12/29/25.
//

#include "Tools/fileLoader.h"
#include <fstream>
#include <sstream>

#include "Automatas/nfa.h"

bool FileLoader::loadNfa(NFA &nfa, const char *filePath) {
    std::ifstream file(filePath);

    if (file.is_open())
    {
        std::string line;
        bool isParsingTransitions = false;

        while (std::getline(file,line))
        {
            if (line.empty() || line[0] == '#')
                continue;

            if (line.starts_with("states:") || line.starts_with("states :")) {
                std::istringstream stateName(line.substr(line.find(':') + 1));
                std::string name;

                while (stateName >> name)
                    nfa.insertState(name);
            }
            else if (line.starts_with("alphabet:") || line.starts_with("alphabet :")) {
                std::istringstream alphabet(line.substr(line.find(':') + 1));
                std::string symbol;

                while (alphabet >> symbol)
                    nfa.initializeAlphabet(symbol);
            }
            else if (line.starts_with("start:") || line.starts_with("start :")) {

            }
            else if (line.starts_with("final:") || line.starts_with("final :")) {

            }
            else if (line.starts_with("transitions:") || line.starts_with("transitions :"))
            {
                isParsingTransitions = true;
            }
            else if (isParsingTransitions)
            {

            }
        }
        return true;
    }
    else
    {
        return false;
    }
}
