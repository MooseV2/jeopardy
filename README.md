# Jeopardy_in_C
The game of Jeopardy written in C.

# Features

* Sexy ncurses TUI
* Even sexier question screen
* [Levenshtein distance](https://en.wikipedia.org/wiki/Levenshtein_distance) based answer validation (ie, minor changes like grey/gray are fine)
* Interrogative validation (<Who/What/Where...> <are/is> <text>)
* Jeopardy music
* Editable questions file
* Trebek compatible
  
# Running without compiling

Builds for macOS and Linux (Ubunutu) are provided under the `build` directory. If you are running Windows, consider not.

Note: You may still need to have `libsndfile` installed to run `jeopardy_linux`. If for some reason you are unable to install it, `jeopardy_linux_nosound` is also provided.

# Compilation

Steps:

1. Ensure `gcc` and `make` are installed
2. Install the following libraries:

~~~
# Mac
brew install libsndfile
brew install libao

# Linux
sudo apt update
sudo apt install libncursesw5-dev
sudo apt install libao-dev
sudo apt install libsndfile-dev
~~~

3. Run `make`


Note: It's possible to build without libao and libsndfile by removing the -DUSESOUND flag from the Makefile.

