#include "ComputerPart.h"

ComputerPart::ComputerPart(QObject *parent)
    : QObject{parent}
{

}

QString ComputerPart::name() const
{
    return m_name;
}

void ComputerPart::setName(const QString &newName)
{
    if (m_name == newName)
        return;
    m_name = newName;
    emit nameChanged();
}

double ComputerPart::price() const
{
    return m_price;
}

void ComputerPart::setPrice(double newPrice)
{
    if (qFuzzyCompare(m_price, newPrice))
        return;
    m_price = newPrice;
    emit priceChanged();
}

ComputerPart::Type ComputerPart::type() const
{
    return m_type;
}
void ComputerPart::setType(ComputerPart::Type newType)
{
    m_type = newType;
}

void ComputerPart::setType(QString _string_type)
{
    m_type = ComputerPart::stringToType(_string_type);
}

ComputerPart::Type ComputerPart::stringToType(QString _type)
{
    _type = _type.toLower();
    if (_type == "videocard")
        return ComputerPart::Type::Videocard;
    else if (_type == "motherboard")
        return ComputerPart::Type::Motherboard;
    else if (_type == "cpu")
        return ComputerPart::Type::CPU;
    else if (_type == "ram")
        return ComputerPart::Type::RAM;
    else if (_type == "drive")
        return ComputerPart::Type::Drive;
    else
        return ComputerPart::Type::Error;
}

QString ComputerPart::compatibility() const
{
    return m_compatibility;
}

void ComputerPart::setCompatibility(const QString &newCompatibility)
{
    m_compatibility = newCompatibility;
}

QString ComputerPart::vendor() const
{
    return m_vendor;
}

void ComputerPart::setVendor(const QString &newVendor)
{
    m_vendor = newVendor;
}


QString ComputerPart::side() const
{
    return m_side;
}

void ComputerPart::setSide(const QString &newSide)
{
    m_side = newSide;
}

ComputerPart::Perfomance ComputerPart::perfomance() const
{
    return m_perfomance;
}

void ComputerPart::setPerfomance(ComputerPart::Perfomance newPerfomance)
{
    m_perfomance = newPerfomance;
}

void ComputerPart::setPerfomance(QString _string_perfomance)
{
    m_perfomance = ComputerPart::stringToPerfomance(_string_perfomance);
}

ComputerPart::Perfomance ComputerPart::stringToPerfomance(QString _string_perfomance)
{
    QString _type = _string_perfomance.toLower();
    if (_type == "low")
        return ComputerPart::Perfomance::Low;
    else if (_type == "middle")
        return ComputerPart::Perfomance::Middle;
    else if (_type == "high")
        return ComputerPart::Perfomance::High;
    else
        return ComputerPart::Perfomance::Error;
}



void ComputerPart::setBudget(ComputerPart::Budget newBudget)
{
    m_budget = newBudget;
}

void ComputerPart::setBudget(QString _string_budget)
{
    m_budget = ComputerPart::stringToBudget(_string_budget);
}

ComputerPart::Budget ComputerPart::stringToBudget(QString _string_budget)
{
    QString _type = _string_budget.toLower();
    if (_type == "low")
        return ComputerPart::Budget::Low;
    else if (_type == "middle")
        return ComputerPart::Budget::Middle;
    else if (_type == "high")
        return ComputerPart::Budget::High;
    else
        return ComputerPart::Budget::Low;
}

ComputerPart::Budget ComputerPart::budget() const
{
    return m_budget;
}


