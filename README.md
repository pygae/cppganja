# cppganja - C++ interface to ganja.js
A very simple/limited interface to [ganja.js](github.com/hugohadfield/cppganja) written for c++

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
