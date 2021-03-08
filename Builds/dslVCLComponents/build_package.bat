@SET BDS=C:\EMB\20.0
@SET BDSINCLUDE=C:\EMB\20.0\include
@SET BDSCOMMONDIR=C:\build\10.3
@SET BUILD=C:\build\10.3
@SET FrameworkDir=C:\Windows\Microsoft.NET\Framework\v4.0.30319
@SET FrameworkVersion=v4.5
@SET FrameworkSDKDir=
@SET PATH=%FrameworkDir%;%FrameworkSDKDir%;C:\EMB\20.0\bin;C:\EMB\20.0\bin64;C:\EMB\20.0\cmake;C:\Users\Public\Documents\Embarcadero\InterBase\redist\InterBase2020\IDE_spoof;%PATH%
@SET LANGDIR=EN
@SET PLATFORM=
@SET PlatformSDK=

REM msbuild.exe
msbuild.exe -t:build -p:OutDir=%BUILD% -p:config=Debug dslVCLComponents.cbproj


