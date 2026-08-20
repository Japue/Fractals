# Fractals
A program that plots fractals using SFML and toml++ for the config

# Setup
Rename example.toml to config.toml, this is the file where you'll configure everything


# Config Explained

## Fractal Types

First you have to select a fractal type, the possible options are divided into some categories:

- [Simple Fractals](#simple-fractals)
    - [Simple Tree](#simple-tree)
    - [H Fractal](#h-fractal)
    - [Numeral System Fractal](#numeral-system-fractal)
- [Line Based Fractals](#line-based-fractals)
    - [Koch Patterns](#koch-patterns)

For each fractal the following is listed:

- an explanation
- fractal_type: the string to put in to fractal_type to get the fractal
- other parameters: other parameters used

The general parameters are used for every fractal so they won't be listed.

---

### Simple Fractals

These are some basic fractal patterns, nothing too special.

#### Simple Tree

This makes a tree that splits into two new ones every iteration, it represents the binary number system. It perfectly never touches the top of the screen.

fractal_type = "simple tree"
other parameters: none

#### H Fractal

This starts with a shape like this |-|, then on every boundary point of the verticals it puts a new shape of the same shape but scaled down/up by scaling. 
#### Numeral System Fractal

---

### Line Based Fractals
#### Koch Patterns



premade_preset accepts:
    "custom" (takes the argument in initial lines)
    "one line"
    "two lines"
    "triangle"
    "sideways triangle"
    "reverse triangle"
    "square"
    "reverse square"
    "rhombus"
    "hexagon"
    "octagon"
    "none"