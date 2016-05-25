	//
	//  ConsoleColour.h
	//  Virtual File System
	//
	//  Created by ئ‍ارسلان ئابلىكىم on 5/15/16.
	//  Copyright © 2016 BUPT. All rights reserved.
	//

#ifndef ConsoleColour_h
#define ConsoleColour_h

#ifdef _WIN32 || _WIN64 // Disable colouring for windows because windows doesnt support it!

#define ConsoleattributesOff "" //All attributes off(color at startup)
#define ConsoleBold "" //Bold on(enable foreground intensity)
#define ConsoleUnderline "" //Underline on
#define ConsoleBlink "" //Blink on(enable background intensity)
#define ConsoleBoldOff "" //Bold off(disable foreground intensity)
#define ConsoleUnderlineOff "" //Underline off
#define ConsoleBlinkOff "" //Blink off(disable background intensity)
								   //forground
#define ConsoleForeBlack "" //Black
#define ConsoleForeRed "" //Red
#define ConsoleForeGreen "" //Green
#define ConsoleForeYellow "" //Yellow
#define ConsoleForeBlue "" //Blue
#define ConsoleForeMagenta "" //Magenta
#define ConsoleForeCyan "" //Cyan
#define ConsoleForeWhite "" //White
#define ConsoleForeDefault "" //Default(foreground color at startup)
#define ConsoleForeLightGray "" //Light Gray
#define ConsoleForeLightRed "" //Light Red
#define ConsoleForeLightGreen "" //Light Green
#define ConsoleForeLightYellow "" //Light Yellow
#define ConsoleForeLightBlue "" //Light Blue
#define ConsoleForeLightMagenta "" //Light Magenta
#define ConsoleForeLightCyan "" //Light Cyan
#define ConsoleForeLightWhite "" //Light White
										 //background
#define ConsoleBackBlack "" //Black
#define ConsoleBackRed "" //Red
#define ConsoleBackGreen "" //Green
#define ConsoleBackYellow "" //Yellow
#define ConsoleBackBlue "" //Blue
#define ConsoleBackMagenta "" //Magenta
#define ConsoleBackCyan "" //Cyan
#define ConsoleBackWhite "" //White
#define ConsoleBackDefault "" //Default(background color at startup)
#define ConsoleBackLightGray "" //Light Gray
#define ConsoleBackLightRed "" //Light Red
#define ConsoleBackLightGreen "" //Light Green
#define ConsoleBackLightYellow "" //Light Yellow
#define ConsoleBackLightBlue "" //Light Blue
#define ConsoleBackLightMagenta "" //Light Magenta
#define ConsoleBackLightCyan "" //Light Cyan
#define ConsoleBackLightWhite "" //Light White

#else

#define ConsoleattributesOff "\x1b[0m" //All attributes off(color at startup)
#define ConsoleBold "\x1b[1m" //Bold on(enable foreground intensity)
#define ConsoleUnderline "\x1b[4m" //Underline on
#define ConsoleBlink "\x1b[5m" //Blink on(enable background intensity)
#define ConsoleBoldOff "\x1b[21m" //Bold off(disable foreground intensity)
#define ConsoleUnderlineOff "\x1b[24m" //Underline off
#define ConsoleBlinkOff "\x1b[25m" //Blink off(disable background intensity)
								   //forground
#define ConsoleForeBlack "\x1b[30m" //Black
#define ConsoleForeRed "\x1b[31m" //Red
#define ConsoleForeGreen "\x1b[32m" //Green
#define ConsoleForeYellow "\x1b[33m" //Yellow
#define ConsoleForeBlue "\x1b[34m" //Blue
#define ConsoleForeMagenta "\x1b[35m" //Magenta
#define ConsoleForeCyan "\x1b[36m" //Cyan
#define ConsoleForeWhite "\x1b[37m" //White
#define ConsoleForeDefault "\x1b[39m" //Default(foreground color at startup)
#define ConsoleForeLightGray "\x1b[90m" //Light Gray
#define ConsoleForeLightRed "\x1b[91m" //Light Red
#define ConsoleForeLightGreen "\x1b[92m" //Light Green
#define ConsoleForeLightYellow "\x1b[93m" //Light Yellow
#define ConsoleForeLightBlue "\x1b[94m" //Light Blue
#define ConsoleForeLightMagenta "\x1b[95m" //Light Magenta
#define ConsoleForeLightCyan "\x1b[96m" //Light Cyan
#define ConsoleForeLightWhite "\x1b[97m" //Light White
										 //background
#define ConsoleBackBlack "\x1b[40m" //Black
#define ConsoleBackRed "\x1b[41m" //Red
#define ConsoleBackGreen "\x1b[42m" //Green
#define ConsoleBackYellow "\x1b[43m" //Yellow
#define ConsoleBackBlue "\x1b[44m" //Blue
#define ConsoleBackMagenta "\x1b[45m" //Magenta
#define ConsoleBackCyan "\x1b[46m" //Cyan
#define ConsoleBackWhite "\x1b[47m" //White
#define ConsoleBackDefault "\x1b[49m" //Default(background color at startup)
#define ConsoleBackLightGray "\x1b[100m" //Light Gray
#define ConsoleBackLightRed "\x1b[101m" //Light Red
#define ConsoleBackLightGreen "\x1b[102m" //Light Green
#define ConsoleBackLightYellow "\x1b[103m" //Light Yellow
#define ConsoleBackLightBlue "\x1b[104m" //Light Blue
#define ConsoleBackLightMagenta "\x1b[105m" //Light Magenta
#define ConsoleBackLightCyan "\x1b[106m" //Light Cyan
#define ConsoleBackLightWhite "\x1b[107m" //Light White

#endif /* if not windows */

#endif /* ConsoleColour_h */
