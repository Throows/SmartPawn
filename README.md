[![Releases](https://img.shields.io/github/v/release/Throows/SmartPawn)](https://github.com/Throows/Throows)
[![Forks](https://img.shields.io/github/forks/Throows/SmartPawn)](https://github.com/Throows/SmartPawn/fork)
[![Stargazers](https://img.shields.io/github/stars/Throows/SmartPawn)](https://github.com/Throows/SmartPawn/stargazers)
[![Issues](https://img.shields.io/github/issues-raw/Throows/SmartPawn)](https://github.com/Throows/SmartPawn/issues)
[![License](https://img.shields.io/github/license/Throows/SmartPawn)](https://github.com/Throows/SmartPawn/blob/master/LICENSE)

<br/>
<!-- <p align="center">
  <a href="https://github.com/Throows/SmartPawn">
    <img src="images/logo.png" alt="Logo" width="80" height="80">
  </a>-->

  <h3 align="center">Smart Pawn</h3>

  <p align="center">
    Smart pawn is a two person game where the goal is to play chest by programming a IA to win for you. The last pawn remaining is the winner.
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

![Photo](https://github.com/Throows/SmartPawn/blob/master/assets/SMHome.jpg?raw=true)

Start by programming your basic IA, then you can improve it by adding new functions and improving the existing ones. The goal is to play chest like game by programming a IA to play for you. The last pawn remaining is the winner. You can also play against your IA (In the future). \
Launch the simulation and see how your IA is doing against the other one. One the game is ended you can see the result of the game by reviewing it thanks to the replay mode. \
Don't Stop improving your IA. You can also share your IA with your friends and see who is the best.


### Built With

* [SFML](https://www.sfml-dev.org/)
* [PyBind11](https://github.com/pybind/pybind11)
* [xmake](https://xmake.io/)



<!-- GETTING STARTED -->
## Getting Started

To build the project you need to install xmake and you will require SFML and PyBind11.

### Prerequisites

- MacOS

1. Install xmake
   ```sh
   brew install xmake
   ```
2. Install SFML
   ```sh
    brew install sfml
    ```
3. Install PyBind11
    ```sh
    brew install pybind11
    ```
4. Build the project
    ```sh
    xmake build
    ```
5. Run the project

    Just start the project and have fun ! There is "by-defaul" IA that you can use to try and understand the games.
    
- Linux & Windows (Not tested)

The game hasn't been tested on windows and linux yet. If you want to try it, you will need to install SFML and PyBind11 and then build the project with xmake. Create an issue if you have any problem.

### Installation

1. Clone the repo
   ```sh
   git clone https://github.com/Throows/SmartPawn.git
    ```

<!-- USAGE EXAMPLES -->
## Usage

Create your IA by editing the `BluePlugin.py` or `RedPlugin.py`files in the `Plugin` Folder. \
You can also review the game by adding the game log file in the `Record` folder. \

_For more examples, please refer to the [Documentation](https://github.com/Throows/SmartPawn/wiki)_

<!-- ROADMAP -->
## Roadmap

See the [open issues](https://github.com/Throows/SmartPawn/issues) for a list of proposed features (and known issues).


<!-- CONTRIBUTING -->
## Contributing

Contributions are what make the open source community such an amazing place to be learn, inspire, and create. Any contributions you make are **greatly appreciated**.

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

If you want to share your IA with the community, you can create a pull request and add your IA in the `ExempleIA` folder. \

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
