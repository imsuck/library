#pragma once

// node needs label() -> string, graph_id() -> string (uid)
template<class node, bool draw_graph = false> struct toptree_logger {
  private:
    set<pair<int, int>> forest_edges;
    set<int> forest_vertices;
    set<node *> vis;
    ofstream dot;
    bool logging = false;
    int iter = 0;
    string filename;

    void start_subgraph(const string &desc) {
        vis.clear();
        forest_edges.clear();
        forest_vertices.clear();

        dot << "\n  subgraph cluster_" << iter << " {" << endl;
        dot << "    fontname = \"monospace\";" << endl;
        if (desc.empty()) {
            dot << "    label = \"Iteration " << iter << "\";" << endl;
        } else {
            dot << "    label = \"" << desc << "\";" << endl;
        }
        dot << "    color = lightgrey;" << endl;
    }

    void end_subgraph() { dot << "  }" << endl; }

    void add_tree(node *r) {
        if (!r) return;
        while (r->p) r = r->p;

        vector<node *> stk;
        stk.push_back(r);

        while (!stk.empty()) {
            node *cur = stk.back();
            stk.pop_back();

            if (!cur || vis.count(cur)) continue;
            vis.insert(cur);
            cur->push_flip_all();

            if constexpr (draw_graph) {
                if (!cur->is_vert) {
                    int a = cur->edge[0];
                    int b = cur->edge[1];
                    if (a > b) swap(a, b);
                    forest_edges.insert({a, b});
                    forest_vertices.insert(a);
                    forest_vertices.insert(b);
                } else {
                    forest_vertices.insert(cur->id);
                }
            }

            string label = cur->label();
            string uid = cur->graph_id() + "_" + to_string(iter);

            string fill_color;
            string font_color = "white";
            string shape;
            string style;
            if (cur->is_vert) {
                style = "filled";
                fill_color = "#2196F3";
                shape = "circle";
            } else if (cur->is_path) {
                style = "filled";
                fill_color = "#FFC107";
                font_color = "black";
                shape = "box";
            } else {
                style = "rounded,filled";
                fill_color = "#FE5F55";
                shape = "box";
            }

            dot << "    " << uid << " [label=\"" << label
                << "\", shape=" << shape << ", fillcolor=\"" << fill_color
                << "\", fontcolor=\"" << font_color << "\", style=\"" << style
                << "\"];" << endl;

            for (int i = 0; i < 3; ++i) {
                node *child = cur->c[i];
                if (child) {
                    string edge_label = "c[" + to_string(i) + "]";
                    string child_id = child->graph_id() + "_" + to_string(iter);

                    if (i == 2) {
                        dot << "    " << uid << " -> " << child_id
                            << " [label=\"" << edge_label
                            << "\", style=dashed, color=grey];" << endl;
                    } else {
                        dot << "    " << uid << " -> " << child_id
                            << " [label=\"" << edge_label << "\"];" << endl;
                    }

                    stk.push_back(child);
                }
            }
        }
    }

    void draw_forest() {
        dot << "\n  subgraph cluster_forest_" << iter << " {\n";
        dot << "    fontname=\"monospace\";\n";
        dot << "    label=\"Represented Forest\";\n";

        for (int v : forest_vertices) {
            string uid = "v" + to_string(v) + "_forest_" + to_string(iter);
            dot << "    " << uid << " [label=\"" << v
                << "\", shape=circle, fillcolor=\"#2196F3\", "
                   "style=\"filled\"];\n";
        }

        for (auto [a, b] : forest_edges) {
            string ua = "v" + to_string(a) + "_forest_" + to_string(iter);
            string ub = "v" + to_string(b) + "_forest_" + to_string(iter);
            dot << "    " << ua << " -> " << ub
                << " [dir=none, color=black];\n";
        }

        dot << "  }\n";
    }

  public:
    toptree_logger(const string &output_file = "toptree_history.dot") :
        filename(output_file) {

        dot.open(filename);
        if (!dot.is_open()) {
            cerr << "Could not open file " << filename << endl;
        }

        dot << "digraph TopTreeHistory {" << endl;
        dot << "  rankdir=TB;" << endl;
        dot << "  node [style=\"filled\", fontcolor=white, "
               "fontname=\"monospace\"];"
            << endl;
        dot << "  edge [fontname=\"monospace\"];" << endl;
    }

    ~toptree_logger() {
        dot << "}" << endl;
        dot.close();
        cerr << "\nGraphviz history generated: " << filename << endl;
    }

    void start(const string &desc = "") {
        assert(!logging);
        logging = true;
        cerr << "Iteration " << iter << ": " << desc << endl;
        start_subgraph(desc);
    }
    void add(node *p) { assert(logging), add_tree(p); }
    void end() {
        assert(logging), logging = false, end_subgraph();
        if constexpr (draw_graph) draw_forest();
        iter++;
    }
};
