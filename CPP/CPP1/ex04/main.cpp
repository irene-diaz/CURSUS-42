#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char** argv)
{
    if(argc != 4)
    {
        std::cout << "Usage: ./replace file s1 s2" << std::endl;
        return 1;
    }

    //open the file
    std::ifstream infile(argv[1]);
    if (!infile)
    {
        std::cout << "Error opening file\n";
        return 1;
    }

    //create the output file
    /*c.str()  => convert std:string to array of characters finish with '\0'*/
    std::ofstream outfile((std::string(argv[1]) + ".replace").c_str());
    if (!outfile)
    {
        std::cout << "Error opening output file\n";
        return 1;
    }

    //get the strings to replace
    std::string s1 = argv[2];
    std::string s2 = argv[3];

    if(s1.empty())
    {
        std::cout << "s1 cannot be empty\n";
        return 1;
    }

    //read the file line by line and replace s1 with s2
    std::string line;
    while(std::getline(infile, line))
    {
        size_t pos = 0;
        
        while ((pos = line.find(s1, pos)) != std::string::npos)
        {
            line.erase(pos, s1.length());
            line.insert(pos, s2);
            //move the position forward to avoid replacing the newly inserted string
            pos += s2.length();
        }

        //write the modified line to the output file
        outfile << line;
        //add a newline if it's not the end of the file
        if(!infile.eof())
            outfile << std::endl;
    }

    return 0;
}