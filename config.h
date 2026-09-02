#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <cmath>

#include <SFML/Graphics.hpp>
#include <toml++/toml.hpp>

#include "base_structs.h"
#include "line_based_fractals/line_input.h"

enum class FractalType {
    simple_tree,
    hfrac,
    num_sys,
    koch,
    mink,
    lightning,
    antenna,
    levy,
    none
};

inline FractalType fractal_type_conv(std::string_view str) {
    if (str == "simple tree") {
        return FractalType::simple_tree;
    } else if (str == "h fractal") {
        return FractalType::hfrac;
    } else if (str == "numeral system") {
        return FractalType::num_sys;
    } else if (str == "koch") {
        return FractalType::koch;
    } else if (str == "minkowski") {
        return FractalType::mink;
    } else if (str == "lightning") {
        return FractalType::lightning;
    } else if (str == "antenna") {
        return FractalType::antenna;
    } else if (str == "levy") {
        return FractalType::levy;
    }
    return FractalType::none;
}


struct Config {
    //constants
    int window_height = 1080;

    //general params
    FractalType fractal_type;
    int iterations = 2;
    float scaling = 0.5f;

    //num_sys params
    int num_sys = 3;

    //line-based params
    InitialLines initial_line_input;
    std::vector<Line> initial_line_vector;

    float line_model_width = 0.5;
    float line_model_height = 0.5;


    Config(std::string toml_file_name, sf::Window& window) {
        try {
            toml::table tbl = toml::parse_file(toml_file_name);
            
            //constants
            window_height = window.getSize().y;

            //general params
            fractal_type = fractal_type_conv(tbl["fractal_type"].value_or("simple_tree"));
            iterations = tbl["iterations"].value_or(iterations);
            scaling = tbl["scaling"].value_or(scaling);

            //num_sys params
            num_sys = tbl["num_sys"].value_or(num_sys);

            //line-based params
            initial_line_input = initial_line_conv(tbl["base_preset"].value_or("one line"));
            initial_line_vector = line_input(initial_line_input, tbl, window);

            line_model_width = tbl["line_model_width"].value_or(line_model_width);
            line_model_height = tbl["line_model_height"].value_or(line_model_height);

        } catch (const toml::parse_error& err) {
            std::cerr << "Parsing failed:\n" << err << "\n";
        }
    }
};