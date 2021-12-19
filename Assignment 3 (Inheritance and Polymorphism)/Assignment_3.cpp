#include <iostream>
#include <string>
#include <fstream>

using namespace std;


/*********************************** FloatArray ***********************************/

class FloatArray{
    protected:
        float * arr;
        int size;
        int num_of_elements;
    public:
        /* Parameterized Constructor */
        FloatArray(int size){
            num_of_elements = 0;
            this->size = size;
            arr = new float[size];
        }

        virtual void add(float a);
        friend ostream& operator << (ostream&, const FloatArray&);
        friend istream& operator >> (istream&, FloatArray&);

        /* Destructor */
        ~FloatArray(){
            delete [] arr;
        }
};

//adds a float at the end of the array
void FloatArray:: add(float a){
    arr[num_of_elements++] = a;
}

//to write the array to a file (ofstream)
ostream& operator << (ostream& os, const FloatArray& obj){
    os<<obj.size<<'|'<<'\t';
    for(int i = 0; i<obj.size; i++){
        os<<obj.arr[i]<<'\t';
    }
    os<<endl;
    return os;
}

//to read the array elements from the file (ifstream) and add them to the array.
istream& operator >> (istream& is, FloatArray& obj){
    float tmp;
    for(int i = 0; i<obj.size; i++){
        is>>tmp;
        obj.add(tmp);
    }
    return is;
}


/*********************************** SortedArray ***********************************/

//Inherits from FloatArray.
class SortedArray : public FloatArray{
    public:
        /* Parameterized Constructor */
        SortedArray(int size):FloatArray(size){
            this->size = size;
        }

        virtual void add(float a);
};

//adds a float at the right place in the array such that the array remains sorted with every add.
//Note: Don’t add to the array then sort but rather add in the right place.
void SortedArray :: add(float a){
    
}


/*********************************** FrontArray ***********************************/

//Inherits from FloatArray
class FrontArray : public FloatArray{
    public:
        /* Parameterized Constructor */
        FrontArray(int size): FloatArray(size){
            this->size = size;
        }

        void add(float a);
};

//adds a float at the front of the array.
void FrontArray :: add(float a){
    num_of_elements++;
    //shifting all the numbers one step to the right so the first place will be empty.
    for(int i = num_of_elements-1; i>=0; i--){
        arr[i+1] = arr[i];
    }
    //assign the first place with the number to be added.
    arr[0] = a;
}


/*********************************** PositiveArray ***********************************/

//Inherits from SortedArray
class PositiveArray : public SortedArray{
    public:
        /* Parameterized Constructor */
        PositiveArray(int size):SortedArray(size){
            this->size = size;
        }
        void add(float a);
};

//adds a float to the array only if it’s a positive number. 
//It then uses the add method of SortedArray.
void PositiveArray :: add(float a){

}


/*********************************** NegativeArray ***********************************/

//Inherits from SortedArray
class NegativeArray : public SortedArray{
    public:
        /* Parameterized Constructor */
        NegativeArray(int size):SortedArray(size){
            this->size = size;
        }
        void add(float a);
};

//adds a float to the array only if it’s a negative number. 
//It then uses the add method of SortedArray.
void NegativeArray :: add(float a){

}


int main(){

    //The only input to my program is the names of the input txt file and output txt file name.
    string in_name, out_name;
    cout<<"Enter the name of the input file: ";
    getline(cin, in_name);
    cout<<"Enter the name of the output file: ";
    getline(cin, out_name);
    ifstream in(in_name);
    ofstream out(out_name, ios::app);
    
    //use polymorphism by creating an array of FloatArray* in main. 
    FloatArray ** arr = new FloatArray*[10];

    /* Read from the txt file and allocate objects according to the type of array 
    and fill the arrays using the extraction operator >>. */
    string type;
    int size, index = 0;
    if(!in.fail()){
        while(!in.eof()){
            in>>type;
            in>>size;
            if(type == "Array") arr[index] = new FloatArray(size);
            else if(type == "Sorted") arr[index] = new SortedArray(size);
            else if(type == "Front") arr[index] = new FrontArray(size);
            else if(type == "Positive") arr[index] = new PositiveArray(size);
            else if(type == "Negative") arr[index] = new NegativeArray(size);
            in>>*(arr[index]);
            index++;
        }
    }

    /* After finishing reading the file, 
    writing the arrays to another text file using the insertion operator<<. */
    if(!out.fail()){
        for(int i = 0; i<10; i++){
            out<<*(arr[i]);
        }
    }

    //Deallocate by deleting objects in main after finishing.
    for(int i = 0; i<10; i++) delete arr[i];
    delete [] arr;

    return 0;
}