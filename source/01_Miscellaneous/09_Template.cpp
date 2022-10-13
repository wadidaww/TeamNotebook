#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse4")
template<class A, class B>
ostream& operator<<(ostream& os, const pair<A, B> &p) {
    os << '(' << p.first << ',' << p.second << ')';
    return os;
}
template<class T>
ostream& operator<<(ostream& os, const vector<T> &v) {
    bool fs = 1; os << '{';
    for(auto &i : v) { if(!fs) os << ", "; os << i; fs = 0; }
    os << '}'; return os;
}
