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

    if (splitList.length() < 2){
        isFileOkFlag = false;
    }
    else {
        fileExtenstion = fileExtenstion.split('.')[1];
    }

    if (isFileOkFlag)
        if  (fileExtenstion != "ses"){
            isFileOkFlag = false;
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
    if (!isFileOk){
        m_dataName = "";
        m_questions_number = 0;
        m_variants_number = 0;
        return false;
    }
    else{
        m_dataName = "data_name";
        m_questions_number = 3;
        m_variants_number = 44;
        return true;
    }
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
