#ifndef TRACER_HPP_INCLUDED
#define TRACER_HPP_INCLUDED
#ifdef TRACE
#include <iostream>
#include <sstream>

template<class Arg>
inline std::string stringify(const Arg& arg) {
    std::stringstream ss;
    ss << arg;
    const auto s = ss.str();
    return std::is_same<Arg,std::string>::value ? "\""+s+"\"": s; }

class tracer_t {
    int trace_depth = 0;
    inline void pause() { std::cout << std::endl, std::cin.get(); }
    template<class Arg, class... Args>
    inline void pause(const Arg& arg, const Args&... args) {
        std::cout << arg, pause(args...); }
    inline void prefix(int depth, int line, const std::string& fun) {
        std::cout << std::string(depth,' ') << depth << ":LINE " << line << ": " << fun  << "("; }
    inline void suffix() { std::cout << ") "; }
    template<class Arg, class... Args>
    inline void suffix(const Arg& arg, const Args&... args) {
        if (std::cout << stringify(arg), sizeof...(Args) > 0)
            std::cout << ",";
        suffix(args...); }
public:
    template<class... Args>
    inline void begin(int line, const std::string& fun, const Args&... args) {
        prefix(++trace_depth,line,fun), suffix(args...), pause("called"); }
    template<class... Args>
    inline void trace(int line, const std::string& fun, const Args&... args) {
        prefix(trace_depth,line,fun), suffix(args...), pause(); }
    template<class Ans, class... Args>
    inline Ans end(int line, const std::string& fun, const Ans& ans, const Args&... args) {
        prefix(trace_depth--,line,fun), suffix(args...), pause("return value = ",ans);
        return ans; } } object;

#define tr_begin(...) object.begin(__LINE__,__FUNCTION__,__VA_ARGS__)
#define tr(...)       object.trace(__LINE__,__FUNCTION__,__VA_ARGS__)
#define tr_end(...)   object.end(__LINE__,__FUNCTION__,__VA_ARGS__)
#define db(arg) std::string(#arg)+" = "+stringify(arg)

#else

#define tr_begin(...)
#define tr(...)
#define tr_end(ans,...) ans
#define db(arg) arg

#endif // TRACE
#endif // TRACER_HPP_INCLUDED
