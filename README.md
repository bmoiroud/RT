# RT

## Project Overview

This project is about creating a raytracer.
This program has been created in C zith SDL2 and OpenCL.

## Installation

``` bash
$> git clone https://github.com/bmoiroud/RT.git && cd RT && make
```

## Usage

### Start it normally
``` bash
$> ./rt <scene.xml>
```
#### using clustering:
start it as a server:
``` bash
$> ./rt <scene.xml> --server <number of client>
```

start it as a client:
``` bash
$> ./rt --client <server ip>
```

| Key        | Action                 |
|:----------:|:-----------------------|
| W          | move forward           |
| S          | move backward          |
| A          | move left              |
| D          | move right             |
| Q          | turn left              |
| E          | turn right             |
| arrow up   | look up                |
| arrow down | look down              |
| H          | show/hide help panel   |
| I          | show/hide info panel   |
| P          | take a screenshot      |
| 1          | enable/disable effects |
| 2          | show/hide focus plane  |
| Space      | move up                |
| CTRL       | move down              |
| esc        | exit                   |

## Features
* Using the SDL2 graphics library
* OpenCL acceleration
* Clustering
* Depth of field
* Anti-aliasing
* procedural textures
* bump mapping
