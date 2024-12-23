# linux_deployment
Humongously simple Qt app packaged for distribution across machines running the same platform as the one it was compiled on (Linux)

# Resources
**Deployment:**
- https://www.youtube.com/watch?v=Y0MSOQGv5N4
- https://stackoverflow.com/questions/49982419/how-to-release-a-qt-c-application-on-linux-and-windows
- https://www.youtube.com/watch?v=PDzlT_ODpM8&ab_channel=probono
- https://github.com/probonopd/linuxdeployqt/issues/377
---

There are several ways to deploy your application:

<h2>windeployqt/linuxdeployqt</h2>

The tools windeployqt or linuxdeployqt (which is 3rd-party) will copy all required dependencies to an executable folder, ready to run on another machine.

Steps:
- Compile the binary in release mode, e.g. the executable path inside the build folder is `app_path='/opt/app/build/Desktop_Qt_6_8_1-Release/app'`
- Set the Qt environment variable, e.g. `export PATH=/opt/Qt/6.8.1/gcc_64/bin/:$PATH`
- Run linuxdeployqt: `./linuxdeployqt-continuous-x86_64.AppImage $app_path -appimage`
- If `ERROR: The host system is too new` appears, add the flag `-unsupported-allow-new-glibc` o `-unsupported-bundle-everything` to the previous command
- All libraries required to run the application on another computer are copied to to the application folder
- The app can be distributed as an AppDir or AppImage

<h3>Notes</h3>

- One needs a .desktop file and an icon, but it can be automatically created 
- If the AppImage is not generated, it is possible that the distribution is too new to use linuxdeployqt, see https://github.com/probonopd/linuxdeployqt/issues/340

<h3>To install linuxdeployqt:</h3>

- Build from source https://github.com/probonopd/linuxdeployqt
- Or install the AppImage from https://github.com/probonopd/linuxdeployqt/releases and `chmod a+x` to permit execution.

<h2>Similar tools</h2>

If linuxdeployqt does not work, another workaroung is to try appimage-builder or go-appimage

<h3>appimage-builder</h3>

Can be downloaded form [here](https://github.com/AppImageCrafters/appimage-builder)

<h3>go-appimage</h3>

Can be downloaded form [here](https://github.com/probonopd/go-appimage/tree/master/src/appimagetool)

<h2>Static build</h2>

Another way is to ship a single binary that links to the executable all necesary Qt code. 

Steps:
- Download the [Qt source code](https://wiki.qt.io/Building_Qt_5_from_Git#Getting_the_source_code)
- Unzip it to a folder
- Open the developer console of your installed compiler (i. e. MingW or MSVC)
- Switch to the folder and type ./configure -static -static-runtime
- When the configuration is done type nmake or make to build Qt statically.
- When the build process has finished create a new kit in Qt Creator and select the new qmake.exe or qmake from your source-code folder.
- Select in the project settings your kit to build a statically executable that requires not additional libraries.

