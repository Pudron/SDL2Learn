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
	win=SDL_CreateWindow("Test",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,100,300,SDL_WINDOW_SHOWN);
	if(win==NULL){
		return false;
	}
	ren=SDL_CreateRenderer(win,-1,SDL_RENDERER_ACCELERATED);
	if(ren==NULL){
		return false;
	}
	SDL_Surface*temp=IMG_Load("test.png");
	if(temp==NULL){
		return false;
	}
	SDL_SetColorKey(temp,SDL_TRUE,SDL_MapRGB(temp->format,0xFF,0xFF,0xFF));
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
	static SDL_Rect rt={0,0,100,300};
	SDL_SetRenderDrawColor(ren,0,0xFF,0xFF,0xFF);
	SDL_RenderClear(ren);
	rt.x=(SDL_GetTicks()/100)%4*100;
	SDL_RenderCopy(ren,tex,&rt,NULL);
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
