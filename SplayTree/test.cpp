#include <iostream>
#include <fstream>
#include <map>
#include <chrono>
#include <random>
#include "SplayTree.h"

int main(int argc, char** argv){
   // typedef std::chrono::duration<int, std::milli> millisecs_t;
    typedef std::chrono::high_resolution_clock clock;
    std::chrono::high_resolution_clock::time_point start, end;
    pl::SplayTree<int,int> splay;
    std::map<size_t, size_t> rb;

    std::random_device rd;
    std::default_random_engine gen(rd());    

   
    std::ofstream outp;
    outp.open("test.txt");
    
    for (size_t i = 10; i < 10000000; i=i * 10){
        
        start = clock::now();
        for (size_t range=0; range < i; ++range)
            splay.insert(range, range);
         end = clock::now();
      
        std::cout << "init of splaytree: elements: " << i << " time: " << 
            std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;
        
         start = clock::now();
        for (size_t range=0; range < i; ++range)
            rb.insert(std::make_pair(range, range));
        end = clock::now();
       std::cout << "init of r-b tree: elements: " << i << " time: " <<
       std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;

       for (size_t range = 2; range < i; range = range * 2){
           std::uniform_int_distribution<> dis(i/2-range/2, i/2+range/2);
           start = clock::now();
           for (size_t repeat = 0; repeat < 10000000; ++repeat){
               splay.find(dis(gen));
           }
           end = clock::now();
           auto splay_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
         
           start = clock::now();
           for (size_t repeat = 0; repeat < 10000000; ++repeat){
               rb.find(dis(gen));
           }
           end = clock::now();
           auto rb_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
           if (splay_time>rb_time){
               std::cout << "RB is faster than SplayTree: range: " << range <<" splay_time: "<<splay_time<<" RB_time: "<<rb_time<<std::endl;
               break;
           }else std::cout << "SplayTree is faster than RB: range: " << range << " splay_time: " << splay_time << " RB_time: " << rb_time << std::endl;


       }
       rb.clear();
       splay.clear();
           
    }
    outp.close();
}