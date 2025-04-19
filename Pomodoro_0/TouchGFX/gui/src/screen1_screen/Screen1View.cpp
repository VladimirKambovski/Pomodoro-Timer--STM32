#include <gui/screen1_screen/Screen1View.hpp>
#include <stdint.h>
#include <main.h>


Screen1View::Screen1View() : minute(0), session(0)
{

}

void Screen1View::setupScreen()
{
    Screen1ViewBase::setupScreen();
    minute = presenter->getMinute();
    session = presenter->getSession();

    Unicode::snprintf(minutes_setBuffer, MINUTES_SET_SIZE, "%02d", minute);
    Unicode::snprintf(sessions_setBuffer, SESSIONS_SET_SIZE, "%02d", session);
    minutes_set.invalidate();
    sessions_set.invalidate();
}

void Screen1View::tearDownScreen()
{
    Screen1ViewBase::tearDownScreen();
}

void Screen1View::incMinutes() {
	minute = (minute + 1) % 60; // Keep new value in range 0..59
	Unicode::snprintf(minutes_setBuffer, MINUTES_SET_SIZE, "%02d", minute);
	minutes_set.invalidate();
}

void Screen1View::decMinutes() {
	minute = (minute + 60 - 1) % 60; // Keep new value in range 0..59
	Unicode::snprintf(minutes_setBuffer, MINUTES_SET_SIZE, "%02d", minute);
	minutes_set.invalidate();
}

void Screen1View::incSessions() {
	session = session + 1;
	Unicode::snprintf(sessions_setBuffer, SESSIONS_SET_SIZE, "%02d", session);
	sessions_set.invalidate();
}

void Screen1View::decSessions() {
	session = session - 1;
	Unicode::snprintf(sessions_setBuffer, SESSIONS_SET_SIZE, "%02d", session);
	sessions_set.invalidate();
}
void Screen1View::startTimer()
{
  presenter->saveMinute(minute);
  presenter->saveSession(session);

  // Send START_TIMER command with study time and sessions
    TimerCommand_t command;
    command.commandType = START_TIMER;
    command.studyTime = minute; // Selected study time
    command.sessions = session; // Selected sessions
    xQueueSend(xCommandQueue, &command, portMAX_DELAY);
}
