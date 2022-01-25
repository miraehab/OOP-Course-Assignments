#include <iostream>

#ifndef SETCOLORFUN_H_INCLUDED
#define SETCOLORFUN_H_INCLUDED
#include <windows.h>
void SetColor(int ForgC)
 {
 WORD wColor;

  HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO csbi;

                       //We use csbi for the wAttributes word.
 if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
 {
                 //Mask out all but the background attribute, and add in the forgournd color
      wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
      SetConsoleTextAttribute(hStdOut, wColor);
 }
 return;
}

/*
Name         | Value
             |
Black        |   0
Blue         |   1
Green        |   2
Cyan         |   3
Red          |   4
Magenta      |   5
Brown        |   6
Light Gray   |   7
Dark Gray    |   8
Light Blue   |   9
Light Green  |   10
Light Cyan   |   11
Light Red    |   12
Light Magenta|   13
Yellow       |   14
White        |   15
*/


#endif // SETCOLORFUN_H_INCLUDED

using namespace std;

class ColoredBox{

    private:
        char ** box;
        char box_char;
        int length;
        int width;
        int color;
        static int max_area;

    public:
        /* Constructors */
        ColoredBox(int, int);
        ColoredBox(int, int, int, char);

        /* Destructor */
        ~ColoredBox();

        /*Getters and Setters */
        void setColor(int);
        int getColor() const;
        void setBoxchar(char);
        char getBoxchar() const;

        /* Member Funnctions */
        int getArea();
        static int getMaxArea();
        void display();
        void displayTransposed();
        void displayWider();
        void displayChess(int);
};

int ColoredBox :: max_area = 0;

//contructor that takes length and width.
ColoredBox :: ColoredBox(int l, int w){
	length = l;
	width = w;
	color = 15;
	box_char = '#';
	if((length*width) > max_area){
        max_area = (length*width);
	}
	box = new char*[length];
	for(int i = 0;i<length;i++){
		box[i]= new char[width];
		for(int j = 0;j<width;j++){
			box[i][j]=box_char;
		}
	}
}

//contructor that takes length,width,color,boxChar
ColoredBox :: ColoredBox(int l, int w, int c, char ch){
	length = l;
	width = w;
	color = c;
	box_char = ch;
	if((length*width) > max_area){
		max_area = (length*width);
	}
	box = new char*[length];
	for(int i = 0; i<length; i++){
		box[i]= new char[width];
		for(int j = 0; j<width; j++){
			box[i][j]=box_char;
		}
	}
}

void ColoredBox :: setColor(int c){
	color =c;
}

int ColoredBox ::  getColor() const{
	return color;
}

void ColoredBox :: setBoxchar(char ch){
	box_char =ch;
}

char ColoredBox ::  getBoxchar() const{
	return box_char;
}

//Prints the box
void ColoredBox :: display(){
    SetColor(color);
	for(int i = 0; i<length; i++){
		for(int j = 0; j<width; j++){
			cout<<box[i][j];
		}
		cout<<endl;
	}
	SetColor(7);
}

//Display the box transposed
void ColoredBox :: displayTransposed(){
    SetColor(color);
	for(int i = 0; i<width; i++){
		for(int j = 0; j<length; j++){
			cout<<box[j][i];
		}
		cout<<endl;
	}
	SetColor(7);
}

//Display the box on a wider scale
void ColoredBox :: displayWider(){
    SetColor(color);
	for(int i = 0; i<length; i++){
		for(int j = 0; j<width; j++){
			cout<<box[i][j]<<" ";
		}
		cout<<endl;
	}
	SetColor(7);
}

//Displays the box as a chess board (one with the original color of the object and the next with the color of the parameter (color2))
void ColoredBox :: displayChess(int color2){
    int temp = color2;
    for(int i = 0; i<length; i++){
		for(int j = 0; j<width; j++){
            if(temp == color2){
                temp = color;
            }else{
                temp = color2;
            }
            SetColor(temp);
			cout<<box[i][j];
		}
		cout<<endl;
	}
	SetColor(7);
}

int ColoredBox :: getArea(){
    return (length*width);
}

int ColoredBox :: getMaxArea(){
    return max_area;
}

ColoredBox :: ~ColoredBox(){
    for(int i = 0; i<length; i++){
		delete []box[i];
	}
	delete []box;
}

int main()
{
    int len,wid,col,col2;
    char boxChar;
    cout<<"Enter length and width of the box separated by a space: ";
    cin>>len>>wid;
    ColoredBox* cb1;
    cb1 = new ColoredBox(len,wid);
    cb1->display();
    cout<<"Set the box to another color: ";
    cin>>col;
    cb1->setColor(col);
    cout<<"Displaying Transposed: "<<endl;
    cb1->displayTransposed();
    cout<<"Displaying Wider: "<<endl;
    cb1->displayWider();
    cout<<"Displaying Chess, enter the other color: "<<endl;
    cin>>col2;
    cb1->displayChess(col2);
    cout<<endl<<"Area="<<cb1->getArea();
    cout<<endl<<"Max Area="<<cb1->getMaxArea()<<endl;
    delete cb1;

    cout<<"Enter length,width,color,character of the box separated by spaces: ";
    cin>>len>>wid>>col>>boxChar;
    ColoredBox* cb2;
    cb2 = new ColoredBox(len,wid,col,boxChar);
    cb2->display();
    cout<<"Displaying Transposed: "<<endl;
    cb2->displayTransposed();
    cout<<"Displaying Wider: "<<endl;
    cb2->displayWider();
    cout<<"Displaying Chess, enter the other color: "<<endl;
    cin>>col2;
    cb2->displayChess(col2);
    cout<<"Displaying original again:"<<endl;
    cb2->display();
    cout<<endl<<"Area="<<cb2->getArea();
    cout<<endl<<"Max Area="<<cb2->getMaxArea()<<endl;
    delete cb2;
    return 0;
}