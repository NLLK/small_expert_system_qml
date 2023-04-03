#ifndef TESTFILEPARSER_H
#define TESTFILEPARSER_H

#include <QString>
#include <QUrl>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>

#include "src/StaticStringConstants.h"
#include "src/models/QuestionModel.h"
class TestFileParser
{
public:
    TestFileParser();
    bool checkFilePath(QString filePath);
    bool parseFile();
    bool parseQuestions(QJsonArray jsonArray);
    int questions_number();
    int variants_number();
    QString dataName() const;

    QList<QuestionModel*>* questionsList();

private:
    int m_questions_number = -1;
    int m_variants_number = -1;
    QUrl m_fileUrl;
    QString m_dataName = StaticStringConstants::FileParser::dataName_fileParsing_error;
    QList<QuestionModel*> m_questionsList;
    //QFile m_file;
};

#endif // TESTFILEPARSER_H
