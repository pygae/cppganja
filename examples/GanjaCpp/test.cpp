
#include <iostream>
#include <time.h>
#include "cga.h"
#include "../../GanjaScene.h"


// Convenience function to get a double in the range a -> b
double rand_float_range(double a, double b){
    return ((b - a) * ((double)rand() / RAND_MAX)) + a;
}


// Convenience function to get a random point near the origin
CGA random_point(double scale=1){
    return up(rand_float_range(-scale, scale), 
    	rand_float_range(-scale, scale), 
    	rand_float_range(-scale, scale));
}


// Convenience function to get a random line near the origin
CGA random_line(double scale=1){
    return (random_point(scale)^random_point(scale)^ni).normalized();
}


// Convenience function to get a random circle near the origin
CGA random_circle(double scale=1){
    return (random_point(scale)^random_point(scale)^random_point(scale)).normalized();
}


// Convenience function to get a random plane near the origin
CGA random_plane(double scale=1){
    return (random_point(scale)^random_point(scale)^random_point(scale)^ni).normalized();
}


int main (int argc, char **argv) {

	// We will seed the RNG to get different results
    unsigned int  seed = time(NULL);
    srand (seed);

    // Print the seed in case we like the look 
    // of the scene and want to recreate
    std::cout << "Seed: " << seed << std::endl;

    // Ok lets make some objects
    CGA point = random_point();
    CGA line = random_line();
    CGA circle = random_circle();
    CGA plane = random_plane();

    // Make the GanjaScene and add the objects to it
	GanjaScene gs = GanjaScene();
	gs.add_object(point, Color::BLACK); // You can specify color explicitly
	gs.add_object(line, Color::RED);
	gs.add_object(circle, Color::BLUE);
	gs.add_object(plane); // Or allow it to default to a semi-see-through grey

	// State what signature our algebra is from 
	std::vector<double> sig{1.0,1.0,1.0,1.0,-1.0};
	std::string html = generate_full_html(gs.as_string(), sig);

	// Write the output to an html file
	std::ofstream myfile;
	myfile.open ("example.html");
	myfile << html;
	myfile.close();


  return 0;
}