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

bool TestFileParser::parseFile(QUrl fileUrl)
{
    m_fileUrl = fileUrl;
    m_questions = 3;
    m_variants = 44;
    return true;
}

int TestFileParser::questions()
{
    if (m_questions == -1)
        return 0;
    else return m_questions;
}

int TestFileParser::variants()
{
    if (m_variants == -1)
        return 0;
    else return m_variants;
}
