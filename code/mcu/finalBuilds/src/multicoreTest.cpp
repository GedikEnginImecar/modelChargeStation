// multicoreTest.cpp
// script to test and reaffirm prior understanding and knowledge of utilizing multi core processing on esp32

#include "Arduino.h"
#include "AudioTools.h"
#include "BluetoothA2DPSink.h"
#include "BluetoothA2DPSource.h"

int count1 = 0;
int count2 = 0;
TaskHandle_t task1Handle = NULL; // used to create a task handler to manipulate it across the program

// pointer to void parameters
// used when creating a FreeRTOS task
// allows you to pass parameters of any kind into the task function
// allows for flexibility and transfer of data between tasks
// pvParameters "pv" stands for pointer void, directly shows that it is a void pointer
void task1(void *pvParameters)
{
    for (;;) // infinite for loop
    {
        Serial.print("Task 1 counter:");
        Serial.println(count1++);              // increments counter
        vTaskDelay(1000 / portTICK_PERIOD_MS); // vTaskDelay counts in ticks, but 1000/portTICK_PERIOD_MS converts it into ms by using constant built in
    }
    if (count1 > 3)
    {
        // vTaskDelete(NULL); // to terminate task internally
        vTaskSuspend(NULL) // to pause/suspend the task
    }
};

void task2(void *pvParameters)
{
    for (;;) // infinite for loop
    {
        Serial.print("Task 2 counter:");
        Serial.println(count2++);              // increments counter
        vTaskDelay(1000 / portTICK_PERIOD_MS); // vTaskDelay counts in ticks, but 1000/portTICK_PERIOD_MS converts it into ms by using constant built in
    }
    if (count2 == 10)
    {
        vTaskDelete(NULL); // to delete a task internally
    }
};

void setup()
{
    Serial.begin(9600);
    // xTaskCreate(function to run,
    // name/description of the task - debug purposes and you can use FreeRTOS to display info about running tasks
    // stack size - esp32 uses bytes but normally expressed in words. value depends on function, it increases with more variables used, can require more if connecting to wifi or loading heavier libs
    // the task parameter to receive when the task is created, if nothing it can be null
    // task priority, the higher the number the higher priority the task will be, FreeRTOS will give that task more time
    // used to get a task handle, allowing tasks to interact with other tasks);
    xTaskCreate(task1, "Task 1", 1000, NULL, 1, &task1Handle); // using task handler to control task externally
    xTaskCreate(task2, "Task 2", 1000, NULL, 1, NULL);
}

void imperativeTask()
{
    vTaskSuspendAll(); // to suspend all tasks to lend priority to code that needs to be executed

    // code that needs to be executed
    Serial.println("Imperative Task");

    xTaskResumeAll(); // to resume all tasks once code above is executed. pay attention to xTask and how it is not vTask
}

void loop()
{
    if (count1 > 3 && task1Handle != NULL) // to check if task 1 is greater than 3 and not null
    // if it is null it will suspend the active task
    {
        vTaskSuspend(task1Handle);
    }

    if (count2 == 5 && task1Handle != NULL) // task1 to resume via its handler when task2 is equal to 5 and task1 handler is not null
    {
        vTaskResume(task1Handle); // to resume the task that was previously suspended
    }

    if (count1 == 10)
    {
        vTaskDelete(task1Handle); // to delete a task
    }
}