//
// Created by syzegno on 19.05.17.
//


#include "PredicateCalculatorPrinter.h"


namespace Handmada {
    PredicateCalculatorPrinter::PredicateCalculatorPrinter(std::ostream& out)
            : out_(out)
    { }


    void PredicateCalculatorPrinter::visit(const OrBinaryCalculator& calculator)
    {
        out_ << "OR\n";
    }


    void PredicateCalculatorPrinter::visit(const AndBinaryCalculator& calculator)
    {
        out_ << "AND\n";
    }


    void PredicateCalculatorPrinter::visit(const OrMultipleCalculator& calculator)
    {
        out_ << "OR <multiple>\n";
    }


    void PredicateCalculatorPrinter::visit(const AndMultipleCalculator& calculator)
    {
        out_ << "AND <multiple>\n";
    }
}
