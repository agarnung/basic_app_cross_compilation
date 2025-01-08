# linux_deployment

## Guide

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

## Troubleshooting

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

## References

- [linuxdeploy Readme](https://github.com/linuxdeploy/linuxdeploy?tab=readme-ov-file)
- [AppImage Packaging Guide](https://docs.appimage.org/packaging-guide/from-source/linuxdeploy-user-guide.html)
- [linuxdeploy-plugin-qt](https://github.com/linuxdeploy/linuxdeploy-plugin-qt)
- [linuxdeploy-plugin-qt Issue 54](https://github.com/linuxdeploy/linuxdeploy-plugin-qt/issues/54)
- [LinuxDeploy Issue 224](https://github.com/linuxdeploy/linuxdeploy/issues/224)
- [Qt Forum - linuxdeploy](https://forum.qt.io/topic/122168/linuxdeploy)

## TODO

- Re-do everything with refined explanations.
- Keep only the bare necessary files from GitHub for reproducibility.

