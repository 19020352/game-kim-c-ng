#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <SDL_mixer.h>
#include <iostream>
#include <SDL_ttf.h>
#include <sstream>
//Screen dimension constants
const int SCREEN_WIDTH = 942;
const int SCREEN_HEIGHT = 656;
const int BUTTON_WIDTH = 385;
const int BUTTON_HEIGHT = 40;
Uint8 unit8 = 255;
int gemcount = 4;

struct plate{
 int a1; //position on board
 int b1; //position on board
 int condition;
 int g;//gem number
 int x; //position on window
 int y; //position on window
 plate(){}
};

//Texture wrapper class
class LTexture
{
	public:
		LTexture();

		~LTexture();

		bool loadFromFile( std::string path );

        void setColor( Uint8 red, Uint8 green, Uint8 blue );

		void setBlendMode( SDL_BlendMode blending );

		void setAlpha( Uint8 alpha );

		bool loadFromRenderedText( std::string textureText, SDL_Color textColor );

		void free();

		void render( int x, int y );

		int getWidth();
		int getHeight();

	private:
		SDL_Texture* mTexture;

		int mWidth;
		int mHeight;
};

class LButton
{
	public:
		//Initializes internal variables
		LButton();

		//Sets top left position
		void setPosition( int x, int y );

		//Handles mouse event
		void handleEvent_back( SDL_Event* e ,bool &q,int &scene);
        void handleEvent_easy( SDL_Event* e ,bool &q,int &scene);
        void handleEvent_normal( SDL_Event* e ,bool &q,int &scene);
        void handleEvent_hard( SDL_Event* e ,bool &q,int &scene);
		//Shows button sprite
		void render();

	private:
		//Top left position
		SDL_Point mPosition;


};

void renderboard();
void rerenderboard();
void getboard();
void regetboard();
bool checkboard();
void clearboard();
void swap_up();
bool outofmove();
void swap_upBOOST2();
void swap_upgrade();
void swap_down();
void swap_left();
void swap_right();
void checkpoint();
bool init();


bool loadMedia();


void close();

SDL_Window* gWindow = NULL;

SDL_Renderer* gRenderer = NULL;



LTexture gBackgroundTexture;
LTexture gem[8];
int x_c=68,y_c=40, a=1,b=1; //cursor direction and codernate
LTexture blank;
LTexture cursor;
LTexture cursor_n;//cursor normal
LTexture cursor_h;//cursor hexagon
LTexture name;
LTexture firstbackground;
LTexture background_3;
LTexture pressenter;
LTexture backtotittlescreen;
LTexture backtotittlescreen_color;
LTexture second;
LButton btts;
LTexture easy;
LTexture easy_color;
LTexture easy_tex;
LButton easy_mode;
LTexture normal;
LTexture normal_color;
LTexture normal_tex;
LButton normal_mode;
LTexture hard;
LTexture hard_color;
LTexture hard_tex;
LButton hard_mode;
LTexture plus1;
LTexture outofmove_tex;
LTexture endgame;
TTF_Font *gFont = NULL;
LTexture score_tex;
LTexture moves_tex;
LTexture plusmoves_tex;
SDL_Color color;
LTexture yourscore;

SDL_Rect gSpriteClips[2];

Mix_Music *music = NULL;
Mix_Chunk *diamond = NULL;
Mix_Chunk *select = NULL;

int score=0;
int moves=20;

std::string score_string(int score ){

std::stringstream ss;
ss << score;
std::string str = ss.str();
return str;
}

std::string moves_string(int moves){

std::stringstream ss;
ss << moves;
std::string str = ss.str();
return str;
}

std::string plusmoves_string(int plusmoves){
std::string fff="+ ";
std::string ff=" moves";
 if(plusmoves==1){ff=" move";}
std::stringstream ss;
ss << plusmoves;
std::string str = ss.str();
return fff+str+ff;
}

LButton::LButton()
{
	mPosition.x = 0;
	mPosition.y = 0;

}

void LButton::setPosition( int x, int y )
{
	mPosition.x = x;
	mPosition.y = y;
}

void LButton::handleEvent_back( SDL_Event* e ,bool &q,int &scene)
{
	//If mouse event happened
	if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )
	{
		second=backtotittlescreen_color;
		int x, y;
		SDL_GetMouseState( &x, &y );
		bool inside = true;
		if( x < mPosition.x )
		{
			inside = false;
		}
		else if( x > mPosition.x + 385)
		{
			inside = false;
		}
		else if( y < mPosition.y )
		{
			inside = false;
		}
		else if( y > mPosition.y + 40 )
		{
			inside = false;
		}
		if( !inside )
		{
			second=backtotittlescreen;
		}
		else
		{
			switch( e->type )
			{
				case SDL_MOUSEMOTION:

				break;

				case SDL_MOUSEBUTTONDOWN:
                q=true;scene=1;second=backtotittlescreen;
				break;

				case SDL_MOUSEBUTTONUP:

				break;
			}
		}
	}
}

void LButton::handleEvent_easy( SDL_Event* e ,bool &q,int &scene){
    if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )
	{
		easy_tex=easy_color;
		int x, y;
		SDL_GetMouseState( &x, &y );
		bool inside = true;
		if( x < mPosition.x )
		{
			inside = false;
		}
		else if( x > mPosition.x + 270)
		{
			inside = false;
		}
		else if( y < mPosition.y )
		{
			inside = false;
		}
		else if( y > mPosition.y + 36 )
		{
			inside = false;
		}
		if( !inside )
		{
			easy_tex=easy;
		}
		else
		{
			switch( e->type )
			{
				case SDL_MOUSEMOTION:

				break;

				case SDL_MOUSEBUTTONDOWN:
                q=true;gemcount=4;scene=3;easy_tex=easy;
				break;

				case SDL_MOUSEBUTTONUP:

				break;
			}
		}
	}
};

void LButton::handleEvent_normal( SDL_Event* e ,bool &q,int &scene){
 if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )
	{
		normal_tex=normal_color;
		int x, y;
		SDL_GetMouseState( &x, &y );
		bool inside = true;
		if( x < mPosition.x )
		{
			inside = false;
		}
		else if( x > mPosition.x + 215)
		{
			inside = false;
		}
		else if( y < mPosition.y )
		{
			inside = false;
		}
		else if( y > mPosition.y + 33 )
		{
			inside = false;
		}
		if( !inside )
		{
			normal_tex=normal;
		}
		else
		{
			switch( e->type )
			{
				case SDL_MOUSEMOTION:

				break;

				case SDL_MOUSEBUTTONDOWN:
                q=true;gemcount=6;scene=3;normal_tex=normal;
				break;

				case SDL_MOUSEBUTTONUP:

				break;
			}
		}
	}
};

void LButton::handleEvent_hard( SDL_Event* e ,bool &q,int &scene){
 if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )
	{
		hard_tex=hard_color;
		int x, y;
		SDL_GetMouseState( &x, &y );
		bool inside = true;
		if( x < mPosition.x )
		{
			inside = false;
		}
		else if( x > mPosition.x + 339)
		{
			inside = false;
		}
		else if( y < mPosition.y )
		{
			inside = false;
		}
		else if( y > mPosition.y + 40 )
		{
			inside = false;
		}
		if( !inside )
		{
			hard_tex=hard;
		}
		else
		{
			switch( e->type )
			{
				case SDL_MOUSEMOTION:

				break;

				case SDL_MOUSEBUTTONDOWN:
                q=true;gemcount=8;scene=3;hard_tex=hard;
				break;

				case SDL_MOUSEBUTTONUP:

				break;
			}
		}
	}
};

LTexture::LTexture()
{
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	free();
}

bool LTexture::loadFromFile( std::string path )
{
	free();

	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0xFF, 0xFF, 0xFF ) );

        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		SDL_FreeSurface( loadedSurface );
	}

	mTexture = newTexture;
	return mTexture != NULL;
}

bool LTexture::loadFromRenderedText( std::string textureText, SDL_Color textColor )
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
	if( textSurface == NULL )
	{
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}
	else
	{
		//Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
		if( mTexture == NULL )
		{
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface( textSurface );
	}

	//Return success
	return mTexture != NULL;
}

 void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
	SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void LTexture::setBlendMode( SDL_BlendMode blending )
{
	SDL_SetTextureBlendMode( mTexture, blending );
}

void LTexture::setAlpha( Uint8 alpha )
{
	SDL_SetTextureAlphaMod( mTexture, alpha );
}

void LTexture::free()
{
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
        mTexture=NULL;

	}
}

void LTexture::render( int x, int y )
{
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };
	SDL_RenderCopy( gRenderer, mTexture, NULL, &renderQuad );
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}

bool init()
{
	bool success = true;

	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{

		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		gWindow = SDL_CreateWindow( "Kim cương", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
				if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
				{
					printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
					success = false;
				}
				if( TTF_Init() == -1 )
				{
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	bool success = true;
            gem[0].loadFromFile("image/0.png");
            cursor_h.loadFromFile( "image/cursor_h.png" );
            cursor_n.loadFromFile( "image/cursor_n.png" );
	        gem[1].loadFromFile( "image/1.png" );
			gem[2].loadFromFile( "image/2.png" );
            gem[3].loadFromFile( "image/3.png" );
            gem[4].loadFromFile( "image/4.png" );
            gem[5].loadFromFile( "image/5.png" );
            gem[6].loadFromFile( "image/6.png" );
            gem[7].loadFromFile( "image/7.png" );
            gem[8].loadFromFile( "image/8.png" );
            hard.loadFromFile( "image/hard.png" );
            hard_color.loadFromFile( "image/hard_color.png" );
            normal.loadFromFile( "image/normal.png" );
            normal_color.loadFromFile( "image/normal_color.png" );
            easy.loadFromFile( "image/easy.png" );
            easy_color.loadFromFile( "image/easy_color.png" );
            background_3.loadFromFile( "image/background(3).png" );
            name.loadFromFile( "image/name.png" );
            firstbackground.loadFromFile( "image/background.png" );
            pressenter.loadFromFile( "image/pressenter.png" );
            backtotittlescreen.loadFromFile( "image/back to tittle screen.png" );
            backtotittlescreen_color.loadFromFile( "image/backtotittle.png" );
            plus1.loadFromFile( "image/plus1.png" );
            outofmove_tex.loadFromFile("image/outofmove.png");
            endgame.loadFromFile("image/endgame.png");
            yourscore.loadFromFile("image/yourscore.png");
            btts.setPosition( SCREEN_WIDTH - BUTTON_WIDTH, SCREEN_HEIGHT - BUTTON_HEIGHT );
            easy_mode.setPosition( 100, 350 );
            normal_mode.setPosition( 100, 400 );
            hard_mode.setPosition( 100, 450 );
            gFont = TTF_OpenFont( "font/pixelmix.ttf", 30 );
            //sound load
            music = Mix_LoadMUS( "sound/music.wav" );
            diamond = Mix_LoadWAV( "sound/diamond.wav" );
            select = Mix_LoadWAV( "sound/select.wav" );

            color = { 255, 215, 0 };

	if( !gBackgroundTexture.loadFromFile( "image/background (2).png" ) )
	{

		printf( "Failed to load background texture image!\n" );
		success = false;
	}

	return success;
}

void close()
{

	for(int i=1;i<9;i++){
        gem[i].free();
	}
    yourscore.free();
    hard.free();
    score_tex.free();
    moves_tex.free();
    plusmoves_tex.free();
	hard_color.free();
	normal.free();
	normal_color.free();
	backtotittlescreen.free();
	gBackgroundTexture.free();
	firstbackground.free();
	name.free();
	easy.free();
	easy_color.free();
	background_3.free();
    cursor.free();
    backtotittlescreen_color.free();
    pressenter.free();
    plus1.free();
    TTF_CloseFont( gFont );
    Mix_FreeChunk( diamond );
	Mix_FreeChunk( select );
    Mix_FreeMusic( music );
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;
	IMG_Quit();
	SDL_Quit();
	TTF_Quit();
}

void swap_up(plate p[12][12],plate &now,plate &up){
    	if(a==1) {return;}
    	int t=0;
     while(t<=59){
            SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );
     		    gBackgroundTexture.render( 0, 0 );
     		     score_tex.loadFromRenderedText( score_string(score).c_str(), color );
                score_tex.render(665,90);
                moves_tex.loadFromRenderedText( moves_string(moves).c_str(), color );
                moves_tex.render(670,260);
                for(int i=1;i<=10;i++){
                      for(int j=1;j<=10;j++){
                    if(i==a and j==b){continue;}
                    if(i==a-1 and j==b){continue;}
                        gem[p[i][j].g].render(p[i][j].x,p[i][j].y);
                      }}
                gem[now.g].render(now.x,now.y-t);
                gem[up.g].render(up.x,up.y+t);
                cursor_n.render(now.x,now.y-t);
                cursor_n.render(up.x,up.y+t);
				SDL_RenderPresent( gRenderer );
     SDL_Delay(4);
     t++;
     }
     t=now.g;now.g=up.g;up.g=t;
}
void swap_upBOOST(plate p[12][12],plate &now,plate &up){
    	if(a==1) {return;}
    	int t=0;
       double time=0.07;
     while(t<=59){
            SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );
     		    gBackgroundTexture.render( 0, 0 );
     		     score_tex.loadFromRenderedText( score_string(score).c_str(), color );
                score_tex.render(665,90);
                moves_tex.loadFromRenderedText( moves_string(moves).c_str(), color );
                moves_tex.render(670,260);
                for(int i=1;i<=10;i++){
                      for(int j=1;j<=10;j++){
                    if(i==now.a1 and j==up.b1){continue;}
                    if(i==now.a1-1 and j==up.b1){continue;}
                        gem[p[i][j].g].render(p[i][j].x,p[i][j].y);
                      }}
                gem[up.g].render(up.x,up.y+t);
				SDL_RenderPresent( gRenderer );
     SDL_Delay(time*up.a1);
     t++;
     }
     t=now.g;now.g=up.g;up.g=t;
}

void swap_upBOOST2(plate p[12][12],plate &now){
    	if(a==1) {return;}
    	double t=0;
      int dem=0;
     while(t<=59){
            SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );
     		    gBackgroundTexture.render( 0, 0 );
     		     score_tex.loadFromRenderedText( score_string(score).c_str(), color );
                score_tex.render(665,90);
                moves_tex.loadFromRenderedText( moves_string(moves).c_str(), color );
                moves_tex.render(670,260);
                for(int i=1;i<=10;i++){
                      for(int j=1;j<=10;j++){
                    if (i<=now.a1 and i>=1 and j==now.b1 and p[i][j].g!=0 ) {gem[p[i][j].g].render(p[i][j].x,p[i][j].y+t);}
                        else{gem[p[i][j].g].render(p[i][j].x,p[i][j].y);}
                      }}
				SDL_RenderPresent( gRenderer );
     SDL_Delay(0.1);
     t+=0.8;
     }
     for(int i=now.a1;i>=2;i--){p[i][now.b1].g=p[i-1][now.b1].g;}
     p[1][now.b1].g=0;

}

void swap_down(plate p[12][12],plate &now,plate &down){
    	if(a==10) {return;}
    	int t=0;

     while(t<=59){
            SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );
     		    gBackgroundTexture.render( 0, 0 );
     		     score_tex.loadFromRenderedText( score_string(score).c_str(), color );
                score_tex.render(665,90);
                moves_tex.loadFromRenderedText( moves_string(moves).c_str(), color );
                moves_tex.render(670,260);
                for(int i=1;i<=10;i++){
                      for(int j=1;j<=10;j++){
                    if(i==a and j==b){continue;}
                    if(i==a+1 and j==b){continue;}
                        gem[p[i][j].g].render(p[i][j].x,p[i][j].y);
                      }}
                gem[now.g].render(now.x,now.y+t);
                gem[down.g].render(down.x,down.y-t);
                cursor_n.render(now.x,now.y+t);
                cursor_n.render(down.x,down.y-t);
				SDL_RenderPresent( gRenderer );
     SDL_Delay(4);
     t++;
     }
     t=now.g;now.g=down.g;down.g=t;
}

void swap_left(plate p[12][12],plate &now,plate &left){
if(b==1) {return;}
    	int t=0;
     while(t<=59){
            SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );
     		    gBackgroundTexture.render( 0, 0 );
     		     score_tex.loadFromRenderedText( score_string(score).c_str(), color );
                score_tex.render(665,90);
                moves_tex.loadFromRenderedText( moves_string(moves).c_str(), color );
                moves_tex.render(670,260);
                for(int i=1;i<=10;i++){
                      for(int j=1;j<=10;j++){
                    if(i==a and j==b){continue;}
                    if(i==a and j==b-1){continue;}
                        gem[p[i][j].g].render(p[i][j].x,p[i][j].y);
                      }}
                gem[now.g].render(now.x-t,now.y);
                gem[left.g].render(left.x+t,left.y);
                cursor_n.render(now.x-t,now.y);
                cursor_n.render(left.x+t,left.y);
				SDL_RenderPresent( gRenderer );
     SDL_Delay(4);
     t++;
     }
     t=now.g;now.g=left.g;left.g=t;
}

void swap_right(plate p[12][12],plate &now,plate &right){
if(b==10) {return;}
    	int t=0;

     while(t<=59){
            SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );
     		    gBackgroundTexture.render( 0, 0 );
     		     score_tex.loadFromRenderedText( score_string(score).c_str(), color );
                score_tex.render(665,90);
                moves_tex.loadFromRenderedText( moves_string(moves).c_str(), color );
                moves_tex.render(670,260);
                for(int i=1;i<=10;i++){
                      for(int j=1;j<=10;j++){
                    if(i==a and j==b){continue;}
                    if(i==a and j==b+1){continue;}
                        gem[p[i][j].g].render(p[i][j].x,p[i][j].y);
                      }}
                gem[now.g].render(now.x+t,now.y);
                gem[right.g].render(right.x-t,right.y);
                cursor_n.render(now.x+t,now.y);
                cursor_n.render(right.x-t,right.y);
				SDL_RenderPresent( gRenderer );
     SDL_Delay(4);
     t++;
     }
     t=now.g;now.g=right.g;right.g=t;
}

bool checkboard(plate p[12][12]){
   bool check=false;
   int t=0;
   for(int i=1;i<=10;i++){
            for(int j=1;j<=8;j++){
            if(p[i][j].g==p[i][j+1].g and p[i][j].g==p[i][j+2].g and p[i][j].g!=0 ){
                    check=true;p[i][j].condition=0;
                    p[i][j+1].condition=0;p[i][j+2].condition=0;
            }
               }
   }
      for(int i=1;i<=8;i++){
            for(int j=1;j<=10;j++){
            if(p[i][j].g==p[i+1][j].g and p[i][j].g==p[i+2][j].g and p[i][j].g!=0){
           check=true;p[i][j].condition=0;p[i+1][j].condition=0;
           p[i+2][j].condition=0;
            }
            }
   }
          // std::cout<<t<<" ";
          return check;
}

void getboard(plate p[12][12]){

  int b=40;int a;int r;
    for(int i=1;i<=10;i++){
            a=68;
            for(int j=1;j<=10;j++){
                r=rand() % gemcount + 1;
                p[i][j].a1=i;p[i][j].b1=j;
                p[i][j].condition=0;
                p[i][j].g=r;
                p[i][j].x=a;a+=59;
                p[i][j].y=b;
            }
            b+=59;
            }

}

void regetboard(plate p[12][12]){
  int r;
    for(int i=1;i<=10;i++){
            for(int j=1;j<=10;j++){
       if(p[i][j].g==0){ r=rand() % gemcount + 1;
                p[i][j].g=r;
       p[i][j].condition=0;
               }
            }}

}

 void renderboard(plate p[12][12]){
            for(int i=1;i<=10;i++){
                      for(int j=1;j<=10;j++){
                        gem[p[i][j].g].render(p[i][j].x,p[i][j].y);
                      }}
}

void rerenderboard(plate p[12][12]){
      double t;

         for(int i=10;i>=1;i--){
            t=0;
            while(t<=40+59*(i-1))
                     {
                        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );
     		    gBackgroundTexture.render( 0, 0 );
     		     score_tex.loadFromRenderedText( score_string(score).c_str(), color );
                score_tex.render(665,90);
                moves_tex.loadFromRenderedText( moves_string(moves).c_str(), color );
                moves_tex.render(670,260);
                     for(int m=1;m<=10;m++){
                      for(int n=1;n<=10;n++){
                      if( p[m][n].condition==1){gem[p[m][n].g].render(p[m][n].x,p[m][n].y);}
                      }}
     		         for(int k=1;k<=10;k++){
     		             if(p[i][k].condition==0){

     		         gem[p[i][k].g].render(p[i][k].x,t);}}
     		         t+=0.5;
     		         SDL_RenderPresent( gRenderer );
     		         SDL_Delay(0);

            }
         for(int k=1;k<=10;k++){ p[i][k].condition=1;}
           }
}

void rerenderboardbk(plate p[12][12]){
      double t;
         for(int i=10;i>=1;i--){
          if(i%2==0) {
		   for(int j=10;j>=1;j--){
           if(p[i][j].condition==0){
                        t=0;
            while(t<=p[i][j].y)
                     {
                        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );
     		    gBackgroundTexture.render( 0, 0 );
     		     score_tex.loadFromRenderedText( score_string(score).c_str(), color );
                score_tex.render(665,90);
                moves_tex.loadFromRenderedText( moves_string(moves).c_str(), color );
                moves_tex.render(670,260);
                     for(int m=1;m<=10;m++){
                      for(int n=1;n<=10;n++){
                      if( p[m][n].condition==1){gem[p[m][n].g].render(p[m][n].x,p[m][n].y);}
                      }}
     		         gem[p[i][j].g].render(p[i][j].x,t);t+=i/2+2;
     		         SDL_RenderPresent( gRenderer );
     		         SDL_Delay(0);

            };
                      p[i][j].condition=1;
           }
          }}
          else{
		  for(int j=1;j<=10;j++){
           if(p[i][j].condition==0){
                        t=0;
            while(t<=p[i][j].y)
                     {
                        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );
     		    gBackgroundTexture.render( 0, 0 );
     		     score_tex.loadFromRenderedText( score_string(score).c_str(), color );
                score_tex.render(665,90);
                moves_tex.loadFromRenderedText( moves_string(moves).c_str(), color );
                moves_tex.render(670,260);
                     for(int m=1;m<=10;m++){
                      for(int n=1;n<=10;n++){
                      if( p[m][n].condition==1){gem[p[m][n].g].render(p[m][n].x,p[m][n].y);}
                      }}
     		         gem[p[i][j].g].render(p[i][j].x,t);t+=i/2+2;
     		         SDL_RenderPresent( gRenderer );
     		         SDL_Delay(0);

            };
                      p[i][j].condition=1;
           }

		  }
         }

}

}

void rerenderboard2(plate p[12][12]){
            double t;
         for(int i=10;i>=1;i--){
          if(i%2==0) {
		   for(int j=10;j>=1;j--){
           if(p[i][j].condition==0){
                        t=0;
            while(t<=p[i][j].y)
                     {
                        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );
     		    gBackgroundTexture.render( 0, 0 );
     		     score_tex.loadFromRenderedText( score_string(score).c_str(), color );
                score_tex.render(665,90);
                moves_tex.loadFromRenderedText( moves_string(moves).c_str(), color );
                moves_tex.render(670,260);
                     for(int m=1;m<=10;m++){
                      for(int n=1;n<=10;n++){
                      if( p[m][n].condition==1){gem[p[m][n].g].render(p[m][n].x,p[m][n].y);}
                      }}
     		         gem[p[i][j].g].render(p[i][j].x,t);t+=1.8;
     		         SDL_RenderPresent( gRenderer );
     		         SDL_Delay(0);

            };
                      p[i][j].condition=1;
           }
          }}
          else{
		  for(int j=1;j<=10;j++){
           if(p[i][j].condition==0){
                        t=0;
            while(t<=p[i][j].y)
                     {
                        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );
     		    gBackgroundTexture.render( 0, 0 );
     		     score_tex.loadFromRenderedText( score_string(score).c_str(), color );
                score_tex.render(665,90);
                moves_tex.loadFromRenderedText( moves_string(moves).c_str(), color );
                moves_tex.render(670,260);
                     for(int m=1;m<=10;m++){
                      for(int n=1;n<=10;n++){
                      if( p[m][n].condition==1){gem[p[m][n].g].render(p[m][n].x,p[m][n].y);}
                      }}
     		         gem[p[i][j].g].render(p[i][j].x,t);t+=1.8;
     		         SDL_RenderPresent( gRenderer );
     		         SDL_Delay(0);

            };
                      p[i][j].condition=1;
           }

		  }
         }

}}


void clearboard(plate p[12][12]){
  int t=255;double f=0;int plusmoves=0;
  for(int i=1;i<=10;i++){
            for(int j=1;j<=10;j++){
                if(p[i][j].condition==0){plusmoves++;}
            }}
            plusmoves-=3;
            plusmoves_tex.loadFromRenderedText( plusmoves_string(plusmoves).c_str(),{0,191,255});
   Mix_PlayChannel( -1, diamond, 0 );
    while(t>0){

    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );
     		    gBackgroundTexture.render( 0, 0 );
     		     score_tex.loadFromRenderedText( score_string(score).c_str(), color );
                score_tex.render(665,90);
                moves_tex.loadFromRenderedText( moves_string(moves).c_str(), color );
                moves_tex.render(670,260);
                for(int i=1;i<=10;i++){
                      for(int j=1;j<=10;j++){
                    if(p[i][j].condition!=0) { gem[p[i][j].g].setAlpha( 255 );
                            gem[p[i][j].g].render(p[i][j].x,p[i][j].y);}
                    if(p[i][j].condition==0)  {gem[p[i][j].g].setAlpha( t );
                            gem[p[i][j].g].render(p[i][j].x,p[i][j].y);
                            if(t<=225){

                             if(plusmoves!=0)  {
                                    plusmoves_tex.setAlpha( t );
                                    plusmoves_tex.render(670,260-f);}

                                    plus1.setAlpha(t);
                                    plus1.render(p[i][j].x,p[i][j].y-f); }
                            }
                      }}
				SDL_RenderPresent( gRenderer );
     SDL_Delay(1);
     t--;
     f+=0.1;
    }
    for(int i=1;i<=8;i++){gem[i].setAlpha(255);}
for(int i=1;i<=10;i++){
            for(int j=1;j<=10;j++){
                if(p[i][j].condition==0){p[i][j].g=0;p[i][j].condition=1;score++;}
            }}
            moves+=plusmoves;
}

void clearboard2(plate p[12][12]){
  int t=255;double f=0;int plusmoves=0;
  for(int i=1;i<=10;i++){
            for(int j=1;j<=10;j++){
                if(p[i][j].condition==0){plusmoves++;}
            }}
   Mix_PlayChannel( -1, diamond, 0 );
    while(t>0){
 plusmoves_tex.loadFromRenderedText( plusmoves_string(plusmoves).c_str(),{0,191,255});
    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );
     		    gBackgroundTexture.render( 0, 0 );
     		     score_tex.loadFromRenderedText( score_string(score).c_str(), color );
                score_tex.render(665,90);
                moves_tex.loadFromRenderedText( moves_string(moves).c_str(), color );
                moves_tex.render(670,260);
                for(int i=1;i<=10;i++){
                      for(int j=1;j<=10;j++){
                    if(p[i][j].condition!=0) { gem[p[i][j].g].setAlpha( 255 );
                            gem[p[i][j].g].render(p[i][j].x,p[i][j].y);}
                    if(p[i][j].condition==0)  {gem[p[i][j].g].setAlpha( t );
                            gem[p[i][j].g].render(p[i][j].x,p[i][j].y);
                            if(t<=225){

                             if(plusmoves!=0)  {
                                    plusmoves_tex.setAlpha( t );
                                    plusmoves_tex.render(670,260-f);}

                                    plus1.setAlpha(t);
                                    plus1.render(p[i][j].x,p[i][j].y-f); }
                            }
                      }}
				SDL_RenderPresent( gRenderer );
     SDL_Delay(1);
     t--;
     f+=0.1;
    }
    for(int i=1;i<=8;i++){gem[i].setAlpha(255);}
for(int i=1;i<=10;i++){
            for(int j=1;j<=10;j++){
                if(p[i][j].condition==0){p[i][j].g=0;p[i][j].condition=1;score++;}
            }}
            moves+=plusmoves;
}

bool outofmove(plate p[12][12]){
bool check=true;
   int t=0;
   for(int i=1;i<=10;i++){
            for(int j=1;j<=10;j++){
            if(j<=9 and p[i][j].g==p[i][j+1].g ){
                if(j<=7 and p[i][j].g==p[i][j+3].g){check=false;break;}
                if(i>=2 and j<=8 and p[i][j].g==p[i-1][j+2].g){check=false;break;}
                if(i<=9 and j<=8 and p[i][j].g==p[i+1][j+2].g){check=false;break;}
                if(j>=2 and i>=2 and p[i][j].g==p[i-1][j-1].g){check=false;break;}
                if(i<=9 and j>=2 and p[i][j].g==p[i+1][j-1].g){check=false;break;}
                if(j>=3 and p[i][j].g==p[i][j-2].g){check=false;break;}
            }
            if(j<=8 and p[i][j].g==p[i][j+2].g){
                if(i>=2 and j<=9 and p[i][j].g==p[i-1][j+1].g){check=false;break;}
                if(i<=9 and j<=9 and p[i][j].g==p[i+1][j+1].g){check=false;break;}
            }
        }
   }
      for(int i=1;i<=10;i++){
            for(int j=1;j<=10;j++){
            if(i<=9 and p[i][j].g==p[i+1][j].g ){
                if(i<=7 and p[i][j].g==p[i+3][j].g){check=false;break;}
                if(i<=8 and j<=9 and p[i][j].g==p[i+2][j+1].g){check=false;break;}
                if(i<=8 and j>=2 and p[i][j].g==p[i+2][j-1].g){check=false;break;}
                if(i>=3 and p[i][j].g==p[i-2][j].g){check=false;break;}
                if(i>=2 and j<=9 and p[i][j].g==p[i-1][j+1].g){check=false;break;}
                if(j>=2 and i>=2 and p[i][j].g==p[i-1][j-1].g){check=false;break;}
            }
            if(i<=8 and p[i][j].g==p[i+2][j].g){
                if(i<=9 and j<=9 and p[i][j].g==p[i+1][j+1].g){check=false;break;}
                if(i<=9 and j>=2 and p[i][j].g==p[i+1][j-1].g){check=false;break;}
            }
            }
   }
          // std::cout<<t<<" ";
          return check;
}

int main( int argc, char* args[] )
{

	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
        //Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
		    int scene=1;
          while(1){
		    if(scene==1){
             score=0;
            moves=20;
		    bool quit_first = false;
			SDL_Event e_first;
			int tt=1;
			int name_blend=255;
			double pressenter_blend=0;
		    while(!quit_first){
                while( SDL_PollEvent( &e_first ) != 0 ){
				        if( e_first.type == SDL_QUIT )
					{
						quit_first = true;close();return 0;

					}
				   else if(e_first.type == SDL_KEYDOWN){
                         if(e_first.key.keysym.sym==13){quit_first=true;scene=2; }
                    }
				}
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );
     		    firstbackground.render( 0, 0 );
                name.setAlpha(name_blend);
                if(name_blend==0){tt=0;}
                if(name_blend==255){tt=1;}
                if(tt==1){name_blend--;pressenter_blend+=1;}
                if(tt==0){name_blend++;pressenter_blend-=1;}
                name.render(25,50);
                pressenter.setAlpha(pressenter_blend);
                pressenter.render(260,500);
				SDL_RenderPresent( gRenderer );
				SDL_Delay(3);

            }}
             if(scene==2){
            	bool quit_second = false;
              SDL_Event e_second;
			while( !quit_second )
			{
				//Handle events on queue
				easy_tex=easy;
				normal_tex=normal;
				hard_tex=hard;
				while( SDL_PollEvent( &e_second ) != 0 )
				{
					//User requests quit
					if( e_second.type == SDL_QUIT )
					{
						quit_second = true;close();return 0;
					}

						btts.handleEvent_back( &e_second ,quit_second,scene);
                      easy_mode.handleEvent_easy( &e_second ,quit_second,scene);
                      normal_mode.handleEvent_normal( &e_second ,quit_second,scene);
                      hard_mode.handleEvent_hard( &e_second ,quit_second,scene);
              SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
              SDL_RenderClear( gRenderer );
              background_3.render( 0, 0 );

					second.render(SCREEN_WIDTH - BUTTON_WIDTH, SCREEN_HEIGHT - BUTTON_HEIGHT);

                    easy_tex.render(100,350);
                    normal_tex.render(100,400);
                    hard_tex.render(100,450);
				SDL_RenderPresent( gRenderer );
			//	if(quit_second==true){scene=3;}
			}}}

     if(scene==3){
		    cursor=cursor_n;int c=1;
		    plate p[12][12];

           for(;;){ getboard(p);if(!checkboard(p)){break;}}

					//Play the music
             if(Mix_PlayMusic(music, -1)==-1) {
       printf("Mix_PlayMusic: %s\n", Mix_GetError());}

   rerenderboardbk(p);

			bool quit = false;
			SDL_Event e;
            int mouse=0;
             int mouse2=0;
			while( !quit )
			{

				while( SDL_PollEvent( &e ) != 0 and !checkboard(p))
				{
					//User requests quit

					if( e.type == SDL_QUIT )
					{
						quit = true;Mix_HaltMusic();close();return 0;
					}
else if( (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP ) and !checkboard(p))
	{
	    int x, y;
		SDL_GetMouseState( &x, &y );

		for(int i=1;i<=10;i++){
            for(int j=1;j<=10;j++){
              if(x>=p[i][j].x and x<=p[i][j].x+57 and y>=p[i][j].y and y<=p[i][j].y+57) {
                x_c=p[i][j].x;y_c=p[i][j].y;cursor=cursor_n;}}}
if(x>=68+10*58 or y>=40+10*58 or x<68 or y<40){cursor=gem[0];}
			switch( e.type )
			{
				case SDL_MOUSEMOTION:
				break;

				case SDL_MOUSEBUTTONDOWN:
                cursor=cursor_h;
                Mix_PlayChannel( -1, select, 0 );
                if(mouse==1){

                    if(x>=p[a+1][b].x and x<=p[a+1][b].x+58 and y>=p[a+1][b].y and y<=p[a+1][b].y+58 and a<=9) {
                    swap_down(p,p[a][b],p[a+1][b]);moves--;
                                if(!checkboard(p)){moves++;swap_down(p,p[a][b],p[a+1][b]);}
                                if(checkboard(p)){clearboard(p);}
              }

             else if(x>=p[a-1][b].x and x<=p[a-1][b].x+58 and y>=p[a-1][b].y and y<=p[a-1][b].y+58 and a>=2) {
                    swap_up(p,p[a][b],p[a-1][b]);moves--;
                                     if(!checkboard(p)){moves++;swap_up(p,p[a][b],p[a-1][b]);}
                                     if(checkboard(p)){clearboard(p);}
              }
              else if(x>=p[a][b+1].x and x<=p[a][b+1].x+58 and y>=p[a][b+1].y and y<=p[a][b+1].y+58 and b<=9) {
                    swap_right(p,p[a][b],p[a][b+1]);moves--;
                                        if(!checkboard(p)){moves++;swap_right(p,p[a][b],p[a][b+1]);}
                                        if(checkboard(p)){clearboard(p);}
              }
                else if(x>=p[a][b-1].x and x<=p[a][b-1].x+58 and y>=p[a][b-1].y and y<=p[a][b-1].y+58 and b>=2) {
                    swap_left(p,p[a][b],p[a][b-1]);moves--;
                                       if(!checkboard(p)){moves++;swap_left(p,p[a][b],p[a][b-1]);}
                                       if(checkboard(p)){clearboard(p);}
              }
             mouse=0;mouse2=1;
                }
             else{  for(int i=1;i<=10;i++){
            for(int j=1;j<=10;j++){
              if(x>=p[i][j].x and x<=p[i][j].x+58 and y>=p[i][j].y and y<=p[i][j].y+58) {a=i;b=j;}}}
              mouse=0;mouse2=0;}
				break;

				case SDL_MOUSEBUTTONUP:
              cursor=cursor_n;
              if(x>=p[a][b].x and x<=p[a][b].x+58 and y>=p[a][b].y and y<=p[a][b].y+58 ) {
                    mouse=1;
              }
     if(mouse2==0){  if(x>=p[a+1][b].x and x<=p[a+1][b].x+58 and y>=p[a+1][b].y and y<=p[a+1][b].y+58 and a<=9) {
                    swap_down(p,p[a][b],p[a+1][b]);moves--;
                                if(!checkboard(p)){moves++;swap_down(p,p[a][b],p[a+1][b]);}
                                if(checkboard(p)){clearboard(p);}
              }

             else if(x>=p[a-1][b].x and x<=p[a-1][b].x+58 and y>=p[a-1][b].y and y<=p[a-1][b].y+58 and a>=2) {
                    swap_up(p,p[a][b],p[a-1][b]);moves--;
                                     if(!checkboard(p)){moves++;swap_up(p,p[a][b],p[a-1][b]);}
                                     if(checkboard(p)){clearboard(p);}
              }
              else if(x>=p[a][b+1].x and x<=p[a][b+1].x+58 and y>=p[a][b+1].y and y<=p[a][b+1].y+58 and b<=9) {
                    swap_right(p,p[a][b],p[a][b+1]);moves--;
                                        if(!checkboard(p)){moves++;swap_right(p,p[a][b],p[a][b+1]);}
                                        if(checkboard(p)){clearboard(p);}
              }
               else if(x>=p[a][b-1].x and x<=p[a][b-1].x+58 and y>=p[a][b-1].y and y<=p[a][b-1].y+58 and b>=2) {
                    swap_left(p,p[a][b],p[a][b-1]);moves--;
                                       if(!checkboard(p)){moves++;swap_left(p,p[a][b],p[a][b-1]);}
                                       if(checkboard(p)){clearboard(p);}
              }}
				break;
			}

	}
				}

       if(checkboard(p)){clearboard2(p);};
                      for(int j=10;j>=1;j--){
                           for(int k=1;k<=6;k++)  {
                            for(int i=2;i<=10;i++){
                         if(p[i][j].g==0 and p[i-1][j].g!=0){swap_upBOOST2(p,p[i][j]);}
                      }}}
             for(;;){
                if(!checkboard(p)){break;}
                if(checkboard(p)){clearboard2(p);
                for(int j=10;j>=1;j--){
                           for(int k=1;k<=6;k++)  {
                            for(int i=2;i<=10;i++){
                         if(p[i][j].g==0 and p[i-1][j].g!=0){swap_upBOOST2(p,p[i][j]);}
                      }}}
                }

             }
                 regetboard(p);
                 rerenderboard2(p);
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

                    btts.handleEvent_back( &e ,quit,scene);

     		    gBackgroundTexture.render( 0, 0 );
                renderboard(p);
                cursor.render(x_c,y_c);
                second.render(SCREEN_WIDTH - BUTTON_WIDTH, SCREEN_HEIGHT - BUTTON_HEIGHT);
                score_tex.loadFromRenderedText( score_string(score).c_str(), color );
                score_tex.render(665,90);
                moves_tex.loadFromRenderedText( moves_string(moves).c_str(), color );
                moves_tex.render(670,260);
				SDL_RenderPresent( gRenderer );
				int oom=0;
				if(outofmove(p) ){
                        for(int i=1;i<=255;i++){
                              getboard(p);
                              SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				              SDL_RenderClear( gRenderer );
				              gBackgroundTexture.render( 0, 0 );
                              renderboard(p);
                              outofmove_tex.setAlpha(oom );oom++;
                              outofmove_tex.render(150,250);
                              SDL_RenderPresent( gRenderer );
                              SDL_Delay(10 );

                        }
                        for(;;){getboard(p);if(!checkboard(p) and !outofmove(p)){break;}}
                        for(int i=1;i<=10;i++){
                          for(int j=1;j<=10;j++){
                             p[i][j].condition=1;}}
                        }
                     if(moves==0 ){
                        int all_blend=255;
                         while(all_blend>=0) {
                        for(int i=1;i<=8;i++){
                             gem[i].setAlpha(all_blend);
                     }
                     SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				              SDL_RenderClear( gRenderer );
				              gBackgroundTexture.render( 0, 0 );
               score_tex.loadFromRenderedText( score_string(score).c_str(), color );
                   score_tex.render(665,90);
                  moves_tex.loadFromRenderedText( moves_string(moves).c_str(), color );
                   moves_tex.render(670,260);
                     renderboard(p);
                     endgame.setAlpha(255-all_blend);
                     endgame.render(250,250);
                     SDL_RenderPresent( gRenderer );
                     SDL_Delay(10);
                     all_blend--;
                     }
                     bool out=false;
                       SDL_Event lost;
                       while(!out) {
                           while( SDL_PollEvent( &lost ) != 0 )
				{
					//User requests quit
					if( lost.type == SDL_QUIT )
					{
						out = true;close();return 0;
					}


                    btts.handleEvent_back( &lost ,out,scene);

				       }
				       SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				              SDL_RenderClear( gRenderer );
				              gBackgroundTexture.render( 0, 0 );
				         second.render(SCREEN_WIDTH - BUTTON_WIDTH, SCREEN_HEIGHT - BUTTON_HEIGHT);
                   score_tex.loadFromRenderedText( score_string(score).c_str(), color );
                   score_tex.render(665,90);
                     endgame.render(250,250);
                     yourscore.render(300,400);score_tex.render(560,405);
                     SDL_RenderPresent( gRenderer );
                     }
                     quit=true;
                }
			}

		}}}
	}

	//Free resources and close SDL
	close();
   return 0;
}
