#pragma once

#define _USE_MATH_DEFINES

enum class Languages
{
	KOR,
	ENG,
	JP,
	COUNT,
};

enum class Menu
{
	Skill = 0,
	Bag,
	Pokemon,
	Run,
};

enum class SkillNum
{
	Skill1 = 0,
	Skill2,
	Skill3,
	Skill4,
};

enum class Origins
{
	TL,
	TC,
	TR,
	ML,
	MC,
	MR,
	BL,
	BC,
	BR,
	CUSTOM,
};

enum class ResourceTypes
{
	Texture,
	Font,
	SoundBuffer,
	AnimationClip,//파일하나당 애니메이션 클립 하나.
};

enum class Dir
{
	Down= 0,
	Left,
	Up,
	Right,
	
};

enum class SceneId
{
	None = -1,
	Title,
	Game,
	Battle,
	MyPokemon,
	Count,
};

enum class TileInformation
{
	WaterStone4 = 0,
	WaterStone3 ,
	FlowerBed1 ,
	FlowerBed2,
	FlowerBedColoum1,
	FlowerBedColoum2,
	FlowerBedRow,
	FlowerBedRowUnder,
	Tree1,
	Tree2,
	Tree3,
	Tree4,
	Grass,
	GrassFlower4,
	GrassFlower1,
	GrassFlower3,
	GrassFlower2,
	StoneWater1,
	StoneWater2,
	WaterStoneHalf24,
	WaterStoneHalf34,
	WaterStone2,
	WaterStone1,
	FlowerBed3,
	FlowerBed4,
	FlowerBedColoum3,
	FlowerBedColoum4,
	GrassFlowerHalf,
	GrassHigh,
	GrassLow,
	Floor,
	Information,
	Carpet,
	Water,
	StoneFloor1,
	StoneFloor2,
	StoneFloor3,
	StoneFloor4,
	StoneWater3,
	StoneWater4,
	WaterStoneHalf12,
	WaterStoneHalf13,

	/*tile = 12,28,29,30,32,*/
};

#include "AnimationClip.h"