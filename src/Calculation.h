#ifndef CALCULATION_H
#define CALCULATION_H

#include "src/models/ComputerPart.h"

#include <QList>

class Calculation
{
public:

    class BudgetPrices{
        class Videocard{
        public:
            static inline double middle = 15000;
            static inline double high = 25000;
        };
        class Motherboard{
        public:
            static inline double middle = 10000;
            static inline double high = 15000;
        };
        class CPU{
        public:
            static inline double middle = 10000;
            static inline double high = 20000;
        };
        class Drive{
        public:
            static inline double middle = 5000;
            static inline double high = 10000;
        };
        class RAM{
        public:
            static inline double middle = 5000;
            static inline double high = 15000;
        };
    public:
        static ComputerPart::Budget getBudgetByPriceNType(double price, ComputerPart::Type type){

            double _middle = 0;
            double _high = 0;

            switch(type){
                case ComputerPart::Type::Videocard: {
                    _middle = BudgetPrices::Videocard::middle;
                    _high = BudgetPrices::Videocard::high;
                    break;
                }
                case ComputerPart::Type::Motherboard: {
                    _middle = BudgetPrices::Motherboard::middle;
                    _high = BudgetPrices::Motherboard::high;
                    break;
                }
                case ComputerPart::Type::CPU: {
                    _middle = BudgetPrices::CPU::middle;
                    _high = BudgetPrices::CPU::high;
                    break;
                }
                case ComputerPart::Type::Drive: {
                    _middle = BudgetPrices::Drive::middle;
                    _high = BudgetPrices::Drive::high;
                    break;
                }
                case ComputerPart::Type::RAM: {
                    _middle = BudgetPrices::RAM::middle;
                    _high = BudgetPrices::RAM::high;
                    break;
                }
            default: break;
            }

            if (price < _middle){
                return ComputerPart::Budget::Low;
            }
            else if (price < _high){
                return ComputerPart::Budget::Middle;
            }
            else return ComputerPart::Budget::High;

        }
    };

    Calculation();
    static void precalculateVariants(QList<ComputerPart*>* variantsList);
};

#endif // CALCULATION_H
