#include<iostream>
#include<string>
namespace mathoperations{
    class Print{
        public:
        std::string s = "Inside Math Operations namespace";
        void printS(){
            std::cout<<s<<std::endl;
        }
    };
    namespace arithmetic{
        template <typename T>
        T add(T x,T y){
            return x+y;
        }
        template <typename T>
        T sub(T x,T y){
            return x-y;
        }
        template <typename T>
        T mul(T x,T y){
            return x*y;
        }
        template <typename T>
        T div(T x,T y){
            return x/y;
        }
        inline namespace minMax{
            template<typename T>
            T min(T x,T y){
                if(x > y) return y;
                return x;
            }
            template <typename T>
            T max(T x,T y){
                if(x > y) return x;
                return y;
            }
        }
    }
}