#include "game.h"
#include "tile.h"
#include "input_manager.h"
#include "menu_controller.h"
#include "account_controller.h"
#include "account_model.h"
#include "score_model.h"
#include "text.h"
#include <complex>
#include "saw.h"
#include "shuriken.h"

game::game_state game::current_game_state_;
int game::score_;

game::game(): character_outofbounds_left_(false), character_outofbounds_right_(false),
              nb_of_frames_since_game_started_(0),
              game_state_is_defaulted_(true), view_x_pos_last_frame_(0)
{
	lives_remaining_ = max_lives_;
	load_new_level_ = false;
	current_scene_ = 0;
	scenes_[2] = "Levels\\scene_1.txt";
	scenes_[1] = "Levels\\scene_2.txt";
	scenes_[0] = "Levels\\scene_3.txt";
	current_game_state_ = main_menu;
	main_win_.create(VideoMode(view_width, view_height, 32), "Fighter", Style::Fullscreen);
	view_game_ = main_win_.getDefaultView();
	view_menu_ = main_win_.getDefaultView();
}

int game::run()
{
	if (!init())
	{
		return EXIT_FAILURE;
	}
	const double ms_per_update = 16.0f;
	auto clock = Clock();
	double previous = 0;
	double lag = 0.0f;
	while (main_win_.isOpen())
	{
		double current = clock.getElapsedTime().asMilliseconds();
		auto elapsed = current - previous;
		previous = current;
		lag += elapsed;

		get_inputs();

		while (lag >= ms_per_update)
		{
			if (main_win_.isOpen())
			{
				update();
				lag -= ms_per_update;
			}
		}
		draw();
	}

	return EXIT_SUCCESS;
}

bool game::init()
{
	if (!tile::load_textures("Sprites\\rock_tile.png"))
	{
		return false;
	}
	if (!shuriken_spawner::load_textures("Sprites\\shuriken.png"))
	{
		return false;
	}
	if (!player_character::load_textures("Sprites\\Swordsmen_no_helm.png", "Sprites\\blank.png"))
	{
		return false;
	}
	if (!skeleton::load_textures("Sprites\\skeleton.png", "Sprites\\blank.png"))
	{
		return false;
	}
	if (!saw::load_textures("Sprites\\spinning_saw.png"))
	{
		return false;
	}
	if (!shuriken::load_textures("Sprites\\shuriken.png"))
	{
		return false;
	}
	if (!spike_trap::load_textures("Sprites\\spike_trap.png"))
	{
		return false;
	}
	if (!text::init()) // Initialize font loading for interface tools.
	{
		return false;
	}
	if (!account_controller::init())
	{
		return false;
	}
	if (!account_model::init())
	{
		return false;
	}

	if (!score_model::init())
	{
		return false;
	}
	// Initialise Heros:
	default_respawn_point_ = Vector2f(grid_size, (scene::scene_height - 13)*grid_size);
	current_respawn_point_ = default_respawn_point_;
	for (size_t i = 0; i < 4; i++)
	{
		heros_.push_back(player_character(Vector2f(0, 0), i));
		heros_.back().setPosition(current_respawn_point_);
		heros_.back().visual_adjustments();
		heros_.back().set_texture();
		if (i > 0)
		{
			heros_.back().kill_movable();
			heros_.back().set_is_active(false);
		}
	}
	for (size_t i = 0; i<50; i++)
	{
		shurikens_[i].visual_adjustments();
		shurikens_[i].set_textures();
		shurikens_[i].set_position(Vector2f(0, 0));
	}

	//Initialize view
	view_current_center_ = Vector2f(scene::scene_width*grid_size / 2, scene::scene_height*grid_size / 2);
	view_game_.setCenter(view_current_center_);
	view_x_pos_last_frame_ = view_current_center_.x;
	view_menu_.setCenter(Vector2f(view_width / 2, view_height / 2));
	main_win_.setView(view_game_);

	scene_.load_scene(scenes_[current_scene_].c_str(), saws_, spike_traps_, skeletons_, tiles_, shuriken_spawner_);

	srand(time(nullptr));
	return true;
}

void game::get_inputs()
{
	//On passe l'événement en référence et celui-ci est chargé du dernier événement reçu!
	while (main_win_.pollEvent(event_))
	{
		input_manager::get_input_manager()->update(main_win_, event_);
		//x sur la fenêtre
		if (event_.type == Event::Closed || current_game_state_ == exiting)
		{
			main_win_.close();
		}
	}
}

void game::update()
{
	// Change game scene.
	if(load_new_level_)
	{
		tiles_.clear();
		skeletons_.clear();
		saws_.clear();
		spike_traps_.clear();
		scene_.load_scene(scenes_[current_scene_].c_str(), saws_, spike_traps_, skeletons_, tiles_, shuriken_spawner_);
		for (size_t i = 0; i < heros_.size(); i++)
		{
			heros_[i].setPosition(current_respawn_point_);
		}
		view_current_center_ = current_respawn_point_;
		load_new_level_ = false;
	}
	if (lives_remaining_ <= 0)
	{
		current_game_state_ = defeat_screen;
	}

	// Pause the game.
	if (current_game_state_ == singleplayer && input_manager::get_input_manager()->get_esc_key())
	{
		current_game_state_ = paused;
	}
	// Update singleplayer.
	if (current_game_state_ == singleplayer)
	{
		game_state_is_defaulted_ = false;
		++nb_of_frames_since_game_started_;
		// Release menu controller if it exists.
		menu_controller::get_menu_controller()->release();

		//update shurikens
		for (size_t i = 0; i<50; i++)
		{
			if (shurikens_[i].get_is_alive() == true)
			{
				movable_and_tile_collision_detection(&shurikens_[i]);
				movable_out_of_bounds(&shurikens_[i]);
				if (shurikens_[i].get_is_colliding_platform_under() == true ||
					shurikens_[i].get_is_colliding_platform_over() == true ||
					shurikens_[i].get_is_colliding_wall_left() == true ||
					shurikens_[i].get_is_colliding_wall_right() == true)
				{
					shurikens_[i].set_is_alive(false);
					shurikens_->set_is_colliding_platform_over(false);
					shurikens_->set_is_colliding_platform_under(false);
					shurikens_->set_is_colliding_wall_left(false);
					shurikens_->set_is_colliding_wall_right(false);
				}


				shurikens_[i].update();
			}
		}
		// Update all enemies.
		for (size_t i = 0; i < spike_traps_.size(); i++)
		{
			spike_traps_[i].update();
		}
		for (size_t i = 0; i < skeletons_.size(); i++)
		{
			skeletons_[i].update();
			movable_and_tile_collision_detection(&skeletons_[i]);
			for (size_t j = 0; j < heros_.size(); j++)
			{
				if (heros_[j].get_is_active() && heros_[j].get_is_alive())
				{
					skeletons_[i].check_hero_is_in_proximity(heros_[j].getPosition());
				}
				if (skeletons_[i].get_attack_intersects_movable(heros_[i]))
				{
					heros_[i].kill_movable();
					--lives_remaining_;
				}
			}
		}
		for (size_t i = 0; i < saws_.size(); i++)
		{
			saws_[i].update();
		}

		auto ammount_of_active_characters = 0;
		auto center_of_all_heros = Vector2f(0, 0);
		for (size_t i = 0; i < heros_.size(); i++) // Update heros.
		{
			if(heros_[i].get_shuriken_button_pressed() == true && shuriken_spawner_.get_player_id() == heros_[i].get_player_id())
			{
				for (size_t j = 0; j< 50; j++)
				{
					if (shurikens_[j].get_is_alive() == false)
					{
						const auto left_joystick_pos = input_manager::get_input_manager()->get_left_joystick_pos(heros_[i].get_player_id());
						shurikens_[j].shoot(heros_[i].getPosition(), heros_[i].get_player_id(), left_joystick_pos, heros_[i].get_character_facing_left());
						heros_[i].set_shuriken_button_pressed(false);
						break;
					}
				}
			}
			if (heros_[i].get_is_active() && !heros_[i].get_is_alive())
			{
				respawn(&heros_[i]);
			}
			if (heros_[i].get_is_active() && heros_[i].get_is_alive())
			{
				++ammount_of_active_characters;
				center_of_all_heros.x += heros_[i].getPosition().x;
				center_of_all_heros.y += heros_[i].getPosition().y;
				heros_[i].update(main_win_);
				movable_out_of_bounds(&heros_[i]);
				movable_and_tile_collision_detection(&heros_[i]);
				;				for (size_t j = 0; j < saws_.size(); j++)
					//checks if the characters collides with the saws.
					;				for (size_t j = 0; j < saws_.size(); j++)
				{
					if (saws_[j].contains(heros_[i].get_bottom_left_point()) || saws_[j].contains(heros_[i].get_bottom_right_point()) ||
						saws_[j].contains(heros_[i].get_left_lower_point()) || saws_[j].contains(heros_[i].get_left_upper_point()) ||
						saws_[j].contains(heros_[i].get_right_lower_point()) || saws_[j].contains(heros_[i].get_right_upper_point()) ||
						saws_[j].contains(heros_[i].get_top_left_point()) || saws_[j].contains(heros_[i].get_top_right_point()))
					{
						heros_[i].kill_movable();
						if (heros_[i].get_player_id() == shuriken_spawner_.get_player_id())
						{
							//Player looses the ability to shoot shurikens 
							shuriken_spawner_.set_is_alive(true);
							shuriken_spawner_.set_player_id(-1);
							heros_[i].set_has_shuriken(false);
						}

					}
				}
				//checks if the characters collides with the traps.
				for (size_t j = 0; j < spike_traps_.size(); j++)
				{

					if (spike_traps_[j].contains(heros_[i].get_bottom_left_point()) || spike_traps_[j].contains(heros_[i].get_bottom_right_point()) ||
						spike_traps_[j].contains(heros_[i].get_left_lower_point()) || spike_traps_[j].contains(heros_[i].get_left_upper_point()) ||
						spike_traps_[j].contains(heros_[i].get_right_lower_point()) || spike_traps_[j].contains(heros_[i].get_right_upper_point()) ||
						spike_traps_[j].contains(heros_[i].get_top_left_point()) || spike_traps_[j].contains(heros_[i].get_top_right_point()))
					{
						heros_[i].kill_movable();
						--lives_remaining_;
						if (heros_[i].get_player_id() == shuriken_spawner_.get_player_id())
						{
							//Player looses the ability to shoot shurikens 
							shuriken_spawner_.set_is_alive(true);
							shuriken_spawner_.set_player_id(-1);
							heros_[i].set_has_shuriken(false);
						}
					}
				}

				//checks if the characters collides with the shurikens.
				for (size_t j = 0; j < 50; j++)
				{
					if (heros_[i].get_player_id() != shurikens_[j].get_shuriken_player_id())
					{
						if (shurikens_[j].contains(heros_[i].get_bottom_left_point()) || shurikens_[j].contains(heros_[i].get_bottom_right_point()) ||
							shurikens_[j].contains(heros_[i].get_left_lower_point()) || shurikens_[j].contains(heros_[i].get_left_upper_point()) ||
							shurikens_[j].contains(heros_[i].get_right_lower_point()) || shurikens_[j].contains(heros_[i].get_right_upper_point()) ||
							shurikens_[j].contains(heros_[i].get_top_left_point()) || shurikens_[j].contains(heros_[i].get_top_right_point()))
						{
							heros_[i].kill_movable();
							--lives_remaining_;
							//Player looses the ability to shoot shurikens 
							if (heros_[i].get_player_id() == shuriken_spawner_.get_player_id())
							{
								shuriken_spawner_.set_is_alive(true);
								shuriken_spawner_.set_player_id(-1);
								heros_[i].set_has_shuriken(false);
							}
						}
					}
				}
				//checks if the characters collides with the shuriken_spawner (bonus).
				if (shuriken_spawner_.get_is_alive() == true)
				{
					if (shuriken_spawner_.contains(heros_[i].get_bottom_left_point()) || shuriken_spawner_.contains(heros_[i].get_bottom_right_point()) ||
						shuriken_spawner_.contains(heros_[i].get_left_lower_point()) || shuriken_spawner_.contains(heros_[i].get_left_upper_point()) ||
						shuriken_spawner_.contains(heros_[i].get_right_lower_point()) || shuriken_spawner_.contains(heros_[i].get_right_upper_point()) ||
						shuriken_spawner_.contains(heros_[i].get_top_left_point()) || shuriken_spawner_.contains(heros_[i].get_top_right_point()))
					{

						shuriken_spawner_.set_player_id(heros_[i].get_player_id());
						heros_[i].set_has_shuriken(true);
					}
				}
			}
		}
		center_of_all_heros.x /= ammount_of_active_characters;
		center_of_all_heros.y /= ammount_of_active_characters;

		// Update view.
		auto distance = sqrt(pow(view_current_center_.x - center_of_all_heros.x, 2) +
			pow(view_current_center_.y - center_of_all_heros.y, 2));
		if (distance > 3) {
			distance /= 25;
			const float pi = 3.14159265358979323846;
			const auto temp_angle = atan2(center_of_all_heros.y - view_current_center_.y, center_of_all_heros.x - view_current_center_.x) * 180 / pi;
			const auto direction = Vector2f(float(cos(pi * temp_angle / 180.0f)), float(sin(pi * temp_angle / 180.0f)));
			view_current_center_ = view_current_center_ + direction * float(distance);
		}

		// Locking the camera so it does not leave the world area.
		if (view_current_center_.x - view_width / 2 <= 0) {
			view_current_center_.x = view_width / 2;
		}
		if (view_current_center_.x + view_width / 2 >= scene::scene_width* grid_size) {
			view_current_center_.x = scene::scene_width* grid_size - view_width / 2;
		}
		if (view_current_center_.y - view_height / 2 <= 0) {
			view_current_center_.y = view_height / 2;
		}
		if (view_current_center_.y + view_height / 2 >= scene::scene_height * grid_size) {
			view_current_center_.y = scene::scene_height* grid_size - view_height / 2;
		}

		view_game_.setCenter(view_current_center_);
		main_win_.setView(view_game_);
	}
	// Update menu.
	else
	{
		if(current_game_state_ == main_menu && !game_state_is_defaulted_)
		{
			current_scene_ = 0;
			load_new_level_ = true;
			game_state_is_defaulted_ = true;
			lives_remaining_ = max_lives_;
			nb_of_frames_since_game_started_ = 0;
			current_respawn_point_ = default_respawn_point_;
		}
		main_win_.setView(view_menu_);
		current_game_state_ = menu_controller::get_menu_controller()->update();
	}
}

void game::movable_and_tile_collision_detection(movable * movable) const
{
	static const auto iterations = 5;
	auto collision_x = true;
	auto collision_y_bottom = true;
	auto collision_y_top = true;
	auto is_on_platform = false;
	auto kill_x_velocity = false;
	auto kill_y_velocity = false;
	movable->set_is_colliding_wall_left(false);
	movable->set_is_colliding_wall_right(false);

	auto movable_adjustment = Vector2f(0, 0);
	for (size_t i = 0; i < iterations && (collision_x || collision_y_bottom || collision_y_top); i++)
	{
		collision_x = collision_y_bottom = collision_y_top = false;
		for (size_t j = 0; j < tiles_.size(); j++)
		{
			// First check to see if it's possible that the shapes are colliding using X and Y axis projection.
			if (abs(movable->getPosition().x - tiles_[j].getPosition().x) * 2 <=
				tiles_[j].getGlobalBounds().width + movable->getGlobalBounds().width
				&&
				abs(movable->getPosition().y + 16 - tiles_[j].getPosition().y) * 2 <=
				tiles_[j].getGlobalBounds().height + movable->getGlobalBounds().height)
			{
				// Verification to see if the character is colliding with the platform horizontally.
				if (movable->get_velocity().x >= 0) // MOVING RIGHT
				{

					if (tiles_[j].contains(movable->get_right_upper_point() + Vector2f(1, 0)) ||
						tiles_[j].contains(movable->get_right_lower_point() + Vector2f(1, 0)))
					{
						movable->set_is_colliding_wall_right(true);
						movable->setPosition(tiles_[j].getPosition().x - movable->getGlobalBounds().width, movable->getPosition().y);
						collision_x = true;
						kill_x_velocity = true;
					}
				}
				else if (movable->get_velocity().x <= 0) // MOVING LEFT
				{
					if (tiles_[j].contains(movable->get_left_lower_point() + Vector2f(-1, 0)) ||
						tiles_[j].contains(movable->get_left_upper_point() + Vector2f(-1, 0)))
					{
						movable->set_is_colliding_wall_left(true);
						movable->setPosition(tiles_[j].getPosition().x + tiles_[j].getGlobalBounds().width, movable->getPosition().y);
						collision_x = true;
						kill_x_velocity = true;
					}
				}
				// Verification to see if the character is colliding with the platform vertically.
				if (movable->get_velocity().y >= 0) // FALLING
				{
					if (tiles_[j].contains(movable->get_bottom_left_point()) ||
						tiles_[j].contains(movable->get_bottom_right_point()))
					{
						is_on_platform = true;
						movable->set_is_colliding_platform_under(true);
						movable->setPosition(movable->getPosition().x, tiles_[j].getPosition().y - movable->getGlobalBounds().height);
						collision_y_top = true;
						kill_y_velocity = true;
					}
				}
				else if (movable->get_velocity().y <= 0) // RISING
				{
					if (tiles_[j].contains(movable->get_top_left_point()) ||
						tiles_[j].contains(movable->get_top_right_point()))
					{
						movable_adjustment.y++;
						movable->set_is_colliding_platform_over(true);
						collision_y_top = true;
						kill_y_velocity = true;
					}
				}
			}
		}
		movable->adjust_movable_position(movable_adjustment);
	}
	if (kill_x_velocity)
	{
		movable->kill_x_velocity();
	}
	if (kill_y_velocity)
	{
		movable->kill_y_velocity();
	}
	movable->set_is_on_platform(is_on_platform);
}


void game::movable_out_of_bounds(movable* movable)
{
	// Out of bounds to the right
	if (movable->getPosition().x + movable->getGlobalBounds().width > scene::scene_width * grid_size + 1)
	{
		character_outofbounds_right_ = true;
		if (load_scene())
		{
			movable->kill_movable();
		}
	}
	// Out of bounds to the left
	if (movable->getPosition().x < -1)
	{
		character_outofbounds_left_ = true;
		if (load_scene())
		{
			movable->kill_movable();
		}
	}
	// Out of bounds downwards
	if (movable->getPosition().y - movable->getGlobalBounds().height * 2 > scene::scene_height * grid_size + 1)
	{
		movable->kill_movable();
	}
	// Out of bounds upwards
	if (movable->getPosition().y < -movable->getGlobalBounds().height * 2)
	{
		movable->kill_movable();
	}
}

void game::respawn(player_character * respawning_hero) const
{
	respawning_hero->start_respawn_delay();
	respawning_hero->update_respawn_delay();
	if (respawning_hero->get_is_alive() && current_game_state_ == singleplayer)
	{
		respawning_hero->setPosition(current_respawn_point_);
	}
}

void game::draw()
{
	if (current_game_state_ != exiting)
	{
		main_win_.clear();
		//Toujours important d'effacer l'écran précédent
		if (current_game_state_ == singleplayer)
		{
			for (size_t i = 0; i < saws_.size(); i++)
			{
				main_win_.draw(saws_[i]);
			}
			for (size_t i = 0; i < spike_traps_.size(); i++)
			{
				main_win_.draw(spike_traps_[i]);
			}
			for (size_t i = 0; i < tiles_.size(); i++)
			{
				main_win_.draw(tiles_[i]);
			}
			for (size_t i = 0; i < skeletons_.size(); i++)
			{
				skeletons_[i].draw(main_win_);
			}
			for (size_t i = 0; i < heros_.size(); i++)
			{
				if (heros_[i].get_is_active() && heros_[i].get_is_alive())
				{
					heros_[i].draw(main_win_);
				}
			}
			for (size_t i = 0; i<50; i++)
			{
				if (shurikens_[i].get_is_alive() == true)
				{
					main_win_.draw(shurikens_[i]);
				}
			}
			if(shuriken_spawner_.get_is_alive()==true)
			{
				main_win_.draw(shuriken_spawner_);
			}
		}
		else
		{
			menu_controller::get_menu_controller()->draw(main_win_);
		}
		main_win_.display();
	}
}

game::game_state game::get_current_game_state()
{
	return current_game_state_;
}

bool game::load_scene()
{
	if (character_outofbounds_left_ || character_outofbounds_right_)
	{
		if (character_outofbounds_left_)
		{
			character_outofbounds_left_ = false;
			if (current_scene_ > 0)
			{
				load_new_level_ = true;
				--current_scene_;
				current_respawn_point_ = Vector2f(grid_size * scene::scene_width - grid_size * 2, (scene::scene_height - 13)*grid_size);
				return false;
			}
			return true;
		}
		if (character_outofbounds_right_)
		{
			character_outofbounds_right_ = false;
			if (current_scene_ < 2)
			{
				load_new_level_ = true;
				++current_scene_;
				current_respawn_point_ = Vector2f(grid_size, (scene::scene_height - 13)*grid_size);
				return false;
			}
			score_ = 10000 * lives_remaining_ - nb_of_frames_since_game_started_;
			current_game_state_ = victory_screen;
		}
	}
	return false;
}

int game::get_score()
{
	return score_;
}
