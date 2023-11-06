void build() {
  GP.BUILD_BEGIN();
  GP.THEME(GP_DARK);
  GP.TITLE("Twinkle");

  GP.LABEL("Поздравляем! Вы получили доступ"); GP.BREAK();
  GP.LABEL("к панели смарт гирлянды");         GP.BREAK();

  GP.BLOCK_TAB_BEGIN("Основное"); //          НАЧАЛО БЛОКА 1
  M_BOX(GP.LABEL("Питание"); GP.CHECK("pwr", pwr); GP.BREAK(););
  M_BOX(GP.LABEL("Яркость"); GP.SLIDER("bright", bright, 5, 255); GP.BREAK(););
  GP.BLOCK_END(); //                          КОНЕЦ БЛОКА 1!

  GP.BLOCK_TAB_BEGIN("Настройка Эффекта"); // НАЧАЛО БЛОКА 2
  M_BOX(GP.LABEL("Выберите"); GP.SELECT("eff", "Подвижная радуга,Статичный цвет,Моргающий цвет,Полиция,Стробоскоп,Бегающий огонек,Набегающий цвет", active_mode - 1); GP.BREAK(););
  M_BOX(GP.LABEL("Скорость"); GP.SLIDER("spd", spd, 1, 20); GP.BREAK(););
  M_BOX(GP.LABEL("Масштаб"); GP.SLIDER("zoom", zoom, 1, 20); GP.BREAK(););
  GP.BLOCK_END(); //                          КОНЕЦ БЛОКА 2

  GP.BLOCK_TAB_BEGIN("Автоматика"); //        НАЧАЛО БЛОКА 3
  M_BOX( GP.LABEL("Автом. смена режима"); GP.SWITCH("is_auto", is_auto); GP.BREAK(); );
  M_BOX( GP.LABEL("Частота"); GP.SLIDER("timetochange", timetochange, 1, 30); GP.BREAK(); );
  M_BOX( GP.LABEL("Пропускать \"Статич. цвет\"?"); GP.CHECK("skip_stcol", skip_stcol); GP.BREAK(); );
  GP.BLOCK_END(); //                          КОНЕЦ БЛОКА 3

  GP.BUILD_END();
}

void action() {
  if ( ui.click() ) {
    if ( ui.click("pwr") ) {
      pwr = ui.getBool("pwr");
    } //              конец IF(PWR)

    if ( ui.click("bright") ) {
      bright = ui.getInt("bright");
      FastLED.setBrightness(bright);
      FastLED.show();
    } //              конец IF(BRIGHT)

    if ( ui.click("eff") ) {
      active_mode = ui.getInt("eff") + 1;
    } //              конец IF(EFF)

    if ( ui.click("spd") ) {
      spd = ui.getInt("spd");
    } //              конец IF(SPD)

    if ( ui.click("zoom") ) {
      zoom = ui.getInt("zoom");
    } //              конец IF(ZOOM)

    if ( ui.click("is_auto") ) {
      is_auto = ui.getBool("is_auto");
    } //              конец IF(IS_AUTO)

    if ( ui.click("timetochange") ) {
      timetochange = ui.getInt("timetochange");
    } //              конец IF(TIMETOCHANGE)

    if ( ui.click("skip_stcol") ) {
      skip_stcol = ui.getBool("skip_stcol");
    } //              конец IF(skip_stcol)
  } //                конец IF
} //                  конец VOID
