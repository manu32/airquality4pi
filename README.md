# airquality4pi

## About

**airquality4pi** is an C++-application for measuring temperature and humidity with a raspberrypi and a connected DHT-sensor.
It's furthermore possible to store and query data to/from a **SQLite**-database.
The application is built using **Conan** as package manager and **CMake** as build system.

## Installation

### Build using Conan

Clone the repository and make sure you have conan installed on your device.
First you need to create a build folder. After that navigate to that folder and execute the conan install command.
Replace `REPOSITORY_ROOT_FOLDER` with the relativ path to the root of this repository. 

```
conan install <REPOSITORY_ROOT_FOLDER>
```

After the dependencies have been installed, execute:

```
conan build <REPOSITORY_ROOT_FOLDER>
```

This line triggers the actual build command and builds the binaries.
