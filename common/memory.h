#define G 6.67e-11
#define dt 100

extern int n;
extern double *bodies_position; // |x|y|z|mass|sx|sy|sz|...|
extern double *bodies_attrs;
extern double *new_bodies_position;
extern double *new_bodies_attrs;

void print_body(int i);
void print_bodies();
void initialize();
void terminate();
void print_new_body(int i);
void print_new_bodies();