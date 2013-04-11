//
//  Timer.cpp
//  gavqt
//
//  Created by Brian Ondov on 1/11/13.
//
//

#include "Timer.h"

void Timer::initialize(unsigned int newDuration)
{
	duration = newDuration;
	timeStart = QDateTime::currentDateTime();
}

bool Timer::update()
{
	QDateTime timeCurrent = QDateTime::currentDateTime();

	float progressLast = progress;

	if ( timeStart.msecsTo(timeCurrent) <= duration )
	{
		progress =
		(1 / (1 + exp(-curvature * ((float)timeStart.msecsTo(timeCurrent) / duration - .5))) - .5) /
		(curveMax - .5) / 2 + .5;
	}
	else
	{
		progress = 1;
	}
	
	return progress != progressLast;
}
