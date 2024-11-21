#include "esp.h"
#include "constants.h"
#include <stdio.h>
#include <iostream>
#include "geom.h"

const float FOV = 90;

void normalizeAngle(vec3& angle) {
	if (angle.x > 360)
		angle.x -= 360;
	if (angle.x < 0)
		angle.x += 360;
	if (angle.y > 90)
		angle.y -= 90;
	if (angle.y < -90)
		angle.y += 90;
}

bool isInFov(Player* owner, Vec3 looking) {
	vec3 angle = CalcAngle(owner->position, looking);
	vec3 playerAngle{ owner->yaw + 180,owner->pitch, 0 };
	normalizeAngle(playerAngle);

	vec3 angleDiff = playerAngle - angle;
	normalizeAngle(angleDiff);

	return (fabs(angleDiff.x) <= FOV / 2 && fabs(angleDiff.y) <= FOV / 2);
}

bool isValidTarget(Player* player) {
	if ((player->health > 100 || player->health <= 0 || !isInFov(localPlayerPtr, player->o)))
		return false;
	return true;
}


Player* ESP::getNearestPlayer() {
	Player * nearestPlayer = nullptr;
	float nearestDistance = 9999999.0f;
	for (int i = 1; i <= numPlayers; i++){
		Player* player = players->players[i];
		if (isValidTarget(player))
			continue;
		float distance = localPlayerPtr->position.Distance(player->position);
		if (distance < nearestDistance) {
			nearestDistance = distance;
			nearestPlayer = player;
		}
	}
	return nearestPlayer;
}

Player* ESP::getNearestEntityAngle() {
	vec3 playerAngle{ localPlayerPtr->yaw + 180,localPlayerPtr->pitch, 0 };
	normalizeAngle(playerAngle);
	Player* nearestPlayer = nullptr;
	float smallestAngle = 999999.0f;

	for (int i = 1; i < numPlayers + 1; i++){
		Player* player = players->players[i];
		if (!isValidTarget(player))
			continue;
		vec3 targetAngle = CalcAngle(localPlayerPtr->position, player->position);
		vec3 angleDiff = playerAngle - targetAngle;
		normalizeAngle(angleDiff);
		float angleMagnitue = angleDiff.Length();
		if (angleMagnitue < smallestAngle) {
			smallestAngle = angleMagnitue;
			nearestPlayer = player;
		}
	}
	return nearestPlayer;
}

void ESP::aimboit() {
	if (!GetAsyncKeyState(VK_SHIFT))
		return;
	Player* target = getNearestPlayer();
	if (!target)
		return;
	Vec3 angle = CalcAngle(localPlayerPtr->position, target->position);
	angle.x += 180;
	localPlayerPtr->yaw = angle.x;
	localPlayerPtr->pitch = angle.y;
}