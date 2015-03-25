#include <cstdlib>
#include <cstdio>
#include <string>
#include <sstream>
#include <cmath>
#include <exception>
#include <stdexcept>

#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

#ifndef M_PI
const double M_PI = 3.14159265358979323846264338327950288419716939937510;
#endif

const double R2D = (180.0/M_PI);
const double D2R = (M_PI/180.0);

#define LOG_TEXT std::printf

inline const double DegToRad(const double &deg)
{
    return deg * D2R;
}

inline const double RadToDeg(const double &rad)
{
    return rad * R2D;
}

void usage(int argc, char *argv[])
{
    std::string name(argv[0]);
    size_t pos = name.find_last_of("\\/");
    if (pos != std::string::npos)
    {
        name = name.substr(pos+1);
    }

    LOG_TEXT("Usage:\n");
    LOG_TEXT("%s <start x> <start y> <end x> <end y> <center x> <center y> <direction> [num segments in 2\u03C0]\n", name.c_str());
}

enum eDirection
{
    eCW = 0,
    eCCW = 1,
};

int main(int argc, char *argv[])
{
    if (argc < 8)
    {
        LOG_TEXT("Not enough arguments\n");
        usage(argc, argv);
        return (1);
    }

    double startx(0.0), starty(0.0);
    double endx(0.0), endy(0.0);
    double cenx(0.0), ceny(0.0);
    eDirection adir = eCCW;
    uint16_t numSegments = 12;

    try
    {
        startx = boost::lexical_cast<double>(argv[1]);
        starty = boost::lexical_cast<double>(argv[2]);
        endx = boost::lexical_cast<double>(argv[3]);
        endy = boost::lexical_cast<double>(argv[4]);
        cenx = boost::lexical_cast<double>(argv[5]);
        ceny = boost::lexical_cast<double>(argv[6]);

        std::string dirArg(argv[7]);
        boost::to_upper(dirArg);
        if (dirArg.compare("CW") == 0 ||
            dirArg.compare("0") == 0)
        {
            adir = eCW;
        }
        else if (dirArg.compare("CCW") == 0 ||
                 dirArg.compare("1") == 0)
        {
            adir = eCCW;
        }
        else
        {
            throw std::invalid_argument("Cannot determine arc direction");
        }

        if (argc >= 9)
        {
            numSegments = boost::lexical_cast<uint16_t>(argv[8]);
        }

        LOG_TEXT("test values:\n"
                 "    start : [%.5f,%.5f]\n"
                 "      end : [%.5f,%.5f]\n"
                 "   center : [%.5f,%.5f]\n"
                 "direction :  %s\n"
                 " segments :  %u\n",
                 startx, starty,
                 endx, endy,
                 cenx, ceny,
                 (adir == eCW ? "CW" : (adir == eCCW ? "CCW" : "BAD")),
                 numSegments);

        LOG_TEXT("\n");
        LOG_TEXT("0 deg in rad = %.3f\n", DegToRad(0));
        LOG_TEXT("0 rad in deg = %.3f\n", RadToDeg(0));
        LOG_TEXT("90 deg in rad = %.3f\n", DegToRad(90));
        LOG_TEXT("\u03C0/2 rad in deg = %.3f\n", RadToDeg(M_PI/2.0));
        LOG_TEXT("180 deg in rad = %.3f\n", DegToRad(180));
        LOG_TEXT("\u03C0 rad in deg = %.3f\n", RadToDeg(M_PI));
        LOG_TEXT("270 deg in rad = %.3f\n", DegToRad(270));
        LOG_TEXT("3\u03C0/2 rad in deg = %.3f\n", RadToDeg(3*M_PI/2.0));
        LOG_TEXT("360 deg in rad = %.3f\n", DegToRad(360));
        LOG_TEXT("2\u03C0 rad in deg = %.3f\n", RadToDeg(2*M_PI));

        double startAngle(0.0);
        double sDeltaX(startx - cenx);
        double sDeltaY(starty - ceny);
        if (sDeltaX == 0.0)
        {
            startAngle = M_PI / 2.0;
            if (starty < ceny)
            {
                startAngle *= -1.0;
            }
        }
        else
        {
            startAngle = std::atan(sDeltaY/sDeltaX);
        }
        LOG_TEXT("Start angle : %.5f\u00B0\n", RadToDeg(startAngle));

        double endAngle(0.0);
        double eDeltaX(endx - cenx);
        double eDeltaY(endy - ceny);
        if (eDeltaX == 0.0)
        {
            endAngle = M_PI / 2.0;
            if (endy < ceny)
            {
                endAngle *= -1.0;
            }
        }
        else
        {
            endAngle = std::atan(eDeltaY/eDeltaX);
        }
        LOG_TEXT("End angle : %.5f\u00B0\n", RadToDeg(endAngle));
    }
    catch( boost::bad_lexical_cast &e )
    {
        LOG_TEXT("Caught boost bad lexical cast exception \"%s\"\n", e.what());
        usage(argc, argv);
        return 1;
    }
    catch( std::exception & e )
    {
        LOG_TEXT("Caught std exception \"%s\"\n", e.what());
        usage(argc, argv);
        return 2;
    }
    catch( ... )
    {
        LOG_TEXT("An unknown exception occurred\n");
        usage(argc, argv);
        return 2;
    }
    return (0);
}
