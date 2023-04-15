#ifndef SIMPLERVARIANT_H
#define SIMPLERVARIANT_H

#include "src/models/Propability.h"
#include <QObject>
#

class SimplerVariant : public QObject
{
    Q_OBJECT
public:
    explicit SimplerVariant(QObject *parent = nullptr);

    Q_PROPERTY(QString variant_text READ variant_text WRITE setVariant_text NOTIFY variant_textChanged)
    Q_PROPERTY(QString match_percentage READ match_percentage WRITE setMatch_percentage NOTIFY match_percentageChanged)

    QString variant_text() const;
    void setVariant_text(const QString &newVariant_text);
    QString match_percentage() const;
    void setMatch_percentage(const QString &newMatch_percentage);

    double value() const;
    void setValue(double newValue);

    QList<Propability> propabilities_list() const;
    void addToPropabilitiesList(Propability value);

signals:
    void variant_textChanged();
    void match_percentageChanged();

private:
    QString m_variant_text;
    QString m_match_percentage;

    QList<Propability> m_propabilities_list;

    double m_value = 0;
};

#endif // SIMPLERVARIANT_H
