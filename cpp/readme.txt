start
https://github.com/IntelRealSense/librealsense


WORKS
g++ -std=c++11 -I/home/miguel/Documents/06Git-Bitbucket/mike/librealsense/examples -I/home/miguel/Documents/06Git-Bitbucket/mike/librealsense/third-party/glfw/include 01-Example.cpp -o example -lGL -lGLU -lrealsense2 -lglfw

g++ -std=c++11 -I/home/miguel/Documents/06Git-Bitbucket/mike/librealsense/third-party 02-Save.cpp -o save -lrealsense2

g++ -std=c++11 03-imshow-OpenCV.cpp -o imshow -lrealsense2 `pkg-config --cflags --libs opencv`

g++ -std=c++11 -I/home/miguel/Documents/06Git-Bitbucket/mike/librealsense/wrappers/opencv 04-grabcuts.cpp -o grabcuts -lrealsense2 `pkg-config --libs opencv`


g++ -std=c++11 -I/home/miguel/Documents/06Git-Bitbucket/mike/librealsense/third-party 000-saveLR-Image.cpp -o saveLR -lrealsense2 `pkg-config --libs opencv`


Ubuntu18.04
g++ -std=c++11 -I/home/miguel/Documents/01GitProjects/github/librealsense/examples -I/home/miguel/Documents/01GitProjects/github/librealsense/third-party/glfw/include 01-Example.cpp -o example -lGL -lGLU -lrealsense2 -lglfw

NOT-WORKS
g++ -std=c++11 -I/home/miguel/Documents/06Git-Bitbucket/mike/librealsense/examples -I/home/miguel/Documents/06Git-Bitbucket/mike/librealsense/third-party/imgui 05-align.cpp -o align -lrealsense2 -lGL -lGLU -lglfw

