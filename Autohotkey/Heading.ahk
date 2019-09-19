;******************** Initialization  ********************************************

Gui, Color, black
Gui -Caption
Gui, Show, x0 y0 w3840 h2160
SystemCursor(0)
WinHide, ahk_class Shell_TrayWnd
WinHide, Start ahk_class Button,
existtest := 1

FileArray := [] 
NumberArray := []
NumberArrayIndexer := 0
Isitempty := 0


RunWait, cmd /c python "%userprofile%\Dropbox\FCBC Missions Map\Python\Heading.py" , , hide





; hide the cursor
SystemCursor(OnOff=0)   ; INIT = "I","Init"; OFF = 0,"Off"; TOGGLE = -1,"T","Toggle"; ON = others
{
   static AndMask, XorMask, $, h_cursor
      ,c0,c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11,c12,c13  ; system cursors
        , b1,b2,b3,b4,b5,b6,b7,b8,b9,b10,b11,b12,b13  ; blank cursors
        , h1,h2,h3,h4,h5,h6,h7,h8,h9,h10,h11,h12,h13  ; handles of default cursors
   if (OnOff = "Init" or OnOff = "I" or $ = "")       ; init when requested or at first call
   {
      $ = h                                           ; active default cursors
      VarSetCapacity( h_cursor,4444, 1 )
      VarSetCapacity( AndMask, 32*4, 0xFF )
      VarSetCapacity( XorMask, 32*4, 0 )
      system_cursors = 32512,32513,32514,32515,32516,32642,32643,32644,32645,32646,32648,32649,32650
      StringSplit c, system_cursors, `,
      Loop %c0%
      {
         h_cursor   := DllCall( "LoadCursor", "uint",0, "uint",c%A_Index% )
         h%A_Index% := DllCall( "CopyImage",  "uint",h_cursor, "uint",2, "int",0, "int",0, "uint",0 )
         b%A_Index% := DllCall("CreateCursor","uint",0, "int",0, "int",0
                             , "int",32, "int",32, "uint",&AndMask, "uint",&XorMask )
      }
   }
   if (OnOff = 0 or OnOff = "Off" or $ = "h" and (OnOff < 0 or OnOff = "Toggle" or OnOff = "T"))
      $ = b       ; use blank cursors
   else
      $ = h       ; use the saved cursors

   Loop %c0%
   {
      h_cursor := DllCall( "CopyImage", "uint",%$%%A_Index%, "uint",2, "int",0, "int",0, "uint",0 )
      DllCall( "SetSystemCursor", "uint",h_cursor, "uint",c%A_Index% )
   }
}


#x::
{
   SystemCursor(1)
   sleep 1000
    WinShow, ahk_class Shell_TrayWnd
    WinShow, Start ahk_class Button
    sleep 1000
ExitApp 
}

f7:: 
{
  SplashImage , ,b1 cw191919 ct9acd32, %A_ScriptName%, Reloaded
  Sleep,750
  Reload
return
}

/*

Send %lightsettings%
sleep 300
Send +u
Loop 10000
{
TestforFinish()
Scanfolders()
Random, number, 1, % totaleducation
randomfile := % FilearrayEducation[number]  ; select a random file
SplitPath, randomfile, OutFileName, OutDir, OutExtension, OutNameNoExt, OutDrive ; split into parts
FileRead, lightsettings, E:\Dropbox\FCBC Missions Map\Light Settings\%OutNameNoExt%.txt ; get the light settings
sleep 300
FileAppend, %OutFileName%, Z:\Public\Public Scans\videotoplay.txt ; send to slave the headervideoname
sleep 300
existtest := 1
SetTitleMatchMode, 2
WinActivate, Q Light ; set lights
Send %lightsettings%
sleep 500
Send +u
WinActivate, Q Light ; set lights

sleep 1000 ; give dropbox a headstart
;msgbox %totaleducation%
runwait, cmd /c ffplay "%randomfile%" -fs -autoexit, , hide ; play the video
FileMove %randomfile%, E:\EducationPlayed\ 
sleep 1000
WinActivate, Q Light ; turn off scene when video is done
Send +u
sleep 500
Send %lightsettings%



*/