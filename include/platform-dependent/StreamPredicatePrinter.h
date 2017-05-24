//
// Created by syzegno on 08.05.17.
//

#ifndef EQUEUE_V2_FILEPREDICATEPRINTER_H
#define EQUEUE_V2_FILEPREDICATEPRINTER_H


#include "IPredicateVisitor.h"
#include "IStream.h"


namespace Handmada {
    class StreamPredicatePrinter : public IPredicateVisitor
    {
    private:
        IStream& stream_;

    public:
        StreamPredicatePrinter(IStream& stream);

        virtual void visit(const NotPredicate& predicate) override;
        virtual void visit(const BinaryPredicate& predicate) override;
        virtual void visit(const MultiplePredicate& predicate) override;
        virtual void visit(const ComparisonPredicate& predicate) override;
    };
}


#endif //EQUEUE_V2_FILEPREDICATEPRINTER_H
