#include "Profiler.h"

Profiler Profiler::theInstanceProfile;

Profiler& Profiler::getInstance()
{
	return theInstanceProfile;
};

#ifdef PROFILING_ON
#include <cassert>
#include <string>
#include <fstream>

static std::ofstream outStream;

void Profiler::initialize(const char* fileName)
{
	this->fileName=fileName;
	frameIndex=0;
	categoryIndex=0;
	numUsedCategories=0;
};

void Profiler::shutdown()
{
	writeData();
};

void Profiler::newFrame()
{
	if(frameIndex > 0)
	{
		assert(categoryIndex==numUsedCategories);
	}
	frameIndex++;
	categoryIndex=0;
};

void Profiler::addEntry(const char* category, float time)
{
	assert(categoryIndex < MAX_PROFILE_CATEGORIES);
	ProfileCategory& pc=categories[categoryIndex];

	if(frameIndex==0)
	{
		pc.name=category;
		numUsedCategories++;
	}
	else
	{
		assert(pc.name == category && category != NULL);
		assert(categoryIndex < numUsedCategories);
	}
	categoryIndex++;

	pc.sample[frameIndex%MAX_FRAME_SAMPLES]=time;
};

char Profiler::getDelimiter(unsigned int index) const
{
	return (((index+1) < numUsedCategories) ? ',' : '\n');
};

bool Profiler::wrapped() const
{
	return frameIndex>=MAX_FRAME_SAMPLES && frameIndex!=-1;
};

void Profiler::writeData() const
{
	outStream.open(fileName, std::ios::trunc);

	//Write category headers
	for(unsigned int i=0; i<numUsedCategories; i++)
	{
		outStream << categories[i].name;

		outStream << getDelimiter(i);
	}

	//Account for last frame if they added entries
	const int NUM_ACTUAL_FRAMES=(categoryIndex==numUsedCategories ? frameIndex+1 : frameIndex);

	unsigned int endIndex;
	unsigned int startIndex;

	if(wrapped())
	{
		endIndex=frameIndex%MAX_FRAME_SAMPLES;
		startIndex=(endIndex+1)%MAX_FRAME_SAMPLES;

		while(startIndex!=endIndex)
		{
			writeFrame(startIndex);
			startIndex=(startIndex+1)%MAX_FRAME_SAMPLES;
		}
		if(categoryIndex==numUsedCategories)
		{
			writeFrame(startIndex);
		}
	}
	else
	{
		startIndex=0;
		endIndex=NUM_ACTUAL_FRAMES;
		while(startIndex<endIndex)
		{
			writeFrame(startIndex++);

			startIndex++;
		}
	}

	outStream.close();
};

void Profiler::writeFrame(unsigned int frameNumber) const
{
	for(unsigned int cat=0;cat<numUsedCategories;cat++)
	{
		outStream << categories[cat].sample[frameNumber];
		outStream << getDelimiter(cat);
	}
};

#endif