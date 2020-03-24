#include<stdio.h>
#include<stdbool.h>
#include<time.h>
#include<math.h>
#include<SDL2/SDL.h>
int w=300,h=400;
bool isRun=true;
SDL_Window*win=NULL;
SDL_Renderer*ren=NULL;
SDL_Rect player;
int playerSpeed=20;
int score=0;
struct{
	double vx,vy;
	SDL_Rect rect;
	int speed;
}ball;
bool init(){
	if(SDL_Init(SDL_INIT_VIDEO)<0){
		return false;
	}
	win=SDL_CreateWindow("pBall",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,w,h,SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE);
	if(win==NULL){
		return false;
	}
	ren=SDL_CreateRenderer(win,-1,SDL_RENDERER_ACCELERATED);
	if(ren==NULL){
		return false;
	}
	player.w=88;
	player.h=35;
	player.x=(w-player.w)/2;
	player.y=h-player.h;
	srand(time(NULL));
	ball.vx=(rand()%2000-1000)/1000;
	ball.vy=sqrt(1.0-(ball.vx*ball.vx));
	ball.speed=100;
	ball.rect.w=30;
	ball.rect.h=30;
	ball.rect.x=(w-ball.rect.w)/2;
	ball.rect.y=0;
	return true;
}
void close(){
	if(ren!=NULL){
		SDL_DestroyRenderer(ren);
	}
	if(win!=NULL){
		SDL_DestroyWindow(win);
	}
}
void event(){
	SDL_Event e;
	if(SDL_PollEvent(&e)){
		switch(e.type){
			case SDL_QUIT:
				isRun=false;
				break;
			case SDL_WINDOWEVENT:
				switch(e.window.event){
					case SDL_WINDOWEVENT_RESIZED:
						SDL_GetWindowSize(win,&w,&h);
						if(player.x>w-player.w){
							player.x=w-player.w;
						}
						break;
					default:
						break;
				}
				break;
			case SDL_KEYDOWN:
				switch(e.key.keysym.sym){
					case SDLK_a:
					case SDLK_LEFT:
						if(player.x>0){
							player.x-=(SDL_GetTicks()/playerSpeed)%2;
						}
						break;
					case SDLK_d:
					case SDLK_RIGHT:
						if(player.x<w-player.w){
							player.x+=(SDL_GetTicks()/playerSpeed)%2;
						}
						break;
					default:
						break;
				}
			default:
				break;
		}
	}
}
void drawPlayer(){
	SDL_SetRenderDrawColor(ren,0xFF,0,0,0xFF);
	player.y=h-player.h;
	SDL_RenderFillRect(ren,&player);
}
void drawBall(){
	ball.rect.x+=(SDL_GetTicks()/(int)(ball.vx*ball.speed))%99999;
	ball.rect.y+=(SDL_GetTicks()/(int)(ball.vy*ball.speed))%99999;
	SDL_SetRenderDrawColor(ren,0,0,0xFF,0xFF);
	SDL_RenderFillRect(ren,&ball.rect);
	if(ball.rect.x<=0 || ball.rect.x>=w-ball.rect.w){
		ball.vx=-ball.vx;
	}
	if(ball.rect.y<=0){
		ball.vy=-ball.vy;
	}else if(ball.rect.y>=h-player.h && ball.rect.x>=player.x && ball.rect.x<=player.x+player.w-ball.rect.w){
		ball.vy=-ball.vy;
		ball.speed=1+rand()%300;
		score+=1;
	}else if(ball.rect.y>=h){

	}
}
void render(){
	SDL_SetRenderDrawColor(ren,0,0,0,0xFF);
	SDL_RenderClear(ren);
	drawPlayer();
	drawBall();
	SDL_RenderPresent(ren);
}
int main(int argc,char**argv){
	if(!init()){
		printf("init error%s\n",SDL_GetError());
		return 1;
	}
	while(isRun){
		render();
		event();
	}
	close();
	return 0;
}

