#include<SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>
#include<stdbool.h>
#include<stdio.h>
bool isRun=true;
SDL_Window*win=NULL;
SDL_Renderer*ren=NULL;
TTF_Font*font=NULL;
SDL_Texture*tex=NULL;
SDL_Rect rect={100,100,0,0};
bool isOn=false,isDown=false;
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
bool initTTF(){
	if(TTF_Init()<0){
		return false;
	}
	font=TTF_OpenFont("FiraCode-Bold.ttf",22);
	if(font==NULL){
		return false;
	}
	SDL_Surface*temp=TTF_RenderText_Solid(font,"Button",(SDL_Color){0xFF,0xFF,0xFF});
	rect.w=temp->w;
	rect.h=temp->h;
	tex=SDL_CreateTextureFromSurface(ren,temp);
	if(tex==NULL){
		return false;
	}
	SDL_FreeSurface(temp);
	return true;
}
void close(){
	if(font!=NULL){
		TTF_CloseFont(font);
	}
	if(tex!=NULL){
		SDL_DestroyTexture(tex);
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
	int mx,my;
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
			case SDL_MOUSEMOTION:
				SDL_GetMouseState(&mx,&my);
				if(mx>=rect.x && my>=rect.y && mx<=rect.x+rect.w && my<=rect.y+rect.h){
					isOn=true;
				}else{
					isOn=false;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				SDL_GetMouseState(&mx,&my);
				if(mx>=rect.x && my>=rect.y && mx<=rect.x+rect.w && my<=rect.y+rect.h){
					isDown=true;
				}
				break;
			case SDL_MOUSEBUTTONUP:
				SDL_GetMouseState(&mx,&my);
				if(mx>=rect.x && my>=rect.y && mx<=rect.x+rect.w && my<=rect.y+rect.h){
					isDown=false;
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
	if(isDown){
		SDL_SetRenderDrawColor(ren,0xFF,0,0,0xFF);
	}else if(isOn){
		SDL_SetRenderDrawColor(ren,0,0xFF,0,0xFF);
	}else{
		SDL_SetRenderDrawColor(ren,66,66,66,0xFF);
	}
	SDL_RenderFillRect(ren,&rect);
	SDL_RenderCopy(ren,tex,NULL,&rect);
	SDL_RenderPresent(ren);
}
int main(int argc,char**argv){
	if(!init()){
		printf("SDL2 init error:%s\n",SDL_GetError());
		return 1;
	}
	if(!initTTF()){
		printf("TTF init error:%s\n",TTF_GetError());
		return 1;
	}
	while(isRun){
		render();
		event();
	}
	close();
	return 0;
}
