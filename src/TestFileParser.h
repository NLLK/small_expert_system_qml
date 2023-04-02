#ifndef TESTFILEPARSER_H
#define TESTFILEPARSER_H

#include <QString>
#include <QUrl>

class TestFileParser
{
public:
    TestFileParser();
    bool checkFilePath(QString filePath);
    bool parseFile();
    int questions_number();
    int variants_number();
    QString dataName() const;

private:
    int m_questions_number = -1;
    int m_variants_number = -1;
    QUrl m_fileUrl;
    QString m_dataName = "";
};

#endif // TESTFILEPARSER_H
