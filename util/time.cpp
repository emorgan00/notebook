auto now() {
    return chrono::steady_clock::now();
}

template<typename T>
string delta(T a, T b) {
    return to_string(chrono::duration_cast<chrono::milliseconds>(b-a))+"ms";
}