#pragma once

#include <drogon/HttpController.h>
#include <functional>
#include <models/Articles.h>
#include <string>

namespace api {
class ArticlesController : public drogon::HttpController<ArticlesController> {
public:
  METHOD_LIST_BEGIN
  ADD_METHOD_TO(ArticlesController::newArticle, "/articles", drogon::Post,
                "LoginFilter");
  ADD_METHOD_TO(ArticlesController::getAllArticles,
                "/articles?tag={}&favorited={}&author={}&offset={}&limit={}",
                drogon::Get);
  METHOD_LIST_END

  void
  newArticle(drogon_model::realworld::Articles &&pNewArticle,
             std::function<void(const drogon::HttpResponsePtr &)> &&callback);

  void getAllArticles(
      const drogon::HttpRequestPtr &req,
      std::function<void(const drogon::HttpResponsePtr &)> &&callback,
      const std::string &tag, const std::string &favorited,
      const std::string &author, int offset = 0, int limit = 0);

private:
  drogon::orm::Mapper<drogon_model::realworld::Articles> articleMapper_ =
      drogon::orm::Mapper<drogon_model::realworld::Articles>(
          drogon::app().getFastDbClient());
};
} // namespace api