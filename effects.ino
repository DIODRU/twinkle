/*
-----На коментарий в этом файле не хватило бюджета! :)-----
void auto_mode() -       функция, проверяющая не пора ли менять режим(учитывая условия таймера и надо ли)
void etick() -           тикер для эффектов. если функция перестанет вызываться, эффекты замрут. также этот тикер определяет какой эффект надо воспроизводить.
void power_off() -       Выключает гирлянду(заливает полностью черным).
void move_rainbow()-     Эффект подвижной радуги. Достигается засчет умножения нынешнего светодиода на счетчик(который при 256 сбрасывается).
void static_color()-     Эффект статичного цвета, скучно, не правда ли? Скорость - ни за что не отвечает, масштаб - отвечает за цвет.
void sparkling_color() - ↑, но интереснее, ведь цвет теперь еще и плавно мерцает! Скорость - отвечает за скорость мерцания.
void police() -          Полицейская мигалка, вся лента мерцает красно-синим. масштаб - ни за что не отвечает.
void strobo() -          Стробоскоп. Мигает постепенно меняющимся цветом. Масштаб - насколько резко меняется цвет.
void running_fire() -    Бегающий по всей гирлянде огонек, машстаб - отвечает за цвет.
void incident_color() -  Набегающий цвет. фиксированный цвет набегает на диоды по очереди. в конце меняется цвет. Масштаб отвечает за резкость смены цвета по Hue.
*/

void auto_mode() {
  static uint32_t tmr;
  if (is_auto && millis() - tmr >= timetochange * 60000) {
    tmr = millis();
    active_mode++;
  }
}

void etick() {
  if (pwr) {
    switch (active_mode) {
      case 0: power_off();       break;
      case 1: move_rainbow();    break;
      case 2: static_color();    break;
      case 3: sparkling_color(); break;
      case 4: police();          break;
      case 5: strobo();          break;
      case 6: running_fire();    break;
      case 7: incident_color();  break;
      case 8: active_mode = 1;   break;
    }
  } else {
    power_off();
  }
}

void power_off() {
  FastLED.clear();
  FastLED.show();
} // Конец VOID

void move_rainbow() {
  static uint32_t tmr;
  static byte counter;
  if (millis() - tmr >= spd * 2) {
    tmr = millis(); // Обязательно для таймера
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i].setHue(counter + i * zoom);
    } // конец FOR
    counter++;
    FastLED.show();
  } // конец IF
} // Конец VOID

void static_color() {
  if (skip_stcol && is_auto) active_mode++;
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i].setHue(zoom * 12);
  }
  FastLED.show();
}

void sparkling_color() {
  static uint32_t tmr;
  static int val = 0;
  static int dir = 2;
  if (millis() - tmr >= spd) {
    tmr = millis();
    val += dir;
    if (val >= 254 || val <= 0) dir = -dir;
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i].setHSV(zoom * 12, 255, val);
    }
    FastLED.show();
  }
}

void police() {
  static uint32_t tmr;
  static bool rob = true;
  if (millis() - tmr >= spd * 50) {
    tmr = millis();
    rob = !rob;
  }
  for (int i = 0; i < NUM_LEDS; i++) {
    if (rob) leds[i].setRGB(255, 0, 0);
    if (!rob) leds[i].setRGB(0, 0, 255);
  }
  FastLED.show();
}

void strobo() {
  static uint32_t tmr;
  static bool is_turned = false;
  static byte val;
  if (millis() - tmr >= spd * 25) {
    tmr = millis();
    val += zoom * 3;
    is_turned = !is_turned;
  }
  if (is_turned) {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i].setHue(val);
    }
    FastLED.show();
  } else { power_off(); }
}

void running_fire() {
  static uint32_t tmr;
  static int val = 0;
  static int dir = 1;
  if (millis() - tmr >= spd * 25) {
    tmr = millis();
    val += dir;
    if (val >= NUM_LEDS - 1 || val <= 0) dir = -dir;
    FastLED.clear();
    leds[val].setHue(zoom * 12);
    FastLED.show();
  }
}

void incident_color() {
  static uint32_t tmr;
  static int led = 0;
  static byte hue = 0;
  if (millis() - tmr >= spd * 12) {
    tmr = millis();
    led++;
    if (led >= NUM_LEDS) {
      led = 0;
      hue += zoom * 3;
    }
    leds[led].setHue(hue);
    FastLED.show();
  }
}
