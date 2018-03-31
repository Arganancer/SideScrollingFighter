#pragma once
#include "movable.h"

class particle : public movable
{
public:

protected:
	int nb_frames_since_spawned_;
	int nb_max_frames_;
};
