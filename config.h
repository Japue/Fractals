#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <cmath>

#include <SFML/Graphics.hpp>
#include <toml++/toml.hpp>

#include "base_structs.h"
#include "line_based_fractals/line_input.h"

struct Config {
    //constants
    int window_height = 1080;

    //general params
    std::string fractal_type = "grow";
    int iterations = 2;
    float scaling = 0.5f;

    //num_sys params
    int num_sys = 3;

    //line-based params
    InitialLines initial_line_input;
    std::vector<Line> initial_line_vector;

    float line_model_width = 0.5;
    float line_model_height = 0.5;
    float rotation_angle = 90;

    //spiral params
    float spiral_scaling = 1.1f;
    float spiral_angle = 1.f;

    //logistic params
    double l_stepsize = 0.0001;
    int l_trash_iterations = 400;
    int l_samples = 10;
    double l_x0 = 0.001;
    double l_a_start = 2;
    double l_a_end = 4;

    //point fractal params
    int p_iterations = 400;
    double a = 2;
    double b = 3;

    double x_start = -100;
    double x_end = 100;
    double x_stepsize = 0.001;

    double y_start = -100;
    double y_end = 100;
    double y_stepsize = 0.001;


    Config(std::string toml_file_name, sf::Window& window) {
        try {
            toml::table tbl = toml::parse_file(toml_file_name);
            
            //constants
            window_height = window.getSize().y;

            //general params
            fractal_type = tbl["fractal_type"].value_or(fractal_type);
            iterations = tbl["iterations"].value_or(iterations);
            scaling = tbl["scaling"].value_or(scaling);

            //num_sys params
            num_sys = tbl["num_sys"].value_or(num_sys);

            //line-based params
            initial_line_input = initial_line_conv(tbl["base_preset"].value_or("one line"));
            initial_line_vector = line_input(initial_line_input, tbl, window);

            line_model_width = tbl["line_model_width"].value_or(line_model_width);
            line_model_height = tbl["line_model_height"].value_or(line_model_height);
            rotation_angle = tbl["rotation_angle"].value_or(rotation_angle);

            //spiral params
            spiral_scaling = tbl["spiral_scaling"].value_or(spiral_scaling);
            spiral_angle = tbl["spiral_angle"].value_or(spiral_angle);

            //logistic params
            l_stepsize = tbl["l_stepsize"].value_or(l_stepsize);
            l_trash_iterations = tbl["l_trash_iterations"].value_or(l_trash_iterations);
            l_samples = tbl["l_samples"].value_or(l_samples);
            l_x0 = tbl["l_x0"].value_or(l_x0);
            l_a_start = tbl["l_a_start"].value_or(l_a_start);
            l_a_end = tbl["l_a_end"].value_or(l_a_end);

            //point fractal params
            p_iterations = tbl["p_iterations"].value_or(p_iterations);
            a = tbl["a"].value_or(a);
            b = tbl["b"].value_or(b);

            x_start = tbl["x_start"].value_or(x_start);
            x_end = tbl["x_end"].value_or(x_end);
            x_stepsize = tbl["x_stepsize"].value_or(x_stepsize);

            y_start = tbl["y_start"].value_or(y_start);
            y_end = tbl["y_end"].value_or(y_end);
            y_stepsize = tbl["y_stepsize"].value_or(y_stepsize);

        } catch (const toml::parse_error& err) {
            std::cerr << "Parsing failed:\n" << err << "\n";
        }
    }
};