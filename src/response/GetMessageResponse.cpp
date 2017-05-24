//
// Created by syzegno on 15.05.17.
//


#include "GetMessageResponse.h"
#include "IResponseVisitor.h"


namespace Handmada {
    GetMessageResponse::GetMessageResponse(std::vector<Message>&& messages)
            : messages_(std::move(messages))
    { }


    OpCode GetMessageResponse::code() const
    {
        return OpCode::SUCCESS;
    }


    void GetMessageResponse::accept(IResponseVisitor& visitor) const
    {
        visitor.visit(*this);
    }


    const std::vector<Message>& GetMessageResponse::messages() const
    {
        return messages_;
    }


    std::unique_ptr<IResponse> GetMessageResponse::create(std::vector<Message>&& messages)
    {
        return std::unique_ptr<IResponse>(new GetMessageResponse(std::move(messages)));
    }
}
