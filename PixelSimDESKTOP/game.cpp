#pragma once

#include "game.h"

Game::Game() {}
Game::~Game() {}

void Game::init(std::vector<GLubyte> pixelData, int textureW, int textureH)
{
	textureData = pixelData;
	texW = textureW;
	texH = textureH;

	Types[0] = AIR	 = PixelType(0, 188, 231, 255, 255, 0	);
	//Types[0] = AIR	 = PixelType(0, 255, 255, 255, 255, 0	);
	Types[1] = SAND	 = PixelType(1, 245, 215, 176, 255, 1600);
	Types[2] = WATER = PixelType(2, 20 , 20 , 255, 100, 997	);
	Types[3] = ROCK  = PixelType(3, 200, 200, 200, 255, 2000);

	// init all pixels as air.
	for (int y = 0; y < texH; ++y)
		for (int x = 0; x < texW; ++x)
			createPixel(25, false, texIdx(x, y), x, y, AIR);

	for (Pixel& p : pixels) {
		updatePixel(p.x, p.y, p.type.r, p.type.g, p.type.b, p.type.a);
		p.flag = false;
	}
}

void Game::updatePixel(int x, int y, int r, int g, int b, int a)
{
	int idx = texIdx(x, y);
	if (texIdx(texW - 1, texH - 1) > idx) {
		textureData[idx + 0] = r;
		textureData[idx + 1] = g;
		textureData[idx + 2] = b;
		textureData[idx + 3] = a;
	}
}

void Game::createPixel(int range, bool flag, int texIdx, int x, int y, PixelType type)
{
	PixelType material = type;
	material.r = material.r - rand() % range;
	material.g = material.g - rand() % range;
	material.b = material.b - rand() % range;
	material.a = material.a - rand() % range;
	pixels.push_back(Pixel(flag, texIdx, x, y, material));
}