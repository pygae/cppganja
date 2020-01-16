# cppganja - C++ interface to ganja.js
A very simple/limited interface to [ganja.js](https://github.com/enkimute/ganja.js) written for c++

# Interface example

```
// A couple of example CGA objects
std::vector<double> test_obj{0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,4.23135483,4.23135483,0.48031496,0.48031496,0.95680003,1.2228812,1.2228812,-0.06350011,-0.28372776,0.,0.,0.,0.,0.,0.};
std::vector<double> test_obj2{0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,-0.08525168,3.49464756,3.52703718,-1.59496133,-1.62835966,0.76309611,0.64874369,0.65012918,0.18968262,-0.22823195,0.,0.,0.,0.,0.,0.};

// Make the scene and add the objects
GanjaScene gs = GanjaScene();
gs.add_object(test_obj);
gs.add_object(test_obj2, Color::RED);

// State what signature our algebra is from 
std::vector<double> sig{1.0,1.0,1.0,1.0,-1.0};
std::string html = generate_full_html(gs.as_string(), sig, 0.1);

// Write the output to an html file
std::ofstream myfile;
myfile.open ("example.html");
myfile << html;
myfile.close();
```

![Interface example](./ExampleImage.png?raw=true)

# Ganja.js generated C++ Example

```

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
```
![Ganja cpp example 2](./ExampleImage2.png?raw=true)
