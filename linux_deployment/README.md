# Linux Deployment

# Índice

1. [Introduction](#introduction)
2. [Resources](#resources)
3. [windeployqt/linuxdeployqt](#windeployqtlinuxdeployqt)
   - [Steps](#steps)
   - [Notes](#notes)
   - [To install `linuxdeployqt`](#to-install-linuxdeployqt)
4. [Similar Tools](#similar-tools)
   - [linuxdeploy](#linuxdeploy)
   - [appimage-builder](#appimage-builder)
   - [go-appimage](#go-appimage)
5. [Static Build](#static-build)
6. [Docker Containers](#docker-containers)
7. [Basic tutorial using linuxdeploy](#basic-tutorial-using-linuxdeploy)
   - [Option A) Install `linuxdeploy` Locally](#option-a-install-linuxdeploy-locally)
   - [Option B) Download the AppImage of `linuxdeploy`](#option-b-download-the-appimage-of-linuxdeploy)
   - [Create the AppDir Structure](#create-the-appdir-structure)
   - [Package the AppImage](#package-the-appimage)
   - [Test the AppImage](#test-the-appimage)
   - [Additional Libraries or Plugins](#additional-libraries-or-plugins)
   - [Troubleshooting](#troubleshooting)
8. [References](#references)

## Introduction

Humongously simple Qt app packaged for distribution across machines running the same platform as the one it was compiled on (Linux).

### Resources

**Deployment:**
- [YouTube - Qt deployment tutorial](https://www.youtube.com/watch?v=Y0MSOQGv5N4)
- [StackOverflow - How to release a Qt C++ application on Linux and Windows](https://stackoverflow.com/questions/49982419/how-to-release-a-qt-c-application-on-linux-and-windows)
- [YouTube - Another Qt deployment tutorial](https://www.youtube.com/watch?v=PDzlT_ODpM8&ab_channel=probono)
- [LinuxDeployQt Issues on GitHub](https://github.com/probonopd/linuxdeployqt/issues/377)

There are several ways to deploy your application:

### windeployqt/linuxdeployqt

The tools `windeployqt` or `linuxdeployqt` (which is 3rd-party) will copy all required dependencies to an executable folder, ready to run on another machine.

#### Steps:
1. Compile the binary in release mode, e.g., the executable path inside the build folder is `app_path='/opt/app/build/Desktop_Qt_6_8_1-Release/app'`
2. Set the Qt environment variable: 
   ```bash
   export PATH=/opt/Qt/6.8.1/gcc_64/bin/:$PATH
   ```
3. Run `linuxdeployqt`:
   ```bash
   ./linuxdeployqt-continuous-x86_64.AppImage $app_path -appimage
   ```
4. If `ERROR: The host system is too new` appears, add the flag `-unsupported-allow-new-glibc` or `-unsupported-bundle-everything` to the previous command.
5. All libraries required to run the application on another computer are copied to the application folder.
6. The app can be distributed as an AppDir or AppImage.

#### Notes:
- One needs a `.desktop` file and an icon, but it can be automatically created.
- If the AppImage is not generated, it is possible that the distribution is too new to use `linuxdeployqt`. See [issue #340](https://github.com/probonopd/linuxdeployqt/issues/340).

#### To install `linuxdeployqt`:
1. Build from source: [LinuxDeployQt GitHub](https://github.com/probonopd/linuxdeployqt)
2. Or install the AppImage from [releases](https://github.com/probonopd/linuxdeployqt/releases) and `chmod a+x` to permit execution.

### Similar Tools

If `linuxdeployqt` does not work, try other similar tools:

#### linuxdeploy
- [Download here](https://github.com/linuxdeploy/linuxdeploy)
- See:
  - [Serial-Studio Workflow for Deploy](https://github.com/Serial-Studio/Serial-Studio/blob/master/.github/workflows/deploy.yml)
  - [AppImage Packaging Guide](https://docs.appimage.org/packaging-guide/from-source/native-binaries.html#using-linuxdeploy-for-building-appimages)
  
#### appimage-builder
- [Download here](https://github.com/AppImageCrafters/appimage-builder)

#### go-appimage
- [Download here](https://github.com/probonopd/go-appimage/tree/master/src/appimagetool)

### Static Build

Another way is to ship a single binary that links to the executable all necessary Qt code.

#### Steps:
1. Download the [Qt source code](https://wiki.qt.io/Building_Qt_5_from_Git#Getting_the_source_code).
2. Unzip it to a folder.
3. Open the developer console of your installed compiler (i.e., MingW or MSVC).
4. Switch to the folder and type `./configure -static -static-runtime`.
5. When the configuration is done, type `nmake` or `make` to build Qt statically.
6. After the build process, create a new kit in Qt Creator and select the new `qmake.exe` or `qmake` from your source code folder.
7. Select in the project settings your kit to build a statically executable that requires no additional libraries.

### Docker Containers

[This project](https://github.com/state-of-the-art/qt6-docker) provides various Docker containers to build an application on multiple platforms.

---

## Basic tutorial suing linuxdeploy

### Guide

This guide explains how to package and deploy an application using `linuxdeploy`. You can choose to either install `linuxdeploy` locally or download the AppImage version, which may come bundled with additional tools. See [issue #218 comment](https://github.com/linuxdeploy/linuxdeploy/issues/218#issuecomment-1256486084) for more information.

### Option A) Install `linuxdeploy` Locally

1. Clone the `linuxdeploy` repository:

    ```bash
    git clone --recursive https://github.com/linuxdeploy/linuxdeploy.git
    ```

2. Install required dependencies and build `linuxdeploy`:

    ```bash
    sudo apt install cmake g++ patchelf
    ```

3. Build `linuxdeploy`:

    ```bash
    mkdir build
    cd build
    cmake ..
    make
    ```

4. Convert `linuxdeploy` to the AppImage format:
    From the `build` directory of `linuxdeploy`:

    ```bash
    ./linuxdeploy-x86_64 --appimage
    ```

### Option B) Download the AppImage of `linuxdeploy`

1. Download the `linuxdeploy` AppImage:

    ```bash
    wget https://github.com/linuxdeploy/linuxdeploy/releases/download/2.0.0-alpha-1-20241106/linuxdeploy-x86_64.AppImage
    ```

2. To list the available plugins in the downloaded AppImage, run:

    ```bash
    ./linuxdeploy-x86_64.AppImage --list-plugins
    ```

    Alternatively, you may want to download the `linuxdeploy-plugin-qt` AppImage:

    ```bash
    wget https://github.com/linuxdeploy/linuxdeploy-plugin-qt/releases/download/2.0.0-alpha-1-20241106/linuxdeploy-plugin-qt-x86_64.AppImage
    ```

3. Grant execution permissions to the downloaded AppImage:

    ```bash
    chmod +x linuxdeploy-x86_64.AppImage
    ```

### Create the AppDir Structure

The required structure for the AppDir must contain at least the following:
- An executable binary
- A `.desktop` file
- An icon

1. Create the base directory for your AppDir:

    ```bash
    mkdir -p MyAppDir
    ```

2. Move your binary executable into the `MyAppDir` directory.

3. Create a `.desktop` file in `<path_to_MyAppDir>/resources`, for example:

    ```ini
    [Desktop Entry]
    Version=1.0
    Name=My App
    Comment=This is my app
    Exec=myapp
    Icon=myapp
    Terminal=false
    Type=Application
    Categories=Utility;
    ```

4. Add your application icon (e.g., `myapp.png`) to the `resources` folder:

    ```bash
    cp foo.png <path_to_MyAppDir>/resources
    ```

The directory structure should now look like this:

    MyAppDir/
    ├── myapp/                # Your executable
    ├── resources/
    │   ├── myapp.png         # Your icon
    │   └── myapp.desktop     # Your desktop entry

### Package the AppImage

1. Inside `MyAppDir`, use the `--executable` option to ensure the executable and necessary dependencies are included:

    ```bash
    ./linuxdeploy-x86_64.AppImage --appdir MyAppDir --executable myapp --desktop-file ./resources/myapp.desktop --icon-file ./resources/myapp.png --output appimage
    ```

2. To generate the AppImage:

    ```bash
    ./linuxdeploy-x86_64.AppImage --appdir MyAppDir --output appimage
    ```

After packaging, the directory structure should look like this:

    /MyAppDir$ tree
    .
    ├── linuxdeploy-x86_64.AppImage
    ├── myapp
    ├── MyAppDir
    │   ├── AppRun -> usr/bin/myapp
    │   ├── myapp.desktop -> usr/share/applications/myapp.desktop
    │   ├── myapp.png -> usr/share/icons/hicolor/512x512/apps/myapp.png
    │   └── usr
    │       ├── bin
    │       │   └── myapp
    │       ├── lib
    │       │   ├── libbrotlicommon.so.1
    │       │   └── ...
    │       └── share
    │           ├── applications
    │           │   └── myapp.desktop
    │           ├── doc
    │           │   ├── libbrotli1
    │           │   │   └── copyright
    │           │   ├── ...
    │           └── icons
    │               └── hicolor
    │                   ├── 128x128
    │                   │   └── apps
    │                   ├── ...
    ├── MyApp-x86_64.AppImage
    └── resources
        ├── myapp.desktop
        └── myapp.png

### Test the AppImage

Run the generated AppImage to ensure it works as expected:

    ```bash
    ./MyApp-x86_64.AppImage
    ```

### Additional Libraries or Plugins

If your application requires additional libraries or plugins, you can specify them like this:

    ```bash
    ./linuxdeploy-x86_64.AppImage --appdir MyAppDir --library /path/to/my/library.so --plugin qt --output appimage
    ```

If everything is configured correctly, you'll be able to distribute your AppImage to other machines.

You can also use the generated AppDir to create an AppImage with [AppImageKit](https://github.com/AppImage/AppImageKit).

### Troubleshooting

If you are using the `linuxdeploy-plugin-qt-x86_64.AppImage`, make sure you set the `qmake` path in your terminal session:

    ```bash
    export PATH=$PATH:/opt/Qt/6.8.1/gcc_64/bin/
    ```

Then, generate the AppDir:

    ```bash
    ./linuxdeploy-plugin-qt-x86_64.AppImage --appdir MyAppDir
    ```

Finally, create the AppImage using the `linuxdeploy` command:

    ```bash
    ./linuxdeploy-x86_64.AppImage --appdir MyAppDir --output appimage
    ```

### References

- [linuxdeploy Readme](https://github.com/linuxdeploy/linuxdeploy?tab=readme-ov-file)
- [AppImage Packaging Guide](https://docs.appimage.org/packaging-guide/from-source/linuxdeploy-user-guide.html)
- [linuxdeploy-plugin-qt](https://github.com/linuxdeploy/linuxdeploy-plugin-qt)
- [linuxdeploy-plugin-qt Issue 54](https://github.com/linuxdeploy/linuxdeploy-plugin-qt/issues/54)
- [LinuxDeploy Issue 224](https://github.com/linuxdeploy/linuxdeploy/issues/224)
- [Qt Forum - linuxdeploy](https://forum.qt.io/topic/122168/linuxdeploy)

### TODO

- Re-do everything with refined explanations.
- Keep only the bare necessary files from GitHub for reproducibility.
