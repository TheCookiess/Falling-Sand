#pragma once
#include "pch.h"
#include "cell.h"
#include "interfaceData.h"

class Game {
public:
	Game();
	~Game();

	void init(u16 newTextureWidth, u16 newTextureHeight, u8 newScaleFactor);
	void reload(u16 newTextureWidth, u16 newTextureHeight, u8 newScaleFactor);
	void loadImage(std::vector<u8> imageTextureData, u16 imageWidth, u16 imageHeight);
	void updateSim(interfaceData& iData);
	void mouseDraw(u16 x, u16 y, u16 size, u8 drawChance, u8 material, u8 shape);
	void createDrawIndicators(u16 x, u16 y, u16 size, u8 shape);
	void updateTextureData(std::vector<u8>& textureData);
	void reset();

private:
	void topDown_Update();
	void l_bottomUp_Update();
	void r_bottomUp_Update();
	void snake_Update();
	void gol_Update();

	// passing around more data than last time lol, u32 ptr && more.
	void changeMaterial(u16 x, u16 y, u8 newMaterial);
	void swapCells(u16 x1, u16 y1, u16 x2, u16 y2);
	bool trySwap(u16 x1, u16 y1, u16 x2, u16 y2);
	bool querySwap(u16 x1, u16 y1, u16 x2, u16 y2);

	void updateCell(Cell& c, u16 x, u16 y);
	void updateSand(u16 x, u16 y);
	void updateWater(u16 x, u16 y);
	void updateEntireTextureData(std::vector<u8>& textureData);

	// make these generics. void foo(u16, u16, u8)
	void drawCircle(u16 x, u16 y, u16 size, u8 material, u8 drawChance, std::function<void(u16, u16, u8)> foo);
	void drawCircleOutline(u16 x, u16 y, u16 size, u8 material, u8 drawChance, std::function<void(u16, u16, u8)> foo);
	void drawLine(u16 x, u16 y, u16 size, u8 material, u8 drawChance, std::function<void(u16, u16, u8)> foo);
	void drawSquare(u16 x, u16 y, u16 size, u8 material, u8 drawChance, std::function<void(u16, u16, u8)> foo);
	void drawSquareOutline(u16 x, u16 y, u16 size, u8 material, u8 drawChance, std::function<void(u16, u16, u8)> foo);

	inline u32 cellIdx(u16 x, u16 y) { return (y * cellWidth) + x; }	
	inline u32 textureIdx(u16 x, u16 y) { return 4 * ((y * textureWidth) + x); }
	inline bool outOfBounds(u16 x, u16 y) 
	{ return x >= cellWidth || y >= cellHeight || x < 0 || y < 0; }

	inline u64 splitMix64_NextRand() 
	{
		u64 z = (seed += UINT64_C(0x9E3779B97F4A7C15));
		z = (z ^ (z >> 30)) * UINT64_C(0xBF58476D1CE4E5B9);
		z = (z ^ (z >> 27)) * UINT64_C(0x94D049BB133111EB);
		return z ^ (z >> 31);
	}

	template<typename T> // cheeky template
	inline T getRand(T min = -1, T max = 1) 
	{ return splitMix64_NextRand() % (max - min + 1) + min; }

	/*----------------------------------------------------------------
	---- Variables ---------------------------------------------------
	----------------------------------------------------------------*/
	
	bool sizeChanged = false;

	u8 fluidDispersionFactor;
	u8 solidDispersionFactor;
	u8 nVariants;
	u8 scaleFactor;
	u16 textureWidth, textureHeight;
    u16 cellWidth, cellHeight;
	u64 seed = 1234567890987654321;
	
	std::vector<Cell> cells;
	std::vector<std::pair<u16, u16>> textureChanges;
	std::vector<std::pair<u16, u16>> drawIndicators;
	std::vector<Material> materials;
};
