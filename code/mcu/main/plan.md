## Planning for rebuilding to make it modular and easier to expand on code

### List of functions

1. LedClass (constructor)
2. setLedValuesVolume
3. setLedValuesConnection
4. ledSetup

5. volumeCallback
6. checkBluetoothConnectionTask
7. audioStreamingSetup

8. setup
9. loop

### Grouping

- LedClass

  - ledSetup
  - setLedValuesVolume
  - setLedValuesBTConnection
    - sets the leds to be red/green,

- bluetooth
  - checkBluetoothConnectionTask
  - volumeCallback
  - audioStreamingSetup

### Target structure

- LedClass

  - ledSetup
  - ledVolume
  - ledBluetooth
  - setLed
  - startTimeoutLed

- bluetooth
  - checkBluetoothConnection
    - check for bt, call ledBluetooth
  - volumeCallback
  - audioStreamingSetup
  - audioStreamingLoop
