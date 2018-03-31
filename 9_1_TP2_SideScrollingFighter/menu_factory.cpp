#include "menu_factory.h"
#include "play.h"
#include "multiplayer.h"
#include "log_in.h"
#include "main_menu.h"
#include "options.h"
#include "score.h"
#include "account_management.h"
#include "pause_menu.h"
#include "create_account.h"
#include "modify_account.h"
#include "delete_account.h"
#include  "high_score.h"
#include "my_high_score.h"
#include "search_high_score.h"
#include "defeat_screen.h"
#include "victory_screen.h"

menu* menu_factory::menu_factory::create_menu(type_menu type)
{
	switch (type)
	{
	case main_menu_e: return new main_menu();
	case log_in_e: return new log_in();
	case play_e: return new play();
	case multiplayer_e: return new multiplayer();
	case options_e: return new options();
	case score_e: return new score();
	case account_management_e: return new account_management();
	case pause_menu_e: return new pause_menu();
	case create_account_e: return new create_account();
	case modify_account_e: return new modify_account();
	case delete_account_e: return new delete_account();
	case high_score_e: return new high_score();
	case my_high_score_e: return new my_high_score();
	case search_high_score_e: return new search_high_score();
	case defeat_screen_e: return new defeat_screen();
	case victory_screen_e: return new victory_screen();
	default: ;
	}
	return nullptr;
}
