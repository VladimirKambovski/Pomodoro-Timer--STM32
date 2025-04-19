# Pomodoro-Timer--STM32  

## 1. Вовед  
Овој проект имплементира Помодоро тајмер кој овозможува ефикасно управување со времето за учење или работа. Работи по принцип на учење сесии (одреден број минути), по кои следува пауза што е 20% од времетраењето на сесијата учење.  

**Клучни технологии:**  
- `FreeRTOS` – За мултитаскинг преку различни таскови  
- `TouchGFX` – За прикажување на GUI интерфејсот на екранот  
- `FreeRTOS Queues` – За комуникација меѓу тасковите и GUI  

---

## 2. Архитектура на кодот  
Проектот се состои од неколку модули:  
- **Task-ови**: Управуваат со логиката на тајмерот и ажурирањето на екранот  
- **Редици (Queues)**: Овозможуваат размена на пораки помеѓу тасковите  
- **GUI (TouchGFX)**: Ги прикажува преостанатите минути, секунди и статусот  

### 2.1. Главни структури во `Main.h`  
Овие структури се користат за пренос на податоци:  
```c
typedef struct {
    int16_t studyTime;
    int16_t sessions;
} TimerCommand_t;

typedef struct {
    int16_t minutes;
    int16_t seconds;
    int16_t currentSession;
    bool isBreak;
} TimerUpdate_t;
```

### 3. freeRTOS Queues 
xCommandQueue | Прима START_TIMER и STOP_TIMER команди од GUI.
xTimeQueue | Испраќа информации за минути, секунди и пауза до GUI (TouchGF Главни таскови
vTimerTask | Ја прима командата START_TIMER преку xCommandQueue.

### 4. Главни таскови
vTimerTask
- Го слуша xCommandQueue.
- Стартува тајмер при START_TIMER.
- Секунда по секунда испраќа TimerUpdate_t преку xTimeQueue
- Управува со број на сесии и прекини

### GUI логика со TouchGFX
**Користени WIDGETS**
-TextArea
-Button
-Image

![image](https://github.com/user-attachments/assets/ae8f87b5-16bb-456c-8c4b-9e52446f5aed)
![image](https://github.com/user-attachments/assets/d2dfdfb3-b49c-466e-bee7-0b624db608b1)


### Ажурирање на време (Tick Event)
```c
void Screen2View::handleTickEvent() {
    TimeUpdate_t timeUpdate;
    if (xQueueReceive(xTimeQueue, &timeUpdate, 0) == pdPASS) {
        minute = timeUpdate.minutes;
        second = timeUpdate.seconds;
        isBreakSession = timeUpdate.isBreak;

        Unicode::snprintf(minutes_leftBuffer1, MINUTES_LEFTBUFFER1_SIZE, "%02d", minute);
        Unicode::snprintf(minutes_leftBuffer2, MINUTES_LEFTBUFFER2_SIZE, "%02d", second);

        minutes_left.invalidate();
    }
}
```
### Старт/стоп на тајмер
```c
void Screen1View::startTimer() {
    presenter->saveMinute(minute);
    presenter->saveSession(session);

    TimerCommand_t command;
    command.commandType = START_TIMER;
    command.studyTime = minute;
    command.sessions = session;

    xQueueSend(xCommandQueue, &command, portMAX_DELAY);
}

void Screen2View::stopTimer() {
    TimerCommand_t command;
    command.commandType = STOP_TIMER;

    xQueueSend(xCommandQueue, &command, portMAX_DELAY);

    presenter->saveMinute(0);
    presenter->saveSession(0);
}
```
### идеи за подобрување
- Додавање на звук кога завршува сесија
- Напредна статистика и визуализации за историја на фокусираност




