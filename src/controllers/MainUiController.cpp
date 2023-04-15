#include "MainUiController.h"
#include "src/Calculation.h"
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


    if (checked){
        if (testFileParser.parseFile()){
            this->setDataName(testFileParser.dataName());
            this->setNumberOfQuestions(testFileParser.questions_number());
            this->setNumberOfVariants(testFileParser.variants_number());
            this->setQuestionsList(*testFileParser.questionsList());
            m_variantsList = *testFileParser.variantsList();
        }
        else checked = false;
    }
    this->setIsFilePathOK(checked);
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

QList<QuestionModel *> MainUiController::questionsList()
{
    return m_questionsList;
}

void MainUiController::setQuestionsList(QList<QuestionModel *> newQuestionsList)
{
    m_questionsList = newQuestionsList;
    emit questionsListChanged();
}

void MainUiController::startTest()
{
    if (!isFilePathOK())
        return;

    //TODO: something do here, or not
}

void MainUiController::stopTest()
{
    //TODO: clear everything
}


void MainUiController::testDone()
{
    calculation.setQuestionsList(m_questionsList);
    calculation.setVariantList(m_variantsList);
    calculation.smallExpertSystemAlgorithm();

    for (int i = 0; i < 3; i++){
        m_resultsList.append(calculation.getVariantList().at(i));
    }

    emit resultsListChanged();
}


QList<SimplerVariant *> MainUiController::resultsList() const
{
    return m_resultsList;
}
