#ifndef SHURIKEN_SPAWNER_H
#define SHURIKEN_SPAWNERH
#include <string>
#include "entity.h"

namespace sf {
	class RenderWindow;
}

class shuriken_spawner : public entity
{
public:	
	shuriken_spawner();

	/// <summary>
	/// Loads the textures.
	/// </summary>
	/// <param name="texture_path">The texture path.</param>
	/// <returns></returns>
	 static bool load_textures(const std::string texture_path);
	
	/// <summary>
	/// Determines whether [contains] [the specified point].
	/// </summary>
	/// <param name="point">The point.</param>
	/// <returns>
	///   <c>true</c> if [contains] [the specified point]; otherwise, <c>false</c>.
	/// </returns>
	 bool contains(Vector2f point);
	
	/// <summary>
	/// Visuals the adjustments.
	/// </summary>
	void visual_adjustments();
	
	/// <summary>
	/// Updates this instance.
	/// </summary>
	void update();
	


	//Accessors
	bool get_is_alive() const;
	 int get_player_id();
	 Vector2f get_position();

	//Mutators
	 void set_is_alive(bool is_alive);
	 void set_textures();
	 void set_position(Vector2f position);
	 void set_player_id(int player_id);

private:
	 static Texture texture_;
	 bool is_alive_;
	 int player_id_;
	 Vector2f center_of_spawner;
	 IntRect** int_rects_shuriken_spawner;


};

#endif