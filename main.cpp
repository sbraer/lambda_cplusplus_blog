#include <iostream>
#include <cassert>
#include <aws/lambda-runtime/runtime.h>
#include <aws/core/utils/json/JsonSerializer.h>
#include <aws/core/utils/memory/stl/SimpleStringStream.h>
#include "mongoDbHelper.h"

using namespace aws::lambda_runtime;
using namespace Aws::Utils::Json;

static invocation_response my_handler(invocation_request const& request)
{
    [[maybe_unused]] JsonValue json_request(request.payload);

    try {
        const auto message = MongoDbHelper::Instance().FindOne("MyCollection","name","Andrea");
        if (message) {
            JsonValue response{*message};
            return invocation_response::success(response.View().WriteCompact(), "application/json");
        }
        else {
            return invocation_response::failure("Requesto to MongoDb", "NotFound");
        }
    }
    catch(const std::exception& e) {
        return invocation_response::failure("Generic error", e.what());
    }
}

int main() {
    run_handler(my_handler);
    return 0;
}
