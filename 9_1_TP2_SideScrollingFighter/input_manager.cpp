#include "input_manager.h"
#include <SFML/Graphics.hpp>
#include <valarray>
#include "game.h"
#include <iostream>

input_manager * input_manager::input_manager_ = nullptr;

input_manager::input_manager() 
{
	clear();
	for (size_t i = 0; i < 4; i++)
	{
		if(Joystick::isConnected(i))
		{
			for (size_t j = 0; j < 4; j++)
			{
				if(player_controller_ids_[j] == -1)
				{
					player_controller_ids_[j] = i;
					break;
				}
			}
		}
	}
	player_controller_ids_[0] = 0;
	mouse_position_ = sf::Vector2i(0, 0);
}

void input_manager::update(sf::RenderWindow& main_win, sf::Event& event) 
{
	switch(event.type)
	{
	case Event::JoystickDisconnected:
		for (size_t i = 0; i < 4; i++)
		{
			if (player_controller_ids_[i] == event.joystickConnect.joystickId)
			{
				player_controller_ids_[i] = -1;
			}
		}
		break;
	case Event::JoystickConnected:
		for (size_t i = 0; i < 4; i++)
		{
			if (player_controller_ids_[i] == -1)
			{
				player_controller_ids_[i] = event.joystickConnect.joystickId;
				break;
			}
		}
		break;
	case Event::JoystickButtonPressed:
		for (size_t i = 0; i < 4; i++)
		{
			if(event.joystickButton.joystickId == i)
			{
				buttons_are_pressed_[i][event.joystickButton.button] = true;
				break;
			}
		}
		break;
	case Event::JoystickButtonReleased:
		for (size_t i = 0; i < 4; i++)
		{
			if (event.joystickButton.joystickId == i)
			{
				buttons_are_pressed_[i][event.joystickButton.button] = false;
				break;
			}
		}
		break;
	case Event::JoystickMoved:
		for (size_t i = 0; i < 4; i++)
		{
			if (event.joystickMove.joystickId == i)
			{
				switch(event.joystickMove.axis)
				{
				case Joystick::X:
					left_joystick_[i].x = event.joystickMove.position;
					break;
				case Joystick::Y:
					left_joystick_[i].y = event.joystickMove.position;
					break;
				case Joystick::Z:
					if (event.joystickMove.position < 0 && event.joystickMove.position > -101)
					{
						right_trigger_[i] = abs(event.joystickMove.position);
					}
					else if (event.joystickMove.position > 0)
					{
						left_trigger_[i] = event.joystickMove.position;
					}
					break;
				case Joystick::R:
					right_joystick_[i].y = event.joystickMove.position;
					break;
				case Joystick::U:
					right_joystick_[i].x = event.joystickMove.position;
					break;
				case Joystick::V:
					break;
				default: break;
				}
			}
		}
		break;
	case Event::TextEntered:
		if (game::get_current_game_state() == game::game_state::main_menu || game::get_current_game_state() == game::game_state::paused)
		{
			// Characters that can be typed in a textbox.
			if (event.text.unicode == 45 || event.text.unicode == 95 || /*Underscore and hyphen*/
				event.text.unicode >= 48 && event.text.unicode <= 57 || /*numerics*/
				event.text.unicode >= 65 && event.text.unicode <= 90 || /*Uppercase alpha*/
				event.text.unicode >= 97 && event.text.unicode <= 122) /*Lowercase alpha*/
			{
				text_entered_event_ = true;
				last_key_sequence_ += char(event.text.unicode);
			}
		}
		break;
	case Event::KeyPressed:
		switch(event.key.code)
		{
		case Keyboard::Key::Tab:
			tab_key_is_pressed_ = true;
			break;
		case Keyboard::Key::Escape:
			esc_key_is_pressed_ = true;
			break;
		case Keyboard::Key::BackSpace:
			backspace_key_is_pressed_ = true;
			break;
		case Keyboard::Key::Space:
			space_key_is_pressed_ = true;
			buttons_are_pressed_[0][0] = true;
			break;
		case Keyboard::Key::Return:
			enter_key_is_pressed_ = true;
			break;
		case Keyboard::Key::A:
			left_joystick_[0] = Vector2f(-100, 0);
			break;
		case Keyboard::Key::W:
			left_joystick_[0] = Vector2f(0, -100);
			break;
		case Keyboard::Key::S:
			left_joystick_[0] = Vector2f(0, 100);
			break;
		case Keyboard::Key::D:
			left_joystick_[0] = Vector2f(100, 0);
			break;
		default: 
			break;
		}
		break;
	case Event::KeyReleased:
		switch (event.key.code)
		{
		case Keyboard::Key::Tab:
			tab_key_is_pressed_ = false;
			break;
		case Keyboard::Key::Escape:
			esc_key_is_pressed_ = false;
			break;
		case Keyboard::Key::BackSpace:
			backspace_key_is_pressed_ = false;
			break;
		case Keyboard::Key::Space:
			space_key_is_pressed_ = false;
			buttons_are_pressed_[0][0] = false;
			break;
		case Keyboard::Key::Return:
			enter_key_is_pressed_ = false;
			break;
		case Keyboard::Key::A:
			left_joystick_[0] = Vector2f(0, 0);
			break;
		case Keyboard::Key::W:
			left_joystick_[0] = Vector2f(0, 0);
			break;
		case Keyboard::Key::S:
			left_joystick_[0] = Vector2f(0, 0);
			break;
		case Keyboard::Key::D:
			left_joystick_[0] = Vector2f(0, 0);
			break;
		default: 
			break;
		}
		break;
	case Event::MouseMoved:
		mouse_position_ = Vector2i(main_win.mapPixelToCoords(Vector2i(event.mouseMove.x, event.mouseMove.y)));
		break;
	case Event::MouseButtonPressed:
		if (event.mouseButton.button == Mouse::Left)
		{
			mouse_l_click_is_pressed_ = mouse_l_click_is_pressed_2_ = true;
		}
		break;
	case Event::MouseButtonReleased:
		if (event.mouseButton.button == Mouse::Left)
		{
			mouse_l_click_is_pressed_ = mouse_l_click_is_pressed_2_ = false;
		}
		break;
	default: 
		break;
	}
}

void input_manager::clear() {
	for (size_t i = 0; i < 4; i++)
	{
		left_joystick_[i] = Vector2f(0, 0);
		right_joystick_[i] = Vector2f(0, 0);

		for (size_t j = 0; j < 4; j++) {
			buttons_are_pressed_[i][j] = false;
		}
	}
	for (size_t i = 0; i < 4; i++)
	{
		directional_keys_[i] = false;
	}
	mouse_l_click_is_pressed_ = false;
	mouse_l_click_is_pressed_2_ = false;

	space_key_is_pressed_ = false;
	esc_key_is_pressed_ = false;
	enter_key_is_pressed_ = false;
	backspace_key_is_pressed_ = false;
	tab_key_is_pressed_ = false;
}

// Keyboard
bool input_manager::get_up() { return directional_keys_[up]; }
bool input_manager::get_down() { return directional_keys_[down]; }
bool input_manager::get_left() { return directional_keys_[left]; }
bool input_manager::get_right() { return directional_keys_[right]; }

bool input_manager::get_esc_key() const
{
	return esc_key_is_pressed_;
}

bool input_manager::get_space_key_is_pressed() const
{
	return space_key_is_pressed_;
}

bool input_manager::get_enter_key() const { return enter_key_is_pressed_; }
bool input_manager::get_backspace_key() const
{
	static bool backspace_key_still_held = false;
	if (backspace_key_is_pressed_ && !backspace_key_still_held)
	{
		backspace_key_still_held = true;
		return backspace_key_is_pressed_;
	}
	if (!backspace_key_is_pressed_ && backspace_key_still_held)
	{
		backspace_key_still_held = false;
	}
	return false;
}

// Textbox
sf::String input_manager::get_last_key_sequence()
{
	text_entered_event_ = false;
	sf::String temp = last_key_sequence_;
	last_key_sequence_ = "";
	return temp;
}
bool input_manager::get_text_entered_event() const
{
	return text_entered_event_;
}


bool input_manager::get_tab_is_pressed() const
{
	static bool tab_key_is_still_pressed = false;
	if (tab_key_is_pressed_ && !tab_key_is_still_pressed)
	{
		tab_key_is_still_pressed = true;
		return tab_key_is_pressed_;
	}
	if (!tab_key_is_pressed_ && tab_key_is_still_pressed)
	{
		tab_key_is_still_pressed = false;
	}
	return false;
}

// Mouse
sf::Vector2i input_manager::get_mouse_position() const { return mouse_position_; }
bool input_manager::get_mouse_l_click() const
{
	static bool mouse_l_still_held = false;
	if (mouse_l_click_is_pressed_ && !mouse_l_still_held)
	{
		mouse_l_still_held = true;
		return mouse_l_click_is_pressed_;
	}
	if (!mouse_l_click_is_pressed_ && mouse_l_still_held)
	{
		mouse_l_still_held = false;
	}
	return false;
}

bool input_manager::get_mouse_l_click_2() const
{
	static bool mouse_l_still_held = false;
	if (mouse_l_click_is_pressed_2_ && !mouse_l_still_held)
	{
		mouse_l_still_held = true;
		return mouse_l_click_is_pressed_2_;
	}
	if (!mouse_l_click_is_pressed_2_ && mouse_l_still_held)
	{
		mouse_l_still_held = false;
	}
	return false;
}

// Joystick
bool input_manager::get_button_is_pressed(int button, int player)
{
	return buttons_are_pressed_[player_controller_ids_[player]][button];
}

sf::Vector2f input_manager::get_left_joystick_pos(int player)
{
	if (left_joystick_[player_controller_ids_[player]].x <= 100 && left_joystick_[player_controller_ids_[player]].y <= 100 &&
		left_joystick_[player_controller_ids_[player]].x >= -100 && left_joystick_[player_controller_ids_[player]].y >= -100)
	{
		return left_joystick_[player_controller_ids_[player]];
	}
	return Vector2f(0, 0);
}

sf::Vector2f input_manager::get_right_joystick_pos(int player)
{
	if (right_joystick_[player_controller_ids_[player]].x <= 100 && right_joystick_[player_controller_ids_[player]].y <= 100 &&
		right_joystick_[player_controller_ids_[player]].x >= -100 && right_joystick_[player_controller_ids_[player]].y >= -100)
	{
		return right_joystick_[player_controller_ids_[player]];
	}
	return Vector2f(0, 0);
}

input_manager* input_manager::get_input_manager()
{
	if (!input_manager_)
		input_manager_ = new input_manager;
	return input_manager_;
}

void input_manager::release()
{
	delete input_manager_;
	input_manager_ = nullptr;
}

float input_manager::get_left_trigger_pos(int player)
{
	return left_trigger_[player_controller_ids_[player]];
}

float input_manager::get_right_trigger_pos(int player)
{
	return right_trigger_[player_controller_ids_[player]];
}
