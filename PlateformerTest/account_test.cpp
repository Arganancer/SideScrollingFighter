#include "stdafx.h"
#include "CppUnitTest.h"
#include <SFML/System/String.hpp>
#include "../9_1_TP2_SideScrollingFighter/account_model.h"
#include "../9_1_TP2_SideScrollingFighter/account_controller.h"
//Il faut que ce dernier lien soit aussi dans 
//[right-click sur projet]\éditeur de liens\propriétés\entrées\dépendances additionnelles
//sinon il y aura une erreur de linkage

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
//using namespace platformer;

namespace projet_sfml_test
{		
	TEST_CLASS(account_test)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			// Mise en place des données
			account_model::init();
			sf::String a;
			// Appel de la méthode à tester
			account_model::get_accounts();
			// Validation des résultats
			Assert::AreEqual(true, true);
			// Clean-up
		}
	};
}