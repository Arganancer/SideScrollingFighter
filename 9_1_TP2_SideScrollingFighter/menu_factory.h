#ifndef MENU_FACTORY_H
#define MENU_FACTORY_H

class menu;

namespace menu_factory
{
	class menu_factory
	{
	public:
		enum type_menu
		{
			exit_e, // Not a menu (causes the game to close).
			play_singleplayer_e, // Not a menu
			play_coop_e, // Not a menu
			play_vs_e, // Not a menu
			main_menu_e,
			log_in_e,
			play_e,
			multiplayer_e,
			options_e,
			score_e,
			account_management_e,
			pause_menu_e,
			create_account_e,
			modify_account_e,
			delete_account_e,
			high_score_e,
			my_high_score_e,
			search_high_score_e,
			victory_screen_e,
			defeat_screen_e,
		};

		static menu* create_menu(type_menu type);
	};
}
#endif