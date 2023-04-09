#include "QuestionModel.h"
#include <QDebug>
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
    QString _type = s_questionType.toLower();
    if (_type == "plain"){
        return QuestionModel::Type::Plain;
    }
    else if (_type == "ranges"){
        return QuestionModel::Type::Ranges;
    }
    else if (_type == "options"){
        return QuestionModel::Type::Options;
    }
    return QuestionModel::Type::Plain;
}

int QuestionModel::plainMinimum() const
{
    return m_plainMinimum;
}

void QuestionModel::setPlainMinimum(int newPlainMinimum)
{
    if (m_plainMinimum == newPlainMinimum)
        return;
    m_plainMinimum = newPlainMinimum;
    emit plainMinimumChanged();
}

int QuestionModel::plainMaximum() const
{
    return m_plainMaximum;
}

void QuestionModel::setPlainMaximum(int newPlainMaximum)
{
    if (m_plainMaximum == newPlainMaximum)
        return;
    m_plainMaximum = newPlainMaximum;
    emit plainMaximumChanged();
}

QVariantList QuestionModel::optionsOptions() const
{
    return m_optionsOptions;
}

void QuestionModel::setOptionsOptions(const QVariantList &newOptionsOptions)
{
    if (m_optionsOptions == newOptionsOptions)
        return;
    m_optionsOptions = newOptionsOptions;
    emit optionsOptionsChanged();
}

int QuestionModel::plainStep() const
{
    return m_plainStep;
}

void QuestionModel::setPlainStep(int newPlainStep)
{
    if (m_plainStep == newPlainStep)
        return;
    m_plainStep = newPlainStep;
    emit plainStepChanged();
}

double QuestionModel::value() const
{
    return m_value;
}

void QuestionModel::setValue(double newValue)
{
    if (qFuzzyCompare(m_value, newValue))
        return;
    m_value = newValue;
    m_relative_value = valueToRelativeValue(m_value);
    qDebug() << m_relative_value;
    emit valueChanged();
}

int QuestionModel::id() const
{
    return m_id;
}

void QuestionModel::setId(int newId)
{
    m_id = newId;
}

double QuestionModel::valueToRelativeValue(double value)
{
    double res = 0;

    switch(this->m_questionType){
        case Type::Options:{
            res = value;//TODO: figure out what to do with it
            break;
        }
        case Type::Plain:{
            res = value / (m_plainMaximum - m_plainMinimum);
            break;
        }
        case Type::Ranges:{
            res = value;//TODO: and it
            break;
        }
    }

    return res;
}
