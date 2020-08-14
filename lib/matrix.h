typedef struct 
{
    int rows;
    int cols;
    double **matrix;
} Matrix;

void print_matrix(Matrix *matrix);
Matrix *init_matrix(int rows, int cols, const double mat[rows][cols]);
int is_null(Matrix *matrix);
int multiply(Matrix *a, Matrix *b, Matrix *result);
int scalar_multiply(Matrix *matrix, double a);
int scalar_add(Matrix *matrix, double a);