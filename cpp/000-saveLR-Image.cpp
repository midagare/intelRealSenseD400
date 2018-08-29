#include <librealsense2/rs.hpp> // Include RealSense Cross Platform API
#include <opencv2/opencv.hpp>   // Include OpenCV API

#include <fstream>              // File IO
#include <iostream>             // Terminal IO
#include <sstream>              // Stringstreams

// 3rd party header for writing png files
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

int main(int argc, char * argv[])
{
	int width = 1280;
	int height = 720;
	int fps = 30;

	const auto window_name_l = "img_l";
    namedWindow(window_name_l, cv::WINDOW_NORMAL);

    const auto window_name_r = "img_r";
    namedWindow(window_name_r, cv::WINDOW_NORMAL);

    const auto window_name_d = "depth";
    namedWindow(window_name_d, cv::WINDOW_NORMAL);

    // Declare depth colorizer for pretty visualization of depth data
    rs2::colorizer color_map;

	//Create a configuration for configuring the pipeline with a non default profile
	rs2::config cfg;

	//Add desired streams to configuration
	cfg.enable_stream(RS2_STREAM_INFRARED, 1, width, height, RS2_FORMAT_Y8, fps);
	cfg.enable_stream(RS2_STREAM_INFRARED, 2, width, height, RS2_FORMAT_Y8, fps);
	cfg.enable_stream(RS2_STREAM_DEPTH, width, height, RS2_FORMAT_Z16, fps);
	
	// Declare RealSense pipeline, encapsulating the actual device and sensors
    rs2::pipeline pipe;

    //Instruct pipeline to start streaming with the requested configuration
    pipe.start(cfg);

    // Capture 30 frames to give autoexposure, etc. a chance to settle
    for (auto i = 0; i < 30; ++i) pipe.wait_for_frames();

    while (1) // Application still alive?
	{
	    // wait for frames and get frameset
		rs2::frameset frameset = pipe.wait_for_frames();
	    // get single infrared frame from frameset
		//rs2::video_frame ir_frame = frameset.get_infrared_frame();

		// get left and right infrared frames from frameset
		rs2::video_frame ir_frame_left = frameset.get_infrared_frame(1);
		rs2::video_frame ir_frame_right = frameset.get_infrared_frame(2);
		rs2::video_frame depth_frame = color_map(frameset.get_depth_frame());

		cv::Mat dMat_left = cv::Mat(cv::Size(width, height), CV_8UC1, (void*)ir_frame_left.get_data());
		cv::Mat dMat_right = cv::Mat(cv::Size(width, height), CV_8UC1, (void*)ir_frame_right.get_data());
		cv::Mat dMat_depth = cv::Mat(cv::Size(width, height), CV_8UC1, (void*)depth_frame.get_data());

		cv::imshow(window_name_l, dMat_left);
		cv::imshow(window_name_r, dMat_right);
		cv::imshow(window_name_d, dMat_depth);
		char c = cv::waitKey(1);
		if (c == 's')
		{

		}
		else if (c == 'q')
			break;
	}


	// wait for frames and get frameset
	rs2::frameset frameset = pipe.wait_for_frames();
    // get single infrared frame from frameset
	//rs2::video_frame ir_frame = frameset.get_infrared_frame();

	// get left and right infrared frames from frameset
	rs2::video_frame ir_frame_left = frameset.get_infrared_frame(1);
	rs2::video_frame ir_frame_right = frameset.get_infrared_frame(2);

	cv::Mat dMat_left = cv::Mat(cv::Size(width, height), CV_8UC1, (void*)ir_frame_left.get_data());
	cv::Mat dMat_right = cv::Mat(cv::Size(width, height), CV_8UC1, (void*)ir_frame_right.get_data());

	cv::imshow(window_name_l, dMat_left);
	cv::imshow(window_name_r, dMat_right);

	rs2::video_frame vf = ir_frame_left;
	// Write images to disk
    std::stringstream png_file;
    png_file << window_name_l << vf.get_profile().stream_name() << ".png";
    stbi_write_png(png_file.str().c_str(), vf.get_width(), vf.get_height(),
                   vf.get_bytes_per_pixel(), vf.get_data(), vf.get_stride_in_bytes());
    std::cout << "Saved " << png_file.str() << std::endl;


    vf = ir_frame_right;

    std::stringstream png_file_r;
    png_file_r << window_name_r << vf.get_profile().stream_name() << ".png";
    stbi_write_png(png_file_r.str().c_str(), vf.get_width(), vf.get_height(),
                   vf.get_bytes_per_pixel(), vf.get_data(), vf.get_stride_in_bytes());
    std::cout << "Saved " << png_file_r.str() << std::endl;


/*
    //Get each frame
	rs2::frame ir_frame = frames.first(RS2_STREAM_INFRARED);
	rs2::frame depth_frame = frames.get_depth_frame();




	rs2::frameset data = pipe.wait_for_frames(); // Wait for next set of frames from the camera
    rs2::frame depth = color_map(data.get_depth_frame());

    // Query frame size (width and height)
    const int w = depth.as<rs2::video_frame>().get_width();
    const int h = depth.as<rs2::video_frame>().get_height();

    // Create OpenCV matrix of size (w,h) from the colorized depth data
    Mat image(Size(w, h), CV_8UC3, (void*)depth.get_data(), Mat::AUTO_STEP);

    // Update the window with new data
    imshow(window_name, image);
*/
    return EXIT_SUCCESS;
}