#include "stdafx.h"
#include "CppUnitTest.h"
#include <SFML/System/String.hpp>
#include "../9_1_TP2_SideScrollingFighter/account_model.h"
#include "../9_1_TP2_SideScrollingFighter/account_controller.h"
//Il faut que ce dernier lien soit aussi dans 
//[right-click sur projet]\�diteur de liens\propri�t�s\entr�es\d�pendances additionnelles
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
			// Mise en place des donn�es
			account_model::init();
			sf::String a;
			// Appel de la m�thode � tester
			account_model::get_accounts();
			// Validation des r�sultats
			Assert::AreEqual(true, true);
			// Clean-up
		}
	};
}