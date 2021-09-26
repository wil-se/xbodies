extern int n;
extern double *bodies_position; // |x|y|z|mass|sx|sy|sz|...|
extern double *bodies_attrs;

void print_body(int i);
void print_bodies();
void initialize();
void terminate();