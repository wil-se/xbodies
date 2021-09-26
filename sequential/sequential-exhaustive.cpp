#include <stdio.h>
#include <GL/glut.h>

#include "../common/memory.h"
#include "../libgl/render.h"


void run_sequential_exhaustive(int argc, char** argv){
    initialize();
    GLUTinit_sequential(argc, argv);
    glutMainLoop();
};


