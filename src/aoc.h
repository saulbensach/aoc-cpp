#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <array>
#include <cmath>
#include <climits>

const std::string PATH = "/home/saul/Work/aoc-cpp/input/";

namespace aoc {
    struct Range {
        long long lower;
        long long upper;

        Range(long long a, long long b) : lower(a), upper(b) {}
    };

    struct Node {
        long x;
        long y;
        long z;
        bool connected = false;

        Node() = default;
        Node(long x, long y, long z) : x(x), y(y), z(z) {}
    };

    struct Edge {
        Node* a;
        Node* b;
        double distance;

        Edge() = default;
        Edge(Node* a, Node* b, double distance) : a(a) , b(b), distance(distance) {}
    };

    struct Graph {
        std::vector<Node*> nodes;
        std::vector<Edge*> edges;

        Graph() = default;
        Graph(Edge* edge) {
            nodes.push_back(edge->a);
            nodes.push_back(edge->b);
            edges.push_back(edge);
        }

        void add_edge(Edge* edge) {
            nodes.push_back(edge->a);
            nodes.push_back(edge->b);
            edges.push_back(edge);
        }

        void add_node(Node* node) {
            nodes.push_back(node);
        }
    };

    double distance(Node *a, Node *b) {
        long p1 = std::pow(a->x - b->x, 2);
        long p2 = std::pow(a->y - b->y, 2);
        long p3 = std::pow(a->z - b->z, 2);
        return std::sqrt(p1 + p2 + p3);
    }

    double distance(JunctionBox *a, JunctionBox *b) {
        long p1 = std::pow(a->x - b->x, 2);
        long p2 = std::pow(a->y - b->y, 2);
        long p3 = std::pow(a->z - b->z, 2);
        return std::sqrt(p1 + p2 + p3);
    }

    int char_to_int(char c) {
        return c - '0';
    }
}