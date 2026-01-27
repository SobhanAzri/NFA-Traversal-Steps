//
// Created by nryxenon on 12/29/25.
//

#include "Tools/fileLoader.h"
#include <fstream>
#include <sstream>
#include "Automatas/nfa.h"
#include "Tools/constants.h"

void FileLoader::loadNfa(NFA &nfa, const char *filePath) {
    std::ifstream file(filePath);


    if (file.is_open())
    {
        std::string line;
        bool isParsingTransitions = false;


        while (std::getline(file,line))
        {
            std::string payload;
            auto colonPos = line.find(':');

            if (colonPos != std::string::npos)
                payload = line.substr(colonPos + 1);
            else
                payload = line;

            std::istringstream lineStream(payload);

            std::string streamIterator;

            if (line.empty() || line[0] == '#') // Comments !
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

                if (symbol == "λ" || symbol == "^")
                    nfa.initializeTransitions(from,destinations,NFA_EPSILON);
                else
                    nfa.initializeTransitions(from,destinations,symbol[0]);
            }
        }
    }
}
