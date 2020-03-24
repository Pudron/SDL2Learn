#include<SDL2/SDL.h>
#include<SDL_ttf.h>
#include<stdbool.h>
#include<stdio.h>
bool isRun=true;
SDL_Window*win=NULL;
SDL_Renderer*ren=NULL;
SDL_Texture*tex=NULL;
TTF_Font*font=NULL;
SDL_Rect rect={0,0,0,0};
bool init(){
	if(SDL_Init(SDL_INIT_VIDEO)<0){
		return false;
	}
	if(TTF_Init()<0){
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
	font=TTF_OpenFont("FiraCode-Bold.ttf",36);
	if(font==NULL){
		return false;
	}
	SDL_Color tc={0xFF,0,0};
	SDL_Surface*temp=TTF_RenderText_Blended(font,"Hello World!",tc);
	//TTF_RenderText_Solid
	//TTF_RenderText_Shaded
	//TTF_RenderText_Blended
	if(temp==NULL){
		return false;
	}
	rect.w=temp->w;
	rect.h=temp->h;
	tex=SDL_CreateTextureFromSurface(ren,temp);
	SDL_FreeSurface(temp);
	if(tex==NULL){
		return false;
	}
	return true;
}
void close(){
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
	SDL_RenderCopy(ren,tex,NULL,&rect);
	SDL_RenderPresent(ren);
}
int main(int argc,char**argv){
	if(!init()){
		printf("SDL2 init error:%s\n",SDL_GetError());
	}
	while(isRun){
		render();
		event();
	}
	return 0;
}
