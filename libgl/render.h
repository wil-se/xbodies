void GLUTinit(int argc, char** argv);
void GLUTinit_sequential(int argc, char** argv);
void compute();
void display_sequential_exhaustive();
void timer(int millisec);
void reshape(int w, int h);
void keyboard(unsigned char key, int /*x*/, int /*y*/);
void motion(int xcam, int ycam);
void mouse(int button, int state, int xcam, int ycam);