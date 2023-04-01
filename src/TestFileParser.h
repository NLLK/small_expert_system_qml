#ifndef TESTFILEPARSER_H
#define TESTFILEPARSER_H

#include <QString>
#include <QUrl>

class TestFileParser
{
public:
    TestFileParser();
    bool checkFilePath(QString filePath);
    bool parseFile(QUrl fileUrl);
    int questions();
    int variants();
private:
    int m_questions = -1;
    int m_variants = -1;
    QUrl m_fileUrl;
};

#endif // TESTFILEPARSER_H
