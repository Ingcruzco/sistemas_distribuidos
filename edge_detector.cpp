#include<iostream>
#include <stdlib.h>
#include <sys/time.h>
#include <cmath>
#include <vector>
// #include "stb/stb_image.h"
#include <string>
using namespace std;
extern "C" {
    #define STB_IMAGE_IMPLEMENTATION
    #include "stb/stb_image.h"
    #define STB_IMAGE_WRITE_IMPLEMENTATION
    #include "stb/stb_image_write.h"
}
#define LOW 20
#define HIGH 25
#define THREADS 1
#define CHANNEL 3

unsigned char *compute_grayscale(unsigned char *img,int width,int height,int channels);
unsigned char *compute_blur(unsigned char *img, int width,int height,int channels);
void compute_gradient(unsigned char* img,unsigned char* img_original, int width,int height);
// unsigned char* convert_to_gray(unsigned char* img,int width,int height);


int main(){
    struct timeval tval_before, tval_after, tval_result;
    gettimeofday(&tval_before, NULL);
    int counter;
    unsigned char *grayImage;
    unsigned char *blurImage;
     string inputPath="picture5.jpg";
    int width,height,channels;
    unsigned char *img = stbi_load(inputPath.c_str(), &width, &height, &channels, 0);
    if(img ==NULL) {
        printf("Error cargando la imagen\n");
        exit(1);
    }
    printf("Imagen cargada con un ancho de: %dpx, un alto de %dpx y %d canales\n",width,height,channels);
    grayImage=compute_grayscale(img,width,height,channels);
    stbi_write_jpg("gray_scale.jpg",width,height,1,grayImage,100);
    blurImage=compute_blur(grayImage,width,height,channels);
    stbi_write_jpg("blur_filter.jpg",width,height,1,blurImage,100);
    // gradientImage=compute_gradient(blurImage,width,height);
    
    free(blurImage);

    unsigned char* gradientImage = stbi_load("blur_filter.jpg",&width, &height, &channels, 0);

    compute_gradient(gradientImage,img,width,height);
    stbi_image_free(img);
    free(grayImage);
    free(gradientImage);
    gettimeofday(&tval_after, NULL);

    timersub(&tval_after, &tval_before, &tval_result);
    printf("Time elapsed: %ld.%06ld\n", (long int)tval_result.tv_sec, (long int)tval_result.tv_usec);
    return 0;
}

unsigned char *compute_grayscale(unsigned char *img,int width,int height,int channels){
    
    int gray_channels=channels==4?2:1;
    size_t img_size =width*height*channels;
    size_t gray_img_size=width*height*gray_channels;
    unsigned char* gray_img=(unsigned char*)malloc(gray_img_size);

    for(unsigned char *p=img,*pg=gray_img;p!=img + img_size;p+=channels,pg+=gray_channels){
        *pg=(uint8_t)((*p + *(p+1)+ *(p+2))/3.0);
        if(channels==4){
            *(pg+1)=*(p+3);
        }
    }


    return gray_img;
}

unsigned char *compute_blur(unsigned char *img, int width,int height,int channels){

    float kernel[5][5]={{0.00390625,0.015625,0.0234375,0.015625,0.00390625},{0.015625,0.0625,0.09375,0.0625,0.015625},{0.0234375,0.09375,0.140625,0.09375,0.0234375},{0.015625,0.0625,0.09375,0.0625,0.015625},{0.00390625,0.015625,0.0234375,0.015625,0.00390625}};
    int gray_channels=1;
    int offset=2;
    int iterator=0;
    size_t img_size =width*height;
    size_t gray_img_size=width*height*gray_channels;
    int acc;
    unsigned char* gray_img=(unsigned char*)malloc(gray_img_size);
    unsigned char* pg=gray_img;
    int xn,yn,y,x;
    for(int i=0;i<gray_img_size;i++){
    // for(int x=0;x<width;x++){
        y=(int)floor(i/width);
        x=(int)(i-y*width);
        acc=0;
        
        for(int a=0;a<5;a++){
            for(int b=0;b<5;b++){
                xn=x+a-offset;
                yn=y+b-offset;
                if(xn<0){
                    xn=0;
                }else if(xn>=width){
                    xn=width-1;
                }
                if(yn<0){
                    yn=0;
                }else if(yn>=height){
                    yn=height-1;
                }
                acc+=*(img+yn*width+xn)*kernel[a][b];
            }
        }
        *(pg+i)=(uint8_t)(acc);
    }




    return gray_img;
}

void compute_gradient(unsigned char* img,unsigned char* img_original, int width,int height){

    size_t img_size =width*height;
    size_t gray_img_size=width*height*CHANNEL;

    unsigned char* gray_img;
    gray_img=compute_grayscale(img,width,height,CHANNEL);
    unsigned char* output_image=(unsigned char*)malloc(width*height*CHANNEL);



    int magx,magy,h,w;
    int mag;
    int acc=0;
    for(int i=0;i<height*width;i++){
            h=(int)floor(i/width);
            w=(int)(i-h*width);
            acc=h*width+w;
            if((w>0)&&(w<width-1)&& (h>0)&&(h<height-1)){
                magx=*(gray_img+acc+1)-*(gray_img+acc-1);
                magy=*(gray#include<iostream>
#include <stdlib.h>
#include <sys/time.h>
#include <cmath>
#include <vector>
// #include "stb/stb_image.h"
#include <string>
using namespace std;
extern "C" {
    #define STB_IMAGE_IMPLEMENTATION
    #include "stb/stb_image.h"
    #define STB_IMAGE_WRITE_IMPLEMENTATION
    #include "stb/stb_image_write.h"
}
#define LOW 20
#define HIGH 25
#define THREADS 1
#define CHANNEL 3

unsigned char *compute_grayscale(unsigned char *img,int width,int height,int channels);
unsigned char *compute_blur(unsigned char *img, int width,int height,int channels);
void compute_gradient(unsigned char* img,unsigned char* img_original, int width,int height);
// unsigned char* convert_to_gray(unsigned char* img,int width,int height);


int main(){
    struct timeval tval_before, tval_after, tval_result;
    gettimeofday(&tval_before, NULL);
    int counter;
    unsigned char *grayImage;
    unsigned char *blurImage;
     string inputPath="picture5.jpg";
    int width,height,channels;
    unsigned char *img = stbi_load(inputPath.c_str(), &width, &height, &channels, 0);
    if(img ==NULL) {
        printf("Error cargando la imagen\n");
        exit(1);
    }
    printf("Imagen cargada con un ancho de: %dpx, un alto de %dpx y %d canales\n",width,height,channels);
    grayImage=compute_grayscale(img,width,height,channels);
    stbi_write_jpg("gray_scale.jpg",width,height,1,grayImage,100);
    blurImage=compute_blur(grayImage,width,height,channels);
    stbi_write_jpg("blur_filter.jpg",width,height,1,blurImage,100);
    // gradientImage=compute_gradient(blurImage,width,height);
    
    free(blurImage);

    unsigned char* gradientImage = stbi_load("blur_filter.jpg",&width, &height, &channels, 0);

    compute_gradient(gradientImage,img,width,height);
    stbi_image_free(img);
    free(grayImage);
    free(gradientImage);
    gettimeofday(&tval_after, NULL);

    timersub(&tval_after, &tval_before, &tval_result);
    printf("Time elapsed: %ld.%06ld\n", (long int)tval_result.tv_sec, (long int)tval_result.tv_usec);
    return 0;
}

unsigned char *compute_grayscale(unsigned char *img,int width,int height,int channels){
    
    int gray_channels=channels==4?2:1;
    size_t img_size =width*height*channels;
    size_t gray_img_size=width*height*gray_channels;
    unsigned char* gray_img=(unsigned char*)malloc(gray_img_size);

    for(unsigned char *p=img,*pg=gray_img;p!=img + img_size;p+=channels,pg+=gray_channels){
        *pg=(uint8_t)((*p + *(p+1)+ *(p+2))/3.0);
        if(channels==4){
            *(pg+1)=*(p+3);
        }
    }


    return gray_img;
}

unsigned char *compute_blur(unsigned char *img, int width,int height,int channels){

    float kernel[5][5]={{0.00390625,0.015625,0.0234375,0.015625,0.00390625},{0.015625,0.0625,0.09375,0.0625,0.015625},{0.0234375,0.09375,0.140625,0.09375,0.0234375},{0.015625,0.0625,0.09375,0.0625,0.015625},{0.00390625,0.015625,0.0234375,0.015625,0.00390625}};
    int gray_channels=1;
    int offset=2;
    int iterator=0;
    size_t img_size =width*height;
    size_t gray_img_size=width*height*gray_channels;
    int acc;
    unsigned char* gray_img=(unsigned char*)malloc(gray_img_size);
    unsigned char* pg=gray_img;
    int xn,yn,y,x;
    for(int i=0;i<gray_img_size;i++){
    // for(int x=0;x<width;x++){
        y=(int)floor(i/width);
        x=(int)(i-y*width);
        acc=0;
        
        for(int a=0;a<5;a++){
            for(int b=0;b<5;b++){
                xn=x+a-offset;
                yn=y+b-offset;
                if(xn<0){
                    xn=0;
                }else if(xn>=width){
                    xn=width-1;
                }
                if(yn<0){
                    yn=0;
                }else if(yn>=height){
                    yn=height-1;
                }
                acc+=*(img+yn*width+xn)*kernel[a][b];
            }
        }
        *(pg+i)=(uint8_t)(acc);
    }




    return gray_img;
}

void compute_gradient(unsigned char* img,unsigned char* img_original, int width,int height){

    size_t img_size =width*height;
    size_t gray_img_size=width*height*CHANNEL;

    unsigned char* gray_img;
    gray_img=compute_grayscale(img,width,height,CHANNEL);
    unsigned char* output_image=(unsigned char*)malloc(width*height*CHANNEL);



    int magx,magy,h,w;_img+acc+width)-*(gray_img+acc-width);
                mag=sqrt(pow(magx,2)+pow(magy,2));
                
                if(mag>HIGH){
                    *(output_image+acc*3)=(uint8_t)255;
                    *(output_image+acc*3+1)=(uint8_t)0;
                    *(output_image+acc*3+2)=(uint8_t)0;
                }
                else{
                    *(output_image+acc*3)=*(img_original+acc*3);
                    *(output_image+acc*3+1)=*(img_original+acc*3+1);
                    *(output_image+acc*3+2)=*(img_original+acc*3+2);    
                }
            }else{
                *(output_image+acc*3)=(uint8_t)*(img_original+acc*3);
                *(output_image+acc*3+1)=(uint8_t)*(img_original+acc*3+1);
                *(output_image+acc*3+2)=(uint8_t)*(img_original+acc*3+2); 
            }
    }

    
    stbi_write_jpg("EDGE_IMAGE.jpg",width,height,3,output_image,100);
    stbi_image_free(output_image);  


}

// unsigned char* convert_to_gray(unsigned char* img,int width,int height){

//    int gray_channels=CHANNEL==4?2:1;
//     size_t img_size =width*height*CHANNEL;
//     size_t gray_img_size=width*height*gray_channels;
//     unsigned char* gray_img=(unsigned char*)malloc(gray_img_size);

//     for(unsigned char *p=img,*pg=gray_img;p!=img + img_size;p+=CHANNEL,pg+=gray_channels){
//         *pg=(uint8_t)((*p + *(p+1)+ *(p+2))/3.0);
//         if(CHANNEL==4){
//             *(pg+1)=*(p+3);
//         }
//     }

//     return gray_img; 

// }















