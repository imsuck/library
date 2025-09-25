template<class TreeDP, class STT> struct DDP {
    using Info = typename TreeDP::Info;
    using Point = typename TreeDP::Point;
    using Path = typename TreeDP::Path;

    STT &stt;
    int n, m, rt;
    vector<Info> info;
    vector<Point> point;
    vector<Path> path;

    void pull(int v) {
        if (stt[v].t == Vertex) {
            path[v] = TreeDP::vertex(info[v]);
        } else if (stt[v].t == AddVertex) {
            path[v] = TreeDP::add_vertex(point[stt[v].l], info[v]);
        } else if (stt[v].t == AddEdge) {
            point[v] = TreeDP::add_edge(path[stt[v].l]);
        } else if (stt[v].t == Compress) {
            path[v] = TreeDP::compress(path[stt[v].l], path[stt[v].r]);
        } else if (stt[v].t == Rake) {
            point[v] = TreeDP::rake(point[stt[v].l], point[stt[v].r]);
        }
    }

    DDP(int _n, STT &_stt, [[maybe_unused]] TreeDP _dp) :
        stt(_stt), n(_n), m(stt.size()), info(n), point(m), path(m) {}
    void build() {
        y_comb([&](auto &dfs, int v) -> void {
            if (stt[v].l != -1) dfs(stt[v].l);
            if (stt[v].r != -1) dfs(stt[v].r);
            pull(v);
        })(stt.rt);
    }
    void pull_from(int v) {
        for (; v != -1; v = stt[v].p) pull(v);
    }
    void set(int v, const Info &x) { info[v] = x, pull_from(v); }
    Path query() { return path[stt.rt]; }
};
