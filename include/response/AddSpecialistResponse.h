//
// Created by syzegno on 14.05.17.
//

#ifndef EQUEUE_V2_ADDSPECIALISTRESPONSE_H
#define EQUEUE_V2_ADDSPECIALISTRESPONSE_H


#include <memory>

#include "IResponse.h"
#include "Types.h"


namespace Handmada {
    class AddSpecialistResponse : public IResponse
    {
    private:
        SpecialistId specialistId_;

    public:
        AddSpecialistResponse(SpecialistId specialistId);

        virtual OpCode code() const override;
        virtual void accept(IResponseVisitor& visitor) const override;

        SpecialistId specialistId() const;
        static std::unique_ptr<IResponse> create(SpecialistId specialistId);
    };
}


#endif //EQUEUE_V2_ADDSPECIALISTRESPONSE_H
