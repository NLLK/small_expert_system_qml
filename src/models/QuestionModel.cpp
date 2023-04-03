#include "QuestionModel.h"

QuestionModel::QuestionModel(QObject *parent)
    : QObject(parent)
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

void QuestionModel::setQuestionType(QString s_questionType)
{
    m_questionType = QuestionModel::stringToQuestionType(s_questionType);
}

QuestionModel::Type QuestionModel::stringToQuestionType(QString s_questionType){
    if (s_questionType.toLower() == "plain"){
        return QuestionModel::Type::Plain;
    }
    else if (s_questionType.toLower() == "ranges"){
        return QuestionModel::Type::Ranges;
    }
    else if (s_questionType.toLower() == "options"){
        return QuestionModel::Type::Options;
    }
    return QuestionModel::Type::Plain;
}
