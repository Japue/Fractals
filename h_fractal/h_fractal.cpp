#include "h_fractal.h"
#include "../base_structs.h"
#include "../config.h"

std::vector<H> hfrac::iterate(const std::vector<H>& begin_h, std::vector<H>& all_h, float scaling) {
    std::vector<H> next_h = {};

    for (const H& h : begin_h) {
        Line prev_left = h.left;
        Line prev_hori = h.hori;

        Line upleft_hori = Line(
            prev_left.end - sf::Vector2f{prev_left.length * scaling, 0.f}, 
            prev_left.end + sf::Vector2f{prev_left.length * scaling, 0.f}, 
            prev_left.length);
        Line downleft_hori = upleft_hori.translate_copy({0.f, prev_left.length});
        Line upright_hori = upleft_hori.translate_copy({prev_hori.length, 0.f});
        Line downright_hori = upleft_hori.translate_copy({prev_hori.length, prev_left.length});

        Line upleft_left = Line(
            upleft_hori.start + sf::Vector2f{0.f, upleft_hori.length * scaling / 2},
            upleft_hori.start - sf::Vector2f{0.f, upleft_hori.length * scaling / 2},
            upleft_hori.length / 2.f);
        Line downleft_left = upleft_left.translate_copy({0.f, prev_left.length});
        Line upright_left = upleft_left.translate_copy({prev_hori.length, 0.f});
        Line downright_left = upleft_left.translate_copy({prev_hori.length, prev_left.length});

        Line upleft_right = Line(
            upleft_hori.end + sf::Vector2f{0.f, upleft_hori.length * scaling / 2},
            upleft_hori.end - sf::Vector2f{0.f, upleft_hori.length * scaling / 2},
            upleft_hori.length / 2.f);
        Line downleft_right = upleft_right.translate_copy({0.f, prev_left.length});
        Line upright_right = upleft_right.translate_copy({prev_hori.length, 0.f});
        Line downright_right = upleft_right.translate_copy({prev_hori.length, prev_left.length});
        
        H upleft = H(upleft_hori, upleft_left, upleft_right);
        H downleft = H(downleft_hori, downleft_left, downleft_right);
        H upright = H(upright_hori, upright_left, upright_right);
        H downright = H(downright_hori, downright_left, downright_right);

        all_h.push_back(upleft);
        all_h.push_back(downleft);
        all_h.push_back(upright);
        all_h.push_back(downright);

        next_h.push_back(upleft);
        next_h.push_back(downleft);
        next_h.push_back(upright);
        next_h.push_back(downright);
    }
    return next_h;
}

std::vector<Line> hfrac::simulate(const Config& config) {
    int window_height = config.window_height;
    Line start_hor_line({-0.5f * window_height, 0.f}, {0.5f * window_height, 0.f}, 1.f * window_height);
    std::vector<H> all_h = {H(
        start_hor_line,
        Line(
            start_hor_line.start + sf::Vector2f{0.f, window_height * 0.25f},
            start_hor_line.start - sf::Vector2f{0.f, window_height * 0.25f},
            start_hor_line.length / 2.f),
        Line(
            start_hor_line.end + sf::Vector2f{0.f, window_height * 0.25f},
            start_hor_line.end - sf::Vector2f{0.f, window_height * 0.25f},
            start_hor_line.length / 2.f)
        )};

    std::vector<H> start_h = all_h;

    for (int i = 0; i < config.iterations; i++) {
        start_h = iterate(start_h, all_h, config.scaling);
    }
    
    std::vector<Line> all_lines = {};

    for (const H& h : all_h) {
        all_lines.push_back(h.hori);
        all_lines.push_back(h.left);
        all_lines.push_back(h.right);
    }

    return all_lines;
}