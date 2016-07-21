/*
 * ThreadLoop.cpp
 *
 *  Created on: Feb 11, 2015
 *      Author: dehann
 */

#include <MidWareTools/ThreadLoop.h>

//----------------------------------------------------------------------------
ThreadLoop::ThreadLoop()
{
	;
}

void ThreadLoop::start()
{
	if (this->Thread)
	{
		std::cout << "Error: Start() called while thread is active." << std::endl;
		return;
	}

	this->ShouldStop = false;
	this->Thread = boost::shared_ptr<boost::thread>(
			new boost::thread(boost::bind(&ThreadLoop::run, this)));
}

void ThreadLoop::stop()
{
	if (this->Thread)
	{
		this->ShouldStop = true;
		this->Thread->join();
		this->Thread.reset();
	}
}


