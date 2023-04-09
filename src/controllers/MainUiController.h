#ifndef MAINUICONTROLLER_H
#define MAINUICONTROLLER_H

#include <QObject>
#include <QUrl>
#include <src/Calculation.h>
#include "src/TestFileParser.h"
#include "src/models/QuestionModel.h"

class MainUiController: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString filePath READ filePath WRITE setFilePath NOTIFY filePathChanged)
    Q_PROPERTY(QString dataName READ dataName WRITE setDataName NOTIFY dataNameChanged)
    Q_PROPERTY(bool isFilePathOK READ isFilePathOK WRITE setIsFilePathOK NOTIFY isFilePathOKChanged)
    Q_PROPERTY(int numberOfQuestions READ numberOfQuestions WRITE setNumberOfQuestions NOTIFY numberOfQuestionsChanged)
    Q_PROPERTY(int numberOfVariants READ numberOfVariants WRITE setNumberOfVariants NOTIFY numberOfVariantsChanged)

    Q_PROPERTY(QList<QuestionModel*> questionsList READ questionsList WRITE setQuestionsList NOTIFY questionsListChanged)
public:
    Q_INVOKABLE void startTest();
    Q_INVOKABLE void testDone();
    Q_INVOKABLE void stopTest();

public:
    explicit MainUiController(QObject *parent = nullptr);
    ~MainUiController();

    QUrl getFilePathURL();

    QString filePath();
    void setFilePath(const QString &newFilePath);

    bool isFilePathOK();
    void setIsFilePathOK(bool newIsFilePathOK);

    int numberOfQuestions();
    void setNumberOfQuestions(int newNumberOfQuestions);

    int numberOfVariants();
    void setNumberOfVariants(int newNumberOfVariants);

    QString dataName() const;
    void setDataName(const QString &newDataName);

    QList<QuestionModel*> questionsList();
    void setQuestionsList(QList<QuestionModel*> newQuestionsList);

signals:
    void filePathChanged();
    void isFilePathOKChanged();
    void numberOfQuestionsChanged();
    void numberOfVariantsChanged();

    void dataNameChanged();

    void questionsListChanged();

private:
    TestFileParser testFileParser;
    Calculation calculation;

    QUrl filePathURL;
    QString m_filePath;
    bool m_isFilePathOK = false;
    int m_numberOfQuestions = 0;
    int m_numberOfVariants = 0;
    QString m_dataName;
    QList<QuestionModel *> m_questionsList;
    QList<ComputerPart*> m_variantsList;
};

#endif // MAINUICONTROLLER_H
