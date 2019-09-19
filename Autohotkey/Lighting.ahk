;Msgbox %1%
FileRead, lightsettings, %1% ; get the light settings
;MsgBox, %lightsettings%
sleep 300
SetTitleMatchMode, 2
IfWinExist ahk_class Qt5QWindowIcon
{
WinActivate ; set lights
sleep 500
Send %lightsettings%
}
IfWinNotExist, ahk_class Qt5QWindowIcon
{
Run	C:\QLC+\qlcplus.exe -o "C:\Users\Missions\Dropbox\FCBC Missions Map\MissionsLighting.qxw" -p -k
}