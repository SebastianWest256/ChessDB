#include "renderer.hpp"
#include "functions.hpp"
#include "text.hpp"
#include "structs.hpp"
#include <iostream>
#include <vector>
#include <cstdlib>  
#include <ctime>   
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <fstream>
const SDL_Color
bblack = { 100,50,100,255 },
bwhite = { 155,105,155,255 },
pblack = { 25,25,25,255 },
pwhite = { 230,230,230,255 };

int main(int argc, char* argv[]) {

    const int TARGET_FPS = 120;
    const int SCREEN_WIDTH = 750;
    const int SCREEN_HEIGHT = 750;

    const int TARGET_FRAME_TIME = 1000 / TARGET_FPS;

    int
        board_x = 50,
        board_y = 50,
        size = 80;
    

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    if (!initialize(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT)) {

        return 1;
    }

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    bool running = true;
    SDL_Event e;
    Uint32 currentFrameTime = SDL_GetTicks();
    Uint32 lastFrameTime = 0;
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    const Uint8* keystate = SDL_GetKeyboardState(NULL);
    int mouse_x, mouse_y;
    camera camera;
    int cam_speed = 5;
    int click_x = 0;
    int click_y = 0;
    bool mouse_last = false;
    bool valid = false;
    bool flip = false;
    bool freset = true;
    bool db_match = false;
    std::vector<std::vector<piece>> pieces(8, std::vector<piece>(8));
    piece current_piece;
    std::string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
    pieces = fenToBoard(fen);
    SDL_Color current;
    std::string filename;
    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;
            }
        }
        Uint32 mouseState = SDL_GetMouseState(&mouse_x, &mouse_y);
        lastFrameTime = currentFrameTime;
        currentFrameTime = SDL_GetTicks();
        Uint32 deltaTime = currentFrameTime - lastFrameTime;
        //std::cout << "FPS: " << 1000 / (deltaTime + 0.0001) << std::endl;
        Uint32 frameTime = SDL_GetTicks() - currentFrameTime;
        if (frameTime < TARGET_FRAME_TIME) {
            SDL_Delay(TARGET_FRAME_TIME - frameTime);
        }
        if (keystate[SDL_SCANCODE_F]) {
            if (freset) {
                flip = !flip;
                freset = false;
            }
        }
        else {
            freset = true;
        }
        drawScreen(renderer, { 0,0,0,255 });
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (i % 2 == j % 2) {
                    current = bwhite;
                }
                else {
                    current = bblack;
                }
                drawRectangle(renderer, board_x + size * j, board_y + size * i, size, size, current);
                 drawPiece(renderer, board_x + size * j, board_y + size * i, size, pieces[toFlip(j,flip)][toFlip(i,flip)].type, pieces[toFlip(j,flip)][toFlip(i,flip)].color);
                
            }
        }
        if (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)) {
            if (mouse_last) {
                if (valid) {
                    drawPiece(renderer, mouse_x - size / 2, mouse_y - size / 2, size, current_piece.type, current_piece.color);
                }
            }
            else {
                if (mouse_x > board_x && mouse_y > board_y && mouse_x < board_x + size * 8 && mouse_y < board_y + size * 8) {
                    current_piece = pieces[toFlip(int((mouse_x - board_x) / size),flip)][toFlip(int((mouse_y - board_y) / size),flip)];
                    pieces[toFlip(int((mouse_x - board_x) / size),flip)][toFlip(int((mouse_y - board_y) / size),flip)].type = 0;
                    valid = true;        
                }
            }
            mouse_last = true;
        }
        else {
            if (mouse_last == true && valid == true) {
                pieces[toFlip(int((mouse_x - board_x) / size),flip)][toFlip(int((mouse_y - board_y) / size),flip)] = current_piece;
                valid = false;
                std::cout << boardToFen(pieces) << "\n";
            }
            mouse_last = false;
        }
        db_match = false;
        if (flip) { filename = "black.txt"; }
        else {
            filename = "white.txt";
        }
        std::ifstream file(filename);
        if (!file) {
             std::cerr << "Unable to open the file.\n";
             return 1; 
        }
        std::string line;
        while (getline(file, line)) {
            if (db_match) { std::cout << line << "\n"; db_match = false; drawMove(renderer, line, board_x, board_y, size, flip); }
            if (line == boardToFen(pieces)) { db_match = true; } 
        }
        file.close(); 

        SDL_RenderPresent(renderer);
    }

    cleanup(window, renderer);
    return 0;
}
