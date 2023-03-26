#include "TestFileParser.h"

TestFileParser::TestFileParser()
{

}

bool TestFileParser::checkFilePath(QString filePath)
{
    if (filePath.length() == 0){
        return false;
    }
    return true;
}
