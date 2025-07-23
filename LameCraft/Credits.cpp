#include "Credits.h"

Credits Credits::m_Credits;

Credits* Credits::Instance()
{
	return &m_Credits;
}

Credits::Credits()
{

}

Credits::~Credits()
{
	
}

void Credits::Init()
{
	if (CreditText.empty()) {
		//Programadores
		CreditText.push_back("RegenStudio");
		CreditText.push_back("AlexDev");
		CreditText.push_back("Johan and Mai");
		CreditText.push_back("Marcin Ploska - Drakon (Author)");
		CreditText.push_back("Kirill Skibin - Woolio (Previous modder)");
		CreditText.push_back("Fin");
		//Artistas
		CreditText.push_back("CYE");
		CreditText.push_back("JhonBob32");
		CreditText.push_back("Ferran");
		CreditText.push_back("Fin");
		//Traductores
		CreditText.push_back("SergioCorP");
		CreditText.push_back("Kartzynn (Portugues-Brasil)");
		CreditText.push_back("Sklad.akrgooda (Russian and Ukrainian)");
		CreditText.push_back("Parrotpp (Catalan-Catalunya)");
		CreditText.push_back("Fin");
		//BetaTesters
		CreditText.push_back("Ickkcknoc");
		CreditText.push_back("GatoNaranja");
		CreditText.push_back("Sklad.akrgooda");
		CreditText.push_back("GiovaneFGC");
		CreditText.push_back("Inedude");
		CreditText.push_back("Jam");
		CreditText.push_back("Mstr_matthew");
		CreditText.push_back("NuinSq");
		CreditText.push_back("Rgcorona");
		CreditText.push_back("PS3-Slim");
		CreditText.push_back("Kartzynn");
		CreditText.push_back("Koishi Komeiji");
		CreditText.push_back("Parrotpp");
		CreditText.push_back("Flame");
		CreditText.push_back("Fin");
		//Extras
		CreditText.push_back("Country: Ecuador");
		CreditText.push_back("Youtube: @RegenStudioTM");
		CreditText.push_back("Instagram: Wandemberg_armijos");
		CreditText.push_back("Discord: Discord.com/invite/7WBeZnp");
		CreditText.push_back("Donate: Paypal.me/mikegaming210");
		CreditText.push_back("Version: Minecraft PSP 4.4");
		CreditText.push_back("Type: RegenStudio Team Edition");
		CreditText.push_back("Stage: Under development");
		CreditText.push_back("Fin");
		//Poema
		CreditText.push_back("Twenty years from now you will be more");
		CreditText.push_back("disappointed by the things that you didn't ");
		CreditText.push_back("do than by the ones you did do.");
		CreditText.push_back("So throw off the bowlines. ");
		CreditText.push_back("Sail away from the safe harbor. ");
		CreditText.push_back("Catch the trade winds in your sails.");
		CreditText.push_back("Explore.");
		CreditText.push_back("Dream.");
		CreditText.push_back("Discover.");
		CreditText.push_back("- Unknown");
	}
	
	if (CreditTitles.empty()) {
		CreditTitles.push_back("Programmers");
		CreditTitles.push_back("Artists");
		CreditTitles.push_back("Translators");
		CreditTitles.push_back("Beta testers");
		CreditTitles.push_back("Extras");
	}
}