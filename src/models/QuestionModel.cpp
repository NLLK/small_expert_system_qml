#include "QuestionModel.h"

QuestionModel::QuestionModel(QObject *parent)
    : QObject{parent}
{

}

QString QuestionModel::questionText() const
{
    return m_questionText;
}

void QuestionModel::setQuestionText(const QString &newQuestionText)
{
    if (m_questionText == newQuestionText)
        return;
    m_questionText = newQuestionText;
    emit questionTextChanged();
}

QuestionModel::Type QuestionModel::questionType() const
{
    return m_questionType;
}

void QuestionModel::setQuestionType(QuestionModel::Type newQuestionType)
{
    if (m_questionType == newQuestionType)
        return;
    m_questionType = newQuestionType;
    emit questionTypeChanged();
}
