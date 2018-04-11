#include <LiquidCrystal_I2C.h>

// Dung vidu cua https://arduino-info.wikispaces.com/LCD-Pushbuttons
#include <Wire.h> 
#include <DS3231.h>
#include <DHT_U.h>

LiquidCrystal_I2C lcd(0x3F, 16, 2);
DS3231 clock;
RTCDateTime dt;
signed char tsecond, tminute, thour, tday, twday, tmonth;
int tyear;
void HienThiThoiGian(void);
int read_LCD_buttons(void);
int key;
int adc_key_in    = 0;
int adc_key_prev  = 0;
#define btnRIGHT  0
#define btnLEFT 1
#define btnUP   2
#define btnDOWN   3
#define btnSELECT 4
#define btnNONE   5
void setup() 
{
	lcd.begin();                              // set up the LCD's number of columns and rows (16x2)
	lcd.backlight();
	lcd.setCursor(0, 0);
	clock.begin();
	Wire.begin();
	dt = clock.getDateTime();
	tsecond = dt.second;
	tminute = dt.minute;
	thour = dt.hour;
	twday = dt.dayOfWeek;
	tday = dt.day;
	tmonth = dt.month;
	tyear = dt.year;
}

void loop() 
{
	// put your main code here, to run repeatedly:
	byte CheDo =0;
	adc_key_prev = key;       // Looking for changes
	key = read_LCD_buttons();  // read the buttons
	while (1)
	{
		adc_key_prev = key;
		key = read_LCD_buttons();
		HienThiThoiGian();

		if (key == btnSELECT)
		{
			CheDo = 1;
			lcd.clear();
		}
		//cai dat gio
		while (CheDo == 1)
		{
			lcd.setCursor(0, 0);
			lcd.print("Setting Hour");
			lcd.setCursor(0, 1);
			lcd.print(thour);
			adc_key_prev = key;
			key = read_LCD_buttons();
			if (key == btnUP)
			{
				thour += 1;
				if (thour > 23)
				{
					thour = 0;
				}
				// Manual (YYYY, MM, DD, HH, II, SS
				clock.setDateTime(tyear, tmonth, tday, thour, tminute, tsecond);
			}
			if (key == btnDOWN)
			{
				thour -= 1;
				if (thour < 0)
				{
					thour = 23;
				}
				clock.setDateTime(tyear, tmonth, tday, thour, tminute, tsecond);
			}
			if (key == btnSELECT)
			{
				CheDo += 1;
				if (CheDo > 7)
				{
					CheDo = 0;
				}
				lcd.clear();
			}
		}//end CheDo 1

			//Cai dat phut
		while (CheDo == 2)
		{
			lcd.setCursor(0, 0);
			lcd.print("Setting Minute");
			lcd.setCursor(0, 1);
			lcd.print(tminute);
			adc_key_prev = key;
			key = read_LCD_buttons();
			if (key == btnUP)
			{
				tminute += 1;
				if (tminute > 59)
				{
					tminute = 0;
				}
				// Manual (YYYY, MM, DD, HH, II, SS
				clock.setDateTime(tyear, tmonth, tday, thour, tminute, tsecond);
			}
			if (key == btnDOWN)
			{
				tminute -= 1;
				if (tminute < 0)
				{
					tminute = 59;
				}
				clock.setDateTime(tyear, tmonth, tday, thour, tminute, tsecond);
			}
			if (key == btnSELECT)
			{
				CheDo += 1;
				if (CheDo > 7)
				{
					CheDo = 0;
				}
				lcd.clear();
			}
		}//end CheDo 2


		//--------------cai dat giay-----------------
		while (CheDo == 3)
		{
			lcd.setCursor(0, 0);
			lcd.print("Setting Secound");
			lcd.setCursor(0, 1);
			lcd.print(tsecond);
			adc_key_prev = key;
			key = read_LCD_buttons();

			if (key == btnUP)
			{
				tsecond += 1;
				if (tsecond > 59)
				{
					tsecond = 0;
				}
				// Manual (YYYY, MM, DD, HH, II, SS
				clock.setDateTime(tyear, tmonth, tday, thour, tminute, tsecond);
			}
			if (key == btnDOWN)
			{
				tsecond -= 1;
				if (tsecond < 0)
				{
					tsecond = 59;
				}
				clock.setDateTime(tyear, tmonth, tday, thour, tminute, tsecond);
			}
			if (key == btnSELECT)
			{
				CheDo += 1;
				if (CheDo > 7)
				{
					CheDo = 0;
				}
				lcd.clear();
			}
		}

		//--------------Cai dat ngay---------------
		while (CheDo == 4)//che do cai ngay
		{
			lcd.setCursor(0, 0);
			lcd.print("Setting day");
			lcd.setCursor(0, 1);
			lcd.print(tday);
			adc_key_prev = key;
			key = read_LCD_buttons();

			if (key == btnUP)//neu nhan nut nhan
			{
				tday = tday + 1;
				if (tday > 31)
				{
					tday = 0;
				}
				clock.setDateTime(tyear, tmonth, tday, thour, tminute, tsecond);
			}
			if (key == btnDOWN)//neu nhan nut nhan
			{
				tday = tday - 1;
				if (tday < 0)
				{
					tday = 31;
				}
				clock.setDateTime(tyear, tmonth, tday, thour, tminute, tsecond);
			}
			if (key == btnSELECT)//neu nhan nut
			{
				CheDo = CheDo + 1;//chuyen sang che do cai dat khac
				if (CheDo > 7)
				{
					CheDo = 0;
				}
				lcd.clear();//xoa man hinh LCD
			}

		}

		//-------cai dat thang---------------------------
		while (CheDo == 5)//che do cai thang
		{
			lcd.setCursor(0, 0);
			lcd.print("Setting Month");
			lcd.setCursor(0, 1);
			lcd.print(tmonth);
			adc_key_prev = key;
			key = read_LCD_buttons();
			if (key == btnUP)//neu nhan nut nhan
			{
				tmonth = tmonth + 1;
				if (tmonth > 12)
				{
					tmonth = 1;
				}
				clock.setDateTime(tyear, tmonth, tday, thour, tminute, tsecond);
			}
			if (key == btnDOWN)//neu nhan nut nhan
			{
				tmonth = tmonth - 1;
				if (tmonth < 1)
				{
					tmonth = 12;
				}
				clock.setDateTime(tyear, tmonth, tday, thour, tminute, tsecond);
			}
			if (key == btnSELECT)//neu nhan nut
			{
				CheDo = CheDo + 1;//chuyen sang che do cai dat khac
				if (CheDo > 7)
				{
					CheDo = 0;
				}
				lcd.clear();//xoa man hinh LCD
			}
		}

		//----------------- Cai dat nam---------
		while (CheDo == 6)//che do cai nam
		{
			lcd.setCursor(0, 0);
			lcd.print("Setting Year");
			lcd.setCursor(0, 1);
			lcd.print(tyear);
			adc_key_prev = key;
			key = read_LCD_buttons();
			if (key == btnUP)//neu nhan nut nhan
			{
				tyear = tyear + 1;
				clock.setDateTime(tyear, tmonth, tday, thour, tminute, tsecond);
			}
			if (key == btnDOWN)//neu nhan nut nhan
			{
				tyear = tyear - 1;
				if (tyear < 2000)
				{
					tyear = 2017;
				}
				clock.setDateTime(tyear, tmonth, tday, thour, tminute, tsecond);
			}
			if (key == btnSELECT)//neu nhan nut
			{
				CheDo = CheDo + 1;//chuyen sang che do cai dat khac
				if (CheDo > 7)
				{
					CheDo = 0;
				}
				lcd.clear();//xoa man hinh LCD
			}
		}
		while (CheDo == 7)//che do cai thu ngay
		{
			lcd.setCursor(0, 0);
			lcd.print("Setting date");
			lcd.setCursor(0, 1);
			//lcd.print("CHE DO CAI THU NGAY");
			//lcd.setCursor(0, 2);
			//lcd.print("THU:");

			//lcd.print(ThuNgay[wday]);     
			//_HienThiSo(wday);
			//String ThuNgay[7]={"CHU NHAT","THU HAI","THU BA", "THU TU", "THU NAM", "THU SAU","THU BAY"};
			switch (twday)
			{
			case 1:
			{
				lcd.print("Monday  ");
				break;//thoat khoi cau truc switch
			}
			case 2:
			{
				lcd.print("Tuesday   ");
				break;//thoat khoi cau truc switch
			}
			case 3:
			{
				lcd.print("wednesday   ");
				break;//thoat khoi cau truc switch
			}
			case 4:
			{
				lcd.print("thursday   ");
				break;//thoat khoi cau truc switch
			}
			case 5:
			{
				lcd.print("friday   ");
				break;//thoat khoi cau truc switch
			}
			case 6:
			{
				lcd.print("Saturday   ");
				break;//thoat khoi cau truc switch
			}
			case 7:
			{
				lcd.print("Sunday   ");
				break;//thoat khoi cau truc switch
			}
			default://khi khong co truong hop o tren nao dung thi vo day
			{
				//co the viet them gi do neu thich
				break;
			}
			}
			adc_key_prev = key;
			key = read_LCD_buttons();
			if (key == btnUP)//neu nhan nut nhan
			{
				twday = twday + 1;
				if (twday > 7)
				{
					twday = 1;
				}
			}
			if (key == btnDOWN)//neu nhan nut nhan
			{
				twday = twday - 1;
				if (twday < 1)
				{
					twday = 7;
				}
			}
			if (key == btnSELECT)//neu nhan nut
			{
				CheDo = CheDo + 1;//chuyen sang che do cai dat khac
				if (CheDo > 7)
				{
					CheDo = 0;
				}
				lcd.clear();//xoa man hinh LCD
			}
		}
	}
}

void HienThiThoiGian(void)
	{
		dt = clock.getDateTime();
		lcd.setCursor(0, 0);
		lcd.print(clock.dateFormat("d-m-Y", dt));
		lcd.print("  ");
		switch (twday)
		{
		case 1:
		{
			lcd.print("Mon");
			break;//thoat khoi cau truc switch
		}
		case 2:
		{
			lcd.print("Tue");
			break;//thoat khoi cau truc switch
		}
		case 3:
		{
			lcd.print("wed");
			break;//thoat khoi cau truc switch
		}
		case 4:
		{
			lcd.print("thu");
			break;//thoat khoi cau truc switch
		}
		case 5:
		{
			lcd.print("fri");
			break;//thoat khoi cau truc switch
		}
		case 6:
		{
			lcd.print("Sat");
			break;//thoat khoi cau truc switch
		}
		case 7:
		{
			lcd.print("Sun");
			break;//thoat khoi cau truc switch
		}
		default://khi khong co truong hop o tren nao dung thi vo day
		{
			//co the viet them gi do neu thich
			break;
		}
		}
		lcd.setCursor(0, 1);
		lcd.print(clock.dateFormat("H:i:s", dt));
   lcd.setCursor(9,1);
   lcd.print("T");
   lcd.setCursor(10,1);
   lcd.write(58);
   clock.forceConversion();
   lcd.print(clock.readTemperature());   
	}


	int read_LCD_buttons(void)
	{
		adc_key_in = analogRead(0);      // read the value from the sensor 
		delay(60); //switch debounce delay. Increase this delay if incorrect switch selections are returned.
		int k = (analogRead(0) - adc_key_in); //gives the button a slight range to allow for a little contact resistance noise
		if (5 < abs(k))
		{
			return btnNONE;
		}  // double checks the keypress. If the two readings are not equal +/-k value after debounce delay, it tries again.
		if (adc_key_in > 1000) return btnNONE; // We make this the 1st option for speed reasons since it will be the most likely result
		if (adc_key_in < 50)   return btnRIGHT;
		if (adc_key_in < 195)  return btnLEFT;
		if (adc_key_in < 380)  return btnUP;
		if (adc_key_in < 555)  return btnDOWN;
		if (adc_key_in < 790)  return btnSELECT;
		return btnNONE;  // when all others fail, return this...
	}

