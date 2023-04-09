#ifndef VARIANT_H
#define VARIANT_H

#include "src/models/ComputerPart.h"

class Variant
{
public:
    Variant();
    ~Variant();
    class Propability{
    public:
        void setPropabilities(double trueValue){
            this->True = trueValue;
            this->False = 1 - trueValue;
        };
    private:
        double True = 0.95;
        double False = 0.05;
    };

    ComputerPart *part() const;
    void setPart(ComputerPart *newPart);

    void setPropabilitiesList(const QList<Variant::Propability *> &newPropabilitiesList);

    QList<Variant::Propability *> propabilitiesList() const;

private:
    ComputerPart* m_part;

    double m_value = 0.5f;
    QList<Variant::Propability*> m_propabilitiesList; //TODO: mem leak
};

#endif // VARIANT_H
