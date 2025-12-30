//
// Created by nryxenon on 12/29/25.
//

#include "Tools/fileLoader.h"
#include <fstream>
#include <sstream>
#include "Automatas/nfa.h"

#define EPSILON '^'

void FileLoader::loadNfa(NFA &nfa, const char *filePath) {
    std::ifstream file(filePath);

    if (file.is_open())
    {
        std::string line;
        bool isParsingTransitions = false;

        nfa.initializeAlphabet(EPSILON); // adding epsilon to alphabets

        while (std::getline(file,line))
        {
            std::istringstream lineStream(line.substr(line.find(':') + 1));
            std::string streamIterator;

            if (line.empty() || line[0] == '#')
                continue;

            if (line.starts_with("states:") || line.starts_with("states :")) {

                while (lineStream >> streamIterator)
                    nfa.insertState(streamIterator);
            }
            else if (line.starts_with("alphabet:") || line.starts_with("alphabet :")) {

                while (lineStream >> streamIterator)
                    nfa.initializeAlphabet(streamIterator[0]);
            }
            else if (line.starts_with("start:") || line.starts_with("start :")) {

                while (lineStream >> streamIterator)
                    nfa.setInitialState(streamIterator);
            }
            else if (line.starts_with("final:") || line.starts_with("final :")) {

                while (lineStream >> streamIterator)
                    nfa.setFinalState(streamIterator);
            }
            else if (line.starts_with("transitions:") || line.starts_with("transitions :"))
            {
                isParsingTransitions = true;
            }
            else if (isParsingTransitions)
            {
                std::string from;
                std::string symbol;
                std::vector<std::string> destinations;

                lineStream >> from >> symbol;

                while (lineStream >> streamIterator)
                    destinations.push_back(streamIterator);

                if (symbol == "λ")
                    nfa.initializeTransitions(from,destinations,EPSILON);
                else
                    nfa.initializeTransitions(from,destinations,symbol[0]);
            }
        }
    }
}
