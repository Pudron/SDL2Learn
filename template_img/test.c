#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<stdbool.h>
#include<stdio.h>
bool isRun=true;
SDL_Window*win=NULL;
SDL_Renderer*ren=NULL;
SDL_Texture*tex=NULL;
bool init(){
	if(SDL_Init(SDL_INIT_VIDEO)<0){
		return false;
	}
	win=SDL_CreateWindow("Test",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,640,480,SDL_WINDOW_SHOWN);
	if(win==NULL){
		return false;
	}
	ren=SDL_CreateRenderer(win,-1,SDL_RENDERER_ACCELERATED);
	if(ren==NULL){
		return false;
	}
	return true;
}
bool initIMG(){
	if(!IMG_Init(IMG_INIT_PNG)){
		return false;
	}
	SDL_Surface*temp=IMG_Load("test.png");
	if(temp==NULL){
		return false;
	}
	tex=SDL_CreateTextureFromSurface(ren,temp);
	SDL_FreeSurface(temp);
	if(tex==NULL){
		return false;
	}
	return true;
}
void close(){
	if(tex!=NULL){
		SDL_DestroyTexture(tex);
	}
	if(ren!=NULL){
		SDL_DestroyRenderer(ren);
	}
	if(win!=NULL){
		SDL_DestroyWindow(win);
	}
	IMG_Quit();
	SDL_Quit();
}
void event(){
	SDL_Event e;
	if(SDL_PollEvent(&e)){
		switch(e.type){
			case SDL_QUIT:
				isRun=false;
				break;
			case SDL_KEYDOWN:
				switch(e.key.keysym.sym){
					//case SDLK_a:
					default:
						break;
				}
				break;
			default:
				break;
		}
	}
}
void render(){
	SDL_SetRenderDrawColor(ren,0xFF,0xFF,0xFF,0xFF);
	SDL_RenderClear(ren);
	SDL_RenderCopy(ren,tex,NULL,NULL);
	SDL_RenderPresent(ren);
}
int main(int argc,char**argv){
	if(!init()){
		printf("SDL2 init error:%s\n",SDL_GetError());
		return 1;
	}
	if(!initIMG()){
		printf("IMG init error:%s\n",IMG_GetError());
		return 1;
	}
	while(isRun){
		render();
		event();
	}
	close();
	return 0;
}
