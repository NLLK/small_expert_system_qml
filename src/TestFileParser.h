#ifndef TESTFILEPARSER_H
#define TESTFILEPARSER_H

#include <QString>

class TestFileParser
{
public:
    TestFileParser();
    bool checkFilePath(QString filePath);
    int questions();
    int variants();
private:
    int m_questions = -1;
    int m_variants = -1;
};

#endif // TESTFILEPARSER_H
