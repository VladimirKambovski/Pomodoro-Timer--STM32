



#ifndef MODEL_HPP
#define MODEL_HPP

#include <stdint.h>

class ModelListener;

class Model
{
public:
    Model();

    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }

    void tick();

    void saveMinute(int16_t saveMinute) {
    	minute = saveMinute;
    }
    void saveSession(int16_t saveSession) {
    	session = saveSession;
    }
    int16_t getMinute() {
    	return minute;
    }
    int16_t getSession() {
    	return session;
    }
protected:
    ModelListener* modelListener;

    int16_t minute;
    int16_t session;
};

#endif // MODEL_HPP
