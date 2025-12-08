//
// Created by nryxenon on 12/8/25.
//
//

#include <fstream>

#include "Tools/fileReader.h"
#include "Automatas/nfa.h"

NFA FileReader::loadFile(const std::string &filePath) {
    NFA nfa;

    std::ifstream automataFile(filePath);

    if (automataFile.is_open())
    {



    }

    return nfa;
}

void readComponents(NFA nfa, const std::string &componentName){

}
