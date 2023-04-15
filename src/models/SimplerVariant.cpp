#include "SimplerVariant.h"

SimplerVariant::SimplerVariant(QObject *parent)
    : QObject{parent}
{

}

QString SimplerVariant::variant_text() const
{
    return m_variant_text;
}

void SimplerVariant::setVariant_text(const QString &newVariant_text)
{
    if (m_variant_text == newVariant_text)
        return;
    m_variant_text = newVariant_text;
    emit variant_textChanged();
}

QString SimplerVariant::match_percentage() const
{
    return m_match_percentage;
}

void SimplerVariant::setMatch_percentage(const QString &newMatch_percentage)
{
    if (m_match_percentage == newMatch_percentage)
        return;
    m_match_percentage = newMatch_percentage;
    emit match_percentageChanged();
}

double SimplerVariant::value() const
{
    return m_value;
}

void SimplerVariant::setValue(double newValue)
{
    m_value = newValue;

    setMatch_percentage(QString("%1%").arg(m_value * 100, 0, 'f', 2));
}

QList<Propability> SimplerVariant::propabilities_list() const
{
    return m_propabilities_list;
}

void SimplerVariant::addToPropabilitiesList(Propability value)
{
    m_propabilities_list.append(value);
}
