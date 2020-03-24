#include<stdio.h>
#include<stdbool.h>
#include<time.h>
#include<math.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_ttf.h>
const double PI=3.1415926535;
const int width=160,height=160;
SDL_Window*win=NULL;
SDL_Renderer*ren=NULL;
TTF_Font*font=NULL;
SDL_Texture*texback=NULL,*texStick=NULL,*texStickH,*texStickM;
bool isRun=false;
bool init(){
    if(SDL_Init(SDL_INIT_VIDEO)<0){
        fprintf(stderr,"SDL init error:%s\n",SDL_GetError());
        return false;
    }
    if(!IMG_Init(IMG_INIT_PNG)){
        fprintf(stderr,"IMG init error:%s\n",IMG_GetError());
        return false;
    }
    if(TTF_Init()<0){
        fprintf(stderr,"TTF init error:%s\n",TTF_GetError());
        return false;
    }
    return true;
}
SDL_Texture*loadImage(const char*file){
    SDL_Surface*temp=IMG_Load(file);
    if(temp==NULL){
        fprintf(stderr,"IMG load error:%s\n",IMG_GetError());
        return NULL;
    }
    SDL_SetColorKey(temp,SDL_TRUE,SDL_MapRGB(temp->format,0xFF,0xFF,0xFF));
    SDL_Texture*texture=SDL_CreateTextureFromSurface(ren,temp);
    SDL_FreeSurface(temp);
    if(texture==NULL){
        fprintf(stderr,"SDL texture error:%s\n",SDL_GetError());
        return NULL;
    }
    return texture;
}
void initUnits(){
    font=TTF_OpenFont("FiraCode-Regular.ttf",16);
    if(font==NULL){
        fprintf(stderr,"TTF open error:%s\n",TTF_GetError());
        return;
    }
    win=SDL_CreateWindow("Clock",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,width,height,SDL_WINDOW_SHOWN|SDL_WINDOW_ALWAYS_ON_TOP);
    if(win==NULL){
        fprintf(stderr,"SDL window error:%s\n",SDL_GetError());
        return;
    }
    ren=SDL_CreateRenderer(win,-1,SDL_RENDERER_ACCELERATED);
    if(ren==NULL){
        fprintf(stderr,"SDL renderer error:%s\n",SDL_GetError());
        return;
    }
    texback=loadImage("background.png");
    if(texback==NULL){
        return;
    }
    texStick=loadImage("stick.png");
    if(texStick==NULL){
        return;
    }
    texStickH=loadImage("stickh.png");
    if(texStickH==NULL){
        return;
    }
    texStickM=loadImage("stickm.png");
    if(texStickM==NULL){
        return;
    }
    isRun=true;
}
void close(){
    if(texback!=NULL){
        SDL_DestroyTexture(texback);
    }
    if(texStick!=NULL){
        SDL_DestroyTexture(texStick);
    }
    if(texStickH!=NULL){
        SDL_DestroyTexture(texStickH);
    }
    if(texStickM!=NULL){
        SDL_DestroyTexture(texStickM);
    }
    if(font!=NULL){
        TTF_CloseFont(font);
    }
    if(ren!=NULL){
        SDL_DestroyRenderer(ren);
    }
    if(win!=NULL){
        SDL_DestroyWindow(win);
    }
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}
void eventHandle(){
    SDL_Event event;
    if(SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_QUIT:
                isRun=false;
                break;
            default:
                break;
        }
    }
}
void render(){
    const SDL_Rect rect={width*7/16,height/16,width/8,height/2};
    const SDL_Point center={width/16,height*7/16};
    time_t nowt=time(NULL);
    struct tm*stm=localtime(&nowt);
    SDL_RenderClear(ren);

    /*画表盘*/
    double tc,ts,rad;
    int len=height/2,len2;
    SDL_RenderCopy(ren,texback,NULL,NULL);
    SDL_SetRenderDrawColor(ren,20,20,20,0xFF);
    for(int i=0;i<60;i++){
        len2=(i%5)?(len-10):(len-30);
        rad=PI/30*i;
        tc=cos(rad);
        ts=sin(rad);
        SDL_RenderDrawLineF(ren,len*tc+len,len-len*ts,len2*tc+len,len-len2*ts);
    }

    /*画针*/
    SDL_RenderCopyEx(ren,texStick,NULL,&rect,stm->tm_sec*6,&center,SDL_FLIP_NONE);
    SDL_RenderCopyEx(ren,texStickH,NULL,&rect,(stm->tm_hour%12)*30+(stm->tm_min*0.5),&center,SDL_FLIP_NONE);
    SDL_RenderCopyEx(ren,texStickM,NULL,&rect,stm->tm_min*6+(stm->tm_sec*0.1),&center,SDL_FLIP_NONE);
    SDL_RenderPresent(ren);
}
int main(int argc,char**argv){
    if(!init()){
        return 1;
    }
    initUnits();
    while(isRun){
        render();
        eventHandle();
    }
    close();
    return 0;
}