#include "npc.h"

class spike_trap: public npc
{
public:
	spike_trap(Vector2f position);
	static bool load_textures(const std::string texture_path);
	void set_textures(int *map, int scene_width, int scene_height, int top, int bottom, int left, int right);
	void update();
	void visual_adjustments();
	bool contains(Vector2f point);
private:
	static Texture texture_;
	bool is_triggered_;
	Vector2f position_;
	FloatRect inactive_hitbox_;
	int delay_counter_;
	int delay_;
	int current_anim_;
};
