#include "MainUiController.h"
#include <QDebug>
MainUiController::MainUiController(QObject *parent) : QObject(parent)
{

}

MainUiController::~MainUiController()
{

}

QString MainUiController::filePath()
{
    if (m_isFilePathOK)
        return filePathURL.fileName();
    return "";
}

QUrl MainUiController::getFilePathURL()
{
    return filePathURL;
}

void MainUiController::setFilePath(const QString &newFilePath)
{
    if (m_filePath == newFilePath)
        return;
    m_filePath = newFilePath;

    bool checked = testFileParser.checkFilePath(m_filePath);
    this->setIsFilePathOK(checked);

    if (checked){
        if (testFileParser.parseFile()){
            this->setDataName(testFileParser.dataName());
            this->setNumberOfQuestions(testFileParser.questions_number());
            this->setNumberOfVariants(testFileParser.variants_number());
        }
    }

    emit filePathChanged();
}

bool MainUiController::isFilePathOK()
{
    return m_isFilePathOK;
}

void MainUiController::setIsFilePathOK(bool newIsFilePathOK)
{
    if (m_isFilePathOK == newIsFilePathOK)
        return;
    m_isFilePathOK = newIsFilePathOK;
    emit isFilePathOKChanged();
}

int MainUiController::numberOfQuestions()
{
    return m_numberOfQuestions;
}

void MainUiController::setNumberOfQuestions(int newNumberOfQuestions)
{
    if (m_numberOfQuestions == newNumberOfQuestions)
        return;
    m_numberOfQuestions = newNumberOfQuestions;
    emit numberOfQuestionsChanged();
}

int MainUiController::numberOfVariants()
{
    return m_numberOfVariants;
}

void MainUiController::setNumberOfVariants(int newNumberOfVariants)
{
    if (m_numberOfVariants == newNumberOfVariants)
        return;
    m_numberOfVariants = newNumberOfVariants;
    emit numberOfVariantsChanged();
}

QString MainUiController::dataName() const
{
    return m_dataName;
}

void MainUiController::setDataName(const QString &newDataName)
{
    if (m_dataName == newDataName)
        return;
    m_dataName = newDataName;
    emit dataNameChanged();
}
