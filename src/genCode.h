#pragma once
#include <cstdint>
#include "geom.h"

class Player
{
public:
	char pad_0000[4]; //0x0000
	Vector3 o; //0x0004
	Vector3 velocity; //0x0010
	Vector3 N00000053; //0x001C
	Vector3 position; //0x0028
	float yaw; //0x0034
	float pitch; //0x0038
	float roll; //0x003C
	int32_t health; //0x00EC
	char pad_00F0[244]; //0x00F0
	int32_t kills; //0x01E4
	char pad_01E8[292]; //0x01E8
	int32_t team; //0x030C
	char pad_0310[56]; //0x0310
	void* vtable;
}; //Size: 0x0348

class EntityList 
{
public:
	Player* players[64];
};