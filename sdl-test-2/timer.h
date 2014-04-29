#ifndef TIMER_H
#define TIMER_H

class Timer
{
public:
	Timer();

	void Start();

	void Stop();

	void Pause();

	void Unpause();

	int Restart();

	int Ticks() const;

	bool Started() const;

	bool Paused() const;

private:
	int mStartTicks, mPausedTicks;
	bool mStarted, mPaused;
};

#endif