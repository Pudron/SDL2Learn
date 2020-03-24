#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<stdbool.h>
bool isRun=true;
SDL_Window*win=NULL;
SDL_Renderer*ren=NULL;
SDL_Texture*texBack,*texPeople;
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
	SDL_Surface*temp=IMG_Load("back.png");
	if(temp==NULL){
		return false;
	}
	texBack=SDL_CreateTextureFromSurface(ren,temp);
	SDL_FreeSurface(temp);
	temp=IMG_Load("people.png");
	if(temp==NULL){
		return false;
	}
	SDL_SetColorKey(temp,SDL_TRUE,SDL_MapRGB(temp->format,0xFF,0xFF,0xFF));
	texPeople=SDL_CreateTextureFromSurface(ren,temp);
	SDL_FreeSurface(temp);
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
	SDL_RenderCopy(ren,texBack,NULL,NULL);
	SDL_Rect rect={400,178,66,109};
	SDL_RenderCopy(ren,texPeople,NULL,&rect);
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
