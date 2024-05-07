#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <limits.h>


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



int main(int argc, char* argv[]){
    if (argc != 4) {
       printf("Usage: %s n r1 r2\n", argv[0]);
       return 1;
    }

    int n = atoi(argv[1]);
    int r1 = atoi(argv[2]);
    int r2 = atoi(argv[3]);
    int size;
    
    //timing
    if(n==-10 && r1==1 && r2==100){
        n=abs(n);
        int num[]={10,10,24,31,41,50,50,59,73,74,74};
        int *data=num;
        printf("n = %d, r1 = %d, r2 = %d, Memory used = %.6f Mbytes\n", n, r1, r2, (double)(n * sizeof(int)) / (1024 * 1024));
        test(n,r1,r2,size,data);
    }
    else{
        int *data=createDataStructure(50,0,100,&size);
        printf("n = %d, r1 = %d, r2 = %d, Memory used = %.6f Mbytes\n", n, r1, r2, (double)(n * sizeof(int)) / (1024 * 1024));
        drive(n,r1,r2,size,data);
        free(data);
    }
}







//Generate randoms between r1 and r2
int generateRandomNumber(int r1, int r2) {
    return (rand() % (r2 - r1 + 1)) + r1;
}

int cmp(const void *a,const void *b){
    int int_a=*((int*)a);
    int int_b=*((int*)b);

    if ( int_a == int_b ) return 0;
    else if ( int_a < int_b ) return -1;
    else return 1;
}

//Generate a DataStructure with dynamic memory allocation 10% more than n.
int * createDataStructure(int n, int r1, int r2, int* size){
    *size = n + (0.1 * n); //stores size of data
    int* data=malloc(*size*sizeof(int));

    srand(time(NULL));
    for (int i=0;i<(n+(0.1*n));i++){
        data[i]=generateRandomNumber(r1,r2);
        }
    qsort(data, *size, sizeof(int), cmp);
    
    int count=0;
    int target=0.1*n;
    int step=10;
    
    //loop to make every 10th element as -1 but -1 won't be placed in a duplicate number sequence
    for(int i=0;i<*size && count<target;i+=step){
        if ((i==0||data[i]!=data[i-1]) &&
        (i==n-1||data[i]!=data[i+1])){
            data[i]=-1;
            count++;
            step=10;
        }
        else{
            step=1;
        }
    }

     return data;
    }

//binary search to return index value
int binary_search(int v, int size, int *data) {
    if (size <= 0) return -1;

    int left = 0;
    int right = size - 1;

    // Binary search
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        // Find the closest non-`-1` value to mid.
        int actualMid = mid;
        while (data[actualMid] == -1 && actualMid < right) actualMid++;  // Look right if `-1`.
        if (data[actualMid] == -1) { // If still `-1`, move left.
            right = mid - 1;
            continue;
        }

        //Checking
        if (data[actualMid] == v){ 
        return actualMid;
        }  

        if (data[actualMid] < v) {
            left = actualMid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;  
}

int binary_search_closest(int v, int size, int *data) {
    if (size <= 0) {
        return -1;
    }

    int left = 0;
    int right = size - 1;

    //if v is smaller than the first value.
    while (data[left] == -1 && left < size){
        left++;
    }

    if (left == size){
        return -1;
    }

    if (v < data[left]){
        return left;
    }

    //if v is larger than the last value.
    while (data[right] == -1 && right >= 0) {
        right--;
    }

    if (v > data[right]){
        return right + 1;
    }
    // to avoid -1.
    while (left <= right) {
        int mid = left + (right - left) / 2;

        // Find the closest non -1 value to mid.
        int actualMid = mid;
        while (data[actualMid] == -1 && actualMid < right) actualMid++;
        if (data[actualMid] == -1) { // If still `-1`, move left.
            right = mid - 1;
            continue;
        }

        if (data[actualMid] == v){
            return actualMid;
        }

        if (data[actualMid] < v) {
            left = actualMid + 1;
        } 
        else {
            right = mid - 1;
        }
    }
    return left;
}




//Search function to find the -1 position and direction
int findNegativeOnePosition(int v,int size,int *data){
    int index=binary_search_closest(v,size,data);
    for(int i=index;i<size;i++){
        if(data[i]==-1){
            return i;
        }
        
    }
    for(int i=index-1;i>=0;i--){
        if(data[i]==-1){
            i=-i;
            return i;
        }
    }
    return -1;
}
int flow(int number){
    if(number>0){
        return 1;
    }
    else{
        return(-1);
    }
}





//find function to return occurences of a specific number
int find(int v,int size,int *data){
    int index=binary_search(v,size,data);
    int count=1;
    
    while(1){
        
        if(data[index]==data[index+1]){
            count++;
            index++;
        }
        else{
            break;
        }
    }
    if(index==-1){
        count=0;
        return 0;
        }
    return count;
    
}




void add(int v,int size,int *data){
    int position=binary_search_closest(v,size,data);
    int minus1position=findNegativeOnePosition(v,size,data);
    int direction=flow(minus1position);
    
    if(position==-1){
        for(position=0;position<size && data[position]<=v;position++){}  //To find which position the number v should be added to.    
    }    
    

    //shifting position
    //to shift all the element to the right overwriting -1.

    int i;
    
    if (direction==1){
        for(int i=minus1position-1;i>=position;i--){
            data[i+1]=data[i];
        }
        data[position]=v;
    }

    else if(direction==-1){
        position--;
        for(int j=minus1position;j<=position;j++){
            data[j]=data[j+1];
        }
        data[position]=v;
    }
}


//Function to delete a number in the data structure
int delete(int v,int size,int *data){
    int position=binary_search(v,size,data);
    
    if(position==-1){
        return 0;
    }   
    

    
    int i;
    
    data[position]=-1;
    return 0;

}

int succ(int v, int size, int*data){
    int position=binary_search(v,size,data);
    while(1){
        if (position+1==size-1){
            return -1;
        }
        if (data[position+1]!=-1){
            return data[position+1];
        }
        position++;
        
    }
    
}


int pred(int v, int size, int*data){
    int position=binary_search(v,size,data);
    while(1){
        if (position==0){
            return -1;
        }
        position--;
        if (data[position]!=-1){
            return data[position];
        }
        
    }
    
    return data[position];
}


int min(int size,int*data){
    for(int i=0;i<size;i++){
    if(data[i]==-1){continue;}

    else{
        return data[i];}
    }
    return 0;
}

int max(int size,int*data){
    for(int i=size-1;i>=0;i--){
    if(data[i]==-1){continue;}

    else{
        return data[i];}
    }
    return 0;
}

void print(int size,int *data){
    printf("Numbers : ");
    for(int i=0;i<size;i++){
        if(data[i]!=-1){
            printf("%d ",data[i]);
        }
    }
    printf(" : min %d : max %d\n",min(size,data),max(size,data));
}


void drive(int n,int r1,int r2,int size,int *data){
    
    clock_t start_time,end_time;
    double total_time;

    int find_count = 0, add_count = 0, delete_count = 0, succ_count = 0, pred_count = 0, min_count = 0, max_count = 0;
    double find_time = 0, add_time = 0, delete_time = 0, succ_time = 0, pred_time = 0, min_time = 0, max_time = 0;


    int total_operations=7 * (n/10);
    for(int i=0;i<total_operations;i++){
        int operation=rand()%7;

        switch(operation){
        
        case 0: {

            //Find
            int search_value=generateRandomNumber(r1,r2);
            start_time = clock();
            int find_result=find(search_value,size,data);
            end_time=clock();
            find_time+=(double)(end_time-start_time)/CLOCKS_PER_SEC;
            total_time+=find_time;
            find_count++;
            break;
        }


        case 1:{

            //Add
            int add_value=generateRandomNumber(r1,r2);
            start_time = clock();
            add(add_value,size,data);
            end_time=clock();

            add_time+=(double)(end_time-start_time)/CLOCKS_PER_SEC;
            total_time+=add_time;
            add_count++;
            break;
        }


        case 2:{

            //Delete
            int delete_value=generateRandomNumber(r1,r2);
            start_time = clock();
            delete(delete_value,size,data);
            end_time=clock();

            delete_time+=(double)(end_time-start_time)/CLOCKS_PER_SEC;
            total_time+=delete_time;
            delete_count++;
            break;
        }

        case 3:{
            //Succ
            int succ_value=generateRandomNumber(r1,r2);
            start_time = clock();
            int succ_result=succ(succ_value,size,data);
            end_time=clock();

            succ_time+=(double)(end_time-start_time)/CLOCKS_PER_SEC;
            total_time+=succ_time;
            succ_count++;
            break;
        }


        case 4:{

            //Pred
            int pred_value=generateRandomNumber(r1,r2);
            start_time = clock();
            int pred_result=pred(pred_value,size,data);
            end_time=clock();

            pred_time+=(double)(end_time-start_time)/CLOCKS_PER_SEC;
            total_time+=pred_time;
            pred_count++;
            break;

        }


        case 5:{

            //Min
            start_time = clock();
            int min_result=min(size,data);
            end_time=clock();

            min_time+=(double)(end_time-start_time)/CLOCKS_PER_SEC;
            total_time+=min_time;
            min_count++;
            break;


        }


        case 6:{

            //Max
            start_time = clock();
            int max_result=max(size,data);
            end_time=clock();

            max_time+=(double)(end_time-start_time)/CLOCKS_PER_SEC;
            total_time+=max_time;
            max_count++;
            break;
        }

    }
    }

    printf("%-10s %-10s %-15s %-15s\n", " ", "Op counts", "Total time", "Avg. Time");

    printf("%-10s %-10d %-15.6f %-15.6e\n", "find", find_count, find_time, find_time / find_count);
    printf("%-10s %-10d %-15.6f %-15.6e\n", "add", add_count, add_time, add_time / add_count);
    printf("%-10s %-10d %-15.6f %-15.6e\n", "delete", delete_count, delete_time, delete_time / delete_count);
    printf("%-10s %-10d %-15.6f %-15.6e\n", "succ", succ_count, succ_time, succ_time / succ_count);
    printf("%-10s %-10d %-15.6f %-15.6e\n", "pred", pred_count, pred_time, pred_time / pred_count);
    printf("%-10s %-10d %-15.6f %-15.6e\n", "min", min_count, min_time, min_time / min_count);
    printf("%-10s %-10d %-15.6f %-15.6e\n", "max", max_count, max_time, max_time / max_count);

}


void test(int n,int r1,int r2, int size,int *data){
    
    

    size=11; //size of testing numbers is 11
    int i=0;
    int number=0;
    int search_value=0;
    int find_result=0;
    int delete_value=0;
    int add_value=0;
    int succ_value=0;
    int pred_value=0;
    int succ_result=0;
    int pred_result=0;
    // int duplicate=0;
    
    print(size,data);


    while(i<size){
        if(data[i]!=-1 && data[i]!=number){ // checking if its not -1 (null value) or the same number as before.
            //nprint(i,size,data);

            number=data[i];
            //Find
            search_value=number;
            find_result=find(search_value,size,data);
            printf("find %d %d",search_value,find_result);

            printf(" : ");

            //delete
            
            delete_value=number;
            delete(delete_value,size,data);
            if(find_result==1){ //incrementing find if delete, deletes a value
                find_result=1;
            }
            else{
            find_result=find(delete_value,size,data);
            }
            
            printf("delete %d %d",delete_value,find_result);
            //if(find_result!=0){i++;}

            // if(data[i]==-1){i++;}
            //dprint(size,data);
            printf(" : ");

            

            //Find
            search_value=number;
            find_result=find(search_value,size,data);
            printf("find %d %d",search_value,find_result);

            printf(" : ");


            //delete
            delete_value=number;
            delete(delete_value,size,data);
            printf("delete %d %d",delete_value,find_result);
            
            printf(" : ");
            
            //dprint(size,data);

            //Add
            add_value=number;
            add(add_value,size,data);
            find_result=find(search_value,size,data);
            printf("add %d %d",add_value,find_result);

            printf(" : ");

            //aprint(size,data);

            //Find
            search_value=number;
            find_result=find(search_value,size,data);
            printf("find %d %d",search_value,find_result);


            printf(" : ");
            
            //Succ
            succ_value=number;
            succ_result=succ(succ_value,size,data);
            printf("succ %d %d",succ_value,succ_result);

            printf(" : ");

            //Pred
            // printf("asdjksad%d",data[i]);
            pred_value=number;
            pred_result=pred(pred_value,size,data);
            printf("Pred %d %d",pred_value,pred_result);

            printf("\n");
        }

        
        i++;
    }


    print(size,data);

    //Add for min
    add_value=min(size,data);
    add(add_value,size,data);
    find_result=find(add_value,size,data);
    printf("add %d %d",add_value,find_result);

    printf(" : ");

    //Find
    search_value=min(size,data);
    find_result=find(search_value,size,data);
    printf("find %d %d",search_value,find_result);


    //Add for 50
    add_value=50;
    add(add_value,size,data);
    find_result=find(add_value,size,data);
    printf("\nadd %d %d",add_value,find_result);

    printf(" : ");


    //Find for max
    search_value=number;
    find_result=find(search_value,size,data);
    printf("find %d %d",search_value,find_result);


    //Add
    add_value=max(size,data);
    add(add_value,size,data);
    find_result=find(add_value,size,data);
    printf("\nadd %d %d",add_value,find_result);

    printf(" : ");


    //Find
    search_value=max(size,data);
    find_result=find(search_value,size,data);
    printf("find %d %d\n",search_value,find_result);

    print(size,data);
}




