# CPPND: Capstone Snake Game Example

This is a starter repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

<img src="snake_game.gif"/>

The Capstone Project gives you a chance to integrate what you've learned throughout this program. This project will become an important part of your portfolio to share with current and future colleagues and employers.

In this project, you can build your own C++ application or extend this Snake game, following the principles you have learned throughout this Nanodegree Program. This project will demonstrate that you can independently create applications using a wide range of C++ features.

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  * Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.

## New Scope
The application keeps track of top scorer's details, namely score and name of top scorer. It persists required information in a file and reads it when application is started, to get top scorer's details. If current player's score isn't less than top scorer's score, then current player is set as top scorer and current player's details are persisted.

## Rubric Points

### Loops, Functions, I/O

|Criteria|Description|
| --- | --- |
|The project demonstrates an understanding of C++ functions and control structures.| A variety of control structures are used in the project.|
| The project reads data from a file and process the data, or the program writes data to a file.| The project reads data of top scorer from an external file `ScorePersistence.txt` and writes data to it as part of the necessary operation of the program.|

### Object Oriented Programming

|Criteria|Description|
| --- | --- |
|Classes encapsulate behavior.| Classes `Player` and `Persistence` group their appropriate data and functions. Member data that is subject to an invariant is hidden from the user. State is accessed via member functions.|
|Overloaded functions allow the same function to operate on different parameters.| `Player::Title` function is overloaded with different signatures.|

### Memory Management

|Criteria|Description|
| --- | --- |
|The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate.| By using smart pointers, the project follows `RAII` pattern.|
| The project uses smart pointers instead of raw pointers.| The project uses `unique_ptr` and `shared_ptr`.|
