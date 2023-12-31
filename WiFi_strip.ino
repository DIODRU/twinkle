#define NUM_LEDS 25 //                  Кол-во диодов(можно поставить больше чем есть, но будет лишняя нагрузка, а также будет неправильно работать "Бегающий огонек")
#define PIN D4 //                       Пин, куда подключена гирлянда

#define WIFI_MODE "AP" //               Подключаться к роутеру("STA"), создавать точку доступа("AP")
#define AP_SSID "esp" //                Название(если режим STA - название вашей домашней вайфай сети, если режим AP - любое название для вашей точки доступа
#define AP_PASS "house102" //           Пароль ↑ (Оставьте пустым, если не нужно)

#include <FastLED.h> //    Библиотека
#include <ESP8266WiFi.h> //         ↑
#include <GyverPortal.h> //         ↑

CRGB leds[NUM_LEDS]; //    Адреса для диодов
GyverPortal ui; //         Переменная интерфейса

//--------------------Для разработчиков!(также и значения по умолчанию)--------------------
bool pwr = true; //       Питание?
bool is_auto = false; //  Автоматическая смена?
bool skip_stcol = true; //Пропускать эффект "Статичный цвет"? (при включенной автоматике)
int active_mode = 1; //   Нынешний режим?
int bright = 200; //      Яркость?
int spd = 10; //          Скорость?
int zoom = 10; //         Масштаб?
int timetochange = 1; //  Частота смены режима?(в минутах)
//-----------------------------------------------------------------------------------------

/*
------------------------------------------------ИНСТРУКЦИЯ ПО НАСТРОЙКЕ!------------------------
    1.Откройте настройки IDE (Файл -> Настройки)
    2.Вставьте ссылку в "Допольнительные ссылки для менеджера плат" -> http://arduino.esp8266.com/stable/package_esp8266com_index.json   <--- ВАЖНО!
    3.Откройте менеджер плат (Инструменты -> Плата -> Менеджер плат...)
    4.Напишите в поиск "esp8266"
    5.Выберите версию 3.5.0 и установите.
    ВАЖНО! --> Если у вас еще не установлен драйвер CH341, то... -> https://github.com/electronicsf/driver-ch341
                                        P.S. Для недоверчивых :) -> https://yandex.ru/search/?text=driver+ch341+arduino
               Также не забудьте скачать зависимости! (находится на гитхабе, в папке libraries)
------------------------------------------------------------------------------------------------
*/

void setup() {
  Serial.begin(115200); //                                Запуск отладки на скорости 115200
  
  FastLED.addLeds<WS2811, PIN, RGB>(leds, NUM_LEDS); //   Загрузка диодов в массив ихних адрессов
  FastLED.setBrightness(200); //                          Установка яркости по умолчанию
  if (WIFI_MODE == "AP") { //                             Если выбрано "создавать точку доступа"
    WiFi.mode(WIFI_AP); //                                Настраиваем режим на точку доступа
    WiFi.softAP(AP_SSID, AP_PASS); //                     ↑ Настраиваем саму точку и сразу запускаем
  }
  if (WIFI_MODE == "STA") {
    WiFi.mode(WIFI_STA); //                               Ставим режим на подключение
    WiFi.begin(AP_SSID, AP_PASS);
    while (WiFi.status() != WL_CONNECTED) {
      for (int i = 0; i < 255; i++ ){
        for (int l = 0; l < NUM_LEDS; l++) {
          leds[l].setHSV(128, 255, i);
        }
        FastLED.show();
        delay(2);
      }
      for (int i = 255; i > 0; i-- ){
        for (int l = 0; l < NUM_LEDS; l++) {
          leds[l].setHSV(128, 255, i);
        }
        FastLED.show();
        delay(2);
      }
    }
    Serial.println(WiFi.localIP());
  }

  ui.attachBuild(build);
  ui.attach(action);
  ui.start();
}

void loop() {
  ui.tick(); //Функция из GyverPortal.h
  etick(); //  Функция из effects.ino
  auto_mode(); // Функция проверки параметра is_auto и ее работы в случае правды
}
