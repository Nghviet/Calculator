#include<bits/stdc++.h>
#include<SDL.h>
#include<SDL_image.h>
#include"Texture.h"
typedef std::pair<int, int> ii;
typedef std::vector<SDL_Rect> vSDLR;
SDL_Window* Window = NULL;
SDL_Renderer* Renderer = NULL;
SDL_Rect clip;
TTF_Font* font;
SDL_Event e;
int sWidth = 1213, sHeight = 534;
vSDLR temp;
bool eject = false;
std::vector< std::shared_ptr<Texture> > gTexture;
Texture UI, Ans;
std::string mapkey[9][5];


bool init()
{
	//Check init err
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << SDL_GetError() << std::endl;
		return false;
	}

	if (TTF_Init() < 0)
	{
		std::cout << TTF_GetError() << std::endl;
		return false;
	}

	//Window create
	Window = SDL_CreateWindow("SDL_Template", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, sWidth, sHeight, SDL_WINDOW_SHOWN);
	if (Window == NULL)
	{
		std::cout << "Window create err " << SDL_GetError() << std::endl;
		return false;
	}
	//Base render
	Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (Renderer == NULL)
	{
		std::cout << "Render create err " << SDL_GetError() << std::endl;
		return false;
	}
	SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 0);
	int img = IMG_INIT_PNG;
	if (!(IMG_Init(img)&img))
	{
		std::cout << "Img err" << SDL_GetError();
		return false;
	}

	return true;
}

bool load()
{
	//Load data from file
	std::ifstream in;
	in.open("loadImage", std::fstream::in);
	if (!in.good())
	{
		std::cout << "Load file err" << std::endl;
		return false;
	}

	int n;
	in >> n;
	for (int i = 0; i < n; i++)
	{
		// Order of render - name - path - number of frame(1 if static) - width(horizontal)(perframe) - height(vertical)(perframe)
		int no, f, w, h;
		std::string name, path;
		in >> no >> name >> path >> f >> w >> h;
		std::shared_ptr<Texture> tmp(new Texture);
		if (!tmp->load(path.c_str(), Renderer))
		{
			std::cout << SDL_GetError() << std::endl;
			return false;
		}
		std::cout << path << " loaded" << std::endl;
		gTexture.push_back(tmp);
	}
	in.close();

	font = TTF_OpenFont("times.ttf", 50);
	if (font == NULL)
	{
		std::cout << TTF_GetError() << std::endl;
		return false;
	}

	return true;
}

void close()
{
	for (int i = 0; i < gTexture.size(); i++) gTexture[i]->free();
	SDL_DestroyRenderer(Renderer);
	SDL_DestroyWindow(Window);
	Window = NULL;
	Renderer = NULL;
	IMG_Quit();
	SDL_Quit();
}

void gen()
{

	mapkey[0][0] = "sqr";   mapkey[1][0] = "pow";   mapkey[2][0] = "sin";   mapkey[3][0] = "cos";	mapkey[4][0] = "tan";	mapkey[5][0] = "CE";	mapkey[6][0] = "C";		mapkey[7][0] = "Del";	mapkey[8][0] = "/";
	mapkey[0][1] = "trit";  mapkey[1][1] = "root";  mapkey[2][1] = "asin";  mapkey[3][1] = "acos";	mapkey[4][1] = "atan";	mapkey[5][1] = "7";		mapkey[6][1] = "8";		mapkey[7][1] = "9";		mapkey[8][1] = "*";
	mapkey[0][2] = "sqrt";  mapkey[1][2] = "dep";   mapkey[2][2] = "log";   mapkey[3][2] = "exp";	mapkey[4][2] = "mod";	mapkey[5][2] = "4";		mapkey[6][2] = "5";		mapkey[7][2] = "6";		mapkey[8][2] = "-";
	mapkey[0][3] = "rev";   mapkey[1][3] = "ep";    mapkey[2][3] = "ln";	mapkey[3][3] = "dms";	mapkey[4][3] = "deg";	mapkey[5][3] = "1";		mapkey[6][3] = "2";		mapkey[7][3] = "3";		mapkey[8][3] = "+";
	mapkey[0][4] = "NULL";  mapkey[1][4] = "Pi";    mapkey[2][4] = "n!";	mapkey[3][4] = "(";		mapkey[4][4] = ")";		mapkey[5][4] = "+-";	mapkey[6][4] = "0";		mapkey[7][4] = ".";		mapkey[8][4] = "=";
}
long preans = 0;
std::string convert(long in)
{
	std::string ans;
	while (in != 0)
	{
		ans.push_back(in % 10 + '0');
		in /= 10;
	}
	if (ans.empty()) ans.push_back('0');
	reverse(ans.begin(), ans.end());
	return ans;
}


std::string rec;
bool quit = false;
long cal()
{
	int x = 0, y = 0;
	bool del = false;
	long ans = 0, cur = 0;
	bool add = true;
	bool min = false;
	bool mul = false;
	bool preadd = true;
	if (rec.empty()) rec.push_back('0');
	std::vector<long> container;
	int tmp;
	while (!quit)
	{
		if (eject)
		{
			if (mul) for (int i = 0; i < container.size(); i++) cur *= container[i];
			if (add) ans += cur;
			if (min) ans -= cur;
			return ans;
		}
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
				return 0;
			}
			if (e.type == SDL_MOUSEMOTION)
			{
				SDL_GetMouseState(&x, &y);
				del = false;
			}
			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				if (y >= 219 && x <= 887)
				{
					int ty = (y - 219) / 62;
					int tx = x / 98;
					std::cout << tx << " " << ty << " :" << mapkey[tx][ty] << std::endl;
					if (mapkey[tx][ty].size() == 1)
					{
						if (mapkey[tx][ty][0] >= '0'&&mapkey[tx][ty][0] <= '9')
						{
							rec.push_back(mapkey[tx][ty][0]);
							cur = cur * 10 + mapkey[tx][ty][0] - '0';
						}
						if (mapkey[tx][ty][0] == '+')
						{
							rec.push_back(mapkey[tx][ty][0]);
							if (mul)
							{
								for (int i = 0; i < container.size(); i++) cur = cur * container[i];
								container.clear();
							}
							if (add)
							{
								ans += cur;
								min = false;
								cur = 0;
							}
							if (min)
							{
								ans -= cur;
								add = true;
								min = false;
								cur = 0;
							}
						}
						if (mapkey[tx][ty][0] == '-')
						{
							rec.push_back(mapkey[tx][ty][0]);
							if (mul)
							{
								for (int i = 0; i < container.size(); i++) cur = cur * container[i];
								container.clear();
							}
							if (add)
							{
								ans += cur;
								add = false;
								min = true;
								cur = 0;
							}
							if (min)
							{
								ans -= cur;
								add = false;
								min = true;
								cur = 0;
							}
						}
						if (mapkey[tx][ty][0] == '*')
						{
							rec.push_back(mapkey[tx][ty][0]);
							mul = true;
							container.push_back(cur);
							cur = 0;
						}
						if (mapkey[tx][ty][0] == '/') rec.push_back(mapkey[tx][ty][0]);
						if (mapkey[tx][ty][0] == '(')
						{
							rec.push_back(mapkey[tx][ty][0]);
							cur = cal();
						}
						if (mapkey[tx][ty][0] == ')')
						{
							rec.push_back(mapkey[tx][ty][0]);
							if (mul) for (int i = 0; i < container.size(); i++) cur *= container[i];
							if (add) ans += cur;
							if (min) ans -= cur;
							return ans;
						}

						if (mapkey[tx][ty][0] == '=')
						{
							if (mul) for (int i = 0; i < container.size(); i++) cur *= container[i];
							if (add) ans += cur;
							if (min) ans -= cur;
							rec.clear();
							eject = true;
							return ans;
						}
					}

					if (mapkey[tx][ty] == "Del")
					{
						rec.pop_back();
						del = true;
					}
				}
			}
		}
		SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 0);
		SDL_RenderClear(Renderer);
		gTexture[0]->render(0, 0, NULL, 0, NULL, SDL_FLIP_NONE, Renderer);
		UI.loadText(rec, { 0,0,0, }, font, Renderer);
		Ans.loadText(convert(preans), { 0,0,0 }, font, Renderer);
		UI.render(10, 27, NULL, 0, NULL, SDL_FLIP_NONE, Renderer);
		Ans.render(10, 85, NULL, 0, NULL, SDL_FLIP_NONE, Renderer);
		SDL_RenderPresent(Renderer);
	}
}

int main(int argc, char * argv[])
{
	if (init()) std::cout << "Initialization completed" << std::endl;
	else
	{
		std::cout << "Initialization failed" << std::endl;
		return 0;
	}

	if (load()) std::cout << "Load completed" << std::endl;
	else
	{
		std::cout << "Load failed" << std::endl;
		return 0;
	}

	gen();
	while (!quit)
	{
		//std::cout << x << " " << y << std::endl;
		//Event handle
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT) quit = true;
		}
		//Keyboard data in
		const Uint8* state = SDL_GetKeyboardState(NULL);
		//Clear screen
		preans = cal();
		std::cout << preans << std::endl;
		eject = false;
		//Update

	}

	close();
	std::cout << rec << std::endl;
	std::cout << "Program terminated";
	return 0;
}