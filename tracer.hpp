#ifndef TRACER_HPP_INCLUDED
#define TRACER_HPP_INCLUDED
#ifdef TRACE
#include <iostream>
#include <sstream>
class tracer_t {
    int trace_depth = 0;
    inline void prefix(int depth, int line, const std::string& fun) {
        std::cout << std::string(depth,' ') << depth << ":LINE " << line << ": " << fun  << "("; }
    inline void suffix() { std::cout << ") "; }
    template<class Arg, class... Args>
    inline void suffix(const Arg& arg, const Args&... args) {
        if (std::cout << stringify(arg), sizeof...(Args) > 0)
            std::cout << ",";
        suffix(args...); }
    inline void pause() { std::cout << std::endl, std::cin.get(); }
public:
    template<class Arg>
    inline std::string stringify(const Arg& arg) {
        std::stringstream ss;
        ss << arg;
        const auto s = ss.str();
        return std::is_same<Arg,std::string>::value ? "\""+s+"\"": s; }
    template<class... Args>
    inline void begin(int line, const std::string& fun, const Args&... args) {
        prefix(++trace_depth,line,fun), suffix(args...), std::cout << "called", pause(); }
    template<class... Args>
    inline void trace(int line, const std::string& fun, const Args&... args) {
        prefix(trace_depth,line,fun), suffix(args...), pause(); }
    template<class Ans, class... Args>
    inline Ans end(int line, const std::string& fun, const Ans& ans, const Args&... args) {
        prefix(trace_depth--,line,fun), suffix(args...), std::cout << "return value = " << ans, pause();
        return ans; } } tracer;
#define db(arg) std::string(#arg)+" = "+tracer.stringify(arg)
#define tr_begin(...) tracer.begin(__LINE__,__FUNCTION__,__VA_ARGS__)
#define tr(...)       tracer.trace(__LINE__,__FUNCTION__,__VA_ARGS__)
#define tr_end(...)   tracer.end(__LINE__,__FUNCTION__,__VA_ARGS__)
#else
#define tr_begin(...)
#define tr(...)
#define tr_end(ans,...) ans
#define db(arg) arg
#endif // TRACE
#endif // TRACER_HPP_INCLUDED
