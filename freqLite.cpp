#include <iostream>
#include <fstream>

using namespace std;

typedef struct node{
    int sum, freq;
    char c;

    struct node *left;
    struct node *right;
}NODE; 

typedef struct hash{
    int value[2];
    struct hash *next;
}HASH;


class DataCompress{
    private:
    int frequency[256][2];
    HASH *hashData[10];

    public:
    void init();
    void sort();
    void retrieve();
    void build_tree();

    void hash();
    void add(int index, int value[2]);

    void display();
};

void DataCompress::init(){
     for (int i = 0; i < 10; i++)
     {
        hashData[i] = NULL;
     }
     
     for(int i = 0; i < 256; i++){
        frequency[i][0] = i;
        frequency[i][1] = 0;
    }
}


void DataCompress::add(int index, int value[2]){
    HASH *pointer, *follower, *temp;
    pointer = follower = hashData[index];
    
    temp = new HASH;
    copy(value, value + 2, temp->value);
    
    while(pointer != NULL){
        follower = pointer;
        pointer = pointer->next;
    }

    if(hashData[index] == NULL){
        hashData[index] = temp;
    }else{
        follower->next = temp;
    }
    temp->next = pointer;

}



void DataCompress::hash(){
    for (int i = 0; i < 256; i++)
    {
        if(frequency[i][1]){
            int x = frequency[i][1] % 10;
            int arr[2] = {frequency[i][0], frequency[i][1]};
            add(x, arr);
        }
    }
    
}

void DataCompress::build_tree(){
    for (int i = 0; i < 256; i++)
    {
        if(frequency[i][1]){
                
        }
    }
    
}


void DataCompress::sort(){
    int temp[2];
    for (int i = 0; i < 256; i++)
    {
        for (int j = i + 1; j < 256; j++)
        {
            //Replace the less than sign to change to ascending order
            if(frequency[i][1] < frequency[j][1]){
                swap(temp, frequency[j]);
                swap(frequency[j], frequency[i]);
                swap(frequency[i], temp);
            }
        }
        
    }
    
}

void DataCompress::retrieve(){
    char c;
    fstream fp;
    fp.open("noise.txt", ios::in);
    if(fp.is_open()){
        while(!fp.eof()){
            fp.get(c);
            for(int i = 0; i < 256; i++){
                if(c == i){
                    frequency[i][1]++;
                }
            }
        }
        fp.close();
    }
}





void DataCompress::display(){
    // for (int i = 0; i < 10; i++)
    // {
    //     int x = i;
    //     HASH *pointer = hashData[i];
    //     while(pointer != NULL){
    //         cout << x + 1 << ": " << (char) (pointer->value[0]) << " is " << pointer->value[1]<< " =>";
    //         pointer = pointer->next;
    //     }
    //     cout << endl;
    // }

    for (int i = 0; i < 256; i++)
    {
        /*
            {
                {A, 24},
                {b, 67}
            }
        
        */
        if(frequency[i][1]) {
            cout << (char) frequency[i][0] << ": " << frequency[i][1] << endl;
        }
    }
    
    
}


int main(){
  DataCompress dc;
  dc.init();
  dc.retrieve();
  dc.sort();
  dc.hash();
  dc.display();




  
}