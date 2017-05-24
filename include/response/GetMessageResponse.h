//
// Created by syzegno on 15.05.17.
//

#ifndef EQUEUE_V2_GETMESSAGERESPONSE_H
#define EQUEUE_V2_GETMESSAGERESPONSE_H


#include <memory>
#include <vector>

#include "IResponse.h"
#include "Message.h"


namespace Handmada {
    class GetMessageResponse : public IResponse
    {
    private:
        std::vector<Message> messages_;

    public:
        GetMessageResponse(std::vector<Message>&& messages);

        virtual OpCode code() const override;
        virtual void accept(IResponseVisitor& visitor) const override;

        const std::vector<Message>& messages() const;
        static std::unique_ptr<IResponse> create(std::vector<Message>&& messages);
    };
}


#endif //EQUEUE_V2_GETMESSAGERESPONSE_H
