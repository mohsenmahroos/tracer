#ifndef TRACER_HPP_INCLUDED
#define TRACER_HPP_INCLUDED
#ifdef TRACE
#include <iostream>
namespace tracer {
    inline void pause() { std::cin.get(); }
    template<class Arg, class... Args>
    inline void pause(const Arg& arg, const Args&... args) { std::cout << arg, pause(args...); }
    class tracer_t {
        int depth = 0;
        inline std::string prefix(int line) const {
            return std::string(depth,' ')+std::to_string(depth)+":LINE "+std::to_string(line)+": "; }
        inline void comma_separated() const {}
        template<class Arg, class... Args>
        inline void comma_separated(const Arg& arg, const Args&... args) const {
            if (std::is_same<Arg,std::string>::value)
                std::cout << "\"" << arg << "\"";
            else
                std::cout << arg;
            if (sizeof...(Args) > 0)
                std::cout << ",", comma_separated(args...); }
        template<class... Args>
        inline void header(int line, const std::string& fun, const Args&... args) const {
            std::cout << prefix(line) << fun << "(", comma_separated(args...), std::cout << ") "; }
    public:
        template<class... Args>
        inline void begin(int line, const std::string& fun, const Args&... args) {
            ++depth, header(line,fun,args...), pause("called\n"); }
        template<class... Args>
        inline void trace(int line, const std::string& fun, const Args&... args) {
            header(line,fun,args...), pause("\n"); }
        template<class Ans, class... Args>
        inline Ans end(int line, const std::string& fun, const Ans& ans, const Args&... args) {
            header(line,fun,args...), --depth, pause("return value = ",ans,"\n");
            return ans; } } object; }
#define tr_begin(...) tracer::object.begin(__LINE__,__FUNCTION__,__VA_ARGS__)
#define tr(...)       tracer::object.trace(__LINE__,__FUNCTION__,__VA_ARGS__)
#define tr_end(...)   tracer::object.end(__LINE__,__FUNCTION__,__VA_ARGS__)
#else
#define tr_begin(...)
#define tr(...)
#define tr_end(ans,...) ans
#endif // TRACE
#endif // TRACER_HPP_INCLUDED
