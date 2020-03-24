#include<SDL2/SDL.h>
#include<stdbool.h>
bool isRun=true;
int w=640,h=480;
SDL_Window*win=NULL;
SDL_Renderer*ren=NULL;
void render();
bool init(){
	if(SDL_Init(SDL_INIT_VIDEO)<0){
		return false;
	}
	win=SDL_CreateWindow("Test",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,w,h,SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE);
	if(win==NULL){
		return false;
	}
	ren=SDL_CreateRenderer(win,-1,SDL_RENDERER_ACCELERATED);
	if(ren==NULL){
		return false;
	}
	return true;
}
void close(){
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
			case SDL_WINDOWEVENT:
				if(e.window.event==SDL_WINDOWEVENT_RESIZED){
					SDL_GetWindowSize(win,&w,&h);
				}
			default:
				break;
		}
	}
}
void draw(){
	SDL_Rect r1={w/4,h/4,w/2,h/2};
	SDL_SetRenderDrawColor(ren,0xFF,0,0,0xFF);
	SDL_RenderFillRect(ren,&r1);

	SDL_Rect r2={w/6,h/6,w*2/3,h*2/3};
	SDL_SetRenderDrawColor(ren,0,0,0xFF,0xFF);
	SDL_RenderDrawRect(ren,&r2);
}
void render(){
	SDL_SetRenderDrawColor(ren,0xFF,0xFF,0xFF,0xFF);
	SDL_RenderClear(ren);
	
	SDL_Rect viewp={0,0,w/2,h/2};
	SDL_RenderSetViewport(ren,&viewp);
	draw();
	SDL_Rect v2={w/2,h/2,w/2,h/2};
	SDL_RenderSetViewport(ren,&v2);
	draw();
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
