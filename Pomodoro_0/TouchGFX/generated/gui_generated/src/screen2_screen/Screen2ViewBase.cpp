/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/screen2_screen/Screen2ViewBase.hpp>
#include <touchgfx/canvas_widget_renderer/CanvasWidgetRenderer.hpp>
#include <touchgfx/Color.hpp>
#include <images/BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>

Screen2ViewBase::Screen2ViewBase() :
    flexButtonCallback(this, &Screen2ViewBase::flexButtonCallbackHandler)
{
    touchgfx::CanvasWidgetRenderer::setupBuffer(canvasBuffer, CANVAS_BUFFER_SIZE);
    
    __background.setPosition(0, 0, 480, 272);
    __background.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    add(__background);

    image1.setXY(0, 0);
    image1.setBitmap(touchgfx::Bitmap(BITMAP_IMAX_POSTER_GREEN_480X272_ID));
    add(image1);

    clockCircle.setPosition(160, 56, 160, 160);
    clockCircle.setCenter(80, 80);
    clockCircle.setRadius(75);
    clockCircle.setLineWidth(5);
    clockCircle.setArc(0, 195);
    clockCircle.setCapPrecision(10);
    clockCirclePainter.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    clockCircle.setPainter(clockCirclePainter);
    add(clockCircle);

    minutes_left.setPosition(190, 111, 100, 50);
    minutes_left.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    minutes_left.setLinespacing(0);
    touchgfx::Unicode::snprintf(minutes_leftBuffer1, MINUTES_LEFTBUFFER1_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_DFE3).getText());
    minutes_left.setWildcard1(minutes_leftBuffer1);
    touchgfx::Unicode::snprintf(minutes_leftBuffer2, MINUTES_LEFTBUFFER2_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_GRIV).getText());
    minutes_left.setWildcard2(minutes_leftBuffer2);
    minutes_left.setTypedText(touchgfx::TypedText(T___SINGLEUSE_0U73));
    add(minutes_left);

    stop.setBoxWithBorderPosition(0, 0, 240, 48);
    stop.setBorderSize(5);
    stop.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(255, 255, 255), touchgfx::Color::getColorFromRGB(155, 157, 158), touchgfx::Color::getColorFromRGB(0, 0, 0), touchgfx::Color::getColorFromRGB(0, 0, 0));
    stop.setText(TypedText(T___SINGLEUSE_DMO7));
    stop.setTextPosition(0, 0, 240, 48);
    stop.setTextColors(touchgfx::Color::getColorFromRGB(10, 10, 10), touchgfx::Color::getColorFromRGB(10, 10, 10));
    stop.setAction(flexButtonCallback);
    stop.setPosition(120, 216, 240, 48);
    add(stop);

    study_break.setXY(185, 5);
    study_break.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    study_break.setLinespacing(0);
    Unicode::snprintf(study_breakBuffer, STUDY_BREAK_SIZE, "%s", touchgfx::TypedText(T___SINGLEUSE_PYMW).getText());
    study_break.setWildcard(study_breakBuffer);
    study_break.resizeToCurrentText();
    study_break.setTypedText(touchgfx::TypedText(T___SINGLEUSE_GEAN));
    add(study_break);
}

Screen2ViewBase::~Screen2ViewBase()
{
    touchgfx::CanvasWidgetRenderer::resetBuffer();
}

void Screen2ViewBase::setupScreen()
{

}

void Screen2ViewBase::flexButtonCallbackHandler(const touchgfx::AbstractButtonContainer& src)
{
    if (&src == &stop)
    {
        //stopTimerInteraction
        //When stop clicked call virtual function
        //Call stopTimer
        stopTimer();
        //changeScreenInteraction
        //When stop clicked change screen to Screen1
        //Go to Screen1 with screen transition towards East
        application().gotoScreen1ScreenSlideTransitionEast();
    }
}
