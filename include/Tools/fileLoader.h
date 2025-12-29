//
// Created by nryxenon on 12/29/25.
//

#ifndef NFA_TRAVERSAL_STEPS_FILELOADER_H
#define NFA_TRAVERSAL_STEPS_FILELOADER_H

class NFA;
class FileLoader {
public :
    static void loadNfa(NFA &nfa,const char* filePath);
};
#endif //NFA_TRAVERSAL_STEPS_FILELOADER_H