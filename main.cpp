#include <vector>
#include <iostream>
#include <functional>
#include <unordered_map>

#include <SFML/Graphics.hpp>
#include <toml++/toml.hpp>

#include "base_structs.h"
#include "config.h"
#include "simple_tree_fractal/simple_tree.h"
#include "h_fractal/h_fractal.h"
#include "num_sys_fractal/num_sys_fractal.h"
#include "line_based_fractals/umbrella_header.h"
#include "spirals/grow.h"
#include "spirals/line_based_spiral.h"
#include "trees/pythagorean.h"
#include "trees/mandel_tree.h"
#include "point_fractals/logistic.h"
#include "point_fractals/julia.h"


using LineSimulateFn = std::function<std::vector<Line>(const Config&)>;
using PointSimulateFn = std::function<std::vector<sf::Vertex>(const Config&)>;

const std::unordered_map<std::string, LineSimulateFn> line_simulate_table = {
    {"simple tree", [](const Config& c) { return simple_tree::simulate(c); }},
    {"hfrac", [](const Config& c) { return hfrac::simulate(c); }},
    {"num_sys", [](const Config& c) { return num_sys::simulate(c); }},
    {"koch", [](const Config& c) { return koch::simulate(c); }},
    {"mink", [](const Config& c) { return mink::simulate(c); }},
    {"lightning", [](const Config& c) { return lightning::simulate(c); }},
    {"antenna", [](const Config& c) { return antenna::simulate(c); }},
    {"levy", [](const Config& c) { return levy::simulate(c); }},
    {"dragon", [](const Config& c) { return dragon::simulate(c); }},
    {"grow", [](const Config& c) { return grow::simulate(c); }},
    {"line_spiral", [](const Config& c) { return line_spiral::simulate(c); }},
    {"pyth", [](const Config& c) { return pyth::simulate(c); }},
    {"mandel tree", [](const Config& c) { return mandel::simulate(c); }}
};

const std::unordered_map<std::string, PointSimulateFn> point_simulate_table = {
    {"logistic", [](const Config& c) { return logistic::simulate(c); }},
    {"julia", [](const Config& c) { return julia::simulate(c); }}
};


int main(){
    //window setup
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Tree Fractal");
    sf::View view = window.getDefaultView();
    view.setCenter({0, 0});

    bool is_dragging = false;
    sf::Vector2i last_mouse_pos = sf::Mouse::getPosition(window);

    //config and fractal generation accordingly
    const Config config("config.toml", window);

    std::vector<sf::Vertex> vertices;
    sf::PrimitiveType primitive_type;

    if (auto it = line_simulate_table.find(config.fractal_type); it != line_simulate_table.end()){
        std::vector<Line> draw_lines = it->second(config);
        vertices.reserve(draw_lines.size() * 2);
        for (const Line& line : draw_lines) {
            vertices.push_back(sf::Vertex{line.start});
            vertices.push_back(sf::Vertex{line.end});
        }
        primitive_type = sf::PrimitiveType::Lines;
        std::cout << "Lines made, starting gameloop";
    } else if (auto it2 = point_simulate_table.find(config.fractal_type); it2 != point_simulate_table.end()){
        vertices = it2->second(config);
        primitive_type = sf::PrimitiveType::Points;
        std::cout << "Points made, starting gameloop\n";
    } else {
        std::cerr << "Not a valid argument for fractal_type" << "\n";
        window.close();
        return 0;
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
        window.draw(vertices.data(), vertices.size(), primitive_type);
        //

        window.display();
    }
}