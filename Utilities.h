#pragma once

#include "Misc.h"
#include <fstream>
#include <sstream>
#include <iostream>

#define VectorTransform(a,b,c){(c)[0]=DotProduct((a),(b)[0])+(b)[0][3];(c)[1]=DotProduct((a),(b)[1])+(b)[1][3];(c)[2]=DotProduct((a),(b)[2])+(b)[2][3];}
#define VectorSubtract(a,b,c) {(c)[0]=(a)[0]-(b)[0];(c)[1]=(a)[1]-(b)[1];(c)[2]=(a)[2]-(b)[2];}

struct Utilities
{
private:
	void CheckCFG();
public:
	void SaveCFG();
	void LoadCFG();
	int CalcBestHitbox(int target);
	bool IsValidEnt(cl_entity_s* ent);
	void CalcFOV(Vector origin, float FOV);
	bool InFOV(float* oldAngles, float* newAngles);
	void VectorAngles(const float* forward, float* angles);
	int ColorDarkening(int col, int x);
	bool Compare(char* str, std::string type[], int size);
	bool VisibleTrace(float* pflFrom, float* pflTo);
	void AdjustSpeed(double x);
};
extern Utilities Utility;