Name "Color Detection"
OutFile "ColorDetectionInstaller.exe"
InstallDir "$PROGRAMFILES64\ColorDetection"
RequestExecutionLevel admin

Page directory
Page instfiles
UninstPage instfiles

Section "Install"
    SetOutPath "$INSTDIR"

    File "release\colorDetection.exe"
    File "release\libgcc_s_seh-1.dll"
    File "release\libstdc++-6.dll"
    File "release\libwinpthread-1.dll"
    File "release\libopencv_core-412.dll"
    File "release\libopencv_highgui-412.dll"
    File "release\libopencv_videoio-412.dll"
    File "release\libopencv_imgproc-412.dll"
    File "release\libopencv_imgcodecs-412.dll"
    File "release\Qt6Core.dll"
    File "release\Qt6Gui.dll"
    File "release\Qt6Widgets.dll"
    File "release\Qt6OpenGL.dll"
    File "release\Qt6OpenGLWidgets.dll"
    File "release\zlib1.dll"
    File "release\libtbb12.dll"
    File "release\libfreetype-6.dll"
    File "release\avcodec-61.dll"
    File "release\avformat-61.dll"
    File "release\avutil-59.dll"
    File "release\swscale-8.dll"
    File "release\swresample-5.dll"
    File "release\libpng16-16.dll"
    File "release\libjpeg-8.dll"
    File "release\libgomp-1.dll"
    File "release\libgstreamer-1.0-0.dll"
    File "release\libgstapp-1.0-0.dll"
    File "release\libgstaudio-1.0-0.dll"
    File "release\libgstvideo-1.0-0.dll"
    File "release\libgstbase-1.0-0.dll"
    File "release\libgstpbutils-1.0-0.dll"

    SetOutPath "$INSTDIR\platforms"
    File "release\platforms\qwindows.dll"

    SetOutPath "$INSTDIR"

    ; Create instructions text file
    FileOpen $0 "$INSTDIR\INSTRUCTIONS.txt" w
    FileWrite $0 "Color Detection - Instructions$\r$\n"
    FileWrite $0 "==============================$\r$\n$\r$\n"
    FileWrite $0 "1. Run colorDetection.exe$\r$\n"
    FileWrite $0 "2. Press ESC to exit$\r$\n"
    FileClose $0

    CreateShortcut "$DESKTOP\ColorDetection.lnk" "$INSTDIR\colorDetection.exe"
    CreateDirectory "$SMPROGRAMS\ColorDetection"
    CreateShortcut "$SMPROGRAMS\ColorDetection\ColorDetection.lnk" "$INSTDIR\colorDetection.exe"

    WriteUninstaller "$INSTDIR\Uninstall.exe"

    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\ColorDetection" \
        "DisplayName" "Color Detection"
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\ColorDetection" \
        "UninstallString" "$INSTDIR\Uninstall.exe"
SectionEnd

Section "Uninstall"
    Delete "$INSTDIR\colorDetection.exe"
    Delete "$INSTDIR\instructions.txt"
    Delete "$INSTDIR\*.dll"
    Delete "$INSTDIR\platforms\*.*"
    Delete "$INSTDIR\Uninstall.exe"
    RMDir "$INSTDIR\platforms"
    RMDir "$INSTDIR"
    Delete "$DESKTOP\ColorDetection.lnk"
    Delete "$SMPROGRAMS\ColorDetection\ColorDetection.lnk"
    RMDir "$SMPROGRAMS\ColorDetection"
    DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\ColorDetection"
SectionEnd