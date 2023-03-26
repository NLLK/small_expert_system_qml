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
    return filePathURL.fileName();
    //return m_filePath;
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

    if (checked){
        filePathURL = QUrl(m_filePath);
        setIsFilePathOK(checked);
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
