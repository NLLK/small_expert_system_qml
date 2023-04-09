#ifndef COMPUTERPART_H
#define COMPUTERPART_H

#include <QObject>

class ComputerPart : public QObject
{
    Q_OBJECT
public:
    explicit ComputerPart(QObject *parent = nullptr);
    ~ComputerPart(){};

    enum class Type{
        Error = -1,
        Videocard = 0,
        Motherboard = 1,
        CPU = 2,
        Drive = 3,
        RAM = 4
    };

    enum class Perfomance{
        Error = -1,
        Low = 0,
        Middle = 1,
        High = 2
    };

    enum class Budget{
        Low = 0,
        Middle = 1,
        High = 2
    };

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(double price READ price WRITE setPrice NOTIFY priceChanged)

    QString name() const;
    void setName(const QString &newName);

    double price() const;
    void setPrice(double newPrice);

    ComputerPart::Type type() const;
    void setType(ComputerPart::Type newType);
    void setType(QString _string_type);

    QString compatibility() const;
    void setCompatibility(const QString &newCompatibility);

    QString vendor() const;
    void setVendor(const QString &newVendor);

    QString side() const;
    void setSide(const QString &newSide);

    ComputerPart::Perfomance perfomance() const;
    void setPerfomance(ComputerPart::Perfomance newPerfomance);
    void setPerfomance(QString _string_perfomance);

    ComputerPart::Budget budget() const;
    void setBudget(ComputerPart::Budget newBudget);
    void setBudget(QString _string_budget);

    ComputerPart::Type stringToType(QString _type);
    ComputerPart::Perfomance stringToPerfomance(QString _string_perfomance);
    ComputerPart::Budget stringToBudget(QString _string_budget);


signals:
    void nameChanged();
    void priceChanged();

private:

    QString m_name;
    double m_price;
    ComputerPart::Type m_type;
    QString m_compatibility;
    QString m_vendor;
    QString m_side;
    ComputerPart::Perfomance m_perfomance;
    ComputerPart::Budget m_budget;

};

#endif // COMPUTERPART_H
