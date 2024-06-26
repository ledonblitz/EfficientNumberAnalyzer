int generateRandomNumber(int r1, int r2);
int cmp(const void *a,const void *b);
int * createDataStructure(int n, int r1, int r2, int* size);
int binary_search(int v, int size, int *data);
int binary_search_closest(int v, int size, int *data);
int findNegativeOnePosition(int v,int size,int *data);
int flow(int number);
int find(int v,int size,int *data);
void add(int v,int size,int *data);
int delete(int v,int size,int *data);
int succ(int v, int size, int*data);
int pred(int v, int size, int*data);
int min(int size,int*data);
int max(int size,int*data);
void print(int size,int *data);
void drive(int n,int r1,int r2,int size,int *data);
void test(int n,int r1,int r2, int size,int *data);