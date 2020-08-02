/** Main.cpp controls lib.h for a simple
 *  Gfx example and Audio example.
 */
#include <SDL.h>
#include <SDL_render.h>
#include <stdlib.h>
#include <SDL_rect.h>
#include <iostream>
#include <random>
using std::default_random_engine;

#define screenw 620
#define screenh 480

SDL_Window* m_window;
SDL_Renderer* m_gRenderer;


void drawTexture(SDL_Texture* texture, SDL_Rect rect) {
    SDL_RenderCopy(m_gRenderer, texture, NULL, &rect);
}

SDL_Texture* createTexture(const char* file, int spriteCode) {
	SDL_Surface* surface = NULL;
    SDL_Texture* texture = NULL;
	
    surface = SDL_LoadBMP(file);
	
	if (spriteCode == 0) {
		SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0xFF, 0, 0xFF));
	}
	
	// 1 for sneek sprite
	// different color key required
	if (spriteCode == 1) {
		SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 0, 0));
	}
	
    texture = SDL_CreateTextureFromSurface(m_gRenderer, surface);
	
    SDL_FreeSurface(surface);
    return texture;
}

int initscreen(int w, int h) {
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        return 1;
    }
    else {
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) ) {
			printf( "Warning: Linear texture filtering not enabled!" );
		}
        m_window = SDL_CreateWindow( "Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN );
        if(m_window == NULL) {
            printf("Window Error! SDL_Error: %s\n", SDL_GetError());
            return 1;
        } else {
            m_gRenderer = SDL_CreateRenderer( m_window, -1, SDL_RENDERER_PRESENTVSYNC );
			if( m_gRenderer == NULL ) {
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				return 1;
			}
        }
    }
    return 0;
}

SDL_Texture* s1Texture = NULL;
int I_ROW = 30;
int J_COLUMN = 12;

char els[30][12] = {0};
char check[30][12] = {0};

bool is_drow_bottom = true; // is or not box down to bottom
    
int count = 0;

int box_point1_i =0,box_point1_j = 5;
int box_point2_i =1,box_point2_j = 5;
int box_point3_i =2,box_point3_j = 5;
int box_point4_i =1,box_point4_j = 6;

int min_left = 5;
int max_right = 6;
int box_center_i =1,box_center_j = 5;

int new_box_point1_i =0,new_box_point1_j = 5;
int new_box_point2_i =1,new_box_point2_j = 5;
int new_box_point3_i =2,new_box_point3_j = 5;
int new_box_point4_i =1,new_box_point4_j = 6;

int new_box_center_i =1,new_box_center_j = 5;


bool drawNewOrNotOnFloor(bool is_down) {
    int caclulateOld = 0;
    for (int i=0;i<29;i++) {
        for (int j=0;j<12;j++) {
            caclulateOld += check[i][j];
        }
    }

    check[box_point1_i][box_point1_j] = 0;
    check[box_point2_i][box_point2_j] = 0;
    check[box_point3_i][box_point3_j] = 0;
    check[box_point4_i][box_point4_j] = 0;

    //redraw box
    //one second down one floor
    

    check[new_box_point1_i][new_box_point1_j] = 1;
    check[new_box_point2_i][new_box_point2_j] = 1;
    check[new_box_point3_i][new_box_point3_j] = 1;
    check[new_box_point4_i][new_box_point4_j] = 1;

    int caclulateNew = 0;
    for (int i=0;i<29;i++) {
        for (int j=0;j<12;j++) {
            caclulateNew += check[i][j];
        }
    } 
    bool flag = false;
    if (caclulateOld == caclulateNew){
        //clean old box
        els[box_point1_i][box_point1_j] = 0;
        els[box_point2_i][box_point2_j] = 0;
        els[box_point3_i][box_point3_j] = 0;
        els[box_point4_i][box_point4_j] = 0;
        
        els[new_box_point1_i][new_box_point1_j] = 1;
        els[new_box_point2_i][new_box_point2_j] = 1;
        els[new_box_point3_i][new_box_point3_j] = 1;
        els[new_box_point4_i][new_box_point4_j] = 1;

        box_point1_i = new_box_point1_i;
        box_point1_j = new_box_point1_j;
        
        box_point2_i = new_box_point2_i;
        box_point2_j = new_box_point2_j;

        box_point3_i = new_box_point3_i;
        box_point3_j = new_box_point3_j;

        box_point4_i = new_box_point4_i;
        box_point4_j = new_box_point4_j;

        box_center_i = new_box_center_i;
        box_center_j = new_box_center_j;
        flag = true;
    } else {
        //wrong need reset from els!! 
        // check[new_box_point1_i][new_box_point1_j] = 0;
        // check[new_box_point2_i][new_box_point2_j] = 0;
        // check[new_box_point3_i][new_box_point3_j] = 0;
        // check[new_box_point4_i][new_box_point4_j] = 0;
        for (int i=0;i<29;i++) {
            for (int j=0;j<12;j++) {
                check[i][j] = els[i][j];
            }
        }

        new_box_point1_i = box_point1_i;
        new_box_point1_j = box_point1_j;
        
        new_box_point2_i = box_point2_i;
        new_box_point2_j = box_point2_j;

        new_box_point3_i = box_point3_i;
        new_box_point3_j = box_point3_j;

        new_box_point4_i = box_point4_i;
        new_box_point4_j = box_point4_j;

        new_box_center_i = box_center_i;
        new_box_center_j = box_center_j;
        
        if (is_down) {
            is_drow_bottom= true;
        }
        flag = false;
    }
    
    SDL_SetRenderDrawColor( m_gRenderer, 100, 0, 0, 0xFF );
            SDL_RenderClear( m_gRenderer ); 
    for(int i=0;i<30;i++) {
        for (int j=0;j<12;j++) {
            if (els[i][j]==1) {
                SDL_Rect s1Rect = { j*20, i*20, 20, 20 }; //player x y w h
                drawTexture(s1Texture, s1Rect);
            }
        }
    }
    //update
    SDL_RenderPresent( m_gRenderer );
    return true;
}

void print(char *value, char argv[30][12]) {
    printf( "%s \n", value);
    for(int i =0;i<29;i++) {
        for (int j=0;j<12;j++) {
            printf( "%d ", argv[i][j] );
        }
        printf( "\n");
    }
}

/** CHARS ARE DONE */
//int mousex; int mousey; int mouseon = 0;
//int red = 0; int green = 0; int blue = 0;

int main ( int argc, char** argv ) {
	
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        return 1;
    }
    else {
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) ) {
			printf( "Warning: Linear texture filtering not enabled!" );
		}
        m_window = SDL_CreateWindow( "Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 600, 800, SDL_WINDOW_SHOWN );
        if(m_window == NULL) {
            printf("Window Error! SDL_Error: %s\n", SDL_GetError());
            return 1;
        } else {
            m_gRenderer = SDL_CreateRenderer( m_window, -1, SDL_RENDERER_PRESENTVSYNC );
			if( m_gRenderer == NULL ) {
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				return 1;
			}
        }
    }
	s1Texture = createTexture("bmp/els_single.bmp",0);
	
	//clearScreen
	SDL_SetRenderDrawColor( m_gRenderer, 100, 0, 0, 0xFF );
    SDL_RenderClear( m_gRenderer );
	
	//update
	SDL_RenderPresent( m_gRenderer );
    /* program main loop */

    // A basic main loop to prevent blocking
    bool is_running = true;
    SDL_Event event;
    int tps = 50;
    int delay_millisecond = 1000 / tps; //10
    

    int DEFAULT_SPEED = 50;
    int speed = 50;
    
    char str_els[10];
    strcpy( str_els , "els" );
    char str_check[10];
    strcpy( str_check , "check" );
    default_random_engine e;
    while (is_running) {
        count = ++count;
        if (is_drow_bottom) {
            //check if delete line
            
            printf( "check if delete line blew   \n" );

            print(str_els, els);
            print(str_check, check);
            
            bool deteleRowRedraw = false;
            for (int i=29;i> 1;i--) {
                bool need_delete = true;
                for (int j=0;j<12;j++) {
                    if (els[i][j] == 0) {
                        need_delete = false;
                    }
                }
                
                if (need_delete) {
                    deteleRowRedraw = true;
                    for (int j=0;j<12;j++) {
                        check[i][j] = 0;
                        els[i][j] = 0;
                    }
                    for (int m=i;m>=0;m--) {
                        for (int j=0;j<12;j++) {
                            check[m][j] = check[m-1][j];
                            els[m][j] = els[m-1][j];
                        }
                    }
                    for (int j=0;j<12;j++) {
                        check[0][j] = 0;
                        els[0][j] = 0;
                    }
                }
            }
            print(str_els, els);
            print(str_check, check);
            printf( "deteleRowRedraw up  %d \n", deteleRowRedraw );
            if (deteleRowRedraw) {
                bool success = drawNewOrNotOnFloor(false);
                continue;
            }
            //drawNewBoxOnTop();
            //draw top new box
            int caclulateOld= 0;
            for (int i=0;i<3;i++) {
                for (int j=0;j<12;j++) {
                    caclulateOld += check[i][j];
                }
            }
            if (caclulateOld != 0 ){
                is_running = false;
            }
            
            int random = e();
            //int random = 3;
            if (random%4 == 0) {
                //T字形 box
                box_point1_i =0,box_point1_j = 5;
                box_point2_i =1,box_point2_j = 5;
                box_point3_i =2,box_point3_j = 5;
                box_point4_i =1,box_point4_j = 6;
                box_center_i =1,box_center_j = 5;

                new_box_point1_i =0,new_box_point1_j = 5;
                new_box_point2_i =1,new_box_point2_j = 5;
                new_box_point3_i =2,new_box_point3_j = 5;
                new_box_point4_i =1,new_box_point4_j = 6;
                new_box_center_i =1,new_box_center_j = 5;

                min_left = 5;
                max_right = 6;
            } else if (random%4 == 1) {
                //Z字形 box
                box_point1_i =0,box_point1_j = 5;
                box_point2_i =0,box_point2_j = 6;
                box_point3_i =1,box_point3_j = 6;
                box_point4_i =2,box_point4_j = 7;
                box_center_i =1,box_center_j = 6;

                new_box_point1_i =0,new_box_point1_j = 5;
                new_box_point2_i =0,new_box_point2_j = 6;
                new_box_point3_i =1,new_box_point3_j = 6;
                new_box_point4_i =2,new_box_point4_j = 6;
                new_box_center_i =1,new_box_center_j = 6;

                min_left = 5;
                max_right = 6;

            } else if (random%4 == 2) {
                //0字形 box
                box_point1_i =0,box_point1_j = 5;
                box_point2_i =0,box_point2_j = 6;
                box_point3_i =1,box_point3_j = 5;
                box_point4_i =1,box_point4_j = 6;
                box_center_i =0,box_center_j = 0;

                new_box_point1_i =0,new_box_point1_j = 5;
                new_box_point2_i =0,new_box_point2_j = 6;
                new_box_point3_i =1,new_box_point3_j = 5;
                new_box_point4_i =1,new_box_point4_j = 6;
                new_box_center_i =0,new_box_center_j = 0;

                min_left = 5;
                max_right = 6;
            } else if (random%4 == 3) {
                //1字形 box
                box_point1_i =0,box_point1_j = 5;
                box_point2_i =1,box_point2_j = 5;
                box_point3_i =2,box_point3_j = 5;
                box_point4_i =3,box_point4_j = 5;
                box_center_i =1,box_center_j = 5;

                new_box_point1_i =0,new_box_point1_j = 5;
                new_box_point2_i =1,new_box_point2_j = 5;
                new_box_point3_i =2,new_box_point3_j = 5;
                new_box_point4_i =3,new_box_point4_j = 5;
                new_box_center_i =1,new_box_center_j = 5;

                min_left = 5;
                max_right = 5;
            } 

            


            els[box_point1_i][box_point1_j] = 1;
            els[box_point2_i][box_point2_j] = 1;
            els[box_point3_i][box_point3_j] = 1;
            els[box_point4_i][box_point4_j] = 1;

            //draw top new box
            check[box_point1_i][box_point1_j] = 1;
            check[box_point2_i][box_point2_j] = 1;
            check[box_point3_i][box_point3_j] = 1;
            check[box_point4_i][box_point4_j] = 1;

            

            int caclulateNew = 0;
            for (int i=0;i<29;i++) {
                for (int j=0;j<12;j++) {
                    caclulateNew += check[i][j];
                }
            }
            
            is_drow_bottom = false;
            speed = DEFAULT_SPEED;

        }
        if (count%speed == 0 && !is_drow_bottom) {
            new_box_point1_i = box_point1_i + 1;
            new_box_point2_i = box_point2_i + 1;
            new_box_point3_i = box_point3_i + 1;
            new_box_point4_i = box_point4_i + 1;

            new_box_center_i = box_center_i +1;
            

            bool success = drawNewOrNotOnFloor(true);
            continue;
        }
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                is_running = false;
            }
           
            switch (event.type) {
                case SDL_QUIT: // exit if the window is closed
                    is_running = false; // set done to true for exit
                    break; // end caseclearscreen(red, green, blue, s1x, s1y, s1w, s1h);
                    
                case SDL_KEYDOWN: // check for keypresses
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        is_running = false;
                    }
                    
                    if (event.key.keysym.sym == SDLK_UP) {
                        bool rotate = true;
                        new_box_point1_i = box_point1_j - box_center_j + box_center_i;
                        new_box_point1_j = box_center_i - box_point1_i + box_center_j;
                        if (new_box_point1_j<0 || new_box_point1_j>11) {
                            rotate = false;
                        }
                        new_box_point2_i = box_point2_j - box_center_j + box_center_i;
                        new_box_point2_j = box_center_i - box_point2_i + box_center_j;
                        if (new_box_point2_j<0 || new_box_point2_j>11) {
                            rotate = false;
                        }

                        new_box_point3_i = box_point3_j - box_center_j + box_center_i;
                        new_box_point3_j = box_center_i - box_point3_i + box_center_j;
                        if (new_box_point3_j<0 || new_box_point3_j>11) {
                            rotate = false;
                        }

                        new_box_point4_i = box_point4_j - box_center_j + box_center_i;
                        new_box_point4_j = box_center_i - box_point4_i + box_center_j;
                        if (new_box_point4_j<0 || new_box_point4_j>11) {
                            rotate = false;
                        }
                        
                        bool success = false;
                        if (rotate) {
                            success = drawNewOrNotOnFloor(false);
                        } else {
                            new_box_point1_i = box_point1_i;
                            new_box_point1_j = box_point1_j;
                            
                            new_box_point2_i = box_point2_i;
                            new_box_point2_j = box_point2_j;

                            new_box_point3_i = box_point3_i;
                            new_box_point3_j = box_point3_j;

                            new_box_point4_i = box_point4_i;
                            new_box_point4_j = box_point4_j;

                            new_box_center_i = box_center_i;
                            new_box_center_j = box_center_j;
                        }
                        
                        if (success) {
                            if (new_box_point2_j < new_box_point1_j) {
                                min_left = new_box_point2_j;
                                max_right = new_box_point1_j;
                            } else {
                                min_left = new_box_point1_j;
                                max_right = new_box_point2_j;
                            }
                            if (min_left > new_box_point3_j) {
                                min_left = new_box_point3_j;
                            }
                            if (max_right < new_box_point3_j) {
                                max_right = new_box_point3_j;
                            }

                            if (min_left > new_box_point4_j) {
                                min_left = new_box_point4_j;
                            }
                            if (max_right < new_box_point4_j) {
                                max_right = new_box_point4_j;
                            }
                        }
                        
                    }
                    
                    if (event.key.keysym.sym == SDLK_DOWN) {
                        speed = 5;
                    }
                    
                    if (event.key.keysym.sym == SDLK_LEFT) {
                        if (min_left - 1 < 0) {

                        } else {
                            new_box_point1_j = box_point1_j - 1;

                            new_box_point2_j = box_point2_j -1;

                            new_box_point3_j = box_point3_j-1;

                            new_box_point4_j = box_point4_j-1;

                            new_box_center_j = box_center_j-1;
                            bool success = drawNewOrNotOnFloor(false);
                            if (success) {
                                min_left = min_left -1 ;
                                max_right = max_right -1 ;
                            }
                        }
                        
                    }
                    
                    if (event.key.keysym.sym == SDLK_RIGHT) {
                        if (max_right + 1 > 11) {

                        } else {
                            new_box_point1_j = box_point1_j + 1;

                            new_box_point2_j = box_point2_j + 1;

                            new_box_point3_j = box_point3_j + 1;

                            new_box_point4_j = box_point4_j + 1;

                            new_box_center_j = box_center_j + 1;
                            bool success = drawNewOrNotOnFloor(false);
                            if (success) {
                                min_left = min_left +1;
                                max_right = max_right +1;
                            }
                        }
                        
                    }
                    
                    //if (event.key.keysym.sym == SDLK_s) {SDL_SaveBMP(screen, "screenshots/screenshot.bmp");}
                    
                    if (event.key.keysym.sym == SDLK_LSHIFT) {
                        
                    }
                    
                    break; // end case
                    
                case SDL_KEYUP:
                    if (event.key.keysym.sym == SDLK_LSHIFT) {
                        
                    }
                    
                    if (event.key.keysym.sym == SDLK_UP) {
                        speed = DEFAULT_SPEED;
                    }
                    
                    if (event.key.keysym.sym == SDLK_DOWN) {

                    }
                    
                    if (event.key.keysym.sym == SDLK_LEFT) {

                    }
                    
                    if (event.key.keysym.sym == SDLK_RIGHT) {

                    }
                    
                    break; // end case
            } /** END INPUT SETTINGS */
        }
        SDL_Delay(delay_millisecond);
    }


    // Close and destroy the window
    SDL_DestroyWindow(m_window);

    // Clean up
    SDL_Quit();

    return 0; // return success!
}

