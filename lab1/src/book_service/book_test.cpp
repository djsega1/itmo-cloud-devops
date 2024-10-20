#include "book.hpp"

#include <userver/utest/utest.hpp>

UTEST(GetBook, Basic) {
  EXPECT_EQ(book_service::GetBook("dostoevsky"), "Here is your book: dostoevsky!\n");
  EXPECT_EQ(book_service::GetBook({}), "Book doesn't exist\n");
}
