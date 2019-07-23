
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <fstream>
#include <stdexcept>
#include "color.h"



std::string read_ganja()
{
    std::string fileName = "ganja.js";
    std::ifstream ifs(fileName.c_str(), std::ios::in | std::ios::binary | std::ios::ate);
    std::ifstream::pos_type fileSize = ifs.tellg();
    ifs.seekg(0, std::ios::beg);
    std::vector<char> bytes(fileSize);
    ifs.read(bytes.data(), fileSize);
    return std::string(bytes.data(), fileSize);
}


std::string generate_full_html(std::string script_json, std::vector<double> sig, double scale=1.0, bool grid=true, bool gl=true){
    int p = std::count_if(sig.begin(), sig.end(), [](double i){return i > 0;});
    int q = std::count_if(sig.begin(), sig.end(), [](double i){return i < 0;});
    auto r = sig.size() - p - q;
    std::string conformal = "false";
    if (q!=0){
        conformal = "true";
    }
    int mv_length = pow(2, sig.size());
    std::string sig_short = std::to_string(p)+ "," + std::to_string(q) + "," + std::to_string(r);
    if (sig_short.compare("4,1,0")||sig_short.compare("3,0,0")||sig_short.compare("3,0,1")){
        std::string gridstr = "true";
        if (!grid){
            std::string gridstr = "false";
        } 
        std::string scalestr = std::to_string(scale);
        // Load ganja and build file
        std::string script_string = "\n"
                "Algebra("+sig_short+",()=>{\n"
                  "var canvas = this.graph((" + script_json + ").map(x=>x.length=="+std::to_string(mv_length)+"?new Element(x):x),\n"
                  "{conformal:"+conformal+",gl:"+std::to_string(gl)+",grid:"+gridstr+",scale:"+scalestr+",useUnnaturalLineDisplayForPointPairs:true});\n"
                  "canvas.style.width = '100vw';\n"
                  "canvas.style.height = '100vh';\n"
                  "document.body.appendChild(canvas);\n"
                "});\n"
                "\n";

        std::string full_html = "<!DOCTYPE html>\n"
        "<html lang=\"en\" style=\"height:100%;\">\n"
        "<HEAD>\n"
            "<meta charset=\"UTF-8\">\n"
            "<title>pyganja</title>\n"
          "<SCRIPT>" + read_ganja() + "</SCRIPT>\n"
        "</HEAD>\n"
        "<BODY style=\"position:absolute; top:0; bottom:0; right:0; left:0; overflow:hidden;\">\n"
        "<SCRIPT>\n"
            "" + script_string + "\n"
        "</SCRIPT>\n"
        "</BODY>\n"
        "</html>\n"
        "\n";
        
        std::cout << full_html;
        return full_html;
    }
    else{
        throw std::runtime_error("Incompatible algebra signature provided");
    }
}



class GanjaScene {
public:
    unsigned int mv_length;
    std::vector<std::vector<double> > internal_array; // For now just store an array of values
    std::vector<unsigned int> color_array; // Every value array has a color for now

    void add(GanjaScene other){
         GanjaScene gs = GanjaScene();
         
    }

    void add_object(std::vector<double> object_array, unsigned int color=0xAA000000){
        mv_length = (unsigned int) object_array.size();
        internal_array.push_back(object_array);
        color_array.push_back(color);
    }

    void add_objects(std::vector<std::vector<double> > object_array_array, unsigned int color=0xAA000000){
        for (int i=0; i<object_array_array.size(); i++){
            add_object(object_array_array[i], color);
        }
    }

    std::string as_string(void ){
        std::string output_string = "[";
        for(int i=0; i<internal_array.size(); i++){
            std::cout << "i: " << i << "\n";
            std::vector<double > thisobj = internal_array[i];
            auto color = color_array[i];
            output_string += std::to_string(color) + ",[";
            for(int j=0; j<thisobj.size(); j++){
                std::cout << "j: " << j << "\n";
                std::string sobj_j = std::to_string(thisobj[j]);
                output_string += sobj_j;
                if (j < (thisobj.size() -1)){
                    output_string += ",";
                }
            }
            output_string += "]";
            if (i < (internal_array.size() -1)){
                output_string += ",";
            }
        }
        std::cout << "don\n";

        std::string s_mv_length = std::to_string(mv_length);
        output_string += "].map(x=>x.length==" + s_mv_length + "?new Element(x):x)";
        return output_string;
    }

};


int main(){

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

    return 0;
}

