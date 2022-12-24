#pragma once

#include "Misc.h"
#include "Utilities.h"

//std::string ZM_LIGHT[8] = { "cosspeed1_host", "cosspeed1_origin", "santaskinlight_host", "santaskinlight_origin, ZM_LIGHT5, ZM_LIGHT6, ZM_LIGHT7, ZM_LIGHT8 };

int StudioDrawPlayer(int flags, struct entity_state_s* pplayer);
int StudioDrawModel(int flags);
void StudioSetupLighting(struct alight_s* plighting);
void StudioEntityLight(struct alight_s* plight);