//
// Created by syzegno on 30.04.17.
//

#ifndef EQUEUE_V2_FILEREQUIREMENTSCANNER_H
#define EQUEUE_V2_FILEREQUIREMENTSCANNER_H


#include <memory>
#include <stdexcept>

#include "IRequirement.h"
#include "IStream.h"


namespace Handmada {
    class StreamRequirementScannerException : public std::runtime_error
    {
    public:
        StreamRequirementScannerException(const std::string& info);
    };


    class StreamRequirementScanner
    {
    private:
        IStream& stream_;

    public:
        StreamRequirementScanner(IStream& stream);

        std::unique_ptr<IRequirement> getNext() const;
    };
}


#endif //EQUEUE_V2_FILEREQUIREMENTSCANNER_H
