// Program: demo2.cpp
// Purpose: Demonstrate use of bmplip for handling
//          bmp colored and grayscale images
//          Program load a gray image and store in another file
// Author:  Mohammad El-Ramly
// Date:    30 March 2018
// Version: 1.0

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;
unsigned char image[SIZE][SIZE];

void loadImage ();
void saveImage ();
void doSomethingForImage ();

int main()
{
    loadImage();
    doSomethingForImage();
    saveImage();
    return 0;
}

//_________________________________________
void loadImage () {
    char imageFileName[100];

    // Get gray scale image file name
    cout << "Enter the source image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    readGSBMP(imageFileName, image);
}

//_________________________________________
void saveImage () {
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    writeGSBMP(imageFileName, image);
}

//_________________________________________
void doSomethingForImage() {
    unsigned char n[SIZE][SIZE];
    int i,j;
    for (i = 0; i < 256; i++) {
        for (j = 0; j < 256; j++) {
            int sum = image[i][j];
            int count = 1;
            int x,y;
            // calculate the average of the surrounding pixels and then divide the sum on the number of them 
            for ( x = -2; x <= 2; x++) {
                for ( y = -2;y <= 2; y++) {
                    if (i + x >= 0 && i + x < 256 && j + y >= 0 && j + y < 256) {
                        sum += image[i + x][j + y];
                        count++;
                    }
                }
            }

            n[i][j] = sum / count;
        }
    }


    for ( i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
                image[i][j] = n[i][j];

        }
    }
}
# ASSIGNMENT1
// Program: c++filters.cpp
//FCAI_OOP_2023/2024_year two_Assignment1_first submission
// Purpose: to make changes in certain image by using six filters
// Authors & IDs:  Mariam Mahmoud Ibrahim -> 20221207/ Malak Ahmed -> 2022/ Hadeel Khaled -> 20220444
// Date: 5 oct 2023
// Version: 1.0

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;
unsigned char image[SIZE][SIZE];
unsigned char imageT[SIZE][SIZE];
int arr1[128][128];
int arr2[128][128];
int arr3[128][128];
int arr4[128][128];

void load_Image ();
void save_Image ();
void Invert ();
void rotate90 ();
void rotate180 ();
void rotate270 ();
void enlarge (int k);
void shuffle (int k,int b, int a, int s);
void skew_horizontal(double k);
void skew_horizontal45();
void skew_vertical(double k);
void skew_vertical45();
bool menu();

int main() {
    cout<<"welcome to our program\n";
    bool flag=true;
    load_Image();
    while(flag){
        if (!menu())
            flag=false;
    }
    cout<<"Thank you and hope you have enjoyed it\n";
    /*double n;
    load_Image();
    cin>>n;
    if(n!=45)
        skew_vertical(n);
    else
        skew_vertical45();
    save_Image();*/
    return 0;
}

//_________________________________________
void load_Image () {
    char imageFileName[100];
    // Get gray scale image file name
    cout << "Enter the source image file name: ";
    cin >> imageFileName;
    // Add to it .bmp extension and load image (getting time)
    strcat (imageFileName, ".bmp");
    readGSBMP(imageFileName, image);
}

//_________________________________________
void save_Image () {
    char imageFileName[100];
    // Get gray scale image file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;
    // Add to it .bmp extension and load image (saving time)
    strcat (imageFileName, ".bmp");
    writeGSBMP(imageFileName, image);
}

//_________________________________________
void Invert() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {

            //dark tones become light and vice verse
            image[i][j] = 255 - image[i][j];

            // invert colors
        }
    }
}

//_________________________________________
void rotate90() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = i; j < SIZE; j++) {
            // swap(image[i][j],image[j][i]);
            int temp = image[i][j];
            image[i][j]=image[j][i];
            image[j][i]=temp;
            // transpose the matrix
        }
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE/2; j++) {
            // swap(image[i][j],image[j][i]);
            int temp = image[i][j];
            image[i][j]=image[i][SIZE-j-1];
            image[i][SIZE-j-1]=temp;
            // reverse the matrix
        }
    }
}

//_________________________________________
void rotate180(){
    // to rotate 180 it means to rotate 90 two times so call it twice
    rotate90();
    rotate90();
}

//_________________________________________
void rotate270(){
    // to rotate 270 it means that rotate 90 first then rotate 90 again and finally
    // rotate 90 so i will call rotate90 function 3 times
    rotate90();
    rotate90();
    rotate90();
}

//_________________________________________
void enlarge(int k) {
    // k is variable to determine the quad of image
    if (k == 1) { // first quad
        for (int i = 0, t = 0; i < 127, t < SIZE; ++i, t += 2) {
            for (int j = 0, y = 0; j < 127, y < SIZE; ++j, y += 2) {
                // copy each pixel in original image and write it four times in other image
                int x = image[i][j];
                imageT[t][y] = x;
                imageT[t + 1][y] = x;
                imageT[t][y + 1] = x;
                imageT[t + 1][y + 1] = x;
            }
        }
    } else if (k == 2) { // second quad
        for (int i = 0, t = 0; i < 127, t < SIZE; ++i, t += 2) {
            for (int j = 127, y = 0; j < SIZE, y < SIZE; ++j, y += 2) {
                // copy each pixel in original image and write it four times in other image
                int x = image[i][j];
                imageT[t][y] = x;
                imageT[t + 1][y] = x;
                imageT[t][y + 1] = x;
                imageT[t + 1][y + 1] = x;
            }
        }
    } else if (k == 3) { // third quad
        for (int i = 127, t = 0; i < SIZE, t < SIZE; ++i, t += 2) {
            for (int j = 0, y = 0; j < 127, y < SIZE; ++j, y += 2) {
                // copy each pixel in original image and write it four times in other image
                int x = image[i][j];
                imageT[t][y] = x;
                imageT[t + 1][y] = x;
                imageT[t][y + 1] = x;
                imageT[t + 1][y + 1] = x;
            }
        }
    } else if (k == 4) { // fourth quad
        for (int i = 127, t = 0; i < SIZE, t < SIZE; ++i, t += 2) {
            for (int j = 127, y = 0; j < SIZE, y < SIZE; ++j, y += 2) {
                // copy each pixel in original image and write it four times in other image
                int x = image[i][j];
                imageT[t][y] = x;
                imageT[t + 1][y] = x;
                imageT[t][y + 1] = x;
                imageT[t + 1][y + 1] = x;
            }
        }
    }
    //coping all work done on the new image to the original one
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            image[i][j] = imageT[i][j];
}
void shuffle (int k, int b, int a, int s){
    // k b a s is my quarters order
    for (int i = 0 , t=0,y=127,n=127 , B=0; i < 127,t<127,y<SIZE,n<SIZE , B<128; ++i,++t,++y,++n,B++) {
        for (int j = 0 ,d=127,l=0,m=127 ,A=0 ; j < 127,d<SIZE,l<127,m<SIZE , A<128; ++j,++d,++l,++m,++A) {
            // making array of each quad that contain n quad of original image
            arr1[B][A]=image[i][j];
            arr2[B][A]=image[t][d];
            arr3[B][A]=image[y][l];
            arr4[B][A]=image[n][m];
        }
    }
    // k is for first quad in the new image (imageT) while it's value is the number of quad in the
    // original image
    if(k==1){// copy first quad into first place
        for (int i = 0, t = 0; i < 127, t < 128; ++i, t ++) {
            for (int j = 0, y = 0; j < 127, y < 128; ++j, y ++) {
                image[i][j]=arr1[t][y];
            }
        }
    }
    else if (k==2) {// copy second quad into first place
        for (int i = 0, t = 0; i < 127, t < 128; ++i, t++) {
            for (int j = 0, y = 0; j < 127, y < 128; ++j, y++) {
                image[i][j] = arr2[t][y];
            }
        }
    }
    else if(k==3){// copy third quad into first place
        for (int i = 0, t = 0; i < 127, t < 128; ++i, t ++) {
            for (int j = 0, y = 0; j < 127, y < 128; ++j, y ++) {
                image[i][j]=arr3[t][y];
            }
        }
    }
    else if (k==4){// copy fourth quad into first place
        for (int i = 0, t = 0; i < 127, t < 128; ++i, t ++) {
            for (int j = 0, y = 0; j < 127, y < 128; ++j, y ++) {
                image[i][j]=arr4[t][y];
            }
        }
    }// b is for second quad in the new image (imageT) while it's value is the number of quad in the
    // original image
    if(b==1){// copy first quad into second place
        for (int i = 0, t = 0; i < 127, t < 128; ++i, t ++) {
            for (int j = 127, y = 0; j < SIZE, y < 128; ++j, y ++) {
                image[i][j]=arr1[t][y];
            }
        }
    }
    else if (b==2){// copy second quad into second place
        for (int i = 0, t = 0; i < 127, t < 128; ++i, t ++) {
            for (int j = 127, y = 0; j < SIZE, y < 128; ++j, y ++) {
                image[i][j]=arr2[t][y];
            }
        }
    }
    else if (b==3){// copy third quad into second place
        for (int i = 0, t = 0; i < 127, t < 128; ++i, t ++) {
            for (int j = 127, y = 0; j < SIZE, y < 128; ++j, y ++) {
                image[i][j]=arr3[t][y];
            }
        }
    }
    else if (b==4){// copy fourth quad into second place
        for (int i = 0, t = 0; i < 127, t < 128; ++i, t ++) {
            for (int j = 127, y = 0; j < SIZE, y < 128; ++j, y ++) {
                image[i][j]=arr4[t][y];
            }
        }
    }// a is for third quad in the new image (imageT) while it's value is the number of quad in the
    // original image
    if(a==1){// copy first quad into third place
        for (int i = 127, t = 0; i < SIZE, t < 128; ++i, t ++) {
            for (int j = 0, y = 0; j < 127, y < 128; ++j, y ++) {
                image[i][j]=arr1[t][y];
            }
        }
    }
    else if (a==2){// copy second quad into third place
        for (int i = 127, t = 0; i < SIZE, t < 128; ++i, t ++) {
            for (int j = 0, y = 0; j < 127, y < 128; ++j, y ++) {
                image[i][j]=arr2[t][y];
            }
        }
    }
    else if (a==3){// copy third quad into third place
        for (int i = 127, t = 0; i < SIZE, t < 128; ++i, t ++) {
            for (int j = 0, y = 0; j < 127, y < 128; ++j, y ++) {
                image[i][j]=arr3[t][y];
            }
        }
    }
    else if (a==4){// copy fourth quad into third place
        for (int i = 127, t = 0; i < SIZE, t < 128; ++i, t ++) {
            for (int j = 0, y = 0; j < 127, y < 128; ++j, y ++) {
                image[i][j]=arr4[t][y];
            }
        }
    }
    // s is for fourth and last quad in the new image (imageT) while it's value is the number of quad in the
    // original image
    if(s==1){// copy first quad into fourth place
        for (int i = 127, t = 0; i < SIZE, t < 128; ++i, t ++) {
            for (int j = 127, y = 0; j < SIZE, y < 128; ++j, y ++) {
                image[i][j]=arr1[t][y];
            }
        }
    }
    else if (s==2){// copy second quad into fourth place
        for (int i = 127, t = 0; i < SIZE, t < 128; ++i, t ++) {
            for (int j = 127, y = 0; j < SIZE, y < 128; ++j, y ++) {
                image[i][j]=arr2[t][y];
            }
        }
    }
    else if (s==3){// copy third quad into fourth place
        for (int i = 127, t = 0; i < SIZE, t < 128; ++i, t ++) {
            for (int j = 127, y = 0; j < SIZE, y < 128; ++j, y ++) {
                image[i][j]=arr3[t][y];
            }
        }
    }
    else if (s==4){// copy fourth quad into fourth place
        for (int i = 127, t = 0; i < SIZE, t < 128; ++i, t ++) {
            for (int j = 127, y = 0; j < SIZE, y < 128; ++j, y ++) {
                image[i][j]=arr4[t][y];
            }
        }
    }
    /*for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            image[i][j] = imageT[i][j];*/
}
bool menu(){
    // function to resending menu till user type 0
    char m,n;
    int a,b,c,d;
    double q;
    cout<<"please choose filter from 0 to s:\n";
    cout<<"1-Black and White Filter\n"<<"2-Invert Filter\n"<<"3-Merge Filter\n"<<"4-Flip Filter\n"<<"5-Rotating Filter\n"<<"6-Darken and Lighten Filter\n"<<"7-Detect Edges\n8-Enlarge Image\n9-Shrink Image\na-Mirror Image\nb-Shuffle Image\nc-Blur Image\nd-Crop Image\ne-Skew Horizontal\nf-Skew Vertical\n"<<"s-Save image to file\n"<<"0-Exit\n";
    cin>>m;
    switch(m){
        case '1':
            //function name حطيه يا هديل
            return true;
            break;
        case '2':
            Invert();
            return true;
            break;
        case '3':
            //function name حطيه يا هديل
            return true;
            break;
        case '4':
            //function name حطيه يا هديل
            return true;
            break;
        case '5':
            cout<<"choose one of directions\n 1-90\n 2-180\n 3-270\n";
            cin>>n;
            if(n=='1') {
                load_Image();
                rotate90();
            }
            else if (n=='2'){
                load_Image();
                rotate180();
            }
            else if (n=='3'){
                load_Image();
                rotate270();
            }
            return true;
            break;
        case '6':
            //function name حطيه يا هديل
            return true;
            break;
        case '7':
            //function name حطيه يا هديل
            return true;
            break;
        case '8':
            cout<<"please enter which quad do you want\n 1-first\n 2-second\n 3-third\n 4-fourth\n";
            cin>>a;
            enlarge(a);
            return true;
            break;
        case '9':
            //function name حطيه يا هديل
            return true;
            break;
        case 'a':
            //function name حطيه يا هديل
            return true;
            break;
        case 'b':
            cout<<"please enter the order you want to shuffle the image\n";
            cin>>a>>b>>c>>d;
            shuffle(a,b,c,d);
            return true;
            break;
        case 'c':
            //function name حطيه يا هديل
            return true;
            break;
        case 'd':
            //function name حطيه يا هديل
            return true;
            break;
        case 'e':
            cout<<"please enter an angle to skew horizontally image according to it\n";
            cin>>q;
            if(q!=45)
                skew_horizontal(q);
            else
                skew_horizontal45();
            return true;
            break;
        case 'f':
            cout<<"please enter an angle to skew vertically image according to it\n";
            cin>>q;
            if(q!=45)
                skew_vertical(q);
            else
                skew_vertical45();
            return true;
            break;
        case 's':
            save_Image();
            cout<<"if you want to save image and load another one click 1\nif you want to save image then stop 2\n";
            cin>>n;
            if(n=='1') {
                load_Image();
            }
            else
                return true;
            return true;
            break;
        case '0':
            return false;
    }
}
void skew_horizontal(double k){
    // continue
    double pi=2*acos(0.0);// to get pi accurate value
    k=(pi*k)/180;// to get angle by radian
    double let=tan(k)*256;// get # of pixels will be white (to leave it )
    double n=256.0/(256-let);// get # of pixels will be taken from old image (compressed image)
    double start = let/256/* steps i will move (make it like ladder)*/,used=0,help;
    int moved=0,pixs=0;// pixels avg that i will copy & number olf pixels
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            // to make all new image white
            imageT[i][j] = 255;
    for (int i = 0; i < SIZE; i++){// move on row and rows will be constants
        help=0;// curent this will define where i should start and where i will end
        for (int j = let-used; j < SIZE-used; j++){// loop for column begin from # of pixels i will leave in new image
            moved=0,pixs=0;
            for( int m =max(0,(int)ceil(help-n))/* to get region and to avoid -ve values*/;m<min(SIZE,(int)ceil(help+n))/* to make sure it will not get out SIZE*/;++m,++pixs){// loop on old image
                // pixels i need to use & increment pixels #
                moved+=image[i][m];
            }// sum of all pixels will be compressed
            moved/=max(1,pixs);// get pixels average (sum of them/there number)
            imageT[i][j]=moved;
            help+=n;// no. of pixels used
        }
        used+=start;
    }
    /*int start=SIZE-1,end=sqrt((255*255)+(rest*rest));
    for (int i = n; i < SIZE; i+=n){
        for (int j = 0; j < SIZE; j++){
            imageT[end][start]=image[i][j];
        }
    }*/
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            // to copy new image in old one
            image[i][j] = imageT[i][j];
}
void skew_horizontal45(){
    //it will give me straight line in the off diagonal of the matrix
    int f=255;
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            // to make all new image white
            imageT[i][j] = 255;
    for(int i=0; i<SIZE; ++i)
        //make straight line diagonally
        imageT[i][f--]=0;
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            // to copy new image in old one
            image[i][j] = imageT[i][j];
}
void skew_vertical(double k){
    // continue
    double pi=2*acos(0.0);// to get pi accurate value
    k=(pi*k)/180;// to get angle by radian
    double let=tan(k)*256;// get # of pixels will be white (to leave it )
    double n=256.0/(256-let);// get # of pixels will be taken from old image (compressed image)
    double start = let/256/* steps i will move (make it like ladder)*/,used=0,help;
    int moved=0,pixs=0;// pixels avg that i will copy & number olf pixels
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            // to make all new image white
            imageT[i][j] = 255;
    for (int i = 0; i < SIZE; i++){// move on column and columns will be constants
        help=0;// curent this will define where i should start and where i will end
        for (int j = let-used; j < SIZE-used; j++){// loop for row begin from # of pixels i will leave in new image
            moved=0,pixs=0;
            for( int m =max(0,(int)ceil(help-n))/* to get region and to avoid -ve values*/;m<min(SIZE,(int)ceil(help+n))/* to make sure it will not get out SIZE*/;++m,++pixs){// loop on old image
                // pixels i need to use & increment pixels #
                moved+=image[m][i];
            }// sum of all pixels will be compressed
            moved/=max(1,pixs);// get pixels average (sum of them/there number)
            imageT[j][i]=moved;//row become column and vice versa
            help+=n;// no. of pixels used
        }
        used+=start;
    }
    /*int start=SIZE-1,end=sqrt((255*255)+(rest*rest));
    for (int i = n; i < SIZE; i+=n){
        for (int j = 0; j < SIZE; j++){
            imageT[end][start]=image[i][j];
        }
    }*/
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            // to copy new image in old one
            image[i][j] = imageT[i][j];
}
void skew_vertical45(){
    //it will give me straight line in the principal diagonal of the matrix
    int f=255;
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            // to make all new image white
            imageT[i][j] = 255;
    for(int i=0; i<SIZE; ++i)
        //make straight line diagonally
        imageT[f--][i]=0;
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            // to copy new image in old one
            image[i][j] = imageT[i][j];
}
