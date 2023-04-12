#include "Variant.h"

Variant::Variant()
{

}

Variant::~Variant()
{

}

ComputerPart *Variant::part() const
{
    return m_part;
}

void Variant::setPart(ComputerPart *newPart)
{
    m_part = newPart;
}

void Variant::setPropabilitiesList(const QList<Variant::Propability *> &newPropabilitiesList)
{
    m_propabilitiesList = newPropabilitiesList;
}

QList<Variant::Propability *> Variant::propabilitiesList() const
{
    return m_propabilitiesList;
}

void Variant::setAnswersList(const QList<double> &newAnswersList)
{
    m_answersList = newAnswersList;
}

void Variant::addToAnswersList(double value)
{
    m_answersList.append(value);
}

QList<double> Variant::answersList() const
{
    return m_answersList;
}
