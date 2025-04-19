#include <gui/screen2_screen/Screen2View.hpp>
#include <stdint.h>
#include <stdbool.h>  // Add this line
#include <main.h>


Screen2View::Screen2View():  minute(0), second(0), session(0),currentSession(0),
isBreakSession(false), tickCount( 0), addStart(1), addEnd(2)
{

}

void Screen2View::setupScreen()
{
    Screen2ViewBase::setupScreen();
    session = presenter->getSession();
    studyTime = presenter->getMinute();

       Unicode::snprintf(minutes_leftBuffer1, MINUTES_LEFTBUFFER1_SIZE, "%02d", minute);
       Unicode::snprintf(minutes_leftBuffer2, MINUTES_LEFTBUFFER2_SIZE,"%02d" , second);

       minutes_left.invalidate();

}

void Screen2View::tearDownScreen()
{
    Screen2ViewBase::tearDownScreen();


}

void Screen2View::handleTickEvent() {
  #ifndef SIMULATOR
  TimeUpdate_t timeUpdate;
  if (xQueueReceive(xTimeQueue, &timeUpdate, 0) == pdPASS) {
    minute = timeUpdate.minutes;   // Mirror FreeRTOS state
    second = timeUpdate.seconds;   // to your existing variables
    isBreakSession = timeUpdate.isBreak;

    // Your existing display code
    Unicode::snprintf(minutes_leftBuffer1, MINUTES_LEFTBUFFER1_SIZE, "%02d", minute);
    Unicode::snprintf(minutes_leftBuffer2, MINUTES_LEFTBUFFER2_SIZE, "%02d", second);
    minutes_left.invalidate();
  }
  #endif
}






//void Screen2View::handleTickEvent() {
//  TimeUpdate_t timeUpdate;
//  if (xQueueReceive(xTimeQueue, &timeUpdate, 0) == pdPASS) {
//    // Update UI with timeUpdate.minutes, timeUpdate.seconds
//    Unicode::snprintf(minutes_leftBuffer1, MINUTES_LEFTBUFFER1_SIZE, "%02d", timeUpdate.minutes);
//    minutes_left.invalidate();
//  }
//}


//void Screen2View::handleTickEvent()
//{
//    if (minute > 0 || second > 0)
//    {
//        tickCount++;
//
//        if (tickCount >= 60) // 1 second has passed
//        {
//            tickCount = 0;
//            if (second == 0)
//            {
//                if (minute > 0)
//                {
//                    minute--;
//                    second = 59;
//                }
//            }
//            else
//            {
//                second--;
//            }
//
//            // Update the display
//            Unicode::snprintf(minutes_leftBuffer1, MINUTES_LEFTBUFFER1_SIZE, "%02d", minute);
//            Unicode::snprintf(minutes_leftBuffer2, MINUTES_LEFTBUFFER2_SIZE, "%02d", second);
//            minutes_left.invalidate();
//        }
//    }
//    else
//    {
//        // Current session has ended
//        if (!isBreakSession)
//        {
//            // Study session ended, start break session
//            isBreakSession = true;
//            minute = breakTime;
//            second = 0;
//        }
//        else
//        {
//            // Break session ended, start next study session
//            isBreakSession = false;
//            currentSession++;
//
//            if (currentSession > session)
//            {
//                // All sessions completed, stop the timer
//                stopTimer();
//                return;
//            }
//            else
//            {
//                // Start the next study session
//                minute = studyTime;
//                second = 0;
//            }
//        }
//
//        // Update the display for the new session
//        Unicode::snprintf(minutes_leftBuffer1, MINUTES_LEFTBUFFER1_SIZE, "%02d", minute);
//        Unicode::snprintf(minutes_leftBuffer2, MINUTES_LEFTBUFFER2_SIZE, "%02d", second);
//        minutes_left.invalidate();
//    }
//}

void Screen2View::stopTimer()
{


	// Send STOP_TIMER command to TimerTask
	  TimerCommand_t command;
	  command.commandType = STOP_TIMER;
	  xQueueSend(xCommandQueue, &command, portMAX_DELAY);

	  // Reset values in the presenter/model
	  presenter->saveMinute(0);    // Reset minutes to 0
	  presenter->saveSession(0);   // Reset sessions to 0

    minute = 0;
    second = 0;
    currentSession = 0;
    isBreakSession = false;



}
