#include "TestFileParser.h"

TestFileParser::TestFileParser()
{

}

bool TestFileParser::checkFilePath(QString filePath)
{
    if (filePath.length() == 0){
        return false;
    }
    QUrl fileUrl = QUrl(filePath);
    QString fileExtenstion = fileUrl.fileName();
    QStringList splitList = fileExtenstion.split('.');
    bool isFileOkFlag = true;
    QFile file;

    if (splitList.length() < 2){
        isFileOkFlag = false;
    }
    else {
        fileExtenstion = fileExtenstion.split('.')[1];
    }

    if (isFileOkFlag){
        if  (fileExtenstion != StaticStringConstants::FileParser::fileExtenstion){
            isFileOkFlag = false;
        }
        else {
            file.setFileName(fileUrl.toLocalFile());
            if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
                isFileOkFlag = false;
            }
            else{
                file.close();
//                m_file = file;
            }
        }
    }

    if (!isFileOkFlag){
        return false;
    }

    m_fileUrl = fileUrl;

    return true;
}

bool TestFileParser::parseFile()
{
    bool isFileOk = true;
    QString __dataName = "";
    int __questions_number = -1;
    int __variants_number = -1;

    QFile file(m_fileUrl.toLocalFile());
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString fileContainment = file.readAll();
    file.close();

    QJsonParseError errHandler;
    QJsonDocument jDoc = QJsonDocument::fromJson(fileContainment.toUtf8(), &errHandler);
    isFileOk = (errHandler.error == QJsonParseError::NoError);

    if (isFileOk){
        if (!jDoc.isObject()) isFileOk = false;
        else{
            QJsonObject jObj = jDoc.object();
            __dataName = jObj[StaticStringConstants::FileParser::jsonf_dataName].toString(StaticStringConstants::FileParser::jsonf_dataName_default);

            QJsonArray jQuestions = jObj[StaticStringConstants::FileParser::jsonf_questions].toArray();
            if (jQuestions.count() != 0){
                __questions_number = jQuestions.count();
                isFileOk = parseQuestions(jQuestions);
            }
            else isFileOk = false;

            QJsonArray jVariants = jObj[StaticStringConstants::FileParser::jsonf_variants].toArray();
            if (jVariants.count() != 0)
                __variants_number = jVariants.count();
            else isFileOk = false;
        }

    }
    if (!isFileOk){
        m_dataName = StaticStringConstants::FileParser::dataName_fileParsing_error;
        m_questions_number = 0;
        m_variants_number = 0;
        return false;
    }
    else {
        m_dataName = __dataName;
        m_questions_number = __questions_number;
        m_variants_number = __variants_number;
        return true;
    }


}

bool TestFileParser::parseQuestions(QJsonArray jsonArray)
{
    m_questionsList.clear();

    for (int i = 0; i < jsonArray.count(); i++){
       QJsonObject jObj = jsonArray[i].toObject();
       int _id = -1;
       try {
           _id = jObj[StaticStringConstants::FileParser::jobj_question_text].toInt(0);
       } catch (...) {

       }

       QString _text = jObj[StaticStringConstants::FileParser::jobj_question_text].toString(StaticStringConstants::FileParser::jobj_question_text_default);
       QString _type = jObj[StaticStringConstants::FileParser::jobj_question_type].toString(StaticStringConstants::FileParser::jobj_question_type_default);
       QuestionModel *model = new QuestionModel;

       model->setQuestionText(_text);
       model->setQuestionType(_type);
       m_questionsList.append(model);
    }

    return true;
}

int TestFileParser::questions_number()
{
    if (m_questions_number == -1)
        return 0;
    else return m_questions_number;
}

int TestFileParser::variants_number()
{
    if (m_variants_number == -1)
        return 0;
    else return m_variants_number;
}

QString TestFileParser::dataName() const
{
    return m_dataName;
}

QList<QuestionModel*>* TestFileParser::questionsList()
{
    return &m_questionsList;
}


