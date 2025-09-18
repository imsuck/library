struct subsets {
    subsets(int m) : s(m), mask(m) {}

    subsets begin() const { return *this; }
    subsets end() const { return {0}; }
    bool operator!=(subsets) const { return s != -1; }
    void operator++() { s--; }
    int operator*() { return s &= mask; }

  private:
    int s, mask;
};
