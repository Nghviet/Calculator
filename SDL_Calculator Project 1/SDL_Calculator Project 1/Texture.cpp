#include<iostream>
#include<string>
#include<fstream>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include"Texture.h"

Texture::Texture()
{
	mTexture = NULL;
	width = 0;
	height = 0;
}

Texture::~Texture()
{
	free();
}

void Texture::free()
{
	SDL_DestroyTexture(mTexture);
	mTexture = NULL;
	width = 0;
	height = 0;
}

bool Texture::load(std::string path, SDL_Renderer* Renderer)
{
	free();
	SDL_Texture* input;
	SDL_Surface* load = IMG_Load(path.c_str());
	if (load == NULL)
	{
		std::cout << IMG_GetError() << std::endl;
		return false;
	}

	SDL_SetColorKey(load, SDL_TRUE, SDL_MapRGB(load->format, 0, 0, 255));
	input = SDL_CreateTextureFromSurface(Renderer, load);
	if (input == NULL)
	{
		std::cout << SDL_GetError() << std::endl;
		return false;
	}

	width = load->w;
	height = load->h;
	mTexture = input;
	SDL_FreeSurface(load);
	return true;
}

bool Texture::loadText(std::string text, SDL_Color color,TTF_Font* font,SDL_Renderer* renderer)
{
	free();
	SDL_Surface* textSur = TTF_RenderText_Solid(font, text.c_str(), color);
	if (textSur == NULL)
	{
		std::cout << TTF_GetError() << std::endl;
		return false;
	}
	mTexture = SDL_CreateTextureFromSurface(renderer, textSur);
	if (mTexture == NULL)
	{
		std::cout << SDL_GetError() << std::endl;
		return false;
	}
	width = textSur->w;
	height = textSur->h;
	return true;
}

void Texture::setColor(Uint8 r, Uint8 g, Uint8 b)
{
	SDL_SetTextureColorMod(mTexture, r, g, b);
}

void Texture::setAlpha(Uint8 a)
{
	SDL_SetTextureAlphaMod(mTexture, a);
}

void Texture::Blend(SDL_BlendMode Blend)
{
	SDL_SetTextureBlendMode(mTexture, Blend);
}

void Texture::render(int x, int y, SDL_Rect* clip, double angle,SDL_Point* center, SDL_RendererFlip flip, SDL_Renderer* renderer)
{
	SDL_Rect render = { x,y,width,height };
	if (clip != NULL)
	{
		render.w = clip->w;
		render.h = clip->h;
	}
	SDL_RenderCopyEx(renderer, mTexture, clip, &render, angle, center, flip);
}

BoxCollider::BoxCollider()
{
	x = 0; y = 0; w = 0; h = 0;
}

BoxCollider::~BoxCollider()
{
	~x; ~y; ~w; ~h;
}

BoxCollider::BoxCollider(int _x, int _y, int _w, int _h)
{
	x = _x; y = _y; w = _w; h = _h;
}

void BoxCollider::render(Uint8 r, Uint8 g, Uint8 b, Uint8 a, SDL_Renderer* renderer)
{
	SDL_Rect temp = { x,y,w,h };
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	SDL_RenderFillRect(renderer, &temp);
}

CircleCollider::CircleCollider()
{
	x = 0; y = 0; r = 0;
}

CircleCollider::CircleCollider(int _x, int _y, int _r)
{
	x = _x; y = _y; r = _r;
}

CircleCollider::~CircleCollider()
{
	~x; ~y; ~r;
}

bool collide(BoxCollider x, BoxCollider y)
{
	if (x.x + x.w < y.x) return false;
	if (y.x + y.w < x.x) return false;
	if (x.y + x.h < y.y) return false;
	if (y.y + y.h < x.y) return false;
	return true;
}

bool collide(CircleCollider x, CircleCollider y)
{
	int X = x.x - y.x;
	int Y = x.y - y.y;
	int R = x.r + y.r;
	if (X * X + Y * Y <= R * R) return true;
	return false;
}