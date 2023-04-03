[![Releases](https://img.shields.io/github/v/release/Throows/SmartPawn)](https://github.com/Throows/SmartPawn/releases)
[![Forks](https://img.shields.io/github/forks/Throows/SmartPawn)](https://github.com/Throows/SmartPawn/fork)
[![Stargazers](https://img.shields.io/github/stars/Throows/SmartPawn)](https://github.com/Throows/SmartPawn/stargazers)
[![Issues](https://img.shields.io/github/issues-raw/Throows/SmartPawn)](https://github.com/Throows/SmartPawn/issues)
[![License](https://img.shields.io/github/license/Throows/SmartPawn)](https://github.com/Throows/SmartPawn/blob/master/LICENSE)\
[![Build-MacOS](https://github.com/Throows/SmartPawn/actions/workflows/build-macos.yml/badge.svg?branch=main)](https://github.com/Throows/SmartPawn/actions/workflows/build-macos.yml)
[![Build-Windows](https://github.com/Throows/SmartPawn/actions/workflows/build-windows.yml/badge.svg?branch=main)](https://github.com/Throows/SmartPawn/actions/workflows/build-windows.yml)
<br/>
<!-- <p align="center">
  <a href="https://github.com/Throows/SmartPawn">
    <img src="images/logo.png" alt="Logo" width="80" height="80">
  </a>-->

  <h3 align="center">Smart Pawn</h3>

  <p align="center">
    Smart pawn is a two person game where the goal is to play chest by programming a IA to win for you. The last pawn remaining is the winner. (Version 1.0.1)
    <br />
    <a href="https://github.com/Throows/SmartPawn"><strong>Explore the docs »</strong></a>
    <br />
    <br />
    <a href="https://github.com/Throows/SmartPawn/releases">View Demo</a>
    ·
    <a href="https://github.com/Throows/SmartPawn/issues">Report Bug</a>
    ·
    <a href="https://github.com/Throows/SmartPawn/issues">Request Feature</a>
  </p>
</p>


<!-- TABLE OF CONTENTS -->
<details open="open">
  <summary><h2 style="display: inline-block">Table of Contents</h2></summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgements">Acknowledgements</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project

![Photo](https://raw.githubusercontent.com/Throows/SmartPawn/main/assets/SMHome.jpg)

Start by programming your basic IA, then you can improve it by adding new functions or modifying the existing ones. The goal is to play chest like game by programming a IA to play for you. The last pawn remaining is the winner. You can also play against your IA (In the future). \
Launch the simulation and see how your IA is doing against the other one. One the game is ended you can see the result of the game by reviewing it thanks to the replay mode. \
Don't Stop improving your IA. You can also share your IA with your friends and see who is the best.


### Built With

* [SFML](https://www.sfml-dev.org/)
* [PyBind11](https://github.com/pybind/pybind11)
* [xmake](https://xmake.io/)
* [spdlog](https://github.com/gabime/spdlog)



<!-- GETTING STARTED -->
## Getting Started

To build the project you need to install xmake and you will require SFML and PyBind11.

### Prerequisites

| Platform    | Compiler   | Status             |
|-------------|------------|--------------------|
| MacOS_arm64 | Clang 14   | :white_check_mark: |
| Windows_x64 | MSVC 19.34 | :white_check_mark: |
| Linux       | Not Tested | :red_circle:       |

- MacOS

1. Install xmake
   ```sh
   brew install xmake
   ```
2. Install SFML (optionnal)
   ```sh
    brew install sfml
    ```
3. Install PyBind11 (optionnal)
    ```sh
    brew install pybind11
    ```
4. Build the project
    ```sh
    xmake build
    ```
5. Run the Game

    Just start the project and have fun ! There is "by-default" IA that you can use to try and understand the games.
    
- Windows

1. Install xmake from the [website](https://xmake.io/#/home)

2. Build the project
    ```sh
    xmake build
    ```
3. Run the Game


### Installation

1. Clone the repo
   ```sh
   git clone https://github.com/Throows/SmartPawn.git
    ```

<!-- USAGE EXAMPLES -->
## Usage

Create your IA by editing the `BluePlugin.py` or `RedPlugin.py`files in the `Plugin` Folder.\
You can also review the game by adding the game log file in the `Record` folder.

_For more examples, please refer to the [Documentation](https://github.com/Throows/SmartPawn/wiki)_

<!-- ROADMAP -->
## Roadmap

See the [open issues](https://github.com/Throows/SmartPawn/issues) for a list of proposed features (and known issues).

- feature/plugin-optimization
This feature aims to optimize the plugin, and add a lots of API methods to create your IA. And to add Plugin customization and unique contexte (mby)
- feature/settings-and-lang
This feature aims to add a settings menu (Board size, etc) and a language selector.
- feature/upgraded-ui
This feature aims to improve a new UI by adding effet (when new event happen in both reader and simulation mode).

<!-- CONTRIBUTING -->
## Contributing

Contributions are what make the open source community such an amazing place to be learn, inspire, and create. Any contributions you make are **greatly appreciated**.

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

If you want to share your IA with the community, you can create a pull request and add your IA in the `ExempleIA` folder.

<!-- LICENSE -->
## License

Distributed under the MIT License. See `LICENSE` for more information.

<!-- CONTACT -->
## Contact

Throows - [@throows](https://www.instagram.com/romain.brtl/) - throowsdev@gmail.com

Project Link: [https://github.com/Throows/SmartPawn](https://github.com/Throows/SmartPawn)

<!-- ACKNOWLEDGEMENTS -->
## Acknowledgements

Will add in the future I HOPE

## Knonw Issues

  - [ ] OpenSSL@3.1 is not working (compiling but not executing on macos arm64) [Link Issue](https://stackoverflow.com/questions/74059978/why-is-lldb-generating-exc-bad-instruction-with-user-compiled-library-on-macos)