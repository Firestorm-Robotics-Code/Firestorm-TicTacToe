namespace lights{
  char data[8] = "\0\0\0\0\0\0\0\0";
  boll ready = false;
  boll helloSent = false;
  void _ROUTINE(int opcode, HardwareSerial coms){ // Opcodes: 1: hello, 2: blank, 3: chant
    if (!ready){
      if (!helloSent || opcode == 1){
        coms.write(1);
      }
    }
    else{
      switch (opcode){
        case 3:
          coms.write(2);
        break;
        case 4:
          coms.write(3);
          coms.write(data);
        break;
      }
      if (!opcode == 2){
        coms.write(data);
      }
    }
    if (coms.available()){
      char data = coms.read();
      if (data == 1){ // Hello acknowledged!
        ready = true;
      }
    }
  }
  void hello(HardwareSerial coms){
    _ROUTINE(1, coms);
  }
  void run(HardwareSerial coms){
    _ROUTINE(2, coms);
  }
  void wait_until_ready(HardwareSerial coms){
    while (!ready){
      _ROUTINE(2, coms);
    }
  }
  void chant(HardwareSerial coms, uint8_t chant){
    data[0] = chant;
    _ROUTINE(3, coms);
  }
  void movePiece(HardwareSerial coms, uint8_t x, uint8_t y, uint8_t x2, uint8_t y2){
    data[0] = x;
    data[1] = y;
    data[2] = x2;
    data[3] = y2;
    _ROUTINE(4, coms);
  }
}
