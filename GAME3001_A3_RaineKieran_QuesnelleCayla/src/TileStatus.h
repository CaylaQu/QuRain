#pragma once
#ifndef __TILE_STATUS__
#define __TILE_STATUS__

enum class TileStatus
{
	NONE = -1,
	UNVISITED,
	OPEN,
	CLOSED,
	GOAL,
	START
};

#endif /* defined (__TILE_STATUS__) */