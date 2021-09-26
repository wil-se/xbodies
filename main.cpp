#include <stdio.h>
#include <cstring>

#include <GL/glut.h>

#include "libgl/render.h"
#include "common/memory.h"
#include "sequential/sequential-exhaustive.h"

int main(int argc, char** argv)
{   
    char* MODE = argv[1];
    char* ALG = argv[2];
    
    printf("%s\n", MODE);
    printf("%s\n", ALG);
    
    if(!strcmp(MODE, "sequential")){
        if(!strcmp(ALG, "exhaustive")){
            printf("Starting sequential exhaustive mode..\n");
            run_sequential_exhaustive(argc, argv);
            // GLUTinit(argc, argv);
            // glutMainLoop();
        }
    }

    
    return 0;
}