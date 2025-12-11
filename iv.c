#include <SDL2/SDL_events.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <wchar.h>

int main(){

    FILE *in = stdin;
    char *pthrowaway = calloc(1000, sizeof(char));
    //read first line (specifier p3 or p6)
    fgets(pthrowaway, 1000, in);
    //read second line (comment)
    fgets(pthrowaway, 1000, in);
    //read third line (dimention width / height)
    char *pdimension = calloc(1000, sizeof(char));
    fgets(pdimension, 1000, in);
    //read fourth line max color value
    fgets(pthrowaway, 1000,in);
    free(pthrowaway);
    
    int height = -1;
    int width = -1;
    sscanf(pdimension, "%d %d\n",&width,&height);
    free(pdimension);
    printf("width : %d, Height : %d\n", width, height);



    printf("Hello World");
    SDL_Window *pwindow = SDL_CreateWindow(" PPM Image Viewer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    SDL_Surface *psurface = SDL_GetWindowSurface(pwindow);
    


    SDL_Rect pixel = (SDL_Rect){0,0,1,1};
    Uint32 color = 0; 
    for (int y = 0; y< height; y++){
        for (int x = 0 ; x < width; x++) {              
            Uint8 r,g,b;
            r = (char) getchar();
            g = (char) getchar();
            b = (char) getchar();
            color = SDL_MapRGB(psurface->format, r,g,b);   
            pixel.x = x;
            pixel.y = y;      
            SDL_FillRect(psurface, &pixel, color);
        }
    }

    SDL_UpdateWindowSurface(pwindow);

    int app_running = 1;
    while (app_running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if(event.type == SDL_Quit){
                app_running = 0;
            }
        }
        SDL_Delay(100);
    }
    return 0;
}
