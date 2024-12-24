#pragma once
 
#include <fmt/format.h>
#include <userver/components/component.hpp>
#include <userver/components/minimal_server_component_list.hpp>
#include <userver/server/handlers/http_handler_base.hpp>
// #include <userver/utest/using_namespace_userver.hpp>
 
namespace book_service {

std::string GetBook(std::string_view name);

class BookHandler final : public userver::server::handlers::HttpHandlerBase {
    public:

    static constexpr std::string_view kName = "handler-book";
    
    using HttpHandlerBase::HttpHandlerBase;
    
    std::string HandleRequestThrow(
        const userver::server::http::HttpRequest& request,
        userver::server::request::RequestContext&) const override;
};
 
}