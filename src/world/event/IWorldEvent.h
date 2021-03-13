#pragma once

class World;

struct IWorldEvent
{
	virtual void handleWorld(World& world) = 0;
};