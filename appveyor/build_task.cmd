@echo off
setlocal enableextensions enabledelayedexpansion

	cd /D %APPVEYOR_BUILD_FOLDER%
	if %errorlevel% neq 0 exit /b 3

	set STABILITY=staging
	set DEPS_DIR=%PHP_BUILD_CACHE_BASE_DIR%\deps-%PHP_REL%-%PHP_SDK_VC%-%PHP_SDK_ARCH%
	rem SDK is cached, deps info is cached as well
	echo Updating dependencies in %DEPS_DIR%
	cmd /c phpsdk_deps --update --no-backup --branch %PHP_REL% --stability %STABILITY% --deps %DEPS_DIR% --crt %PHP_BUILD_CRT%
	if %errorlevel% neq 0 exit /b 3

	rem Something went wrong, most likely when concurrent builds were to fetch deps
	rem updates. It might be, that some locking mechanism is needed.
	if not exist "%DEPS_DIR%" (
		cmd /c phpsdk_deps --update --force --no-backup --branch %PHP_REL% --stability %STABILITY% --deps %DEPS_DIR% --crt %PHP_BUILD_CRT%
	)
	if %errorlevel% neq 0 exit /b 3

	for %%z in (%ZTS_STATES%) do (
		set ZTS_STATE=%%z
		if "!ZTS_STATE!"=="enable" set ZTS_SHORT=ts
		if "!ZTS_STATE!"=="disable" set ZTS_SHORT=nts

		cd /d C:\projects\php-src

		cmd /c buildconf.bat --force

		if %errorlevel% neq 0 exit /b 3

		cmd /c configure.bat --disable-all --enable-cli --!ZTS_STATE!-zts --enable-action_at_a_distance=shared --enable-object-out-dir=%PHP_BUILD_OBJ_DIR% --with-config-file-scan-dir=%APPVEYOR_BUILD_FOLDER%\build\modules.d --with-prefix=%APPVEYOR_BUILD_FOLDER%\build --with-php-build=%DEPS_DIR%

		if %errorlevel% neq 0 exit /b 3

		nmake /NOLOGO

		if %errorlevel% neq 0 exit /b 3

		nmake install

		if %errorlevel% neq 0 exit /b 3

		nmake test TESTS="%APPVEYOR_BUILD_FOLDER%\build\ext\tests\basic\"

		if %errorlevel% neq 0 exit /b 3

		cd /d %APPVEYOR_BUILD_FOLDER%

		if not exist "%APPVEYOR_BUILD_FOLDER%\build\ext\php_action_at_a_distance.dll" exit /b 3

		rem xcopy %APPVEYOR_BUILD_FOLDER%\LICENSE %APPVEYOR_BUILD_FOLDER%\php_action_at_a_distance-%PHP_REL%-!ZTS_SHORT!-%PHP_BUILD_CRT%-%PHP_SDK_ARCH%\ /y /f
		xcopy %APPVEYOR_BUILD_FOLDER%\docs %APPVEYOR_BUILD_FOLDER%\php_action_at_a_distance-%PHP_REL%-!ZTS_SHORT!-%PHP_BUILD_CRT%-%PHP_SDK_ARCH%\docs\ /y /f
		xcopy %APPVEYOR_BUILD_FOLDER%\php %APPVEYOR_BUILD_FOLDER%\php_action_at_a_distance-%PHP_REL%-!ZTS_SHORT!-%PHP_BUILD_CRT%-%PHP_SDK_ARCH%\examples\ /y /f
		rem xcopy %APPVEYOR_BUILD_FOLDER%\build\ext\php_action_at_a_distance.dll %APPVEYOR_BUILD_FOLDER%\php_action_at_a_distance-%PHP_REL%-!ZTS_SHORT!-%PHP_BUILD_CRT%-%PHP_SDK_ARCH%\ /y /f
		xcopy %APPVEYOR_BUILD_FOLDER%\build\ext\*.dll %APPVEYOR_BUILD_FOLDER%\php_action_at_a_distance-%PHP_REL%-!ZTS_SHORT!-%PHP_BUILD_CRT%-%PHP_SDK_ARCH%\ /y /f
		7z a php_action_at_a_distance-%PHP_REL%-!ZTS_SHORT!-%PHP_BUILD_CRT%-%PHP_SDK_ARCH%.zip %APPVEYOR_BUILD_FOLDER%\php_action_at_a_distance-%PHP_REL%-!ZTS_SHORT!-%PHP_BUILD_CRT%-%PHP_SDK_ARCH%\*
		appveyor PushArtifact php_action_at_a_distance-%PHP_REL%-!ZTS_SHORT!-%PHP_BUILD_CRT%-%PHP_SDK_ARCH%.zip -FileName php_action_at_a_distance-%APPVEYOR_REPO_TAG_NAME%-%PHP_REL%-!ZTS_SHORT!-%PHP_BUILD_CRT%-%PHP_SDK_ARCH%.zip

		move build\ext\php_action_at_a_distance.dll artifacts\php_action_at_a_distance-%PHP_REL%-!ZTS_SHORT!-%PHP_BUILD_CRT%-%PHP_SDK_ARCH%.dll
	)
endlocal
