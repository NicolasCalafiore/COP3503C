#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>
#include <cstring>
#include <functional>
#include <map>

using namespace std;

struct Header {
    char idLength;
    char colorMapType;
    char dataTypeCode;
    short colorMapOrigin;
    short colorMapLength;
    char colorMapDepth;
    short xOrigin;
    short yOrigin;
    short width;
    short height;
    char bitsPerPixel;
    char imageDescriptor;
};

struct Pixel{
    unsigned char R;
    unsigned char G;
    unsigned char B;
};

//Prototypes
bool OpenFile(string path, ifstream& file);
void PrintPixel(Pixel* pixel, string pixel_name = "", bool does_endl = true);
void WriteTGAFile(string path, const vector<Pixel>& pixel_map, Header& header);
void CompareFilesBinary(string path_one, string path_two, Header* header, bool is_debug, string file_one_name, string file_two_name);
bool PixelsAreEqual(Pixel pixel_one, Pixel pixel_two);
void MultiplyMethod(vector<Pixel>& pixels_one, vector<Pixel>& pixels_two);
void SubtractMethod(vector<Pixel>& pixels_one, vector<Pixel>& pixels_two);
void OverlayMethod(vector<Pixel>& pixel_map, vector<Pixel>& secondary_pixel_map);
void ScreenMethod(vector<Pixel>& pixel_map, vector<Pixel>& secondary_pixel_map);
vector<Pixel*>* AdditionMethod(const vector<Pixel*>* pixels_one, const vector<Pixel*>* pixels_two);
void FlipImage(vector<Pixel>& pixel_map);
void HelpMessage();
void InvalidFileMessage();
bool IsValidFile(string value);
void FileDoesNotExist();
void CLIMultiply(int& arg_index, char* argv[], vector<Pixel>& pixel_map);
bool OutputIsValid(string path);
bool CLIOpenFile(string path, ifstream& file);
bool InputIsValid(string path, ifstream& file, bool is_argument);
Header CLIGetHeader(ifstream& file);
void CLIReadPixels(ifstream& file, vector<Pixel>& pixel_map, Header& header);
void CLISubstract(int& arg_index, char* argv[], vector<Pixel>& pixel_map);
void CLIOverlay(int& arg_index, char* argv[], vector<Pixel>& pixel_map);
void CLIScreen(int& arg_index, char* argv[], vector<Pixel>& pixel_map);
void CLICombine(int& arg_index, char* argv[], vector<Pixel>& red_pixel_map);
void CombineMethod(vector<Pixel>& pixel_map, vector<Pixel>& red_map, vector<Pixel>& green_map, vector<Pixel>& blue_map);
void FlipImage(vector<Pixel>& pixel_map);
void CLIFlip(int& arg_index, char* argv[], vector<Pixel>& pixel_map);
void CLIColorRestricted(bool only_red, bool only_green, bool only_blue, int& arg_index, char* argv[], vector<Pixel>& pixel_map);
void CLIAddColor(bool only_red, bool only_green, bool only_blue, int& arg_index, char* argv[], vector<Pixel>& pixel_map);
void CLIScaleColor(bool only_red, bool only_green, bool only_blue, int& arg_index, char* argv[], vector<Pixel>& pixel_map);


int main(int argc, char *argv[]){
    //OUTPUT_FILE argv[1]
    //SOURCE_FILE argv[2]
    //METHOD argv[3]

    if(argc == 1 || strcmp(argv[1], "--help") == 0) { HelpMessage(); return 0;}

    if(!OutputIsValid(argv[1])) return -1;

    ifstream file;
    if(!InputIsValid(argv[2], file, false)) return -1;
    Header file_header = CLIGetHeader(file);
    vector<Pixel> pixel_map;
    CLIReadPixels(file, pixel_map, file_header);

    int arg_index = 2;

    while(arg_index < argc - 1){

        arg_index++;

        if(strcmp(argv[arg_index], "multiply") == 0)
            CLIMultiply(arg_index, argv, pixel_map);

        else if(strcmp(argv[arg_index], "subtract") == 0)
            CLISubstract(arg_index, argv, pixel_map);

        else if(strcmp(argv[arg_index], "overlay") == 0)
            CLIOverlay(arg_index, argv, pixel_map);

        else if(strcmp(argv[arg_index], "screen") == 0)
            CLIScreen(arg_index, argv, pixel_map);

        else if(strcmp(argv[arg_index], "combine") == 0)
            CLICombine(arg_index, argv, pixel_map);

        else if(strcmp(argv[arg_index], "flip") == 0)
            CLIFlip(arg_index, argv, pixel_map);

        //bool CLIColorRestricted(bool only_red, bool only_green, bool only_blue, int& arg_index, char* argv[], vector<Pixel>& pixel_map);
        else if(strcmp(argv[arg_index], "onlyred") == 0)
            CLIColorRestricted(true, false, false, arg_index, argv, pixel_map);

        else if(strcmp(argv[arg_index], "onlygreen") == 0)
            CLIColorRestricted(false, true, false, arg_index, argv, pixel_map);

        else if(strcmp(argv[arg_index], "onlyblue") == 0)
            CLIColorRestricted(false, false, true, arg_index, argv, pixel_map);

        else if(strcmp(argv[arg_index], "addred") == 0)
            CLIAddColor(true, false, false, arg_index, argv, pixel_map);

        else if(strcmp(argv[arg_index], "addgreen") == 0)
            CLIAddColor(false, true, false, arg_index, argv, pixel_map);

        else if(strcmp(argv[arg_index], "addblue") == 0)
            CLIAddColor(false, false, true, arg_index, argv, pixel_map);

        else if(strcmp(argv[arg_index], "scalered") == 0)
            CLIScaleColor(true, false, false, arg_index, argv, pixel_map);

        else if(strcmp(argv[arg_index], "scalegreen") == 0)
            CLIScaleColor(false, true, false, arg_index, argv, pixel_map);

        else if(strcmp(argv[arg_index], "scaleblue") == 0)
            CLIScaleColor(false, false, true, arg_index, argv, pixel_map);
        else{
            cout << "Invalid method name." << endl;
            return -1;
        }
    }



    WriteTGAFile(argv[1], pixel_map, file_header);
    return 0;
}

void HelpMessage(){
    cout << "Project 2: Image Processing, Fall 2023" << endl << endl;
    cout << "Usage:" << endl;
    cout << "\t./project2.out [output] [firstImage] [method] [...]" << endl;
}
void InvalidFileMessage(){
    cout << "Invalid file name." << endl;
}
void FileDoesNotExist(){
    cout << "File does not exist." << endl;
}
bool IsValidFile(string value){

    if(value[value.size() - 1] != 'a') return false;
    if(value[value.size() - 2] != 'g') return false;
    if(value[value.size() - 3] != 't') return false;
    if(value[value.size() - 4] != '.') return false;
    return true;
}
Header CLIGetHeader(ifstream& file){

    Header header{};
    file.read(&header.idLength, sizeof(header.idLength));
    file.read(&header.colorMapType, sizeof(header.colorMapType));
    file.read(&header.dataTypeCode, sizeof(header.dataTypeCode));
    file.read(reinterpret_cast<char*>(&header.colorMapOrigin), sizeof(header.colorMapOrigin));
    file.read(reinterpret_cast<char*>(&header.colorMapLength), sizeof(header.colorMapLength));
    file.read(&header.colorMapDepth, sizeof(header.colorMapDepth));
    file.read(reinterpret_cast<char*>(&header.xOrigin), sizeof(header.xOrigin));
    file.read(reinterpret_cast<char*>(&header.yOrigin), sizeof(header.yOrigin));
    file.read(reinterpret_cast<char*>(&header.width), sizeof(header.width));
    file.read(reinterpret_cast<char*>(&header.height), sizeof(header.height));
    file.read(&header.bitsPerPixel, sizeof(header.bitsPerPixel));
    file.read(&header.imageDescriptor, sizeof(header.imageDescriptor));

    return header;
}


void CLIMultiply(int& arg_index, char* argv[], vector<Pixel>& pixel_map){
    cout << "CLI Multiply" << endl;
    arg_index++;
    ifstream secondary_file;
    if(!InputIsValid(argv[arg_index], secondary_file, true)){
        cout << "Invalid argument, invalid file name";
        exit(-1);
    }

    Header secondary_header = CLIGetHeader(secondary_file);
    vector<Pixel> secondary_pixel_map;
    CLIReadPixels(secondary_file, secondary_pixel_map, secondary_header);

    MultiplyMethod(pixel_map, secondary_pixel_map);

}
void CLISubstract(int& arg_index, char* argv[], vector<Pixel>& pixel_map){
    cout << "CLI Subtract" << endl;
    arg_index++;
    ifstream secondary_file;
    if(!InputIsValid(argv[arg_index], secondary_file, true)){
        InvalidFileMessage();
        exit(-1);
    }

    Header secondary_header = CLIGetHeader(secondary_file);
    vector<Pixel> secondary_pixel_map;
    CLIReadPixels(secondary_file, secondary_pixel_map, secondary_header);

    SubtractMethod(pixel_map, secondary_pixel_map);

}
void CLIOverlay(int& arg_index, char* argv[], vector<Pixel>& pixel_map){
    cout << "CLI Overlay" << endl;
    arg_index++;
    ifstream secondary_file;
    if(!InputIsValid(argv[arg_index], secondary_file, true)){
        InvalidFileMessage();
        exit(-1);
    }

    Header secondary_header = CLIGetHeader(secondary_file);
    vector<Pixel> secondary_pixel_map;
    CLIReadPixels(secondary_file, secondary_pixel_map, secondary_header);

    OverlayMethod(pixel_map, secondary_pixel_map);

}
void CLIScreen(int& arg_index, char* argv[], vector<Pixel>& pixel_map){
    cout << "CLI Screen" << endl;
    arg_index++;
    ifstream secondary_file;
    if(!InputIsValid(argv[arg_index], secondary_file, true)){
        InvalidFileMessage();
        exit(-1);
    }

    Header secondary_header = CLIGetHeader(secondary_file);
    vector<Pixel> secondary_pixel_map;
    CLIReadPixels(secondary_file, secondary_pixel_map, secondary_header);

    ScreenMethod(pixel_map, secondary_pixel_map);

}
void CLICombine(int& arg_index, char* argv[], vector<Pixel>& red_pixel_map){
    cout << "CLI Combine" << endl;
    arg_index++;

    ifstream green_file;
    if(!InputIsValid(argv[arg_index], green_file, true)){
        InvalidFileMessage();
        exit(-1);
    }
    arg_index++;

    ifstream blue_file;
    if(!InputIsValid(argv[arg_index], blue_file, true)){
        InvalidFileMessage();
        exit(-1);
    }

    Header green_header = CLIGetHeader(green_file);
    Header blue_header = CLIGetHeader(blue_file);

    vector<Pixel> green_pixel_map;
    CLIReadPixels(green_file, green_pixel_map, green_header);

    vector<Pixel> blue_pixel_map;
    CLIReadPixels(blue_file, blue_pixel_map, blue_header);

    vector<Pixel> pixel_map;
    CombineMethod(pixel_map, red_pixel_map, green_pixel_map, blue_pixel_map);

    red_pixel_map = pixel_map;

}
void CLIFlip(int& arg_index, char* argv[], vector<Pixel>& pixel_map){
    cout << "CLI Flip" << endl;
    FlipImage(pixel_map);
    exit(-1);
}
void CLIColorRestricted(bool only_red, bool only_green, bool only_blue, int& arg_index, char* argv[], vector<Pixel>& pixel_map){
    cout << "CLIColorRestricted" << endl;
    for(auto & i : pixel_map){

        if(only_red){
            i.G = i.R;
            i.B = i.R;
        }
        if(only_green){
            i.R = i.G;
            i.B = i.G;
        }
        if(only_blue){
            i.G = i.B;
            i.R = i.B;
        }
    }

}
void CLIAddColor(bool only_red, bool only_green, bool only_blue, int& arg_index, char* argv[], vector<Pixel>& pixel_map){
    cout << "CLIAddColor" << endl;
    arg_index++;
    int amount = stoi(argv[arg_index]);

    for(auto & i : pixel_map){

        if(only_red){
            i.R = i.R + amount < 255 ? i.R + amount : 255;
        }
        if(only_green){
            i.G = i.G + amount < 255 ? i.G + amount : 255;
        }
        if(only_blue){
            i.B = i.B + amount < 255 ? i.B + amount : 255;
        }
    }

}
void CLIScaleColor(bool only_red, bool only_green, bool only_blue, int& arg_index, char* argv[], vector<Pixel>& pixel_map){
    cout << "CLIScaleColor" << endl;
    arg_index++;
    int amount = stoi(argv[arg_index]);

    for(auto & i : pixel_map){

        if(only_red){
            i.R = i.R * amount < 255 ? i.R * amount : 255;
        }
        if(only_green){
            i.G = i.G * amount < 255 ? i.G * amount : 255;
        }
        if(only_blue){
            i.B = i.B * amount < 255 ? i.B * amount : 255;
        }
    }

}

void CLIReadPixels(ifstream& file, vector<Pixel>& pixel_map, Header& header){
    for(int i = 0; i < header.width; i++){
        for(int j = 0; j < header.height; j++){
            Pixel pixel;
            file.read(reinterpret_cast<char*>(&pixel.B), sizeof(pixel.B));
            file.read(reinterpret_cast<char*>(&pixel.G), sizeof(pixel.G));
            file.read(reinterpret_cast<char*>(&pixel.R), sizeof(pixel.R));
            pixel_map.push_back(pixel);
        }
    }
}
bool OutputIsValid(string path){
    if(!IsValidFile(path)){
        InvalidFileMessage();
        return false;
    }

    return true;
}
bool InputIsValid(string path, ifstream& file, bool is_argument){
    if(!IsValidFile(path)){
        if(!is_argument) InvalidFileMessage();
        if(is_argument) cout << "Invalid argument, invalid file name." << endl;
        return false;
    }
    if(!CLIOpenFile(path, file)){
        if(!is_argument) FileDoesNotExist();
        if(is_argument) cout << "Invalid argument, file does not exist." << endl;
        return false;
    }

    return true;
}
bool CLIOpenFile(string path, ifstream& file){
    file.open("./" + path, ios::binary);;
    if(file.is_open()) return true;
    else return false;
}



void WriteTGAFile(string path, const vector<Pixel>& pixel_map, Header& header){
    ofstream output_file("./" + path, ios::binary);

    // Write header
    output_file.write(&header.idLength, sizeof(header.idLength));
    output_file.write(&header.colorMapType, sizeof(header.colorMapType));
    output_file.write(&header.dataTypeCode, sizeof(header.dataTypeCode));
    output_file.write(reinterpret_cast<char*>(&header.colorMapOrigin), sizeof(header.colorMapOrigin));
    output_file.write(reinterpret_cast<char*>(&header.colorMapLength), sizeof(header.colorMapLength));
    output_file.write(&header.colorMapDepth, sizeof(header.colorMapDepth));
    output_file.write(reinterpret_cast<char*>(&header.xOrigin), sizeof(header.xOrigin));
    output_file.write(reinterpret_cast<char*>(&header.yOrigin), sizeof(header.yOrigin));
    output_file.write(reinterpret_cast<char*>(&header.width), sizeof(header.width));
    output_file.write(reinterpret_cast<char*>(&header.height), sizeof(header.height));
    output_file.write(&header.bitsPerPixel, sizeof(header.bitsPerPixel));
    output_file.write(&header.imageDescriptor, sizeof(header.imageDescriptor));

    // Write pixel data
    for (Pixel pixel : pixel_map) {
        output_file.write(reinterpret_cast<char*>(&pixel.B), sizeof(pixel.B));
        output_file.write(reinterpret_cast<char*>(&pixel.G), sizeof(pixel.G));
        output_file.write(reinterpret_cast<char*>(&pixel.R), sizeof(pixel.R));
    }

}
void PrintPixel(Pixel* pixel, string pixel_name, bool does_endl){
    cout << pixel_name << ": (" << static_cast<int>(pixel->R) << ", " << static_cast<int>(pixel->G) << ", " << static_cast<int>(pixel->B) << ") ";
    if(does_endl) cout << endl;
}
bool PixelsAreEqual(Pixel pixel_one, Pixel pixel_two){
    if(pixel_one.B != pixel_two.B) return false;
    if(pixel_one.G != pixel_two.G) return false;
    if(pixel_one.R != pixel_two.R) return false;

    return true;
}
void MultiplyMethod(vector<Pixel>& pixel_map, vector<Pixel>& secondary_pixel) {

    vector<Pixel> new_pixel_map;

    for (int i = 0; i < pixel_map.size(); i++) {
        Pixel pixel_one = pixel_map[i];
        Pixel pixel_two = secondary_pixel[i];

        // Convert pixel values to normalized values (0-1 range)
        float norm_R1 = pixel_one.R / 255.0f;   // 0/255 = 0
        float norm_G1 = pixel_one.G / 255.0f;   // 56/255 = .2196
        float norm_B1 = pixel_one.B / 255.0f;   // 255/255 = 1

        float norm_R2 = pixel_two.R / 255.0f;   // 2/255 =.00784
        float norm_G2 = pixel_two.G / 255.0f;   //  0/255 = 0
        float norm_B2 = pixel_two.B / 255.0f;   // 0/255 = 0

        // Perform multiplication with normalized values
        float new_R = norm_R1 * norm_R2;    // 0 * .00784 = 0
        float new_G = norm_G1 * norm_G2;    // .2196 * 0 = 0
        float new_B = norm_B1 * norm_B2;    // 1 * 0 = 0

        // Convert back to pixel range (0-255) with rounding
        Pixel new_pixel;
        new_pixel.R = static_cast<unsigned char>(new_R * 255.0f + 0.5f);
        new_pixel.G = static_cast<unsigned char>(new_G * 255.0f + 0.5f);
        new_pixel.B = static_cast<unsigned char>(new_B * 255.0f + 0.5f);

        new_pixel_map.push_back(new_pixel);
    }

    pixel_map = new_pixel_map;
}

void SubtractMethod(vector<Pixel>& pixel_map, vector<Pixel>& secondary_pixel_map){
    vector<Pixel> new_pixel_map;

    for (int i = 0; i < pixel_map.size(); i++) {
        Pixel pixel_one = secondary_pixel_map[i];
        Pixel pixel_two = pixel_map[i];

        Pixel new_pixel;
        new_pixel.R = pixel_one.R - pixel_two.R < 0 ? 0 : pixel_one.R - pixel_two.R;
        new_pixel.G = pixel_one.G - pixel_two.G < 0 ? 0 : pixel_one.G - pixel_two.G;
        new_pixel.B = pixel_one.B - pixel_two.B < 0 ? 0 : pixel_one.B - pixel_two.B;

        new_pixel_map.push_back(new_pixel);
    }

    pixel_map = new_pixel_map;
}
vector<Pixel*>* AdditionMethod(const vector<Pixel*>* pixels_one, const vector<Pixel*>* pixels_two){
    vector<Pixel*>* new_pixel_map = new vector<Pixel*>();

    for (int i = 0; i < pixels_one->size(); i++) {
        Pixel pixel_one = *(*(pixels_one))[i];
        Pixel pixel_two = *(*(pixels_two))[i];

        Pixel* new_pixel = new Pixel;
        new_pixel->R = pixel_one.R + pixel_two.R > 255 ? 255 : pixel_one.R + pixel_two.R;
        new_pixel->G = pixel_one.G + pixel_two.G > 255 ? 255 : pixel_one.G + pixel_two.G;
        new_pixel->B = pixel_one.B + pixel_two.B > 255 ? 255 : pixel_one.B + pixel_two.B;

        new_pixel_map->push_back(new_pixel);
    }

    return new_pixel_map;
}
void ScreenMethod(vector<Pixel>& pixel_map, vector<Pixel>& secondary_pixel_map) {
    vector<Pixel> new_pixel_map;

    for (int i = 0; i < pixel_map.size(); i++) {
        Pixel pixel_one = pixel_map[i];
        Pixel pixel_two = secondary_pixel_map[i];

        // Normalize pixel values
        float norm_R1 = pixel_one.R / 255.0f;   // 2
        float norm_G1 = pixel_one.G / 255.0f;   // 0/255 = 0
        float norm_B1 = pixel_one.B / 255.0f;   // 219/255 = .8588

        float norm_R2 = pixel_two.R / 255.0f;   //0
        float norm_G2 = pixel_two.G / 255.0f;   //1
        float norm_B2 = pixel_two.B / 255.0f;   //1

        float new_R = 1 - ((1 - norm_R1) * (1 - norm_R2));
        float new_G = 1 - ((1 - norm_G1) * (1 - norm_G2));
        float new_B = 1 - ((1 - norm_B1) * (1 - norm_B2));


        // Create new pixel and add to the result vector
        Pixel new_pixel;
        new_pixel.R = static_cast<unsigned char>(new_R * 255.0f + 0.5f);
        new_pixel.G = static_cast<unsigned char>(new_G * 255.0f + 0.5f);
        new_pixel.B = static_cast<unsigned char>(new_B * 255.0f + 0.5f);

        new_pixel_map.push_back(new_pixel);
    }

    pixel_map = new_pixel_map;
}
void OverlayMethod(vector<Pixel>& pixel_map, vector<Pixel>& secondary_pixel_map){
    vector<Pixel> new_pixel_map;

    for (int i = 0; i < pixel_map.size(); i++) {
        Pixel pixel_one = pixel_map[i];
        Pixel pixel_two = secondary_pixel_map[i];


        float norm_R1 = pixel_one.R / 255.0f;   // 0/255 = 0
        float norm_G1 = pixel_one.G / 255.0f;   // 56/255 = .2196
        float norm_B1 = pixel_one.B / 255.0f;   // 255/255 = 1

        float norm_R2 = pixel_two.R / 255.0f;   // 2/255 =.00784
        float norm_G2 = pixel_two.G / 255.0f;   //  0/255 = 0
        float norm_B2 = pixel_two.B / 255.0f;   // 0/255 = 0

        float new_R = norm_R2 <= .5f ? (2 * norm_R1  * norm_R2) : (1-( 2 * (1-norm_R1) * (1-norm_R2)));
        float new_G = norm_G2 <= .5f ? (2 * norm_G1  * norm_G2) : (1-( 2 * (1-norm_G1) * (1-norm_G2)));
        float new_B = norm_B2 <= .5f ? (2 * norm_B1  * norm_B2) : (1-( 2 * (1-norm_B1) * (1-norm_B2)));

        Pixel new_pixel;
        new_pixel.R = static_cast<unsigned char>(new_R * 255.0f + 0.5f);
        new_pixel.G = static_cast<unsigned char>(new_G * 255.0f + 0.5f);
        new_pixel.B = static_cast<unsigned char>(new_B * 255.0f + 0.5f);

        new_pixel_map.push_back(new_pixel);
    }

    pixel_map = new_pixel_map;
}
void FlipImage(vector<Pixel>& pixel_map) {
    vector<Pixel> flipped_list;

    for (int i = pixel_map.size() - 1; i >= 0; i--) {
        flipped_list.push_back(pixel_map[i]);
    }

    pixel_map = flipped_list;
}
void CombineMethod(vector<Pixel>& pixel_map, vector<Pixel>& red_map, vector<Pixel>& green_map, vector<Pixel>& blue_map){

    for(int i = 0; i < red_map.size(); i++){
        Pixel pixel{};

        pixel.R = red_map[i].R;
        pixel.G = green_map[i].G;
        pixel.B = blue_map[i].B;

        pixel_map.push_back(pixel);
    }
}












