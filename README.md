# Cub3D

Cub3D is a 3D raycasting project implemented in C using the MiniLibX graphics library. Developed for the 42 network, it renders a 3D view of a 2D map and allows player navigation through a virtual environment.

## Features

- **Raycasting engine:** Renders a pseudo-3D scene from a 2D map.
- **Map parsing:** Validates map files and detects player starting positions via functions such as [`find_char`](src/parsing/utils.c).
- **Player movement:** Supports forward, backward, and lateral movement along with rotation.
- **Cross-platform support:** Uses different MiniLibX implementations for macOS ([`mlx_mac/mlx.h`](mlx_mac/mlx.h)) and Linux ([`mlx_linux/mlx.h`](mlx_linux/mlx.h)).
- **Custom utilities:** Includes helper functions for graphics, vector math, and more from [`cub3d.h`](include/cub3d.h).

## Project Structure

```
cub3d/
├── cub3d                # Main project directory and executable target
├── include              # Header files (e.g. [cub3d.h](include/cub3d.h))
├── libft                # Custom library (Libft implementation)
├── mlx_linux            # MiniLibX implementation for Linux
├── mlx_mac              # MiniLibX implementation for macOS
├── src                  # Source code (e.g. [utils.c](src/parsing/utils.c))
├── Makefile             # Build configuration and targets
└── .vscode              # VSCode configurations (launch.json, settings.json)
```

## Prerequisites

### macOS
- [XQuartz](https://www.xquartz.org/)
- Xcode command line tools

### Linux
- GCC and Make
- X11 libraries: `libxext-dev`, `libx11-dev`, `libbsd-dev`, etc.

For Ubuntu/Debian, install dependencies with:

```bash
sudo apt-get install gcc make libxext-dev libx11-dev libbsd-dev
```

## Build Instructions

Run the following command in the project root to compile the project:

```bash
make
```

The appropriate MiniLibX library will be selected based on your operating system. The executable will be created as defined in the [Makefile](Makefile).

## Usage

Launch the game with:

```bash
./cub3d [map_file]
```

- **[map_file]**: Path to a valid map file containing characters for walls (`1`), empty spaces (`0`), and a single player starting position marked with one of `N`, `S`, `E`, or `W`.

If the map contains any invalid character, functions like [`find_char`](src/parsing/utils.c) will print an error.

## Controls

Controls vary by operating system (see key mappings in [cub3d.h](include/cub3d.h)):
  
- **Movement:** Typically use WASD keys (or corresponding macOS keys) for forward, backward, left, and right movement.
- **Rotation:** Use the arrow keys.
- **Exit:** Press the Escape key.

## Debugging

- This project can display debug info (e.g., FPS, raycasting details) when enabled.
- Modify debug flags as needed in your configuration.

## License

This project is released under the BSD 2-Clause License. See [mlx_linux/LICENSE](mlx_linux/LICENSE) for details.

## Acknowledgments

- **MiniLibX:** A simple X-Window Interface Library, see [mlx_linux/README.md](mlx_linux/README.md) for more info.
- **Libft:** Utility functions and data structures used throughout the project.