#ifndef DEBUG_PROFILER_H
#define DEBUG_PROFILER_H

class __declspec(dllexport) Profiler
{
	static const unsigned int MAX_FRAME_SAMPLES=1000;
#if PROFILING_ON
	const char* fileName;
	static const unsigned int MAX_PROFILE_CATEGORIES=20;
	int frameIndex;
	unsigned int categoryIndex;
	unsigned int numUsedCategories;
#endif
	Profiler() {}
	Profiler(const Profiler&);

#if PROFILING_ON
	struct ProfileCategory
	{
		const char* name;
		float sample[MAX_FRAME_SAMPLES];
	} categories[MAX_PROFILE_CATEGORIES];

	char getDelimiter(unsigned int index) const;
	bool wrapped() const;
	void writeFrame(unsigned int frameNumber) const;
	void writeData() const;
#endif

public:
	static Profiler theInstanceProfile;
	Profiler& operator=(const Profiler&);
	static Profiler& getInstance();
#if PROFILING_ON
	void initialize(const char* fileName);
	void shutdown();
	void newFrame();
	void addEntry(const char* category, float time);
#else
	void initialize(const char* fileName) {};
	void shutdown() {};
	void newFrame() {};
	void addEntry(const char* category, float time){};
#endif
};

#define gameProfiler Profiler::getInstance();

#endif