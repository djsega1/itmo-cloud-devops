#include "book.hpp"

#include <userver/http/content_type.hpp>

namespace book_service {
   
std::string GetBook(std::string_view name) {
    if (name.empty()) return "Book doesn't exist\n";
    return fmt::format("Here is your book: {}!\n", name);
}

std::string book_service::BookHandler::HandleRequestThrow(
    const userver::server::http::HttpRequest& request,
    userver::server::request::RequestContext&) const {
  request.GetHttpResponse().SetContentType(userver::http::content_type::kTextPlain);
  return book_service::GetBook(request.GetArg("name"));
}

}