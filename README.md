# Jeopardy in C
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

# Caveats

1. This looks best with a dark terminal theme. I recommend [base16](https://github.com/chriskempson/base16).
2. Make sure your terminal is *at least* 202 characters wide and 52 characters tall. You can check with `echo -e "cols\nlines" | tput -S`. If you've expanded the window to full screen and it's still not enough, reduce your font size.
3. A GPU-based terminal emulator like [kitty](https://github.com/kovidgoyal/kitty) can significantly reduce any screen tearing. Refreshing a 202x52 display means updating over 10,000 cells at once.
4. It's recommended to use a terminal that supports 24-bit colour. Here's a test command (should appear in colour): `printf "\x1b[38;2;255;100;0mTRUECOLOR\x1b[0m\n"`

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

