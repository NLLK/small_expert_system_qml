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
#include "src/models/ComputerPart.h"
class TestFileParser
{
public:
    TestFileParser();
    bool checkFilePath(QString filePath);
    bool parseFile();
    bool parseQuestions(QJsonArray jsonArray);
    bool parseVariants(QJsonArray jsonArray);
    int questions_number();
    int variants_number();
    QString dataName() const;

    QList<QuestionModel*>* questionsList();
    QList<ComputerPart*>* variantsList();

private:
    int m_questions_number = -1;
    int m_variants_number = -1;
    QUrl m_fileUrl;
    QString m_dataName = StaticStringConstants::FileParser::dataName_fileParsing_error;
    QList<QuestionModel*> m_questionsList;
    QList<ComputerPart*> m_variantsList;
    //QFile m_file;
};

#endif // TESTFILEPARSER_H
