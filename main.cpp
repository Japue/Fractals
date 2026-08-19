#include <vector>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <toml++/toml.hpp>

#include "base_structs.h"
#include "simple_tree_fractal/simple_tree.h"
#include "h_fractal/h_fractal.h"
#include "num_sys_fractal/num_sys_fractal.h"
#include "koch_fractal/koch_fractal.h"

int main(){
    //general_params
    int fractal_type = 0;
    int iterations = 4;
    float scaling = 0.5;

    //num_sys_params
    int num_sys = 3;

    std::vector<Line> initial_line_vector = {};

    //toml parsing for parameters
    try {
        toml::table tbl = toml::parse_file("config.toml");
        fractal_type = tbl["general_params"]["fractal_type"].value_or(fractal_type);
        iterations = tbl["general_params"]["iterations"].value_or(iterations);
        scaling = static_cast<float>(tbl["general_params"]["scaling"].value_or(scaling));
        num_sys = tbl["num_sys_params"]["num_sys"].value_or(num_sys);
        toml::array* initial_lines = tbl["koch_paramsf"]["initial_lines"].as_array();
        if (initial_lines) {
            for (auto&& line_node : *initial_lines) {
                toml::array* line_arr = line_node.as_array();
                if (!line_arr || line_arr->size() != 2) continue; // skip malformed entries

                toml::array* start_arr = (*line_arr)[0].as_array();
                toml::array* end_arr = (*line_arr)[1].as_array();
                if (!start_arr || !end_arr) continue;

                float start_x = start_arr->get(0)->value_or(0.0f);
                float start_y = start_arr->get(1)->value_or(0.0f);
                float end_x = end_arr->get(0)->value_or(0.0f);
                float end_y = end_arr->get(1)->value_or(0.0f);

                sf::Vector2f start{start_x, start_y};
                sf::Vector2f end{end_x, end_y};
                float length = std::sqrt(std::pow(end_x - start_x, 2.f) + std::pow(end_y - start_y, 2.f));

                initial_line_vector.push_back(Line(start, end, length));
            }
        }
    } catch (const toml::parse_error& err) {
        std::cerr << "Parsing failed:\n" << err << "\n";
    }

    //window setup
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Tree Fractal");
    sf::View view = window.getDefaultView();
    view.setCenter({0, 0});

    bool is_dragging = false;
    sf::Vector2i last_mouse_pos = sf::Mouse::getPosition(window);

    //fractal selection and generation
    std::vector<Line> draw_lines;
    switch (fractal_type){
        case 0:
            draw_lines = tree::simulate(iterations, scaling, window.getSize().y);
            break;
        case 1:
            draw_lines = hfrac::simulate(iterations, scaling, window.getSize().y);
            break;
        case 2:
            draw_lines = num_sys::simulate(iterations, scaling, num_sys, window.getSize().y);
            break;
        case 3:
            draw_lines = koch::simulate(iterations, scaling, initial_line_vector, window.getSize().y);
            break;
    }

    //gameloop
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {

            //event handling
            if (event -> is<sf::Event::Closed>()) {
                window.close();
            }

            if (const auto* keyPressed = event -> getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->code == sf::Keyboard::Key::Escape) {
                    window.close();
                }
            }

            if (const auto* mousePressed = event -> getIf<sf::Event::MouseButtonPressed>()) {
                if (mousePressed->button == sf::Mouse::Button::Left) {
                    is_dragging = true;
                }
            }
            
            if (const auto* mouseReleased = event -> getIf<sf::Event::MouseButtonReleased>()) {
                if (mouseReleased->button == sf::Mouse::Button::Left) {
                    is_dragging = false;
                }
            }

            if (const auto* scrolled = event -> getIf<sf::Event::MouseWheelScrolled>()) {
                if (scrolled->delta > 0) {
                    view.zoom(0.9f);
                } else {
                    view.zoom(1.1f);
                }
            }
        }

        window.clear();

        //dragging
        sf::Vector2i new_mouse_pos = sf::Mouse::getPosition(window);
        if (is_dragging) {
            sf::Vector2i delta_pos = last_mouse_pos - new_mouse_pos;

            sf::Vector2u window_size_u = window.getSize();
            sf::Vector2f window_size(static_cast<float>(window_size_u.x), static_cast<float>(window_size_u.y));
            sf::Vector2f view_size = view.getSize();

            sf::Vector2f scale_and_float(static_cast<float>(delta_pos.x) * (view_size.x / window_size.x), static_cast<float>(delta_pos.y) * (view_size.y / window_size.y));
            view.setCenter(view.getCenter() + scale_and_float);
        }
        last_mouse_pos = new_mouse_pos;
        window.setView(view);

        //drawing
        for (const Line& line : draw_lines) {
            std::array line_points = {
                sf::Vertex{line.start},
                sf::Vertex{line.end}};

            window.draw(line_points.data(), line_points.size(),
                        sf::PrimitiveType::Lines);
        }
        //

            window.display();
    }
}