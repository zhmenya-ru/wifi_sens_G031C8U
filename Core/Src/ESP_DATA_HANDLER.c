/**
  ******************************************************************************

  File:		ESP DATA HANDLER
  Author:   ControllersTech
  Updated:  3rd Aug 2020

  ******************************************************************************
  Copyright (C) 2017 ControllersTech.com

  This is a free software under the GNU license, you can redistribute it and/or modify it under the terms
  of the GNU General Public License version 3 as published by the Free Software Foundation.
  This software library is shared with public for educational purposes, without WARRANTY and Author is not liable for any damages caused directly
  or indirectly by this software, read more about this on the GNU General Public License.

  ******************************************************************************
*/



#include "ESP_DATA_HANDLER.h"
#include "UartRingbuffer.h"
#include "stdio.h"
#include "string.h"

extern UART_HandleTypeDef huart1;

#define wifi_uart &huart1

#define maxnumberofusers  10  // Max number of users

char buffer[20];
userDetails user[maxnumberofusers];

int usernumber = 0;

int sizeofuser (userDetails *user)
{
	int size=0;
	while (user[size].firstname[0] != '\0') size++;
	return size+1;
}

char *home = "<!DOCTYPE html>\n\
		<html lang=\"en\">\n\
		<head>\n\
		<meta charset=\"UTF-8\">\n\
		<style>a {text-decoration: none;display: block;margin: 10px 2px;}</style>\n\
		</head>\n\
		<body>\n\
		<h1>Главный Экран</h1>\n\
		<a href=\"/heating\">\n\
    	<button>Настройки отопления</button>\n\
		</a>\n\
		</body></html>";


char *heating = "<!DOCTYPE html>\n\
		<html lang=\"en\">\n\
		<head>\n\
    	<meta charset=\"UTF-8\">\n\
    	<style>body {height: 100%;width: 100%;overflow-x: hidden;margin: 0 auto;}\n\
		a {text-decoration: none;margin: 20px;display: block;padding: 10px;width:\n\
		200px;height: 25px;background-color: green;color: white;line-height: 25px;\n\
		font-size: 20px;text-align: center;border-radius: 5px;}\n\
        button {line-height: 20px;font-size: 20px;}\n\
        h1 {text-align: center;width: 100%;}.wrapper {width: 100%;margin: 0 auto;\n\
        text-align: center;display: flex;flex-direction: column;align-items: center;}\n\
        </style>\n\
        </head>\n\
        <body>\n\
        <h1>Настройки отопления</h1>\n\
        <div class=\"wrapper\">\n\
        <a href=\"/zal\">Зал</a>\n\
        <a href=\"/vann\">Ванная</a>\n\
        <a href=\"/kryl\">Крыльцо</a>\n\
        <a href=\"/lest\">Лестница</a>\n\
        <a href=\"/ps\">Полотенце Сушитель</a>\n\
        <a href=\"/kotel\">Котел</a>\n\
        <a href=\"/dets\">Детская</a>\n\
        <a href=\"/spal\">Спальня</a>\n\
        <a href=\"/glad\">Гладилка</a>\n\
        <a href=\"/tual\">Туалет</a>\n\
        <a href=\"/home\">Домой</a>\n\
        </div>\n\
        </body>\n\
        </html>";

char *settings = "";

char *zal = "<!DOCTYPE html>\n\
		<html lang=\"en\">\n\
		<head>\n\
		<meta charset=\"UTF-8\">\n\
		<style>\n\
        body {height: 100%;width: 100%;font-size: 20px;overflow-x: hidden;}\n\
        a {text-decoration: none;margin: 20px;display: block;width: 100px;}\n\
        button {line-height: 20px;font-size: 20px;}h1 {text-align: center;width: 100%;}\n\
        input {color: red;font-size: 18px;}#otn-vlag {color: blue;}#temp {color: green;width: 100px;}\n\
        input[type='submit'] {color: white;background-color: green;}\n\
        </style>\n\
        </head>\n\
        <body>\n\
        <h1>Параметры отопления в Зале</h1>\n\
        <h2>Текущие значения</h2>\n\
        <form action=\"/zal-sumbit\">\n\
        <label for=\"otn-vlag\">Относительная влажность</label>\n\
        <input id=\"otn-vlag\" value=\"0.00\" min=\"0\" max=\"100\"  name=\"otn-vlag\" type=\"text\" disabled=\"disabled\">\n\
        <br><br><label for=\"temp-kom\">Температура в комнате</label>\n\
        <input id=\"temp-kom\" value=\"0.00\" min=\"0\" max=\"100\" name=\"temp-kom\" type=\"text\" disabled=\"disabled\">\n\
        <br><br><label for=\"temp-obr\">Температура обратного контура</label>\n\
        <input id=\"temp-obr\" value=\"0.00\" min=\"0\" max=\"100\" name=\"temp-obr\" type=\"text\" disabled=\"disabled\">\n\
        <br><br><h2>Установка</h2><label for=\"temp\">Температура</label>\n\
        <input id=\"temp\" min=\"0\" max=\"100\" size=\"10\" type=\"number\">\n\
        <input type=\"submit\" value=\"Установить\">\n\
        </form><br><br>\n\
        <a href=\"/heating\">\n\
        <button>Назад</button></a>\n\
        </body>\n\
        </html>";

char *vann = "<!DOCTYPE html>\n\
		<html lang=\"en\">\n\
		<head>\n\
		<meta charset=\"UTF-8\">\n\
		<style>\n\
        body {height: 100%;width: 100%;font-size: 20px;overflow-x: hidden;}\n\
        a {text-decoration: none;margin: 20px;display: block;width: 100px;}\n\
        button {line-height: 20px;font-size: 20px;}h1 {text-align: center;width: 100%;}\n\
        input {color: red;font-size: 18px;}#otn-vlag {color: blue;}#temp {color: green;width: 100px;}\n\
        input[type='submit'] {color: white;background-color: green;}\n\
        </style>\n\
        </head>\n\
        <body>\n\
        <h1>Параметры отопления в Ванной</h1>\n\
        <h2>Текущие значения</h2>\n\
        <form action=\"/vann-sumbit\">\n\
        <label for=\"otn-vlag\">Относительная влажность</label>\n\
        <input id=\"otn-vlag\" value=\"0.00\" min=\"0\" max=\"100\"  name=\"otn-vlag\" type=\"text\" disabled=\"disabled\">\n\
        <br><br><label for=\"temp-kom\">Температура в Ванной</label>\n\
        <input id=\"temp-kom\" value=\"0.00\" min=\"0\" max=\"100\" name=\"temp-kom\" type=\"text\" disabled=\"disabled\">\n\
        <br><br><label for=\"temp-obr\">Температура обратного контура</label>\n\
        <input id=\"temp-obr\" value=\"0.00\" min=\"0\" max=\"100\" name=\"temp-obr\" type=\"text\" disabled=\"disabled\">\n\
        <br><br><label for=\"temp-pol1\">Температура пола №1</label>\n\
        <input id=\"temp-pol1\" value=\"0.00\" min=\"0\" max=\"100\" name=\"temp-obr\" type=\"text\" disabled=\"disabled\">\n\
        <br><br><label for=\"temp-pol2\">Температура пола №2</label>\n\
        <input id=\"temp-pol2\" value=\"0.00\" min=\"0\" max=\"100\" name=\"temp-obr\" type=\"text\" disabled=\"disabled\">\n\
		<br><br><h2>Установка</h2><label for=\"temp\">Температура</label>\n\
        <input id=\"temp\" min=\"0\" max=\"100\" size=\"10\" type=\"number\">\n\
        <input type=\"submit\" value=\"Установить\">\n\
        </form><br><br>\n\
        <a href=\"/heating\">\n\
        <button>Назад</button></a>\n\
        </body>\n\
        </html>";

char *kryl = "<!DOCTYPE html>\n\
		<html lang=\"en\">\n\
		<head>\n\
		<meta charset=\"UTF-8\">\n\
		<style>\n\
        body {height: 100%;width: 100%;font-size: 20px;overflow-x: hidden;}\n\
        a {text-decoration: none;margin: 20px;display: block;width: 100px;}\n\
        button {line-height: 20px;font-size: 20px;}h1 {text-align: center;width: 100%;}\n\
        input {color: red;font-size: 18px;}#otn-vlag {color: blue;}#temp {color: green;width: 100px;}\n\
        input[type='submit'] {color: white;background-color: green;}\n\
        </style>\n\
        </head>\n\
        <body>\n\
        <h1>Параметры отопления на Крыльце</h1>\n\
        <h2>Текущие значения</h2>\n\
        <form action=\"/vann-sumbit\">\n\
        <label for=\"otn-vlag\">Относительная влажность</label>\n\
        <input id=\"otn-vlag\" value=\"0.00\" min=\"0\" max=\"100\"  name=\"otn-vlag\" type=\"text\" disabled=\"disabled\">\n\
        <br><br><label for=\"temp-kom\">Температура в Ванной</label>\n\
        <input id=\"temp-kom\" value=\"0.00\" min=\"0\" max=\"100\" name=\"temp-kom\" type=\"text\" disabled=\"disabled\">\n\
        <br><br><label for=\"temp-obr\">Температура обратного контура</label>\n\
        <input id=\"temp-obr\" value=\"0.00\" min=\"0\" max=\"100\" name=\"temp-obr\" type=\"text\" disabled=\"disabled\">\n\
        <br><br><label for=\"temp-pol1\">Температура пола №1</label>\n\
        <input id=\"temp-pol1\" value=\"0.00\" min=\"0\" max=\"100\" name=\"temp-obr\" type=\"text\" disabled=\"disabled\">\n\
        <br><br><label for=\"temp-pol2\">Температура пола №2</label>\n\
        <input id=\"temp-pol2\" value=\"0.00\" min=\"0\" max=\"100\" name=\"temp-obr\" type=\"text\" disabled=\"disabled\">\n\
		<br><br><h2>Установка</h2><label for=\"temp\">Температура</label>\n\
        <input id=\"temp\" min=\"0\" max=\"100\" size=\"10\" type=\"number\">\n\
        <input type=\"submit\" value=\"Установить\">\n\
        </form><br><br>\n\
        <a href=\"/heating\">\n\
        <button>Назад</button></a>\n\
        </body>\n\
        </html>";

char *lest = "<!DOCTYPE html>\n\
		<html lang=\"en\">\n\
		<head>\n\
		<meta charset=\"UTF-8\">\n\
		<style>\n\
        body {height: 100%;width: 100%;font-size: 20px;overflow-x: hidden;}\n\
        a {text-decoration: none;margin: 20px;display: block;width: 100px;}\n\
        button {line-height: 20px;font-size: 20px;}h1 {text-align: center;width: 100%;}\n\
        input {color: red;font-size: 18px;}#otn-vlag {color: blue;}#temp {color: green;width: 100px;}\n\
        input[type='submit'] {color: white;background-color: green;}\n\
        </style>\n\
        </head>\n\
        <body>\n\
        <h1>Параметры отопления под Лестницой</h1>\n\
        <h2>Текущие значения</h2>\n\
        <form action=\"/lest-sumbit\">\n\
        <label for=\"otn-vlag\">Относительная влажность</label>\n\
        <input id=\"otn-vlag\" value=\"0.00\" min=\"0\" max=\"100\"  name=\"otn-vlag\" type=\"text\" disabled=\"disabled\">\n\
        <br><br><label for=\"temp-kom\">Температура под Лестницей</label>\n\
        <input id=\"temp-kom\" value=\"0.00\" min=\"0\" max=\"100\" name=\"temp-kom\" type=\"text\" disabled=\"disabled\">\n\
        <br><br><label for=\"temp-obr\">Температура обратного контура</label>\n\
        <input id=\"temp-obr\" value=\"0.00\" min=\"0\" max=\"100\" name=\"temp-obr\" type=\"text\" disabled=\"disabled\">\n\
        <br><br><h2>Установка</h2><label for=\"temp\">Температура</label>\n\
        <input id=\"temp\" min=\"0\" max=\"100\" size=\"10\" type=\"number\">\n\
        <input type=\"submit\" value=\"Установить\">\n\
        </form><br><br>\n\
        <a href=\"/heating\">\n\
        <button>Назад</button></a>\n\
        </body>\n\
        </html>";

char *ps = "<!DOCTYPE html>\n\
		<html lang=\"en\">\n\
		<head>\n\
		<meta charset=\"UTF-8\">\n\
		<style>\n\
        body {height: 100%;width: 100%;font-size: 20px;overflow-x: hidden;}\n\
        a {text-decoration: none;margin: 20px;display: block;width: 100px;}\n\
        button {line-height: 20px;font-size: 20px;}h1 {text-align: center;width: 100%;}\n\
        input {color: red;font-size: 18px;}#otn-vlag {color: blue;}#temp {color: green;width: 100px;}\n\
        input[type='submit'] {color: white;background-color: green;}\n\
        </style>\n\
        </head>\n\
        <body>\n\
        <h1>Параметры температуры Полотенцесушителя</h1>\n\
        <h2>Текущие значения</h2>\n\
        <form action=\"/ps-sumbit\">\n\
        <label for=\"otn-vlag\">Относительная влажность</label>\n\
        <input id=\"otn-vlag\" value=\"0.00\" min=\"0\" max=\"100\"  name=\"otn-vlag\" type=\"text\" disabled=\"disabled\">\n\
        <br><br><label for=\"temp-kom\">Температура полотенцесушителя</label>\n\
        <input id=\"temp-kom\" value=\"0.00\" min=\"0\" max=\"100\" name=\"temp-kom\" type=\"text\" disabled=\"disabled\">\n\
        <br><br><label for=\"temp-obr\">Температура обратного контура</label>\n\
        <input id=\"temp-obr\" value=\"0.00\" min=\"0\" max=\"100\" name=\"temp-obr\" type=\"text\" disabled=\"disabled\">\n\
        <br><br><h2>Установка</h2><label for=\"temp\">Температура</label>\n\
        <input id=\"temp\" min=\"0\" max=\"100\" size=\"10\" type=\"number\">\n\
        <input type=\"submit\" value=\"Установить\">\n\
        </form><br><br>\n\
        <a href=\"/heating\">\n\
        <button>Назад</button></a>\n\
        </body>\n\
        </html>";

char *kotel = "<!DOCTYPE html>\n\
		<html lang=\"en\">\n\
		<head>\n\
    	<meta charset=\"UTF-8\">\n\
    	<style>\n\
        body {height: 100%;width: 100%;font-size: 20px;overflow-x: hidden;}\n\
        a {text-decoration: none;margin: 20px;display: block;width: 100px;}\n\
        button {line-height: 20px;font-size: 20px;}\n\
        h1 {text-align: center;width: 100%;}\n\
        input {color: red;font-size: 18px;}\n\
        #otn-vlag {color: blue;}\n\
        #temp {color: green;width: 100px;}\n\
        input[type='submit'] {color: white;background-color: green;}\n\
        </style></head><body>\n\
        <h1>Параметры отопления в Котельной</h1>\n\
        <h2>Текущие значения</h2>\n\
        <form action=\"/kotel-sumbit\">\n\
        <label for=\"otn-vlag\">Относительная влажность</label>\n\
        <input id=\"otn-vlag\" min=\"0\" max=\"100\"  name=\"otn-vlag\" type=\"text\" disabled=\"disabled\" value=\"0.00\">\n\
        <br><br><label for=\"temp-kom\">Температура в комнате</label>\n\
        <input id=\"temp-kom\" min=\"0\" max=\"100\" name=\"temp-kom\" type=\"text\" disabled=\"disabled\" value=\"0.00\">\n\
        <br><br><label for=\"temp-obr\">Температура обратного контура</label>\n\
        <input id=\"temp-obr\" min=\"0\" max=\"100\" name=\"temp-obr\" type=\"text\" disabled=\"disabled\" value=\"0.00\">\n\
        <br><br><h2>Установка</h2>\n\
        <label for=\"temp\">Температура</label>\n\
        <input id=\"temp\" min=\"0\" max=\"100\" size=\"10\" type=\"number\">\n\
        <input type=\"submit\" value=\"Установить\">\n\
        </form><br><br>\n\
        <a href=\"./heating\">\n\
        <button>Назад</button></a>\n\
        </body></html>";

char *dets = "<!DOCTYPE html>\n\
		<html lang=\"en\">\n\
		<head>\n\
		<meta charset=\"UTF-8\">\n\
		<style>\n\
        body {height: 100%;width: 100%;font-size: 20px;overflow-x: hidden;}\n\
        a {text-decoration: none;margin: 20px;display: block;width: 100px;}\n\
        button {line-height: 20px;font-size: 20px;}h1 {text-align: center;width: 100%;}\n\
        input {color: red;font-size: 18px;}#otn-vlag {color: blue;}#temp {color: green;width: 100px;}\n\
        input[type='submit'] {color: white;background-color: green;}\n\
        </style>\n\
        </head>\n\
        <body>\n\
        <h1>Параметры отопления в Детской</h1>\n\
        <h2>Текущие значения</h2>\n\
        <form action=\"/dets-sumbit\">\n\
        <label for=\"otn-vlag\">Относительная влажность</label>\n\
        <input id=\"otn-vlag\" value=\"0.00\" min=\"0\" max=\"100\"  name=\"otn-vlag\" type=\"text\" disabled=\"disabled\">\n\
        <br><br><label for=\"temp-kom\">Температура в комнате</label>\n\
        <input id=\"temp-kom\" value=\"0.00\" min=\"0\" max=\"100\" name=\"temp-kom\" type=\"text\" disabled=\"disabled\">\n\
        <br><br><label for=\"temp-obr\">Температура обратного контура</label>\n\
        <input id=\"temp-obr\" value=\"0.00\" min=\"0\" max=\"100\" name=\"temp-obr\" type=\"text\" disabled=\"disabled\">\n\
        <br><br><h2>Установка</h2><label for=\"temp\">Температура</label>\n\
        <input id=\"temp\" min=\"0\" max=\"100\" size=\"10\" type=\"number\">\n\
        <input type=\"submit\" value=\"Установить\">\n\
        </form><br><br>\n\
        <a href=\"/heating\">\n\
        <button>Назад</button></a>\n\
        </body>\n\
        </html>";

char *spal = "<!DOCTYPE html>\n\
		<html lang=\"en\">\n\
		<head>\n\
		<meta charset=\"UTF-8\">\n\
		<style>\n\
        body {height: 100%;width: 100%;font-size: 20px;overflow-x: hidden;}\n\
        a {text-decoration: none;margin: 20px;display: block;width: 100px;}\n\
        button {line-height: 20px;font-size: 20px;}h1 {text-align: center;width: 100%;}\n\
        input {color: red;font-size: 18px;}#otn-vlag {color: blue;}#temp {color: green;width: 100px;}\n\
        input[type='submit'] {color: white;background-color: green;}\n\
        </style>\n\
        </head>\n\
        <body>\n\
        <h1>Параметры отопления в Спальне</h1>\n\
        <h2>Текущие значения</h2>\n\
        <form action=\"/spal-sumbit\">\n\
        <label for=\"otn-vlag\">Относительная влажность</label>\n\
        <input id=\"otn-vlag\" value=\"0.00\" min=\"0\" max=\"100\"  name=\"otn-vlag\" type=\"text\" disabled=\"disabled\">\n\
        <br><br><label for=\"temp-kom\">Температура в комнате</label>\n\
        <input id=\"temp-kom\" value=\"0.00\" min=\"0\" max=\"100\" name=\"temp-kom\" type=\"text\" disabled=\"disabled\">\n\
        <br><br><label for=\"temp-obr\">Температура обратного контура</label>\n\
        <input id=\"temp-obr\" value=\"0.00\" min=\"0\" max=\"100\" name=\"temp-obr\" type=\"text\" disabled=\"disabled\">\n\
        <br><br><h2>Установка</h2><label for=\"temp\">Температура</label>\n\
        <input id=\"temp\" min=\"0\" max=\"100\" size=\"10\" type=\"number\">\n\
        <input type=\"submit\" value=\"Установить\">\n\
        </form><br><br>\n\
        <a href=\"/heating\">\n\
        <button>Назад</button></a>\n\
        </body>\n\
        </html>";

char *glad = "<!DOCTYPE html>\n\
		<html lang=\"en\">\n\
		<head>\n\
		<meta charset=\"UTF-8\">\n\
		<style>\n\
        body {height: 100%;width: 100%;font-size: 20px;overflow-x: hidden;}\n\
        a {text-decoration: none;margin: 20px;display: block;width: 100px;}\n\
        button {line-height: 20px;font-size: 20px;}h1 {text-align: center;width: 100%;}\n\
        input {color: red;font-size: 18px;}#otn-vlag {color: blue;}#temp {color: green;width: 100px;}\n\
        input[type='submit'] {color: white;background-color: green;}\n\
        </style>\n\
        </head>\n\
        <body>\n\
        <h1>Параметры отопления в Гладилке</h1>\n\
        <h2>Текущие значения</h2>\n\
        <form action=\"/glad-sumbit\">\n\
        <label for=\"otn-vlag\">Относительная влажность</label>\n\
        <input id=\"otn-vlag\" value=\"0.00\" min=\"0\" max=\"100\"  name=\"otn-vlag\" type=\"text\" disabled=\"disabled\">\n\
        <br><br><label for=\"temp-kom\">Температура в комнате</label>\n\
        <input id=\"temp-kom\" value=\"0.00\" min=\"0\" max=\"100\" name=\"temp-kom\" type=\"text\" disabled=\"disabled\">\n\
        <br><br><label for=\"temp-obr\">Температура обратного контура</label>\n\
        <input id=\"temp-obr\" value=\"0.00\" min=\"0\" max=\"100\" name=\"temp-obr\" type=\"text\" disabled=\"disabled\">\n\
        <br><br><h2>Установка</h2><label for=\"temp\">Температура</label>\n\
        <input id=\"temp\" min=\"0\" max=\"100\" size=\"10\" type=\"number\">\n\
        <input type=\"submit\" value=\"Установить\">\n\
        </form><br><br>\n\
        <a href=\"/heating\">\n\
        <button>Назад</button></a>\n\
        </body>\n\
        </html>";

char *tual = "<!DOCTYPE html>\n\
		<html lang=\"en\">\n\
		<head>\n\
		<meta charset=\"UTF-8\">\n\
		<style>\n\
        body {height: 100%;width: 100%;font-size: 20px;overflow-x: hidden;}\n\
        a {text-decoration: none;margin: 20px;display: block;width: 100px;}\n\
        button {line-height: 20px;font-size: 20px;}h1 {text-align: center;width: 100%;}\n\
        input {color: red;font-size: 18px;}#otn-vlag {color: blue;}#temp {color: green;width: 100px;}\n\
        input[type='submit'] {color: white;background-color: green;}\n\
        </style>\n\
        </head>\n\
        <body>\n\
        <h1>Параметры отопления в Туалете</h1>\n\
        <h2>Текущие значения</h2>\n\
        <form action=\"/tual-sumbit\">\n\
        <label for=\"otn-vlag\">Относительная влажность</label>\n\
        <input id=\"otn-vlag\" value=\"0.00\" min=\"0\" max=\"100\"  name=\"otn-vlag\" type=\"text\" disabled=\"disabled\">\n\
        <br><br><label for=\"temp-kom\">Температура в комнате</label>\n\
        <input id=\"temp-kom\" value=\"0.00\" min=\"0\" max=\"100\" name=\"temp-kom\" type=\"text\" disabled=\"disabled\">\n\
        <br><br><label for=\"temp-obr\">Температура обратного контура</label>\n\
        <input id=\"temp-obr\" value=\"0.00\" min=\"0\" max=\"100\" name=\"temp-obr\" type=\"text\" disabled=\"disabled\">\n\
        <br><br><h2>Установка</h2><label for=\"temp\">Температура</label>\n\
        <input id=\"temp\" min=\"0\" max=\"100\" size=\"10\" type=\"number\">\n\
        <input type=\"submit\" value=\"Установить\">\n\
        </form><br><br>\n\
        <a href=\"/heating\">\n\
        <button>Назад</button></a>\n\
        </body>\n\
        </html>";

char *page1 = "<!DOCTYPE html>\n\
		<html>\n\
		<body>\n\
		<h1>ESP8266 USER DATA COLLECTION</h1>\n\
		<h2> DATA STORED Successfully </h2>\n\
		<p> Click Below to Submit again </p>\n\
		<form action=\"/home\">\n\
		<input type=\"submit\" value=\"Submit Again\">\n\
		</form><br><br>\n\
		<form action=\"/page2\">\n\
		<input type=\"submit\" value=\"View Data\">\n\
		</form>\n\
		</body></html>";

char *page2_Top = "<!DOCTYPE html>\n\
		<html>\n\
		<body>\n\
		<h1>ESP8266 USER DATA COLLECTION</h1>\n\
		<h2> DATA CCOLLECTED is Shown BELOW </h2>\n";

char *page2_end = "<p> Click Below to Submit again </p>\n\
		<form action=\"/home\">\n\
		<input type=\"submit\" value=\"Submit again\">\n\
		</body></html>";

char *table = "<style>table {  font-family: arial, sans-serif;\
		border-collapse: collapse;  width: 50%;}\
		td, th {  border: 1px solid #dddddd;\
		text-align: left;  padding: 8px;}tr:nth-child(even)\
		{  background-color: #dddddd;}</style><table><tr><th>Name</th><th>Age</th></tr>";


/*****************************************************************************************************************************************/

void ESP_Init (char *SSID, char *PASSWD, char *STAIP)
{
	char data[80];

	Ringbuf_init();

	Uart_sendstring("AT+RST\r\n");
	HAL_Delay(2000);

	/********* AT **********/
	Uart_flush();
	Uart_sendstring("AT\r\n");
	while(!(Wait_for("OK\r\n")));


	/********* AT+CWMODE=1 **********/
	Uart_flush();
	Uart_sendstring("AT+CWMODE=1\r\n");
	while (!(Wait_for("OK\r\n")));

	/* Set Static IP Address */
	/********* AT+CWSTAIP=IPADDRESS **********/
	Uart_flush();
	sprintf (data, "AT+CIPSTA=\"%s\"\r\n", STAIP);
	Uart_sendstring(data);
	while (!(Wait_for("OK\r\n")));

	/********* AT+CWJAP="SSID","PASSWD" **********/
	Uart_flush();
	sprintf (data, "AT+CWJAP=\"%s\",\"%s\"\r\n", SSID, PASSWD);
	Uart_sendstring(data);
	while (!(Wait_for("OK\r\n")));

	/********* AT+CIPMUX **********/
	Uart_flush();
	Uart_sendstring("AT+CIPMUX=1\r\n");
	while (!(Wait_for("OK\r\n")));

	/********* AT+CIPSERVER **********/
	Uart_flush();
	Uart_sendstring("AT+CIPSERVER=1,80\r\n");
	while (!(Wait_for("OK\r\n")));

}




int Server_Send (char *str, int Link_ID)
{
	int len = strlen (str);
	char data[80];
	Uart_flush();
	sprintf (data, "AT+CIPSEND=%d,%d\r\n", Link_ID, len);
	Uart_sendstring(data);
	while (!(Wait_for(">")));
	Uart_sendstring (str);
	while (!(Wait_for("SEND OK")));
	Uart_flush();
	sprintf (data, "AT+CIPCLOSE=%d\r\n",Link_ID);
	Uart_sendstring(data);
	while (!(Wait_for("OK\r\n")));
	return 1;
}

void Server_Handle (char *str, int Link_ID)
{
	char datatosend[4096] = {0};
	if (!(strcmp (str, "/heating")))
	{
		sprintf(datatosend, heating);
		Server_Send(datatosend, Link_ID);
	}
	//******************************************
	else if (!(strcmp (str, "/zal")))
	{
		char localbuf[2048];
		sprintf(datatosend, page2_Top);
		strcat (datatosend, table);
		int bufsize = (sizeofuser (user));
		for (int i=0; i<bufsize; i++)
		{
			sprintf (localbuf, "<tr><td>%s %s</td>	<td>%s</td></tr>",user[i].firstname,user[i].lastname,user[i].age);
			strcat (datatosend, localbuf);
		}
		strcat (datatosend, "</table>");
		strcat(datatosend, page2_end);
		sprintf(datatosend, zal);
		Server_Send(datatosend, Link_ID);
	}
	//*****************************************
	else if (!(strcmp (str, "/vann")))
	{
		sprintf(datatosend, vann);
		Server_Send(datatosend, Link_ID);
	}
	//*****************************************
	else if (!(strcmp (str, "/kryl")))
	{
		sprintf(datatosend, kryl);
		Server_Send(datatosend, Link_ID);
	}
	//*****************************************
	else if (!(strcmp (str, "/lest")))
	{
		sprintf(datatosend, lest);
		Server_Send(datatosend, Link_ID);
	}
	//*****************************************
	else if (!(strcmp (str, "/ps")))
	{
		sprintf(datatosend, ps);
		Server_Send(datatosend, Link_ID);
	}
	//*****************************************
	else if (!(strcmp (str, "/kotel")))
	{
		sprintf(datatosend, kotel);
		Server_Send(datatosend, Link_ID);
	}
	//*****************************************
	else if (!(strcmp (str, "/dets")))
	{
		sprintf(datatosend, dets);
		Server_Send(datatosend, Link_ID);
	}
	//*****************************************
	else if (!(strcmp (str, "/spal")))
	{
		sprintf(datatosend, spal);
		Server_Send(datatosend, Link_ID);
	}
	//*****************************************
	else if (!(strcmp (str, "/glad")))
	{
		sprintf(datatosend, glad);
		Server_Send(datatosend, Link_ID);
	}
	//*****************************************
	else if (!(strcmp (str, "/tual")))
	{
		sprintf(datatosend, tual);
		Server_Send(datatosend, Link_ID);
	}
	//*****************************************

	else if (!(strcmp (str, "/page2")))
	{
		char localbuf[2048];
		sprintf(datatosend, page2_Top);
		strcat (datatosend, table);
		int bufsize = (sizeofuser (user));
		for (int i=0; i<bufsize; i++)
		{
			sprintf (localbuf, "<tr><td>%s %s</td>	<td>%s</td></tr>",user[i].firstname,user[i].lastname,user[i].age);
			strcat (datatosend, localbuf);
		}
		strcat (datatosend, "</table>");
		strcat(datatosend, page2_end);
		Server_Send(datatosend, Link_ID);
	}
	else
	{
		sprintf (datatosend, home);
		Server_Send(datatosend, Link_ID);
	}

}

void Server_Start (void)
{
	char buftostoreheader[128] = {0};
	char Link_ID;
	while (!(Get_after("+IPD,", 1, &Link_ID)));

	Link_ID -= 48;
	while (!(Copy_upto(" HTTP/1.1", buftostoreheader)));
	if (Look_for("/heating", buftostoreheader) == 1)
	{
//		GetDataFromBuffer("fname=", "&", buftostoreheader, user[usernumber].firstname);
//		GetDataFromBuffer("lname=", "&", buftostoreheader, user[usernumber].lastname);
//		GetDataFromBuffer("age=", " HTTP", buftostoreheader, user[usernumber].age);
//		usernumber++;
//		if (usernumber >9) usernumber = 0;
		Server_Handle("/heating",Link_ID);
	}
	//**************************************************
	else if (Look_for("/zal", buftostoreheader) == 1)
	{
		Server_Handle("/zal",Link_ID);
	}
	//**************************************************
	else if (Look_for("/vann", buftostoreheader) == 1)
	{
		Server_Handle("/vann",Link_ID);
	}
	//*************************************************
	else if (Look_for("/kryl", buftostoreheader) == 1)
	{
		Server_Handle("/kryl",Link_ID);
	}
	//*************************************************
	else if (Look_for("/lest", buftostoreheader) == 1)
	{
		Server_Handle("/lest",Link_ID);
	}
	//*************************************************
	else if (Look_for("/ps", buftostoreheader) == 1)
	{
		Server_Handle("/ps",Link_ID);
	}
	//*************************************************
	else if (Look_for("/kotel", buftostoreheader) == 1)
	{
		Server_Handle("/kotel",Link_ID);
	}
	//*************************************************
	else if (Look_for("/dets", buftostoreheader) == 1)
	{
		Server_Handle("/dets",Link_ID);
	}
	//*************************************************
	else if (Look_for("/spal", buftostoreheader) == 1)
	{
		Server_Handle("/spal",Link_ID);
	}
	//*************************************************
	else if (Look_for("/glad", buftostoreheader) == 1)
	{
		Server_Handle("/glad",Link_ID);
	}
	//*************************************************
	else if (Look_for("/tual", buftostoreheader) == 1)
	{
		Server_Handle("/tual",Link_ID);
	}
	//*************************************************
	else if (Look_for("/zal-sumbit", buftostoreheader) == 1)
	{
		GetDataFromBuffer("temp=", "&", buftostoreheader, user[usernumber].firstname);
		Server_Handle("/zal",Link_ID);
	}
	//*************************************************
	else if (Look_for("/vann-sumbit", buftostoreheader) == 1)
	{
		GetDataFromBuffer("temp=", "&", buftostoreheader, user[usernumber].firstname);
		Server_Handle("/vann",Link_ID);
	}
	//*************************************************
	else if (Look_for("/kryl-sumbit", buftostoreheader) == 1)
	{
		GetDataFromBuffer("temp=", "&", buftostoreheader, user[usernumber].firstname);
		Server_Handle("/kryl",Link_ID);
	}
	//*************************************************
	else if (Look_for("/lest-sumbit", buftostoreheader) == 1)
	{
		GetDataFromBuffer("temp=", "&", buftostoreheader, user[usernumber].firstname);
		Server_Handle("/lest",Link_ID);
	}
	//*************************************************
	else if (Look_for("/ps-sumbit", buftostoreheader) == 1)
	{
		GetDataFromBuffer("temp=", "&", buftostoreheader, user[usernumber].firstname);
		Server_Handle("/ps",Link_ID);
	}
	//*************************************************
	else if (Look_for("/kotel-sumbit", buftostoreheader) == 1)
	{
		GetDataFromBuffer("temp=", "&", buftostoreheader, user[usernumber].firstname);
		Server_Handle("/kotel",Link_ID);
	}
	//*************************************************
	else if (Look_for("/dets-sumbit", buftostoreheader) == 1)
	{
		GetDataFromBuffer("temp=", "&", buftostoreheader, user[usernumber].firstname);
		Server_Handle("/dets",Link_ID);
	}
	//*************************************************
	else if (Look_for("/spal-sumbit", buftostoreheader) == 1)
	{
		GetDataFromBuffer("temp=", "&", buftostoreheader, user[usernumber].firstname);
		Server_Handle("/spal",Link_ID);
	}
	//*************************************************
	else if (Look_for("/glad-sumbit", buftostoreheader) == 1)
	{
		GetDataFromBuffer("temp=", "&", buftostoreheader, user[usernumber].firstname);
		Server_Handle("/glad",Link_ID);
	}
	//*************************************************
	else if (Look_for("/tual-sumbit", buftostoreheader) == 1)
	{
		GetDataFromBuffer("temp=", "&", buftostoreheader, user[usernumber].firstname);
		Server_Handle("/tual",Link_ID);
	}
	//*************************************************

	else if (Look_for("/page2", buftostoreheader) == 1)
	{
		Server_Handle("/page2",Link_ID);
	}

	else if (Look_for("/home", buftostoreheader) == 1)
	{
		Server_Handle("/home",Link_ID);
	}

	else if (Look_for("/favicon.ico", buftostoreheader) == 1);

	else
	{
		Server_Handle("/ ", Link_ID);
	}
}



