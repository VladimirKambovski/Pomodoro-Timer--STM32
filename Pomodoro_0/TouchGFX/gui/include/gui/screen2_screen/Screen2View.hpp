#ifndef SCREEN2VIEW_HPP
#define SCREEN2VIEW_HPP

#include <gui_generated/screen2_screen/Screen2ViewBase.hpp>
#include <gui/screen2_screen/Screen2Presenter.hpp>

class Screen2View : public Screen2ViewBase
{
public:
    Screen2View();
    virtual ~Screen2View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void handleTickEvent();
    virtual void stopTimer();

protected:
    int16_t minute;
    int16_t second;
    int16_t session;
    int16_t currentSession;  // Current session number
    bool isBreakSession;     // True if the current session is a break, false for study
    int16_t studyTime;       // Selected study time (e.g., 25 minutes)
    int16_t breakTime;       // Break time (10% of study time)
    int16_t tickCount;
    int16_t addStart;
    int16_t addEnd;
};

#endif // SCREEN2VIEW_HPP
