/* Author: DJfromSpace (Dillon E Jones) */

#include <iostream>
#include <string>
#include "../../runtime/core/DreamApp.h"

int main()
{
	DreamApp app;
	if (!app.Init())
	{
		return -1;
	}

	app.TestFunc();

	return 0;
}
