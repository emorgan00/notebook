struct ahocorasick {

    struct node {
        int p; // the parent of this node in the transition graph
        int c; // the character by which p transitions to this node
        int link; // suffix link
        int exit; // exit link
        int leaf; // indicates how many words in the dictionary end here
        map<int, int> adj; // transitions of form {char, destination}
    };

    // state 0 = empty string

    int n = 1;
    vector<node> a;

    ahocorasick() : a({{0, 0, 0, -2, 0, {}}}) {}

    // adds a string to the dictionary of the automaton,
    // and returns the state corresponding to that string
    template<typename it>
    int insert(it first, it last) {
        int v = 0;
        for (it i = first; i != last; i++) {
            if (!a[v].adj.count(*i))
                a.push_back({v, *i, -1, -2, 0, {}}), a[v].adj[*i] = n++;
            v = a[v].adj[*i];
        } a[v].leaf++;
        return v;
    }

    int insert(string str) { return insert(str.begin(), str.end()); }

    // returns the state corresponding to the longest proper suffix
    // of x which is a prefix of one of the words in the dictionary.
    // runs in O(log(min(n, K))) time (amortized).
    int link(int x) {
        if (a[x].link != -1) return a[x].link;
        return a[x].link = a[x].p == 0 ? 0 : push(link(a[x].p), a[x].c);
    }

    // let x be the state corresponding to string s, then this returns
    // the state corresponding to the longest suffix of (s + character c)
    // which is a prefix of one of the words in the dictionary.
    // runs in O(log(min(n, K))) time (amortized).
    int push(int x, int c) {
        if (a[x].adj.count(c)) return a[x].adj[c];
        return a[x].adj[c] = x == 0 ? 0 : push(link(x), c);
    }

    // returns the state corresponding to the longest suffix
    // of x which is exactly equal to one of the words in the dictionary,
    // or -1 if no such suffix exists.
    // runs in O(log(min(n, K))) time (amortized).
    int exit(int x) {
        if (a[x].exit != -2) return a[x].exit;
        if (x == 0 && !a[x].leaf) return a[x].exit = -1;
        return a[x].exit = a[x].leaf ? x : exit(link(x));
    }

    // returns the state corresponding to the input string, runs in O(input).
    template<typename it>
    int find(it first, it last) {
        int x = 0;
        for (it i = first; i != last; i++)
            x = push(x, *i);
        return x;
    }

    int find(string str) { return find(str.begin(), str.end()); }

    // returns the string corresponding to state x, runs in O(output).
    string print(int x) {
        string str = "";
        while (x) str += a[x].c, x = a[x].p;
        reverse(str.begin(), str.end());
        return str;
    }
};