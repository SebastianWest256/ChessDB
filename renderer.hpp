#ifndef RENDERER_HPP
#define RENDERER_HPP
#include <SDL.h>
#include <string>
bool initialize(SDL_Window*& window, SDL_Renderer*& renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT);
void cleanup(SDL_Window* window, SDL_Renderer* renderer);
void drawScreen(SDL_Renderer* renderer, SDL_Color color);
void drawPoint(SDL_Renderer* renderer, int x, int y, SDL_Color color);
void drawLine(SDL_Renderer* renderer, int x1, int y1, int x2, int y2, SDL_Color color);
void drawRectangle(SDL_Renderer* renderer, int x, int y, int width, int height, SDL_Color color);
void drawRectangleOutline(SDL_Renderer* renderer, float x, float y, float width, float height, SDL_Color color);
void drawCircle(SDL_Renderer* renderer, int x_center, int y_center, int radius, SDL_Color color);
void drawCircleOutline(SDL_Renderer* renderer, int centerX, int centerY, int radius, SDL_Color color);
void drawRotatedRectangle(SDL_Renderer* renderer, int x_center, int y_center, int width, int height, float angleInDegrees, SDL_Color color);
void drawRotatedRectangleOutline(SDL_Renderer* renderer, int x_center, int y_center, int width, int height, float angleInDegrees, SDL_Color color);
void drawTriangle(SDL_Renderer* renderer, int x1, int y1, int x2, int y2, int x3, int y3, SDL_Color color);
void drawTriangleOutline(SDL_Renderer* renderer, int x1, int y1, int x2, int y2, int x3, int y3, SDL_Color color);
void drawEllipse(SDL_Renderer* renderer, int x_center, int y_center, int a, int b, SDL_Color color);
void drawEllipseOutline(SDL_Renderer* renderer, int x_center, int y_center, int a, int b, SDL_Color color);
void drawThickLine(SDL_Renderer* renderer, int x1, int y1, int x2, int y2, int thickness, SDL_Color color);
void drawPiece(SDL_Renderer* renderer, int x, int y, float size, int piece, SDL_Color color);
void drawMove(SDL_Renderer* renderer, const std::string& move, int board_x, int board_y, int size, bool flip);
#endif