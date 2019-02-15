#pragma once
#ifndef TEXTURE_H_
#define TEXTURE_H_

#include<SDL.h>
#include<SDL_ttf.h>
#include<string>
struct Texture
{
	SDL_Texture* mTexture;
	int width, height;

	Texture();

	~Texture();

	void free();

	bool load(std::string path, SDL_Renderer* Renderer);

	bool loadText(std::string text, SDL_Color color, TTF_Font* font, SDL_Renderer* renderer);

	void setColor(Uint8 r, Uint8 g, Uint8 b);

	void setAlpha(Uint8 a);

	void Blend(SDL_BlendMode Blend);

	void render(int x, int y, SDL_Rect*clip, double angle, SDL_Point* center, SDL_RendererFlip flip, SDL_Renderer* renderer);
};

struct BoxCollider
{
	int x, y;
	int w, h;

	BoxCollider();

	BoxCollider(int _x, int _y, int _w, int _h);

	~BoxCollider();

	void render(Uint8 r, Uint8 g, Uint8 b, Uint8 a,SDL_Renderer* renderer);
};

struct CircleCollider
{
	int x, y;
	int r;

	CircleCollider();

	CircleCollider(int _x, int _y, int _r);

	~CircleCollider();

};

bool collide(BoxCollider x, BoxCollider y);

bool collide(BoxCollider x, CircleCollider y);

bool collide(CircleCollider x, CircleCollider y);

#endif 