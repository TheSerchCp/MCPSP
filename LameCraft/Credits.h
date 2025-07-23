#ifndef CREDITS_H_
#define CREDITS_H_

#include <string>
#include <pspiofilemgr.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <vector>
#include <string>
class Credits
{
public:

	Credits();
	~Credits();
	
	static Credits m_Credits;
	static Credits* Instance();
	
	void Init();

	std::vector<std::string> CreditText;
	
	std::vector<std::string> CreditTitles;

};

#endif
