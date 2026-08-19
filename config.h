#pragma once

#include <vector>
#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>
#include <toml++/toml.hpp>

#include "base_structs.h"

enum class FractalType {
    simple_tree,
    hfrac,
    num_sys,
    koch,
    none
};

FractalType fractal_type_conv(std::string_view str) {
    if (str == "simple tree") {
        return FractalType::simple_tree;
    } else if (str == "h fractal") {
        return FractalType::hfrac;
    } else if (str == "numeral system") {
        return FractalType::num_sys;
    } else if (str == "koch") {
        return FractalType::koch;
    }
    return FractalType::none;
}

enum class InitialLines {
    custom,
    oneline,
    twoline,
    none
};

InitialLines initial_line_conv(std::string_view str) {
    if (str == "custom") {
        return InitialLines::custom;
    } else if (str == "one line") {
        return InitialLines::oneline;
    } else if (str == "two lines") {
        return InitialLines::twoline;
    }
    return InitialLines::none;
}


struct Config {
    //constants
    int window_height = 1080;

    //general params
    FractalType fractal_type = FractalType::simple_tree;
    int iterations = 2;
    float scaling = 0.5f;

    //num_sys params
    int num_sys = 3;

    //line-based params
    InitialLines initial_line_input = InitialLines::oneline;
    std::vector<Line> initial_line_vector = {};


    Config(std::string toml_file_name, sf::Window& window) {
        try {
            toml::table tbl = toml::parse_file(toml_file_name);
            
            //constants
            window_height = window.getSize().y;

            //general params
            fractal_type = fractal_type_conv(tbl["fractal_type"].value_or("tree"));
            iterations = tbl["iterationse"].value_or(iterations);
            scaling = tbl["scaling"].value_or(scaling);

            //num_sys params
            num_sys = tbl["num_sys"].value_or(num_sys);

            //line-based params
            initial_line_input = tbl["premade_preset"].value_or(initial_line_input);

            switch (initial_line_input) {
                case InitialLines::custom:
                    toml::array* arr = tbl["initial_lines"].as_array();
                    for (auto&& line : *arr) {
                        toml::array* points_arr = line.as_array();
                        toml::array* start_arr = (*points_arr)[0].as_array();
                        toml::array* end_arr = (*points_arr)[1].as_array();

                        float start_x = start_arr->get(0)->value_or(0.f);
                        float start_y = start_arr->get(1)->value_or(0.f);
                        float end_x = end_arr->get(0)->value_or(0.f);
                        float end_y = end_arr->get(1)->value_or(0.f);

                        initial_line_vector.push_back(Line(
                            {start_x, start_y}, 
                            {end_x, end_y}, 
                            std::sqrt(std::pow(end_x - start_x, 2.f) + std::pow(end_y - start_y, 2.f))
                        ));
                    }
                    break;

                case InitialLines::oneline:
                    Line line({window_height / -4.f, 0.f}, {window_height / 4.f, 0.f}, window_height / 2.f);
                    initial_line_vector.push_back(line);
                    break;

                case InitialLines::twoline:
                    Line line_up({window_height / -4.f, 0.f}, {window_height / 4.f, 0.f}, window_height / 2.f);
                    Line line_down({window_height / 4.f, 0.f}, {window_height / -4.f, 0.f}, window_height / 2.f);
                    initial_line_vector.push_back(line_up);
                    initial_line_vector.push_back(line_down);
                    break;
            
                case InitialLines::none:
                    std::cerr << "Not a valid argument for premade_preset" << "\n";
                    break;
            }
        } catch (const toml::parse_error& err) {
            std::cerr << "Parsing failed:\n" << err << "\n";
        }
    }
};