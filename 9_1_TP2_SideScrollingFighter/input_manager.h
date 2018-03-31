#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>

// This class is a modified version of the input manager class used in my TP1.

enum direction
{
	up,
	left,
	down,
	right,
};

/// <summary>
/// « input_manager » gère l’état du clavier, de la souris, et de la manette.
/// </summary>
class input_manager
{
#pragma region Constructor + Singleton methods
public:
	static input_manager *get_input_manager();
	static void release();
private:
	/// <summary>
	/// Initialise une nouvelle instance de la classe <see cref = "input_manager" />.
	/// </summary>
	input_manager();
	input_manager(const input_manager&); // Does not need to be defined, stops the singleton from being able to be copied.
	void operator=(const input_manager&); // Does not need to be defined, stops the singleton from being able to be copied.

	static input_manager *input_manager_;

#pragma endregion 
public:
	/// <summary>
	/// Efface toutes les valeurs stockées de l'état du matériel à partir de la dernière image(frame).
	/// </summary>
	void clear();

	/// <summary>
	/// Mets à jour toutes les valeurs de l'état du matériel de cette image(frame).
	/// </summary>
	/// <param name="main_win">L'écran principal.</param>
	void update(sf::RenderWindow& main_win, sf::Event& event);

#pragma region Keyboard
	// Menu Keys	
	/// <summary>
	/// Retourne l’état de la is_selected « Esc ».
	/// </summary>
	/// <returns>Retourne « vrai » si la is_selected « Esc » est enfoncée, retourne « faux » sinon.</returns>
	bool get_esc_key() const;

	/// <summary>
	/// Retourne l’état de la is_selected « Enter ».
	/// </summary>
	/// <returns>Retourne « vrai » si la is_selected « Enter » est enfoncée, retourne « faux » sinon.</returns>
	bool get_enter_key() const;

	/// <summary>
	/// Retourne l’état de la is_selected « Backspace ».
	/// </summary>
	/// <returns>Retourne « vrai » si la is_selected « Backspace » est enfoncée, retourne « faux » sinon.</returns>
	bool get_backspace_key() const;

	// Keyboard direction Accessors (both arrays and wasd).	
	/// <summary>
	/// Retourne l’état de la is_selected « W » ou de la is_selected « Up ».
	/// </summary>
	/// <returns>Retourne « vrai » si la is_selected « W » ou si la is_selected « Up » est enfoncée, retourne « faux » sinon.</returns>
	bool get_up();

	/// <summary>
	/// Retourne l’état de la is_selected « S » ou de la is_selected « Down »..
	/// </summary>
	/// <returns>Retourne « vrai » si la is_selected « S » ou si la is_selected « Down ». est enfoncée, retourne « faux » sinon.</returns>
	bool get_down();

	/// <summary>
	/// Retourne l’état de la is_selected « A » ou de la is_selected « Left »..
	/// </summary>
	/// <returns>Retourne « vrai » si la is_selected « A » ou si la is_selected « Left » est enfoncée, retourne « faux » sinon.</returns>
	bool get_left();

	/// <summary>
	/// Retourne l’état de la is_selected « D » ou de la is_selected « Right »..
	/// </summary>
	/// <returns>Retourne « vrai » si la is_selected « D » ou si la is_selected « Right » est enfoncée, retourne « faux » sinon.</returns>
	bool get_right();

	bool get_space_key_is_pressed() const;

	sf::String get_last_key_sequence();
	bool get_text_entered_event() const;
	bool get_tab_is_pressed() const;

private:
	bool directional_keys_[4];
	bool space_key_is_pressed_;

	// Textbox variables
	sf::String last_key_sequence_;
	char text_entered_event_;

	// Menu keys
	bool esc_key_is_pressed_;
	bool enter_key_is_pressed_;
	bool backspace_key_is_pressed_;
	bool tab_key_is_pressed_;
#pragma endregion 

#pragma region Mouse
public:
	/// <summary>
	/// Retourne la position en X de la souris.
	/// </summary>
	/// <returns>La position en X de la souris.</returns>
	sf::Vector2i get_mouse_position() const;

	/// <summary>
	/// Retourne l'état du clic gauche de la souris.
	/// </summary>
	/// <returns>Retourne « vrai » si le clic gauche de la souris est enfoncé, retourne « faux » sinon.</returns>
	bool get_mouse_l_click() const;

	bool get_mouse_l_click_2() const;

private:
	sf::Vector2i mouse_position_;
	bool mouse_l_click_is_pressed_;
	bool mouse_l_click_is_pressed_2_;
#pragma endregion 

#pragma region Joystick
public:
	/// <summary>
	/// Gets the buttons.
	/// </summary>
	/// <param name="button">The button.</param>
	/// <returns></returns>
	bool get_button_is_pressed(int button, int player);

	sf::Vector2f get_left_joystick_pos(int player);
	sf::Vector2f get_right_joystick_pos(int player);
	float get_left_trigger_pos(int player);
	float get_right_trigger_pos(int player);

private:
	int player_controller_ids_[4]{-1, -1, -1, -1 };
	bool buttons_are_pressed_[4][32];
	sf::Vector2f left_joystick_[4];
	sf::Vector2f right_joystick_[4];
	float left_trigger_[4];
	float right_trigger_[4];
#pragma endregion 
};

#endif
