//
// Created by syzegno on 07.05.17.
//


#include "PredicatePrinter.h"
#include "BooleanLiteral.h"
#include "AttributeValuePrinter.h"
#include "PredicateCalculatorPrinter.h"


namespace Handmada {
    namespace {
        const char* const indent = "      ";
        const char* const branch = " |--> ";


        void printIndent(std::ostream& output, int shift)
        {
            for (int i = 0; i < shift - 1; i++) {
                output << indent;
            }
            if (shift > 0) {
                output << branch;
            }
        }
    }


    PredicatePrinter::PredicatePrinter(std::ostream& output, int shift)
        : output_(output), shift_(shift)
    { }


    void PredicatePrinter::visit(const NotPredicate& predicate)
    {
        printIndent(output_, shift_);
        output_ << "NOT" << std::endl;
        shift_++;
        predicate.predicate_->accept(*this);
        shift_--;
    }


    void PredicatePrinter::visit(const ComparisonPredicate& predicate)
    {
        printIndent(output_, shift_);
        output_ << '$' << predicate.attribute().name();
        output_ << ' ' << ComparisonFlag::toString(predicate.flag()) << ' ';

        AttributeValuePrinter printer(output_);
        predicate.attribute().accept(printer);
    }


    void PredicatePrinter::visit(const BinaryPredicate& predicate)
    {
        printIndent(output_, shift_);
        PredicateCalculatorPrinter printer(output_);
        predicate.calculator().accept(printer);
        shift_++;
        predicate.predicateA().accept(*this);
        predicate.predicateB().accept(*this);
        shift_--;
    }


    void PredicatePrinter::visit(const MultiplePredicate& predicate)
    {
        printIndent(output_, shift_);
        PredicateCalculatorPrinter printer(output_);
        predicate.calculator().accept(printer);
        shift_++;
        for (auto& pre : predicate.predicates()) {
            pre->accept(*this);
        }
        shift_--;
    }
}
