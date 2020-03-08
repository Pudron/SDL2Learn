#include<SDL2/SDL.h>
#include<stdbool.h>
bool isRun=true;
SDL_Window*win=NULL;
SDL_Renderer*ren=NULL;
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
			default:
				break;
		}
	}
}
void render(){
	SDL_SetRenderDrawColor(ren,0xFF,0xFF,0xFF,0xFF);
	SDL_RenderClear(ren);

	SDL_Rect r1={170,140,300,200};
	SDL_SetRenderDrawColor(ren,0xFF,0,0,0xFF);
	SDL_RenderFillRect(ren,&r1);

	SDL_Rect r2={70,90,500,300};
	SDL_SetRenderDrawColor(ren,0,0,0xFF,0xFF);
	SDL_RenderDrawRect(ren,&r2);

	SDL_SetRenderDrawColor(ren,0,0xFF,0,0xFF);
	SDL_RenderDrawLine(ren,0,240,640,240);

	SDL_SetRenderDrawColor(ren,0,0,0,0xFF);
	for(int i=0;i<480;i+=6){
		SDL_RenderDrawPoint(ren,320,i);
	}

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
