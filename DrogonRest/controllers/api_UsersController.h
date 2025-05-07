#pragma once

#include <drogon/HttpController.h>
#include <models/Users.h>

namespace api {
class UsersController : public drogon::HttpController<UsersController> {
public:
  METHOD_LIST_BEGIN
  ADD_METHOD_TO(UsersController::newUser, "/users", drogon::Post);
  ADD_METHOD_TO(UsersController::login, "/users/login", drogon::Post);
  ADD_METHOD_TO(UsersController::currentUser, "/user", drogon::Get,
                "LoginFilter");
  ADD_METHOD_TO(UsersController::update, "/user", drogon::Put, "LoginFilter");
  METHOD_LIST_END

  void newUser(drogon_model::realworld::Users &&pNewUser,
               std::function<void(const drogon::HttpResponsePtr &)> &&callback);

  void login(drogon_model::realworld::Users &&pNewUser,
             std::function<void(const drogon::HttpResponsePtr &)> &&callback);

  void
  currentUser(const drogon::HttpRequestPtr &req,
              std::function<void(const drogon::HttpResponsePtr &)> &&callback);

  void update(const drogon::HttpRequestPtr &req,
              std::function<void(const drogon::HttpResponsePtr &)> &&callback,
              drogon_model::realworld::Users &&pNewUser);

private:
  drogon::orm::Mapper<drogon_model::realworld::Users> userMapper_ =
      drogon::orm::Mapper<drogon_model::realworld::Users>(
          drogon::app().getFastDbClient());

  struct UserWithToken {
    std::string email;
    std::string username;
    std::string bio;
    std::string image;
    std::string token;

    explicit UserWithToken(const drogon_model::realworld::Users &user);
    Json::Value toJson() const;
  };

  void checkInputUser(const drogon_model::realworld::Users &user,
                      const std::function<void(bool)> &callback);
};
} // namespace api